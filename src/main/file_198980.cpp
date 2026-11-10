// SPDX-License-Identifier: AGPL-3.0-or-later
// The source file from 0x198980 to 0x19D410, built whole (config/us/files.tsv): one file between
// two exact edges, which could be several. It holds the object sets (class 0x2C) and the
// classes built on them (0x2D, 0x2E), classes 0x5C and 0x5D, class 0x17, class 0x71, the object
// gatherer (class 0x41), class 0x7C and class 0x8B with the VU0 helpers only it and
// func_0019D2A8/func_0019D338 call. Its .rodata (0x24C870 to 0x24C930) is the jump tables of
// func_0019A6A8, func_0019B378 and func_0019C1C0 and the FLT_MAX literal of
// func_0019AF00; its .data (0x26A910 to 0x26ABF0) is the globals below, all initialised. Named
// after its first address until what it was is known.
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
#include "pad_record.h"
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
// A descriptor slot called by its index (the slots past class 0x01's, whose types the
// descriptors give differently).
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
// The active switched collider's data block (SwitchedCollider + 0x580): at 0x18 the collider.
struct ActiveColliderData {
    u8 pad0[0x18];
    void* f18;
};
// One of the nine 0x78-byte records at the start of a level's record (G27C230): its flags.
struct LevelTaskRecord { s32 flags; u8 rest[0x74]; };
// The element stack (g_elementStack), as file_15F678.cpp and file_16AA18.cpp view it.
struct ElementStackState { u8 pad0[0x30]; s32 f30; };
extern ElementStackState g_elementStack;
void MarkLevelRecordComplete(s32 index);
void RequestWorldLoadByMode(s32 mode);
void InitSwitchedCollider(C17* self);
// One of C17's three markers at 0x61C (StartC17Marker): its owner, the object found for it and
// that object's state walker.
struct C17Marker { s32 owner; s32 object; s32 walker; };
s32 FindFirstObjectById(s32 a, s32 b, s32 c, s32 d);
void ResolveAndStartObject(s32 a);
s32 CreateStateWalker(s32 a, s32 b, s32 c, s32 d);
void GetStateWalkerTargetKey(void* dev, s32* out);
void GetStateWalkerCurrentKey(void* dev, s32* out);
void SetStateWalkerTarget(void* dev, s32 value);
void ActivateSwitchedCollider(void* value);
void ShowModeLabel(u32 mode);
s32 GetPadHorizontalStep(PadRecord* p);
s32 GetPadVerticalStep(PadRecord* p);
void ClearPadPressedBits(PadRecord* p, s32 mask);
void RecordC17ColliderCompletion(C17* self);
void CopyMemory(void* dst, void* src, s32 size);
void ResetPadStepRepeat(void* p);
s32 ComputeCompletionMask(void);
void FadeOutAndQueueMovie(s32 value);
void* FindFirstObjectByIdMode4(void* a, s32 code, void* c);
void CopyObjectData(void* self);
void ResolveObjectLinks(void* self, s32 n, void* table);
extern u8 g_flagTable[];
void InitObjectSet(ObjectSet* self);
void* TakeFlagTableIndex(void* p);
void LoadObjectSet(ObjectSet* self);
void ResolveObjectLinks(void* self, s32 a1, void* a2);
void* AllocateFrontMemory(s32 size);
// What func_0019BE08 is given: two quadwords at 0x20 and 0x30.
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
void StartSoundEffect(s32 a0, void* a1, void* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
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
// A list walk's frame (as ListFrame), pushed by its constructor.
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
// A list walk's frame (as ListFrame) that pushes itself and pops itself when it goes.
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

// The file's .data, in retail's order. D_0026A910 and D_0026A914 are read by the VU0 function
// func_00198BD8, D_0026A968 by func_00199698, D_0026ABB0 and D_0026ABC0 by func_0019B298 and
// func_0019B378.
f32 D_0026A910 = 100.0f;
f32 D_0026A914 = 0.0f;
ObjectLink D_0026A918[1] = { { 0x0, 0x22B, 0x2D0 } };
ObjectLink D_0026A928[1] = { { 0x0, 0x22D, 0x2D8 } };
ObjectLink D_0026A938[1] = { { 0x0, 0x22C, 0x2D4 } };
ObjectLink g_numberedItemLinks[1] = { { 0x0, 0x339, 0x5BC } };
f32 D_0026A958[2] = { 0.8f, 1.2f };
f32 D_0026A960[2] = { 0.9f, 1.1f };
f32 D_0026A968 = 300.0f;
T219C_Params D_0026A970 = { { 0.85f, 0.75f, 100.0f, 0.0f, 1.0f, -3.0f, 0.0f, 0.0f, -1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.2f, 0.25f, 0.0f }, (void (*)(void*))SetNumberedItemFlag };
s32 D_0026A9E0[28] = { 2, 4, 8, 16, 65536, 32, 64, 128, 256, 512, 131072, 1024, 2048, 8192, 4096, 16384, 32768, 0, 0, 0, 0, 0, 0, 268435456, 536870912, 1073741824, (-2147483647 - 1), 1 };
// The links func_0019A1E0 resolves for a C17, and two words after them that retail's label
// holds as zeros (the label runs to the next table, D_0026AB90; nothing reads them).
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


void InitObjectSet(ObjectSet* self)
{
    InitCollider(self);
    self->f554 = 1;
}

void LoadObjectSet(ObjectSet* self)
{
    LoadCollider(self);
    FindOrBuildMemberGroup(&self->f584, self);
    ListWalkFrame fr(&self->children);
    fr.cursor = (s32)self->children.head + fr.link;
    BaseObject* p = (BaseObject*)self->children.head;
    while (p != 0) {
        if (p->desc->flags & 0x40) {
            s32 i = self->count570;
            self->found574[i] = p;
            self->count570 = i + 1;
            ResolveAndStartObject(p);
        }
        s32 nx = *(s32*)fr.cursor;
        fr.cursor = nx + fr.link;
        p = (BaseObject*)nx;
    }
    *(s32*)&g_activeListFrames = fr.prev;
}

void PostLoadObjectSet(ObjectSet* self)
{
    s32 i;

    PostLoadPlacedObject(self);
    for (i = 0; i < self->n55C; i++) {
        void* r = FindFirstObjectByIdMode4(self->world, self->keys560[i], self);
        if (r != 0) {
            self->found574[self->count570++] = r;
        }
    }
}

void StartObjectSet(ObjectSet* self)
{
    s32 i;

    StartPlacedObject(self);
    for (i = 0; i < self->count570; i++) {
        void* node = self->found574[i];
        if (HasAnimationEventKind19(node)) {
            self->f558 = 1;
        }
        ResolveAndStartObject(node);
    }
    if (((SlotTest*)self->desc)[76](self) == 0) {
        self->desc->m03(self);
    }
}

void UpdateCollider(void* self);
void* GetActiveSwitchedCollider();

// The part of the active collider's block at 0x580 that UpdateObjectSet reads.
struct ActiveReach {
    s32 on;                 // 0x00
    u8 pad04[0x14 - 0x04];
    f32 reach;              // 0x14
    PlacedObject* target;   // 0x18
};

// Each frame while the active collider is near: the set moves to a point 100 out from its
// target, on the ground away from the set.
void UpdateObjectSet(ObjectSet* self)
{
    Vec02 d;
    UpdateCollider(self);
    s32 held = self->f59C;
    self->f59C = 0;
    SwitchedCollider* a = (SwitchedCollider*)GetActiveSwitchedCollider();
    if (a == 0) {
        return;
    }
    if (((SlotTest*)self->desc)[76](self) != 1) {
        return;
    }
    ActiveReach* r = (ActiveReach*)&a->f580;
    if (r->on == 0) {
        return;
    }
    if (r->target == 0) {
        return;
    }
    if (held == 0) {
        f32 reach = r->reach + self->f550;
        u128 e = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(r->target->v140));
        s32 far = reach * reach <= Vu0::ToFloatMoved(Vu0::Dot(e, e));
        if (far) {
            return;
        }
    }
    self->desc->m15(self, 0);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(r->target->v140));
    d.z = 0.0f;
    u128 base = Vu0::Q(r->target->v150);
    u128 out = Vu0::ScalarAt(D_0026A910);
    Vu0::Q(d) = Vu0::MulAddX2(base, Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(D_00248D30)), out, Vu0::Q(g_unitZVector), Vu0::ScalarAt(D_0026A914));
    self->desc02()->m20(self, &d);
    ((SlotFn*)self->desc)[77](self);
}

