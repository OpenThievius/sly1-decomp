# SPDX-License-Identifier: AGPL-3.0-or-later
"""Replay GCC 2.95's first scheduling pass (haifa-sched, before reload) on a block, from the dumps.

    python3 tools/sched1.py FILE.cpp FUNC [--keep DIR] [--block N]   compile with the dumps, replay
    python3 tools/sched1.py --dumps DIR FUNC [--block N]             replay unit.ii.sched in DIR
    ... [--check] [--trace UID ...] [--prio UID=N ...] [--order]

sched1 reorders each basic block's insns by list scheduling, and the order it leaves decides every
pseudo's life, so local-alloc's and global-alloc's choices (tools/globalalloc.py) follow from it.
The compile asks for -dS -fsched-verbose-6 and -dN: the `.sched` dump then prints, per block, the
dependence table (each insn's code, dependence count, priority, cost, function unit and the insns
that depend on it, in the block's original order), the scheduled RTL whose LOG_LINKS give each
dependence's kind, and the scheduler's own trace (the ready list each cycle, each insn issued and
on which unit); the `.regmove` dump (-dN, the pass just before) gives the insns' REG_DEAD and
REG_UNUSED notes before sched1 removes them. This tool replays the scheduler cycle by cycle in our own code, following
haifa-sched.c's schedule_block:

- the priority of an insn is its longest path to the end of the block: its own cost with no
  dependents, else the maximum over them of the link's cost plus theirs; a link costs the
  producer's result latency, or 1 for an anti or output dependence (mips' ADJUST_COST) or when
  the consumer is not a recognised insn (a USE);
- the ready list starts with the insns that depend on nothing, and is sorted each cycle (best
  last) by rank_for_schedule: higher priority; then the smaller register weight (sets and
  clobbers minus REG_DEAD and REG_UNUSED notes, before sched1 removes the deaths); then the class
  against the insn just scheduled (not dependent, or a 1-cycle link, before an anti or output
  dependent, before a true dependent); then more dependents; then the earlier original position;
- each cycle issues up to two insns (the EE's issue rate), from the best down; an insn whose
  function unit is still busy waits (one memory access per cycle: the memory unit is busy for
  one cycle after an issue; the two ALUs are two instances); issuing resolves its dependents,
  which become ready this cycle when the link costs at most one cycle, else are queued for that
  many cycles. A newly ready insn takes the issued insn's slot in the array, as GCC's
  `ready[i] = ready[--n_ready]` does, and is not considered again in the same cycle;
- an insn made ready by its last dependence that sets a register live at the block's end, set
  once in the function, has its priority raised to max_priority (adjust_priority's birthing
  rule; deaths no longer count, since the notes were removed);
- a jump ends the block.

--alloc REG chains the replay into tools/globalalloc.py's local-alloc and global-alloc replays
(a function of one block): the deaths and lives are recomputed for the replayed order, so a
--prio hypothesis is followed to the registers without compiling.

--check replays every block of the function and compares the order and the cycle of each insn
with the trace the compiler printed. --prio UID=N sets an insn's priority (its dependents' are not
recomputed), to test a hypothesis without compiling; --order prints the replayed order;
--trace UID prints when an insn became ready and issued and what was ahead of it.

Validated (2026-11-10) on every function of src/main and 29 of the largest near misses: of
30,639 blocks scheduled alone (185,363 insns) the replay issues all but 4 in the trace's exact
order and cycles, func_00109488's 8,808-insn block included; 52 blocks of regions of several
blocks (interblock scheduling) are not replayed. The 4 involve the R5900's multiply-add and
block-move insns, whose clobbered scratch registers carry REG_UNUSED notes; how they are weighed
is not settled.

Partial emulators by other workers (build/swarm/w15-1CC818/sim.py in the g11 worktree,
w15-156288/sim.py and w15-142278/sim2.py in g10) read the same dependence tables; this replay
follows the scheduler's array handling and units more closely and checks itself on the trace.
"""

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import regalloc  # noqa: E402

ISSUE_RATE = 2
# function unit -> (instances, cycles an issue keeps an instance busy). An insn may use several
# (`[memory flop]`: a load to an FPR); the table prints each insn's units.
UNITS = {"memory": (1, 1), "alu": (2, 1), "flop": (1, 1), "fmac": (1, 1), "fdiv": (1, 1),
         "r5900imuldiv": (2, 1)}

ROW = re.compile(r"^;;\s+(\d+)\s+(-?\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+) -\s+(\d+)\s+(.*?)\t?:([ \d/b]*)$")


