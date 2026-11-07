# SPDX-License-Identifier: AGPL-3.0-or-later
"""The game's class map, from the class descriptors of retail's .rodata.

    python3 tools/classes.py            # writes config/us/classes.tsv, methods.tsv, creators.tsv
    python3 tools/classes.py --check    # fails when a committed table is out of date

Retail keeps one pointer per class id in a table at D_00247448 (149 words):
func_0011E580(id, ...) creates an object of class `id` from entry `id` (it
allocates the descriptor's size, stores the descriptor at +0 and calls the
slot at +0x10), and func_0015A4B8(id, ...) walks the parent pointers from
entry `id`. Each pointer leads to a descriptor (the ClassDesc_217418 tables of
src/main/class_descriptors.cpp):

    +0x00  the parent's descriptor
    +0x04  the class id (equal to its index in the table)
    +0x08  flags
    +0x0C  the size of an object
    +0x10  method slots, one word each

A descriptor does not count its slots. It runs at most to the end of its data
label (spimdisasm ends a label where the next one starts) or to the next
descriptor of the table. A child has at least its parent's slots, so a class
ends at the fewest slots any of its children has: where its label runs on
past that, the words after it are other data no code names (the `note`
column), and the class has no more slots than that. The tool fails when a
class holds an id other than its index or names a function
config/us/functions.tsv does not have.

classes.tsv, one row per table entry: index, descriptor, kind (`class`;
`root`, the empty entry every chain ends at; `head`, a parent and id with no
slots; `empty`), id, parent (index), depth (steps to the root), flags, size,
words (the descriptor's length to its label's end, header included), slots,
own (how many slots the class fills itself), note, and every slot in order:
`+func_X` where the class puts its own function (in a slot its parent lacks
or fills otherwise), `func_X` where it keeps its parent's, `0` where the slot
is empty (`+0` where it empties one its parent fills).

methods.tsv, one row per function in any slot: the slots it is the class's own
method in, each as `index@offset` (the offset in the descriptor), and how many
classes inherit it (which ones classes.tsv shows, slot by slot).

creators.tsv, one row per class some function creates with a constant id: the
functions that call func_0011E580 with that id in $a0 (followed back through
straight-line code and the ways into a local label; an id from data, a
stream or an argument is not followed).

Reads asm/us/data/*.s and asm/us/text.s, which tools/setup_asm.py writes, and
config/us/functions.tsv; --check passes without asm/us/. The tables hold
indices, ids, flags, sizes and function names, no instructions or other data.
"""

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
OUT = ROOT / "config" / "us"

TABLE = 0x247448
ENTRIES = 149
CREATE = "func_0011E580"           # create(id, parent, a2, a3, a4)
HEADER_WORDS = 4                   # parent, id, flags, size

DLABEL = re.compile(r"^dlabel (\S+)")
ENDLABEL = re.compile(r"^enddlabel ")
DATUM = re.compile(r"^\s*/\* [0-9A-F]+ ([0-9A-F]{8}) ?([0-9A-F]*) \*/\s+\.(word|short|byte|space)\s+(.*)$")
LABEL = re.compile(r"^(?:glabel|nonmatching) (func_[0-9A-F]{8})")
INSN = re.compile(r"^\s*/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+(\S+)\s*(.*)$")
LOCAL = re.compile(r"^\s*(\.L[0-9A-F]+):")


# --- reading the listings ------------------------------------------------------

def read_data(texts):
    """(words, labels) from data listings: words {address: (value, operand)} of every .word,
    the value from the listing's bytes and the operand as spimdisasm wrote it; labels
    {address: end} of every data label, end being the address after its data."""
    words, labels = {}, {}
    for text in texts:
        current = None
        for line in text.splitlines():
            m = DLABEL.match(line)
            if m:
                current = [None, None]
                continue
            if ENDLABEL.match(line):
                current = None
                continue
            m = DATUM.match(line)
            if not m or current is None:
                continue
            address, raw, kind, operand = int(m.group(1), 16), m.group(2), m.group(3), m.group(4).strip()
            size = {"word": 4, "short": 2, "byte": 1}.get(kind)
            if size is None:
                size = int(operand.split(",")[0], 0)
            if current[0] is None:
                current[0] = address
            labels[current[0]] = current[1] = address + size
            if kind == "word":
                words[address] = (int.from_bytes(bytes.fromhex(raw), "little"), operand)
    return words, labels


