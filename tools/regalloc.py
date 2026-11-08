# SPDX-License-Identifier: AGPL-3.0-or-later
"""Explain where a near miss's registers differ from retail's, from the compiler's own dumps.

    python3 tools/regalloc.py FILE.cpp FUNC [--version eu] [--keep DIR]

The file is compiled as tools/check.py compiles it, once more with -g (for the line notes) and
the register allocators' dumps (-dl, -dg: `.lreg` after local-alloc, `.greg` after global-alloc
and reload) and -dp (each instruction of the assembly marked with its insn's number). The
assembler's listing then gives each of our final instructions its insn, so that:

- our instructions are aligned with retail's (as tools/regdiff.py aligns them, registers set
  aside), and each register that differs is paired with retail's register in the same operand;
- our hard register is mapped back to the value (the pseudo) that holds it in that insn, through
  the same insn in `.lreg` (pseudos) and `.greg` (hard registers), and to the allocator that gave
  it: local-alloc (`;; Register N in H.` in `.lreg`), global-alloc (`.greg`'s `regs to allocate`,
  in its priority order), or reload (a pseudo with no register, or a reload insn);
- retail's register is looked up in our compile: which of our values, or which hard register
  (an argument, a return value, a call's), holds it while the value is live (liveness computed
  backwards through each basic block from the flow information `.lreg` prints).

For each value it prints where it is born and dies (insn and source line), what took retail's
register and why that one went first (local-alloc: a shorter life or more uses, ties by birth;
global-alloc: its printed order; a call crossed needs a saved register), and the likely lever.
Where the dump does not say why (a register free over the whole life but not chosen: a copy
preference or the allocation order), it says so. The model is the dump's: local-alloc measures
lifetimes its own way (one insn longer at each end), so a priority here is a guide, not the
compiler's number (docs/TOOLCHAIN.md, "Constants in one very long block").
"""

import argparse
import collections
import difflib
import math
import os
import re
import shutil
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check  # noqa: E402
import compile as cc  # noqa: E402
import elf  # noqa: E402
import regdiff  # noqa: E402
import symbols  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
DUMP_FLAGS = ["-g", "-dl", "-dg", "-dp"]

GPR = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
       "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "s8", "ra"]
NUMBER = {name: i for i, name in enumerate(GPR)}
NUMBER["fp"] = 30
# Callee-saved in the EE's ABI: s0-s7 and fp, $f20-$f31.
SAVED = set(range(16, 24)) | {30} | set(range(32 + 20, 32 + 32))


def reg_name(n):
    """`$a0`, `$f12`, or `hard 67` for a GCC hard register number (0-31 GPRs, 32-63 FPRs)."""
    if 0 <= n < 32:
        return "$" + GPR[n]
    if 32 <= n < 64:
        return "$f%d" % (n - 32)
    return "hard %d" % n


def reg_number(token):
    """GCC's number for a register as objdump spells it (`a0`, `$f12`), or None ($vf, $vi)."""
    if token in NUMBER:
        return NUMBER[token]
    m = re.match(r"^\$f(\d+)$", token)
    return 32 + int(m.group(1)) if m else None


# ---------------------------------------------------------------------------------------------
# RTL dumps

class Str(str):
    """A quoted string of the dump (a file name, an asm template)."""


def tokens(text):
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c.isspace():
            i += 1
        elif c in "()[]":
            yield c
            i += 1
        elif c == '"':
            j = i + 1
            while j < n and text[j] != '"':
                j += 2 if text[j] == "\\" else 1
            yield Str(text[i + 1:j])
            i = j + 1
        else:
            j = i
            while j < n and not text[j].isspace() and text[j] not in '()[]"':
                j += 1
            yield text[i:j]
            i = j


def parse_sexpr(text):
    """One s-expression of RTL text as nested lists; `[...]` vectors become lists headed '['."""
    stack = [[]]
    for tok in tokens(text):
        if tok in ("(", "["):
            stack.append(["["] if tok == "[" else [])
        elif tok in (")", "]"):
            done = stack.pop()
            if not stack:
                break
            stack[-1].append(done)
        else:
            stack[-1].append(tok)
    top = stack[0]
    return top[0] if top else None


def head(x):
    """`reg` for `reg/v:SI`: an RTL code without its flags and mode."""
    return x[0].split("/")[0].split(":")[0] if isinstance(x, list) and x and isinstance(x[0], str) else None


def regs_in(x, out=None):
    """Every (reg ...) in walk order, as register numbers."""
    out = [] if out is None else out
    if isinstance(x, list):
        if head(x) == "reg" and len(x) > 1 and x[1].isdigit():
            out.append(int(x[1]))
            return out
        for y in x:
            regs_in(y, out)
    return out


def defs_uses(pattern):
    """(defined, used) register numbers of an insn's pattern. A set or clobber of a whole reg
    defines it; a set of part of one (subreg, strict_low_part, zero_extract) uses it as well."""
    defs, uses = set(), set()

    def dest(d):
        h = head(d)
        if h == "reg":
            defs.add(int(d[1]))
        elif h in ("subreg", "strict_low_part", "zero_extract", "sign_extract"):
            inner = regs_in(d)
            defs.update(inner[:1])
            uses.update(inner)
        else:
            uses.update(regs_in(d))      # a memory destination's address

    def walk(x):
        h = head(x)
        if h == "set":
            dest(x[1])
            uses.update(regs_in(x[2]))
        elif h == "clobber":
            if head(x[1]) == "reg":
                defs.add(int(x[1][1]))
            else:
                uses.update(regs_in(x[1]))
        elif h == "parallel" or (isinstance(x, list) and x and x[0] == "["):
            for y in x[1:]:
                walk(y)
        else:
            uses.update(regs_in(x))

    walk(pattern)
    return defs, uses


class Insn:
    def __init__(self, kind, uid, pattern, rest, line, pos):
        self.kind, self.uid, self.pattern, self.rest, self.line, self.pos = kind, uid, pattern, rest, line, pos
        self.regs = regs_in(pattern)
        self.defs, self.uses = defs_uses(pattern)
        if kind == "call_insn":
            # CALL_INSN_FUNCTION_USAGE: the argument registers the call reads.
            for item in rest:
                for x in _flat(item):
                    if head(x) == "use":
                        self.uses.update(regs_in(x))


def _flat(x):
    if isinstance(x, list):
        yield x
        for y in x:
            yield from _flat(y)


