// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x4F50-byte record at D_00264A40 (00194000.cpp defines it as zeros): the state of the
// memory-card functions of 0018C000.cpp (func_0018B670 .. func_0018D0A0), which take it as their
// first parameter, and of func_001943E8, func_00195958 and func_001E9108, which name it.
// Written for this project from what retail's code does (build/swarm/st3/groups.tsv, g2213).
//
// The size is the label's (0x4F50 to the next one), which 00194000.cpp's definition spans.
#ifndef G264A40_H
#define G264A40_H

#include "common.h"
#include "g27c220.h"

struct G264A40 {
    s32 f00;                // 0x00: func_0018D0A0
    void* f04;              // 0x04: func_0018C250, func_0018D0A0
    void* f08;              // 0x08: func_0018C250, func_0018D0A0
    s32 f0C;                // 0x0C: func_0018BDC8, func_0018C028, func_001E9108
    f32 f10;                // 0x10: func_0018BDC8, func_0018C028
    s32 f14;                // 0x14: func_0018BDC8, func_0018C1A8, func_0018C250, func_0018D0A0
    s32 f18;                // 0x18: func_0018BDC8, func_0018C178, func_001E9108
    f32 f1C;                // 0x1C: func_0018BDC8, func_0018C178
    f32 f20;                // 0x20: func_0018BDC8, func_0018D0A0
    s32 f24;                // 0x24: func_0018D0A0
    s32 f28;                // 0x28: func_0018C250, func_0018D0A0
    s32 f2C;                // 0x2C: func_0018D0A0
    u8 pad30[0x4F44 - 0x30];
    union {
        G27C220* image;     // 0x4F44: the block func_0018C568 writes (Data_18C568, 0x1A00 bytes)
        u8* p4F44;          // 0x4F44: func_0018C638
        void* f4F44;        // 0x4F44: func_001943E8, func_00195958
        s32 i4F44;          // 0x4F44: func_0018BDC8, func_0018C178, func_0018C7F8, func_001E9108
    };
    union {
        void* f4F48;        // 0x4F48: func_0018C028 (an array of 0x1A5C-byte entries, Elem_18C028)
        s32 i4F48;          // 0x4F48: func_001E9108
    };
    union {
        void* f4F4C;        // 0x4F4C: func_001943E8, func_00195958
        s32 i4F4C;          // 0x4F4C: func_0018C770
    };
};

typedef char check_G264A40[sizeof(G264A40) == 0x4F50 ? 1 : -1];

extern G264A40 D_00264A40;      // 00194000.cpp

#endif
