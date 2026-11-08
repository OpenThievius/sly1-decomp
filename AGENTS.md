# Instructions for agents

This file is for AI agents (Claude, Codex or others) working in this repository. Read it
completely before changing anything, then README.md, CONTRIBUTING.md, LEGAL.md and
docs/ROADMAP.md. The repository follows the structure and conventions of the OpenRAC
decompilations (rac3-decomp, rac2-decomp), the sister project of the same maintainers: keep it
that way.

## What this repository is

A matching decompilation of *Sly Cooper and the Thievius Raccoonus* (PS2). The primary target
is the NTSC-U `SCUS_971.98`; PAL `SCES_509.17` comes second. The May 2002 prototype is
recognised by the tools and nothing is ever taken from it (docs/PROTOTYPE.md). The game is **C++** built with SN Systems' GCC 2.95.3 for the PS2
(docs/TOOLCHAIN.md). Both versions build byte for byte from their assembly, and the US build links
every C function of `src/` at its retail address. docs/AGENT_WORKFLOW.md is the whole matching
procedure; read it before you match anything.

| Path | What it is | Who writes it |
| --- | --- | --- |
| `config/versions.json` | every version: serial, role, disc and executable checksums | by hand, rarely |
| `config/splat/<version>.yaml` | splat's configuration | by hand |
| `config/<version>/symbol_addrs.txt` | names for retail addresses | by hand |
| `config/<version>/functions.tsv`, `config/eu/map.tsv` | every function, and PAL's pairing with US | `tools/inventory.py` |
| `config/<version>/layout.tsv` | what each part of the executable is: game code, libraries, data sections | by hand |
| `config/cflags.tsv` | the compiler, and the flags of each source file | by hand |
| `config/us/c_data.tsv` | every global the C defines, from the last full build that printed `MATCH` (counted as matched data) | `tools/build.py` |
| `config/us/generated.tsv` | the functions the compiler makes for a file (a static initialiser, the constructor that calls it), under retail's names | by hand |
| `config/us/statics.tsv` | the labels retail has for a function's `static` variables and their guards (docs/AGENT_WORKFLOW.md) | by hand |
| `config/eu/c_status.tsv` | each C function checked at its PAL counterpart | `tools/version_check.py` |
| `config/us/original_asm.tsv`, `config/eu/original_asm.tsv` | the game-code functions that are original assembly or linker leftovers, counted as finished apart from the exact C (docs/ASM_CLASSIFICATION.md); PAL's table holds the functions only PAL has | `tools/classify_asm.py` |
| `config/us/classes.tsv`, `methods.tsv`, `creators.tsv` | the game's class map from retail's class descriptors: each class's parent, id, flags, size and method slots (own or inherited), the classes each function is a method of, and the functions that create an object of a class | `tools/classes.py` |
| `tools/symbols.py` | the shared name map: either name of a symbol, for the tools that read source text | by hand |
| `config/names/`, `include/names.h` | readable names for address-named functions and globals, each with its evidence, one table per source file (`config/names/main/value.tsv`) and one for globals (`data.tsv`), and the macros generated from them (docs/NAMING.md) | by hand; `names.h` by `tools/names.py header` |
| `config/us/tables.tsv`, `members.tsv`, `installers.tsv`, `dispatch.tsv` | every other table of function pointers in retail's data (method tables, GCC vtables, callback records), the tables each function is in, the functions that install each table, and the calls through an object's table by slot | `tools/tables.py` |
| `src/main/XXXXXXXX.cpp` | matched game C++, one file per 16 KiB window of `.text` | you |
| `src/main/<name>.cpp`, `config/us/files.tsv` | a real source file, found in retail and proved by building it whole (docs/AGENT_WORKFLOW.md); the table gives its code range and where its data starts | you, by hand |
| `src/lib/XXXXXXXX.cpp` | matched library code, by the same windows; built with Sony's 2.9-ee-991111, which `config/cflags.tsv` names per file (docs/TOOLCHAIN.md) | you |
| `src/libm/XXXXXXXX.cpp` | the math library (0x204F68–0x2093F0), by the same windows; built with Sony's Linux 2.9-ee-991111-01 when the toolchain has it (docs/TOOLCHAIN.md) | you |
| `include/` | the project's own headers | by hand |
| `src/versions/eu/<file>/<function>.cpp` | PAL's own definition of a function whose PAL bytes differ, built in its shared file's unit (docs/VERSIONS.md) | you |
| `nonmatching/` | near misses, never linked, each with its verdict line; `README.md` is the index | you; verdicts and index by `tools/nonmatching.py` |
| `progress/<version>/report.json`, the README table | what ByteMatch shows | `tools/progress.py` |
| `tools/`, `tests/` | setup, split, checks | by hand |
| `docs/` | research notes and decisions | by hand |
| `baserom/`, `asm/`, `assets/`, `build/`, `include/*.inc`, `include/include_asm.h` | your discs, and what is generated from them | never committed |

