// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "shapes.h"
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
#include "animation.h"
#include "queued_call.h"
#include "globals.h"
#include "asm_func.h"
#include "scaling_volume.h"
#include "placed_object.h"
#include "base_object.h"
#include "vu0.h"
#include "game_clock.h"
#include "object_finder.h"

f32 RandomFloatInRange(f32 a, f32 b);
extern f32 g_gameTime;
// Two floats (CopyVec2).
struct Point2 { f32 x; f32 y; };
void SetAnimationPlayerSpeed(AnimationPlayer* self, f32 speed);
s32 IsObjectOfKind(BaseObject* list, s32 key);
s32 IsObjectDescendantOf(BaseObject* node, BaseObject* target);
void SetColliderFrozen(Collider* self, s32 flag);
struct SoundLevelEntry;
void ReleaseSoundLevel(SoundLevelEntry* self);
void NotifyStateWalkerChange(StateWalker* self, s32 a, s32 b);
void CommitStateWalkerArrival(StateWalker* self);
void StartNextStateWalkerEdge(StateWalker* self);
void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);
// A free slot of a world pool (Pool6C): its first word links the next.
struct FreeSlot { FreeSlot* next; };
void* PopFreeSlot(Pool6C* pool);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void AppendToList(List01* self, void* item);
void RemoveFromList(List01* list, void* item);
void StartObject(BaseObject* self);
struct T219CHook;
struct World;
void SpawnInitialStateWalker(StateGraph* self);
void* AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);
s32 FindStateEntryIndex(StateGraph* self, s32 key);
void StopAnimationPlayer(AnimationPlayer* self);
void ReleaseCallRecords(World* self, T219CHook* node);
void RemoveFromList(List01* list, void* item);
void PushFreeSlot(Pool6C* list, void* item);
struct __attribute__((aligned(16))) Quad_001B4580 { f32 v[4]; };
s32 IsAgentSlotIndex(s32 index);
void StartPlacedObject(PlacedObject* self);
void* AllocateFrontMemory(s32 size);
void BuildFreeList(Pool6C* s, s32 v, s32 n);
void AddCallbackNode(World* world, Callback01** head, void* fn, void* ctx);
void StartAgent(Agent* self);
void ResolveCompanionAgentObjects(CompanionAgent* self);
void UpdateAgent(Agent* self, f32 dt);
void AimCompanionAgentPose(CompanionAgent *self);
void EnterAgentState(Agent* self, s32 evt, Animation* arg);
typedef s32 (*VFn_1B7818)(void* self);
s32 IsAgentTargetInRange(Agent* self);
struct AgentNotification;
struct Agent;
void HandleAgentNotification(Agent* self, s32 kind, AgentNotification* msg);
void UpdatePlacedObject(PlacedObject* self, f32 f);
void InitAgent(Agent* self);
StateWalker* CreateStateWalker(StateGraph* self, void* a1, s32 a2, s32 a3);
u16 MapCharToCode(u8 ch);
extern "C" s32 GetStringLength(const char* s);
void StartNextStateWalkerEdge(StateWalker* self);
void SeekAnimationPlayer(AnimationPlayer* self, s32 mode, f32 a, f32 b);
s32 FindStateEntryIndexOrZero(void* self, s32 key);
void NotifyStateWalkerChange(StateWalker* self, s32 a, s32 b);
void StartNextStateWalkerEdge(StateWalker* self);
s32 FindStateEntryIndexOrZero(void* self, s32 key);
void CommitStateWalkerArrival(StateWalker* self);
void StopAnimationPlayer(AnimationPlayer* self);
void StartNextStateWalkerEdge(StateWalker* self);
// A class descriptor of two words: the parent's and the class id (config/us/classes.tsv, kind head).
// A class descriptor of two words, the parent's and the class id (classes.tsv, kind head).
extern const ClassHead g_stateWalkerMethods;
void* PopZeroedFreeSlot(Pool6C* pool);
void AppendToList(List01* self, void* item);
extern u8 D_0021A790[];
s32 MatchesObjectId(BaseObject* a, s32 b);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(u32 bytes);
void* CreatePoseSource(World* root, PlacedObject* value, const T2195_Vt* table);
void InsertAttachment(PlacedObject* self, Attachment* src);
extern f32 D_002746A0[8];
s32 GetAgentRosterState(Agent* self);
s32 IsAgentFacingBlocked(Agent* self);
void* AllocateBackMemory(s32 size);
void NotifyStateWalkerChange(StateWalker* self, s32 a, s32 b);
void CreateAnimationPlayerWithoutPresetTargets(Animation* self, BaseObject* alt, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);
void AddAnimationPlayerCallback(AnimationPlayer* a0, void* a1, void* a2);
void HandleStateWalkerTrackEnd(StateWalker* self, s32 a, s32 b);
void ApplyListedPoseSources(AnimationPlayer* a0, s32 flag);
void StopAnimationPlayer(AnimationPlayer* self);
void CallStateWalkerListeners(StateWalker* self, s32 a, void* b);

// A Shift-JIS code and the character it stands for (MapCharToCode).
// A Shift-JIS code and the character it stands for (MapCharToCode reads the tables).
struct SjisCharEntry { u16 code; u16 id; };

