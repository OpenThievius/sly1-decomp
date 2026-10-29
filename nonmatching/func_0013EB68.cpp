// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: state-change conditions and helper calls match, but the compiler
// schedules the state store on the wrong side of the global float load.
#include "common.h"

extern f32 D_0026185C;
void func_00129DF8(void* self);
void func_0013EF50(void* self, s32 a, s32 b);
void func_0013F070(void* self, void* p);

struct Self_0013EB68 { u8 pad0[4]; void* child; u8 pad8[0x11C]; f32 value124; u8 pad128[4]; u32 state12C; };

void func_0013EB68(Self_0013EB68* self, u32 state)
{
    s32 oldState = self->state12C;
    if (state == oldState) {
        return;
    }
    s32 becameActive = oldState == 0 && state == 1;
    s32 becameInactive = oldState != -1 && state < 1;
    self->state12C = state;
    func_00129DF8(self->child);
    self->value124 = D_0026185C;
    if (becameActive) {
        func_0013EF50(self, 0, 0);
    }
    if (becameInactive) {
        func_0013F070(self, 0);
    }
}
