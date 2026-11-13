# SPDX-License-Identifier: AGPL-3.0-or-later
"""Readable names for address-named symbols (docs/NAMING.md).

    python3 tools/names.py header     # config/names/ -> include/names.h, each row in its table
    python3 tools/names.py check      # the tables and the header agree, and every row is well formed
    python3 tools/names.py apply [--dry-run] [FILE ...]   # write the readable names in declarations and definitions

Every function and global has an address name (func_XXXXXXXX, D_XXXXXXXX): the build reads the
address out of it. A readable name sits on top as a macro in include/names.h,
generated from the tables in config/names/ (symbol, name, evidence), as OpenRAC's rac1-decomp
keeps its names (its docs/NAMES.md). Any code may write the readable name; the preprocessor
turns it back, so the objects are byte for byte the same, and the tools find a symbol under either
name (tools/symbols.py).

A function's row is in the table of the source file that holds it (config/us/files.tsv):
src/main/value.cpp's in config/names/main/value.tsv. A function only PAL has (func_eu_XXXXXXXX) is
in the table of the shared file its own definition under src/versions/eu/ is built in. A global's
row is in config/names/data.tsv.
`header` moves each row to its table and sorts every table by symbol, so a row may be added to any
of them first.

`apply` rewrites the address names of named symbols to their readable names in src/, nonmatching/
and include/ (or in the files it is given): definitions, prototypes, extern declarations, bodies,
initialisers. It keeps the markers (INCLUDE_ASM and the others), comments, strings and #include
lines as they are, changes a file only from the point where it has seen names.h, and reports a
name that is also another identifier in a file instead of converting it there. It is idempotent,
and the objects are byte for byte the same. The tools find a definition under either name
(tools/symbols.py).
"""

import argparse
import bisect
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import symbols  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
TABLES = ROOT / "config" / "names"
DATA_TABLE = TABLES / "data.tsv"
# A function no proved file holds; none should be once every file is proved.
OTHER_TABLE = TABLES / "other.tsv"
HEADER = ROOT / "include" / "names.h"
COLUMNS = ["symbol", "name", "evidence"]

SYMBOL = re.compile(r"^(func(_[a-z]+)?|D)_[0-9A-F]{8}$")
# A function only one version has (func_eu_XXXXXXXX, tools/version_src.py): its table is the shared
# file's its own definition is built in, or the one of the closest function before it both have.
OWN = re.compile(r"^func_([a-z]+)_([0-9A-F]{8})$")
FUNC_NAME = re.compile(r"^[A-Z][A-Za-z0-9]*$")        # PascalCase: RegisterButtonCodes
DATA_NAME = re.compile(r"^g_[a-z][A-Za-z0-9]*$")      # g_ and camelCase: g_buttonCodes
# The original developers wrote a Hungarian prefix on every identifier (a pointer p, an array a, a
# count c, flags grf...). Our names never take one (AGENTS.md, "Our own names"; docs/NAMING.md).
HUNGARIAN = re.compile(r"^(g_)?(p|pp|a|c|grf|f|dg|cb|ib|pv|pf)[A-Z]")


class NameError_(Exception):
    pass


def _relative(path):
    path = Path(path)
    return path.relative_to(ROOT).as_posix() if path.is_absolute() and ROOT in path.parents else str(path)


def read_table(path):
    """The rows of one table, as dicts with the table's path and line; none when it does not exist."""
    if not path.exists():
        return []
    where = _relative(path)
    lines = path.read_text().splitlines()
    if not lines or lines[0].split("\t") != COLUMNS:
        raise NameError_("%s: the first line must be %s" % (where, "\t".join(COLUMNS)))
    rows = []
    for n, line in enumerate(lines[1:], 2):
        if not line.strip():
            continue
        cells = line.split("\t")
        if len(cells) != len(COLUMNS):
            raise NameError_("%s:%d: %d columns, not %d" % (where, n, len(cells), len(COLUMNS)))
        rows.append(dict(zip(COLUMNS, cells), line=n, table=where))
    return rows


