# SPDX-License-Identifier: AGPL-3.0-or-later
"""Compile C++ and compare one function with retail, byte for byte.

    python3 tools/check.py FILE.cpp FUNC [FUNC ...] [--version us|eu] [--diff]

FUNC is the function's name in config/<version>/functions.tsv or
config/us/symbol_addrs.txt (func_0011A338, or the name we gave it). The file
is compiled with its flags (config/cflags.tsv), the function is found in the
object (its C++ mangled name starts with FUNC), and every relocation in it is
resolved to the address it has in the version: calls and data by name, a
literal in the object's .rodata by checking that retail's own constant at the
address retail uses holds the same bytes. Then the words are compared with
retail's, and the bytes after the function up to the next one must be
padding.

Prints EXACT, or DIFFER with both disassemblies side by side (--diff shows
them for EXACT too). With --version eu the function is checked at its PAL
counterpart (config/eu/map.tsv), with every address translated to PAL's. A
file of src/versions/eu/ (tools/version_src.py) is checked in PAL, built in
its shared file's unit; --unit SHARED.cpp does the same for a definition kept
anywhere else (a worker's folder).

A function that uses a .rodata literal of its own (a float or a string written in C) is EXACT here
and marked `rodata`: the literal, for as many bytes as the instruction reaches (a string, up to its
NUL), is compared with retail's, and the build links it by baking retail's address into the code
(tools/rodata.py). A constant can also be read through an extern (extern f32 D_00219718[]): the
object then has no .rodata, and the relocation reaches retail's address by name.
"""

import argparse
import bisect
import json
import re
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import compile as cc  # noqa: E402
import elf  # noqa: E402
import version_src  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
VERSION_NAME = re.compile(r"^(?:func|D|jtbl)_([a-z]+)_([0-9A-Fa-f]{8})(?:__|$)")  # func_eu_00138718
ADDR_NAME = re.compile(r"^(?:func|D|jtbl|L)_([0-9A-Fa-f]{6,8})(?:__|$)")
LOAD_ADDRESS = 0x100000  # where the executable starts, in every version
SYMBOL_LINE = re.compile(r"^\s*([^\s=]+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;")


def load_functions(key):
    rows = {}
    path = ROOT / "config" / key / "functions.tsv"
    for line in path.read_text().splitlines()[1:]:
        name, addr, size, kind, _ = line.split("\t")
        rows[name] = (int(addr, 16), int(size), kind)
    return rows


def load_libcalls(key):
    """{libcall name: address}: the soft-float routines the compiler calls by name (config/<version>/libcalls.tsv)."""
    path = ROOT / "config" / key / "libcalls.tsv"
    if not path.exists():
        return {}
    functions = load_functions(key)
    out = {}
    for line in path.read_text().splitlines()[1:]:
        name, function = line.split("\t")[:2]
        out[name] = functions[function][0]
    return out


def load_symbols(key):
    out = load_libcalls(key)
    path = ROOT / "config" / key / "symbol_addrs.txt"
    if path.exists():
        for line in path.read_text().splitlines():
            m = SYMBOL_LINE.match(line)
            if m:
                out[m.group(1)] = int(m.group(2), 16)
    return out


def base_name(sym):
    """func_0011A338__FP5Stacki -> func_0011A338; Push__5Stacki -> Push (a free function's base)."""
    return sym.split("__", 1)[0] if "__" in sym[1:] else sym


