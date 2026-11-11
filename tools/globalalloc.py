# SPDX-License-Identifier: AGPL-3.0-or-later
"""Replay GCC 2.95's register allocators on a function, from the compiler's own dumps.

    python3 tools/globalalloc.py FILE.cpp FUNC [--keep DIR]        compile with -dl -dg, then replay
    python3 tools/globalalloc.py --dumps DIR FUNC                  replay unit.ii.lreg/.greg in DIR
    ... [--check] [--evictions] [--trace REG ...] [--set REG:refs=N,length=N,local=H ...]
    ... [--local] [--pri REG=N ...]

global-alloc (global.c) places the pseudos local-alloc left without a register. The dumps give
its inputs but not the order of its decisions: `.lreg` has each pseudo's uses and life
(`Register N used R times across L insns`, after update_equiv_regs' doubling), local-alloc's
placements (`;; Register N in H.`) and the RTL; `.greg` has the order of the pseudos still to
place (`;; N regs to allocate:`), every pseudo's conflicts and pruned preferences, and the final
dispositions, after reload. This tool replays the allocator between the two, step by step, in
our own code, following what global.c does:

- every pseudo with uses and a life is an allocno, numbered in register order, local ones too
  (a function receiving a nonlocal goto leaves out the call-crossing ones);
- the conflicts are global_conflicts' scan of each block from its live-at-start registers: a
  register set conflicts with everything live; a pseudo local-alloc placed is also its hard
  register; clobbers go live before the insn's deaths, sets after, unused outputs die after.
  Conflicts with the eliminable registers (s8 among them) are dropped;
- the order is the priority floor_log2(refs) * refs / life * 10000 * size (8-byte words),
  truncated to an int, highest first, ties by allocno number;
- the preferences come from the RTL: a set between a pseudo and a hard register (or a pseudo
  local-alloc placed) prefers it, a plain copy also as a copy preference; merged along insns
  where one dies into the other, then pruned of conflicting and unusable registers. Each pseudo
  also avoids the registers lower-priority conflicting pseudos prefer;
- find_reg, per pseudo in order: the first register of the allocation order free of conflicts;
  pass 0 takes only registers already in use (call-clobbered ones, the RTL's, local-alloc's and
  earlier global placements), so a saved register is opened in pass 1 by the first pseudo that
  finds nothing else (also found by the func_0020CAF8 worker's emulator, build/swarm/w17-20CAF8b/
  gsim.py, docs/toolchain/long-block-constants.md, "Pass 0 takes no new saved register"); a copy
  preference, then a preference, of a compatible class replaces it; failing that, a call-crossing
  pseudo tries a call-clobbered register when caller-saves pays (4 * calls < refs); failing that,
  the "poorly used" rule: from the last register of the order down, the first holding only
  local-alloc's pseudos whose total refs per insn of life is below this pseudo's is taken, and
  every local pseudo in it loses its register (an evicted pseudo later in the order is then
  placed by global-alloc like the others; earlier ones are left to reload);
- each placement adds the register to the conflicts of every pseudo conflicting with it and
  marks it no longer local-only, so it cannot be taken by an eviction any more.

--local replays local-alloc (local-alloc.c's block_alloc) first and uses its placements:
quantities for the pseudos of one block that die once, tied where an input dies into the output
(a copy, an operation's operand, an asm's input, an indirect call's address register), hard
registers as suggestions, births and deaths at 2n / 2n+1, the suggested quantities first, then
all by priority (the same measure over birth to death), each in the first register free over
its life widened by one insn at each end, else over its life. GCC sorts two or three quantities
by hand, comparing quantities 0-2 by number; that is kept. The tie is read from the RTL, not from
the machine description's constraints, so a few placements differ where a pattern's constraints
decide. --pri REG=N sets the priority of REG's quantity (its first register) to see where the
quantities would go, and global-alloc then runs on that.

The target is the EE's: 0-31 GPRs, 32-63 FPRs, 64-66 hi/lo, 67-74 the FP condition codes (fixed),
79-110 vf0-vf31, pseudos from 116 (Sony's library compiler: the plain MIPS layout, pseudos from
80; set_target). --check compares the replay with the dumps: the order of the pseudos to allocate,
the preferences, the conflicts and the dispositions (pseudos reload spilled or re-placed,
`Register N now on stack/in H`, are left out). --evictions explains every poorly-used eviction:
which registers the scan met from the top down and why each was passed over or taken; --trace one
pseudo's turn. --set changes a pseudo's refs, life or local placement before the replay, to test a
hypothesis without compiling (local=-1 removes it). Reload's spills and retry_global_alloc are not
replayed.

Validated (2026-11-10) on every function of src/main, src/lib, src/libm and 39 of the largest near
misses, 4,501 functions: the global replay agrees with the dumps on the order, preferences,
conflicts and dispositions of all 88,502 pseudos, 20,799 global placements and 22 evictions, and
on func_00109488 (2,068 pseudos, six evictions). The local replay differs from the dumps on 970
of 67,035 local placements, none of func_00109488's 203.
"""

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import regalloc  # noqa: E402

# The target's registers. SN's game compiler (the default) numbers them 0-31 GPRs, 32-63 FPRs,
# 64-66 hi/lo, 67-74 the FP condition codes, 75 the return-address pointer, 79-110 vf0-vf31 and
# starts pseudos at 116 (FIRST_PSEUDO 112, four virtual registers); Sony's library compiler has
# the plain MIPS layout without the vector unit (FIRST_PSEUDO 76). set_target() switches.
FIRST_PSEUDO = 112
GPRS = set(range(32))
FPRS = set(range(32, 64))
VFS = set(range(79, 111))
MD_REGS = {64, 65, 66}
ST_REGS = set(range(67, 75))
# The FP condition codes act as fixed: no dump records a conflict with $fcc0 or places a pseudo
# in one (the compares set it explicitly).
FIXED = {0, 1, 26, 27, 28, 29, 31, 75, 79} | ST_REGS
CALL_USED = set()
# Hard registers that frame-pointer elimination may replace: their conflicts are dropped.
ELIMINABLE = {0, 1, 30, 75}
# Registers caller-saves cannot save around a call (no move to memory): hi, lo, the FP flags.
LOSING_CALLER_SAVE = MD_REGS | ST_REGS
# PSEUDO_REGNO_SIZE counts 8-byte words (a 16-byte pseudo is size 2: twice the priority, and
# never evicts); a GPR or a vf register holds 16 bytes as one hard register.
UNITS_PER_WORD = 8
HARD_REG_BYTES = 16
MODE_BYTES = {"QI": 1, "HI": 2, "SI": 4, "SF": 4, "DI": 8, "DF": 8, "TI": 16, "V4SF": 16, "CC": 4}
CLASSES = {}


