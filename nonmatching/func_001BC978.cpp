// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 892/900 (99.1%), checked 2026-11-10
#include "common.h"
#include "collider.h"
#include "globals.h"
#include "vu0.h"
// NEAR (2026-11-10, worker w12-1BC978): everything but one GPR. Fixed since the last notes:
// the zero test as one boolean (`s32 still = a && b && c;`; the `still = 0; if (..) still = 1;`
// form, with the Vec::Of copies in the condition, expands the && into a temporary that jump.c
// makes a conditional move, then copies to `still`, and that copy's v0 preference pushed the
// offset's GPR copy to v1); the inertia's rotation untied (RotateUntied: rows first, the result
// in row 0's register, as retail); the impulse stored and then scaled in place (`t = Cross;
// t = MulX(t, ..)`: retail stores t twice). Still differs: the compiler's qmfc2 of offsetSq's dot
// takes v0 (retail v1), and sched2 then puts the t store before roSq's mtc1. Local-alloc gives
// the dot's TI_REGS pseudo the first free GPR: d's pseudo dies (its mtc1, sched1 insn 827) before
// offsetSq's is born (876), because the offset's reload waits for rn's frame store. Ruled out:
// every combination of ToFloat/ToFloatMoved/ToFloatNow/ToFloatViaBits for d, offsetSq, roSq
// (64 compiles; ToFloat for offsetSq gives v1 but moves its mtc1), every order of the four
// statements, permute.py --auto, the offset as a Vec local, u128 operands (the loop shrinks
// and loop.c reduces it), RotateMembers.
// Why (w15, 2026-11-10; docs/toolchain/reloads-and-stores.md): both dots are TI_REGS pseudos.
// d's (r368) takes rn's vf1 by local-alloc's suggestion (rn dies in the asm), so its qmfc2 is
// the mtc1's input reload (v0); offsetSq's (r393) has no suggestion (the offset lives on to
// ro's Rotate) and takes the first GPR, v0. Retail's v1 fits a second reload in reload's
// round robin, i.e. offsetSq's dot in a VU0 register. Also not it: o->mass read in the
// expression, ToFloatViaBits for offsetSq.
// w19 (2026-11-10, tools/globalalloc.py, sched1.py, -dR dumps): retail's v1 is reload's rotation
// (v0 for d's reload, v1 next, a0 skipped while it holds the call's argument), so offsetSq's dot
// is a VU0 pseudo whose qmfc2 is the mtc1 asm's input reload. The second difference is roSq's
// conversion: with the compiler's qmfc2 (unit vu0) sched2 puts the mtc1 before the t store, as
// retail; with ToFloat's asm qmfc2 never. But ToFloatMoved makes roSq's dot TI_REGS in v0 and
// its output reload takes vf1 (retail vf5, a local VU0 placement), so retail has both products
// VU_REGS with "r" readers: func_00186230's wall twice. Probes, not landed: a dummy "j" operand
// (v1, but the third reference reorders the VU0 registers); an mtc1 helper taking u64 with
// `(u64)` of the dot (inheritance from the output reload register: every offsetSq line retail's,
// four lines left to two; for roSq vf1 again), no evidence the original had it.

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
            s32 still = __builtin_fabsf(Vu0::ToFloatMoved(Vu0::Vec::Of(o->offset))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatY(Vu0::Vec::Of(o->offset))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Vec::Of(o->offset))) < 0.0001f;
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
                    Vu0::Q(rn) = Vu0::RotateUntied(o->inertia, Vu0::Vec::Of(axis)).q;
                    f32 d = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(rn), Vu0::Vec::Of(axis)));
                    f32 offsetSq = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(o->offset), Vu0::Vec::Of(o->offset)));
                    f32 mass = o->mass;
                    Vu0::Q(ro) = Vu0::Rotate(o->m110, Vu0::Vec::Of(o->offset)).q;
                    f32 roSq = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(ro), Vu0::Vec::Of(ro)));
                    Vu0::Q(t) = Vu0::Cross(Vu0::Vec::Of(vel), Vu0::Vec::Of(ro)).q;
                    Vu0::Q(t) = Vu0::MulX(Vu0::Vec::Of(t), Vu0::Vec::Scalar(mass / (mass + d / offsetSq) / roSq)).q;
                    ConstrainVectorByParentAnchor(o, &o->v460, &t, &t, 0);
                    Vu0::Q(ang) = Vu0::Add(Vu0::Vec::Of(ang), Vu0::Vec::Of(t)).q;
                }
            }
        }
        Vu0::Q(mine->linear) = Vu0::Add(Vu0::Vec::Of(mine->linear), Vu0::Vec::Of(vel)).q;
        Vu0::Q(mine->angular) = Vu0::Add(Vu0::Vec::Of(mine->angular), Vu0::Vec::Of(ang)).q;
    }
}
