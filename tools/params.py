# SPDX-License-Identifier: AGPL-3.0-or-later
"""Find declarations whose parameters disagree with the function's C definition.

    python3 tools/params.py                         # every function whose declarations disagree
    python3 tools/params.py --file main/player.cpp  # only the declarations in one file (or a few)
    python3 tools/params.py --summary               # the counts only
    python3 tools/params.py --version eu            # PAL's units

GCC 2.95 mangles a C++ function's parameter types into its symbol (`func_0018A388__FP10World2Boss`),
and the build links each `func_XXXXXXXX` by its address whatever the mangling (tools/build.py), so a
declaration whose parameters differ from the definition's still links and the build still matches.
A port links normally, so there every declaration has to agree with the definition. This tool reads
the symbols of the objects of the last full build (build/us/src/, `nm`; run tools/build.py after a
change), so it sees the declarations a file uses (a call, an address taken); one nothing uses
leaves no symbol and is not reported. PAL's build links assembly and has no C objects: with
`--version eu` the files with PAL definitions of their own (src/versions/eu/) are compiled in their
shared file's unit (tools/version_src.py) and take their US object's place.

Each function is reported with its definition's parameters (or every spelling, when it has no C
definition: original assembly) and each file whose spelling differs, with the kind of difference
(a spelling may show several; the summary counts each kind once per file and spelling):

    count       a different number of parameters
    linkage     C linkage (`extern "C"`, no parameters in the symbol) against C++
    ptr/int     a pointer (or reference, or function pointer) where the other has an integer
    void*       `void*` against a typed pointer
    pointee     pointers to different types
    scalar      different scalar types (signedness, width, float against integer)
    order       the same float parameters at other positions: the same registers on the EE, which
                passes floats and the rest each in their own registers, so only the order the
                caller evaluates its arguments in tells them apart (the other kinds are then
                those of the remaining parameters)

A top-level `const` of a parameter passed by value is not part of the type and is ignored. A file
may declare a function two ways (C++ overloading keeps both): each spelling is its own row.
"""

import argparse
import collections
import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import symbols  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
SYMBOL = re.compile(r"^(func_(?:[a-z]+_)?[0-9A-F]{8})(?:__F(.*))?$")
DEFINED = set("TtWw")

BUILTIN = {"i": "int", "c": "char", "s": "short", "l": "long", "x": "long long", "f": "float",
           "d": "double", "v": "void", "b": "bool", "w": "wchar_t", "r": "long double", "e": "..."}
QUALIFIER = {"C": "const ", "V": "volatile ", "U": "unsigned ", "S": "signed "}


class DemangleError(ValueError):
    pass


class _Reader:
    def __init__(self, text):
        self.text, self.i, self.seen = text, 0, []

    def peek(self):
        if self.i >= len(self.text):
            raise DemangleError("unexpected end of %r" % self.text)
        return self.text[self.i]

    def number(self):
        start = self.i
        while self.i < len(self.text) and self.text[self.i].isdigit():
            self.i += 1
        if start == self.i:
            raise DemangleError("a number expected at %d of %r" % (start, self.text))
        return int(self.text[start:self.i])

    def count(self):
        """One digit, or several followed by '_' (GCC 2.95's back-reference counts and indexes)."""
        if not self.peek().isdigit():
            raise DemangleError("a count expected at %d of %r" % (self.i, self.text))
        j = self.i
        while j < len(self.text) and self.text[j].isdigit():
            j += 1
        if j - self.i > 1 and j < len(self.text) and self.text[j] == "_":
            n, self.i = int(self.text[self.i:j]), j + 1
            return n
        self.i += 1
        return int(self.text[self.i - 1])

    def back(self, n):
        if n >= len(self.seen):
            raise DemangleError("a reference to parameter %d of %r" % (n, self.text))
        return self.seen[n]

    def name(self):
        n = self.number()
        out = self.text[self.i:self.i + n]
        if len(out) != n:
            raise DemangleError("a name runs past the end of %r" % self.text)
        self.i += n
        return out

    def type(self):
        """A type's text; a function type comes back as FUNCTION + 'ret(*)(args)' until a pointer takes it."""
        quals = ""
        while True:
            c = self.peek()
            if c in QUALIFIER:
                quals += QUALIFIER[c]
                self.i += 1
                continue
            self.i += 1
            if c in "PR":
                inner = self.type()
                if inner.startswith(FUNCTION):
                    inner = inner[len(FUNCTION):]
                    return inner if c == "P" else inner.replace("(*)", "(&)", 1)
                out = inner + ("*" if c == "P" else "&")
                return out + " " + quals.strip() if quals else out     # a const pointer: T* const
            if c == "A":
                n = self.number()
                if self.peek() != "_":
                    raise DemangleError("an array without its '_' in %r" % self.text)
                self.i += 1
                return quals + self.type() + "[%d]" % (n + 1)
            if c == "F":
                args = []
                while self.peek() != "_":
                    args.append(self.type())
                self.i += 1
                ret = self.type()
                return FUNCTION + quals + "%s(*)(%s)" % (ret, ", ".join(args))
            if c == "Q":
                if self.peek() == "_":
                    self.i += 1
                    n = self.number()
                    self.i += 1
                else:
                    n = int(self.peek())
                    self.i += 1
                return quals + "::".join(self.name() for _ in range(n))
            if c == "T":            # the same type as parameter n
                return quals + self.back(self.count())
            if c == "G":            # a class passed by value
                return quals + self.type()
            if c.isdigit():
                self.i -= 1
                return quals + self.name()
            if c == "I":            # a sized integer (mode(TI): u128): I, its width in hex
                if self.peek() == "_":
                    end = self.text.index("_", self.i + 1)
                    width, self.i = self.text[self.i + 1:end], end + 1
                else:
                    width, self.i = self.text[self.i:self.i + 2], self.i + 2
                return quals + "int%d" % int(width, 16)
            if c in BUILTIN:
                return quals + BUILTIN[c]
            raise DemangleError("unknown type code %r in %r" % (c, self.text))