Every tool takes `--version us|eu|may19` where it makes sense, and reads its paths from
`tools/versions.py`.

## Commands

| Command | What it does |
| --- | --- |
| `python3 tools/setup.py [PATH ...]` | recognises disc images and writes `baserom/<version>/<executable>` |
| `venv/bin/python tools/setup_asm.py --version us` | runs splat; writes `asm/us/` and `build/us/` |
| `python3 tools/toolchain.py` | finds the compiler (`SLY1_TOOLCHAIN`) and its runner (`SLY1_RUNNER`, wibo, wine) and compiles a test unit |
| `python3 tools/build.py [--version eu]` | the full build: `MATCH ... with N functions from C` |
| `python3 tools/todo.py [--max-size N] [--exclude vu,jtbl,...]` | the functions still to match, with their tags |
| `python3 tools/check.py FILE.cpp FUNC [--version eu]` | compiles one file and compares one function with retail |
| `python3 tools/version_check.py` | every C function at its PAL counterpart: `config/eu/c_status.tsv` |
| `python3 tools/check.py src/versions/eu/FILE/FUNC.cpp FUNC` | PAL's own definition, built in its shared file's unit, against PAL |
| `python3 tools/version_src.py todo` | the functions only PAL has, not yet defined, with their tags and file |
| `python3 tools/permute.py FILE FUNC [--auto]` | every order of the lines marked `/*P*/` (or of each run of simple statements), compiled and scored; stops at EXACT |
| `python3 tools/permuter_setup.py FILE FUNC` | sets a near miss up for decomp-permuter (fetched into the gitignored `tools/ext/`, never committed) |
| `python3 tools/permute_night.py FUNC ...` | decomp-permuter on near misses one after another, unattended, with the barrier-making rewrites off; keeps each zero, spliced back and checked, in `build/permute_night/` |
| `python3 tools/regdiff.py FILE FUNC` (or `--all`) | whether an attempt differs from retail only in its registers (`registers`), in instruction order too (`order`), or in its code (`code`) |
| `python3 tools/decls.py` | declarations whose return type contradicts the function's C definition or retail's callers (a wrong `void` looks like a register tie in the caller) |
| `python3 tools/nonmatching.py check` | re-scores the near misses in `nonmatching/` and writes the index (`--check` in CI) |
| `python3 tools/progress.py [--check]` | the ByteMatch reports and the README table |
| `python3 tools/inventory.py [--check]` | the function tables and PAL's pairing |
| `python3 tools/classify_asm.py [--check]` | which game-code functions are original assembly (needs `asm/us/`) |
| `python3 tools/classes.py [--check]` | the class map: classes, their methods and creators (needs `asm/us/`) |
| `python3 tools/tables.py [--check]` | the other function-pointer tables, their members and installers (needs `asm/us/`) |
| `python3 tools/names.py header\|check\|apply` | the readable names: `config/names/` to `include/names.h` (each row moved to its table), the tables' rules, and `apply [--dry-run] [FILE ...]`, which writes the readable names in declarations and definitions (docs/NAMING.md) |
| `python3 -m unittest discover -s tests` | the tools' unit tests (CI) |
| `python3 tools/proprietary.py` | scans what git would commit for game data and proprietary material |
| `python3 tests/check_repository.py` | `proprietary.py`, licence headers (CI) |

## Matching rules (from the first matched function on)

- **A match is retail's bytes in a build that equals retail.** Not a compiled object on its
  own, not a masked comparison, not a model's claim. Report exactly what you ran and what it
  printed.
