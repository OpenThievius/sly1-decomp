# SPDX-License-Identifier: AGPL-3.0-or-later
"""Enumerate candidate statements at one site of a function and score each against retail.

    python3 tools/sitesearch.py GENERATOR [--file FILE] [--jobs 6] [--list] [--limit N]
                                [--eu] [--summary] [--match TEXT]
    python3 tools/sitesearch.py --generators

tools/tsearch.py rewrites a function without changing its meaning; this tool does the other
thing a near miss sometimes needs: it inserts a statement that is not in the text yet, from a
defined space, at one place. A generator knows its function, its file and its site; it yields
(label, prediction, text) for every candidate: the whole file with the candidate written at the
site. Each candidate is compiled the way the function lands (tools/tsearch.py's Scorer: the
file's compiler and flags) and scored as tools/check.py compares it. Everything goes to
build/sitesearch/GENERATOR/: log.tsv (label, prediction, score on us, code hash, the statement),
and every EXACT candidate as exact/LABEL.cpp. A rerun skips the labels log.tsv already has, so a
long run can be stopped and resumed. --eu then scores every EXACT candidate on PAL (eu.tsv), and
--summary counts the EXACT candidates by each field of the labels.

The candidates are plain C++ by construction (no inline assembly, volatile, register or goto;
`guard()` rejects any that has more of them than the start). An EXACT candidate is retail's
bytes in a compiled object, not a match: it is one once it stands in src/ and tools/build.py
prints MATCH.

Generators:

head-test     func_0020BB18 (AllocatePictureBuffers, src/lib/mpeg_decoder.cpp): a test at the
              head of the body, after the early return and before the picture stores, that only
              combine can fold and whose condition reads one of the plane pointers before its
              assignment (docs/toolchain/sched1.md, "A block whose first cycle holds one insn").
              Which planes are named as locals, and with which type; the pointer read as itself,
              cast, dereferenced or in arithmetic; the foldable value (w, h and size, masks,
              remainders); the operator joining them; the arm and the statement's form.
              The prediction is "use" where combine should fold the condition and leave the
              USE (no dereference, a value whose zero is known only from its bits), "no" where
              it should not, with "?" where the arm (a return, a call, a local, nothing) may
              undo it either way.
"""

import argparse
import concurrent.futures
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import versions  # noqa: E402

ROOT = versions.ROOT
OUT = ROOT / "build" / "sitesearch"

FORBIDDEN = (r"\basm\b", r"\b__asm__\b", r"\bvolatile\b", r"\bregister\b", r"\bgoto\b")


def guard(start, text):
    """Whether TEXT has no more inline assembly, volatile, register or goto than START."""
    return all(len(re.findall(p, text)) <= len(re.findall(p, start)) for p in FORBIDDEN)


# ---------------------------------------------------------------------------------------------
# head-test: func_0020BB18


BB18_FILE = "src/lib/mpeg_decoder.cpp"
BB18_FUNC = "func_0020BB18"
STORES = "    pic->width = w;\n    pic->height = h;\n"
DECL_AFTER = "    s32 rows;\n"
ASSIGN_BEFORE = "    RewindMpegRingToMark((s32*)&st->pool);\n"
SIZE = "    size = (u32)(w * 0x180 * h) >> 8;\n"


def bb18_neutral(text):
    """The file with func_0020BB18's stand-in test removed and no plane named by a local (the
    near miss's form, 102 lines from retail). Accepts the landed form or the neutral one."""
    s = text.index("void AllocatePictureBuffers(Picture_20BB18* pic)\n{")
    e = text.index("\n}\n", s) + 3
    body = text[s:e]
    k = body.find("    // NOT THE ORIGINAL'S STATEMENT")
    if k >= 0:
        body = body[:k] + body[body.index(STORES, k):]
    # Any statement between the early return and the picture stores is the site's: drop it.
    r = body.index("        return;\n") + len("        return;\n")
    body = body[:r] + body[body.index(STORES, r):]
    body = body.replace("    u32* p3;\n", "")
    body = body.replace("    p3 = &st->planes[3].addr;\n", "")
    body = re.sub(r"\bp3,", "&st->planes[3].addr,", body)
    body = body.replace("(Item_20B9D0*)p3", "(Item_20B9D0*)&st->planes[3]")
    assert not re.search(r"\bp\d\b", body), body
    return text[:s] + body + text[e:]


