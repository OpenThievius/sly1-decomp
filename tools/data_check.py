# SPDX-License-Identifier: AGPL-3.0-or-later
"""Check every global C defines at its PAL counterpart.

    python3 tools/data_check.py [--check]

tools/version_check.py calls this (this file also runs on its own). For each
global of config/us/c_data.tsv the source file is compiled as the US build
compiles it, the global's bytes are taken from the object's section (every
relocation in it resolved to the PAL address of its target, as tools/check.py
resolves code relocations), and they are compared with PAL's retail bytes at
the global's PAL address. The address is the translation of the US one
(tools/check.py: Resolver.translate): paired directly, or the nearest paired
address below it plus the same offset when that stays short of the next one.
Nothing is masked and nothing is guessed: a global counts only when every byte
equals PAL's.

The results go to config/eu/c_data_status.tsv, one row per US global:
`match`, `differs` (PAL's bytes are not what this C builds) or `absent` (the
global has no place or no bytes in PAL: its address does not translate, or it
is .bss, which no file holds). tools/progress.py counts PAL's data from the
`match` rows. The table holds addresses, sizes and statuses only.

--check needs no toolchain: it fails when a global of config/us/c_data.tsv has
no row, or a row names one it no longer lists.
"""

import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
STATUS = ROOT / "config" / "eu" / "c_data_status.tsv"
HEADER = "us_name\teu_address\tsize\tstatus\tnote"
WHOLE_KINDS = {".rodata": "rodata", ".data": "data", ".bss": "bss", ".gcc_except_table": "except"}


def us_globals():
    """[(name, us address, size, section, source)] of config/us/c_data.tsv."""
    path = ROOT / "config" / "us" / "c_data.tsv"
    out = []
    for line in path.read_text().splitlines()[1:]:
        if line:
            name, addr, size, section, source = line.split("\t")
            out.append((name, int(addr, 16), int(size), section, source))
    return out


def read_status():
    rows = {}
    if STATUS.exists():
        for line in STATUS.read_text().splitlines()[1:]:
            name, addr, size, status, note = (line.split("\t") + [""] * 5)[:5]
            rows[name] = (addr, int(size), status, note)
    return rows


def section_target(obj, resolver, whole, rsym, addend):
    """The version's address a relocation of a data section reaches, or None.

    rsym: the relocation's symbol; addend: the word's own value. A section symbol of a whole file
    (-fno-data-sections) is the file's section at its US address (config/us/files.tsv); one of a
    file built with -fdata-sections is the global or function that section holds.
    """
    import elf
    if rsym["type"] == elf.STT_SECTION and rsym["shndx"] < len(obj.sections):
        sec = obj.sections[rsym["shndx"]]
        secname = sec["name"]
        if secname.startswith((".text.", ".data.", ".rodata.")):
            base = resolver.address(secname.split(".", 2)[2])
            return None if base is None else base + addend
        if secname in WHOLE_KINDS and whole and whole.get(WHOLE_KINDS[secname]) is not None:
            return resolver.translate(whole[WHOLE_KINDS[secname]] + addend)
        if secname == ".text":
            named = [s for s in obj.symbols if s["shndx"] == sec["index"] and s["name"]
                     and s["value"] <= addend and resolver.address(s["name"]) is not None]
            if named:
                near = max(named, key=lambda s: s["value"])
                return resolver.address(near["name"]) + addend - near["value"]
        return None
    t = resolver.address(rsym["name"])
    if t is not None:
        return t + addend
    if rsym["shndx"] not in (elf.SHN_UNDEF,) and rsym["shndx"] < len(obj.sections):
        # A symbol the object defines in one of its whole file's data sections.
        kind = WHOLE_KINDS.get(obj.sections[rsym["shndx"]]["name"])
        if kind and whole and whole.get(kind) is not None:
            return resolver.translate(whole[kind] + rsym["value"] + addend)
    return None


