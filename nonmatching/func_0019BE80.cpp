// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 456/488 (93.4%), checked 2026-11-07
// NEAR: the walk, the registers and the vector part match; the schedule differs: retail loads the reach (0x624) and squares it before the first vector loads, ours does it after the Dot.
#include "common.h"
#include "switched_collider.h"
#include "object_set.h"
#include "object_gatherer.h"
#include "path_curve_object.h"
#include "c5c.h"
#include "c5d.h"
#include "effect_owner.h"
#include "effect_spawner.h"
#include "c8b.h"
#include "world.h"
#include "effect.h"
#include "list_iter.h"
#include "globals.h"
#include "game_progress.h"
#include "object_message.h"
#include "object_event.h"
#include "object_link.h"
#include "camera.h"
#include "packet_writer.h"
#include "screen_element.h"
#include "step_sequence.h"
#include "asm_func.h"
#include "vu0.h"
void InitCollider(void* self);
void func_0019BE80(ObjectGatherer* self);
void ComputePolarOffset(void* out, f32 x, f32 y, f32 z);
void ScatterObjectsAtPoint(void* p, void* v, s32 a, s32 b);
extern u8 g_scatterController[];
void SetObjectGathererSuspended(ObjectGatherer* self, s32 a1);
void PostLoadPlacedObject(void* self);
void* FindFirstObjectByIdMode4(void* a, void* b, void* c);
typedef s32 (*SlotTest)(void* self);
void StartPlacedObject(void* self);
s32 HasAnimationEventKind19(void* node);
void ResolveAndStartObject(void* node);
typedef void (*SlotFn)(void* self);
void* FindOrCreateSeekedAnimationPlayer(void* item, s32 a, f32 x, s32 b, f32 y, s32 c);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
s32 IsObjectAttached(void* self);
void CopyCollider(void*);
void InitObjectSet(ObjectSet*);
void ApplyColliderPendingImpulse(void);
void RegisterObject(void*);
void AppendToList(void*, void*);
void UnregisterObject(void*);
void RemoveFromList(void*, void*);
void StartObject(void*);
void* FindFirstObjectById(void*, s32, s32, void*);
void RegisterCollider(void*);
void UnregisterCollider(void*);
void InitObject(void*);
void HandlePlacedObjectNotification(ObjectSet* self, s32 msg, ObjectMessage* m);
s32 IsObjectOfKind(void* obj, s32 kind);
void* GetActiveSwitchedColliderData();
s32 IsObjectDescendantOf(void* e, void* b);
struct ActiveColliderData {
    u8 pad0[0x18];
    void* f18;
};
struct LevelTaskRecord { s32 flags; u8 rest[0x74]; };
struct ElementStackState { u8 pad0[0x30]; s32 f30; };
extern ElementStackState g_elementStack;
void MarkLevelRecordComplete(s32 index);
void RequestWorldLoadByMode(s32 mode);
void InitSwitchedCollider(C17* self);
struct C17Marker { s32 owner; s32 object; s32 walker; };
s32 FindFirstObjectById(s32 a, s32 b, s32 c, s32 d);
void ResolveAndStartObject(s32 a);
s32 CreateStateWalker(s32 a, s32 b, s32 c, s32 d);
void GetStateWalkerTargetKey(void* dev, s32* out);
void GetStateWalkerCurrentKey(void* dev, s32* out);
void SetStateWalkerTarget(void* dev, s32 value);
void ResetPadStepRepeat(void* p);
s32 ComputeCompletionMask(void);
void FadeOutAndQueueMovie(s32 value);
void* FindFirstObjectByIdMode4(void* a, s32 code, void* c);
extern u8 g_padRecord[];
void CopyObjectData(void* self);
void ResolveObjectLinks(void* self, s32 n, void* table);
extern u8 g_flagTable[];
void InitObjectSet(ObjectSet* self);
void* TakeFlagTableIndex(void* p);
void LoadObjectSet(ObjectSet* self);
void ResolveObjectLinks(void* self, s32 a1, void* a2);
void* AllocateFrontMemory(s32 size);
struct GatherTrigger { u8 pad[0x20]; Quad16 q20; Quad16 q30; };
void func_0019C1C0(void* self, s32 mode);
s32 GetObjectSetActivationState(ObjectSet* self);
s32 TestFlagTableBit(void* table, s32 index);
void SetFlagTableBit(void* table, s32 index);
void CollectObjectSet(ObjectSet* self);
typedef void (*SlotFnInt)(void* self, s32 a);
void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
s32 HandleObjectEvent(void* self, ObjectEvent* ev);
void CopyCollider(void* self);
void LoadPlacedObject(void* self);
s32 GatherObjectsById(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void FlagNumberedItem(void* obj);
s32 IsObjectOfKind(void* node, s32 kind);
extern f32 g_gameTime[];
f32 RandomGaussian(f32 a, f32 b, f32 c);
void LoadCollider(void* self);
void FindOrBuildMemberGroup(void* sub, void* self);
void* FindFirstObjectByIdMode1(void* self, s32 kind, void* arg);
extern s32 D_00270454;
extern u8 g_memoryCard[];
void SetStateWalkerTarget(void* a, s32 b);
void PopStackElement(void* q);
void ApplyCompletionFlags(s32 mode);
void StartMemoryCardSave(void* p);
void* FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
extern s32 D_00275C34;
void StartObjectSet(ObjectSet* self);
f32 RandomFloatInRange(f32 a, f32 b);
s32 RandomIntInRange(s32 a, s32 b);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void TransformPointBetweenFrames(void* a0, s32 a1, void* a2, void* a3);
Effect* CreateEffect(s32 kind, EffectOwner* sys);
void SetNumberedItemFlag(NumberedItem* self);
void ChooseStepSequenceState(s32 x);
void StartPlacedObject(C17* o);
void ResolveObjectLinks(C17* o, s32 n, u8* t);
void StartC17Marker(void* p, s32 x);
s32 CreateStateWalker(s32 a, C17* b, s32 c, s32 d);
void SetStateWalkerTarget(s32 a, s32 b);
BaseObject* FindFirstObjectByIdMode4(World* a, s32 b, C17* c);
void GetCurrentLevelBit(s32* p);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);
void SetStateWalkerTarget(void* p, s32 n);
void* FindOrCreateSeekedAnimationPlayer(void* self, s32 key, s32 a2, s32 a3, f32 fa, f32 fb);
void QueuePlayerWalkerActivation(Player* a, s32 v);
struct ListWalkFrame {
    s32 list; s32 cursor; s32 link; s32 prev;
    ListWalkFrame(List01* l) {
        cursor = (s32)l;
        list = (s32)l;
        link = l->offset;
        prev = *(s32*)&g_activeListFrames;
        *(s32*)&g_activeListFrames = (s32)this;
    }
};
void ResolveAndStartObject(BaseObject* n);
s32 IsObjectOfKind(void* key, s32 kind);
s32 IsObjectAttached(void* p);
void HandleSwitchedColliderNotification(void* self, s32 code, s32* rec);
void SetPlayerState(void* self, s32 a, s32 b);
s32 CompletesWorldBits(s32 bits);
void ChooseStepSequenceState(StepSequence* s);
void InitCollider(Collider* self);
void AppendToList(void* list, void* item);
void RemoveFromList(void* table, void* self);
extern f32 g_gameClock[];
void func_0019CEC0(void* a, void* b, void* c, f32 d);
void func_0019D0E0(void* a, void* b, void* c, void* d, void* e);
void func_0019C9C8(void* a, s32 b, void* c);
void UnregisterCollider(Collider* self);
struct LoadStream;
s32 ReadBufferedS16(LoadStream* in);
void func_00137FB0(LoadStream* in, void* p);
void* AllocateZeroedFrontMemory(s32 n);
s32 ReadBufferedS8(LoadStream* in);
void DecodeC8BGridIndex(C8B* o, s32 i, f32* x, f32* y, f32* z);
void ComputeGridBlendWeights(f32 x, f32 y, f32 z, C8B* o, void* p);
f32 ReadBufferedFloat(LoadStream* in);
void ReadPropertyRecords(C8B* o, LoadStream* in);
struct ListWalker;
struct ListWalker {
    List01 *list;
    s32 *cur;
    s32 step;
    ListWalker *prev;
    ListWalker(List01 *l)
    {
        list = l;
        cur = (s32 *)&l->head;
        step = l->offset;
        prev = ((ListWalker*)g_activeListFrames);
        g_activeListFrames = (ListFrame*)this;
    }
    ~ListWalker() { g_activeListFrames = (ListFrame*)prev; }
    s32 Next()
    {
        s32 n = *cur;
        cur = (s32 *)(n + step);
        return n;
    }
};
void RemoveFromList(List01 *a, ObjectGatherer *b);
void AppendToList(List01 *a, ObjectGatherer *b);
void TransformPointBetweenFrames(void *a, s32 b, void *c, Quad4 *d);
void PlaceColliderClearOfContacts(ObjectGatherer *a, Quad4 *b, void *c);
void SetColliderPartListed(ObjectGatherer *self, s32 flag);
void StartObject(void* self);
void* FindFirstObjectByIdMode4(void* a, s32 b, void* c);
void* FindFirstObjectByIdMode1(void* a, s32 b, void* c);
void ComputeWrappedDeltas(s32 a, s32 b, void* c, s32 d, s32 e, void* f);
void BuildCombinedBlendAnimation(void* self, s32 a, s32 b, void* c, s32 d, void* e, void* f, void* g);
void SetBlendEntryRecordFlag(void* g, void* n);
void ComputeGridBlendWeights(C8B* self, f32* out, f32 a, f32 b, f32 c);
void SetBlendItemWeights(void* g, s32 a, s32 b, void* c);
void func_0012CD78(f32 a, f32 b, Gr8B* g, void* r1, void* r2, s32 r3, void* r4, s32 r5, s32 r6, s32 r7);
f32 D_0026A910 = 100.0f;
s32 D_0026A914 = 0;
ObjectLink D_0026A918[1] = { { 0x0, 0x22B, 0x2D0 } };
ObjectLink D_0026A928[1] = { { 0x0, 0x22D, 0x2D8 } };
ObjectLink D_0026A938[1] = { { 0x0, 0x22C, 0x2D4 } };
ObjectLink g_numberedItemLinks[1] = { { 0x0, 0x339, 0x5BC } };
f32 D_0026A958[2] = { 0.8f, 1.2f };
f32 D_0026A960[2] = { 0.9f, 1.1f };
f32 D_0026A968 = 300.0f;
T219C_Params D_0026A970 = { { 0.85f, 0.75f, 100.0f, 0.0f, 1.0f, -3.0f, 0.0f, 0.0f, -1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.2f, 0.25f, 0.0f }, (void (*)(void*))SetNumberedItemFlag };
s32 D_0026A9E0[28] = { 2, 4, 8, 16, 65536, 32, 64, 128, 256, 512, 131072, 1024, 2048, 8192, 4096, 16384, 32768, 0, 0, 0, 0, 0, 0, 268435456, 536870912, 1073741824, (-2147483647 - 1), 1 };
struct C17LinkTable { ObjectLink e[26]; s32 end[2]; };
C17LinkTable D_0026AA50 = { {
    { 0, 0x376, 0x610 }, { 0, 0x37C, 0x618 }, { 4, 0x377, 0x61C }, { 4, 0x378, 0x628 }, { 4, 0x379, 0x634 }, { 6, 0x3A2, 0x768 }, { 6, 0x3A4, 0x76C }, { 6, 0x3A5, 0x770 }, { 6, 0x3A6, 0x774 }, { 6, 0x3A7, 0x77C }, { 6, 0x3A8, 0x780 }, { 6, 0x3A9, 0x784 }, { 6, 0x3AB, 0x788 }, { 6, 0x3AC, 0x78C }, { 6, 0x3AD, 0x790 }, { 6, 0x3AE, 0x794 }, { 6, 0x3AF, 0x798 }, { 6, 0x3B0, 0x79C }, { 6, 0x3B1, 0x7A0 }, { 6, 0x3B2, 0x7A4 }, { 6, 0x3B3, 0x7A8 }, { 6, 0x3B4, 0x7C4 }, { 6, 0x3B5, 0x7C8 }, { 6, 0x3B6, 0x7CC }, { 6, 0x3B7, 0x7D0 }, { 6, 0x3D8, 0x7D4 } }, { 0, 0 } };
