// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"

#include "list_iter.h"
#include "timed_object.h"
#include "switched_collider.h"
#include "world.h"
#include "globals.h"
#include "object_link.h"
#include "state_trigger.h"
#include "owner_message.h"
#include "vu0.h"
#include "path_curve.h"

void InitCollider(Collider* self);
void UpdateCollider(Collider* self);
TrackPlayer* FindTrackPlayer(TimedObject* self);
// Slot 17 takes the frame time (Desc01::m11); func_001AEFA0 ignores it, but func_001AF5C8's call
// passes it (retail's frame shows the argument live).
void UpdateTimedObject(TimedObject* self, f32 dt);

ObjectLink g_timedGroupLinks[2] = { { 2, 0x28A, 0xAE4 }, { 2, 0x28B, 0xAE8 } };

void LoadCollider(Collider* self);
void ResolveObjectLinks(void* self, s32 n, void* table);

s32 MatchesObjectId(void* key, s32 item);
s32 IsObjectOfKind(void* key, s32 item);

extern f32 g_gameClock[];
s32 g_groupStaggerDirty = 0;

void SetColliderFrozen(void* self, void* p);
void AppendToList(void* list, void* item);
void RemoveFromList(void* list, void* item);

void StartPlacedObject(PlacedObject* self);
void* CreateObjectCopy(void* a, void* b, void* c);

s32 IsObjectExcluded(TimedObject* self, void* key);
s32 MaskWorldBitsBySave();

extern f32 g_gameTime[];
void TriggerScriptEvent(PlacedObject* self, s32 a, s32 b, s32 c);

ObjectLink g_sequencedObjectLinks[2] = {
    { 2, 0x28C, 0x5D0 },
    { 2, 0x28D, 0x5D4 },
};
void SetColliderAnchors(Collider* self, s32 a1, Vec02* a2, s32 a3, Vec02* a4);

// The record at PlacedObject::f200 of these objects: its word at 0x44 is cleared at start and
// set to 4 or 0 as the sequence enters state 0 or 2.
struct Record200 {
    u8 pad0[0x44];
    s32 f44;
};

s32 GetActiveSwitchedCollider(void);

