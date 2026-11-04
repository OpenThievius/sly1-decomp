// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x14-byte record at D_00269990 (001E4000.cpp defines it as zeros), read by func_0018B5C0,
// func_0018B600 (00188000.cpp) and func_001943E8, func_00195958 (file_193210.cpp). Written for
// this project from what retail's code does (globals.tsv). The size is the label's (0x14).
#ifndef G269990_H
#define G269990_H

#include "common.h"

struct G269990 {
    union {
        void* f00;          // 0x00: func_0018B600
        s32 i00;            // 0x00: func_0018B5C0
    };
    s32 f04;                // 0x04: func_0018B5C0, func_0018B600
    s32 (*fn)(void* a);     // 0x08: func_0018B600 calls it
    void* f0C;              // 0x0C: func_0018B600
    s32 f10;                // 0x10: func_0018B5C0, func_0018B600, func_001943E8
};

typedef char check_G269990[sizeof(G269990) == 0x14 ? 1 : -1];

extern G269990 D_00269990;      // 001E4000.cpp

#endif
