// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_171DD8 { u8 pad0[0x620]; s32 f620; s32 f624; s32 f628; s32 f62C; u8 pad1[0x8]; f32 f638; u8 pad2[0x54]; void* f690; u8 pad3[0x2C]; s32 f6C0; u8 pad4[0xAC4]; void* f1188; s32 f118C; u8 pad5[0x10A4]; void* f2234; u8 pad6[0x2D4]; s32 f250C; s32 f2510; };
struct Loc_171DD8 { u8 pad0[8]; f32 f8; };

s32 func_00171180(void* self);
s32 func_00171C80(void* self, void* p, s32 n);
void func_001719E8(void* self, s32 a, s32 b, s32 c, f32 k, void* d);
void func_001278A8(s32 a, s32 b, void* c, s32 d, void* e, s32 f, s32 g);
f32 func_001EA480(f32 a, f32 b);
s32 func_001B63C0(void* p, s32 n);
void func_001B6628(void* p, s32 n);

extern f32 D_00261860;

void func_00171DD8(Obj_171DD8* self)
{
    Loc_171DD8 loc;
    if (func_00171180(self) == 0) {
        if (self->f690 != 0) {
            func_001278A8(self->f6C0, 0, (u8*)self + 0x6A0, 0, &loc, 0, 0);
            loc.f8 = func_001EA480(loc.f8, 10.0f);
            self->f638 = self->f638 + loc.f8 * D_00261860;
        }
    }
    if (self->f250C == 0) return;
    u8* p1 = (u8*)self + 0x1190;
    f32 k = 5.0f;
    func_001719E8(self, self->f628, self->f620, self->f250C, k, p1);
    u8* p2 = (u8*)self + 0x1290;
    func_001719E8(self, self->f62C, self->f624, self->f2510, k, p2);
    if (func_00171C80(self, p1, self->f250C) != 0) {
        if (func_00171C80(self, p2, self->f2510) != 0) return;
    }
    if (self->f118C != 0) return;
    if (self->f1188 == 0) return;
    if (func_001B63C0(self->f1188, 0x148) >= 0) func_001B6628(self->f2234, 0x148);
    self->f118C = 1;
}

struct Obj_172AE0 { u8 pad0[0x21CC]; s32 f21cc; };

void func_001B9680(void* self);

void func_00172AE0(Obj_172AE0* self)
{
    func_001B9680(self);
    self->f21cc = 0;
}

extern u8* D_002623C0;

void func_001922E8(void* a, void* b);
void func_001D29C8(s32 id);

void func_00173708(void* a, void* b)
{
    func_001922E8(a, b);
    s32 id;
    if (b != 0) id = *(s32*)(D_002623C0 + 0x19FC);
    else id = -1;
    func_001D29C8(id);
}
