// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x7E (descriptor D_002177C0, 0x50 bytes), an object with a point of its own, and the
// four classes under it: 0x7F (0x80), 0x80 (0x70), 0x81 (0x60) and 0x82 (0x60). Written for
// this project from what retail's code does (config/us/classes.tsv).
//
// Each class's fields follow its parent's and end at the size its descriptor gives; the
// pads keep every field at its retail offset. Fields are named for what the code does with
// them; step 6 of the roadmap may rename them.
#ifndef C7E_H
#define C7E_H

#include "c01.h"

struct __attribute__((aligned(16))) Vec4_7E { f32 x, y, z, w; };

// Eight bytes that 0x7F, 0x80 and 0x81 keep through a copy (slot 9: saved, the parent's copy,
// restored); retail moves them as one unaligned doubleword.
struct __attribute__((packed)) Keep7E { u64 bits; };

// 0x7E: a point, read from the level stream as three floats (func_00192068 through
// func_00137E70) and moved into and out of another object's frame (func_001920E0,
// func_00192128 through func_00128018).
struct C7E : C01 {
    u8 pad34[0x40 - 0x34];
    Vec4_7E pos;            // 0x40
};

// 0x7F: registers itself in the table D_002626F8 (slots 6, 7); an object id (-1 for none)
// resolved after loading (slot 15) into an object whose 0x398 it clears.
struct C7F : C7E {
    Keep7E keep;            // 0x50
    u8 pad58[0x60 - 0x58];
    s32 id60;               // 0x60: -1 for none (-1 at setup)
    void* found64;          // 0x64: the object id60 names
    s32 f68;                // 0x68: 1 at setup
    u8 pad6C[0x70 - 0x6C];
    f32 f70;                // 0x70: the largest float at setup (D_0024A798)
    u8 pad74[0x80 - 0x74];
};

// 0x80: registers itself in the table D_00264088 (slots 6, 7); an object id resolved after
// loading (slot 16, func_0015A418 with 0x104).
struct C80 : C7E {
    Keep7E keep;            // 0x50
    u8 pad58[0x5C - 0x58];
    s32 id5C;               // 0x5C: -1 for none
    s32 found60;            // 0x60: what func_0015A418 returns for id5C
    u8 pad64[0x70 - 0x64];
};

// 0x81: registers itself in a table inside its level (C6C::list1C84, slots 6, 7).
struct C81 : C7E {
    Keep7E keep;            // 0x50
    f32 f58;                // 0x58: the largest float at setup
    u8 pad5C[0x60 - 0x5C];
};

// 0x82: a string read from the level stream after the point (func_00192150 through
// func_001384A0, which allocates it).
struct C82 : C7E {
    u8* text;               // 0x50
    u8 pad54[0x60 - 0x54];
};

// Each class ends at its descriptor's size.
typedef char check_C7E[sizeof(C7E) == 0x50 ? 1 : -1];
typedef char check_C7F[sizeof(C7F) == 0x80 ? 1 : -1];
typedef char check_C80[sizeof(C80) == 0x70 ? 1 : -1];
typedef char check_C81[sizeof(C81) == 0x60 ? 1 : -1];
typedef char check_C82[sizeof(C82) == 0x60 ? 1 : -1];

// The methods (config/us/classes.tsv); a slot's function takes its class's object.
void func_00192068(C7E* self, void* stream);         // 0x7E slot 10
void func_001920E0(C7E* self, s32 value);            // 0x7E slot 21
s32 func_00192128(C7E* self, void* other);           // 0x7E slot 22
void func_0016A100(C7F* self);                       // 0x7F slot 0
void func_0016A140(C7F* self);                       // 0x7F slot 6
void func_0016A178(C7F* self);                       // 0x7F slot 7
void func_0016A1F8(C7F* self);                       // 0x7F slot 9
void func_0016A1B0(C7F* self);                       // 0x7F slot 15
void func_0017FD90(C80* self);                       // 0x80 slot 6
void func_0017FDC8(C80* self);                       // 0x80 slot 7
void func_0017FE00(C80* self);                       // 0x80 slot 9
void func_0017FE48(C80* self);                       // 0x80 slot 16
void func_001C10A8(C81* self);                       // 0x81 slot 0
void func_001C10D8(C81* self);                       // 0x81 slot 6
void func_001C1110(C81* self);                       // 0x81 slot 7
void func_001C1148(C81* self);                       // 0x81 slot 9
void func_00192150(C82* self, void* stream);         // 0x82 slot 10

#endif
