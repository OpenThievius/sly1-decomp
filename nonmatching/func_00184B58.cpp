// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 312/376 (83.0%), checked 2026-11-07
// BYTES 0/376, checked 2026-11-07
// NEAR: the VU0 registers of the apex and the rim swap (retail loads the apex into vf2 and moves the rim to vf1; here the reverse), and retail stores the rim's GPR copy to its local and to FromFloats' slot after the square root where here they come first. Every instruction is retail's otherwise: the two FromFloats vectors, the axis scaled by the Scalar half range, the local reused for the difference and the offset. Tried the rim as a u128 stored after the difference, the apex read into a value first, ToFloat.
// In the context of its file, src/main/base_object.cpp.
#include "common.h"
#include "cone_volume.h"
#include "world.h"
#include "vu0.h"

f32 Tangent(f32 a);
s32 QueryValueListMask(void* self, f32 radius, void* center, s32* out);

void UpdateConeVolumeBounds(ConeVolume* self)
{
    if (self->value == 0) {
        return;
    }
    switch (self->mode) {
    case 0:
        self->mask = 0x0FFFFFFF;
        break;
    case 1:
        QueryValueListMask(self->world->f1EC4, self->rangeMax, &self->v140, &self->mask);
        break;
    case 2:
    case 3: {
        Vec02 apex;
        Vec02 rim;
        Vec02 v;
        Vec02 center;
        Vu0::Q(apex) = Vu0::FromFloats(0.0f, 0.0f, self->rangeMax * 0.5f);
        f32 t = Tangent(self->outerAngle * 0.00872664712f);
        Vu0::Q(rim) = Vu0::FromFloats(t * self->rangeMax, 0.0f, self->rangeMax);
        Vu0::Q(v) = Vu0::Sub(Vu0::Q(rim), Vu0::Q(apex));
        f32 r = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(v)));
        Vu0::Q(v) = Vu0::MulX(Vu0::Q(self->axis), Vu0::Scalar(self->rangeMax * 0.5f));
        Vu0::Q(center) = Vu0::Add(Vu0::Q(self->v140), Vu0::Q(v));
        QueryValueListMask(self->world->f1EC4, r, &center, &self->mask);
        break;
    }
    }
}
