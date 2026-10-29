// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: alignment calculation registers and field-store order differ.
#include "common.h"
struct Obj_137290 { s32 f0; s32 f4; s32 f8; s32 fC; u8 pad10[8]; s32 f18; s32 f1C; s32 f20; s32 f24; s32 f28; s32 f2C; s32 f30; };
Obj_137290* func_00137290(Obj_137290* self, s32 a1, s32 a2, s32 a3)
{
    s32 align = (a2 + 0x3F) & -0x40;
    self->f4 = -1;
    self->f0 = a3;
    self->fC = a1 - (align - a2);
    self->f20 = 0;
    self->f18 = 0;
    self->f24 = 0;
    self->f1C = 0;
    self->f30 = 0;
    self->f28 = 0;
    self->f2C = 0;
    self->f8 = align;
    return self;
}
