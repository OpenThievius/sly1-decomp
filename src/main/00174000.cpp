// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_177828 {
    u8 pad0[0x4B8];
    s32 f4B8;
    u8 pad1[0x2BD8 - 0x4BC];
    s32 f2BD8;
};

void func_00177828(Obj_177828* self, s32 value)
{
    self->f2BD8 = value;
    self->f4B8 = 0;
}