def slot_name(word):
    """A slot as the table shows it: the function's name, `0`, or the word in hex."""
    number, operand = word
    if operand.startswith("func_"):
        return operand
    return "0" if number == 0 else "0x%X" % number


# --- the descriptors -----------------------------------------------------------

def descriptors(words, labels, functions):
    """[dict] per table entry, in table order: index, address, kind, words (the descriptor's
    length in words, to its label's end or the next descriptor), and for a class parent
    (index), id, flags, size and slots (names, see slot_name)."""
    table = []
    for i in range(ENTRIES):
        if TABLE + 4 * i not in words:
            raise SystemExit("error: D_%08X has no word %d" % (TABLE, i))
        table.append(words[TABLE + 4 * i][0])
    starts = sorted(set(table))
    by_address = {}
    for i, a in enumerate(table):
        by_address.setdefault(a, i)

    out = []
    for i, address in enumerate(table):
        row = {"index": i, "address": address, "kind": "", "slots": [], "words": 0, "note": ""}
        out.append(row)
        if address not in labels:
            row["kind"] = "not at a label"
            continue
        end = labels[address]
        later = [s for s in starts if s > address]
        if later and later[0] < end:
            end = later[0]
        body = []
        for a in range(address, end, 4):
            if a not in words:
                break
            body.append(words[a])
        row["words"] = len(body)
        parent = body[0][0] if body else None
        if len(body) >= HEADER_WORDS and parent in by_address:
            row.update(kind="class", parent=by_address[parent], id=body[1][0], flags=body[2][0],
                       size=body[3][0], slots=[slot_name(w) for w in body[HEADER_WORDS:]])
        elif len(body) == 2 and parent in by_address and body[1][0] == i:
            row.update(kind="head", parent=by_address[parent], id=i)   # parent and id, no class
        elif all(w[0] == 0 for w in body):
            row["kind"] = "empty"
        else:
            row["kind"] = "%d words" % len(body)
    for row in out:
        if row["kind"] in ("class", "head"):
            p = out[row["parent"]]
            if p["kind"] == "empty":
                p["kind"] = "root"
    for row in out:
        if row["kind"] == "class" and row["id"] != row["index"]:
            raise SystemExit("error: entry 0x%02X holds class id 0x%X" % (row["index"], row["id"]))
        for name in row["slots"]:
            if name.startswith("func_") and name not in functions:
                raise SystemExit("error: entry 0x%02X names %s, which is not a function" % (row["index"], name))
    trim(out)
    depths(out)
    own(out)
    return out


def trim(rows):
    """Ends each class at its children's slots: a child has at least its parent's slots, so
    a parent whose label runs on past what every child has holds other data there (tables
    no code names, so spimdisasm put no label at them). Children first."""
    children = {}
    for r in rows:
        if r["kind"] == "class":
            children.setdefault(r["parent"], []).append(r)
    done = set()

    def visit(r):
        if r["index"] in done:
            return
        done.add(r["index"])
        for c in children.get(r["index"], []):
            visit(c)
        n = min([len(r["slots"])] + [len(c["slots"]) for c in children.get(r["index"], [])])
        if n < len(r["slots"]):
            r["note"] = "%d words after its slots" % (len(r["slots"]) - n)
            r["slots"] = r["slots"][:n]

    for r in rows:
        if r["kind"] == "class":
            visit(r)


def depths(rows):
    for row in rows:
        depth, seen, r = 0, set(), row
        while r["kind"] in ("class", "head"):
            if r["index"] in seen:
                raise SystemExit("error: entry 0x%02X has a parent loop" % row["index"])
            seen.add(r["index"])
            r = rows[r["parent"]]
            depth += 1
        row["depth"] = depth


