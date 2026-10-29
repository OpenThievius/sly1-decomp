// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: object fields and helper calls are modeled. The compiler emits
// the two immediate values in opposite registers and schedules the byte
// stores differently from retail.
#include "common.h"

extern u8 D_00261420[];
void func_00123ED0(void);
void func_00152470(void* object, void* self);
s32 func_00140FF8(void* object);

struct Self_00146340 { u8 pad0[0x14]; u8* parent; u8 pad18[0x2B8]; s32 lastA; u8 pad2D4[4]; s32 zero2D8; s32 lastB; u8 pad2E0[0x60]; u32 flags; u8 pad344[0x38]; s32 result37C; u8 pad380[8]; f32 value388; };

void func_00146340(Self_00146340* self)
{
    self->lastA = -1;
    self->zero2D8 = 0;
    self->lastB = -1;
    self->value388 = 30.0f;
    func_00123ED0();
    func_00152470(self->parent + 0x1C54, self);
    s32 result = func_00140FF8(D_00261420);
    self->flags = 1;
    self->result37C = result;
    ((u8*)self)[0x2B0] = 16;
    ((u8*)self)[0x2B3] = 16;
    ((u8*)self)[0x2B2] = 16;
    ((u8*)self)[0x2B1] = 16;
}