void CollectObjectSet(ObjectSet* self)
{
    SlotFn fn = ((SlotFn*)self->desc)[7];
    fn(self);
    s32 i = self->count570;
    i--;
    for (; i >= 0; i--) {
        (void)FindOrCreateSeekedAnimationPlayer(self->found574[i], 0, 0.0f, 1, 1.0f, 0);
    }
    ((SlotFn*)self->desc)[78](self);
    (void)TriggerScriptEvent(self, 2, 0, 0);
}

void NotifyObjectSetTarget(ObjectSet* self)
{
    BaseObject* t = (BaseObject*)self->f584;
    if (t != 0) {
        SlotMessage msg;
        msg.kind = 1;
        msg.owner = self;
        t->desc->m1B(t, &msg);
    }
}

s32 GetObjectSetActivationState(ObjectSet* self)
{
    if (IsObjectAttached(self)) {
        return (self->f554 != 0) ? 1 : 2;
    }
    return 0;
}

void AddObjectSetKey(ObjectSet* queue, void* item)
{
    queue->keys560[queue->n55C++] = item;
}

void HandleObjectSetNotification(ObjectSet* self, s32 msg, ObjectMessage* m)
{
    (void)HandlePlacedObjectNotification(self, msg, m);
    if (msg == 5) {
        for (s32 i = 0; i < self->count570; i++) {
            if (m->key == (s32)self->found574[i]) {
                self->marks588[i] = 1;
            }
        }
        Player* g = g_player;
        if (g != 0) {
            if (m == g->watched2230) {
                g->desc->m18(g, self);
                self->done598 = 1;
            }
        }
    }
}

s32 TestObjectSetMayContact(ObjectSet* unused, void* obj)
{
    if (IsObjectOfKind(obj, 8) != 0 || IsObjectOfKind(obj, 0x3B) != 0) {
        return 1;
    }
    return 0;
}

void LatchObjectSetContact(ObjectSet* self, Contact03* elems, s32 idx)
{
    ActiveColliderData* r = (ActiveColliderData*)GetActiveSwitchedColliderData();
    if (r->f18 == 0) return;
    {
        s32 one = 1;
        ContactEnd03* e = (ContactEnd03*)((u8*)elems + ((one - idx) << 6));
        if (IsObjectDescendantOf(e->part, r->f18) != 0) {
            self->f59C = one;
        }
    }
}

void InitFlaggedObjectSet(FlaggedObjectSet* self)
{
    InitObjectSet(self);
    self->f5A0 = (s32)TakeFlagTableIndex(g_flagTable);
}

void CopyFlaggedObjectSet(FlaggedObjectSet* obj)
{
    s32 value = obj->f5A0;
    CopyCollider(obj);
    obj->f5A0 = value;
}

s32 GetFlaggedObjectSetActivationState(FlaggedObjectSet* self)
{
    s32 r = GetObjectSetActivationState(self);
    if (r == 1) {
        r = TestFlagTableBit(g_flagTable, self->f5A0) ? 0 : r;
    }
    return r;
}

void CollectFlaggedObjectSet(FlaggedObjectSet* self)
{
    SetFlagTableBit(g_flagTable, self->f5A0);
    CollectObjectSet(self);
}

void LoadC5CObject(C5C* self)
{
    LoadPlacedObject(self);
    ResolveObjectLinks(self, 1, (u8*)D_0026A918);
}

void StartC5CObject(C5C* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 1, (u8*)D_0026A928);
}

void LoadC5DObject(C5D* self)
{
    LoadPlacedObject(self);
    ResolveObjectLinks(self, 1, (u8*)D_0026A938);
}

void StartC5DObject(C5D* self)
{
    StartPlacedObject(self);
    self->count300 = GatherObjectsById(self->world, 1, 0x5C, self, 8, self->objs304);
    s32 i;
    C5C* e;
    for (i = 0; i < self->count2DC; i++) {
        e = (C5C*)FindFirstObjectById(self->world, 4, self->ids2E0[i], self);
        if (e != 0) {
            u32 k = self->count300;
            if (k < 8) {
                self->objs304[k] = (void*)e;
                self->count300 = k + 1;
            }
        }
    }
    s32 s4 = (g_currentLevelRecord->f448 & self->mask2D0) ? 0x22F : 0x22E;
    for (i = 0; i < self->count300; i++) {
        e = (C5C*)self->objs304[i];
        e->f2D4 = CreateStateWalker(e->f2D0, e, -1, 0);
        SetStateWalkerTarget(e->f2D4, s4);
    }
    self->f2D8 = CreateStateWalker(self->f2D4, self, -1, 0);
    SetStateWalkerTarget(self->f2D8, s4);
}

void SetC5DObjectMaskBit(C5D* flags, u32 bit)
{
    flags->mask2D0 = 1 << (bit + 1);
}

void AddC5DObjectId(C5D* queue, void* item)
{
    u32 count = queue->count2DC;
    if (count < 8) {
        queue->ids2E0[count] = (s32)item;
        queue->count2DC = count + 1;
    }
}

void QueueWalkerActivationOnPlayer(s32 a0) {
    if (g_player != 0) {
        (void)QueuePlayerWalkerActivation(g_player, a0);
    }
}

void InitNumberedItem(NumberedItem* obj)
{
    InitObjectSet(obj);
    obj->f5A0 = obj->world->count2300++;
}

void LoadNumberedItem(NumberedItem* self)
{
    LoadObjectSet(self);
    s32 i = 0x318;
    ResolveObjectLinks(self, 1, (u8*)g_numberedItemLinks);
    self->f5B0 = AllocateFrontMemory(0x80);
    while (i < 0x338) {
        s32 r = (s32)FindFirstObjectById(self->world, 1, i, self);
        if (r == 0) {
            break;
        }
        s32 count = self->n5AC;
        i++;
        ((s32*)self->f5B0)[count] = r;
        self->n5AC = count + 1;
        ResolveAndStartObject(r);
    }
}

void CopyNumberedItem(NumberedItem* obj)
{
    s32 value = obj->f5A0;
    CopyCollider(obj);
    obj->f5A0 = value;
}

void StartNumberedItem(NumberedItem* self)
{
    s32 neg;
    s32 one;
    f32 r;

    StartObjectSet(self);
    self->f5B8 = RandomFloatInRange(-3.14159274f, 3.14159274f);
    self->f5B4 = RandomFloatInRange(D_0026A958[0], D_0026A958[1]);
    if (RandomIntInRange(0, 1) != 0) {
        self->f5B4 = -self->f5B4;
    }
    neg = -1;
    one = 1;
    r = RandomFloatInRange(D_0026A960[0], D_0026A960[1]);
    self->f5A8 = self->f5A8 * r;
    self->f5A4 = RandomFloatInRange(0.0f, self->f5A8 + self->f5A8);

    {
        s32 bit = self->f5A0;
        s32 mask = one << (bit & 7);
        if (g_currentEntry->bits68[bit / 8] & mask) {
            self->desc->m03(self);
        }
    }

    if (D_00275C34 != 0) {
        if (RandomIntInRange(0, 100) < 20) {
            G27C230* d = g_currentEntry;
            s32 bit = self->f5A0;
            s32 mask = one << (bit & 7);
            if (d->bits68[bit / 8] & mask) {
                d->bits68[bit / 8] = d->bits68[bit / 8] & ~mask;
                d->count64--;
            }
            self->desc->m03(self);
        }
    }
}

struct ActiveColliderTarget {
    s32 f0;
    u8 pad4[0x18 - 0x4];
    PlacedObject* f18;
};
s32 MaskWorldBitsBySave(void);
void ComputeObjectMotionInFrame(void* obj, s32 a, void* pos, Vec02* out, s32 b, s32 c, s32 d);

