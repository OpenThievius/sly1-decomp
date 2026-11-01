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

    python3 tools/check.py src/versions/eu/main/00140000/func_00142F10.cpp func_00142F10
    python3 tools/version_check.py      # c_status.tsv notes these rows `version-specific`

What makes PAL differ, from the first `differs` rows read one by one:

- **50 Hz.** Times and rates: func_00142F10 clamps the frame step to 1/50 to 1/25 of a second,
  where US has 1/60 to 1/30.
- **Field offsets.** Some objects are laid out differently (a field at 0x590 where US has it at
  0x304): the PAL definition uses a struct of its own.
- **Unsigned bytes.** PAL's string and character functions read `u8` where US reads `s8`.
- **Other calls and arguments.** A call to a function only PAL has, or one more argument.

Code and data only PAL has are named `func_eu_XXXXXXXX` and `D_eu_XXXXXXXX`, and reach that PAL
address alone (`tools/check.py`).

A function only PAL has (a `config/eu/map.tsv` row with `-` as its US name) is defined the same
way, as `src/versions/eu/<shared file>/func_eu_XXXXXXXX.cpp`, in the shared file whose code it
sits among: the file of the closest function before it that both versions have. Having no shared
definition to replace, it is added at the end of that file's unit. `c_status.tsv` has a row for
it under that name, noted `only in PAL`.

    python3 tools/version_src.py todo      # the functions only PAL has, not yet defined: size, tags, file
    python3 tools/check.py src/versions/eu/main/00134000/func_eu_001374E0.cpp func_eu_001374E0

A definition counts only when it is EXACT in PAL, and the shared C stays EXACT in US. This
layout follows OpenRAC's (rac1-decomp, `docs/VERSIONS.md`; credited in
[THIRD_PARTY_NOTICES.md](../THIRD_PARTY_NOTICES.md)); the tools are ours.
