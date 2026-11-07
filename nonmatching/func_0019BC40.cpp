// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 392/456 (86.0%), checked 2026-11-07
// NEAR: right instructions, frame and control flow; in the two ring-advance blocks retail loads the radius (lwc1 5F0/5F4) first and the two vector loads after it, with the mul.s after the second lqc2; ours loads the vectors first and the radius after, and puts the mul.s after the qmfc2. Tried the statement order, a temp, a reference and the permuter.
#include "common.h"
#include "object_gatherer.h"
#include "list_iter.h"
#include "placed_object.h"
#include "vu0.h"

void BuildPlacedObjectTransform(void* self, void* a, void* out);

void func_0019BC40(ObjectGatherer* self, void* a1, void* a2)
{
    Vec02 tmp[4];
    ListFrame frame;
    PlacedObject* obj;
    if (self->state == 4) {
        return;
    }
    if (self->flags & 0x100000000ULL) {
        return;
    }
    BuildPlacedObjectTransform(self, a2, tmp);
    switch (self->state) {
    case 0:
        obj = (PlacedObject*)self->base5EC;
        obj->desc02()->m24(obj, a1, tmp);
        break;
    case 1: {
        f32 r = self->near5F0 * self->near5F0;
        u128 d = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(self->v650));
        s32 far = r < Vu0::ToFloat(Vu0::Dot(d, d));
        if (far) {
            self->ring = (self->ring + 1) % self->lowCount;
            Vu0::Q(self->v650) = Vu0::Q(self->v140);
        }
        obj = (PlacedObject*)self->lowObjects[self->ring];
        obj->desc02()->m24(obj, a1, tmp);
        break;
    }
    case 2: {
        f32 r = self->near5F4 * self->near5F4;
        u128 d = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(self->v650));
        s32 far = r < Vu0::ToFloat(Vu0::Dot(d, d));
        if (far) {
            self->ring = (self->ring + 1) % self->highCount;
            Vu0::Q(self->v650) = Vu0::Q(self->v140);
        }
        obj = (PlacedObject*)self->highObjects[self->ring];
        obj->desc02()->m24(obj, a1, tmp);
        break;
    }
    default:
        return;
    }
}
