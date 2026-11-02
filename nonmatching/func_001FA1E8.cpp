// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 610/640 (95.3%), checked 2026-11-02
#include "common.h"

struct Ctl_1FA1E8 {
    u32 f0;
    u32 f4;
    s32 f8;
    void* fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32* f1C;
};

struct Slot_1FA1E8 {
    void* f0;
    void* f4;
};

struct Req_1FA1E8 {
    s32 pad[4];
    u32 f10;
};

extern s32 D_002779B8;
extern Ctl_1FA1E8 D_00629398;
extern Slot_1FA1E8 D_006293C0[];
extern s32 D_006294C0[];
extern u8 D_006292C0[];
extern u8 D_00629340[];
extern Req_1FA1E8 D_00629380;
extern s32 D_00629394;

void func_001FA190(void);
void func_001FA1B0(void);
void func_001FA6B0(void);
s32 func_001F9D60(void);
void func_001F9DA8(void);
void func_001F6C20(s32 a);
void func_001F6CC0(void);
s32 func_001F6970(s32 a, void* b, s32 c);
void func_001F6E78(s32 a);
s32 func_001F6CF0(u32 a);
void func_001F6CE0(u32 a, s32 b);
void func_001FA630(u32 index, void* b, s32 c, s32 d, s32 e, s32 f);

void func_001FA1E8(void)
{
    s32 i;
    func_001F9D60();
    if (D_002779B8 != 0) {
        func_001F9DA8();
        return;
    }
    D_002779B8 = 1;
    D_00629398.f0 = (u32)D_006292C0 | 0x20000000;
    D_00629398.f4 = (u32)D_00629340 | 0x20000000;
    D_00629398.f10 = 0x20;
    D_00629398.f8 = 0;
    D_00629398.fC = D_006293C0;
    D_00629398.f14 = 0;
    D_00629398.f18 = 0;
    D_00629398.f1C = D_006294C0;
    Slot_1FA1E8* p = D_006293C0;
    for (i = 31; i >= 0; i--) {
        p->f0 = 0;
        p->f4 = 0;
        p++;
    }
    for (i = 31; i >= 0; i--) {
        D_006294C0[i] = 0;
    }
    D_006293C0[0].f0 = (void*)func_001FA1B0;
    D_006293C0[1].f0 = (void*)func_001FA190;
    D_006293C0[0].f4 = &D_00629398;
    D_006293C0[1].f4 = &D_00629398;
    i = 0x20;
    func_001F9DA8();
    func_001F6C20(0);
    if ((*(volatile u32*)0x1000E010 & 0x20) != 0) {
        *(volatile u32*)0x1000E010 = i;
    }
    if ((*(volatile u32*)0x1000C000 & 0x100) == 0) {
        func_001F6CC0();
    }
    D_00629394 = func_001F6970(5, (void*)func_001FA6B0, 0);
    func_001F6E78(5);
    D_00629398.f8 = func_001F6CF0(0x80000000);
    if (D_00629398.f8 != 0) {
        D_00629380.f10 = (u32)D_006292C0;
        func_001FA630(0x80000000, &D_00629380, 0x14, 0, 0, 0);
        return;
    }
    while ((func_001F6CF0(4) & 0x20000) == 0) {
    }
    D_00629398.f8 = func_001F6CF0(2);
    func_001F6CE0(0x80000000, D_00629398.f8);
    func_001F6CE0(0x80000001, (s32)&D_00629398);
    D_00629380.f10 = (u32)D_006292C0;
    *(s32*)((u8*)&D_00629380 + 0xC) = 0;
    func_001FA630(0x80000002, &D_00629380, 0x14, 0, 0, 0);
}
