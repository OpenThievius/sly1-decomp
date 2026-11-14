// SPDX-License-Identifier: AGPL-3.0-or-later
// The kernel library's code from 0x1FA068 to 0x1FA890, built whole as one file between two exact
// edges (config/us/files.tsv); it could be several objects (the leftovers of stripped functions
// between its groups are no evidence either way). It holds the small calls func_001FA068 to
// func_001FA0E0 (func_001FA078 runs the TLB set-up func_001FA9C0 through func_001FA068, then the
// system call stub 4, func_001F6920) and the request func_001FA140, then the command channel to
// the IOP: func_001FA1E8 sets it up once (the flag D_002779B8: the control record D_00629398,
// the table of 32 handler slots D_006293C0 and the 32 words D_006294C0, the receive buffers
// D_006292C0 and D_00629340, the interrupt handler func_001FA6B0), func_001FA4A0 and
// func_001FA4D0 set and clear a command's handler, and func_001FA4F8 (through func_001FA630 and
// func_001FA670) sends a packet by DMA. func_001FA7D8 is original assembly, and the six
// leftovers are LINKER_REMNANT (config/us/original_asm.tsv).
#include "common.h"
#include "asm_func.h"
#include "system.h"

struct Packet_1FA068 {
    s32 head[4];
    s32 index;
    s32 value;
};

struct Channel_1FA068;
typedef void (*Handler_1FA068)(Packet_1FA068* packet, Channel_1FA068* channel);

struct Slot_1FA068 {
    Handler_1FA068 handler;
    void* arg;
};

// The channel's control record: the receive buffers' uncached addresses, the IOP's address, the
// system and user handler tables, the table of words, and two words no code reads (its label
// is 0x28 bytes).
struct Channel_1FA068 {
    u32 buffer;
    u32 buffer2;
    s32 iop;
    Slot_1FA068* system;
    s32 system_count;
    Slot_1FA068* user;
    s32 user_count;
    s32* words;
    s32 f20;
    s32 f24;
};

struct Request_1FA068 {
    s32 head[3];
    s32 opt;
    void* buffer;
};

struct Header_1FA4F8 { s32 w0; s32 w4; s32 w8; };
struct Transfer_1FA4F8 { s32 w0; s32 w4; s32 w8; s32 wC; };

struct Pair_2779B0 { s32 a; void* b; };
extern u8 g_imageEndMarker[];

static Pair_2779B0 g_imageEndRecord = { 0, g_imageEndMarker };
static s32 g_commandChannelReady[2] = { 0, 0 };

static u8 g_commandReceiveBuffer[0x80];
static u8 g_commandReceiveBuffer2[0x40];
static Request_1FA068 g_commandRequest;
static s32 g_commandDmaHandlerId;
static Channel_1FA068 g_commandChannel;
static Slot_1FA068 g_commandSystemSlots[32];
static s32 g_commandChannelWords[32];

s32 SetUpTlbForMemory(void);
void ExitProgramSyscall(s32 status);
void CallDebugService(s32 req, void* arg);
extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);
extern "C" void SyncDataCache(s32 a);
void ArmIopDmaChain(void);
s32 AddDmaHandler(s32 cause, void* handler, s32 arg);
s32 RemoveDmaHandler(s32 cause, s32 id);
s32 EnableDmaInterrupt(s32 cause);
s32 DisableDmaInterrupt(s32 cause);
s32 ReadIopRegister(u32 reg);
u32 WriteIopRegister(u32 reg, u32 value);
s32 StartIopDmaFromInterrupt(Transfer_1FA4F8* transfers, s32 n);
extern "C" s32 StartIopDma(Transfer_1FA4F8* transfers, s32 n);
s32 HandleCommandInterrupt(s32 cause);
extern "C" void WriteBackDataCacheRange(void* data, s32 size);

void SetUpTlb(void)
{
    SetUpTlbForMemory();
}

LINKER_REMNANT(func_001FA070);

extern "C" void TerminateProgram(s32 status)
{
    SetUpTlb();
    ExitProgramSyscall(status);
}

void ClearImageEndRecordWord(void)
{
    g_imageEndRecord.a = 0;
}

LINKER_REMNANT(func_001FA0B0);

extern "C" s32 GetProcessId(void)
{
    return 1;
}

extern "C" s32 SignalProcess(s32 mode, s32 status)
{
    if (mode == 1) {
        TerminateProgram(status);
    }
    return 0;
}

LINKER_REMNANT(func_001FA108);

