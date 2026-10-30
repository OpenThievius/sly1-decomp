// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: retail emits max.s for the float field; the source comparison
// emits a branch instead.
#include "common.h"

struct __attribute__((aligned(16))) Quad_D6608 { s32 a, b; f32 height; s32 d; };
struct Obj_D6608 {
    void** vtable;
    u8 pad4[0x26B8];
    s32 callbackArg;
    void (*callback)(s32, void*);
    u8 pad26C4[0x6C];
    s32 state2730;
};
extern f32 D_00275160;
void func_00192C58(void* self);
void func_00175170(void* self, s32 mode, s32 value);

void func_001D6608(Obj_D6608* self)
{
    if (self->state2730) {
        func_00192C58(self);
        self->state2730 = 0;
    }
    if (self->callback) {
        void (*callback)(s32, void*) = self->callback;
        self->callback = 0;
        callback(self->callbackArg, self);
        *(s32*)((u8*)self + 0x2498) = 0;
    } else {
        Quad_D6608 quad = *(Quad_D6608*)((u8*)self + 0x150);
        if (quad.height < D_00275160) quad.height = D_00275160;
        ((void (*)(void*, Quad_D6608*))self->vtable[36])(self, &quad);
        func_00175170(self, 2, 6);
        *(s32*)((u8*)self + 0x2498) = 0;
    }
    *(s32*)((u8*)self + 0x226C) = 0;
}
