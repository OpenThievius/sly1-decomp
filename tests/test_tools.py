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
import classify_asm  # noqa: E402
import disc  # noqa: E402
import progress  # noqa: E402
import nonmatching  # noqa: E402
import permute  # noqa: E402
import todo  # noqa: E402
import c_layout  # noqa: E402
import check  # noqa: E402
import rodata  # noqa: E402
import version_src  # noqa: E402
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


class TranslationTest(unittest.TestCase):
    """How a US address reaches PAL's when the pairing does not name it."""

    def resolver(self, translation):
        r = check.Resolver.__new__(check.Resolver)
        r.functions, r.symbols, r.translation, r.paired = {}, {}, translation, None
        return r

    def test_an_address_below_the_executable_is_the_same(self):
        self.assertEqual(self.resolver({0x200000: 0x201000}).address("D_00000FA0"), 0xFA0)

    def test_a_byte_inside_a_paired_datum_keeps_its_offset(self):
        r = self.resolver({0x247AA8: 0x248FA8, 0x247AF0: 0x2490F0})
        self.assertEqual(r.address("D_00247AD0"), 0x248FD0)

    def test_an_offset_that_reaches_the_next_datum_is_refused(self):
        r = self.resolver({0x247AA8: 0x248FA8, 0x247AF0: 0x248FB0})
        self.assertIsNone(r.address("D_00247AD0"))


class VersionSourceTest(unittest.TestCase):
    """A version's own definition takes the shared one's place in the shared file's unit."""

    SHARED = (
        '#include "common.h"\n'
        "void func_00100010(s32* p);\n"
        "void func_00100010(s32* p)\n"
        "{\n"
        '    const char* s = "}"; /* } */\n'
        "    if (p) { *p = 1; }\n"
        "}\n"
        "s32 func_00100020(void) { return 2; }\n"
    )

    def test_the_definition_is_replaced_and_the_rest_kept(self):
        with tempfile.TemporaryDirectory() as tmp:
            shared, own = Path(tmp) / "shared.cpp", Path(tmp) / "func_00100010.cpp"
            shared.write_text(self.SHARED)
            own.write_text("void func_00100010(s32* p)\n{\n    *p = 3;\n}\n")
            text = version_src.unit_text(shared, {"func_00100010": own})
        self.assertIn("*p = 3;", text)
        self.assertNotIn("*p = 1;", text)
        self.assertIn("void func_00100010(s32* p);", text)
        self.assertIn("s32 func_00100020(void) { return 2; }", text)

    def test_a_function_only_the_version_has_is_added_at_the_end(self):
        with tempfile.TemporaryDirectory() as tmp:
            shared, own = Path(tmp) / "shared.cpp", Path(tmp) / "func_eu_00100030.cpp"
            shared.write_text(self.SHARED)
            own.write_text("void func_eu_00100030(void)\n{\n}\n")
            text = version_src.unit_text(shared, {"func_eu_00100030": own})
        self.assertTrue(text.startswith(self.SHARED.rstrip("\n")))
        self.assertTrue(text.rstrip().endswith("void func_eu_00100030(void)\n{\n}"))

    def test_a_version_file_names_its_version_and_shared_file(self):
        path = versions.ROOT / "src" / "versions" / "eu" / "main" / "00140000" / "func_00142F10.cpp"
        self.assertEqual(version_src.version_of(path),
                         ("eu", versions.ROOT / "src" / "main" / "00140000.cpp"))
        self.assertIsNone(version_src.version_of(versions.ROOT / "src" / "main" / "00140000.cpp"))

    def test_the_shared_sources_leave_the_versions_out(self):
        self.assertFalse(any("versions" in p.parts for p in versions.sources()))

    def test_a_name_with_a_version_reaches_that_version_alone(self):
        r = check.Resolver.__new__(check.Resolver)
        r.functions, r.symbols, r.translation, r.paired, r.key = {}, {}, {}, None, "eu"
        self.assertEqual(r.address("func_eu_001387C8"), 0x1387C8)
        r.key = "us"
        self.assertIsNone(r.address("func_eu_001387C8"))


