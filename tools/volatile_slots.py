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

The same assembler filled the slot of a return (`j $31`) left empty in reorder mode with the
instruction before it, where that is one real instruction: a volatile store (func_001F7270's
write to the serial port), or the second half of a two-instruction pattern the compiler never
puts in a slot itself, the `dsra $r,$r,32` of a 64-to-32-bit truncation (func_002115F8,
func_001F7390). Our assembler leaves every reorder-mode slot empty. A volatile load right before a
reorder-mode `jal` goes into its slot too (func_00203B18's semaphore), unless a label comes
before it or the instruction before it was emitted under noreorder (a branch's slot): there that
assembler did not swap, and retail keeps both of func_00202DA0's volatile loads before their
calls. An assembler macro (`li`, `la`, `dli`) is left where it is (func_001F9AD8).

    python3 tools/volatile_slots.py IN.s [OUT.s]    (rewrites IN.s in place without OUT.s)
"""
import re
import sys

STORE = re.compile(r"^\s*(sb|sh|sw|sd)\s+(\$\w+),\s*(.+?)\s*$")
LOAD = re.compile(r"^\s*(lb|lbu|lh|lhu|lw|lwu|ld)\s+(\$\w+),\s*(-?\w*\(?.*?\(\$\w+\))\s*$")
BASED = re.compile(r"^(.*)\((\$\w+)\)$")
JAL = re.compile(r"^\s*jal\s+\S+\s*$")
RETURN = re.compile(r"^\s*j\s+\$(31|ra)\s*$")
# one real instruction of registers and small constants (no macro, no load)
ALU = re.compile(r"^\s*(d?s(ll|rl|ra)v?|d?addu|d?subu|d?addiu|and|or|xor|nor|andi|ori|xori|"
                 r"slt|sltu|slti|sltiu|move)\s+\$\w+(,\s*(\$\w+|-?\d+))+\s*$")
RA = ("$31", "$ra")


def is_code(line):
    s = line.strip()
    return bool(s) and not s.startswith(("#", ".")) and not s.endswith(":")


def movable(line):
    """Whether the assembler would move this instruction into the slot of the return after it."""
    m = STORE.match(line)
    if m:
        based = BASED.match(m.group(3))
        return m.group(2) not in RA and not (based and based.group(2) in RA)
    return bool(ALU.match(line)) and not any(r in RA for r in re.findall(r"\$\w+", line))


def fill(asm):
    """The assembly text with each volatile store before a reorder-mode `jal`, and each movable
    instruction before a reorder-mode return, moved into its slot."""
    lines = asm.split("\n")
    out = []
    reorder = True
    volatile = False
    store = None  # index in `out` of the last volatile store, while nothing but comments follows it
    load = None  # the same for a volatile load the assembler may swap with a `jal`
    after_reorder = False  # whether the last instruction was emitted in reorder mode, no label since
    last = None  # index in `out` of the last instruction, while nothing but comments follows it
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
        if reorder and load is not None and JAL.match(line):
            prev = out.pop(load)
            out += ["\t.set\tnoreorder", line, prev, "\t.set\treorder"]
            load = last = None
            after_reorder = False
            continue
        if reorder and last is not None and RETURN.match(line) and movable(out[last]):
            prev = out.pop(last)
            out.append("\t.set\tnoreorder")
            m = STORE.match(prev)
            if m and not BASED.match(m.group(3)):
                op, reg, addr = m.groups()
                out += ["\tlui\t$1,%%hi(%s)" % addr, line, "\t%s\t%s,%%lo(%s)($1)" % (op, reg, addr)]
            else:
                out += [line, prev]
            out.append("\t.set\treorder")
            store = last = None
            continue
        if is_code(line):
            store = len(out) if (volatile and reorder and STORE.match(line)) else None
            load = len(out) if (volatile and reorder and after_reorder and LOAD.match(line)) else None
            last = len(out) if reorder else None
            after_reorder = reorder
        elif s and not s.startswith("#"):
            last = None  # a label or a directive: nothing moves across it
            if s.endswith(":"):
                after_reorder = False
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
