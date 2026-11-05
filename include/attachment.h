// SPDX-License-Identifier: AGPL-3.0-or-later
// Kind t2195: the attachments of a placed object (class 0x02, c02.h): a record that gives the
// object a position, an orientation and values of its own, or takes them from somewhere else
// (another object, a track of an animation, an aim). Written for this project from what
// retail's code does (config/us/tables.tsv, docs/DISC.md "Objects").
//
// The records come from the world's pool at World::pool1B20 (func_00121228 takes one, stores the
// table at +0 and calls its slot 0; func_00121358, slot 2, gives it back). An object keeps its
// attachments in the list at PlacedObject::list1E0 (the link at +8), and the ones that give its position
// and orientation in PlacedObject::f1EC and PlacedObject::f1F0. Eight tables (D_00219560 ...) of ten slots make
// eight variants; they share this base, up to +0x13, and each adds fields from there.
// Every field line ends with its offset. The size of a record is the pool's, which no code here
// shows (the largest variant reaches 0xC8), so the variants have no sizeof check.
#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#include "placed_object.h"

struct Animation;     // an animation (c83.h)
struct S1DBBD8; // a callback record (s1dbbd8.h)
struct Attachment;

// The table. Slots 4 and 5 give the position and the orientation (each with a vector next to
// it), slot 6 a float and its slope, slot 7 a matrix, slot 8 a float by index.
struct T2195_Vt {
    void (*init)(Attachment* self, PlacedObject* owner);                              // 0x00: set up for an owner
    void (*copy)(Attachment* self, Attachment* src);                              // 0x04: copy src's record, keeping the owner and the link
    void (*release)(Attachment* self, s32 flags);                            // 0x08: out of the owner's list, back to the pool
    void* m3;                                                           // 0x0C
    void (*getPos)(Attachment* self, f32 t, Vec02* pos, Vec02* vec);         // 0x10
    void (*getRot)(Attachment* self, f32 t, Mat02* rot, Vec02* vec);         // 0x14
    void (*getValue)(Attachment* self, f32* value, f32* slope);              // 0x18
    void (*getMatrix)(Attachment* self, Mat02* out);                         // 0x1C
    f32 (*getIndexed)(Attachment* self, s32 index);                          // 0x20
    void* m9;                                                           // 0x24
};

// The link in the owner's list (an unaligned doubleword, as PlacedObject::link40 and the others).
struct __attribute__((packed)) Link2195 {
    Attachment* next;            // 0x00
    Attachment* prev;            // 0x04
};

struct Attachment {
    const T2195_Vt* vt;     // 0x00
    PlacedObject* owner;             // 0x04: set by slot 0
    Link2195 link;          // 0x08: in PlacedObject::list1E0
    s8 mode0;               // 0x10: -1 unset; how the position is given (2, 3; 7 becomes 3, func_001226D8)
    s8 mode1;               // 0x11: the same for the orientation (0 ends the chain of func_00122C48)
    s8 mode2;               // 0x12
    s8 mode3;               // 0x13
};

// The 0xC0-byte record the owner points to at PlacedObject::f224: its value (+0x8C) and its flags (+0xB0).
struct Rec2195_224 {
    u8 pad00[0x8C]; // 0x00
    f32 f8C;                // 0x8C
    f32 f90;                // 0x90: func_00120AA8
    u8 pad94[0xB0 - 0x94]; // 0x94
    s32 fB0;                // 0xB0: bit 0x20 gives the value at +0x8C
};

// The player an animation track attachment follows (D_002197C0): it holds the animation, a
// time and a speed, the attachment it drives (+0x28) and the list of the ones that follow it
// (+0x44). func_0012E9E0 keeps the time (+0x14) and the speed (+0x18) within the length.
// It is a 0xEC-byte record of the world's pool at World::pool1B58 (func_0012D3F8 takes one,
// stores the table D_002197B8 at +0, makes the list at +0x44 with offset 0x20 and points +0x60
// at its own +0x64).
struct AnimationPlayer {
    const void* vt;         // 0x00: D_002197B8
    u8 pad04[0x08 - 0x04]; // 0x04
    Animation* anim;              // 0x08: its tracks (Animation::tracks at +0x3C) are what the attachment follows
    void* fC;               // 0x0C: an object func_0012F760 calls slot 18 of
    f32 f10;                // 0x10
    f32 time;               // 0x14
    f32 speed;              // 0x18
    f32 f1C;                // 0x1C: a scale of the speed (func_0012F6B0, func_0012F6D0; func_0012C288 sets it)
    s32 f20;                // 0x20: the next timed entry (func_0012E4E0, func_0012D5D0)
    s8 state24;             // 0x24: func_0012D448
    u8 pad25[0x28 - 0x25]; // 0x25
    Attachment* driven;          // 0x28
    void* f2C;              // 0x2C: func_0012D5D0
    void* f30;              // 0x30: func_0012D5D0
    u8 pad34[0x44 - 0x34]; // 0x34
    List01 list44;          // 0x44: the attachments that follow it (offset 0x20)
    union {
        s32 f50;            // 0x50: its address goes to func_001BF718 (func_0012E760)
        void* p50;          // 0x50: an object func_0012D5D0 calls through
    };
    u8 f54[8];              // 0x54: handed to func_0015F9A0 (func_0012E760)
    s32 f5C;                // 0x5C: the number of f60 entries (func_0012C288)
    void* f60;              // 0x60: its own +0x64 at set-up (func_0012D3F8)
    u8 pad64[0xE4 - 0x64]; // 0x64
    S1DBBD8* fE4;           // 0xE4: its callbacks, records of World::pool1B14 (func_0012F760 calls each, func_0012E760 gives them back)
    u8 padE8[0xEC - 0xE8]; // 0xE8
};