def bb18_name(text, planes, typed=False, size_first=False):
    """Name the planes PLANES by locals p0..p8 (u32* to the address, or Plane_20BB18* to the
    plane when TYPED), assigned in plane order just before the ring is rewound."""
    s = text.index("void AllocatePictureBuffers(Picture_20BB18* pic)\n{")
    e = text.index("\n}\n", s) + 3
    body = text[s:e]
    ty = "Plane_20BB18*" if typed else "u32*"
    body = body.replace(DECL_AFTER, DECL_AFTER + "".join("    %s p%d;\n" % (ty, k) for k in planes), 1)
    body = body.replace(ASSIGN_BEFORE, "".join(
        "    p%d = &st->planes[%d]%s;\n" % (k, k, "" if typed else ".addr") for k in planes) + ASSIGN_BEFORE, 1)
    for k in planes:
        body = body.replace("&st->planes[%d].addr," % k, ("&p%d->addr," if typed else "p%d,") % k)
        body = body.replace("(Item_20B9D0*)&st->planes[%d]" % k, "(Item_20B9D0*)p%d" % k)
    if size_first:
        body = body.replace(SIZE, "", 1).replace(STORES, SIZE + STORES, 1)
    return text[:s] + body + text[e:]


def bb18_insert(text, stmt):
    s = text.index("void AllocatePictureBuffers(Picture_20BB18* pic)\n{")
    k = text.index(STORES, s)
    return text[:k] + stmt + text[k:]


# The pointer read: (form, needs an integer context). P is the local's name.
READS_ADDR = [("(u32)P", "i"), ("(s32)P", "i"), ("*P", "i"), ("P", "p")]
READS_PLANE = [("(u32)P", "i"), ("P->addr", "i"), ("P->width", "i"), ("P", "p")]

# Values known to be zero only from the bits of a value set in an earlier block (w and h are
# shifted left by 4), so that combine folds them and cse does not: (text, foldable).
VALUES = [
    ("w & 15", True), ("h & 15", True), ("w & 7", True), ("w & 1", True), ("h & 1", True),
    ("(u32)w % 16", True), ("w % 16", False), ("(w | h) & 15", True),
    ("(w & 15) | (h & 15)", True), ("(w + h) & 15", True),
]
VALUES_SIZE = [("size & 63", True), ("size & 15", True), ("size % 64", True)]

# Conditions: (name, template, folds when the value does, the read kind it needs).
CONDS = [
    ("and", "{I} & ({V})", True, "i"),
    ("and_r", "({V}) & {I}", True, "i"),
    ("and_ne", "({I} & ({V})) != 0", True, "i"),
    ("mul", "{I} * ({V})", True, "i"),
    ("mul_r", "({V}) * {I}", True, "i"),
    ("cond", "({V}) ? {I} : 0", False, "i"),
    ("addi_ne", "{I} + ({V}) != {I}", True, "i"),
    ("addi_lt", "(u32)({I} + ({V})) < (u32){I}", True, "i"),
    ("land", "({V}) && {R}", False, "p"),
    ("land_r", "{R} && ({V})", False, "p"),
    ("add_ne", "{R} != {R} + ({V})", True, "p"),
    ("add_ne_r", "{R} + ({V}) != {R}", True, "p"),
    ("add_lt", "{R} + ({V}) < {R}", True, "p"),
]
# Conditions whose zero comes from the expression itself (the tree folder may see it first), or
# from the pointer's low bits masked against w's or h's: (name, template, prediction).
SELF_CONDS = [
    ("shl_mask", "({I} << 4) & 15", "use"), ("mul16_mask", "({I} * 16) & 15", "use"),
    ("clr_mask", "({I} & ~15) & 15", "no"),
    ("low_and_w", "({I} & 15) & w", "use"), ("low_and_h", "({I} & 15) & h", "use"),
    ("low_and_w_ne", "(({I} & 15) & w) != 0", "use"), ("mod_and_w", "({I} % 16) & w", "use"),
    ("mul_w_mask", "({I} * w) & 15", "use"), ("mul_h_mask", "({I} * h) & 15", "use"),
]

