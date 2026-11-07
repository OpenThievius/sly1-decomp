# SPDX-License-Identifier: AGPL-3.0-or-later
"""Run decomp-permuter on near misses one after another, unattended, and keep what reaches zero.

    python3 tools/permute_night.py FUNC [FUNC ...] [--minutes 28] [--jobs 12]

Each FUNC is set up from nonmatching/FUNC.cpp (tools/permuter_setup.py) and permuted for
--minutes with --jobs processes, then the next. The rewrites that can only make what AGENTS.md
forbids (do/while(0) blocks, dummy expressions, x ^ 0, padding locals, self-assignments) are
weighted 0, and those that moved registers by hand (a callee's return type, a global's type, a
declaration's place) weighted up. Every zero-score candidate is kept in build/permute_night/FUNC/,
with its function spliced back into the near miss and checked with tools/check.py
(EXACT_*.cpp when it is EXACT). Nothing lands by itself: a zero is a lead to read by hand
(docs/AGENT_WORKFLOW.md). The log is build/permute_night/log.txt, one line per function.

decomp-permuter is fetched into tools/ext/ as docs/AGENT_WORKFLOW.md says.
"""

import argparse
import glob
import os
import re
import shutil
import signal
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import version_src  # noqa: E402
import symbols  # noqa: E402
import versions  # noqa: E402

ROOT = versions.ROOT
OUT = ROOT / "build" / "permute_night"
PERMUTER = ROOT / "tools" / "ext" / "decomp-permuter" / "permuter.py"
VENV = ROOT / "tools" / "ext" / "venv"
BARRIERS = ["perm_add_mask", "perm_xor_zero", "perm_ins_block", "perm_empty_stmt", "perm_mult_zero",
            "perm_dummy_comma_expr", "perm_add_self_assignment", "perm_duplicate_assignment",
            "perm_pad_var_decl", "perm_var_cond_block", "perm_sameline"]
BOOSTS = {"perm_randomize_function_type": 15, "perm_randomize_external_type": 15, "perm_reorder_decls": 15}


def venv_python():
    for rel in ("bin/python", "Scripts/python.exe"):
        if (VENV / rel).exists():
            return str(VENV / rel)
    raise SystemExit("no Python environment in tools/ext/venv (docs/AGENT_WORKFLOW.md)")


def splice(near_miss, candidate, func):
    """The near miss's text with FUNC's definition taken from the candidate, or None."""
    if not Path(near_miss).exists():
        return None         # matched and removed while the run was on it
    text, cand = Path(near_miss).read_text(), Path(candidate).read_text()
    try:
        s, e = version_src.definition_span(text, func)
        cs, ce = version_src.definition_span(cand, func)
    except version_src.VersionSourceError:
        return None
    return text[:s] + cand[cs:ce] + text[e:]


def run_one(func, minutes, jobs, log, python):
    near_miss = ROOT / "nonmatching" / ("%s.cpp" % func)
    t0 = time.time()
    setup = subprocess.run([sys.executable, str(ROOT / "tools" / "permuter_setup.py"), str(near_miss), func],
                           capture_output=True, text=True, cwd=ROOT)
    work = ROOT / "build" / "permuter" / func
    if setup.returncode:
        return "setup failed: %s" % (setup.stderr or setup.stdout).strip()[-120:]
    for old in glob.glob(str(work / "output-*")):
        shutil.rmtree(old, ignore_errors=True)      # an earlier run's candidates
    with open(work / "settings.toml", "a") as f:
        f.write("\n[weight_overrides]\n" + "".join("%s = 0\n" % b for b in BARRIERS)
                + "".join("%s = %d\n" % kv for kv in BOOSTS.items()))
    with open(work / "run.log", "w") as out:
        p = subprocess.Popen([python, str(PERMUTER), "-j%d" % jobs, str(work)], stdout=out, stderr=subprocess.STDOUT,
                             cwd=ROOT, start_new_session=True)
        try:
            p.wait(timeout=minutes * 60)
        except subprocess.TimeoutExpired:
            os.killpg(p.pid, signal.SIGTERM)
            time.sleep(3)
            try:
                os.killpg(p.pid, signal.SIGKILL)
            except OSError:
                pass
    text = (work / "run.log").read_text(errors="replace").replace("\r", "\n")
    base = re.search(r"base score = (\d+)", text)
    scores = [int(m) for m in re.findall(r"output-(\d+)-\d+", " ".join(os.listdir(work)))]
    note = "base %s, best %s" % (base.group(1) if base else "?", min(scores) if scores else "-")
    zeros = sorted(glob.glob(str(work / "output-0-*")))
    if zeros:
        keep = OUT / func
        keep.mkdir(parents=True, exist_ok=True)
        exact = 0
        for z in zeros:
            name = os.path.basename(z)
            shutil.copytree(z, keep / name, dirs_exist_ok=True)
            spliced = splice(near_miss, os.path.join(z, "source.c"), func)
            if spliced is None:
                continue
            path = keep / (name + ".cpp")
            path.write_text(spliced)
            res = subprocess.run([sys.executable, str(ROOT / "tools" / "check.py"), str(path), func],
                                 capture_output=True, text=True, cwd=ROOT).stdout
            if res.startswith("EXACT"):
                exact += 1
                path.rename(keep / ("EXACT_" + name + ".cpp"))
        note += "  %d zero(s), %d EXACT by check.py, in %s" % (len(zeros), exact, keep.relative_to(ROOT))
    return "%4.0fs  %s" % (time.time() - t0, note)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("funcs", nargs="+", metavar="FUNC")
    parser.add_argument("--minutes", type=float, default=28)
    parser.add_argument("--jobs", type=int, default=os.cpu_count() or 4)
    args = parser.parse_args(argv)
    args.funcs = [symbols.canonical(f) for f in args.funcs]     # either name (tools/symbols.py)
    missing = [f for f in args.funcs if not (ROOT / "nonmatching" / ("%s.cpp" % f)).exists()]
    if missing:
        parser.error("no near miss in nonmatching/ for %s" % ", ".join(missing))
    python = venv_python()
    OUT.mkdir(parents=True, exist_ok=True)
    with open(OUT / "log.txt", "a", buffering=1) as log:
        log.write("%s start: %d functions, %.0f min each, -j%d\n"
                  % (time.strftime("%H:%M:%S"), len(args.funcs), args.minutes, args.jobs))
        for n, func in enumerate(args.funcs, 1):
            try:
                note = run_one(func, args.minutes, args.jobs, log, python)
            except Exception as e:      # one function's trouble never ends the night
                note = "stopped: %s: %s" % (type(e).__name__, e)
            log.write("%s %3d/%d %-14s %s\n" % (time.strftime("%H:%M:%S"), n, len(args.funcs), func, note))
        log.write("%s done\n" % time.strftime("%H:%M:%S"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