class Resolver:
    """Names and addresses of the US build, translated to another version's when asked."""

    def __init__(self, key):
        self.key = key
        self.functions = load_functions("us")
        self.symbols = load_symbols("us")
        self.translation = translation(key) if key != "us" else None
        self.paired = None

    def us_address(self, sym):
        if sym in self.symbols:
            return self.symbols[sym]
        if sym in self.functions:
            return self.functions[sym][0]
        b = base_name(sym)
        if b in self.symbols:
            return self.symbols[b]
        if b in self.functions:
            return self.functions[b][0]
        m = ADDR_NAME.match(sym)
        if m:
            return int(m.group(1), 16)
        return None

    def address(self, sym):
        m = VERSION_NAME.match(sym)
        if m:
            # Code or data only one version has (tools/version_src.py): its own address, there alone.
            return int(m.group(2), 16) if m.group(1) == self.key else None
        a = self.us_address(sym)
        if a is None or self.translation is None:
            return a
        if a in self.translation:
            return self.translation[a]
        if a < LOAD_ADDRESS:
            return a    # an absolute address below the executable (D_00000FA0) is the same in every version
        return self.inside(a)

    def inside(self, a):
        """The address of a byte inside a paired datum: the datum's own, plus the same offset.

        Only when the offset stays short of the next paired address in both versions. A wrong
        guess cannot pass: a function is EXACT only when the version's own code holds the address.
        """
        if self.paired is None:
            self.paired = sorted(self.translation)
        i = bisect.bisect_right(self.paired, a) - 1
        if i < 0 or i + 1 >= len(self.paired):
            return None
        lo, hi = self.paired[i], self.paired[i + 1]
        if self.translation[lo] + (a - lo) < self.translation[hi]:
            return self.translation[lo] + (a - lo)
        return None


def translation(key):
    """US address -> the version's, for every function and every datum paired code refers to."""
    cache = ROOT / "build" / key / "translation.json"
    sources = [ROOT / "config" / key / "map.tsv", ROOT / "asm" / "us" / "text.s", ROOT / "asm" / key / "text.s"]
    if cache.exists() and all(cache.stat().st_mtime >= s.stat().st_mtime for s in sources if s.exists()):
        return {int(k): v for k, v in json.loads(cache.read_text()).items()}
    pairs = {}
    rows = [l.split("\t") for l in (ROOT / "config" / key / "map.tsv").read_text().splitlines()[1:]]
    bodies_us, bodies_v = operand_symbols("us"), operand_symbols(key)
    for eu_name, eu_addr, size, us_name, us_addr, how in rows:
        if us_name == "-":
            continue
        pairs[int(us_addr, 16)] = int(eu_addr, 16)
        if how == "fingerprint":
            for a, b in zip(bodies_us.get(us_name, []), bodies_v.get(eu_name, [])):
                if a is not None and b is not None:
                    pairs.setdefault(a, b)
    # Functions paired by their order give their data too, when every instruction lines up: the same
    # count, and an address in the same places. The fingerprint pairs above come first.
    for eu_name, eu_addr, size, us_name, us_addr, how in rows:
        if us_name == "-" or how == "fingerprint":
            continue
        a_ops, b_ops = bodies_us.get(us_name, []), bodies_v.get(eu_name, [])
        if len(a_ops) == len(b_ops) and [a is None for a in a_ops] == [b is None for b in b_ops]:
            for a, b in zip(a_ops, b_ops):
                if a is not None:
                    pairs.setdefault(a, b)
    cache.parent.mkdir(parents=True, exist_ok=True)
    cache.write_text(json.dumps(pairs))
    return pairs


def operand_symbols(key):
    """{function: [address named in each instruction's operands, or None]} from asm/<key>/text.s."""
    out, current = {}, None
    sym = re.compile(r"\b(?:func|D|jtbl)_([0-9A-F]{6,8})\b")
    for line in (ROOT / "asm" / key / "text.s").read_text().splitlines():
        if line.startswith("nonmatching "):
            current = line.split()[1].rstrip(",")
            out[current] = []
        elif current and line.lstrip().startswith("/*"):
            m = sym.search(line.split("*/", 1)[1])
            out[current].append(int(m.group(1), 16) if m else None)
    return out


def retail_image(key):
    return elf.Elf(versions.boot_path(key).read_bytes())


def target_of(key, name):
    """(address, size) of FUNC in the version."""
    us = load_functions("us")
    symbols = load_symbols("us")
    if name in us:
        addr, size, _ = us[name]
    elif name in symbols:
        addr = symbols[name]
        size = next((s for a, s, _ in us.values() if a == addr), None)
    else:
        raise KeyError("%s is not in config/us/functions.tsv or config/us/symbol_addrs.txt" % name)
    if key == "us":
        return addr, size
    for line in (ROOT / "config" / key / "map.tsv").read_text().splitlines()[1:]:
        eu_name, eu_addr, eu_size, us_name, us_addr, how = line.split("\t")
        if us_addr != "-" and int(us_addr, 16) == addr:
            return int(eu_addr, 16), int(eu_size)
    raise KeyError("%s has no counterpart in config/%s/map.tsv" % (name, key))


