# SPDX-License-Identifier: AGPL-3.0-or-later
"""Compile the source with a modern Clang, syntax only, to find what a port's compiler rejects.

    python3 tools/modern_check.py             # counts by kind, and the errors a port must fix
    python3 tools/modern_check.py --check     # fail if a file has more port errors than the baseline
    python3 tools/modern_check.py --baseline  # rewrite config/modern_baseline.tsv

The matching build uses the 1999 compiler, which accepts things a current one does not. This tool
compiles every C and C++ unit of src/ the way the game is built (32-bit little-endian MIPS, C++98
or C89 with GNU extensions, the build's include paths) with Clang, without generating code, and
sorts each error:

    ps2         the PS2-only inline-assembly helpers (include/vu0.h, system.h, fpu.h, mul_wide.h):
                vector-unit registers and constraints Clang does not know, the 128-bit values
                they pass, and any error inside those headers (g++ 2.95's named return values). A port replaces these helpers (docs/PORTING.md), so they are counted
                and not listed.
    toolchain   the 1999 compiler's own internals: its variable-argument builtins
                (`__builtin_next_arg`), the C++ runtime's exception records and its
                `__builtin_eh_return` (three arguments there, two in later compilers); a port uses its
                own compiler's <stdarg.h> and runtime. Counted, not listed.
    port        everything else: code a modern compiler rejects, which a port must change.

Two g++ 2.95 extensions removed from later compilers are rewritten on a copy of the tree first,
so the rest of each file is still checked: the minimum and maximum operators (`a <? b`,
`a >? b`, and `a >?= b`), and named return values (`T F(args) return r { ... }`, which retail's matrix
functions need, docs/TOOLCHAIN.md), listed in the report as changes a port must make. config/modern_baseline.tsv records each file's port errors; `--check`
fails when a file has more than its baseline, so a change cannot add new ones. Needs `clang`
(or $CLANG); without it, `--check` says so and passes.
"""

import argparse
import collections
import concurrent.futures
import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BASELINE = ROOT / "config" / "modern_baseline.tsv"
FLAGS = ["-fsyntax-only", "-w", "-ferror-limit=0", "--target=mipsel-linux-gnu", "-Iinclude",
         "-Isrc", "-D__GNUC__=2", "-D__GNUC_MINOR__=9", "-D__mips__", "-D__R5900__",
         "-D__mips_single_float", "-fno-color-diagnostics", "-fno-spell-checking"]
PS2 = re.compile(r"in asm$|unknown register name|cannot take the address of an rvalue of type "
                 r"'(?:s|u)128'|__builtin_(?:set|long)jmp is not supported")
# The PS2-only helper headers (docs/PORTING.md): a port replaces them, so their own errors (vector
# registers, g++ 2.95's named return values) are not the port's to fix in the game code.
HELPERS = {"include/vu0.h", "include/fpu.h", "include/system.h", "include/mul_wide.h"}
# The 1999 compiler's own internals the code reaches: its variable-argument builtins and the C++
# runtime's exception records. A port uses its own compiler's <stdarg.h> and C++ runtime.
TOOLCHAIN = re.compile(r"'__builtin_(?:next_arg|args_info|saveregs)'|'__exception_info'|"
                       r"include <typeinfo> before using the 'typeid'")
ERROR = re.compile(r"^(?P<file>[^:\n]+):(?P<line>\d+):(?P<col>\d+): error: (?P<msg>.*)$", re.M)


def units():
    out = []
    for d in ("src/main", "src/lib", "src/libm"):
        out += sorted(str(p.relative_to(ROOT)) for p in (ROOT / d).glob("*.c*"))
    return out


def sanitize(text):
    """g++'s `<?` and `>?` become `+ ` (columns kept); a string literal broken over a line is
    closed and reopened, as Clang wants."""
    out, i, n, state = [], 0, len(text), "code"
    while i < n:
        ch, nx = text[i], text[i + 1] if i + 1 < n else ""
        if state == "code":
            if ch == "/" and nx == "/":
                state = "line"
            elif ch == "/" and nx == "*":
                out.append("/*")
                i += 2
                state = "block"
                continue
            elif ch == '"':
                state = "string"
            elif ch == "'":
                state = "char"
            elif ch in "<>" and nx == "?" and text[i - 1:i] != ch:
                if text[i + 2:i + 3] == "=":    # the compound forms, `a >?= b`
                    out.append("+= ")
                    i += 3
                else:
                    out.append("+ ")
                    i += 2
                continue
        elif state == "line":
            if ch == "\n":
                state = "code"
        elif state == "block":
            if ch == "*" and nx == "/":
                out.append("*/")
                i += 2
                state = "code"
                continue
        else:
            if ch == "\\":
                out.append(ch + nx)
                i += 2
                continue
            if ch == "\n" and state == "string":
                out.append('"\n"')
                i += 1
                continue
            if (ch == '"' and state == "string") or (ch == "'" and state == "char"):
                state = "code"
        out.append(ch)
        i += 1
    return "".join(out)


