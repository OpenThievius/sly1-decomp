// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x20-byte slots func_001BE728 (001BC000.cpp) takes as the first parameter: the six at
// D_00262890, the one at D_00262950 (file_16AA18.cpp, func_0016B300) and the one at D_0026A118.
// Written for this project from what retail's code does (build/swarm/st3/groups.tsv, g1915). The
// labels give the size: D_00262890 runs 0xC0 bytes, D_00262950 and D_0026A118 0x20. The tables
// of fixed keys are KeyRecords too: g_soundBankKeys (D_00244F40, read as wordA ^ maskA and
// wordB ^ maskB), g_memoryCardIconKey (D_00248470) and g_streamVoiceKeys (D_002482D8).
#ifndef KEY_RECORD_H
#define KEY_RECORD_H

#include "common.h"

struct KeyRecord {
    s32 wordA;             // 0x00: func_001BE728 (xor maskA gives the id word)
    s32 wordB;             // 0x04: func_001BE728 (xor maskB; only its non-zero is tested)
    s32 idA;               // 0x08: with idB, what identifies the key (identity_key.h: w[2] ^ w[6])
    s32 word0C;            // 0x0C
    s32 word10;            // 0x10
    s32 maskA;               // 0x14: func_001BE728
    s32 idB;               // 0x18
    s32 maskB;               // 0x1C: func_001BE728
};

typedef char check_KeyRecord[sizeof(KeyRecord) == 0x20 ? 1 : -1];

extern KeyRecord D_00262890[6];
extern KeyRecord D_00262950;
extern KeyRecord D_0026A118;

#endif
