// SPDX-License-Identifier: AGPL-3.0-or-later
// Kind 0x2176: key-frame curves (src/main/path_curve.cpp). A curve is a heap object that
// func_0014D9A8(kind) makes (0x1C bytes for kind 0, 0x1D0 for kind 1) and stores the table at
// +0 and the kind at +4; the slot-10 loaders of classes 0x50 (func_00154F98, Rec50+0x20), 0x79
// (func_00158B30, Rec79+0x20), 0x6E (func_001B2840, C6E+0x34) and 0x63 (func_001E2648,
// OnOffObject+0x2E4) keep it and read it from the level stream with slot 0.
//
// Kind 0 is the base (table D_002176D0, a time-sorted list of 16-byte points); kind 1
// (T2176_708, table D_00217708) keeps in and out tangents as well (a Hermite spline) and a
// cache of the samples of one segment. D_00217568+0x130 is an unreferenced table of the
// abstract base with slots 5 to 8 only (func_0014DA18, func_0014DA28 and the two shared
// functions). Written for this project from what retail's code does (docs/DISC.md).
#ifndef T2176_H
#define T2176_H

#include "common.h"

struct T2176;

// The table (14 slots, 4 bytes each). Slot types are those of kind 0's matched methods; kind 1
// has its own function in slots 1 to 4, 10, 11 and 12 (with other parameters: its callers cast)
// and in slot 9 a function that returns nothing. Slots 7 and 8 are shared by both kinds.
struct T2176_Vt {
    void (*m00)(T2176* self, void* stream);                                  // 0x00: load, then calls m09
    void (*m01)(T2176* self, s32 a1, s32 a2);                                // 0x04
    void (*m02)(T2176* self, s32 a1, s32 a2);                                // 0x08
    void (*m03)(T2176* self, s32 idx, void* a2, s32 a3, void* a4, s32 a5);  // 0x0C
    void (*m04)(T2176* self, void* a, void* b);                              // 0x10: moves the points by a matrix
    f32 (*m05)(T2176* self, f32 t);                                          // 0x14: arc length at a time
    f32 (*m06)(T2176* self, f32 t);                                          // 0x18: the time of an arc length
    f32 (*m07)(T2176* self);                                                 // 0x1C: last time (func_0014DB40)
    f32 (*m08)(T2176* self);                                                 // 0x20: last arc length (func_0014DB58)
    f32 (*m09)(T2176* self);                                                 // 0x24: after loading: fills the arc lengths
    void (*m10)(T2176* self, void* a1, void* a2, void* a3, void* a4, f32* out0, f32* out1);   // 0x28
    void (*m11)(T2176* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6);  // 0x2C
    void (*m12)(T2176* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6);  // 0x30
    void* m13;                                                               // 0x34
};

// Kind 0 (0x1C bytes). The count, times, arc lengths and points are read in this order by
// func_0014DD28 (wrap first); the arc lengths are filled by slot 9.
struct T2176 {
    const T2176_Vt* vt;     // 0x00
    s32 kind;               // 0x04: 0 or 1
    s32 wrap;               // 0x08: nonzero, the times repeat (func_0014D138)
    s32 count;              // 0x0C: number of keys
    f32* times;             // 0x10: sorted, count entries
    f32* lengths;           // 0x14: the arc length at each key, count entries
    void* points;           // 0x18: count points of 16 bytes
};

// Kind 1 (0x1D0 bytes, table D_00217708): a spline. func_0014E510 samples one segment (the
// one in idx1C0, -1 after loading) into pts30 and its arc lengths into len170.
struct T2176_708 : T2176 {
    void* inTan;            // 0x1C: count tangents of 16 bytes
    void* outTan;           // 0x20
    u8 pad24[0x30 - 0x24];
    f32 pts30[20][4];       // 0x30: 20 samples of one segment
    f32 len170[20];         // 0x170: their arc lengths
    s32 idx1C0;             // 0x1C0: the segment sampled, or -1
    u8 pad1C4[0x1D0 - 0x1C4];
};

typedef char check_T2176[sizeof(T2176) == 0x1C ? 1 : -1];
typedef char check_T2176_708[sizeof(T2176_708) == 0x1D0 ? 1 : -1];

#endif
