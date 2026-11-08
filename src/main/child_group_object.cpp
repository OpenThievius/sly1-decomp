// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "child_group_object.h"
#include "object_message.h"
#include "vu0.h"
#include "object_event.h"
#include "globals.h"
#include "transform_object.h"
#include "attachment.h"

// The file's .data, in retail's order: class 0x3B's set-up values, then the constants of its
// assembly functions.
Quad3B D_00261320 = { 0x42480000, 0x459C4000, 0, 0 };
Quad3B D_00261330 = { 0x43FA0000, 0x3FE66666, 0, 0 };
Quad3B D_00261340 = { 0x3F000000, 0x3E4CCCCD, 0, 0 };
Pair3B D_00261350 = { 0x44160000, 0x44AF0000 };
Pair3B D_00261358 = { 0x41A00000, 0x42480000 };
f32 D_00261360 = 600.0f;
INCLUDE_DATA(D_00261364);
f32 D_00261370[4] = { 1.0f, -1.0f, 0.0f, 0.0f };
f32 D_00261380[4] = { 2.0f, -1.5f, 0.0f, 0.0f };

void InitCollider(Collider* self);

void InitChildGroupObject(ChildGroupObject* self)
{
    InitCollider(self);
    self->f554 = 3.4028235e+38f;
    self->f55C = 200.0f;
    self->f560 = 200.0f;
    self->f550 = 0;
    self->f56C = *(Pair3B*)&D_00261320;
    self->f568 = 800.0f;
    self->f574 = 5000.0f;
    self->f5D0 = *(Quad3B*)&D_00261330;
    self->f5E0 = *(Pair3B*)&D_00261350;
    self->f5F0 = *(Quad3B*)&D_00261340;
    self->f600 = *(Pair3B*)&D_00261358;
    self->f674 = 1;
    self->f678 = 1;
    self->f67C = 0;
}

void LoadCollider(void* self);
void FindOrBuildMemberGroup(void* sub, void* self);

void LoadChildGroupObject(ChildGroupObject* self)
{
    LoadCollider(self);
    FindOrBuildMemberGroup(&self->member5BC, self);
}

void CopyCollider(void* self, void* other);
u32 CopyToFrontMemory(s32 size, void* src);

void CopyChildGroupObject(ChildGroupObject* self, ChildGroupObject* other)
{
    CopyCollider(self, other);
    if (other->slot) self->slot = (void*)CopyToFrontMemory(0x24, other->slot);
}

struct ScopedListFrame;
struct ScopedListFrame {
    void* base; void* cur; s32 off; ScopedListFrame* prev;
    ScopedListFrame(List01* l) {
        cur = l;
        base = l;
        ScopedListFrame* p = (ScopedListFrame*)g_activeListFrames;
        off = l->offset;
        g_activeListFrames = (ListFrame*)this;
        prev = p;
    }
    ~ScopedListFrame() { g_activeListFrames = (ListFrame*)prev; }
};

void StartPlacedObject(void* self);
s32 IsObjectOfKind(void* node, s32 kind);
void ResolveAndStartObject(s32 a);
void* AllocateFrontMemory(s32 size);

void StartChildGroupObject(ChildGroupObject* self)
{
    StartPlacedObject(self);
    ScopedListFrame f(&self->children);
    void* n;
    void* t = *(void**)f.base;
    f.cur = (u8*)t + f.off;
    n = t;
    if (n != 0) {
        do {
            if (IsObjectOfKind(n, 0x27)) {
                s32 c = self->count;
                if ((u32)c < 16) {
                    self->arr[c] = (s32)n;
                    self->count = c + 1;
                    ResolveAndStartObject((s32)n);
                }
            }
            void* c = f.cur; s32 o = f.off; void* a = *(void**)c;
            f.cur = (u8*)a + o; n = a;
        } while (n != 0);
    }
    if (self->active != 0) {
        self->entries = (Entry3B*)AllocateFrontMemory(0xC0);
    }
}

void HandlePlacedObjectNotification(ChildGroupObject* self, s32 kind, ObjectMessage* msg);
void StartChildGroupDelay(ChildGroupObject* p, f32 delta);

void HandleChildGroupNotification(ChildGroupObject* self, s32 kind, ObjectMessage* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 0xA) {
        if ((ChildGroupObject*)msg->target == self) {
            if (((ChildGroupObject*)msg->target)->f550 == 0) {
                StartChildGroupDelay((ChildGroupObject*)msg->target, 0.0f);
            }
        }
    }
}

extern f32 g_gameTime;
void UpdateCollider(Collider* self);
void func_0013B828(ChildGroupObject* self);
void func_0013BF68(ChildGroupObject* self);

void UpdateChildGroupObject(ChildGroupObject* self)
{
    s32 slow;
    if (self->f554 <= g_gameTime || (slow = Vu0::ToFloat(Vu0::Length(Vu0::Q(self->v150))) < self->f558)) {
        func_0013BF68(self);
    } else {
        UpdateCollider(self);
        if (self->active != 0) {
            func_0013B828(self);
        }
    }
}

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
        Vu0::StoreX(*(u32*)&e->value, Vu0::Dot(point, dir));
        Vu0::Q(*(Vec02*)((u8*)e + 0x10)) = dir;
        if (self->entryCount >= 4) {
            return;
        }
    }
}

