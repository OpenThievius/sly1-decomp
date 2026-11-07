// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 380/384, checked 2026-11-07
// NEAR: right instructions, stack stores and calls; differs in the VU0 registers (retail loads the matrix rows into vf3/vf6/vf5 and the vector rows via one base pointer (addiu v0,s0,0x110 then 0x10(v0)); ours reads every row from s0 and numbers the registers differently) and in the dead-store pairs, which retail writes row by row right after each product.
#include "common.h"
#include "child_group_object.h"
#include "attachment.h"
#include "vu0.h"

void BuildShortestArcRotation(void* from, void* to, void* out);
void BuildBasisFromXAndZHint(void* x, void* z, void* out);
void TransformRotationBetweenFrames(void* a, void* b, void* c, void* d);
extern const Vec02 g_unitZVector;

static inline Mat02 MulRows(const Mat02& a, const Mat02& b)
{
    Mat02 m;
    Vu0::Q(m.r[0]) = Vu0::Rotate(a, Vu0::Q(b.r[0]));
    Vu0::Q(m.r[1]) = Vu0::Rotate(a, Vu0::Q(b.r[1]));
    Vu0::Q(m.r[2]) = Vu0::Rotate(a, Vu0::Q(b.r[2]));
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

