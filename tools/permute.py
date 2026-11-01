# SPDX-License-Identifier: AGPL-3.0-or-later
"""Try every order of some statements of a near miss, and keep the closest.

    python3 tools/permute.py FILE FUNC [--auto] [--version eu] [--unit SHARED.cpp] [--write OUT]

The compiler schedules independent statements (a run of stores, say) in an order that follows
the source only loosely: retail's order is often one particular order of the same lines, and
"tried every order" by hand usually means tried a few. This tries them all.

Mark the lines to reorder with a /*P*/ comment; consecutive marked lines form one group, and the
groups are permuted together (at most --limit orders in all). --auto marks every run of two to
seven consecutive simple statements (an assignment or a call ending in `;`) instead, and then
permutes one run at a time, keeping the best order of each before the next; a run with more
orders than --limit is taken in overlapping windows that fit it.

Each candidate is compiled the way the function lands (its src/ file's compiler and flags,
check.source_for(); with --unit, in that shared file's unit as PAL's own definitions are) and
compared with retail as tools/check.py compares it. The score is the number of bytes that differ
(another size counts every byte). It stops at the first EXACT order and prints it; --write saves
the best candidate. Nothing it finds counts until tools/check.py says EXACT in the build.

After OpenRAC's tools/permute.py (rac1-decomp, docs/agents/PERMUTER.md; credited in
THIRD_PARTY_NOTICES.md); the code is ours.
"""

import argparse
import concurrent.futures
import itertools
import math
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
WORK = ROOT / "build" / "permute"
MARK = "/*P*/"
SIMPLE = re.compile(r"^\s+(?!return\b|if\b|else\b|for\b|while\b|do\b|switch\b|case\b|goto\b|break\b|"
                    r"continue\b)[^{};]*;\s*(//.*|/\*.*\*/)?\s*$")


def groups(lines, auto):
    """[[line index, ...], ...]: the runs of lines to permute."""
    out, run = [], []
    for i, line in enumerate(lines):
        hit = (SIMPLE.match(line) and "=" in line or SIMPLE.match(line) and "(" in line) if auto else MARK in line
        if hit:
            run.append(i)
            continue
        if len(run) >= 2:
            out.append(run[:7] if auto else run)
        run = []
    if len(run) >= 2:
        out.append(run[:7] if auto else run)
    return out


class Scorer:
    def __init__(self, func, key, unit, source_path):
        import check
        import compile as cc
        self.check, self.cc = check, cc
        self.func, self.key, self.unit = func, key, Path(unit).resolve() if unit else None
        self.source = check.source_for(source_path, func) if not unit else self.unit
        self.resolver = check.Resolver(key)
        self.image = check.retail_image(key)
        _, self.size = check.target_of(key, func)
        WORK.mkdir(parents=True, exist_ok=True)

    def score(self, text, tag):
        """Bytes that differ from retail (0 = EXACT), or None if it does not compile."""
        import elf
        src = WORK / ("%s_%s.cpp" % (self.func, tag))
        obj = WORK / ("%s_%s.o" % (self.func, tag))
        if self.unit:
            import version_src
            mine = {n: p for n, p in version_src.overrides(self.key).items()
                    if version_src.version_of(p)[1] == self.unit}
            body = WORK / ("%s_%s_def.cpp" % (self.func, tag))
            body.write_text(text)
            mine[self.func] = body
            src.write_text(version_src.unit_text(self.unit, mine))
        else:
            src.write_text(text)
        try:
            self.cc.compile_file(src, obj, source=self.source)
            r = self.check.check_function(elf.Elf(obj.read_bytes()), self.func, self.key, self.resolver, self.image)
        except (self.cc.CompileError, KeyError):
            return None
        finally:
            for p in (src, obj):
                if p.exists():
                    p.unlink()
        if r.get("status") == "EXACT":
            return 0
        ours, retail = r.get("ours", b""), r.get("retail", b"")[:self.size]
        if len(ours) != self.size:
            return self.size + abs(len(ours) - self.size)
        return sum(1 for a, b in zip(ours, retail) if a != b)


def orders(lines, runs):
    """Every candidate text for one or more runs permuted together."""
    for choice in itertools.product(*(itertools.permutations(r) for r in runs)):
        new = list(lines)
        for run, perm in zip(runs, choice):
            for dst, src in zip(run, perm):
                new[dst] = lines[src]
        yield new


def search(scorer, lines, runs, jobs, limit):
    """(best score, best lines) over the orders of `runs`, stopping at 0."""
    total = math.prod(math.factorial(len(r)) for r in runs)
    if total > limit:
        raise SystemExit("%d orders is more than --limit %d: mark fewer lines" % (total, limit))
    best = (None, lines)
    with concurrent.futures.ThreadPoolExecutor(jobs) as pool:
        batch = []
        for n, cand in enumerate(orders(lines, runs)):
            batch.append((n, cand))
            if len(batch) < jobs * 4:
                continue
            best = merge(best, pool, scorer, batch)
            batch = []
            if best[0] == 0:
                return best
        if batch:
            best = merge(best, pool, scorer, batch)
    return best


def merge(best, pool, scorer, batch):
    for (n, cand), s in zip(batch, pool.map(lambda b: scorer.score("\n".join(b[1]) + "\n", "%d_%d" % (os.getpid(), b[0])), batch)):
        if s is not None and (best[0] is None or s < best[0]):
            best = (s, cand)
    return best


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("file")
    parser.add_argument("func")
    parser.add_argument("--auto", action="store_true", help="permute every run of simple statements, one at a time")
    parser.add_argument("--version", default="us", choices=["us", "eu"])
    parser.add_argument("--unit", metavar="SHARED.cpp", help="FILE is a version's own definition in that unit")
    parser.add_argument("--jobs", type=int, default=6)
    parser.add_argument("--limit", type=int, default=5040)
    parser.add_argument("--write", metavar="OUT", help="save the best candidate here")
    args = parser.parse_args(argv)
    key = "eu" if args.unit and args.version == "us" else args.version
    lines = Path(args.file).read_text().rstrip("\n").split("\n")
    runs = groups(lines, args.auto)
    if not runs:
        print("nothing to permute: mark lines with %s, or use --auto" % MARK)
        return 2
    scorer = Scorer(args.func, key, args.unit, args.file)
    start = scorer.score("\n".join(lines) + "\n", "start")
    print("%s: start %s bytes differ; %d run(s) of %s lines" % (
        args.func, "?" if start is None else start, len(runs), "/".join(str(len(r)) for r in runs)))
    best = (start, lines)
    if args.auto:
        # One run at a time, each from the best so far; a run with more orders than --limit is
        # taken in overlapping windows of as many lines as the limit allows.
        k = max(n for n in range(2, 8) if math.factorial(n) <= args.limit)
        runs = [r[i:i + k] for r in runs for i in range(0, max(1, len(r) - 1), k - 1) if len(r[i:i + k]) >= 2]
        for run in runs:
            s, cand = search(scorer, best[1], [run], args.jobs, args.limit)
            if s is not None and (best[0] is None or s < best[0]):
                best = (s, cand)
            if best[0] == 0:
                break
    else:
        s, cand = search(scorer, lines, runs, args.jobs, args.limit)
        if s is not None and (best[0] is None or s < best[0]):
            best = (s, cand)
    status = "EXACT" if best[0] == 0 else "best %s bytes differ" % best[0]
    print("%s: %s" % (args.func, status))
    if args.write and best[0] is not None and (start is None or best[0] < start):
        Path(args.write).write_text("\n".join(best[1]) + "\n")
        print("wrote %s" % args.write)
    return 0 if best[0] == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
