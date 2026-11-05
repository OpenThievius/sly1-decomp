// SPDX-License-Identifier: AGPL-3.0-or-later
// An entry of the table D_00247AF0 (00160000.cpp defines its 46 entries): a key, an id, a name
// and flags. func_001600A0 returns the entry whose key is the same as its argument's (stride
// 0x2C, 46 entries: it stops at D_00247AF0 + 0x7E8), func_001601A0 and func_00160208 read the
// id and the flags. Written for this project from what retail's code does (g4680).
#ifndef S1600A0_H
#define S1600A0_H

#include "s18e410.h"

struct S1600A0 {
    S18E410 key;            // 0x00: func_001600A0 compares its words 2 and 6
    s32 id;                 // 0x20: func_001601A0, func_00160208
    union {
        const char* name;   // 0x24: 00160000.cpp's initialisers
        s32 i24;            // 0x24: Ent_1600A0 (as a word)
    };
    union {
        u32 flags;          // 0x28: Entry_247AF0
        s32 i28;            // 0x28: func_00160208
    };
};

typedef char check_S1600A0[sizeof(S1600A0) == 0x2C ? 1 : -1];

extern const S1600A0 D_00247AF0[];      // 00160000.cpp: 46 entries

#endif
