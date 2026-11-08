#!/usr/bin/env python3
# SPDX-License-Identifier: AGPL-3.0-or-later
"""Pad the compiler's short loops as the assembler that built the game did, whatever comes before them.

The EE assembler pads a short loop for the R5900's short-loop erratum: when fewer than five
instructions lie between a backward branch's target label and the branch, with no other branch
or jump among them, it puts nops before the branch until there are five (docs/TOOLCHAIN.md, "The
assembler matters"); some loops it leaves alone (one holding an FPU operation such as `neg.s`).
Retail never has more than that: no loop of five instructions or more has two nops or more
before its branch, and no short loop has more than its count needs (2026-11-08, every backward
branch of SCUS_971.98's .text with no other branch or jump in its loop).

Our assembler counts wrongly where its fragment list breaks near the label. Its fragments live
on an obstack, and a new fragment starts whenever the current chunk runs out (about every 3992
bytes of straight code in a section); when such a break falls within the five instructions after
a loop's label, it counts only the instructions in the label's own fragment and pads a loop that
needs no padding (a 5-instruction loop gets up to five nops, a 10-instruction one as well).
Where the breaks fall depends on everything before them in the section, so a function's C can be
EXACT on its own and still break its file: func_001BC0E0's `.p2align 2` before its divide label
moves the next break into StartSoundEffect's copy loop, which then gets five nops and moves every
later function of file_1B7968.cpp by 0x18. Retail shows no such padding anywhere.

This writes out the padding as our assembler gives it to a loop whose fragment does not break,
which is the original's: every backward branch the compiler emits under `.set noreorder` to one of
its own labels (`$Ln`) is aimed at a forward alias of the label, `$LSLk = $Ln` after it. At the
branch that symbol is not yet defined, so our assembler leaves the loop alone. Each loop with no
other branch or jump inside is first assembled on its own, in a section of its own (a fresh
fragment list, which breaks only every 4 KB), and the nops our assembler puts before its branch
there are written before the branch in the final text. The assembler stays the judge of which
loops it pads and by how much (the 4-instruction list walk at 0x153B18, with its `neg.s`, gets
none in retail and here); only the miscount is gone.

    oracle(asm)               the loops on their own, to assemble first
    padding(obj)              {k: nops} from that assembly's object
    rewrite(asm, padding)     the text to assemble
"""
import re
import struct

LABEL = re.compile(r"^(\$L\d+):\s*$")
BRANCH = re.compile(r"^(\s*)(b|beq|bne|beqz|bnez|blez|bgtz|bltz|bgez|bltzal|bgezal|bc[0-3][tf])(l?)"
                    r"(\s+)(.*?)(\$L\d+)\s*$")
MARK = "__short_loop_%d"
ALIAS = "$LSL%d"
JUMP = re.compile(r"^\s*(b|beq|bne|beqz|bnez|blez|bgtz|bltz|bgez|bltzal|bgezal|bal|bc[0-3][tf]|j|jal|jr|jalr)"
                  r"l?\s")
SET = {".set\tnoreorder": "reorder", ".set noreorder": "reorder", ".set\treorder": "reorder",
       ".set reorder": "reorder", ".set\tnomacro": "macro", ".set nomacro": "macro",
       ".set\tmacro": "macro", ".set macro": "macro", ".set\tnoat": "at", ".set noat": "at",
       ".set\tat": "at", ".set at": "at"}


def _loops(lines):
    """Yield (index of the target label's line, index of the branch line, branch match, the
    `.set` state at the label) for each backward branch under noreorder to a compiler label."""
    state = {"reorder": ".set\treorder", "macro": ".set\tmacro", "at": ".set\tat"}
    seen = {}
    for i, line in enumerate(lines):
        s = line.strip()
        if s in SET:
            state[SET[s]] = s
        m = LABEL.match(line)
        if m:
            seen[m.group(1)] = (i, dict(state))
            continue
        if s.startswith(".end"):
            seen = {}  # a function's labels stay its own
            continue
        if state["reorder"] in (".set\tnoreorder", ".set noreorder"):
            b = BRANCH.match(line)
            if b and b.group(6) in seen:
                top, at_label = seen[b.group(6)]
                yield top, i, b, at_label


