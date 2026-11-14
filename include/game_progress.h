// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x1A00-byte block at D_0027C220 (.bss) and the records in it. Written for this project
// from what retail's code does.
//
// The block is what func_00160650 checksums and func_0018CDD8 writes out (a type, a size, a
// sum, then the data): after a 0x10-byte head come six records of 0x44C bytes, one per level
// (func_001603E8 reaches record n's word 0x448 at 0x458 + n * 0x44C), and the game's own words
// at 0x19D8..0x19FC. D_002623C0 points to the block; D_002623C4 and D_002623C8 both point to a
// record, the first one at D_0027C230 to begin with (game_progress.cpp defines all three pointers).
#ifndef GAME_PROGRESS_H
#define GAME_PROGRESS_H

#include "common.h"

// One level's record. Its readers reach it through D_002623C8 (the flags, the timers, the two
// bit sets) and D_002623C4 (the words at its end).
struct G27C230 {
    union {
        s32 flags;          // 0x00: func_00148598, func_0019AD68, func_001DD710 (s32)
        u32 bits;           // 0x00: func_00151300, func_0019A1E0, func_001DFEB8 (u32)
    };
    f32 elapsedTime;        // 0x04: func_00160690
    f32 f08;                // 0x08: func_001E02C8
    f32 dt;                 // 0x0C: func_00151D28, func_00151ED8, func_001A4898 and six extern views
    f32 f10;                // 0x10: func_001DD9D8, func_001DDA08
    void* f14;              // 0x14: func_001A4EF0
    u8 pad18[0x64 - 0x18];
    s32 count64;            // 0x64: the bits of bits68 (func_00199500, func_00199850, func_00199B18)
    u8 bits68[0x70 - 0x68]; // 0x68
    s32 count70;            // 0x70: the bits of bits74 (func_00151ED8, func_001D9338)
    u8 bits74[0x438 - 0x74]; // 0x74: no code bounds it; it runs to the next known word
    s32 f438;               // 0x438: func_00148598
    s32 f43C;               // 0x43C: object_gatherer.cpp (Ctx_002623C4)
    s32 f440;               // 0x440: commentary_best_time.cpp (Cnt_1E02C8)
    f32 levelElapsedTime;   // 0x444: func_00160690 (Obj_002623C4)
    s32 f448;               // 0x448: func_00199218; func_001603E8 sets 0x20 in record n's
};

// The block. The head's words are func_00160650's and func_0018CDD8's (Save_160650,
// Img_18CDD8); the words after the records are read by twenty functions in fourteen files
// (build/swarm/st3/groups.tsv, g1481).
struct GameProgress {
    s32 type;               // 0x00: func_001605E8, func_00160650, func_0018CDD8
    s32 size;               // 0x04
    s32 sum;                // 0x08: func_00160650's checksum (func_0018CDD8 keeps a handle there)
    f32 totalTime;          // 0x0C: func_00160690, func_00160948, func_001935B0
    G27C230 levels[6];      // 0x10: func_001603E8
    s32 levelIndex;         // 0x19D8: func_00146470, func_001481A0, func_00151A88, func_0019A088 and more
    s32 entryIndex;         // 0x19DC: func_00146470, func_001F0468, func_001DFEB8
    s32 reserveCount;       // 0x19E0: func_00148F80, func_001481A0
    s32 spareCount;         // 0x19E4: func_00148038, func_00151D28, func_001DDCB0
    s32 pickupCount;        // 0x19E8: func_001481A0
    union {
        s32 optionFlags;    // 0x19EC: func_0016B300, func_00199850, func_001A7E90, func_001A7EE8
        u32 u19EC;          // 0x19EC: func_00195958 (u32)
    };
    union {
        s32 f19F0;          // 0x19F0: func_0019A000, func_0019AD68; the mask of func_001603E8
        u32 u19F0;          // 0x19F0: func_0019A1E0 (u32)
    };
    union {
        s32 f19F4;          // 0x19F4: func_001603E8 sets bits by level
        u32 u19F4;          // 0x19F4: func_0016BDD0, func_0018E4F0 (u32)
    };
    s32 movieBits;          // 0x19F8: func_00160690
    s32 lastHintMode;       // 0x19FC: func_001605E8
};

typedef char check_G27C230[sizeof(G27C230) == 0x44C ? 1 : -1];
typedef char check_GameProgress[sizeof(GameProgress) == 0x1A00 ? 1 : -1];

extern GameProgress D_0027C220;      // .bss: the head (label D_0027C220, 0x10) and D_0027C230 (0x19F0)
extern G27C230 D_0027C230[];    // .bss: D_0027C220.levels, the label the two record pointers name
extern GameProgress* g_saveData;     // game_progress.cpp: = D_0027C220
extern G27C230* g_currentLevelRecord;     // game_progress.cpp: = D_0027C230
extern G27C230* g_currentEntry;     // game_progress.cpp: = D_0027C230

#endif