typedef char check_AnimationPlayer[sizeof(AnimationPlayer) == 0xEC ? 1 : -1];   // the pool's records (func_001DB4C8)

struct __attribute__((packed)) Pk8_2195 { u64 v; };
struct __attribute__((packed)) Pair2195 { s32 lo; s32 hi; };

// D_00219588: a copy of the owner's position, matrix and values, taken when it is set up.
struct T2195_588 : Attachment {
    u8 pad14[0x20 - 0x14]; // 0x14
    Vec02 pos;              // 0x20: PlacedObject::v190
    Vec02 vec;              // 0x30
    Mat02 rot;              // 0x40: PlacedObject::m1A0
    Vec02 v70;              // 0x70
    f32 f80;                // 0x80: the value at Rec2195_224::f8C, when its flag is set
    f32 f84;                // 0x84
    u8 pad88[0x90 - 0x88]; // 0x88
    Mat02 m90;              // 0x90: the identity
    s32 countC0;            // 0xC0: PlacedObject::f26C
    f32* valuesC4;          // 0xC4: the owner's values (+0x274)
};

// D_002195B0: pointers into the owner's own fields.
struct T2195_5B0 : Attachment {
    u8 pad14[0x1C - 0x14]; // 0x14
    Vec02* pos;             // 0x1C: &PlacedObject::v190
    Vec02* vec;             // 0x20: D_00248D30
    Mat02* rot;             // 0x24: &PlacedObject::m1A0
    Vec02* vec2;            // 0x28: D_00248D30
    f32* p2C;               // 0x2C: &Rec2195_224::f8C, when its flag is set
    f32* p30;               // 0x30: D_00248D30
    Mat02* ident;           // 0x34: D_002483D0
    s32* count;             // 0x38: &PlacedObject::f26C
    f32* values;            // 0x3C: the owner's values (+0x274)
};

// D_002195D8: two matrices of its own.
struct T2195_5D8 : Attachment {
    u8 pad14[0x40 - 0x14]; // 0x14
    Mat02 m40;              // 0x40: the identity
    u8 pad70[0x90 - 0x70]; // 0x70
    Mat02 m90;              // 0x90: the identity
};

// D_00219600: a value of its own.
struct T2195_600 : Attachment {
    u8 pad14[0x1C - 0x14]; // 0x14
    f32 f1C;                // 0x1C: 1.0
    f32 f20;                // 0x20: 0.25
};

// D_002197C0: follows a track of an animation: the animation's player drives it (slots 4 to 8
// ask the track's curves).
struct T2195_7C0 : Attachment {
    s32 f14;                // 0x14: the player's start (func_0012C288, func_0012D5D0)
    f32 f18;                // 0x18
    AnimationPlayer* player;     // 0x1C
    Pair2195 w20;           // 0x20: kept by slot 1
    s32 index;              // 0x28: the track
};

// D_0021A790: an aim at a target.
struct T2195_790 : Attachment {
    u8 pad14[0x1C - 0x14]; // 0x14
    s32 hasTarget;          // 0x1C
    s32 f20;                // 0x20: -1
    void* target;           // 0x24
    u8 pad28[0x30 - 0x28]; // 0x28
    Vec02 point;            // 0x30
    f32 f40;                // 0x40: 800.0
    s32 f44;                // 0x44: 1
    s32 f48;                // 0x48: -1
    u8 pad4C[0x50 - 0x4C]; // 0x4C
    Vec02 v50;              // 0x50
    Pk8_2195 p60;           // 0x60
    u8 pad68[0x70 - 0x68]; // 0x68
    Vec02 v70;              // 0x70
    Pk8_2195 p80;           // 0x80
};

typedef char check_Attachment[sizeof(Attachment) == 0x14 ? 1 : -1];
typedef char check_T2195_Vt[sizeof(T2195_Vt) == 0x28 ? 1 : -1];

#endif
