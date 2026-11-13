# SPDX-License-Identifier: AGPL-3.0-or-later
"""Every function of a version's .text, and the pairing of PAL's with the US's.

    python3 tools/inventory.py --version us     # writes config/us/functions.tsv
    python3 tools/inventory.py --version eu     # writes config/eu/functions.tsv and config/eu/map.tsv
    python3 tools/inventory.py --check          # fails when a committed table is out of date

functions.tsv has one row per function splat found: its name, address, size,
kind (`code`, or `handwritten` where spimdisasm says so) and fingerprint. The
fingerprint is a short hash of the function's instructions with every
relocated field masked (call targets, %hi/%lo halves), so the same code at
another address has the same fingerprint. It holds no retail bytes.

map.tsv pairs each PAL function with its US counterpart by aligning the two
versions' fingerprints in address order: equal runs pair by fingerprint, a
run replaced by one of the same length pairs by position. Unpaired functions
are PAL's own. config/eu/map_fixes.tsv corrects the pairs position gets wrong
where PAL moved a function (`fixed`), each with retail's evidence.

Two steps correct what position gets wrong. A PAL function that moved (it sits elsewhere than
its US copy, so the alignment pairs its neighbours by position) is found by its code: when a
US function and a PAL function that are not paired by fingerprint have the same instructions,
relocated fields masked and the padding behind the last `jr` ignored, and no other function of
either version has them, they are a pair (`moved`), and the functions they were paired with by
position are unpaired. And a pair by position whose sizes differ more than SIZE_RATIO times is
no pair (a stripped function's 4-byte leftover is not the counterpart of a 644-byte function):
PAL's function is its own.

A last step, `similar`, pairs what is still unpaired on both sides: for each US function with
no counterpart, the unpaired PAL functions that lie between the PAL copies of its nearest paired
neighbours, of 0.6 to 1.6 times its size, are scored by the similarity of their instructions
(immediates, symbols and labels masked) and by the callees they share (PAL's mapped to US
names). A pair is made only when it clears SIMILAR_MIN and each side's best is the other, by a
margin over the runner-up (PAL's own changes, a wider layout or an extra call, change the bytes
and so the fingerprint, not the shape).

Reads asm/<version>/, which tools/setup_asm.py writes; --check reads only the
committed tables and the asm when it is there.
"""

import argparse
import collections
import difflib
import hashlib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
NONMATCHING = re.compile(r"^nonmatching (\S+), 0x([0-9A-Fa-f]+)")
INSN = re.compile(r"^\s*/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/\s+(\S+)\s*(.*)$")
RELOCATED = re.compile(r"%(hi|lo|gp_rel)\(|\bfunc_|\bD_|\bjtbl_")


def functions_from_asm(key):
    """[(name, address, size, kind, fingerprint)] in address order, from asm/<key>/."""
    out = []
    files = sorted((ROOT / "asm" / key).rglob("*.s"))
    if not files:
        raise SystemExit("error: asm/%s/ is empty; run tools/setup_asm.py --version %s" % (key, key))
    for path in files:
        text = path.read_text()
        if '.section .text' not in text[:1000]:
            continue  # data, rodata, bss: no functions
        current, words, handwritten, pending_hand = None, [], False, False

        def close():
            if current:
                h = hashlib.sha1(" ".join(words).encode()).hexdigest()[:16]
                out.append((current[0], current[1], current[2], "handwritten" if handwritten else "code", h))

        for line in text.splitlines():
            if line.startswith("/* Handwritten function */"):
                pending_hand = True
                continue
            m = NONMATCHING.match(line)
            if m:
                close()
                current = [m.group(1), None, int(m.group(2), 16)]
                words, handwritten, pending_hand = [], pending_hand, False
                continue
            m = INSN.match(line)
            if m and current is not None:
                vram, word, mnemonic, operands = int(m.group(1), 16), m.group(2), m.group(3), m.group(4)
                if current[1] is None:
                    current[1] = vram
                words.append(masked_word(m))               # opcode kept on a call, relocated fields masked
        close()
    out = [f for f in out if f[1] is not None]
    out.sort(key=lambda f: f[1])
    return out