FUNCTION = "\0fn:"


def demangle(params):
    """[type text] of a GCC 2.95 mangled parameter list (what follows `__F`); `v` alone is ()."""
    if params == "v":
        return []
    r = _Reader(params)
    while r.i < len(params):
        c = r.peek()
        if c == "N":                # count repeats of parameter n
            r.i += 1
            count = r.count()
            index = r.count()
            r.seen += [r.back(index)] * count
        else:
            t = r.type()
            r.seen.append(t[len(FUNCTION):] if t.startswith(FUNCTION) else t)
    return r.seen


def by_value(t):
    """A parameter's type without the top-level const of a value parameter (not part of the type)."""
    if t.endswith("* const"):
        return t[:-len(" const")]
    if t.startswith("const ") and not t.endswith(("*", "&", ")")):
        return t[len("const "):]
    return t


def is_pointer(t):
    return t.endswith(("*", "&")) or "(*)" in t


def kinds(a, b):
    """The kinds of difference between two parameter lists (None for C linkage)."""
    if a is None or b is None:
        return {"linkage"}
    if len(a) != len(b):
        return {"count"}
    out = set()
    fa, fb = [i for i, t in enumerate(a) if t == "float"], [i for i, t in enumerate(b) if t == "float"]
    if fa != fb and len(fa) == len(fb):
        # The EE passes floats in $f12.. and the rest in $a0.., each in its own order: the same
        # registers, but a caller evaluates its arguments in the order it writes them.
        out.add("order")
        a, b = [t for t in a if t != "float"], [t for t in b if t != "float"]
    for x, y in zip(a, b):
        if x == y:
            continue
        px, py = is_pointer(x), is_pointer(y)
        if px and py:
            out.add("void*" if {x, y} & {"void*", "const void*"} else "pointee")
        elif px or py:
            out.add("ptr/int")
        else:
            out.add("scalar")
    return out


def nm():
    tool = shutil.which(os.environ.get("MIPS_PREFIX", "mips-linux-gnu-") + "nm")
    if not tool:
        sys.exit("GNU nm for mips not found (MIPS_PREFIX, default mips-linux-gnu-)")
    return tool


def source_of(obj, base):
    """The source of an object of build/<version>/src/, or None when it no longer exists."""
    stem = Path(obj).relative_to(base).with_suffix("")
    for ext in (".cpp", ".c"):
        src = ROOT / "src" / stem.with_suffix(ext)
        if src.exists():
            return src
    return None


def objects(version, tmp):
    """[(source, object)] of the units the version builds from C."""
    base = ROOT / "build" / "us" / "src"
    out = {}
    for obj in sorted(base.rglob("*.o")):
        src = source_of(obj, base)
        if src is not None:
            out[src] = obj
    if version != "us":
        # PAL's build links its assembly; its C is the US units, with PAL's own definitions
        # (src/versions/<version>/) built in their shared file's unit (tools/version_src.py).
        import version_src
        shared = sorted({version_src.version_of(p)[1] for p in version_src.overrides(version).values()})
        for i, src in enumerate(shared):
            obj = Path(tmp) / ("%d.o" % i)
            version_src.compile_unit(src, version, obj)
            out[src] = obj
    return sorted(out.items())


