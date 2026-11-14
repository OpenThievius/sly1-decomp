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
| 0x247AF0 | 46 × 0x2C | levels: record, level code (world × 0x100 + level), name, goal flags | LZ-compressed |
| 0x248490 | 17 × 0x20 | videos | MPEG program streams |
| 0x244F40 | 7 × 0x20 | sound banks, loaded by the IOP sound driver | |
| 0x248748 | 33 × 0x2C | music, by level code | VAG |
| 0x2482D8, 0x2628B0 | 7, 6 × 0x20 | sounds | VAG |
| 0x248470 | 1 | a file copied to the memory card | |

PAL has the same scheme at other addresses (see PAL).

A level's goal flags (0, 2 or 0xE) say which goals it offers, each kept done or not in
the bit of the same value in the level's save word, whose bit 0x1 says it has been
entered: 0x4 a collection goal, set by the collection code (0x19AD68), 0x8 a best time
(0x1E02C8), and 0x2 a further goal whose setter is not identified. The
completion percentage and the unlocks count these bits over every level that offers
them (0x160B28, 0x1602A0).

Reading goes through the CD library's sector read (0x203B18), called by a blocking retry
wrapper (0x140CC8). Levels are read by a ring-buffered stream (0x137490) and decompressed
as they arrive (0x1378A0): LZSS over an 8 KiB window, a flag byte for eight items, a
reference of two bytes (13-bit position, 3-bit length + 3). Videos have their own
double-buffered stream (0x12FE70). Sound banks are loaded by the sound driver from a
sector the game sends it. After the tray has been opened, the game checks the disc by the
CRC-32 of sector 1,368,303 (US).

These tables cover 60% of the unlisted sectors. The levels hold the rest of the records
(see Levels), bringing it to every sector but 13 empty ones.

## Levels

A level is one LZ-compressed file. Decompressed, it is read front to back by the
world's loader (0x1DCEA0, called from the level load at 0x1E4EA8) through a stream of
little-endian reads:

| Part | Format | Reader |
| --- | --- | --- |
| header | s32 size of the texture data at the end; u32 time stamp | 0x1DB928 |
| flags | u8 debug-data flag (0 on retail); s16 sound bank (index into 0x244F40); u32 count of debug blocks | 0x1DCEA0, 0x1DCCC0 |
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

The debug-data flag, when set, makes the loaders read and skip blocks the game never uses:
count − 1 length-prefixed blocks after the flags (0x1DCCC0), three per script entry and
the two counts' worth after the values (0x1C1190), and five u16 per value (0x11BA28). It is
0 in every retail level, so none of these blocks is there and the count is read and ignored.

The time stamps read as Unix times on 25 August 2002, within 32 minutes; the code only
compares them.

A level holds disc records of its own. The record after the music names the level's sound
bank: these are the 45 files that start `01 00 00 00`, one per level except the splash
screen. Three object classes read records: lists of steps (0x150570) and of events
(0x12BC38) name 1,362 VAG sounds and 13 videos (see Events). With them, the records name
every unlisted sector but 13 empty ones (the 64-sector VAG at 454,000 is named by the
record at 0x26A118, which 0x1936A0 reads).

### Textures

The texture tables (0x1B3040) say what the texture data at the end of the level holds and
how the GS draws it. Each table is counted by a u16:

