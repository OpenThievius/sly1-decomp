// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x6C (descriptor D_002214A0, 0x2360 bytes): the world, the object every level object
// has as its level (BaseObject::world). Written for this project from what retail's code does
// (config/us/classes.tsv).
//
// The fields follow the parent's and end at the size the descriptor gives; the pads keep
// every field at its retail offset. Only the fields the matched methods read are named, and
// the lists and pools other classes' methods reach through BaseObject::world; the many sub-records
// func_001DB4C8 sets up are reached by offset (its SUB macro).
#ifndef WORLD_H
#define WORLD_H

#include "placed_object.h"
#include "shapes.h"      // U64P

struct C17;
struct EffectOwner;
struct Contacts03;
struct QueuedCall;     // an entry of the callback list at 0x1EC8 (queued_call.h)

struct Actor6C;

// The methods slots 0x118 and 0x11C of an object that the world updates every frame.
struct ActorVtbl6C {
    u8 pad0[0x8];
    s32 f8;                 // 0x8
    u8 padC[0x118 - 0xC];
    void (*update)(Actor6C* self, f32 dt);   // 0x118
    void (*post)(Actor6C* self);             // 0x11C
};

// An object in one of the world's lists (func_001EA118).
struct Actor6C {
    ActorVtbl6C* vtable;    // 0x00
    u8 pad4[0x1C - 0x4];
    void* f1C;              // 0x1C
    u8 pad20[0x34 - 0x20];
    void* f34;              // 0x34
    u8 pad38[0x228 - 0x38];
    s32 tries;              // 0x228: how often func_00129D70 failed it
    u8 pad22C[0x30C];
    u64 flags;              // 0x538: bit 63 asks for func_001BB9D0
};

// A list head: the first element, the one after it, and the offset of the link in an element.
struct ActorList6C { Actor6C* head; u8 pad4[4]; s32 offset; };

// A pool of free records of one size (func_001B5EA0 takes the first, func_001B5EE0 clears it).
struct Pool6C { s32 size; void* base; void* head; };

// A setting of an IOP channel: the index into its table and the value (func_001C08B0).
// A sound of the level (20 bytes; func_001C0A50 appends one, func_001C0B38 starts them all):
// the sound and two pairs of floats handed to func_001BFCD8 as blocks.
struct WorldSoundEntry {
    s32 sound;              // 0x00: its g_soundEntries row
    U64P repeat;            // 0x04: the repeat interval and a second float (4.0, 6.0 at first)
    union {
        U64P range;         // 0x0C: (3000.0, 8000.0) at first
        struct {
            f32 range0;     // 0x0C: func_001C0AB8 sets 8000 - 50 y
            f32 range1;     // 0x10: func_001C0AB8 sets 8000 - 50 x
        };
    };
};

struct IopChannelSetting { s32 index; s32 value; };   // base: the records' block (func_001B5DD0)

