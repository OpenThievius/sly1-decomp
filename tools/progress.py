# SPDX-License-Identifier: AGPL-3.0-or-later
"""The progress reports ByteMatch reads, and the README's table.

    python3 tools/progress.py           # writes progress/<version>/report.json and the README table
    python3 tools/progress.py --check   # fails when either is out of date (CI)

One report per version, in objdiff's report format, so that
https://bytematch.dev/OpenThievius/sly1-decomp shows it: CI uploads
progress/us/report.json as the artifact SCUS_971.98_report and
progress/eu/report.json as SCES_509.17_report.

Everything comes from committed tables, so CI can regenerate it with no disc
and no compiler: the functions of each version (config/<version>/functions.tsv),
what src/ defines (a US function is finished when src/ defines it and the build
links it), and PAL's check of that C (config/eu/c_status.tsv, from
tools/version_check.py), what each part of the executable is
(config/<version>/layout.tsv), and which functions are original assembly
(config/us/original_asm.tsv, tools/classify_asm.py).

A function that is original assembly counts as finished too: it was not made from C, so
there is nothing to match, and the build keeps its bytes from the disassembly. The exact C
matches are counted apart (exact_c() and the README table), as OpenRAC does. A PAL function
is original assembly when its US counterpart (config/eu/map.tsv) is.

Units follow that layout. Code units are the source files: one per 16 KiB
window of game code (game/<window>, src/main/) and of the libraries
(lib/<window>, src/lib/); a unit is complete when every function in it is.
Data units are the sections with bytes (data/<section>): they measure data,
which comes from the disassembly until C can place it (docs/ROADMAP.md).
Each unit is in one category, game, lib or data, and every category has its
own measures.
"""

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import classify_asm  # noqa: E402
import nonmatching  # noqa: E402
import todo  # noqa: E402
import version_check  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
README = ROOT / "README.md"
BEGIN, END = "<!-- progress:begin (tools/progress.py) -->", "<!-- progress:end -->"


def functions(key):
    rows = []
    for line in (ROOT / "config" / key / "functions.tsv").read_text().splitlines()[1:]:
        name, addr, size, kind, _ = line.split("\t")
        rows.append((name, int(addr, 16), int(size)))
    return rows


def exact_c(key):
    """Names of the version's functions whose C builds the retail bytes."""
    done = set(version_check.defined_in_src())
    if key == "us":
        return done
    status = version_check.read_status()
    done |= set(version_check.only_eu())    # functions only PAL has, defined in src/versions/eu/
    return {eu for us, (eu, s, _) in status.items() if s == "match" and us in done}


def original_asm(key):
    """Names of the version's functions that are original assembly (config/us/original_asm.tsv)."""
    listed = classify_asm.read_table()
    if key == "us":
        return set(listed)
    return {eu for us, eu in version_check.eu_names().items() if us in listed}


def finished(key):
    """Names of the version's functions that count as matched: exact C, or original assembly."""
    both = set(version_check.defined_in_src()) & set(classify_asm.read_table())
    if both:
        raise SystemExit("error: %s is in config/us/original_asm.tsv and defined in src/; "
                         "a function is one or the other" % ", ".join(sorted(both)))
    return exact_c(key) | original_asm(key)


def fuzzy(key):
    """{function name in the version's report: share of retail's bytes} of its staged near misses.

    tools/nonmatching.py writes the verdicts; a near miss stays below 100 and a matched function's
    staged file is left over, not counted.
    """
    names = {us: eu for us, (eu, _, _) in version_check.read_status().items()}
    out = {}
    for (version, func), path in nonmatching.staged().items():
        if version != key or nonmatching.matched(version, func):
            continue
        name = func if key == "us" else (
            "func_" + func[len("func_eu_"):] if func.startswith("func_eu_") else names.get(func))
        if name:
            out[name] = nonmatching.share(path)
    return out


def measures(funcs, done, linked, data=0, near=None):
    """objdiff's measures of some functions and some bytes of data (none of it matched yet).

    fuzzy_match_percent also credits each near miss (near: {name: share}) with its share of bytes;
    `_fuzzy_code` carries those bytes to the totals and is not written.
    """
    near = near or {}
    total = sum(s for _, _, s in funcs)
    matched = sum(s for n, _, s in funcs if n in done)
    count = sum(1 for n, _, _ in funcs if n in done)
    close = matched + sum(s * near[n] / 100.0 for n, _, s in funcs if n not in done and n in near)
    pct = lambda a, b: (100.0 * a / b) if b else 100.0
    return {
        "_fuzzy_code": close,
        "fuzzy_match_percent": pct(close, total),
        "total_code": str(total),
        "matched_code": str(matched),
        "matched_code_percent": pct(matched, total),
        "total_data": str(data),
        "matched_data": "0",
        "matched_data_percent": pct(0, data),
        "total_functions": len(funcs),
        "matched_functions": count,
        "matched_functions_percent": pct(count, len(funcs)),
        "complete_code": str(matched if linked else 0),
        "complete_code_percent": pct(matched if linked else 0, total),
        "complete_data": "0",
        "complete_data_percent": pct(0, data),
    }


def add(into, m, close):
    """Sums one unit's measures into a total (percentages are recomputed by finish())."""
    for k in ("total_code", "matched_code", "total_data", "matched_data", "complete_code", "complete_data"):
        into[k] = str(int(into.get(k, "0")) + int(m[k]))
    into["_fuzzy_code"] = into.get("_fuzzy_code", 0.0) + close
    for k in ("total_functions", "matched_functions", "total_units", "complete_units"):
        into[k] = into.get(k, 0) + m[k]


