// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 720/724, checked 2026-11-08
// NEAR: same size as retail; 159 of 181 instructions equal by position (regdiff). The move of the pending move and spin of a collider with the rotation turned by half the frame time's spin (sibling of ApplyColliderPendingImpulse). Differs: (1) the rows of the matrix the product reads (self->rot, b) are loaded together before the first product where retail loads row 0 first and rows 1 and 2 after the first stores to the stack, through the register that holds &self->rot (v0 + 0x10, 0x20); here they are s0-based and hoisted, so the registers of the product differ (a's rows vf3/vf6/vf5 and b's vf4/vf2/vf1 in retail); (2) the first still flag takes a0 and the Y/Z temporaries v1 where retail has v1 and a0 (daddu v1,zero,zero is scheduled before the saves). The product is mul_rotation.h's MulRotationRows with the last two rows' out stores written row by row (out->r[i] = r.r[i], out->r[2] = z, then r.r[2] = z) and the matrix through a Mat02* local, which gives retail's three direct sqc2 to the matrix; the shared forms give an lq/sq copy of the last row.
// In the context of its file, src/main/file_1B7968.cpp.
#include "common.h"
#include "list_iter.h"
#include "collider.h"
#include "globals.h"
#include "vu0.h"
#include "mul_rotation.h"

void SettlePoseSourceModes(Attachment* a);

struct ListWalk {
    static void Begin(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
    static u8* Next(ListFrame* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
    static void End(ListFrame* it) { g_activeListFrames = it->prev; }
};

void BuildRotationFromVector(Vec02* v, Mat02* mat);

static inline void MulRotationRowsTry(Mat02* out, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    out->r[0] = r.r[0];
    out->r[1] = r.r[1];
    out->r[2] = z;
    r.r[2] = z;
}
extern f32 g_frameDt[];

void func_001B8148(Collider* self, s32 flag)
{
    s32 still = 0;
    s32 moved = flag;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->v490))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->v490))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->v490))) < 0.0001f) {
        still = 1;
    }
    if (!still) {
        Vu0::Q(self->v150) = Vu0::Add(Vu0::Q(self->v150), Vu0::Q(self->v490));
        Vu0::Q(self->pos) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(self->v490), Vu0::Scalar(g_frameDt[0] * 0.5f));
        if (self->f1EC != 0) {
            SettlePoseSourceModes(self->f1EC);
        }
        Vu0::Q(self->v490) = Vu0::Zero();
        moved = 1;
    }
    still = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->spin4A0))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->spin4A0))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->spin4A0))) < 0.0001f) {
        still = 1;
    }
    if (!still) {
        Vec02 delta;
        Mat02 turn;
        Vu0::Q(self->v160) = Vu0::Add(Vu0::Q(self->v160), Vu0::Q(self->spin4A0));
        Vu0::Q(delta) = Vu0::MulX(Vu0::Q(self->spin4A0), Vu0::Scalar(g_frameDt[0] * 0.5f));
        BuildRotationFromVector(&delta, &turn);
        Mat02* rot = &self->rot;
        MulRotationRowsTry(rot, turn, *rot);
        if (self->f1F0 != 0) {
            SettlePoseSourceModes(self->f1F0);
        }
        Vu0::Q(self->spin4A0) = Vu0::Zero();
        moved = 1;
    }
    ListFrame it;
    ListWalk::Begin(&it, &self->children);
    for (PlacedObject* c = (PlacedObject*)ListWalk::Next(&it); c != 0; c = (PlacedObject*)ListWalk::Next(&it)) {
        if (c->desc->flags & 2) {
            ((Collider*)c)->desc03()->m30((Collider*)c, moved);
        }
    }
    ListWalk::End(&it);
    if (moved != 0) {
        if (flag == 0) {
            if (self->desc->m12 != 0) {
                self->desc->m12(self);
            }
        }
    }
}
