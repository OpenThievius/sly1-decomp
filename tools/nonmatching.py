# SPDX-License-Identifier: AGPL-3.0-or-later
"""The near misses in nonmatching/: their verdicts, their index, and staging the closest attempts.

    python3 tools/nonmatching.py check                 # re-score every staged file (compiler needed)
    python3 tools/nonmatching.py stage GLOB [--max 0.15]
    python3 tools/nonmatching.py --check               # CI: verdicts present, nothing staged is matched

A near miss is C for a function that compiles and comes close to retail but is not EXACT. The best
one per function is kept, so everyone can see what is open and how close it is, and pick it up
instead of starting over. Nothing builds these files into the game.

- nonmatching/func_XXXXXXXX.cpp: a US function, checked as tools/check.py checks it.
- nonmatching/eu/FUNC.cpp: PAL's own definition (docs/VERSIONS.md), checked in the shared file
  its header names (`--unit src/main/....cpp`).

Each file's second line is its verdict, written by `check`:

    // BYTES 196/208 (94.2%), checked 2026-11-01      the same size, so many bytes equal retail's
    // SIZE 216/208, checked 2026-11-01               another size: every byte after it moves, so 0
    // BROKEN, checked 2026-11-01                     no longer compiles or places against its file: 0

tools/progress.py reports the share as the function's fuzzy_match_percent: matched code and
matched functions still count EXACT functions only, and a near miss stays below 100.
nonmatching/README.md lists every one, closest first; it is generated.

`stage` adds an attempt (a worker's file) when it is within --max of retail's bytes and closer
than what is staged. Landing a function removes its staged file (by whoever staged it: --check
lists those left over, and progress ignores them).

The layout follows OpenRAC's (rac1-decomp, docs/reference/NONMATCHING.md; credited in
THIRD_PARTY_NOTICES.md); the tool is ours.
"""

import argparse
import datetime
import glob
import re
import shutil
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
DIR = ROOT / "nonmatching"
INDEX = DIR / "README.md"
SPDX = "// SPDX-License-Identifier: AGPL-3.0-or-later"
VERDICT = re.compile(r"^// (?:BYTES (\d+)/(\d+) \([\d.]+%\)|SIZE (\d+)/(\d+)|(BROKEN)), checked (\d{4}-\d{2}-\d{2})$")
UNIT = re.compile(r"--unit (\S+\.cpp)")


def staged():
    """{(version, function): file} of every staged near miss."""
    out = {("us", p.stem): p for p in sorted(DIR.glob("func_*.cpp"))}
    out.update({("eu", p.stem): p for p in sorted((DIR / "eu").glob("func_*.cpp"))})
    return out


def verdict(path):
    """(matching bytes, retail's size, checked) from a file's verdict line, or None."""
    lines = Path(path).read_text().splitlines()
    m = VERDICT.match(lines[1]) if len(lines) > 1 else None
    if not m:
        return None
    if m.group(1):
        return int(m.group(1)), int(m.group(2)), m.group(6)
    if m.group(5):
        return 0, 0, m.group(6)
    return 0, int(m.group(4)), m.group(6)


def share(path):
    """The fuzzy match of a staged file, 0 to just under 100: what tools/progress.py reports."""
    v = verdict(path)
    if not v or not v[1]:
        return 0.0
    return min(100.0 * v[0] / v[1], 99.99)


def unit_of(path):
    """The shared file a PAL definition is built in, from its header."""
    m = UNIT.search(Path(path).read_text())
    if not m:
        raise SystemExit("%s: no `--unit src/....cpp` in its header" % Path(path).relative_to(ROOT))
    return ROOT / m.group(1)


def score(path, key, func):
    """(status, matching bytes, our size, retail's size) of an attempt, compiled as it would land."""
    import check
    import compile as cc
    import elf
    import version_src
    with tempfile.TemporaryDirectory(prefix="sly1-nm-") as tmp:
        obj_path = Path(tmp) / "unit.o"
        try:
            if key == "us":
                cc.compile_file(path, obj_path)
            else:
                shared = unit_of(path)
                unit, _ = version_src.unit(shared, key, {func: Path(path).resolve()})
                cc.compile_file(unit, obj_path, flags=cc.flags_for(shared))
        except cc.CompileError:
            return "ERROR", 0, 0, 0
        obj = elf.Elf(obj_path.read_bytes())
    try:
        r = check.check_function(obj, func, key, check.Resolver(key), check.retail_image(key))
    except KeyError:
        return "ERROR", 0, 0, 0
    if "ours" not in r:
        return "ERROR", 0, 0, 0
    _, size = check.target_of(key, func)
    ours, retail = r["ours"], r["retail"][:size]
    if r["status"] == "EXACT":
        return "EXACT", size, size, size
    if len(ours) != size:
        return "DIFFER", 0, len(ours), size
    return "DIFFER", sum(1 for a, b in zip(ours, retail) if a == b), size, size