class Dump:
    """One function's part of an `.lreg` or `.greg` dump."""

    def __init__(self, text):
        self.insns, self.order, self.chain = {}, [], []     # insns by number; insns in order; every element
        self.info, self.local, self.disposition = {}, {}, {}
        self.blocks = {}        # n -> dict(first, last, start, end, preds, succs)
        self.to_allocate, self.conflicts, self.preferences, self.spilled_for = [], {}, {}, []
        line = None
        chunk, depth = [], 0
        lines = text.splitlines()
        block = None
        i = 0
        while i < len(lines):
            s = lines[i]
            i += 1
            if chunk or (s.startswith("(") and not depth):
                chunk.append(s)
                depth += _balance(s)
                if depth > 0:
                    continue
                sx = parse_sexpr("\n".join(chunk))
                chunk, depth = [], 0
                if not isinstance(sx, list) or not sx:
                    continue
                kind = head(sx)
                if len(sx) > 1 and isinstance(sx[1], str) and sx[1].isdigit():
                    self.chain.append(int(sx[1]))
                if kind == "note":
                    if len(sx) > 5 and isinstance(sx[4], list) and sx[4] and isinstance(sx[4][0], Str):
                        line = (str(sx[4][0]), int(sx[5]))
                    continue
                if kind in ("insn", "jump_insn", "call_insn") and len(sx) > 4:
                    ins = Insn(kind, int(sx[1]), sx[4], sx[5:], line, len(self.order))
                    self.insns[ins.uid] = ins
                    self.order.append(ins.uid)
                continue
            m = re.match(r"^Register (\d+) used (\d+) times across (\d+) insns(.*)$", s)
            if m:
                rest = m.group(4)
                blk = re.search(r" in block (\d+)", rest)
                calls = re.search(r"crosses (\d+) calls?", rest)
                sets = re.search(r"set (\d+) times?", rest)
                self.info[int(m.group(1))] = dict(
                    refs=int(m.group(2)), length=int(m.group(3)), block=int(blk.group(1)) if blk else None,
                    calls=int(calls.group(1)) if calls else 0, sets=int(sets.group(1)) if sets else 0,
                    fp="FP_REGS" in rest,
                    user="user var" in rest, size=int((re.search(r"(\d+) bytes", rest) or [0, 4])[1]))
                continue
            m = re.match(r"^Basic block (\d+): first insn (\d+), last (\d+)\.", s)
            if m:
                block = dict(first=int(m.group(2)), last=int(m.group(3)), preds=[], succs=[], start=set(), end=set())
                self.blocks[int(m.group(1))] = block
                continue
            if block is not None:
                for key, field in (("Predecessors:", "preds"), ("Successors:", "succs")):
                    if s.startswith(key):
                        block[field] = s[len(key):].split()
                for key, field in (("Registers live at start:", "start"), ("Registers live at end:", "end")):
                    if s.startswith(key):
                        block[field] = {int(x) for x in s[len(key):].split() if x.isdigit()}
            m = re.match(r"^;; Register (\d+) in (\d+)\.", s)
            if m:
                self.local[int(m.group(1))] = int(m.group(2))
                continue
            m = re.match(r"^;; \d+ regs to allocate:(.*)$", s)
            if m:
                self.to_allocate = [int(x) for x in re.findall(r"\d+", m.group(1).split("(")[0])]
                # an allocno of several registers is printed `N (k)`: keep only the reg numbers
                self.to_allocate = [int(x) for x in re.sub(r"\(\d+\)", "", m.group(1)).split()]
                continue
            m = re.match(r"^;; (\d+) (conflicts|preferences):(.*)$", s)
            if m:
                target = self.conflicts if m.group(2) == "conflicts" else self.preferences
                target[int(m.group(1))] = [int(x) for x in m.group(3).split()]
                continue
            m = re.match(r"^Spilling for insn (\d+)\.", s)
            if m:
                self.spilled_for.append(int(m.group(1)))
                continue
            if s.startswith(";; Register dispositions:"):
                while i < len(lines) and lines[i].strip() and not lines[i].startswith(";;"):
                    for a, b in re.findall(r"(\d+) in (\d+)", lines[i]):
                        self.disposition[int(a)] = int(b)
                    i += 1

    def first_pseudo(self):
        """The first pseudo register number (the lowest the dump describes)."""
        return min(self.info) if self.info else 64


def _balance(s):
    depth, instr = 0, False
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
    return depth


def function_part(text, func):
    """The part of a dump for FUNC (from its `;; Function` header to the next)."""
    parts = re.split(r"^(?=;; Function )", text, flags=re.M)
    for part in parts:
        first = part.split("\n", 1)[0]
        if part.startswith(";; Function ") and re.search(r"\b%s\b" % re.escape(func), first):
            return part
    return None


def liveness(dump):
    """{uid: set of registers live across the insn} (live before it, after it, or referenced),
    from each basic block's live-at-end set, backwards. Registers are hard and pseudo alike."""
    live_at = {}
    pos = {uid: k for k, uid in enumerate(dump.chain)}
    for b in dump.blocks.values():
        if b["first"] not in pos or b["last"] not in pos:
            continue
        live = set(b["end"])
        for k in range(pos[b["last"]], pos[b["first"]] - 1, -1):
            ins = dump.insns.get(dump.chain[k])
            if ins is None:
                continue
            after = set(live)
            live -= ins.defs
            live |= ins.uses
            live_at[ins.uid] = after | live | set(ins.regs)
    return live_at


# ---------------------------------------------------------------------------------------------
# The assembler's listing: each instruction of the function with its insn number (-dp)

LISTING_LINE = re.compile(r"^\s*\d+\s+([0-9a-f]{4}) ([0-9A-F]+)\s?(.*)$")
LISTING_MORE = re.compile(r"^\s*\d*\s+([0-9A-F]{8,})\s*$")     # more words of a macro's expansion
LISTING_SECTION = re.compile(r"^\s*\d+\s+(?:[0-9a-f]{4} [0-9A-F]+)?\s*\.(section\s+([^,\s]+)|text|data|rdata|bss)\b")
UID_MARK = re.compile(r"#\s+(\d+)\s+\S+\s+\[length = \d+\]")


