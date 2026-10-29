// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: register allocation and conditional value selection differ around the state store.
#include "common.h"
struct Vtbl_12A528 { u8 pad[0xBC]; void (*notify)(void*); };
struct State_12A528 { u8 pad[0x11]; s8 value; };
struct Obj_12A528 { Vtbl_12A528* vtbl; u8 pad[0x200 - 4]; State_12A528* state; };
extern void func_00129730(void*);
void func_0012A528(Obj_12A528* self, s32 value)
{
    s32 adjusted = value;
    func_00129730(self);
    if ((adjusted ^ 3) == 0) adjusted = 9;
    self->state->value = adjusted;
    self->vtbl->notify(self);
}