def spellings(version="us"):
    """{function: {params tuple or None (C linkage): {(source file, defined)}}}."""
    out = collections.defaultdict(lambda: collections.defaultdict(set))
    tool = nm()
    with tempfile.TemporaryDirectory(prefix="sly1-params-") as tmp:
        _read(out, tool, objects(version, tmp))
    return out


def _read(out, tool, objs):
    for src, obj in objs:
        rel = src.relative_to(ROOT / "src").as_posix()
        text = subprocess.run([tool, str(obj)], capture_output=True, text=True, check=True).stdout
        for line in text.splitlines():
            parts = line.split()
            if len(parts) < 2:
                continue
            m = SYMBOL.match(parts[-1])
            if not m:
                continue
            try:
                params = None if m.group(2) is None else tuple(by_value(t) for t in demangle(m.group(2)))
            except DemangleError:
                params = ("<%s>" % m.group(2),)     # kept as written, so it still differs
            out[m.group(1)][params].add((rel, parts[-2] in DEFINED))


def fmt(params):
    return 'extern "C"' if params is None else "(%s)" % ", ".join(params)


def assembly(version="us"):
    """The functions that are original assembly (config/<version>/original_asm.tsv, and the US
    table's for PAL too): their symbol is defined by a marker, without parameters."""
    out = set()
    for v in {"us", version}:
        path = ROOT / "config" / v / "original_asm.tsv"
        if path.exists():
            out.update(l.split("\t")[0] for l in path.read_text().splitlines()[1:] if l)
    return out


def disagreements(spell, asm=frozenset()):
    """[(function, definition params or 'none', its files, {params: (files, kinds)})] for every
    function whose spellings differ, with the files whose spelling differs from the definition's
    (or, with no C definition, every spelling)."""
    out = []
    for func in sorted(spell):
        lists = spell[func]
        if func in asm:     # the marker's symbol is not a declaration
            lists = {p: uses for p, uses in lists.items() if not (p is None and all(d for _, d in uses))}
        if len(lists) < 2:
            continue
        defs = [] if func in asm else [p for p, uses in lists.items() if any(d for _, d in uses)]
        if defs:
            definition = defs[0]
            where = sorted(f for f, d in lists[definition] if d)
            rows = {p: (sorted({f for f, _ in uses}), kinds(definition, p))
                    for p, uses in lists.items() if p != definition}
        else:
            definition, where = "none", []
            first = next(iter(sorted(lists, key=lambda p: (p is None, p or ()))))
            rows = {p: (sorted({f for f, _ in uses}), kinds(first, p) if p != first else set())
                    for p, uses in lists.items()}
        out.append((func, definition, where, rows))
    return out


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--version", default="us", choices=["us", "eu"])
    parser.add_argument("--file", action="append", default=[],
                        help="only declarations in this source file (a path under src/, or its end); repeatable")
    parser.add_argument("--summary", action="store_true", help="the counts only")
    args = parser.parse_args(argv)

    def wanted(f):
        return not args.file or any(f == x or f.endswith("/" + x) or ("src/" + f) == x for x in args.file)

    rows = disagreements(spellings(args.version), assembly(args.version))
    counts = collections.Counter()
    tally = {True: [0, 0, set()], False: [0, 0, set()]}     # with a C definition or not: functions, pairs, files
    for func, definition, where, spells in rows:
        shown = {p: (fs, k) for p, (fs, k) in spells.items() if any(wanted(f) for f in fs)}
        if not shown:
            continue
        t = tally[definition != "none"]
        t[0] += 1
        if not args.summary:
            name = symbols.readable(func)
            label = func if name == func else "%s (%s)" % (func, name)
            if definition == "none":
                print("%s  no C definition" % label)
            else:
                print("%s  %s  defined in %s" % (label, fmt(definition), " ".join(where)))
        for p, (fs, k) in sorted(shown.items(), key=lambda kv: (kv[0] is None, kv[0] or ())):
            fs = [f for f in fs if wanted(f)]
            t[1] += len(fs)
            t[2].update(fs)
            for kind in k:
                counts[kind] += len(fs)
            if not args.summary:
                print("    %-42s %-22s %s" % (fmt(p), ", ".join(sorted(k)) or "-", " ".join(fs)))
    for kind, n in counts.most_common():
        print("%6d  %s" % (n, kind), file=sys.stderr)
    for has, what in ((True, "differ from the C definition"), (False, "disagree, with no C definition (assembly)")):
        n, pairs, files = tally[has]
        print("%d function(s) whose declarations %s: %d (file, spelling) pair(s) in %d file(s)"
              % (n, what, pairs, len(files)), file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
