/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The pad library, one object in retail from 0x203FD0 to the math library: the remote calls to
 * the IOP's pad module (bind, version, setup, opening a port's slot and the commands on it), the
 * readers of the two frames each open slot's buffer holds, and their data cache write-back
 * (assembly). Its .data begins with the library's identification string and ends with the two
 * tables of state names; its .bss holds the two clients, the slots' state, each slot's DMA
 * words and the request buffer. C, built by the cc1 of 2.9-ee-991111 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "remote_call_client.h"
#include "asm_func.h"
#include "system.h"

/* A port's slot: the buffer of its two frames, its DMA words and the IOP's address they are
 * sent to (f08, from the open request's reply), whether it is open. */
typedef struct PadSlot {
    u8* buffer;
    u32* dma;
    u32* f08;
    s32 f0C;
    s32 open;
    s32 f14;
    s32 f18;
} PadSlot;

/* One of the two frames of a slot's buffer, 0x80 bytes. */
typedef struct PadFrame {
    u8 head[0x30];
    u8 f30[8][4];
    u16 f50[4];
    s32 count;
    u8 pad5C[4];
    s32 size;
    u8 f64;
    u8 f65;
    u8 f66;
    u8 f67;
    u8 f68;
    u8 f69;
    u8 f6A;
    u8 pad6B[5];
    u8 state;
    u8 mode;
    u8 f72;
    u8 pad73[6];
    u8 f79;
    u8 f7A;
    u8 f7B;
    u8 f7C;
    u8 pad7D[3];
} PadFrame;

/* One transfer of the IOP's DMA: the source, the IOP's destination, the size and the mode. */
typedef struct PadDmaTransfer {
    u32* src;
    void* dst;
    s32 size;
    s32 attr;
} PadDmaTransfer;

/* The requests sent to the pad module, each a view of the request buffer. */
typedef struct PadRequest {
    s32 command;
    s32 port;
    s32 slot;
    s32 result;
    u8* arg10;
    u32* arg14;
} PadRequest;

typedef struct PadActRequest {
    s32 command;
    s32 port;
    s32 slot;
    u8 bytes[6];
    u8 pad12[2];
    s32 result;
} PadActRequest;

typedef struct PadModeRequest {
    s32 command;
    s32 port;
    s32 slot;
    s32 arg0C;
    s32 arg10;
    s32 result;
} PadModeRequest;

typedef struct PadInfoRequest {
    s32 command;
    s32 port;
    s32 slot;
    s32 data;
    s32 result;
} PadInfoRequest;

char D_0027AE70[16] = "PsIIlibpad  2410";
s32 D_0027AE80 = 0;
s32 D_0027AE84 = 1;

static RemoteCallClient g_padClients[2] __attribute__((aligned(64)));
static PadSlot g_padSlots[2][4];
static u32 D_0062ABC0[2][4][8] __attribute__((aligned(64)));
static u8 g_padRequest[0x80] __attribute__((aligned(64)));

s32 PrintFormatted(const char* fmt, ...);
void* CopyBytes(void* dst, const void* src, s32 size);
void* FillMemory(void* p, s32 value, s32 size);
s32 SendPadDma(s32 port, s32 slot);
s32 ResetPadModule(s32 mode);
s32 SetPadRequestMode(s32 port, s32 slot, s32 mode);
s32 GetPadButtonMask(s32 port, s32 slot);
s32 SendPadMaskRequest(s32 port, s32 slot, s32 data);
s32 GetPadModuleVersion(void);
void RefreshPadFrames(void* start, void* end);
s32 GetIopDmaStatus(s32 id);
s32 StartIopDma(PadDmaTransfer* transfers, s32 n);

/* Sends a slot's DMA words to the IOP, into the half of its IOP buffer the new count selects.
 * The record table holds sixteen transfers, of which one is sent: retail's frame has 0x100
 * bytes of locals with the record at its bottom (docs/TOOLCHAIN.md, "A local's size is the
 * frame"). The failure message is written twice, as cross-jumping merges the copies after
 * allocation; written once, CSE carries the busy test's slot offset into the transfer. */
s32 SendPadDma(s32 port, s32 slot)
{
    PadDmaTransfer transfers[16];
    u32* dma = g_padSlots[port][slot].dma;
    u8* dst;
    s32 id;
    u32 count;

    if (g_padSlots[port][slot].f0C != 0 && GetIopDmaStatus(g_padSlots[port][slot].f0C) >= 0) {
        if (D_0027AE84 != 0)
            PrintFormatted("libpad: sceSifSetDma faild\n");
        return 0;
    }
    count = dma[0] + 1;
    dst = (u8*)g_padSlots[port][slot].f08 + ((count & 1) << 5);
    dma[0] = count;
    RefreshPadFrames(dma, dma + 8);
    transfers[0].dst = dst;
    transfers[0].src = dma;
    transfers[0].size = 0x20;
    transfers[0].attr = 0;
    id = StartIopDma(transfers, 1);
    if (id == 0) {
        if (D_0027AE84 != 0)
            PrintFormatted("libpad: sceSifSetDma faild\n");
        return 0;
    }
    g_padSlots[port][slot].f0C = id;
    return 1;
}

