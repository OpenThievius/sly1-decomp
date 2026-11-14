# SPDX-License-Identifier: AGPL-3.0-or-later
"""One header per source file, declaring the functions the file defines.

    python3 tools/headers.py write     # (re)write include/functions/*.h from the definitions
    python3 tools/headers.py check     # the headers agree with the definitions (CI)
    python3 tools/headers.py apply     # replace the files' own declarations by the headers

Each C++ file of src/main/ and src/lib/ that defines functions gets include/functions/<file>.h:
the prototype of every free function it defines, as the definition spells it, in the file's
order, with the types it names forward-declared or, where a header of include/ defines them,
that header included. A file that calls another file's functions includes that file's header
instead of declaring them itself, so a signature is written once, where it is defined.

`apply` (a one-time conversion of src/main/, kept for files that still declare their own)
removes a file's own declaration of a function only where it agrees with the definition: the
same return type, the same parameter types in the object's symbol (tools/params.py, which
reads the last full build), a single line, no default argument, one spelling in the file. A
declaration that differs is a view the file keeps on purpose (#148 lists them) and stays, and
the file then does not include that function's header, whose declaration would conflict; nor
a header that forward-declares a name the file typedefs, nor its own header where PAL
redefines some of its functions (src/versions/eu/main/<file>/). The libraries keep their own
declarations: Sony's compiler, which builds them, does not take the game's headers. The build
must print the same MATCH after, and tools/version_check.py the same counts.
"""

import argparse
import collections
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "include" / "functions"
NAMES = ROOT / "include" / "names.h"
SOURCES = ("src/main", "src/lib")

KEYWORDS = set("""auto bool break case char class const continue default delete do double else enum
extern float for goto if inline int long new operator private protected public register return
short signed sizeof static struct switch template this typedef union unsigned virtual void volatile
while __attribute__ __inline__ __restrict __extension__ mode TI""".split())
BUILTIN = set("s8 u8 s16 u16 s32 u64 s64 u32 f32 sptr uptr".split())
SKIP_START = ("#", "//", "/*", " ", "\t", "}", "{", "static ", "typedef ", "struct ", "class ",
              "union ", "enum ", "namespace ", "template ", "return ", "inline ", "using ")
IDENT = re.compile(r"[A-Za-z_]\w*")


def names():
    """{readable name: address name} from include/names.h."""
    out = {}
    for line in NAMES.read_text().splitlines():
        m = re.match(r"#define (\w+)\s+(func_\w+)\s*$", line)
        if m:
            out[m.group(1)] = m.group(2)
    return out


def sources():
    out = []
    for d in SOURCES:
        out += sorted((ROOT / d).glob("*.cpp"))
    return out


def header_of(src):
    return OUT / (Path(src).stem + ".h")


def strip_comments(s):
    return re.sub(r"/\*.*?\*/", "", re.sub(r"//[^\n]*", "", s), flags=re.S)


def items(path):
    """[(kind 'def' or 'decl', name, signature text, first line, last line, linkage C)] of the
    file-scope functions declared or defined in the first column."""
    lines = path.read_text(errors="replace").split("\n")
    out = []
    c_block = 0
    i = 0
    while i < len(lines):
        line = lines[i]
        if re.match(r'extern "C"\s*\{', line):
            c_block += 1
            i += 1
            continue
        if c_block and line.startswith("}"):
            c_block -= 1
            i += 1
            continue
        if not line or line.startswith(SKIP_START) or "(" not in line:
            i += 1
            continue
        # Join lines until the parameter list's parentheses close.
        j, text = i, strip_comments(line)
        open_at = text.find("(")
        end = close_of(text, open_at)
        while end < 0 and j + 1 < len(lines):
            j += 1
            text += " " + strip_comments(lines[j]).strip()
            end = close_of(text, open_at)
        if end < 0:
            i = j + 1
            continue
        text = text.rstrip()
        rest = text[end + 1:].strip()
        nxt = lines[j + 1].strip() if j + 1 < len(lines) else ""
        if rest.endswith(";") and rest[:-1].strip() in ("", "const"):
            kind = "decl"
        elif rest == "{" or rest.startswith("{") or (rest == "" and nxt.startswith("{")):
            kind = "def"
        else:
            i = j + 1
            continue
        head = text[:text.find("(")]
        m = re.search(r"([A-Za-z_]\w*)\s*$", head)
        if not m or "::" in head or "operator" in head or "=" in head.split("(")[0]:
            i = j + 1
            continue
        sig = text[:end + 1]
        linkage = c_block > 0 or sig.startswith('extern "C"')
        sig = re.sub(r'^extern "C"\s*', "", sig)
        sig = re.sub(r"^extern\s+", "", sig)
        out.append((kind, m.group(1), " ".join(sig.split()), i, j, linkage))
        i = j + 1
    return out


def close_of(text, at):
    """The index of the parenthesis closing the one at `at`, or -1."""
    depth = 0
    for k in range(at, len(text)):
        if text[k] == "(":
            depth += 1
        elif text[k] == ")":
            depth -= 1
            if depth == 0:
                return k
    return -1


