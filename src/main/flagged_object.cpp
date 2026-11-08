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

// The file's .rodata: the FLT_MAX constants of its two assembly functions.
extern const f32 D_00249E3C = 3.4028235e+38f;
extern const f32 D_00249E40 = 3.4028235e+38f;

// The file's .data, in retail's order: the loader's link table of class 0x38, then the flag
// table (its bitmap and the snapshot func_00140E10 saves, 0x430 bytes in two labels).
u32 g_flaggedObjectLinks[4] = { 2, 0x545, 0x5A8, 0 };
u8 g_flagTable[528] = {0};
u8 g_flagTableSaved[544] = {0};

INCLUDE_ASM(func_00140D90);

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

void ReadBufferedRotation3(void* a, void* b);
void ReadBufferedVector3(void* a, void* b);
s32 ReadMeshTables(void*, void*, void*, void*, void*);
void ReadPropertyRecords(void* a, void* b);

void ReadObjectTransformAndTables(void* a0, void* a1)
{
    ReadBufferedRotation3(a1, (u8*)a0 + 0x50);
    ReadBufferedVector3(a1, (u8*)a0 + 0x40);
    ReadMeshTables(a1, (u8*)a0 + 0x80, (u8*)a0 + 0x84, (u8*)a0 + 0x88, (u8*)a0 + 0x8C);
    ReadPropertyRecords(a0, a1);
}

struct __attribute__((aligned(16))) Quad_00141170 { f32 v[4]; };
void ConvertPointIntoObjectFrame(void* self, void* value, void* out);
s32 IsPointInsideFaceTree(void* self, void* value);

s32 TestPointAgainstObjectShape(ObjectGatherer* self, void* value)
{
    Quad_00141170 local;
    ConvertPointIntoObjectFrame(self, value, &local);
    return IsPointInsideFaceTree(self->f8C, &local);
}

void InitCollider(Collider* self);
void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);

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

void LoadCollider(Collider* self);
void ResolveObjectLinks(void* self, s32 a, void* b);
s32 IsObjectOfKind(void* node, s32 kind);
void ResolveAndStartObject(void* node);

void CollectChildLists(FlaggedObject* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 1, g_flaggedObjectLinks);

    ScopedListFrame frame(&self->children);
    void* head = *(void**)((u8*)self + 0x34);
    frame.cursor = (void*)((s32)head + frame.next_off);
    void* node = head;
    if (node != 0) {
        do {
            if (IsObjectOfKind(node, 0x7B)) {
                s32 n = self->countB;
                self->objsB[n] = node;
                self->countB = n + 1;
            } else {
                if (!IsObjectOfKind(node, 0x83)) {
                    goto skip;
                }
                s32 n = self->countA;
                self->objsA[n] = node;
                self->countA = n + 1;
            }
            ResolveAndStartObject(node);
skip:
            void* next = *(void**)frame.cursor;
            frame.cursor = (void*)((s32)next + frame.next_off);
            node = next;
        } while (node != 0);
    }
}

void PostLoadPlacedObject(void* self);
void* FindFirstObjectByIdMode4(void* host, s32 id, void* ctx);

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

void StartPlacedObject(FlaggedObject* self);
s32 GetAliasId(u8* node);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);
void SetStateWalkerTarget(void* p, s32 n);

void StartFlaggedObject(FlaggedObject* self)
{
    StartPlacedObject(self);
    for (s32 i = 0; i < self->countA; i++)
        ResolveAndStartObject(self->objsA[i]);
    for (s32 i = 0; i < self->countB; i++)
        ResolveAndStartObject(self->objsB[i]);
    if (self->childId == -1) {
        ListFrame it;
        u8* obj;
        ListWalkBegin::Of(&it, (List01*)&self->children);
        while ((obj = ListWalkNext::Of(&it)) != 0) {
            if (IsObjectOfKind(obj, 0x74) != 0) {
                self->childId = GetAliasId(obj);
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
        self->handle = (StateWalker*)CreateStateWalker(self->f5A8, self, 0x546, 0);

        if (TestFlagTableBit((FlagTable*)g_flagTable, self->flagIndex) != 0)
            SetStateWalkerTarget(self->handle, 0x547);
    }
}

void CopyCollider(Collider* self);
void* CreateObjectCopy(void* item, void* x, FlaggedObject* self);

void CopyFlaggedObject(FlaggedObject* self)
{
    s32 keepB = self->flagIndex;
    s32 keepA = self->ordinal;
    CopyCollider(self);
    self->flagIndex = keepB;
    self->ordinal = keepA;
    for (s32 i = 0; i < self->countA; i++) {
        self->objsA[i] = CreateObjectCopy(self->objsA[i], self->world, self);
    }
    for (s32 j = 0; j < self->countB; j++) {
        self->objsB[j] = CreateObjectCopy(self->objsB[j], self->world, self);
    }
}

extern s32 D_0026EC58;
void UpdateCollider(Collider* self);
PlacedObject* GetActiveSwitchedCollider();
void GetObjectWorldPosition(void* obj, f32* out);
void RaiseObjectFlag(FlaggedObject* self);

void UpdateFlaggedObject(FlaggedObject* self)
{
    UpdateCollider(self);
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
        Vu0::Q(table->point) = Vu0::FromFloats(D_00249E40, D_00249E40, D_00249E40);
    }
    for (s32 i = 0; i < self->countB; i++) {
        void* obj = self->objsB[i];
        if (TestPointAgainstObjectShape((ObjectGatherer*)obj, &player->v140)) {
            GetObjectWorldPosition(obj, (f32*)g_flagTableSaved);
            RaiseObjectFlag(self);
            break;
        }
    }
}

extern u8 g_padRecord[];

void RaiseObjectFlag(FlaggedObject* self);
s32 GetActiveSwitchedCollider(void* self, ObjectEvent* ev);
s32 HandleObjectEvent(void* self, ObjectEvent* ev);
void StartPadRecordPattern(void* p, f32 f, s32 n);

s32 HandleFlaggedObjectEvent(FlaggedObject* self, ObjectEvent* ev)
{
    s32 r = GetActiveSwitchedCollider(self, ev);
    if (ev->type == r) {
        if ((ev->extraFlags & 0x10) == 0) {
            StartPadRecordPattern(g_padRecord, 0.2f, 2);
        }
        RaiseObjectFlag(self);
        return 1;
    }
    return HandleObjectEvent(self, ev);
}

extern u8 g_scatterController[];

void RaiseScatterLevelForObject(void* table, FlaggedObject* self);
s32 IsObjectDescendantOf(s32 v, FlaggedObject* self);
void CreateAnimationPlayerWithoutPresetTargets(void* p, s32 a, s32 b, s32 c, f32 x, f32 y);

void RaiseObjectFlag(FlaggedObject* self)
{
    RaiseScatterLevelForObject(g_scatterController, self);
    s32 sel;
    if (self->handle != 0) {
        sel = TestFlagTableBit((FlagTable*)g_flagTable, self->flagIndex) ? 0x549 : 0x548;
    }
    s32 idx = -1;
    SetFlagTableBit((FlagTable*)g_flagTable, self->flagIndex);
    if (IsObjectDescendantOf((s32)self->child, self)) {
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
        CreateAnimationPlayerWithoutPresetTargets(self->objsA[i], 0, 0, 0, 0.0f, 1.0f);
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
