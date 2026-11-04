# SPDX-License-Identifier: AGPL-3.0-or-later
"""Every table of function pointers in a version's data, who installs it, and who uses it.

    python3 tools/tables.py            # writes config/us/tables.tsv, members.tsv, installers.tsv, dispatch.tsv
    python3 tools/tables.py --check    # fails when a committed table is out of date

Reads asm/<version>/data/*.s (splat's .rodata and .data) and asm/<version>/text.s.
A table is a run of words, under one of spimdisasm's labels, that holds at least
one function address (`.word func_X`). Each label is one table, except that a
label holding several GCC vtables one after the other is cut at each vtable's
header. Every table gets a kind:

  descriptor     a class descriptor listed in D_00247448 (clsA maps these; not analysed here)
  descriptor?    a descriptor's shape (word 0 a descriptor or D_00217410, three
                 integers, then methods) but not in D_00247448's list
  vtable         GCC 2.95's vtable under -fno-rtti: 8-byte entries {s16 delta,
                 s16 index; fn}, the first {0, 0}, closed by a {0, 0} entry
  vtable/rtti    the same entries with a function in slot 0 (the type-info
                 function) and no closing entry: the library's libstdc++
                 classes, built with RTTI (their mangled names sit next to them).
                 A label that ends in such entries after other data (a string)
                 gives the entries their own table, LABEL+0xOFF
  methods/embedded  a method table inside another label, found by the shape of
                 its family (see embedded())
  descriptor-tail   words past a descriptor's own methods that no family fits
  methods        only function addresses and zeros (a plain method table)
  records/N      function addresses at a fixed stride of N words, among other
                 data (an array of structs that each carry a callback)
  mixed          function addresses among other data, no stride
  fnptr          a one-word label holding one function's address: a global
                 function pointer (a handler the code reads and replaces)
  init-list      a count, that many code addresses, a zero: the static
                 constructors' and destructors' lists (.data's end)
  eh_frame       function addresses that are the start addresses of the
                 frame-unwind records (CIE/FDE chains) of .data: no table
  tlb            TLB entries {PageMask, EntryHi, EntryLo0, EntryLo1} whose
                 EntryHi happens to equal a function's address: no table

members.tsv leaves out what groups no functions into a class: descriptors
(clsA's), fnptr, init-list, eh_frame and tlb.

Writes three tables to --out:

  tables.tsv   address, section, label, kind, entry count, function count, the
               entries in order (`-` for a zero, `?` for a word that is no function)
  members.tsv  per function: every (table, slot) it appears in; slot is the index
               of the entry (a vtable's slot 1 is the first method)
  ctors.tsv    per table: the functions that store its address (lui/addiu, then
               sw of that register: `+OFF(reg)` into an object, or a global's
               name), that pass it to a call (`aN>func`), that return it, that
               take its address otherwise (`addr`), that load a slot of it
               directly (`lw %lo(T)`), and the data labels that hold it

  dispatch.tsv calls through a table's slot: `lw $x, K($obj); lw $f, OFF($x);
               jalr $f`, by (K, OFF), with the calling functions (a guide:
               a straight walk, no types)

The output is a function of the asm alone: same asm, same files.
"""

import argparse
import re
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
DESCRIPTOR_LIST = "D_00247448"
ROOT_DESCRIPTOR = "D_00217410"  # the descriptors' root: two zero words
GAME = (0x100000, 0x1F59C4)
NOT_GROUPS = ("descriptor", "fnptr", "init-list", "eh_frame", "tlb")

WORD = re.compile(r"^\s*/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+\.word\s+(.+?)\s*$")
OTHER = re.compile(r"^\s*/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F ]+ \*/\s+\.(byte|short|asciz|ascii|float|double)\b")
DLABEL = re.compile(r"^dlabel (\S+)")
GLABEL = re.compile(r"^glabel (\S+)")
INSN = re.compile(r"^\s*/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+(\S+)\s*(.*)$")
LO = re.compile(r"%lo\((D_[0-9A-F]+)(?: \+ (0x[0-9A-F]+))?\)")
FUNC = re.compile(r"^func_([0-9A-F]{8})$")
# Instructions whose first operand is read, not written.
NO_DEST = re.compile(r"^(s[bhwdq]|s[wd]c1|swl|swr|sdl|sdr|sqc2|b|j|beq|bne|bl|bg|mt|ctc|sync|cache|teq|tne|syscall|break|c\.)")


