// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 292/288, checked 2026-11-07
// NEAR: differs only in the register of the vertex pointer in the last-vertex branch (retail keeps it in a1 and passes it on to the transform; ours computes it in v1 and moves it to a1), which moves the lui/mtc1/lqc2 order and puts the FromFloat word in a0 instead of v0, and is 4 bytes longer.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "vu0.h"
#include "globals.h"
#include "object_link.h"
#include "attachment.h"
#include "pad_record.h"

void CopyColliderMeshesInFrame(void* self);
void BuildMatrixFromRotationAndTranslation(const Vec02* pos, const Mat02* rot, Mat4* out);
void TransformByMatrixWithW(Mat4* m, Vec02* in, void* out, f32 w);

void func_001C4FF8(TurningCollider* self)
{
    Mat4 world;
    Vec02 k;
    s32 lowest = -1;
    s32 i = 0;
    CopyColliderMeshesInFrame(self);
    BuildMatrixFromRotationAndTranslation(&self->v140, &self->m110, &world);
    f32 lowZ = 3.40282347e+38f;
    for (; i < self->mesh.vertCount; i++) {
        Vec02* v = (Vec02*)self->mesh.verts + i;
        if (i == self->mesh.vertCount - 1) {
            Vu0::Q(k) = Vu0::FromFloat(-self->f6CC);
            Vu0::Q(*v) = Vu0::MulAddX(Vu0::Q(((Vec02*)self->mesh.verts)[lowest]), Vu0::Q(g_unitZVector), Vu0::Q(k));
            self->f6D0 = i;
            Vec02* dst = (Vec02*)self->meshCopy.verts + i;
            self->f6D4 = (s32)dst;
            TransformByMatrixWithW(&world, v, dst, 1.0f);
        } else if (v->z < lowZ) {
            lowZ = v->z;
            lowest = i;
            self->f6D8 = ((Vec02*)self->meshCopy.verts + i);
        }
    }
}
