// SPDX-License-Identifier: AGPL-3.0-or-later
// Three words func_00168D68(rec, a, b) sets to { a, a, b } (00168000.cpp; func_00168D78,
// func_00168D88 and func_001690C0 read it). D_002626D8 is one (001E4000.cpp defines it; its
// label runs 0x10 bytes), func_00169780 and func_001B3040 keep one on their stacks. Written for
// this project from what retail's code does (build/swarm/st3/groups.tsv, g1873).
#ifndef S168D68_H
#define S168D68_H

#include "common.h"

struct S168D68 {
    s32 f0;                 // 0x00: a
    s32 f4;                 // 0x04: a; func_001690C0 (Ctl_1690C0)
    s32 f8;                 // 0x08: b
};


extern S168D68 D_002626D8;      // 001E4000.cpp

#endif
