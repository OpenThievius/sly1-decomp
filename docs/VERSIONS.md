# The versions

| Key | Disc | Executable | Disc date | Role |
|---|---|---|---|---|
| `us` | NTSC-U v1.00 | `SCUS_971.98` | 2002-08-24 | primary target |
| `eu` | PAL v1.00, *Sly Raccoon* (En, Fr, De, Es, It) | `SCES_509.17` | 2002-11-27 | second target |
| `may19` | E3 build 5-19D, prototype | `SCUS_971.98` | 2002-05-19 | recognised only: nothing is taken from it ([PROTOTYPE.md](PROTOTYPE.md)) |

Every checksum is in [`config/versions.json`](../config/versions.json). The US
target is primary because it is the original release.

## The executables

Both retail executables are ELF32 MIPS (`0x20924001`: noreorder, eabi64, 5900, mips3) with
entry point `0x100008`. Their main sections:

| Section | US address | US size | PAL address | PAL size |
|---|---|---:|---|---:|
| `.text` | `0x100000` | `0x111E0C` | `0x100000` | `0x1132CC` |
| `.vutext` | `0x211E10` | `0x5550` | `0x2132D0` | `0x5550` |
| `.rodata` | `0x217380` | `0x391BB` | `0x218880` | `0x38FDB` |
| `.data` | `0x250580` | `0x2AC34` | `0x251880` | `0x330F4` |
| `.gcc_except_table` | `0x27B200` | `0x94` | `0x284980` | `0x94` |
| `.sbss` | `0x27B300` | `0x2C` | `0x284A80` | `0x2C` |
| `.bss` | `0x27B380` | `0x3B1304` | `0x284B00` | `0x3B1304` |

Each also has 13 `.DVP.overlay..*` sections (VU microcode), `.reginfo`, a
`.stack` and the `.DVP.ovlytab` tables. Both are stripped: no symbols and no
debug information, so every name in this project is our own.

Notes:

- PAL's `.text` is 0x14C0 bytes longer than US's, so PAL needs its own map.
  Code that is the same is one source, checked against both.
- The US split finds 4,766 functions in `.text` (`tools/setup_asm.py`).

## PAL's own C

Every function has one C source, its file in `src/`, checked against both versions
(`tools/version_check.py`, `config/eu/c_status.tsv`). Where PAL's bytes differ and one source
cannot give both, PAL gets a definition of its own:

    src/versions/eu/<path of the shared file without .cpp>/<function>.cpp

holding that function alone, under its US name, with any declaration only it needs. It is built
in the shared file's translation unit, in place of the shared definition, with the shared file's
flags (`tools/version_src.py`): PAL never builds a function with options or a context its object
did not have. The US build and `tools/todo.py` never see these files.

    python3 tools/check.py src/versions/eu/main/game_clock/func_00142F10.cpp func_00142F10
    python3 tools/version_check.py      # c_status.tsv notes these rows `version-specific`

What makes PAL differ, from the first `differs` rows read one by one:

- **50 Hz.** Times and rates: func_00142F10 clamps the frame step to 1/50 to 1/25 of a second,
  where US has 1/60 to 1/30.
- **Field offsets.** Some objects are laid out differently (a field at 0x590 where US has it at
  0x304): the PAL definition uses a struct of its own.
- **Unsigned bytes.** PAL's string and character functions read `u8` where US reads `s8`.
  Where that changes a function's type, not only its body, the shared file declares the type
  for both: a version's unit starts with `#define VERSION_EU 1`, so the declaration can read
  `#ifdef VERSION_EU` / `typedef u8 Letter_1AEA08;` / `#else` / `typedef s8 ...` / `#endif`
  (src/main/screen_element.cpp, func_001AEA08). A struct whose layout differs is declared the same way:
  `MovieStream` (src/main/movie_player.cpp) is a word longer in PAL, which the static initialiser
  GCC generates for that file needs, having no definition of its own to replace. That is the
  macro's one use: it never selects code, which is PAL's own definition's job.
- **Other calls and arguments.** A call to a function only PAL has, or one more argument.

PAL's data is credited the same way (`tools/data_check.py`, run by `tools/version_check.py`,
`config/eu/c_data_status.tsv`). Each global of `config/us/c_data.tsv` is built as the US build
builds it and its bytes, with every relocated word resolved to the PAL address of its target, are
compared with PAL's retail bytes at the global's PAL address. A row is `match`, `differs` or
`absent` (`.bss`, which no file holds, or no PAL address). Nothing is masked: a table whose pointers
reach something PAL does not have, or whose bytes PAL changed, is `differs`; the row's note says
where the bytes first differ and what the words that differ are (text, pointers, other data). The
report counts the `match` rows' bytes as PAL's matched data (never as complete data: PAL links no
C), on 2026-11-11 288,915 of 464,563 (62.19%).

Where a global is in PAL comes from the translation of its US address (`tools/check.py`,
`Resolver`), which pairs, in this order of evidence:

- the addresses paired code names (the same operand of the same instruction in two paired
  functions);
- the start of each section both executables have (`.rodata`, `.data`, `.gcc_except_table`, `.sbss`,
  `.bss`, `.vutext`), from their section headers: PAL's sections grew by different amounts, and a
  datum at a section's start is exactly at its start;
