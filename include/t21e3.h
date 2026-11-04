// SPDX-License-Identifier: AGPL-3.0-or-later
// Kind 0x21E3: animated texture conditions ("loaded conditions": src/main/001B4000.cpp and
// 00158000.cpp). Each is read from the level stream by func_001B4A10: a type (1 to 8), an
// object of func_001B4920(type) bytes on the heap whose table func_001B4980(type) is stored at
// +0 and the type at +8, then slot 0 with the 0x1C-byte block the stream holds. func_001B3040
// (001B0000.cpp) keeps the objects in D_00274540 and each owns a record (T21E3_Rec) it binds
// with slot 1; func_001B4878 calls slot 2 on them every frame.
//
// The 0x2C-byte base is the same for all eight tables: a frame stamp, the type, the id of the
// record, and a cursor (the animated position the object drives: a frame index, or a pair of
// texture coordinates). Each variant adds its own parameters after it. Written for this
// project from what retail's code does.
#ifndef T21E3_H
#define T21E3_H

#include "common.h"

struct T21E3;
struct T21E3_Rec;

// The 0x1C bytes slot 0 reads from the stream (func_00137A60(stream, 0x1C, block)).
struct T21E3_Src {
    s16 id;                 // 0x00: the record's key (func_001B4AA0)
    u16 flag;               // 0x02: nonzero sets bit 2 of the cursor's flags
    f32 f4;                 // 0x04
    union {
        f32 f8;             // 0x08
        s32 i8;             // 0x08: type 4 (func_001B5060), read as unsigned
    };
    f32 fC;                 // 0x0C
    f32 f10;                // 0x10
    union {
        u16 u14;            // 0x14: types 1 to 3, as a number
        s16 s14;            // 0x14: type 5 (func_00159680)
        f32 f14;            // 0x14: type 8 (func_001B54D0)
    };
    f32 f18;                // 0x18: type 8
};

// What a cursor writes when it moves (func_001B47C0): value = base + ((index * stride) << 4).
struct T21E3_Frames {
    s32 stride;             // 0x00
    s32 base;               // 0x04
};
struct T21E3_Patch {
    u8 pad00[4];
    s32 value;              // 0x04
};
struct T21E3_Link {
    T21E3_Frames* src;      // 0x00
    T21E3_Patch* dst;       // 0x04
    T21E3_Link* next;       // 0x08
};

// The animated position of an object (0x1C bytes at +0x10). func_001B46E0 (a frame index) and
// func_001B4750 (a pair of coordinates) change it and link it into the list D_0027451C of the
// cursors to flush (D_00274544 is the list's first); func_001B47C0 flushes them at the end of
// the frame.
struct T21E3_Cursor {
    s32 flags;              // 0x00: bit 0 frames, bit 1 coordinates, bit 2 set by the stream
    T21E3_Rec* rec;         // 0x04: the record (null until it is bound)
    s32 idx;                // 0x08: the frame
    f32 x;                  // 0x0C
    f32 y;                  // 0x10
    T21E3_Link* links;      // 0x14
    T21E3_Cursor* next;     // 0x18: in the list to flush
};

// A record of D_002744FC (0x28 bytes each, func_001B3040 reads them): func_001B4688 finds one
// by its key. Its owner is the object that binds it.
struct T21E3_Rec {
    u8 kind;                // 0x00
    u8 flags;               // 0x01
    s16 key;                // 0x02
    u8 pad04[0x13 - 0x04];
    u8 nelem;               // 0x13: the elements at 0x14
    void* elems;           // 0x14: nelem elements of 0x14 bytes
    s32 f18;                // 0x18: the number of entries at 0x1C
    void* ents;             // 0x1C: f18 entries of 8 bytes
    s32 count;              // 0x20: frames (the first element's second word)
    T21E3* owner;           // 0x24
};

struct T21E3_Vt {
    void (*m00)(T21E3* self, const T21E3_Src* src);   // 0x00: set up from the stream's block
    void (*m01)(T21E3* self);                          // 0x04: bind the record (func_001B4AD0 caches it)
    void (*m02)(T21E3* self, f32 dt);                  // 0x08: step; called every frame
    f32 (*m03)(T21E3* self);                           // 0x0C: a value in [0, 1] (func_001B4B38: 0)
    void (*m04)(T21E3* self, void* unused, void* other);  // 0x10: type 4's (func_001B5160)
    T21E3_Cursor* (*m05)(T21E3* self, const T21E3_Rec* rec);  // 0x14: the cursor of a record, or 0
    void (*m06)(T21E3* self, void** out);              // 0x18: type 8: pointers to its outputs
    void* m07;                                         // 0x1C
};

// The base (0x2C bytes).
struct T21E3 {
    const T21E3_Vt* vt;     // 0x00
    f32 stamp;              // 0x04: D_0026185C when last stepped (func_001B4B08)
    s32 type;               // 0x08: 1 to 8, selects the table and the size
    s32 id;                 // 0x0C: the key of its record
    T21E3_Cursor cur;       // 0x10
};

