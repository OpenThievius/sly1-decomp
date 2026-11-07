// SPDX-License-Identifier: AGPL-3.0-or-later
// Three words func_00168D68(allocator, start, limit) sets to { start, start, limit }
// (file_167D68.cpp): func_00168D88 hands out the next size units and moves the cursor past them
// (returning the old one), func_00168D78 puts the cursor back at the start, func_001690C0
// reads the cursor. D_002626D8 is one (file_167D68.cpp defines it; its label runs 0x10 bytes),
// func_00169780 and func_001B3040 keep one on their stacks. Written for this project from what
// retail's code does (build/swarm/st3/groups.tsv, g1873).
#ifndef BUMP_ALLOCATOR_H
#define BUMP_ALLOCATOR_H

#include "common.h"

struct BumpAllocator {
    s32 start;              // 0x00: the first argument
    s32 next;               // 0x04: the cursor; func_00168D88 advances it, func_001690C0 rounds it
    s32 limit;              // 0x08: the second argument; stored, no code reads it
};


extern BumpAllocator g_bumpAllocator;        // file_167D68.cpp

#endif
