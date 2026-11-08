// SPDX-License-Identifier: AGPL-3.0-or-later
// The flag table at D_00261420 (.data, 0x430 bytes over two labels, g_flagTable): flags objects
// take an index of (TakeFlagTableIndex) and set, clear and test (SetFlagTableBit,
// ClearFlagTableBit, TestFlagTableBit), with a snapshot SaveFlagTableSnapshot takes and
// RestoreFlagTableSnapshot puts back. flagged_object.cpp defines its functions; zone_collider.cpp
// calls them too. Written for this project from what retail's code does.
#ifndef FLAG_TABLE_H
#define FLAG_TABLE_H

#include "common.h"

struct FlagBits {
    s32 count;              // 0x000: the flags set (SetFlagTableBit, ClearFlagTableBit)
    u8 bits[0x200];         // 0x004
};

struct FlagTable {
    s32 f000;               // 0x000
    s32 nextIndex;          // 0x004: the last index TakeFlagTableIndex gave out (RestoreFlagTableSnapshot clears it)
    FlagBits live;          // 0x008: the flags (TestFlagTableBit reads bit n at 0xC + n / 8)
    s32 changed;            // 0x20C: set when a bit changes; SaveFlagTableSnapshot and RestoreFlagTableSnapshot clear it
    f32 point[4] __attribute__((aligned(16)));  // 0x210: where the last flag was raised (func_00141690), FLT_MAX when cleared
    FlagBits saved;         // 0x220: the snapshot
    s32 fadeA;              // 0x424: the two words SaveFlagTableSnapshot keeps for StartScreenFadeFromFlagTable
    s32 fadeB;              // 0x428
    s32 hasFade;            // 0x42C: 1 once SaveFlagTableSnapshot has stored them
};

typedef char check_FlagBits[sizeof(FlagBits) == 0x204 ? 1 : -1];
typedef char check_FlagTable[sizeof(FlagTable) == 0x430 ? 1 : -1];

#endif
