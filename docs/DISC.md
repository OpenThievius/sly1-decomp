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

These tables cover 60% of the unlisted sectors. The levels hold the rest of the records
(see Levels), bringing it to all but 77 sectors.

## Levels

A level is one LZ-compressed file. Decompressed, it is read front to back by the
world's loader (0x1DCEA0, called from the level load at 0x1E4EA8) through a stream of
little-endian reads:

| Part | Format | Reader |
| --- | --- | --- |
| header | s32 size of the texture data at the end; u32 time stamp | 0x1DB928 |
| flags | u8 names flag (0 on retail); s16 sound bank (index into 0x244F40); u32 string count | 0x1DCEA0, 0x1DCCC0 |
| values | u32 count and two u32 counts of names, then the values, each a tagged type | 0x1C1190, 0x11BA28 |
| world properties | s16 field ids, ended by a negative one, each with its value | 0x11EC40 |
| music | an optional disc record and name, overriding the music table; empty on US | 0x138550, 0x1384A0 |
| level sound bank | a disc record, loaded by the sound driver | 0x138550, 0x1BEB10 |
| textures | CLUTs, images, shaders and a short list, each counted by a u16 | 0x1B3040 |
| objects | an s16 count, then per object its class, id and value index and the class's own data; objects hold their children the same way | 0x11ECB8 |
| texture data | at the next multiple of 16: CLUT colours and pixels, addressed by offset from the texture tables | 0x1DBA38 |

The texture data starts at the multiple of 16 after the objects; the file ends with 26 to
747 bytes, a copy of the bytes 0x1FFF before them, that the game never reads. When a level
is loaded again, or another with the same time stamp, the texture data is still in memory
and the stream stops before it. Every byte of every US level is read by retail's loaders
(see Objects).

The time stamps read as Unix times on 25 August 2002, within 32 minutes; the code only
compares them.

A level holds disc records of its own. The record after the music names the level's sound
bank: these are the 45 files that start `01 00 00 00`, one per level except the splash
screen. Three object classes read records: lists of steps (0x150570) and of events
(0x12BC38) name 1,362 VAG sounds and 13 videos (see Events). With them, the records name
1,355,898 of the 1,355,975 unlisted sectors; what remains is a 64-sector VAG at 454,000
and 13 empty sectors.

### Objects

The objects are a tree. A list is an s16 count, then per object an s16 class (an index
into the 149 entries at 0x247448, of which 0x01–0x91 are classes), an s16 id and an
s16 index into the value table (-1 for none); the object is created and its class's
load method (descriptor + 0x38) reads the rest. 56 classes have their own load method;
the others inherit their parent's. Most objects end with the common block (0x1289C0):

| Part | Format |
| --- | --- |
| placement | 3×3 matrix, 3-float position |
| flags and ranges | three u8, a u32, four f32 |
| properties | s16 field ids ended by a negative one, each with its value |
| geometry | model entries and meshes (0x162890) |
| options | u32 flags, then the matrices, references and values they select (0x128C10) |
| a list | u8 count of {s16, one f32 per geometry channel} |
| children | an object list, with this object as parent |

Class 0x03 and the classes under it put collision meshes before the common block
(0x1BAC30). The first object of every level is class 0x04 (the scenery, 39% of all
object bytes) or 0x86. Classes 0x83 and 0x88 hold lists of events (0x12B8C8) and are
another 21%.

Running retail's own loaders over the 46 US levels reads every object byte: in each
level the objects end exactly where the texture data must start for it to end where the
file's data does. The 26 to 747 bytes after the texture data repeat the bytes 0x1FFF
before them and are never read.

### Geometry

The geometry block (0x162890) is 52% of all level bytes. It holds a model as a list of
entries, each either an instance of an earlier entry or a set of meshes:

