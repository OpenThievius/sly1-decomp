# SPDX-License-Identifier: AGPL-3.0-or-later
"""Unit tests for the tools. They need no disc and no compiler."""

import hashlib
import os
import struct
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import disc  # noqa: E402
import todo  # noqa: E402
import versions  # noqa: E402

BOOT = b"\x7fELF" + bytes(range(256)) * 20


def record(name, lba, size, is_dir=False):
    ident = name.encode() if is_dir else (name + ";1").encode()
    if name in ("\x00", "\x01"):
        ident = name.encode()
    length = 33 + len(ident) + (len(ident) + 1) % 2
    rec = bytearray(length)
    rec[0] = length
    struct.pack_into("<I", rec, 2, lba)
    struct.pack_into(">I", rec, 6, lba)
    struct.pack_into("<I", rec, 10, size)
    struct.pack_into(">I", rec, 14, size)
    rec[25] = 2 if is_dir else 0
    rec[32] = len(ident)
    rec[33:33 + len(ident)] = ident
    return bytes(rec)


def make_iso(files):
    """A minimal ISO 9660 image: a root directory holding `files` ({name: bytes})."""
    sectors = {}
    lba = 19
    entries = [record("\x00", 18, 2048, True), record("\x01", 18, 2048, True)]
    for name, data in files.items():
        entries.append(record(name, lba, len(data)))
        for i in range(0, max(len(data), 1), 2048):
            sectors[lba] = data[i:i + 2048].ljust(2048, b"\0")
            lba += 1
    sectors[18] = b"".join(entries).ljust(2048, b"\0")
    pvd = bytearray(2048)
    pvd[0:6] = b"\x01CD001"
    pvd[40:72] = b"TEST".ljust(32)
    pvd[156:190] = record("\x00", 18, 2048, True)
    sectors[16] = bytes(pvd)
    sectors[17] = b"\xffCD001".ljust(2048, b"\0")
    return [sectors.get(i, bytes(2048)) for i in range(lba)]


def to_raw(sectors):
    out = []
    for user in sectors:
        header = disc.SYNC + b"\0\0\0\x02" + b"\0\0\x08\0\0\0\x08\0"
        out.append(header + user + bytes(disc.RAW_SECTOR - 24 - 2048))
    return b"".join(out)


class DiscTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.files = {"SYSTEM.CNF": b"BOOT2=cdrom0:\\SLUS_000.00;1\r\nVER=1.00\r\nVMODE=NTSC\r\n",
                      "SLUS_000.00": BOOT}

    def tearDown(self):
        self.tmp.cleanup()

    def write(self, name, data):
        path = os.path.join(self.tmp.name, name)
        with open(path, "wb") as f:
            f.write(data)
        return path

    def check(self, path, raw):
        with disc.Disc(path) as d:
            self.assertEqual(d.raw, raw)
            self.assertEqual(d.volume_id, "TEST")
            self.assertEqual(d.boot_name(), "SLUS_000.00")
            self.assertEqual([e["name"] for e in d.listdir()], ["SYSTEM.CNF", "SLUS_000.00"])
            self.assertEqual(d.read_file("slus_000.00"), BOOT)
            with self.assertRaises(disc.DiscError):
                d.find("MISSING.BIN")

    def test_iso(self):
        self.check(self.write("t.iso", b"".join(make_iso(self.files))), raw=False)

    def test_raw_mode2(self):
        self.check(self.write("t.img", to_raw(make_iso(self.files))), raw=True)

    def test_not_a_disc(self):
        with self.assertRaises(disc.DiscError):
            disc.Disc(self.write("x.iso", bytes(2048 * 20)))

    def test_checksums(self):
        c = disc.checksums(b"abc")
        self.assertEqual(c["sha1"], hashlib.sha1(b"abc").hexdigest())
        self.assertEqual(c["crc32"], "352441c2")
        self.assertEqual(c["size"], 3)


class VersionsTest(unittest.TestCase):
    def test_table(self):
        table = versions.versions()
        self.assertIn(versions.primary(), table)
        for key, v in table.items():
            for field in ("title", "region", "serial", "role", "boot", "disc"):
                self.assertIn(field, v, key)
            self.assertIn(v["role"], ("primary", "secondary", "reference"))
            self.assertRegex(v["boot"]["sha1"], "^[0-9a-f]{40}$")
            self.assertEqual(versions.identify_boot(v["boot"]["name"], v["boot"]["sha1"]), key)
        self.assertEqual(table[versions.primary()]["role"], "primary")
        self.assertIsNone(versions.identify_boot("SCUS_971.98", "0" * 40))

    def test_splat_configs_name_their_version(self):
        for key, v in versions.versions().items():
            path = versions.splat_config(key)
            if path.exists():
                text = path.read_text()
                self.assertIn("sha1: %s" % v["boot"]["sha1"], text, path)
                self.assertIn("baserom/%s/%s" % (key, v["boot"]["name"]), text, path)


