// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "flagged_object.h"
#include "object_gatherer.h"
#include "world.h"
#include "object_event.h"
#include "screen_fade.h"
#include "flag_table.h"
#include "vu0.h"
#include "object_finder.h"
struct BaseObject;
struct TransformObject;
struct Vec02;


// Types other files define, named by the parameters of their functions declared here.
struct ObjectLink;
struct AnimationPlayer;

// The file's .rodata: the FLT_MAX literal of ResetFlagTable (func_00140D90), then the literal of
// UpdateFlaggedObject (func_00141690).

// The file's .data, in retail's order: the loader's link table of class 0x38, then the flag
// table (its bitmap and the snapshot func_00140E10 saves, 0x430 bytes in two labels).
u32 g_flaggedObjectLinks[4] = { 2, 0x545, 0x5A8, 0 };
u8 g_flagTable[528] = {0};
u8 g_flagTableSaved[544] = {0};

extern "C" void* FillMemory(void* p, s32 value, s32 size);

void ResetFlagTable(FlagTable* r)
{
    r->nextIndex = 0;
    r->live.count = 0;
    FillMemory(r->live.bits, 0, sizeof(r->live.bits));
    r->changed = 0;
    Vu0::Q(r->point) = Vu0::FromFloats(3.4028235e+38f, 3.4028235e+38f, 3.4028235e+38f);
    FillMemory(&r->saved, 0, 0x20C);
    r->hasFade = 0;
    r->fadeA = -1;
    r->fadeB = -1;
}

void SaveFlagTableSnapshot(FlagTable* r, s32 a, s32 b)
{
    r->changed = 0;
    r->saved = r->live;
    r->fadeA = a;
    r->fadeB = b;
    r->hasFade = 1;
}

void StartScreenFade(ScreenFade* fade, FadeRequest* args, s32 count);

void StartScreenFadeFromFlagTable(FlagTable* r)
{
    FadeRequest args;
    args.kind = 1;
    args.key = &D_00275B04;
    if (r->hasFade != 0) {
        args.f08 = r->fadeA;
        args.f0C = r->fadeB;
        args.flags = 0x11;
    } else {
        args.f08 = -1;
        args.f0C = -1;
        args.flags = 0x10;
    }
    StartScreenFade(&g_screenFade, &args, 1);
}

void RestoreFlagTableSnapshot(FlagTable* p)
{
    p->nextIndex = 0;
    p->live = p->saved;
    p->changed = 0;
}

s32 TakeFlagTableIndex(FlagTable* c)
{
    c->nextIndex = c->nextIndex + 1;
    return c->nextIndex;
}

s32 TestFlagTableBit(FlagTable* table, s32 index)
{
    u8* bits = (u8*)table;
    s32 mask = 1 << (index & 7);
    bits += index / 8;
    return (bits[0xC] & mask) != 0;
}

void SetFlagTableBit(FlagTable* self, s32 bit)
{
    u8* base = self->live.bits;
    u8* byte = base + bit / 8;
    s32 mask = 1 << (bit & 7);
    s32 cur = *byte & mask;
    if (cur == 0) {
        self->changed = 1;
        goto done;
    }
done:
    if (!(*byte & mask)) {
        *byte = (u8)(*byte | mask);
        self->live.count++;
    }
}

void ClearFlagTableBit(FlagTable* self, s32 bit)
{
    u8* base = self->live.bits;
    u8* byte = base + bit / 8;
    s32 mask = 1 << (bit & 7);
    s32 cur = *byte & mask;
    if (cur != 0) {
        self->changed = 1;
        goto done;
    }
done:
    if ((*byte & mask) != 0) {
        *byte = (u8)(*byte & ~mask);
        self->live.count--;
    }
}

struct BufferedStream;
void ReadBufferedRotation3(BufferedStream* self, void* out);
void ReadBufferedVector3(BufferedStream* src, void* dst);
void ReadMeshTables(void*, void*, void*, void*, void*);
void ReadPropertyRecords(void* a, void* b);

void ReadObjectTransformAndTables(void* a0, void* a1)
{
    ReadBufferedRotation3((BufferedStream*)a1, (u8*)a0 + 0x50);
    ReadBufferedVector3((BufferedStream*)a1, (u8*)a0 + 0x40);
    ReadMeshTables(a1, (u8*)a0 + 0x80, (u8*)a0 + 0x84, (u8*)a0 + 0x88, (u8*)a0 + 0x8C);
    ReadPropertyRecords(a0, a1);
}

struct __attribute__((aligned(16))) Quad_00141170 { f32 v[4]; };
void ConvertPointIntoObjectFrame(TransformObject* self, Vec02* p, Vec02* out);
s32 IsPointInsideFaceTree(void* self, void* value);

s32 TestPointAgainstObjectShape(ObjectGatherer* self, void* value)
{
    Quad_00141170 local;
    ConvertPointIntoObjectFrame((TransformObject*)self, (Vec02*)value, (Vec02*)&local);
    return IsPointInsideFaceTree(self->f8C, &local);
}