def write_functions(key, funcs):
    path = ROOT / "config" / key / "functions.tsv"
    lines = ["name\taddress\tsize\tkind\tfingerprint"]
    lines += ["%s\t%08X\t%d\t%s\t%s" % (n, a, s, k, h) for n, a, s, k, h in funcs]
    return path, "\n".join(lines) + "\n"


def masked_word(m):
    """One instruction's word as the fingerprints hash it: relocated fields masked."""
    insn = int.from_bytes(bytes.fromhex(m.group(2)), "little")  # splat prints the bytes in file order
    if RELOCATED.search(m.group(4)):
        insn &= 0xFC000000 if m.group(3) in ("jal", "j") else 0xFFFF0000
    return "%08X" % insn


def core_fingerprints(key):
    """{name: hash of the function's masked instructions without the padding words behind them}:
    the same code, whatever the alignment after it (PAL pads functions differently)."""
    out, current, words = {}, None, []

    def close():
        if current:
            while words and words[-1] == "00000000":
                words.pop()
            out[current] = hashlib.sha1(" ".join(words).encode()).hexdigest()[:16]

    for path in sorted((ROOT / "asm" / key).rglob("*.s")):
        text = path.read_text()
        if ".section .text" not in text[:1000]:
            continue
        for line in text.splitlines():
            m = NONMATCHING.match(line)
            if m:
                close()
                current, words = m.group(1), []
                continue
            m = INSN.match(line)
            if m and current is not None:
                words.append(masked_word(m))
        close()
        current, words = None, []
    return out


def read_functions(key):
    path = ROOT / "config" / key / "functions.tsv"
    rows = []
    for line in path.read_text().splitlines()[1:]:
        n, a, s, k, h = line.split("\t")
        rows.append((n, int(a, 16), int(s), k, h))
    return rows


def pair(eu, us):
    """[(eu_row, us_row or None, how)], aligning the two versions' fingerprints in order.

    Runs of equal fingerprints pair as `fingerprint`; a run replaced by another
    of the same length pairs by position (`order`, or `order-size` where the
    sizes differ too); what is left is PAL's own (`none`).
    """
    matcher = difflib.SequenceMatcher(None, [r[4] for r in eu], [r[4] for r in us], autojunk=False)
    result = []
    for op, e0, e1, u0, u1 in matcher.get_opcodes():
        if op == "equal":
            result += [(eu[e0 + i], us[u0 + i], "fingerprint") for i in range(e1 - e0)]
        elif op == "replace" and e1 - e0 == u1 - u0:
            result += [(eu[e0 + i], us[u0 + i], "order" if eu[e0 + i][2] == us[u0 + i][2] else "order-size")
                       for i in range(e1 - e0)]
        else:
            result += [(r, None, "none") for r in eu[e0:e1]]
    return result


POSITION = ("none", "order", "order-size")    # the pairings position makes, which `moved` may correct
SIZE_RATIO = 4                                # how far apart a pair by position's sizes may be


def drop_implausible(pairs):
    """`pairs` without the pairs by position whose sizes differ more than SIZE_RATIO times."""
    return [(e, None, "none") if how in ("order", "order-size") and not (
        u[2] <= SIZE_RATIO * e[2] and e[2] <= SIZE_RATIO * u[2]) else (e, u, how) for e, u, how in pairs]