void PrintToDebugConsole(const u8* text)
{
    const u8* local = text;
    CallDebugService(0x10, &local);
}

LINKER_REMNANT(func_001FA168);

void StoreChannelWord(Packet_1FA068* packet, Channel_1FA068* channel)
{
    channel->words[packet->index] = packet->value;
}

s32 StoreIopChannelAddress(Packet_1FA068* packet, Channel_1FA068* channel)
{
    s32 value = packet->index;
    channel->iop = value;
    return value;
}

s32 GetChannelWord(s32 index)
{
    return g_commandChannelWords[index];
}

LINKER_REMNANT(func_001FA1D8);

s32 SendCommand(u32 cmd, void* packet, s32 size, void* data, s32 addr, s32 count);

void InitCommandChannel(void)
{
    s32 i;
    DisableInterrupts();
    if (g_commandChannelReady[0] != 0) {
        EnableInterrupts();
        return;
    }
    g_commandChannelReady[0] = 1;
    g_commandChannel.buffer = (u32)g_commandReceiveBuffer | 0x20000000;
    g_commandChannel.buffer2 = (u32)g_commandReceiveBuffer2 | 0x20000000;
    g_commandChannel.system_count = 0x20;
    g_commandChannel.iop = 0;
    g_commandChannel.system = g_commandSystemSlots;
    g_commandChannel.user = 0;
    g_commandChannel.user_count = 0;
    g_commandChannel.words = g_commandChannelWords;
    for (i = 0; i < 32; i++) {
        g_commandSystemSlots[i].handler = 0;
        g_commandSystemSlots[i].arg = 0;
    }
    for (i = 0; i < 32; i++) {
        g_commandChannelWords[i] = 0;
    }
    g_commandSystemSlots[0].handler = (Handler_1FA068)StoreIopChannelAddress;
    g_commandSystemSlots[1].handler = StoreChannelWord;
    g_commandSystemSlots[0].arg = &g_commandChannel;
    g_commandSystemSlots[1].arg = &g_commandChannel;
    EnableInterrupts();
    SyncDataCache(0);
    if ((*(volatile u32*)0x1000E010 & 0x20) != 0) {
        *(volatile u32*)0x1000E010 = 0x20;
    }
    if ((*(volatile u32*)0x1000C000 & 0x100) == 0) {
        ArmIopDmaChain();
    }
    g_commandDmaHandlerId = AddDmaHandler(5, (void*)HandleCommandInterrupt, 0);
    EnableDmaInterrupt(5);
    g_commandChannel.iop = ReadIopRegister(0x80000000);
    if (g_commandChannel.iop != 0) {
        g_commandRequest.buffer = g_commandReceiveBuffer;
        SendCommand(0x80000000, &g_commandRequest, 0x14, 0, 0, 0);
        return;
    }
    while ((ReadIopRegister(4) & 0x20000) == 0) {
    }
    g_commandChannel.iop = ReadIopRegister(2);
    WriteIopRegister(0x80000000, g_commandChannel.iop);
    WriteIopRegister(0x80000001, (u32)&g_commandChannel);
    g_commandRequest.buffer = g_commandReceiveBuffer;
    g_commandRequest.opt = 0;
    SendCommand(0x80000002, &g_commandRequest, 0x14, 0, 0, 0);
}

void ShutDownCommandChannel(void)
{
    (void)DisableDmaInterrupt(5);
    (void)RemoveDmaHandler(5, g_commandDmaHandlerId);
    g_commandChannelReady[0] = 0;
}

extern "C" void SetCommandHandler(s32 cmd, Handler_1FA068 handler, void* arg)
{
    s32 off = cmd << 3;
    if (cmd < 0) {
        cmd = (s32)g_commandChannel.system;
    } else {
        cmd = (s32)g_commandChannel.user;
    }
    off += cmd;
    Slot_1FA068* slot = (Slot_1FA068*)off;
    slot->handler = handler;
    slot->arg = arg;
}

extern "C" void ClearCommandHandler(s32 cmd)
{
    s32 off = cmd << 3;
    if (cmd < 0) {
        cmd = (s32)g_commandChannel.system;
    } else {
        cmd = (s32)g_commandChannel.user;
    }
    off += cmd;
    ((Slot_1FA068*)off)->handler = 0;
}

