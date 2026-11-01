# Original assembly

Some retail code was not made from C, and some words are what the linker left of a function it
stripped. Compiling C to match those bytes would misrepresent where they come from, and the
build already keeps them from the disassembly. `config/us/original_asm.tsv` lists them, and
`tools/progress.py` counts them as finished, apart from the exact C matches.

This follows [OpenRAC's classification](https://github.com/OpenRAC/rac1-decomp) (rac1-decomp,
`docs/ASM_CLASSIFICATION.md`; credited in THIRD_PARTY_NOTICES.md). The rules below are ours,
from the evidence in this game's bytes.

## What is counted

The progress report's `matched_functions` and `matched_code` now include the listed functions.
The README table and `tools/progress.py` show the two apart:

    3,183 exact C, 670 original assembly, of 4,770 functions

A function is exact C when `src/` defines it and the build links it and still prints `MATCH`
(`tools/version_check.py` for PAL). A function cannot be both: `tools/progress.py` stops if
`src/` defines a listed function, and `tests/test_tools.py` checks the table.

A PAL function is original assembly when its US counterpart (`config/eu/map.tsv`) is: the
same source, built for the other region.

**Changing what the report counts is a policy change and needs the maintainers' review**
(OpenRAC's docs say the same of theirs). The exact C count is kept visible so that nothing is
hidden by it.

## The table

`config/us/original_asm.tsv`, written by `python3 tools/classify_asm.py` and checked with
`--check` (both need `asm/us/`; CI only reads the committed table). Columns: name, address,
size, kind, why.

### handwritten

The function holds an instruction the compiler cannot emit:

- a VU0 macro-mode instruction (COP2: `vaddx`, `lqc2`, `ctc2`, ...): 561 functions;
- a 128-bit multimedia (MMI) instruction that no function matched in C contains: 21;
- the disassembler's own "handwritten" mark: 7, among them the crt0 entry (func_00100008) and
  func_001000C0 at the start of game code.

The MMI rule is evidence-based. Six functions that are matched in C contain `por`, the
compiler's 128-bit `|`, so `por` proves nothing and is in `COMPILER_EMITS`. An instruction is
added there only together with a function that is matched in C and contains it.

### remnant

A run of words the linker left of a function it stripped. It counts when:

1. it starts on an 8-byte boundary, where a stripped function began;
2. it holds no jump or branch;
3. nothing refers to it: no instruction or data in `asm/us/` names it;
4. the code before it is finished: going back over earlier remnants, there is a `jr` and its
   delay slot, a tail `j`, or the start of game code.

Fragments that fail a test stay unmatched, with the `fragment` blocker in `tools/todo.py`, as
a boundary for a person to look at. 81 remnants (636 bytes) pass.

## What is not classified

- **Sony's libraries** (`src/lib`, 0x1F59C4 and up) are matched in C with Sony's own compiler
  (docs/TOOLCHAIN.md, "The libraries"), so nothing in that range is classified here. Their
  hand-written routines stay unmatched with their blockers until the same rules are applied
  to them.
- **Kernel and cache instructions** (`syscall`, `mfc0`, `cache`, `ei`, ...) and
  **`max.s`/`min.s`/`sqrt.s`**: the compiler may not emit them, but they are not in the rule
  above, and a function can use them in a plain wrapper. They stay `system` and `nonc` in
  `tools/todo.py` until a function's other evidence (hand-placed nops, `$at` as a working
  register, a branch into the middle of a function) says it was written as assembly.

## Keeping it right

- `python3 tools/classify_asm.py --check` after `tools/setup_asm.py`: fails if a rule or the
  disassembly changed what the table should hold.
- A function in the table is not work for `tools/todo.py` (blocker `asm`).
- If a function in the table is ever matched in C, remove it from the rules (an instruction
  that is `COMPILER_EMITS`), not from the check.
