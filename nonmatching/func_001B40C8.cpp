// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 126/184 (68.5%), checked 2026-11-07
// NEAR: order: the zero stores come out in another order than retail's; a random order search
//       reached 21 differing lines and was not kept.
#include "common.h"
#include "script_value.h"
#include "cursor_animator.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "collider.h"
#include "state_graph.h"
#include "camera_positioned_object.h"
#include "world.h"
#include "attachment.h"
#include "state_walker.h"
#include "globals.h"

void LoadAnimatorBase(CursorAnimator* self, const AnimatorParams* src);
void BindAnimatorRecord(CursorAnimator* self);
void SetCursorFrame(AnimCursor* cur, s32 idx);
void SetCursorCoords(AnimCursor* cur, f32 x, f32 y);
AnimRecord* FindAnimRecord(s32 key);
extern AnimCursor* g_lastPendingCursor;
extern AnimCursor* g_pendingCursors;

f32 RandomFloatInRange(f32 a, f32 b);

void BindFrameRunAnimator(FrameRunAnimator* p)
{
    BindAnimatorRecord(p);
    if (p->cursor.record != 0) {
        f32 a = RandomFloatInRange(p->durMin, p->durMax);
        p->rate = (f32)p->cursor.record->count / a;
        f32 b = RandomFloatInRange(p->waitMin, p->waitMax);
        p->wait0 = b;
        p->wait = b;
    }
}

f32 GetFrameRunProgress(FrameRunAnimator* p)
{
    return (p->pos / p->rate) / ((f32)p->cursor.record->count / p->rate + p->wait0);
}


void LoadFramePingPongAnimator(FramePingPongAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->durMin = s->f4;
    p->durMax = s->f8;
    p->waitMin = s->fC;
    p->waitMax = s->f10;
    p->pos = (f32)s->u14;
}

f32 GetFramePingPongProgress(FramePingPongAnimator* p)
{
    f32 x = p->rate;
    f32 a;
    if (x < 0.0f) {
        x = -x;
        a = (f32)(p->cursor.record->count << 1) - p->pos;
    } else {
        a = p->pos;
    }
    return (a / x) / ((f32)(p->cursor.record->count << 1) / x + p->wait0);
}


void LoadRandomJumpAnimator(RandomJumpAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->waitMin = s->f4;
    p->waitMax = s->f8;
}


void BindAngleFrameAnimator(AngleFrameAnimator* p)
{
    BindAnimatorRecord(p);
    if (p->cursor.record != 0) {
        s32 n = p->cursor.record->count;
        if (n >= 2) {
            p->step = p->sector / (f32)n;
        }
    }
}

struct FacingXY { f32 x; f32 y; };
struct PartFacingSource { u8 pad0[0x34]; s32 i34; };
struct DrawnPart {
    void* vt; u8 pad0[0xC]; FacingXY vec; u8 pad1[0x60]; PartFacingSource* p78;
};

extern u8 DrawModelPart[];
f32 ArctangentOfRatio(f32 a, f32 b);
f32 WrapModulo(f32 a, f32 b);

void FollowObjectAngle(AngleFrameAnimator* p, void* unused, DrawnPart* q)
{
    if (p->cursor.record == 0) {
        return;
    }
    if (p->cursor.record->count < 2) {
        return;
    }
    if (*(void**)q != (void*)DrawModelPart) {
        return;
    }
    FacingXY* vv;
    if (q->p78->i34 != 0) {
        vv = &q->vec;
    } else {
        vv = (FacingXY*)g_camera->g80;
    }
    f32 t = ArctangentOfRatio(vv->y, vv->x);
    f32 r = WrapModulo(p->phase - t, p->sector);
    s32 k = (s32)(r / p->step);
    SetCursorFrame(&p->cursor, k);
}

f32 FloatRemainder(f32 a, f32 b);

void StepScrollAnimator(ScrollAnimator* p, f32 t)
{
    if (p->cursor.record != 0) {
        f32 r1 = FloatRemainder(p->cursor.u + p->velU * p->mulU * t, p->wrapU);
        f32 r2 = FloatRemainder(p->cursor.v + p->velV * p->mulV * t, p->wrapV);
        SetCursorCoords(&p->cursor, r1, r2);
    }
}

void SetScrollScale(ScrollAnimator* p, f32 a, f32 b)
{
    p->mulU = a;
    p->mulV = b;
}


void SetCursorCoords(AnimCursor* a0, f32 a, f32 b)
{
    if (a0->record == 0) return;
    if (a0->u == a && a0->v == b) return;
    a0->u = a;
    AnimCursor* v = a0->next;
    a0->v = b;
    if (v != 0) return;
    if (a0 == g_lastPendingCursor) return;
    if (g_lastPendingCursor == 0) g_lastPendingCursor = a0;
    a0->next = g_pendingCursors;
    g_pendingCursors = a0;
}

extern f32 g_gameTime;

s32 ClaimAnimatorStep(CursorAnimator* a0)
{
    if (a0->stamp != g_gameTime) {
        a0->stamp = g_gameTime;
        return 1;
    }
    return 0;
}

struct Vec2_1B55A8 { f32 x; f32 y; };

void CopyVec2(Vec2_1B55A8* a0, Vec2_1B55A8* a1)
{
    a0->x = a1->x;
    a0->y = a1->y;
}

struct Walk_1B5D80 { s32 a; u32 b; u32 c; };

void BuildFreeList(Walk_1B5D80* s, s32 v, s32 n)
{
    u32 cur = s->b;
    s->a = v;
    s->c = cur;
    for (s32 i = 1; i < n; i++) {
        u32 prev = cur;
        s32 a = s->a;
        cur = s->b + i * a;
        *(u32*)prev = cur;
    }
    *(u32*)cur = 0;
}

void PushFreeSlot(Pool6C* list, Attachment* item)
{
    if (item) {
        item->vt = (const T2195_Vt*)list->head;
        list->head = item;
    }
}

u32 GetStateEntryKey(StateGraph* a0, s32 a1)
{
    a1 = (a1 << 3) + (u32)a0->f38;
    return *(u32*)a1;
}

struct Obj_1B65F8 {
    u8 pad0[0x24];
    void* f24;
    u8 pad1[0x10];
    f32 f38;
};

void SetAnimationPlayerSpeed(void* p);

void SetStateWalkerSpeed(Obj_1B65F8* self, f32 v)
{
    self->f38 = v;
    if (self->f24 != 0) {
        SetAnimationPlayerSpeed(self->f24);
    }
}

struct Slot_1B71C8 {
    void* first;
    s32 second;
};

struct Self_1B71C8 {
    u8 pad0[0xCD4];
    s32 count;
    u8 pad1[4];
    Slot_1B71C8 slots[1];
};

s32 IsObjectOfKind(void* a, s32 b);
s32 IsObjectDescendantOf(Collider* e, void* b);

s32 IsCompanionAgentBlocker(Self_1B71C8* self, Collider* ent)
{
    if (ent->flags538 & (1ULL << 43)) {
        return 0;
    }
    if (IsObjectOfKind(ent->root, 5) != 0) {
        return 0;
    }
    if (IsObjectOfKind(ent->root, 0x4C) != 0) {
        return 0;
    }
    for (s32 i = 0; i < self->count; i++) {
        if (IsObjectDescendantOf(ent, self->slots[i].first) != 0) {
            return 0;
        }
    }
    return 1;
}

void SetColliderFrozen(CompanionAgent* self, void* p);
void ReleaseSoundLevel(void* p);

