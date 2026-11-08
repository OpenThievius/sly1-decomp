# SPDX-License-Identifier: AGPL-3.0-or-later
"""decomp-permuter's compiler: build one candidate as FUNC's own src/ file would be built.

    python3 tools/permuter_compile.py FUNC IN.c -o OUT.o

Called by the compile.sh that tools/permuter_setup.py writes. The candidate is copied under
build/permuter/ (the Windows tools get paths relative to the repository) and compiled by
tools/compile.py with the compiler and flags of the src/ file that holds FUNC.
"""

import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    if len(argv) != 4 or argv[2] != "-o":
        print("usage: permuter_compile.py FUNC IN.c -o OUT.o", file=sys.stderr)
        return 2
    func, src, _, out = argv
    import check
    import compile as cc
    work = ROOT / "build" / "permuter" / "cc"
    work.mkdir(parents=True, exist_ok=True)
    copy = work / ("%s_%d.cpp" % (func, os.getpid()))
    copy.write_text(with_aliases(only_definition(Path(src).read_text(), func)))
    try:
        cc.compile_file(copy, out, source=check.source_for(copy, func))
    except cc.CompileError as e:
        print(e, file=sys.stderr)
        return 1
    finally:
        copy.unlink()
    only_function(out, func)
    plain_names(out)
    return 0


ALIAS = re.compile(r'static const char permuter_alias_\d+\[\] = "(\w+)=([^"]+)";')


TYPEDEF = re.compile(r'static const char permuter_typedef_(\w+)\[\] = "((?:[^"\\\\]|\\\\.)*)";')


def with_aliases(text):
    """The candidate with permuter_setup.py's call aliases as #defines again (Fpu__Sqrt -> Fpu::Sqrt),
    and each attributed typedef (u128's mode(TI)) as it was written."""
    for m in list(TYPEDEF.finditer(text)):
        name, original = m.group(1), m.group(2).replace('\\"', '"')
        text = re.sub(r"\btypedef\b[^;]*\b%s\s*;" % re.escape(name), lambda _: original, text, count=1)
    text = TYPEDEF.sub("", text)
    defines = ["#define %s %s" % m.groups() for m in ALIAS.finditer(text)]
    return "\n".join(defines) + "\n" + ALIAS.sub("", text) if defines else text


def only_definition(text, func):
    """The candidate with every other function definition cut down to its declaration: a near miss
    holds its whole unit, and the permuter scores all the code in the object against retail's one
    function. Inline helpers, which have readable names, keep their bodies."""
    import symbols
    import todo
    import version_src
    func = symbols.canonical(func)
    spans = []
    for m in todo.definitions(text):
        name = m.group(1)
        if name == func or not name.startswith("func_") or text[:m.start(1)].endswith("::"):
            continue        # FUNC itself, or a class's method, which only its class may declare
        try:
            start, end = version_src.definition_span(text[m.start():], name)
        except version_src.VersionSourceError:
            continue
        brace = text.find("{", m.start())
        spans.append((brace, m.start() + end))
    for a, b in sorted(spans, reverse=True):
        text = text[:a] + ";" + text[b:]
    # A whole file's assembly functions (include/asm_func.h) are code the object would hold too.
    return re.sub(r'^__asm__\("\.section \.text\\n.*$', "", text, flags=re.M)


def only_function(obj_path, func):
    """Drop the other code left in the object: a class's methods, which keep their bodies, and what
    the compiler generates for the unit (a static initialiser and its constructor list)."""
    import check
    import elf
    obj = elf.Elf(Path(obj_path).read_bytes())
    other = [s["name"] for s in obj.sections if s["name"].startswith((".text.", ".rel.text."))
             and check.base_name(s["name"].split(".text.", 1)[1]) != func]
    generated = [s["name"] for s in obj.sections if s["name"] in (".ctors", ".rel.ctors")]
    objcopy = shutil.which(os.environ.get("MIPS_PREFIX", "mips-linux-gnu-") + "objcopy")
    for drop in (other + generated, generated):
        if not drop:
            continue
        r = subprocess.run([objcopy] + ["--remove-section=%s" % n for n in drop] + [str(obj_path)],
                           capture_output=True)
        if r.returncode == 0:
            return


def plain_names(obj_path):
    """Rename each C++ mangled symbol to its plain name (func_X__FPv -> func_X), as retail's target.o
    has them: otherwise the permuter counts every label and call as a difference and never reaches 0."""
    import check
    import elf
    obj = elf.Elf(Path(obj_path).read_bytes())
    uses = {}
    for sec in obj.sections:
        if sec["name"].startswith(".text") and sec["size"]:
            for _off, _type, sym in obj.relocations(sec["name"]):
                uses[sym["name"]] = uses.get(sym["name"], 0) + 1
    # A unit that declares a function twice with other arguments has two mangled names for it, and
    # objcopy renames only one symbol to each name: take the one the code refers to most.
    best = {}
    for s in obj.symbols:
        name = s["name"]
        if name and check.base_name(name) != name:
            plain = check.base_name(name)
            if plain not in best or uses.get(name, 0) > uses.get(best[plain], 0):
                best[plain] = name
    renames = sorted((old, new) for new, old in best.items())
    if not renames:
        return
    args = [a for old, new in renames for a in ("--redefine-sym", "%s=%s" % (old, new))]
    objcopy = shutil.which(os.environ.get("MIPS_PREFIX", "mips-linux-gnu-") + "objcopy")
    subprocess.run([objcopy] + args + [str(obj_path)], check=True)


if __name__ == "__main__":
    sys.exit(main())
