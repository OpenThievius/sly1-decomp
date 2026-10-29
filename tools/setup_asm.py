# SPDX-License-Identifier: AGPL-3.0-or-later
"""Generate asm/<version>/ from your boot executable with splat.

    python3 tools/setup_asm.py [--version us]

Needs tools/requirements.txt installed and tools/setup.py run first. asm/ and
build/ are generated from game data, so git ignores them.
"""

import argparse
import hashlib
import shutil
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--version", default=versions.primary(), choices=sorted(versions.versions()))
    parser.add_argument("--clean", action="store_true", help="remove asm/<version>/ first")
    args = parser.parse_args(argv)

    v = versions.get(args.version)
    boot = versions.boot_path(args.version)
    config = versions.splat_config(args.version)
    if not config.exists():
        print("error: %s has no splat configuration yet (%s)" % (args.version, config.relative_to(versions.ROOT)))
        return 1
    if not boot.exists():
        print("error: %s is missing; run python3 tools/setup.py first" % boot.relative_to(versions.ROOT))
        return 1
    if hashlib.sha1(boot.read_bytes()).hexdigest() != v["boot"]["sha1"]:
        print("error: %s is not the retail %s" % (boot.relative_to(versions.ROOT), v["serial"]))
        return 1

    asm = versions.ROOT / "asm" / args.version
    if args.clean and asm.exists():
        shutil.rmtree(asm)
    (versions.ROOT / "build" / args.version).mkdir(parents=True, exist_ok=True)
    return subprocess.call([sys.executable, "-m", "splat", "split", str(config)], cwd=versions.ROOT)


if __name__ == "__main__":
    sys.exit(main())