void StopSoundRecord(void* snd, s32 n);
void StartSoundEffect(s32 kind, void* snd, void* owner, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void SetEffectSpawnerActiveForever(void* p);

void InitOwnerMessage(void* buf, s32 n, void* self);

void SetCursorFrame(s32 a, s32 frame);

void EnterSequencedSubstate(SequencedObject* self, s32 arg);
void StopTrackPlayer(TimedObject* self);
s32 IsSoleAcceptedObject(TimedObject* o, void* p);
void StaggerGroupOffsets();
void SetBlinkObjectFrame(BlinkObject* self);

void InitTimedObject(TimedObject* a0) {
    InitCollider(a0);
    a0->f554 = 0;
    a0->state = -1;
}

void SetTimedObjectTarget(TimedObject* self, s32 value)
{
    self->trigger = (StateTrigger*)value;
}

void EnterTimedObjectState(TimedObject* self, s32 state)
{
    if (self->state == state) return;
    if (self->state == 1 && state == 2) {
        if (self->trigger != 0) {
            SetStateTriggerStateFromMessage(self->trigger, 0);
            if (self->state != 1) state = self->state;
        }
        TriggerScriptEvent(self, 2, 0, 0);
    }
    self->state = state;
    self->f55C = g_gameTime[0];
}

s32 IsObjectInAcceptLists(TimedObject* self, void* value)
{

    if (self->f5B4 != 0) {
        return 1;
    }
    if (IsObjectExcluded(self, value) != 0) {
        return 0;
    }
    for (s32 i = 0; i < self->ids564.count; i++) {
        if (MatchesObjectId(value, self->ids564.items[i]) != 0) {
            return 1;
        }
    }
    for (s32 i = 0; i < self->ids58C.count; i++) {
        if (IsObjectOfKind(value, self->ids58C.items[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

s32 IsObjectExcluded(TimedObject* self, void* key)
{
    for (s32 i = 0; i < self->ids578.count; i++) {
        if (MatchesObjectId(key, self->ids578.items[i]) != 0) {
            return 1;
        }
    }
    for (s32 i = 0; i < self->ids5A0.count; i++) {
        if (IsObjectOfKind(key, self->ids5A0.items[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

s32 IsSoleAcceptedObject(TimedObject* o, void* p)
{
    if (p == 0) return 0;
    if (o->f5B4 == 0 && o->ids564.count == 1 && o->ids58C.count == 0 && MatchesObjectId(p, o->ids564.items[0]) != 0) return 1;
    return 0;
}

void StopTrackPlayer(TimedObject* self)
{
    TrackPlayer* node = FindTrackPlayer(self);

    if (node != 0) {
        self->f5CC = node->f18.f;
        node->f18.w = 0;
        self->f5C8 = node;
    }
}

void UpdateTimedObject(TimedObject* self)
{
    UpdateCollider(self);
    TrackPlayer* sink = self->f5C8;
    if (sink != 0) {
        Player* g = g_player;
        if (g != 0) {
            if (g->f2220 != 4) {
                sink->f18.f = self->f5CC;
                self->f5C8 = 0;
                *(s32*)&self->f5CC = 0;
            }
        }
    }
}

void AddTimedObjectAcceptedObjectId(TimedObject* self, s32 value)
{
    u32 n = self->ids564.count;
    if (n < 4) {
        self->ids564.items[n] = value;
        self->ids564.count = n + 1;
    }
}

void AddTimedObjectExcludedObjectId(TimedObject* self, s32 item)
{
    s32 n = self->ids578.count;
    if ((u32)n < 4) {
        self->ids578.items[n] = item;
        self->ids578.count = n + 1;
    }
}

void AddTimedObjectAcceptedClassId(TimedObject* self, s32 item)
{
    s32 n = self->ids58C.count;
    if ((u32)n < 4) {
        self->ids58C.items[n] = item;
        self->ids58C.count = n + 1;
    }
}

void AddTimedObjectExcludedClassId(TimedObject* q, u32 value)
{
    u32 n = q->ids5A0.count;
    if (n < 4) {
        q->ids5A0.items[n] = value;
        q->ids5A0.count = n + 1;
    }
}

void InitTimedGroup(TimedGroup* self)
{
    InitTimedObject(self);
    self->fB04 = 1.0f;
}

void LoadTimedGroup(TimedGroup* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 2, g_timedGroupLinks);
}

// A walk of a list that RemoveFromList keeps valid: the frame is pushed on g_activeListFrames
// (list_iter.h) and each step reads the next item through the link.
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

void PostLoadPlacedObject(PlacedObject* self);
void TransformPointBetweenFrames(void* from, void* to, void* point, Vec02* out);
void SetEffectSpawnerActiveForever(BaseObject* obj);
s32 QueryValueListMask(void* self, f32 radius, void* center, void* out);

// The curve object at 0x34 of a path curve object.
struct GroupCurveObject {
    u8 pad00[0x34];
    PathCurve* curve;       // 0x34
};

// Collects the path curves and the 0x50 objects among the group's children, and widens the
// reach (f2A8) of the group and of its parents to cover them.
void PostLoadTimedGroup(TimedGroup* self)
{
    ListFrame frame;
    Vec02 point;
    PostLoadPlacedObject(self);
    BeginListWalk::Of(&frame, &self->children);
    BaseObject* node;
    while ((node = NextInList<BaseObject>::Of(&frame)) != 0) {
        if (IsObjectOfKind(node, 0x6E) != 0) {
            if ((u32)self->groupCount < 16) {
                PathCurve* curve = ((GroupCurveObject*)node)->curve;
                if (curve->kind == 0) {
                    s32 n = self->groupCount;
                    self->groupCount = n + 1;
                    TimedGroupChild* g = (TimedGroupChild*)((u8*)self + n * 0x50 + 0x5E0);
                    g->child = node;
                    g->riseScale = curve->lengths[curve->count - 1];
                    s32* widest = (s32*)((u8*)self + 0xAE0);
                    s32 w = *widest;
                    if (!(curve->count < w)) {
                        w = curve->count;
                    }
                    *widest = w;
                    for (s32 i = 0; i < curve->count; i++) {
                        TransformPointBetweenFrames(self, 0, (u8*)curve->points + i * 16, &point);
                        f32 d = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(point))));
                        if (self->f2A8 < d) {
                            self->f2A8 = d;
                        }
                    }
                }
            }
        } else if (IsObjectOfKind(node, 0x50) != 0) {
            if ((u32)self->groups[0].count < 4) {
                TimedGroupEntry* e = &self->groups[0].items[self->groups[0].count++];
                e->obj = node;
                e->value = node->id == 0x289;
                SetEffectSpawnerActiveForever(node);
            }
        }
    }
    if ((self->flags & 0x3000000) != 0x2000000) {
        QueryValueListMask(*(void**)((u8*)self->world + 0x1EC4), self->f2A8, &self->v140, (u8*)self + 0x88);
    }
    PlacedObject* o = self;
    if (o->parent != 0) {
        do {
            f32 reach = Vu0::ToFloat(Vu0::Length(Vu0::Q(o->pos))) + o->f2A8;
            PlacedObject* up = (PlacedObject*)o->parent;
            if (reach <= up->f2A8) {
                break;
            }
            up->f2A8 = reach;
            if ((up->flags & 0x3000000) != 0x2000000) {
                QueryValueListMask(*(void**)((u8*)up->world + 0x1EC4), reach, &up->v140, (u8*)up + 0x88);
            }
            o = (PlacedObject*)o->parent;
        } while (o->parent != 0);
    }
    g_activeListFrames = frame.prev;
}

void CloneTimedGroupEntries(TimedGroup* self)
{
    TimedGroupChild* src = &self->groups[0];
    StartPlacedObject(self);
    for (s32 i = 0; i < self->groupCount; i++) {
        TimedGroupChild* g = &self->groups[i];
        BaseObject* c = g->child;
        c->desc->m03(c);
        if (i != 0) {
            {
                s32 j;
                for (j = 0; j < src->count; j++) {
                    TimedGroupEntry* s = src->items + j;
                    TimedGroupEntry* d = g->items + j;
                    BaseObject* o = (BaseObject*)CreateObjectCopy(s->obj, self->world, self);
                    d->obj = o;
                    if (o->desc->m0F != 0) {
                        o->desc->m0F(o);
                    }
                    o = d->obj;
                    o->desc->m10(o);
                    d->value = s->value;
                }
            }
            g->count = src->count;
        }
    }
    self->fB00 = IsSoleAcceptedObject(self, (void*)g_player);
    self->desc30()->m4D(self, self->f560);
}

void StaggerGroupOffsets()
{
    ListFrame frame;
    s32 count = 0;
    TimedGroup* n = (TimedGroup*)g_currentWorld->list1CA8.head;
    while (n != 0) {
        s32 t = count + 1;
        count = (n->state != 8) ? t : count;
        n = n->listNext;
    }
    if (count != 0) {
        s32 idx = 0;
        n = (TimedGroup*)g_currentWorld->list1CA8.head;
        while (n != 0) {
            if (n->state != 8) {
                n->fAFC = g_gameClock[1] + (0.03333333507180214f / (f32)count) * (f32)idx;
                idx++;
            }
            n = n->listNext;
        }
    }
    g_groupStaggerDirty = 0;
}

void UpdateTimedGroup(TimedGroup* self, f32 amount)
{
    s32 cmd;
    f32 v;
    f32 hi;
    f32 lo;

    UpdateTimedObject(self, amount);
    v = self->fB04 + amount * self->fB08;
    hi = 1.0f;
    lo = 0.0f;
    if (v < lo)
        v = lo;
    else if (hi < v)
        v = hi;
    self->fB04 = v;
    if (g_groupStaggerDirty)
        StaggerGroupOffsets();
    cmd = self->state;
    switch (cmd) {
    case 0:
        if (self->f5B8 < g_gameTime[0] - self->f55C)
            cmd = 1;
        if (self->desc30()->m48)
            self->desc30()->m48(self, &cmd);
        break;
    case 2:
        cmd = 3;
        if (self->desc30()->m48)
            self->desc30()->m48(self, &cmd);
        break;
    case 3:
        if (self->f5BC < g_gameTime[0] - self->f55C) {
            if (self->f554 == 0) {
                cmd = 8;
                break;
            }
            if (self->f554 != 1)
                break;
            cmd = 4;
            if (self->desc30()->m48)
                self->desc30()->m48(self, &cmd);
            break;
        }
        if (self->desc30()->m48)
            self->desc30()->m48(self, &cmd);
        break;
    case 4:
        if (self->f5B8 < g_gameTime[0] - self->f55C)
            cmd = 5;
        if (self->desc30()->m48)
            self->desc30()->m48(self, &cmd);
        break;
    case 1:
    case 5:
    case 6:
        if (self->desc30()->m48)
            self->desc30()->m48(self, &cmd);
        break;
    case 7:
        if (self->fAEC < g_gameTime[0] - self->f55C)
            cmd = 8;
        else if (self->desc30()->m48)
            self->desc30()->m48(self, &cmd);
        break;
    case 8:
        break;
    }
    self->desc30()->m4D(self, cmd);
}

void SetStaggeredColliderFrozen(TimedGroup* self, void* p)
{
    SetColliderFrozen(self, p);
    if (p != 0) {
        if (self->flagAF8 != 0) {
            RemoveFromList(&self->world->list1CA8, self);
            self->flagAF8 = 0;
        }
    } else {
        AppendToList(&self->world->list1CA8, self);
        self->flagAF8 = 1;
    }
    g_groupStaggerDirty = 1;
}

struct DrawPoints {
    u8 pad0[0xC];
    s32 count;
    u8 pad10[0x18 - 0x10];
    Vec02* points;
};

void DrawCollider(TimedGroup* self, void* a1, void* a2);
void DrawBeamBetweenPoints(void* world, void* a1, void* a2, void* a3, f32 a, f32 b);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
Vec02* AllocateBackMemory(s32 size);
f32 ComputeTimedGroupRamp(TimedGroup* o, TimedGroupChild* c);

void DrawTimedGroup(TimedGroup* self, void* a1, void* a2)
{
    DrawCollider(self, a1, a2);
    s32 st = self->state;
    if (st == 8 || st < 0) return;
    void* fp;
    if (st < 4) {
        fp = *(void**)((u8*)self + 0xAE4);
    } else if (st < 8) {
        fp = *(void**)((u8*)self + 0xAE8);
    } else {
        return;
    }
    if (fp == 0) {
        fp = (void*)self->world->f1D14;
        if (fp == 0) return;
    }
    s32 i = 0;
    PushBackMemoryMark();
    Vec02* buf = AllocateBackMemory(*(s32*)((u8*)self + 0xAE0) << 4);
    while (i < self->groupCount) {
        TimedGroupChild* g = &self->groups[i];
        f32 acc = 0.0f;
        DrawPoints* src = *(DrawPoints**)((u8*)g->child + 0x34);
        s32 n = src->count;
        f32 total = ComputeTimedGroupRamp(self, g);
        if (*(s32*)((u8*)g + 0xC) != 0) {
            s32 lim = *(s32*)((u8*)g + 0x20) + 2;
            if (lim < n) n = lim;
        }
        s32 next = i + 1;
        s32 k;
        for (k = 0; k < n; k++) {
            TransformPointBetweenFrames(self, (void*)0, &src->points[k], &buf[k]);
        }
        if (*(s32*)((u8*)g + 0xC) != 0) {
            buf[*(s32*)((u8*)g + 0x20) + 1] = *(Vec02*)((u8*)g + 0x10);
        }
        for (k = 0; k < n - 1; k++) {
            u128 d = Vu0::Sub(Vu0::Q(buf[k]), Vu0::Q(buf[k + 1]));
            f32 len = Vu0::ToFloat(Vu0::Sqrt(Vu0::Dot(d, d)));
            f32 rest = total - acc;
            if (rest < len) {
                f32 t = rest / len;
                u128 ws = Vu0::Scalar(1.0f - t);
                u128 p0 = Vu0::Q(buf[k]);
                u128 wt = Vu0::Scalar(t);
                u128 p1 = Vu0::Q(buf[k + 1]);
                Vu0::Q(buf[k + 1]) = Vu0::MulXSum(p0, ws, p1, wt);
            }
            DrawBeamBetweenPoints(fp, a1, &buf[k], &buf[k + 1], 1.0f, a2 != 0 ? *(f32*)((u8*)a2 + 0x40) : 1.0f);
            acc += len;
            if (total < acc) break;
        }
        switch (self->state) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
            g->fallScale = acc;
            break;
        }
        i = next;
    }
    PopBackMemoryMark();
}

s32 IsTimedGroupCandidate(TimedObject* a0, Collider* a1)
{
    u64 m = 0x8000;
    m <<= 28;
    if ((a1->flags538 & m) != 0 || a1->root == a0->root || IsObjectExcluded(a0, a1) != 0) {
        return 0;
    }
    if ((void*)a1 == (void*)g_player && ((Player*)a1)->f2220 == 6 && ((Player*)a1)->f239C == 3) {
        if ((MaskWorldBitsBySave() & 0x12000) != 0) {
            return 0;
        }
    }
    s64 t = (s64)a1->flagsHi;
    return ((s32)t ^ 1) & 1;

}

s32 FindNearestSpanObject(s32 flags, Vec02* a, Vec02* b, s32 count, Collider** list, ColliderSpan* out);
void GatherCollidersInSphere(World* world, f32 radius, s32 zero, Vec02* at, s32 (*filter)(TimedObject*, Collider*), TimedObject* self, s32* n, Collider*** list);
void* GetOwnSpawnRecord(BaseObject* obj, s32 mode);
void SetEffectSpawnerInactive(BaseObject* obj);
void InitOwnerMessage(OwnerMessage* out, s32 a, TimedObject* self);

// Slot 72 of class 0x31: walks each group's points (its child's curve, in the world) in pieces,
// looks for the nearest object across each piece that is in view (the player first when the
// group follows it, else those near the piece's middle), and when one is reached within the
// group's ramp, keeps where and tells it, or the player, of the new state; the group's spawners
// are then moved to the place or let run.
void ChooseTimedGroupState(TimedGroup* self, s32* state)
{
    ColliderSpan span;
    Vec02 p0;
    Vec02 p1;
    Vec02 mid;
    if (g_gameTime[0] < self->fAFC) {
        return;
    }
    s32 i = 0;
    self->fAFC = g_gameTime[0] + 0.033333335f;
    PushBackMemoryMark();
    Vec02* pts = AllocateBackMemory(*(s32*)((u8*)self + 0xAE0) << 4);
    while (i < self->groupCount) {
        TimedGroupChild* g = &self->groups[i];
        f32 acc = 0.0f;
        s32 k;
        s32 next = i + 1;
        s32 active = 0;
        f32 total = ComputeTimedGroupRamp(self, g);
        DrawPoints* src = *(DrawPoints**)((u8*)g->child + 0x34);
        s32 n = src->count;
        *(Collider**)((u8*)g + 0xC) = 0;
        for (k = 0; k < n; k++) {
            TransformPointBetweenFrames(self, (void*)0, &src->points[k], &pts[k]);
        }
        for (k = 0; k < n - 1; k++) {
            s32 look = 1;
            Collider* hit = 0;
            Vu0::Q(p0) = Vu0::Q(pts[k]);
            Vu0::Q(p1) = Vu0::Q(pts[k + 1]);
            Vu0::Q(mid) = Vu0::MulXSum(Vu0::Q(p0), Vu0::Scalar(0.5f), Vu0::Q(p1), Vu0::Scalar(0.5f));
            f32 len = Vu0::Distance(p0, p1);
            f32 radius = len * 0.5f;
            if (self->fB00 != 0) {
                Camera* cam = g_camera;
                u128 ones = Vu0::Ones();
                u128 v = Vu0::Sub(Vu0::Q(mid), Vu0::Q(cam->f40));
                u32 signs = Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), v, ones, Vu0::Scalar(radius)) ^ 0xF0;
                look = signs == 0;
                if (look && g_player != 0 && *(s32*)((u8*)self + 0x5D0) == 1) {
                    if (g_player->f2220 != 6 || g_player->f239C != 3 || (MaskWorldBitsBySave() & 0x12000) == 0) {
                        hit = (Collider*)FindNearestSpanObject(0, &p0, &p1, 1, (Collider**)&g_player, &span);
                        look = 0;
                    }
                }
            }
            if (look) {
                s32 count;
                Collider** list;
                PushBackMemoryMark();
                GatherCollidersInSphere(self->world, radius, 0, &mid, IsTimedGroupCandidate, self, &count, &list);
                hit = (Collider*)FindNearestSpanObject(0, &p0, &p1, count, list, &span);
                PopBackMemoryMark();
            }
            if (hit != 0) {
                s32 near = acc + Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Vec::Of(p0), Vu0::Vec::Of(span.q[0])))) < total;
                if (near) {
                    Vu0::Q(*(Quad16*)((u8*)g + 0x10)) = Vu0::Q(span.q[0]);
                    *(s32*)((u8*)g + 0x20) = k;
                    *(Collider**)((u8*)g + 0xC) = hit;
                    if (*state < 8) {
                        active = *state >= 4;
                    }
                    if (IsObjectInAcceptLists(self, hit) != 0) {
                        switch (*state) {
                        case 1:
                            *state = 2;
                            break;
                        case 5:
                            *state = 6;
                        case 4:
                        case 6:
                        case 7:
                            if (*state == 6 && hit == (Collider*)g_player) {
                                OwnerMessage buf;
                                InitOwnerMessage(&buf, 2, self);
                                if (g_player->desc06()->m4C(g_player, &buf) != 0) {
                                    StopTrackPlayer(self);
                                }
                            }
                            break;
                        }
                        self->desc30()->m4D(self, *state);
                    }
                    break;
                }
            }
            acc += len;
            if (total < acc) {
                break;
            }
        }
        for (s32 j = 0; j < g->count; j++) {
            TimedGroupEntry* e = &g->items[j];
            Collider* h;
            u64 m = 0x8000;
            m <<= 41;
            if (active && (h = *(Collider**)((u8*)g + 0xC)) != 0 && ((h->flags538 & m) != 0 || e->value == 0)) {
                Quad16* rec = (Quad16*)GetOwnSpawnRecord(e->obj, 1);
                rec[6] = span.q[2];
                TransformPointBetweenFrames((void*)0, self, &span.q[0], &p0);
                ((void (*)(BaseObject*, Vec02*))((void**)e->obj->desc)[33])(e->obj, &p0);
                SetEffectSpawnerInactive(e->obj);
            } else {
                SetEffectSpawnerActiveForever(e->obj);
            }
        }
        i = next;
    }
    PopBackMemoryMark();
}

void SetTimedGroupMode(TimedGroup* self, s32 flag)
{
    s32 m = 5;
    self->f554 = flag;
    if (!flag) {
        m = 1;
    }
    self->desc30()->m4D(self, m);
}

void RequestTimedGroupEnd(TimedGroup* self)
{
    if (self->state == 8) {
        return;
    }
    s32 m = 7;
    if (!self->f554) {
        m = 3;
    }
    self->desc30()->m4D(self, m);
}

void FinishTimedGroup(TimedGroup* self)
{
    if (self->state < 3) {
        if (self->state >= 0) {
            self->desc30()->m4D(self, 3);
        }
    }
    self->f554 = 1;
}

void EnterTimedGroupState(TimedGroup* self, s32 s)
{
    s32 st = self->state;
    if (st == s) return;
    if (st == -1 || st == 8) {
        f32 z = 0.0f;
        f32 a = 1000.0f, c = 100.0f, d = 0.4f;
        StartSoundEffect(0x1A, &self->f5C4, self, 0, a, c, d, z, z, 0, 0);
    }
    switch (s) {
    case 3:
    case 7:
        for (s32 i = 0; i < self->groupCount; i++) {
            TimedGroupChild* e = &self->groups[i];
            for (s32 j = 0; j < e->count; j++) SetEffectSpawnerActiveForever(e->items[j].obj);
        }
        break;
    case 8: {
        f32 v;
        if (self->f554 == 0) v = self->f5BC; else v = self->fAEC;
        StopSoundRecord(self->f5C4, (s32)v * 1000);
        self->desc->m03(self);
        g_groupStaggerDirty = 1;
        break;
    }
    default:
        break;
    }
    EnterTimedObjectState(self, s);
}

f32 ComputeTimedGroupRamp(TimedGroup* o, TimedGroupChild* c)
{
    f32 s = c->riseScale;
    f32 r;
    f32 m;
    f32 t;
    switch (o->state) {
    case 0:
    case 4: {
        f32 t0 = o->f5B8;
        if (t0 == 0.0f) {
            r = o->fB04;
        } else {
            f32 q = (g_gameTime[0] - o->f55C) / t0;
            m = o->fB04;
            if (q < 0.0f)
                r = 0.0f;
            else if (m < q)
                r = m;
            else
                r = q;
        }
        break;
    }
    case 1:
    case 2:
    case 5:
    case 6:
        r = o->fB04;
        break;
    case 3:
    case 7:
        t = o->f554 == 0 ? o->f5BC : o->fAEC;
        if (t == 0.0f) {
            r = 0.0f;
        } else {
            f32 m = o->fB04;
            r = 1.0f - (g_gameTime[0] - o->f55C) / t;
            if (r < 0.0f)
                r = 0.0f;
            else if (m < r)
                r = m;
        }
        s = c->fallScale;
        break;
    case 8:
        r = 0.0f;
        break;
    }
    return s * r;
}

void SetTimedGroupFadeOutTime(TimedGroup* self, f32 x)
{
    self->fB08 = -1.0f / x;
}

void SetTimedGroupFadeInTime(TimedGroup* p, f32 x) { p->fB08 = 1.0f / x; }

void InitSequencedObject(SequencedObject* o)
{
    InitTimedObject(o);
    o->state5D8 = -1;
}

void SetupSequencedObject(SequencedObject* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 2, g_sequencedObjectLinks);
    if (self->f5D0 == 0) {
        self->f5D0 = self;
    }
    if (self->f5D4 == 0) {
        self->f5D4 = self->world->f1D14;
    }
    if (self->f200 != 0) {
        ((Record200*)self->f200)->f44 = 0;
    }
    u64 m = 0x8000;
    m <<= 28;
    self->flags538 |= m;
    SetColliderAnchors(self, 3, 0, 3, 0);
    self->desc30()->m4D(self, self->f560);
}