def set_target(first_pseudo=112):
    """The register layout of the compiler whose dumps are read: 112 for SN's (game code),
    76 for Sony's (the libraries)."""
    global FIRST_PSEUDO, VFS, CALL_USED, CLASSES
    FIRST_PSEUDO = first_pseudo
    VFS = set(range(79, 111)) if first_pseudo > 76 else set()
    vu = VFS - {79}
    CALL_USED = (set(range(1, 16)) | set(range(24, 30)) | {31} | set(range(32, 52))
                 | (set(range(64, FIRST_PSEUDO)) - {79}) | FIXED)
    CLASSES = {
        "NO_REGS": set(),
        "GR_REGS": GPRS,
        "FP_REGS": FPRS,
        "VU_REGS": vu,
        "TI_REGS": GPRS | vu,
        "HI_REG": {64}, "LO_REG": {65}, "HILO_REG": {66}, "MD_REGS": {64, 65},
        "HI_AND_GR_REGS": GPRS | {64}, "LO_AND_GR_REGS": GPRS | {65}, "HILO_AND_GR_REGS": GPRS | {66},
        # The R5900's classes of both multiply units: in the dumps only hi and lo are placed.
        "HI01_REG": {64}, "LO01_REG": {65}, "HILO01_REG": {66},
        "HI01_AND_GR_REGS": GPRS | {64}, "LO01_AND_GR_REGS": GPRS | {65},
        "HILO01_AND_GR_REGS": GPRS | {66},
        "ST_REGS": ST_REGS,
        "ALL_REGS": set(range(FIRST_PSEUDO)),
    }


set_target()
# REGNO_REG_CLASS for the preference's class test (mips.c's table): the mips16 subclasses of
# the GPRs are kept, as they decide whether a preference may replace the register found.
SUBCLASS = {2: "M16_NA", 3: "M16_NA", 16: "M16_NA", 17: "M16_NA", 4: "M16", 5: "M16", 6: "M16",
            7: "M16", 24: "T"}
SUPER = {"M16_NA": {"M16_NA", "M16", "M16_T", "GR"}, "M16": {"M16", "M16_T", "GR"},
         "T": {"T", "M16_T", "GR"}, "GR": {"GR"}}
NON_E_CODES = {"reg", "const_int", "const_double", "const_string", "pc", "scratch", "label_ref",
               "symbol_ref", "unspec", "unspec_volatile", "parallel", "asm_operands", "asm_input",
               "return", "cond", "cc0", "const", "addr_vec", "addr_diff_vec"}
# (const ...) is "e" in rtl.def, but its operand is never a register: same result either way.


def regno_class(r):
    if r in GPRS:
        return SUBCLASS.get(r, "GR")
    if r in FPRS:
        return "FP"
    if r in VFS:
        return "VU"
    return "R%d" % r


def classes_compatible(a, b):
    ca, cb = regno_class(a), regno_class(b)
    if ca == cb:
        return True
    return cb in SUPER.get(ca, {ca}) or ca in SUPER.get(cb, {cb})


