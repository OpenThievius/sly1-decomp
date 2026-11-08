// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 798/900 (88.7%), checked 2026-11-08
// Tried night-close8: the offset read into a Vec local before the flag (no change), RotateUntied for the inertia (worse, 64).
#include "common.h"
#include "collider.h"
#include "globals.h"
#include "vu0.h"
// NEAR (2026-11-08, worker night-vumid2): the whole body of retail's loop over a body's parts
// (the zero test of the offset through ToFloatMoved/ToFloatY/ToFloatZ, RotateTransposed, the
// normalised cross product with its fallback, the Rotate of the inertia, the three dots, the
// weight mass / (mass + d / offsetSq) / roSq) and the loop kept as retail's (not reduced: the
// vectors are Vec values, which make the loop big enough for loop.c to leave it alone). What
// still differs is the allocation inside the arm: retail loads the inertia's rows first and the
// axis last (RotateUntied: the result takes row 0's register, the axis keeps vf2 for the dot),
// here the axis is loaded first and the tied Rotate copies it (a vmove); the registers of the
// flag `still` and of the vector are swapped (retail v1 / v0); the later vectors follow.
// Tried: the order of the Dot's operands, RotateUntied for both rotations, ToFloat and
// ToFloatMoved for the lengths.

struct ImpulseRow {
    Vec02 linear;           // 0x00
    Vec02 angular;          // 0x10
};

void ConstrainVectorByParentAnchor(Collider* self, Vec02* anchor, Vec02* in, Vec02* out, Vec02* dir);
void ComputeColliderPointVelocity(Collider* body, Vec02* point, ImpulseRow* row, Vec02* out);

void func_001BC978(void* unusedA, void* unusedB, s32 n, Collider** list, ImpulseRow* rows)
{
    Vec02 vel;
    Vec02 ang;
    Vec02 loc;
    Vec02 axis;
    Vec02 rn;
    Vec02 ro;
    Vec02 t;
    for (s32 i = 1; i < n; i++) {
        Collider* o = list[i];
        Collider* parent = (Collider*)o->parent;
        ImpulseRow* mine = &rows[o->index];
        ImpulseRow* par = &rows[parent->index];
        ComputeColliderPointVelocity(parent, &o->v140, par, &vel);
        if (o->flags538 & (1ULL << 54)) {
            Vu0::Q(mine->linear) = Vu0::Add(Vu0::Vec::Of(mine->linear), Vu0::Vec::Of(vel)).q;
            Vu0::Q(mine->angular) = Vu0::Add(Vu0::Vec::Of(mine->angular), Vu0::Vec::Of(par->angular)).q;
            continue;
        }
        ConstrainVectorByParentAnchor(o, &o->v440, &vel, 0, &vel);
        ConstrainVectorByParentAnchor(o, &o->v460, &par->angular, 0, &ang);
        if (o->mode470 != 3) {
            s32 still = 0;
            if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Vec::Of(o->offset))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatY(Vu0::Vec::Of(o->offset))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Vec::Of(o->offset))) < 0.0001f) {
                still = 1;
            }
            if (!still) {
                const u128& fb = Vu0::Q(D_00248D30);
                Vu0::Q(loc) = Vu0::RotateTransposed(o->m110, Vu0::Vec::Of(vel)).q;
                Vu0::Q(axis) = Vu0::Cross(Vu0::Vec::Of(o->offset), Vu0::Vec::Of(loc)).q;
                Vu0::Vec l = Vu0::Length(Vu0::Vec::Of(axis));
                if (Vu0::ToFloatMoved(l) < 0.0001f) {
                    Vu0::Set(axis, fb);
                } else {
                    Vu0::Set(axis, Vu0::DivX(Vu0::Vec::Of(axis), l).q);
                }
                if (0.0001f < Vu0::ToFloat(l)) {
                    Vu0::Q(rn) = Vu0::Rotate(o->inertia, Vu0::Vec::Of(axis)).q;
                    f32 d = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(rn), Vu0::Vec::Of(axis)));
                    f32 offsetSq = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(o->offset), Vu0::Vec::Of(o->offset)));
                    f32 mass = o->mass;
                    Vu0::Q(ro) = Vu0::Rotate(o->m110, Vu0::Vec::Of(o->offset)).q;
                    f32 roSq = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(ro), Vu0::Vec::Of(ro)));
                    Vu0::Q(t) = Vu0::MulX(Vu0::Cross(Vu0::Vec::Of(vel), Vu0::Vec::Of(ro)), Vu0::Vec::Scalar(mass / (mass + d / offsetSq) / roSq)).q;
                    ConstrainVectorByParentAnchor(o, &o->v460, &t, &t, 0);
                    Vu0::Q(ang) = Vu0::Add(Vu0::Vec::Of(ang), Vu0::Vec::Of(t)).q;
                }
            }
        }
        Vu0::Q(mine->linear) = Vu0::Add(Vu0::Vec::Of(mine->linear), Vu0::Vec::Of(vel)).q;
        Vu0::Q(mine->angular) = Vu0::Add(Vu0::Vec::Of(mine->angular), Vu0::Vec::Of(ang)).q;
    }
}