class Block:
    """One block's dependence table and trace from a verbose `.sched` dump."""

    def __init__(self, number):
        self.number = number
        self.rows = {}           # uid -> dict(code, deps, prio, cost, unit, succ)
        self.order = []          # the original order (LUID)
        self.trace = []          # [(clock, uid)] as the compiler issued them
        self.initial = []        # the ready list it printed first


def parse_sched(text):
    """[Block] of one function's part of a `.sched` dump made with -fsched-verbose-6."""
    blocks, cur, clock = [], None, 0
    for s in text.splitlines():
        m = re.match(r"^;;\s+-- basic block (\d+) from \d+ to \d+ -- before reload", s)
        if m:
            cur = Block(int(m.group(1)))
            blocks.append(cur)
            continue
        if cur is None:
            continue
        m = ROW.match(s)
        if m:
            uid = int(m.group(1))
            cur.rows[uid] = dict(code=int(m.group(2)), deps=int(m.group(4)), prio=int(m.group(5)),
                                 cost=int(m.group(6)), unit=m.group(9).strip(),
                                 succ=[int(x.split("/")[0]) for x in m.group(10).split()])
            cur.order.append(uid)
            continue
        m = re.match(r"^;;\s+Ready list initially:(.*)$", s)
        if m:
            cur.initial = [int(x.split("/")[0]) for x in m.group(1).split()]
            continue
        m = re.match(r"^;;\s+Ready list \(t =\s*(\d+)\):", s)
        if m:
            clock = int(m.group(1))
            continue
        m = re.match(r"^;;\s+--> scheduling insn <<<(\d+)>>>", s)
        if m:
            cur.trace.append((clock, int(m.group(1))))
    return blocks


def link_kinds(text):
    """{(producer, consumer): 0 true, 1 anti, 2 output} from the LOG_LINKS of the RTL."""
    kinds = {}
    for m in re.finditer(r"^\((?:insn|jump_insn|call_insn)[/a-z]* (\d+) ", text, re.M):
        uid = int(m.group(1))
        end = text.find("\n\n", m.start())
        body = text[m.start():end if end > 0 else len(text)]
        for kind, prod in re.findall(r"\(insn_list(:REG_DEP_\w+)? (\d+)", body):
            kinds[(int(prod), uid)] = 0 if not kind else (1 if "ANTI" in kind else 2)
    return kinds


def insn_info(text):
    """{uid: dict(weight, births, sets, deaths, call)} from an RTL dump whose notes are sched1's
    input (`.combine`): the register weight, the registers a SET makes live (birthing_insn_p's
    candidates), every register set or clobbered, the REG_DEAD and REG_UNUSED registers."""
    import globalalloc as ga
    out = {}
    chunk, depth, instr = [], 0, False
    for s in text.splitlines():
        if chunk or (s.startswith("(") and not depth):
            chunk.append(s)
            depth, instr = ga.balance(s, depth, instr)
            if depth > 0 or instr:
                continue
            sx = regalloc.parse_sexpr("\n".join(chunk))
            chunk = []
            if not isinstance(sx, list) or regalloc.head(sx) not in ("insn", "jump_insn", "call_insn"):
                continue
            pat = sx[4]
            rest = [x for x in sx[5:] if isinstance(x, list) or x == "nil"]
            notes = ga.note_list(rest[1] if len(rest) > 1 else None)
            h = ga.code(pat)
            elems = [pat] if h in ("set", "clobber") else (
                [y for y in pat[1][1:] if ga.code(y) in ("set", "clobber")] if h == "parallel" else [])
            deaths = [int(d[1]) for k, d in notes if k in ("REG_DEAD", "REG_UNUSED") and ga.code(d) == "reg"]
            n_notes = len(deaths)
            sets, births = [], []
            for e in elems:
                d = e[1]
                while ga.code(d) in ("subreg", "strict_low_part", "zero_extract", "sign_extract"):
                    d = d[1]
                if ga.code(d) == "reg":
                    sets.append(int(d[1]))
                    if ga.code(e) == "set" and ga.code(e[1]) == "reg":
                        births.append(int(d[1]))
            out[int(sx[1])] = dict(weight=len(elems) - n_notes, births=births, sets=sets,
                                   deaths=deaths, call=regalloc.head(sx) == "call_insn",
                                   dead_only=[int(d[1]) for k, d in notes if k == "REG_DEAD" and ga.code(d) == "reg"])
    return out