void UpdateSequencedObject(SequencedObject* self) {
    s32 st;
    s32 s1;
    UpdateTimedObject(self);
    st = self->state;
    switch (self->state) {
    case 0:
        if (self->f5B8 < g_gameTime[0] - self->f55C) st = 1;
        break;
    case 2:
        st = 3;
        break;
    case 3:
        if (self->f5BC < g_gameTime[0] - self->f55C) st = 8;
        break;
    case 4:
        if (self->f5B8 < g_gameTime[0] - self->f55C) st = 5;
        break;
    case 1:
    case 5:
        if (self->desc30()->m48) {
            self->desc30()->m48(self, &st);
        }
        goto tail;
    case 6:
        s1 = self->state5D8;
        switch (s1) {
        case 0:
            if (g_player && g_player->desc06()->m4B(g_player, 2)) {
                s1 = 2;
            } else if (self->f5E0 < g_gameTime[0] - self->f5DC) {
                if (g_player) {
                    u8 buf[16];
                    InitOwnerMessage(buf, 2, self);
                    if (g_player->desc06()->m4C(g_player, buf)) {
                        s1 = 1;
                        StopTrackPlayer(self);
                    }
                } else {
                    s1 = 1;
                }
            }
            break;
        case 1:
            if (self->f5E4 < g_gameTime[0] - self->f5DC) s1 = 2;
            break;
        case 2:
            if (self->f5E8 < g_gameTime[0] - self->f5DC) {
                s1 = -1;
                st = 5;
            }
            break;
        }
        EnterSequencedSubstate(self, s1);
        goto tail;
    case 7:
        if (self->f5BC < g_gameTime[0] - self->f55C) st = 8;
        break;
    case 8:
        if (self->f5C0 == 0) {
            switch (self->f554) {
            case 0: st = 0; break;
            case 1: st = 4; break;
            }
        }
        goto tail;
    }
tail:
    self->desc30()->m4D(self, st);
}