- **Plain C++.** No inline assembly in functions, no register pins, no artificial barriers.
  The exception is the inline-assembly helpers the original developers' C called, for the
  instructions the compiler cannot emit. Retail's bare `sqrt.s` behaves as such a helper, which
  no C form reproduces (docs/TOOLCHAIN.md): include/fpu.h's `Fpu::Sqrt`. (`max.s` and `min.s` are
  not: they are g++'s own minimum and maximum operators, `a >? b` and `a <? b`, plain C++ of this
  compiler.) The functions config/us/original_asm.tsv classifies `inline`
  (docs/ASM_CLASSIFICATION.md: compiled C around VU0, MMI or system instructions) are matched
  with helpers of the same kind. A helper is one instruction, or one short sequence, that the
  compiler cannot emit and that recurs across retail's functions; it lives in a shared header
  in `include/`, written once for every function that needs it, and is named for what it does.
  A function never holds inline assembly of its own, and a helper never reproduces one
  function's code: that would be assembly written as C. The other exception is `MUL_WIDE` (include/mul_wide.h),
  one `multu` whose halves are read from lo and hi, which the toolchain's runtime multiplied with
  and no C product gives; only that runtime's C uses it. Nothing else writes inline assembly.
  The toolchain's own runtime (`libgcc`, config/us/libcalls.tsv) was compiled as C, so its C is a
  `.c` file under `src/lib/`, built by Sony's Linux `cc1` with its own row in config/cflags.tsv
  (docs/TOOLCHAIN.md); its statement macros (`do { } while (0)`) are allowed as in the math
  library, where they are the runtime's helpers of that form and retail's code needs them.
  A whole file (`config/us/files.tsv`) holds the original assembly functions inside its range
  (`config/us/original_asm.tsv`) at file scope, their bytes taken from the disassembly: that is
  not inline assembly in a function. As OpenRAC's decompilations mark them, hand-written assembly
  is `ASM_FUNC(func_X);` and a linker's leftover `LINKER_REMNANT(func_X);` (include/asm_func.h),
  both final source; `LINKER_REMNANT_AFTER_INIT(func_X);`, written after the file's last
  definition, is a leftover retail has between the static initialiser GCC generates and its
  `_GLOBAL_$I$`. A function of its range that is not matched yet is `INCLUDE_ASM(func_X);` until
  its C matches: such a function is never counted as matched (not in `config/us/original_asm.tsv`,
  not in the build's count of functions from C), and its exact C replaces the line. The build
  fails when a marker disagrees with `config/us/original_asm.tsv`.
  `volatile` is one only where it stops the compiler. It is allowed where it is what the
  original had: a hardware register, at a fixed address (`*(volatile u32*)0x10002010`) or
  through a pointer to a register block (a DMA channel's), and data shared with hardware, an
  interrupt handler or another thread (a library's semaphore ids and state flags, a field an
  interrupt handler sets), where retail's code reads and writes it as volatile.
  `do { } while (0)` is one too, except in the math library's bit-access macros
  (`FLOAT_TO_BITS`, `BITS_TO_FLOAT`, and `DOUBLE_TO_WORDS`, `WORDS_TO_DOUBLE`, `DOUBLE_HIGH`,
  `SET_DOUBLE_HIGH` for a double's words, in include/float_bits.h): retail's math library was
  written with macros of that form, as its 8-byte-aligned labels show (docs/TOOLCHAIN.md).
  src/libm uses them for a float's bits and a double's words. In game code it is allowed
  only where it is what the original developers wrote: a macro of a group of statements, in
  the form C macros take (`#define NAME(...) do { ... } while (0)`), that the original
  plausibly had and retail's code needs. Never a wrapper written only to move instructions.
- **An unused local only as a type the original plausibly declared.** GCC 2.95 gives an unused
  struct local a stack slot, so retail's frames show where the original declared one. A list
  walk whose frame has an unused 16-byte gap declares the walk's frame, `ListFrame frame;`
  (include/list_iter.h). A padding array (`s32 scratch[4];`), an invented type or a field that
  exists only to size the frame is not allowed.
- **One flag set per source file**, never per function.
- **`#pragma interface` and `#pragma implementation`, as a pair, and no other pragma.** GCC 2.95
  writes out a class's inline functions at the end of the one file that says
  `#pragma implementation "header.h"` for a header in `include/` that says `#pragma interface`.
  Use the pair only where retail shows that emission (a class's small methods placed after the
  file's static initialiser, docs/AGENT_WORKFLOW.md, "Finding and proving a file"), and nothing
  else of the kind.
- **A global is defined in C** only where its initial value matches retail's bytes at its address:
  one file defines it, under its eight-digit `D_XXXXXXXX` name, and every other file declares it
  `extern`. Until then it stays `extern` (its bytes come from the disassembly). A global retail
  holds as zeros, filled at run time, is defined with `= {0}` (or `= {}`, `= 0`) over its whole
  label, to the next label, as OpenRAC's rac1-decomp defines its zero buffers: with the type its
  readers give it where they show one (fields at their offsets, the rest as padding up to the
  label's end), or a byte array of the label's size where they don't. A size the code shows (a
  clear of N bytes, a loop bound, a class size) wins over the label's.
- **Our own names and types.** Retail is stripped: every function, type, field and file name
  is chosen by us from what retail's code does. Functions and globals keep their address names;
  readable names are macros from `config/names/`, each with its evidence, and docs/NAMING.md
  is the convention. Never write a name you remember from the original game, its prototype or
  another project (a Hungarian prefix such as `psw`, `plo`, `grf` is a sign of one).
  The one exception is a name retail's own bytes spell: the type-name strings of the C++
  runtime's type information in retail's `.rodata` (`9bad_alloc` is the class `bad_alloc`), used
  only where a proved file needs it, because the compiler writes that string from the class's
  name (docs/NAMING.md). Never a name recalled from the game or another project.
- If you get close but not exact, keep the attempt in `nonmatching/` with what still differs,
  and move on. Stop on a function after about ten compiles without getting closer.

## Coordinating work

Matching work is coordinated in the pinned
[Contributor coordination](https://github.com/OpenThievius/sly1-decomp/issues/1) issue, after
rac2-decomp's (OpenRAC). It is a noticeboard, not a task queue or a record of finished work:
`master` is authoritative.

- **One comment per contributor.** Before you match anything, or hand work to agents, make sure
  your contributor has exactly one comment there; create it if not. Edit it in place; never edit
  anyone else's.
- **List only your own reservations**, scope first: a source file (`src/main/00118000.cpp`) or a
  few, then individual functions where a scope would be too big. Don't copy or describe other
  people's.
- **At most 500 unfinished functions per contributor**, across every branch, worktree and agent.
  Functions on `master` don't count; local matches and open pull requests do.
- **Read the others first** and avoid overlap. Someone else's scope is theirs: ask in a comment.
- **A reservation ends** when its functions reach `master` or you release them in your comment.
- **Agents** check their contributor's comment and remaining allowance before starting or
  assigning work, never expand a reservation past 500, and never touch another comment.

## Which model does what

Sort by size with `tools/todo.py` (docs/AGENT_WORKFLOW.md):

- **Haiku**: up to 400 bytes, many workers at once.
- **Sonnet**: 401 to 1,000 bytes, and what Haiku gave up on. Near misses are Sonnet's: on the ones
  closest to retail, Sonnet workers matched 40 of 92 (43%), where Haiku retries matched 28 of 420 (7%).
- **Opus**: over 1,000 bytes, complex ones, near misses in `nonmatching/`, and leading (the full
  build, landing, the reports).

Workers write in `build/swarm/<worker>/` and never edit `src/`; only the lead lands, after the full
build. A worker's EXACT is not a match until `tools/build.py` prints `MATCH` with it linked.

## Rules

- **Derive everything ourselves.** Work from the retail executable of your own disc and public
  hardware documentation. Take nothing from anyone else: no code, symbol maps, splits, names or
  notes from other decompilations or ports of this game, and no third-party code. Never Sony's
  SDK source, samples or headers, or leaked or NDA material, not even as a reference.
- **The toolchain's archives, one use.** As OpenRAC does, `tools/classify_asm.py` reads the
  source-file name a member of the toolchain's `libc.a` or `libm.a` records (`.S` or `.c`) to
  classify a function as original assembly (docs/ASM_CLASSIFICATION.md). Nothing else is read
  from them, and nothing from them goes into the repository.
- **OpenRAC is the exception.** Its own work (tools, build code, docs, toolchain research) may be
  used, openly credited: name it in the commit body and list it in THIRD_PARTY_NOTICES.md
  (LEGAL.md, "OpenRAC"). Not what OpenRAC took from others, and no Ratchet & Clank game code.
- **Nothing from the prototype.** No code, data, symbol names, signatures, types, field names
  or file lists from it, and no tool that extracts them. Looking at it to understand a function
  is allowed only if what you then write is entirely your own, reasoned from retail's bytes
  (docs/PROTOTYPE.md). When in doubt, treat it as copied and leave it out.
- **No proprietary material ever touches the repository**: disc images, executables, `asm/`,
  `assets/`, build output, dumps, the compiler or any SDK binary, SDK headers, links to
  toolchains. Not in a commit, not on a branch, not in a pull request. `tools/proprietary.py`
  (run by `tests/check_repository.py` and CI) checks this; never weaken it to get a file in.
- **Licence.** Everything is AGPL-3.0-or-later. Every new source file starts with
  `SPDX-License-Identifier: AGPL-3.0-or-later` (the check enforces it).
- **English** in everything that lands here.
- **Never delete what you did not create**, and leave other people's uncommitted work alone.
- **The branch is `master`.** Never rewrite its history and never force-push it.

## Commits

As in OpenRAC (CONTRIBUTING.md, "Commits"):

- Conventional Commits with a scope: `feat(us): ...`, `fix(tools): ...`, `docs: ...`,
  `build: ...`, `chore: ...`. The summary says what the change does or what is now true, in
  lower case, without a full stop.
- A prose body wrapped at 72 columns: what changed, why, and what you verified (the commands
  and what they printed).
- One logical change per commit, each leaving the tools and checks working.
- No `Co-authored-by:` trailers or other attribution lines for AI tools.
- Push and open pull requests only when asked.