// The file's .data, in retail's order.
s32 D_00274548[4] = { 0, 1, 2, 0 };
s32 D_00274558[4] = { 2, 0, 1, 0 };
s32 D_00274568[4] = { 0, 2, 1, 0 };
s32 D_00274578[4] = { 1, 0, 2, 0 };
SjisCharEntry D_00274588[34] = {
    { 0x8140, 0x0020 }, { 0x8149, 0x0021 }, { 0x8168, 0x0022 }, { 0x8194, 0x0023 },
    { 0x8190, 0x0024 }, { 0x8193, 0x0025 }, { 0x8195, 0x0026 }, { 0x8166, 0x0027 },
    { 0x8169, 0x0028 }, { 0x816A, 0x0029 }, { 0x8196, 0x002A }, { 0x817B, 0x002B },
    { 0x8143, 0x002C }, { 0x817C, 0x002D }, { 0x8144, 0x002E }, { 0x815E, 0x002F },
    { 0x8146, 0x003A }, { 0x8147, 0x003B }, { 0x8171, 0x003C }, { 0x8181, 0x003D },
    { 0x8172, 0x003E }, { 0x8148, 0x003F }, { 0x8197, 0x0040 }, { 0x816D, 0x005B },
    { 0x818F, 0x005C }, { 0x816E, 0x005D }, { 0x814F, 0x005E }, { 0x8151, 0x005F },
    { 0x8165, 0x0060 }, { 0x816F, 0x007B }, { 0x8162, 0x007C }, { 0x8170, 0x007D },
    { 0x8150, 0x007E }, { 0x0000, 0x0000 }
};
SjisCharEntry D_00274610[4] = {
    { 0x824F, 0x0030 }, { 0x8260, 0x0041 }, { 0x8281, 0x0061 }, { 0x0000, 0x0000 }
};
f32 D_00274620[16] = { 0.0f, 0.0f, -80.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, -70.0f, 40.0f, 0.0f, 0.0f, 70.0f, 40.0f, 0.0f };
f32 D_00274660[16] = { 0.0f, 0.0f, -20.0f, 0.0f, 0.0f, 0.0f, 70.0f, 0.0f, 0.0f, -30.0f, 30.0f, 0.0f, 0.0f, 30.0f, 30.0f, 0.0f };
f32 D_002746A0[8] = { 1000.0f, 0.0f, 0.0f, 0.0f, 2.0f, -2.0f, 0.0f, 0.0f };