class Replay:
    def __init__(self, block, kinds, info, birthing=(), prio=None):
        self.b, self.kinds, self.info = block, kinds, info
        self.luid = {u: i for i, u in enumerate(block.order)}
        self.birthing = set(birthing)
        self.prio = {u: r["prio"] for u, r in block.rows.items()}
        self.prio.update(prio or {})
        self.events = {}

    def link_cost(self, a, b):
        rows = self.b.rows
        if self.kinds.get((a, b), 0) != 0 or rows[b]["code"] < 0:
            return 1
        return max(1, rows[a]["cost"])

    def computed_priorities(self):
        pr = {}
        rows = self.b.rows
        for u in reversed(self.b.order):
            succ = [v for v in rows[u]["succ"] if v in rows]
            pr[u] = max((self.link_cost(u, v) + pr[v] for v in succ), default=max(1, rows[u]["cost"]))
        return pr

    def run(self):
        rows, prio = self.b.rows, self.prio
        deps = {u: 0 for u in rows}
        for u, r in rows.items():
            for v in r["succ"]:
                if v in deps:
                    deps[v] += 1
        tick = {u: 0 for u in rows}
        ready = [u for u in self.b.order if deps[u] == 0]
        queue = {}               # clock -> [uids]
        unit_tick = {name: [0] * n for name, (n, _) in UNITS.items()}
        out, clock, last = [], 0, None
        weight = {u: self.info.get(u, {}).get("weight", 0) for u in rows}

        def cls(x):
            if last is None:
                return 0
            if x not in rows[last]["succ"] or self.link_cost(last, x) == 1:
                return 3
            return 1 if self.kinds.get((last, x), 0) == 0 else 2

        def key(x):
            return (prio[x], -weight[x], cls(x), len(rows[x]["succ"]), -self.luid[x])

        def names(x):
            return [n for n in rows[x]["unit"].strip("[]").split() if n in UNITS]

        def hazard(x):
            return max([min(max(0, t - clock) for t in unit_tick[n]) for n in names(x)] or [0])

        def occupy(x):
            for name in names(x):
                n, busy = UNITS[name]
                ticks = unit_tick[name]
                k = next((i for i in range(n) if ticks[i] - clock <= 0), 0)
                ticks[k] = clock + busy

        n_total = len(rows)
        while len(out) < n_total:
            clock += 1
            ready += queue.pop(clock, [])
            if not ready:
                nxt = min(queue)
                ready += queue.pop(nxt)
                clock = nxt
            ready.sort(key=key)
            can = ISSUE_RATE
            i = len(ready) - 1
            while i >= 0 and can:
                x = ready[i]
                cost = hazard(x)
                if cost > 1:
                    queue.setdefault(clock + cost, []).append(x)
                    ready[i] = ready[-1]
                    ready.pop()
                elif cost == 0:
                    out.append((clock, x))
                    self.events.setdefault(x, {})["issued"] = clock
                    last = x
                    can -= 1
                    occupy(x)
                    if rows[x]["succ"]:
                        maxp = max(prio[ready[0]], prio[x])
                        for v in rows[x]["succ"]:
                            if v not in rows:
                                continue
                            tick[v] = max(tick[v], clock + self.link_cost(x, v))
                            deps[v] -= 1
                            if deps[v] == 0:
                                if v in self.birthing and maxp > prio[v]:
                                    prio[v] = maxp
                                eff = tick[v] - clock
                                self.events.setdefault(v, {})["ready"] = clock
                                if eff <= 1:
                                    ready.append(v)
                                else:
                                    queue.setdefault(clock + eff, []).append(v)
                    ready[i] = ready[-1]
                    ready.pop()
                    if rows[x].get("jump"):
                        break
                i -= 1
                if i >= len(ready):
                    i = len(ready) - 1
        self.out = out
        return out


def birthing_insns(block, info, live_start, n_sets):
    """The insns birthing_insn_p accepts: a SET of a register live at the end of
    find_pre_sched_live's forward walk (sets make live, a call makes every call-clobbered
    register live, REG_DEAD and REG_UNUSED kill), set once in the function."""
    import globalalloc as ga
    ga.set_target(112)
    clobbered = (ga.CALL_USED - ga.FIXED) & set(range(ga.FIRST_PSEUDO))
    live = set(live_start)
    for u in block.order:
        i = info.get(u)
        if not i:
            continue
        live |= set(i["sets"])
        if i["call"]:
            live |= clobbered
        live -= set(i["deaths"])
    return {u for u in block.order if any(r in live and n_sets.get(r) == 1 for r in info.get(u, {}).get("births", ()))}