def read_tables(top=TABLES):
    """The rows of every table under config/names/, table by table."""
    return [r for path in sorted(Path(top).rglob("*.tsv")) for r in read_table(path)]


def proved_files():
    """[(start, end, source path)] of the proved files (config/us/files.tsv), by start address."""
    path = ROOT / "config" / "us" / "files.tsv"
    rows = [l.split("\t") for l in path.read_text().splitlines()[1:] if l] if path.exists() else []
    return sorted((int(r[1], 16), int(r[2], 16), r[0]) for r in rows if int(r[2], 16) > int(r[1], 16))


def table_for(symbol, files, own=None):
    """The table a symbol's row belongs in, relative to the root: its source file's, or data.tsv.
    A function only one version has goes in the table `own` ({symbol: table}, own_tables()) gives."""
    if not symbol.startswith("func_"):
        return _relative(DATA_TABLE)
    if OWN.match(symbol):
        own = own_tables(files) if own is None else own
        return own.get(symbol, _relative(OTHER_TABLE))
    addr = int(symbol[5:], 16)
    i = bisect.bisect_right([f[0] for f in files], addr) - 1
    if i < 0 or addr >= files[i][1]:
        return _relative(OTHER_TABLE)
    return source_table(files[i][2])                    # src/main/value.cpp


def source_table(source):
    """The table of a source file (src/main/value.cpp -> config/names/main/value.tsv)."""
    source = Path(_relative(source))
    return _relative(TABLES / source.parent.relative_to("src") / (source.stem + ".tsv"))


def own_functions():
    """[(version key, func_<key>_XXXXXXXX, the address of the closest function before it that
    the version shares with US, or None)] of the functions only a version has (config/<key>/map.tsv
    rows without a US name)."""
    out = []
    for path in sorted((ROOT / "config").glob("*/map.tsv")):
        key = path.parent.name
        rows = [l.split("\t") for l in path.read_text().splitlines()[1:] if l]
        before = None
        for r in sorted(rows, key=lambda r: int(r[1], 16)):
            if r[3] != "-":
                before = int(r[4], 16)
            else:
                out.append((key, "func_%s_%s" % (key, r[1].upper()), before))
    return out


def own_tables(files):
    """{func_<key>_XXXXXXXX: table} of the functions only a version has: the table of the shared file
    that its own definition (src/versions/<key>/<shared file>/<function>.cpp) is built in, or, with no
    definition, of the file that holds the closest function before it that both versions have."""
    import version_src
    out = {}
    for key, name, before in own_functions():
        definition = version_src.overrides(key).get(name)
        if definition is not None:
            out[name] = source_table(version_src.version_of(definition)[1])
        elif before is not None:
            out[name] = table_for("func_%08X" % before, files)
    return out


def table_texts(rows, files, own=None):
    """{table path: text} with every row in its table, each table sorted by symbol."""
    own = own_tables(files) if own is None and any(OWN.match(r["symbol"]) for r in rows) else own
    tables = {}
    for r in rows:
        tables.setdefault(table_for(r["symbol"], files, own), []).append(r)
    return {path: "\n".join(["\t".join(COLUMNS)] +
                             ["\t".join(r[c] for c in COLUMNS) for r in sorted(rs, key=lambda r: r["symbol"])]) + "\n"
            for path, rs in tables.items()}


def header_text(rows):
    out = ["// SPDX-License-Identifier: AGPL-3.0-or-later",
           "// Readable names for address-named symbols. Generated by tools/names.py header from",
           "// config/names/; do not edit. Each is a macro for the symbol the build and every tool",
           "// use (func_XXXXXXXX, D_XXXXXXXX), so code may write either and compiles to the same object.",
           "// Declarations, definitions and bodies may use the readable one (tools/names.py apply);",
           "// the markers (INCLUDE_ASM and the others) and comments keep the address name.",
           "// The names are ours, from what the code does (docs/NAMING.md).",
           "#ifndef NAMES_H",
           "#define NAMES_H",
           ""]
    width = max([len(r["name"]) for r in rows] + [0])
    for r in sorted(rows, key=lambda r: r["symbol"]):
        out.append("#define %-*s %s" % (width, r["name"], r["symbol"]))
    out += ["", "#endif", ""]
    return "\n".join(out)


