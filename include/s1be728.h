// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x20-byte slots func_001BE728 (001BC000.cpp) takes as the first parameter: the six at
// D_00262890, the one at D_00262950 (00168000.cpp, func_0016B300) and the one at D_0026A118.
// Written for this project from what retail's code does (build/swarm/st3/groups.tsv, g1915). The
// labels give the size: D_00262890 runs 0xC0 bytes, D_00262950 and D_0026A118 0x20.
#ifndef S1BE728_H
#define S1BE728_H

#include "common.h"

struct S1BE728 {
    s32 w0;                 // 0x00: func_001BE728
    s32 w4;                 // 0x04
    u8 pad08[0x14 - 0x08];
    s32 w14;                // 0x14
    u8 pad18[0x1C - 0x18];
    s32 w1C;                // 0x1C
};

typedef char check_S1BE728[sizeof(S1BE728) == 0x20 ? 1 : -1];

extern S1BE728 D_00262890[6];
extern S1BE728 D_00262950;
extern S1BE728 D_0026A118;

#endif
