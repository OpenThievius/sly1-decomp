// SPDX-License-Identifier: AGPL-3.0-or-later
// The ring buffer func_00130070 and func_001300D8 (00130000.cpp) take as the first parameter: a
// state and three positions. func_0018F890 (file_18D8E0.cpp) keeps one. Written for this project
// from what retail's code does (build/swarm/st3/groups.tsv, g1249).
#ifndef S130070_H
#define S130070_H

#include "common.h"

struct S130070 {
    s32 state;              // 0x00: func_00130070
    u8 pad04[0x18 - 0x04];
    s32 head;               // 0x18: func_0018F890
    s32 base;               // 0x1C
    s32 tail;               // 0x20: func_001300D8, func_0018F890
};

#endif
