// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 744/764 (97.4%), checked 2026-11-08
// NEAR (2026-11-08, night-size2): the same size as retail (764). The product is MulRotationIntoWorld (b's rows read by index, mul_rotation.h's Indexed form, written through the object to m110), the type kind read into a local from bits24 as an int field (include/placed_object.h: retail's ld, dsll 8, dsra32, andi 3), the last record read into a variable of its own. Still differs: the frame (retail 160, an unused 16 bytes above the products' x, y, z and r, not a ListFrame: one declared in a block is not given a slot; declared at the function's top it is, but first, at 0, which moves every slot up 16 (night-sizex2)) and the parent pointer's register in the first block (retail v1, the record's; here a0; an if/else, one void* for both, and the second test read from self->f224 change nothing).
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

// The product a b into the object's world matrix (m110), written through the object.
static inline void MulRotationIntoWorld(PlacedObject* o, const Mat02& a, const Mat02& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    const u128* q = (const u128*)&b;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, q[0]);
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, q[1]);
    r.r[1] = y;
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, q[2]);
    o->m110 = r;
}

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
            MulRotationIntoWorld(self, par->m110, self->rot);
        } else {
            self->m110 = self->rot;
        }
    } else {
        par = (PlacedObject*)self->parent;
        if (par != 0) {
            Vu0::Q(self->v140) = Vu0::Add(Vu0::Rotate(par->m110, Vu0::Q(self->pos)), Vu0::Q(par->v140));
            MulRotationIntoWorld(self, par->m110, self->rot);
        } else {
            self->v140 = self->pos;
            self->m110 = self->rot;
        }
    }
    u32 kind = self->bits24;
    if (kind == 2) {
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
    Rec2195_224* last = self->f224;
    if (last != 0 && (last->fB0 & 0x8020) == 0x8020) {
        ((PlacedObject*)last->f80)->f224->p64 = (BaseObject*)1;
        ((PlacedObject*)last->p84)->f224->p64 = (BaseObject*)1;
    }
}
