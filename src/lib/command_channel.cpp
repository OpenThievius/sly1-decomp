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

struct CommandPacket {
    s32 head[4];
    s32 index;
    s32 value;
};

struct CommandChannel;
typedef void (*CommandHandler)(CommandPacket* packet, CommandChannel* channel);

struct HandlerSlot {
    CommandHandler handler;
    void* arg;
};

// The channel's control record: the receive buffers' uncached addresses, the IOP's address, the
// system and user handler tables, the table of words, and two words no code reads (its label
// is 0x28 bytes).
struct CommandChannel {
    u32 buffer;
    u32 buffer2;
    s32 iop;
    HandlerSlot* system;
    s32 systemCount;
    HandlerSlot* user;
    s32 userCount;
    s32* words;
    s32 f20;
    s32 f24;
};

struct ChannelRequest {
    s32 head[3];
    s32 opt;
    void* buffer;
};

// The first words of a command packet: its size in the low byte (and the length of the data that
// goes with it above), the data's address, and the command.
struct PacketHeader { s32 sizeCount; s32 addr; s32 cmd; };
// One transfer of the DMA chain to the IOP: its source, its destination, its size and its mode word.
struct DmaTransfer { s32 src; s32 dst; s32 size; s32 mode; };

struct ImageEndRecord { s32 a; void* b; };
extern u8 D_0064C700[];

static ImageEndRecord D_002779B0 = { 0, D_0064C700 };
static s32 D_002779B8[2] = { 0, 0 };

static u8 D_006292C0[0x80];
static u8 D_00629340[0x40];
static ChannelRequest D_00629380;
static s32 D_00629394;
static CommandChannel D_00629398;
static HandlerSlot D_006293C0[32];
static s32 D_006294C0[32];

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
s32 StartIopDmaFromInterrupt(DmaTransfer* transfers, s32 n);
extern "C" s32 StartIopDma(DmaTransfer* transfers, s32 n);
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
    D_002779B0.a = 0;
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

void StoreChannelWord(CommandPacket* packet, CommandChannel* channel)
{
    channel->words[packet->index] = packet->value;
}

s32 StoreIopChannelAddress(CommandPacket* packet, CommandChannel* channel)
{
    s32 value = packet->index;
    channel->iop = value;
    return value;
}

s32 GetChannelWord(s32 index)
{
    return D_006294C0[index];
}

LINKER_REMNANT(func_001FA1D8);

s32 SendCommand(u32 cmd, void* packet, s32 size, void* data, s32 addr, s32 count);

void InitCommandChannel(void)
{
    s32 i;
    DisableInterrupts();
    if (D_002779B8[0] != 0) {
        EnableInterrupts();
        return;
    }
    D_002779B8[0] = 1;
    D_00629398.buffer = (u32)D_006292C0 | 0x20000000;
    D_00629398.buffer2 = (u32)D_00629340 | 0x20000000;
    D_00629398.systemCount = 0x20;
    D_00629398.iop = 0;
    D_00629398.system = D_006293C0;
    D_00629398.user = 0;
    D_00629398.userCount = 0;
    D_00629398.words = D_006294C0;
    for (i = 0; i < 32; i++) {
        D_006293C0[i].handler = 0;
        D_006293C0[i].arg = 0;
    }
    for (i = 0; i < 32; i++) {
        D_006294C0[i] = 0;
    }
    D_006293C0[0].handler = (CommandHandler)StoreIopChannelAddress;
    D_006293C0[1].handler = StoreChannelWord;
    D_006293C0[0].arg = &D_00629398;
    D_006293C0[1].arg = &D_00629398;
    EnableInterrupts();
    SyncDataCache(0);
    if ((*(volatile u32*)0x1000E010 & 0x20) != 0) {
        *(volatile u32*)0x1000E010 = 0x20;
    }
    if ((*(volatile u32*)0x1000C000 & 0x100) == 0) {
        ArmIopDmaChain();
    }
    D_00629394 = AddDmaHandler(5, (void*)HandleCommandInterrupt, 0);
    EnableDmaInterrupt(5);
    D_00629398.iop = ReadIopRegister(0x80000000);
    if (D_00629398.iop != 0) {
        D_00629380.buffer = D_006292C0;
        SendCommand(0x80000000, &D_00629380, 0x14, 0, 0, 0);
        return;
    }
    while ((ReadIopRegister(4) & 0x20000) == 0) {
    }
    D_00629398.iop = ReadIopRegister(2);
    WriteIopRegister(0x80000000, D_00629398.iop);
    WriteIopRegister(0x80000001, (u32)&D_00629398);
    D_00629380.buffer = D_006292C0;
    D_00629380.opt = 0;
    SendCommand(0x80000002, &D_00629380, 0x14, 0, 0, 0);
}

