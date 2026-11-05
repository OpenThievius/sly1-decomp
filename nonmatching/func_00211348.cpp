// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 623/628 (99.2%), checked 2026-11-05
#include "common.h"
// NEAR: only the first status poll differs: retail keeps the 0x10002010 address in v1 and the value in v0, ours swaps v0/v1 (5 instructions)

struct Queue_211348;
struct Self_211348 {
    u8 pad000[0xD8];
    s32 fD8;
    u8 pad0DC[0x858 - 0xDC];
    Queue_211348* f858;
};

struct Desc_211348 {
    u32 addr;
    s32 pad4[2];
    s32 w;
    s32 h;
};

struct Msg_211348 {
    s32 cmd;
    s32 pad04[7];
};

struct Xfer_211348 {
    u32 size;
    u32 addr;
};

s32 func_001F6980(s32 channel, s32 (*handler)(s32, void*), s32 next, void* arg);
s32 func_001F6990(s32 channel, s32 id);
s32 func_001F6E10(s32 channel);
s32 func_001F6E78(s32 channel);
s32 func_001F9D60(void);
s32 func_001F9DA8(void);
s32 func_00211240(s32 unused, void* p);
void func_0020B190(Queue_211348* q, Msg_211348* m);
void func_0020F0C0(Self_211348* self, u32 value);
void func_00210E00(Self_211348* self, u32 addr, u32 size);
void func_00211090(Self_211348* self, s32 addr, s32 size);

void func_00211348(Self_211348* self, Desc_211348* d)
{
    Msg_211348 msg;
    Xfer_211348 xfer;
    s32 count = d->w * d->h;
    msg.cmd = 2;
    func_0020B190(self->f858, &msg);
    if ((*(volatile u32*)0x10002010 & 0x4000) != 0) {
        *(volatile u32*)0x10002010 = 0x40000000;
    }
    s32 small = count < 0x400;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    func_0020F0C0(self, 0);
    u32 addr = d->addr;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    u32 chunk = 0xFFFF;
    xfer.size = count * 0x18;
    xfer.addr = addr & 0xFFFFFFF;
    if (xfer.size > chunk) {
        s32 id = func_001F6980(4, func_00211240, 0, &xfer);
        *(volatile u32*)0x1000E010 = 0x10;
        func_001F6E78(4);
        (void)func_001F9D60();
        *(volatile u32*)0x1000B410 = xfer.addr;
        *(volatile u32*)0x1000B420 = chunk;
        *(volatile u32*)0x1000B400 = 0x101;
        (void)func_001F9DA8();
        xfer.addr = (xfer.addr + 0xFFFF0) & 0xFFFFFFF;
        xfer.size = xfer.size - chunk;
        if (small) {
            func_00210E00(self, self->fD8, count);
        } else {
            func_00211090(self, self->fD8, count);
        }
        func_001F6E10(4);
        func_001F6990(4, id);
    } else {
        (void)func_001F9D60();
        *(volatile u32*)0x1000B410 = d->addr & 0xFFFFFFF;
        *(volatile u32*)0x1000B420 = xfer.size;
        *(volatile u32*)0x1000B400 = 0x101;
        (void)func_001F9DA8();
        xfer.size = 0;
        if (small) {
            func_00210E00(self, self->fD8, count);
        } else {
            func_00211090(self, self->fD8, count);
        }
    }
    msg.cmd = 3;
    func_0020B190(self->f858, &msg);
}