// The reach test reads the target's position at the use (*(const u128*)&...), not through Q's
// reference: the reference's address is a pseudo that CSE then reuses for the &target->v140
// passed after the test, where retail forms it afresh (docs/TOOLCHAIN.md, "CSE").
void UpdateNumberedItem(NumberedItem* self)
{
    Vec02 first;
    Vec02 second;
    UpdateObjectSet(self);
    if ((MaskWorldBitsBySave() & 0x20000) == 0) {
        return;
    }
    if (((SlotTest*)self->desc)[76](self) != 1) {
        return;
    }
    ActiveColliderTarget* data = (ActiveColliderTarget*)GetActiveSwitchedColliderData();
    if (data->f0 == 0) {
        return;
    }
    PlacedObject* target = data->f18;
    if (target == 0) {
        return;
    }
    u128 gap = Vu0::Sub(*(const u128*)&target->v140, Vu0::Q(self->v140));
    if (D_0026A968 * D_0026A968 < Vu0::ToFloatMoved(Vu0::Dot(gap, gap))) {
        return;
    }
    ComputeObjectMotionInFrame(target, 0, &target->v140, &first, 0, 0, 0);
    ComputeObjectMotionInFrame(self, 0, &self->v140, &second, 0, 0, 0);
    u128 rel = Vu0::Sub(Vu0::Q(second), Vu0::Q(first));
    u128 away = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(data->f18->v140));
    u128 dir = Vu0::NormalizeOrMoved(away, Vu0::Q(D_00248D30));
    if (Vu0::ToFloat(Vu0::Dot(rel, dir)) > -50.0f) {
        ((SlotFn*)self->desc)[77](self);
    }
}

