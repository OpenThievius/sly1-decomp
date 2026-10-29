// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: object-base selection and field-store/branch order differ.
#include "common.h"
struct Obj_137328 {
    s32 f0; s32 state; s32 f8; s32 fC;
    s32 f10; s32 f14; s32 f18; s32 f1C; s32 f20;
    s32 f24; s32 f28; s32 f2C; s32 f30; s32 f34; s32 f38; s32 f3C; s32 f40; s32 f44; s32 f48; s32 f4C; s32 f50; s32 f54; s32 f58;
};
s32 func_00137328(Obj_137328* self, s32 a1, s32 a2)
{
    s32 value = self->fC;
    self->state = 1;
    self->f48 = a1;
    self->f40 = a2;
    self->f20 = self->f8;
    self->f10 = a2;
    self->f14 = a2;
    self->f38 = 0;
    self->f44 = 0;
    self->f3C = 0;
    if (value < 0) value += 0xFFFFF;
    value >>= 20;
    if (value < 2) value = 2;
    self->f50 = 0;
    self->f54 = 0;
    self->f4C = value;
    self->f58 = value - 1;
    return 1;
}
