// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 225/228 (98.7%), checked 2026-11-06
/* NEAR: 2 lines differ. Retail sends the list walk's end (t == 0) straight to "return 0" but keeps the null check after the break; with the walk inline here the end goes through that check (beqz target, and its delay slot nop vs move v0,zero). With the walk written in the function body the check is deleted instead (35 lines). */
#include "common.h"

/* A frame description record: its length, the distance back to its common record, its range. */
typedef struct FrameDesc {
    u32 length;
    s32 commonDelta;
    u32 start;
    u32 range;
} FrameDesc;

/* A registered block of frame descriptions: the code it covers, its sorted records, the next. */
typedef struct FrameTable {
    u32 start;
    u32 end;
    void* records;
    FrameDesc** sorted;
    u32 count;
    struct FrameTable* next;
} FrameTable;

extern FrameTable* D_0062A7B8;
void func_001FF518(FrameTable* table);

static inline FrameTable* owner(u32 pc)
{
    FrameTable* t;

    for (t = D_0062A7B8; t != 0; t = t->next) {
        if (t->start == 0)
            func_001FF518(t);
        if (pc >= t->start && pc < t->end)
            break;
    }
    return t;
}

FrameDesc* func_001FF658(u32 pc)
{
    FrameTable* t;
    u32 lo, hi, mid;
    FrameDesc* f;

    t = owner(pc);
    if (t == 0)
        return 0;

    lo = 0;
    hi = t->count;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        f = t->sorted[mid];
        if (pc < f->start)
            hi = mid;
        else if (pc < f->start + f->range)
            return f;
        else
            lo = mid + 1;
    }
    return 0;
}