void SetNumberedItemFlag(NumberedItem* self)
{
    f32 zf;
    G27C230* ctx = g_currentEntry;
    zf = 0.0f;
    s32 n = self->f5A0;
    u8* p = ctx->bits68;
    s32 byte = n / 8;
    p += byte;
    s32 b = *p;
    s32 mask = 1 << (n & 7);
    if ((b & mask) == 0) {
        *p = (u8)(b | mask);
        ctx->count64++;
    }
    s32 count = g_currentEntry->count64;
    s32 s0 = -1;
    s32 s1 = 0;
    if (((g_saveData->f19EC ^ 1) & 1) != 0) {
        if (count > 0) {
            s0 = 0x348;
            s1 = 1;
        }
    } else if ((g_saveData->f19EC & 4) == 0) {
        if (count < g_currentWorld->count2300) {
            goto L980;
        }
        s0 = 0x34A;
        s1 = 4;
    }
    if (count < g_currentWorld->count2300) {
        goto L980;
    }
    StartSoundEffect(0x6A, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
L980:
    g_saveData->f19EC = g_saveData->f19EC | s1;
    s32 r = (s32)FindFirstObjectById((void*)g_currentWorld, 1, s0, 0);
    if (r != 0) {
        ChooseStepSequenceState(r);
    }
}

void CollectNumberedItem(NumberedItem* self)
{
    Quad16 loc;
    T217D_E30* g = &D_0026C948;
    g->vt->m14(g);
    Effect* n = CreateEffect(0x10, 0);
    if (n != 0) {
        if (g_currentEntry->count64 + 1 >= g_currentWorld->count2300) {
            f32 z = 0.0f;
            StartSoundEffect(0x21, 0, 0, 0, 3000.0f, 300.0f, 1.0f, z, z, 0, 0);
        }
        n->p134 = self;
        n->params = &D_0026A970;
        TransformPointBetweenFrames(self, 0, self->f5BC + 0x100, &loc);
        n->vt->m00(n, &loc, 1.0f, 0);
        n->i20 = *(s32*)&self->f5BC;
    } else {
        SetNumberedItemFlag(self);
    }
    CollectObjectSet(self);
}

void func_00199AF0(NumberedItem* p)
{
    ((SlotFn*)p->desc)[77](p);
}

void FlagNumberedItem(NumberedItem* self)
{
    self->desc->m03(self);
    s32 n = self->f5A0;
    G27C230* m = g_currentEntry;
    s32 idx = n / 8;
    u8 cur = m->bits68[idx];
    s32 mask = 1 << (n & 7);
    if (!(cur & mask)) {
        m->bits68[idx] = cur | mask;
        m->count64 = m->count64 + 1;
    }
    s32 i = self->count570;
    i--;
    while (i >= 0) {
        FindOrCreateSeekedAnimationPlayer(self->found574[i], 0, 1, 0, 0.0f, 1.0f);
        i--;
    }
    TriggerScriptEvent(self, 2, 0, 0);
}

void GetNumberedItemFlag(NumberedItem* self, s32* out)
{
    s32 n = self->f5A0;
    s32 byte = n / 8;
    s32 bit = n & 7;
    u8 b = g_currentEntry->bits68[byte];
    s32 mask = 1;
    mask <<= bit;
    *out = (b & mask) != 0;
}

void ApplyNumberedItemPendingImpulse(void)
{
    ApplyColliderPendingImpulse();
}

s32 HandleNumberedItemObjectEvent(NumberedItem* self, ObjectEvent* a1)
{
    if (a1->eventFlags & 0x8) {
        ((SlotFnInt)((void**)self->desc)[25])(self, 0);
        SetColliderAnchors(self, 0, 0, 3, 0);
    }
    HandleObjectEvent(self, a1);
    if (a1->eventFlags & 0x10) {
        ((SlotFn)((void**)self->desc)[77])(self);
    }
    return 1;
}

struct SpinFrame4 {
    Vec02 r[4];
};

struct SpinKeyframe {
    u8 pad00[0x40];
    u8 from[0x10];          // 0x40
    u8 to[0x10];            // 0x50
};

void BuildAxisAngleMatrix(const Vec02* axis, f32 angle, Mat02* out);
void RotateMatrixUpright(Mat02* sub, s32 zero, Mat02* out);
void BuildPlacedObjectTransform(NumberedItem* self, void* a, SpinFrame4* out);
void BuildMatrixFromRotationAndTranslation(void* rot, void* from, SpinFrame4* out);
void MultiplyMatrices(SpinFrame4* out, SpinFrame4* b, SpinFrame4* in);
void func_00125C90(NumberedItem* self, void* a, SpinFrame4* m);

static inline void MulRotation(Mat02* out, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    const u128* rows = (const u128*)&a;
    u128 a0 = rows[0];
    u128 a1 = rows[1];
    u128 a2 = rows[2];
    Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    r.r[2] = z;
    *out = r;
}

// Turns the item by its spin and builds its transform for the frame, with the keyframe its
// phase picks in the ring of its objects.
void SpinNumberedItemTransform(NumberedItem* self, void* a1, void* a2)
{
    Mat02 axis;
    Mat02 turned;
    SpinFrame4 base;
    Vec02 unused;
    if (self->flags & ((u64)0x8000 << 17)) {
        return;
    }
    self->f5B8 = self->f5B8 + self->f5B4 * g_gameClock[2];
    BuildAxisAngleMatrix(&g_unitZVector, self->f5B8, &axis);
    MulRotation(&turned, *(const Mat02*)((u8*)self + 0x110), axis);
    if (self->parent != 0) {
        RotateMatrixUpright(&turned, 0, &turned);
    }
    BuildPlacedObjectTransform(self, a2, &base);
    BuildMatrixFromRotationAndTranslation(&self->v140, &turned, &base);
    if (self->n5AC > 0) {
        SpinFrame4 key;
        SpinFrame4 product;
        self->f5A4 = self->f5A4 + g_gameClock[2];
        while (self->f5A8 + self->f5A8 <= self->f5A4) {
            self->f5A4 = self->f5A4 - (self->f5A8 + self->f5A8);
        }
        s32 index = (s32)((f32)self->n5AC * self->f5A4 / self->f5A8);
        if (index >= self->n5AC) {
            s32 twice = self->n5AC * 2;
            s32 m = index + 1;
            index = twice - m;
        }
        SpinKeyframe* k = ((SpinKeyframe**)self->f5B0)[index];
        BuildMatrixFromRotationAndTranslation(k->from, k->to, &key);
        MultiplyMatrices(&product, &base, &key);
        base = product;
    }
    func_00125C90(self, a1, &base);
}

void FlagAllNumberedItems(void)
{
    void* arr[0x100];
    s32 i = GatherObjectsById((void*)g_currentWorld, 0x105, 0x2E, 0, 0x100, arr) - 1;
    if (i >= 0) {
        void** p = (void**)(i * 4 + (s32)arr);
        do {
            FlagNumberedItem(*p);
            if (((BaseObject*)*p)->parent != 0) {
                if (IsObjectOfKind(((BaseObject*)*p)->parent, 0x20) != 0) {
                    BaseObject* s = ((BaseObject*)*p)->parent;
                    s->desc->m03(s);
                }
            }
            i--;
            p--;
        } while (i >= 0);
    }
    D_0026C948.vt->m14(&D_0026C948);
}

void SetSavedWorldBits(u32 value)
{
    g_saveData->u19F0 = value;
}

s32 CompletesWorldBits(s32 bits)
{
    s64 mask = 0xF000;
    mask <<= 16;
    mask |= 0xFFFF;
    if ((g_saveData->f19F0 & mask) == mask) {
        return 0;
    }
    if (ComputeCompletionMask() & 2) {
        return 0;
    }
    GameProgress* c = g_saveData;
    s64 v = c->f19F0 | bits;
    s32 r = 1;
    if ((v & mask) ^ mask) {
        r = 0;
    }
    return r;
}

void MarkLevelRecordComplete(s32 index)
{
    if (index == -1) index = g_saveData->f19D8;
    u8* base = (u8*)g_saveData + (index * 0x44C + 0x10);
    LevelTaskRecord* p = (LevelTaskRecord*)base;
    LevelTaskRecord* end = (LevelTaskRecord*)(base + 0x438);
    do {
        p->flags |= 1;
        p++;
    } while ((s32)p < (s32)end);
    *(s32*)(base + 0x448) |= 0x1F;
}

void MarkAllLevelRecordsComplete()
{
    for (s32 i = 0; i < 6; i++) MarkLevelRecordComplete(i);
    if (g_elementStack.f30 == 2) RequestWorldLoadByMode(0);
}

void InitC17Collider(C17* self)
{
    InitSwitchedCollider(self);
    self->f64C = -1;
    self->f644 = -1;
}

void StartC17Marker(C17Marker* self, s32 x)
{
    self->object = FindFirstObjectById((s32)g_currentWorld, 0x101, 0x37A, self->owner);
    ResolveAndStartObject(self->object);
    self->walker = CreateStateWalker(self->object, self->owner, x, 0);
}

void StartC17Collider(C17* o)
{
    u32 i;
    StartPlacedObject(o);
    ResolveObjectLinks(o, 0x1A, (u8*)D_0026AA50.e);
    for (i = 0; i < 3; i++)
        StartC17Marker(o->f61C + i * 12, 0x390);
    s32 h = CreateStateWalker(o->f610, o, 0x384, 1);
    o->f764 = -1;
    o->f614 = (StateWalker*)h;

    if (g_currentEntry->bits & 4) {
        SetStateWalkerTarget(h, 0x38F);
        return;
    }
    o->world->f1CE4 = o;
    for (s32 e = 0; e < 6; e++) {
        Ent17* en = &o->f658[e];
        for (s32 k = 0; k < en->count; k++) {
            BaseObject* r = FindFirstObjectByIdMode4(o->world, en->keys[k], o);
            if (r) {
                en->list[en->n++] = r;
            }
        }
        if (en->n > 0)
            en->pick = RandomIntInRange(0, en->n - 1);
    }
    o->f648 = (void*)FindFirstObjectByIdMode4(o->world, o->f644, o);
    o->f650 = FindFirstObjectByIdMode4(o->world, o->f64C, o);
    if (((BaseObject*)o->f650))
        ((BaseObject*)o->f650)->desc->m17(((BaseObject*)o->f650), o);
    if (((g_saveData->f19D8 << 8) | g_saveData->f19DC) == 3) {
        o->f760 = 1;
    } else {
        GetCurrentLevelBit(&o->f760);
        if (o->f760 & 0xF000FFFFl) {
            s32 cnt = 0;
            LevelTaskRecord* p = (LevelTaskRecord*)g_currentLevelRecord;
            LevelTaskRecord* end = p + 9;
            do {
                if (p->flags & 4)
                    cnt++;
                p++;
            } while (p < end);
            if (cnt != 2)
                o->f760 = 0;
            if (o->f760 & 0xF000FFFFl) {
                o->f764 = 0;
                goto lookup;
            }
        }
        o->f760 = 2;
        if (g_saveData->u19F0 & 2) {
            do {
                o->f760 = o->f760 << 1;
            } while ((o->f760 & 0xF000FFFFl) && (g_saveData->u19F0 & o->f760));
        }
        o->f760 &= (s32)0xF000FFFF;
    }
    if ((o->f760 & 0xF000FFFFl) == 0)
        return;
    o->f764 = 0;
lookup:
    if (D_0026A9E0[0] != (s32)o->f760) {
        do {
            o->f764++;
            if (o->f764 >= 0x1C) {
                o->f764 = -1;
                return;
            }
        } while (D_0026A9E0[o->f764] != (s32)o->f760);
    }
    if (o->f764 >= 0x1C)
        o->f764 = -1;
}

void HandleC17ColliderActivation(C17* self, s32 flag)
{
    s32 r;
    s32 flags;
    void* a;
    s32 n;

    GetStateWalkerTargetKey(self->f614, &r);
    if (r == -1) {
        GetStateWalkerCurrentKey(self->f614, &r);
    }
    if (flag != 0) {
        if (r != 0x38F) {
            SetStateWalkerTarget(self->f614, 0x385);
        }
        ResetPadStepRepeat(&g_padRecord);
        flags = g_saveData->f19EC;
        if ((flags & 8) == 0) {
            a = FindFirstObjectByIdMode4((void*)g_currentWorld, 0x39A, self);
        } else {
            if ((flags & 0x10) != 0) {
                goto tail;
            }
            a = FindFirstObjectByIdMode4((void*)g_currentWorld, 0x39B, self);
        }
        if (a != 0) {
            n = self->f7D8;
            self->f7DC[n] = a;
            self->f7D8 = n + 1;
        }
tail:
        a = self->f648;
        if (a != 0) {
            n = self->f7D8;
            self->f7DC[n] = a;
            self->f7D8 = n + 1;
        }
        if (g_player != 0) {
            self->blk580 = g_player->blk580;
            self->f604 = g_player->f604;
        }
    } else {
        if (r != 0x38F) {
            SetStateWalkerTarget(self->f614, 0x384);
        }
        self->f7D8 = 0;
        if ((ComputeCompletionMask() & 4) != 0) {
            FadeOutAndQueueMovie(4);
        }
    }
}

// The combination lock: the pad turns the three dials (each key 0x385..0x38D a dial and a digit
// band, 0x38E open, 0x38F done), the dials matching f640's digits open it, and the queued step
// sequences run one at a time.
void ControlC17Collider(C17* self, PadRecord* pad)
{
    s32 cur;
    s32 target;

    GetStateWalkerCurrentKey(self->f614, &cur);
    GetStateWalkerTargetKey(self->f614, &target);
    s32 key = target == -1 ? cur : target;
    if (cur == 0x38F) {
        ActivateSwitchedCollider(g_player);
        return;
    }
    if (cur == 0x38E && target == cur) {
        if (self->f7D8 == 0 && D_0027051C == 0) {
            SetStateWalkerTarget(self->f614, 0x38F);
            switch (self->f760) {
            case 2:
            case 0x10:
                ShowModeLabel(0);
                break;
            case 0x80:
                ShowModeLabel(4);
                break;
            case 8:
            case 0x1000:
                ShowModeLabel(2);
                break;
            case 4:
            case 0x400:
                ShowModeLabel(1);
                break;
            case 0x200:
                ShowModeLabel(5);
                break;
            case 0x8000:
                ShowModeLabel(6);
                break;
            case 0x40:
                ShowModeLabel(3);
                break;
            }
        }
    } else if (target != 0x38F) {
        if (target == 0x38E)
            return;
        s32 dir = -1;
        s32 h = GetPadHorizontalStep(pad);
        s32 v = GetPadVerticalStep(pad);
        if (h < 0)
            dir = 1;
        else if (h > 0)
            dir = 0;
        else if (v < 0)
            dir = 2;
        else if (v > 0)
            dir = 3;
        else if (pad->flags & 0x20)
            dir = 0;
        else if (pad->flags & 0x80)
            dir = 1;
        else if (pad->flags & 0x10)
            dir = 2;
        else if (pad->flags & 0x40)
            dir = 3;
        ClearPadPressedBits(pad, 0xF0);
        switch (dir) {
        case 0:
            if (key < 0x385)
                break;
            if (key < 0x388)
                SetStateWalkerTarget(self->f614, 0x388);
            else if (key < 0x38B)
                SetStateWalkerTarget(self->f614, 0x38B);
            break;
        case 1:
            if (key < 0x388)
                break;
            if (key < 0x38B)
                SetStateWalkerTarget(self->f614, 0x385);
            else if (key < 0x38E)
                SetStateWalkerTarget(self->f614, 0x388);
            break;
        case 2:
            switch (key) {
            case 0x385:
            case 0x386:
            case 0x387:
                SetStateWalkerTarget(self->f614, 0x386);
                break;
            case 0x388:
            case 0x389:
            case 0x38A:
                SetStateWalkerTarget(self->f614, 0x389);
                break;
            case 0x38B:
            case 0x38C:
            case 0x38D:
                SetStateWalkerTarget(self->f614, 0x38C);
                break;
            }
            break;
        case 3:
            switch (key) {
            case 0x385:
            case 0x386:
            case 0x387:
                SetStateWalkerTarget(self->f614, 0x387);
                break;
            case 0x388:
            case 0x389:
            case 0x38A:
                SetStateWalkerTarget(self->f614, 0x38A);
                break;
            case 0x38B:
            case 0x38C:
            case 0x38D:
                SetStateWalkerTarget(self->f614, 0x38D);
                break;
            }
            break;
        }
        s32 i = 0;
        s32 code = *(s32*)(self->f61C + 0x24);
        for (; i < 3; i++, code *= 10) {
            C17Marker* m = &((C17Marker*)self->f61C)[i];
            s32 t;
            s32 c;
            GetStateWalkerTargetKey((void*)m->walker, &t);
            if (t != -1)
                break;
            GetStateWalkerCurrentKey((void*)m->walker, &c);
            if (c - 0x390 != code / 100 % 10)
                break;
        }
        if (i >= 3 && (g_currentEntry->flags & 4) == 0) {
            RecordC17ColliderCompletion(self);
            return;
        }
    }
    if (self->f7D8 > 0 && D_0027051C == 0) {
        ChooseStepSequenceState((StepSequence*)self->f7DC[0]);
        self->f7D8--;
        CopyMemory(&self->f7DC[0], &self->f7DC[1], self->f7D8 * 4);
    }
}

void HandleC17ColliderNotification(C17* self, s32 msg, s32* rec)
{
    HandleSwitchedColliderNotification(self, msg, rec);
    if (msg == 12 && rec[1] == (s32)self->f650) {
        if (self->f654 != 0 && g_player != 0) {
            g_player->f23CC = self;
            g_player->f239C = 7;
            SetPlayerState(g_player, 6, 16);
        } else {
            s32 k;
            s32 a;
            s32 b;
            D_0026C948.vt->m14(&D_0026C948);
            a = g_currentEntry->count64;
            b = g_currentWorld->count2300;
            k = -1;
            if (a == b) {
                k = CompletesWorldBits(*(s32*)((u8*)self + 0x760)) ? 5 : 4;
            } else if ((g_saveData->u19F0 & 0xF0000000) == 0) {
                if (a == b - 1) {
                    k = 3;
                } else {
                    f32 r = (f32)a / (f32)b;
                    if (r < 0.5f) {
                        k = 0;
                    } else if (r < 0.8f) {
                        k = 1;
                    } else {
                        k = 2;
                    }
                }
            }
            if (k != -1) {
                Ent17* e = (Ent17*)((u8*)self + (k * 0x2C + 0x658));
                *(s32*)((StepSequence*)e->list[e->pick])->target304 = 0;
                ChooseStepSequenceState((StepSequence*)e->list[e->pick]);
                e->pick = (e->pick + 1) % e->n;
            }
        }
    }
}

void AddEntryRecordKey(C17* list, u32 index, void* item)
{
    Ent17* record = (Ent17*)((u8*)list + 0x658 + index * 0x2C);
    u32 count = record->count;
    if (count < 4) {
        record->keys[count] = (s32)item;
        record->count = count + 1;
    }
}

void RecordC17ColliderCompletion(C17* self)
{
    s32 sel;
    s32 idx;
    s32 n;
    s32 v;
    void* item;
    BaseObject* r;

    SetStateWalkerTarget(self->f614, 0x38E);
    if (self->f650 == 0) {
        self->f7D8 = 0;
    } else {
        ((BaseObject*)self->f650)->desc->m18((BaseObject*)self->f650, self);
        self->f650 = 0;
        self->f7D8 = 0;
    }

    if (D_00270454 != 0) {
        PopStackElement((void*)&g_elementStack);
    }
    if ((self->f760 & (s64)0xF000FFFF) != 0) {
        G27C230* ctx = g_currentLevelRecord;
        GameProgress* g = g_saveData;
        G27C230* ctl = g_currentEntry;

        ctx->f43C = ctx->f43C + 1;
        g->f19F0 = g->f19F0 | self->f760;
        self->world->f1CE4 = 0;
        ctl->flags = ctl->flags | 4;

        v = g->f19EC;
        if ((v & 8) == 0) {
            g->f19EC = v | 8;
        } else if ((v & 0x10) == 0) {
            g->f19EC = v | 0x10;
        }

        if (ComputeCompletionMask() & 4) {
            ApplyCompletionFlags(4);
        }

        sel = 0x37E;
        if (self->f760 != 1) {
            sel = 0x37F;
            StartMemoryCardSave(g_memoryCard);
        }

        r = (BaseObject*)FindFirstObjectById(self->world, 0x101, sel, self);
        if (r != 0) {
            r->desc->m02(r);
        }

        idx = self->f764;
        if (idx >= 0) {
            item = self->f768[idx];
            if (item != 0) {
                n = self->f7D8;
                self->f7DC[n] = item;
                self->f7D8 = n + 1;
            }
        }
    }
}

void InitC71Object(C71* self)
{
    InitObject(self);
    self->targetId = -1;
    self->f4C = 3.4028235e+38f;
}

void RegisterC71Object(C71* obj)
{
    RegisterObject(obj);
    AppendToList(&obj->world->list1C90, obj);
}

void UnregisterC71Object(C71* obj)
{
    UnregisterObject(obj);
    RemoveFromList(&obj->world->list1C90, obj);
}

void StartC71Object(C71* obj)
{
    StartObject(obj);
    if (obj->targetId != -1)
        obj->target = (s32)FindFirstObjectById(obj->world, 4, obj->targetId, obj);
}

void CopyC71Object(C71* self)
{
    PathCurveKeptBits tmp;

    tmp = self->keep;
    CopyObjectData(self);
    self->keep = tmp;
}

void InitObjectGatherer(ObjectGatherer* self)
{
    InitCollider(self);
    self->f60C = 1.0f;
    self->f608 = 0.5f;
    self->f55C = RandomGaussian(*(f32*)g_gameTime + 3.0f, 1.0f, 2.5f);
    self->f664 = -1;
}

void LoadObjectGatherer(ObjectGatherer* self)
{
    s32 k = 0x269;
    LoadCollider(self);
    FindOrBuildMemberGroup(&self->group, self);
    ResolveObjectLinks(self, 1, (u8*)g_objectGathererLoadLinks);
    for (; k < 0x288; k++) {
        void* node = FindFirstObjectByIdMode1(self->world, k, self);
        if (node != 0) {
            ResolveAndStartObject(node);
            if (k < 0x279) {
                self->lowObjects[self->lowCount++] = node;
            } else {
                self->highObjects[self->highCount++] = node;
            }
        }
    }
}

void StartObjectGatherer(ObjectGatherer* self)
{
    ResolveObjectLinks(self, 1, (u8*)g_objectGathererStartLinks);
    StartPlacedObject(self);
    self->state = -1;
    func_0019C1C0(self, 1);
    self->v650 = self->v140;
}

void AddObjectGatherer(ObjectGatherer* obj)
{
    RegisterCollider(obj);
    AppendToList(&obj->world->list1C60, obj);
}

void RemoveObjectGatherer(ObjectGatherer* obj)
{
    UnregisterCollider(obj);
    RemoveFromList(&obj->world->list1C60, obj);
}

void CopyObjectGatherer(ObjectGatherer* self)
{
    PackedS64 tmp;
    tmp = self->q600;
    CopyCollider(self);
    self->q600 = tmp;
}

void StepCollider(Collider* self, f32 t);
void SteerColliderTowardRotation(Collider* self, void* a, s32 b, void* table, s32 c, f32 t);
void TurnColliderTowardRotation(Collider* self, f32 scale, void* basis, void* data);
void BuildBasisFromX(void* self, void* value);

void StepObjectGatherer(ObjectGatherer* self, f32 dt)
{
    Vec02 delta;
    Mat02 basis;
    Vec02 target;
    StepCollider(self, dt);
    switch (self->state) {
    case 1:
        Vu0::Q(delta) = Vu0::Sub(Vu0::Q(self->v640), Vu0::Q(self->v140));
        delta.z = 0.0f;
        BuildBasisFromX(&delta, &basis);
        TurnColliderTowardRotation(self, dt, &basis, D_0026ABB0);
        break;
    case 2:
        TransformPointBetweenFrames(*(void**)((u8*)self->f660 + 0x18), 0, (u8*)self->f660 + 0x40, &target);
        Vu0::Q(delta) = Vu0::Sub(Vu0::Q(target), Vu0::Q(self->v140));
        delta.z = 0.0f;
        BuildBasisFromX(&delta, &basis);
        TurnColliderTowardRotation(self, dt, &basis, D_0026ABB0);
        break;
    default:
        SteerColliderTowardRotation(self, 0, 0, (void*)&D_00248D30, (s32)self->p214, dt);
        break;
    }
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

struct GatherCandidate {
    u8 pad00[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x40 - 0x1C];
    Vec02 pos;              // 0x40
};

void UpdateCollider(Collider* self, f32 dt);
void* FindColliderFloorContact(void* self, s32 key, s32* out);
s32 TestPointAgainstObjectShape(void* obj, Vec02* p);
void ClearRootTries(void* self);

// Each update: the state's sound, push and speed.
void UpdateObjectGatherer(ObjectGatherer* self, f32 dt)
{
    Vec02 dir;
    Vec02 target;
    SwitchedCollider* act = (SwitchedCollider*)GetActiveSwitchedCollider();
    UpdateCollider(self, dt);
    s32 state = self->state;
    if (act != 0) {
        u128 pos = Vu0::Q(act->v140);
        Vu0::Q(target) = Vu0::MulAddX(pos, Vu0::Q(act->v150), Vu0::Scalar(0.5f));
    }
    if (state < 3) {
        if (state >= 0 && self->f55C < g_gameClock[1]) {
            StartSoundEffect(0x3B, 0, self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            self->f55C = RandomGaussian(g_gameClock[1] + 3.0f, 1.0f, 2.5f);
        }
    }
    if (act != 0 && (u32)state < 2 && Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(target), Vu0::Q(self->v140)), Vu0::Sub(Vu0::Q(target), Vu0::Q(self->v140)))) < 90000.0f) {
        ListFrame frame;
        BeginListWalk::Of(&frame, &self->world->list1C60);
        ObjectGatherer* n;
        while ((n = NextInList<ObjectGatherer>::Of(&frame)) != 0) {
            if (self != n) {
                s32 near = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(n->v140), Vu0::Q(self->v140)), Vu0::Sub(Vu0::Q(n->v140), Vu0::Q(self->v140)))) < self->f624 * self->f624;
                if (near) {
                    func_0019C1C0(n, 2);
                }
            }
        }
        state = 2;
        g_activeListFrames = frame.prev;
    } else {
        s32 side;
        s32 go;
        switch (state) {
        case 0:
            if (self->f558 < g_gameTime[0]) {
                state = 1;
            }
            break;
        case 1: {
            go = 0;
            if (self->ring == 0 && self->f554 + 0.5f < g_gameTime[0] && Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->v150))) < self->f614 * 0.1f) {
                go = FindColliderFloorContact(self, 0, &side) != 0;
            }
            if (go) {
                Vec02 push;
                Vu0::Q(push) = Vu0::MulXSum(Vu0::Q(self->m110.r[0]), Vu0::Scalar(self->f614 * 0.7f), Vu0::Q(g_unitZVector), Vu0::ScalarAt(self->f620));
                self->desc02()->m20(self, &push);
                break;
            }
            if (self->f558 < g_gameTime[0]) {
                state = 0;
                break;
            }
            if (Vu0::ToFloatMoved(Vu0::DotXY(Vu0::Sub(Vu0::Q(self->v640), Vu0::Q(self->v140)), Vu0::Sub(Vu0::Q(self->v640), Vu0::Q(self->v140)))) < 400.0f) {
                state = 0;
            }
            break;
        }
        case 2: {
            go = 0;
            if (self->ring == 0 && self->f554 + 0.7f < g_gameTime[0] && Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->v150))) < self->f618 * 0.3f) {
                go = FindColliderFloorContact(self, 0, &side) != 0;
            }
            if (go) {
                Vec02 push;
                Vu0::Q(push) = Vu0::MulXSum(Vu0::Q(self->m110.r[0]), Vu0::Scalar(self->f618 * 0.5f), Vu0::Q(g_unitZVector), Vu0::ScalarAt(self->f620));
                self->desc02()->m20(self, &push);
                break;
            }
            if (self->f558 < g_gameTime[0]) {
                state = 1;
                break;
            }
            if (self->f660 != 0 && TestPointAgainstObjectShape(self->f660, &self->v140) != 0) {
                state = 4;
            }
            break;
        }
        case 3:
            break;
        case 4:
            if (self->f558 < g_gameClock[1] && act != 0 && 360000.0f < Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(act->v140)), Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(act->v140))))) {
                ListFrame frame;
                s32 any = 0;
                BeginListWalk::Of(&frame, &self->world->list1C60);
                while (NextInList<ObjectGatherer>::Of(&frame) != 0) {
                    if (Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(act->v140)), Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(act->v140)))) < 90000.0f) {
                        any = 1;
                        break;
                    }
                }
                if (any != 0) {
                    self->f558 = g_gameClock[1] + RandomFloatInRange(0.2f, 3.0f);
                } else {
                    state = 1;
                }
                g_activeListFrames = frame.prev;
            } else {
                self->desc02()->m20(self, (Vec02*)&D_00248D30);
                self->desc02()->m21(self, (Vec02*)&D_00248D30);
            }
            break;
        }
    }
    func_0019C1C0(self, state);
    switch (state) {
    case 1:
    case 2: {
        f32 speed;
        if (state == 1) {
            Vu0::Q(self->v630) = Vu0::Sub(Vu0::Q(self->v640), Vu0::Q(self->v140));
            speed = self->f614;
        } else {
            speed = self->f618;
            Vec02 at;
            TransformPointBetweenFrames(((GatherCandidate*)self->f660)->frame, 0, &((GatherCandidate*)self->f660)->pos, (Quad4*)&at);
            u128 d = Vu0::Sub(Vu0::Q(at), Vu0::Q(self->v140));
            f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(d, d)));
            if (dist < 500.0f) {
                speed = self->f618 <? (D_0026ABC0[0] + dist * (D_0026ABC0[1] + dist * D_0026ABC0[2]));
            }
            Vu0::Q(self->v630) = d;
        }
        dir = self->v630;
        Vu0::Q(dir) = Vu0::DivX(Vu0::Q(dir), Vu0::Length(Vu0::Q(dir)));
        f32 c = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(self->m110.r[0]), Vu0::Q(dir)));
        f32 lo = 0.0f;
        f32 hi = 1.0f;
        if (c < lo) {
            c = lo;
        } else if (hi < c) {
            c = hi;
        }
        self->f61C = c * speed;
        ClearRootTries(self);
        return;
    }
    case 0:
    case 3:
    case 4:
        self->f61C = 0.0f;
        return;
    }
}

