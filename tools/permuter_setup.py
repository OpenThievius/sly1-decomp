# SPDX-License-Identifier: AGPL-3.0-or-later
"""Set up a near miss for decomp-permuter, against this project's own compiler.

    python3 tools/permuter_setup.py FILE FUNC          # writes build/permuter/FUNC/
    python3 tools/permuter_compile.py ...              # what that folder's compile.sh runs

decomp-permuter (https://github.com/simonlindholm/decomp-permuter, MIT) randomly rewrites one C
function -- statement order, temporaries, types, branch shape -- and keeps whatever compiles
closer to a target object. It is the tool for a register-allocation or scheduling tie that no
hand rewrite moves. It is never committed: fetch it into tools/ext/ (gitignored) as
docs/AGENT_WORKFLOW.md says, with its own Python environment there.

The folder this writes is what the permuter reads:

- target.o: retail's function, assembled from splat's listing (asm/us/text.s) with the build's
  assembler and flags, so its relocations look like a compiled object's;
- base.c: FILE preprocessed by the toolchain's cpp, with a `typedef struct X X;` for each struct
  it names, so that the permuter's C parser reads our C++ (wrap anything else C++ in
  PERM_IGNORE(...));
- compile.sh: compiles a candidate through tools/compile.py with the compiler and flags of the
  src/ file that holds FUNC (Sony's for the library), as tools/check.py does;
- settings.toml: the function's name and compiler type.

A score of 0 from the permuter is a lead, not a match: copy the candidate back and run
tools/check.py; it counts once that prints EXACT in a build that matches. As OpenRAC wires it up
(rac1-decomp, docs/agents/PERMUTER.md; credited in THIRD_PARTY_NOTICES.md); the code is ours.
"""

import argparse
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
OUT = ROOT / "build" / "permuter"
STRUCT = re.compile(r"\b(struct|union)\s+([A-Za-z_]\w*)\s*[{;]")


def target(func, dest):
    """Assemble retail's listing of FUNC into dest/target.o."""
    import build
    import c_layout
    header, chunks = c_layout.split_text("us")
    if func not in chunks:
        raise SystemExit("%s is not in asm/us/text.s" % func)
    src = dest / "target.s"
    src.write_text("\n".join(header + chunks[func]) + "\n")
    subprocess.run([build.tool("as")] + build.AS_FLAGS + [str(src), "-o", str(dest / "target.o")], check=True)


def base(path, dest):
    """FILE preprocessed, with a typedef for each struct, as dest/base.c."""
    import compile as cc
    run, cpp, _cc1plus, _as = cc.tools()
    ii = dest / "base.ii"
    proc = subprocess.run(run + [str(cpp)] + cc.CPP_DEFINES + ["-P", str(Path(path).resolve().relative_to(ROOT)),
                                                             str(ii.relative_to(ROOT))],
                          cwd=ROOT, capture_output=True, text=True)
    if proc.returncode:
        raise SystemExit("cpp failed:\n" + proc.stderr)
    text = ii.read_text()
    tags = sorted({m.group(2) for m in STRUCT.finditer(text)})
    lines = ["typedef %s %s %s;" % (kind, tag, tag) for tag in tags
             for kind in [next(m.group(1) for m in STRUCT.finditer(text) if m.group(2) == tag)]]
    (dest / "base.c").write_text("\n".join(lines) + "\n" + text)
    ii.unlink()


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("file")
    parser.add_argument("func")
    args = parser.parse_args(argv)
    dest = OUT / args.func
    dest.mkdir(parents=True, exist_ok=True)
    target(args.func, dest)
    base(args.file, dest)
    compile_sh = dest / "compile.sh"
    compile_sh.write_text('#!/bin/sh\nexec "%s" "%s" %s "$@"\n' % (sys.executable, ROOT / "tools" / "permuter_compile.py",
                                                                  args.func))
    compile_sh.chmod(0o755)
    (dest / "settings.toml").write_text('func_name = "%s"\ncompiler_type = "gcc"\n' % args.func)
    print("wrote %s: target.o, base.c, compile.sh, settings.toml" % dest.relative_to(ROOT))
    print("run: tools/ext/venv/bin/python tools/ext/decomp-permuter/permuter.py -j6 %s" % dest.relative_to(ROOT))
    return 0


if __name__ == "__main__":
    sys.exit(main())