void SetCompanionAgentFrozen(CompanionAgent* self, void* p)
{
    SetColliderFrozen(self, p);
    if (p != 0) {
        ReleaseSoundLevel(self->fCC0);
        self->fCC0 = 0;
    }
}

struct Entry_1B65C8 { s32 value; s32 extra; };
struct Host_1B65C8 { u8 pad[0x38]; Entry_1B65C8* entries; };
struct Node_1B65C8 { u8 pad[0x18]; Host_1B65C8* host; u8 pad2[0x2C - 0x1C]; s32 index; };

void GetStateWalkerNextKey(Node_1B65C8* self, s32* out)
{
    s32 value;
    if (self->index >= 0) {
        value = self->host->entries[self->index].value;
    } else {
        value = -1;
    }
    *out = value;
}

struct Node_1B6C68 {
    u8 pad[0x28];
    s32 f28;
    s32 index;
};

void NotifyStateWalkerChange(Node_1B6C68* self, s32 a, s32 b);

void CommitStateWalkerArrival(Node_1B6C68* self)
{
    NotifyStateWalkerChange(self, self->f28, self->index);
    s32 v = self->index;
    self->index = -1;
    self->f28 = v;
}

struct Node_1B6CA8 {
    u8 pad[0x24];
    s32 f24;
};

void CommitStateWalkerArrival(Node_1B6CA8* self);
void StartNextStateWalkerEdge(Node_1B6CA8* self);

void HandleStateWalkerTrackEnd(Node_1B6CA8* self, s32 a, s32 b)
{
    if (a == 5 && b == self->f24) {
        CommitStateWalkerArrival(self);
        StartNextStateWalkerEdge(self);
    }
}

typedef void (*VFn_1B6D78)(void* self);
struct Obj_1B6D78 { VFn_1B6D78* vtbl; };
typedef void (*Cb_1B6D78)(void* obj, s32 a, s32 b);
struct Link_1B6D78 {
    Cb_1B6D78 fn;
    void* obj;
    u8 pad[0x8];
    Link_1B6D78* next;
};
struct Node_1B6D78 {
    u8 pad[0x1C];
    Obj_1B6D78* f1C;
    u8 pad2[0x3C - 0x20];
    Link_1B6D78* f3C;
};

void CallStateWalkerListeners(Node_1B6D78* self, s32 a, s32 b)
{
    Obj_1B6D78* o = self->f1C;
    if (o != 0) {
        o->vtbl[18](o);
    }
    Link_1B6D78* link = self->f3C;
    if (link != 0) {
        do {
            void* obj = link->obj;
            Cb_1B6D78 fn = link->fn;
            link = link->next;
            fn(obj, a, b);
        } while (link != 0);
    }
}

struct Entry_1B6E28 { s32 value; s32 extra; };
struct Node_1B6E28 { u8 pad[0x18]; StateGraph* host; };

void TriggerScriptEvent(StateGraph* host, s32 a, s32 b, void** args);

void NotifyStateWalkerChange(Node_1B6E28* self, s32 idx1, s32 idx2)
{
    void* args[3];
    s32 v1;
    s32 v2;
    if (idx1 >= 0) {
        v1 = ((Entry_1B6E28*)self->host->f38)[idx1].value;
    } else {
        v1 = -1;
    }
    if (idx2 >= 0) {
        v2 = ((Entry_1B6E28*)self->host->f38)[idx2].value;
    } else {
        v2 = -1;
    }
    args[0] = &self;
    args[1] = &v1;
    args[2] = &v2;
    TriggerScriptEvent(self->host, 0xE, 3, args);
}


void SetCursorFrame(AnimCursor* a0, s32 a1)
{
    if (a0->record != 0) {
        s32 hi = a0->record->count - 1;
        if (a1 < 0) {
            a1 = 0;
        } else {
            a1 = (hi < a1) ? hi : a1;
        }
        if (a0->frame != a1) {
            AnimCursor* n = a0->next;
            a0->frame = a1;
            if (n == 0) {
                if (a0 != g_lastPendingCursor) {
                    if (g_lastPendingCursor == 0) {
                        g_lastPendingCursor = a0;
                    }
                    a0->next = g_pendingCursors;
                    g_pendingCursors = a0;
                }
            }
        }
    }
}


void SubmitMeshQueueEntry(void* p);

void FlushCursors(void)
{
    AnimCursor* n = g_pendingCursors;
    while (n != 0) {
        for (FrameLink* e = n->links; e != 0; e = e->next) {
            if (n->flags & 1) {
                e->dst->value = e->src->base + ((n->frame * e->src->stride) << 4);
            }
            SubmitMeshQueueEntry(e->dst);
        }
        AnimCursor* nx = n->next;
        n->next = 0;
        n = nx;
    }
    g_pendingCursors = 0;
    g_lastPendingCursor = 0;
}

extern s32 g_cursorAnimatorCount;
extern CursorAnimator** g_cursorAnimators;

s32 ClaimAnimatorStep(CursorAnimator* p);

void StepAnimators(f32 t)
{
    for (s32 i = 0; i < g_cursorAnimatorCount; i++) {
        CursorAnimator* o = g_cursorAnimators[i];
        if (ClaimAnimatorStep(o) != 0) {
            void (*fn)(CursorAnimator*, f32) = o->methods->step;
            if (fn != 0) {
                fn(o, t);
            }
        }
    }
}

s32 ReadBufferedU16(void* a);
s32 GetAnimatorSize(s32 type);
void* AllocateZeroedFrontMemory(s32 size);
void* GetAnimatorMethods(s32 type);
void ReadBufferedStreamBytes(void* owner, s32 key, void* out);

CursorAnimator* ReadAnimator(void* a0)
{
    s32 type = ReadBufferedU16(a0);
    CursorAnimator* result = 0;
    if (type != 0) {
        CursorAnimator* o = (CursorAnimator*)AllocateZeroedFrontMemory(GetAnimatorSize(type));
        void* vt = GetAnimatorMethods(type);
        o->type = type;
        o->methods = (const CursorAnimatorMethods*)vt;
        u32 buf[8];
        ReadBufferedStreamBytes(a0, 0x1C, buf);
        o->methods->load(o, (AnimatorParams*)buf);
        result = o;
    }
    return result;
}

struct Node_1B5EA0 { Node_1B5EA0* next; };
struct Pool_1B5EA0 { u8 pad[8]; Node_1B5EA0* head; };

void* PopFreeSlot(Pool_1B5EA0* pool)
{
    Node_1B5EA0* n = pool->head;
    if (n != 0) {
        pool->head = n->next;
    }
    return n;
}

struct Node_1B5EC0 { Node_1B5EC0* next; };
struct Pool_1B5EC0 { u8 pad[8]; Node_1B5EC0* head; };

void* PopFreeSlot(Pool_1B5EC0* pool);

void* TakePoolSlot(Pool_1B5EC0* pool)
{
    return PopFreeSlot(pool);
}

struct Node_1B5EE0 { Node_1B5EE0* next; };
struct Pool_1B5EE0 { s32 count; u8 pad[4]; Node_1B5EE0* head; };

void* PopFreeSlot(Pool_1B5EE0* pool);
void FillMemory(void* p, int zero, s32 count);

void* PopZeroedFreeSlot(Pool_1B5EE0* pool)
{
    void* p = PopFreeSlot(pool);
    FillMemory(p, 0, pool->count);
    return p;
}

