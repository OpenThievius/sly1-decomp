// SPDX-License-Identifier: AGPL-3.0-or-later
// The five pools of fixed-size entries at D_0025C250 .. D_0025C2D0 (value.cpp defines them;
// the values of the script machine are taken from them, func_0011C240). Written for this
// project from what retail's code does (build/swarm/st3/groups.tsv, g793).
//
// func_0011C128(pool, size, count) sets one up: the stride is the entry's size plus 8, the
// memory comes from func_0018D500, and the entries are chained into the free list through
// their first word (func_0011C288 gives entry n: mem + n * stride). func_0011C2A0,
// func_0011C2B0 and func_0011C2E8 walk and unlink the live entries. The constructor and
// destructor are value.cpp's: its static initialiser builds the five (func_0011C0A8, with
// func_0011C0E8 and func_0011C108, config/us/generated.tsv), so they stay as it has them.
#ifndef ENTRY_POOL_H
#define ENTRY_POOL_H

#include "common.h"

struct EntryPool {
    s32 stride;             // 0x00: size + 8 (func_0011C128); func_0011C288 multiplies by it
    s32 count;              // 0x04: entries (func_0011C128)
    u8* mem;                // 0x08: func_0011C128, func_0011C288
    void* freeList;         // 0x0C: the first free entry (func_0011C128, func_0011C2E8)
    union {
        s32 live;           // 0x10: cleared by func_0011C128 (Pool_11C128)
        void* liveHead;     // 0x10: the first live entry (func_0011C2A0, func_0011C2B0, func_0011C2E8)
    };
    union {
        s32 high;           // 0x14: cleared by func_0011C128 (Pool_11C128)
        void* liveMark;     // 0x14: the end mark of the live list: func_0011C2A0 sets it to the head, func_0011C2E8 sweeps after it
    };
    void* removeCallback;   // 0x18: set by func_0011BF70; func_0011C2E8 calls it on removal
    s32 pad1C;              // 0x1C

    EntryPool() { removeCallback = 0; }
    ~EntryPool() {}
};

typedef char check_EntryPool[sizeof(EntryPool) == 0x20 ? 1 : -1];

extern EntryPool g_valueNodePool;
extern EntryPool g_scopePool;
extern EntryPool g_keyedValuePool;
extern EntryPool g_payloadPool;
extern EntryPool g_propertyRefPool;

#endif