def compare(block, out, file=sys.stdout):
    """0 when the replay issues the block's insns in the trace's order and cycles, 1 when not,
    None for a block of a multi-block region (interblock scheduling, not replayed)."""
    want = block.trace
    if {u for c, u in want} != set(block.rows):
        print("block %d: part of a region of several blocks, not replayed" % block.number, file=file)
        return None
    k = next((i for i, (a, b) in enumerate(zip(out, want)) if a != b), None)
    if k is None and len(out) == len(want):
        print("block %d: %d insns, order and cycles as the trace (%d cycles)" % (
            block.number, len(want), want[-1][0] if want else 0), file=file)
        return 0
    k = k if k is not None else min(len(out), len(want))
    print("block %d: %d insns, first difference at %d: replay %s, trace %s" % (
        block.number, len(want), k, out[k:k + 4], want[k:k + 4]), file=file)
    same_order = [u for c, u in out] == [u for c, u in want]
    if same_order:
        print("  (same order, different cycles)", file=file)
    return 1


def load(folder, func):
    folder = Path(folder)
    sched = regalloc.function_part((folder / "unit.ii.sched").read_text(errors="replace"), func)
    # sched1's input notes: regmove's dump, the pass just before (combine's if there is none)
    name = "unit.ii.regmove" if (folder / "unit.ii.regmove").exists() else "unit.ii.combine"
    comb = regalloc.function_part((folder / name).read_text(errors="replace"), func)
    if sched is None or comb is None:
        raise SystemExit("no part for %s in the dumps" % func)
    return sched, comb


def lreg_flow(lreg_text):
    """{block: registers live at its start} and {pseudo: times set}, from `.lreg`."""
    live = {}
    for m in re.finditer(r"^Basic block (\d+): .*?\n(?:.*\n)*?Registers live at start:([^\n]*)", lreg_text, re.M):
        live[int(m.group(1))] = {int(x) for x in m.group(2).split() if x.isdigit()}
    sets = {int(a): int(b) for a, b in re.findall(r"^Register (\d+) used -?\d+ times across -?\d+ insns.*?; set (\d+) times?", lreg_text, re.M)}
    return live, sets


def replay_function(sched, comb, live=None, n_sets=None, prio=None):
    blocks = parse_sched(sched)
    kinds = link_kinds(sched)
    jumps = {int(u) for u in re.findall(r"^\(jump_insn[/a-z]* (\d+) ", sched, re.M)}
    for b in blocks:
        for u in b.rows:
            b.rows[u]["jump"] = u in jumps
    # insns split by sched1 itself (split_block_insns) are not in .combine: their notes are
    # the scheduled RTL's
    info = insn_info(sched)
    combined = insn_info(comb)
    info.update(combined)
    # REG_N_SETS: the dump's count for pseudos, the RTL's sets and clobbers for hard registers
    counts = {}
    for i in combined.values():
        for r in i["sets"]:
            counts[r] = counts.get(r, 0) + 1
    counts.update(n_sets or {})
    results = []
    for b in blocks:
        births = birthing_insns(b, info, (live or {}).get(b.number, set()), counts) if live is not None else ()
        r = Replay(b, kinds, info, births, prio)
        r.run()
        results.append((b, r))
    return results


def compile_dumps(path, func, keep):
    import compile as cc
    import check as chk
    path = Path(path)
    source = chk.source_for(path, func)
    flags = cc.flags_for(source) + ["-dS", "-dN", "-dl", "-dg", "-fsched-verbose-6"]
    keep = Path(keep)
    keep.mkdir(parents=True, exist_ok=True)
    cc.compile_file(path, keep / "unit.o", flags, source=source, keep_dumps=keep)
    return keep


