// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 113/156 (72.4%), checked 2026-11-07
#include "common.h"
#include "attachment.h"
#include "placed_object.h"
#include "vu0.h"
s32 ResolveAimTarget(T2195_790* a0);
void ClearRootTries(PlacedObject* o);
void SortAttachments(PlacedObject* o);
// NEAR (2026-11-07, worker vu0-e6): retail keeps the owner and the new key in one register (s1)
// and schedules the product of the range with itself between the vsub and the vmul.xyz; this
// reuses the owner's variable for the key to get the s1 (a plain local key goes to v1) but the
// range product still comes after the dot product's setup (14 lines differ).

void func_00185498(T2195_790* self)
{
    s32 o = (s32)self->owner;
    PlacedObject* target = (PlacedObject*)ResolveAimTarget(self);
    if (target != 0) {
        u128 d = Vu0::Sub(Vu0::Q(((PlacedObject*)o)->v140), Vu0::Q(target->v140));
        if (self->f40 * self->f40 < Vu0::ToFloat(Vu0::Dot(d, d))) {
            o = self->f48;
        } else {
            ClearRootTries((PlacedObject*)o);
            o = self->f44;
        }
        if (o != self->key) {
            self->key = o;
            SortAttachments(self->owner);
        }
    }
}