def parse_data(path):
    """[(label, section, [(address, token)])] in file order."""
    section = path.name.split(".")[0]
    out, cur = [], None
    for line in path.read_text().splitlines():
        m = DLABEL.match(line)
        if m:
            cur = (m.group(1), section, [])
            out.append(cur)
            continue
        if cur is None:
            continue
        m = WORD.match(line)
        if m:
            cur[2].append((int(m.group(1), 16), m.group(2)))
        elif OTHER.match(line):
            cur[2].append((int(OTHER.match(line).group(1), 16), "?"))
    return out


VALUE = re.compile(r"^D_([0-9A-F]+)(?: \+ (0x[0-9A-F]+))?$")


def value(tok):
    """A word's value: hex, or a symbol that names its address (D_10 + 0x3)."""
    if tok.startswith("0x"):
        return int(tok, 16)
    m = VALUE.match(tok) or FUNC.match(tok)
    if m:
        return int(m.group(1), 16) + (int(m.group(2), 16) if m.lastindex and m.lastindex > 1 and m.group(2) else 0)
    return None


def eh_frame_pcs(labels):
    """The addresses of the start-address words of every FDE in the frame-unwind chains.

    A chain starts at a CIE: a length, a zero id, a version byte 1. Each record is
    a length and that many bytes; an FDE's second word (non-zero) points back at
    its CIE and its third is the start address of the code it describes. A zero
    length ends the chain."""
    word = {}
    for _, _, words in labels:
        for a, t in words:
            word[a] = t
    pcs = set()
    for a in sorted(word):
        if not (value(word.get(a + 4, "")) == 0 and (value(word.get(a + 8, "")) or 0) & 0xFF == 1):
            continue
        n = value(word[a])
        if n is None or not 0x10 <= n <= 0x40 or a in pcs:
            continue
        p = a
        while True:
            n = value(word.get(p, ""))
            if not n or n % 4 or n > 0x1000 or p + 4 not in word:
                break
            if value(word[p + 4]):  # an FDE
                pcs.add(p + 8)
            p += 4 + n
    return pcs


def init_list(words, before):
    """True for a count (here, or as the word before the label), that many code addresses, a zero."""
    toks = [t for _, t in words]
    for k, body in ((value(toks[0]) if toks else None, toks[1:]), (value(before) if before else None, toks)):
        if k and 0 < k <= len(body) - 1 and is_zero(body[k]):
            if all((value(t) or 0) in range(0x100000, 0x211E0C) for t in body[:k]):
                return True
    return False


def tlb(words):
    toks = [value(t) for _, t in words]
    if len(toks) < 8 or len(toks) % 4:
        return False
    return all(v is not None and v & 0x1FFF == 0 and v & ~0x01FFE000 == 0 and v for v in toks[0::4])


def is_func(tok):
    return FUNC.match(tok) is not None


def is_zero(tok):
    return tok == "0x00000000"


def small_pair(tok):
    """A vtable entry's first word: {s16 delta, s16 index} as two small halves."""
    if not tok.startswith("0x"):
        return False
    v = int(tok, 16)
    lo, hi = v & 0xFFFF, v >> 16
    return (lo < 0x100 or lo >= 0xFF00) and (hi < 0x100 or hi >= 0xFF00)