ARMS = [
    ("width0", "pic->width = 0;"), ("height0", "pic->height = 0;"),
    ("both0", "pic->width = pic->height = 0;"), ("f130", "st->f130 = 0;"), ("f12C", "st->f12C = 0;"),
    ("f848", "st->f848 = 0;"), ("size0", "size = 0;"), ("empty", "{ }"), ("return", "return;"),
    ("report", "ReportMpegError((Dec_20B9F0*)st, \"picture size is not a multiple of 16\");"),
    ("ptr0", None),
]


def bb18_statements(cond, arm):
    """(form, statement text) for one condition and arm: the if statement, and where the arm
    allows them an assertion written as a conditional expression, the condition as an
    expression statement, and the arm as a conditional expression."""
    out = [("if", "    if (%s)\n        %s\n" % (cond, arm))]
    if arm.startswith("ReportMpegError"):
        out.append(("assert", "    !(%s) ? (void)0 : (void)%s;\n" % (cond, arm.rstrip(";"))))
    if arm == "pic->width = 0;":
        out.append(("expr", "    (void)(%s);\n" % cond))
        out.append(("ternary", "    (%s) ? (void)(pic->width = 0) : (void)0;\n" % cond))
    return out


def bb18_candidates(text):
    neutral = bb18_neutral(text)
    seen = set()

    def emit(label, pred, src):
        if label in seen:
            return None
        seen.add(label)
        return (label, pred, src)

    def grid(cfg, src0, ptr, reads, values, conds, arms, forms=None):
        for rform, rkind in reads:
            r = rform.replace("P", ptr)
            for cname, tpl, cfold, need in conds:
                if need == "p" and rkind != "p" or need == "i" and rkind != "i":
                    continue
                for vtext, vfold in values:
                    cond = tpl.replace("{I}", r).replace("{R}", r).replace("{V}", vtext)
                    deref = rform.startswith("*") or "->" in rform
                    pred = "use" if cfold and vfold and not deref else "no"
                    for aname, arm in arms:
                        if aname == "ptr0":
                            arm = ("%s->addr = 0;" if reads is READS_PLANE else "*%s = 0;") % ptr
                        for form, stmt in bb18_statements(cond, arm):
                            if forms and form not in forms:
                                continue
                            p = pred if aname not in ("return", "report", "size0", "empty") else pred + "?"
                            label = "%s / %s / %s / %s / %s / %s" % (cfg, rform, cname, vtext, aname, form)
                            c = emit(label, p, bb18_insert(src0, stmt))
                            if c:
                                yield c + (stmt.strip(),)
        for rform, rkind in reads:
            if rkind != "i":
                continue
            r = rform.replace("P", ptr)
            for cname, tpl, pred in SELF_CONDS:
                if rform.startswith("*") or "->" in rform:
                    pred = "no"
                for aname, arm in arms[:2]:
                    stmt = "    if (%s)\n        %s\n" % (tpl.replace("{I}", r), arm)
                    c = emit("%s / %s / %s / - / %s / if" % (cfg, rform, cname, aname), pred, bb18_insert(src0, stmt))
                    if c:
                        yield c + (stmt.strip(),)

    # 1. The full grid with plane 3's address named (the landed form's local).
    one3 = bb18_name(neutral, [3])
    yield from grid("one3", one3, "p3", READS_ADDR, VALUES, CONDS, ARMS)
    # 2. The same with size computed before the test, and size's own alignment as the value.
    one3s = bb18_name(neutral, [3], size_first=True)
    yield from grid("one3-sizefirst", one3s, "p3", READS_ADDR, VALUES_SIZE + VALUES[:2], CONDS, ARMS[:6])
    # 3. Which planes are named, and as what: a reduced grid on each.
    small_vals = [VALUES[0], VALUES[1], VALUES[5]]
    small_arms = [ARMS[0], ARMS[1], ARMS[3]]
    configs = [("one%d" % k, [k], k, False) for k in range(9) if k != 3]
    configs += [("six-r%d" % k, list(range(3, 9)), k, False) for k in range(3, 9)]
    configs += [("nine-r%d" % k, list(range(9)), k, False) for k in range(9)]
    configs += [("plane%d" % k, [k], k, True) for k in range(9)]
    configs += [("planes6-r%d" % k, list(range(3, 9)), k, True) for k in range(3, 9)]
    for cfg, planes, k, typed in configs:
        src0 = bb18_name(neutral, planes, typed=typed)
        reads = READS_PLANE if typed else READS_ADDR
        yield from grid(cfg, src0, "p%d" % k, reads, small_vals, CONDS, small_arms + [ARMS[6]], forms={"if"})
    # 4. No pointer read at all: the value's own test (the controls).
    for vtext, _ in VALUES:
        for aname, arm in ARMS[:4]:
            stmt = "    if (%s)\n        %s\n" % (vtext, arm)
            c = emit("none / - / plain / %s / %s / if" % (vtext, aname), "no", bb18_insert(neutral, stmt))
            if c:
                yield c + (stmt.strip(),)