# g++ 2.95's named return value: `T F(args) return name {` declares `name` as the result.
NAMED_RETURN = re.compile(r"^(?!\s*//)(?P<head>[^\n;{}/]*?(?P<type>[A-Za-z_][\w:]*)\s+[\w:]+\s*\((?:(?!//)[^;{}])*?\))\s*"
                          r"return\s+(?P<name>\w+)\s*\n\{", re.M)


def standard_returns(text):
    """[(line, name)] of g++'s named return values in text, and the text with each rewritten to
    standard C++ (the name declared at the top of the body; a modern compiler then sees the rest)."""
    found = []

    def sub(m):
        found.append((text.count("\n", 0, m.start()) + 1, m.group("name")))
        return "%s\n{ %s %s;" % (m.group("head"), m.group("type"), m.group("name"))
    return NAMED_RETURN.sub(sub, text), found


def mirror(tmp):
    named = []
    for d in ("include", "src"):
        for path in (ROOT / d).rglob("*"):
            if path.is_dir() or path.suffix not in (".h", ".c", ".cpp", ".inc"):
                continue
            dst = Path(tmp) / path.relative_to(ROOT)
            dst.parent.mkdir(parents=True, exist_ok=True)
            text, found = standard_returns(path.read_text(errors="replace"))
            named += [(str(path.relative_to(ROOT)), line, name) for line, name in found]
            dst.write_text(sanitize(text))
    return named


def compile_unit(clang, tmp, unit):
    lang = ["-x", "c", "-std=gnu89"] if unit.endswith(".c") else ["-x", "c++", "-std=gnu++98"]
    r = subprocess.run([clang] + FLAGS + lang + [unit], capture_output=True, text=True, cwd=tmp)
    errors = []
    for m in ERROR.finditer(r.stderr):
        f = m.group("file")
        if os.path.isabs(f):
            f = os.path.relpath(os.path.realpath(f), os.path.realpath(tmp))
        msg = m.group("msg")
        src = Path(tmp) / f
        line = src.read_text(errors="replace").split("\n")[int(m.group("line")) - 1] if src.exists() else ""
        kind = ("ps2" if PS2.search(msg) or f in HELPERS else
                "toolchain" if TOOLCHAIN.search(msg) or "__builtin_eh_return" in line else "port")
        errors.append((unit, f, int(m.group("line")), kind, m.group("msg")))
    return errors


def run(clang):
    with tempfile.TemporaryDirectory(prefix="sly1-modern-") as tmp:
        run.named = mirror(tmp)
        with concurrent.futures.ThreadPoolExecutor(os.cpu_count() or 4) as ex:
            results = list(ex.map(lambda u: compile_unit(clang, tmp, u), units()))
    # An error in a header shows once per unit that includes it: count it once.
    seen, out = set(), []
    for errs in results:
        for unit, f, line, kind, msg in errs:
            key = (f, line, msg)
            if key not in seen:
                seen.add(key)
                out.append((unit, f, line, kind, msg))
    return out


def per_file(errors):
    counts = collections.Counter()
    for _, f, _, kind, _ in errors:
        if kind == "port":
            counts[f] += 1
    return counts


def read_baseline():
    if not BASELINE.exists():
        return {}
    rows = [l.split("\t") for l in BASELINE.read_text().splitlines()[1:] if l]
    return {f: int(n) for f, n in rows}


def write_baseline(counts):
    lines = ["file\tport_errors"] + ["%s\t%d" % (f, n) for f, n in sorted(counts.items())]
    BASELINE.write_text("\n".join(lines) + "\n")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--check", action="store_true", help="fail if a file has more port errors than the baseline")
    ap.add_argument("--baseline", action="store_true", help="rewrite config/modern_baseline.tsv")
    ap.add_argument("--all", action="store_true", help="list every port error (default: the first 40)")
    args = ap.parse_args(argv)
    clang = os.environ.get("CLANG") or shutil.which("clang")
    if not clang:
        print("clang not found (set CLANG): skipped")
        return 0
    errors = run(clang)
    kinds = collections.Counter(kind for *_, kind, _ in errors)
    counts = per_file(errors)
    print("%d port errors in %d files; %d in the PS2-only helpers; %d on the old compiler's internals"
          % (kinds["port"], len(counts), kinds["ps2"], kinds["toolchain"]))
    print("%d g++ named return values, rewritten for the check; a port rewrites them: %s"
          % (len(run.named), ", ".join("%s:%d" % (f, l) for f, l, _ in run.named)))
    if args.baseline:
        write_baseline(counts)
        print("wrote %s" % BASELINE.relative_to(ROOT))
        return 0
    if args.check:
        base = read_baseline()
        worse = [(f, n, base.get(f, 0)) for f, n in sorted(counts.items()) if n > base.get(f, 0)]
        for f, n, b in worse:
            print("more port errors than the baseline: %s %d (was %d)" % (f, n, b))
        return 1 if worse else 0
    shown = [e for e in errors if e[3] == "port"]
    for unit, f, line, _, msg in shown if args.all else shown[:40]:
        print("%s:%d: %s" % (f, line, msg))
    return 0


if __name__ == "__main__":
    sys.exit(main())
