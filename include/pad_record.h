// SPDX-License-Identifier: AGPL-3.0-or-later
// The two 0xC4-byte records D_00262C70 and D_00262D38 (001E4000.cpp defines both as zeros):
// one type, read by the functions of 0016C000.cpp (func_0016E1A0, func_0016E238, func_0016E630,
// func_0016E940, func_0016EC20, func_0016EC38, func_0016EC88, func_0016EED0, func_0016F108,
// func_0016F238) and by twelve other files. Written for this project from what retail's code
// does (build/swarm/st3/groups.tsv, g1917).
//
// The size is the labels': each runs 0xC4 bytes to the next one.
#ifndef G262C70_H
#define G262C70_H

#include "common.h"
#include "s1eb050.h"

struct G262C70 {
    u8 pad00[0x04];
    s32 f04;                // 0x04: func_0016E1A0, func_0016E238, func_0016E940
    s32 f08;                // 0x08: func_0016E1A0, func_0016E238, func_0016E940
    s32 f0C;                // 0x0C: func_0016E1A0
    s32 f10;                // 0x10: func_0016E1A0, func_0016E940
    s32 f14;                // 0x14: func_0016B580, func_0016BBA8, func_0016EC38, func_001E9108, func_001F1A08
    s32 f18;                // 0x18: func_0016E940, func_0016EC38, func_0016F108
    f32 f1C;                // 0x1C: func_0016E1A0, func_0016E238
    union {
        s32 f20;            // 0x20: func_0016E1A0
        f32 x20;            // 0x20: func_0016E940
    };
    f32 f24;                // 0x24: func_0016E940
    s32 f28;                // 0x28: func_0016EC88
    s32 f2C;                // 0x2C: func_0016EC88, func_0016EED0
    f32 f30;                // 0x30: func_0016BBA8, func_001F1A08
    f32 f34;                // 0x34
    f32 f38;                // 0x38: func_0016BBA8, func_0016EED0, func_001F1A08
    f32 f3C;                // 0x3C
    f32 f40;                // 0x40: func_00151300, func_0016E940, func_0016EED0
    f32 f44;                // 0x44
    f32 f48;                // 0x48
    u8 f4C;                 // 0x4C: func_0016E940
    u8 f4D;                 // 0x4D
    u8 pad4E[0x50 - 0x4E];
    union {
        s32 f50;            // 0x50: func_0016E1A0
        f32 x50;            // 0x50: func_0016E940
    };
    S1EB050 a54[4];         // 0x54: func_0016E1A0 (Pair_16E1A0); func_0016E940 reads a54[0].lo
    f32 f74;                // 0x74: func_0016E940
    f32 f78;                // 0x78: func_00132500, func_0016E940
    f32 f7C;                // 0x7C: func_00151300, func_0016E940
    u8 f80;                 // 0x80: func_0016E940
    u8 f81;                 // 0x81
    u8 pad82[0x84 - 0x82];
    union {
        s32 f84;            // 0x84: func_0016E1A0
        f32 x84;            // 0x84: func_0016E940
    };
    S1EB050 a88[4];         // 0x88: func_0016E1A0; func_0016E940 reads a88[0].lo
    union {
        s16 fA8;            // 0xA8: func_0016E1A0
        u16 keyA8;          // 0xA8: func_0016E940, func_0016EED0, func_0016F108, func_0016F238
    };
    u16 flags;              // 0xAA: func_0016EC20 and nine other files' views
    u16 hAC;                // 0xAC: func_0016E940
    u8 fAE[0xBA - 0xAE];    // 0xAE: func_0016E940, func_0016F108
    u8 padBA[0xBC - 0xBA];
    void* fBC;              // 0xBC: func_0016E1A0, func_0016E238, func_0016EC38
    union {
        s32 fC0;            // 0xC0: func_0016E1A0, func_0016E238
        void* pC0;          // 0xC0: func_0016EC38
    };
};

typedef char check_G262C70[sizeof(G262C70) == 0xC4 ? 1 : -1];

extern G262C70 D_00262C70;      // 001E4000.cpp
extern G262C70 D_00262D38;      // 001E4000.cpp

#endif