def line(matching, ours, size, day):
    if ours != size:
        return "// SIZE %d/%d, checked %s" % (ours, size, day)
    return "// BYTES %d/%d (%.1f%%), checked %s" % (matching, size, 100.0 * matching / size if size else 0, day)


def write_verdict(path, text):
    lines = Path(path).read_text().splitlines()
    body = [l for l in lines if l != SPDX and not VERDICT.match(l)]
    Path(path).write_text("\n".join([SPDX, text] + body) + "\n")


def write_index():
    rows = []
    for (key, func), path in staged().items():
        if matched(key, func):
            continue
        v = verdict(path)
        rows.append((-share(path), key, func, path, v))
    rows.sort()
    text = ["# Near misses", "",
            "Generated by `python3 tools/nonmatching.py check`: never edit it by hand. Closest first;",
            "the share is of retail's bytes (0 when the size differs). See tools/nonmatching.py.", "",
            "| Function | Version | Match | Checked |", "|---|---|---:|---|"]
    for neg, key, func, path, v in rows:
        match = ("%.1f%%" % -neg) if v and v[0] else ("does not compile" if v and not v[1] else "size differs")
        text.append("| [%s](%s) | %s | %s | %s |" % (func, path.relative_to(DIR).as_posix(), key, match,
                                                    v[2] if v else "-"))
    INDEX.write_text("\n".join(text) + "\n")


def matched(key, func):
    """True when the function is matched already, so its staged file is left over."""
    import version_check
    if key == "us":
        return func in version_check.defined_in_src()
    return version_check.read_status().get(func, ("", ""))[1] == "match"


def cmd_check():
    day = datetime.date.today().isoformat()
    exact = []
    for (key, func), path in staged().items():
        if matched(key, func):
            print("matched already, left as it is: %s" % path.relative_to(ROOT))
            continue
        status, matching, ours, size = score(path, key, func)
        if status == "EXACT":
            exact.append(path)
            continue
        if status == "ERROR":
            print("does not compile or place: %s" % path.relative_to(ROOT))
            write_verdict(path, "// BROKEN, checked %s" % day)
            continue
        write_verdict(path, line(matching, ours, size, day))
    write_index()
    for p in exact:
        print("now EXACT, land it: %s" % p.relative_to(ROOT))
    print("checked %d near misses" % len(staged()))
    return 0


def cmd_stage(pattern, most, key):
    """Stage each function's closest attempt among the files the pattern finds."""
    import version_check
    defined = set(version_check.defined_in_src())
    day = datetime.date.today().isoformat()
    best = {}
    for f in sorted(glob.glob(pattern)):
        func = Path(f).stem
        if key == "us" and func in defined:
            continue
        status, matching, ours, size = score(f, key, func)
        if status != "DIFFER" or ours != size or not size or 1 - matching / size > most:
            continue
        if func not in best or matching > best[func][1]:
            best[func] = (f, matching, ours, size)
    added = 0
    for func, (f, matching, ours, size) in sorted(best.items()):
        dest = (DIR if key == "us" else DIR / "eu") / (func + ".cpp")
        if dest.exists() and (verdict(dest) or (0, 1))[0] >= matching:
            continue
        dest.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(f, dest)
        write_verdict(dest, line(matching, ours, size, day))
        added += 1
    write_index()
    print("staged %d near misses" % added)
    return 0


def check_current():
    """CI: every staged file of an unmatched function has a verdict.

    A staged file whose function is matched is left over: listed, not a failure, because only the
    contributor who staged it removes it (AGENTS.md: never delete what you did not create).
    """
    problems, left = [], []
    for (key, func), path in staged().items():
        rel = path.relative_to(ROOT)
        if matched(key, func):
            left.append(rel)
        elif verdict(path) is None:
            problems.append("%s has no verdict line (run python3 tools/nonmatching.py check)" % rel)
    if left:
        print("note: %d staged files are for matched functions (their contributors remove them)" % len(left))
    for p in problems:
        print("stale: " + p)
    return 1 if problems else 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--check", action="store_true", help="CI: no compiler needed")
    sub = parser.add_subparsers(dest="cmd")
    sub.add_parser("check", help="re-score every staged file and write the index")
    p = sub.add_parser("stage", help="stage the closest attempts among the files GLOB finds")
    p.add_argument("pattern")
    p.add_argument("--max", type=float, default=0.15, help="the largest share of retail's bytes that may differ")
    p.add_argument("--version", default="us", choices=["us", "eu"])
    args = parser.parse_args(argv)
    if args.check:
        return check_current()
    if args.cmd == "check":
        return cmd_check()
    if args.cmd == "stage":
        return cmd_stage(args.pattern, args.max, args.version)
    parser.print_help()
    return 2


if __name__ == "__main__":
    sys.exit(main())
