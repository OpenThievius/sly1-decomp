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
#include "fpu.h"
#include "owner_message.h"
#include "hit_target.h"
#include "value_range.h"
#include "functions/base_object.h"
#include "functions/child_group_object.h"
#include "functions/collider.h"
#include "functions/collider_span.h"
#include "functions/effect_spawner.h"
#include "functions/matrix.h"
#include "functions/oscillator.h"
#include "functions/path_follower.h"
#include "functions/placed_object.h"
#include "functions/player.h"
#include "functions/sound_system.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
#include "functions/world_contacts.h"
#include "functions/zone_collider.h"
struct BufferedStream;
struct Quad16;

struct BaseObject;
struct Vec02;

struct Mat02;
struct Vec02;


// Types other files define, named by the parameters of their functions declared here.
struct NodeQuery;

// The file's .data, in retail's order: class 0x3B's set-up values, then the constants of its
// assembly functions.
Quad3B g_childGroupMassRange = { 0x42480000, 0x459C4000, 0, 0 };
Quad3B g_childGroupScatterCurve = { 0x43FA0000, 0x3FE66666, 0, 0 };
Quad3B g_childGroupSpreadCurve = { 0x3F000000, 0x3E4CCCCD, 0, 0 };
Pair3B g_childGroupScatterRange = { 0x44160000, 0x44AF0000 };
Pair3B g_childGroupSpreadRange = { 0x41A00000, 0x42480000 };
f32 g_childGroupKnockbackSpeed = 600.0f;
f32 g_childGroupKnockbackLift = 800.0f;
// The two polynomials the knockback evaluates (TimePolynomial), aligned to 16 as the object's own
// polynomials at 0x5D0 and 0x5F0 are (Quad3B): retail has the 8 bytes of zeros that alignment
// leaves after the knockback's upward weight, D_00261364.
f32 g_childGroupApproachCurve[4] __attribute__((aligned(16))) = { 1.0f, -1.0f, 0.0f, 0.0f };
f32 g_childGroupDistanceCurve[4] __attribute__((aligned(16))) = { 2.0f, -1.5f, 0.0f, 0.0f };


void InitChildGroupObject(ChildGroupObject* self)
{
    InitCollider(self);
    self->blastTime = 3.4028235e+38f;
    self->blastRadius = 200.0f;
    self->playerBlastRadius = 200.0f;
    self->contactMode = 0;
    self->massRange = *(Pair3B*)&g_childGroupMassRange;
    self->pushStrength = 800.0f;
    self->maxMass = 5000.0f;
    self->speedCurve = *(Quad3B*)&g_childGroupScatterCurve;
    self->speedRange = *(Pair3B*)&g_childGroupScatterRange;
    self->spinCurve = *(Quad3B*)&g_childGroupSpreadCurve;
    self->spinRange = *(Pair3B*)&g_childGroupSpreadRange;
    self->announceBlast = 1;
    self->f678 = 1;
    self->ownerMessageMode = 0;
}