def allocate_after(order, lreg_text, greg_text):
    """Both allocators on a one-block function whose insns are put in ORDER (uids, as a replay
    issued them): the deaths are recomputed for that order (a backward walk from the registers
    live at the end), each pseudo's life keeps its ratio to its span in the dump's own order
    (update_equiv_regs doubles most constants'), then local-alloc's and global-alloc's replays
    (tools/globalalloc.py) run. Returns (local placements, the global model)."""
    import copy
    import globalalloc as ga
    pseudos, local, insns, flow = ga.parse_lreg(lreg_text)
    if len(flow["blocks"]) != 1:
        raise SystemExit("--alloc needs a function of one block")
    at = flow["at"]
    end = re.search(r"Registers live at end:([^\n]*)", lreg_text)
    live = {int(x) for x in end.group(1).split() if x.isdigit()} if end else set()
    insns = list(insns)
    for u in reversed(order):
        pat, notes, usage = insns[at[u]]
        defs, uses = regalloc.defs_uses(pat)
        if usage:
            uses |= set(regalloc.regs_in(usage))
        dead = sorted(r for r in uses if r not in live and r not in ga.FIXED)
        unused = sorted(r for r in defs if r not in live and r not in uses and r not in ga.FIXED)
        live = (live - defs) | uses
        items = [(k, d) for k, d in ga.note_list(notes) if k not in ("REG_DEAD", "REG_UNUSED")]
        items += [("REG_DEAD", ["reg:SI", str(r)]) for r in dead]
        items += [("REG_UNUSED", ["reg:SI", str(r)]) for r in unused]
        node = ["nil"]
        for k, d in reversed(items):
            node = ["expr_list:" + k, d, node]
        insns[at[u]] = (pat, node, usage)

    def spans(seq, table):
        first, last = {}, {}
        for k, u in enumerate(seq):
            for r in regalloc.regs_in(table[at[u]][0]):
                first.setdefault(r, k)
                last[r] = k
        return first, last

    old = [u for u in flow["chain"] if u in at]
    of, ol = spans(old, insns)
    nf, nl = spans(order, insns)
    pseudos = copy.deepcopy(pseudos)
    for r, p in pseudos.items():
        if r in of and r in nf:
            p.length = int(round(p.length / float(ol[r] - of[r] + 1) * (nl[r] - nf[r] + 1)))
    ids = set(order)
    flow = dict(flow, chain=[flow["chain"][0]] + list(order) + [x for x in flow["chain"][1:] if x not in ids],
                blocks=[(order[0], order[-1], flow["blocks"][0][2])])
    placed = ga.LocalModel(pseudos, insns, flow).run()
    m = ga.Model(pseudos, placed, insns, ga.parse_greg(greg_text))
    m.flow, m.recompute = flow, True
    ga.replay(m)
    return placed, m


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("file", nargs="?")
    ap.add_argument("func")
    ap.add_argument("--dumps")
    ap.add_argument("--keep")
    ap.add_argument("--block", type=int, action="append")
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--order", action="store_true")
    ap.add_argument("--trace", type=int, action="append")
    ap.add_argument("--prio", action="append", help="UID=N: an insn's priority")
    ap.add_argument("--alloc", type=int, action="append",
                    help="then replay both allocators on the replayed order; print this pseudo's register")
    args = ap.parse_args(argv)
    folder = Path(args.dumps) if args.dumps else compile_dumps(
        args.file, args.func, args.keep or regalloc.ROOT / "build" / "sched1" / args.func)
    sched, comb = load(folder, args.func)
    lreg_path = folder / "unit.ii.lreg"
    live = n_sets = None
    if lreg_path.exists():
        part = regalloc.function_part(lreg_path.read_text(errors="replace"), args.func)
        if part:
            live, n_sets = lreg_flow(part)
    prio = {int(k): int(v) for k, v in (x.split("=") for x in args.prio or [])}
    bad = 0
    for b, r in replay_function(sched, comb, live, n_sets, prio):
        if args.block and b.number not in args.block:
            continue
        if args.check or not (args.order or args.trace):
            bad += compare(b, r.out) or 0
        if args.order:
            print(" ".join(str(u) for c, u in r.out))
        for u in args.trace or []:
            if u in b.rows:
                ev = r.events.get(u, {})
                pos = [x for c, x in r.out].index(u)
                print("insn %d: priority %d, ready at %s, issued at cycle %s, position %d of %d" % (
                    u, r.prio[u], ev.get("ready", 0), ev.get("issued"), pos, len(r.out)))
    if args.alloc:
        import globalalloc as ga
        lt = regalloc.function_part((folder / "unit.ii.lreg").read_text(errors="replace"), args.func)
        gt = regalloc.function_part((folder / "unit.ii.greg").read_text(errors="replace"), args.func)
        (b, r), = replay_function(sched, comb, live, n_sets, prio)
        placed, m = allocate_after([u for c, u in r.out], lt, gt)
        for x in args.alloc:
            print("pseudo %d: local %s, final %s" % (x, regalloc.reg_name(placed[x]) if x in placed else "-",
                                                     regalloc.reg_name(m.renumber.get(x, -1)) if m.renumber.get(x, -1) >= 0 else "-"))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