| Part | Format |
| --- | --- |
| header | two u8 flags; u8 count of s16 bones; u8 count of f32 morph weights (channels); u16 entry count |
| entry | u16 flags; for 0x1 an s16 entry index and a 4×3 matrix (an instance); fields selected by 0x2–0x200 (distances, a texture animation, an attachment); a bounding sphere; s16; three u8 |
| meshes | u16 count; each a bounding sphere, five u8 counts, then at a multiple of 4 the positions (3 f32), normals (3 f32), RGBA colours, UVs (2 f32) and four-byte vertex records; u16 shader; u8; u8 count of bone indices and their weights (f32 per position and bone); with channels, morph target positions and normals and per vertex u16 indices into them |
| line meshes | u16 count; each positions (3 f32), four-byte records of position indices, bones and weights, and morph targets |

A vertex record holds the indices of its position, normal, UV (0xFF none) and colour
(0x7F none), and in the colour byte's top bit the start of a triangle strip. The shader's
first byte chooses between a lit conversion, which uses the normals, and an unlit one.
Line meshes are drawn as GS lines. Instances (36,578 of 65,446 entries) read nothing
after their sphere and bytes. The file holds plain arrays: the loader builds the VIF
packets itself, copying only a line mesh's positions, records and weights unchanged.

A standalone parser written from this reads every geometry block of the 46 US levels
(23,944 blocks) exactly as retail's loader does, read for read.

### Animations

Classes 0x83 and 0x88 (20% of all level bytes) are animations. An animation (0x83,
0x12B8C8) holds an s16 object id, its length (an s16 count of 1/60 s, the unit of every
time below), a u16 count of target object ids, an s8 count of tracks, three event lists
and a property list. A track is an s16 target and s8 flags selecting a position (0x1),
a rotation in Euler angles (0x2), a scale (0x4), a weight (0x8) and a u8 count of morph
channels (0x10), each a curve whose s8 kind chooses its reader:

| Curve | Reader | Format |
| --- | --- | --- |
| Hermite | 0x11EFC8 | u16 count; per key time, f32 value, two s8 modes, f32 in and out slopes |
| Bézier | 0x11F210 | u16 count; per key time, f32 value, two s8 modes, four f32 handle offsets |
| linear | 0x11F568 | u16 count; per key time, f32 value |
| per axis | 0x11F798 | u8 axis mask, 3-float constant, a u8 kind and a scalar curve per set bit |
| vector | 0x11FA88 | u16 count; per key time, 3-float value, in and out tangents (Hermite) |

Vector keys are 73% of these bytes. A graph (0x88, 0x1B5F50) holds u8-counted states
{s16 id, s16 next} and transitions {s8, s16 from, s16 to, s32, f32}, a property list,
an s16 it drops, then for each transition whose s8 is set an animation created inline
(class, id and value index as in an object list).

### Events

An animation's three event lists (0x12BC38) run when it starts, as its time passes
each event (the second list, the only one with times) and when it ends. A list is an s8
count; an event an s8 kind (0x00–0x3B), its time in the timed list, and a payload of 0
to 32 bytes chosen by the kind. Kind 0x00 plays a sound effect at an object, 0x2C a
streamed sound and 0x33 a video, both named by a disc record; the others start, stop
and adjust animations, objects and the world.

Class 0x65 (mostly created inline by 0x53) ends with a list of steps (0x150570): an s8
count of steps, each an s8 kind (0–7) and its payload; kind 0 plays a streamed sound and
kind 7 a video from a disc record, kind 3 holds two floats, two bytes, four ids and a
string.

The events and steps name 1,362 VAG sounds and 13 videos, among them the 172,705-sector
video at 593,237. A standalone parser written from this reads every animation, graph and
step list of the 46 US levels (14,753 blocks, 34.9 MB) exactly as retail's loaders do,
read for read.

## Next

1. **Each format, from its reader.** Field by field: class 0x03's collision meshes and the
   event lists (0x11FA88 and its siblings), which hold most of a level's bytes; what each
   class is; PAL's levels. Then models, textures and sound, documented here, and the
   extractor written in OpenThievius, from the functions that parse them.
2. **The remaining data.** The 64-sector VAG at 454,000, which no record found yet names;
   what the event kinds and the object classes are in the game.
