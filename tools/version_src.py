# SPDX-License-Identifier: AGPL-3.0-or-later
"""A version's own C: the functions whose bytes differ there from the shared C.

    python3 tools/version_src.py unit src/versions/eu/main/00134000/func_001365A8.cpp
    python3 tools/version_src.py list [--version eu]

Every function has one C source for every version, its file in src/. Where a version's
bytes differ (a field offset, a constant, another callee, a byte read unsigned), that
version gets a definition of its own:

    src/versions/<version>/<path of the shared file without .cpp>/<function>.cpp

holding the function alone (with any declaration only it needs), under its US name. It is
built in the shared file's translation unit, in place of the shared definition, with the
shared file's flags: the version never builds a function with options or a context its
object did not have. The US build never sees these files (versions.sources()).

Code and data only a version has are named with its key, func_eu_XXXXXXXX and
D_eu_XXXXXXXX, and reach that address in that version alone (tools/check.py). A
function only the version has is defined the same way, in the shared file whose
code it sits among (`todo` names it: the file of the closest function before it
that both versions have); having no shared definition to replace, it is added at
the end of that file's unit.

The layout follows OpenRAC's (rac1-decomp, docs/VERSIONS.md; credited in
THIRD_PARTY_NOTICES.md); the code is ours.
"""

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
VERSIONS = ROOT / "src" / "versions"
OWN_NAME = re.compile(r"^func_([a-z]+)_([0-9A-F]{8})$")  # a function only that version has: func_eu_001387C8


class VersionSourceError(Exception):
    pass


def overrides(key):
    """{function: its definition file} for the version."""
    base = VERSIONS / key
    return {p.stem: p for p in sorted(base.rglob("*.cpp"))} if base.exists() else {}


def version_of(path):
    """(version key, shared file) for a file of src/versions/, or None for any other file."""
    path = Path(path).resolve()
    if VERSIONS not in path.parents:
        return None
    rel = path.relative_to(VERSIONS)
    if len(rel.parts) < 3:
        raise VersionSourceError("%s is not src/versions/<version>/<shared file>/<function>.cpp" % path)
    return rel.parts[0], ROOT / "src" / Path(*rel.parts[1:-1]).with_suffix(".cpp")


def skip(text, i):
    """The index after a comment, string or character literal that starts at i, or i."""
    if text.startswith("//", i):
        end = text.find("\n", i)
        return len(text) if end < 0 else end
    if text.startswith("/*", i):
        end = text.find("*/", i + 2)
        return len(text) if end < 0 else end + 2
    if text[i] in "\"'":
        j = i + 1
        while j < len(text) and text[j] != text[i]:
            j += 2 if text[j] == "\\" else 1
        return j + 1
    return i


def definition_span(text, name):
    """(start, end) of the definition of `name` in a file's text: its first line to its closing brace."""
    import todo
    for m in todo.DEFINITION.finditer(text):
        if m.group(1) != name:
            continue
        i, depth = m.start(), 0
        while i < len(text):
            j = skip(text, i)
            if j != i:
                i = j
                continue
            if text[i] == ";" and depth == 0:
                break       # a declaration after all
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
                if depth == 0:
                    return m.start(), i + 1
            i += 1
    raise VersionSourceError("no definition of %s" % name)


def unit_text(shared, definitions):
    """The shared file's text with each function of `definitions` ({name: file}) defined by its file.

    A function only the version has (OWN_NAME) replaces nothing: it is added at the end, in name order.
    """
    text = Path(shared).read_text()
    own = sorted(n for n in definitions if OWN_NAME.match(n))
    spans = sorted(((definition_span(text, name), path) for name, path in definitions.items() if name not in own),
                   reverse=True)
    for (start, end), path in spans:
        text = text[:start] + Path(path).read_text().rstrip() + "\n" + text[end:]
    for name in own:
        text = text.rstrip("\n") + "\n\n" + Path(definitions[name]).read_text().rstrip() + "\n"
    return text


def only_here(key):
    """[(version's name, address, size, shared file)] of the game-code functions only the version has.

    The shared file is the one that holds the closest function before it that both versions have.
    """
    import todo
    rows = [l.split("\t") for l in (ROOT / "config" / key / "map.tsv").read_text().splitlines()[1:]]
    game = [(r[2], r[3]) for r in todo.layout(key) if r[0] == "code" and r[5] == "src/main"]
    out, before = [], None
    for name, addr, size, us_name, us_addr, how in sorted(rows, key=lambda r: int(r[1], 16)):
        a = int(addr, 16)
        if us_name != "-":
            before = int(us_addr, 16)
        elif before is not None and any(s <= a < e for s, e in game):
            out.append((name, a, int(size), ROOT / todo.source_of(before)))
    return out


def unit(shared, key, trying=None):
    """The translation unit the version builds for a shared file: written under build/<version>/versions/.

    trying: {function: file}, definitions kept elsewhere (a worker's folder) that take their place too.
    """
    shared = Path(shared).resolve()
    rel = shared.relative_to(ROOT / "src")
    mine = {n: p for n, p in overrides(key).items() if version_of(p)[1] == shared}
    mine.update(trying or {})
    out = ROOT / "build" / key / "versions" / ("try" if trying else "") / rel
    out.parent.mkdir(parents=True, exist_ok=True)
    text = unit_text(shared, mine)
    if not out.exists() or out.read_text() != text:
        out.write_text(text)
    return out, sorted(mine)


def compile_unit(shared, key, obj):
    """Compile the version's unit for a shared file to `obj`, with the shared file's flags. Returns its own functions."""
    import compile as cc
    path, mine = unit(shared, key)
    cc.compile_file(path, obj, source=shared)
    return mine


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = parser.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("unit", help="write the unit a version builds for a definition's shared file")
    p.add_argument("path")
    p = sub.add_parser("list", help="the version's own definitions")
    p.add_argument("--version", default="eu")
    p = sub.add_parser("todo", help="the functions only the version has, not yet defined, with their tags")
    p.add_argument("--version", default="eu")
    args = parser.parse_args(argv)
    if args.cmd == "unit":
        key, shared = version_of(args.path)
        out, mine = unit(shared, key)
        print("%s: %s" % (out.relative_to(ROOT), ", ".join(mine)))
    elif args.cmd == "list":
        for name, path in overrides(args.version).items():
            print("%s\t%s" % (name, path.relative_to(ROOT)))
    else:
        import todo
        bodies = todo.bodies(args.version)
        done = overrides(args.version)
        for name, addr, size, shared in only_here(args.version):
            own = "func_%s_%08X" % (args.version, addr)
            if own not in done:
                tags = ",".join(sorted(todo.tags_of(bodies.get(name, []), "code"))) or "none"
                print("%s\t%d\t%s\t%s" % (own, size, tags, shared.relative_to(ROOT)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