ASM_FUNC(func_0019BB10);

ASM_FUNC(func_0019BB90);

void BuildPlacedObjectTransform(void* self, void* a, void* out);

void func_0019BC40(ObjectGatherer* self, void* a1, void* a2)
{
    Vec02 tmp[4];
    ListFrame frame;
    PlacedObject* obj;
    if (self->state == 4) {
        return;
    }
    if (self->flags & 0x100000000ULL) {
        return;
    }
    BuildPlacedObjectTransform(self, a2, tmp);
    switch (self->state) {
    case 0:
        obj = (PlacedObject*)self->base5EC;
        obj->desc02()->m24(obj, a1, tmp);
        break;
    case 1: {
        f32 r = self->near5F0 * self->near5F0;
        u128 d = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(self->v650));
        s32 far = r < Vu0::ToFloatMoved(Vu0::Dot(d, d));
        if (far) {
            self->ring = (self->ring + 1) % self->lowCount;
            Vu0::Q(self->v650) = Vu0::Q(self->v140);
        }
        obj = (PlacedObject*)self->lowObjects[self->ring];
        obj->desc02()->m24(obj, a1, tmp);
        break;
    }
    case 2: {
        f32 r = self->near5F4 * self->near5F4;
        u128 d = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(self->v650));
        s32 far = r < Vu0::ToFloatMoved(Vu0::Dot(d, d));
        if (far) {
            self->ring = (self->ring + 1) % self->highCount;
            Vu0::Q(self->v650) = Vu0::Q(self->v140);
        }
        obj = (PlacedObject*)self->highObjects[self->ring];
        obj->desc02()->m24(obj, a1, tmp);
        break;
    }
    default:
        return;
    }
}

