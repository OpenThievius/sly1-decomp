# SPDX-License-Identifier: AGPL-3.0-or-later
"""Find your disc images and put each version's boot executable in baserom/.

    python3 tools/setup.py                    # every image in baserom/
    python3 tools/setup.py PATH [PATH ...]    # these images, or every image in these folders

Each image is recognised by the executable its SYSTEM.CNF boots and that
executable's SHA-1 (config/versions.json), so file names do not matter. The
executable is written to baserom/<version>/<name>, which git ignores. A file
already there is checked, never overwritten. A reference disc (the May 2002
prototype) is recognised and reported, and nothing is extracted from it.
"""

import argparse
import hashlib
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import disc  # noqa: E402
import versions  # noqa: E402

IMAGE_SUFFIXES = {".iso", ".img", ".bin"}


def candidates(paths):
    for p in paths:
        p = Path(p)
        if p.is_dir():
            yield from sorted(c for c in p.iterdir() if c.suffix.lower() in IMAGE_SUFFIXES and c.is_file())
            for sub in sorted(c for c in p.iterdir() if c.is_dir() and c.name not in versions.versions()):
                yield from sorted(c for c in sub.iterdir() if c.suffix.lower() in IMAGE_SUFFIXES and c.is_file())
        elif p.is_file():
            yield p
        else:
            print("skip: %s does not exist" % p, file=sys.stderr)


def setup_image(image):
    try:
        with disc.Disc(str(image)) as d:
            name = d.boot_name()
            data = d.read_file(name)
    except disc.DiscError as e:
        print("skip: %s" % e)
        return None
    sha1 = hashlib.sha1(data).hexdigest()
    key = versions.identify_boot(name, sha1)
    if key is None:
        print("unknown: %s boots %s (sha1 %s), which no version in config/versions.json has" % (image, name, sha1))
        return None
    if versions.get(key)["role"] == "reference":
        print("skip: %-6s %s: a reference disc; nothing is taken from it (docs/PROTOTYPE.md)" % (key, image.name))
        return None
    out = versions.boot_path(key)
    if out.exists():
        have = hashlib.sha1(out.read_bytes()).hexdigest()
        if have != sha1:
            print("error: %s exists with sha1 %s, not %s; move it away and run again" % (out, have, sha1))
            return None
        print("ok:   %-6s %s (already in place)" % (key, out.relative_to(versions.ROOT)))
        return key
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_bytes(data)
    print("ok:   %-6s %s from %s" % (key, out.relative_to(versions.ROOT), image.name))
    return key


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("paths", nargs="*", default=[str(versions.BASEROM)])
    args = parser.parse_args(argv)

    found = {k for k in (setup_image(i) for i in candidates(args.paths)) if k}
    for key, v in versions.versions().items():
        if v["role"] != "reference" and key not in found and not versions.boot_path(key).exists():
            print("missing: %-6s %s (%s)" % (key, v["serial"], v["role"]))
    if versions.primary() in found or versions.boot_path(versions.primary()).exists():
        print("next: python3 tools/setup_asm.py --version %s" % versions.primary())
        return 0
    return 1


if __name__ == "__main__":
    sys.exit(main())
