# The retail disc

What the retail discs hold and where, measured by this project on both of
them. It is the starting point for the asset research in OpenThievius: the
formats themselves are documented from retail's own code as that code is
decompiled, never from other projects or the prototype
([PROTOTYPE.md](PROTOTYPE.md)).

## The file system

The ISO 9660 file system lists only what the console needs to boot:

| File | US sector | PAL sector | |
| --- | ---: | ---: | --- |
| `SYSTEM.CNF` | 275 | 277 | boot configuration |
| `SCUS_971.98` / `SCES_509.17` | 276 | 278 | the executable |
| `IOPRP243.IMG` | 1113 | 1134 | IOP replacement modules |
| `SIO2MAN`, `PADMAN`, `MCMAN`, `MCSERV`, `LIBSD`, `989SND` `.IRX` | 1237– | 1258– | IOP modules |
| `USBD.IRX`, `IOP.IRX` | | 1346, 1364 | PAL only |

The listed files end at sector 1401 on US and 1448 on PAL. Everything the
game loads besides them, levels, models, textures and sound, is **outside the
file system**: unlisted sectors from **12345** to the end of the disc, on both
versions (1,368,320 sectors on US, 1,427,648 on PAL). The first of them is a
VAG sound header.

## What is known about that data

- **No names.** The executable holds no file names for it: its only device
  strings are `cdrom0:`, the IOP modules and `ioprp243.img`. The data is found
  by sector, through records the executable holds (below).
- **The start sector is not a constant.** 12345 (`0x3039`) appears once in
  the code, as the increment of a random number generator in the libraries
  (0x1F6728), so the base comes from the index or from data, not from an
  immediate.
- **Data only.** Measured over the whole data area: no MIPS function returns
  (`jr $ra`) at a rate above chance, where the executable's `.text` has about
  4,500 per MiB. Levels carry no code of their own, so there is no level or
  shared code to decompile as there is in some other PS2 games: everything is
  in the executable, and config/<version>/layout.tsv covers all of it.

## How the game finds its data

There is no index on the disc. Every piece of data the game loads is named by a 32-byte
record in the executable's read-only data, in which the start sector and the size are
hidden with XOR:

| Words (u32) | |
| --- | --- |
| 0 ^ 5 | start sector |
| 1 ^ 7 | size in bytes; 0 means no entry |
| 2 ^ 6 | identifier: records are compared on it |
| 3, 4 | never read |

The records are grouped in tables (US addresses):

| Table | Entries | What | Format on the disc |
| --- | ---: | --- | --- |
| 0x247AF0 | 46 × 0x2C | levels: record, level code (world × 0x100 + level), name, flags | LZ-compressed |
| 0x248490 | 17 × 0x20 | videos | MPEG program streams |
| 0x244F40 | 7 × 0x20 | sound banks, loaded by the IOP sound driver | |
| 0x248748 | 33 × 0x2C | music, by level code | VAG |
| 0x2482D8, 0x2628B0 | 7, 6 × 0x20 | sounds | VAG |
| 0x248470 | 1 | a file copied to the memory card | |

PAL has the same scheme at other addresses; its level records hold five sector ranges per
level.

Reading goes through the CD library's sector read (0x203B18), called by a blocking retry
wrapper (0x140CC8). Levels are read by a ring-buffered stream (0x137490) and decompressed
as they arrive (0x1378A0): LZSS over an 8 KiB window, a flag byte for eight items, a
reference of two bytes (13-bit position, 3-bit length + 3). Videos have their own
double-buffered stream (0x12FE70). Sound banks are loaded by the sound driver from a
sector the game sends it. After the tray has been opened, the game checks the disc by the
CRC-32 of sector 1,368,303 (US).

These tables cover 60% of the unlisted sectors. The levels themselves hold 269 more
records of the same form (263 VAG sounds, six videos), bringing it to 80%. The
rest, including 45 files that start `01 00 00 00`, is not yet accounted for.

## Next

1. **Each format, from its reader.** Levels, models, textures and sound are
   documented here, and the extractor written in OpenThievius, from the
   functions that parse them.
2. **The remaining data.** Find the records of the videos, sounds and the
   files starting `01 00 00 00` that no table names yet, and the part of the
   level parser that reads the records a level holds.
