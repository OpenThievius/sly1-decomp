// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x24-byte record at D_00261EF0 (001E4000.cpp defines it as zeros), read by
// func_00151A88, func_00151ED8, func_00152010 and func_00152410 (00150000.cpp). Written for this
// project from what retail's code does (globals.tsv). The size is the label's (0x24).
#ifndef G261EF0_H
#define G261EF0_H

#include "common.h"

struct G261EF0 {
    u8 pad00[0x04];
    s32 f04;                // 0x04: func_00151A88, func_00152010
    s32 f08;                // 0x08
    s32 f0C;                // 0x0C
    s32 f10;                // 0x10
    s32 f14;                // 0x14
    s32 f18;                // 0x18
    void* table;            // 0x1C: func_00151A88, func_00151ED8, func_00152010, func_00152410
    s32 f20;                // 0x20: func_00151A88
};

typedef char check_G261EF0[sizeof(G261EF0) == 0x24 ? 1 : -1];

extern G261EF0 D_00261EF0;      // 001E4000.cpp

#endif