if __name__ == "__main__":
    unittest.main()


class ProprietaryTest(unittest.TestCase):
    def setUp(self):
        sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
        import proprietary
        self.check = proprietary.check_file

    def test_clean_source_passes(self):
        src = b"// SPDX-License-Identifier: AGPL-3.0-or-later\n#include \"common.h\"\nint Add(int a, int b) { return a + b; }\n"
        self.assertEqual(self.check("src/add.cpp", src), [])
        self.assertEqual(self.check("baserom/README.md", b"# discs\n"), [])
        self.assertEqual(self.check("toolchains/README.md", b"# compilers\n"), [])

    def test_binaries_and_data_dirs(self):
        self.assertTrue(self.check("SCUS_971.98.iso", b"x"))
        self.assertTrue(self.check("dump/disc.cue", b"FILE"))
        self.assertTrue(self.check("tools/cc1plus.exe", b"x"))
        self.assertTrue(self.check("asm/us/text.s", b"x"))
        self.assertTrue(self.check("baserom/us/notes.txt", b"x"))
        self.assertTrue(self.check("toolchains/gcc/README.md", b"x"))
        self.assertTrue(self.check("SCUS_971.98", b"\x7fELF" + bytes(60)))
        self.assertTrue(self.check("big.json", b"{}" + b" " * (600 * 1024)))

    def test_sdk_material(self):
        self.assertTrue(self.check("src/gs.cpp", b"#include <eekernel.h>\n"))
        self.assertTrue(self.check("src/gs.cpp", b'#include "sdk/libgraph.h"\n'))
        self.assertTrue(self.check("include/sifrpc.h", b"int x;\n"))
        self.assertTrue(self.check("src/x.c", b"/* Copyright (C) 2001 Sony " + b"Computer Entertainment Inc. */\n"))
        self.assertTrue(self.check("src/x.c", b"/* SCE " + b"CONFIDENTIAL */\n"))

    def test_retail_dumps(self):
        asm = b"glabel func_00100008\n    /* 1008 00100008 27BDFFF0 " + b"*/  addiu $sp, $sp, -0x10\n"
        self.assertTrue(self.check("notes/func.md", asm))
        line = b", ".join(b"0x%02X" % i for i in range(16)) + b"\n"
        self.assertTrue(self.check("src/table.c", line * 8))
        self.assertEqual(self.check("src/table.c", line * 7), [])


class BlockerTest(unittest.TestCase):
    def test_permanent_blockers_come_first(self):
        self.assertEqual(todo.blocker({"vu", "rodata", "jtbl"}), "vu")
        self.assertEqual(todo.blocker({"system", "rodata"}), "system")
        self.assertEqual(todo.blocker({"handwritten", "jtbl"}), "handwritten")

    def test_jump_table_then_rodata_then_none(self):
        self.assertEqual(todo.blocker({"jtbl", "rodata"}), "jtbl")
        self.assertEqual(todo.blocker({"data", "rodata", "float"}), "rodata")
        self.assertEqual(todo.blocker({"calls", "data"}), "none")


class DefinitionTest(unittest.TestCase):
    def names(self, text):
        return [m.group(1) for m in todo.DEFINITION.finditer(text)]

    def test_definitions_and_declarations(self):
        text = ("s32 func_00100008(void* a, s32 b);\n"
                "void func_00100010(void) {}\n"
                "\n"
                "s32 func_00100018(u8* bits, s32 index)\n"
                "{\n"
                "    s32 mask = 1 << (index & 7);\n"
                "    return bits[index / 8] & mask;\n"
                "}\n"
                "struct __attribute__((aligned(16))) Quad_100018 {\n"
                "    s32 a, b, c, d;\n"
                "};\n"
                "u32 func_0010001C(u32 i) { if (i >= 10) return 0; return i; }\n"
                "void* func_00100020(void* self,\n"
                "                    s32 n)\n"
                "{\n"
                "    return self;\n"
                "}\n")
        # A one-line definition does not swallow the one after it, and a struct
        # with an attribute in front of its name is not a function; a one-line
        # definition with statements in its body is one.
        self.assertEqual(self.names(text), ["func_00100010", "func_00100018", "func_0010001C", "func_00100020"])
