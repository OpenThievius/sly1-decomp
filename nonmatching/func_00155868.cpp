// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 0/580, checked 2026-11-07
// NEAR: the wrap loop over the owned records' points is retail's instruction for instruction; in the head retail keeps the first Splat's GPR value (v0) live into the no-target arm, storing hi with sq from it and copying it to VU0 again (qmtc2 vf3) for the MulX, where here hi and the MulX take the VU0 copy made for size's store; the GPRs of the head differ with it. Tried the splat as a u128, a struct copy, a second Splat, the arms swapped, Set.
// In the context of its file, src/main/file_1549C8.cpp.
#include "common.h"
#include "effect_spawner.h"
#include "world_listed_object.h"
#include "owned_record.h"
#include "list_iter.h"
#include "vu0.h"

f32 WrapModulo(f32 x, f32 m);

void func_00155868(EffectSpawner* self)
{
    if (!(1e-4f < self->margin)) {
        return;
    }
    Vec02 size;
    Vec02 lo;
    Vec02 hi;
    Vu0::Q(size) = Vu0::Splat(self->margin);
    if (self->rec->target != 0) {
        Vu0::Q(lo) = Vu0::Sub(Vu0::Q(((PlacedObject*)self->rec->target)->v140), Vu0::Q(size));
        Vu0::Q(hi) = Vu0::Add(Vu0::Q(((PlacedObject*)self->rec->target)->v140), Vu0::Q(size));
    } else {
        hi = size;
        Vu0::Q(lo) = Vu0::MulX(Vu0::Q(size), Vu0::Scalar(-1.0f));
    }
    Vu0::Q(size) = Vu0::Splat(self->margin + self->margin);
    if (self->rec->f120 != 0) {
        return;
    }
    WorldListedObject* w = (WorldListedObject*)self->held348;
    if (w == 0) {
        return;
    }
    for (OwnedRecord* r = (OwnedRecord*)w->members.head; r != 0; r = r->next) {
        Vec02* p = r->points[r->bank];
        for (s32 i = 0; i < r->count; i++, p++) {
            Vec02 delta;
            ListFrame frame;
            if (p->x < lo.x || hi.x < p->x) {
                delta.x = lo.x + WrapModulo(p->x - lo.x, size.x) - p->x;
                p->x += delta.x;
            }
            if (p->y < lo.y || hi.y < p->y) {
                delta.y = lo.y + WrapModulo(p->y - lo.y, size.y) - p->y;
                p->y += delta.y;
            }
            if (p->z < lo.z || hi.z < p->z) {
                delta.z = lo.z + WrapModulo(p->z - lo.z, size.z) - p->z;
                p->z += delta.z;
            }
        }
    }
}
