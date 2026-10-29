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
  by sector, through an index the code reads.
- **The start sector is not a constant.** 12345 (`0x3039`) appears once in
  the code, as the increment of a random number generator in the libraries
  (0x1F6728), so the base comes from the index or from data, not from an
  immediate.
- **Data only.** Measured over the whole data area: no MIPS function returns
  (`jr $ra`) at a rate above chance, where the executable's `.text` has about
  4,500 per MiB. Levels carry no code of their own, so there is no level or
  shared code to decompile as there is in some other PS2 games: everything is
  in the executable, and config/<version>/layout.tsv covers all of it.

## Next

1. **The loader.** Find, by decompiling it, the code that reads sectors
   (the calls into the CD library, then their callers) and how it locates
   the index: where it is, how it is stored, and how an entry names a
   sector range.
2. **Each format, from its reader.** Levels, models, textures and sound are
   documented here, and the extractor written in OpenThievius, from the
   functions that parse them.