void CopyVec3(Vec3* dst, Vec3* src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

void CopyVec2(Point2* a0, Point2* a1)
{
    a0->x = a1->x;
    a0->y = a1->y;
}

void* MoveMemory(void* dst, void* src, s32 size);
struct RampProfile;
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
void SetCursorCoords(AnimCursor* cursor, f32 u, f32 v);
struct Frame_166690;
void DrawModelPart(Frame_166690* self);
// Drops the first entry of a three-entry window: the other two move down.
template <class T>
static inline void DropFirst(T* window)
{
    MoveMemory(window, window + 1, 2 * sizeof(T));
}

static inline f32 ClampBetween(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

// Slot 4 of the triangle animator (g_triangleAnimatorMethods): where the segment between the
// objects at Rec2195_224::p64 and p60 crosses the strip, the strip's coordinates there, offset,
// clamped and eased into the cursor. &self->cursor is written at the call: GCSE makes the entry
// test's self+16 its reaching register, a PRE pseudo numbered by its hash bucket. The edges are
// subtracted as u128 values (no Vec copies), which brings GCSE's table to 183 buckets, where
// self+16 hashes before &tri[2] (docs/toolchain/gcse.md, func_001B55C0).
void UpdateTriangleAnimatorCursor(TriangleAnimator* self, PlacedObject* obj, void** part)
{
    if (self->cursor.record == 0 || *part != (void*)DrawModelPart) {
        return;
    }
    Vec02 b;
    Vec02 a;
    Vec02 tri[3];
    Point2 uv[3];
    Vec02 edge[3];
    f32 u;
    f32 v;
    BaseObject* end = obj->linkRecord->p64;
    TransformPointBetweenFrames((PlacedObject*)end->parent, obj, (Vec02*)((u8*)end + 0x40), &b);
    end = obj->linkRecord->p60;
    TransformPointBetweenFrames((PlacedObject*)end->parent, obj, (Vec02*)((u8*)end + 0x40), &a);
    CopyVec3((Vec3*)&tri[1], (Vec3*)&self->points[0]);
    CopyVec3((Vec3*)&tri[2], (Vec3*)&self->points[1]);
    CopyVec2(&uv[1], (Point2*)&self->coords[0]);
    CopyVec2(&uv[2], (Point2*)&self->coords[1]);
    for (s32 i = 2; i < self->count; i++) {
        s32* order;
        s32* next;
        if (i & 1) {
            order = D_00274568;
            next = D_00274578;
        } else {
            order = D_00274548;
            next = D_00274558;
        }
        DropFirst(tri);
        DropFirst(uv);
        CopyVec3((Vec3*)&tri[2], (Vec3*)&self->points[i]);
        CopyVec2(&uv[2], (Point2*)&self->coords[i]);
        StripPoint* pt = &self->points[i];
        if (pt->flags & 0x8000) {
            continue;
        }
        Vec02 n;
        Vec02 p;
        s32 j;
        for (j = 0; j < 3; j++) {
            Vu0::Q(edge[j]) = Vu0::Sub(Vu0::Q(tri[order[(j + 1) % 3]]), Vu0::Q(tri[order[j]]));
        }
        Vu0::Vec e0 = Vu0::Vec::Of(edge[0]);
        Vu0::Vec e2 = Vu0::Vec::Of(edge[2]);
        Vu0::Vec c;
        {
            Vec02 neg;
            Vu0::Q(neg) = Vu0::FromFloat(-1.0f);
            c = Vu0::Cross(e0, Vu0::MulX(e2, Vu0::Vec::Of(neg)));
        }
        Vu0::Q(n) = Vu0::DivX(c, Vu0::Length(c)).q;
        f32 d0 = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(n), Vu0::Vec::Of(tri[0])));
        f32 da = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(n), Vu0::Vec::Of(a))) - d0;
        f32 db = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(n), Vu0::Vec::Of(b))) - d0;
        if (da >= 0.0f && db >= 0.0f) {
            continue;
        }
        if (da < 0.0f && db < 0.0f) {
            continue;
        }
        f32 t = da / (da - db);
        Vu0::Q(p) = Vu0::Add(Vu0::MulX(Vu0::Vec::Of(a), Vu0::Vec::Scalar(1.0f - t)), Vu0::MulX(Vu0::Vec::Of(b), Vu0::Vec::Scalar(t))).q;
        f32 su = 0.0f;
        f32 sv = 0.0f;
        for (j = 0; j < 3; j++) {
            Vec02 m;
            Vu0::Vec e = Vu0::Cross(Vu0::Vec::Of(edge[j]), Vu0::Vec::Of(n));
            Vu0::Q(m) = Vu0::DivX(e, Vu0::Length(e)).q;
            f32 dv = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(m), Vu0::Vec::Of(tri[order[j]])));
            f32 dp = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(m), Vu0::Vec::Of(p))) - dv;
            if (0.0f < dp) {
                break;
            }
            f32 w = dp / (Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(m), Vu0::Vec::Of(tri[next[j]]))) - dv);
            su += w * uv[next[j]].x;
            sv += w * uv[next[j]].y;
        }
        if (j >= 3) {
            u = su;
            v = sv;
            break;
        }
    }
    Vec3 ramp = { 1.0f, 0.1f, 0.1f };
    f32 iu = 1.0f - u;
    f32 iv = 1.0f - v;
    f32 cu = ClampBetween(iu - self->u0, self->uMin, self->uMax);
    f32 cv = ClampBetween(iv - self->v0, self->vMin, self->vMax);
    ApproachValueWithRamp(self->cursor.u, cu, g_gameClock.dt, (RampProfile*)&ramp, 0);
    ApproachValueWithRamp(self->cursor.v, cv, g_gameClock.dt, (RampProfile*)&ramp, 0);
    SetCursorCoords(&self->cursor, cu, cv);
}

extern const char D_0024D278[8] = ".Kanji.";

LINKER_REMNANT(func_001B5B48);

u16 MapCharToCode(u8 ch)
{
    s32 base = 0;
    s32 idx;
    if (ch >= 0x20 && ch < 0x30) {
        base = 1;
    } else if (ch >= 0x30 && ch < 0x3A) {
        idx = 0;
    } else if (ch >= 0x3A && ch < 0x41) {
        base = 0xB;
    } else if (ch >= 0x41 && ch < 0x5B) {
        idx = 1;
    } else if (ch >= 0x5B && ch < 0x61) {
        base = 0x25;
    } else if (ch >= 0x61 && ch < 0x7B) {
        idx = 2;
    } else if (ch >= 0x7B && ch < 0x7F) {
        base = 0x3F;
    } else {
        return 0;
    }
    u16 code;
    if (base != 0) {
        SjisCharEntry* e = &D_00274588[ch - (base + 0x1F)];
        code = e->code;
    } else {
        code = D_00274610[idx].code + ch - D_00274610[idx].id;
    }
    return code;
}

void ConvertStringToCharCodes(u8* src, u16* dst)
{
    s32 n = GetStringLength((const char*)src);
    s32 i;
    for (i = 0; i < n; i++) {
        u32 r = MapCharToCode(src[i]);
        u32 lo = (r & 0xFF) << 8;
        u32 hi = (r >> 8) & 0xFF;
        dst[i] = (u16)(hi | lo);
    }
    dst[i] = 0;
}

void StartCameraPositionedObject(CameraPositionedObject* self)
{
    StartPlacedObject(self);
    self->flags = (self->flags & 0xFFFFFCFFFFFFFFFFULL) | 0x10000000000ULL;
}

void MoveObjectToCamera(CameraPositionedObject* self, f32 dt)
{
    UpdatePlacedObject(self, dt);
    Vec02* src = (Vec02*)g_camera->position;
    Vec02 q = *src;
    if (self->followHeight == 0) {
        q.z = self->v140.z;
    }
    self->desc02()->m1D(self, &q);
}

