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
`config/eu/c_data_status.tsv`). Each global of `config/us/c_data.tsv` is built (a whole file's
section, which is one row) and its bytes, with every relocated word resolved to the PAL address of
its target, are compared with PAL's retail bytes at the global's PAL address. A row is `match`,
`differs` or `absent` (`.bss`, which no file holds, or no PAL address). Nothing is masked: a table
whose pointers reach something PAL does not have, or whose bytes PAL changed, is `differs`; the
row's note says where the bytes first differ and what the words that differ are (text, pointers,
other data). The report counts the `match` rows' bytes as PAL's matched data (never as complete
data: PAL links no C), on 2026-11-11 332,070 of 464,563 (71.48%; 288,919, 62.19%, before PAL's own data), which with the original assembly the reports count (the `.vutext` microprograms) is 353,910 bytes, 76.18% of PAL's data (66.89% before).

### PAL's own data

A global PAL holds differently (another value, a string id where US has a pointer, a table with
other rows) gets a definition of its own, the same way a function does:

    src/versions/eu/<path of the shared file without .cpp>/D_XXXXXXXX.cpp

holding that one definition, from its type to its `;`, under its US address name (the shared file
may write the readable name, `config/names/`; the definition is found under either). Its type is
the US definition's and its initial values are what PAL's bytes show, as a US global's are what
retail's show: PAL's string ids are `(const char*)0x47`, a word PAL fills where US has a zero is
written there, and where PAL's table has one more row than US's the extra row's words are written
into the globals that follow (the declarations stay US's). A comment says what differs. No global,
padding or type is invented for PAL: a definition that needs one is not written, and the row stays
`differs` with its note (below).

`version_src.unit_text` puts it in the shared file's unit in place of the shared definition
(`version_src.data_span` finds the definition: a top-level statement, never an `extern`), so a
PAL unit holds its functions and its globals together. The data check builds that unit for each
file in which PAL has anything of its own (`version_src.has_own`: a function or a global in
`src/versions/eu/`, or a declaration that reads `VERSION_EU`), built whole as the US build builds it
(`config/us/files.tsv`) and with the data the file includes (`INCLUDE_RODATA`, `INCLUDE_DATA`),
which the unit for a function check leaves out; any other file is built as the US build builds it.
So PAL's rodata is what PAL's own functions and globals make: the string literals and the jump
tables of a function PAL defines itself are PAL's, and a row of such a file can match for the
first time (six did). The comparison is the same as ever: PAL's bytes at the PAL address, every
pointer translated through the same placement, never masked. The shared C stays EXACT in US and
the US build never sees these files.

    python3 tools/version_src.py data      # the globals PAL defines itself, with their files
    python3 tools/data_check.py            # (through tools/version_check.py) c_data_status.tsv
    python3 tools/data_check.py --check    # a definition's file names a global its shared file defines

Only globals both versions have are defined this way. Data only PAL has (`D_eu_XXXXXXXX`, with no
US counterpart to replace) has no row in `c_data_status.tsv`, which lists US's globals, so PAL's
extra data is not counted yet; it would be added at the end of the unit like a function only PAL
has, and needs rows of its own.

What stays `differs`, and why, from the last full check:

| Cause | Rows | Globals |
|---|---:|---|
| Literals and jump tables of functions PAL has no C for: strings translated, reordered or turned into ids, floats, cases elsewhere. The named arrays of these rows that are PAL's own data are defined (`D_002495C0`, `D_002497D8`, `D_00249838`), the rest is the code's | 9 | `D_00249428`, `D_00249CA0`, `D_0024A2D0`, `D_0024A7A0`, `D_0024B280`, `D_0024B660`, `D_0024CBD0`, `D_0024DB20`, `D_0024E600` |
| One word that no global holds, or that needs another row's section: the pad word after `g_buildFrame` (PAL has 1 in it), the pointer to the literal `"ab"`, a method table slot that holds another method, a function with no PAL pairing | 4 | `D_00261F70`, `D_002743A0` (every global of it is defined, but the literal `"ab"` moves with the rodata of `D_0024CBD0`), `D_0024B438`, `D_00217380` |
| Objects a constructor fills in (`BoxStyle D_00262988`, `D_002629A8`): PAL's bytes there are static data, and a C++ object with a constructor has no initial value to write; a table PAL grew and moved (`D_0026A138`, the pause menu's rows and the pointers into them) | 2 | `D_00262718`, `D_00269CD8` |
| Grown tables inside labels the file includes from the disassembly (`INCLUDE_DATA`), which are not C | 2 | `D_00275940`, `D_00275B60` |
| Tables of hashes: about 30 `extern const` tables of `global_tables.cpp` hold other words (1,261), each a struct or hash list that needs PAL's value for every field; not defined yet | 1 | `D_00244F40` |

The 18 differ in `config/eu/c_data_status.tsv` with a note of where, and the 201 matches are
the 185 of before, 10 that PAL's own globals made (`D_00262A30`, `D_002779C0`, `D_0027AF70`,
`D_0026C3E0`, `D_00275140`, `D_00261090`, `D_002699B0`, `D_00274F38`, `D_002758E0`, `D_002623C0`) and
6 that the PAL unit made without any (`D_002499F0`, `D_00249FE0`, `D_0024A860`, `D_0024DAA0`,
`D_0024E1C0`, `D_0024DCB0`: the jump tables and strings of functions PAL defines itself).

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
included labels equal PAL's too (the two retail images agree on them). Only 2 of the rows that differ
differ inside an included label (`D_00275940`, `D_00275B60`, both tables PAL grew).

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