struct SequencedTransform {
    Quad16 rows[4];
    f32 f40;
    f32 f44;
    u8 pad48[8];
};
void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, SequencedTransform* dst);
void BuildScaledTransformMatrix(Vec02* pos, Mat02* rot, Vec02* scale, SequencedTransform* out);
void DrawBeamBetweenPoints(void* world, void* a1, void* a2, void* a3, f32 a, f32 b);

static inline f32 ClampRange(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

void DrawSequencedObject(SequencedObject* self, void* a1, Quad16* a2)
{
    Vec02 scale;
    SequencedTransform tmp;
    Collider* tgt;
    if (self->state != 8) {
        BuildPlacedObjectTransform(self, a2, &tmp);
        switch (self->state) {
        case 0:
        case 4: {
            f32 t;
            if (self->f5B8 == 0.0f) {
                t = 1.0f;
            } else {
                t = (g_gameTime[0] - self->f55C) / self->f5B8;
                t = ClampRange(t, 0.0f, 1.0f);
            }
            Vu0::Q(scale) = Vu0::Splat(t);
            scale.x = 1.0f;
            break;
        }
        case 3:
        case 7: {
            f32 t;
            if (self->f5BC == 0.0f) {
                t = 0.0f;
            } else {
                t = 1.0f - (g_gameTime[0] - self->f55C) / self->f5BC;
                t = ClampRange(t, 0.0f, 1.0f);
            }
            Vu0::Q(scale) = Vu0::Splat(t);
            scale.x = 1.0f;
            break;
        }
        case 1:
        case 2:
        case 5:
            Vu0::Q(scale) = Vu0::Splat(1.0f);
            break;
        case 6: {
            f32 r;
            scale.x = 1.0f;
            switch (self->state5D8) {
            case 0:
                if (self->f5E0 == 0.0f) {
                    r = 0.1f;
                } else {
                    r = 1.0f - (g_gameTime[0] - self->f5DC) / self->f5E0;
                    if (r < 0.1f) {
                        r = 0.1f;
                        scale.z = scale.y = r;
                        break;
                    }
                    r = ClampRange(r, 0.1f, 1.0f);
                }
                scale.z = scale.y = r;
                break;
            case 1:
                if (g_player != 0 && self->f5D4 != 0) {
                    f32 w;
                    if (self->f5E4 == 0.0f) {
                        w = 1.0f;
                    } else {
                        w = ClampRange((g_gameTime[0] - self->f5DC) / self->f5E4, 0.0f, 1.0f);
                    }
                    Vec02 blend;
                    Vu0::Q(blend) = Vu0::MulXSum(Vu0::Q(self->v140), Vu0::Scalar(1.0f - w), Vu0::Q(((Collider*)g_player)->v140), Vu0::Scalar(w));
                    DrawBeamBetweenPoints((void*)self->f5D4, a1, &blend, &((Collider*)g_player)->v140, 10.0f, tmp.f40);
                }
                r = 0.1f;
                scale.z = scale.y = r;
                break;
            case 2:
                if (self->f5E8 == 0.0f) {
                    r = 1.0f;
                } else {
                    r = (g_gameTime[0] - self->f5DC) / self->f5E8;
                    r = ClampRange(r, 0.1f, 1.0f);
                }
                scale.z = scale.y = r;
                break;
            }
            break;
        }
        }
        if (self->state >= 0) {
            if (self->state < 4) {
                tgt = self;
            } else if (self->state < 8) {
                tgt = self->f5D0;
            }
        }
        BuildScaledTransformMatrix(&self->v140, &self->m110, &scale, &tmp);
        tgt->desc02()->m26(tgt, a1, &tmp);
    }
}

s32 TestSequencedObjectMayContact() { return 1; }

s32 IsSequencedObjectCandidate(TimedObject* self, Collider* other)
{
    if ((other->flags538 & (1UL << 43)) != 0 || (s32)other->root == GetActiveSwitchedCollider() || other->root == self->root || IsObjectExcluded(self, other) != 0) {
        return 0;
    }
    s64 t = (s64)other->flagsHi;
    return ((s32)t ^ 1) & 1;
}

s32 IsPointInsideCollider(Collider* self, Vec02* p);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, s32 p1, Vec02* lo, Vec02* hi, s32 (*filter)(TimedObject*, Collider*), TimedObject* self, s32* n, Collider*** list);
s32 FindNearestSpanObject(s32 flags, Vec02* a, Vec02* b, s32 count, Collider** list, ColliderSpan* out);
extern const Vec02 g_unitXVector;