def section_bytes(obj, secname, resolver, whole):
    """(bytes, note): the section's contents with every relocated word resolved to the version's
    address, or (None, why)."""
    import elf
    sec = obj.section(secname)
    if sec is None:
        return None, "the object has no %s" % secname
    data = bytearray(obj.contents(sec))
    for offset, rtype, rsym in obj.relocations(secname):
        if rtype != elf.R_MIPS_32:
            return None, "relocation type %d in the data is not supported" % rtype
        addend = int.from_bytes(data[offset:offset + 4], "little")
        t = section_target(obj, resolver, whole, rsym, addend)
        if t is None:
            return None, "a pointer to %s, which has no address in PAL" % (rsym["name"] or obj.sections[rsym["shndx"]]["name"])
        data[offset:offset + 4] = (t & 0xFFFFFFFF).to_bytes(4, "little")
    return bytes(data), ""


def check_global(obj, row, resolver, image, whole):
    """(eu address or None, status, note) of one row of c_data.tsv, `obj` being its source's object."""
    name, addr, size, section, _source = row
    if section == ".bss":
        return None, "absent", "bss: no bytes in the executable"
    eu = resolver.translate(addr)
    if eu is None:
        return None, "absent", "no PAL address: its US address is not inside a paired datum"
    data, note = section_bytes(obj, section, resolver, whole)
    if data is None:
        return eu, "differs", note
    try:
        theirs = image.read_vaddr(eu, len(data))
    except ValueError:
        return eu, "differs", "PAL has no bytes at 0x%08X.." % eu
    if theirs == data:
        return eu, "match", ""
    first = next(i for i, (a, b) in enumerate(zip(data, theirs)) if a != b)
    return eu, "differs", "first difference at +0x%X" % first


def run():
    import check
    import compile as cc
    import elf
    import tempfile
    import todo
    resolver = check.Resolver("eu")
    image = check.retail_image("eu")
    wholes = todo.whole_files()
    by_source = {}
    for row in us_globals():
        by_source.setdefault(row[4], []).append(row)
    rows = {}
    for source, group in sorted(by_source.items()):
        whole = wholes.get(source)
        with tempfile.TemporaryDirectory(prefix="sly1-dc-") as tmp:
            obj_path = Path(tmp) / "unit.o"
            cc.compile_file(ROOT / source, obj_path, whole=whole is not None)
            obj = elf.Elf(obj_path.read_bytes())
        for row in group:
            eu, status, note = check_global(obj, row, resolver, image, whole)
            rows[row[0]] = ("-" if eu is None else "%08X" % eu, row[2], status, note)
    write(rows)
    return 0


def write(rows):
    text = HEADER + "\n" + "".join("%s\t%s\t%d\t%s\t%s\n" % (n, a, s, st, note)
                                    for n, (a, s, st, note) in sorted(rows.items()))
    STATUS.write_text(text)
    counts = {}
    for _a, _s, status, _n in rows.values():
        counts[status] = counts.get(status, 0) + 1
    print("wrote %s: %s" % (STATUS.relative_to(ROOT) if ROOT in STATUS.parents else STATUS, ", ".join("%d %s" % (v, k) for k, v in sorted(counts.items()))))


def check_current():
    listed = {g[0]: g for g in us_globals()}
    rows = read_status()
    problems = ["%s has no row in config/eu/c_data_status.tsv (run tools/version_check.py)" % n
                for n in sorted(set(listed) - set(rows))]
    problems += ["config/eu/c_data_status.tsv has %s, which config/us/c_data.tsv no longer lists" % n
                 for n in sorted(set(rows) - set(listed))]
    problems += ["config/eu/c_data_status.tsv gives %s %d bytes, config/us/c_data.tsv %d" % (n, rows[n][1], listed[n][2])
                 for n in sorted(set(rows) & set(listed)) if rows[n][1] != listed[n][2]]
    for p in problems:
        print("stale: " + p)
    return 1 if problems else 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args(argv)
    return check_current() if args.check else run()


if __name__ == "__main__":
    sys.exit(main())