class BlockerTest(unittest.TestCase):
    def test_permanent_blockers_come_first(self):
        self.assertEqual(todo.blocker({"vu", "rodata", "jtbl"}), "vu")
        self.assertEqual(todo.blocker({"system", "rodata"}), "system")
        self.assertEqual(todo.blocker({"handwritten", "jtbl"}), "handwritten")

    def test_jump_table_then_rodata_then_none(self):
        self.assertEqual(todo.blocker({"jtbl", "rodata"}), "jtbl")
        self.assertEqual(todo.blocker({"data", "rodata", "float"}), "rodata")
        self.assertEqual(todo.blocker({"calls", "data"}), "none")


class ClassifyAsmTest(unittest.TestCase):
    RET = ["addiu $sp, $sp, -0x10", "jr $ra", "nop"]

    def classify(self, listings, refs=None):
        funcs = [(n, a, 4 * len(b), k) for n, a, k, b in listings]
        return {r[0]: (r[3], r[4]) for r in classify_asm.classify(funcs, {n: b for n, _a, _k, b in listings}, refs or {})}

    def test_a_vu0_instruction_makes_a_function_handwritten(self):
        got = self.classify([("f", 0x100000, "code", ["vaddx.xyzw $vf1, $vf2, $vf3", "jr $ra", "nop"])])
        self.assertEqual(got["f"][0], "handwritten")

    def test_a_multimedia_instruction_does_too_unless_the_compiler_emits_it(self):
        got = self.classify([("mmi", 0x100000, "code", ["pcpyld $v0, $a0, $a1", "jr $ra", "nop"]),
                             ("por", 0x100010, "code", ["por $v0, $a0, $a1", "jr $ra", "nop"])])
        self.assertIn("mmi", got)
        self.assertNotIn("por", got)

    def test_the_disassemblers_mark_counts(self):
        got = self.classify([("f", 0x100000, "handwritten", self.RET)])
        self.assertEqual(got["f"][0], "handwritten")

    def test_a_leftover_word_after_a_return_is_a_remnant(self):
        got = self.classify([("f", 0x100000, "code", self.RET), ("r", 0x100010, "code", ["addiu $sp, $sp, 0x10"])])
        self.assertEqual(got["r"][0], "remnant")
        self.assertNotIn("f", got)

    def test_a_remnant_needs_its_conditions(self):
        base = ("f", 0x100000, "code", self.RET)
        frag = ["addiu $sp, $sp, 0x10"]
        self.assertNotIn("r", self.classify([base, ("r", 0x100014, "code", frag)]))               # not on 8 bytes
        self.assertNotIn("r", self.classify([base, ("r", 0x100010, "code", ["j func_00100000", "nop"])]))  # a jump
        self.assertNotIn("r", self.classify([base, ("r", 0x100010, "code", frag)], {"r": 1}))     # reached
        before = ("g", 0x100000, "code", ["jr $ra", "nop", "addiu $v0, $zero, 1"])                  # ends on code
        self.assertNotIn("r", self.classify([before, ("r", 0x100010, "code", frag)]))

    def test_the_chain_stays_finished_across_remnants(self):
        got = self.classify([("f", 0x100000, "code", self.RET), ("a", 0x100010, "code", ["addiu $sp, $sp, 0x10"]),
                             ("b", 0x100018, "code", ["addiu $sp, $sp, 0x20"])])
        self.assertEqual(sorted(n for n in got if got[n][0] == "remnant"), ["a", "b"])


class SystemEvidenceTest(unittest.TestCase):
    """The #18 rules: kernel and system instructions, and stores before the frame, as OpenRAC's."""

    def test_a_kernel_instruction_is_original_assembly(self):
        self.assertIn("syscall", classify_asm.handwritten(["addiu", "syscall", "jr", "nop"], "code"))
        self.assertIn("max.s", classify_asm.handwritten(["max.s", "jr", "nop"], "code"))

    def test_what_the_compiler_emits_is_not(self):
        self.assertIsNone(classify_asm.handwritten(["sqrt.s", "jr", "nop"], "code"))
        self.assertIsNone(classify_asm.handwritten(["div", "break", "mflo", "jr", "nop"], "code"))

    def test_stores_before_the_frame(self):
        lines = ["swc1 $f12, 0x0($a0)", "nop", "addiu $sp, $sp, -0x10", "sd $ra, 0x0($sp)", "jr $ra", "nop"]
        self.assertIn("frame", classify_asm.handwritten(classify_asm.ops_of(lines), "code", lines))
        normal = ["addiu $sp, $sp, -0x10", "sd $ra, 0x0($sp)", "nop", "sw $a0, 0x4($sp)", "jr $ra", "nop"]
        self.assertIsNone(classify_asm.handwritten(classify_asm.ops_of(normal), "code", normal))

    def test_the_divide_trap_and_sqrt_do_not_block(self):
        self.assertNotIn("system", todo.tags_of(["div $zero, $a0, $a1", "break 0, 7", "mflo $v0", "jr $ra"], "code"))
        self.assertIn("system", todo.tags_of(["break 1023, 1023", "jr $ra"], "code"))
        self.assertNotIn("nonc", todo.tags_of(["sqrt.s $f0, $f12", "jr $ra"], "code"))


