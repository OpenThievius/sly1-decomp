// SPDX-License-Identifier: AGPL-3.0-or-later
// The 33 LevelEntry records of 0x2C bytes at D_00248748 (.rodata; global_tables.cpp defines them): a level, a
// float, eight words and a name, which func_001DFE80 (commentary_best_time.cpp) looks up by the first word.
// Written for this project from what retail's code does (globals.tsv). The label runs 0x5B8
// bytes to D_00248D00: 33 entries and the padding to 16 bytes.
#ifndef LEVEL_ENTRY_H
#define LEVEL_ENTRY_H

#include "common.h"

struct LevelEntry {
    s32 levelId;            // 0x00: func_001DFE80's key
    f32 f04;                // 0x04
    u32 record[8];          // 0x08
    const char* credits;    // 0x28
};

typedef char check_LevelEntry[sizeof(LevelEntry) == 0x2C ? 1 : -1];

extern const LevelEntry g_levelEntries[33];    // 001E4000.cpp

#endif
