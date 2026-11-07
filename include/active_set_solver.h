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

// An item (0x60 bytes) of the solver: an unknown x in [0, limit] (no upper bound unless
// `bounded`), its residual and the rate that changes it, its row of the matrix, and the link
// (+0x4C) of the list it is in. func_00153A50 moves items between the lists.
struct ActiveSetItem {
    void* owner;            // 0x00: its object, whose word at 0xCC picks the row of `axes` (func_001536C8)
    u8 pad04[0x10 - 0x04];
    f32 axis[4];            // 0x10: the item's direction, dotted with each item's axes (func_001536C8)
    u8 pad20[0x28 - 0x20];
    s32 kind;               // 0x28: 2 enters the active list at once (func_00153EC0)
    s32 bounded;            // 0x2C: nonzero, x stops at `limit` (func_00153A50)
    f32 limit;              // 0x30
    f32 x;                  // 0x34: the unknown (func_00154880 returns it)
    f32 val;                // 0x38: the residual; a pending item below -0.01 is pivoted in
    f32 rate;               // 0x3C: how fast val changes with the active items' step
    u8 (*axes)[16];         // 0x40: vectors of 16 bytes, one per owner index (func_001536C8)
    f32* row;               // 0x44: the item's row of the matrix; 0 until func_00153780 builds it
    u8 pad48[4];
    ActiveSetItem* next;    // 0x4C: the list link (func_00153608 clears it and the word after)
    u8 pad50[0x60 - 0x50];
};

typedef char check_ActiveSetItem[sizeof(ActiveSetItem) == 0x60 ? 1 : -1];

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