LOAD_WIDTH = {0x20: 1, 0x24: 1, 0x21: 2, 0x25: 2, 0x23: 4, 0x27: 4, 0x31: 4, 0x35: 8, 0x37: 8, 0x1E: 16}


def literal_width(insn, section, start):
    """How many bytes of a .rodata literal the instruction at its %lo reaches.

    A load or store says: 1, 2, 4, 8 or 16. An address (addiu) is a string, which is read up to
    and including its terminating NUL.
    """
    op = insn >> 26
    if op == 0x09:
        end = section.find(b"\0", start)
        return (end + 1 - start) if end >= 0 else len(section) - start + 1
    return LOAD_WIDTH.get(op, 4)


def jump_table(obj, index, start, resolver):
    """A jump table in .rodata at `start`, as retail would hold it: the address of each case label.

    The words are R_MIPS_32 relocations against the function sections (content = offset). Returns the
    run of consecutive words from `start` that point into one function, or None if there is no relocation at `start`.
    """
    words = {}
    for off, rtype, rsym in obj.relocations(obj.sections[index]["name"]):
        if rtype == elf.R_MIPS_32 and rsym["type"] == elf.STT_SECTION:
            words[off] = rsym
    if start not in words:
        return None
    section, out, at = obj.contents(obj.sections[index]), b"", start
    first = words[start]["shndx"]
    while at in words and words[at]["shndx"] == first:      # a table belongs to one function
        name = obj.sections[words[at]["shndx"]]["name"]
        base = resolver.address(name[len(".text."):]) if name.startswith(".text.") else None
        if base is None:
            return None
        out += (base + int.from_bytes(section[at:at + 4], "little")).to_bytes(4, "little")
        at += 4
    return out


def s16(x):
    return x - 0x10000 if x & 0x8000 else x


