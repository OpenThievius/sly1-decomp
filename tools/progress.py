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
tools/version_check.py). Units are the source files of src/main/, one per
16 KiB window of .text; a unit is complete when every function in it is.
"""

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
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


def finished(key):
    """Names of the version's functions that count as matched."""
    done = set(version_check.defined_in_src())
    if key == "us":
        return done
    status = version_check.read_status()
    return {eu for us, (eu, s, _) in status.items() if s == "match" and us in done}


def measures(funcs, done, linked):
    total = sum(s for _, _, s in funcs)
    matched = sum(s for n, _, s in funcs if n in done)
    pct = lambda a, b: (100.0 * a / b) if b else 100.0
    m = {
        "fuzzy_match_percent": pct(matched, total),
        "total_code": str(total),
        "matched_code": str(matched),
        "matched_code_percent": pct(matched, total),
        "total_functions": len(funcs),
        "matched_functions": sum(1 for n, _, _ in funcs if n in done),
        "matched_functions_percent": pct(sum(1 for n, _, _ in funcs if n in done), len(funcs)),
        "complete_code": str(matched if linked else 0),
        "complete_code_percent": pct(matched if linked else 0, total),
    }
    return m


def report(key):
    funcs = functions(key)
    done = finished(key)
    linked = key == versions.primary()
    units = {}
    for f in funcs:
        units.setdefault(todo.window_of(f[1]), []).append(f)
    out_units, complete_units = [], 0
    for window in sorted(units):
        members = units[window]
        m = measures(members, done, linked)
        m["total_units"] = 1
        complete = linked and all(n in done for n, _, _ in members)
        m["complete_units"] = 1 if complete else 0
        complete_units += m["complete_units"]
        source = "src/main/%08X.cpp" % window
        meta = {"complete": complete, "progress_categories": ["game"]}
        if (ROOT / source).exists():
            meta["source_path"] = source
        out_units.append({
            "name": "main/%08X" % window,
            "measures": m,
            "functions": [{"name": n, "size": str(s), "fuzzy_match_percent": 100.0 if n in done else 0.0,
                           "address": str(a - members[0][1]), "metadata": {"virtual_address": str(a)}}
                          for n, a, s in members],
            "metadata": meta,
        })
    top = measures(funcs, done, linked)
    top["total_units"] = len(out_units)
    top["complete_units"] = complete_units
    category = dict(top)
    return {"measures": top, "units": out_units, "version": 2,
            "categories": [{"id": "game", "name": "Game code", "measures": category}]}


def readme_table(reports):
    lines = [BEGIN,
             "| Version | Functions | Code |",
             "| --- | ---: | ---: |"]
    for key, r in reports.items():
        m = r["measures"]
        lines.append("| %s `%s` | %s of %s | %s of %s bytes (%.2f%%) |" % (
            versions.get(key)["region"].split(" (")[0], versions.get(key)["serial"],
            format(m["matched_functions"], ","), format(m["total_functions"], ","),
            format(int(m["matched_code"]), ","), format(int(m["total_code"]), ","), m["matched_code_percent"]))
    lines.append("")
    lines.append("A US function counts when the build links its C and still prints `MATCH`; a PAL function "
                 "when that same C also builds PAL's bytes at its counterpart (`tools/version_check.py`).")
    lines.append(END)
    return "\n".join(lines)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args(argv)

    problems = 0
    if version_check.check_current():
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
