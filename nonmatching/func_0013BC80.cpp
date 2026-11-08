// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 380/384, checked 2026-11-07
// NEAR: (2026-11-08, night-size3) the size is retail's now: b's rows read as a struct (*(const
// Vu0::Vec*)&b.r[i]) make the stack stores alias them, so retail's reloads of rows 1 and 2 through
// v0 = s0+0x110 after each product come back. Still differs: the VU0 registers (retail gives a's
// rows vf3, vf6, vf5 and b's row 0 vf4, here vf2, vf6, vf4 and vf5) and the order of the dead
// copies (retail stores each product to 0x30 then 0x60 before the next load; here 0x60 at once and
// 0x30 after the stores to the object). MulRotation's x, y, z form, Vec stores into m and a Mat02*
// out were tried.
#include "common.h"
#include "child_group_object.h"
#include "attachment.h"
#include "vu0.h"
// NEAR (2026-11-08, wave 3 retry): RotateUntied in MulRows: the instructions are retail's; the
// VU0 registers and the dead stores differ. Retail loads the rotation's rows into vf3, vf6 and
// vf5 and the rows of the second matrix one at a time through v0 = s0+0x110 (addiu v0 after the
// first lqc2), storing each product's pair of dead copies (0x30, 0x60) before the next product;
// here all rows are loaded first, v0 is not formed and the pairs come after the stores to the
// object. MulRotation (x, y, z, r), x, y, z inside MulRows (the frame grows to 224) and
// explicit pairs give other shapes.
void BuildShortestArcRotation(void* from, void* to, void* out);
void BuildBasisFromXAndZHint(void* x, void* z, void* out);
void TransformRotationBetweenFrames(void* a, void* b, void* c, void* d);
extern const Vec02 g_unitZVector;

static inline Mat02 MulRows(const Mat02& a, const Mat02& b)
{
    Mat02 m;
    Vu0::Q(m.r[0]) = Vu0::RotateUntied(a, (*(const Vu0::Vec*)&b.r[0]).q);
    Vu0::Q(m.r[1]) = Vu0::RotateUntied(a, (*(const Vu0::Vec*)&b.r[1]).q);
    Vu0::Q(m.r[2]) = Vu0::RotateUntied(a, (*(const Vu0::Vec*)&b.r[2]).q);
    return m;
}

void func_0013BC80(ChildGroupObject* self, Collider* obj, Vec02* pos, Vec02* z)
{
    Mat02 a;

    if ((*(s32*)((u8*)self + 0x60C)) != 0) {
        return;
    }
    (*(Collider**)((u8*)self + 0x670)) = obj;
    (*(s32*)((u8*)self + 0x60C)) = 1;
    if (pos != 0) {
        (*(Vec02*)((u8*)self + 0x610)) = *pos;
    } else {
        (*(Vec02*)((u8*)self + 0x610)) = self->v140;
    }
    (*(Vec02*)((u8*)self + 0x650)) = self->v150;
    (*(Vec02*)((u8*)self + 0x660)) = self->v160;
    switch ((*(s32*)((u8*)self + 0x608))) {
    case 0: {
        BuildShortestArcRotation(&self->m110.r[2], z ? z : (Vec02*)&g_unitZVector, &a);
        (*(Mat02*)((u8*)self + 0x620)) = MulRows(a, self->m110);
        Rec2195_224* rec = self->f224;
        void* frame;
        if (rec != 0) {
            if ((rec->fB0 & 8) != 0) {
                frame = rec->p60;
            } else {
                frame = self->parent;
            }
        } else {
            frame = self->parent;
        }
        TransformRotationBetweenFrames(0, frame, (Mat02*)((u8*)self + 0x620), (Mat02*)((u8*)self + 0x620));
        break;
    }
    case 1:
        BuildBasisFromXAndZHint((Vec02*)((u8*)self + 0x650), (void*)&g_unitZVector, (Mat02*)((u8*)self + 0x620));
        break;
    case 2:
        (*(Mat02*)((u8*)self + 0x620)) = self->rot;
        break;
    }
}