s32 HandleObjectGathererObjectEvent(ObjectGatherer* self, GatherTrigger* src)
{
    SlotMessage loc;
    if (self->state != 3) {
        func_0019C1C0(self, 3);
        BaseObject* obj = (BaseObject*)self->group;
        if (obj != 0) {
            loc.kind = 6;
            loc.qb = src->q20;
            loc.qa = src->q30;
            obj->desc->m1B(obj, &loc);
        }
    }
    return 1;
}

void* GetActiveSwitchedCollider();
void MeasurePointToSegment(void* p, Vec02* a, Vec02* b, f32* t, f32* dist);

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
        s32 far = reach2 < Vu0::ToFloatMoved(Vu0::Dot(off, off));
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

void SetObjectGathererSuspended(ObjectGatherer *self, s32 a1) {
    if (a1 != 0) {
        RemoveFromList(&self->world->list1C60, self);
        ((BaseObject *)self->f5FC)->desc->m03((BaseObject *)self->f5FC);
    } else {
        Quad4 buf;
        AppendToList(&self->world->list1C60, self);
        ((BaseObject *)self->f5FC)->desc->m02((BaseObject *)self->f5FC);
        TransformPointBetweenFrames(*(void **)((u8 *)self->f660 + 0x18), 0,
                      (u8 *)self->f660 + 0x40, &buf);
        PlaceColliderClearOfContacts(self, &buf, (void*)&g_unitZVector);
    }
    SetColliderPartListed(self, a1 == 0);
    ListWalker it(&self->parts);
    s32 node = it.Next();
    while (node != 0) {
        SetColliderPartListed((ObjectGatherer *)node, a1 == 0);
        node = it.Next();
    }
    self->desc02()->m20(self, (Vec02 *)&D_00248D30);
    self->desc02()->m21(self, (Vec02 *)&D_00248D30);
}