void LoadChildGroupObject(ChildGroupObject* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    FindOrBuildMemberGroup(&self->member5BC, self);
}

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
            if (IsObjectOfKind((BaseObject*)n, 0x27)) {
                s32 c = self->count;
                if ((u32)c < 16) {
                    self->arr[c] = (s32)n;
                    self->count = c + 1;
                    ResolveAndStartObject((BaseObject*)n);
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


void HandleChildGroupNotification(ChildGroupObject* self, s32 kind, ObjectMessage* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 0xA) {
        if ((ChildGroupObject*)msg->target == self) {
            if (((ChildGroupObject*)msg->target)->contactMode == 0) {
                StartChildGroupDelay((ChildGroupObject*)msg->target, 0.0f);
            }
        }
    }
}

extern f32 g_gameTime;

void UpdateChildGroupObject(ChildGroupObject* self, f32 dt)
{
    s32 slow;
    if (self->blastTime <= g_gameTime || (slow = Vu0::ToFloat(Vu0::Length(Vu0::Q(self->v150))) < self->settleSpeed)) {
        ApplyChildGroupRepulsion(self);
    } else {
        UpdateCollider(self, dt);
        if (self->active != 0) {
            RefreshChildGroupObjectContacts(self);
        }
    }
}

extern List01 g_class75List;

void RefreshChildGroupObjectContacts(ChildGroupObject* self)
{
    ListFrame frame;
    Vec02 tmp;
    ColliderSpan span;

    for (s32 i = 0; i < self->entryCount; i++) {
        PlacedObject* o = (PlacedObject*)self->entries[i].key;
        if (o->root != 0) {
            SetContactPairFlags(self->world, self->contacts, ((Collider*)o->root)->contacts, 0, 0x40);
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
        if (CollectBoundsSpans(&tmp, &self->v370, &self->v140, n->scale, 1, &span) == 0) {
            continue;
        }
        SetContactPairFlags(self->world, self->contacts, ((Collider*)a->root)->contacts, 0x40, 0);
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

Collider* GetActiveSwitchedCollider(void);

void HandleChildGroupObjectContact(ChildGroupObject* self, ContactPair* pair, s32 which)
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
    switch (self->contactMode) {
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
        if (FindNearestSpanObject(0, &self->v370, &self->v140, 1, &side->obj, &span) != 0) {
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
    o->m620 = m;
}

void RecordChildGroupPose(ChildGroupObject* self, Collider* obj, Vec02* pos, Vec02* z)
{
    Mat02 a;

    if ((self->flag60C) != 0) {
        return;
    }
    (self->obj670) = obj;
    (self->flag60C) = 1;
    if (pos != 0) {
        (self->v610) = *pos;
    } else {
        (self->v610) = self->v140;
    }
    (self->v650) = self->v150;
    (self->v660) = self->v160;
    switch ((self->mode608)) {
    case 0: {
        BuildShortestArcRotation(&self->m110.r[2], z ? z : (Vec02*)&g_unitZVector, &a);
        MulPoseRows(self, a, self->m110);
        Rec2195_224* rec = self->linkRecord;
        void* frame;
        if (rec != 0) {
            if ((rec->flags & 8) != 0) {
                frame = rec->p60;
            } else {
                frame = self->parent;
            }
        } else {
            frame = self->parent;
        }
        TransformRotationBetweenFrames(0, (PlacedObject*)frame, &self->m620, &self->m620);
        break;
    }
    case 1:
        BuildBasisFromXAndZHint(&self->v650, (const Vec02*)&g_unitZVector, &self->m620);
        break;
    case 2:
        (self->m620) = self->rot;
        break;
    }
}

extern f32 g_gameTime;

void StartChildGroupDelay(ChildGroupObject* self, f32 delta)
{
    self->blastTime = g_gameTime + delta;
}

extern f32 g_childGroupKnockbackLift;
struct VectorConstraint;

// The owner-message callback of a group's knockback: pushes the object away from the group
// (from the group to it, flat and unit length, or along X when they coincide; a kind-0x3D
// group's own direction at 0x700 instead), by D_00261360 along it and D_00261364 upward,
// constrained by the object's parent anchor, through the object's slot 36; a kind-7 object is
// put in state 0x2B.
// The unit vector is stored through a pointer as a structure, and the first weight is read as
// the float itself: a scalar at a fixed address does not wait for a structure store at a
// varying one, so sched2 loads the weight in the store's shadow and no argument move takes
// the slot (docs/toolchain/sched1.md, "A store in each arm leaves the join block to sched2").
void ApplyChildGroupKnockback(ChildGroupObject* self, Collider* other)
{
    Vec02 d;
    Vec02 r;
    if (IsObjectOfKind(self, 0x3D) != 0) {
        d = *(Vec02*)((u8*)self + 0x700);
    } else {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(other->v140), Vu0::Q(self->v140));
    }
    d.z = 0.0f;
    Vec02* p = &d;
    *(Vu0::Vec*)p = Vu0::NormalizeOr(Vu0::Vec::Of(d), Vu0::Vec::Of(g_unitXVector));
    Vu0::Q(r) = Vu0::MulXSum(Vu0::Q(d), Vu0::ScalarAtValue(g_childGroupKnockbackSpeed), Vu0::Q(g_unitZVector), Vu0::ScalarAtValue(g_childGroupKnockbackLift));
    ConstrainVectorByParentAnchor(other, (VectorConstraint*)&other->v440, &r, &r, 0);
    other->desc02()->m20(other, &r);
    if (IsObjectOfKind(other, 7) != 0) {
        SetPlayerState((Player*)other, 4, 0x2B);
    }
}

Collider* GetActiveSwitchedCollider();
extern f32 g_childGroupApproachCurve[4];
extern f32 g_childGroupDistanceCurve[4];

void PushBackMemoryMark();
void PopBackMemoryMark();
void* AllocateBackMemory(s32 size);
struct FaceRef;
struct Mesh03;
struct MeshHitEntry;
void CopyMemory(void* dst, void* src, u32 size);
s32 CollectMeshHits(Vec02* center, f32 radius, s32 count, FaceRef* list, FaceRef* cursor, Mesh03* mesh, s32 cap, MeshHitEntry* out);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
struct TimedStateObject;
extern const Vec02 g_unitZVector;
extern ValueRange g_unitRange;

static inline f32 MaxF(f32 a, f32 b) { return b >? a; }

typedef void (*ColliderMsgFn)(Collider* self, void* msg);
typedef s32 (*ColliderQueryFn)(Collider* self, void* msg);

// The query func_0013BF68 sends for each object it hits (0x40 bytes, FillMemory'd).
struct BlastQuery { ChildGroupObject* from; Collider* to; u8 pad08[0x10 - 0x08]; s32 kind; u8 pad14[0x20 - 0x14]; Vec02 pos; Vec02 vel; };
// The message a ChildGroupObject's member gets (kind 9): the object, then two floats at 0x30.
struct BlastMessage { s32 kind; ChildGroupObject* from; u8 pad08[0x30 - 0x08]; f32 f30; f32 f34; };
// The sound slot at +0x680.
struct BlastSound { s32 id; f32 a; f32 b; f32 c; };

void ApplyChildGroupRepulsion(ChildGroupObject* self)
{
    Collider* player;
    s32 count;
    Collider** list;
    Vec02* pos;
    Mat02* rot;
    Vec02* vel;
    Vec02* spin;
    RecordChildGroupPose(self, 0, 0, 0);
    player = (Collider*)GetActiveSwitchedCollider();
    PushBackMemoryMark();
    if (*(s32*)self->pad564 != 0) {
        CollectContactingParts(self, &count, (void***)&list);
        if (self->obj670 != 0) {
            s32 i;
            for (i = 0; i < count; i++) {
                if (self->obj670 == list[i])
                    break;
            }
            if (i >= count) {
                Collider** nl = (Collider**)AllocateBackMemory((count + 1) * 4);
                nl[0] = self->obj670;
                CopyMemory(nl + 1, list, count * 4);
                list = nl;
            }
        }
    } else {
        GatherCollidersInSphere(self->world, 0, MaxF(self->blastRadius, self->playerBlastRadius), &self->v610, 0, 0, &count, &list);
    }
    pos = &self->v610;
    rot = &self->m620;
    vel = &self->v650;
    spin = &self->v660;
    for (s32 i = 0; i < count; i++) {
        Collider* c = list[i];
        if (c->root == self->root)
            continue;
        if (c->id == 1)
            continue;
        if ((c->desc->flags & 0x20) != 0 && ((ChildGroupObject*)c)->contactMode != 1) {
            StartChildGroupDelay((ChildGroupObject*)c, 0.1f);
            continue;
        }
        if (*(s32*)self->pad564 == 0 && c->tree.nodes != 0) {
            u8 hits[0x30];
            if (!CollectMeshHits(pos, c->root == player ? self->playerBlastRadius : self->blastRadius, c->tree.count2, (FaceRef*)c->tree.nodes, 0, &c->meshCopy, 1, (MeshHitEntry*)hits))
                continue;
        }
        if (IsObjectOfKind(c, 5)) {
            OwnerMessage msg;
            InitOwnerMessage(&msg, self->ownerMessageMode, self);
            msg.fn = (void (*)())ApplyChildGroupKnockback;
            (*(ColliderQueryFn*)((u8*)c->desc + 0x140))(c, &msg);
            continue;
        }
        if (c->mass < self->maxMass && c->parent == 0) {
            Vec02 dir;
            Vec02 imp;
            Vec02 nv;
            Vec02 sp;
            Vec02 ns;
            Vec02 off;
            Vu0::Q(dir) = Vu0::Sub(Vu0::Q(c->v140), Vu0::Q(self->v610));
            Vu0::Q(off) = Vu0::Q(dir);
            dir.z += 200.0f;
            Vu0::Q(dir) = Vu0::NormalizeOr(Vu0::Q(dir), Vu0::Q(g_unitZVector));
            f32 m = 1.0f / Fpu::Sqrt(ClampToRange((ValueRange*)&self->massRange, c->mass) / *(f32*)&self->massRange.a);
            f32 sv = g_unitRange.Limit(((TimePolynomial*)g_childGroupApproachCurve)->Eval(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(c->v150), Vu0::Q(dir))) / self->pushStrength));
            f32 d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(off))) - (c->radius3CC + self->radius3D0);
            f32 sd = g_unitRange.Limit(((TimePolynomial*)g_childGroupDistanceCurve)->Eval((d >? 0.0f) / self->blastRadius));
            f32 k = self->pushStrength * m * sv * sd;
            Vu0::Q(imp) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(k));
            ConstrainColliderVector(c, &c->v440, &imp, &imp, 0);
            Vu0::Q(nv) = Vu0::Add(Vu0::Q(c->v150), Vu0::Q(imp));
            ((const Desc02*)c->desc)->m20(c, &nv);
            if (0.0001f < k) {
                f32 r = k * 0.01f;
                f32 nr = -r;
                f32 x = RandomFloatInRange(nr, r);
                f32 y = RandomFloatInRange(nr, r);
                f32 z = RandomFloatInRange(nr, r);
                Vu0::Q(sp) = Vu0::FromFloats(x, y, z);
                ConstrainColliderVector(c, &c->v460, &sp, &sp, 0);
                Vu0::Q(ns) = Vu0::Add(Vu0::Q(c->v160), Vu0::Q(sp));
                ((const Desc02*)c->desc)->m21(c, &ns);
            }
        }
        BlastQuery q;
        FillMemory(&q, 0, sizeof(q));
        q.to = c;
        Vu0::Q(q.pos) = Vu0::Q(self->v610);
        Vu0::Q(q.vel) = Vu0::Q(self->v150);
        q.kind = 0x10;
        q.from = self;
        FindNodeForQuery((NodeQuery*)&q, 0, 0);
    }
    PopBackMemoryMark();
    Vec02 at;
    {
        PlacedObject* frame;
        if (self->linkRecord != 0 && (*(u32*)((u8*)self->linkRecord + 0xB0) & 4) != 0)
            frame = *(PlacedObject**)((u8*)self->linkRecord + 0x60);
        else
            frame = (PlacedObject*)self->parent;
        TransformPointBetweenFrames(0, frame, pos, &at);
        ((const Desc02*)self->desc)->m1D(self, &at);
    }
    ((const Desc02*)self->desc)->m1E(self, rot);
    ((const Desc02*)self->desc)->m20(self, vel);
    ((const Desc02*)self->desc)->m21(self, spin);
    if (self->announceBlast != 0) {
        Vec02* at;
        if (self->member5BC != 0) {
            BlastMessage msg;
            msg.kind = 9;
            msg.f30 = *(f32*)self->pad5C0;
            msg.f34 = self->blastRadius;
            msg.from = self;
            (*(ColliderMsgFn*)((u8*)*(void**)self->member5BC + 0x7C))((Collider*)self->member5BC, &msg);
            at = &self->v140;
        } else {
            SendPointEventToWorldListener((Quad16*)&self->v140, self->blastRadius);
            at = &self->v140;
        }
        BlastSound* snd = (BlastSound*)self->slot;
        if (snd != 0)
            StartSoundEffect(snd->id, 0, 0, at, snd->a, snd->b, snd->c, 0.0f, 0.0f, 0, 0);
        else
            StartSoundEffect(0x35, 0, 0, at, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    if (self->count > 0) {
        f32 sa = ((ValueRange*)&self->speedRange)->Limit(((TimePolynomial*)&self->speedCurve)->Eval(self->blastRadius));
        f32 sb = ((ValueRange*)&self->spinRange)->Limit(((TimePolynomial*)&self->spinCurve)->Eval(self->blastRadius));
        for (s32 j = 0; j < self->count; j++) {
            Collider* o = (Collider*)self->arr[j];
            if (IsObjectAttached(o))
                continue;
            f32 x, y, z;
            f32 na = -sa;
            f32 nb = -sb;
            Vec02 v;
            Vec02 w;
            Vec02 rv;
            o->desc->m02(o);
            o->desc->m15(o, 0);
            SetTimedState((TimedStateObject*)o, 1);
            ((const Desc02*)o->desc)->m1D(o, &self->v140);
            x = RandomFloatInRange(0.0f, sa * 2.5f);
            y = RandomFloatInRange(na, sa);
            z = RandomFloatInRange(na, sa);
            Vu0::Q(v) = Vu0::FromFloats(x, y, z);
            Vu0::Q(rv) = Vu0::Rotate(self->m110, Vu0::Q(v));
            ((const Desc02*)o->desc)->m20(o, &rv);
            f32 sx = RandomFloatInRange(nb, sb);
            f32 sy = RandomFloatInRange(nb, sb);
            f32 sz = RandomFloatInRange(nb, sb);
            Vu0::Q(w) = Vu0::FromFloats(sx, sy, sz);
            ((const Desc02*)o->desc)->m21(o, &w);
        }
    }
    self->desc->m03(self);
    TriggerScriptEvent(self, 2, 0, 0);
    self->flag60C = 0;
    self->blastTime = 3.4028235e+38f;
}


s32 GetChildGroupSoundParams(ChildGroupObject* self)
{
    if (self->slot == 0) {
        InitSoundParams((SoundRecord**)&self->slot);
    }
    return (s32)self->slot;
}