def own(rows):
    """Marks every slot own (a slot the parent lacks, or holds something else in) or
    inherited. A new slot that is empty is not own."""
    for row in rows:
        row["own"] = []
        if row["kind"] != "class":
            continue
        parent = rows[row["parent"]]
        inherited = parent["slots"] if parent["kind"] == "class" else []
        for k, name in enumerate(row["slots"]):
            row["own"].append(name != inherited[k] if k < len(inherited) else name != "0")


# --- the creators --------------------------------------------------------------

def read_text(text):
    """{function: [(address, mnemonic, operands), or (None, label, "") for a local label]}
    from asm/us/text.s."""
    out, current = {}, None
    for line in text.splitlines():
        m = LABEL.match(line)
        if m:
            current = out.setdefault(m.group(1), [])
            continue
        if current is None:
            continue
        m = LOCAL.match(line)
        if m:
            current.append((None, m.group(1), ""))
            continue
        m = INSN.match(line)
        if m:
            current.append((int(m.group(1), 16), m.group(2), m.group(3)))
    return out


CONST = re.compile(r"^\$a0, \$zero, (-?0x[0-9A-Fa-f]+|-?\d+)$")
WRITES_A0 = re.compile(r"^\$a0\b")
STORES = {"sb", "sh", "sw", "sd", "sq", "swc1", "sdc1"}
JUMPS = {"j", "b", "jr"}                       # no fall-through after their delay slot
CALLS = {"jal", "jalr"}
TARGET = re.compile(r"(\.L[0-9A-F]+)$")


def writes_a0(insn):
    """(True, constant or None) when insn sets $a0, else (False, None)."""
    _a, mnemonic, operands = insn
    if mnemonic in STORES or mnemonic.startswith("b") or not WRITES_A0.match(operands):
        return False, None
    m = CONST.match(operands)
    return True, (int(m.group(1), 0) if m and mnemonic in ("addiu", "daddiu", "ori") else None)


def a0_at(insns, pos, seen=None):
    """The constant $a0 holds when insns[pos] runs, or None: backwards through straight-line
    code, and at a local label through every way in (the fall-through and each branch to it,
    with its delay slot). None when a path sets it otherwise, calls, or reaches the entry."""
    seen = set() if seen is None else seen
    for j in range(pos - 1, -1, -1):
        insn = insns[j]
        if insn[0] is None:
            if j in seen:
                return "loop"
            seen.add(j)
            ways = []
            if j >= 2 and insns[j - 2][0] is not None and insns[j - 2][1] in JUMPS:
                pass                                 # the code before the label does not fall into it
            else:
                ways.append(a0_at(insns, j, seen))
            for b, other in enumerate(insns):
                if other[0] is not None and TARGET.search(other[2] or "") and \
                        TARGET.search(other[2]).group(1) == insn[1] and other[1] not in CALLS:
                    slot = insns[b + 1] if b + 1 < len(insns) else None
                    hit, number = writes_a0(slot) if slot and slot[0] is not None else (False, None)
                    ways.append(number if hit else a0_at(insns, b, seen))
            ways = [w for w in ways if w != "loop"]
            return ways[0] if ways and all(w == ways[0] for w in ways) else None
        if insn[1] in CALLS:
            return None
        hit, number = writes_a0(insn)
        if hit:
            return number
    return None


def a0_before(insns, k):
    """The constant in $a0 at the call insns[k], its delay slot included, or None."""
    if k + 1 < len(insns) and insns[k + 1][0] is not None:
        hit, number = writes_a0(insns[k + 1])
        if hit:
            return number
    return a0_at(insns, k)


