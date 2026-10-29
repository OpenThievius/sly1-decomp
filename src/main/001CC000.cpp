// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Vec2_CDB28 {
    f32 x;
    f32 y;
};

void func_001280C0(void* a, s32 b, void* c, Vec2_CDB28* d);
f32 func_00205778(f32 a, f32 b);

void func_001CDB28(u8* a0, f32* a1)
{
    Vec2_CDB28 v;
    void* owner = *(void**)(a0 + 0x2204);
    func_001280C0(*(void**)((u8*)owner + 0x18), 0, (u8*)owner + 0x50, &v);
    *a1 = func_00205778(v.y, v.x);
}

struct Target_001CD088 { s32 pad0; void* target; };
struct Actor_001CD088 { u8 pad0[0x22AC]; Target_001CD088* ref; };

void func_001B9AB0(void* target, void* slot);
void func_001B9AC8(void* target, void* slot);

void func_001CD088(Actor_001CD088* self)
{
    func_001B9AB0(self->ref->target, (u8*)self + 0x22D0);
    func_001B9AC8(self->ref->target, (u8*)self + 0x22E0);
}