def _candidates(lines):
    """The loops our assembler may pad: those with no branch or jump between label and branch."""
    for k, (top, at, b, state) in enumerate(_loops(lines)):
        body = lines[top + 1:at]
        if not any(JUMP.match(l) for l in body):
            yield k, top, at, b, state, body


def oracle(asm):
    """Each loop the assembler may pad, on its own in a section of its own, its labels renamed
    and a marker before its branch; None when there is none."""
    lines = asm.split("\n")
    out = []
    for k, top, at, b, state, body in _candidates(lines):
        rename = lambda text: re.sub(r"(\$L\d+)\b", lambda m: "%s_%d" % (m.group(1), k), text)
        indent, op, likely, space, operands, target = b.groups()
        out += ['\t.section .text.short_loop_%d,"ax",@progbits' % k] + ["\t" + v for v in state.values()]
        out += [rename(lines[top])] + [rename(l) for l in body]
        out += [MARK % k + ":", "%s%s%s%s%s%s_%d" % (indent, op, likely, space, operands, target, k),
                "\tnop", "\t.set\tmacro", "\t.set\treorder", "\t.set\tat"]
    return "\n".join(out) + "\n" if out else None


def is_jump(word):
    """Whether a MIPS word is a branch or a jump (a call included)."""
    op = word >> 26
    rs = (word >> 21) & 31
    rt = (word >> 16) & 31
    if op in (2, 3, 4, 5, 6, 7, 20, 21, 22, 23):
        return True
    if op == 0 and (word & 0x3F) in (8, 9):
        return True
    if op == 1 and rt in (0, 1, 2, 3, 16, 17, 18, 19):
        return True
    return op in (16, 17, 18, 19) and rs == 8


def padding(obj):
    """{k: nops} from the oracle's object (ELF32, little endian): the words our assembler put
    between each loop's marker and its branch."""
    shoff = struct.unpack_from("<I", obj, 0x20)[0]
    shentsize, shnum = struct.unpack_from("<HH", obj, 0x2E)
    sections = [struct.unpack_from("<IIIIIIIIII", obj, shoff + i * shentsize) for i in range(shnum)]
    result = {}
    for sh in sections:
        if sh[1] != 2:  # SHT_SYMTAB
            continue
        strtab = sections[sh[6]]
        for at in range(sh[4], sh[4] + sh[5], 16):
            name, value, _size, _info, _other, shndx = struct.unpack_from("<IIIBBH", obj, at)
            name = obj[strtab[4] + name:].split(b"\0", 1)[0].decode()
            m = re.match(MARK.replace("%d", r"(\d+)") + "$", name)
            if m:
                sec = sections[shndx]
                data = obj[sec[4] + value:sec[4] + sec[5]]
                words = struct.unpack("<%dI" % (len(data) // 4), data)
                result[int(m.group(1))] = next(i for i, w in enumerate(words) if is_jump(w))
    return result


def rewrite(asm, pads=None):
    """The assembly text with each loop's branch aimed at a forward alias of its label and the
    nops `pads` gives it ({k: nops}, from padding()) before its branch."""
    pads = pads or {}
    lines = asm.split("\n")
    after = {}
    before = {}
    branch = {}
    for k, (top, at, b, _state) in enumerate(_loops(lines)):
        indent, op, likely, space, operands, target = b.groups()
        branch[at] = "%s%s%s%s%s%s" % (indent, op, likely, space, operands, ALIAS % k)
        after.setdefault(at, []).append("%s = %s" % (ALIAS % k, target))
        before.setdefault(at, []).extend(["\tnop"] * pads.get(k, 0))
    out = []
    for i, line in enumerate(lines):
        out += before.get(i, [])
        out.append(branch.get(i, line))
        out += after.get(i, [])
    return "\n".join(out)
