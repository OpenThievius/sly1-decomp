# SPDX-License-Identifier: AGPL-3.0-or-later
"""A small reader for little-endian ELF32 files: sections, symbols, REL relocations."""

import struct

SHT_SYMTAB = 2
SHT_REL = 9
SHT_NOBITS = 8
STT_FUNC = 2
STT_SECTION = 3
SHN_UNDEF = 0

R_MIPS_32 = 2
R_MIPS_26 = 4
R_MIPS_HI16 = 5
R_MIPS_LO16 = 6


class Elf:
    def __init__(self, data):
        if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 1:
            raise ValueError("not a little-endian ELF32 file")
        self.data = data
        shoff, = struct.unpack_from("<I", data, 0x20)
        shentsize, shnum, shstrndx = struct.unpack_from("<HHH", data, 0x2E)
        raw = [struct.unpack_from("<IIIIIIIIII", data, shoff + i * shentsize) for i in range(shnum)]
        names = raw[shstrndx][4]
        self.sections = []
        for i, (name, typ, flags, addr, off, size, link, info, align, entsize) in enumerate(raw):
            self.sections.append({"index": i, "name": self._str(names, name), "type": typ, "flags": flags,
                                  "addr": addr, "offset": off, "size": size, "link": link, "info": info})
        self.symbols = []
        for s in self.sections:
            if s["type"] == SHT_SYMTAB:
                strtab = self.sections[s["link"]]["offset"]
                for i in range(s["size"] // 16):
                    name, value, size, info, other, shndx = struct.unpack_from("<IIIBBH", data, s["offset"] + i * 16)
                    self.symbols.append({"name": self._str(strtab, name), "value": value, "size": size,
                                         "type": info & 15, "bind": info >> 4, "shndx": shndx})

    def _str(self, base, offset):
        end = self.data.index(b"\0", base + offset)
        return self.data[base + offset:end].decode("latin-1")

    def section(self, name):
        for s in self.sections:
            if s["name"] == name:
                return s
        return None

    def contents(self, section):
        if section["type"] == SHT_NOBITS:
            return bytes(section["size"])
        return self.data[section["offset"]:section["offset"] + section["size"]]

    def relocations(self, target_name):
        """[(offset, type, symbol)] of the REL section that applies to `target_name`."""
        target = self.section(target_name)
        out = []
        for s in self.sections:
            if s["type"] == SHT_REL and s["info"] == target["index"]:
                for i in range(s["size"] // 8):
                    offset, info = struct.unpack_from("<II", self.data, s["offset"] + i * 8)
                    out.append((offset, info & 0xFF, self.symbols[info >> 8]))
        return out

    def read_vaddr(self, addr, size):
        """Bytes of a loaded image at a virtual address (for a linked executable)."""
        for s in self.sections:
            if s["addr"] and s["addr"] <= addr and addr + size <= s["addr"] + s["size"] and s["type"] != SHT_NOBITS:
                start = s["offset"] + addr - s["addr"]
                return self.data[start:start + size]
        raise ValueError("no section holds 0x%X..0x%X" % (addr, addr + size))