def finish(m):
    pct = lambda a, b: (100.0 * int(a) / int(b)) if int(b) else 100.0
    close = m.pop("_fuzzy_code", None)
    m["matched_code_percent"] = pct(m["matched_code"], m["total_code"])
    m["fuzzy_match_percent"] = (100.0 * close / int(m["total_code"]) if int(m["total_code"]) else 100.0) \
        if close is not None else m["matched_code_percent"]
    m["matched_data_percent"] = pct(m["matched_data"], m["total_data"])
    m["matched_functions_percent"] = pct(m["matched_functions"], m["total_functions"])
    m["complete_code_percent"] = pct(m["complete_code"], m["total_code"])
    m["complete_data_percent"] = pct(m["complete_data"], m["total_data"])
    return m


CATEGORIES = {"game": "Game code", "lib": "Libraries", "data": "Data"}


def report(key):
    funcs = functions(key)
    done = finished(key)
    linked = key == versions.primary()
    near = fuzzy(key)
    units = []
    for kind, name, start, end, category, folder in todo.layout(key):
        if kind == "data":
            m = measures([], done, linked, end - start)
            m["total_units"], m["complete_units"] = 1, 0
            units.append((category, m.pop("_fuzzy_code"), {"name": "data/%s" % name, "measures": m,
                                     "metadata": {"complete": False, "progress_categories": [category]}}))
            continue
        windows = {}
        for f in funcs:
            if start <= f[1] < end:
                windows.setdefault(todo.window_of(f[1]), []).append(f)
        for window in sorted(windows):
            members = windows[window]
            m = measures(members, done, linked, near=near)
            close = m.pop("_fuzzy_code")
            complete = linked and all(n in done for n, _, _ in members)
            m["total_units"], m["complete_units"] = 1, 1 if complete else 0
            meta = {"complete": complete, "progress_categories": [category]}
            source = "%s/%08X.cpp" % (folder, window)
            if (ROOT / source).exists():
                meta["source_path"] = source
            units.append((category, close, {
                "name": "%s/%08X" % (name, window),
                "measures": m,
                "functions": [{"name": n, "size": str(s), "fuzzy_match_percent": 100.0 if n in done else near.get(n, 0.0),
                               "address": str(a - members[0][1]), "metadata": {"virtual_address": str(a)}}
                              for n, a, s in members],
                "metadata": meta,
            }))
    placed = sum(len(u.get("functions", [])) for _, _, u in units)
    if placed != len(funcs):
        raise SystemExit("error: config/%s/layout.tsv places %d of %d functions" % (key, placed, len(funcs)))
    top, cats = {}, {c: {} for c in CATEGORIES}
    for category, close, u in units:
        add(top, u["measures"], close)
        add(cats[category], u["measures"], close)
    return {"measures": finish(dict(measures([], done, linked), **top)), "units": [u for _, _, u in units],
            "version": 2,
            "categories": [{"id": c, "name": CATEGORIES[c], "measures": finish(dict(measures([], done, linked), **cats[c]))}
                           for c in CATEGORIES]}


BYTEMATCH = "https://bytematch.dev/OpenThievius/sly1-decomp"


def badge(serial, label, measure):
    return "[![%s](%s.svg?mode=shield&label=%s&measure=%s&version=%s)](%s/%s)" % (
        label, BYTEMATCH, label, measure, serial, BYTEMATCH, serial)


def readme_table(reports):
    """The README's progress table: ByteMatch's live badges, and the numbers of the committed reports."""
    lines = [BEGIN,
             "| Version | Region | Target | Code | Functions | In the committed report |",
             "|---|---|---|---|---|---|"]
    for key, r in reports.items():
        v = versions.get(key)
        m = r["measures"]
        asm = len(original_asm(key))
        lines.append("| v1.00 | %s | `%s` | %s | %s | %s of %s functions, %.2f%% of code (%s exact C, %s original assembly) |" % (
            v["region"], v["serial"],
            badge(v["serial"], "Code", "matched_code_percent"), badge(v["serial"], "Functions", "matched_functions"),
            format(m["matched_functions"], ","), format(m["total_functions"], ","), m["matched_code_percent"],
            format(len(exact_c(key)), ","), format(asm, ",")))
    lines.append("")
    lines.append("A US function counts when the build links its C and still prints `MATCH`; a PAL function "
                 "when that same C also builds PAL's bytes at its counterpart (`tools/version_check.py`). "
                 "Original assembly (hand-written code and the linker's leftovers, `docs/ASM_CLASSIFICATION.md`) "
                 "counts as finished too and is shown apart from the exact C.")
    lines.append(END)
    return "\n".join(lines)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args(argv)

    problems = 0
    if version_check.check_current():
        problems += 1
    if args.check and nonmatching.check_current():
        problems += 1
    keys = [k for k, v in versions.versions().items() if v["role"] != "reference"]
    reports = {k: report(k) for k in keys}
    for key, r in reports.items():
        path = ROOT / "progress" / key / "report.json"
        text = json.dumps(r, indent=1) + "\n"
        if args.check:
            if not path.exists() or path.read_text() != text:
                print("stale: %s (run python3 tools/progress.py)" % path.relative_to(ROOT))
                problems += 1
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text)
            m = r["measures"]
            print("%s: %d of %d functions, %.2f%% of code" % (key, m["matched_functions"], m["total_functions"],
                                                              m["matched_code_percent"]))
    readme = README.read_text()
    if BEGIN in readme and END in readme:
        new = readme.split(BEGIN)[0] + readme_table(reports) + readme.split(END, 1)[1]
        if new != readme:
            if args.check:
                print("stale: README.md progress table (run python3 tools/progress.py)")
                problems += 1
            else:
                README.write_text(new)
    elif args.check:
        print("README.md has no progress table markers")
        problems += 1
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