// Type 1 (table D_0021E358, 0x4C bytes): runs through the frames, then waits.
struct T21E3_358 : T21E3 {
    f32 durMin;             // 0x2C: seconds for a run, from (durMin, durMax)
    f32 durMax;             // 0x30
    f32 waitMin;            // 0x34: seconds to wait after one
    f32 waitMax;            // 0x38
    f32 rate;               // 0x3C: frames per second
    f32 pos;                // 0x40: the frame, as a float
    f32 wait0;              // 0x44: the wait chosen at binding
    f32 wait;               // 0x48: what is left of it
};

// Type 2 (D_0021E378, 0x4C): the same, forwards and back.
struct T21E3_378 : T21E3 {
    f32 durMin;             // 0x2C
    f32 durMax;             // 0x30
    f32 waitMin;            // 0x34
    f32 waitMax;            // 0x38
    f32 rate;               // 0x3C
    f32 pos;                // 0x40
    f32 wait0;              // 0x44
    f32 wait;               // 0x48
};

// Type 3 (D_0021E398, 0x38): jumps to a random other frame after a random wait.
struct T21E3_398 : T21E3 {
    f32 waitMin;            // 0x2C
    f32 waitMax;            // 0x30
    f32 wait;               // 0x34
};

// Type 4 (D_0021E3B8, 0x38): the frame follows the angle of another object (slot 4).
struct T21E3_3B8 : T21E3 {
    f32 phase;              // 0x2C: from the stream, or random when it is the largest float
    f32 sector;             // 0x30: 2 pi over the stream's count
    f32 step;               // 0x34: sector over the number of frames
};

// Type 6 (D_0021E3D8, 0x44): scrolls the coordinates.
struct T21E3_3D8 : T21E3 {
    f32 velU;               // 0x2C
    f32 velV;               // 0x30
    f32 wrapU;              // 0x34
    f32 wrapV;              // 0x38
    f32 mulU;               // 0x3C: 1.0 at setup (func_001B5388 sets both)
    f32 mulV;               // 0x40
};

// Type 7 (D_0021E3F8, 0x3C): moves the coordinates on a circle.
struct T21E3_3F8 : T21E3 {
    f32 omega;              // 0x2C: radians per second
    f32 radius;             // 0x30
    f32 centerU;            // 0x34
    f32 centerV;            // 0x38
};

// Type 8 (D_0021E418, 0x50): a triangle of coordinates (a corner and two edges).
struct T21E3_418 : T21E3 {
    f32 u0;                 // 0x2C
    f32 v0;                 // 0x30
    f32 du1;                // 0x34
    f32 du2;                // 0x38
    f32 dv1;                // 0x3C
    f32 dv2;                // 0x40
    f32 out44;              // 0x44: slot 6 returns the addresses of these three
    f32 out48;              // 0x48
    f32 out4C;              // 0x4C
};

// Type 5 (D_0021E438, 0x78): fades between two records (frames in, frames out) with a mode.
struct T21E3_438 : T21E3 {
    f32 scale;              // 0x2C
    f32 lo;                 // 0x30
    f32 hi;                 // 0x34
    f32 limit;              // 0x38
    s32 id2;                // 0x3C: the key of the second record
    T21E3_Cursor cur2;      // 0x40
    s32 count;              // 0x5C: the larger of the two records' frames
    s32 mode;               // 0x60: -1 at binding, 0 to 3 (func_00159770)
    f32 stamp2;             // 0x64: D_0026185C when the mode last changed
    f32 level;              // 0x68
    f32 step;               // 0x6C
    f32 pos;                // 0x70
    f32 ratio;              // 0x74
};

typedef char check_T21E3_Src[sizeof(T21E3_Src) == 0x1C ? 1 : -1];
typedef char check_T21E3_Cursor[sizeof(T21E3_Cursor) == 0x1C ? 1 : -1];
typedef char check_T21E3_Rec[sizeof(T21E3_Rec) == 0x28 ? 1 : -1];
typedef char check_T21E3[sizeof(T21E3) == 0x2C ? 1 : -1];
typedef char check_T21E3_358[sizeof(T21E3_358) == 0x4C ? 1 : -1];
typedef char check_T21E3_378[sizeof(T21E3_378) == 0x4C ? 1 : -1];
typedef char check_T21E3_398[sizeof(T21E3_398) == 0x38 ? 1 : -1];
typedef char check_T21E3_3B8[sizeof(T21E3_3B8) == 0x38 ? 1 : -1];
typedef char check_T21E3_3D8[sizeof(T21E3_3D8) == 0x44 ? 1 : -1];
typedef char check_T21E3_3F8[sizeof(T21E3_3F8) == 0x3C ? 1 : -1];
typedef char check_T21E3_418[sizeof(T21E3_418) == 0x50 ? 1 : -1];
typedef char check_T21E3_438[sizeof(T21E3_438) == 0x78 ? 1 : -1];

#endif