class OriginalAsmTableTest(unittest.TestCase):
    """The committed config/us/original_asm.tsv, which CI reads without a disc."""

    def setUp(self):
        self.table = classify_asm.read_table()
        self.funcs = {n: (a, s) for n, a, s, _k in todo.functions()}

    def test_every_row_is_a_function(self):
        for name in self.table:
            self.assertIn(name, self.funcs, name)

    def test_the_kinds_are_known(self):
        self.assertLessEqual(set(self.table.values()), {"handwritten", "remnant"})

    def test_no_function_is_both_original_assembly_and_c(self):
        self.assertEqual(sorted(set(self.table) & todo.finished()), [])


class ProgressCountTest(unittest.TestCase):
    def test_original_assembly_counts_as_finished_but_not_as_exact_c(self):
        asm = progress.original_asm("us")
        self.assertTrue(asm)
        self.assertEqual(progress.finished("us"), progress.exact_c("us") | asm)
        self.assertEqual(progress.exact_c("us") & asm, set())

    def test_a_pal_function_follows_its_us_counterpart(self):
        pal = progress.original_asm("eu")
        self.assertTrue(pal)
        self.assertLessEqual(len(pal), len(progress.original_asm("us")))


class CompilerTagTest(unittest.TestCase):
    """`compiler` marks Sony's library code; config/cflags.tsv builds it with Sony's compiler."""

    def test_a_64_bit_save_in_the_prologue_is_tagged_and_does_not_block(self):
        lines = ["addiu $sp, $sp, -0x20", "sd $ra, 0x18($sp)", "sd $s0, 0x10($sp)", "jal func_00100000", "jr $ra"]
        self.assertIn("compiler", todo.tags_of(lines, "function"))
        self.assertEqual(todo.blocker(todo.tags_of(lines, "function")), "none")

    def test_an_sq_save_or_a_late_sd_is_not_the_compiler_blocker(self):
        self.assertNotIn("compiler", todo.tags_of(["addiu $sp, $sp, -0x10", "sq $ra, 0x0($sp)", "jr $ra"], "function"))
        late = ["nop"] * todo.PROLOGUE + ["sd $ra, 0x18($sp)"]
        self.assertNotIn("compiler", todo.tags_of(late, "function"))

    def test_its_other_tags_decide(self):
        self.assertEqual(todo.blocker({"compiler", "rodata", "jtbl"}), "jtbl")
        self.assertEqual(todo.blocker({"compiler", "vu"}), "vu")

    def test_the_library_files_name_sonys_compiler(self):
        import compile as cc
        for path in sorted((versions.ROOT / "src" / "lib").glob("*.cpp")):
            self.assertEqual(cc.row_for(path)[1], "2.9-ee-991111", path.name)
        self.assertEqual(cc.row_for(versions.ROOT / "src" / "main" / "00100000.cpp")[1], "2.95.3")