def split_vtables(words):
    """Cut a run of vtable entries at each header; [] if the words are not vtables."""
    if len(words) < 4 or len(words) % 2 or not (is_zero(words[0][1]) and is_zero(words[1][1])):
        return []
    ents = [(words[i], words[i + 1]) for i in range(0, len(words), 2)]
    for a, b in ents:
        if not small_pair(a[1]) or not (is_func(b[1]) or is_zero(b[1])):
            return []
    if not any(is_func(b[1]) for _, b in ents):
        return []
    # A vtable: header {0,0}, entries with a function, a closing {0,0}.
    # Further {0,0} entries are padding, until one that a function follows: a new header.
    tables, start, i, n = [], 0, 1, len(ents)
    while i < n:
        if is_zero(ents[i][1][1]):
            j = i + 1
            while j < n and is_zero(ents[j][1][1]) and is_zero(ents[j][0][1]):
                j += 1
            if j < n and j > i + 1:
                # ents[j-1] is the next header
                tables.append(ents[start:j - 1])
                start = j - 1
            i = j
        else:
            i += 1
    tables.append(ents[start:])
    out = []
    for t in tables:
        flat = [w for e in t for w in e]
        out.append(flat)
    return out


def rtti_suffix(words):
    """Where a label's trailing {0, fn} entries start (two or more, 8-aligned), or None."""
    n = len(words)
    i = n
    while i >= 2 and is_zero(words[i - 2][1]) and is_func(words[i - 1][1]) and words[i - 2][0] % 8 == 0:
        i -= 2
    if n - i < 4:
        return None
    if i and not any(not t.startswith("0x") or (t != "0x00000000" and not is_func(t)) for _, t in words[:i]):
        return None  # only zeros before: a plain table that alternates, not a vtable after data
    return i


def stride(positions):
    """The stride of the function words, in words, if they sit at one."""
    if len(positions) < 3:
        return None
    gaps = {b - a for a, b in zip(positions, positions[1:])}
    if len(gaps) == 1:
        g = gaps.pop()
        return g if g > 1 else None
    return None


def classify(label, words, descriptors, descriptor_labels):
    funcs = [i for i, (_, t) in enumerate(words) if is_func(t)]
    if label in descriptors:
        return "descriptor"
    toks = [t for _, t in words]
    if (len(toks) > 4 and (toks[0] in descriptor_labels or toks[0] == ROOT_DESCRIPTOR)
            and all(t.startswith("0x") for t in toks[1:4])
            and all(is_func(t) or is_zero(t) for t in toks[4:])):
        return "descriptor?"
    if len(toks) == 1:
        return "fnptr"
    if all(is_func(t) or is_zero(t) for t in toks):
        return "methods"
    s = stride(funcs)
    if s:
        return "records/%d" % s
    return "mixed"