void BuildFreeList(Pool6C* s, s32 v, s32 n)
{
    u32 cur = (u32)s->base;
    s->size = v;
    s->head = (void*)cur;
    for (s32 i = 1; i < n; i++) {
        u32 prev = cur;
        s32 a = s->size;
        cur = (u32)s->base + i * a;
        *(u32*)prev = cur;
    }
    *(u32*)cur = 0;
}

void InitSlotPool(Pool6C* s, s32 size, s32 count)
{
    s32 stride = (size + 7) & ~7;
    s->base = AllocateFrontMemory(stride * count);
    BuildFreeList(s, stride, count);
}

void InitAlignedSlotPool(Pool6C* s, s32 size, s32 count)
{
    s32 addr = (s32)AllocateFrontMemory(size * count + 0x30);
    s->base = (void*)((addr + 0x3F) & -0x40);
    BuildFreeList(s, size, count);
}

LINKER_REMNANT(func_001B5E98);

void* PopFreeSlot(Pool6C* pool)
{
    FreeSlot* n = (FreeSlot*)pool->head;
    if (n != 0) {
        pool->head = n->next;
    }
    return n;
}

void* TakePoolSlot(Pool6C* pool)
{
    return PopFreeSlot(pool);
}

void* PopZeroedFreeSlot(Pool6C* pool)
{
    void* p = PopFreeSlot(pool);
    FillMemory(p, 0, pool->size);
    return p;
}

void PushFreeSlot(Pool6C* list, void* item)
{
    if (item) {
        ((FreeSlot*)item)->next = (FreeSlot*)list->head;
        list->head = item;
    }
}

LINKER_REMNANT(func_001B5F48);

void SetListLinkOffset(List01* self, s32 value);
s32 ReadBufferedU8(BufferedStream* s);
s32 ReadBufferedS8(BufferedStream* s);
s32 ReadBufferedS16(BufferedStream* s);
s32 ReadBufferedS32(BufferedStream* s);
f32 ReadBufferedFloat(BufferedStream* s);
void ReadPropertyRecords(void* self, void* obj);
BaseObject* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);
void ResolveAndStartObject(BaseObject* o);

void LoadStateGraph(StateGraph* self, BufferedStream* s)
{
    s32 i;
    s32 j;
    SetListLinkOffset(&self->walkers, 8);
    self->stateCount = ReadBufferedU8(s);
    self->states = (StateEntry*)AllocateFrontMemory(self->stateCount * sizeof(StateEntry));
    for (i = 0; i < self->stateCount; i++) {
        StateEntry* e = &self->states[i];
        e->key = ReadBufferedS16(s);
        e->extra = ReadBufferedS16(s);
    }
    for (i = 0; i < self->stateCount; i++) {
        StateEntry* e = &self->states[i];
        if (e->extra != -1) {
            e->extra = FindStateEntryIndexOrZero(self, e->extra);
        }
    }
    self->edgeCount = ReadBufferedU8(s);
    self->edges = (StateEdge*)AllocateFrontMemory(self->edgeCount * sizeof(StateEdge));
    for (j = 0; j < self->edgeCount; j++) {
        StateEdge* e = &self->edges[j];
        e->anim = (Animation*)ReadBufferedS8(s);
        e->a = FindStateEntryIndexOrZero(self, ReadBufferedS16(s));
        e->b = FindStateEntryIndexOrZero(self, ReadBufferedS16(s));
        e->flags = ReadBufferedS32(s);
        e->weight = ReadBufferedFloat(s);
    }
    ReadPropertyRecords(self, s);
    ReadBufferedS16(s);
    for (j = 0; j < self->edgeCount; j++) {
        StateEdge* e = &self->edges[j];
        if (e->anim != 0) {
            s32 kind = ReadBufferedS16(s);
            s32 b = ReadBufferedS16(s);
            s32 c = ReadBufferedS16(s);
            BaseObject* o = CreateTypedRecord(kind, self->world, self->parent, b, c);
            e->anim = (Animation*)o;
            o->desc->m0A(o, s);
            ResolveAndStartObject(o);
        }
    }
}

void StartStateGraph(StateGraph* self)
{
    StartObject(self);
    if (self->armed != 0) {
        AppendQueuedCall(self->world, (void*)SpawnInitialStateWalker, self, 0, 0);
    }
}

void SpawnInitialStateWalker(StateGraph* self)
{
    s32 i = 0;
    s32 n = self->edgeCount;
    Animation* e = 0;
    if (n > 0) {
        StateEdge* p = self->edges;
        do {
            e = p->anim;
            i++;
            p++;
        } while (i < n && e == 0);
    }
    BaseObject* r;
    if (self->edgeCount > 0 && e != 0 && e->id != -1) {
        r = FindFirstObjectByIdMode4(self->world, e->id, self);
    } else {
        r = 0;
    }
    CreateStateWalker(self, (void*)r, -1, 0);
}