def creators(text_insns, rows):
    """{class index: [function]}: the functions that call func_0011E580 with a constant id."""
    out = {}
    for func, insns in sorted(text_insns.items()):
        for k, insn in enumerate(insns):
            if insn[1] == "jal" and insn[2] == CREATE:
                cid = a0_before(insns, k)
                if cid is not None and 0 <= cid < len(rows):
                    out.setdefault(cid, [])
                    if func not in out[cid]:
                        out[cid].append(func)
    return out


# --- the tables ----------------------------------------------------------------

def write_classes(rows):
    lines = ["index\tdescriptor\tkind\tid\tparent\tdepth\tflags\tsize\twords\tslots\town\tnote\tmethods"]
    for r in rows:
        parent = "0x%02X" % r["parent"] if "parent" in r else "-"
        cid = "0x%X" % r["id"] if "id" in r else "-"
        if r["kind"] != "class":
            lines.append("0x%02X\t%08X\t%s\t%s\t%s\t%d\t-\t-\t%d\t0\t0\t-\t-" % (
                r["index"], r["address"], r["kind"], cid, parent, r["depth"], r["words"]))
            continue
        methods = " ".join(("+" if o else "") + n for n, o in zip(r["slots"], r["own"])) or "-"
        lines.append("0x%02X\t%08X\tclass\t%s\t%s\t%d\t0x%X\t0x%X\t%d\t%d\t%d\t%s\t%s" % (
            r["index"], r["address"], cid, parent, r["depth"], r["flags"], r["size"], r["words"],
            len(r["slots"]), sum(r["own"]), r["note"] or "-", methods))
    return OUT / "classes.tsv", "\n".join(lines) + "\n"


def methods(rows):
    """{function: ([own index@slot], [inherited index@slot])}."""
    out = {}
    for r in rows:
        for k, (operand, is_own) in enumerate(zip(r["slots"], r["own"])):
            name = operand
            if not name.startswith("func_"):
                continue
            entry = out.setdefault(name, ([], []))
            entry[0 if is_own else 1].append("0x%02X@0x%X" % (r["index"], 4 * (HEADER_WORDS + k)))
    return out


def write_methods(rows):
    # Which classes inherit a method is in classes.tsv (every slot of every class); this table
    # keeps where the function is the class's own and how many classes inherit it.
    lines = ["function\town\tinherited_by"]
    for name, (mine, theirs) in sorted(methods(rows).items()):
        lines.append("%s\t%s\t%d" % (name, " ".join(mine) or "-",
                                       len({m.split("@")[0] for m in theirs})))
    return OUT / "methods.tsv", "\n".join(lines) + "\n"


def write_creators(made):
    lines = ["index\tcreators"]
    for index in sorted(made):
        lines.append("0x%02X\t%s" % (index, " ".join(made[index])))
    return OUT / "creators.tsv", "\n".join(lines) + "\n"


def read_functions(path):
    return {line.split("\t")[0] for line in path.read_text().splitlines()[1:] if line}


def build(root=ROOT):
    data = sorted((root / "asm" / "us" / "data").glob("*.s"))
    if not data:
        raise SystemExit("error: asm/us/data/ is empty; run tools/setup_asm.py --version us")
    words, labels = read_data(p.read_text() for p in data)
    rows = descriptors(words, labels, read_functions(root / "config" / "us" / "functions.tsv"))
    made = creators(read_text((root / "asm" / "us" / "text.s").read_text()), rows)
    return rows, [write_classes(rows), write_methods(rows), write_creators(made)]


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args(argv)
    if not (ROOT / "asm" / "us" / "data").exists():
        if args.check:
            return 0
        print("error: asm/us/ is missing; run tools/setup_asm.py --version us")
        return 1
    _rows, outputs = build()
    stale = []
    for path, text in outputs:
        if args.check:
            if not path.exists() or path.read_text() != text:
                stale.append(path)
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text)
            print("wrote %s (%d rows)" % (path.relative_to(ROOT), text.count("\n") - 1))
    for p in stale:
        print("stale: %s" % p.relative_to(ROOT))
    return 1 if stale else 0


if __name__ == "__main__":
    sys.exit(main())
