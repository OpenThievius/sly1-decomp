// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 506/516 (98.1%), checked 2026-11-07
// NEAR: everything but the allocation of the three loop registers of the lengths: retail keeps the qmfc2 temp in a1 (allocated after the loop pointers, which take v0, v1, a0), here ToBits gives v0 and shifts them. A ToFloat there gives retail registers but mtc1/swc1. Needs a ToBits form whose result is allocated like ToFloat's.
#include "common.h"
#include "switched_collider.h"
#include "deferred_request.h"
#include "vu0.h"
void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);

struct DrawScale {
    u8 pad00[0x40];
    f32 f40;
};

void DrawCollider(Collider* self, void* a, void* m);
void BuildPlacedObjectTransform(void* obj, void* c, void* out);
void RotateMatrixUpright(Mat02* self, Mat02* scratch, Mat02* out);
void BuildMatrixFromRotationAndTranslation(void* pos, void* rot, void* out);
void func_001268B8(void* world, void* a1, void* a2, void* a3, f32 a, f32 b);

void DrawPathFollower(PathFollower* self, void* a, DrawScale* b)
{
    DrawCollider(self, a, b);
    if (self->f690 != 0) {
        f32 len[3];
        DrawTransform m;
        Vec02 pos;
        Mat02 rot;
        for (s32 i = 0; i < 3; i++) {
            *(u32*)&len[i] = Vu0::ToBits(Vu0::Length(Vu0::Q(self->m110.r[i])));
        }
        BuildPlacedObjectTransform(self, b, &m);
        RotateMatrixUpright(&self->m110, 0, &rot);
        f32 sx = len[2] >? len[0];
        f32 sy = len[2] >? len[1];
        Vu0::Q(rot.r[0]) = Vu0::MulX(Vu0::Q(rot.r[0]), Vu0::Scalar(sx));
        Vu0::Q(rot.r[1]) = Vu0::MulX(Vu0::Q(rot.r[1]), Vu0::Scalar(sy));
        Vu0::Q(pos) = Vu0::Add(Vu0::Q(self->v140), Vu0::Rotate(rot, Vu0::Q(self->f690->pos)));
        BuildMatrixFromRotationAndTranslation(&pos, &rot, &m);
        self->f690->desc02()->m26(self->f690, a, &m);
    }
    if (self->fB28 != 0 || self->fB2C != 0) {
        Vec02 q[4];
        for (s32 i = 0; i < 4; i++) {
            TransformPointBetweenFrames(self, 0, &self->f6B0[i].v10, &q[i]);
        }
        if (self->fB28 != 0) {
            func_001268B8(self->fB28, a, &q[0], &q[1], 1.0f, b != 0 ? b->f40 : 1.0f);
        }
        if (self->fB2C != 0) {
            func_001268B8(self->fB2C, a, &q[2], &q[3], 1.0f, b != 0 ? b->f40 : 1.0f);
        }
    }
}
