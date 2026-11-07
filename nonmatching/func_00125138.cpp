// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 772/764, checked 2026-11-07
// NEAR: structure found, 772 bytes against 764 and most of the vector code is displaced: the world frame from the parent, or from the attachment record's object when flag 4 or 8 is set (Rotate of the position plus the parent's, MulRotationRows of the parent's matrix and the object's); then the value-list query, the range record and the children's slot 23. Retail computes the three rows of the product into its two temporaries before it stores the matrix and loads the parent's rows as vf3, vf5 and vf6 through the pointer at +0x110; ours stores the first row of m110 before the third is computed and numbers the registers otherwise (a1 for the record, vf2 and vf4 for the rows).
// In the context of its file, src/main/placed_object.cpp.
// 0x1233C0 to 0x130F48: the state triggers (classes 0x22 and 0x2F), the placed object's set-up,
// update and loading (func_00123ED0 to func_001289C0), its range, sound and colour records, the
// code checksum, the animation players and their events, the id filter object, the sector stream
// reader and the curve segment helpers. One file between two edges; it could be several.
#include "common.h"
#include "mul_rotation.h"
#include "attachment.h"
#include "range_record.h"
#include "world.h"

void QueryValueListMask(void* list, f32 x, void* vec, void* out);
void SetRangeRecordPosition(RangeRecord* r, void* p);
void SetRangeRecordDirection(RangeRecord* r, void* p);
void StoreRangeRecordVector(void* self, void* src);

void func_00125138(PlacedObject* self)
{
    Rec2195_224* rec = self->f224;
    PlacedObject* par;
    if (rec != 0 && (rec->fB0 & 0xC) != 0) {
        par = (rec->fB0 & 4) ? (PlacedObject*)rec->p60 : (PlacedObject*)self->parent;
        if (par != 0) {
            Vu0::Q(self->v140) = Vu0::Add(Vu0::Rotate(par->m110, Vu0::Q(self->pos)), Vu0::Q(par->v140));
        } else {
            self->v140 = self->pos;
        }
        rec = self->f224;
        par = (rec->fB0 & 8) ? (PlacedObject*)rec->p60 : (PlacedObject*)self->parent;
        if (par != 0) {
            MulRotationRows(&self->m110, par->m110, self->rot);
        } else {
            self->m110 = self->rot;
        }
    } else {
        par = (PlacedObject*)self->parent;
        if (par != 0) {
            Vu0::Q(self->v140) = Vu0::Add(Vu0::Rotate(par->m110, Vu0::Q(self->pos)), Vu0::Q(par->v140));
            MulRotationRows(&self->m110, par->m110, self->rot);
        } else {
            self->v140 = self->pos;
            self->m110 = self->rot;
        }
    }
    if (self->bits24 == 2) {
        if (self->world->f1EC4 != 0) {
            QueryValueListMask(self->world->f1EC4, self->f2A8, &self->v140, &self->f88);
        } else {
            self->f88 = 0x0FFFFFFF;
        }
    }
    if (self->f284 != 0) {
        SetRangeRecordPosition(self->f284, &self->v140);
        if (self->f284->link != 0 && *(u8*)self->f284->link == 3) {
            Vec02 dir;
            Vu0::Q(dir) = Vu0::MulX(Vu0::Q(self->m110.r[2]), Vu0::Scalar(-1.0f));
            SetRangeRecordDirection(self->f284, &dir);
            StoreRangeRecordVector(self->f284, &self->m110.r[1]);
        }
    }
    for (BaseObject* n = (BaseObject*)self->children.head; n != 0; n = n->next) {
        if (n->desc->m13 != 0) {
            n->desc->m13(n);
        }
    }
    rec = self->f224;
    if (rec != 0 && (rec->fB0 & 0x8020) == 0x8020) {
        ((PlacedObject*)rec->f80)->f224->p64 = (BaseObject*)1;
        ((PlacedObject*)rec->p84)->f224->p64 = (BaseObject*)1;
    }
}
