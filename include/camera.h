// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x6D (descriptor D_00221520, 0x590 bytes), a direct child of 0x01. Written for this
// project from what retail's code does (config/us/classes.tsv). Only the span func_00143648
// sets up is declared; its other users (file_143140.cpp) still reach the rest by offset.
#ifndef CAMERA_H
#define CAMERA_H

#include "base_object.h"
#include "t2173.h"

// func_00143648 (slot 0) fills the identity frame at 0x80 and the settings at 0x1C0..0x208,
// then five sub-objects at 0x454, 0x460, 0x4C0, 0x510 and 0x520.
//
// The controllers are the kind t2173 (include/t2173.h). The camera keeps the ones in action in
// a stack ordered by key: func_00145088 pushes, func_001451F0 removes, func_00143E40 runs the
// first. The stack's size is the span up to the first controller (no code checks a limit).
struct Camera : BaseObject {
    u8 pad34[0x40 - 0x34];
    s32 f40[4];             // 0x40
    u8 pad50[0x80 - 0x50];
    union {
        s32 f80[4];         // 0x80
        f32 g80[4];         // 0x80: func_00144FF8 reads the first two as floats
    };
    s32 f90[4];             // 0x90
    s32 fA0[4];             // 0xA0
    u8 padB0[0x1C0 - 0xB0];
    f32 f1C0;               // 0x1C0
    f32 f1C4;               // 0x1C4
    f32 f1C8;               // 0x1C8
    union {
        s32 i1CC;           // 0x1CC
        f32 f1CC;           // 0x1CC
    };
    f32 f1D0;               // 0x1D0
    u8 pad1D4[0x1E4 - 0x1D4];
    f32 f1E4;               // 0x1E4
    f32 f1E8;               // 0x1E8
    u8 pad1EC[0x1F8 - 0x1EC];
    f32 f1F8;               // 0x1F8
    f32 f1FC;               // 0x1FC
    f32 f200;               // 0x200
    u8 pad204[0x218 - 0x204];
    f32 f218;               // 0x218
    s32 f21C;               // 0x21C
    s32 f220;               // 0x220
    s32 f224;               // 0x224
    s32 f228;               // 0x228
    f32 f22C;               // 0x22C
    u8 pad230[0x2B0 - 0x230];
    f32 f2B0;               // 0x2B0
    f32 f2B4;               // 0x2B4
    f32 f2B8;               // 0x2B8
    f32 f2BC;               // 0x2BC
    f32 f2C0;               // 0x2C0
    u8 pad2C4[0x2D0 - 0x2C4];
    s32 f2D0[4];            // 0x2D0
    void* f2E0;             // 0x2E0
    u8 pad2E4[0x340 - 0x2E4];
    s32 f340;               // 0x340
    void* f344[8];          // 0x344
    f32 f364;               // 0x364
    u8 pad368[0x3D0 - 0x368];
    s32 stackCount;         // 0x3D0: how many entries are in use
    T2173Entry stack[8];    // 0x3D4: the first is in action
    T2173 ctl454;           // 0x454: D_00217398
    T2173_3B0 ctl460;       // 0x460: D_002173B0
    T2173_3C8 ctl4C0;       // 0x4C0: D_002173C8
    T2173_3E0 ctl510;       // 0x510: D_002173E0
    T2173_3F8 ctl520;       // 0x520: D_002173F8
};

typedef char check_Camera[sizeof(Camera) == 0x590 ? 1 : -1];

void func_00143648(Camera* self);   // slot 0

#endif