def known_functions():
    """Every US function, and every function only a version has (func_eu_XXXXXXXX)."""
    rows = (ROOT / "config" / "us" / "functions.tsv").read_text().splitlines()[1:]
    return {r.split("\t")[0] for r in rows if r} | {name for _, name, _ in own_functions()}


def identifiers_in_sources():
    """{identifier: first file} of every identifier in src/, include/ and nonmatching/ (names.h aside)."""
    found = {}
    for top in ("src", "include", "nonmatching"):
        for path in sorted((ROOT / top).rglob("*")):
            if path.suffix not in (".c", ".cpp", ".h") or path == HEADER:
                continue
            text = re.sub(r"//[^\n]*|/\*.*?\*/", " ", path.read_text(errors="replace"), flags=re.S)
            for ident in re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\b", text):
                found.setdefault(ident, path.relative_to(ROOT).as_posix())
    return found


def _where(r):
    return "%s:%d" % (r.get("table", "config/names"), r["line"])


def problems(rows, functions=None, idents=None, header=None, files=None, own=None):
    """What is wrong with the tables, and with names.h against them: a list of messages."""
    functions = known_functions() if functions is None else functions
    if files is not None and own is None and any(OWN.match(r["symbol"]) for r in rows):
        own = own_tables(files)
    errs = []
    seen_symbol, seen_name = {}, {}
    for r in rows:
        where = _where(r)
        sym, name = r["symbol"], r["name"]
        if not SYMBOL.match(sym):
            errs.append("%s: %s is not an address name (func_XXXXXXXX, func_eu_XXXXXXXX or D_XXXXXXXX)"
                        % (where, sym))
        elif OWN.match(sym) and sym not in functions:
            errs.append("%s: %s is not a function only that version has (config/%s/map.tsv)"
                        % (where, sym, OWN.match(sym).group(1)))
        elif sym.startswith("func_") and sym not in functions:
            errs.append("%s: %s is not in config/us/functions.tsv" % (where, sym))
        style = FUNC_NAME if sym.startswith("func_") else DATA_NAME
        if not style.match(name):
            errs.append("%s: %s does not follow docs/NAMING.md (%s)" % (
                where, name, "PascalCase" if sym.startswith("func_") else "g_ then camelCase"))
        if HUNGARIAN.match(name):
            errs.append("%s: %s starts with a Hungarian prefix; our names never take one" % (where, name))
        if not r["evidence"].strip():
            errs.append("%s: %s has no evidence" % (where, name))
        if sym in seen_symbol:
            errs.append("%s: %s is named twice (also %s)" % (where, sym, seen_symbol[sym]))
        if name in seen_name:
            errs.append("%s: %s names two symbols (also %s)" % (where, name, seen_name[name]))
        seen_symbol[sym], seen_name[name] = where, where
        if files is not None and "table" in r and r["table"] != table_for(sym, files, own):
            errs.append("%s: %s belongs in %s: run python3 tools/names.py header"
                        % (where, sym, table_for(sym, files, own)))
    if idents is not None:
        for r in rows:
            other = idents.get(r["name"])
            if other is not None and not _is_use(r, other):
                errs.append("%s: %s is already an identifier in %s" % (_where(r), r["name"], other))
    if header is not None and header != header_text(rows):
        errs.append("include/names.h is not what config/names/ gives: run python3 tools/names.py header")
    return errs


def _is_use(row, path):
    """Whether the readable name's appearance in `path` is a use of the macro, not another identifier.
    A source that uses a name includes names.h through common.h; a name the source defines as a
    struct, a field or a local would shadow the macro, so the check looks for its definition forms.
    A global's name (g_) is never a type, and a type's name never reaches past a cast's bracket."""
    return not declares_name(row["name"], code_only((ROOT / path).read_text(errors="replace")))


