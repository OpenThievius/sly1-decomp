# Names

Retail is stripped. Every name in this repository is ours, chosen from what the code does
(AGENTS.md, "Our own names and types"). This file says how names are given, written and
recorded, so each one is chosen once and can be checked.

## What keeps its address name

Every function and global keeps its address name: `func_XXXXXXXX` for code and `D_XXXXXXXX` for
data. The build, the symbol map and every tool read the address out of that name. It is what
declarations and definitions use, what `INCLUDE_ASM` names, and what the linker sees.

## Readable names sit on top, as macros

| File | What it is |
| --- | --- |
| `config/names.tsv` | the table: one row per named symbol, with the symbol, its name, and the evidence for the name |
| `include/names.h` | generated from the table by `tools/names.py header`: `#define RegisterButtonCodes func_0016F588` for each row |
| `tools/names.py` | `header` writes `names.h`; `check` checks the table's rules and that `names.h` agrees with it |

Function bodies may use the readable name. The preprocessor turns it back into the address name,
so the objects are byte for byte the same either way. Declarations, prototypes and definitions
keep the address name for now, because the tools find definitions by it. A later step will let
definitions take the readable name too, through a layer that maps it back for the tools. This
scheme follows OpenRAC's rac1-decomp (its `docs/NAMES.md`) without its sources of names: it reads
names from symbol files and another decompilation of its game, which this project never does.
Every name here is a name we gave.

## Types, fields and locals

Types, fields, parameters and locals are already ours, so they are renamed in place. The
header that holds a type is named after it in `snake_case` (`include/button_code.h` for
`ButtonCode`). Until a family is named, its header and types keep their ids: `cNN`, `tXXXX`,
`vXXXX`, `sXXXXXX`, `gXXXXXX` and `rXXXXXX` (docs/ROADMAP.md, item 6). Every field line keeps its
`// 0xNNN` offset comment.

## How a name is written

| What | Style | Example |
| --- | --- | --- |
| a function | `PascalCase`, a verb first | `RegisterButtonCodes`, `AdvanceButtonCodes` |
| a global | `g_` and `camelCase` | `g_buttonCodes` |
| a type | `PascalCase`, a noun | `ButtonCode`, `ButtonCodeSlot` |
| a field, a parameter, a local | `camelCase` | `length`, `pos`, `next` |
| a function-pointer type | the type it serves and `Fn` | `ButtonCodeFn` |

No name takes a Hungarian prefix: no `p` for a pointer, `a` for an array, `c` for a count, `grf`
for flags, `f` for a flag. The original developers wrote their identifiers that way, so a
Hungarian name here would look like theirs. `tools/names.py check` rejects a prefix of that kind.

## Where a name comes from

A name says what the code is seen to do: what a function changes, what a type holds, how a field
is read and written. Its row in `config/names.tsv` gives that evidence in a sentence: the
functions that read and write it, the values it takes, what calls it.

Never take a name from memory of the original game, its prototype, another decompilation or a
port of it, whether it is a symbol, a type, a field or a file name. That holds even when the
name seems obviously right. If a name comes to mind before the evidence does, choose another
word from the code. A name that only restates the address (`Fn16F588`) is better than one
remembered. Reviewers, human and agent, check new names against this before they land.

One kind of name is retail's own: the type-name strings the C++ runtime's type information keeps
in `.rodata` (`9bad_alloc`, `13bad_exception`, `9exception`: a length, then the class's name).
GCC writes that string from the class's name, so a whole file that defines the class (a proved
file, config/us/files.tsv) can only match retail's `.rodata` under that name. Such a name is
allowed only where retail's bytes spell it and a proved file needs it, and the mangled names
that follow from it (`_vt$9bad_alloc`, `__tf9bad_alloc`) go into `config/us/libcalls.tsv` with
it. It is read from retail's data, never remembered, and it opens no door to any other name.

## Workflow

1. Give a family its names: its types and fields in place (they are ours), its functions and
   globals as rows of `config/names.tsv`, each with its evidence.
2. Run `python3 tools/names.py header`, then use the readable names in the bodies.
3. Check that nothing changed: `tools/names.py check`, the full build (`MATCH`) and
   `tools/version_check.py` (the same counts), and `tests/check_repository.py`.