/* The message of a function the linker stripped. */
const char D_0024F758[] = "libpad: tPadDma Structure Invalid\n";

s32 InitPadLibrary(s32 mode)
{
    s32 i;
    s32 version;
    s32 major;

    D_0027AE80 = 1;
    while (BindRemoteService(&g_padClients[0], 0x80000100, 0), g_padClients[0].server == 0) {
        for (i = 0x10000; i != -1; i--) {
        }
    }
    for (;;) {
        BindRemoteService(&g_padClients[1], 0x80000101, 0);
        if (g_padClients[1].server != 0)
            break;
        for (i = 0x10000; i != -1; i--) {
        }
    }
    version = GetPadModuleVersion();
    major = version >> 8;
    if (major != 4) {
        if (D_0027AE84 != 0) {
            PrintFormatted("libpad: Module version mismatch ");
            PrintFormatted("[libpad.a = %d.%d, padman.irx = %d.%d]\n", 4, 0, major, version & 0xFF);
        }
        return 0;
    }
    return ResetPadModule(mode);
}

s32 ResetPadModule(s32 mode)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        g_padSlots[0][i].open = 0;
        g_padSlots[0][i].f18 = 0;
        g_padSlots[0][i].f14 = 0;
        g_padSlots[1][i].open = 0;
        g_padSlots[1][i].f18 = 0;
        g_padSlots[1][i].f14 = 0;
    }
    ((PadRequest*)g_padRequest)->command = 0x10;
    ((PadRequest*)g_padRequest)->arg10 = 0;
    if (CallRemoteService(g_padClients, 1, 0, g_padRequest, 0x80, g_padRequest, 0x80, 0, 0) < 0)
        return 0;
    return ((PadRequest*)g_padRequest)->result;
}