void AddColliderToSweepAxes(void* owner, void* self);
Contacts03* TakeContactTable(void* owner, void* self);
void InitContactPairFlags(void* owner, void* self);
void AppendToList(void* p, void* self);
void RegisterPlacedObject(void* self);
void SetColliderPartListed(Collider* self, s32 flag);
void UpdateAnchorModeFlags(void* p);
void ResolveContactHandler(void* self);

void RegisterCollider(Collider* self)
{
    World* owner = self->world;
    owner->count34++;
    if (self->parent == 0) {
        AddColliderToSweepAxes(owner, self);
        self->contacts = TakeContactTable(owner, self);
        InitContactPairFlags(owner, self);
        owner->count38++;
        AppendToList(&owner->bodies, self);
    }
    RegisterPlacedObject(self);
    SetColliderPartListed(self, 1);
    self->desc03()->m44(self);
    if (!(self->flags538 & (1ULL << 54))) {
        UpdateAnchorModeFlags(self->root03());
    } else {
        UpdateAnchorModeFlags(self);
    }
    ResolveContactHandler(self);
}

void UnregisterPlacedObject(void* self);
void RemoveColliderFromSweepAxes(void* owner, void* self);
void ReleaseContactTable(void* owner, Contacts03* contacts);
void RemoveFromList(void* p, void* self);
void FreeTouchNodes(void* owner, Touch03* list);

void UnregisterCollider(Collider* self)
{
    Collider* old50 = self->root03();
    World* owner = self->world;
    SetColliderPartListed(self, 0);
    UnregisterPlacedObject(self);
    owner->count34--;
    if (self->parent == 0) {
        RemoveColliderFromSweepAxes(owner, self);
        ReleaseContactTable(owner, self->contacts);
        owner->count38--;
        RemoveFromList(&owner->bodies, self);
    }
    FreeTouchNodes(owner, self->touching);
    u64 flags = self->flags538;
    self->touching = 0;
    if (!(flags & (1ULL << 54)) && old50 != self) {
        UpdateAnchorModeFlags(old50);
    }
}

void ClearRootObjectStateBits(void* owner, void* self, s32 n);

void SetColliderPartListed(Collider* self, s32 flag)
{
    if (flag == ((self->flags538 >> 50) & 1)) {
        return;
    }
    if (flag != 0) {
        AppendToList(&self->root03()->parts, self);
    } else {
        RemoveFromList(&self->root03()->parts, self);
    }
    self->flags538 = (self->flags538 & ~(1ULL << 50)) | ((u64)(flag & 1) << 50);
    ClearRootObjectStateBits(self->world, self, 7);
    Collider* sub = self->root03();
    sub->desc03()->m32(sub);
}

void LoadAnimatorBase(CursorAnimator* self, const AnimatorParams* src)
{
    s32 old = self->cursor.flags;
    self->recordKey = src->recordKey;
    self->cursor.flags = old | 1;
    if (src->flag != 0) {
        self->cursor.flags = old | 5;
    }
}


void BindAnimatorRecord(CursorAnimator* self)
{
    if (self->cursor.record == 0) {
        self->cursor.record = FindAnimRecord(self->recordKey);
    }
}

f32 GetAnimatorZeroProgress(void)
{
    return 0.0f;
}

AnimCursor* FindAnimatorCursor(CursorAnimator* self, const AnimRecord* key)
{
    if (key->key == self->recordKey) {
        return &self->cursor;
    }
    return 0;
}


void StartObject(void* self);
void SpawnInitialStateWalker(void* self);
void AppendQueuedCall(void* owner, void* fn, void* arg, s32 a3, s32 a4);

void StartStateGraph(StateGraph* self)
{
    StartObject(self);
    if (self->armed != 0) {
        AppendQueuedCall(self->world, (void*)SpawnInitialStateWalker, self, 0, 0);
    }
}

struct Pair_1B63C0 {
    s32 key_00;
    s32 value_04;
};

s32 FindStateEntryIndex(StateGraph* self, s32 key)
{
    s32 count = self->f34;
    if (count > 0) {
        Pair_1B63C0* p = (Pair_1B63C0*)self->f38;
        s32 i = 0;
        do {
            if (p->key_00 == key) {
                return i;
            }
            i++;
            p++;
        } while (i < count);
    }
    return -1;
}


void LoadFrameRunAnimator(FrameRunAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->durMin = s->f4;
    p->durMax = s->f8;
    p->waitMin = s->fC;
    p->waitMax = s->f10;
    p->pos = (f32)s->u14;
}

f32 RandomFloatInRange(f32 a, f32 b);
f32 WrapModulo(f32 a, f32 b);

void StepFrameRunAnimator(FrameRunAnimator* p, f32 dt)
{
    if (p->cursor.record == 0) {
        return;
    }
    if (p->cursor.record->count < 2) {
        return;
    }
    if (p->wait > 0.0f) {
        p->wait = p->wait - dt;
        return;
    }
    p->pos = p->pos + p->rate * dt;
    if ((f32)p->cursor.record->count <= p->pos) {
        f32 a = RandomFloatInRange(p->durMin, p->durMax);
        p->rate = (f32)p->cursor.record->count / a;
        f32 b = RandomFloatInRange(p->waitMin, p->waitMax);
        p->wait0 = b;
        p->wait = b;
    }
    f32 t = WrapModulo(p->pos, (f32)p->cursor.record->count);
    p->pos = t;
    SetCursorFrame(&p->cursor, (s32)t);
}

s32 FindStateEntryIndex(void* self, s32 key);

s32 FindStateEntryIndexOrZero(void* self, s32 key)
{
    s32 r = FindStateEntryIndex(self, key);
    return r < 0 ? 0 : r;
}

struct Reg_001B6438 { u8 pad0[0x1B88]; };
struct Owner_001B6438 { u8 pad0[0x14]; Reg_001B6438* reg_14; };
struct Obj_001B6438 {
    u8 pad0[0x18];
    Owner_001B6438* owner_18;
    u8 pad1[0x24 - 0x1C];
    void* handle_24;
    u8 pad2[0x3C - 0x28];
    void* ptr_3C;
};

void StopAnimationPlayer(void* p);
void ReleaseCallRecords(void* a, void* b);
void RemoveFromList(void* a, void* b);
void PushFreeSlot(void* a, void* b);
void TriggerScriptEvent(void* a, s32 b, s32 c, s32 d);

void DestroyStateWalker(Obj_001B6438* self)
{
    Owner_001B6438* owner = self->owner_18;
    if (self->handle_24 != 0) {
        StopAnimationPlayer(self->handle_24);
        self->handle_24 = 0;
    }
    ReleaseCallRecords(self->owner_18->reg_14, self->ptr_3C);
    self->ptr_3C = 0;
    RemoveFromList((u8*)self->owner_18 + 0x48, self);
    RemoveFromList((u8*)self->owner_18->reg_14 + 0x1B94, self);
    PushFreeSlot((u8*)self->owner_18->reg_14 + 0x1B88, self);
    TriggerScriptEvent(owner, 0x12, 0, 0);
}

struct Vec3_1B5588 { f32 x; f32 y; f32 z; };