GENERATORS = {
    "head-test": (BB18_FILE, BB18_FUNC, bb18_candidates),
}


# ---------------------------------------------------------------------------------------------
# Running


def safe(label):
    import hashlib
    return "%s_%s" % (re.sub(r"[^A-Za-z0-9_.-]+", "_", label)[:120], hashlib.sha1(label.encode()).hexdigest()[:8])


def read_log(path):
    done = {}
    if path.exists():
        for line in path.read_text().splitlines()[1:]:
            f = line.split("\t")
            if len(f) >= 4:
                done[f[0]] = f
    return done


def run(gen, path, jobs, limit, match):
    import tsearch
    file, func, make = GENERATORS[gen]
    path = Path(path or ROOT / file)
    start = path.read_text()
    out = OUT / gen
    (out / "exact").mkdir(parents=True, exist_ok=True)
    log = out / "log.tsv"
    done = read_log(log)
    if not log.exists():
        log.write_text("label\tprediction\tscore\tcode\tstatement\n")
    cands = [c for c in make(start) if c[0] not in done and (not match or match in c[0])]
    if limit:
        cands = cands[:limit]
    for c in cands:
        assert guard(start, c[2]), c[0]
    scorer = tsearch.Scorer(func, path, "us", work=out / "work")
    print("%d candidates to score (%d already in the log)" % (len(cands), len(done)), flush=True)
    n_exact = 0
    with concurrent.futures.ThreadPoolExecutor(jobs) as ex, open(log, "a") as fh:
        futs = {ex.submit(scorer.score, c[2], "c%d_%d" % (i, os.getpid())): c for i, c in enumerate(cands)}
        for i, fut in enumerate(concurrent.futures.as_completed(futs), 1):
            label, pred, text, stmt = futs[fut]
            s, code = fut.result()
            score = "fail" if s is None else ("EXACT" if s == (0, 0) else "%d/%d" % s)
            fh.write("%s\t%s\t%s\t%s\t%s\n" % (label, pred, score, (code or "-")[:12], stmt.replace("\n", " ")))
            fh.flush()
            if score == "EXACT":
                n_exact += 1
                (out / "exact" / (safe(label) + ".cpp")).write_text(text)
            if i % 100 == 0:
                print("%d/%d scored, %d EXACT" % (i, len(cands), n_exact), flush=True)
    print("done: %d scored, %d EXACT" % (len(cands), n_exact))
    return 0


