// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x55 (descriptor D_0021C6C8, 0x390 bytes), an object that holds a state (+0x2D0) and
// changes it through its class's slot 47 (func_00147AB0), and the classes under it: 0x56, 0x59,
// 0x5A (0x390, no fields of their own) and 0x57, 0x58 (0x3A0, a timer and its two limits).
// Written for this project from what retail's code does (config/us/classes.tsv).
//
// Each class's fields follow its parent's and end at the size its descriptor gives; the pads keep
// every field at its retail offset. Class 0x55 sits under 0x02 (include/c02.h, still padding):
// the fields its methods read inside 0x02's range are in C02View, a view for casts, and are
// proposed for C02 in build/swarm/ty5/NOTES.md. Names may change at the naming step.
#ifndef C55_H
#define C55_H

#include "c02.h"

struct __attribute__((aligned(16))) Quad55 { s32 a, b, c, d; };

// 0x02's fields (offsets inside 0x00..0x2D0) read by this family's methods.
struct C02View : C01 {
    u8 pad34[0x110 - 0x34];
    Quad55 q110;            // 0x110
    Quad55 q120;            // 0x120
    Quad55 q130;            // 0x130
    u8 pad140[0x2B0 - 0x140];
    u8 tint[4];             // 0x2B0: four bytes, set to 0x10 by func_00146340
    u8 pad2B4[0x2D0 - 0x2B4];
};

// A thing that takes a message in its class's slot 31 (0x10 + 4 * 31 = 0x8C).
struct Notify55 {
    void (**vtbl)(Notify55* self, void* message);
};

struct C55;

// An object a message names whose flags (+0xC) func_001473E0 tests.
struct Other55 {
    u8 pad0[0xC];
    s32 fC;
};

// Class descriptor of this family: slot 47 (0xCC) sets the object's state.
struct Desc55 : Desc01 {
    u8 pad80[0xCC - 0x80];
    void (*setState)(C55* self, s32 state);     // 0xCC: func_00147AB0 (class 0x55), others override
};

// 0x55: a state, a few movement numbers set by each subclass's constructor.
struct C55 : C02 {
    s32 state;              // 0x2D0
    u8 pad2D4[0x2D8 - 0x2D4];
    s32 f2D8;               // 0x2D8
    s32 f2DC;               // 0x2DC
    u8 pad2E0[0x2E8 - 0x2E0];
    void* f2E8;             // 0x2E8: the object whose message ends it (func_00147EF8)
    void* f2EC;             // 0x2EC
    u8 pad2F0[0x320 - 0x2F0];
    union {
        f32 f320;           // 0x320
        s32 i320;
    };
    u8 pad324[0x338 - 0x324];
    void* f338;             // 0x338
    s32 f33C;               // 0x33C (unused here)
    s32 f340;               // 0x340
    f32 f344;               // 0x344
    union {
        f32 f348;           // 0x348
        s32 i348;
    };
    f32 f34C;               // 0x34C
    f32 f350;               // 0x350
    f32 f354;               // 0x354
    f32 f358;               // 0x358
    u8 pad35C[0x374 - 0x35C];
    u8 tail374[8];          // 0x374: copied unaligned by func_00146418
    s32 f37C;               // 0x37C
    Notify55* f380;         // 0x380
    u8 pad384[0x388 - 0x384];
    f32 f388;               // 0x388
    u8 pad38C[0x390 - 0x38C];
};

struct C56 : C55 {};
struct C59 : C55 {};
struct C5A : C55 {};
struct C5B : C55 {};

// 0x57 and 0x58: a timer (f398) that counts down from a value chosen between two limits.
struct C57 : C55 {
    f32 f390;               // 0x390
    f32 f394;               // 0x394
    f32 f398;               // 0x398
    u8 pad39C[0x3A0 - 0x39C];
};
struct C58 : C55 {
    f32 f390;               // 0x390
    f32 f394;               // 0x394
    f32 f398;               // 0x398
    u8 pad39C[0x3A0 - 0x39C];
};

typedef char check_C55[sizeof(C55) == 0x390 ? 1 : -1];
typedef char check_C56[sizeof(C56) == 0x390 ? 1 : -1];
typedef char check_C57[sizeof(C57) == 0x3A0 ? 1 : -1];
typedef char check_C58[sizeof(C58) == 0x3A0 ? 1 : -1];
typedef char check_C59[sizeof(C59) == 0x390 ? 1 : -1];
typedef char check_C5A[sizeof(C5A) == 0x390 ? 1 : -1];
typedef char check_C5B[sizeof(C5B) == 0x390 ? 1 : -1];
typedef char check_Desc55[sizeof(Desc55) == 0xD0 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_00146340(C55* self);                       // 0x55 slot 0
void func_001463C0(C55* self, void* stream);         // 0x55 slot 10
void func_00146418(C55* self, void* other);          // 0x55 slot 9
void func_00146470(C55* self);                       // 0x55 slot 16
s32 func_001473E0(C55* self, Other55* other);           // 0x55 slot 45
void func_00147428(C55* self);                       // 0x55 slot 17 (original assembly)
void func_00147AB0(C55* self, s32 mode);             // 0x55 slot 47
void func_00147E40(C58* self);                       // 0x58 slot 0
void func_00147EF8(C58* self, s32 kind, void* target);
void func_00147FB0(C58* self);
void func_00148298(C58* self, s32 mode);
void func_00148400(C56* self);
void func_00148470(C56* self, s32 mode);
void func_00148510(C59* self);
void func_00148598(C59* self, s32 mode);
void func_00148698(C5A* self);
void func_00148718(C5A* self);
void func_00148770(C5A* self, s32 kind, void* msg);
void func_00148828(C5A* self);
void func_00148888(C5A* self, s32 mode);
void func_00148D90(C57* self);
void func_00148E40(C57* self, s32 kind, void* msg);
void func_00148EF8(C57* self);
void func_00148FF0(C57* self, s32 mode);
void func_00149168(C5B* self);

#endif
