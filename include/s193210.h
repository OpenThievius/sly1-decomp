// SPDX-License-Identifier: AGPL-3.0-or-later
// The record func_00193210(rec, a, b, c, d) fills and returns (file_193210.cpp): five words, then
// four words it stores one by one with swl/swr (its arguments 1 to 4 are such words too).
// func_001E4EA8 keeps one in a 0x28-byte local. Written for this project from what retail's code
// does (build/swarm/st3/groups.tsv, g4869 and g4870).
#ifndef S193210_H
#define S193210_H

#include "shapes.h"

struct S193210 {
    s32 f00;                // 0x00
    s32 f04;                // 0x04
    s32 f08;                // 0x08
    s32 f0C;                // 0x0C
    s32 f10;                // 0x10
    U32P f14;               // 0x14
    U32P f18;               // 0x18
    U32P f1C;               // 0x1C
    U32P f20;               // 0x20
};

#endif
