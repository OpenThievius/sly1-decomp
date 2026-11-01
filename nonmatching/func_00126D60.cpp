// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 148/132, checked 2026-11-01
// NEAR: This candidate is 148 bytes versus retail 132; branch layout and
//        floating-point operations differ.
#include "common.h"

struct Timed_00126D60 { u8 pad0[4]; f32 rate; f32 result; };
struct Object_00126D60 { u8 pad0[0x298]; Timed_00126D60* timed; };
extern s32 func_00182FC8(void*);
extern void func_00126C58(void*);

void func_00126D60(Object_00126D60* self, f32 step)
{
    if (func_00182FC8(self)) {
        func_00126C58(self);
        f32 value;
        if (step == 0.0f) {
            value = -self->timed->rate - 0.0001f;
            if (value > 0.0f) value = 0.0f;
        } else {
            value = -1.0f / step;
        }
        self->timed->result = value;
    }
}