void ShutDownCommandChannel(void)
{
    (void)DisableDmaInterrupt(5);
    (void)RemoveDmaHandler(5, D_00629394);
    D_002779B8[0] = 0;
}

extern "C" void SetCommandHandler(s32 cmd, CommandHandler handler, void* arg)
{
    s32 off = cmd << 3;
    if (cmd < 0) {
        cmd = (s32)D_00629398.system;
    } else {
        cmd = (s32)D_00629398.user;
    }
    off += cmd;
    HandlerSlot* slot = (HandlerSlot*)off;
    slot->handler = handler;
    slot->arg = arg;
}

extern "C" void ClearCommandHandler(s32 cmd)
{
    s32 off = cmd << 3;
    if (cmd < 0) {
        cmd = (s32)D_00629398.system;
    } else {
        cmd = (s32)D_00629398.user;
    }
    off += cmd;
    ((HandlerSlot*)off)->handler = 0;
}

s32 SendCommandPacket(u32 cmd, s32 flags, PacketHeader* obj, s32 size, void* data, s32 addr, s32 count)
{
    DmaTransfer recs[2];
    s32 n;
    s32 result;

    if ((u32)(size - 0x10) >= 0x61u) {
        return 0;
    }
    n = 0;
    if (count > 0) {
        u8 lo = ((u8*)obj)[0];
        n = 1;
        recs[0].src = (s32)data;
        recs[0].dst = addr;
        obj->addr = addr;
        obj->sizeCount = lo | (count << 8);
        recs[0].size = count;
        recs[0].mode = 0;
        if (flags & 4) {
            WriteBackDataCacheRange(data, count);
        }
    } else {
        obj->addr = 0;
        obj->sizeCount = ((u8*)obj)[0];
    }
    recs[n].src = (s32)obj;
    recs[n].dst = D_00629398.iop;
    recs[n].size = size;
    obj->cmd = cmd;
    ((u8*)obj)[0] = (u8)size;
    recs[n].mode = 0x44;
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
    return SendCommandPacket(cmd, 0, (PacketHeader*)packet, size, data, addr, count);
}

s32 SendCommandFromInterrupt(u32 cmd, void* packet, s32 size, void* data, s32 addr, s32 count)
{
    return SendCommandPacket(cmd, 1, (PacketHeader*)packet, size, data, addr, count);
}

s32 ArmIopDmaChainFromInterrupt(void);

// A quadword, moved with lq and sq.
typedef unsigned int Quadword __attribute__((mode(TI)));

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
    volatile Quadword local[7];
    CommandChannel* ch;
    volatile u8* buffer;
    volatile CommandPacket* packet;
    volatile Quadword* src;
    CommandHandler handler;
    s32 n;
    s32 i;

    EnableInterrupts();
    ch = &D_00629398;
    buffer = (volatile u8*)ch->buffer;
    n = buffer[0];
    if (n == 0) {
        return 0;
    }
    n = (n + 15) / 16;
    buffer[0] = 0;
    src = (volatile Quadword*)buffer;
    for (i = 0; i < n; i++) {
        local[i] = *src++;
    }
    ArmIopDmaChainFromInterrupt();
    packet = (volatile CommandPacket*)local;
    if (packet->head[2] < 0) {
        n = packet->head[2] & 0x7FFFFFFF;
        if (n < ch->systemCount) {
            handler = ch->system[n].handler;
            if (handler != 0) {
                handler((CommandPacket*)packet, (CommandChannel*)ch->system[n].arg);
            }
        }
    } else {
        n = packet->head[2];
        if (n < ch->userCount) {
            handler = ch->user[n].handler;
            if (handler != 0) {
                handler((CommandPacket*)packet, (CommandChannel*)ch->user[n].arg);
            }
        }
    }
    SyncAndEnableInterrupts();
    return 0;
}

ASM_FUNC(func_001FA7D8);

LINKER_REMNANT(func_001FA884);
