# SPDX-License-Identifier: AGPL-3.0-or-later
"""decomp-permuter's compiler: build one candidate as FUNC's own src/ file would be built.

    python3 tools/permuter_compile.py FUNC IN.c -o OUT.o

Called by the compile.sh that tools/permuter_setup.py writes. The candidate is copied under
build/permuter/ (the Windows tools get paths relative to the repository) and compiled by
tools/compile.py with the compiler and flags of the src/ file that holds FUNC.
"""

import os
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
    shutil.copyfile(src, copy)
    try:
        cc.compile_file(copy, out, source=check.source_for(copy, func))
    except cc.CompileError as e:
        print(e, file=sys.stderr)
        return 1
    finally:
        copy.unlink()
    plain_names(out)
    return 0


def plain_names(obj_path):
    """Rename each C++ mangled symbol to its plain name (func_X__FPv -> func_X), as retail's target.o
    has them: otherwise the permuter counts every label and call as a difference and never reaches 0."""
    import check
    import elf
    obj = elf.Elf(Path(obj_path).read_bytes())
    renames = sorted({(s["name"], check.base_name(s["name"])) for s in obj.symbols
                      if s["name"] and check.base_name(s["name"]) != s["name"]})
    if not renames:
        return
    args = [a for old, new in renames for a in ("--redefine-sym", "%s=%s" % (old, new))]
    objcopy = shutil.which(os.environ.get("MIPS_PREFIX", "mips-linux-gnu-") + "objcopy")
    subprocess.run([objcopy] + args + [str(obj_path)], check=True)


if __name__ == "__main__":
    sys.exit(main())