s32 OpenPadPort(s32 port, s32 slot, u8* buffer)
{
    PadRequest* request;
    PadFrame* frame;
    u32* dma;
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
    request->arg10 = buffer;
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

PadFrame* GetNewerPadFrame(s32 port, s32 slot)
{
    PadFrame* frames = (PadFrame*)g_padSlots[port][slot].buffer;
    s32 newer;

    RefreshPadFrames(frames, frames + 2);
    newer = frames[0].count < frames[1].count;
    return &frames[newer];
}

s32 ReadPadFrame(s32 port, s32 slot, u8* data)
{
    PadFrame* frame;

    if (g_padSlots[port][slot].open == 0)
        return 0;
    frame = GetNewerPadFrame(port, slot);
    CopyBytes(data, frame, frame->size);
    return frame->size;
}

s32 GetPadSlotState(s32 port, s32 slot)
{
    PadFrame* frame;

    if (g_padSlots[port][slot].open == 0)
        return 0x63;
    frame = GetNewerPadFrame(port, slot);
    if (frame->state == 6) {
        if (frame->mode == 2)
            return 5;
    }
    return frame->state;
}

LINKER_REMNANT(func_00204608);

s32 SetPadRequestMode(s32 port, s32 slot, s32 mode)
{
    if (g_padSlots[port][slot].open == 0)
        return 0;
    GetNewerPadFrame(port, slot)->mode = mode;
    return 1;
}

u32 GetPadRequestMode(s32 port, s32 slot)
{
    if (g_padSlots[port][slot].open == 0)
        return 0;
    return GetNewerPadFrame(port, slot)->mode;
}

LINKER_REMNANT(func_002046C8);
s32 GetPadReplyTableByte(s32 port, s32 slot, s32 index, s32 kind)
{
    PadFrame* frame;
    s32 count;

    if (g_padSlots[port][slot].open == 0)
        return 0;
    frame = GetNewerPadFrame(port, slot);
    if (frame->f72 != 1)
        return 0;
    if (frame->f64 < 2)
        return 0;
    count = frame->f6A;
    if (index >= count)
        return 0;
    if (index == -1)
        return count;
    switch (kind) {
    case 1:
        return frame->f30[index][0];
    case 2:
        return frame->f30[index][1];
    case 3:
        return frame->f30[index][2];
    case 4:
        return frame->f30[index][3];
    }
    return 0;
}
LINKER_REMNANT(func_002047F0);
s32 GetPadReplyListValue(s32 port, s32 slot, s32 kind, s32 index)
{
    PadFrame* frame;

    if (g_padSlots[port][slot].open == 0)
        return 0;
    frame = GetNewerPadFrame(port, slot);
    if (frame->f72 != 1)
        return 0;
    if (frame->mode == 2)
        return 0;
    switch (kind) {
    case 1:
        if (frame->f65 == 0xF3)
            return 0;
        return frame->f65 >> 4;
    case 2:
        if (frame->f64 == 1)
            return 0;
        return frame->f50[frame->f69];
    case 3:
        if (frame->f64 == 1)
            return 0;
        return frame->f69;
    case 4:
        if (frame->f64 == 1)
            return 0;
        if (index == -1)
            return frame->f68;
        if (index < frame->f68)
            return frame->f50[index];
        return 0;
    }
    return 0;
}

s32 SendPadTwoWordRequest(s32 port, s32 slot, s32 a2, s32 a3)
{
    PadModeRequest* request = (PadModeRequest*)g_padRequest;
    s32 result;

    request->arg0C = a2;
    request->arg10 = a3;
    request->command = 6;
    request->port = port;
    request->slot = slot;
    if (CallRemoteService(g_padClients, 1, 0, request, 0x80, request, 0x80, 0, 0) < 0)
        return 0;
    result = request->result;
    if (result == 1) {
        SetPadRequestMode(port, slot, 2);
        result = request->result;
    }
    return result;
}

s32 SetPadActuatorBytes(s32 port, s32 slot, u8* src)
{
    u32* dma;
    u8* bytes;
    s32 i;
    s32 ok;

    if (GetNewerPadFrame(port, slot)->f72 != 1)
        return 0;
    dma = g_padSlots[port][slot].dma;
    bytes = (u8*)(dma + 3);
    for (i = 0; i < 6; i++)
        bytes[i] = src[i];
    ok = 1;
    dma[1] = 1;
    dma[2] = 6;
    if (SendPadDma(port, slot) != 1)
        ok = 0;
    return ok;
}


s32 SendPadSixByteRequest(s32 port, s32 slot, u8* src)
{
    PadActRequest* request = (PadActRequest*)g_padRequest;
    s32 i;

    request->command = 8;
    request->port = port;
    request->slot = slot;
    i = 0;
    do {
        request->bytes[i] = src[i];
        i++;
    } while (i < 6);
    if (CallRemoteService(g_padClients, 1, 0, request, 0x80, request, 0x80, 0, 0) < 0)
        return 0;
    if (request->result == 1)
        SetPadRequestMode(port, slot, 2);
    return request->result;
}

s32 GetPadButtonMask(s32 port, s32 slot)
{
    PadFrame* frame;

    if (g_padSlots[port][slot].open == 0)
        return 0;
    frame = GetNewerPadFrame(port, slot);
    if (frame->f72 != 1)
        return 0;
    if (frame->f64 < 2)
        return 0;
    if (frame->f66 < 2)
        return 0;
    return frame->f79 + ((u64)frame->f7A << 8) + ((u64)frame->f7B << 16) + ((u64)frame->f7C << 24);
}


s32 SendPadMaskRequest(s32 port, s32 slot, s32 data)
{
    PadInfoRequest* request = (PadInfoRequest*)g_padRequest;
    s32 status;
    s32 result;

    request->data = data;
    request->command = 10;
    request->port = port;
    request->slot = slot;
    status = CallRemoteService(g_padClients, 1, 0, request, 0x80, request, 0x80, 0, 0);
    if (status < 0)
        return 0;
    result = request->result;
    if (result == 1) {
        SetPadRequestMode(port, slot, 2);
        result = request->result;
    }
    return result;
}

s32 HasFullPadMask(s32 port, s32 slot)
{
    if (g_padSlots[port][slot].open == 0)
        return 0;
    return GetPadButtonMask(port, slot) == 0x3FFFF;
}

s32 SendFullPadMask(s32 port, s32 slot)
{
    if (g_padSlots[port][slot].open == 0)
        return 0;
    return SendPadMaskRequest(port, slot, 0xFFF);
}

LINKER_REMNANT(func_00204DA0);

s32 GetPadModuleVersion(void)
{
    PadRequest* request = (PadRequest*)g_padRequest;

    request->command = 0x12;
    if (CallRemoteService(g_padClients, 1, 0, request, 0x80, request, 0x80, 0, 0) < 0)
        return 0;
    return request->result;
}

ASM_FUNC(func_00204E20);
s32 DisableInterrupts(void);
s32 EnableInterrupts(void);
void InvalidateDataCacheRange(u32 start, u32 end);

/* The data cache written back over a range, its ends rounded down to whole lines, with
 * interrupts disabled around it when they are enabled. */
void RefreshPadFrames(void* start, void* end)
{
    u32 enabled = ReadCop0Status();
    enabled &= 0x10000;
    if (enabled)
        DisableInterrupts();
    InvalidateDataCacheRange((u32)start & ~0x3F, (u32)end & ~0x3F);
    if (enabled)
        EnableInterrupts();
}
LINKER_REMNANT(func_00204F48);

/* The names of a slot's states and of a command's results, which no function left in retail
 * reads. */
const char* D_0027AE88[8] = { "DISCONNECT", "", "FINDCTP1", "", "", "EXECCMD", "STABLE", "ERROR" };
const char* D_0027AEA8[3] = { "COMPLETE", "FAILED", "BUSY" };
s32 D_0027AEB4 = 0;
