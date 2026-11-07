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

ASM_FUNC(func_001AF108);

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

ASM_FUNC(func_001AF820);

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

INCLUDE_RODATA(jtbl_0024CFF0);
ASM_FUNC(func_001AFBB0);

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

INCLUDE_RODATA(jtbl_0024D070);
ASM_FUNC(func_001B0838);

s32 TestSequencedObjectMayContact() { return 1; }

s32 IsSequencedObjectCandidate(TimedObject* self, Collider* other)
{
    if ((other->flags538 & (1UL << 43)) != 0 || (s32)other->root == GetActiveSwitchedCollider() || other->root == self->root || IsObjectExcluded(self, other) != 0) {
        return 0;
    }
    s64 t = (s64)other->flagsHi;
    return ((s32)t ^ 1) & 1;
}

ASM_FUNC(func_001B0C68);

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
void FillMemory(TouchQuery* p, s32 zero, s32 size);
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
void FindNodeForQuery(TouchQuery* p, s32 a, s32 b);

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
                const Vec02* k = &g_unitZVector;
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
                                req.Init(self, o, k);
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
