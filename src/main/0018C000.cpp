// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_18D168 { u8 pad0[4]; void* p4; void* p8; u8 pad1[0x18]; s32 p24; s32 p28; s32 p2C; };

s32 func_00209CB8(void* a, void* b, s32* c, s32* d, s32* e);
s32 func_0018BD00(s32 v, s32 code, s32 extra);

s32 func_0018D168(Obj_18D168* a0, s32* a1)
{
    s32 v = func_0018BD00(func_00209CB8(a0->p4, a0->p8, &a0->p24, &a0->p28, &a0->p2C), 1, 0);
    switch (v) {
    case 9: v = 0; break;
    case 10: v = 12; break;
    }
    if (v == 0) { *a1 = a0->p28 << 10; } else { *a1 = 0; }
    return v;
}

s32 func_00209870(void* a, void* b, void* c);
s32 func_0018BD00(s32 v, s32 code, void* extra);

s32 func_0018D2E8(void* a0, void* a1, void* a2, void* a3, void* a4)
{
    return func_0018BD00(func_00209870(a1, a2, a3), 5, a4);
}

void* func_0018D500(u32 n);
void func_001F5C0C(void* p, s32 v, s32 n);

void* func_0018D5C0(u32 n)
{
    void* p = func_0018D500(n);
    if (p) {
        func_001F5C0C(p, 0, n);
    }
    return p;
}

int func_0018D740(void)
{
    return 0;
}

struct Obj_18E678 { u8 pad0[4]; s32 f04; s32 f08; };

void func_0018E6A0(void* self);

void func_0018E678(Obj_18E678* self, s32 a1, s32 a2)
{
    self->f04 = a2;
    self->f08 = a1;
    func_0018E6A0(self);
}

int func_0018E938(void)
{
    return 1;
}

struct Obj_18FF28 {
    u8 pad0[0x5F0];
    s32 f5F0;
    u8 pad1[0xC38 - 0x5F4];
    s32 fC38;
    s32 fC3C;
    s32 fC40;
    s32 fC44;
};

extern u8 D_00269B60[];

void func_001C72A0(void* self);
void func_00124DF8(void* self, s32 n, void* table);
s32 func_001CA758(void* self, s32 id);

void func_0018FF28(Obj_18FF28* self)
{
    func_001C72A0(self);
    func_00124DF8(self, 2, D_00269B60);
    self->f5F0 = func_001CA758(self, 0xEF);
    self->fC38 = func_001CA758(self, 0x16C);
    self->fC3C = func_001CA758(self, 0x16D);
    self->fC40 = func_001CA758(self, 0x16A);
    self->fC44 = func_001CA758(self, 0x16B);
}
