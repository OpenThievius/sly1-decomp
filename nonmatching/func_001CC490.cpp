// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 932/904, checked 2026-11-08
#include "common.h"
#include "vu0.h"
#include "globals.h"
#include "switched_collider.h"
// NEAR (2026-11-08, worker night-vumid2): the instruction stream is retail's, loop for loop (the
// madd of the row address, the dividing, the dots through ToBits, the weighted sums), with the
// frame equal; what differs is the allocator's choices: the nine spilled loop invariants (the
// addresses of the locals, stored in the prologue) take their slots in another order (retail:
// cross, m, scaled, rows, factor, j << 5, vel, rhs, sol; here sol, rows, m, j << 5, factor, vel,
// cross, scaled, rhs) and the first loop's induction variables take s2..s5 in another order
// (retail: objs pointer, pts pointer, F pointer, i; here i first). Vec values (not u128) are
// needed so the inner loop is as big to loop.c as retail's (no reduction of the row address).
// Tried: the order of the cross and scaled statements, the rhs copy after the loops, the
// declaration order, explicit walking pointers (worse).

struct LinkRow {
    Vec02 a;
    Vec02 b;
};

void ConstrainVectorByParentAnchor(void* self, void* anchor, Vec02* in, Vec02* out, s32 mode);
void ApplyColliderInverseInertia(void* self, Vec02* in, Vec02* out);
void ComputeColliderPointVelocity(void* self, void* data, LinkRow* row, Vec02* out);
void FactorSymmetricMatrix(s32 n, f32* a, f32* l);
void SolveFactoredSystem(s32 n, f32* a, f32* b, f32* c);
void TransformDirectionBetweenFrames(s32 zero, void* frame, Vec02* in, Vec02* out);

void func_001CC490(PlacedObject* a, PlacedObject* b, Vec02* point, f32* target, LinkRow* out)
{
    PlacedObject* objs[2];
    Vec02 pts[2];
    Vec02 axis;
    Vec02 cross;
    Vec02 scaled;
    Vec02 torque;
    LinkRow rows[2][3];
    Vec02 vel[2];
    Vec02 diff[3];
    f32 m[3][3];
    f32 factor[3][3];
    f32 rhs[3];
    f32 sol[3];
    s32 i;
    s32 j;

    objs[0] = a;
    objs[1] = b;
    pts[0] = a->v140;
    pts[1] = *point;
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 2; i++) {
            PlacedObject* o = objs[i];
            axis = g_identityMatrix.r[j];
            if (i == 1) {
                Vu0::Q(axis) = Vu0::MulX(Vu0::Vec::Of(axis), Vu0::Vec::Scalar(-1.0f)).q;
            }
            Vu0::Q(cross) = Vu0::Cross(Vu0::Sub(Vu0::Vec::Of(pts[i]), Vu0::Vec::Of(o->v140)), Vu0::Vec::Of(axis)).q;
            Vu0::Q(scaled) = Vu0::DivX(Vu0::Vec::Of(axis), Vu0::Vec::ScalarAt(*(f32*)((u8*)o + 0x368))).q;
            ConstrainVectorByParentAnchor(o, (u8*)o + 0x440, &scaled, &rows[i][j].a, 0);
            ApplyColliderInverseInertia(o, &cross, &torque);
            ConstrainVectorByParentAnchor(o, (u8*)o + 0x460, &torque, &rows[i][j].b, 0);
            ComputeColliderPointVelocity(o, point, &rows[i][j], &vel[i]);
        }
        Vu0::Q(diff[j]) = Vu0::Sub(Vu0::Vec::Of(vel[0]), Vu0::Vec::Of(vel[1])).q;
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 3; i++) {
            *(u32*)&m[j][i] = Vu0::ToBits(Vu0::Dot(Vu0::Q(g_identityMatrix.r[i]), Vu0::Q(diff[j])));
        }
        rhs[j] = target[j];
    }
    FactorSymmetricMatrix(3, &m[0][0], &factor[0][0]);
    SolveFactoredSystem(3, &factor[0][0], rhs, sol);
    for (i = 0; i < 2; i++) {
        Vu0::Q(out[i].a) = Vu0::MulXSum3(Vu0::Vec::Of(rows[i][0].a), Vu0::Vec::ScalarAt(sol[0]), Vu0::Vec::Of(rows[i][1].a), Vu0::Vec::ScalarAt(sol[1]), Vu0::Vec::Of(rows[i][2].a), Vu0::Vec::ScalarAt(sol[2])).q;
        Vu0::Q(out[i].b) = Vu0::MulXSum3(Vu0::Vec::Of(rows[i][0].b), Vu0::Vec::ScalarAt(sol[0]), Vu0::Vec::Of(rows[i][1].b), Vu0::Vec::ScalarAt(sol[1]), Vu0::Vec::Of(rows[i][2].b), Vu0::Vec::ScalarAt(sol[2])).q;
        TransformDirectionBetweenFrames(0, *(void**)((u8*)objs[i] + 0x18), &out[i].a, &out[i].a);
        TransformDirectionBetweenFrames(0, *(void**)((u8*)objs[i] + 0x18), &out[i].b, &out[i].b);
    }
}