def check_function(obj, name, key, resolver, image):
    """A result dict: status EXACT / DIFFER / ERROR, the words, notes."""
    code_sections = {sec["index"] for sec in obj.sections if sec["name"].startswith(".text")}
    funcs = [s for s in obj.symbols if s["type"] == elf.STT_FUNC and s["shndx"] in code_sections]
    found = [s for s in funcs if s["name"] == name or base_name(s["name"]) == name]
    if not found:
        return {"status": "ERROR", "note": "no function named %s in the object (it has: %s)"
                % (name, ", ".join(s["name"] for s in funcs) or "none")}
    sym = found[0]
    text = obj.sections[sym["shndx"]]
    addr, size = target_of(key, name)
    code = bytearray(obj.contents(text)[sym["value"]:sym["value"] + sym["size"]])
    n = len(code)
    retail = image.read_vaddr(addr, max(size or 0, n))
    words = lambda b, i: int.from_bytes(b[i:i + 4], "little")
    notes, uses_rodata = [], False
    relocs = sorted((r for r in obj.relocations(text["name"]) if sym["value"] <= r[0] < sym["value"] + n),
                    key=lambda r: r[0])

    def target(rsym, addend_bits):
        """The address a relocated field reaches, or None: by name, or for a section symbol by its function."""
        if rsym["type"] == elf.STT_SECTION and rsym["shndx"] < len(obj.sections):
            secname = obj.sections[rsym["shndx"]]["name"]
            if secname.startswith(".text."):
                base = resolver.address(secname[len(".text."):])
                return None if base is None else base + addend_bits
            return None
        t = resolver.address(rsym["name"])
        return None if t is None else t + addend_bits

    # Every relocation is resolved first, so that a difference shows real addresses. A HI16 waits
    # for the next LO16 of its symbol; every HI16 pending for that symbol takes that LO16's address,
    # as the GNU linker pairs them. A later LO16 without a pending HI16 reuses the last pairing's.
    pending, last_hi, last_full, forward, failure = {}, {}, {}, {}, None
    for n_reloc, (offset, rtype, rsym) in enumerate(relocs):
        i = offset - sym["value"]
        insn = words(code, i)
        key_sym = (rsym["name"], rsym["shndx"])
        in_rodata = rsym["shndx"] not in (elf.SHN_UNDEF,) and rsym["shndx"] < len(obj.sections) \
            and obj.sections[rsym["shndx"]]["name"].startswith(".rodata")
        if rtype == elf.R_MIPS_26:
            t = target(rsym, (insn & 0x3FFFFFF) << 2)
            if t is None:
                failure = failure or "a call to %s, which has no address in this version" % rsym["name"]
                continue
            code[i:i + 4] = ((insn & 0xFC000000) | ((t >> 2) & 0x3FFFFFF)).to_bytes(4, "little")
        elif rtype == elf.R_MIPS_HI16:
            if i in forward:
                # Its %lo came first and has formed the address already.
                hi_insn = words(code, i)
                code[i:i + 4] = ((hi_insn & 0xFFFF0000) | (((forward.pop(i) + 0x8000) >> 16) & 0xFFFF)).to_bytes(4, "little")
            else:
                pending.setdefault(key_sym, []).append(i)
        elif rtype == elf.R_MIPS_LO16:
            his = pending.pop(key_sym, None)
            if his:
                hi_addend = (words(code, his[0]) & 0xFFFF) << 16
                last_hi[key_sym] = (his, hi_addend)
            else:
                his, hi_addend = last_hi.get(key_sym, ([], 0))
            ahead = None
            if not his:
                # A %lo before its %hi (the lui sits later, in a loop's delay slot): pair it with the next one.
                ahead = next((o2 - sym["value"] for o2, t2, s2 in relocs[n_reloc + 1:]
                              if t2 == elf.R_MIPS_HI16 and (s2["name"], s2["shndx"]) == key_sym), None)
                if ahead is not None:
                    hi_addend = (words(code, ahead) & 0xFFFF) << 16
            addend = hi_addend + s16(insn & 0xFFFF)
            if in_rodata:
                # Retail's own constant: read the address retail's hi/lo pair forms and compare the bytes.
                r_hi = (words(retail, his[0]) & 0xFFFF) << 16 if his else \
                    ((words(retail, ahead) & 0xFFFF) << 16 if ahead is not None else 0)
                full = r_hi + s16(words(retail, i) & 0xFFFF)
                section = obj.contents(obj.sections[rsym["shndx"]])
                start = addend + rsym["value"]
                width = literal_width(insn, section, start)
                lit = section[start:start + width]
                table = jump_table(obj, rsym["shndx"], start, resolver)
                if table is not None:
                    lit, width = table, len(table)
                try:
                    theirs = image.read_vaddr(full, len(lit))
                except ValueError:
                    theirs = None
                if theirs != lit or len(lit) != width:
                    failure = failure or "the .rodata literal at +0x%X is not retail's constant at 0x%X" % (addend, full)
                uses_rodata = True
            else:
                t = target(rsym, 0)
                if t is None:
                    failure = failure or "a reference to %s, which has no address in this version" % rsym["name"]
                    continue
                full = t + addend
            last_full[key_sym] = full
            if ahead is not None:
                forward[ahead] = full
            for h in his:
                hi_insn = words(code, h)
                code[h:h + 4] = ((hi_insn & 0xFFFF0000) | (((full + 0x8000) >> 16) & 0xFFFF)).to_bytes(4, "little")
            code[i:i + 4] = ((insn & 0xFFFF0000) | (full & 0xFFFF)).to_bytes(4, "little")
        elif rtype == elf.R_MIPS_32:
            failure = failure or "a 32-bit relocation in code (a jump table?): not supported yet"
        else:
            failure = failure or "relocation type %d is not supported yet" % rtype
    # A %hi whose %lo came earlier (a lui in a loop's delay slot) takes the address that %lo formed.
    for key_sym in list(pending):
        if key_sym in last_full:
            for h in pending.pop(key_sym):
                hi_insn = words(code, h)
                code[h:h + 4] = ((hi_insn & 0xFFFF0000) | (((last_full[key_sym] + 0x8000) >> 16) & 0xFFFF)).to_bytes(4, "little")
    if pending:
        failure = failure or "a %%hi without its %%lo (%s)" % ", ".join(k[0] for k in pending)
    shown = {"ours": bytes(code), "retail": retail, "address": addr}
    if failure and failure.startswith(("a call", "a reference", "a 32-bit", "relocation", "a %hi")):
        return dict(shown, status="ERROR", note=failure)
    if failure:
        return dict(shown, status="DIFFER", note=failure)
    if size is not None and n > size:
        return dict(shown, status="DIFFER", note="the C is %d bytes, retail's function %d" % (n, size))
    retail = retail[:size] if size else retail[:n]
    if uses_rodata:
        notes.append("rodata")
    status = "EXACT" if bytes(code) == retail[:n] and not any(retail[n:]) else "DIFFER"
    if status == "DIFFER" and bytes(code) == retail[:n]:
        notes.append("retail has %d more bytes of code after it" % (len(retail) - n))
    return {"status": status, "note": ", ".join(notes), "ours": bytes(code), "retail": retail, "address": addr}