void func_0019C1C0(ObjectGatherer* self, s32 mode)
{
    Vec02 offset;
    if (self->state == mode) {
        return;
    }
    if (self->state == 4) {
        SetObjectGathererSuspended(self, 0);
        self->f660 = 0;
    }
    *(s32*)((u8*)self->f5FC + 0x88) = 14;
    self->f558 = g_gameClock[1];
    switch (mode) {
    case 0:
        self->f558 = self->f558 + RandomFloatInRange(self->f608, self->f60C);
        self->ring = 0;
        Vu0::Q(self->v650) = Vu0::Q(self->v140);
        break;
    case 1: {
        f32 angle = RandomFloatInRange(0.0f, 6.2831855f);
        f32 radius = RandomFloatInRange(0.0f, self->f610);
        ComputePolarOffset(&offset, angle, radius, 0.0f);
        Vu0::Q(self->v640) = Vu0::Add(Vu0::Q(self->v190), Vu0::Q(offset));
        self->ring = 0;
        self->f558 = self->f558 + RandomFloatInRange(3.0f, 5.0f);
        break;
    }
    case 2:
        func_0019BE80(self);
        self->f558 = self->f558 + 10.0f;
        self->ring = 0;
        break;
    case 3:
        StartSoundEffect(0x3A, 0, 0, (s32)&self->v140, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        ScatterObjectsAtPoint(g_scatterController, &self->v140, self->f664, self->f668);
        self->desc->m03(self);
        break;
    case 4:
        SetObjectGathererSuspended(self, 1);
        self->f558 = self->f558 + RandomFloatInRange(3.0f, 15.0f);
        break;
    }
    self->state = mode;
    self->f554 = g_gameClock[1];
}

void RegisterC7CObject(BaseObject* obj)
{
    RegisterObject(obj);
    AppendToList(&obj->world->list1C6C, obj);
}

void UnregisterC7CObject(BaseObject* obj)
{
    UnregisterObject(obj);
    RemoveFromList(&obj->world->list1C6C, obj);
}

void InitC8BObject(C8B* obj)
{
    InitObject(obj);
    obj->second38 = -1;
    obj->first34 = -1;
}

void LoadC8BObject(C8B* o, LoadStream* in)
{
    {
        s32 i = 0x17;
        s32* p = (s32*)((u8*)o + 0xF0);
        do {
            i--;
            *p = ReadBufferedS16(in);
            p += 8;
        } while (i >= 0);
    }
    s32 i = 0;
    o->f48 = ReadBufferedS16(in);
    func_00137FB0(in, o->fA0);
    o->fC4 = (Rec8B*)AllocateZeroedFrontMemory(o->fA4 * 100);
    for (i = 0; i < o->fA4; i++) {
        f32 x;
        f32 y;
        f32 z;
        Rec8B* r = &o->fC4[i];
        o->fC4[i].id = ReadBufferedS8(in);
        DecodeC8BGridIndex(o, i, &x, &y, &z);
        ComputeGridBlendWeights(x, y, z, o, r->pos);
    }
    o->fC8 = ReadBufferedS16(in);
    o->fCC = (u8*)AllocateZeroedFrontMemory(o->fC8 << 4);
    for (s32 e = 0; e < o->fC8; e++) {
        s32* r = (s32*)(o->fCC + (e << 4));
        s32 j = 3;
        do {
            j--;
            *r = ReadBufferedS16(in);
            r++;
        } while (j >= 0);
    }
    o->fD0 = o->fD4 = ReadBufferedS16(in);
    o->fD8 = (Tri8B*)AllocateZeroedFrontMemory(o->fD0 * 12);
    o->fDC = (Edge8B*)AllocateZeroedFrontMemory(o->fD0 << 3);
    for (s32 n = 0; n < o->fD0; n++) {
        Tri8B* t = &o->fD8[n];
        Edge8B* e = &o->fDC[n];
        s32 a = ReadBufferedS16(in);
        s32 b = ReadBufferedS16(in);
        s32 c = ReadBufferedS16(in);
        t->a = o->fB0 + (a << 5);
        if (b > 0) {
            b--;
            t->b = (u8*)&o->fD8[b];
        } else if (b < 0) {
            b = ~b;
            e->a = o->fCC + (b << 4);
        }
        if (c > 0) {
            c--;
            t->c = (u8*)&o->fD8[c];
        } else if (c < 0) {
            c = ~c;
            e->b = o->fCC + (c << 4);
        }
    }
    o->fE0 = ReadBufferedFloat(in);
    ReadPropertyRecords(o, in);
}

void StartC8BObject(C8B* self)
{
    Slot8B* s;
    s32 i;
    StartObject(self);
    self->f3C = FindFirstObjectByIdMode4(self->world, self->first34, self);
    if (self->f3C == 0) return;
    self->f40 = FindFirstObjectByIdMode1(self->world, self->second38, self->f3C);
    if (self->f40 == 0) return;
    for (i = 0; i < 24; i++) {
        s = &self->slots[i];
        Node8B* n = (Node8B*)FindFirstObjectByIdMode1(self->world, s->fC, self->f3C);
        s->n4 = n;
        if (n != 0) n->vtbl[7](n);
    }
    ComputeWrappedDeltas(0x20, 0x18, self->slots, 0x10, 2, D_0026ABD0);
    BuildCombinedBlendAnimation(self->f3C, 0x20, 0x18, self->slots, 1, D_0026ABE0, D_0026ABD8, &self->f3E4);
    if (self->f3E4->f78 == 0) self->f3E4->f78 = 1;
    void* nd = FindFirstObjectByIdMode1(self->world, 0x36, self->f3C);
    if (nd != 0) SetBlendEntryRecordFlag(self->f3E4, nd);
    f32 buf[24];
    ComputeGridBlendWeights(self, buf, self->f54, self->f58, self->f5C);
    Slot8B* d = self->slots;
    f32* src = buf;
    for (i = 0; i < 24; i++, d++) *(f32*)d = *src++;
    SetBlendItemWeights(self->f3E4, 0x20, 0x18, self->slots);
    func_0012CD78(self->f3E4->pC0->p8->f8, 0.0f, self->f3E4, self->f40, self->f3C, 1, &self->q70, 0, 0, 0);
    self->f60 = self->f3E4->pC0->p8->f8;
    if (self->f80 != 0) {
        ComputeGridBlendWeights(self, buf, self->f84, self->f88, self->f8C);
        d = self->slots;
        src = buf;
        for (i = 0; i < 24; i++, d++) *(f32*)d = *src++;
        SetBlendItemWeights(self->f3E4, 0x20, 0x18, self->slots);
        func_0012CD78(self->f3E4->pC0->p8->f8, 0.0f, self->f3E4, self->f40, self->f3C, 1, &self->q90, 0, 0, 0);
    } else {
        self->q90 = self->q70;
    }
    self->f50 = 1;
}

INCLUDE_ASM(func_0019C9C8);

INCLUDE_ASM(func_0019CC10);

void DecodeC8BGridIndex(C8B* self, s32 p, f32* out0, f32* out1, f32* out2)
{
    s32 n = self->f48;
    s32 q = p / ((n + 1) * (3 * n + 1));
    s32 r = p - q * (n + 1) * (3 * n + 1);
    s32 m = r / (3 * n + 1);
    s32 s = r - m * (3 * n + 1);
    *out0 = (f32)(q - n) / (f32)self->f48;
    *out1 = (f32)m / (f32)self->f48;
    *out2 = (f32)s / (f32)self->f48;
}

void SetC8BObjectVector(C8B* value, f32 x, f32 y, f32 z)
{
    value->f54 = x;
    value->f58 = y;
    value->f5C = z;
}

void SetC8BObjectVectorFlagged(C8B* self, f32 x, f32 y, f32 z)
{
    self->f80 = 1;
    self->f54 = x;
    self->f58 = y;
    self->f5C = z;
}

// What func_0019CE50 reads: an object to place at a time (+0x18) and a point in its frame (+0x40).
struct FramePoint_0019CE50 {
    u8 pad0[0x18];
    void* object;           // 0x18
    u8 pad1C[0x40 - 0x1C];
    Vec02 point;            // 0x40
};

void ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, s32 e, s32 f, f32 t);

