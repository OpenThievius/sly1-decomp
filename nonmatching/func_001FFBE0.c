// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 30/40 (75.0%), checked 2026-11-07
/* NEAR: it matched as C++ in src/lib/001FC000.cpp, but the unwinder's file (src/lib/unwind.c) is C,
 * proved whole. In C the store to the list head (a static scalar) is scheduled before the stores
 * into the new record, in every order of the source tried (tools/permute.py) and with the head
 * non-static; retail stores the record's fields at 0xC and 0x14 first. GCC 2.95 lets a fixed
 * scalar pass stores into a structure through a pointer, so retail's head was probably not a
 * plain scalar, or something before this function took its address. Written for this project
 * from retail's code. */
#include "common.h"

typedef struct FrameTable {
    u32 start;
    u32 end;
    void* records;
    void** sorted;
    u32 count;
    struct FrameTable* next;
} FrameTable;

static FrameTable* D_0062A7B8;

void RegisterFrameInfo(void* begin, FrameTable* ob)
{
    ob->records = begin;
    ob->end = 0;
    ob->start = 0;
    ob->count = 0;
    ob->sorted = (void**)begin;
    ob->next = D_0062A7B8;
    D_0062A7B8 = ob;
}