ObjectLink g_objectGathererLoadLinks[1] = { { 0x0, 0x268, 0x5EC } };
ObjectLink g_objectGathererStartLinks[1] = { { 0x4, 0x267, 0x5FC } };
f32 D_0026ABB0[4] = { 12.0f, 0.0f, 0.12f, 0.0f };
f32 D_0026ABC0[4] = { 500.0f, 1.0f, 0.0f, 0.0f };
s32 D_0026ABD0[2] = { 0x130, 0x132 };
s32 D_0026ABD8[2] = { 2, 0 };
s32 D_0026ABE0[4] = { 0x10, 0, 0, 0 };
void* GetActiveSwitchedCollider();
void MeasurePointToSegment(void* p, Vec02* a, Vec02* b, f32* t, f32* dist);

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

struct GatherCandidate {
    u8 pad00[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x40 - 0x1C];
    Vec02 pos;              // 0x40
};

// Picks, of the class 0x7C objects within reach, the one farthest from the active collider along
// the segment to it, and keeps it in f660.
void func_0019BE80(ObjectGatherer* self)
{
    ListFrame frame;
    Vec02 point;
    f32 t;
    f32 dist;
    f32 bestDist;
    f32 bestT;
    f32 bestLen;
    GatherCandidate* best;
    if (GetActiveSwitchedCollider() == 0) {
        return;
    }
    best = 0;
    bestDist = 0.0f;
    BeginListWalk::Of(&frame, &self->world->list1C6C);
    GatherCandidate* node;
    while ((node = NextInList<GatherCandidate>::Of(&frame)) != 0) {
        TransformPointBetweenFrames(node->frame, 0, &node->pos, (Quad4*)&point);
        f32 reach = *(f32*)((u8*)self + 0x624);
        f32 reach2 = reach * reach;
        u128 off = Vu0::Sub(Vu0::Q(point), Vu0::Q(self->v140));
        s32 far = reach2 < Vu0::ToFloat(Vu0::Dot(off, off));
        if (!far) {
            MeasurePointToSegment((u8*)GetActiveSwitchedCollider() + 0x140, &self->v140, &point, &t, &dist);
            f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(point), Vu0::Q(self->v140))));
            if (bestDist < dist || (t < 0.0001f && bestT < 0.0001f && len < bestLen)) {
                bestT = t;
                bestDist = dist;
                best = node;
                bestLen = len;
            }
        }
    }
    self->f660 = best;
    g_activeListFrames = frame.prev;
}
