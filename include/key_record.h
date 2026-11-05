// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x20-byte slots func_001BE728 (001BC000.cpp) takes as the first parameter: the six at
// D_00262890, the one at D_00262950 (00168000.cpp, func_0016B300) and the one at D_0026A118.
// Written for this project from what retail's code does (build/swarm/st3/groups.tsv, g1915). The
// labels give the size: D_00262890 runs 0xC0 bytes, D_00262950 and D_0026A118 0x20.
#ifndef KEY_RECORD_H
#define KEY_RECORD_H

#include "common.h"

struct KeyRecord {
    s32 wordA;             // 0x00: func_001BE728 (xor maskA gives the id word)
    s32 wordB;             // 0x04: func_001BE728 (xor maskB; only its non-zero is tested)
    u8 pad08[0x14 - 0x08];
    s32 maskA;               // 0x14: func_001BE728
    u8 pad18[0x1C - 0x18];
    s32 maskB;               // 0x1C: func_001BE728
};

typedef char check_KeyRecord[sizeof(KeyRecord) == 0x20 ? 1 : -1];

extern KeyRecord D_00262890[6];
extern KeyRecord D_00262950;
extern KeyRecord D_0026A118;

#endif