| Table | Format | Reader |
| --- | --- | --- |
| CLUTs | 12 bytes: u32 load class; u16 colour count; u16 GS blocks; u32 offset in the data | 0x1B2B50 |
| images | 20 bytes: u16 width, height; u32 load class; u8 PSM; u8 buffer width (TBW); u16 GS blocks; u32 byte size; u32 offset in the data | 0x1B2CA8 |
| shaders | a u16 count of animated ones, then per shader 20 bytes (u8 type 0–10, u8 flags, s16 id, two RGBA colours, u32 load class, s16 id of the shader whose textures a type-0 shader's third pass takes, u8 never read, u8 set count), a texture animation (0x1B4A10) and its texture sets: u16 never read, u16 clamp bits, u8 image count, u8 CLUT count, then u16 image and CLUT indices | 0x1B3040, 0x1B2F00 |
| fonts | 16 bytes: u16 image, u16 CLUT, u8 never read, u8 advance of a character the font lacks, u8 line height, u8 slot, f32 scale, u16 glyph count; per glyph u16 character, x, y, width | 0x15D8A8 |

Images are 4-bit (PSMT4, 11,003), 8-bit (PSMT8, 2,570) or 32-bit (41), of powers of two
from 8 to 1,024 texels, their pixels in GS rows, low nibble first. A CLUT holds RGBA
colours with alpha up to 0x80; up to 16 colours serve a 4-bit image, more an 8-bit one,
stored in the GS's CSM1 order. The code builds each TEX0 from these fields (TBW, PSM,
TW and TH as log2, CBP and TBP0 from its own GS memory allocator, CPSM 32-bit, CLD 1),
and a shader's pass ORs the image's TEX0 with its CLUT's. Type-0 shaders, most of them,
draw one image three times with three CLUTs, the last two added.

The load class chooses when a texture goes to GS memory: 0x10000000 at level load, from
block 0x1E00; zone bits 0–27 on request (0x1B3488); five groups and 0x20000000 into a
swap area from 0x1400; 0x80000000 the fonts. The texture data holds every CLUT, then every
image, in table order at multiples of 16, ending exactly at its size; it stays in memory
and is sent in place, each texture as BITBLTBUF, TRXPOS, TRXREG and TRXDIR writes, an
IMAGE GIFtag and a DMA reference to its bytes.

A standalone parser written from this reads the texture tables of the 46 US levels
(215,790 reads) exactly as retail's loader does, read for read; every index lies within
its CLUT's colours, every offset and size within the data, every glyph within its image.

### Objects

The objects are a tree. A list is an s16 count, then per object an s16 class (an index
into the 149 entries at 0x247448, of which 0x01–0x91 are classes), an s16 id and an
s16 index into the value table (-1 for none); the object is created and its class's
load method (descriptor + 0x38) reads the rest. 56 classes have their own load method;
the others inherit their parent's. Most objects end with the common block (0x1289C0):

