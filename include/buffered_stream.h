// SPDX-License-Identifier: AGPL-3.0-or-later
// The reader func_00137290(rec, base, size, flags) sets up over a buffer (it aligns the end to
// 64 bytes and returns rec): func_001372E0, func_00137398, func_001373B0, func_001373D0,
// func_00137820, func_001378A0, func_00137A60 and the readers func_00137B90 .. func_00137DF8
// (00134000.cpp) work on it. Written for this project from what retail's code does
// (build/swarm/st3/groups.tsv, g828).
//
// No code shows its size: three of its callers (func_0011EDA8, func_0018CC20, func_001E4EA8)
// give it 0x60 bytes of their frames, func_001E4EA8 with fields up to 0x60, so the record runs
// to 0x60 without a size check.
#ifndef S137290_H
#define S137290_H

#include "common.h"

struct S137290 {
    s32 flags;              // 0x00: the fourth argument (func_00137290, func_00137A60)
    s32 mode;               // 0x04: -1 at set-up (func_00137398, func_001373D0)
    s32 end;                // 0x08: the buffer's end, aligned to 64
    s32 start;              // 0x0C: the base, moved back by the alignment
    s32 f10;                // 0x10: func_001373D0
    s32 f14;                // 0x14: func_001373D0
    union {
        u8* cur;            // 0x18: the readers (func_00137B90 .. func_00137DF8), func_001378A0
        s32 ptr;            // 0x18: func_00137290, func_00137398, func_00137A60
    };
    s32 remaining;          // 0x1C: the readers; func_00137A60 (count)
    union {
        u8* next;           // 0x20: func_001378A0
        s32 nextPtr;        // 0x20: func_00137290, func_00137A60
    };
    s32 nextCount;          // 0x24: func_00137290, func_001378A0, func_00137A60
    s32 f28;                // 0x28: func_00137290, func_001378A0
    s32 f2C;                // 0x2C: func_00137290, func_001378A0
    union {
        s32 f30;            // 0x30: func_00137290
        void* owner;        // 0x30: func_001E4EA8 sets it
    };
    s32 f34;                // 0x34: func_001373D0
    s32 f38;                // 0x38
    s32 f3C;                // 0x3C
    s32 f40;                // 0x40
    u8 pad44[0x60 - 0x44];
};

#endif
