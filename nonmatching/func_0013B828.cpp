// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 413/432 (95.6%), checked 2026-11-07
// NEAR: the word at +0x20 is now stored as retail does (Vu0::ToBits: qmfc2, then sw). Still differs in registers only: retail keeps the entry pointer in v1 (the product of count and 0x30 in a0) and takes qmfc2 into v0, the point in vf2 and the direction in vf1; here the entry is in a0, qmfc2 in v1 and the vectors the other way. The loads in either order, both stores before the dot, the word in a local first, the dot on fresh loads: no closer.
#include "common.h"
#include "child_group_object.h"
#include "attachment.h"
#include "vu0.h"
#include "transform_object.h"
#include "list_iter.h"

extern List01 g_class75List;
void SetContactPairFlags(World* w, s32 a, s32 b, u8 set, u8 clr);
s32 IsObjectAttached(void* p);
s32 GetObjectWorldPosition(void* self, Vec02* out);
s32 CollectBoundsSpans(Vec02* a, void* b, void* c, s32 d, ColliderSpan* e, f32 x);

void func_0013B828(ChildGroupObject* self)
{
    ListFrame frame;
    Vec02 tmp;
    ColliderSpan span;

    for (s32 i = 0; i < self->entryCount; i++) {
        PlacedObject* o = (PlacedObject*)self->entries[i].key;
        if (o->root != 0) {
            SetContactPairFlags(self->world, (s32)self->contacts, (s32)((Collider*)o->root)->contacts, 0, 0x40);
        }
    }
    self->entryCount = 0;
    for (Class75Object* n = (Class75Object*)g_class75List.head; n != 0; n = *(Class75Object**)&n->link) {
        if (n->f90 == 0) {
            continue;
        }
        if ((n->count & 0x10) == 0) {
            continue;
        }
        PlacedObject* a = (PlacedObject*)n;
        while (a != 0 && (a->desc->flags & 2) == 0) {
            a = (PlacedObject*)a->parent;
        }
        if (a == 0) {
            continue;
        }
        if (IsObjectAttached(a) == 0) {
            continue;
        }
        GetObjectWorldPosition(n, &tmp);
        if (CollectBoundsSpans(&tmp, (u8*)self + 0x370, &self->v140, 1, &span, n->scale) == 0) {
            continue;
        }
        SetContactPairFlags(self->world, (s32)self->contacts, (s32)((Collider*)a->root)->contacts, 0x40, 0);
        Entry3B* e = &self->entries[self->entryCount++];
        e->key = (s32)a;
        u128 point = Vu0::Q(span.q[0]);
        Vu0::Q(*(Vec02*)((u8*)e + 0x00)) = point;
        u128 dir = Vu0::Q(span.q[2]);
        *(u32*)&e->value = Vu0::ToBits(Vu0::Dot(point, dir));
        Vu0::Q(*(Vec02*)((u8*)e + 0x10)) = dir;
        if (self->entryCount >= 4) {
            return;
        }
    }
}

