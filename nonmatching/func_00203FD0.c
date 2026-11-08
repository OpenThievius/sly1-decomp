// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 252/276 (91.3%), checked 2026-11-08
/* NEAR (src/lib/pad.c, where it is INCLUDE_ASM before D_0024F738; built as C by 2.9-ee-991111):
 * the code is retail's: the failure message written twice, once after the busy test and once
 * after a failed transfer (cross-jumping merges them), keeps CSE from following the busy
 * test's skip into the transfer, so the slot's offset is computed afresh after
 * GetIopDmaStatus with port and slot in s2 and s0, as retail. Left: the frame. Retail has 0x100
 * bytes of locals below its saves; the one transfer here gives a 0x60 frame, so every stack
 * offset differs. An array of 16 transfers (PadDmaTransfer transfers[16], the first used)
 * gives retail's frame and makes it EXACT, but that is a frame-sized local AGENTS.md does not
 * allow unless the original plausibly declared it: left to the lead. */
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
    PadDmaTransfer transfer;
    u32* dma = g_padSlots[port][slot].dma;
    u8* dst;
    s32 id;
    u32 count;

    if (g_padSlots[port][slot].f0C != 0 && GetIopDmaStatus(g_padSlots[port][slot].f0C) >= 0) {
        if (D_0027AE84 != 0)
            PrintFormatted(D_0024F738);
        return 0;
    }
    count = dma[0] + 1;
    dst = (u8*)g_padSlots[port][slot].f08 + ((count & 1) << 5);
    dma[0] = count;
    RefreshPadFrames(dma, dma + 8);
    transfer.dst = dst;
    transfer.src = dma;
    transfer.size = 0x20;
    transfer.attr = 0;
    id = StartIopDma(&transfer, 1);
    if (id == 0) {
        if (D_0027AE84 != 0)
            PrintFormatted(D_0024F738);
        return 0;
    }
    g_padSlots[port][slot].f0C = id;
    return 1;
}
