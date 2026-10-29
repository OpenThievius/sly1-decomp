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