def declares_name(name, text):
    """Whether `text` declares `name` as a type, field, local or parameter (so the macro would
    rewrite that declaration too). A declaration of the symbol itself, which starts in the first
    column (`extern u8 g_imageEnd[];`, `EntryPool g_pool;`), is not one."""
    name = re.escape(name)
    declares = re.compile(r"(?:^|[;{}(,])\s*(?P<decl>(?!(?:return|case|goto|else|delete|throw|sizeof)\b)"
                          r"(?:(?:extern|static|const|volatile|unsigned|signed|struct)\s+)*(?!g_)[A-Za-z_]\w*"
                          r"(?:\s*[\*&])*\s+[\*&]*%s)\s*[;=\[,)]" % name, re.M)
    for m in declares.finditer(text):
        at = m.start("decl")
        if at == 0 or text[at - 1] == "\n":
            continue
        return True
    return re.search(r"\b(struct|class|union|enum|typedef)\s+[^;{()]*\b%s\b" % name, text, re.M) is not None


# ---- apply: the address names of named symbols become their readable names ----

# What a scan skips: comments, strings, characters, the markers that name a disassembly file, an
# #include or #undef line, the name a #define defines; then each identifier.
SCAN = re.compile(r"""//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|'(?:\\.|[^'\\\n])*'"""
                  r"""|\b(?:%s)\s*\([^)\n]*\)"""
                  r"""|\#\s*(?:include|undef)[^\n]*|\#\s*define\s+[A-Za-z_]\w*"""
                  r"""|\b[A-Za-z_]\w*\b""" % "|".join(symbols.MARKERS), re.S)
INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]*"([^"\n]+)"', re.M)
SOURCE_SUFFIXES = (".c", ".cpp", ".h")
# Units the build assembles from several files (src/versions/, nonmatching/eu/): names.h comes
# from the shared file, so these files have it from their first line.
SPLICED = ("src/versions/", "nonmatching/eu/")


def include_target(name, home):
    """The file a quoted #include names: next to the includer, in include/, or from the root."""
    for base in (Path(home), ROOT / "include", ROOT):
        if (base / name).is_file():
            return (base / name).resolve()
    return None


_REACHES = {}


def reaches_names(path, seen=None):
    """Whether including `path` brings in names.h (directly or through its own includes)."""
    path = Path(path).resolve()
    if seen is None and path in _REACHES:
        return _REACHES[path]
    found = _reaches(path, seen)
    if seen is None:
        _REACHES[path] = found
    return found


def _reaches(path, seen):
    if path == HEADER.resolve():
        return True
    seen = set() if seen is None else seen
    if path in seen:
        return False
    seen.add(path)
    for m in INCLUDE.finditer(path.read_text(errors="replace")):
        target = include_target(m.group(1), path.parent)
        if target and reaches_names(target, seen):
            return True
    return False


def names_from(path, text):
    """The offset from which `text` (the file at `path`) has names.h in effect, or None."""
    rel = _relative(path)
    if rel.startswith(SPLICED):
        return 0
    for m in INCLUDE.finditer(text):
        target = include_target(m.group(1), Path(path).parent)
        if target and reaches_names(target):
            return m.end()
    return None


def convert(text, to_name, start=0):
    """(new text, converted, kept): `text` with each address name of `to_name` written as its
    readable name from offset `start` on, outside comments, strings, markers and #include lines.
    `converted` and `kept` list (offset, address name, readable name) of the names changed and of
    those before `start`, which stay."""
    done, kept, out, last = [], [], [], 0
    for m in SCAN.finditer(text):
        word = m.group(0)
        if word not in to_name:
            continue
        if m.start() < start:
            kept.append((m.start(), word, to_name[word]))
            continue
        out.append(text[last:m.start()])
        out.append(to_name[word])
        done.append((m.start(), word, to_name[word]))
        last = m.end()
    out.append(text[last:])
    return "".join(out), done, kept