def type_names(sig, fname):
    """The identifiers of a signature that name types (not keywords, builtins, parameter names
    or the function)."""
    inside = sig[sig.find("(") + 1:sig.rfind(")")]
    params = set()
    for p in split_params(inside):
        p = p.strip()
        if "(" in p:      # a function pointer: (*name)(...)
            m = re.search(r"\(\s*\*\s*(\w+)\s*\)", p)
            if m:
                params.add(m.group(1))
            continue
        m = re.search(r"([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*$", p)
        if m and len(IDENT.findall(p)) > 1:
            params.add(m.group(1))
    out = []
    for m in IDENT.finditer(sig):
        t = m.group(0)
        if sig[max(0, m.start() - 2):m.start()] == "::":
            continue
        if t in KEYWORDS or t in BUILTIN or t in params or t == fname or t in out:
            continue
        out.append(t)
    return out


def split_params(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "(<":
            depth += 1
        elif ch in ")>":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return out


def include_types():
    """{type name: (header, key)} for the types the headers of include/ define: key is the
    class-key a forward declaration uses (struct, union), or None for a name only its header
    can declare (a typedef, an enum, a namespace)."""
    out = {}
    for h in sorted((ROOT / "include").glob("*.h")):
        text = strip_comments(h.read_text(errors="replace"))
        rel = h.name
        for m in re.finditer(r"\b(struct|class|union|enum|namespace)\s+(?:__attribute__\s*\(\(.*?\)\)\s*)?([A-Za-z_]\w*)\s*(?::[^;{]*)?\{", text):
            key = {"struct": "struct", "class": "struct", "union": "union"}.get(m.group(1))
            out.setdefault(m.group(2), (rel, key))
        for m in re.finditer(r"\btypedef\b[^;]*?\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*(?:__attribute__\s*\(\(.*?\)\)\s*)?;", text):
            out[m.group(1)] = (rel, None)
        for m in re.finditer(r"\btypedef\b[^;]*\(\s*\*\s*([A-Za-z_]\w*)\s*\)", text):
            out[m.group(1)] = (rel, None)
    return out


def local_typedefs(path):
    """The names a source file defines by typedef (which a forward declaration cannot name)."""
    text = strip_comments(path.read_text(errors="replace"))
    out = set(m.group(1) for m in re.finditer(r"\btypedef\b[^;]*?\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*(?:__attribute__\s*\(\(.*?\)\)\s*)?;", text))
    out |= set(m.group(1) for m in re.finditer(r"\btypedef\b[^;]*\(\s*\*\s*([A-Za-z_]\w*)\s*\)", text))
    out |= set(m.group(1) for m in re.finditer(r"\benum\s+([A-Za-z_]\w*)", text))
    return out


def definitions(readable):
    """{source: [(symbol, signature, linkage)]} for the free functions each file defines, and
    {symbol: source}."""
    defs, where = collections.OrderedDict(), {}
    for src in sources():
        rows = []
        for kind, name, sig, _, _, linkage in items(src):
            if kind != "def":
                continue
            sym = readable.get(name, name if name.startswith("func_") else None)
            if sym is None or sym in where:
                continue
            rows.append((sym, sig, linkage))
            where[sym] = src
        if rows:
            defs[src] = rows
    return defs, where


def exportable(src, rows, inc):
    """The rows whose types a header can name, with the forward declarations and includes they
    need. A struct or union is forward-declared, so a header pulls in no class header; a
    typedef, enum or namespace of include/ brings its header. A type the file only typedefs
    cannot be named outside it, and its functions stay out of the header."""
    local = local_typedefs(src)
    text = strip_comments(Path(src).read_text(errors="replace"))
    ok, fwd, includes = [], set(), set()
    for sym, sig, linkage in rows:
        name = sig[:sig.find("(")].split()[-1].lstrip("*&")
        tys = type_names(sig, name)
        if any(t in local and t not in inc for t in tys):
            continue
        for t in tys:
            if t in inc:
                header, key = inc[t]
            else:
                m = re.search(r"\b(struct|class|union)\s+%s\b" % re.escape(t), text)
                header, key = None, "union" if m and m.group(1) == "union" else "struct"
            if key is None:
                includes.add(header)
            else:
                fwd.add((key, t))
        ok.append((sym, sig, linkage))
    return ok, fwd, includes


def header_text(src, rows, fwd, includes):
    rel = Path(src).relative_to(ROOT).as_posix()
    guard = "FUNCTIONS_%s_H" % re.sub(r"\W", "_", Path(src).stem).upper()
    lines = ["// SPDX-License-Identifier: AGPL-3.0-or-later",
             "// The functions %s defines, as its definitions spell them." % rel,
             "// Generated by tools/headers.py write; do not edit.",
             "#ifndef " + guard, "#define " + guard, "", '#include "common.h"']
    for h in sorted(includes - {"common.h", "names.h"}):
        lines.append('#include <%s>' % h)
    lines.append("")
    for key, t in sorted(fwd, key=lambda kt: kt[1]):
        lines.append("%s %s;" % (key, t))
    if fwd:
        lines.append("")
    for sym, sig, linkage in rows:
        lines.append(('extern "C" ' if linkage else "") + sig + ";")
    lines += ["", "#endif", ""]
    return "\n".join(lines)


def generate():
    readable = names()
    inc = include_types()
    defs, where = definitions(readable)
    texts, exported = {}, {}
    generate.forward = {}
    for src, rows in defs.items():
        ok, fwd, includes = exportable(src, rows, inc)
        if not ok:
            continue
        texts[header_of(src)] = header_text(src, ok, fwd, includes)
        generate.forward[header_of(src)] = {n for _, n in fwd}
        for sym, _, _ in ok:
            exported[sym] = src
    return texts, exported, readable


def cmd_write(_):
    texts, _, _ = generate()
    OUT.mkdir(exist_ok=True)
    for p in OUT.glob("*.h"):
        if p not in texts:
            p.unlink()
    for p, t in texts.items():
        if not p.exists() or p.read_text() != t:
            p.write_text(t)
    print("wrote %d headers in %s" % (len(texts), OUT.relative_to(ROOT)))


def cmd_check(_):
    texts, _, _ = generate()
    bad = [p for p, t in texts.items() if not p.exists() or p.read_text() != t]
    bad += [p for p in OUT.glob("*.h") if p not in texts]
    for p in bad:
        print("stale: %s (run tools/headers.py write)" % p.relative_to(ROOT))
    if bad:
        sys.exit(1)
    print("ok: %d headers" % len(texts))


def returns(sig):
    """A signature's return type, spaces removed (`static`, `inline` and `extern` dropped)."""
    head = sig[:sig.find("(")]
    head = head[:len(head) - len(re.search(r"\w+\s*$", head).group(0))]
    return re.sub(r"\b(static|inline|extern)\b|\s", "", head)


def cmd_apply(args):
    import params
    texts, exported, readable = generate()
    defs, _ = definitions(readable)
    defret = {sym: returns(sig) for rows in defs.values() for sym, sig, _ in rows}
    spell = params.spellings()
    # {symbol: definition params}; {(symbol, file): set of params spelled there}
    defp, filep = {}, collections.defaultdict(set)
    for sym, lists in spell.items():
        for p, uses in lists.items():
            for f, d in uses:
                if d:
                    defp[sym] = p
                else:
                    filep[(sym, f)].add(p)
    only = set(args.files) if args.files else None
    removed_total = kept_total = 0
    for src in sources():
        rel = src.relative_to(ROOT / "src").as_posix()
        # The libraries are built by Sony's compiler, which does not take the game's class
        # headers: they keep their own declarations.
        if not rel.startswith("main/"):
            continue
        if only and str(src.relative_to(ROOT)) not in only:
            continue
        lines = src.read_text().split("\n")
        drop = {}
        own_types = local_typedefs(src)
        blocked = set()
        if (ROOT / "src" / "versions" / "eu" / "main" / src.stem).is_dir():
            # PAL redefines some of this file's functions, at times with other parameters, in
            # the file's own unit (docs/VERSIONS.md): its own header would add the US overloads.
            blocked.add(header_of(src))
        for kind, name, sig, a, b, linkage in items(src):
            if kind != "decl":
                continue
            sym = readable.get(name, name if name.startswith("func_") else None)
            if sym is None or sym not in exported:
                continue
            header = header_of(exported[sym])
            spelled = filep.get((sym, rel), set())
            if returns(sig) != defret.get(sym):
                blocked.add(header)     # the same parameters with another return type: the
                kept_total += 1         # header's declaration would conflict with this one
                continue
            if a != b or "=" in sig.split("(", 1)[1] or len(spelled) > 1 or \
                    (spelled and spelled != {defp.get(sym)}):
                kept_total += 1
                continue
            if generate.forward.get(header, set()) & own_types:
                blocked.add(header)     # the header would forward-declare a name this file typedefs
                kept_total += 1
                continue
            drop[a] = header
        need = {h for a, h in drop.items() if h not in blocked}
        drop = {a for a, h in drop.items() if h not in blocked}
        if not drop:
            continue
        removed_total += len(drop)
        out = [l for k, l in enumerate(lines) if k not in drop]
        # Include the headers after the file's first block of includes.
        last = next((k for k, l in enumerate(out) if l.startswith("#include")), None)
        while last is not None and last + 1 < len(out) and out[last + 1].startswith("#include"):
            last += 1
        incs = ['#include "functions/%s"' % h.name for h in sorted(need)
                if '#include "functions/%s"' % h.name not in out]
        if last is None:
            first = next(k for k, l in enumerate(out) if l and not l.startswith("//"))
            out[first:first] = incs + [""]
        else:
            out[last + 1:last + 1] = incs
        src.write_text("\n".join(out))
    print("removed %d declarations, kept %d that differ" % (removed_total, kept_total))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("write")
    sub.add_parser("check")
    a = sub.add_parser("apply")
    a.add_argument("files", nargs="*")
    args = ap.parse_args(argv)
    {"write": cmd_write, "check": cmd_check, "apply": cmd_apply}[args.cmd](args)


if __name__ == "__main__":
    main()
