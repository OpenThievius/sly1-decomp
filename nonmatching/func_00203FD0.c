// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 244/276, checked 2026-11-08
/* NEAR (src/lib/pad.c, where it is INCLUDE_ASM before D_0024F738; built as C by 2.9-ee-991111):
 * the tail (the failure message shared by the busy test and a failed transfer, the success
 * last) is retail's. Left: retail keeps port and slot in s2 and s0 and computes the slot's
 * offset afresh after GetIopDmaStatus (li 28, li 112, mult, mult1 again), where ours keeps the
 * products; and retail's frame has 0x100 bytes of locals below its saves, which only an array
 * of 16 transfers gives here (a padding-sized local AGENTS.md does not allow in src/: what
 * the original declared there is not known). Tried: a slot pointer, direct indexing, an inline
 * slot accessor, the f0C read into the id local. */
#include "common.h"

typedef struct PadSlot {
    u8* buffer;
    u32* dma;
    s32 f08;
    s32 f0C;
    s32 open;
    s32 f14;
    s32 f18;
} PadSlot;

typedef struct PadDmaTransfer {
    u32* src;
    void* dst;
    s32 size;
    s32 attr;
} PadDmaTransfer;

extern s32 D_0027AE84;
static PadSlot g_padSlots[2][4];
extern const char D_0024F738[];
s32 PrintFormatted(const char* format, ...);
void RefreshPadFrames(void* start, void* end);
s32 GetIopDmaStatus(s32 id);
s32 StartIopDma(PadDmaTransfer* transfers, s32 n);

s32 SendPadDma(s32 port, s32 slot)
{
    PadDmaTransfer transfers[16];
    PadSlot* p = &g_padSlots[port][slot];
    u32* dma = p->dma;
    u8* dst;
    s32 id;

    if (p->f0C != 0 && GetIopDmaStatus(p->f0C) >= 0)
        goto fail;
    dst = (u8*)g_padSlots[port][slot].f08 + ((++dma[0] & 1) << 5);
    RefreshPadFrames(dma, dma + 8);
    transfers[0].src = dma;
    transfers[0].dst = dst;
    transfers[0].size = 0x20;
    transfers[0].attr = 0;
    id = StartIopDma(transfers, 1);
    if (id == 0) {
    fail:
        if (D_0027AE84 != 0)
            PrintFormatted(D_0024F738);
        return 0;
    }
    g_padSlots[port][slot].f0C = id;
    return 1;
}