def parse_listing(text, section):
    """[(offset, uid or None, asm text)] of every word the listing puts in `section`."""
    current, out, src, next_offset = None, [], "", 0
    for s in text.splitlines():
        s = s.rstrip("\r")
        if s.startswith("GAS LISTING") or not s.strip():
            continue
        m = LISTING_SECTION.match(s)
        if m:
            current = m.group(2) or "." + m.group(1)
            continue
        m = LISTING_LINE.match(s)
        if m:
            offset, data, src = int(m.group(1), 16), m.group(2), m.group(3)
        else:
            m = LISTING_MORE.match(s)
            if not m:
                continue
            offset, data = next_offset, m.group(1)
        next_offset = offset + len(data) // 2
        if current != section:
            continue
        uid = UID_MARK.search(src)
        for k in range(len(data) // 8):
            out.append((offset + 4 * k, int(uid.group(1)) if uid else None, src.strip()))
    return out


# ---------------------------------------------------------------------------------------------
# Compiling

class Compiled:
    pass


def compile_with_dumps(path, func, key, keep):
    """Compile PATH as check.py does with the dumps, and once more with -g for the line notes;
    keep both in KEEP (plain/ and g/). The -g compile is analysed when its code is the same,
    else the plain one (without source lines). Returns a Compiled with ours and retail's
    disassembly, the listing and the two dumps."""
    path = Path(path)
    source = check.source_for(path, func)
    flags = cc.flags_for(source)
    keep = Path(keep)
    if keep.exists():
        shutil.rmtree(keep)
    resolver, image = check.Resolver(key), check.retail_image(key)
    results = {}
    for tag, extra in (("plain", DUMP_FLAGS[1:]), ("g", DUMP_FLAGS)):
        folder = keep / tag
        folder.mkdir(parents=True)
        obj_path = folder / "unit.o"
        cc.compile_file(path, obj_path, flags + extra, source=source, keep_dumps=folder)
        obj = elf.Elf(obj_path.read_bytes())
        r = check.check_function(obj, func, key, resolver, image)
        if "ours" not in r:
            raise RuntimeError(r.get("note", "no code"))
        results[tag] = (obj, r, folder)
    out = Compiled()
    out.same_with_g = results["plain"][1]["ours"] == results["g"][1]["ours"]
    obj, r, folder = results["g" if out.same_with_g else "plain"]
    out.folder = folder
    out.status = results["plain"][1]["status"]
    out.address = r["address"]
    _, size = check.target_of(key, func)
    out.ours = check.disassemble(r["ours"], r["address"])
    out.retail = check.disassemble(r["retail"][:size], r["address"])
    # The function's section and its symbol (its mangled name).
    code_sections = {sec["index"] for sec in obj.sections if sec["name"].startswith(".text")}
    sym = next(s for s in obj.symbols if s["type"] == elf.STT_FUNC and s["shndx"] in code_sections
               and (s["name"] == func or check.base_name(s["name"]) == func))
    section = obj.sections[sym["shndx"]]["name"]
    out.symbol, out.section, out.start = sym["name"], section, sym["value"]
    release = cc.compiler_for(source)
    run, _, _, ee_as = cc.tools(cc.LINUX_COMPANION.get(release, release))
    as_flags = [f for f in flags if f.startswith(("-G", "-O"))]
    listing = folder / "unit.lst"
    proc = cc.run_step(run + [str(ee_as)] + as_flags + [
        "-alm=%s" % os.path.relpath(listing, ROOT), os.path.relpath(folder / "unit.s", ROOT),
        "-o", os.path.relpath(folder / "listing.o", ROOT)], cwd=ROOT)
    if proc.returncode or not listing.exists():
        raise RuntimeError("the assembler's listing failed: %s" % proc.stderr.strip())
    out.listing = parse_listing(listing.read_text(errors="replace"), section)
    out.lreg_text = (folder / "unit.ii.lreg").read_text(errors="replace")
    out.greg_text = (folder / "unit.ii.greg").read_text(errors="replace")
    return out


# ---------------------------------------------------------------------------------------------
# Analysis

def align(ours, retail):
    """[(i, j)] pairs of our instruction i and retail's j that agree with registers set aside."""
    a, b = regdiff.masked(ours), regdiff.masked(retail)
    pairs = []
    for blk in difflib.SequenceMatcher(None, a, b, autojunk=False).get_matching_blocks():
        pairs += [(blk.a + k, blk.b + k) for k in range(blk.size)]
    return pairs


def register_tokens(text):
    return [m.group(0) for m in regdiff.REGISTER.finditer(text)]


def floor_log2(n):
    return int(math.log2(n)) if n > 0 else -1


def priority(info):
    """local-alloc's and global-alloc's measure: floor_log2(refs) * refs / life (times size)."""
    if not info or info["length"] <= 0:
        return 0.0
    return floor_log2(info["refs"]) * info["refs"] * max(info["size"] // 4, 1) / float(info["length"])


def asm_template(pattern):
    """The template of an inline asm insn's pattern, or None."""
    for x in _flat(pattern):
        if head(x) in ("asm_operands", "asm_input"):
            for y in _flat(x):
                if isinstance(y, list):
                    for z in y:
                        if isinstance(z, Str):
                            return str(z)
            for z in x[1:]:
                if isinstance(z, Str):
                    return str(z)
    return None


def template_regexes(template):
    """One regex per instruction of an asm template, its operands (%0, %1, %z2) matching anything."""
    out = []
    for part in re.split(r"\\n|\n|;", template):
        part = part.replace("\\t", " ").replace("\t", " ").strip()
        if not part or part.startswith(("#", ".")):
            continue
        literal = [re.sub(r"(?:\\\s)+", r"\\s*", re.escape(piece)) for piece in re.split(r"%[a-zA-Z]?\d+", part)]
        out.append(re.compile(r"^\s*" + "(.+?)".join(literal) + r"\s*$"))
    return out


def asm_uids(listing, greg, start):
    """{instruction index: insn} for the instructions of inline asm, which -dp leaves unmarked:
    the k-th final line an asm template's instruction matches is that template's k-th insn in
    `.greg` order (asm statements keep their order)."""
    parts = []      # (regex, uid) in .greg order
    for uid in greg.order:
        if uid is None:
            continue
        tpl = asm_template(greg.insns[uid].pattern)
        if tpl:
            parts += [(rx, uid) for rx in template_regexes(tpl)]
    used, out = collections.Counter(), {}
    for offset, uid, text in listing:
        if uid is not None:
            continue
        line = text.split("#")[0].strip()
        for rx in dict.fromkeys(r for r, _ in parts):
            if rx.match(line):
                hits = [u for r, u in parts if r.pattern == rx.pattern]
                k = used[rx.pattern]
                if k < len(hits):
                    out[(offset - start) // 4] = hits[k]
                    used[rx.pattern] += 1
                break
    return out


class Analysis:
    def __init__(self, compiled, func, source_root=ROOT):
        self.c, self.func = compiled, func
        lpart, gpart = function_part(compiled.lreg_text, func), function_part(compiled.greg_text, func)
        if lpart is None or gpart is None:
            raise RuntimeError("the dumps have no `;; Function` part for %s" % func)
        self.lreg, self.greg = Dump(lpart), Dump(gpart)
        self.live = liveness(self.lreg)
        self.uid_at = {}
        for offset, uid, text in compiled.listing:
            self.uid_at[(offset - compiled.start) // 4] = (uid, text)
        self.by_template = asm_uids(compiled.listing, self.greg, compiled.start)
        for i, uid in self.by_template.items():
            self.uid_at[i] = (uid, self.uid_at[i][1])
        self.source_root = source_root
        self.retail_of = {}     # pseudo -> Counter of retail's registers at its aligned operands
        self.reload_at = {}     # (insn, hard) -> the .lreg insn a reload register serves
        self.follows = collections.defaultdict(set)     # value -> values retail has in its register
        self._lines = {}

    # -- source lines
    def line_text(self, where):
        if not where:
            return ""
        f, n = where
        if f not in self._lines:
            p = Path(f) if Path(f).is_absolute() else self.source_root / f
            try:
                self._lines[f] = p.read_text(errors="replace").splitlines()
            except OSError:
                self._lines[f] = []
        text = self._lines[f][n - 1].strip() if 0 < n <= len(self._lines[f]) else ""
        return text[:70]

    def where(self, uid):
        ins = self.lreg.insns.get(uid) or self.greg.insns.get(uid)
        if ins is None or ins.line is None:
            return "insn %d" % uid
        f, n = ins.line
        short = "" if Path(f).name == Path(self.c.source_name).name else Path(f).name + ":"
        return "insn %d, line %s%d `%s`" % (uid, short, n, self.line_text(ins.line))

    # -- values
    def pseudo_of(self, uid, hard):
        """(kind, pseudo or None, note) for our hard register HARD in insn UID."""
        l, g = self.lreg.insns.get(uid), self.greg.insns.get(uid)
        if l is None:
            if g is not None:
                return self.reload_insn(uid, hard)
            return "unknown", None, "insn %d is made after allocation (prologue, epilogue or a split)" % uid
        if g is not None and len(l.regs) == len(g.regs):
            hits = [p for p, h in zip(l.regs, g.regs) if h == hard]
            pseudos = sorted({p for p in hits if p >= self.lreg.first_pseudo()})
            if pseudos:
                p = pseudos[0]
                if self.greg.disposition.get(p) == hard:
                    return "pseudo", p, ""
                self.reload_at[(uid, hard)] = uid
                return "reloaded", p, "pseudo %d has %s, reload put it in %s for this insn" % (
                    p, reg_name(self.greg.disposition[p]) if p in self.greg.disposition else "no register",
                    reg_name(hard))
            if hits:
                return "hard", hard, "the insn names %s itself" % reg_name(hard)
        cands = sorted({p for p in l.regs if self.greg.disposition.get(p) == hard})
        if cands:
            return "pseudo", cands[0], "" if len(cands) == 1 else "also %s" % cands[1:]
        if hard in l.regs:
            return "hard", hard, "the insn names %s itself" % reg_name(hard)
        spilled = [p for p in l.regs if p >= self.lreg.first_pseudo() and p not in self.greg.disposition]
        if spilled:
            self.reload_at[(uid, hard)] = uid
            return "reloaded", spilled[0], "pseudo %d has no register; %s is reload's here" % (spilled[0], reg_name(hard))
        return "unknown", None, "no value of insn %d is in %s" % (uid, reg_name(hard))

    def reload_insn(self, uid, hard):
        """A reload insn (in .greg, not .lreg): the value it loads or stores, found in the nearest
        insn after it (an input reload) or before it (an output reload) that has HARD in it."""
        chain = [u for u in self.greg.order]
        k = chain.index(uid)
        for step, what in ((1, "input"), (-1, "output")):
            j = k + step
            while 0 <= j < len(chain) and chain[j] not in self.lreg.insns:
                j += step
            if 0 <= j < len(chain) and hard in self.greg.insns[chain[j]].regs:
                kind, p, _ = self.pseudo_of(chain[j], hard)
                if kind in ("pseudo", "reloaded"):
                    self.reload_at[(uid, hard)] = chain[j]
                    return "reloaded", p, "insn %d is reload's: the %s reload of r%d for insn %d (%s)" % (
                        uid, what, p, chain[j], self.line_label(chain[j]))
        saved = [q for q, h in self.greg.disposition.items() if h == hard and self.lreg.info.get(q, {}).get("calls")]
        if len(saved) == 1:
            return "reloaded", saved[0], "insn %d saves or restores r%d around a call (caller-saves)" % (uid, saved[0])
        return "reload", None, "insn %d is reload's (not in .lreg), and the insns around it do not name %s" % (
            uid, reg_name(hard))

    def block_span(self, p):
        """(birth, death) of a pseudo local to one block, counted in insns of that block in `.lreg`'s
        order (after sched1), as local-alloc counts them; None if it is not local to a block."""
        info = self.lreg.info.get(p)
        if not info or info["block"] is None or info["block"] not in self.lreg.blocks:
            return None
        b = self.lreg.blocks[info["block"]]
        chain = self.lreg.chain
        try:
            lo, hi = chain.index(b["first"]), chain.index(b["last"])
        except ValueError:
            return None
        k, birth, death = 0, None, None
        for uid in chain[lo:hi + 1]:
            ins = self.lreg.insns.get(uid)
            if ins is None:
                continue
            if p in ins.regs:
                if birth is None:
                    birth = k
                death = k
            k += 1
        return None if birth is None else (birth, death)

    def block_order(self, block, values):
        """`insn 122 sets r130, insn 120 sets r129, insn 123 uses r129 r130`: the insns of BLOCK that
        name any of VALUES, in `.lreg`'s order."""
        b = self.lreg.blocks[block]
        chain = self.lreg.chain
        out = []
        for uid in chain[chain.index(b["first"]):chain.index(b["last"]) + 1]:
            ins = self.lreg.insns.get(uid)
            if ins is None:
                continue
            sets = [v for v in values if v in ins.defs]
            uses = [v for v in values if v in ins.regs and v not in ins.defs]
            bits = (["sets " + " ".join("r%d" % v for v in sets)] if sets else []) + \
                   (["uses " + " ".join("r%d" % v for v in uses)] if uses else [])
            if bits:
                out.append("insn %d %s" % (uid, ", ".join(bits)))
        return "; ".join(out)

    def pri(self, p):
        """The priority p was placed by: local-alloc's for a value local to a block (refs over its
        span in the block's insns after sched1), else global-alloc's (refs over the dump's life)."""
        info = self.lreg.info.get(p)
        span = self.block_span(p) if self.allocator(p)[0] == "local-alloc" else None
        if span and info:
            return floor_log2(info["refs"]) * info["refs"] * max(info["size"] // 4, 1) / float(max(span[1] - span[0], 1))
        return priority(info)

    def life_text(self, p):
        span = self.block_span(p) if self.allocator(p)[0] == "local-alloc" else None
        if span:
            return "a span of %d insns in its block" % max(span[1] - span[0], 1)
        info = self.lreg.info.get(p)
        return "a life of %d insns" % info["length"] if info else "?"

    def life(self, p):
        """[uid] of the insns over which register P is live, in insn order."""
        return [uid for uid in self.lreg.order if p in self.live.get(uid, ())]

    def born_dies(self, p):
        uids = [uid for uid in self.lreg.order if p in self.lreg.insns[uid].regs]
        sets = [uid for uid in uids if p in self.lreg.insns[uid].defs]
        born = sets[0] if sets else (uids[0] if uids else None)
        return born, (uids[-1] if uids else None)

    def allocator(self, p):
        """(name, note) of who gave pseudo P its final register."""
        final = self.greg.disposition.get(p)
        if p in self.lreg.local:
            lh = self.lreg.local[p]
            if final == lh:
                return "local-alloc", ""
            if final is None:
                return "none", "local-alloc gave it %s; global-alloc evicted it (a poorly used local register) " \
                               "or reload spilled it" % reg_name(lh)
            return "reload", "local-alloc gave it %s; it ended in %s" % (reg_name(lh), reg_name(final))
        if p in self.greg.to_allocate:
            if final is None:
                return "none", "global-alloc found no register (%d of %d in its order); reload spills it" % (
                    self.greg.to_allocate.index(p) + 1, len(self.greg.to_allocate))
            return "global-alloc", "%d of %d in its order" % (self.greg.to_allocate.index(p) + 1, len(self.greg.to_allocate))
        if final is None:
            return "none", "no register"
        return "local-alloc", "(not in the local list; tied to another quantity)"

    def describe(self, p):
        i = self.lreg.info.get(p, {})
        bits = []
        if i:
            bits.append("%d refs over %d insns" % (i["refs"], i["length"]))
            if i["sets"] > 1:
                bits.append("set %d times" % i["sets"])
            if i["calls"]:
                bits.append("crosses %d call%s" % (i["calls"], "s" if i["calls"] > 1 else ""))
            bits.append("user variable" if i["user"] else "temporary")
            bits.append("block %d" % i["block"] if i["block"] is not None else "several blocks")
        return "r%d (%s)" % (p, ", ".join(bits))

    def holders(self, p, hard):
        """[(holder, overlap uids)]: our pseudos with final register HARD, and HARD itself, live
        over part of P's life."""
        life = set(self.life(p))
        out = []
        for q, h in self.greg.disposition.items():
            if h == hard and q != p:
                ov = life & set(self.life(q))
                if ov:
                    out.append((q, ov))
        # $sp, and $fp before reload (the frame pointer, eliminated later): live everywhere in .lreg
        hov = {uid for uid in life if hard in self.live.get(uid, ())} if hard not in (29, 30) else set()
        if hov:
            out.append((("hard", hard), hov))
        return out

    def is_main(self, line):
        return line is not None and Path(line[0]).name == Path(self.c.source_name).name

    def line_label(self, uid):
        """`line 12`, or `vu0.h:859` for a line of another file."""
        ins = self.lreg.insns.get(uid) or self.greg.insns.get(uid)
        if ins is None or ins.line is None:
            return "insn %d" % uid
        return "line %d" % ins.line[1] if self.is_main(ins.line) else "%s:%d" % (Path(ins.line[0]).name, ins.line[1])

    def span(self, uids):
        """`insns A to B, lines L-M`: the first and last insn in order, and the source file's lines."""
        lines = sorted(self.lreg.insns[u].line[1] for u in uids if self.is_main(self.lreg.insns[u].line))
        order = sorted(uids, key=lambda u: self.lreg.insns[u].pos)
        lines = "line %d" % lines[0] if lines and lines[0] == lines[-1] else \
            "lines %d-%d" % (lines[0], lines[-1]) if lines else ""
        insns = "insn %d" % order[0] if len(order) == 1 else "insns %d to %d" % (order[0], order[-1])
        return insns + (", " + lines if lines else "")

    def placed_before(self, q, p):
        """True if q was given its register before p was (False if after; None if the dump cannot
        say). local-alloc runs before global-alloc; local-alloc takes its quantities by priority
        (ties by birth); global-alloc follows the order `.greg` prints."""
        qa, pa = self.allocator(q)[0], self.allocator(p)[0]
        if pa in ("none", "reload"):
            return True
        if qa == "local-alloc" and pa == "global-alloc":
            return True
        if qa == "global-alloc" and pa == "local-alloc":
            return False
        if qa == pa == "global-alloc":
            order = self.greg.to_allocate
            return order.index(q) < order.index(p) if q in order and p in order else None
        if qa == pa == "local-alloc":
            mine, theirs = self.pri(p), self.pri(q)
            if theirs != mine:
                return theirs > mine
            bp, bq = self.born_dies(p)[0], self.born_dies(q)[0]
            if bp is None or bq is None:
                return None
            return self.lreg.insns[bq].pos < self.lreg.insns[bp].pos
        return None

    def explain(self, p, ours_hard, retail_hard, reload_at=()):
        """Lines explaining why pseudo P has OURS_HARD and not RETAIL_HARD, and levers. RELOAD_AT:
        the insns where OURS_HARD is a reload register for P."""
        out, levers = [], []
        alloc, note = self.allocator(p)
        info = self.lreg.info.get(p, {})
        born, dies = self.born_dies(p)
        out.append("%s" % self.describe(p))
        if born is not None:
            out.append("born %s" % self.where(born))
            out.append("dies %s" % self.where(dies))
        if alloc == "none":
            out.append("has no hard register (%s); reload put it in %s here" % (note, reg_name(ours_hard)))
        else:
            out.append("got %s from %s%s" % (reg_name(ours_hard), alloc, (": " + note) if note else ""))
        if reload_at:
            return out + self.explain_reload(p, ours_hard, retail_hard, reload_at), levers
        ours_saved, retail_saved = ours_hard in SAVED, retail_hard in SAVED
        calls = info.get("calls", 0)
        if calls and ours_saved and not retail_saved and retail_hard < 64:
            out.append("it crosses %d call%s and got a saved register; retail's %s is caller-saved: retail's "
                       "value does not cross the call, or is kept in %s and saved around it (caller-saves, "
                       "which global-alloc takes when the refs outnumber 4 per call crossed)"
                       % (calls, "s" if calls > 1 else "", reg_name(retail_hard), reg_name(retail_hard)))
            levers.append("r%d crosses %d call%s (its life: %s): if retail's value does not, compute it after the "
                          "call or use it up before" % (p, calls, "s" if calls > 1 else "", self.span(self.life(p))))
        elif calls and not ours_saved and ours_hard < 64:
            out.append("it crosses %d call%s in a caller-saved register: saved and restored around the call "
                       "(caller-saves)" % (calls, "s" if calls > 1 else ""))
        elif not calls and retail_saved and not ours_saved:
            out.append("retail's %s is a saved register: there the value lives across a call, ours does not"
                       % reg_name(retail_hard))
            levers.append("r%d: retail keeps it across a call (a saved register); ours lives across none" % p)
        mine = self.pri(p)
        conflicts = set(self.greg.conflicts.get(p, ()))
        held = self.holders(p, retail_hard)
        blocking, later = [], []
        for q, ov in sorted(held, key=lambda h: -len(h[1])):
            first = True if isinstance(q, tuple) else self.placed_before(q, p)
            (later if first is False else blocking).append((q, ov, first))
        for q, ov, first in blocking:
            if isinstance(q, tuple):
                used = any(retail_hard in self.lreg.insns[u].regs for u in ov)
                out.append("%s is %s as a hard register over %d insns of its life (%s)" % (
                    reg_name(retail_hard), "used" if used else "live", len(ov), self.span(ov)))
                if retail_hard in conflicts:
                    out.append("  .greg lists %s among r%d's conflicts" % (reg_name(retail_hard), p))
                levers.append("%s is busy as a hard register (an argument, a return value or a call's) during "
                              "r%d's life (%s): in retail the value starts after that use or ends before it"
                              % (reg_name(retail_hard), p, self.span(ov)))
                continue
            qalloc = self.allocator(q)[0]
            qborn, qdies = self.born_dies(q)
            out.append("%s is taken by %s, %s, over %d insns of its life (%s)"
                       % (reg_name(retail_hard), self.describe(q), qalloc, len(ov), self.span(ov)))
            if qborn is not None:
                out.append("  r%d born %s; dies %s" % (q, self.where(qborn), self.where(qdies)))
            why = self.why_first(p, alloc, q, qalloc, mine, self.pri(q))
            if why:
                out.append("  " + why + ("" if first else " (the dump cannot say which was placed first)"))
            levers.append(self.lever(p, q, ov, qborn, qdies, born, dies, retail_hard))
        for q, ov, _ in later:
            out.append("%s goes to r%d (%s) over %d insns of its life, but r%d was placed after r%d: not what "
                       "kept it from r%d" % (reg_name(retail_hard), q, self.allocator(q)[0], len(ov), q, p, p))
        if blocking:
            return out, levers
        out.append("%s was free when r%d was placed: it took %s first" % (
            reg_name(retail_hard), p, reg_name(ours_hard)))
        blockers = self.retail_blockers(p, ours_hard)
        for q, ov in blockers:
            out.append("in retail, %s holds r%d over %d insns of this life (%s); r%d is %s in ours, so retail's "
                       "value had to take another register"
                       % (reg_name(ours_hard), q, len(ov), self.span(ov), q,
                          reg_name(self.greg.disposition[q]) if q in self.greg.disposition else "on the stack"))
            self.follows[p].add(q)
        if blockers:
            return out, levers
        ties = self.ties(p) if alloc == "local-alloc" else []
        prefs = self.greg.preferences.get(p) if alloc == "global-alloc" else None
        if ties:
            out.append("local-alloc took %s by a copy suggestion: %s" % (reg_name(ours_hard), "; ".join(ties)))
            levers.append("r%d is tied to %s by a copy; retail's is not (write the value without that move, "
                          "or move it from another value)" % (p, reg_name(ours_hard)))
        elif prefs:
            ties = self.ties(p, ours_hard)
            out.append("global-alloc took %s by preference (.greg: %s), from the sets that tie it to what is "
                       "in %s%s" % (reg_name(ours_hard), ", ".join(reg_name(x) for x in prefs), reg_name(ours_hard),
                                    ": " + ", ".join(ties) if ties else " (the dump does not show which)"))
            levers.append("r%d prefers %s because it is set from or into %s; in retail it is not tied so, or "
                          "something of retail's holds %s first" % (
                              p, reg_name(ours_hard), ", ".join(ties) if ties else "a value there",
                              reg_name(ours_hard)))
        else:
            out.append("the dump does not show why %s chose %s over %s (its allocation order, its own "
                       "lifetimes one insn longer at each end, or a value of retail's that the aligned code does "
                       "not show in %s)" % (alloc, reg_name(ours_hard), reg_name(retail_hard), reg_name(ours_hard)))
        return out, levers

    def why_no_register(self, p):
        """Why global-alloc left P without a register: each register it could take (a saved one if
        it crosses a call), and the first value placed before it that holds it over its life."""
        info = self.lreg.info.get(p, {})
        fp = info.get("fp")
        regs = [r for r in (range(32 + 20, 64) if fp else list(range(16, 24)) + [30])] if info.get("calls") else \
            [r for r in (range(32, 64) if fp else list(range(2, 26)) + [30])]
        taken = []
        for r in regs:
            hold = [q for q, ov in self.holders(p, r) if not isinstance(q, tuple) and self.placed_before(q, p)]
            if hold:
                taken.append("%s r%d" % (reg_name(r), hold[0]))
        if not taken:
            return []
        return ["the %s registers it could take are held over its life by values placed before it: %s"
                % ("saved" if info.get("calls") else "", ", ".join(taken))]

    def explain_reload(self, p, ours_hard, retail_hard, at):
        """Reload's register for P at the insns AT: what holds retail's register there in ours."""
        out = self.why_no_register(p) if self.allocator(p)[0] == "none" else []
        out += ["%s is reload's choice for %s: per insn it takes the registers holding no live value first, "
               "then those whose live values have the fewest refs (order_regs_for_reload)"
               % (reg_name(ours_hard), ", ".join("insn %d (%s)" % (u, self.line_label(u)) for u in at))]
        for u in at:
            live = self.live.get(u, set())
            held = sorted(q for q in live if self.greg.disposition.get(q) == retail_hard and q != p)
            if retail_hard in live and retail_hard not in (29, 30):
                out.append("at insn %d, retail's %s is live as a hard register" % (u, reg_name(retail_hard)))
            elif held:
                out.append("at insn %d, retail's %s holds %s in ours" % (
                    u, reg_name(retail_hard), ", ".join(self.describe(q) for q in held)))
            else:
                out.append("at insn %d, retail's %s holds no live value in ours: reload's order, or the reload "
                           "registers already taken in that insn, decided it" % (u, reg_name(retail_hard)))
        return out

    def retail_blockers(self, p, hard):
        """[(q, overlap)]: our values retail puts in HARD (most of their aligned operands) whose life
        in ours overlaps P's."""
        life = set(self.life(p))
        out = []
        for q, counts in self.retail_of.items():
            if q == p or not counts or counts.most_common(1)[0][0] != hard or q not in self.greg.disposition:
                continue    # a value with no register of its own is in reload's registers insn by insn
            ov = life & set(self.life(q))
            if ov:
                out.append((q, ov))
        return sorted(out, key=lambda x: -len(x[1]))

    def roots(self):
        """The values that the others' differences follow from: in `follows`, reached from a value
        and following nothing themselves (or the first of a cycle)."""
        out = []
        for p in self.follows:
            seen, stack = set(), [p]
            while stack:
                q = stack.pop()
                if q in seen:
                    continue
                seen.add(q)
                nxt = self.follows.get(q)
                if nxt:
                    stack.extend(nxt)
                elif q not in out:
                    out.append(q)
        return out

    def swaps(self):
        """Lines for pairs of values whose registers retail swaps: p has q's register in retail and q
        has p's, with what would flip the order the allocator placed them in."""
        out, seen = [], set()
        for p, counts in self.retail_of.items():
            hp = self.greg.disposition.get(p)
            if hp is None or not counts:
                continue
            rp = counts.most_common(1)[0][0]
            for q, h in self.greg.disposition.items():
                if q == p or h != rp or (q, p) in seen or not self.retail_of.get(q):
                    continue
                if self.retail_of[q].most_common(1)[0][0] != hp or hp == rp:
                    continue
                seen.add((p, q))
                if not set(self.life(p)) & set(self.life(q)):
                    continue    # they never compete for a register
                first = self.placed_before(p, q)
                if first is None:
                    continue
                a, b = (p, q) if first else (q, p)       # a was placed first in ours
                out.append(self.flip(a, b))
        return out

    def flip(self, a, b):
        """Ours placed A before B, and retail gives each the other's register: what would put B first."""
        ia, ib = self.lreg.info.get(a, {}), self.lreg.info.get(b, {})
        aa, ab = self.allocator(a)[0], self.allocator(b)[0]
        text = "r%d (%s) and r%d (%s) swap registers in retail. Ours placed r%d first (%s, then %s)" % (
            a, reg_name(self.greg.disposition[a]), b, reg_name(self.greg.disposition[b]), a, aa, ab)
        if aa != ab:
            return text + ": local-alloc's values go before global-alloc's; in retail the other is local to a " \
                          "block, or neither is"
        pa, pb = self.pri(a), self.pri(b)
        text += "; priority %.3f (%s) against %.3f (%s)" % (pa, self.life_text(a), pb, self.life_text(b))
        if aa == "local-alloc":
            sa, sb = self.block_span(a), self.block_span(b)
            if pa == pb:
                text += ". Equal: local-alloc takes the one born first (r%d at insn %d of the block, r%d at %d)" % (
                    a, sa[0], b, sb[0]) if sa and sb else ". Equal: local-alloc takes the one born first"
            if sa and sb and ib.get("refs", 0) > 1 and pa > 0:
                weight = floor_log2(ib["refs"]) * ib["refs"] * max(ib["size"] // 4, 1)
                most = math.ceil(weight / pa) - 1
                if most >= 1:
                    text += ". r%d goes first with a span of at most %d insns between its set and its last " \
                            "use (now %d), or the same span as r%d and born before it" % (b, most, sb[1] - sb[0], a)
                else:
                    text += ". r%d goes first only with the same span as r%d (%d) and born before it, or with " \
                            "more refs" % (b, a, max(sa[1] - sa[0], 1))
                text += "; or r%d with a longer span. The spans are in sched1's order, which can differ from " \
                        "the final order: %s" % (a, self.block_order(self.lreg.info[a]["block"], (a, b)))
            return text
        if pa == pb:
            text += ". Equal: global-alloc takes the lower register number first (the value the RTL made " \
                    "first): r%d before r%d" % (min(a, b), max(a, b))
        if ib.get("refs", 0) > 1 and pa > 0:
            weight = floor_log2(ib["refs"]) * ib["refs"] * max(ib["size"] // 4, 1)
            text += ". r%d goes first with a life of at most %d insns (now %d)" % (
                b, math.ceil(weight / pa) - 1, ib["length"])
            r = ib["refs"]
            while r < ib["refs"] + 20 and floor_log2(r) * r * max(ib["size"] // 4, 1) / float(ib["length"]) <= pa:
                r += 1
            if r < ib["refs"] + 20:
                text += " or %d refs (now %d)" % (r, ib["refs"])
            if ia.get("refs", 0) > 1 and pb > 0:
                life = floor_log2(ia["refs"]) * ia["refs"] * max(ia["size"] // 4, 1) / pb
                text += ", or r%d with a life of at least %d insns (now %d)" % (a, math.floor(life) + 1, ia["length"])
        return text

    def ties(self, p, hard=None):
        """The insns that tie P to a register: a copy between P and a hard register (local-alloc's
        copy suggestion), or, with HARD, a set of P from (or into) an expression of HARD or of a
        value given HARD (global-alloc's preferences)."""
        out = []
        for uid in self.lreg.order:
            ins = self.lreg.insns[uid]
            pat = ins.pattern
            if head(pat) != "set" or p not in ins.regs:
                continue
            dest, src = regs_in(pat[1]), regs_in(pat[2])
            if hard is None:
                if head(pat[1]) == "reg" and head(pat[2]) == "reg":
                    other = src[0] if dest == [p] else dest[0] if src == [p] else None
                    if other is not None and other < self.lreg.first_pseudo():
                        out.append("%s (%s)" % (reg_name(other), self.where(uid)))
                continue
            if p in dest:
                others = src
            elif p in src:
                others = dest
            else:
                continue
            for o in others:
                if o == hard or (o != p and self.greg.disposition.get(o) == hard):
                    item = "%s (%s)" % (reg_name(o) if o == hard else "r%d" % o, self.line_label(uid))
                    if item not in out:
                        out.append(item)
                    break
        return out[:4]

    def why_first(self, p, alloc, q, qalloc, mine, theirs):
        if qalloc == "local-alloc" and alloc != "local-alloc":
            return "local-alloc runs first: r%d took it before global-alloc saw r%d" % (q, p)
        if qalloc == "local-alloc" and alloc == "local-alloc":
            if theirs > mine:
                return "local-alloc placed r%d first: priority %.3f (%s) against r%d's %.3f (%s)" % (
                    q, theirs, self.life_text(q), p, mine, self.life_text(p))
            if theirs < mine:
                return "by the dump's measure r%d (%.3f) ranks below r%d (%.3f), yet it was placed: local-alloc's " \
                       "own lifetimes, a tie of quantities, or r%d could not take %s for its own reasons" % (
                           q, theirs, p, mine, p, "it")
            return "equal priority (%.3f): local-alloc breaks ties by birth order" % mine
        if qalloc == "global-alloc" and alloc in ("global-alloc", "none"):
            order = self.greg.to_allocate
            if q in order and p in order:
                return "global-alloc's order puts r%d %s r%d (%d against %d; priority %.3f against %.3f)" % (
                    q, "before" if order.index(q) < order.index(p) else "after", p,
                    order.index(q) + 1, order.index(p) + 1, theirs, mine)
        if qalloc == "global-alloc" and alloc == "local-alloc":
            return "r%d (local) was placed first, and global-alloc gave r%d what was left" % (p, q)
        return ""

    def lever(self, p, q, ov, qborn, qdies, born, dies, hard):
        order = lambda u: self.lreg.insns[u].pos if u in self.lreg.insns else 0
        line = self.line_label
        if qdies is not None and born is not None and order(qborn) < order(born) and order(qdies) > order(born):
            return ("r%d (in %s) is still live when r%d is born (%s): its last use is at %s; "
                    "used earlier, or not kept that long, would leave %s to r%d"
                    % (q, reg_name(hard), p, line(born), line(qdies), reg_name(hard), p))
        if qborn is not None and dies is not None and order(qborn) > order(born) and order(qborn) < order(dies):
            return ("r%d (in %s) is born (%s) while r%d is still live (until %s): set later, or "
                    "r%d used up earlier, would leave %s to r%d"
                    % (q, reg_name(hard), line(qborn), p, line(dies), p, reg_name(hard), p))
        return "r%d and r%d overlap (%s): one of them shorter, or the two written in another order" % (
            p, q, self.span(ov))


def run(path, func, key="us", keep=None, out=sys.stdout):
    func = symbols.canonical(func)
    keep = Path(keep) if keep else ROOT / "build" / "regalloc" / func
    c = compile_with_dumps(path, func, key, keep)
    c.source_name = str(path)
    verdict, agree, total = regdiff.classify(c.ours, c.retail)
    w = lambda s="": print(s, file=out)
    w("%s %s: %s, %d of %d instructions agree with registers set aside (%s)" % (
        func, key, verdict, agree, total, path))
    w("dumps in %s" % os.path.relpath(c.folder, ROOT))
    if not c.same_with_g:
        w("NOTE: with -g the compiler makes other code, so these dumps have no source lines.")
    if verdict == "EXACT":
        return 0
    a = Analysis(c, func)
    pairs = align(c.ours, c.retail)
    groups = collections.OrderedDict()
    for i, j in pairs:
        ta, tb = register_tokens(c.ours[i][1]), register_tokens(c.retail[j][1])
        if len(ta) != len(tb):
            continue
        uid, _ = a.uid_at.get(i, (None, ""))
        for x, y in zip(ta, tb):
            hx, hy = reg_number(x), reg_number(y)
            if hx is None or hy is None or (x != y and {hx, hy} & {0, 29}):
                continue    # $zero or $sp against a register: a difference of code, not of allocation
            if uid is None:
                kind, p, note = "unknown", None, "no insn number (an instruction the assembler made, or one -dp " \
                                                 "and the asm templates do not name)"
            else:
                kind, p, note = a.pseudo_of(uid, hx)
            if kind in ("pseudo", "reloaded"):
                a.retail_of.setdefault(p, collections.Counter())[hy] += 1
            if x == y:
                continue
            gkey = (kind, p if kind in ("pseudo", "reloaded") else (uid if kind != "hard" else hx), hx, hy)
            g = groups.setdefault(gkey, dict(addrs=[], uids=set(), note=note, at=set()))
            g["addrs"].append(c.address + 4 * i)
            if uid is not None:
                g["uids"].add(uid)
                if (uid, hx) in a.reload_at:
                    g["at"].add(a.reload_at[(uid, hx)])
    unpaired = sum(1 for i, j in pairs if c.ours[i][0] != c.retail[j][0])
    w("%d aligned instructions differ; %d register differences in %d groups" % (
        unpaired, sum(len(g["addrs"]) for g in groups.values()), len(groups)))
    if verdict == "code":
        w("NOTE: the code differs too (regdiff: code): only the aligned instructions are explained.")
    w()
    # The substitution: our register -> retail's, per value.
    levers, frame = [], []
    by_value = collections.OrderedDict()
    for (kind, p, hx, hy), g in groups.items():
        by_value.setdefault((kind, p), []).append((hx, hy, g))
    for (kind, p), rows in by_value.items():
        subst = ", ".join("%s -> retail %s (%d)" % (reg_name(hx), reg_name(hy), len(g["addrs"])) for hx, hy, g in rows)
        addrs = sorted({ad for _, _, g in rows for ad in g["addrs"]})
        addr_text = " ".join("%X" % ad for ad in addrs[:6]) + (" ..." if len(addrs) > 6 else "")
        if kind in ("pseudo", "reloaded"):
            w("value r%d: ours %s  [at %s]" % (p, subst, addr_text))
            hx, hy, g = max(rows, key=lambda r: len(r[2]["addrs"]))
            if kind == "reloaded":
                w("  " + g["note"])
            lines, lv = a.explain(p, hx, hy, sorted(g["at"]))
            for s in lines:
                w("  " + s)
            levers += lv
        elif kind == "hard":
            w("hard register %s: ours %s  [at %s]" % (reg_name(p), subst, addr_text))
            w("  the insn names the hard register itself (an argument, return value or the frame): "
              "it follows from the values around it")
        elif "made after allocation" in rows[0][2]["note"]:
            frame.append((subst, addr_text))
            continue
        else:
            w("insn %s: ours %s  [at %s]" % (p, subst, addr_text))
            w("  " + rows[0][2]["note"])
        w()
    if frame:
        w("the prologue, epilogue and later splits: %s" % "; ".join("%s [at %s]" % f for f in frame))
        w("  made after allocation: their registers follow from the values' (the saved registers used)")
        w()
    levers = a.swaps() + levers
    roots = a.roots()
    if roots:
        for q in roots:
            chained = sorted(p for p in a.follows if q in a.follows[p])
            levers.append("r%d starts a chain: retail has it in the register %s take%s in ours; fix r%d first, "
                          "and the others may follow" % (
                              q, ", ".join("r%d" % p for p in chained) or "others", "s" if len(chained) == 1 else "", q))
    if levers:
        w("Likely levers:")
        seen = set()
        for s in levers:
            if s not in seen:
                seen.add(s)
                w("- " + s)
    return 1


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("src")
    parser.add_argument("func")
    parser.add_argument("--version", default="us", choices=["us", "eu"])
    parser.add_argument("--keep", metavar="DIR", help="where the dumps go (default build/regalloc/FUNC/)")
    args = parser.parse_args(argv)
    try:
        return run(Path(args.src), args.func, args.version, args.keep)
    except (cc.CompileError, RuntimeError, KeyError) as e:
        print("ERROR: %s" % e)
        return 2


if __name__ == "__main__":
    sys.exit(main())
