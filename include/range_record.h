// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x2E0-byte record a placed object keeps at PlacedObject::f284 (c02.h): func_001291D0 takes it from
// the world's pool World::pool1BF4 (func_001B5EE0), sets it up with func_001B1AC8 and puts it in
// World::list1C00. Written for this project from what retail's code does.
//
// The size is the pool's: func_001DB4C8 sets pool1BF4 up with func_001B5DD0(pool, 0x2E0, 0x20).
// Its readers are func_00124A48 (PlacedObject slot 16), func_001293D8, func_00152E48 and the functions
// func_001B1B38..func_001B2010 of src/main/001B0000.cpp.
#ifndef RANGE_RECORD_H
#define RANGE_RECORD_H

#include "placed_object.h"

struct RangeRecord {
    void* link;             // 0x00: what func_001B4688 finds for a key (func_001B1CF8; 0x2C when -1); func_001B1B38 reads its word 0xC
    f32 f04;                // 0x04: -1 at set-up (func_001B1AC8); func_001B1D38 tests it, func_001B1D70 sets it
    f32 f08;                // 0x08: -1 at set-up; func_001B1D70 copies f04 into it while negative, func_001B1DA8 sets it
    u8 pad0C[0x20 - 0x0C];
    Vec02 v20;              // 0x20: D_00248D20 scaled by -1 (func_001B1AC8)
    Vec02 v30;              // 0x30: D_00248D10 (func_001B1AC8)
    f32 f40;                // 0x40: 100 at set-up; func_001B1FB0, func_001B2010
    f32 f44;                // 0x44: 400 at set-up; func_001B1FE0, func_001B2010
    u8 pad48[0xB0 - 0x48];
    s32 fB0;                // 0xB0: -1 at set-up; func_00124A48, func_001293D8
    void* fB4;              // 0xB4: func_00124A48
    u8 padB8[0xC0 - 0xB8];
    s32 fC0;                // 0xC0: cleared by func_001B1BF0 whenever a value above changes
    u8 padC4[0x2D0 - 0xC4];
    u8* f2D0;               // 0x2D0: func_001B1B38
    u8 pad2D4[0x2E0 - 0x2D4];
};

typedef char check_RangeRecord[sizeof(RangeRecord) == 0x2E0 ? 1 : -1];

#endif
