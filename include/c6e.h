// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x6E (descriptor D_00217740, 0x38 bytes), an object driven by a hook object it finds
// in the level stream, and the four classes under it: 0x6F (0x60), 0x70 (0x70), 0x71 (0x5C)
// and 0x72 (0x40). Written for this project from what retail's code does
// (config/us/classes.tsv).
//
// Each class's fields follow its parent's and end at the size its descriptor gives; the
// pads keep every field at its retail offset. Fields are named for what the code does with
// them; step 6 of the roadmap may rename them.
#ifndef C6E_H
#define C6E_H

#include "base_object.h"
#include "path_curve.h"

// Eight bytes that each subclass keeps through a copy (slot 9: saved, the parent's copy,
// restored); retail moves them as one unaligned doubleword.
struct __attribute__((packed)) Keep6E { u64 bits; };

// 0x6E: a key-frame curve (include/path_curve.h) found by the index the stream names; slot 0 of
// its table reads it (func_001B2840), slot 4 is told the frames of the object's parent and of
// another object (func_001B28A8).
struct C6E : BaseObject {
    PathCurve* curve;           // 0x34
};

// 0x6F: an object id (-1 for none) resolved after loading (slot 15) into an object whose
// 0x398 it clears.
struct C6F : C6E {
    Keep6E keep;            // 0x38
    u8 pad40[0x44 - 0x40];
    s32 id44;               // 0x44: -1 for none
    void* found48;          // 0x48: the object id44 names
    s32 f4C;                // 0x4C: 1 at setup
    s32 f50;                // 0x50: 3 at setup
    u8 pad54[0x58 - 0x54];
    f32 f58;                // 0x58: the largest float at setup (D_0024A794)
    u8 pad5C[0x60 - 0x5C];
};

struct __attribute__((aligned(16))) Quad70 { u8 b[16]; };

// 0x70: a 16-byte value set from D_00248D00, three integers, a float and an object id
// resolved after loading.
struct C70 : C6E {
    Keep6E keep;            // 0x38
    Quad70 q40;             // 0x40
    s32 f50;                // 0x50: 8 at setup
    s32 f54;                // 0x54: 9 at setup
    s32 f58;                // 0x58: -1 at setup
    f32 f5C;                // 0x5C: D_0024B650 at setup
    u8 pad60[0x64 - 0x60];
    s32 id64;               // 0x64: -1 for none
    s32 found68;            // 0x68: what func_0015A418 returns for id64
    u8 pad6C[0x70 - 0x6C];
};

// 0x71: a float and an object id resolved after loading.
struct C71 : C6E {
    Keep6E keep;            // 0x38
    u8 pad40[0x4C - 0x40];
    f32 f4C;                // 0x4C: D_0024C8C4 at setup
    u8 pad50[0x54 - 0x50];
    s32 id54;               // 0x54: -1 for none
    s32 found58;            // 0x58: what func_0015A418 returns for id54
};

// 0x72: only the eight bytes it keeps.
struct C72 : C6E {
    Keep6E keep;            // 0x38
};

// Each class ends at its descriptor's size.
typedef char check_C6E[sizeof(C6E) == 0x38 ? 1 : -1];
typedef char check_C6F[sizeof(C6F) == 0x60 ? 1 : -1];
typedef char check_C70[sizeof(C70) == 0x70 ? 1 : -1];
typedef char check_C71[sizeof(C71) == 0x5C ? 1 : -1];
typedef char check_C72[sizeof(C72) == 0x40 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_001B2840(C6E* self, void* stream);        // 0x6E slot 10
void func_001B28A8(C6E* self, BaseObject* other);          // 0x6E slot 21
void func_00169CD8(C6F* self);                      // 0x6F slot 0
void func_00169D20(C6F* self);                      // 0x6F slot 6
void func_00169D58(C6F* self);                      // 0x6F slot 7
void func_00169DD8(C6F* self);                      // 0x6F slot 9
void func_00169D90(C6F* self);                      // 0x6F slot 15
void func_00191F08(C70* self);                      // 0x70 slot 0
void func_00191F68(C70* self);                      // 0x70 slot 6
void func_00191FA0(C70* self);                      // 0x70 slot 7
void func_00192020(C70* self);                      // 0x70 slot 9
void func_00191FD8(C70* self);                      // 0x70 slot 16
void func_0019AF00(C71* self);                      // 0x71 slot 0
void func_0019AF38(C71* self);                      // 0x71 slot 6
void func_0019AF70(C71* self);                      // 0x71 slot 7
void func_0019AFF0(C71* self);                      // 0x71 slot 9
void func_0019AFA8(C71* self);                      // 0x71 slot 16
void func_00180EB0(C72* self);                      // 0x72 slot 6
void func_00180EE8(C72* self);                      // 0x72 slot 7
void func_00180F20(C72* self);                      // 0x72 slot 9

#endif