def embedded(tables, labels, descriptors):
    """Method tables inside another label, found by their family's shape.

    A family is two or more `methods` tables of one length (four entries or
    more). Its signature is each slot whose function most of the family (two
    tables at least) shares.
    A window of that length, of functions and zeros only, sharing at least 60%
    of the signature (two slots at least), is an embedded table: spimdisasm gave
    it no label, since nothing names its address.

    Two places are searched. A descriptor's tail: a class has no more methods
    than the least of its children, so a descriptor's words past 4 + that count
    are not its own; they are cut into family windows, and what is left with a
    function in it is `descriptor-tail`. Any other label, from its second word,
    for windows of a family of three or more that start with a function."""
    fams = defaultdict(list)
    for _, _, label, kind, words in tables:
        if kind == "methods" and len(words) >= 4:
            fams[len(words)].append([t for _, t in words])
    sigs = []
    for n, members in sorted(fams.items()):
        if len(members) < 2:
            continue
        sig = {}
        for i in range(n):
            col = [m[i] for m in members if is_func(m[i])]
            if col:
                best = max(sorted(set(col)), key=col.count)
                if col.count(best) >= 2 and col.count(best) * 2 >= len(members):
                    sig[i] = best
        if len(sig) >= 2:
            sigs.append((n, len(members), sig))
    sigs.sort(key=lambda x: (-x[0], -x[1]))

    def fits(win, sig):
        need = max(2, -(-len(sig) * 3 // 5))
        return (all(is_func(t) or is_zero(t) for t in win)
                and sum(1 for k, f in sig.items() if win[k] == f) >= need)

    bylabel = {l: w for l, _, w in labels}
    least = {}
    for d in descriptors:
        if d in bylabel and bylabel[d]:
            parent = bylabel[d][0][1]
            least[parent] = min(least.get(parent, 1 << 30), len(bylabel[d]) - 4)
    out = []
    for label, section, words in labels:
        if label.startswith("jtbl_") or not any(is_func(t) for _, t in words):
            continue
        toks = [t for _, t in words]
        name = lambda i: "%s+0x%X" % (label, words[i][0] - words[0][0])
        if label in descriptors:
            if label not in least or 4 + least[label] >= len(toks):
                continue
            i, rest = 4 + least[label], []
            while i < len(toks):
                for n, _, sig in sigs:
                    if i + n <= len(toks) and fits(toks[i:i + n], sig):
                        out.append((words[i][0], section, name(i), "methods/embedded", words[i:i + n]))
                        i += n
                        break
                else:
                    rest.append(i)
                    i += 1
            if any(is_func(toks[k]) for k in rest):
                out.append((words[rest[0]][0], section, name(rest[0]), "descriptor-tail", [words[k] for k in rest]))
            continue
        taken = [False] * len(toks)
        for n, count, sig in sigs:
            if count < 3:
                continue
            i = 1
            while i + n <= len(toks):
                win = toks[i:i + n]
                if is_func(win[0]) and not any(taken[i:i + n]) and fits(win, sig):
                    for k in range(i, i + n):
                        taken[k] = True
                    out.append((words[i][0], section, name(i), "methods/embedded", words[i:i + n]))
                    i += n
                else:
                    i += 1
    return out


def parse_text(path):
    """{function: [(address, mnemonic, operands)]}."""
    funcs, cur = {}, None
    for line in path.read_text().splitlines():
        m = GLABEL.match(line)
        if m:
            cur = m.group(1)
            funcs[cur] = []
            continue
        if line.startswith("endlabel"):
            cur = None
            continue
        if cur:
            m = INSN.match(line)
            if m:
                funcs[cur].append((int(m.group(1), 16), m.group(2), m.group(3)))
    return funcs


def regs(ops):
    return [o.strip() for o in ops.split(",")]


ARGS = ("$a0", "$a1", "$a2", "$a3", "$a4", "$a5", "$a6", "$a7")
CLOBBERED = ARGS + ("$v0", "$v1", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9", "$at")
MOVES = ("daddu", "addu", "or", "move")


def scan_uses(funcs, wanted):
    """{table label: {function: set of uses}} for the labels in wanted.

    A straight walk through each function that follows a table's address from
    its addiu through register moves: `store` where it is stored (to an
    object's field or a global), `arg` where it is in an argument register at
    a call, `return` where it is in $v0 at the jr $ra, `addr` otherwise, and
    `load` for an lw of one of the table's slots by its own %lo. Branches are
    ignored (a register keeps its table along the text), so this is a guide."""
    uses = defaultdict(lambda: defaultdict(set))
    for fn, insns in funcs.items():
        held = {}  # register -> table label
        call = None  # a jal whose delay slot is next
        for _, mn, ops in insns:
            m = LO.search(ops)
            r = regs(ops)
            if m and m.group(1) in wanted:
                lab, add = m.group(1), m.group(2)
                if mn in ("addiu", "daddiu"):
                    if add:
                        uses[lab][fn].add("addr+%s" % add)
                    else:
                        held[r[0]] = lab
                        uses[lab][fn].add("addr")
                elif mn in ("lw", "ld"):
                    uses[lab][fn].add("load+%s" % (add or "0x0"))
                    held.pop(r[0], None)
                else:
                    uses[lab][fn].add(mn)
            elif mn in ("sw", "sd") and r and r[0] in held:
                dst = r[1]
                g = LO.search(dst)
                if g:
                    target = g.group(1) + (" + " + g.group(2) if g.group(2) else "")
                else:
                    off = dst.split("(")[0] or "0x0"
                    target = "+%s(%s)" % (off, dst.split("(")[1].rstrip(")"))
                uses[held[r[0]]][fn].add("store " + target)
            elif mn in MOVES and len(r) == 3 and r[2] == "$zero" and r[1] in held:
                held[r[0]] = held[r[1]]
            elif r and r[0].startswith("$") and not NO_DEST.match(mn) and r[0] in held:
                held.pop(r[0])
            if call is not None:
                target, ret = call
                if ret:
                    if "$v0" in held:
                        uses[held["$v0"]][fn].add("return")
                else:
                    for a in ARGS:
                        if a in held:
                            uses[held[a]][fn].add("arg %s>%s" % (a[1:], target))
                    for c in CLOBBERED:
                        held.pop(c, None)
                call = None
            if mn.startswith("jal"):
                call = (r[-1], False)
            elif mn == "jr" and r[0] == "$ra":
                call = ("", True)
            elif mn == "j" and FUNC.match(r[0]):  # a tail call
                call = (r[0], False)
    return uses


def scan_dispatch(funcs):
    """{(vptr offset, slot offset): [function]} for every call through a pointer read from a pointer.

    `lw $x, K($obj)`, then `lw $f, OFF($x)`, then `jalr $f`: a call through
    slot OFF of a table whose address the object holds at +K. A GCC vtable's
    slot n is at OFF = 8n + 4 (its delta at 8n)."""
    out = defaultdict(list)
    for fn, insns in funcs.items():
        tab, slot = {}, {}
        for _, mn, ops in insns:
            r = regs(ops)
            if mn == "jalr":
                f = r[-1]
                if f in slot:
                    out[slot[f]].append(fn)
                continue
            if mn == "lw" and len(r) == 2 and "(" in r[1] and "%" not in r[1]:
                off = int(r[1].split("(")[0] or "0", 16) if r[1].split("(")[0] not in ("", "0") else 0
                base = r[1].split("(")[1].rstrip(")")
                if base in tab:
                    slot[r[0]] = (tab[base], off)
                    tab.pop(r[0], None)
                else:
                    tab[r[0]] = off
                    slot.pop(r[0], None)
                continue
            if r and r[0].startswith("$") and not NO_DEST.match(mn):
                tab.pop(r[0], None)
                slot.pop(r[0], None)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--version", default="us")
    ap.add_argument("--check", action="store_true", help="fail if a committed table is out of date")
    args = ap.parse_args()
    asm = ROOT / "asm" / args.version
    datadir = asm / "data"
    if not (asm / "text.s").exists():
        raise SystemExit("error: asm/%s/ is empty; run tools/setup_asm.py --version %s" % (args.version, args.version))

    labels = []
    for p in sorted(datadir.glob("*.s")):
        labels += parse_data(p)
    bylabel = {l: (s, w) for l, s, w in labels}
    descriptors = set()
    if DESCRIPTOR_LIST in bylabel:
        descriptors = {t for _, t in bylabel[DESCRIPTOR_LIST][1] if t.startswith("D_")}

    pcs = eh_frame_pcs(labels)
    tables = []  # (address, section, label, kind, words)
    prev = None
    for label, section, words in labels:
        before, prev = (prev[-1][1] if prev else None), words
        if label.startswith("jtbl_") or not any(is_func(t) for _, t in words):
            continue
        fw = [a for a, t in words if is_func(t)]
        if all(a in pcs for a in fw):
            tables.append((words[0][0], section, label, "eh_frame", words))
            continue
        if tlb(words):
            tables.append((words[0][0], section, label, "tlb", words))
            continue
        if label not in descriptors and init_list(words, before):
            tables.append((words[0][0], section, label, "init-list", words))
            continue
        vts = split_vtables(words) if label not in descriptors else []
        if vts:
            for i, flat in enumerate(vts):
                name = label if i == 0 else "%s+0x%X" % (label, flat[0][0] - words[0][0])
                tables.append((flat[0][0], section, name, "vtable", flat))
            continue
        n = rtti_suffix(words) if label not in descriptors else None
        if n is not None:
            if n and any(is_func(t) for _, t in words[:n]):
                tables.append((words[0][0], section, label, classify(label, words[:n], descriptors, descriptors), words[:n]))
            name = label if n == 0 else "%s+0x%X" % (label, words[n][0] - words[0][0])
            tables.append((words[n][0], section, name, "vtable/rtti", words[n:]))
            continue
        kind = classify(label, words, descriptors, descriptors)
        tables.append((words[0][0], section, label, kind, words))
    tables += embedded(tables, labels, descriptors)
    tables.sort()

    funcs = parse_text(asm / "text.s")
    uses = scan_uses(funcs, {t[2] for t in tables})
    names = {t[2] for t in tables}
    datarefs = defaultdict(set)
    for label, _, words in labels:
        for _, t in words:
            m = VALUE.match(t)
            if m and t.split(" ")[0] in names:
                datarefs[t.split(" ")[0]].add(label)

    import tempfile
    final = ROOT / "config" / args.version
    tmp = tempfile.TemporaryDirectory()
    out = Path(tmp.name) if args.check else final
    with open(out / "dispatch.tsv", "w") as f:
        f.write("vptr\tslot_offset\tsites\tfunctions\n")
        for (k, off), fns in sorted(scan_dispatch(funcs).items()):
            if k < 0 or off < 0:
                continue
            f.write("+0x%X\t0x%X\t%d\t%s\n" % (k, off, len(fns), " ".join(sorted(set(fns)))))
    members = defaultdict(list)
    with open(out / "tables.tsv", "w") as f:
        f.write("address\tsection\tlabel\tkind\tentries\tfunctions\tslots\n")
        for addr, section, label, kind, words in tables:
            if kind == "vtable":
                ents = [words[i + 1][1] for i in range(0, len(words), 2)]
            else:
                ents = [t for _, t in words]
            shown = []
            for i, t in enumerate(ents):
                if is_func(t):
                    shown.append(t)
                    if kind not in NOT_GROUPS:
                        members[t].append("%s[%d]" % (label, i))
                else:
                    shown.append("-" if is_zero(t) else "?")
            nf = sum(1 for t in ents if is_func(t))
            if kind == "descriptor":
                shown = ["(clsA)"]
            f.write("%08X\t%s\t%s\t%s\t%d\t%d\t%s\n" % (addr, section, label, kind, len(ents), nf, " ".join(shown)))
    with open(out / "members.tsv", "w") as f:
        f.write("function\taddress\tzone\ttables\tslots\n")
        for fn in sorted(members, key=lambda n: int(n[5:], 16)):
            a = int(fn[5:], 16)
            zone = "game" if GAME[0] <= a < GAME[1] else "lib"
            slots = members[fn]
            f.write("%s\t%08X\t%s\t%d\t%s\n" % (fn, a, zone, len({s.split("[")[0] for s in slots}), " ".join(slots)))
    with open(out / "installers.tsv", "w") as f:
        f.write("address\tlabel\tkind\tinstall\tpass\treturn\taddr\tload\tdata\n")
        for addr, section, label, kind, words in tables:
            u = uses.get(label, {})
            inst, pas, ret, take, load = [], [], [], [], []
            for fn in sorted(u):
                kinds = u[fn]
                st = sorted(k[6:] for k in kinds if k.startswith("store "))
                ar = sorted(k[4:] for k in kinds if k.startswith("arg "))
                if st:
                    inst.append("%s:%s" % (fn, ",".join(st)))
                if ar:
                    pas.append("%s:%s" % (fn, ",".join(ar)))
                if "return" in kinds:
                    ret.append(fn)
                if not (st or ar or "return" in kinds) and any(k.startswith("addr") for k in kinds):
                    take.append(fn)
                if any(k.startswith("load") for k in kinds):
                    load.append(fn)
            f.write("%08X\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n" % (addr, label, kind, " ".join(inst) or "-",
                                                       " ".join(pas) or "-", " ".join(ret) or "-",
                                                       " ".join(take) or "-", " ".join(load) or "-",
                                                       " ".join(sorted(datarefs.get(label, ()))) or "-"))
    names = ("tables.tsv", "members.tsv", "installers.tsv", "dispatch.tsv")
    if args.check:
        stale = [n for n in names if not (final / n).exists() or (final / n).read_text() != (out / n).read_text()]
        if stale:
            raise SystemExit("stale: %s (run python3 tools/tables.py)" % ", ".join(stale))
        return
    for n in names:
        print("wrote %s" % (final / n).relative_to(ROOT))


if __name__ == "__main__":
    main()