// Slot 72 of class 0x32: picks the state from the player's place (inside the object or not, and
// which way it faces by the mode), writing 2 or 6 into state when nothing stands between.
void ChooseSequencedObjectState(TimedObject* self, s32* state)
{
    Vec02 delta;
    Collider** list;
    s32 count;
    if (g_player == 0) {
        return;
    }
    if (((s32 (*)(Player*, s32))((void**)g_player->desc)[79])(g_player, 2) != 0) {
        return;
    }
    Player* pl = g_player;
    if (IsPointInsideCollider(self, &pl->v140) == 0) {
        return;
    }
    if (pl == g_player && pl->f2220 == 6) {
        Vu0::Q(delta) = Vu0::Sub(Vu0::Q(pl->v140), Vu0::Q(self->v140));
        delta.z = 0.0f;
        Vu0::Q(delta) = Vu0::NormalizeOr(Vu0::Q(delta), Vu0::Q(g_unitXVector));
        switch (g_player->f239C) {
        case 3:
            return;
        case 0:
            if (0.0f < Vu0::ToFloat(Vu0::Dot(Vu0::Q(delta), Vu0::Q(g_player->m110.r[0])))) {
                return;
            }
            break;
        case 1:
            if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(delta), Vu0::Q(g_player->m110.r[0]))) < 0.0f) {
                return;
            }
            break;
        case 2:
            if (g_player->f2228 == 0x10) {
                return;
            }
            break;
        }
    }
    PushBackMemoryMark();
    Vec02* at = &pl->v140;
    GatherCollidersInBox(self->world, 0, at, &self->root->v140, IsSequencedObjectCandidate, self, &count, &list);
    if (FindNearestSpanObject(1, &self->v140, at, count, list, 0) == 0) {
        *state = self->f554 == 0 ? 2 : 6;
    }
    PopBackMemoryMark();
}