def moved(pairs, us, core_us, core_eu):
    """`pairs` with the functions that moved paired by their code (see the module docstring).
    core_us and core_eu are core_fingerprints' tables."""
    count_us, count_eu = collections.Counter(core_us.values()), collections.Counter(core_eu.values())
    movable_eu = {e[0]: i for i, (e, u, how) in enumerate(pairs) if how in POSITION}
    where_us = {u[0]: i for i, (e, u, how) in enumerate(pairs) if u}
    by_core = {core_eu[n]: n for n in movable_eu if n in core_eu and count_eu[core_eu[n]] == 1}
    found = []
    for u in us:
        i = where_us.get(u[0])
        if i is not None and pairs[i][2] not in POSITION:
            continue
        core = core_us.get(u[0])
        e_name = by_core.get(core) if core is not None and count_us[core] == 1 else None
        # A pair of two unpaired functions is `similar`'s to make; this step corrects position's pairs.
        if e_name and i != movable_eu[e_name] and (i is not None or pairs[movable_eu[e_name]][1]):
            found.append((movable_eu[e_name], u))
    out = list(pairs)
    for j, u in found:                                         # unpair what position paired with them
        out[j] = (out[j][0], None, "none")
        if u[0] in where_us:
            out[where_us[u[0]]] = (out[where_us[u[0]]][0], None, "none")
    for j, u in found:
        out[j] = (out[j][0], u, "moved")
    return out


SIMILAR_MIN = 0.6        # instruction similarity a pair needs
SIMILAR_MARGIN = 0.05    # how far the best candidate must lead the runner-up, on both sides
SIMILAR_SIZE = (0.6, 1.6)
MASK = re.compile(r"0x[0-9A-Fa-f]+|-?\b\d+\b|\b(?:func|D|jtbl)_\w+|\.L\w+|%(?:hi|lo|gp_rel)\([^)]*\)")


def bodies_from_asm(key):
    """{name: ([normalised instruction], [callee name])} from asm/<key>/: each instruction is its
    mnemonic and operands with immediates, symbols and labels masked."""
    out = {}
    for path in sorted((ROOT / "asm" / key).rglob("*.s")):
        text = path.read_text()
        if ".section .text" not in text[:1000]:
            continue
        cur = None
        for line in text.splitlines():
            m = NONMATCHING.match(line)
            if m:
                cur = out[m.group(1)] = ([], [])
                continue
            m = INSN.match(line)
            if m and cur is not None:
                mnemonic, operands = m.group(3), m.group(4)
                cur[0].append(mnemonic + " " + MASK.sub("N", operands))
                if mnemonic == "jal":
                    cur[1].append(operands.strip())
    return out


def similar(pairs, us, eu_body, us_body):
    """`pairs` with the clear one-to-one matches among the functions still unpaired added as
    `similar` (see the module docstring), in rounds until none is added: a pair made in one round
    resolves callees for the next. `us` is the US function rows; eu_body and us_body are
    bodies_from_asm's tables."""
    by_name = {u[0]: u for u in us}
    order = sorted(us, key=lambda r: r[1])
    out = list(pairs)
    while True:
        added = _similar_round(out, order, by_name, eu_body, us_body)
        if not added:
            return out
        for i, u in added.items():
            out[i] = (out[i][0], u, "similar")


def _similar_round(pairs, order, by_name, eu_body, us_body):
    """{index in pairs: US row} for this round's clear matches."""
    paired = {u[0]: e for e, u, _ in pairs if u}
    eu_to_us = {e[0]: u[0] for e, u, _ in pairs if u}
    eu_addr = {e[0]: e[1] for e, _, _ in pairs}
    free_eu = [i for i, (e, u, _) in enumerate(pairs) if not u]
    # PAL window of each unpaired US function: between its paired neighbours' PAL copies.
    lows, window, prev, nxt = {}, {}, None, None
    for u in order:
        if u[0] in paired:
            prev = eu_addr[paired[u[0]][0]]
        else:
            lows[u[0]] = prev
    for u in reversed(order):
        if u[0] in paired:
            nxt = eu_addr[paired[u[0]][0]]
        else:
            window[u[0]] = (lows[u[0]], nxt)

    def score(u, e):
        ub, ucalls = us_body.get(u[0], ([], []))
        eb, ecalls = eu_body.get(e[0], ([], []))
        if not ub or not eb:
            return 0.0
        # Only callees both versions resolve count: a callee still unpaired on either side says nothing.
        ecalls = [u[0] if c == e[0] else eu_to_us[c] for c in ecalls if c == e[0] or c in eu_to_us]
        ucalls = [c for c in ucalls if c == u[0] or c in paired]
        common = sum((collections.Counter(ucalls) & collections.Counter(ecalls)).values())
        if (ucalls or ecalls) and common * 2 < min(len(ucalls), len(ecalls)):
            return 0.0
        return difflib.SequenceMatcher(None, ub, eb, autojunk=False).ratio()

    scores = {}
    for u in order:
        if u[0] in paired:
            continue
        lo, hi = window[u[0]]
        for i in free_eu:
            e = pairs[i][0]
            if (lo is not None and e[1] <= lo) or (hi is not None and e[1] >= hi):
                continue
            if not SIMILAR_SIZE[0] * u[2] <= e[2] <= SIMILAR_SIZE[1] * u[2] + 16:
                continue
            sc = score(u, e)
            if sc >= SIMILAR_MIN:
                scores[(u[0], i)] = sc
    by_us, by_eu = collections.defaultdict(list), collections.defaultdict(list)
    for (un, i), sc in scores.items():
        by_us[un].append((sc, i))
        by_eu[i].append((sc, un))

    def leads(rows, key):
        rows = sorted(rows, reverse=True)
        return rows[0][1] == key and (len(rows) == 1 or rows[0][0] - rows[1][0] >= SIMILAR_MARGIN)

    return {i: by_name[un] for (un, i) in sorted(scores) if leads(by_us[un], i) and leads(by_eu[i], un)}