- for a datum with no pair of its own (`Resolver.place`): the start that the paired addresses
  inside it imply, when there are at least two and every one implies the same; otherwise the
  nearest pair below it plus the same offset, when that stays short of the next one. What lies
  between that pair and the datum may have changed size in PAL (a string, a table), which the
  addresses inside the datum do not suffer from.

A pointer into another global the check has placed is resolved through its placement. A whole file's
section (`config/us/files.tsv`) holds the labels the file includes from the disassembly
(`INCLUDE_DATA`, `INCLUDE_RODATA`) at their places: they are compared as US's bytes, read from the
US disassembly, against PAL's, like the C's own bytes, so a section counts for PAL only when the
included labels equal PAL's too (the two retail images agree on them). Only 2 of the 34 rows that
differ differ inside an included label (`D_00275940`, `D_00275B60`, both tables PAL grew).

The 34 globals that still differ, by cause. None is a placement the tools could still derive; the one
word that is a gap of the tools' is in the last row (`func_001AC638` has no PAL pairing, and the
slot in PAL holds `func_001AB2B0`, which has none either):

| Cause | Rows | Globals |
|---|---:|---|
| PAL's text differs: strings translated, moved, removed or turned into ids | 11 | `D_00249428`, `D_00249CA0`, `D_0024A2D0`, `D_0024A7A0`, `D_0024B280`, `D_0024B438`, `D_0024B660`, `D_0024CBD0`, `D_0024DB20`, `D_0024DCB0`, `D_0027AF70` |
| Jump tables of functions PAL defines itself (`version-specific, rodata` in `c_status.tsv`): PAL's own code puts the cases elsewhere | 6 | `D_002499F0`, `D_00249FE0`, `D_0024A860`, `D_0024DAA0`, `D_0024E1C0`, `D_0024E600` |
| String pointers PAL does not have: its table holds ids, or its own table | 5 | `D_00261090`, `D_002699B0`, `D_00269CD8`, `D_002743A0`, `D_00274F38` |
| Values and tables PAL changed (floats, ids, hashes, an inserted row) | 11 | `D_00244F40`, `D_00261F70`, `D_002623C0`, `D_00262718`, `D_00262A30`, `D_0026C3E0`, `D_00275140`, `D_002758E0`, `D_00275940`, `D_00275B60`, `D_002779C0` |
| Method tables: one slot holds a US function with no PAL pairing, one a different method | 1 | `D_00217380` |

Four rows of the first two causes also hold words of the other (`D_0024B438`, `D_0024B660`,
`D_00249CA0`, `D_0024E600`). What remains is not placement but PAL's own bytes, and the way to
credit more is PAL's own definitions: the rodata a `version-specific` function carries is PAL's, and
the data its own C defines is checked nowhere yet.

Code and data only PAL has are named `func_eu_XXXXXXXX` and `D_eu_XXXXXXXX`, and reach that PAL
address alone (`tools/check.py`). So is a datum both versions have when the tools cannot pair its
PAL address with the US one (no paired code names both): the comment of the definition says
which US datum it is.

A function only PAL has (a `config/eu/map.tsv` row with `-` as its US name) is defined the same
way, as `src/versions/eu/<shared file>/func_eu_XXXXXXXX.cpp`, in the shared file whose code it
sits among: the file of the closest function before it that both versions have. Having no shared
definition to replace, it is added at the end of that file's unit. `c_status.tsv` has a row for
it under that name, noted `only in PAL`.

A function only PAL has can still be a US function's counterpart that the position pairing missed, because
PAL's own changes (fields moved for its wide text, an extra call) changed its bytes too much.
`tools/inventory.py` has a last step for these (`similar` in `config/eu/map.tsv`): the unpaired PAL
functions between the PAL copies of a US function's paired neighbours are scored by instruction
similarity and shared callees, and a clear one-to-one match is paired. Such a counterpart is
PAL's own definition of the US function, `src/versions/eu/<file>/<US function>.cpp`, like any
other (PAL's func_eu_001AD800, 780 bytes, is US DrawSlidingGlyphElement, func_001ACAA8, 760
bytes, with the fields 0x310 further on and func_eu_001374E0 called on the frame's layout). A
function the step still leaves unpaired and that PAL has no counterpart for stays `func_eu_`.

Two gaps of the tools, found on 2026-11-08. `version_src.py todo` lists game code only, so the
library functions only PAL has are found from `config/eu/map.tsv`. And a function whose closest
shared function lies in a `.c` file (PAL's four routines after libm's copy_sign.c, 0x20A730 to
0x20A870) cannot be built in that file's unit: they are defined in the unit of the library file
whose code they belong with (src/lib/memory_card_client.cpp, the "rom0:ROMVER" reader), which
builds and checks them the same way. A function only PAL has whose bytes are one of US's
original-assembly functions (func_001F7738, US func_00201720's routine linked a second time) is
classified as that by tools/classify_asm.py, as US's is.

    python3 tools/version_src.py todo      # the functions only PAL has, not yet defined: size, tags, file
    python3 tools/check.py src/versions/eu/main/00134000/func_eu_001374E0.cpp func_eu_001374E0

A definition counts only when it is EXACT in PAL, and the shared C stays EXACT in US. This
layout follows OpenRAC's (rac1-decomp, `docs/VERSIONS.md`; credited in
[THIRD_PARTY_NOTICES.md](../THIRD_PARTY_NOTICES.md)); the tools are ours.
