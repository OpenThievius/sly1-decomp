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
// func_001FA670) sends a packet by DMA. func_001FA6B0 and func_001FA7D8 are original assembly,
// and the six leftovers are LINKER_REMNANT (config/us/original_asm.tsv).
#include "common.h"
#include "asm_func.h"

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
extern u8 D_0064C700[];

static Pair_2779B0 D_002779B0 = { 0, D_0064C700 };
static s32 D_002779B8[2] = { 0, 0 };

static u8 D_006292C0[0x80];
static u8 D_00629340[0x40];
static Request_1FA068 D_00629380;
static s32 D_00629394;
static Channel_1FA068 D_00629398;
static Slot_1FA068 D_006293C0[32];
static s32 D_006294C0[32];

s32 func_001FA9C0(void);
void func_001F6920(s32 status);
void func_001F6D10(s32 req, void* arg);
s32 func_001F9D60(void);
s32 func_001F9DA8(void);
void func_001F6C20(s32 a);
void func_001F6CC0(void);
s32 func_001F6970(s32 cause, void* handler, s32 arg);
s32 func_001F6990(s32 cause, s32 id);
void func_001F6E78(s32 cause);
s32 func_001F6E10(s32 cause);
s32 func_001F6CF0(u32 reg);
u32 func_001F6CE0(u32 reg, u32 value);
s32 func_001F6CB0(Transfer_1FA4F8* transfers, s32 n);
s32 func_001F6CA0(Transfer_1FA4F8* transfers, s32 n);
void func_001FA6B0(void);
void func_001FA7D8(void* data, s32 size);

void func_001FA068(void)
{
    func_001FA9C0();
}

LINKER_REMNANT(func_001FA070);

void func_001FA078(s32 status)
{
    func_001FA068();
    func_001F6920(status);
}

void func_001FA0A0(void)
{
    D_002779B0.a = 0;
}

LINKER_REMNANT(func_001FA0B0);

s32 func_001FA0D8(void)
{
    return 1;
}

s32 func_001FA0E0(s32 mode, s32 status)
{
    if (mode == 1) {
        func_001FA078(status);
    }
    return 0;
}

LINKER_REMNANT(func_001FA108);

void func_001FA140(s32 value)
{
    s32 local = value;
    func_001F6D10(0x10, &local);
}

LINKER_REMNANT(func_001FA168);

void func_001FA190(Packet_1FA068* packet, Channel_1FA068* channel)
{
    channel->words[packet->index] = packet->value;
}

s32 func_001FA1B0(Packet_1FA068* packet, Channel_1FA068* channel)
{
    s32 value = packet->index;
    channel->iop = value;
    return value;
}

s32 func_001FA1C0(s32 index)
{
    return D_006294C0[index];
}

LINKER_REMNANT(func_001FA1D8);

s32 func_001FA630(u32 cmd, void* packet, s32 size, void* data, s32 addr, s32 count);

void func_001FA1E8(void)
{
    s32 i;
    func_001F9D60();
    if (D_002779B8[0] != 0) {
        func_001F9DA8();
        return;
    }
    D_002779B8[0] = 1;
    D_00629398.buffer = (u32)D_006292C0 | 0x20000000;
    D_00629398.buffer2 = (u32)D_00629340 | 0x20000000;
    D_00629398.system_count = 0x20;
    D_00629398.iop = 0;
    D_00629398.system = D_006293C0;
    D_00629398.user = 0;
    D_00629398.user_count = 0;
    D_00629398.words = D_006294C0;
    for (i = 0; i < 32; i++) {
        D_006293C0[i].handler = 0;
        D_006293C0[i].arg = 0;
    }
    for (i = 0; i < 32; i++) {
        D_006294C0[i] = 0;
    }
    D_006293C0[0].handler = (Handler_1FA068)func_001FA1B0;
    D_006293C0[1].handler = func_001FA190;
    D_006293C0[0].arg = &D_00629398;
    D_006293C0[1].arg = &D_00629398;
    func_001F9DA8();
    func_001F6C20(0);
    if ((*(volatile u32*)0x1000E010 & 0x20) != 0) {
        *(volatile u32*)0x1000E010 = 0x20;
    }
    if ((*(volatile u32*)0x1000C000 & 0x100) == 0) {
        func_001F6CC0();
    }
    D_00629394 = func_001F6970(5, (void*)func_001FA6B0, 0);
    func_001F6E78(5);
    D_00629398.iop = func_001F6CF0(0x80000000);
    if (D_00629398.iop != 0) {
        D_00629380.buffer = D_006292C0;
        func_001FA630(0x80000000, &D_00629380, 0x14, 0, 0, 0);
        return;
    }
    while ((func_001F6CF0(4) & 0x20000) == 0) {
    }
    D_00629398.iop = func_001F6CF0(2);
    func_001F6CE0(0x80000000, D_00629398.iop);
    func_001F6CE0(0x80000001, (u32)&D_00629398);
    D_00629380.buffer = D_006292C0;
    D_00629380.opt = 0;
    func_001FA630(0x80000002, &D_00629380, 0x14, 0, 0, 0);
}

void func_001FA468(void)
{
    (void)func_001F6E10(5);
    (void)func_001F6990(5, D_00629394);
    D_002779B8[0] = 0;
}

void func_001FA4A0(s32 cmd, Handler_1FA068 handler, void* arg)
{
    s32 off = cmd << 3;
    if (cmd < 0) {
        cmd = (s32)D_00629398.system;
    } else {
        cmd = (s32)D_00629398.user;
    }
    off += cmd;
    Slot_1FA068* slot = (Slot_1FA068*)off;
    slot->handler = handler;
    slot->arg = arg;
}

void func_001FA4D0(s32 cmd)
{
    s32 off = cmd << 3;
    if (cmd < 0) {
        cmd = (s32)D_00629398.system;
    } else {
        cmd = (s32)D_00629398.user;
    }
    off += cmd;
    ((Slot_1FA068*)off)->handler = 0;
}

s32 func_001FA4F8(u32 cmd, s32 flags, Header_1FA4F8* obj, s32 size, void* data, s32 addr, s32 count)
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
            func_001FA7D8(data, count);
        }
    } else {
        obj->w4 = 0;
        obj->w0 = ((u8*)obj)[0];
    }
    recs[n].w0 = (s32)obj;
    recs[n].w4 = D_00629398.iop;
    recs[n].w8 = size;
    obj->w8 = cmd;
    ((u8*)obj)[0] = (u8)size;
    recs[n].wC = 0x44;
    func_001FA7D8(obj, size);
    n++;
    if (flags & 1) {
        result = func_001F6CB0(recs, n);
    } else {
        result = func_001F6CA0(recs, n);
    }
    return result;
}

s32 func_001FA630(u32 cmd, void* packet, s32 size, void* data, s32 addr, s32 count)
{
    return func_001FA4F8(cmd, 0, (Header_1FA4F8*)packet, size, data, addr, count);
}

s32 func_001FA670(u32 cmd, void* packet, s32 size, void* data, s32 addr, s32 count)
{
    return func_001FA4F8(cmd, 1, (Header_1FA4F8*)packet, size, data, addr, count);
}

ASM_FUNC(func_001FA6B0);

ASM_FUNC(func_001FA7D8);

LINKER_REMNANT(func_001FA884);