void SetSequencedObjectMode(SequencedObject* self, s32 value)
{
    s32 m = 5;
    self->f554 = value;
    if (!value) {
        m = 1;
    }
    self->desc30()->m4D(self, m);
}

void RequestSequencedObjectEnd(SequencedObject* self)
{
    if (self->state != 8) {
        self->desc30()->m4D(self, self->f554 == 0 ? 3 : 7);
    }
    StateTrigger* r = self->trigger;
    if (r != 0) {
        if (r->state == 1) {
            if (__builtin_fabsf(g_gameTime[0] - r->stateTime) < 0.2f) {
                self->f5C0 = r->state;
            }
        }
    }
}

void FinishSequencedObject(SequencedObject* o)
{
    if (o->f554 == 0) {
        o->f554 = 1;
        if (o->state != 8) {
            o->desc30()->m4D(o, 3);
        }
    }
}

void EnterSequencedObjectState(SequencedObject* self, s32 s)
{
    if (self->state != s) {
        switch (self->state) {
        case -1: case 0: case 1: case 2: case 3: case 4: case 5: case 7:
            break;
        case 6:
            EnterSequencedSubstate(self, -1);
            break;
        case 8:
            self->f5C0 = 0;
            break;
        }
        switch (s) {
        case 6:
            EnterSequencedSubstate(self, 0);
            break;
        case 0: case 1: case 2: case 3: case 4: case 5: case 7: case 8:
            break;
        }
        EnterTimedObjectState(self, s);
    }
}