StateWalker* CreateStateWalker(StateGraph* self, void* a1, s32 a2, s32 a3)
{
    StateWalker* obj = (StateWalker*)PopZeroedFreeSlot(&self->world->pool1B88);
    obj->f1C = a1;
    obj->vt = (void*)&g_stateWalkerMethods;
    obj->playerFlags = a3;
    obj->f38 = 1.0f;
    obj->owner = self;
    obj->nextEntry = -1;
    AppendToList(&self->world->list1B94, obj);

    AppendToList((List01*)((u8*)self + 0x48), obj);
    if (a2 != -1) {
        s32 v = FindStateEntryIndexOrZero(self, a2);
        obj->currentEntry = v;
        obj->index = v;
        NotifyStateWalkerChange(obj, -1, v);
    }
    StartNextStateWalkerEdge(obj);
    StateWalker** pp = &obj;
    TriggerScriptEvent(self, 0x11, 1, (void*)&pp);
    return obj;
}

void* FindListNodeByKey(StateGraph* self, void* key)
{
    ListFrame frame;
    StateWalker* node = (StateWalker*)self->walkers.head;
    if (node != 0) {
        do {
            if (node->f1C == key) {
                return node;
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}

s32 FindStateEntryIndex(StateGraph* self, s32 key)
{
    s32 count = self->stateCount;
    if (count > 0) {
        StateEntry* p = self->states;
        s32 i = 0;
        do {
            if (p->key == key) {
                return i;
            }
            i++;
            p++;
        } while (i < count);
    }
    return -1;
}

s32 FindStateEntryIndexOrZero(void* self, s32 key)
{
    s32 r = FindStateEntryIndex((StateGraph*)self, key);
    return r < 0 ? 0 : r;
}

u32 GetStateEntryKey(StateGraph* a0, s32 a1)
{
    a1 = (a1 << 3) + (u32)a0->states;
    return *(u32*)a1;
}

void DestroyStateWalker(StateWalker* self)
{
    StateGraph* owner = self->owner;
    if (self->player != 0) {
        StopAnimationPlayer(self->player);
        self->player = 0;
    }
    ReleaseCallRecords(self->owner->world, (T219CHook*)self->calls);
    self->calls = 0;
    RemoveFromList(&self->owner->walkers, self);
    RemoveFromList((List01*)((u8*)self->owner->world + 0x1B94), self);
    PushFreeSlot(&self->owner->world->pool1B88, self);
    TriggerScriptEvent(owner, 0x12, 0, 0);
}

void SetStateWalkerTarget(StateWalker* self, s32 key)
{
    s32 v;
    if (key != -1) {
        v = FindStateEntryIndexOrZero(self->owner, key);
    } else {
        v = -1;
    }
    if (v != self->index) {
        self->index = v;
        StateEdge* p = self->edge;
        if (p != 0 && (p->flags & 2)) {
            CommitStateWalkerArrival(self);
            StopAnimationPlayer(self->player);
            self->player = 0;
        }
        if (self->player == 0) {
            StartNextStateWalkerEdge(self);
        }
    }
}

void GetStateWalkerTargetKey(StateWalker* a0, s32* out) {
    s32 idx = a0->index;
    s32 v;
    if (idx >= 0) {
        v = ((StateGraph*)a0->owner)->states[idx].key;
    } else {
        v = -1;
    }
    *out = v;
}

void GetStateWalkerCurrentKey(StateWalker* a0, s32* out) {
    s32 idx = a0->currentEntry;
    s32 v;
    if (idx >= 0) {
        v = ((StateGraph*)a0->owner)->states[idx].key;
    } else {
        v = -1;
    }
    *out = v;
}

void GetStateWalkerNextKey(StateWalker* self, s32* out)
{
    s32 value;
    if (self->nextEntry >= 0) {
        value = ((StateGraph*)self->owner)->states[self->nextEntry].key;
    } else {
        value = -1;
    }
    *out = value;
}

void SetStateWalkerSpeed(StateWalker* self, f32 v)
{
    self->f38 = v;
    if (self->player != 0) {
        SetAnimationPlayerSpeed(self->player, v);
    }
}

void TeleportStateWalker(StateWalker* self, s32 key)
{
    s32 s1 = FindStateEntryIndexOrZero(self->owner, key);
    if (self->currentEntry == s1) {
        s32 v = self->index;
        if (v == s1 || v == -1) {
            return;
        }
    }
    NotifyStateWalkerChange(self, self->currentEntry, s1);
    self->index = s1;
    self->currentEntry = s1;
    self->nextEntry = -1;
    StartNextStateWalkerEdge(self);
}


void StartNextStateWalkerEdge(StateWalker* self)
{
    StateGraph* g = self->owner;
    PushBackMemoryMark();
    if (self->index == self->currentEntry)
    {
        self->index = g->states[self->index].extra;
    }
    s32 target = self->index;
    if (target == -1)
    {
        goto fail;
    }
    {
        s32 cur = self->currentEntry;
        s32* dist = (s32*)AllocateBackMemory(g->stateCount * 4);
        s32 i;
        s32 j;
        StateEdge* p;
        for (i = 0; i < g->stateCount; i++)
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
            self->index = -1;
            goto fail;
        }
    found:
        for (i = 0; i < g->stateCount; i++)
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
        StateEdge** cand = (StateEdge**)AllocateBackMemory(g->edgeCount * 4);
        StateEdge* e;
        for (;;)
        {
            s32 n = 0;
            for (j = 0; j < g->edgeCount; j++)
            {
                StateEdge* c = &g->edges[j];
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
            if (e->anim != 0)
            {
                break;
            }
            if (e->a == cur)
            {
                NotifyStateWalkerChange(self, self->currentEntry, e->b);
                self->currentEntry = cur = e->b;
            }
            else
            {
                NotifyStateWalkerChange(self, self->currentEntry, e->a);
                self->currentEntry = cur = e->a;
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
                self->nextEntry = e->b;
                fa = 0.0f;
                fb = self->f38;
            }
            else
            {
                self->nextEntry = e->a;
                fb = -self->f38;
                fa = e->anim->length;
            }
            void* old = self->player;
            self->edge = e;
            self->player = 0;
            if (e->anim != 0)
            {
                CreateAnimationPlayerWithoutPresetTargets(e->anim, (BaseObject*)self->f1C, self->playerFlags, &self->player, fa, fb);
                if (self->player != 0)
                {
                    AddAnimationPlayerCallback(self->player, HandleStateWalkerTrackEnd, self);
                }
            }
            if (old != 0)
            {
                ApplyListedPoseSources((AnimationPlayer*)old, 0);
                StopAnimationPlayer((AnimationPlayer*)old);
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
    if (self->player != 0)
    {
        ApplyListedPoseSources(self->player, 0);
        StopAnimationPlayer(self->player);
        self->player = 0;
    }
done:
    PopBackMemoryMark();
    CallStateWalkerListeners(self, 0x14, self);
}

void CommitStateWalkerArrival(StateWalker* self)
{
    NotifyStateWalkerChange(self, self->currentEntry, self->nextEntry);
    s32 v = self->nextEntry;
    self->nextEntry = -1;
    self->currentEntry = v;
}

void HandleStateWalkerTrackEnd(StateWalker* self, s32 a, s32 b)
{
    if (a == 5 && b == (s32)self->player) {
        CommitStateWalkerArrival(self);
        StartNextStateWalkerEdge(self);
    }
}

void AdvanceStateWalkerTime(StateWalker* self, f32 t)
{
    f32 rem = t;
    AnimationPlayer* item;
    while ((item = self->player) != 0) {
        f32 diff = item->anim->length - item->time;
        if (rem < diff) {
            SeekAnimationPlayer(item, 1, rem, 1.0f);
            break;
        }
        rem = rem - diff;
        CommitStateWalkerArrival(self);
        StartNextStateWalkerEdge(self);
    }
}

void CallStateWalkerListeners(StateWalker* self, s32 a, void* b)
{
    BaseObject* o = (BaseObject*)self->f1C;
    if (o != 0) {
        o->desc->m0E(o, a, b);
    }
    QueuedCall* link = self->calls;
    if (link != 0) {
        do {
            void* obj = link->arg;
            void (*fn)(void* arg, s32 kind, void* payload) = link->notify;
            link = link->next;
            fn(obj, a, b);
        } while (link != 0);
    }
}

void AddStateWalkerListener(StateWalker* self, PlacedObject** p)
{
    AddCallbackNode(self->owner->world, (Callback01**)&self->calls, (void*)(*p)->link40.prev, p);
}

void NotifyStateWalkerChange(StateWalker* self, s32 idx1, s32 idx2)
{
    void* args[3];
    s32 v1;
    s32 v2;
    if (idx1 >= 0) {
        v1 = self->owner->states[idx1].key;
    } else {
        v1 = -1;
    }
    if (idx2 >= 0) {
        v2 = self->owner->states[idx2].key;
    } else {
        v2 = -1;
    }
    args[0] = &self;
    args[1] = &v1;
    args[2] = &v2;
    TriggerScriptEvent(self->owner, 0xE, 3, args);
}

void InitCompanionAgent(CompanionAgent* self)
{
    InitAgent(self);
    self->closeRadius = 2000.0f;
    self->reachRadius = 300.0f;
    self->reachHeight = 300.0f;
    self->closeHeight = 300.0f;
    self->closeZoneId = -1;
    self->closeZone = 0;
    s32 i = 16;
    Slot08* e = &self->lookEntries[16];
    do {
        e->id = -1;
        i--;
        e--;
    } while (i >= 0);
    self->companionId = -1;
}

void ResolveCompanionAgentObjects(CompanionAgent* self)
{
    s32 best = -1;
    s32 j = 16;
    Slot08* e = self->lookEntries;
    do {
        s32 key = e->id;
        if (key == best) {
            e->obj = 0;
        } else {
            e->obj = (void*)FindFirstObjectByIdMode4(self->world, key, self);
        }
        e++;
        j--;
    } while (j >= 0);

    PushBackMemoryMark();
    best = 0;
    s32 count = GatherObjectsById(self->world, 0x201, 0x60, self, 0, 0);
    BaseObject** list = (BaseObject**)AllocateBackMemory(count << 2);
    count = GatherObjectsById(self->world, 0x201, 0x60, self, count, list);
    if (count > 0) {
        do {
            if (MatchesObjectId(*list, self->companionId) != 0) {
                best = (s32)*list;
            } else {
                (*list)->desc->m03(*list);
            }
            list++;
            count--;
        } while (count != 0);
    }
    self->fC14 = (void*)best;
    PopBackMemoryMark();
    if (self->fC14 != 0) {
        self->poseSource = CreatePoseSource(self->world, (PlacedObject*)self->fC14, (const T2195_Vt*)D_0021A790);
        ((T2195_790*)self->poseSource)->mode1 = 2;
        ((T2195_790*)self->poseSource)->hasTarget = 1;
        ((T2195_790*)self->poseSource)->f84 = ((T2195_790*)self->poseSource)->f80 = 0;
        InsertAttachment((PlacedObject*)self->fC14, (Attachment*)self->poseSource);
        self->bindingObject = (s32)self->fC14;
    }
}

void SetCompanionAgentLookId(CompanionAgent* self, s32 index, s32 value)
{
    (void)IsAgentSlotIndex(index);
    self->lookEntries[index].id = value;
}

void AddCompanionAgentExcludedId(CompanionAgent* self, s32 value)
{
    s32 n = self->excludedCount;
    if ((u32)n < 4) {
        self->excludedObjects[n].id = value;
        n++;
        self->excludedCount = n;
    }
}

void StartCompanionAgent(CompanionAgent* self)
{
    StartAgent(self);
    ResolveCompanionAgentObjects(self);
    if (self->closeZoneId != -1) {
        self->closeZone = (ObjectGatherer*)FindFirstObjectByIdMode4(self->world, self->closeZoneId, self);
    }
    if (self->excludedCount > 0) {
        s32 i = 0;
        Slot08* p = self->excludedObjects;
        do {
            p->obj = (void*)FindFirstObjectById(self->world, 0x104, p->id, self);
            p++;
            i++;
        } while (i < self->excludedCount);
    }
}

s32 IsCompanionAgentBlocker(CompanionAgent* self, Collider* ent)
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
    for (s32 i = 0; i < self->excludedCount; i++) {
        if (IsObjectDescendantOf(ent, (BaseObject*)self->excludedObjects[i].obj) != 0) {
            return 0;
        }
    }
    return 1;
}

s32 IsPadSelectFlagHeld(World* world);
struct ObjectGatherer;
s32 TestPointAgainstObjectShape(ObjectGatherer* self, void* value);
SoundLevelEntry* PushSoundLevel(s32 kind);
void RemoveSoundLevelAndRecompute(SoundLevelEntry* self);
s32 IsPointInsideObjectFaces(ScalingVolume* self, void* point);
s32 IsPlayerUntargetableByAgent(Agent* self);
void GatherCollidersInBox(World* world, Collider* skip, Vec02* a, Vec02* b, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);
s32 FindNearestSpanObject(s32 flags, Vec02* a1, Vec02* a2, s32 count, Collider** list, ColliderSpan* out);

#define F(T, o) (*(T*)((u8*)self + (o)))

// Whether the companion can reach its target (slot 0x16C of class 0x09): not while select is
// held or the agent is busy; the target must be near enough (or inside the agent's volume), the
// player targetable, and no blocking collider may lie between the agent and each of the four
// corners of the target's box for its roster state. The target test is one block that falls to
// the shared `return 0`, which keeps the last test a branch (jump.c makes a store-flag of
// `if (c) return 1; return 0;` only when nothing else reaches that return). The corner count is
// set in each arm of the switch and never on the default path, so it stays a variable equal to
// 4 that global-alloc leaves without a register (retail's `li v0,4` at each use), and it bounds
// both loops, which share one index (docs/toolchain/loops.md, "A count set in each arm").
s32 IsCompanionAgentTargetReachable(CompanionAgent* self)
{
    if (IsPadSelectFlagHeld(self->world) != 0 || F(s32, 0xCCC) != 0) return 0;
    if (F(s32, 0xCC8) != 0) return 1;
    PlacedObject* target = (PlacedObject*)self->desc08()->m62(self);
    if (target != 0) {
        if (self->fC14 == 0 || self->f724 == 0xB || self->f724 == 0x10) return 0;
        Vec02 a;
        if (IsObjectOfKind(target, 6) != 0) {
            if (*(s32*)((u8*)target + 0x690) != 0) {
                a = *(Vec02*)((u8*)target + 0x6A0);
            } else {
                a = target->v140;
                a.z -= 70.0f;
            }
        } else {
            a = target->v140;
        }
        Vec02 delta;
        Vu0::Q(delta) = Vu0::Sub(Vu0::Q(a), Vu0::Q(self->v140));
        f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(delta), Vu0::Q(delta))));
        s32 near;
        if (self->closeZone != 0) {
            near = TestPointAgainstObjectShape(self->closeZone, &a);
        } else {
            near = 0;
            if (dist < self->closeRadius) {
                if (__builtin_fabsf(delta.z) < self->closeHeight) near = 1;
            }
        }
        if (near != 0) {
            if (self->soundLevel == 0) self->soundLevel = PushSoundLevel(-0x14);
        } else {
            RemoveSoundLevelAndRecompute((SoundLevelEntry*)self->soundLevel);
            self->soundLevel = 0;
        }
        if (IsPointInsideObjectFaces((ScalingVolume*)self->fC14, &a) == 0) {
            if (self->reachRadius < dist) return 0;
            if (self->reachHeight < __builtin_fabsf(delta.z)) return 0;
        }
        s32 v = GetAgentRosterState(self);
        if ((F(s32, 0xCD0) & 1) == 0) {
            if (v != 2) {
                if (IsPlayerUntargetableByAgent(self) != 0) return 0;
            }
        }
        if (F(s32, 0xCD0) & 2) return 1;
        f32* table;
        s32 n;
        switch (v) {
        case 2:
            table = D_00274620;
            n = 4;
            break;
        case 0:
        case 1:
            table = D_00274660;
            n = 4;
            break;
        }
        Vec02* pos = F(PlacedObject*, 0x734) != 0 ? &F(PlacedObject*, 0x734)->v140 : &self->v140;
        PushBackMemoryMark();
        Vec02 lo = *pos;
        Vec02 hi = *pos;
        Vec02* buf = (Vec02*)AllocateBackMemory(n << 4);
        s32 count;
        Collider** list;
        s32 i;
        for (i = 0; i < n; i++) {
            TransformPointBetweenFrames(target, 0, (Vec02*)(table + i * 4), &buf[i]);
            Vu0::Q(lo) = Vu0::Min(Vu0::Q(lo), Vu0::Q(buf[i]));
            Vu0::Q(hi) = Vu0::Max(Vu0::Q(hi), Vu0::Q(buf[i]));
        }
        GatherCollidersInBox(self->world, 0, &lo, &hi, IsCompanionAgentBlocker, self, &count, &list);
        for (i = 0; i < n; i++) {
            if (FindNearestSpanObject(0, pos, &buf[i], count, list, 0) == 0) break;
        }
        PopBackMemoryMark();
        if (i < n) return 1;
    }
    return 0;
}

#undef F

void UpdateCompanionAgent(CompanionAgent* self, f32 dt)
{
    UpdateAgent(self, dt);
    AimCompanionAgentPose(self);
}

void AimCompanionAgentPose(CompanionAgent *self) {
    T2195_790 *t;
    s32 r;
    s32 res;
    f32 f;

    if (self->fC14 == 0) {
        return;
    }
    t = (T2195_790 *)self->poseSource;
    r = GetAgentRosterState(self);
    switch (r) {
    case 0:
    case 1:
        if ((void *)self->lookTarget != 0) {
            t->target = (void *)self->lookTarget;
            t->point = *(Vec02 *)&D_00248D30;
        } else {
            t->target = self;
            t->point = *(Vec02 *)D_002746A0;
        }
        f = 1.3f;
        if (r == 0) {
            f = 1.0f;
        }
        break;
    case 2:
        if ((void *)self->lookTarget != 0) {
            t->target = (void *)self->lookTarget;
            t->point = *(Vec02 *)&D_00248D30;
        } else if (IsAgentFacingBlocked(self) != 0) {
            t->target = self;
            t->point = *(Vec02 *)D_002746A0;
        } else {
            res = (s32)self->desc08()->m62(self);
            if (res != 0) {
                t->target = (void *)res;
                t->point = *(Vec02 *)&D_00248D30;
            } else {
                t->target = self;
                t->point = *(Vec02 *)D_002746A0;
            }
        }
        f = 1.3f;
        break;
    case 3:
        t->target = self;
        t->point = *(Vec02 *)D_002746A0;
        f = 0.1f;
        break;
    }
    ((ScalingVolume*)self->fC14)->f2F0 = f;
}

void EnterCompanionAgentState(CompanionAgent* self, s32 evt, Animation* arg)
{
    EnterAgentState(self, evt, arg);
    switch (self->f724) {
    case 6:
        self->clipEndCount = 0;
        break;
    case 0xB: {
        BaseObject* p = ((BaseObject*)self->fC14);
        if (p != 0) {
            p->desc->m03(p);
        }
        ReleaseSoundLevel((SoundLevelEntry*)self->soundLevel);
        self->soundLevel = 0;
        break;
    }
    }
    self->lookTarget = *(s32*)((u8*)self + (self->f724 << 3) + 0xC3C);
}

s32 IsCompanionAgentTargetInRange(CompanionAgent* self)
{
    if (IsAgentTargetInRange(self) == 0) {
        return 0;
    }
    return ((VFn_1B7818*)self->desc)[91](self);
}

s32 AnswerCompanionAgentRosterPoll(CompanionAgent* self)
{
    s32 r;
    if (self->f724 == 11) {
        goto ret1;
    }
    if (self->f724 != 6) {
        goto ret0;
    }
    if (self->clipEndCount <= 0) {
        goto ret0;
    }
    if (5.0f < g_gameTime - self->stateTime) {
        r = 2;
        return r;
    }
ret1:
    return 1;
ret0:
    r = 0;
    return r;
}

void HandleCompanionAgentNotification(CompanionAgent* self, s32 code, void* req)
{
    HandleAgentNotification(self, code, (AgentNotification*)req);
    if (code == 7) {
        if (req == self->statePlayer) {
            self->clipEndCount++;
        }
    }
}

void SetCompanionAgentFrozen(CompanionAgent* self, s32 p)
{
    SetColliderFrozen(self, p);
    if (p != 0) {
        ReleaseSoundLevel((SoundLevelEntry*)self->soundLevel);
        self->soundLevel = 0;
    }
}