s32 CreatePooledContact(void*, s32, void*, void*, s32, s32, s32, void*, f32);

void RunKeyedChildGroupEntry(ChildGroupObject* self, s32 key, s32 a2, s32 a3, s32 a4, void* arg5)
{
    s32 i;
    if (self->active) {
        for (i = 0; i < self->entryCount; i++) {
            if (self->entries[i].key == key) break;
        }
        if (i < self->entryCount) {
            Entry3B* e = &self->entries[i];
            CreatePooledContact(self, key, e, &e->data, 9, 0, 0, arg5, e->value);
        }
    }
}

// What func_0013BA70 is given: the two sides of a contact, 0x40 bytes each (the object at +4),
// and a vector after them.
struct ContactSide {
    u8 pad0[4];
    Collider* obj;          // 0x04
    u8 pad8[0x40 - 8];
};

struct ContactPair {
    ContactSide side[2];    // 0x00
    Vec02 v80;              // 0x80
};

Collider* FindNearestSpanObject(s32 flags, void* a1, void* a2, s32 count, Collider** list, ColliderSpan* out);
Collider* GetActiveSwitchedCollider(void);
s32 IsObjectDescendantOf(void* a, void* b);
void RecordChildGroupPose(ChildGroupObject* self, Collider* obj, Vec02* pos, Vec02* dir);

void func_0013BA70(ChildGroupObject* self, ContactPair* pair, s32 which)
{
    Vec02 pos;
    ColliderSpan span;
    Vec02 dir;
    Vec02 k;

    if (self->flag60C != 0) {
        return;
    }
    pos = self->v140;
    ContactSide* side = &pair->side[1 - which];
    Collider* obj = side->obj;
    switch (self->f550) {
    case 1:
        return;
    case 2: {
        Collider* other = GetActiveSwitchedCollider();
        if (other == 0) {
            return;
        }
        if (IsObjectDescendantOf(obj, other) != 0) {
            break;
        }
        return;
    }
    case 0:
        if (FindNearestSpanObject(0, (u8*)self + 0x370, &self->v140, 1, &side->obj, &span) != 0) {
            pos = *(Vec02*)&span.q[0];
        }
        break;
    default:
        return;
    }
    u128 r;
    if (which == 0) {
        r = Vu0::Q(pair->v80);
    } else {
        Vu0::Q(k) = Vu0::FromFloat(-1.0f);
        r = Vu0::MulX(Vu0::Q(pair->v80), Vu0::Q(k));
    }
    Vu0::Q(dir) = r;
    RecordChildGroupPose(self, obj, &pos, &dir);
    StartChildGroupDelay(self, 0.0f);
}

s32 HandleObjectEvent(Collider* self, ObjectEvent* ev);
void RecordChildGroupPose(ChildGroupObject* self, s32 a, s32 b, Vec02* dir);

s32 HandleChildGroupObjectEvent(ChildGroupObject* self, ObjectEvent* ev)
{
    s32 handled = HandleObjectEvent(self, ev);
    if (handled != 0 && (ev->eventFlags & 0x10) != 0) {
        Vec02 dir;
        Vu0::Q(dir) = Vu0::NormalizeOr(Vu0::Q(ev->v30), Vu0::Q(g_unitZVector));
        RecordChildGroupPose(self, 0, 0, &dir);
        StartChildGroupDelay(self, 0.0f);
    }
    return handled;
}

void BuildShortestArcRotation(void* from, void* to, void* out);
void BuildBasisFromXAndZHint(void* x, void* z, void* out);
void TransformRotationBetweenFrames(void* a, void* b, void* c, void* d);

// The product of the turn a and the object's matrix b into the pose at +0x620: b's rows read by
// index, each result stored to its vector local and to the matrix local, the last in the other
// order, then the matrix written through the object.
static inline void MulPoseRows(ChildGroupObject* o, const Mat02& a, const Mat02& b)
{
    const u128* q = (const u128*)&b;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 m;
    Vu0::Q(m.r[0]) = Vu0::Q(x) = Vu0::RotateUntied(a, q[0]);
    Vu0::Q(m.r[1]) = Vu0::Q(y) = Vu0::RotateUntied(a, q[1]);
    Vu0::Q(z) = Vu0::Q(m.r[2]) = Vu0::RotateUntied(a, q[2]);
    *(Mat02*)((u8*)o + 0x620) = m;
}

void RecordChildGroupPose(ChildGroupObject* self, Collider* obj, Vec02* pos, Vec02* z)
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
        MulPoseRows(self, a, self->m110);
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

extern f32 g_gameTime;

void StartChildGroupDelay(ChildGroupObject* self, f32 delta)
{
    self->f554 = g_gameTime + delta;
}

INCLUDE_ASM(func_0013BE18);

// The FLT_MAX func_0013BF68 loads, the last of the file's .rodata.
extern const f32 D_00249D78 = 3.4028235e+38f;

INCLUDE_ASM(func_0013BF68);

void InitSoundParams(void* p);

s32 GetChildGroupSoundParams(ChildGroupObject* self)
{
    if (self->slot == 0) {
        InitSoundParams(&self->slot);
    }
    return (s32)self->slot;
}
