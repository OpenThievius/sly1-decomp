// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x50-byte record func_00153528(rec, n) sets up: it clears the 0x50 bytes, allocates 2n
// items of 0x60 bytes (func_0018D658) and makes four lists (func_00152438, link at 0x4C);
// func_00153780, func_00153A50 and func_00153EC0 work on it, and func_00154880 keeps one on its
// stack. Written for this project from what retail's code does (build/swarm/st3/groups.tsv,
// g1657).
#ifndef S153528_H
#define S153528_H

#include "c01.h"

struct S153528 {
    union {
        s32 f00;            // 0x00: 2n (func_00153528)
        u32 hdr;            // 0x00: func_00154880
    };
    s32 count;              // 0x04: func_00153A50
    u8* items;              // 0x08: the 2n items of 0x60 bytes (func_00153528)
    List01 a;               // 0x0C: func_00153528, func_00153A50; func_00153EC0 reads its head as a word
    List01 b;               // 0x18
    List01 c;               // 0x24
    List01 d;               // 0x30: func_00153EC0 walks it
    s32 total;              // 0x3C: func_00153A50, func_00153EC0
    f32* mat;               // 0x40: func_00153528, func_00153A50
    f32* vec1;              // 0x44
    f32* vec2;              // 0x48
    f32* vec3;              // 0x4C
};

typedef char check_S153528[sizeof(S153528) == 0x50 ? 1 : -1];

#endif
