// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 105/220 (47.7%), checked 2026-11-07
// NEAR: right instructions; retail's layout differs. It tests state 1, state 2, then branches to the default (the steer call) which sits after the shared tail, and computes the basis address (addiu s0, sp, 16) inside each of the two cases; ours (switch with the default first or if chains) puts the default before the tail and the basis address after the join. Tried a switch, if chains, a goto and a Mat02* assigned per case.
#include "common.h"
#include "collider.h"
#include "object_gatherer.h"
#include "vu0.h"

void TransformPointBetweenFrames(void* a0, s32 a1, void* a2, void* a3);
void StepCollider(Collider* self, f32 t);
void SteerColliderTowardRotation(Collider* self, void* a, s32 b, void* table, s32 c, f32 t);
void TurnColliderTowardRotation(Collider* self, f32 scale, void* basis, void* data);
void BuildBasisFromX(void* self, void* value);
extern u8 D_00248D30[];
extern f32 D_0026ABB0[4];

void StepObjectGatherer(ObjectGatherer* self, f32 dt)
{
    Vec02 delta;
    Mat02 basis;
    Vec02 target;
    StepCollider(self, dt);
    switch (self->state) {
    case 1:
        Vu0::Q(delta) = Vu0::Sub(Vu0::Q(self->v640), Vu0::Q(self->v140));
        break;
    case 2:
        TransformPointBetweenFrames(*(void**)((u8*)self->f660 + 0x18), 0, (u8*)self->f660 + 0x40, &target);
        Vu0::Q(delta) = Vu0::Sub(Vu0::Q(target), Vu0::Q(self->v140));
        break;
    default:
        SteerColliderTowardRotation(self, 0, 0, (void*)&D_00248D30, (s32)self->p214, dt);
        return;
    }
    delta.z = 0.0f;
    BuildBasisFromX(&delta, &basis);
    TurnColliderTowardRotation(self, dt, &basis, D_0026ABB0);
}
