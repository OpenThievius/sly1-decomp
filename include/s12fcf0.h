// SPDX-License-Identifier: AGPL-3.0-or-later
// The record func_0012FCF0(rec, size) sets up (it aligns size to 64 at 0x14, sets 0x04 to -1,
// clears the rest and returns rec): func_0012FD30, func_0012FD78, func_0012FDE8, func_0012FE70,
// func_0012FF10, func_0012FF20 and func_0012FFE8 (0012C000.cpp) work on it, func_0018F198 keeps one
// on its stack. Written for this project from what retail's code does (build/swarm/st3/groups.tsv,
// g1158). No code shows its size: the set-up and the views end at 0x2C.
#ifndef S12FCF0_H
#define S12FCF0_H

#include "common.h"

struct S12FCF0 {
    s32 state;              // 0x00: func_0012FD30, func_0012FDE8, func_0012FE70, func_0012FF20, func_0012FFE8
    union {
        s32 f04;            // 0x04: -1 at set-up; func_0012FDE8, func_0012FF20
        void* p04;          // 0x04: func_0012FE70
    };
    union {
        s32 f08;            // 0x08: func_0012FDE8, func_0012FFE8
        void* p08;          // 0x08: func_0012FE70
    };
    s32 f0C;                // 0x0C: func_0012FE70, func_0012FF10, func_0012FF20, func_0012FFE8
    s32 f10;                // 0x10
    s32 size;               // 0x14: the second argument, aligned to 64
    s32 f18;                // 0x18
    s32 f1C;                // 0x1C
    s32 f20;                // 0x20
    s32 f24;                // 0x24
    s32 f28;                // 0x28
};

#endif
