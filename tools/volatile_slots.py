#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Put a volatile store into the delay slot of the call right after it, as the assembler that
built Sony's libraries did.

Sony's 2.9-ee-991111 compiler marks a volatile access with `.set volatile` / `.set novolatile`
(kept as comments in its output) and never fills a delay slot with it, so a `jal` right after a
volatile store goes out in reorder mode with an empty slot. Our assembler then adds a nop. In
retail the store sits in the call's slot instead; for a store to an address the assembler builds
itself, its `lui $at` stays before the `jal` and the `sw ...($at)` goes in the slot
(func_0020FAF0, func_00211348). This writes out what that assembler did: the store moves into the
slot of the `jal`, under noreorder.

The idea is OpenRAC's (rac1-decomp, tools/fix_volatile_slot.py, for the same compiler's objects);
this is written anew for this build (THIRD_PARTY_NOTICES.md).

    python3 tools/volatile_slots.py IN.s [OUT.s]    (rewrites IN.s in place without OUT.s)
"""
import re
import sys

STORE = re.compile(r"^\s*(sb|sh|sw|sd)\s+(\$\w+),\s*(.+?)\s*$")
BASED = re.compile(r"^(.*)\((\$\w+)\)$")
JAL = re.compile(r"^\s*jal\s+\S+\s*$")
RA = ("$31", "$ra")


def is_code(line):
    s = line.strip()
    return bool(s) and not s.startswith(("#", ".")) and not s.endswith(":")


def fill(asm):
    """The assembly text with each volatile store before a reorder-mode `jal` moved into its slot."""
    lines = asm.split("\n")
    out = []
    reorder = True
    volatile = False
    store = None  # index in `out` of the last volatile store, while nothing but comments follows it
    for line in lines:
        s = line.strip()
        if s in (".set\tnoreorder", ".set noreorder"):
            reorder = False
        elif s in (".set\treorder", ".set reorder"):
            reorder = True
        if s.replace(" ", "\t") == "#.set\tvolatile":
            volatile = True
        elif s.replace(" ", "\t") == "#.set\tnovolatile":
            volatile = False
        if reorder and store is not None and JAL.match(line):
            m = STORE.match(out[store])
            op, reg, addr = m.groups()
            based = BASED.match(addr)
            if reg not in RA and not (based and based.group(2) in RA):
                del out[store]
                out.append("\t.set\tnoreorder")
                if based:
                    out += [line, "\t%s\t%s,%s" % (op, reg, addr)]
                else:
                    # a store to a symbol or constant: the assembler's own $at pair
                    out += ["\tlui\t$1,%%hi(%s)" % addr, line, "\t%s\t%s,%%lo(%s)($1)" % (op, reg, addr)]
                out.append("\t.set\treorder")
                store = None
                continue
        if is_code(line):
            store = len(out) if (volatile and reorder and STORE.match(line)) else None
        out.append(line)
    return "\n".join(out)


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    src = argv[0]
    dst = argv[1] if len(argv) > 1 else src
    with open(src) as f:
        text = f.read()
    with open(dst, "w") as f:
        f.write(fill(text))


if __name__ == "__main__":
    main()
