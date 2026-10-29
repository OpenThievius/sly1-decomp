# SPDX-License-Identifier: AGPL-3.0-or-later
"""Find game data and proprietary material in the files git would commit.

    python3 tools/proprietary.py            # scan this repository (tests/check_repository.py runs it)

What it rejects:

- binaries, disc images and their sidecar files, archives, objects, libraries,
  executables (by name, and by an ELF or PE header);
- anything in a folder that holds game data, generated assembly, build output
  or a toolchain;
- includes of Sony SDK headers, files named like them, and Sony SDK
  copyright or confidentiality banners;
- splat disassembly (its address comments), wherever it is pasted;
- runs of hex byte literals long enough to be a dump of retail data;
- files over 512 KiB.

This file is shared with OpenThievius (tools/proprietary.py there); keep the
two copies identical (OpenThievius's shared/files.json lists them).
"""

import re
import subprocess
import sys
from pathlib import Path

MAX_BYTES = 512 * 1024

BINARY_SUFFIXES = {
    # disc images and their sidecars
    ".iso", ".img", ".bin", ".cue", ".ccd", ".sub", ".mdf", ".mds", ".nrg", ".chd", ".cso",
    # executables, objects, libraries, PS2 modules
    ".elf", ".irx", ".erx", ".o", ".obj", ".a", ".lib", ".so", ".dylib", ".dll", ".exe",
    # the game's archives
    ".wal", ".wac",
    # archives of anything
    ".7z", ".zip", ".gz", ".tgz", ".xz", ".bz2", ".rar", ".tar", ".zst",
}

# Folders that only ever hold game data, generated assembly, build output or toolchains.
# A README.md directly inside one is allowed (baserom/README.md, toolchains/README.md).
DATA_DIRS = ("asm/", "assets/", "build/", "baserom/", "toolchain/", "toolchains/", "venv/", ".venv/")

# Headers of Sony's PS2 SDK. Their contents are proprietary: never include, copy or recreate them
# under these names. The project writes its own declarations from the retail code.
SDK_HEADERS = {
    "eekernel.h", "eeregs.h", "eestruct.h", "eetypes.h", "libcdvd.h", "libdev.h", "libdma.h",
    "libgifpk.h", "libgraph.h", "libipu.h", "libmc.h", "libmpeg.h", "libpad.h", "libpc.h",
    "libpkt.h", "libscf.h", "libsdr.h", "libssyn.h", "libvifpk.h", "libvu0.h", "libmtap.h",
    "libnet.h", "libspu2m.h", "libsd.h", "sif.h", "sifcmd.h", "sifdev.h", "sifrpc.h",
    "devfont.h", "devgif.h", "devvif0.h", "devvif1.h", "devvu0.h", "devvu1.h", "libusbkb.h",
}

INCLUDE = re.compile(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]', re.M)
# Written in pieces so that this file does not match itself.
BANNERS = [
    re.compile("Sony" + r"\s+Computer\s+Entertainment\s+Inc", re.I),
    re.compile("SCE" + r"\s+CONFIDENTIAL", re.I),
    re.compile("Copyright" + r"\s*\(C\)[^\n]{0,40}\bSCEI\b", re.I),
]
# splat's per-instruction comment: /* file offset, address, instruction word */
SPLAT_LINE = re.compile("/[*]" + r" [0-9A-F]{1,8} [0-9A-F]{8} [0-9A-F]{8} " + "[*]/")
HEX_BYTE = re.compile(r"\b0x[0-9A-Fa-f]{2}\b")


def tracked(root):
    """What git would commit: tracked files plus untracked ones that are not ignored."""
    out = subprocess.run(["git", "ls-files", "-z", "--cached", "--others", "--exclude-standard"],
                         cwd=root, capture_output=True)
    if out.returncode:
        raise SystemExit("error: %s is not a git checkout" % root)
    return sorted({p for p in out.stdout.decode().split("\0") if p})


def check_file(rel, data):
    """The problems with one file, given its path relative to the root and its bytes."""
    errors = []
    low = rel.lower()
    name = low.rsplit("/", 1)[-1]
    suffix = "." + name.rsplit(".", 1)[-1] if "." in name else ""

    if suffix in BINARY_SUFFIXES:
        errors.append("a %s file: binaries, disc images and game data are never committed" % suffix)
    for d in DATA_DIRS:
        if low.startswith(d) and low != d + "readme.md":
            errors.append("in %s, which holds game data, generated files or a toolchain" % d.rstrip("/"))
    if data[:4] == b"\x7fELF":
        errors.append("an ELF file")
    if data[:2] == b"MZ" and b"PE\0\0" in data[:1024]:
        errors.append("a Windows executable")
    if len(data) > MAX_BYTES:
        errors.append("%d bytes; files over %d bytes are not committed" % (len(data), MAX_BYTES))
    if name in SDK_HEADERS:
        errors.append("named like a Sony SDK header")
    if b"\0" in data[:8192]:
        return errors  # binary: the text checks below do not apply

    text = data.decode("utf-8", "replace")
    for m in INCLUDE.finditer(text):
        if m.group(1).replace("\\", "/").rsplit("/", 1)[-1].lower() in SDK_HEADERS:
            errors.append("includes the Sony SDK header %s" % m.group(1))
    for pattern in BANNERS:
        if pattern.search(text):
            errors.append("carries a Sony SDK copyright or confidentiality banner")
    if SPLAT_LINE.search(text):
        errors.append("contains disassembly of the retail code (splat's address comments)")
    dense = sum(1 for line in text.splitlines() if len(HEX_BYTE.findall(line)) >= 16)
    if dense >= 8:
        errors.append("contains %d lines of hex byte literals: a dump of retail data?" % dense)
    return errors


def scan(root):
    root = Path(root)
    problems = []
    for rel in tracked(root):
        path = root / rel
        if path.is_file() and not path.is_symlink():
            problems += ["%s: %s" % (rel, e) for e in check_file(rel, path.read_bytes())]
        elif path.is_symlink():
            problems.append("%s: a symbolic link (toolchain and disc links stay out of git)" % rel)
    return problems


def main():
    root = Path(__file__).resolve().parent.parent
    problems = scan(root)
    for p in problems:
        print("error: " + p)
    print("%s: %d problem(s)" % ("FAIL" if problems else "ok", len(problems)))
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
