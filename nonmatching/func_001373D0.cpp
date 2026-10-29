// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: control-flow shape, frame size, and state stores differ.
#include "common.h"
extern s32 func_001F8C38(s32);
extern void func_00203E28(void);
extern void func_0011E2A0(void);
struct Obj_1373D0 { s32 flags; s32 state; u8 pad8[0x10]; s32 f18; s32 f1C; s32 f20; s32 f24; s32 f28; s32 f2C; u8 pad30[4]; s32 f34; u8 pad38[4]; s32 f3C; };
void func_001373D0(Obj_1373D0* self)
{
    s32 result = -1;
    if (self->state == 0) {
        if (self->f34 >= 0) result = func_001F8C38(self->f34);
        self->f2C = 0;
    } else if (self->state == 1) {
        if (self->f3C != 0) {
            if (self->flags & 2) func_00203E28();
            else func_0011E2A0();
        }
        self->f2C = 0;
    } else {
        self->f2C = 0;
    }
    self->state = result;
    self->f20 = 0;
    self->f18 = 0;
    self->f24 = 0;
    self->f1C = 0;
    self->f28 = 0;
}