def disassemble(data, addr):
    with tempfile.NamedTemporaryFile(suffix=".bin") as f:
        f.write(data)
        f.flush()
        out = subprocess.run(["mips-linux-gnu-objdump", "-D", "-b", "binary", "-m", "mips:5900", "-EL",
                              "--adjust-vma=0x%X" % addr, f.name], capture_output=True, text=True).stdout
    lines = []
    for line in out.splitlines():
        m = re.match(r"^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)$", line)
        if m:
            lines.append((m.group(2), m.group(3).replace("\t", " ")))
    return lines


def show(result):
    ours, retail = disassemble(result["ours"], result["address"]), disassemble(result["retail"], result["address"])
    width = 44
    print("    %-*s   %s" % (width, "ours", "retail"))
    for i in range(max(len(ours), len(retail))):
        a = ours[i] if i < len(ours) else ("", "")
        b = retail[i] if i < len(retail) else ("", "")
        mark = " " if a[0] == b[0] else "*"
        print("  %s %-*s   %s" % (mark, width, (a[0] + " " + a[1]).strip()[:width], (b[0] + " " + b[1]).strip()))


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("src")
    parser.add_argument("funcs", nargs="+")
    parser.add_argument("--version", default="us", choices=["us", "eu"])
    parser.add_argument("--flags", help="override the file's flags (to explore only: matches count with its own)")
    parser.add_argument("--diff", action="store_true", help="show the disassembly for EXACT too")
    parser.add_argument("--unit", metavar="SHARED.cpp",
                        help="FILE is a version's own definition of FUNC, kept elsewhere: build it in SHARED's unit")
    args = parser.parse_args(argv)

    own = version_src.version_of(args.src)
    if args.unit:
        own = (args.version if args.version != "us" else "eu", Path(args.unit).resolve())
    if own and args.version == "us":
        args.version = own[0]       # a version's own definition is checked in that version
    with tempfile.TemporaryDirectory(prefix="sly1-check-") as tmp:
        out = Path(tmp) / "unit.o"
        try:
            if own:
                # Built in its shared file's unit, in place of the shared definition.
                trying = {f: Path(args.src).resolve() for f in args.funcs} if args.unit else None
                path, _ = version_src.unit(own[1], own[0], trying)
                cc.compile_file(path, out, args.flags.split() if args.flags else cc.flags_for(own[1]))
            else:
                cc.compile_file(args.src, out, args.flags.split() if args.flags else None)
        except cc.CompileError as e:
            print("ERROR: does not compile:\n%s" % e)
            return 2
        obj = elf.Elf(out.read_bytes())
    image = retail_image(args.version)
    resolver = Resolver(args.version)
    worst = 0
    for name in args.funcs:
        try:
            r = check_function(obj, name, args.version, resolver, image)
        except KeyError as e:
            r = {"status": "ERROR", "note": str(e).strip("'\"")}
        print("%s: %s %s%s" % (r["status"], name, args.version, (" (%s)" % r["note"]) if r.get("note") else ""))
        if "ours" in r and (r["status"] != "EXACT" or args.diff):
            show(r)
        worst = max(worst, {"EXACT": 0, "DIFFER": 1, "ERROR": 2}[r["status"]])
    return worst


if __name__ == "__main__":
    sys.exit(main())