void func_0019CE50(void* self, FramePoint_0019CE50* p, Vec02* out, f32 t)
{
    Vec02 pos;
    Mat02 rot;
    ComputeObjectFrameAtTime(p->object, 0, &pos, &rot, 0, 0, t);
    Vu0::Q(*out) = Vu0::Add(Vu0::Rotate(rot, Vu0::Q(p->point)), Vu0::Q(pos));
}

// What func_0019CEC0 reads of its first argument: the object whose frame it measures in.
struct FrameOwner_0019CEC0 {
    u8 pad0[0x3C];
    void* object;           // 0x3C
};

// The point func_0019CE50 places at time t, in the frame of self's object at that time.
void func_0019CEC0(void* self, void* p, void* out, f32 t)
{
    Vec02 pos;
    Vec02 point;
    Mat02 rot;
    func_0019CE50(self, (FramePoint_0019CE50*)p, &point, t);
    ComputeObjectFrameAtTime(((FrameOwner_0019CEC0*)self)->object, 0, &pos, &rot, 0, 0, t);
    Vu0::Q(point) = Vu0::Sub(Vu0::Q(point), Vu0::Q(pos));
    Vu0::Q(*(Vec02*)out) = Vu0::RotateTransposed(rot, Vu0::Q(point));
}

struct TreePlane {
    Vec02 normal;
    f32 dist;
};

u8* func_0019CF68(C8B* self, Tri8B* node, Vec02* pt)
{
    if (node == 0) {
        node = self->fD8;
    }
    for (;;) {
        TreePlane* plane = (TreePlane*)node->a;
        f32 d = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(*pt), Vu0::Q(plane->normal))) - plane->dist;
        if (d < -0.0001f) {
            if (node->b == 0) {
                return self->fDC[node - self->fD8].a;
            }
            node = (Tri8B*)node->b;
        } else if (d > 0.0001f) {
            if (node->c == 0) {
                return self->fDC[node - self->fD8].b;
            }
            node = (Tri8B*)node->c;
        } else {
            u8* r;
            if (node->c == 0) {
                r = self->fDC[node - self->fD8].b;
            } else {
                r = func_0019CF68(self, (Tri8B*)node->c, pt);
            }
            if (r != 0) {
                return r;
            }
            if (node->b == 0) {
                return self->fDC[node - self->fD8].a;
            }
            node = (Tri8B*)node->b;
        }
    }
}

// Bisects the segment from self's point at 0x90 to *from for the last place func_0019CF68 accepts
// (ten halvings); the point, what it returned there and the distance from *from, into the
// outputs that are not 0.
void func_0019D0E0(void* a, void* b, void* c, void* d, void* e)
{
    u8* self = (u8*)a;
    Vec02* from = (Vec02*)b;
    Vec02* out = (Vec02*)c;
    s32* hit = (s32*)d;
    f32* dist = (f32*)e;
    Vec02 point;
    Vec02 best;
    s32 first = (s32)func_0019CF68((C8B*)self, 0, from);
    s32 found;
    if (first != 0) {
        if (out != 0) {
            *out = *from;
        }
        if (hit != 0) {
            *hit = first;
        }
        if (dist != 0) {
            *dist = 0.0f;
        }
        return;
    }
    found = 0;
    f32 lo = 0.0f;
    f32 hi = 1.0f;
    for (s32 i = 9; i >= 0; i--) {
        f32 t = (lo + hi) * 0.5f;
        Vu0::Q(point) = Vu0::MulXSum(Vu0::Q(*(Vec02*)(self + 0x90)), Vu0::Scalar(1.0f - t), Vu0::Q(*from), Vu0::Scalar(t));
        s32 r = (s32)func_0019CF68((C8B*)self, 0, &point);
        if (r != 0) {
            found = r;
            lo = t;
            best = point;
        } else {
            hi = t;
        }
    }
    if (found == 0) {
        best = *(Vec02*)(self + 0x70);
        found = (s32)func_0019CF68((C8B*)self, 0, &best);
    }
    if (out != 0) {
        *out = best;
    }
    if (hit != 0) {
        *hit = found;
    }
    if (dist != 0) {
        Vu0::StoreX(*dist, Vu0::Length(Vu0::Sub(Vu0::Q(*from), Vu0::Q(best))));
    }
}

void TrackAimTargetObject(Player* self, void* x, void* y)
{
    Quad16 q0;
    Quad16 q1;
    s32 w20;
    s32 w24;
    if (y != 0) {
        f32 d = self->f2424 - g_gameClock[1];
        if (d < g_gameClock[2]) {
            d = g_gameClock[2];
        }
        func_0019CEC0(x, y, &q0, d);
        func_0019D0E0(x, &q0, &q1, &w20, &w24);
        func_0019C9C8(x, w20, &q1);
    }
}

void TrackAimTargetPoint(void* self, void* dst, PathCurveObject* src, f32* k)
{
    Quad16 q0;
    Quad16 q1;
    Quad16 q2;
    Quad16 q3;
    s32 w40;
    s32 w44;
    TransformPointBetweenFrames(0, (s32)src->parent, (u8*)self + 0x140, &q0);
    PathCurve* o = src->curve;
    if (o->vt->m12 != 0) {
        o->vt->m12(o, *k, &q0, 0, (f32*)&q1, 0, 0, k);
    }
    TransformPointBetweenFrames((void*)src->parent, (s32)self, &q1, &q2);
    func_0019D0E0(dst, &q2, &q3, &w40, &w44);
    func_0019C9C8(dst, w40, &q3);
}