void EnterSequencedSubstate(SequencedObject* self, s32 arg)
{
    if (self->state5D8 == arg) return;
    switch (self->state5D8) {
    case -1:
        break;
    case 0:
        break;
    case 1:
        StopSoundRecord(self->f5C4, 0);
        break;
    case 2:
        break;
    }
    switch (arg) {
    case -1:
        break;
    case 0:
        if (self->f200 != 0) {
            ((Record200*)self->f200)->f44 = 4;
        }
        break;
    case 1:
        StartSoundEffect(0x1B, &self->f5C4, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    case 2:
        if (self->f200 != 0) {
            ((Record200*)self->f200)->f44 = 0;
        }
        break;
    }
    self->state5D8 = arg;
    self->f5DC = g_gameTime[0];
}

void InitBlinkObject(BlinkObject* self)
{
    InitTimedObject(self);
    self->animB.first = -1;
    self->animB.last = -1;
    self->animC.first = -1;
    self->animC.last = -1;
    self->animA.first = -1;
    self->animA.last = -1;
    self->blinkFrame = -1;
}

void SetupBlinkObject(BlinkObject* self)
{
    StartPlacedObject(self);
    for (s32 i = 0; i < self->elemCount; i++) {
        Elem02* it = self->elems[i];
        if (it->kind == 1 && it->f14 != 0) {
            self->f610 = it;
            break;
        }
    }
    self->desc30()->m4D(self, self->f560);
}

void UpdateBlinkObject(BlinkObject* self)
{
    s32 state;

    UpdateTimedObject(self);
    state = self->state;
    switch (state) {
    case 0:
        if (self->f5B8 < g_gameTime[0] - self->f55C) {
            state = 1;
        }
        break;
    case 1:
        if (0.0f <= self->f608) {
            if (self->f608 < g_gameTime[0] - self->f55C) {
                state = 3;
                break;
            }
        }
        if (self->desc30()->m48 != 0) {
            self->desc30()->m48(self, &state);
        }
        break;
    case 3:
        if (self->f5BC < g_gameTime[0] - self->f55C) {
            state = 8;
        }
        break;
    case 4:
        if (self->f5B8 < g_gameTime[0] - self->f55C) {
            state = 5;
        }
        break;
    case 5:
        if (0.0f <= self->f608) {
            if (self->f608 < g_gameTime[0] - self->f55C) {
                state = 7;
                break;
            }
        }
        if (self->desc30()->m48 != 0) {
            self->desc30()->m48(self, &state);
        }
        break;
    case 7:
        if (self->f5BC < g_gameTime[0] - self->f55C) {
            state = 8;
        }
        break;
    case 8:
        if (self->f5C0 == 0) {
            if (self->f60C < g_gameTime[0] - self->f55C) {
                switch (self->f554) {
                case 0:
                    state = 0;
                    break;
                case 1:
                    state = 4;
                    break;
                }
            }
        }
        break;
    }
    self->desc30()->m4D(self, state);
    SetBlinkObjectFrame(self);
}

struct TouchQuery;
void* FillMemory(void* p, s32 value, s32 size);
// The 0x40-byte request frame FindNodeForQuery is handed for an object that is not the player:
// the object, what touched it, where that is and the direction (the unit z).
struct TouchQuery {
    void Init(BlinkObject* s, Collider* o, const Vec02* k);
    void* self;
    void* tgt;
    s32 pad8[6];
    Vec02 q20;
    Vec02 q30;
};

inline void TouchQuery::Init(BlinkObject* s, Collider* o, const Vec02* k)
{
    FillMemory(this, 0, 0x40);
    tgt = o;
    self = s;
    q20 = o->v140;
    q30 = *k;
}

s32 IsObjectInAcceptLists(BlinkObject* self, Collider* t);
void InitOwnerMessage(OwnerMessage* out, s32 a, BlinkObject* self);
PlacedObject *FindNodeForQuery(TouchQuery* p, s32 a, s32 b);

void ChooseBlinkObjectState(BlinkObject* self, s32* out)
{
    OwnerMessage buf;
    TouchQuery req;
    Collider* owner = (Collider*)self->root;
    s32 lastSide = 1;       // a contact has two ends: end[lastSide - x] is the other one
    ContactRow03* l = owner->contacts->head;
    if (l != 0) {
        do {
            Contact03* n = l->head;
            if (n != 0) {
                do {
                    s32 x = owner != n->end[0].body;
                    ContactEnd03* b = &n->end[lastSide - x];
                    ContactEnd03* a = &n->end[x];
                    Collider* o = b->body;
                    if (a->part == self && IsObjectInAcceptLists(self, o) != 0) {
                        if (self->f618 == 0) {
                            *out = self->f554 == 0 ? 2 : 6;
                        }
                        if ((u32)(*out - 5) < 2) {
                            if (o == g_player) {
                                InitOwnerMessage(&buf, 1, self);
                                if (g_player->desc05()->m4C(g_player, &buf) != 0) {
                                    StopTrackPlayer(self);
                                }
                            } else {
                                req.Init(self, o, &g_unitZVector);
                                FindNodeForQuery(&req, 0, 0);
                            }
                        }
                    }
                    n = n->next;
                } while (n != 0);
            }
            l = l->next;
        } while (l != 0);
    }
}

void SetBlinkObjectMode(BlinkObject* self, s32 mode)
{
    self->f554 = mode;
    self->desc30()->m4D(self, mode == 0 ? 1 : 5);
}

void RequestBlinkObjectEnd(BlinkObject* self)
{
    if (self->state != 8) {
        self->desc30()->m4D(self, self->f554 == 0 ? 3 : 7);
    }
    StateTrigger* r = self->trigger;
    if (r != 0) {
        if (r->state == 1) {
            if (__builtin_fabsf(g_gameTime[0] - r->stateTime) < 0.2f) {
                self->f5C0 = r->state;
            }
        }
    }
}

void FinishBlinkObject(BlinkObject* self)
{
    self->f554 = 1;
    if (self->f608 < 0.0f) {
        self->f618 = 0;
        switch (self->state) {
        case 1:
            self->desc30()->m4D(self, 3);
            break;
        case 5:
            self->desc30()->m4D(self, 7);
            break;
        }
    }
}

void EnterBlinkObjectState(BlinkObject* self, s32 n)
{
    if (self->state == n) return;
    switch (self->state) {
    case 1:
    case 5:
        StopSoundRecord(self->f5C4, 0);
        self->f614 = self->f55C;
        break;
    case 8:
        self->f5C0 = 0;
        self->f618 = 0;
        break;
    }
    switch (n) {
    case 1:
        StartSoundEffect(15, &self->f5C4, self, 0, 2000.0f, 500.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    case 2:
    case 6:
        self->f618 = 1;
        break;
    case 3:
    case 4:
    case 7:
        break;
    case 5:
        StartSoundEffect(27, &self->f5C4, self, 0, 2000.0f, 500.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    }
    EnterTimedObjectState(self, n);
    if (self->f618 != 0 && (n == 2 || n == 6)) {
        self->state = (n == 2) ? 1 : 5;
        self->f55C = self->f614;
    }
}

void SetBlinkObjectFrame(BlinkObject* self)
{
    s32 first, last, mode, frame;
    f32 duration, start;

    switch (self->state) {
    case 0:
    case 4:
    case 8:
        first = self->animA.first;
        last = self->animA.last;
        duration = self->animA.duration;
        mode = self->animA.mode;
        start = self->f55C;
        break;
    case 1:
        first = self->animB.first;
        last = self->animB.last;
        duration = self->animB.duration;
        mode = self->animB.mode;
        start = self->f55C;
        break;
    case 3:
        frame = (s32)((g_gameTime[0] - self->f55C) / (1.0f / self->blinkRate)) % 2;
        if (frame != 0) {
            first = self->animB.first;
            last = self->animB.last;
            duration = self->animB.duration;
            mode = self->animB.mode;
            start = self->f614;
        } else {
            first = self->blinkFrame;
            last = first;
        }
        break;
    case 7:
        frame = (s32)((g_gameTime[0] - self->f55C) / (1.0f / self->blinkRate)) % 2;
        if (frame != 0) {
            first = self->animC.first;
            last = self->animC.last;
            duration = self->animC.duration;
            mode = self->animC.mode;
            start = self->f614;
        } else {
            first = self->blinkFrame;
            last = first;
        }
        break;
    case 5:
        first = self->animC.first;
        last = self->animC.last;
        duration = self->animC.duration;
        mode = self->animC.mode;
        start = self->f55C;
        break;
    }

    s32 count = last - first + 1;
    if (count == 1 || duration <= 0.0f) {
        frame = first;
    } else {
        switch (mode) {
        case 0:
            frame = (s32)((g_gameTime[0] - start) / (duration / (f32)count)) % count;
            break;
        case 1: {
            s32 period = count * 2 - 2;
            frame = (s32)((g_gameTime[0] - start) / (duration / (f32)period)) % period;
            if (frame >= count)
                frame -= (frame - count + 1) * 2;
            break;
        }
        }
        frame += first;
    }
    SetCursorFrame((s32)self->f610 + 0x10, frame);
}
