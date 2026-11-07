// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 385/440 (87.5%), checked 2026-11-07
// NEAR: right instructions, stores (including the two dead Mat02 copies, forwarded from the vector registers) and control flow; the allocator numbers differ: retail keeps the rows in vf5, vf7 and vf8 and the matrix in vf6, vf4 and vf3 (ours vf6, vf7, vf4 and vf5, vf3, vf2), takes the final sum in the second operand's register, and puts outVec in s3 and the address of tmpRot in s4 (ours the reverse). Ten variants of statement order and temporaries tried.
#include "common.h"
#include "globals.h"
#include "attachment.h"
#include "list_iter.h"
#include "placed_object.h"
#include "vu0.h"

extern const T2195_Vt D_00219560;
void MultiplyMatrices3x3(void* a, void* b, void* out);

struct ChildPoseSource : Attachment {
    u8 pad18[0x1C - 0x18];
    s32 count;
};

void CombineChildPoseRotations(ChildPoseSource* self, Mat02* outRot, Vec02* outVec, f32 t)
{
    ListFrame frame;
    Mat02 saved;
    Mat02 tmpRot;
    Mat02 m;
    Vec02 tmpVec;
    Mat02 copy1;
    Mat02 copy2;
    PlacedObject* owner = self->owner;
    *outRot = owner->m1A0;
    *outVec = D_00248D30;
    owner->desc02()->m29(owner, outRot, 0);
    saved = *outRot;
    Attachment* c = self;
    s32 n = ((ChildPoseSource*)c)->count;
    if (n > 0) {
        c = c->link.next;
        while (c != 0) {
            if ((u8)(c->mode1 + 1) >= 2) {
                if (c->vt != &D_00219560) {
                    c->vt->getRot(c, t, &tmpRot, &tmpVec);
                    MultiplyMatrices3x3(&saved, &tmpRot, &m);
                    u128 v0 = Vu0::Q(outRot->r[0]);
                    u128 v1 = Vu0::Q(outRot->r[1]);
                    u128 v2 = Vu0::Q(outRot->r[2]);
                    Vu0::Q(outRot->r[0]) = Vu0::Rotate(m, v0);
                    Vu0::Q(outRot->r[1]) = Vu0::Rotate(m, v1);
                    Vu0::Q(outRot->r[2]) = Vu0::Rotate(m, v2);
                    copy1 = *outRot;
                    copy2 = copy1;
                    Vu0::Q(*outVec) = Vu0::Add(Vu0::Rotate(m, Vu0::Q(*outVec)), Vu0::Q(tmpVec));
                }
                n--;
            }
            if (n <= 0) {
                break;
            }
            c = c->link.next;
        }
    }
}
