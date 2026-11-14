# SPDX-License-Identifier: AGPL-3.0-or-later
"""The alignment padding between the data C defines: config/us/padding.tsv.

    python3 tools/padding.py           # writes config/us/padding.tsv
    python3 tools/padding.py --check   # fails when the table is out of date

The linker places each file's section at the next multiple of the section's alignment, and
GCC pads inside a section up to an object's alignment; the zeros it leaves are made by the
assembler and the linker, not by any object of the source, so no C global defines them (a
padding array is not allowed: AGENTS.md). tools/progress.py counts them as matched data from
this table, by one rule. A run of bytes is padding when

- no global C defines covers it and no row of config/us/original_data.tsv either;
- it lies between the end of one credited object (a C section or global of
  config/us/c_data.tsv, or a row of original_data.tsv) and the start of the next one in the
  same section, with nothing in between;
- the next one is a C section or global, and rounding the gap's start up to that section's
  alignment (its sh_addralign in the object the last build linked) gives exactly its start:
  the gap is shorter than the alignment and is what the linker or GCC inserts;
- every byte of it is zero in retail.

A whole file's section that includes labels from the disassembly (INCLUDE_RODATA,
INCLUDE_DATA) is covered by C apart from those labels, which sit at their addresses; a gap next
to one is not padding until the label is C. The table is written by tools/build.py with
config/us/c_data.tsv after each build that prints MATCH, and needs the disc, asm/us/ and that
build's objects to be written or checked; tools/progress.py and CI read only the table.
"""

import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
TABLE = ROOT / "config" / "us" / "padding.tsv"
HEADER = "address\tsize\talign\tbefore"


def aligned_up(addr, align):
    return (addr + align - 1) // align * align if align > 1 else addr


def find(objects, sections, read):
    """[(address, size, align, before)] of the padding runs.

    objects: [(start, end, align or None, name)] of the credited objects; align None for one
    whose alignment does not decide a gap (an original data row). sections: [(start, end)] of
    the data sections. read(address, size) gives retail's bytes."""
    out = []
    for lo, hi in sections:
        mine = sorted(o for o in objects if lo <= o[0] < hi)
        for prev, nxt in zip(mine, mine[1:]):
            start, end = prev[1], nxt[0]
            if end <= start or not nxt[2]:
                continue
            if aligned_up(start, nxt[2]) != end or any(read(start, end - start)):
                continue
            out.append((start, end - start, nxt[2], nxt[3]))
    return out


def section_alignment(source, section, name):
    """The alignment of a C file's section (a global's own section: .data.D_XXXXXXXX), from the
    object of the last build."""
    import elf
    obj = ROOT / "build" / "us" / Path(source).with_suffix(".o")
    if not obj.exists():
        raise SystemExit("error: %s is missing; run python3 tools/build.py" % obj.relative_to(ROOT))
    o = elf.Elf(obj.read_bytes())
    sec = o.section(section) if section.count(".") > 1 else (o.section("%s.%s" % (section, name)) or o.section(section))
    if sec is None:
        raise SystemExit("error: %s has no section %s" % (obj.relative_to(ROOT), section))
    return sec["align"]


def credited(key="us"):
    """[(start, end, align, name)] of the objects config/us/c_data.tsv and original_data.tsv
    credit. A whole file's section that includes labels from the disassembly is split around
    them (c_data.tsv gives its size without them)."""
    import asm_func
    import progress
    listings = {}
    out = []
    for line in (ROOT / "config" / key / "c_data.tsv").read_text().splitlines()[1:]:
        if not line:
            continue
        name, addr, size, section, source = line.split("\t")
        addr, size = int(addr, 16), int(size)
        align = section_alignment(source, section, name)
        label = "%s %s" % (source, section)
        if section not in (".rodata", ".data"):
            out.append((addr, addr + size, align, label))
            continue
        text = (ROOT / source).read_text()
        included = asm_func.included_rodata(text) if section == ".rodata" else asm_func.included_data(text)
        if not included:
            out.append((addr, addr + size, align, label))
            continue
        listing = "%s.%s.s" % (section[1:], section[1:])
        if listing not in listings:
            listings[listing] = (ROOT / "asm" / key / "data" / listing).read_text()
        pieces = sorted((int(l[-8:], 16), asm_func.label_size(listings[listing], l)) for l in included)
        end = addr + size + sum(s for _a, s in pieces)
        at = addr
        for a, s in pieces:
            if a > at:
                out.append((at, a, align if at == addr else None, label))
            at = a + s
        if end > at:
            out.append((at, end, None, label))
    out += [(a, a + s, None, "original data") for a, s in progress.original_data(key)]
    return sorted(out)


def compute(key="us"):
    import check
    import todo
    image = check.retail_image(key)
    sections = [(s, e) for kind, _n, s, e, _c, _f in todo.layout(key) if kind == "data"]
    return find(credited(key), sections, image.read_vaddr)


def render(rows):
    return HEADER + "\n" + "".join("%08X\t%d\t%d\t%s\n" % r for r in rows)


def read_table(path=TABLE):
    """[(address, size)] of config/us/padding.tsv."""
    if not path.exists():
        return []
    rows = [l.split("\t") for l in path.read_text().splitlines()[1:] if l]
    return [(int(r[0], 16), int(r[1])) for r in rows]


def write(key="us"):
    text = render(compute(key))
    if not TABLE.exists() or TABLE.read_text() != text:
        TABLE.write_text(text)
    return text


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--check", action="store_true", help="fail when config/us/padding.tsv is out of date")
    args = parser.parse_args(argv)
    text = render(compute())
    rows = text.count("\n") - 1
    size = sum(int(l.split("\t")[1]) for l in text.splitlines()[1:])
    if args.check:
        if not TABLE.exists() or TABLE.read_text() != text:
            print("stale: %s (run python3 tools/padding.py)" % TABLE.relative_to(ROOT))
            return 1
        print("ok: %s, %d runs of padding, %d bytes" % (TABLE.relative_to(ROOT), rows, size))
        return 0
    if not TABLE.exists() or TABLE.read_text() != text:
        TABLE.write_text(text)
    print("wrote %s: %d runs of padding, %d bytes" % (TABLE.relative_to(ROOT), rows, size))
    return 0


if __name__ == "__main__":
    sys.exit(main())
