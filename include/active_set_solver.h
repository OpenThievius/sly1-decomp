// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x50-byte solver state func_00153528(solver, n) sets up: it clears the 0x50 bytes, allocates 2n
// items of 0x60 bytes (func_0018D658) and makes four lists (func_00152438, link at 0x4C).
// func_00153A50 pivots items between the lists, solving the linear system of the active ones
// each round; func_00153EC0 feeds the pending items to it; func_00154880 keeps one on its
// stack. Written for this project from what retail's code does (build/swarm/st3/groups.tsv,
// g1657).
#ifndef ACTIVE_SET_SOLVER_H
#define ACTIVE_SET_SOLVER_H

#include "base_object.h"

struct ActiveSetSolver {
    union {
        s32 slots;          // 0x00: 2n, the number of items allocated (func_00153528)
        u32 hdr;            // 0x00: func_00154880
    };
    s32 count;              // 0x04: func_00153A50
    u8* items;              // 0x08: the 2n items of 0x60 bytes (func_00153528)
    List01 active;          // 0x0C: func_00153528, func_00153A50; func_00153EC0 reads its head as a word
    List01 atLow;           // 0x18: items func_00153A50 moves to and from the active list when one's value reaches zero
    List01 atHigh;          // 0x24: the same when it reaches its upper bound
    List01 pending;         // 0x30: func_00153EC0 walks it
    s32 activeCount;        // 0x3C: the active list's length (func_00153A50, func_00153EC0)
    f32* matrix;            // 0x40: the active items' square matrix (func_00153A50)
    f32* factor;            // 0x44: what func_0014B0C0 makes of the matrix
    f32* rhs;               // 0x48: the negated values of the active items
    f32* solution;          // 0x4C: func_0014B3E0's result
};

typedef char check_ActiveSetSolver[sizeof(ActiveSetSolver) == 0x50 ? 1 : -1];

#endif