void CopyVec3(Vec3_1B5588* dst, Vec3_1B5588* src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

void SetListLinkOffset(void* self, s32 value);
void InitPlacedObject(void* self);
void ClearRecordBody(Mesh03* mesh);
void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
s32 LookupScriptVariable(void* a, s32 b, s32 c, ScriptValue* d);
void ResolveContactHandler(void* self);

void InitCollider(Collider* self)
{
    ScriptValue local;
    s32 s0;
    InitScriptValue(&local);
    SetListLinkOffset(&self->parts, 0x2E4);
    InitPlacedObject(self);
    ClearRecordBody(&self->mesh);
    self->meshCopy = self->mesh;
    if (self->parent != 0) {
        SetColliderAnchors(self, 3, 0, 3, 0);
    }
    self->f4BC = -1;
    self->index = -1;
    if (self->f2C != 0) {
        s0 = LookupScriptVariable(self->f2C, 6, 1, &local);
        s0 |= LookupScriptVariable(self->f2C, 7, 1, &local);
        if (s0 != 0) {
            self->flags538 |= (u64)0x8000 << 48;
        }
    }
    self->gravity = self->world->gravity;
    ResolveContactHandler(self);
    DestroyScriptValue(&local, 2);
}

struct __attribute__((aligned(16))) Quad_001B4580 { f32 v[4]; };

void ConvertHsvToRgb(Quad_001B4580* p);

void ConvertHsv255ToRgb255(Quad_001B4580* src, f32* dst)
{
    Quad_001B4580 tmp = *src;
    tmp.v[1] = tmp.v[1] * 0.003921569f;
    tmp.v[2] = tmp.v[2] * 0.003921569f;
    ConvertHsvToRgb(&tmp);
    dst[0] = dst[0] * 255.0f;
    dst[1] = dst[1] * 255.0f;
    dst[2] = dst[2] * 255.0f;
}

struct Slot_1B70B0 { s32 value; s32 pad4; };
struct Self_1B70B0 { u8 pad0[0xC38]; Slot_1B70B0 slots[1]; };

s32 IsAgentSlotIndex(s32 index);

void SetCompanionAgentLookId(Self_1B70B0* self, s32 index, s32 value)
{
    (void)IsAgentSlotIndex(index);
    self->slots[index].value = value;
}


void AddCompanionAgentExcludedId(CompanionAgent* self, s32 value)
{
    s32 n = self->fCD4;
    if ((u32)n < 4) {
        self->fCD8[n].id = value;
        n++;
        self->fCD4 = n;
    }
}

f32 GetScrollProgress(ScrollAnimator* p) { f32 result=0.0f; if (p->velU != 0.0f) result=(p->cursor.u/p->wrapU)*0.5f; else result=0.5f; if (p->velV != 0.0f) result += (p->cursor.v/p->wrapV)*0.5f; else result += 0.5f; return result; }

void GetTriangleOutputs(TriangleAnimator* self, void** out) { out[0] = &self->out44; out[1] = &self->out4C; out[2] = &self->out48; }

void StartPlacedObject(void* self);

void StartCameraPositionedObject(CameraPositionedObject* self)
{
    StartPlacedObject(self);
    self->flags = (self->flags & 0xFFFFFCFFFFFFFFFFULL) | 0x10000000000ULL;
}

struct Walk_1B5DD0 { s32 a; void* b; s32 c; };

void* AllocateFrontMemory(s32 size);
void BuildFreeList(void* s, s32 v, s32 n);

void InitSlotPool(Walk_1B5DD0* s, s32 size, s32 count)
{
    s32 stride = (size + 7) & ~7;
    s->b = AllocateFrontMemory(stride * count);
    BuildFreeList(s, stride, count);
}

struct Walk_1B5E30 { s32 a; void* b; s32 c; };

void* AllocateFrontMemory(s32 size);
void BuildFreeList(void* s, s32 v, s32 n);

void InitAlignedSlotPool(Walk_1B5E30* s, s32 size, s32 count)
{
    s32 addr = (s32)AllocateFrontMemory(size * count + 0x30);
    s->b = (void*)((addr + 0x3F) & -0x40);
    BuildFreeList(s, size, count);
}

struct Node_1B6388 {
    u8 pad0[0x8];
    Node_1B6388* next;
    u8 pad1[0x10];
    s32 key;
};

struct Owner_1B6388 {
    u8 pad0[0x48];
    Node_1B6388* head;
};

void* FindListNodeByKey(Owner_1B6388* self, s32 key)
{
    ListFrame frame;
    Node_1B6388* node = self->head;
    if (node != 0) {
        do {
            if (node->key == key) {
                return node;
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}

struct Holder_1B6DF8 {
    u8 pad0[0x14];
    void* ptr;
};

struct Self_1B6DF8 {
    u8 pad0[0x18];
    Holder_1B6DF8* holder;
};

void AddCallbackNode(void* a, void* b, s32 c, void* d);

void AddStateWalkerListener(Self_1B6DF8* self, PlacedObject** p)
{
    AddCallbackNode(self->holder->ptr, (u8*)self + 0x3C, (s32)(*p)->link40.prev, p);
}

struct Pair_1B7128 {
    s32 key;
    s32 value;
};

void StartAgent(void* self);
void ResolveCompanionAgentObjects(void* self);
s32 FindFirstObjectByIdMode4(void* host, s32 id, void* ctx);
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);

void StartCompanionAgent(CompanionAgent* self)
{
    StartAgent(self);
    ResolveCompanionAgentObjects(self);
    if (self->fC28 != -1) {
        self->fC2C = FindFirstObjectByIdMode4(self->world, self->fC28, self);
    }
    if (self->fCD4 > 0) {
        s32 i = 0;
        Pair_1B7128* p = (Pair_1B7128*)self->fCD8;
        do {
            p->value = FindFirstObjectById(self->world, 0x104, p->key, self);
            p++;
            i++;
        } while (i < self->fCD4);
    }
}

void UpdateAgent(void* self);
void AimCompanionAgentPose(void* self);

void UpdateCompanionAgent(CompanionAgent* self)
{
    UpdateAgent(self);
    AimCompanionAgentPose(self);
}

typedef void (*VFn_1B7790)(void* self);
struct Sub_1B7790 { VFn_1B7790* vtbl; };
void EnterAgentState(void* self);
void ReleaseSoundLevel(void* p);

void EnterCompanionAgentState(CompanionAgent* self)
{
    EnterAgentState(self);
    switch (self->f724) {
    case 6:
        self->fCC4 = 0;
        break;
    case 0xB: {
        Sub_1B7790* p = ((Sub_1B7790*)self->fC14);
        if (p != 0) {
            p->vtbl[7](p);
        }
        ReleaseSoundLevel(self->fCC0);
        self->fCC0 = 0;
        break;
    }
    }
    self->fC30 = *(s32*)((u8*)self + (self->f724 << 3) + 0xC3C);
}

typedef s32 (*VFn_1B7818)(void* self);

s32 IsAgentTargetInRange(void* self);

s32 IsCompanionAgentTargetInRange(CompanionAgent* self)
{
    if (IsAgentTargetInRange(self) == 0) {
        return 0;
    }
    return ((VFn_1B7818*)self->desc)[91](self);
}

void HandleAgentNotification(void* self, s32 code, void* req);

void HandleCompanionAgentNotification(CompanionAgent* self, s32 code, void* req)
{
    HandleAgentNotification(self, code, req);
    if (code == 7) {
        if (req == self->f7E0) {
            self->fCC4++;
        }
    }
}

f32 RandomFloatInRange(f32 a, f32 b);

void BindFramePingPongAnimator(FramePingPongAnimator* p)
{
    BindAnimatorRecord(p);
    if (p->cursor.record != 0) {
        f32 a = RandomFloatInRange(p->durMin, p->durMax);
        p->rate = (f32)(p->cursor.record->count * 2) / a;
        f32 b = RandomFloatInRange(p->waitMin, p->waitMax);
        p->wait0 = b;
        p->wait = b;
    }
}

f32 RandomFloatInRange(f32 a, f32 b);

void StepFramePingPongAnimator(FramePingPongAnimator* p, f32 dt)
{
    AnimRecord* d = p->cursor.record;
    if (d == 0) return;
    if (d->count < 2) return;
    if (0.0f < p->wait) {
        p->wait = p->wait - dt;
        return;
    }
    f32 prod = p->rate * dt;
    f32 sum = p->pos + prod;
    p->pos = sum;
    if ((f32)d->count <= sum) {
        p->pos = sum - prod;
        p->rate = -p->rate;
    }
    if (p->pos < 0.0f) {
        p->pos = 0.0f;
        f32 a = RandomFloatInRange(p->durMin, p->durMax);
        p->rate = (f32)(p->cursor.record->count * 2) / a;
        f32 b = RandomFloatInRange(p->waitMin, p->waitMax);
        p->wait0 = b;
        p->wait = b;
    }
    SetCursorFrame(&p->cursor, (s32)p->pos);
}

extern f32 g_gameTime;
f32 WrapAngle(f32 a);
void ComputeSinCos(f32 angle, f32* a, f32* b);

void StepCircleAnimator(CircleAnimator* self)
{
    if (self->cursor.record != 0) {
        f32 t[2];
        f32 ang = WrapAngle(g_gameTime * self->omega);
        ComputeSinCos(ang, &t[0], &t[1]);
        t[0] = t[0] * self->radius + self->centerU;
        t[1] = t[1] * self->radius + self->centerV;
        SetCursorCoords(&self->cursor, t[0], t[1]);
    }
}

extern f32 g_gameTime;
f32 WrapModulo(f32 x, f32 y);

f32 GetCircleProgress(CircleAnimator* p)
{
    f32 a = WrapModulo(g_gameTime * p->omega, 6.2831855f);
    return a * 0.15915494f;
}


void LoadTriangleAnimator(TriangleAnimator* self, AnimatorParams* src)
{
    LoadAnimatorBase(self, src);
    s32 fl = self->cursor.flags;
    self->u0 = src->f4;
    self->v0 = src->f8;
    self->du1 = src->fC - src->f4;
    self->du2 = src->f10 - src->f4;
    self->dv1 = src->f14 - src->f8;
    f32 d = src->f18 - src->f8;
    self->cursor.flags = (fl & -2) | 2;
    self->dv2 = d;
}

void UpdatePlacedObject(void* self);


void MoveObjectToCamera(CameraPositionedObject* self)
{
    UpdatePlacedObject(self);
    Vec02* src = (Vec02*)g_camera->f40;
    Vec02 q = *src;
    if (self->followHeight == 0) {
        q.z = self->v140.z;
    }
    self->desc02()->m1D(self, &q);
}

void InitAgent(void* self);

struct Ent_1B6EC8 { s32 v; s32 pad; };
void InitCompanionAgent(CompanionAgent* self)
{
    InitAgent(self);
    self->fC20 = 2000.0f;
    self->fC18 = 300.0f;
    self->fC1C = 300.0f;
    self->fC24 = 300.0f;
    self->fC28 = -1;
    self->fC2C = 0;
    s32 i = 16;
    Ent_1B6EC8* e = (Ent_1B6EC8*)((u8*)self + 0xCB8);
    do {
        e->v = -1;
        i--;
        e--;
    } while (i >= 0);
    self->fC10 = -1;
}


void LoadCircleAnimator(CircleAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->omega = s->f4; p->radius = s->f8; p->centerU = s->fC; p->centerV = s->f10; p->cursor.flags = (p->cursor.flags & ~1) | 2;
}

extern f32 g_gameTime;

s32 AnswerCompanionAgentRosterPoll(CompanionAgent* self)
{
    s32 r;
    if (self->f724 == 11) {
        goto ret1;
    }
    if (self->f724 != 6) {
        goto ret0;
    }
    if (self->fCC4 <= 0) {
        goto ret0;
    }
    if (5.0f < g_gameTime - self->f728) {
        r = 2;
        return r;
    }
ret1:
    return 1;
ret0:
    r = 0;
    return r;
}

extern s32 g_animRecordCount;
extern AnimRecord* g_animRecords;

AnimRecord* FindAnimRecord(s32 key)
{
    if (key == -1) {
        return 0;
    }
    s32 i = 0;
    if (i < g_animRecordCount) {
        AnimRecord* p = g_animRecords;
        do {
            if (p->key == key) {
                return p;
            }
            i++;
            p++;
        } while (i < g_animRecordCount);
    }
    return 0;
}

struct Item_1B61F0 {
    u8 pad_00[0x40];
    s32 value_40;
};

struct Slot_1B61F0 {
    Item_1B61F0* item_00;
    s32 pad_04[4];
};

struct Bank_1B61F0 {
    u8 pad_00[0x14];
    void* owner_14;
    u8 pad_18[0x24];
    s32 count_3C;
    Slot_1B61F0* slots_40;
};

s32 FindFirstObjectByIdMode4(void* owner, s32 value, void* bank);
void CreateStateWalker(void* bank, s32 r, s32 minus_one, s32 zero);

void SpawnInitialStateWalker(Bank_1B61F0* self)
{
    s32 i = 0;
    s32 n = self->count_3C;
    Item_1B61F0* e = 0;
    if (n > 0) {
        Slot_1B61F0* p = self->slots_40;
        do {
            e = p->item_00;
            i++;
            p++;
        } while (i < n && e == 0);
    }
    s32 r;
    if (self->count_3C > 0 && e != 0 && e->value_40 != -1) {
        r = FindFirstObjectByIdMode4(self->owner_14, e->value_40, self);
    } else {
        r = 0;
    }
    CreateStateWalker(self, r, -1, 0);
}

void LoadScrollAnimator(ScrollAnimator* p, AnimatorParams* s)
{
    LoadAnimatorBase(p, s);
    p->velU = s->f4;
    p->velV = s->f8;
    p->wrapU = s->fC;
    p->wrapV = s->f10;
    p->mulV = 1.0f;
    p->mulU = 1.0f;
    p->cursor.flags = (p->cursor.flags & ~1) | 2;
}

u16 MapCharToCode(u8 ch);
s32 GetStringLength(void* p);

void ConvertStringToCharCodes(u8* src, u16* dst)
{
    s32 n = GetStringLength(src);
    s32 i;
    for (i = 0; i < n; i++) {
        u32 r = MapCharToCode(src[i]);
        u32 lo = (r & 0xFF) << 8;
        u32 hi = (r >> 8) & 0xFF;
        dst[i] = (u16)(hi | lo);
    }
    dst[i] = 0;
}

struct Inner_1B6CF0 { u8 pad[0x34]; f32 f34; };
struct Item_1B6CF0 {
    u8 pad[0x8];
    Inner_1B6CF0* inner;
    u8 pad2[0x14 - 0x0C];
    f32 f14;
};
struct Node_1B6CF0 { u8 pad[0x24]; s32 f24; };

f32 CommitStateWalkerArrival(Node_1B6CF0* self);
void StartNextStateWalkerEdge(Node_1B6CF0* self);
void SeekAnimationPlayer(void* a, f32 b, f32 c, s32 d);

void AdvanceStateWalkerTime(Node_1B6CF0* self, f32 t)
{
    f32 rem = t;
    Item_1B6CF0* item = (Item_1B6CF0*)self->f24;
    while (item) {
        f32 diff = item->inner->f34 - item->f14;
        if (rem < diff) {
            SeekAnimationPlayer(item, rem, 1.0f, 1);
            break;
        }
        rem = rem - diff;
        (void)CommitStateWalkerArrival(self);
        StartNextStateWalkerEdge(self);
        item = (Item_1B6CF0*)self->f24;
    }
}

f32 RandomFloatInRange(f32 a, f32 b);

void LoadAngleFrameAnimator(AngleFrameAnimator* self, AnimatorParams* key)
{
    LoadAnimatorBase(self, key);
    self->phase = key->f4;
    f32 d = (f32)(u32)key->i8;
    f32 q = 6.2831855f / d;
    self->sector = q;
    if (self->phase == 3.4028234663852886e+38f) {
        self->phase = RandomFloatInRange(0.0f, q);
    }
}

struct Entry_001B6568 {
    s32 value;
    s32 extra;
};
struct Sub_001B6568 {
    u8 pad0[0x38];
    Entry_001B6568* table;
};
void GetStateWalkerTargetKey(StateWalker* a0, s32* out) {
    s32 idx = a0->index;
    s32 v;
    if (idx >= 0) {
        v = ((Sub_001B6568*)a0->owner)->table[idx].value;
    } else {
        v = -1;
    }
    *out = v;
}

struct Entry_001B6598 {
    s32 value;
    s32 extra;
};
struct Sub_001B6598 {
    u8 pad0[0x38];
    Entry_001B6598* table;
};
struct Ctx_001B6598 {
    u8 pad0[0x18];
    Sub_001B6598* sub;
    u8 pad1[0x28 - 0x1C];
    s32 index;
};

void GetStateWalkerCurrentKey(Ctx_001B6598* a0, s32* out) {
    s32 idx = a0->index;
    s32 v;
    if (idx >= 0) {
        v = a0->sub->table[idx].value;
    } else {
        v = -1;
    }
    *out = v;
}

s32 FindStateEntryIndexOrZero(void* self, s32 key);
void NotifyStateWalkerChange(StateWalker* self, s32 a, s32 b);
void StartNextStateWalkerEdge(StateWalker* self);

void TeleportStateWalker(StateWalker* self, s32 key)
{
    s32 s1 = FindStateEntryIndexOrZero(self->owner, key);
    if (self->f28 == s1) {
        s32 v = self->index;
        if (v == s1 || v == -1) {
            return;
        }
    }
    NotifyStateWalkerChange(self, self->f28, s1);
    self->index = s1;
    self->f28 = s1;
    self->f2C = -1;
    StartNextStateWalkerEdge(self);
}

struct Flags_1B64D8 { u8 pad0[0xC]; s32 flags; };
struct Node_1B64D8 {
    u8 pad0[0x18];
    void* f18;
    u8 pad1[0x24 - 0x1C];
    void* f24;
    u8 pad2[0x30 - 0x28];
    s32 f30;
    Flags_1B64D8* f34;
};

s32 FindStateEntryIndexOrZero(StateGraph* self, s32 key);
void CommitStateWalkerArrival(Node_1B64D8* self);
void StopAnimationPlayer(AnimationPlayer* obj);
void StartNextStateWalkerEdge(Node_1B64D8* self);

void SetStateWalkerTarget(Node_1B64D8* self, s32 key)
{
    s32 v;
    if (key != -1) {
        v = FindStateEntryIndexOrZero((StateGraph*)self->f18, key);
    } else {
        v = -1;
    }
    if (v != self->f30) {
        self->f30 = v;
        Flags_1B64D8* p = self->f34;
        if (p != 0 && (p->flags & 2)) {
            CommitStateWalkerArrival(self);
            StopAnimationPlayer((AnimationPlayer*)self->f24);
            self->f24 = 0;
        }
        if (self->f24 == 0) {
            StartNextStateWalkerEdge(self);
        }
    }
}

extern const ClassHead g_stateWalkerMethods;
extern const u8 D_00217410[];

void* PopZeroedFreeSlot(Pool6C* pool);
void AppendToList(List01* list, StateWalker* item);
s32 FindStateEntryIndexOrZero(StateGraph* self, s32 key);
void NotifyStateWalkerChange(StateWalker* self, s32 a, s32 b);
void StartNextStateWalkerEdge(StateWalker* self);
void TriggerScriptEvent(StateGraph* self, s32 a, s32 b, void* c);

StateWalker* CreateStateWalker(StateGraph* self, s32 a1, s32 a2, s32 a3)
{
    StateWalker* obj = (StateWalker*)PopZeroedFreeSlot(&self->world->pool1B88);
    obj->f1C = a1;
    obj->vt = (void*)&g_stateWalkerMethods;
    obj->f20 = a3;
    obj->f38 = 1.0f;
    obj->owner = self;
    obj->f2C = -1;
    AppendToList(&self->world->list1B94, obj);

    AppendToList((List01*)((u8*)self + 0x48), obj);
    if (a2 != -1) {
        s32 v = FindStateEntryIndexOrZero(self, a2);
        obj->f28 = v;
        obj->index = v;
        NotifyStateWalkerChange(obj, -1, v);
    }
    StartNextStateWalkerEdge(obj);
    StateWalker** pp = &obj;
    TriggerScriptEvent(self, 0x11, 1, (void*)&pp);
    return obj;
}

s32 GetAnimatorSize(s32 k)
{
    switch (k) {
    case 1:
    case 2:
        return 0x4C;
    case 3:
    case 4:
        return 0x38;
    case 5:
        return 0x78;
    case 6:
        return 0x44;
    case 7:
        return 0x3C;
    case 8:
        return 0x50;
    }
    return 0;
}

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table g_frameRunAnimatorMethods[];
extern const Fn_Table g_framePingPongAnimatorMethods[];
extern const Fn_Table g_randomJumpAnimatorMethods[];
extern const Fn_Table g_angleFrameAnimatorMethods[];
extern u8 g_crossfadeAnimatorMethods[];
extern const Fn_Table g_scrollAnimatorMethods[];
extern const Fn_Table g_circleAnimatorMethods[];
extern const Fn_Table g_triangleAnimatorMethods[];

void* GetAnimatorMethods(s32 n)
{
    switch (n) {
    case 1: return ((u8*)g_frameRunAnimatorMethods);
    case 2: return ((u8*)g_framePingPongAnimatorMethods);
    case 3: return ((u8*)g_randomJumpAnimatorMethods);
    case 4: return ((u8*)g_angleFrameAnimatorMethods);
    case 5: return g_crossfadeAnimatorMethods;
    case 6: return ((u8*)g_scrollAnimatorMethods);
    case 7: return ((u8*)g_circleAnimatorMethods);
    case 8: return ((u8*)g_triangleAnimatorMethods);
    }
    return 0;
}

struct Hdr_1B6F50;
struct Elem_1B6F50;
struct Sub_1B6F50 { u8 p0[0x11]; u8 f11; u8 p1[0x0A]; s32 f1C; u8 p2[0x60]; s32 f80; s32 f84; };
typedef void (*VFn_1B6F50)(void* self);
struct Elem_1B6F50 { VFn_1B6F50* vtbl; };
struct Ent_1B6F50 { s32 key; void* val; };
extern u8 D_0021A790[];
void* FindFirstObjectByIdMode4(Hdr_1B6F50* obj, s32 id, CompanionAgent* flags);
s32 GatherObjectsById(Hdr_1B6F50* a0, s32 a1, s32 a2, CompanionAgent* a3, s32 a4, void* a5);
s32 MatchesObjectId(Elem_1B6F50* a, s32 b);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(u32 bytes);
void* CreatePoseSource(Hdr_1B6F50* root, s32 value, void* table);
void InsertAttachment(Hdr_1B6F50* self, void* src);

void ResolveCompanionAgentObjects(CompanionAgent* self)
{
    s32 best = -1;
    s32 j = 16;
    Ent_1B6F50* e = (Ent_1B6F50*)self->fC38;
    do {
        s32 key = e->key;
        if (key == best) {
            e->val = 0;
        } else {
            e->val = FindFirstObjectByIdMode4((Hdr_1B6F50*)self->world, key, self);
        }
        e++;
        j--;
    } while (j >= 0);

    PushBackMemoryMark();
    best = 0;
    s32 count = GatherObjectsById((Hdr_1B6F50*)self->world, 0x201, 0x60, self, 0, 0);
    Elem_1B6F50** list = (Elem_1B6F50**)AllocateBackMemory(count << 2);
    count = GatherObjectsById((Hdr_1B6F50*)self->world, 0x201, 0x60, self, count, list);
    if (count > 0) {
        do {
            if (MatchesObjectId(*list, self->fC10) != 0) {
                best = (s32)*list;
            } else {
                (*list)->vtbl[7](*list);
            }
            list++;
            count--;
        } while (count != 0);
    }
    self->fC14 = (void*)best;
    PopBackMemoryMark();
    if (self->fC14 != 0) {
        self->fC34 = CreatePoseSource((Hdr_1B6F50*)self->world, (s32)self->fC14, D_0021A790);
        ((Sub_1B6F50*)self->fC34)->f11 = 2;
        ((Sub_1B6F50*)self->fC34)->f1C = 1;
        ((Sub_1B6F50*)self->fC34)->f84 = ((Sub_1B6F50*)self->fC34)->f80 = 0;
        InsertAttachment((Hdr_1B6F50*)self->fC14, self->fC34);
        self->fBF0 = (s32)self->fC14;
    }
}

extern f32 D_002746A0[8];

struct Quad_1B7638 {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} __attribute__((aligned(16)));

struct Sub_1B7638 {
    u8 pad0[0x2F0];
    f32 f2F0;
};

struct Target_1B7638 {
    u8 pad0[0x24];
    void *field24;
    u8 pad1[0x30 - 0x28];
    struct Quad_1B7638 quad30;
};


s32 GetAgentRosterState(CompanionAgent *self);
s32 IsAgentFacingBlocked(CompanionAgent *self);

void AimCompanionAgentPose(CompanionAgent *self) {
    struct Target_1B7638 *t;
    s32 r;
    s32 res;
    f32 f;

    if (self->fC14 == 0) {
        return;
    }
    t = (struct Target_1B7638 *)self->fC34;
    r = GetAgentRosterState(self);
    switch (r) {
    case 0:
    case 1:
        if ((void *)self->fC30 != 0) {
            t->field24 = (void *)self->fC30;
            t->quad30 = *(struct Quad_1B7638 *)&D_00248D30;
        } else {
            t->field24 = self;
            t->quad30 = *(struct Quad_1B7638 *)D_002746A0;
        }
        f = 1.3f;
        if (r == 0) {
            f = 1.0f;
        }
        break;
    case 2:
        if ((void *)self->fC30 != 0) {
            t->field24 = (void *)self->fC30;
            t->quad30 = *(struct Quad_1B7638 *)&D_00248D30;
        } else if (IsAgentFacingBlocked(self) != 0) {
            t->field24 = self;
            t->quad30 = *(struct Quad_1B7638 *)D_002746A0;
        } else {
            res = (s32)self->desc08()->m62(self);
            if (res != 0) {
                t->field24 = (void *)res;
                t->quad30 = *(struct Quad_1B7638 *)&D_00248D30;
            } else {
                t->field24 = self;
                t->quad30 = *(struct Quad_1B7638 *)D_002746A0;
            }
        }
        f = 1.3f;
        break;
    case 3:
        t->field24 = self;
        t->quad30 = *(struct Quad_1B7638 *)D_002746A0;
        f = 0.1f;
        break;
    }
    ((struct Sub_1B7638 *)self->fC14)->f2F0 = f;
}

struct RandomRangeLow { s32 v; };
s32 RandomIntInRange(RandomRangeLow lo, s32 hi);
f32 RandomFloatInRange(f32 a, f32 b);

void StepRandomJumpAnimator(RandomJumpAnimator* self, f32 x)
{
    AnimRecord* p = self->cursor.record;
    if (p == 0)
        return;
    s32 count = p->count;
    if (count < 2)
        return;
    if (0.0f < self->wait) {
        self->wait = self->wait - x;
        return;
    }
    RandomRangeLow lo;
    lo.v = 1;
    s32 v = RandomIntInRange(lo, count - 1);
    s32 rem = (self->cursor.frame + v) % self->cursor.record->count;
    SetCursorFrame(&self->cursor, rem);
    self->wait = RandomFloatInRange(self->waitMin, self->waitMax);
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001B55C0();
extern const Fn_Table g_frameRunAnimatorMethods[8] = { (Fn_Table)LoadFrameRunAnimator, (Fn_Table)BindFrameRunAnimator, (Fn_Table)StepFrameRunAnimator, (Fn_Table)GetFrameRunProgress, 0, (Fn_Table)FindAnimatorCursor, 0, 0 };
extern const Fn_Table g_framePingPongAnimatorMethods[8] = { (Fn_Table)LoadFramePingPongAnimator, (Fn_Table)BindFramePingPongAnimator, (Fn_Table)StepFramePingPongAnimator, (Fn_Table)GetFramePingPongProgress, 0, (Fn_Table)FindAnimatorCursor, 0, 0 };
extern const Fn_Table g_randomJumpAnimatorMethods[8] = { (Fn_Table)LoadRandomJumpAnimator, (Fn_Table)BindAnimatorRecord, (Fn_Table)StepRandomJumpAnimator, (Fn_Table)GetAnimatorZeroProgress, 0, (Fn_Table)FindAnimatorCursor, 0, 0 };
extern const Fn_Table g_angleFrameAnimatorMethods[8] = { (Fn_Table)LoadAngleFrameAnimator, (Fn_Table)BindAngleFrameAnimator, 0, (Fn_Table)GetAnimatorZeroProgress, (Fn_Table)FollowObjectAngle, (Fn_Table)FindAnimatorCursor, 0, 0 };
extern const Fn_Table g_scrollAnimatorMethods[8] = { (Fn_Table)LoadScrollAnimator, (Fn_Table)BindAnimatorRecord, (Fn_Table)StepScrollAnimator, (Fn_Table)GetScrollProgress, 0, (Fn_Table)FindAnimatorCursor, 0, 0 };
extern const Fn_Table g_circleAnimatorMethods[8] = { (Fn_Table)LoadCircleAnimator, (Fn_Table)BindAnimatorRecord, (Fn_Table)StepCircleAnimator, (Fn_Table)GetCircleProgress, 0, (Fn_Table)FindAnimatorCursor, 0, 0 };
extern const Fn_Table g_triangleAnimatorMethods[8] = { (Fn_Table)LoadTriangleAnimator, (Fn_Table)BindAnimatorRecord, 0, (Fn_Table)GetAnimatorZeroProgress, (Fn_Table)func_001B55C0, (Fn_Table)FindAnimatorCursor, (Fn_Table)GetTriangleOutputs, 0 };

struct Track_1B66A0
{
    u8 pad00[0x34];
    f32 f34;
};
struct Edge_1B66A0
{
    Track_1B66A0* track;
    s32 a;
    s32 b;
    u32 flags;
    f32 weight;
};
struct Link_1B66A0
{
    s32 f0;
    s32 next;
};
struct Graph_1B66A0
{
    u8 pad00[0x34];
    s32 nodeCount;
    Link_1B66A0* links;
    s32 edgeCount;
    Edge_1B66A0* edges;
};
struct Mover_1B66A0
{
    u8 pad00[0x18];
    Graph_1B66A0* graph;
    s32 f1C;
    s32 f20;
    void* f24;
    s32 cur;
    s32 f2C;
    s32 target;
    Edge_1B66A0* edge;
    f32 f38;
};

void PushBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
void PopBackMemoryMark(void);
f32 RandomFloatInRange(f32 a, f32 b);
void NotifyStateWalkerChange(Mover_1B66A0* self, s32 a, s32 b);
void CreateAnimationPlayerWithoutPresetTargets(Track_1B66A0* track, s32 a1, s32 a2, void** out, f32 fa, f32 fb);
void AddAnimationPlayerCallback(void* obj, void (*fn)(Mover_1B66A0*, s32, s32), Mover_1B66A0* self);
void HandleStateWalkerTrackEnd(Mover_1B66A0* self, s32 a, s32 b);
void ApplyListedPoseSources(void* obj, s32 zero);
void StopAnimationPlayer(void* obj);
void CallStateWalkerListeners(Mover_1B66A0* self, s32 a, Mover_1B66A0* b);

void StartNextStateWalkerEdge(Mover_1B66A0* self)
{
    Graph_1B66A0* g = self->graph;
    PushBackMemoryMark();
    if (self->target == self->cur)
    {
        self->target = g->links[self->target].next;
    }
    s32 target = self->target;
    if (target == -1)
    {
        goto fail;
    }
    {
        s32 cur = self->cur;
        s32* dist = (s32*)AllocateBackMemory(g->nodeCount * 4);
        s32 i;
        s32 j;
        Edge_1B66A0* p;
        for (i = 0; i < g->nodeCount; i++)
        {
            dist[i] = (i == cur) ? 0 : -1;
        }
        s32 level = 1;
        for (;;)
        {
            s32 changed = 0;
            for (j = 0; j < g->edgeCount; j++)
            {
                p = &g->edges[j];
                if (dist[p->a] == level - 1 && dist[p->b] < 0)
                {
                    dist[p->b] = level;
                    changed = 1;
                }
                if ((p->flags & 1) && dist[p->b] == level - 1 && dist[p->a] < 0)
                {
                    dist[p->a] = level;
                    changed = 1;
                }
            }
            if (level == 1)
            {
                for (j = 0; j < g->edgeCount; j++)
                {
                    p = &g->edges[j];
                    if (p->a == cur && p->b == cur)
                    {
                        dist[cur] = 1;
                        changed = 1;
                    }
                }
            }
            if (!changed)
            {
                break;
            }
            if (dist[target] > 0)
            {
                goto found;
            }
            level++;
        }
        if (dist[target] < 0)
        {
            self->target = -1;
            goto fail;
        }
    found:
        for (i = 0; i < g->nodeCount; i++)
        {
            if (i != target && dist[i] == level)
            {
                dist[i] = -1;
            }
        }
        for (s32 m = level; m > 1; m--)
        {
            level++;
            for (j = 0; j < g->edgeCount; j++)
            {
                p = &g->edges[j];
                if (dist[p->b] == level - 1 && dist[p->a] == m - 1)
                {
                    dist[p->a] = level;
                }
                if ((p->flags & 1) && dist[p->a] == level - 1 && dist[p->b] == m - 1)
                {
                    dist[p->b] = level;
                }
            }
        }
        Edge_1B66A0** cand = (Edge_1B66A0**)AllocateBackMemory(g->edgeCount * 4);
        Edge_1B66A0* e;
        for (;;)
        {
            s32 n = 0;
            for (j = 0; j < g->edgeCount; j++)
            {
                Edge_1B66A0* c = &g->edges[j];
                if (dist[c->b] == level && c->a == cur)
                {
                    cand[n++] = c;
                }
                else if ((c->flags & 1) && dist[c->a] == level && c->b == cur)
                {
                    cand[n++] = c;
                }
            }
            f32 sum = 0.0f;
            for (i = 0; i < n; i++)
            {
                sum += cand[i]->weight;
            }
            f32 r = RandomFloatInRange(0.0f, sum);
            for (i = 0; i < n; i++)
            {
                r -= cand[i]->weight;
                if (r < 0.0f)
                {
                    break;
                }
            }
            e = cand[i];
            if (e->track != 0)
            {
                break;
            }
            if (e->a == cur)
            {
                NotifyStateWalkerChange(self, self->cur, e->b);
                self->cur = cur = e->b;
            }
            else
            {
                NotifyStateWalkerChange(self, self->cur, e->a);
                self->cur = cur = e->a;
            }
            if (cur == target)
            {
                goto arrived;
            }
            level--;
        }
        {
            f32 fa;
            f32 fb;
            if (e->a == cur)
            {
                self->f2C = e->b;
                fa = 0.0f;
                fb = self->f38;
            }
            else
            {
                self->f2C = e->a;
                fb = -self->f38;
                fa = e->track->f34;
            }
            void* old = self->f24;
            self->edge = e;
            self->f24 = 0;
            if (e->track != 0)
            {
                CreateAnimationPlayerWithoutPresetTargets(e->track, self->f1C, self->f20, &self->f24, fa, fb);
                if (self->f24 != 0)
                {
                    AddAnimationPlayerCallback(self->f24, HandleStateWalkerTrackEnd, self);
                }
            }
            if (old != 0)
            {
                ApplyListedPoseSources(old, 0);
                StopAnimationPlayer(old);
            }
            goto done;
        }
    }
arrived:
    StartNextStateWalkerEdge(self);
    PopBackMemoryMark();
    return;
fail:
    self->edge = 0;
    if (self->f24 != 0)
    {
        ApplyListedPoseSources(self->f24, 0);
        StopAnimationPlayer(self->f24);
        self->f24 = 0;
    }
done:
    PopBackMemoryMark();
    CallStateWalkerListeners(self, 0x14, self);
}

extern const ClassHead g_stateWalkerMethods = { D_00217410, 0x93 };
f32 D_002746A0[8] = { 1000.0f, 0.0f, 0.0f, 0.0f, 2.0f, -2.0f, 0.0f, 0.0f };

extern s32 g_imageRecordCountA;
extern s32 g_defaultFont;
extern s32 g_fontCount;
extern s32 g_fontRecords;
extern s32 g_imageRecordCountB;
extern s32 g_animRecordCount;
extern s32 g_fonts[5];
extern s32 g_activeImageMask;
extern s32 g_cursorAnimatorCount;
extern s32 g_maskImageUploads[6];
extern s32 g_maskedImagesPacket;
void InitMeshQueue(void);

void ResetScreenResources(void)
{
    g_imageRecordCountA = 0;
    g_imageRecordsB = 0;
    g_defaultFont = 0;
    g_fontCount = 0;
    g_fontRecords = 0;
    g_animRecords = 0;
    g_imageRecordsA = 0;
    g_imageRecordCountB = 0;
    g_animRecordCount = 0;
    FillMemory(g_fonts, 0, 0x14);
    g_cursorAnimators = 0;
    g_activeImageMask = 0;
    g_pendingCursors = 0;
    g_lastPendingCursor = 0;
    g_cursorAnimatorCount = 0;
    FillMemory(g_maskImageUploads, 0, 0x18);
    g_maskedImagesPacket = 0;
    InitMeshQueue();
}
