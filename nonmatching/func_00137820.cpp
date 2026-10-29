// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: register allocation and field access scheduling differ.
#include "common.h"
extern void func_001377C0(void*);
extern void func_00137490(void*);
extern void func_00193288(void*);
struct Obj_137820 { u8 pad0[4]; s32 state; u8 pad8[8]; s32 f10; s32 f14; u8 pad18[0xC]; s32 f24; u8 pad28[4]; s32 f2C; s32 f30; };
void func_00137820(Obj_137820* self)
{
    if (self->state != 0) {
        if (self->state == 1) func_00137490(self);
    } else {
        func_001377C0(self);
    }
    s32 amount = self->f14 - self->f24;
    self->f14 = amount > 0 ? amount : 0;
    if (self->f30 != 0) func_00193288((u8*)self->f30);
}