def run_eu(gen, path, jobs):
    """Score on PAL every candidate the log has as EXACT on US, regenerated from its label."""
    import tsearch
    file, func, make = GENERATORS[gen]
    path = Path(path or ROOT / file)
    out = OUT / gen
    exact = {f[0] for f in read_log(out / "log.tsv").values() if f[2] == "EXACT"}
    eu = out / "eu.tsv"
    done = read_log(eu)
    if not eu.exists():
        eu.write_text("label\tprediction\teu score\tcode\n")
    cands = [c for c in make(path.read_text()) if c[0] in exact and c[0] not in done]
    scorer = tsearch.Scorer(func, path, "eu", work=out / "work_eu")
    n = 0
    with concurrent.futures.ThreadPoolExecutor(jobs) as ex, open(eu, "a") as fh:
        futs = {ex.submit(scorer.score, c[2], "e%d_%d" % (i, os.getpid())): c for i, c in enumerate(cands)}
        for fut in concurrent.futures.as_completed(futs):
            s, code = fut.result()
            score = "fail" if s is None else ("EXACT" if s == (0, 0) else "%d/%d" % s)
            n += score == "EXACT"
            fh.write("%s\t%s\t%s\t%s\n" % (futs[fut][0], futs[fut][1], score, (code or "-")[:12]))
    print("eu: %d checked, %d EXACT" % (len(cands), n))
    return 0


def summary(gen):
    """EXACT against scored, by each field of the labels."""
    rows = list(read_log(OUT / gen / "log.tsv").values())
    print("%d scored, %d EXACT" % (len(rows), sum(f[2] == "EXACT" for f in rows)))
    if not rows:
        return 0
    for i in range(len(rows[0][0].split(" / "))):
        tally = {}
        for f in rows:
            k = f[0].split(" / ")[i]
            t = tally.setdefault(k, [0, 0])
            t[0] += f[2] == "EXACT"
            t[1] += 1
        print("field %d: %s" % (i + 1, ", ".join("%s %d/%d" % (k, e, n) for k, (e, n) in sorted(tally.items()))))
    pred = {}
    for f in rows:
        t = pred.setdefault(f[1], [0, 0])
        t[0] += f[2] == "EXACT"
        t[1] += 1
    print("by prediction: %s" % ", ".join("%s %d/%d" % (k, e, n) for k, (e, n) in sorted(pred.items())))
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("generator", nargs="?")
    parser.add_argument("--file", help="the file to start from (default: the generator's src/ file)")
    parser.add_argument("--jobs", type=int, default=3)
    parser.add_argument("--limit", type=int, default=0, help="score at most N candidates")
    parser.add_argument("--match", help="only the labels that contain TEXT")
    parser.add_argument("--list", action="store_true", help="print the candidates, compile nothing")
    parser.add_argument("--eu", action="store_true", help="check the EXACT candidates on PAL")
    parser.add_argument("--generators", action="store_true", help="list the generators")
    parser.add_argument("--summary", action="store_true", help="EXACT against scored, by label field")
    args = parser.parse_args(argv)
    if args.generators:
        for name, (file, func, _) in GENERATORS.items():
            print("%-12s %s %s" % (name, func, file))
        return 0
    if args.generator not in GENERATORS:
        parser.error("GENERATOR: one of %s" % ", ".join(GENERATORS))
    if args.list:
        file = GENERATORS[args.generator][0]
        for label, pred, _, stmt in GENERATORS[args.generator][2](Path(args.file or ROOT / file).read_text()):
            if not args.match or args.match in label:
                print("%s\t%s\t%s" % (label, pred, stmt.replace("\n", " ")))
        return 0
    if args.summary:
        return summary(args.generator)
    if args.eu:
        return run_eu(args.generator, args.file, args.jobs)
    return run(args.generator, args.file, args.jobs, args.limit, args.match)


if __name__ == "__main__":
    sys.exit(main())
