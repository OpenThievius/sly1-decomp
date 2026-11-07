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

// The file's .rodata: the FLT_MAX constants of its two assembly functions.
extern const f32 D_00249E3C = 3.4028235e+38f;
extern const f32 D_00249E40 = 3.4028235e+38f;

// The file's .data, in retail's order: the loader's link table of class 0x38, then the flag
// table (its bitmap and the snapshot func_00140E10 saves, 0x430 bytes in two labels).
u32 D_00261410[4] = { 2, 0x545, 0x5A8, 0 };
u8 D_00261420[528] = {0};
u8 D_00261630[544] = {0};

ASM_FUNC(func_00140D90);

void func_00140E10(FlagTable* r, s32 a, s32 b)
{
    r->changed = 0;
    r->saved = r->live;
    r->fadeA = a;
    r->fadeB = b;
    r->hasFade = 1;
}

void func_001EFFA0(ScreenFade* fade, FadeRequest* args, s32 count);

void func_00140ED0(FlagTable* r)
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

void func_00140F48(FlagTable* p)
{
    p->nextIndex = 0;
    p->live = p->saved;
    p->changed = 0;
}

s32 func_00140FF8(FlagTable* c)
{
    c->nextIndex = c->nextIndex + 1;
    return c->nextIndex;
}

s32 func_00141008(FlagTable* table, s32 index)
{
    u8* bits = (u8*)table;
    s32 mask = 1 << (index & 7);
    bits += index / 8;
    return (bits[0xC] & mask) != 0;
}

void func_00141040(FlagTable* self, s32 bit)
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

void func_001410A0(FlagTable* self, s32 bit)
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

void func_00137EB0(void* a, void* b);
void func_00137E70(void* a, void* b);
s32 func_001E4C48(void*, void*, void*, void*, void*);
void func_0011EC40(void* a, void* b);

void func_00141108(void* a0, void* a1)
{
    ReadBufferedRotation3(a1, (u8*)a0 + 0x50);
    ReadBufferedVector3(a1, (u8*)a0 + 0x40);
    ReadMeshTables(a1, (u8*)a0 + 0x80, (u8*)a0 + 0x84, (u8*)a0 + 0x88, (u8*)a0 + 0x8C);
    ReadPropertyRecords(a0, a1);
}

struct __attribute__((aligned(16))) Quad_00141170 { f32 v[4]; };
void func_001F3B48(void* self, void* value, void* out);
s32 func_001E4DC0(void* self, void* value);

s32 func_00141170(ObjectGatherer* self, void* value)
{
    Quad_00141170 local;
    func_001F3B48(self, value, &local);
    return func_001E4DC0(self->f8C, &local);
}

void func_001B7968(Collider* self);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

void func_001411A8(FlaggedObject* self)
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

struct Frame_141210;

struct Frame_141210 {
    void* list;
    void* cursor;
    s32 next_off;
    Frame_141210* prev;
    Frame_141210(List01* l)
    {
        list = l;
        cursor = l;
        next_off = l->offset;
        prev = (Frame_141210*)D_0027B314;
        D_0027B314 = (ListFrame*)this;
    }
    ~Frame_141210() { D_0027B314 = (ListFrame*)prev; }
};

void func_001BAC30(Collider* self);
void func_00124DF8(void* self, s32 a, void* b);
s32 func_001300E8(void* node, s32 kind);
void func_00182ED8(void* node);

void func_00141210(FlaggedObject* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 1, g_flaggedObjectLinks);

    Frame_141210 frame(&self->children);
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

void func_001249A8(void* self);
void* func_0015A448(void* host, s32 id, void* ctx);

void func_00141338(FlaggedObject* self)
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

struct List_141438 { u8* head; u8 pad4[4]; s32 offset; };
struct Iter_141438 { List_141438* list; u8* link; s32 offset; Iter_141438* saved; };
struct Next_141438 {
    static u8* Of(Iter_141438* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};
struct Begin_141438 {
    static void Of(Iter_141438* it, List_141438* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_141438*)((void*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

void func_00124A48(FlaggedObject* self);
s32 func_00183438(u8* node);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_001B64D8(void* p, s32 n);

void func_00141438(FlaggedObject* self)
{
    StartPlacedObject(self);
    for (s32 i = 0; i < self->countA; i++)
        ResolveAndStartObject(self->objsA[i]);
    for (s32 i = 0; i < self->countB; i++)
        ResolveAndStartObject(self->objsB[i]);
    if (self->childId == -1) {
        Iter_141438 it;
        u8* obj;
        Begin_141438::Of(&it, (List_141438*)&self->children);
        while ((obj = Next_141438::Of(&it)) != 0) {
            if (IsObjectOfKind(obj, 0x74) != 0) {
                self->childId = GetAliasId(obj);
                if (self->childId == -1)
                    self->childId = *(s32*)(obj + 8);
                self->child = obj;
            }
        }
        g_activeListFrames = (ListFrame*)it.saved;
    } else {
        self->child = FindFirstObjectByIdMode4(self->world, self->childId, self);
    }
    if (self->f5A8 != 0) {
        self->handle = (StateWalker*)CreateStateWalker(self->f5A8, self, 0x546, 0);

        if (TestFlagTableBit((FlagTable*)g_flagTable, self->flagIndex) != 0)
            SetStateWalkerTarget(self->handle, 0x547);
    }
}

void func_001BA130(Collider* self);
void* func_00183058(void* item, void* x, FlaggedObject* self);

void func_001415D0(FlaggedObject* self)
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

ASM_FUNC(func_00141690);

extern u8 D_00262C70[];

void func_00141870(FlaggedObject* self);
s32 func_001925F0(void* self, ObjectEvent* ev);
s32 func_001BC320(void* self, ObjectEvent* ev);
void func_0016EC38(void* p, f32 f, s32 n);

s32 func_001417F0(FlaggedObject* self, ObjectEvent* ev)
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

extern u8 D_00261EF0[];

void func_00151ED8(void* table, FlaggedObject* self);
s32 func_00182F40(s32 v, FlaggedObject* self);
void func_0012C7B0(void* p, s32 a, s32 b, s32 c, f32 x, f32 y);

void func_00141870(FlaggedObject* self)
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

void func_001419A0(FlaggedObject* q, s32 value)
{
    q->idsB[q->nIdsB++] = value;
}

void func_001419C0(FlaggedObject* obj, void* item)
{
    s32 n = obj->nIdsA;
    obj->idsA[n] = (s32)item;
    obj->nIdsA = n + 1;
}

void func_001419E0(FlaggedObject* self, s32 value)
{
    self->childId = value;
}
