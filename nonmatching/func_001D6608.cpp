// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 154/160 (96.2%), checked 2026-11-07
// NEAR: 2 lines differ: retail fills the slot-36 jalr's delay with `move a1, sp` and sets a0 before
//       the quad copy; ours the other way round. max.s via `>?` is right. ~20 compiles.
#include "common.h"
#include "switched_collider.h"

extern float D_00275160;

void func_00192C58(Player* self);
void func_00175170(Player* self, s32 a, s32 b);

void func_001D6608(Player* self)
{
    if (self->f2730 != 0) {
        func_00192C58(self);
        self->f2730 = 0;
    }
    if (self->f26B4.fn != 0) {
        s32 fn = self->f26B4.fn;
        self->f26B4.fn = 0;
        ((void (*)(s32, Player*))fn)(self->f26B4.data, self);
        self->f2498 = 0;
    } else {
        Vec02 v = self->v150;
        v.z = D_00275160 >? v.z;
        const Desc02* d = self->desc02();
        d->m20(self, &v);
        func_00175170(self, 2, 6);
        self->f2498 = 0;
    }
    self->f226C = 0.0f;
}