def hard_nregs(r, nbytes):
    if r in FPRS:
        return max(1, (nbytes + 3) // 4)
    return max(1, (nbytes + HARD_REG_BYTES - 1) // HARD_REG_BYTES)


def mode_ok(r, p):
    """HARD_REGNO_MODE_OK, as the EE's registers take this pseudo's mode."""
    if r in GPRS:
        return True
    if r in FPRS:
        return p.nbytes <= 4 and p.mode in ("SF", "SI")
    if r in VFS:
        return p.nbytes == 16
    if r in MD_REGS:
        return p.mode not in ("SF", "DF")
    if r in ST_REGS:
        return p.mode == "CC"
    return False


def floor_log2(n):
    return n.bit_length() - 1 if n > 0 else -1


# ---------------------------------------------------------------------------------------------
# The dumps

class Pseudo:
    def __init__(self, regno, refs, length, calls, pref, alt, nbytes):
        self.regno, self.refs, self.length, self.calls = regno, refs, length, calls
        self.pref, self.alt, self.nbytes = pref, alt, nbytes
        self.mode = None

    @property
    def size(self):
        return max(1, (self.nbytes + UNITS_PER_WORD - 1) // UNITS_PER_WORD)


INFO = re.compile(r"^Register (\d+) used (-?\d+) times across (-?\d+) insns(.*)$", re.M)


def balance(s, depth, instr):
    """The bracket depth after line S, and whether it ends inside a string."""
    j = 0
    while j < len(s):
        c = s[j]
        if instr:
            if c == "\\":
                j += 1
            elif c == '"':
                instr = False
        elif c == '"':
            instr = True
        elif c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        j += 1
    return depth, instr


def parse_lreg(text):
    """(pseudos by regno, local placements {regno: hard}, insns [(pattern, notes, usage)], flow)
    of one function's part of a `.lreg` dump. flow has the chain of every element's uid in
    order, each insn's index in insns by uid, and the blocks (first uid, last uid, the
    registers live at the start)."""
    pseudos = {}
    for m in INFO.finditer(text):
        rest = m.group(4)
        calls = re.search(r"crosses (\d+) calls?", rest)
        nbytes = re.search(r"(\d+) bytes", rest)
        pref, alt = "GR_REGS", "NO_REGS"
        c = re.search(r"; ([A-Z0-9_]+) or none", rest)
        if c:
            pref = c.group(1)
        else:
            c = re.search(r"; pref ([A-Z0-9_]+), else ([A-Z0-9_]+)", rest)
            if c:
                pref, alt = c.group(1), c.group(2)
        deaths = re.search(r"dies in (\d+) places?", rest)
        blk = re.search(r" in block (\d+)", rest)
        pseudos[int(m.group(1))] = Pseudo(int(m.group(1)), int(m.group(2)), int(m.group(3)),
                                          int(calls.group(1)) if calls else 0, pref, alt,
                                          int(nbytes.group(1)) if nbytes else 4)
        pseudos[int(m.group(1))].deaths = int(deaths.group(1)) if deaths else 1
        pseudos[int(m.group(1))].block = int(blk.group(1)) if blk else None
    local = {int(a): int(b) for a, b in re.findall(r"^;; Register (\d+) in (\d+)\.", text, re.M)}
    blocks = []
    for m in re.finditer(r"^Basic block \d+: first insn (\d+), last (\d+)\.\n(?:.*\n)*?Registers live at start:([^\n]*)",
                         text, re.M):
        blocks.append((int(m.group(1)), int(m.group(2)), {int(x) for x in m.group(3).split() if x.isdigit()}))
    insns, chain, at, kinds = [], [], {}, {}
    chunk, depth, instr = [], 0, False
    for s in text.splitlines():
        if chunk or (s.startswith("(") and not depth):
            chunk.append(s)
            depth, instr = balance(s, depth, instr)     # an asm string may span lines
            if depth > 0 or instr:
                continue
            sx = regalloc.parse_sexpr("\n".join(chunk))
            chunk, depth = [], 0
            if not isinstance(sx, list) or len(sx) < 2 or not str(sx[1]).isdigit():
                continue
            chain.append(int(sx[1]))
            kinds[int(sx[1])] = regalloc.head(sx)
            if regalloc.head(sx) in ("insn", "jump_insn", "call_insn") and len(sx) > 4:
                # after the pattern: the insn code, `{name}` when recognised, LOG_LINKS,
                # REG_NOTES and, for a call, CALL_INSN_FUNCTION_USAGE
                rest = [x for x in sx[5:] if isinstance(x, list) or x == "nil"]
                notes = rest[1] if len(rest) > 1 else None
                usage = rest[2] if regalloc.head(sx) == "call_insn" and len(rest) > 2 else None
                at[int(sx[1])] = len(insns)
                insns.append((sx[4], notes, usage))
    for ins in insns:
        for x in regalloc._flat(ins[0]):
            if code(x) == "reg" and int(x[1]) in pseudos and pseudos[int(x[1])].mode is None:
                pseudos[int(x[1])].mode = mode_of(x)
    return pseudos, local, insns, dict(chain=chain, at=at, blocks=blocks, kind=kinds)


def parse_greg(text):
    """The global pass's own record: {order, conflicts, preferences, disposition, changed}."""
    out = dict(order=[], conflicts={}, preferences={}, disposition={}, changed=set(), spilled=[])
    lines = text.splitlines()
    i = 0
    while i < len(lines):
        s = lines[i]
        i += 1
        if not s.startswith((";;", " Register", "Spilling reg")):
            continue
        m = re.match(r"^;; \d+ regs to allocate:(.*)$", s)
        if m:
            out["order"] = [int(x.split("+")[0]) for x in re.sub(r"\(\d+\)", "", m.group(1)).split()]
            continue
        m = re.match(r"^;; (\d+) (conflicts|preferences):(.*)$", s)
        if m:
            key = "conflicts" if m.group(2) == "conflicts" else "preferences"
            out[key][int(m.group(1))] = [int(x) for x in m.group(3).split()]
            continue
        m = re.match(r"^ Register (\d+) now (?:on stack|in \d+)\.", s)
        if m:
            out["changed"].add(int(m.group(1)))
            continue
        m = re.match(r"^Spilling reg (\d+)\.", s)
        if m:
            out["spilled"].append(int(m.group(1)))
            continue
        if s.startswith(";; Register dispositions:"):
            while i < len(lines) and lines[i].strip() and not lines[i].startswith(";;"):
                for a, b in re.findall(r"(\d+) in (\d+)", lines[i]):
                    out["disposition"][int(a)] = int(b)
                i += 1
    return out


def function_part(text, func):
    part = regalloc.function_part(text, func)
    if part is None:
        raise SystemExit("no ';; Function' part for %s in the dump" % func)
    return part


# ---------------------------------------------------------------------------------------------
# RTL helpers for the preferences

def code(x):
    return regalloc.head(x)


def mode_of(x):
    if isinstance(x, list) and x and isinstance(x[0], str) and ":" in x[0]:
        return x[0].split(":")[1]
    return None


def stores(pattern):
    """note_stores: [(dest, setter)] of a pattern, the destination stripped of subregs of
    pseudos and of partial-store wrappers; setter is the SET or CLOBBER."""
    out = []

    def one(x):
        h = code(x)
        if h in ("set", "clobber"):
            d = x[1]
            while True:
                hd = code(d)
                if hd == "subreg" and not (code(d[1]) == "reg" and int(d[1][1]) < FIRST_PSEUDO):
                    d = d[1]
                elif hd in ("zero_extract", "sign_extract", "strict_low_part"):
                    d = d[1]
                else:
                    break
            out.append((d, x))
        elif h == "parallel":
            # last element first, as note_stores walks a PARALLEL
            for y in reversed(x[1][1:] if isinstance(x[1], list) and x[1] and x[1][0] == "[" else x[1:]):
                one(y)

    one(pattern)
    return out


def note_list(notes):
    """[(kind, datum)] of a REG_NOTES chain."""
    out = []
    while isinstance(notes, list) and notes and isinstance(notes[0], str) and notes[0] != "nil":
        kind = notes[0].split(":")[1] if ":" in notes[0] else notes[0]
        out.append((kind, notes[1] if len(notes) > 1 else None))
        notes = notes[2] if len(notes) > 2 else None
    return out


def reg_of(x):
    """(regno, word offset) of a REG or a SUBREG of one, else None."""
    if code(x) == "reg":
        return int(x[1]), 0
    if code(x) == "subreg" and code(x[1]) == "reg":
        return int(x[1][1]), int(x[2])
    return None


# ---------------------------------------------------------------------------------------------
# The model

class Model:
    def __init__(self, pseudos, local, insns, greg, need_fp=False, log=None):
        self.p = pseudos
        self.local = dict(local)
        self.insns = insns
        self.greg = greg
        self.need_fp = need_fp
        self.events = []
        self.recompute = False     # compute the conflicts from the RTL instead of the dump
        self.verify = False        # compute them too, to compare with the dump

    # -- setup, as global_alloc does it

    def setup(self):
        P = self.p
        self.regs = [r for r in sorted(P) if P[r].refs != 0 and P[r].length != -1]
        # A function that receives a nonlocal goto (the unwinder's) keeps call-crossing pseudos
        # out of the allocation; the dump shows it as conflict lines missing for them.
        printed = set(self.greg["conflicts"])
        if printed and any(r not in printed and P[r].calls for r in self.regs):
            self.regs = [r for r in self.regs if not P[r].calls]
        self.allocno = {r: a for a, r in enumerate(self.regs)}
        self.renumber = dict(self.local)
        ever = set()
        for pattern, notes, usage in self.insns:
            for r in regalloc.regs_in(pattern) + (regalloc.regs_in(usage) if usage else []):
                if r < FIRST_PSEUDO:
                    ever.add(r)
        self.ever_live = ever
        self.used_so_far = (ever | CALL_USED) | set(self.local.values())
        self.no_global = {30} if self.need_fp else set()
        self.local_refs, self.local_len = {}, {}
        for r, h in self.local.items():
            p = P[r]
            for j in range(h, h + hard_nregs(h, p.nbytes)):
                self.local_refs[j] = self.local_refs.get(j, 0) + p.refs
                self.local_len[j] = self.local_len.get(j, 0) + p.length
        for j in ever:
            self.local_refs[j] = 0
        # conflicts: from the .greg dump, or computed from the RTL as global_conflicts does
        # (always when a local placement was changed, since they depend on it)
        self.dumped_conf, self.dumped_hard = self.conflicts_from_dump()
        if self.recompute or self.verify or not self.greg["conflicts"]:
            self.computed = self.compute_conflicts()
        if self.recompute or not self.greg["conflicts"]:
            self.conf = self.computed[0]
            self.hard_conf = {r: set(v) for r, v in self.computed[1].items()}   # grows as regs are placed
        else:
            self.conf, self.hard_conf = self.dumped_conf, {r: set(v) for r, v in self.dumped_hard.items()}
        self.build_preferences()
        self.expand_preferences()
        self.order = sorted(self.regs, key=lambda r: (-self.priority(r), self.allocno[r]))
        self.prune_preferences()

    def conflicts_from_dump(self):
        conf = {r: set() for r in self.regs}
        hard = {r: set() for r in self.regs}
        for r, lst in self.greg["conflicts"].items():
            if r not in conf:
                continue
            for x in lst:
                if x >= FIRST_PSEUDO:
                    if x in conf:
                        conf[r].add(x)
                        conf[x].add(r)
                else:
                    hard[r].add(x)
        for r in self.regs:
            hard[r] -= ELIMINABLE
        return conf, hard

    def compute_conflicts(self):
        """global_conflicts: scan each block forward from the registers live at its start.
        A register set conflicts with everything live then; a pseudo local-alloc placed acts
        as its hard register too. Clobbers go live before the insn's deaths, sets after."""
        index = {r: i for i, r in enumerate(self.regs)}
        regs = self.regs
        conflicts = [0] * len(regs)
        hconf = {}                # hard reg -> bitset of allocnos that conflict with it
        state = {}

        def nregs_of(x, h):
            m = mode_of(x)
            nb = MODE_BYTES.get(m, 4)
            return hard_nregs(h, nb)

        def one_hard(h):
            hconf[h] = hconf.get(h, 0) | state["live"]

        def one_pseudo(a):
            conflicts[a] |= state["live"]
            for h in state["hard"]:
                hconf[h] = hconf.get(h, 0) | (1 << a)

        def store(x, setter):
            if code(x) == "subreg":
                x = x[1]
            if code(x) != "reg":
                return
            state["set"].append(x)
            r = int(x[1])
            if r >= FIRST_PSEUDO and r in index:
                state["live"] |= 1 << index[r]
                one_pseudo(index[r])
            h = self.renumber.get(r, -1) if r >= FIRST_PSEUDO else r
            if 0 <= h < FIRST_PSEUDO and h not in FIXED:
                for j in range(h, h + nregs_of(x, h)):
                    one_hard(j)
                    state["hard"].add(j)

        def death(x):
            r = int(x[1])
            if r >= FIRST_PSEUDO and r in index:
                state["live"] &= ~(1 << index[r])
            h = self.renumber.get(r, -1) if r >= FIRST_PSEUDO else r
            if 0 <= h < FIRST_PSEUDO and h not in FIXED:
                for j in range(h, h + nregs_of(x, h)):
                    state["hard"].discard(j)

        pos = {u: k for k, u in enumerate(self.flow["chain"])}
        for first, last, start in self.flow["blocks"]:
            state["live"], state["hard"] = 0, set()
            vec = []
            for r in sorted(start):
                if r < FIRST_PSEUDO:
                    state["hard"].add(r)            # fixed ones too: they never die
                elif r in index:
                    state["live"] |= 1 << index[r]
                    vec.append(index[r])
                elif self.renumber.get(r, -1) >= 0:
                    state["hard"].add(self.renumber[r])
            for a in vec:
                conflicts[a] |= state["live"]
                for h in state["hard"]:
                    hconf[h] = hconf.get(h, 0) | (1 << a)
            for k in range(pos[first], pos[last] + 1):
                i = self.flow["at"].get(self.flow["chain"][k])
                if i is None:
                    continue
                pattern, notes, usage = self.insns[i]
                state["set"] = []
                nl = note_list(notes)
                sts = stores(pattern)
                for d, setter in sts:
                    if code(setter) == "clobber":
                        store(d, setter)
                for kind, datum in nl:
                    if kind == "REG_DEAD" and code(datum) == "reg":
                        death(datum)
                for d, setter in sts:
                    store(d, setter)
                if code(pattern) == "parallel" and sum(1 for d, st in sts if code(st) == "set") > 1:
                    outs = [st[1] for d, st in sts if code(st) == "set" and code(st[1]) != "reg"]
                    for kind, datum in nl:
                        if kind == "REG_DEAD" and code(datum) == "reg":
                            r = int(datum[1])
                            if any(r in regalloc.regs_in(o) for o in outs):
                                if r >= FIRST_PSEUDO and r in index:
                                    one_pseudo(index[r])
                                h = self.renumber.get(r, -1) if r >= FIRST_PSEUDO else r
                                if 0 <= h < FIRST_PSEUDO and h not in FIXED:
                                    one_hard(h)
                unused = {int(d[1]) for kind, d in nl if kind == "REG_UNUSED" and code(d) == "reg"}
                for x in reversed(state["set"]):
                    if int(x[1]) in unused:
                        death(x)
        conf = {r: set() for r in regs}
        for a, r in enumerate(regs):
            bits, j = conflicts[a], 0
            while bits:
                if bits & 1:
                    conf[r].add(regs[j])
                    conf[regs[j]].add(r)
                bits >>= 1
                j += 1
        hard = {r: set() for r in regs}
        for h, bits in hconf.items():
            if h in ELIMINABLE:
                continue
            j = 0
            while bits:
                if bits & 1:
                    hard[regs[j]].add(h)
                bits >>= 1
                j += 1
        return conf, hard

    def priority(self, r):
        p = self.p[r]
        length = p.length if p.length != 0 else -1
        return int(float(floor_log2(p.refs) * p.refs) / length * 10000 * p.size)

    def build_preferences(self):
        self.prefs = {r: set() for r in self.regs}
        self.copy_prefs = {r: set() for r in self.regs}
        for pattern, notes, usage in self.insns:
            for dest, setter in stores(pattern):
                if code(setter) == "set":
                    self.set_preference(dest, setter[2])

    def set_preference(self, dest, src):
        copy = True
        if code(src) not in NON_E_CODES and isinstance(src, list) and len(src) > 1:
            src, copy = src[1], False
        s, d = reg_of(src), reg_of(dest)
        if s is None or d is None:
            return
        (sr, so), (dr, do) = s, d
        offset = so - do
        if sr in self.renumber:
            sr = self.renumber[sr]
        if dr in self.renumber:
            dr = self.renumber[dr]
        if dr < FIRST_PSEUDO <= sr and sr in self.allocno:
            h = dr - offset
            if 0 <= h < FIRST_PSEUDO:
                if copy:
                    self.copy_prefs[sr].add(h)
                self.prefs[sr].add(h)
        if sr < FIRST_PSEUDO <= dr and dr in self.allocno:
            h = sr + offset
            if 0 <= h < FIRST_PSEUDO:
                if copy:
                    self.copy_prefs[dr].add(h)
                self.prefs[dr].add(h)

    def expand_preferences(self):
        for h in (self.prefs, self.copy_prefs):
            for r in h:
                h[r] -= ELIMINABLE
        for pattern, notes, usage in self.insns:
            sets = [x for x in stores(pattern) if code(x[1]) == "set"]
            unused = {reg_of(d)[0] for k, d in note_list(notes) if k == "REG_UNUSED" and reg_of(d)}
            live_sets = [x for x in sets if not (reg_of(x[1][1]) and reg_of(x[1][1])[0] in unused)]
            if len(sets) == 1:
                one = sets[0][1]
            elif len(live_sets) == 1:
                one = live_sets[0][1]
            else:
                continue
            if code(one[1]) != "reg":
                continue
            a1 = int(one[1][1])
            if a1 not in self.allocno:
                continue
            for kind, datum in note_list(notes):
                if kind != "REG_DEAD" or code(datum) != "reg":
                    continue
                a2 = int(datum[1])
                if a2 not in self.allocno or a2 in self.conf[a1]:
                    continue
                if code(one[2]) == "reg" and int(one[2][1]) == a2:
                    u = self.copy_prefs[a1] | self.copy_prefs[a2]
                    self.copy_prefs[a1], self.copy_prefs[a2] = set(u), set(u)
                u = self.prefs[a1] | self.prefs[a2]
                self.prefs[a1], self.prefs[a2] = set(u), set(u)

    def class_of(self, r, alt=False):
        name = self.p[r].alt if alt else self.p[r].pref
        if name not in CLASSES:
            raise SystemExit("unknown register class %s (pseudo %d): add it to CLASSES" % (name, r))
        return CLASSES[name]

    def prune_preferences(self):
        self.someone = {}
        for i in range(len(self.order) - 1, -1, -1):
            a = self.order[i]
            temp = set(self.hard_conf[a])
            temp |= FIXED if self.p[a].calls == 0 else CALL_USED
            temp |= set(range(FIRST_PSEUDO)) - self.class_of(a)
            self.prefs[a] -= temp
            self.copy_prefs[a] -= temp
            some = set()
            for j in self.order[i + 1:]:
                if j in self.conf[a]:
                    t = set(self.prefs[j])
                    if self.p[j].size <= self.p[a].size:
                        t -= self.prefs[a]
                    some |= t
            self.someone[a] = some

    # -- allocation

    def run(self):
        self.setup()
        self.step = 0
        self.taken_by = {}       # hard reg -> (step, pseudo, how) when it stopped being local-only
        for j in self.ever_live:
            self.taken_by[j] = (None, None, "used in the RTL")
        for r in self.order:
            self.step += 1
            if self.renumber.get(r, -1) >= 0 or self.p[r].length < 0:
                continue
            self.find_reg(r, set(), False, False)
            if self.renumber.get(r, -1) < 0 and self.p[r].alt != "NO_REGS":
                self.find_reg(r, set(), True, False)
            if self.renumber.get(r, -1) < 0:
                self.events.append(dict(kind="none", reg=r, step=self.step))
        return self.renumber

    def find_reg(self, a, losers, alt, accept_cc, trace=None):
        p = self.p[a]
        cls = self.class_of(a, alt)
        allregs = set(range(FIRST_PSEUDO))
        if accept_cc:
            used1 = set(FIXED)
        elif p.calls == 0:
            used1 = set(FIXED)
        else:
            used1 = set(CALL_USED)
        used1 |= self.no_global | losers | (allregs - cls)
        used2 = set(used1)
        used1 |= self.hard_conf[a]
        used = used1 | (allregs - self.used_so_far) | self.someone[a]
        best, how = -1, None
        for pss in (0, 1):
            if pss == 1:
                used = set(used1)
            for regno in range(FIRST_PSEUDO):
                if regno not in used and mode_ok(regno, p):
                    lim = regno + hard_nregs(regno, p.nbytes)
                    if all(j not in used for j in range(regno + 1, lim)):
                        best, how = regno, "pass %d" % pss
                        break
            if best >= 0:
                break
        for prefs, name in ((self.copy_prefs, "copy preference"), (self.prefs, "preference")):
            # A preference of a class compatible with the register found replaces it; the copy
            # preferences are tried first, and a hit there skips the plain ones.
            prefs[a] -= used
            if not prefs[a] or best < 0:
                continue
            hit = None
            for i in range(FIRST_PSEUDO):
                if i in prefs[a] and mode_ok(i, p) and classes_compatible(i, best):
                    lim = i + hard_nregs(i, p.nbytes)
                    if all(j not in used and classes_compatible(j, best + j - i) for j in range(i + 1, lim)):
                        hit = i
                        break
            if hit is not None:
                best, how = hit, name
                break
        if best < 0 and not accept_cc and p.calls and 4 * p.calls < p.refs:
            self.find_reg(a, losers | LOSING_CALLER_SAVE, alt, True)
            if self.renumber.get(a, -1) >= 0:
                self.events[-1]["how"] += " (caller-saved)"
                return
        if best < 0 and p.size == 1 and not getattr(self, "retrying", False):
            mine = float(p.refs) / (p.length if p.length else -1)
            scan = []
            for regno in range(FIRST_PSEUDO - 1, -1, -1):
                lr = self.local_refs.get(regno, 0)
                if lr == 0:
                    if regno in cls and regno not in used2 and regno in self.taken_by:
                        scan.append((regno, "not local-only", self.taken_by.get(regno)))
                    continue
                if regno in used2 or not mode_ok(regno, p):
                    continue
                theirs = float(lr) / self.local_len[regno]
                if theirs < mine:
                    gone = [k for k, h in self.renumber.items() if h >= 0 and h <= regno < h + hard_nregs(h, self.p[k].nbytes)]
                    for k in gone:
                        self.renumber[k] = -1
                    scan.append((regno, "taken: %.6f < %.6f" % (theirs, mine), gone))
                    self.events.append(dict(kind="evict", reg=a, step=self.step, hard=regno, gone=gone,
                                            scan=scan, mine=mine))
                    best, how = regno, "evicted %s" % " ".join(map(str, gone))
                    break
                scan.append((regno, "kept: %.6f >= %.6f" % (theirs, mine), None))
        if best >= 0:
            self.renumber[a] = best
            lim = best + hard_nregs(best, p.nbytes)
            for j in range(best, lim):
                self.used_so_far.add(j)
                if self.local_refs.get(j, 0):
                    self.taken_by[j] = (self.step, a, how)
                elif j not in self.taken_by:
                    self.taken_by[j] = (self.step, a, how)
                self.local_refs[j] = 0
            for j in self.conf[a]:
                self.hard_conf[j] |= set(range(best, lim))
            self.events.append(dict(kind="place", reg=a, step=self.step, hard=best, how=how))


# ---------------------------------------------------------------------------------------------
# local-alloc's quantities

ARITH = {"plus", "minus", "mult", "div", "udiv", "mod", "umod", "and", "ior", "xor", "ashift",
         "ashiftrt", "lshiftrt", "rotate", "rotatert", "neg", "not", "abs", "sqrt", "smax", "smin",
         "umax", "umin", "sign_extend", "zero_extend", "truncate", "float_extend",
         "float_truncate", "float", "fix", "unsigned_float", "unsigned_fix", "lo_sum",
         "eq", "ne", "lt", "ltu", "gt", "gtu", "le", "leu", "ge", "geu"}
LIKELY_SPILLED = {24, 64, 65, 66}         # hard registers of a class of one (T_REG, hi, lo)


class LocalModel:
    """block_alloc, per block: quantities for the pseudos local to the block that die once,
    tied along insns where an input dies into the output (a copy, an operation's first or
    second operand, the low part of an address), births and deaths at 2n / 2n+1 of the insn
    count, the suggested hard registers first, then every quantity by priority
    floor_log2(refs) * refs * size / (death - birth), shortest life and most uses first, in the
    first register of the order free over its life (one insn longer at each end first, as
    INSN_SCHEDULING asks). The tie is read from the RTL, not from the machine description's
    constraints: an approximation that --check-local measures against the dump."""

    def __init__(self, pseudos, insns, flow):
        self.p, self.insns, self.flow = pseudos, insns, flow
        self.log = []

    def eligible(self, r):
        p = self.p.get(r)
        return p is not None and p.block is not None and p.deaths == 1

    def run(self, priority_override=None):
        out = {}
        pos = {u: k for k, u in enumerate(self.flow["chain"])}
        for b, (first, last, start) in enumerate(self.flow["blocks"]):
            out.update(self.block(b, pos[first], pos[last], start, priority_override))
        return out

    def block(self, b, lo, hi, start, override):
        qty_of, qtys = {}, []
        live = {r for r in start if r < FIRST_PSEUDO}
        occ = {}                  # hard reg -> bitset of indices where it is live

        def mark(h, a, z):
            occ[h] = occ.get(h, 0) | (((1 << (z - a)) - 1) << a)

        n = 0
        livemask_at = []
        elig = lambda r: r >= FIRST_PSEUDO and self.eligible(r) and self.p[r].block == b

        def new_qty(r, birth):
            q = dict(regs=[r], birth=birth, death=-1, refs=self.p[r].refs, size=self.p[r].size,
                     cls=self.p[r].pref, alt=self.p[r].alt, sugg=set(), copy=set(), nbytes=self.p[r].nbytes, calls=self.p[r].calls,
                     p=self.p[r], num=len(qtys))
            qtys.append(q)
            qty_of[r] = q
            return q

        def born(x, birth):
            r = int(x[1])
            if r < FIRST_PSEUDO:
                if r not in FIXED:
                    live.add(r)
                    if birth < 2 * n:
                        mark(r, birth, 2 * n)
                return
            if elig(r):
                q = qty_of.get(r) or new_qty(r, birth)
                q["death"] = -1

        def died(x, output):
            r = int(x[1])
            if r < FIRST_PSEUDO:
                live.discard(r)
                if output:
                    mark(r, 2 * n, 2 * n + 1)
                return
            if r in qty_of:
                qty_of[r]["death"] = 2 * n + output

        def combine(used, setr, copy):
            if code(used) == "subreg":
                used = used[1]
            if code(setr) == "subreg":
                setr = setr[1]
            if code(used) != "reg" or code(setr) != "reg":
                return False
            u, sreg = int(used[1]), int(setr[1])
            if u >= FIRST_PSEUDO and u not in qty_of:
                return False
            if sreg >= FIRST_PSEUDO and not elig(sreg):
                return False
            if u == sreg or (u < FIRST_PSEUDO and sreg < FIRST_PSEUDO):
                return False
            if u in LIKELY_SPILLED or sreg in LIKELY_SPILLED:
                return False
            if mode_of(used) != mode_of(setr) and not ({mode_of(used), mode_of(setr)} <= {"SI", "DI", "HI", "QI"}):
                return False
            if u < FIRST_PSEUDO:
                q = qty_of.get(sreg)
                if q is None:
                    q = new_qty(sreg, 2 * n)
                    q["death"] = -1
                (q["copy"] if copy else q["sugg"]).add(u)
                return False
            if sreg < FIRST_PSEUDO:
                (qty_of[u]["copy"] if copy else qty_of[u]["sugg"]).add(sreg)
                return False
            if sreg in qty_of:
                return False
            if not any(k == "REG_DEAD" and code(d) == "reg" and int(d[1]) == u for k, d in nl):
                return False
            q = qty_of[u]
            pc, sc = CLASSES.get(self.p[sreg].pref, set()), CLASSES.get(q["cls"], set())
            if not (pc <= sc or sc <= pc):
                return False
            q["regs"].append(sreg)
            qty_of[sreg] = q
            if pc < sc:
                q["cls"] = self.p[sreg].pref
            q["refs"] += self.p[sreg].refs
            q["calls"] += self.p[sreg].calls
            return True

        for k in range(lo, hi + 1):
            uid = self.flow["chain"][k]
            kind = self.flow["kind"].get(uid)
            if kind != "note":
                n += 1
            i = self.flow["at"].get(uid)
            if i is not None:
                pattern, notes, usage = self.insns[i]
                nl = note_list(notes)
                combined = None
                sets = [st for d, st in reversed(stores(pattern)) if code(st) == "set"]
                if len(sets) >= 1 and code(pattern) in ("set", "parallel"):
                    st = sets[0]
                    r0, src = st[1], st[2]
                    if code(r0) in ("reg", "subreg"):
                        if code(src) in ("reg", "subreg"):
                            cands = [(src, True)]
                        elif code(src) in ARITH:
                            cands = [(x, False) for x in src[1:] if code(x) in ("reg", "subreg")]
                        elif code(src) == "call" and code(src[1]) == "mem" and code(src[1][1]) == "reg":
                            cands = [(src[1][1], False)]      # an indirect call's address register
                        elif code(src) == "asm_operands" and len(src) > 4 and isinstance(src[4], list):
                            # an asm's inputs, unless its first output is early-clobbered
                            con = str(src[2][0] if isinstance(src[2], list) and src[2] else src[2])
                            cands = [] if not con.startswith("=") or con.startswith("=&") else [
                                (x, False) for x in src[4][1:] if code(x) in ("reg", "subreg")]
                        else:
                            cands = []
                        for x, cp in cands:
                            if combine(x, r0, cp):
                                combined = int((x[1] if code(x) == "subreg" else x)[1])
                                break
                for kd, d in nl:
                    if kd == "REG_DEAD" and code(d) == "reg" and int(d[1]) != combined:
                        died(d, 0)
                for d, st in stores(pattern):
                    if code(d) in ("reg", "subreg"):
                        born(d if code(d) == "reg" else d[1], 2 * n - (code(st) == "clobber"))
                for kd, d in nl:
                    if kd == "REG_UNUSED" and code(d) == "reg":
                        died(d, 1)
            for h in live:
                mark(h, 2 * n, 2 * n + 2)
        total = n

        def pri(q):
            if override and q["regs"][0] in override:
                return override[q["regs"][0]]
            return int(float(floor_log2(q["refs"]) * q["refs"] * q["size"]) / (q["death"] - q["birth"]) * 10000)

        base = set(FIXED) | {0, 75, 30}

        def free(q, cls, born_i, dead_i, only=None):
            if dead_i <= born_i:
                dead_i = born_i
            width = ((1 << (dead_i - born_i)) - 1) << born_i
            for h in range(FIRST_PSEUDO):
                if h in base or h not in CLASSES.get(cls, set()) or (only is not None and h not in only):
                    continue
                if not mode_ok(h, q["p"]) or occ.get(h, 0) & width:
                    continue
                if q["calls"] and h in CALL_USED:
                    continue
                mark(h, born_i, dead_i)
                return h
            return -1

        def sugg_key(q):
            return len(q["copy"]) if q["copy"] else len(q["sugg"]) * FIRST_PSEUDO

        def order(key):
            # qsort with the qty number as the last key; for two or three quantities GCC sorts by
            # hand, comparing quantities 0, 1 and 2 by number whatever has been exchanged
            seq = list(qtys)
            if len(seq) in (2, 3):
                def cmp(a, b):
                    ka, kb = key(qtys[a]), key(qtys[b])
                    return (ka > kb) - (ka < kb)
                if len(seq) == 3:
                    if cmp(0, 1) > 0:
                        seq[0], seq[1] = seq[1], seq[0]
                    if cmp(1, 2) > 0:
                        seq[2], seq[1] = seq[1], seq[2]
                if cmp(0, 1) > 0:
                    seq[0], seq[1] = seq[1], seq[0]
                return seq
            return sorted(seq, key=lambda q: (key(q), q["num"]))

        phys = {}
        for q in order(lambda q: (sugg_key(q), -pri(q))):
            if not (q["sugg"] or q["copy"]):
                continue
            h = free(q, q["cls"], q["birth"], q["death"], q["copy"] or q["sugg"])
            if h < 0 and q["copy"] and q["sugg"]:
                h = free(q, q["cls"], q["birth"], q["death"], q["sugg"])
            phys[q["num"]] = h
        for q in order(lambda q: -pri(q)):
            if phys.get(q["num"], -1) >= 0:
                continue
            fb = max(0, q["birth"] - 2 + q["birth"] % 2)
            fd = min(total * 2 + 1, q["death"] + 2 - q["death"] % 2)
            h = free(q, q["cls"], fb, fd)
            if h < 0:
                h = free(q, q["cls"], q["birth"], q["death"])
            if h < 0 and q["alt"] != "NO_REGS":
                h = free(q, q["alt"], fb, fd)
                if h < 0:
                    h = free(q, q["alt"], q["birth"], q["death"])
            phys[q["num"]] = h
            self.log.append((q["regs"][0], pri(q), q["birth"], q["death"], h))
        self.qtys = qtys
        out = {}
        for q in qtys:
            if phys.get(q["num"], -1) >= 0:
                for r in q["regs"]:
                    out[r] = phys[q["num"]]
        return out


# ---------------------------------------------------------------------------------------------
# Checking and reporting

def check(model, out=sys.stdout):
    """Compare the replay with the dumps; returns the number of disagreements."""
    g, bad = model.greg, 0
    mine = [r for r in model.order if r not in model.local]
    if mine != g["order"]:
        k = next((i for i, (x, y) in enumerate(zip(mine, g["order"])) if x != y), min(len(mine), len(g["order"])))
        print("order: differs at %d of %d (ours %s, dump %s)" % (k, len(g["order"]), mine[k:k + 3], g["order"][k:k + 3]), file=out)
        bad += 1
    else:
        print("order: %d pseudos to allocate, as the dump" % len(mine), file=out)
    pd = 0
    for r in model.regs:
        dumped = set(g["preferences"].get(r, []))
        if dumped != model.prefs_at_dump.get(r, set()):
            pd += 1
            if pd <= 5:
                print("preferences of %d: ours %s, dump %s" % (r, sorted(model.prefs_at_dump.get(r, ())), sorted(dumped)), file=out)
    print("preferences: %d of %d pseudos differ" % (pd, len(model.regs)), file=out)
    bad += pd
    if getattr(model, "computed", None) and g["conflicts"]:
        conf, hard = model.computed
        cd = 0
        for r in model.regs:
            if conf[r] != model.dumped_conf[r] or hard[r] != model.dumped_hard[r]:
                cd += 1
                if cd <= 5:
                    print("conflicts of %d: pseudos +%s -%s, hard +%s -%s" % (
                        r, sorted(conf[r] - model.dumped_conf[r])[:8], sorted(model.dumped_conf[r] - conf[r])[:8],
                        sorted(hard[r] - model.dumped_hard[r]), sorted(model.dumped_hard[r] - hard[r])), file=out)
        print("conflicts: %d of %d pseudos differ from the dump's" % (cd, len(model.regs)), file=out)
        bad += cd
    disp, changed = g["disposition"], g["changed"]
    agree = dd = 0
    for r in model.regs:
        if r in changed:
            continue
        ours = model.renumber.get(r, -1)
        theirs = disp.get(r, -1)
        if ours == theirs:
            agree += 1
        else:
            dd += 1
            if dd <= 10:
                print("pseudo %d: replay %s, dump %s" % (r, ours, theirs), file=out)
    print("dispositions: %d agree, %d differ, %d left to reload" % (agree, dd, len(changed & set(model.regs))), file=out)
    return bad + dd


def report_evictions(model, out=sys.stdout, only=None):
    for e in model.events:
        if e["kind"] != "evict" or (only and e["reg"] not in only):
            continue
        p = model.p[e["reg"]]
        print("step %d: pseudo %d (%d refs / %d insns = %.6f) takes %s, evicting %s" % (
            e["step"], e["reg"], p.refs, p.length, e["mine"], regalloc.reg_name(e["hard"]),
            " ".join("%d" % k for k in e["gone"])), file=out)
        for regno, why, extra in e["scan"]:
            if why == "not local-only":
                st = extra
                if st and st[0] is not None:
                    why = "already global's: step %d, pseudo %d (%s)" % st
                elif st:
                    why = "not local-only: %s" % st[2]
                else:
                    why = "no local pseudo"
            print("    %-6s %s" % (regalloc.reg_name(regno), why), file=out)


def trace(model, r, out=sys.stdout):
    p = model.p[r]
    print("pseudo %d: %d refs, %d insns, %d calls, %s; priority %d, position %d of %d; local %s" % (
        r, p.refs, p.length, p.calls, p.pref, model.priority(r), model.order.index(r) + 1,
        len(model.order), model.local.get(r)), file=out)
    for e in model.events:
        if e.get("reg") == r:
            print("    step %d: %s" % (e["step"], {k: v for k, v in e.items() if k not in ("scan",)}), file=out)
        elif e["kind"] == "evict" and r in e["gone"]:
            print("    evicted at step %d by pseudo %d from %s" % (e["step"], e["reg"], regalloc.reg_name(e["hard"])), file=out)
    print("    final: %s" % model.renumber.get(r, -1), file=out)


def apply_sets(pseudos, local, sets):
    for s in sets or []:
        reg, _, kv = s.partition(":")
        r = int(reg)
        for item in kv.split(","):
            k, _, v = item.partition("=")
            if k == "local":
                if int(v) < 0:
                    local.pop(r, None)
                else:
                    local[r] = int(v)
            else:
                setattr(pseudos[r], k, int(v))


def load(folder, func):
    folder = Path(folder)
    lreg = function_part((folder / "unit.ii.lreg").read_text(errors="replace"), func)
    greg = function_part((folder / "unit.ii.greg").read_text(errors="replace"), func)
    return lreg, greg


def model_from_text(lreg, greg, sets=None, need_fp=False):
    first = min((int(x) for x in re.findall(r"^Register (\d+) used", lreg, re.M)), default=116)
    set_target(76 if first < 116 else 112)
    pseudos, local, insns, flow = parse_lreg(lreg)
    apply_sets(pseudos, local, sets)
    m = Model(pseudos, local, insns, parse_greg(greg), need_fp=need_fp)
    m.flow = flow
    return m


def replay(m, verify=False):
    m.verify = verify
    orig_prune = m.prune_preferences

    def prune_and_keep():
        orig_prune()
        m.prefs_at_dump = {r: set(v) for r, v in m.prefs.items()}
    m.prune_preferences = prune_and_keep
    m.run()
    return m


def compile_dumps(path, func, keep):
    import compile as cc
    import check as chk
    path = Path(path)
    source = chk.source_for(path, func)
    flags = cc.flags_for(source) + ["-dl", "-dg"]
    keep = Path(keep)
    keep.mkdir(parents=True, exist_ok=True)
    cc.compile_file(path, keep / "unit.o", flags, source=source, keep_dumps=keep)
    return keep


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("file", nargs="?", help="the .cpp to compile with -dl -dg")
    ap.add_argument("func")
    ap.add_argument("--dumps", help="a folder holding unit.ii.lreg and unit.ii.greg")
    ap.add_argument("--keep", help="where to keep the dumps (default build/globalalloc/FUNC)")
    ap.add_argument("--check", action="store_true", help="compare the replay with the dumps")
    ap.add_argument("--evictions", action="store_true", help="explain every poorly-used eviction")
    ap.add_argument("--trace", type=int, action="append", help="explain one pseudo's turn")
    ap.add_argument("--set", action="append", help="REG:refs=N,length=N,local=H before the replay")
    ap.add_argument("--need-fp", action="store_true", help="the function keeps a frame pointer")
    ap.add_argument("--local", action="store_true",
                    help="replay local-alloc too, compare it with the dump and use its placements")
    ap.add_argument("--pri", action="append", help="REG=N: local-alloc priority of REG's quantity (implies --local)")
    args = ap.parse_args(argv)
    if args.dumps:
        folder = Path(args.dumps)
    else:
        if not args.file:
            ap.error("give FILE.cpp or --dumps DIR")
        folder = compile_dumps(args.file, args.func, args.keep or regalloc.ROOT / "build" / "globalalloc" / args.func)
    lreg, greg = load(folder, args.func)
    m = model_from_text(lreg, greg, args.set, args.need_fp)
    m.recompute = any("local=" in x for x in args.set or [])
    if args.local or args.pri:
        override = {int(k): int(v) for k, v in (x.split("=") for x in args.pri or [])}
        placed = LocalModel(m.p, m.insns, m.flow).run(override)
        moved = sorted(r for r in set(placed) | set(m.local) if placed.get(r) != m.local.get(r))
        print("local-alloc: %d placements, %d differ from the dump%s" % (
            len(placed), len(moved), (": " + " ".join("%d:%s>%s" % (r, m.local.get(r), placed.get(r))
                                                       for r in moved[:20])) if moved else ""))
        m.local, m.recompute = placed, True
    m = replay(m, verify=args.check)
    status = 0
    if args.check or not (args.evictions or args.trace):
        status = 1 if check(m) else 0
    if args.evictions:
        report_evictions(m)
    for r in args.trace or []:
        trace(m, r)
    return status


if __name__ == "__main__":
    sys.exit(main())