class NonmatchingTest(unittest.TestCase):
    """A near miss's verdict line, and the share of retail's bytes the report credits it with."""

    def verdict(self, line):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "func_00100000.cpp"
            path.write_text(nonmatching.SPDX + "\n" + line + "\nvoid func_00100000(void) {}\n")
            return nonmatching.verdict(path), nonmatching.share(path)

    def test_bytes_give_their_share(self):
        self.assertEqual(self.verdict("// BYTES 196/208 (94.2%), checked 2026-11-01"),
                         ((196, 208, "2026-11-01"), 100.0 * 196 / 208))

    def test_another_size_or_a_broken_file_gives_nothing(self):
        self.assertEqual(self.verdict("// SIZE 216/208, checked 2026-11-01")[1], 0.0)
        self.assertEqual(self.verdict("// BROKEN, checked 2026-11-01")[1], 0.0)

    def test_a_near_miss_stays_below_a_match(self):
        self.assertLess(self.verdict("// BYTES 208/208 (100.0%), checked 2026-11-01")[1], 100.0)

    def test_no_verdict_line(self):
        self.assertEqual(self.verdict("// some note"), (None, 0.0))

    def test_writing_a_verdict_replaces_the_old_one(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "func_00100000.cpp"
            path.write_text(nonmatching.SPDX + "\n// BYTES 1/8 (12.5%), checked 2026-10-01\n// note\n")
            nonmatching.write_verdict(path, "// BYTES 6/8 (75.0%), checked 2026-11-01")
            self.assertEqual(path.read_text().splitlines(),
                             [nonmatching.SPDX, "// BYTES 6/8 (75.0%), checked 2026-11-01", "// note"])


class PermuteTest(unittest.TestCase):
    LINES = ["void f(S* s)", "{", "    s->a = 1; /*P*/", "    s->b = 2; /*P*/", "    g(s);", "    s->c = 3;",
             "    s->d = 4;", "    if (s->a) {", "        return;", "    }", "}"]

    def test_marked_lines_form_runs(self):
        self.assertEqual(permute.groups(self.LINES, auto=False), [[2, 3]])

    def test_auto_takes_runs_of_simple_statements(self):
        self.assertEqual(permute.groups(self.LINES, auto=True), [[2, 3, 4, 5, 6]])

    def test_every_order_is_tried(self):
        got = {tuple(c[2:4]) for c in permute.orders(self.LINES, [[2, 3]])}
        self.assertEqual(got, {("    s->a = 1; /*P*/", "    s->b = 2; /*P*/"), ("    s->b = 2; /*P*/", "    s->a = 1; /*P*/")})


class StructReturnTest(unittest.TestCase):
    def test_struct_pointer_return_is_a_definition(self):
        text = "struct Node_2003F8 *func_002003F8(struct Node_2003F8 *self, s32 a1) {\n    return self;\n}\n"
        self.assertEqual([m.group(1) for m in todo.DEFINITION.finditer(text)], ["func_002003F8"])

    def test_struct_definitions_are_not(self):
        text = "struct Node_2003F8 {\n    s32 f0;\n};\nstruct Pad_1 *func_00100000(void);\n"
        self.assertEqual([m.group(1) for m in todo.DEFINITION.finditer(text)], [])


class DecodedListingTest(unittest.TestCase):
    def test_raw_sqrt_word_is_named(self):
        # sqrt.s $f0, $f0 is 0x46000004 (little-endian bytes 04 00 00 46 in the listing)
        self.assertEqual(todo.decoded("    /* 1 2 04000046 */  c1         0x4").split()[0], "sqrt.s")
        self.assertEqual(todo.decoded("    /* 1 2 00000046 */  c1         0x0").split()[0], "c1")

    def test_other_lines_are_unchanged(self):
        self.assertEqual(todo.decoded("    /* 1 2 00000000 */  nop"), "nop")


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


class AbsoluteAliasTest(unittest.TestCase):
    def test_short_names_get_their_eight_digit_spelling(self):
        text = "D_10 = 0x10;\nD_FA0 = 0xFA0;\nD_00000FD8 = 0xFD8;\nsomething_else = 0x20;\n"
        self.assertEqual(c_layout.absolute_aliases(text), {"D_00000010": "D_10", "D_00000FA0": "D_FA0"})


class CaseLabelTest(unittest.TestCase):
    def test_only_labels_inside_c_functions_are_provided(self):
        with tempfile.TemporaryDirectory() as d:
            data = Path(d) / "asm" / "us" / "data"
            data.mkdir(parents=True)
            (data / "rodata.s").write_text(".word .L00136628\n.word .L00200000\n")
            old = c_layout.ROOT
            c_layout.ROOT = Path(d)
            try:
                got = c_layout.case_labels([(0x1365F0, 0x58)])
            finally:
                c_layout.ROOT = old
        self.assertEqual(got, {".L00136628": 0x136628})


class RunAlignmentTest(unittest.TestCase):
    def test_a_run_needs_only_the_alignment_its_directives_ask_for(self):
        self.assertEqual(c_layout.run_alignment(["glabel a", "nop"]), 4)
        self.assertEqual(c_layout.run_alignment([".align 3", "glabel a", ".align 2", "nop"]), 8)
        self.assertEqual(c_layout.run_alignment(["  .align 4"]), 16)


def tiny_object(rtypes=(5, 6), text_words=(0x3C020000, 0x8C420000)):
    """A little-endian ELF32 object: one function in .text.func_X, a .rodata and its .rel.text."""
    import struct
    shstr = b"\0.text.func_X\0.rodata\0.rel.text.func_X\0.symtab\0.strtab\0.shstrtab\0"
    off = lambda name: shstr.index(b"\0" + name.encode() + b"\0") + 1
    strtab = b"\0func_X\0"
    text = b"".join(struct.pack("<I", w) for w in text_words)
    ro = b"\0\0\x80\x3f"
    sym = lambda name, value, size, info, shndx: struct.pack("<IIIBBH", name, value, size, info, 0, shndx)
    symtab = sym(0, 0, 0, 0, 0) + sym(0, 0, 0, 3, 2) + sym(1, 0, len(text), 2, 1)
    rels = b"".join(struct.pack("<II", 4 * n, (1 << 8) | r) for n, r in enumerate(rtypes))
    bodies = [text, ro, rels, symtab, strtab, shstr]
    base = 52
    offs, at = [], base
    for b in bodies:
        offs.append(at)
        at += len(b)
    at = (at + 3) & ~3
    shdrs = [struct.pack("<IIIIIIIIII", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)]
    spec = [(".text.func_X", 1, 6, 0, 0, 0), (".rodata", 1, 2, 0, 0, 0), (".rel.text.func_X", 9, 0, 0, 1, 3),
            (".symtab", 2, 0, 5, 0, 16), (".strtab", 3, 0, 0, 0, 0), (".shstrtab", 3, 0, 0, 0, 0)]
    # link for .rel is the symtab (section 4); info is the text (section 1); .symtab links the strtab (5)
    links = {3: 4, 4: 5}
    infos = {3: 1}
    for n, (name, typ, flags, _, _, entsize) in enumerate(spec):
        idx = n + 1
        shdrs.append(struct.pack("<IIIIIIIIII", off(name), typ, flags, 0, offs[n], len(bodies[n]),
                                 links.get(idx, 0), infos.get(idx, 0) if idx != 4 else 1, 4, entsize))
    header = bytearray(52)
    header[:16] = b"\x7fELF\x01\x01\x01" + bytes(9)
    struct.pack_into("<HHIIIIIHHHHHH", header, 16, 1, 8, 1, 0, 0, at, 0, 52, 0, 0, 40, len(shdrs), 6)
    return bytes(header) + b"".join(bodies) + bytes(at - base - sum(len(b) for b in bodies)) + b"".join(shdrs)


class RodataBakeTest(unittest.TestCase):
    class Image:
        def read_vaddr(self, addr, size):
            words = {0x100000: 0x3C020025, 0x100004: 0x8C42A124}   # lui v0,0x25 ; lw v0,-0x5edc(v0)
            return words[addr].to_bytes(4, "little")

    class Resolver:
        def us_address(self, name):
            return 0x100000 if name == "func_X" else None

    def test_the_immediates_become_retails_and_the_relocations_vanish(self):
        patched, names, baked = rodata.patch(tiny_object(), self.Image(), self.Resolver())
        self.assertEqual(names, [".rodata"])
        self.assertEqual(baked, 2)
        o = c_layout.elf.Elf(patched)
        text = o.section(".text.func_X")
        words = [int.from_bytes(patched[text["offset"] + i:text["offset"] + i + 4], "little") for i in (0, 4)]
        self.assertEqual(words, [0x3C020025, 0x8C42A124])
        self.assertEqual([r[1] for r in o.relocations(".text.func_X")], [0, 0])

    def test_a_rodata_relocation_that_is_not_hi_or_lo_is_refused(self):
        with self.assertRaises(rodata.RodataError):
            rodata.patch(tiny_object(rtypes=(5, 2)), self.Image(), self.Resolver())
