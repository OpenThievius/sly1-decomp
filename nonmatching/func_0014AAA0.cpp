// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 254/304 (83.6%), checked 2026-11-07
// NEAR: same size, same control flow and calls; only the third Rotate's register differs. Retail's rotated rows take vf3, vf4 and vf1 (the third result in the matrix's row 0 register, not in its vector's vf6), and it stores the three rows to basis first, then to the two copies in an interleaved order (0x90, 0x60, 0xA0, 0x70, ...); ours ties each result to its vector and stores the copies first.
#include "common.h"
#include "camera.h"
#include "camera_controller.h"
#include "placed_object.h"
#include "vu0.h"

void ConvertPositionToWorld(void* n, void* out);
void TransformPointBetweenFrames(void* a0, s32 a1, void* a2, void* a3);
void BuildBasisFromX(void* self, void* value);
void BuildBasisFromXAndZHint(void* a, void* b, void* out);
void SetCameraPlacement(Camera* cam, void* pos, void* basis);

void UpdateValueCameraController(ValueCameraController* ctl)
{
    Vec02 pos;
    Mat02 basis;
    Vec02 v40;
    Vec02 v50;
    Mat02 t1;
    Mat02 t2;
    u8* o = (u8*)ctl->ptr;
    Camera* cam = ctl->owner;
    TransformPointBetweenFrames(o, 0, o + 0x2E0, &pos);
    if (*(u8**)(o + 0x2D8) != 0) {
        Vu0::Q(v40) = Vu0::Sub(Vu0::Q(((PlacedObject*)*(u8**)(o + 0x2D8))->v140), Vu0::Q(pos));
        BuildBasisFromX(&v40, &basis);
    } else if (*(u8**)(o + 0x2D4) != 0) {
        ConvertPositionToWorld(*(u8**)(o + 0x2D4), &v40);
        Vu0::Q(v50) = Vu0::Sub(Vu0::Q(v40), Vu0::Q(pos));
        BuildBasisFromX(&v50, &basis);
    } else {
        BuildBasisFromXAndZHint(o + 0x2F0, o + 0x300, &basis);
        const Mat02& m = *(Mat02*)(o + 0x110);
        u128 r0 = Vu0::Rotate(m, Vu0::Q(basis.r[0]));
        u128 r1 = Vu0::Rotate(m, Vu0::Q(basis.r[1]));
        u128 r2 = Vu0::Rotate(m, Vu0::Q(basis.r[2]));
        Vu0::Q(basis.r[0]) = r0;
        Vu0::Q(basis.r[1]) = r1;
        Vu0::Q(basis.r[2]) = r2;
        t2 = basis;
        t1 = t2;
    }
    SetCameraPlacement(cam, o + 0x140, &basis);
}