FIXES = ROOT / "config" / "eu" / "map_fixes.tsv"


def apply_fixes(pairs, us, fixes=None):
    """`pairs` with the pairings config/eu/map_fixes.tsv corrects: where PAL moved a function,
    position pairs the wrong ones, and retail's callers and strings show the right ones (`fixed`).
    A US function may end up paired once only."""
    if fixes is None:
        fixes = {}
        if FIXES.exists():
            for line in FIXES.read_text().splitlines()[1:]:
                if line.strip() and not line.startswith("#"):
                    eu_name, us_name = line.split("\t")[:2]
                    fixes[eu_name] = us_name
    by_name = {r[0]: r for r in us}
    out = [(e, by_name[fixes[e[0]]], "fixed") if e[0] in fixes else (e, u, how) for e, u, how in pairs]
    seen = [u[0] for _, u, _ in out if u]
    twice = sorted({n for n in seen if seen.count(n) > 1})
    if twice:
        raise SystemExit("error: config/eu/map_fixes.tsv pairs %s twice" % ", ".join(twice))
    return out


def write_map(pairs):
    path = ROOT / "config" / "eu" / "map.tsv"
    lines = ["eu_name\teu_address\tsize\tus_name\tus_address\thow"]
    for e, u, how in pairs:
        lines.append("%s\t%08X\t%d\t%s\t%s\t%s" % (e[0], e[1], e[2], u[0] if u else "-", "%08X" % u[1] if u else "-", how))
    return path, "\n".join(lines) + "\n"


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--version", choices=["us", "eu"])
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args(argv)

    stale = []
    for key in ([args.version] if args.version else ["us", "eu"]):
        if not (ROOT / "asm" / key).exists():
            if not args.check:
                print("error: asm/%s/ is missing; run tools/setup_asm.py --version %s" % (key, key))
                return 1
            continue
        outputs = [write_functions(key, functions_from_asm(key))]
        if key == "eu":
            us_funcs = functions_from_asm("us")
            pairs = apply_fixes(pair(functions_from_asm("eu"), us_funcs), us_funcs)
            pairs = moved(drop_implausible(pairs), us_funcs, core_fingerprints("us"), core_fingerprints("eu"))
            pairs = similar(pairs, us_funcs, bodies_from_asm("eu"), bodies_from_asm("us"))
            outputs.append(write_map(pairs))
        for path, text in outputs:
            if args.check:
                if not path.exists() or path.read_text() != text:
                    stale.append(path.relative_to(ROOT))
            else:
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(text)
                print("wrote %s (%d rows)" % (path.relative_to(ROOT), text.count("\n") - 1))
    for p in stale:
        print("stale: %s" % p)
    return 1 if stale else 0


if __name__ == "__main__":
    sys.exit(main())