void InitCollider(Collider* self);
void SetColliderAnchors(Collider* self, s32 a1, Vec02* a2, s32 a3, Vec02* a4);

void InitFlaggedObject(FlaggedObject* self)
{
    InitCollider(self);
    self->flagIndex = TakeFlagTableIndex((FlagTable*)g_flagTable);
    self->childId = -1;
    World* in = self->world;
    s32 n = in->count2304;
    self->ordinal = n;
    n = n + 1;
    in->count2304 = n;
    SetColliderAnchors(self, 3, 0, 3, 0);
}

struct ScopedListFrame {
    void* list;
    void* cursor;
    s32 next_off;
    ScopedListFrame* prev;
    ScopedListFrame(List01* l)
    {
        list = l;
        cursor = l;
        next_off = l->offset;
        prev = (ScopedListFrame*)g_activeListFrames;
        g_activeListFrames = (ListFrame*)this;
    }
    ~ScopedListFrame() { g_activeListFrames = (ListFrame*)prev; }
};

void LoadCollider(Collider* self, BufferedStream* stream);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
s32 IsObjectOfKind(BaseObject* list, s32 key);
void ResolveAndStartObject(BaseObject* self);

void CollectChildLists(FlaggedObject* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    ResolveObjectLinks(self, 1, (ObjectLink*)g_flaggedObjectLinks);

    ScopedListFrame frame(&self->children);
    void* head = *(void**)((u8*)self + 0x34);
    frame.cursor = (void*)((s32)head + frame.next_off);
    void* node = head;
    if (node != 0) {
        do {
            if (IsObjectOfKind((BaseObject*)node, 0x7B)) {
                s32 n = self->countB;
                self->objsB[n] = node;
                self->countB = n + 1;
            } else {
                if (!IsObjectOfKind((BaseObject*)node, 0x83)) {
                    goto skip;
                }
                s32 n = self->countA;
                self->objsA[n] = node;
                self->countA = n + 1;
            }
            ResolveAndStartObject((BaseObject*)node);
skip:
            void* next = *(void**)frame.cursor;
            frame.cursor = (void*)((s32)next + frame.next_off);
            node = next;
        } while (node != 0);
    }
}

void PostLoadPlacedObject(PlacedObject* self);

void ResolveListIds(FlaggedObject* self)
{
    PostLoadPlacedObject(self);
    s32 i = 0;
    while (i < self->nIdsA) {
        void* r = FindFirstObjectByIdMode4(self->world, self->idsA[i], self);
        if (r != 0) {
            s32 k = self->countA;
            self->objsA[k] = r;
            self->countA = k + 1;
        }
        i++;
    }
    i = 0;
    while (i < self->nIdsB) {
        void* r = FindFirstObjectByIdMode4(self->world, self->idsB[i], self);
        if (r != 0) {
            s32 k = self->countB;
            self->objsB[k] = r;
            self->countB = k + 1;
        }
        i++;
    }
}

struct ListWalkNext {
    static u8* Of(ListFrame* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};
struct ListWalkBegin {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = (ListFrame*)it;
    }
};

struct StateGraph;
void StartPlacedObject(PlacedObject* self);
s32 GetAliasId(BaseObject* self);
StateWalker* CreateStateWalker(StateGraph* self, void* a1, s32 a2, s32 a3);
void SetStateWalkerTarget(StateWalker* self, s32 key);

void StartFlaggedObject(FlaggedObject* self)
{
    StartPlacedObject(self);
    for (s32 i = 0; i < self->countA; i++)
        ResolveAndStartObject((BaseObject*)self->objsA[i]);
    for (s32 i = 0; i < self->countB; i++)
        ResolveAndStartObject((BaseObject*)self->objsB[i]);
    if (self->childId == -1) {
        ListFrame it;
        u8* obj;
        ListWalkBegin::Of(&it, (List01*)&self->children);
        while ((obj = ListWalkNext::Of(&it)) != 0) {
            if (IsObjectOfKind((BaseObject*)obj, 0x74) != 0) {
                self->childId = GetAliasId((BaseObject*)obj);
                if (self->childId == -1)
                    self->childId = *(s32*)(obj + 8);
                self->child = obj;
            }
        }
        g_activeListFrames = (ListFrame*)it.prev;
    } else {
        self->child = FindFirstObjectByIdMode4(self->world, self->childId, self);
    }
    if (self->f5A8 != 0) {
        self->handle = (StateWalker*)CreateStateWalker((StateGraph*)self->f5A8, self, 0x546, 0);

        if (TestFlagTableBit((FlagTable*)g_flagTable, self->flagIndex) != 0)
            SetStateWalkerTarget(self->handle, 0x547);
    }
}

void CopyCollider(Collider* self, Collider* src);
void* CreateObjectCopy(BaseObject* self, World* world, BaseObject* parent);

