# SPDX-License-Identifier: AGPL-3.0-or-later
"""Check every C function of src/ at its PAL counterpart.

    python3 tools/version_check.py [--check]

Each file of src/ is compiled once, as the US build compiles it, and each
function it defines is compared with PAL's at its counterpart
(config/eu/map.tsv), every address translated as tools/check.py does. The
results go to config/eu/c_status.tsv, one row per C function: `match`,
`differs` (PAL's bytes are not what this C builds), `absent` (PAL has no
counterpart) or `error` (the check could not place it). tools/progress.py
counts PAL's finished functions from it.

--check needs no toolchain: it fails when a C function of src/ has no row, or
a row names a function src/ no longer defines (CI runs it through
tools/progress.py --check).
"""

import argparse
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
STATUS = ROOT / "config" / "eu" / "c_status.tsv"
HEADER = "us_name\teu_name\tstatus\tnote"


def read_status():
    if not STATUS.exists():
        return {}
    rows = {}
    for line in STATUS.read_text().splitlines()[1:]:
        us, eu, status, note = (line.split("\t") + [""])[:4]
        rows[us] = (eu, status, note)
    return rows


def defined_in_src():
    """{function name: source file} for every function src/ defines."""
    import todo
    out = {}
    for path in sorted((ROOT / "src").rglob("*.cpp")) if (ROOT / "src").exists() else []:
        for m in todo.DEFINITION.finditer(path.read_text()):
            out[m.group(1)] = path
    return out


def eu_names():
    out = {}
    for line in (ROOT / "config" / "eu" / "map.tsv").read_text().splitlines()[1:]:
        eu_name, eu_addr, size, us_name, us_addr, how = line.split("\t")
        if us_name != "-":
            out[us_name] = eu_name
    return out


def run():
    import check
    import compile as cc
    import elf
    defined = defined_in_src()
    names = eu_names()
    resolver = check.Resolver("eu")
    image = check.retail_image("eu")
    rows = {}
    by_file = {}
    for name, path in defined.items():
        by_file.setdefault(path, []).append(name)
    for path, funcs in sorted(by_file.items()):
        with tempfile.TemporaryDirectory(prefix="sly1-vc-") as tmp:
            obj_path = Path(tmp) / "unit.o"
            cc.compile_file(path, obj_path)
            obj = elf.Elf(obj_path.read_bytes())
        for name in sorted(funcs):
            if name not in names:
                rows[name] = ("-", "absent", "")
                continue
            try:
                r = check.check_function(obj, name, "eu", resolver, image)
            except KeyError as e:
                rows[name] = (names[name], "error", str(e).strip("'\""))
                continue
            status = {"EXACT": "match", "DIFFER": "differs"}.get(r["status"], "error")
            rows[name] = (names[name], status, r.get("note", ""))
    text = HEADER + "\n" + "".join("%s\t%s\t%s\t%s\n" % (n, *rows[n]) for n in sorted(rows))
    STATUS.write_text(text)
    counts = {}
    for _, status, _ in rows.values():
        counts[status] = counts.get(status, 0) + 1
    print("wrote %s: %s" % (STATUS.relative_to(ROOT), ", ".join("%d %s" % (v, k) for k, v in sorted(counts.items()))))
    return 0


def check_current():
    defined = set(defined_in_src())
    rows = set(read_status())
    problems = ["%s has no row in config/eu/c_status.tsv (run tools/version_check.py)" % n for n in sorted(defined - rows)]
    problems += ["config/eu/c_status.tsv has %s, which src/ no longer defines" % n for n in sorted(rows - defined)]
    for p in problems:
        print("stale: " + p)
    return 1 if problems else 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args(argv)
    return check_current() if args.check else run()


if __name__ == "__main__":
    sys.exit(main())
