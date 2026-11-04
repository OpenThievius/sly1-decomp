// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x50 (descriptor 0x350 bytes, parent 0x02), an object that owns a 0x200-byte record
// (+0x2D0) shared with its copies and resolves the objects its ids name after loading. Written
// for this project from what retail's code does (config/us/classes.tsv).
//
// Fields follow the parent's and end at the size the descriptor gives; the pads keep every
// field at its retail offset. Class 0x4D's slot 23 also copies class 0x02's float at 0x80
// (include/c02.h) from it.
#ifndef C50_H
#define C50_H

#include "c02.h"
#include "t2176.h"

// The record the object points to (func_00154F98 makes it, func_00155778 makes it the object's
// own before a change, func_001550E8 fills it from the ids).
struct Rec50 {
    s32 uses;               // 0x00: objects sharing it
    u8 pad04[0x10 - 0x04];
    s32 kind;               // 0x10: 3, 4 seen
    u8 pad14[0x20 - 0x14];
    union {
        T2176* curve20;     // 0x20: the key-frame curve found by index (func_00154F98)
        s32 value20;        // 0x20: a value taken from another object (func_001550E8)
    };
    u8 pad24[0x7C - 0x24];
    void* target;           // 0x7C
    u8 pad80[0x120 - 0x80];
    s32 f120;               // 0x120
    u8 pad124[0x188 - 0x124];
    s32 f188;               // 0x188
    u8 pad18C[0x1D8 - 0x18C];
    void* found[3];         // 0x1D8: objects named by the ids
    u8 pad1E4[0x200 - 0x1E4];
};

struct C50 : C02 {
    Rec50* rec;             // 0x2D0
    s32 f2D4;               // 0x2D4: -1 at setup
    s32 f2D8;               // 0x2D8: -1 at setup
    f32 f2DC;               // 0x2DC: 10.0 at setup
    f32 f2E0;               // 0x2E0: 10.0 at setup
    u8 pad2E4[0x2F8 - 0x2E4];
    union {
        s64 key2F8;         // 0x2F8: the two ids, tested together against -1
        s32 id2F8[2];       // 0x2F8, 0x2FC
    };
    s32 id300;              // 0x300
    s32 id304;              // 0x304
    u8 pad308[0x30C - 0x308];
    s32 id30C;              // 0x30C
    s32 f310;               // 0x310: -1 at setup
    u8 list314[0x10];       // 0x314: initialised with func_00152438
    u8 pad324[0x340 - 0x324];
    f32 f340;               // 0x340: -1.0 at setup
    C01* held344;           // 0x344: objects it must let go of when told (slot 13)
    C01* held348;           // 0x348
    u8 pad34C[0x350 - 0x34C];
};

typedef char check_C50[sizeof(C50) == 0x350 ? 1 : -1];

void func_00154C10(C50* self);                       // slot 0
void func_00155080(C50* self);                       // slot 9
void func_00154F98(C50* self, s32 count);            // slot 10
void func_00155678(C50* self, s32 mode, C01* p);     // slot 13
void func_001550E8(C50* self);                       // slot 15

#endif
