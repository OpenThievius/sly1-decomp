// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: The body has the right size, but stores to the initialization fields
// are scheduled in a different order.
#include "common.h"
struct State_0012FDA0 { s32 w[11]; };
void func_0012FE70(void* self);
s32 func_0012FDA0(void* ptr, s32 a, s32 b)
{
    State_0012FDA0* self = (State_0012FDA0*)ptr;
    self->w[2] = a;
    self->w[0] = 1;
    self->w[9] = b;
    self->w[10] = b;
    self->w[7] = self->w[5];
    self->w[6] = 0;
    self->w[8] = 0;
    func_0012FE70(self);
    return 1;
}
