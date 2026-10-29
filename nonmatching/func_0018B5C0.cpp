// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The constant values are right, but register selection and store
//        offsets/order still differ.
#include "common.h"

extern s32 func_001E2268(s32, s32);
struct State_0018B5C0 { volatile s32 value; volatile s32 status; s32 pad[2]; volatile s32 kind; };
void func_0018B5C0(State_0018B5C0* self)
{
    s32 value = func_001E2268(1, 1);
    self->status = -1;
    self->kind = 34;
    self->value = value;
}
