# SPDX-License-Identifier: AGPL-3.0-or-later
"""Find the compiler and the runner for it, and check that they work.

    python3 tools/toolchain.py           # report what is found and compile a test unit

The game is C++ built with Sony's GNU EE compiler 2.9-ee-991111b
(docs/TOOLCHAIN.md). Its Windows build is the `local/sce/ee/gcc` tree of the
public sce_ps2_sdk_24 mirror; the compiler is proprietary and never committed.

- SLY1_TOOLCHAIN, or the `toolchain` link in the repository root: the
  `ee/gcc` directory (it holds `lib/gcc-lib/ee/2.9-ee-991111/cc1plus.exe`).
- SLY1_RUNNER: what runs the Windows tools; else `wibo`, then `wine`, from PATH.
"""

import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

COMPILER_VERSION = "2.9-ee-991111"
EXPECTED_BANNER = "2.9-ee-991111b"
# Placeholder until the flags are qualified against retail (docs/TOOLCHAIN.md).
DEFAULT_FLAGS = ["-O2", "-G0"]

TEST_UNIT = "class Counter { public: int value; int Above(char limit); };\nint Counter::Above(char limit) { return value > limit; }\n"


def toolchain_dir():
    env = os.environ.get("SLY1_TOOLCHAIN")
    path = Path(env).expanduser() if env else versions.ROOT / "toolchain"
    return path if path.exists() else None


def cc1plus(root):
    for name in ("cc1plus.exe", "cc1plus"):
        p = root / "lib" / "gcc-lib" / "ee" / COMPILER_VERSION / name
        if p.exists():
            return p
    return None


def runner(tool):
    if tool is None or tool.suffix != ".exe":
        return []
    env = os.environ.get("SLY1_RUNNER")
    if env:
        return [env]
    for name in ("wibo", "wine"):
        found = shutil.which(name)
        if found:
            return [found]
    return None


def main():
    root = toolchain_dir()
    if root is None:
        print("toolchain: not found. Set SLY1_TOOLCHAIN to the ee/gcc directory of the sce_ps2_sdk_24")
        print("           mirror, or link it as ./toolchain (docs/TOOLCHAIN.md).")
        return 1
    tool = cc1plus(root)
    print("toolchain: %s" % root)
    if tool is None:
        print("cc1plus:   missing (expected lib/gcc-lib/ee/%s/cc1plus.exe)" % COMPILER_VERSION)
        return 1
    print("cc1plus:   %s" % tool)
    run = runner(tool)
    if run is None:
        print("runner:    none. Install wibo (github.com/decompals/wibo) or Wine, or set SLY1_RUNNER.")
        return 1
    print("runner:    %s" % (run[0] if run else "(native)"))

    with tempfile.TemporaryDirectory() as tmp:
        src, out = Path(tmp) / "test.cpp", Path(tmp) / "test.s"
        src.write_text(TEST_UNIT)
        proc = subprocess.run(run + [str(tool), "-version", "-quiet"] + DEFAULT_FLAGS + [str(src), "-o", str(out)],
                              capture_output=True, text=True)
        banner = (proc.stderr or proc.stdout).strip().splitlines()[:1]
        print("version:   %s" % (banner[0] if banner else "(none)"))
        if proc.returncode or not out.exists():
            print("error: the test unit did not compile:\n%s" % proc.stderr)
            return 1
        if EXPECTED_BANNER not in (banner[0] if banner else ""):
            print("warning: this is not %s, the compiler retail was built with" % EXPECTED_BANNER)
            return 1
    print("ok: the compiler runs and is %s" % EXPECTED_BANNER)
    return 0


if __name__ == "__main__":
    sys.exit(main())
