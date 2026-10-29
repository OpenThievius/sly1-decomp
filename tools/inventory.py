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
are PAL's own.

Reads asm/<version>/, which tools/setup_asm.py writes; --check reads only the
committed tables and the asm when it is there.
"""

import argparse
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
                insn = int.from_bytes(bytes.fromhex(word), "little")  # splat prints the bytes in file order
                if RELOCATED.search(operands):
                    if mnemonic in ("jal", "j"):
                        insn &= 0xFC000000                    # opcode kept, 26-bit target masked
                    else:
                        insn &= 0xFFFF0000                    # %hi/%lo immediate masked
                words.append("%08X" % insn)
        close()
    out = [f for f in out if f[1] is not None]
    out.sort(key=lambda f: f[1])
    return out


def write_functions(key, funcs):
    path = ROOT / "config" / key / "functions.tsv"
    lines = ["name\taddress\tsize\tkind\tfingerprint"]
    lines += ["%s\t%08X\t%d\t%s\t%s" % (n, a, s, k, h) for n, a, s, k, h in funcs]
    return path, "\n".join(lines) + "\n"


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
            outputs.append(write_map(pair(functions_from_asm("eu"), functions_from_asm("us"))))
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
