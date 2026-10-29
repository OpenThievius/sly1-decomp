// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_D27C0 {
    u8 pad0[0x14];
    void* owner;
    u8 pad1[0x2718 - 0x18];
    s32 state;
};

void func_001DDA20(void* a);
void func_001DDB58(void* a);
void func_001DDA50(void* a);
void func_001DDBB8(void* a);

void func_001D27C0(Obj_D27C0* a0, s32 a1)
{
    if (a0->state != a1) {
        if (a0->state == -1) {
            func_001DDA20(a0->owner);
            func_001DDB58(a0->owner);
        }
        a0->state = a1;
        if (a1 == -1) {
            func_001DDA50(a0->owner);
            func_001DDBB8(a0->owner);
        }
    }
}

struct Ref_D3500;

struct Node_D3500 {
    Ref_D3500* ref;
    u8 pad0[0xC - 4];
    s32 flags;
};

struct Ref_D3500 {
    s32* vtbl;
    u8 pad0[0x18 - 4];
    Ref_D3500* f18;
    u8 pad1[0x50 - 0x1C];
    s32 f50;
};

struct Self_D3500 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x554 - 0x18];
    s32 f554;
};

extern s32 D_00262E10;

void* func_001BC320(Self_D3500* a);
void func_001D32D8(Self_D3500* a, Ref_D3500* b, s32 c);
void func_001861E8(void* a, s32 b);

void* func_001D3500(Self_D3500* a0, Node_D3500* a1)
{
    void* r = func_001BC320(a0);
    if (r != 0 && (a1->flags & 0x20)) {
        Ref_D3500* a2 = a1->ref;
        s32 v1;
        if (a2->vtbl[2] & 1) {
            v1 = a2->f50;
        } else {
            v1 = a2->f18->f50;
        }
        func_001D32D8(a0, a1->ref, (v1 ^ D_00262E10) == 0);
        func_001861E8(a0->f14, a0->f554);
        a0->f554 = 0;
    }
    return r;
}