s32 SendCommandPacket(u32 cmd, s32 flags, Header_1FA4F8* obj, s32 size, void* data, s32 addr, s32 count)
{
    Transfer_1FA4F8 recs[2];
    s32 n;
    s32 result;

    if ((u32)(size - 0x10) >= 0x61u) {
        return 0;
    }
    n = 0;
    if (count > 0) {
        u8 lo = ((u8*)obj)[0];
        n = 1;
        recs[0].w0 = (s32)data;
        recs[0].w4 = addr;
        obj->w4 = addr;
        obj->w0 = lo | (count << 8);
        recs[0].w8 = count;
        recs[0].wC = 0;
        if (flags & 4) {
            WriteBackDataCacheRange(data, count);
        }
    } else {
        obj->w4 = 0;
        obj->w0 = ((u8*)obj)[0];
    }
    recs[n].w0 = (s32)obj;
    recs[n].w4 = g_commandChannel.iop;
    recs[n].w8 = size;
    obj->w8 = cmd;
    ((u8*)obj)[0] = (u8)size;
    recs[n].wC = 0x44;
    WriteBackDataCacheRange(obj, size);
    n++;
    if (flags & 1) {
        result = StartIopDmaFromInterrupt(recs, n);
    } else {
        result = StartIopDma(recs, n);
    }
    return result;
}

s32 SendCommand(u32 cmd, void* packet, s32 size, void* data, s32 addr, s32 count)
{
    return SendCommandPacket(cmd, 0, (Header_1FA4F8*)packet, size, data, addr, count);
}

s32 SendCommandFromInterrupt(u32 cmd, void* packet, s32 size, void* data, s32 addr, s32 count)
{
    return SendCommandPacket(cmd, 1, (Header_1FA4F8*)packet, size, data, addr, count);
}

s32 ArmIopDmaChainFromInterrupt(void);

// A quadword, moved with lq and sq.
typedef unsigned int Quad_1FA6B0 __attribute__((mode(TI)));

// The DMA interrupt handler of the command channel: with interrupts enabled again, takes the
// packet from the receive buffer (the low byte of its first word is its size; zero when none
// came), frees the buffer, re-arms the DMA chain and runs the handler of the packet's command,
// a system command (the top bit set) or a user one, then ends the handler.
// The receive buffer is written by the DMA channel, so its quadwords are volatile, and the
// stack copy is declared with the same volatile quadword type: retail loads the copy's command
// word again at each use (three `lw 8(sp)`) and leaves the branch's delay slot empty, which
// only a volatile read gives (docs/toolchain/alias-classes.md, "A stack word loaded at each
// use beside an empty branch slot is a volatile read"). The maintainer accepted this placement
// on 2026-11-12: the qualifier belongs to the type of DMA-written data. One
// int holds the size in bytes, then in quadwords, then the command's index, and one pointer
// the handler of either table: each is a variable set several times, which is global-alloc's
// ($a1 and $a2 throughout). As the index it lives beside the table's count in $a0, so the
// quadword count cannot take $a0 and the loop's counter is a copy of it
// (docs/toolchain/alias-classes.md, "One int for a size, a count and an index").
s32 HandleCommandInterrupt(s32 cause)
{
    volatile Quad_1FA6B0 local[7];
    Channel_1FA068* ch;
    volatile u8* buffer;
    volatile Packet_1FA068* packet;
    volatile Quad_1FA6B0* src;
    Handler_1FA068 handler;
    s32 n;
    s32 i;

    EnableInterrupts();
    ch = &g_commandChannel;
    buffer = (volatile u8*)ch->buffer;
    n = buffer[0];
    if (n == 0) {
        return 0;
    }
    n = (n + 15) / 16;
    buffer[0] = 0;
    src = (volatile Quad_1FA6B0*)buffer;
    for (i = 0; i < n; i++) {
        local[i] = *src++;
    }
    ArmIopDmaChainFromInterrupt();
    packet = (volatile Packet_1FA068*)local;
    if (packet->head[2] < 0) {
        n = packet->head[2] & 0x7FFFFFFF;
        if (n < ch->system_count) {
            handler = ch->system[n].handler;
            if (handler != 0) {
                handler((Packet_1FA068*)packet, (Channel_1FA068*)ch->system[n].arg);
            }
        }
    } else {
        n = packet->head[2];
        if (n < ch->user_count) {
            handler = ch->user[n].handler;
            if (handler != 0) {
                handler((Packet_1FA068*)packet, (Channel_1FA068*)ch->user[n].arg);
            }
        }
    }
    SyncAndEnableInterrupts();
    return 0;
}

ASM_FUNC(func_001FA7D8);

LINKER_REMNANT(func_001FA884);
