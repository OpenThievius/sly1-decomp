// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 84/92 (91.3%), checked 2026-11-07
#include "common.h"
#include "placed_object.h"
#include "vu0.h"
// NEAR (2026-11-07, worker inline-vu0): all but two instructions: retail puts mtc1 v0,$f1 right
// after the first qmfc2 and the store of ab after it; here the scheduler puts the store first.
// A volatile ToFloat changes the whole order; ToFloat inside a union read goes through memory.

f32 ComputeSegmentParameter(const Vec02* a, const Vec02* b, const Vec02* p)
{
    Vec02 ap;
    Vec02 ab;
    Vu0::Q(ap) = Vu0::Sub(Vu0::Q(*p), Vu0::Q(*a));
    Vu0::Q(ab) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    return Vu0::ToFloat(Vu0::Dot(Vu0::Q(ap), Vu0::Q(ab))) / Vu0::ToFloat(Vu0::Dot(Vu0::Q(ab), Vu0::Q(ab)));
}