def code_only(text):
    """`text` with its comments and strings blanked (newlines kept)."""
    def blank(m):
        word = m.group(0)
        return re.sub(r"[^\n]", " ", word) if word.startswith(("//", "/*", '"', "'")) else word
    return SCAN.sub(blank, text)


def collisions(text, names):
    """{name: why} for the readable names that `text` also uses as another identifier: a field read
    through `.` or `->`, or a type, field, local or parameter it declares. The macro would rewrite
    those too, so the converter leaves such a name alone in that file."""
    code, bad = code_only(text), {}
    wanted = {n for n in names}
    for m in re.finditer(r"[A-Za-z_]\w*", code):
        name = m.group(0)
        if name not in wanted or name in bad:
            continue
        before = code[max(0, m.start() - 3):m.start()].rstrip()
        if before.endswith((".", "->")):
            bad[name] = "read as a field"
            continue
        # Judge the declaration forms on the statement around the use, not on the whole file.
        window = code[max(0, m.start() - 160):m.end() + 40]
        if declares_name(name, window):
            bad[name] = "declared as another identifier"
    return bad


def apply_files(paths, rows=None, write=True):
    """Convert each file. Returns [(path, names written, names kept before names.h, {name: why
    skipped})] for the files that have any."""
    rows = read_tables() if rows is None else rows
    to_name = {r["symbol"]: r["name"] for r in rows}
    report = []
    for path in paths:
        path = Path(path)
        if path.resolve() == HEADER.resolve() or path.suffix not in SOURCE_SUFFIXES:
            continue
        text = path.read_text(errors="replace")
        start = names_from(path, text)
        new, done, kept = convert(text, to_name, len(text) + 1 if start is None else start)
        bad = collisions(text, {n for _, _, n in done})
        if bad:
            allowed = {k: v for k, v in to_name.items() if v not in bad}
            new, done, kept = convert(text, allowed, len(text) + 1 if start is None else start)
        if done and write and new != text:
            path.write_text(new)
        if done or kept or bad:
            report.append((path, len(done), len(kept), bad))
    return report


def default_files():
    out = []
    for top in ("src", "nonmatching", "include"):
        out += [p for p in sorted((ROOT / top).rglob("*")) if p.suffix in SOURCE_SUFFIXES]
    return out


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("command", choices=("header", "check", "apply"))
    parser.add_argument("files", nargs="*", help="apply: the files to convert (default: src/, nonmatching/, include/)")
    parser.add_argument("--dry-run", action="store_true", help="apply: report what would change, write nothing")
    args = parser.parse_args(argv)
    try:
        rows = read_tables()
    except NameError_ as e:
        print("error: %s" % e)
        return 1
    files = proved_files()
    if args.command == "apply":
        paths = [Path(f).resolve() for f in args.files] or default_files()
        report = apply_files(paths, rows, write=not args.dry_run)
        total = 0
        for path, n, kept, bad in report:
            total += n
            note = "".join("; kept %s: %s" % kv for kv in sorted(bad.items()))
            if kept:
                note += "; %d before names.h" % kept
            if n or note:
                print("%s: %d%s" % (_relative(path), n, note))
        print("%s %d names in %d files" % ("would write" if args.dry_run else "wrote", total,
                                           sum(1 for r in report if r[1])))
        return 0
    if args.command == "header":
        texts = table_texts(rows, files)
        for path in sorted(TABLES.rglob("*.tsv")):
            if _relative(path) not in texts:
                path.unlink()
        for rel, text in texts.items():
            path = ROOT / rel
            if not path.exists() or path.read_text() != text:
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(text)
        text = header_text(rows)
        if not HEADER.exists() or HEADER.read_text() != text:
            HEADER.write_text(text)
        print("wrote include/names.h: %d names in %d tables" % (len(rows), len(texts)))
        return 0
    errs = problems(rows, idents=identifiers_in_sources(),
                    header=HEADER.read_text() if HEADER.exists() else header_text([]), files=files)
    for e in errs:
        print("error: " + e)
    if not errs:
        print("ok: %d names" % len(rows))
    return 1 if errs else 0


if __name__ == "__main__":
    sys.exit(main())
