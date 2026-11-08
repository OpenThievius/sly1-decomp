// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 0/628, checked 2026-11-07
// NEAR: the lane tests (ToFloatY, ToFloatZ), the move, the child walk and the frame are retail's; in the rotation retail reads the placement's rows 1 and 2 through a pointer (addiu v0, s0, 0xD0) after storing each product row to the stack, where here all three rows are loaded first and the product rows stored after, so the VU0 registers and the order of the stores differ. Tried MulRotation, MulRotationRows and MulRotationRowsX, the matrix through a pointer local, the result stored through it.
// In the context of its file, src/main/file_1B7968.cpp.
#include "common.h"
#include "collider.h"
#include "list_iter.h"
#include "attachment.h"
#include "vu0.h"
#include "mul_rotation.h"

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

void SettlePoseSourceModes(Attachment* a);
void BuildRotationFromVector(Vec02* v, Mat02* m);

void ApplyColliderPendingMove(Collider* self, s32 quiet)
{
    Mat02 rot;
    Mat02 m;
    s32 moved = quiet;
    s32 still = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->v490))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->v490))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->v490))) < 0.0001f) {
        still = 1;
    }
    if (!still) {
        Vu0::Q(self->pos) = Vu0::Add(Vu0::Q(self->pos), Vu0::Q(self->v490));
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
        BuildRotationFromVector(&self->spin4A0, &rot);
        Mat02* frame = &self->rot;
        MulRotationRows(&m, rot, *frame);
        *frame = m;
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
            c->desc02()->m2F(c, moved);
        }
    }
    if (moved && !quiet && self->desc->m12 != 0) {
        self->desc->m12(self);
    }
    ListWalk::End(&it);
}
