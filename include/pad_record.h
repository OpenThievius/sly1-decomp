// SPDX-License-Identifier: AGPL-3.0-or-later
// The two 0xC4-byte records D_00262C70 and D_00262D38 (pad_input.cpp defines both as zeros):
// one type, read by the functions of pad_input.cpp (func_0016E1A0, func_0016E238, func_0016E630,
// func_0016E940, func_0016EC20, func_0016EC38, func_0016EC88, func_0016EED0, func_0016F108,
// func_0016F238) and by twelve other files. Written for this project from what retail's code
// does (build/swarm/st3/groups.tsv, g1917).
//
// The size is the labels': each runs 0xC4 bytes to the next one.
#ifndef PAD_RECORD_H
#define PAD_RECORD_H

#include "common.h"
#include "value_range.h"

struct PadRecord {
    u8 pad00[0x04];
    s32 port;               // 0x04: func_0016E1A0, func_0016E238, func_0016E940
    s32 slot;               // 0x08: func_0016E1A0, func_0016E238, func_0016E940
    u8* buffer;             // 0x0C: the 64-byte aligned buffer func_0016E1A0 gives the pad library
    s32 deviceType;         // 0x10: func_0016E1A0, func_0016E940
    s32 connectionMode;     // 0x14: func_0016B580, func_0016BBA8, func_0016EC38, func_001E9108, func_001F1A08
    s32 connectionStep;     // 0x18: func_0016E940, func_0016EC38, func_0016F108
    f32 connectionChangeTime; // 0x1C: func_0016E1A0, func_0016E238
    union {
        s32 f20;            // 0x20: func_0016E1A0
        f32 lastReadTime;   // 0x20: func_0016E940
    };
    f32 lastActiveTime;     // 0x24: func_0016E940
    s32 stepX;              // 0x28: func_0016EC88
    s32 stepY;              // 0x2C: func_0016EC88, func_0016EED0
    f32 nextStepTimeX;      // 0x30: func_0016BBA8, func_001F1A08
    f32 stepDelayX;         // 0x34
    f32 nextStepTimeY;      // 0x38: func_0016BBA8, func_0016EED0, func_001F1A08
    f32 stepDelayY;         // 0x3C
    f32 stickX;             // 0x40: func_00151300, func_0016E940, func_0016EED0
    f32 stickY;             // 0x44
    f32 stickMagnitude;     // 0x48
    u8 stickPrevRawX;       // 0x4C: func_0016E940
    u8 stickPrevRawY;       // 0x4D
    u8 pad4E[0x50 - 0x4E];
    union {
        s32 stickActive;    // 0x50: func_0016E1A0, func_0016E738's latch
        f32 x50;            // 0x50: func_0016E940
    };
    ValueRange stickRanges[4]; // 0x54: func_0016E1A0 (Pair_16E1A0), func_0016E738 (from func_0016E940)
    f32 secondStickX;       // 0x74: func_0016E940
    f32 secondStickY;       // 0x78: func_00132500, func_0016E940
    f32 secondStickMagnitude; // 0x7C: func_00151300, func_0016E940
    u8 secondStickPrevRawX; // 0x80: func_0016E940
    u8 secondStickPrevRawY; // 0x81
    u8 pad82[0x84 - 0x82];
    union {
        s32 secondStickActive; // 0x84: func_0016E1A0, func_0016E738's latch
        f32 x84;            // 0x84: func_0016E940
    };
    ValueRange secondStickRanges[4]; // 0x88: func_0016E1A0, func_0016E738 (from func_0016E940)
    union {
        s16 fA8;            // 0xA8: func_0016E1A0
        u16 buttons;        // 0xA8: func_0016E940, func_0016EED0, func_0016F108, func_0016F238
    };
    u16 flags;              // 0xAA: func_0016EC20 and nine other files' views
    u16 released;           // 0xAC: func_0016E940
    u8 pressure[0xBA - 0xAE]; // 0xAE: func_0016E940, func_0016F108
    u8 padBA[0xBC - 0xBA];
    void* patternPlayer;    // 0xBC: func_0016E1A0, func_0016E238, func_0016EC38
    union {
        s32 patternsEnabled; // 0xC0: func_0016E1A0, func_0016E238
        void* pC0;          // 0xC0: func_0016EC38
    };
};

typedef char check_PadRecord[sizeof(PadRecord) == 0xC4 ? 1 : -1];

extern PadRecord g_padRecord;      // pad_input.cpp
extern PadRecord g_blankPadRecord;      // pad_input.cpp

#endif
