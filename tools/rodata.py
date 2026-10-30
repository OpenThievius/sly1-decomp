# SPDX-License-Identifier: AGPL-3.0-or-later
"""Make the C functions that read .rodata linkable.

    python3 tools/rodata.py OBJECT        # bakes one compiled object in place

The build puts each C function at its retail address and keeps retail's own data
from the disassembly. A function that loads a literal reads it through a
%hi/%lo pair aimed at the object's .rodata, which has no place in that image. For
each such pair this takes the immediates of retail's own instruction at the same
place in the function, writes them into the object's code, turns the relocation
into R_MIPS_NONE and removes the object's .rodata. It is the address the linker
would have given the literal had the object's .rodata been laid where retail's is.

Whether the literal is retail's is not decided here: tools/check.py compares the
bytes at the address retail's instruction forms, and tools/build.py prints MATCH
only when the whole image equals retail.

A relocation inside .rodata (a jump table) and any rodata relocation that is not a
%hi or %lo are refused.
"""

import shutil
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elf  # noqa: E402

R_MIPS_NONE = 0


class RodataError(Exception):
    pass


def _objcopy():
    import os
    tool = shutil.which(os.environ.get("MIPS_PREFIX", "mips-linux-gnu-") + "objcopy")
    if tool is None:
        raise RodataError("GNU objcopy for mips not found (MIPS_PREFIX, default mips-linux-gnu-)")
    return tool


def patch(data, image, resolver, label="object"):
    """(patched bytes, [rodata section names], relocations baked) for an object's bytes."""
    data = bytearray(data)
    obj = elf.Elf(bytes(data))
    rodata = {s["index"]: s["name"] for s in obj.sections if s["name"].startswith(".rodata") and s["size"]}
    if not rodata:
        return bytes(data), [], 0
    functions = {s["shndx"]: s for s in obj.symbols if s["type"] == elf.STT_FUNC and s["shndx"] in range(len(obj.sections))}
    baked = 0
    for rel in obj.sections:
        if rel["type"] != elf.SHT_REL:
            continue
        target = obj.sections[rel["info"]]
        if target["index"] in rodata:
            raise RodataError("%s has a relocation inside %s (a jump table?): not supported yet"
                              % (label, target["name"]))
        for i in range(rel["size"] // 8):
            at = rel["offset"] + i * 8
            offset, info = struct.unpack_from("<II", data, at)
            rsym, rtype = obj.symbols[info >> 8], info & 0xFF
            if rsym["shndx"] not in rodata:
                continue
            if rtype not in (elf.R_MIPS_HI16, elf.R_MIPS_LO16):
                raise RodataError("%s: relocation type %d against %s is not supported yet"
                                  % (label, rtype, rodata[rsym["shndx"]]))
            func = functions.get(target["index"])
            if func is None:
                raise RodataError("%s: %s refers to .rodata but holds no function" % (label, target["name"]))
            addr = resolver.us_address(func["name"])
            if addr is None:
                raise RodataError("%s: %s has no address" % (label, func["name"]))
            retail, = struct.unpack("<I", image.read_vaddr(addr + offset - func["value"], 4))
            word_at = target["offset"] + offset
            ours, = struct.unpack_from("<I", data, word_at)
            struct.pack_into("<I", data, word_at, (ours & 0xFFFF0000) | (retail & 0xFFFF))
            struct.pack_into("<II", data, at, offset, R_MIPS_NONE)
            baked += 1
    return bytes(data), list(rodata.values()), baked


def bake(path, image, resolver):
    """Rewrite the object at `path`; returns how many relocations were baked (0 if it has no .rodata)."""
    patched, names, baked = patch(Path(path).read_bytes(), image, resolver, str(path))
    if not names:
        return 0
    tmp = Path(str(path) + ".baking")
    tmp.write_bytes(patched)
    cmd = [_objcopy()] + ["--remove-section=%s" % name for name in names] + [str(tmp), str(path)]
    proc = subprocess.run(cmd, capture_output=True, text=True)
    tmp.unlink()
    if proc.returncode:
        raise RodataError("objcopy: " + (proc.stderr or proc.stdout).strip())
    return baked


def main(argv=None):
    import check
    args = (argv if argv is not None else sys.argv)[1:]
    if len(args) != 1:
        print(__doc__.split("\n\n")[0])
        return 2
    n = bake(args[0], check.retail_image("us"), check.Resolver("us"))
    print("baked %d relocation(s) in %s" % (n, args[0]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
