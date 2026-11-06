// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 355/412 (86.2%), checked 2026-11-06
#include "common.h"
// NEAR: body and calls right, tail call right; only the scheduling/register choice of the 10 stores to D_00627800 (s2/s0 setup order) differs

struct Ctl_1F7BE8 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
};

extern u8 D_00626000[];
extern u8 D_00626800[];
extern u8 D_00627000[];
extern Ctl_1F7BE8 D_00627800;
extern s32 D_00277134;

s32 func_001F9D60(void);
void func_001F9DA8(void);
void func_001FA1E8(void);
s32 func_001FA1C0(s32 index);
void func_001FA4A0(u32 index, void (*fn)(void), void* arg);
s32 func_001FA630(u32 a, void* b, s32 c, s32 d, s32 e, s32 f);
s32 func_001F6CF0(u32 reg);
void func_001F6CE0(u32 reg, u32 value);
void func_001F7EA8(void);
void func_001F8010(void);
void func_001F8200(void);
void func_001F7F60(void);

void func_001F7BE8(void)
{
    func_001F9D60();
    if (D_00277134 != 0) {
        func_001F9DA8();
        return;
    }
    s32 one = 1;
    D_00277134 = one;
    func_001F9DA8();
    func_001FA1E8();
    func_001F9D60();
    u8* buf = D_00626000;
    Ctl_1F7BE8* c = &D_00627800;
    c->f4 = (s32)buf | 0x20000000;
    c->f0 = one;
    c->f8 = 0x20;
    c->fC = 0;
    c->f10 = 0;
    c->f14 = (s32)D_00626800 | 0x20000000;
    c->f18 = 0x20;
    c->f1C = (s32)D_00627000 | 0x20000000;
    c->f20 = 0x20;
    c->f24 = 0;
    func_001FA4A0(0x80000008, func_001F7EA8, c);
    func_001FA4A0(0x80000009, func_001F8010, c);
    func_001FA4A0(0x8000000A, func_001F8200, c);
    func_001FA4A0(0x8000000C, func_001F7F60, c);
    func_001F9DA8();
    if (func_001F6CF0(0x80000002) != 0) {
        return;
    }
    s32* p = (s32*)(buf + 0x40);
    p[3] = one;
    func_001FA630(0x80000002, p, 0x10, 0, 0, 0);
    while (func_001FA1C0(0) == 0) {
    }
    func_001F6CE0(0x80000002, 1);
}