| Part | Format |
| --- | --- |
| placement | 3×3 matrix, 3-float position |
| view and fade | three u8 modes (whether the view mask follows the world's zones, per-part view masks, per-part fades); u32 view mask, the camera's bits the object is drawn in; f32 far and near fade distances (the largest float for the defaults, 10¹⁰ and 2,000); f32 a second radius, read by zone colliders; f32 bounding radius |
| properties | s16 field ids ended by a negative one, each with its value |
| geometry | model entries and meshes (0x162890) |
| options | u32 flags, then the matrices, references and values they select (0x128C10) |
| value sets | u8 count of {s16 key, one f32 per morph channel}: a script selects one by key and its floats become the channels' weights (0x12B2F8) |
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
| header | u8 skinned (drawn on the dynamic, lit path; the loader also sets it for bones or morphs); u8 never read; u8 count of s16 bones; u8 count of f32 morph weights (channels); u16 entry count |
| entry | u16 flags; for 0x1 an s16 entry index and a 4×3 matrix (an instance); the fields the other flags select (below); a bounding sphere; s16 never read; u8 billboard (faces the camera when nonzero); u8 draw kind; u8 lighting mask (the light kinds that reach it) |
| meshes | u16 count; each a bounding sphere, five u8 counts (positions, normals, colours, UVs, vertex records), then at a multiple of 4 the positions (3 f32), normals (3 f32), RGBA colours, UVs (2 f32) and four-byte vertex records; u16 shader; u8 a 0–255 value the lit conversion scales to 0x7FA6 in its VIF header; u8 count of bone indices and their weights (f32 per position and bone); with channels, morph target positions and normals and per vertex u16 indices into them |
| line meshes | u16 count; each positions (3 f32), four-byte records of position indices, bones and weights, and morph targets |

An entry's flags select, in order: 0x2 a u32 never read; 0x4 an f32 sort depth, stored
squared with its sign (the largest float: the camera distance); 0x8 an f32 fog value; 0x10
and 0x20 the far and near fade distances, used in per-part fade mode; 0x40 a texture
animation; 0x80 a facing axis and cubic (32 bytes) that fade the entry as the camera sees it
edge-on; 0x100 an attachment (s16 id, s8 bone and, for a bone, four f32 and a 4×4 matrix,
then three u8, the first sizing the extra positions); 0x200 an f32 scale of its radius for
the lights' sphere tests. A draw kind of 3, 4, 7 or 8 becomes 0xD while the object fades,
5 or 9 becomes 0xE.

A vertex record holds the indices of its position, normal, UV (0xFF none) and colour
(0x7F none), and in the colour byte's top bit the start of a triangle strip. The shader's
first byte chooses between a lit conversion, which uses the normals, and an unlit one.
Line meshes are drawn as GS lines. Instances (36,578 of 65,446 entries) read nothing
after their sphere and bytes. The file holds plain arrays: the loader builds the VIF
packets itself, copying only a line mesh's positions, records and weights unchanged.

A standalone parser written from this reads every geometry block of the 46 US levels
(23,944 blocks) exactly as retail's loader does, read for read.

### Collision

Class 0x03 and the classes under it read a collision prefix before the common block
(0x1BAC30): 22.6% of all level bytes.

| Part | Format |
| --- | --- |
| flag | u8: the meshes are used in place (class 0x04, the scenery) or copied per object |
| collision mesh | f32 radius; u16 count of vertices (3 f32); u16 face count; u16 link count; per face three u16 vertex indices (its plane), a bounding sphere (f32 radius, 3 f32 centre) and a u8 count of links {u16, u16 the shared edge's two vertices, u16 the other face} |
| its tree | u16 node count, u16 (the same count), per node u16 face, u16 back child, u16 front child (0xFFFF none) |
| mass | f32 mass, 3×3 inertia tensor, 3 f32 offset |
| groups | u16 count of {s16, u16 geometry entry}, runs that each start at an s16 of 0 or more; u32 count (0 or the node count) of s16 node groups, per tree node the run it starts |
| face references | u32 count of {s16 geometry entry, s16 mesh}, then if any an s16 start index per face and one more |
| second mesh | a mesh and its tree, the same format (empty in most objects) |

Faces are planar polygons: the three indices only give the plane, which the loader
computes. Each shared edge is stored once, with the face that owns it. The tree is a BSP
tree over the faces' planes, rooted at node 0, its back child always the next node; a
sphere goes to the front child when wholly in front of the plane, to the back child when
wholly behind, to both otherwise. Node groups fade the scenery between the camera and the
player: the camera's line to the followed object is run through the tree, and each node it
crosses fades its run of geometry entries for 0.1 s (0x143BE0); face references are empty
on US. Objects with no collision mesh often carry a unit-density sphere's mass and inertia.

A standalone parser written from this reads every prefix of the 46 US levels (4,637
objects) exactly as retail's loader does, read for read.

### Animations

Classes 0x83 and 0x88 (20% of all level bytes) are animations. An animation (0x83,
0x12B8C8) holds an s16 object id, its length (an s16 count of 1/60 s, the unit of every
time below), a u16 count of target object ids, an s8 count of tracks, three event lists
and a property list. A track is an s16 target and s8 flags selecting a position (0x1),
a rotation in Euler angles (0x2), a scale (0x4), a weight (0x8) and a u8 count of morph
channels (0x10), each a curve whose s8 kind chooses its reader. Flag 0x20 marks the track
whose position moves the object itself: the loader keeps it apart from the others, and the
characters' movement reads it.


| Curve | Reader | Format |
| --- | --- | --- |
| Hermite | 0x11EFC8 | u16 count; per key time, f32 value, s8 never read, s8 mode (5 holds the value to the next key), f32 in and out slopes |
| Bézier | 0x11F210 | u16 count; per key time, f32 value, s8 never read, s8 mode (as Hermite), four f32 handle offsets |
| linear | 0x11F568 | u16 count; per key time, f32 value |
| per axis | 0x11F798 | u8 axis mask, 3-float constant, a u8 kind and a scalar curve per set bit |
| vector | 0x11FA88 | u16 count; per key time, 3-float value, in and out tangents (Hermite) |

Vector keys are 73% of these bytes. A graph (0x88, 0x1B5F50) holds u8-counted states
{s16 id, s16 next: the state to go on to on arriving, -1 none} and transitions {s8 has an
animation, s16 from, s16 to, s32 flags (0x1 walked both ways, 0x2 cut short when the target
changes), f32 weight in a random choice among equal routes}, a property list, an s16 never
read, then for each transition with an animation the animation, created inline (class, id
and value index as in an object list); a transition without one is taken at once.

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

## PAL

PAL holds every level five times, once per language, and moves the localized sound into
the levels. Its level table (0x2490F0) has 46 records of 0xAC bytes: five disc records, the
level code at +0xA0, at +0xA4 the id of the level's name in the level's string table, and
the flags at +0xA8. The copy read is chosen by a language slot (0x263710): at start-up from
the system language (0x160538, an entry of the init table; values 1, 2, 4, 3, 5 give slots
0 to 4, anything else slot 0), later from the language menu, which reloads level 0x003. The
copies' strings make the slots English, French, German, Spanish and Italian.

Videos (0x24B0D0), sound banks (0x246440), the memory-card file and the disc check (sector
1,427,630) are tables as on US. The music table (0x24B388, 33 × 0xC) keeps only the level
code, a float and the credits; the music is named by the level's own record. The sounds the
US tables name (0x2482D8, 0x2628B0, 0x26A118) become indices into 14 voice records each
level holds.

A PAL level is a US level with two more parts and three changed fields, read by PAL's world
loader (0x1DDC68):

| Part | Format | Reader |
| --- | --- | --- |
| strings | after the flags: u16 count; per string a u16 length and that many 16-bit characters (190 in every level, the same in all levels of a language) | 0x1DDA10, 0x1387C8 |
| voices | after the level sound bank: 14 disc records | 0x1DDC68 |
| event kind 0x36 | s16, s16 and a string id, where US has a string | 0x12BD58 |
| step kind 3, class 0x82 | the name in 16-bit characters | 0x150820, 0x192CD8 |

Everything else is read by the same code as on US. Running retail PAL's loaders over the
230 level copies, the US parsers read every geometry block (119,740) and collision prefix
(23,185) exactly, read for read, and with the changes above every animation, graph and step
list (46,775 blocks); in every copy the objects end exactly where the texture data must
start. The copies of a level differ in their strings, sounds, music and texture data, not in
their objects; PAL English has two objects more than US in levels 0x003, 0x305 and 0x306.

The records of the executable and of the levels name 1,415,288 of PAL's 1,415,303 unlisted
sectors: 230 level copies, 17 + 13 videos, the sound banks, 164 music streams, 190 level
sound banks, 70 voices and 2,625 event and step sounds (525 per language). What remains is
15 empty sectors at the end of the disc.

## Next

1. **The sound banks' own format,** which the IOP's sound driver reads, not the executable;
   then the extractor, written in OpenThievius from these readers. Every level field the
   executable reads has its role above where the code shows one (2026-11-14); the rest are
   marked never read or by their shape.
2. **What the data is in the game.** The event kinds and object classes, which so far
   have only a shape; PAL's language-specific music and its voice index 5.