struct World : BaseObject {
    s32 count34;            // 0x34: the 0x03 objects in the world (func_001B7A98, func_001B7B78)
    s32 count38;            // 0x38: the bodies among them (0x03 objects without a parent)
    List01 bodies;          // 0x3C: the bodies, linked at Collider::link2D0 (offset 0x2D0)
    List01 list48;          // 0x48: the objects without a parent (func_00182C80)
    List01 list54;          // 0x54: the placed objects without a parent (func_001240F8)
    ActorList6C list60;     // 0x60: the objects func_00129D70 tries to start
    ActorList6C list6C;     // 0x6C: the objects updated every frame
    List01 list78;          // 0x78: the placed objects without a parent that have +0x294 set
    u8 pad84[0x1884 - 0x84];
    void* f1884[0x95];      // 0x1884: the objects by id, chained at BaseObject::nextById (func_0015A4F0)
    void* buf1AD8;          // 0x1AD8: 0x4800 bytes
    void* buf1ADC;          // 0x1ADC: 0x10000 bytes, a byte for each pair of contact tables (func_001DC828)
    Contacts03* tables;     // 0x1AE0: the bodies' contact tables (func_001DC828 numbers one by its place)
    Contacts03* freeTables; // 0x1AE4: the tables not in use (func_001DC7D0 takes the first)
    Contacts03* usedTables; // 0x1AE8: the tables in use
    s32 f1AEC;              // 0x1AEC
    Pool6C pool1AF0;        // 0x1AF0: 0x10-byte records, the contact rows (func_001DC828 gives them back)
    Pool6C pool1AFC;        // 0x1AFC: 0xE0-byte records, the contacts (func_001BC4D8)
    Pool6C pool1B08;        // 0x1B08: 0x10-byte records (func_001DBB50, func_001DBB90)
    Pool6C pool1B14;        // 0x1B14: the 0x14-byte QueuedCall entries (func_001DBBD8, func_001DBC18)
    Pool6C pool1B20;        // 0x1B20: the Attachment records (func_00121228 takes one, func_00121358 gives it back)
    Pool6C pool1B2C;        // 0x1B2C: the 0x140-byte records of kind t219c (func_0019EA78), 0x180 of them
    EffectOwner* f1B38;             // 0x1B38
    EffectOwner* f1B3C;             // 0x1B3C
    Pool6C pool1B40;        // 0x1B40: 0x10C0-byte records (func_00139C70)
    u8 pad1B4C[0x1B58 - 0x1B4C];
    Pool6C pool1B58;        // 0x1B58: the 0xEC-byte AnimationPlayer records (func_0012D3F8)
    void* f1B64;            // 0x1B64
    s32 f1B68;              // 0x1B68
    s32 f1B6C;              // 0x1B6C
    void* f1B70;            // 0x1B70
    s32 f1B74;              // 0x1B74
    s32 f1B78;              // 0x1B78
    ActorList6C list1B7C;   // 0x1B7C
    Pool6C pool1B88;        // 0x1B88: the 0x40-byte StateWalker handles (func_001B6290)
    List01 list1B94;        // 0x1B94: the handles in use (func_001B6290 adds each)
    u8 pad1BA0[0x1BAC - 0x1BA0];
    List01 list1BAC;        // 0x1BAC: the sound records (func_001C0808 walks them)
    Pool6C pool1BB8;        // 0x1BB8: the sound level entries (func_001BEDF8 gives one back)
    List01 list1BC4;        // 0x1BC4: the sound level entries in use (func_001BEE48 walks them)
    Pool6C pool1BD0;        // 0x1BD0: the records func_00158F80 queues in list1BDC
    List01 list1BDC;        // 0x1BDC
    List01 list1BE8;        // 0x1BE8: class 0x51's objects (func_00183DC0)
    Pool6C pool1BF4;        // 0x1BF4: the 0x2E0-byte records of PlacedObject::f284
    List01 list1C00;        // 0x1C00: the PlacedObject::f284 records in use
    u8 pad1C0C[0x1C24 - 0x1C0C];
    u8* f1C24;              // 0x1C24
    s32 f1C28;              // 0x1C28
    s32 f1C2C;              // 0x1C2C
    void* f1C30;            // 0x1C30
    s32 f1C34;              // 0x1C34
    s32 f1C38;              // 0x1C38
    List01 list1C3C;        // 0x1C3C: class 0x53's objects
    List01 list1C48;        // 0x1C48: class 0x40's objects (offset 0x5DC)
    List01 list1C54;        // 0x1C54: the 0x55 family's objects
    List01 list1C60;        // 0x1C60: class 0x41's objects (offset 0x600)
    List01 list1C6C;        // 0x1C6C: class 0x7C's objects (func_0019C3D0, func_0019C408)
    List01 list1C78;        // 0x1C78: class 0x46's objects (offset 0x56C)
    List01 list1C84;        // 0x1C84: class 0x81's objects
    List01 list1C90;        // 0x1C90: class 0x71's objects
    List01 list1C9C;        // 0x1C9C: class 0x72's objects
    List01 list1CA8;        // 0x1CA8: class 0x31's objects (offset 0xAF0)
    List01 list1CB4;        // 0x1CB4: class 0x4D's objects
    List01 list1CC0;        // 0x1CC0: class 0x4D's objects
    List01 list1CCC;        // 0x1CCC: class 0x10's objects (offset 0xC10)
    u8 pad1CD8[0x1CE4 - 0x1CD8];
    C17* f1CE4;             // 0x1CE4: the class 0x17 object (func_0019A1E0)
    union {
        BaseObject* slot1CE8[31];  // 0x1CE8: objects by key, at the index func_0011ECA0 gives (func_0011ECB8)
        struct {
            u8 pad1CE8[0x1D14 - 0x1CE8];
            s32 f1D14;      // 0x1D14: class 0x32's default for its +0x5D4 (func_001B04D0)
            u8 pad1D18[0x1D28 - 0x1D18];
            s32 f1D28;      // 0x1D28
            u8 pad1D2C[0x1D60 - 0x1D2C];
            BaseObject* f1D60;     // 0x1D60: told (slot 27) when a 0x55-family object ends
        };
    };
    u8 f1D64;               // 0x1D64
    u8 f1D65;
    u8 f1D66;
    u8 pad1D67;
    f32 f1D68;              // 0x1D68
    f32 f1D6C;              // 0x1D6C
    s32 f1D70;              // 0x1D70: -1
    s32 f1D74;              // 0x1D74
    u8 pad1D78[0x1D7C - 0x1D78];
    f32 f1D7C;              // 0x1D7C
    s32 soundCount;         // 0x1D80: the number of soundEntries (func_001C0A50)
    WorldSoundEntry soundEntries[16];  // 0x1D84: the level's sounds, started by func_001C0B38
    void* f1EC4;            // 0x1EC4: the class 0x86 object (func_001EE900)
    QueuedCall* f1EC8;         // 0x1EC8: the callback list's first entry (func_001DBCC8 appends, func_001DBE48 runs them)
    QueuedCall* f1ECC;         // 0x1ECC: its last
    s32 regroupCount;       // 0x1ED0: objects queued for regrouping (func_0015F678; func_0015FA58 clears it)
    union {
        void* buf1ED4;      // 0x1ED4: 0x1000 bytes
        PlacedObject** regroupObjects; // the queue func_0015F678 appends to
    };
    u8 pad1ED8[0x1EE0 - 0x1ED8];
    Vec02 gravity;          // 0x1EE0: every 0x03 object's at set-up (func_001B7968)
    s32 f1EF0;              // 0x1EF0: the number of f1EF4 entries
    void* f1EF4;            // 0x1EF4: 8-byte entries, a key and a value (func_001C1190, func_001C1390, func_001C13E8)
    s32 f1EF8;              // 0x1EF8
    s32 f1EFC;              // 0x1EFC
    u8 f1F00[0x40];         // 0x1F00
    u8 pad1F40[0x2300 - 0x1F40];
    s32 count2300;          // 0x2300: numbers class 0x2E's objects (func_001993F0)
    s32 count2304;          // 0x2304: numbers class 0x38's objects (func_001411A8)
    f32 f2308;              // 0x2308
    f32 f230C;              // 0x230C
    void* f2310;            // 0x2310
    void* f2314;            // 0x2314
    f32 f2318;              // 0x2318
    s32 f231C;              // 0x231C
    s32 f2320;              // 0x2320
    void* f2324;            // 0x2324
    IopChannelSetting channel2[4]; // 0x2328: the stack of IOP channel 2 settings (func_001C08B0 pushes, func_001C0950 pops)
    s32 channel2Count;      // 0x2348
    f32 f234C;              // 0x234C
    f32 f2350;              // 0x2350
    s32 f2354;              // 0x2354
    s32 f2358;              // 0x2358: 1 after func_001EBEB0 (class 0x13)
    s32 f235C;              // 0x235C
};

typedef char check_World[sizeof(World) == 0x2360 ? 1 : -1];

void func_001DB4C8(World* self);      // 0x6C slot 0
void func_001EA118(World* self);      // 0x6C slot 17 (every frame)

#endif