void CopyFlaggedObject(FlaggedObject* self, FlaggedObject* src)
{
    s32 keepB = self->flagIndex;
    s32 keepA = self->ordinal;
    CopyCollider(self, src);
    self->flagIndex = keepB;
    self->ordinal = keepA;
    for (s32 i = 0; i < self->countA; i++) {
        self->objsA[i] = CreateObjectCopy((BaseObject*)self->objsA[i], self->world, self);
    }
    for (s32 j = 0; j < self->countB; j++) {
        self->objsB[j] = CreateObjectCopy((BaseObject*)self->objsB[j], self->world, self);
    }
}

extern s32 D_0026EC58;
void UpdateCollider(Collider* self, f32 dt);
PlacedObject* GetActiveSwitchedCollider();
void GetObjectWorldPosition(BaseObject* self, Vec02* out);
void RaiseObjectFlag(FlaggedObject* self);

void UpdateFlaggedObject(FlaggedObject* self, f32 dt)
{
    UpdateCollider(self, dt);
    if (D_0026EC58 >= 2) {
        self->desc->m03(self);
        return;
    }
    PlacedObject* player = GetActiveSwitchedCollider();
    if (player == 0) {
        return;
    }
    FlagTable* table = (FlagTable*)g_flagTable;
    if (TestFlagTableBit(table, self->flagIndex)) {
        if (table->changed == 0) {
            return;
        }
        u128 d = Vu0::Sub(Vu0::Q(table->point), Vu0::Q(player->v140));
        if (Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(d, d))) < 1000.0f) {
            return;
        }
        Vu0::Q(table->point) = Vu0::FromFloats(3.4028235e+38f, 3.4028235e+38f, 3.4028235e+38f);
    }
    for (s32 i = 0; i < self->countB; i++) {
        void* obj = self->objsB[i];
        if (TestPointAgainstObjectShape((ObjectGatherer*)obj, &player->v140)) {
            GetObjectWorldPosition((BaseObject*)obj, (Vec02*)g_flagTableSaved);
            RaiseObjectFlag(self);
            break;
        }
    }
}

extern u8 g_padRecord[];

void RaiseObjectFlag(FlaggedObject* self);
struct PadRecord;
s32 HandleObjectEvent(Collider* self, ObjectEvent* shape);
void StartPadRecordPattern(PadRecord* self, s32 pattern, f32 duration);

s32 HandleFlaggedObjectEvent(FlaggedObject* self, ObjectEvent* ev)
{
    void* r = GetActiveSwitchedCollider();
    if (ev->source == r) {
        if ((ev->extraFlags & 0x10) == 0) {
            StartPadRecordPattern((PadRecord*)g_padRecord, 2, 0.2f);
        }
        RaiseObjectFlag(self);
        return 1;
    }
    return HandleObjectEvent(self, ev);
}

extern u8 g_scatterController[];

struct ScatterController;
struct FlaggedObject;
void RaiseScatterLevelForObject(ScatterController* obj, FlaggedObject* node);
s32 IsObjectDescendantOf(BaseObject* node, BaseObject* target);
void CreateAnimationPlayerWithoutPresetTargets(Animation* self, BaseObject* alt, s32 flags, AnimationPlayer** out, f32 fa, f32 fb); // stays void: retail returns a value, but declared so func_00141870 differs in registers

void RaiseObjectFlag(FlaggedObject* self)
{
    RaiseScatterLevelForObject((ScatterController*)g_scatterController, self);
    s32 sel;
    if (self->handle != 0) {
        sel = TestFlagTableBit((FlagTable*)g_flagTable, self->flagIndex) ? 0x549 : 0x548;
    }
    s32 idx = -1;
    SetFlagTableBit((FlagTable*)g_flagTable, self->flagIndex);
    if (IsObjectDescendantOf((BaseObject*)self->child, self)) {
        for (BaseObject* n = self; n != 0; n = n->parent) {
            Alias01* sl = n->alias;
            if (sl != 0) {
                idx = sl->id;
            }
        }
        if (idx == -1) {
            idx = self->id;
        }
    }
    SaveFlagTableSnapshot((FlagTable*)g_flagTable, self->childId, idx);
    for (s32 i = 0; i < self->countA; i++) {
        CreateAnimationPlayerWithoutPresetTargets((Animation*)self->objsA[i], 0, 0, 0, 0.0f, 1.0f);
    }
    if (self->handle != 0) {
        SetStateWalkerTarget(self->handle, sel);
    }
}

void AppendFlaggedObjectIdB(FlaggedObject* q, s32 value)
{
    q->idsB[q->nIdsB++] = value;
}

void AppendFlaggedObjectIdA(FlaggedObject* obj, void* item)
{
    s32 n = obj->nIdsA;
    obj->idsA[n] = (s32)item;
    obj->nIdsA = n + 1;
}

void SetFlaggedChildId(FlaggedObject* self, s32 value)
{
    self->childId = value;
}
