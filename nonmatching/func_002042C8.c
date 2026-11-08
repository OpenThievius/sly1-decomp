// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 454/484 (93.8%), checked 2026-11-08
/* NEAR: the pad library's slot opener (src/lib/pad.c, where it is INCLUDE_ASM). The size is
 * retail's and all but the tail matches: with the slot's stores in this order (tools/permute.py's
 * best of the seven lines) only their order and registers differ. Retail stores open, the first
 * DMA word, f0C, f08, the buffer and the DMA words' address, in the order of the C in the
 * earlier attempt, which put the DMA word's store last and took 4 more bytes. Order-class pass: tools hill-climb of the stores (open, f08, buffer, dma, dma[0]=0, f0C) is 9 words against 13; retail stores open, dma[0], f0C, f08, buffer, dma, but that written order is worse (34). Tried: a slot
 * pointer, indexed stores, a local for the DMA words, the word stored through the array. */
#include "common.h"

/* A remote call client: the server it is bound to at +0x24. */
typedef struct RpcClient {
    u8 pad00[0x24];
    void* server;
} RpcClient;

/* A port's slot: the buffer of its two frames, its DMA words, whether it is open. */
typedef struct PadSlot {
    u8* buffer;
    s32* dma;
    s32 f08;
    s32 f0C;
    s32 open;
    s32 f14;
    s32 f18;
} PadSlot;

/* One of the two frames of a slot's buffer, 0x80 bytes. */
typedef struct PadFrame {
    u8 head[0x58];
    s32 count;
    u8 pad5C[4];
    s32 size;
    u8 pad64[3];
    u8 f67;
    u8 pad68[8];
    u8 state;
    u8 mode;
    u8 pad72[0x0E];
} PadFrame;

extern s32 D_0027AE84;
static RpcClient g_padClients[2] __attribute__((aligned(64)));
static PadSlot g_padSlots[2][4];
static s32 D_0062ABC0[2][4][8] __attribute__((aligned(64)));
static u8 g_padRequest[0x80] __attribute__((aligned(64)));

typedef struct PadRequest {
    s32 command;
    s32 port;
    s32 slot;
    s32 result;
    s32 arg10;
    s32 arg14;
} PadRequest;

s32 PrintFormatted(const char* format, ...);
void* FillMemory(void* dst, s32 value, s32 size);
s32 CallRemoteService(RpcClient* client, s32 function, s32 mode, void* send, s32 send_size, void* receive,
                  s32 receive_size, void* end, void* end_arg);

s32 OpenPadPort(s32 port, s32 slot, u8* buffer)
{
    PadRequest* request;
    PadFrame* frame;
    PadSlot* state;
    s32* dma;
    s32 i;

    if ((u32)buffer & 0x3F) {
        if (D_0027AE84 != 0)
            PrintFormatted("libpad: buffer addr is not 64 byte align. %08x\n", buffer);
        return 0;
    }
    if (g_padSlots[port][slot].open == 1) {
        if (D_0027AE84 != 0)
            PrintFormatted("libpad: pad port is already open [%d][%d]\n", port, slot);
        return 0;
    }
    frame = (PadFrame*)buffer;
    for (i = 0; i < 2; i++) {
        frame->count = 0;
        frame->state = 5;
        frame->mode = 2;
        frame->f67 = 0;
        FillMemory(frame, 0xFF, 0x20);
        frame->size = 0;
        frame++;
    }
    request = (PadRequest*)g_padRequest;
    request->command = 1;
    request->port = port;
    request->slot = slot;
    request->arg10 = (s32)buffer;
    if (CallRemoteService(g_padClients, 1, 0, request, 0x80, request, 0x80, 0, 0) < 0)
        return 0;
    dma = D_0062ABC0[port][slot];
    g_padSlots[port][slot].open = 1;
    g_padSlots[port][slot].f08 = request->arg14;
    g_padSlots[port][slot].buffer = buffer;
    g_padSlots[port][slot].dma = dma;
    dma[0] = 0;
    g_padSlots[port][slot].f0C = 0;
    return request->result;
}
