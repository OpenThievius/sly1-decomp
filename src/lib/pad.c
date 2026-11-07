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

/* A port's slot: the buffer of its two frames, its DMA words, whether it is open. */
typedef struct PadSlot {
    u8* buffer;
    u32* dma;
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

/* The requests sent to the pad module, each a view of the request buffer. */
typedef struct PadRequest {
    s32 command;
    s32 port;
    s32 slot;
    s32 result;
    s32 arg10;
    s32 arg14;
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

s32 PrintFormatted(const char* format, ...);
void* CopyBytes(void* dst, const void* src, s32 size);
void* FillMemory(void* dst, s32 value, s32 size);
s32 BindRemoteService(RemoteCallClient* client, u32 server, s32 mode);
s32 CallRemoteService(RemoteCallClient* client, s32 function, s32 mode, void* send, s32 send_size, void* receive,
                  s32 receive_size, void* end, void* end_arg);
s32 SendPadDma(s32 port, s32 slot);
s32 func_00204228(s32 mode);
s32 SetPadRequestMode(s32 port, s32 slot, s32 mode);
s32 func_00204B80(s32 port, s32 slot);
s32 SendPadMaskRequest(s32 port, s32 slot, s32 data);
s32 func_00204DB8(void);
void RefreshPadFrames(void* start, void* end);

INCLUDE_ASM(func_00203FD0);

/* The message of func_00203FD0, defined here while it is assembly (after it: an included
 * function leaves the assembler in .text), and one of a function the linker stripped. */
const char D_0024F738[] = "libpad: sceSifSetDma faild\n";
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
    version = func_00204DB8();
    major = version >> 8;
    if (major != 4) {
        if (D_0027AE84 != 0) {
            PrintFormatted("libpad: Module version mismatch ");
            PrintFormatted("[libpad.a = %d.%d, padman.irx = %d.%d]\n", 4, 0, major, version & 0xFF);
        }
        return 0;
    }
    return func_00204228(mode);
}

s32 func_00204228(s32 mode)
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

INCLUDE_ASM(func_002042C8);

/* The messages of func_002042C8, defined here while it is assembly. */
const char D_0024F7D0[] = "libpad: buffer addr is not 64 byte align. %08x\n";
const char D_0024F800[] = "libpad: pad port is already open [%d][%d]\n";

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
INCLUDE_ASM(func_002046D0);
LINKER_REMNANT(func_002047F0);
INCLUDE_ASM(func_002047F8);

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

INCLUDE_ASM(func_002049E8);

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

INCLUDE_ASM(func_00204B80);

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
    return func_00204B80(port, slot) == 0x3FFFF;
}

s32 SendFullPadMask(s32 port, s32 slot)
{
    if (g_padSlots[port][slot].open == 0)
        return 0;
    return SendPadMaskRequest(port, slot, 0xFFF);
}

LINKER_REMNANT(func_00204DA0);

s32 func_00204DB8(void)
{
    PadRequest* request = (PadRequest*)g_padRequest;

    request->command = 0x12;
    if (CallRemoteService(g_padClients, 1, 0, request, 0x80, request, 0x80, 0, 0) < 0)
        return 0;
    return request->result;
}

ASM_FUNC(func_00204E20);
ASM_FUNC(func_00204EC8);
LINKER_REMNANT(func_00204F48);

/* The names of a slot's states and of a command's results, which no function left in retail
 * reads. */
const char* D_0027AE88[8] = { "DISCONNECT", "", "FINDCTP1", "", "", "EXECCMD", "STABLE", "ERROR" };
const char* D_0027AEA8[3] = { "COMPLETE", "FAILED", "BUSY" };
s32 D_0027AEB4 = 0;
