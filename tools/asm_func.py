#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""One original-assembly function of the disassembly, as a file a C source can include.

A whole file (config/us/files.tsv) is built as one object, as the original was, so an original
assembly function inside its range has to be in that object too. `INCLUDE_ASM(func_X);`
(include/asm_func.h) includes build/us/asm_func/func_X.s, which tools/compile.py writes from
asm/us/text.s before compiling: the function's lines, from its label to its size, with the
listing's macros written out (the toolchain's 1999 assembler does not read splat's) and its
registers as numbers (that assembler rejects most of their names). Nothing of the game is
committed: the file is generated in build/ from each contributor's own disassembly.

    python3 tools/asm_func.py func_X ...    (writes the files and prints their paths)
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
INCLUDE = re.compile(r"^\s*INCLUDE_ASM\(\s*(func_[0-9A-F]{8})\s*\)", re.M)
# The listing names the registers as the 64-bit ABI does: $8-$11 are $a4-$a7 and $12-$15 are
# $t0-$t3 (checked against the encodings).
REGS = {n: i for i, n in enumerate(
    "zero at v0 v1 a0 a1 a2 a3 a4 a5 a6 a7 t0 t1 t2 t3 s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra".split())}
REGS["s8"] = 30


def included(text):
    """The functions a C source includes with INCLUDE_ASM, in order."""
    return INCLUDE.findall(text)


def function_lines(listing, name):
    """The lines of `name` in a splat text listing, from its label to its declared size, and that
    size: (lines, size). The padding after its end belongs to the next function's alignment."""
    m = re.search(r"^nonmatching %s, (0x[0-9A-Fa-f]+)\n\n?glabel %s\n" % (name, name), listing, re.M)
    if m is None:
        raise KeyError("%s is not a function of the listing" % name)
    size = int(m.group(1), 16)
    out, words = [], 0
    for line in listing[m.end():].split("\n"):
        if words * 4 >= size:
            break
        if re.match(r"^\s*(endlabel|nonmatching|glabel)\b", line):
            break
        out.append(line)
        if re.match(r"^\s*/\*\s*[0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/", line):
            words += 1
    if words * 4 != size:
        raise KeyError("%s: %d bytes of code found, the listing says %d" % (name, words * 4, size))
    return out, size


ENCODED = re.compile(r"^(\s*)/\*\s*[0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s*(\S+)")


def numeric(line):
    """A line with the general registers as numbers. A VU0 macro instruction (a v* mnemonic) is
    written as its word from the listing: that assembler does not read their $ACC, $Q and
    broadcast operands, and they take no relocation."""
    m = ENCODED.match(line)
    if m and m.group(3).startswith("v"):
        b = m.group(2)
        return "%s.word\t0x%s%s%s%s\t# %s" % (m.group(1), b[6:8], b[4:6], b[2:4], b[0:2], line.split("*/", 1)[1].strip())
    return re.sub(r"\$(\w+)\b", lambda m: "$%d" % REGS[m.group(1)] if m.group(1) in REGS else m.group(0), line)


def source(listing, name):
    """The assembly file for `name`."""
    lines, size = function_lines(listing, name)
    # The alignment the original object gave the function: 8 where its address allows, as the
    # compiler aligns its own functions.
    align = 3 if int(name[5:], 16) % 8 == 0 else 2
    head = ["\t.align\t%d" % align, "\t.globl\t%s" % name, "\t.type\t%s, @function" % name, "%s:" % name]
    return "\n".join(head + [numeric(line) for line in lines] + ["\t.size\t%s, %d" % (name, size), ""])


def write(names, key="us"):
    """Write build/<key>/asm_func/<name>.s for each name where it is missing or older than the
    listing; returns the paths."""
    text = ROOT / "asm" / key / "text.s"
    out_dir = ROOT / "build" / key / "asm_func"
    paths, listing = [], None
    for name in names:
        path = out_dir / ("%s.s" % name)
        if not path.exists() or path.stat().st_mtime < text.stat().st_mtime:
            if listing is None:
                listing = text.read_text()
            out_dir.mkdir(parents=True, exist_ok=True)
            path.write_text(source(listing, name))
        paths.append(path)
    return paths


if __name__ == "__main__":
    for p in write(sys.argv[1:]):
        print(p.relative_to(ROOT))
