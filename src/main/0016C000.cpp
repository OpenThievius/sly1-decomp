// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_001F3A40(void);

void func_0016C4B8(void)
{
    func_001F3A40();
}

extern s32 D_002629C8;

void func_0016DCF0(s32 value)
{
    D_002629C8 = value;
}

struct Obj_16DF30 { u8 pad0[0x6E8]; s32 f6e8; u8 pad1[0x7A0 - 0x6EC]; s32 f7a0; u8 pad2[0x7A8 - 0x7A4]; s32 f7a8; };

void func_001400A8(void* self);

void func_0016DF30(Obj_16DF30* self)
{
    func_001400A8(self);
    self->f6e8 = 0;
    self->f7a0 = -1;
    self->f7a8 = -1;
}

struct Obj_16EC38 { u8 pad0[0x14]; s32 f14; s32 f18; u8 pad1[0xBC - 0x1C]; void* fBC; void* fC0; };

void func_001A7CE8(void* p);

void func_0016EC38(Obj_16EC38* self)
{
    if (self->fC0 == 0) return;
    if (self->f18 < 3) return;
    if (self->f14 != 3) return;
    func_001A7CE8(self->fBC);
}

struct Obj_16F7B0 { u8 pad0[0x21C8]; f32 f21c8; u8 pad1[0x2284 - 0x21CC]; f32 f2284; };

extern void* D_00262E10;
extern u8 D_00262E40[];

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 id, void* table);
void func_00159478(void* a, void* b);

void func_0016F7B0(Obj_16F7B0* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 0x97, D_00262E40);
    func_00159478((u8*)self + 0x2428, self);
    self->f2284 = -1.0f;
    self->f21c8 = -1.0f;
    D_00262E10 = self;
}
