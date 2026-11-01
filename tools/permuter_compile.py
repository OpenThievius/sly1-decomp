# SPDX-License-Identifier: AGPL-3.0-or-later
"""decomp-permuter's compiler: build one candidate as FUNC's own src/ file would be built.

    python3 tools/permuter_compile.py FUNC IN.c -o OUT.o

Called by the compile.sh that tools/permuter_setup.py writes. The candidate is copied under
build/permuter/ (the Windows tools get paths relative to the repository) and compiled by
tools/compile.py with the compiler and flags of the src/ file that holds FUNC.
"""

import os
import shutil
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
    return 0


if __name__ == "__main__":
    sys.exit(main())
