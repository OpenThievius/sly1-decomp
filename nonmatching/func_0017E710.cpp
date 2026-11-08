// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1492/1496, checked 2026-11-08
// NEAR (src/main/file_17D248.cpp, where it is INCLUDE_ASM; 2026-11-08, night-untouched): the
// three loops, the class 0x75 walk with its frame (BeginListWalk and NextInList as
// file_1549C8.cpp has them), the height band and the queries are retail's code, 218 lines in
// all. Left: (1) retail keeps the high half of g_activeListFrames in s8 from the start (its
// lui in RecordCameraTimestamp's delay slot) through the walk's push and the final pop; here
// each use has its own lui, so s8 goes to the zero vector's address and the walk's frame push
// is ordered otherwise. (2) The NormalizeOr fallback: retail loads D_00248D00 with lq before
// the length's vsqrt and moves it with qmtc2 on the fallback's path (the divide taken by bc1f);
// here it is an lqc2 in the bc1t's slot. Tried: the frame written member by member, the query's
// owner and object stored before the direction.
#include "common.h"
#include "collider.h"
#include "globals.h"
#include "placed_object.h"
#include "vu0.h"
#include "node_query.h"
#include "list_iter.h"
#include "transform_object.h"

extern f32 D_00264028;
extern f32 D_0026402C;
extern f32 D_00264030;
extern f32 D_00264034;
extern f32 D_00264038[2];

s32 IsObjectAttached(void* p);
void RecordCameraTimestamp(Camera* camera);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInSphere(void* world, void* self, Vec02* center, void* filter, void* ctx, s32* count,
                             Collider*** list, f32 radius);
s32 IsObjectOfKind(void* object, s32 kind);
s32 GetObjectWorldPosition(void* object, Vec02* out);
void* FillMemory(void* dst, s32 value, s32 size);
PlacedObject* FindNodeForQuery(NodeQuery* q, s32 n, PlacedObject** list);
// A hit CollectMeshHits gives (0x30 bytes): its point first.
struct MeshPointHit {
    Vec02 point;
    u8 pad10[0x30 - 0x10];
};
s32 CollectMeshHits(f32 radius, Vec02* point, s32 count, void* nodes, void* a3, Mesh03* mesh, s32 max, MeshPointHit* out);
s32 IsInsideRange(f32* range, f32 value);
s32 RandomIntInRange(s32 lo, s32 hi);
extern List01 g_class75List;

// A walk of a list that RemoveFromList keeps valid: the frame is pushed on g_activeListFrames
// (list_iter.h) and each step reads the next item through the link (as file_1549C8.cpp's).
struct BeginListWalk {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};

template <class T> struct NextInList {
    static T* Of(ListFrame* it)
    {
        T* obj = *(T**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

// The player's reach of the frame with the object at 0x25E4: the class 0x75 objects near its
// point at 0x6A0 (within 300, 500 under a class 0x58 parent, and within 150 up or down) and the
// colliders gathered around it (the attached ones whose mesh reaches the point within that height,
// or that are near enough themselves) become queries of kind 0x20 aimed from the point.
void func_0017E710(Player* self)
{
    f32 band[2];
    ListFrame fr;
    s32 count;
    Collider** list;
    Class75Object* n;
    s32 i;

    if (!IsObjectAttached(self->f25D8[3])) {
        return;
    }
    RecordCameraTimestamp(g_camera);
    PushBackMemoryMark();
    GatherCollidersInSphere(self->world, self, &self->v140, 0, 0, &count, &list, D_00264028);
    for (i = 0; i < count; i++) {
        list[i]->flags538 |= (u64)0x8000 << 47;
    }
    band[0] = self->v6A0.z + D_00264038[0];
    band[1] = self->v6A0.z + D_00264038[1];
    BeginListWalk::Of(&fr, &g_class75List);
    n = NextInList<Class75Object>::Of(&fr);
    while (n != 0) {
        NodeQuery q;
        Vec02 pos;
        f32 range = D_00264028;
        PlacedObject* p;
        s32 far;
        for (p = (PlacedObject*)n->parent; p != 0; p = (PlacedObject*)p->parent) {
            if ((p->desc->flags & 2) && (((Collider*)p)->flags538 & ((u64)0x8000 << 47))) {
                goto next;
            }
            if (IsObjectOfKind(p, 0x58)) {
                range = D_0026402C;
            }
        }
        GetObjectWorldPosition(n, &pos);
        far = range < Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v6A0)),
                                                         Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v6A0))))) - n->scale;
        if (far) {
            goto next;
        }
        if (pos.z + n->scale < band[0] || band[1] < pos.z - n->scale) {
            goto next;
        }
        FillMemory(&q, 0, 0x40);
        q.p00 = self;
        q.hold = n;
        {
            u128 d = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v6A0));
            Vu0::Q(q.pos) = Vu0::Q(pos);
            Vu0::Q(q.dir) = Vu0::MulX(Vu0::NormalizeOr(d, Vu0::Q(D_00248D00)), Vu0::ScalarAt(D_00264030));
            q.weight = self->mass * D_00264034;
            q.kind = 0x20;
        }
        FindNodeForQuery(&q, 0, 0);
    next:
        n = NextInList<Class75Object>::Of(&fr);
    }
    for (i = 0; i < count; i++) {
        Collider* o = list[i];
        NodeQuery q;
        if (!IsObjectAttached(o)) {
            continue;
        }
        if (o->flags538 & ((u64)0x8000 << 25)) {
            s32 out = D_00264028 < Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(o->v140), Vu0::Q(self->v6A0))))
                || o->v140.z + o->radius3CC < band[0] || band[1] < o->v140.z - o->radius3CC;
            if (out) {
                continue;
            }
        } else if (o->tree.nodes != 0) {
            MeshPointHit hits[32];
            s32 hitCount = CollectMeshHits(D_00264028, &self->v6A0, o->tree.count2, o->tree.nodes, 0, &o->meshCopy, 32, hits);
            s32 j;
            for (j = 0; j < hitCount; j++) {
                if (IsInsideRange(band, hits[j].point.z)) {
                    break;
                }
            }
            if (j >= hitCount) {
                continue;
            }
        }
        FillMemory(&q, 0, 0x40);
        q.p00 = self;
        q.hold = o;
        if (o->meshCopy.vertCount > 0) {
            q.pos = ((Vec02*)o->meshCopy.verts)[RandomIntInRange(0, o->meshCopy.vertCount - 1)];
        } else {
            q.pos = o->v140;
        }
        {
            u128 d = Vu0::Sub(Vu0::Q(o->v140), Vu0::Q(self->v6A0));
            u128 dir = Vu0::NormalizeOr(d, Vu0::Q(D_00248D00));
            Vu0::Q(q.dir) = Vu0::MulX(dir, Vu0::ScalarAt(D_00264030));
            q.weight = self->mass * D_00264034;
            q.kind = 0x20;
        }
        FindNodeForQuery(&q, 0, 0);
    }
    for (i = 0; i < count; i++) {
        list[i]->flags538 &= ~((u64)0x8000 << 47);
    }
    PopBackMemoryMark();
    g_activeListFrames = fr.prev;
}
