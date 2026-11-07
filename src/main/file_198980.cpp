// SPDX-License-Identifier: AGPL-3.0-or-later
// The source file from 0x198980 to 0x19D410, built whole (config/us/files.tsv): one file between
// two exact edges, which could be several. It holds the object sets (class 0x2C) and the
// classes built on them (0x2D, 0x2E), classes 0x5C and 0x5D, class 0x17, class 0x71, the object
// gatherer (class 0x41), class 0x7C and class 0x8B with the VU0 helpers only it and
// func_0019D2A8/func_0019D338 call. Its .rodata (0x24C870 to 0x24C930) is the jump tables of
// func_0019A6A8, func_0019B378 and func_0019C1C0 (assembly for now) and the FLT_MAX literal of
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
#include "asm_func.h"
void func_001B7968(void* self);
void func_001249A8(void* self);
void* func_0015A448(void* a, void* b, void* c);
// A descriptor slot called by its index (the slots past class 0x01's, whose types the
// descriptors give differently).
typedef s32 (*SlotTest)(void* self);
void func_00124A48(void* self);
s32 func_0012C9A8(void* node);
void func_00182ED8(void* node);
typedef void (*SlotFn)(void* self);
void* func_0012C8F8(void* item, s32 a, f32 x, s32 b, f32 y, s32 c);
void func_001837E0(void* self, s32 a, s32 b, s32 c);
s32 func_00182FC8(void* self);
void func_001BA130(void*);
void func_00198980(ObjectSet*);
void func_001B7F78(void);
void func_00182D48(void*);
void func_00152470(void*, void*);
void func_00182ED0(void*);
void func_00152600(void*, void*);
void func_00182C58(void*);
void* func_0015A418(void*, s32, s32, void*);
void func_001B7A98(void*);
void func_001B7B78(void*);
void func_00182C18(void*);
void func_00127378(ObjectSet* self, s32 msg, ObjectMessage* m);
s32 func_001300E8(void* obj, s32 kind);
void* func_001929F8();
s32 func_00182F40(void* e, void* b);
// The active switched collider's data block (SwitchedCollider + 0x580): at 0x18 the collider.
struct ActiveColliderData {
    u8 pad0[0x18];
    void* f18;
};
// One of the nine 0x78-byte records at the start of a level's record (G27C230): its flags.
struct LevelTaskRecord { s32 flags; u8 rest[0x74]; };
// The element stack (g_elementStack), as file_15F678.cpp and file_16AA18.cpp view it.
struct ElementStackState { u8 pad0[0x30]; s32 f30; };
extern ElementStackState D_00275BC0;
void func_0019A088(s32 index);
void func_001E5278(s32 mode);
void func_001921A8(C17* self);
// One of C17's three markers at 0x61C (StartC17Marker): its owner, the object found for it and
// that object's state walker.
struct C17Marker { s32 owner; s32 object; s32 walker; };
s32 func_0015A418(s32 a, s32 b, s32 c, s32 d);
void func_00182ED8(s32 a);
s32 func_001B6290(s32 a, s32 b, s32 c, s32 d);
void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);
void func_0016EC88(void* p);
s32 func_001602A0(void);
void func_00160578(s32 value);
void* func_0015A448(void* a, s32 code, void* c);
extern u8 D_00262C70[];
void func_001830D8(void* self);
void func_00124DF8(void* self, s32 n, void* table);
extern u8 D_00261420[];
void func_00198980(ObjectSet* self);
void* func_00140FF8(void* p);
void func_001989B0(ObjectSet* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void* func_0018D500(s32 size);
// What func_0019BE08 is given: two quadwords at 0x20 and 0x30.
struct GatherTrigger { u8 pad[0x20]; Quad16 q20; Quad16 q30; };
void func_0019C1C0(void* self, s32 mode);
s32 func_00198E98(ObjectSet* self);
s32 func_00141008(void* table, s32 index);
void func_00141040(void* table, s32 index);
void func_00198DA8(ObjectSet* self);
typedef void (*SlotFnInt)(void* self, s32 a);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
s32 func_001BC320(void* self, ObjectEvent* ev);
void func_001BA130(void* self);
void func_001289C0(void* self);
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void func_00199B18(void* obj);
s32 func_001300E8(void* node, s32 kind);
extern f32 D_0026185C[];
f32 func_001EAB48(f32 a, f32 b, f32 c);
void func_001BAC30(void* self);
void func_00159478(void* sub, void* self);
void* func_0015A480(void* self, s32 kind, void* arg);
extern s32 D_00270454;
extern u8 D_00264A40[];
void func_001B64D8(void* a, s32 b);
void func_001E9570(void* q);
void func_001604B8(s32 mode);
void func_0018C7F8(void* p);
void* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
extern s32 D_00275C34;
void func_00198B28(ObjectSet* self);
f32 func_001EAAE0(f32 a, f32 b);
s32 func_001EAA70(s32 a, s32 b);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00128018(void* a0, s32 a1, void* a2, void* a3);
Effect* func_0019EA78(s32 kind, EffectOwner* sys);
void func_00199850(NumberedItem* self);
void func_001518B8(s32 x);
void func_00124A48(C17* o);
void func_00124DF8(C17* o, s32 n, u8* t);
void func_0019A178(void* p, s32 x);
s32 func_001B6290(s32 a, C17* b, s32 c, s32 d);
void func_001B64D8(s32 a, s32 b);
BaseObject* func_0015A448(World* a, s32 b, C17* c);
void func_00160D30(s32* p);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_001B64D8(void* p, s32 n);
void* func_0012C8F8(void* self, s32 key, s32 a2, s32 a3, f32 fa, f32 fb);
void func_001781E0(Player* a, s32 v);
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
void func_00182ED8(BaseObject* n);
s32 func_001300E8(void* key, s32 kind);
s32 func_00182FC8(void* p);
void func_00192230(void* self, s32 code, s32* rec);
void func_00175170(void* self, s32 a, s32 b);
s32 func_0019A000(s32 bits);
void func_001518B8(StepSequence* s);
void func_001B7968(Collider* self);
void func_00152470(void* list, void* item);
void func_00152600(void* table, void* self);
extern f32 D_00261858[];
struct Frame_19D2A8 { Quad16 q0; Quad16 q1; s32 w20; s32 w24; };
void func_0019CEC0(void* a, void* b, void* c, f32 d);
void func_0019D0E0(void* a, void* b, void* c, void* d, void* e);
void func_0019C9C8(void* a, s32 b, void* c);
struct Frame_19D338 {
    Quad16 q0;
    Quad16 q1;
    Quad16 q2;
    Quad16 q3;
    s32 w40;
    s32 w44;
    s32 w48;
    s32 w4C;
};
void func_001B7B78(Collider* self);
struct LoadStream;
s32 func_00137D10(LoadStream* in);
void func_00137FB0(LoadStream* in, void* p);
void* func_0018D5C0(s32 n);
s32 func_00137CC0(LoadStream* in);
void func_0019CD90(C8B* o, s32 i, f32* x, f32* y, f32* z);
void func_0019CC10(f32 x, f32 y, f32 z, C8B* o, void* p);
f32 func_00137DF8(LoadStream* in);
void func_0011EC40(C8B* o, LoadStream* in);
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
void func_00152600(List01 *a, ObjectGatherer *b);
void func_00152470(List01 *a, ObjectGatherer *b);
void func_00128018(void *a, s32 b, void *c, Quad4 *d);
void func_001B9860(ObjectGatherer *a, Quad4 *b, void *c);
void func_001B7C40(ObjectGatherer *self, s32 flag);
void func_00182C58(void* self);
void* func_0015A448(void* a, s32 b, void* c);
void* func_0015A480(void* a, s32 b, void* c);
void func_00139600(s32 a, s32 b, void* c, s32 d, s32 e, void* f);
void func_00139038(void* self, s32 a, s32 b, void* c, s32 d, void* e, void* f, void* g);
void func_00139B38(void* g, void* n);
void func_0019CC10(C8B* self, f32* out, f32 a, f32 b, f32 c);
void func_001399F8(void* g, s32 a, s32 b, void* c);
void func_0012CD78(f32 a, f32 b, Gr8B* g, void* r1, void* r2, s32 r3, void* r4, s32 r5, s32 r6, s32 r7);

// The file's .data, in retail's order. D_0026A910 and D_0026A914 are read by the VU0 function
// func_00198BD8, D_0026A968 by func_00199698, D_0026ABB0 and D_0026ABC0 by func_0019B298 and
// func_0019B378.
f32 D_0026A910 = 100.0f;
s32 D_0026A914 = 0;
ObjectLink D_0026A918[1] = { { 0x0, 0x22B, 0x2D0 } };
ObjectLink D_0026A928[1] = { { 0x0, 0x22D, 0x2D8 } };
ObjectLink D_0026A938[1] = { { 0x0, 0x22C, 0x2D4 } };
ObjectLink D_0026A948[1] = { { 0x0, 0x339, 0x5BC } };
f32 D_0026A958[2] = { 0.8f, 1.2f };
f32 D_0026A960[2] = { 0.9f, 1.1f };
f32 D_0026A968 = 300.0f;
T219C_Params D_0026A970 = { { 0.85f, 0.75f, 100.0f, 0.0f, 1.0f, -3.0f, 0.0f, 0.0f, -1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.2f, 0.25f, 0.0f }, (void (*)(void*))func_00199850 };
s32 D_0026A9E0[28] = { 2, 4, 8, 16, 65536, 32, 64, 128, 256, 512, 131072, 1024, 2048, 8192, 4096, 16384, 32768, 0, 0, 0, 0, 0, 0, 268435456, 536870912, 1073741824, (-2147483647 - 1), 1 };
ObjectLink D_0026AA50[26] = {
    { 0, 0x376, 0x610 }, { 0, 0x37C, 0x618 }, { 4, 0x377, 0x61C }, { 4, 0x378, 0x628 }, { 4, 0x379, 0x634 }, { 6, 0x3A2, 0x768 }, { 6, 0x3A4, 0x76C }, { 6, 0x3A5, 0x770 }, { 6, 0x3A6, 0x774 }, { 6, 0x3A7, 0x77C }, { 6, 0x3A8, 0x780 }, { 6, 0x3A9, 0x784 }, { 6, 0x3AB, 0x788 }, { 6, 0x3AC, 0x78C }, { 6, 0x3AD, 0x790 }, { 6, 0x3AE, 0x794 }, { 6, 0x3AF, 0x798 }, { 6, 0x3B0, 0x79C }, { 6, 0x3B1, 0x7A0 }, { 6, 0x3B2, 0x7A4 }, { 6, 0x3B3, 0x7A8 }, { 6, 0x3B4, 0x7C4 }, { 6, 0x3B5, 0x7C8 }, { 6, 0x3B6, 0x7CC }, { 6, 0x3B7, 0x7D0 }, { 6, 0x3D8, 0x7D4 } };
// Eight zero bytes no code reads, inside retail's label D_0026AA50 after its 26 entries.
s32 D_0026AB88[2] = { 0, 0 };
ObjectLink D_0026AB90[1] = { { 0x0, 0x268, 0x5EC } };
ObjectLink D_0026ABA0[1] = { { 0x4, 0x267, 0x5FC } };
f32 D_0026ABB0[4] = { 12.0f, 0.0f, 0.12f, 0.0f };
f32 D_0026ABC0[4] = { 500.0f, 1.0f, 0.0f, 0.0f };
s32 D_0026ABD0[2] = { 0x130, 0x132 };
s32 D_0026ABD8[2] = { 2, 0 };
s32 D_0026ABE0[4] = { 0x10, 0, 0, 0 };


void func_00198980(ObjectSet* self)
{
    InitCollider(self);
    self->f554 = 1;
}

void func_001989B0(ObjectSet* self)
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

void func_00198A88(ObjectSet* self)
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

void func_00198B28(ObjectSet* self)
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

ASM_FUNC(func_00198BD8);

void func_00198DA8(ObjectSet* self)
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

void func_00198E58(ObjectSet* self)
{
    BaseObject* t = (BaseObject*)self->f584;
    if (t != 0) {
        SlotMessage msg;
        msg.kind = 1;
        msg.owner = self;
        t->desc->m1B(t, &msg);
    }
}

s32 func_00198E98(ObjectSet* self)
{
    if (IsObjectAttached(self)) {
        return (self->f554 != 0) ? 1 : 2;
    }
    return 0;
}

void func_00198ED8(ObjectSet* queue, void* item)
{
    queue->keys560[queue->n55C++] = item;
}

void func_00198EF8(ObjectSet* self, s32 msg, ObjectMessage* m)
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

s32 func_00198FB0(ObjectSet* unused, void* obj)
{
    if (IsObjectOfKind(obj, 8) != 0 || IsObjectOfKind(obj, 0x3B) != 0) {
        return 1;
    }
    return 0;
}

void func_00199000(ObjectSet* self, Contact03* elems, s32 idx)
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

void func_00199070(FlaggedObjectSet* self)
{
    InitObjectSet(self);
    self->f5A0 = (s32)TakeFlagTableIndex(g_flagTable);
}

void func_001990A8(FlaggedObjectSet* obj)
{
    s32 value = obj->f5A0;
    CopyCollider(obj);
    obj->f5A0 = value;
}

s32 func_001990E0(FlaggedObjectSet* self)
{
    s32 r = GetObjectSetActivationState(self);
    if (r == 1) {
        r = TestFlagTableBit(g_flagTable, self->f5A0) ? 0 : r;
    }
    return r;
}

void func_00199138(FlaggedObjectSet* self)
{
    SetFlagTableBit(g_flagTable, self->f5A0);
    CollectObjectSet(self);
}

void func_00199170(C5C* self)
{
    LoadPlacedObject(self);
    ResolveObjectLinks(self, 1, (u8*)D_0026A918);
}

void func_001991A8(C5C* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 1, (u8*)D_0026A928);
}

void func_001991E0(C5D* self)
{
    LoadPlacedObject(self);
    ResolveObjectLinks(self, 1, (u8*)D_0026A938);
}

void func_00199218(C5D* self)
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

void func_00199380(C5D* flags, u32 bit)
{
    flags->mask2D0 = 1 << (bit + 1);
}

void func_00199398(C5D* queue, void* item)
{
    u32 count = queue->count2DC;
    if (count < 8) {
        queue->ids2E0[count] = (s32)item;
        queue->count2DC = count + 1;
    }
}

void func_001993C0(s32 a0) {
    if (g_player != 0) {
        (void)QueuePlayerWalkerActivation(g_player, a0);
    }
}

void func_001993F0(NumberedItem* obj)
{
    InitObjectSet(obj);
    obj->f5A0 = obj->world->count2300++;
}

void func_00199428(NumberedItem* self)
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

void func_001994C8(NumberedItem* obj)
{
    s32 value = obj->f5A0;
    CopyCollider(obj);
    obj->f5A0 = value;
}

void func_00199500(NumberedItem* self)
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

ASM_FUNC(func_00199698);

void func_00199850(NumberedItem* self)
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

void func_001999D0(NumberedItem* self)
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
        func_00128018(self, 0, self->f5BC + 0x100, &loc);
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

void func_00199B18(NumberedItem* self)
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

void func_00199C10(NumberedItem* self, s32* out)
{
    s32 n = self->f5A0;
    s32 byte = n / 8;
    s32 bit = n & 7;
    u8 b = g_currentEntry->bits68[byte];
    s32 mask = 1;
    mask <<= bit;
    *out = (b & mask) != 0;
}

void func_00199C58(void)
{
    ApplyColliderPendingImpulse();
}

s32 func_00199C78(NumberedItem* self, ObjectEvent* a1)
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

ASM_FUNC(func_00199D08);

void func_00199F38(void)
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

void func_00199FF0(u32 value)
{
    g_saveData->u19F0 = value;
}

s32 func_0019A000(s32 bits)
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

void func_0019A088(s32 index)
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

void func_0019A0F0()
{
    for (s32 i = 0; i < 6; i++) MarkLevelRecordComplete(i);
    if (g_elementStack.f30 == 2) RequestWorldLoadByMode(0);
}

void func_0019A148(C17* self)
{
    InitSwitchedCollider(self);
    self->f64C = -1;
    self->f644 = -1;
}

void func_0019A178(C17Marker* self, s32 x)
{
    self->object = FindFirstObjectById((s32)g_currentWorld, 0x101, 0x37A, self->owner);
    ResolveAndStartObject(self->object);
    self->walker = CreateStateWalker(self->object, self->owner, x, 0);
}

void func_0019A1E0(C17* o)
{
    u32 i;
    StartPlacedObject(o);
    ResolveObjectLinks(o, 0x1A, (u8*)D_0026AA50);
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

void func_0019A520(C17* self, s32 flag)
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
        ResetPadStepRepeat(g_padRecord);
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

INCLUDE_RODATA(jtbl_0024C870);
INCLUDE_RODATA(jtbl_0024C8A0);
INCLUDE_ASM(func_0019A6A8);

void func_0019AB78(C17* self, s32 msg, s32* rec)
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

void func_0019AD30(C17* list, u32 index, void* item)
{
    Ent17* record = (Ent17*)((u8*)list + 0x658 + index * 0x2C);
    u32 count = record->count;
    if (count < 4) {
        record->keys[count] = (s32)item;
        record->count = count + 1;
    }
}

void func_0019AD68(C17* self)
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

void func_0019AF00(C71* self)
{
    InitObject(self);
    self->targetId = -1;
    self->f4C = 3.4028235e+38f;
}

void func_0019AF38(C71* obj)
{
    RegisterObject(obj);
    AppendToList(&obj->world->list1C90, obj);
}

void func_0019AF70(C71* obj)
{
    UnregisterObject(obj);
    RemoveFromList(&obj->world->list1C90, obj);
}

void func_0019AFA8(C71* obj)
{
    StartObject(obj);
    if (obj->targetId != -1)
        obj->target = (s32)FindFirstObjectById(obj->world, 4, obj->targetId, obj);
}

void func_0019AFF0(C71* self)
{
    PathCurveKeptBits tmp;

    tmp = self->keep;
    CopyObjectData(self);
    self->keep = tmp;
}

void func_0019B038(ObjectGatherer* self)
{
    InitCollider(self);
    self->f60C = 1.0f;
    self->f608 = 0.5f;
    self->f55C = RandomGaussian(*(f32*)g_gameTime + 3.0f, 1.0f, 2.5f);
    self->f664 = -1;
}

void func_0019B0A0(ObjectGatherer* self)
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

void func_0019B188(ObjectGatherer* self)
{
    ResolveObjectLinks(self, 1, (u8*)g_objectGathererStartLinks);
    StartPlacedObject(self);
    self->state = -1;
    func_0019C1C0(self, 1);
    self->v650 = self->v140;
}

void func_0019B1E0(ObjectGatherer* obj)
{
    RegisterCollider(obj);
    AppendToList(&obj->world->list1C60, obj);
}

void func_0019B218(ObjectGatherer* obj)
{
    UnregisterCollider(obj);
    RemoveFromList(&obj->world->list1C60, obj);
}

void func_0019B250(ObjectGatherer* self)
{
    PackedS64 tmp;
    tmp = self->q600;
    CopyCollider(self);
    self->q600 = tmp;
}

ASM_FUNC(func_0019B298);

INCLUDE_RODATA(jtbl_0024C8D0);
INCLUDE_RODATA(jtbl_0024C8F0);
ASM_FUNC(func_0019B378);

ASM_FUNC(func_0019BB10);

ASM_FUNC(func_0019BB90);

ASM_FUNC(func_0019BC40);

s32 func_0019BE08(ObjectGatherer* self, GatherTrigger* src)
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

ASM_FUNC(func_0019BE80);

void func_0019C068(ObjectGatherer *self, s32 a1) {
    if (a1 != 0) {
        RemoveFromList(&self->world->list1C60, self);
        ((BaseObject *)self->f5FC)->desc->m03((BaseObject *)self->f5FC);
    } else {
        Quad4 buf;
        AppendToList(&self->world->list1C60, self);
        ((BaseObject *)self->f5FC)->desc->m02((BaseObject *)self->f5FC);
        func_00128018(*(void **)((u8 *)self->f660 + 0x18), 0,
                      (u8 *)self->f660 + 0x40, &buf);
        func_001B9860(self, &buf, (void*)&g_unitZVector);
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

INCLUDE_RODATA(jtbl_0024C910);
ASM_FUNC(func_0019C1C0);

void func_0019C3D0(BaseObject* obj)
{
    RegisterObject(obj);
    AppendToList(&obj->world->list1C6C, obj);
}

void func_0019C408(BaseObject* obj)
{
    UnregisterObject(obj);
    RemoveFromList(&obj->world->list1C6C, obj);
}

void func_0019C440(C8B* obj)
{
    InitObject(obj);
    obj->second38 = -1;
    obj->first34 = -1;
}

void func_0019C470(C8B* o, LoadStream* in)
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
        func_0019CD90(o, i, &x, &y, &z);
        func_0019CC10(x, y, z, o, r->pos);
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

void func_0019C728(C8B* self)
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
    func_00139038(self->f3C, 0x20, 0x18, self->slots, 1, D_0026ABE0, D_0026ABD8, &self->f3E4);
    if (self->f3E4->f78 == 0) self->f3E4->f78 = 1;
    void* nd = FindFirstObjectByIdMode1(self->world, 0x36, self->f3C);
    if (nd != 0) func_00139B38(self->f3E4, nd);
    f32 buf[24];
    func_0019CC10(self, buf, self->f54, self->f58, self->f5C);
    Slot8B* d = self->slots;
    f32* src = buf;
    for (i = 0; i < 24; i++, d++) *(f32*)d = *src++;
    func_001399F8(self->f3E4, 0x20, 0x18, self->slots);
    func_0012CD78(self->f3E4->pC0->p8->f8, 0.0f, self->f3E4, self->f40, self->f3C, 1, &self->q70, 0, 0, 0);
    self->f60 = self->f3E4->pC0->p8->f8;
    if (self->f80 != 0) {
        func_0019CC10(self, buf, self->f84, self->f88, self->f8C);
        d = self->slots;
        src = buf;
        for (i = 0; i < 24; i++, d++) *(f32*)d = *src++;
        func_001399F8(self->f3E4, 0x20, 0x18, self->slots);
        func_0012CD78(self->f3E4->pC0->p8->f8, 0.0f, self->f3E4, self->f40, self->f3C, 1, &self->q90, 0, 0, 0);
    } else {
        self->q90 = self->q70;
    }
    self->f50 = 1;
}

ASM_FUNC(func_0019C9C8);

INCLUDE_ASM(func_0019CC10);

void func_0019CD90(C8B* self, s32 p, f32* out0, f32* out1, f32* out2)
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

void func_0019CE28(C8B* value, f32 x, f32 y, f32 z)
{
    value->f54 = x;
    value->f58 = y;
    value->f5C = z;
}

void func_0019CE38(C8B* self, f32 x, f32 y, f32 z)
{
    self->f80 = 1;
    self->f54 = x;
    self->f58 = y;
    self->f5C = z;
}

ASM_FUNC(func_0019CE50);

ASM_FUNC(func_0019CEC0);

ASM_FUNC(func_0019CF68);

ASM_FUNC(func_0019D0E0);

void func_0019D2A8(Player* self, void* x, void* y)
{
    Frame_19D2A8 f;
    if (y != 0) {
        f32 d = self->f2424 - g_gameClock[1];
        if (d < g_gameClock[2]) {
            d = g_gameClock[2];
        }
        func_0019CEC0(x, y, &f.q0, d);
        func_0019D0E0(x, &f.q0, &f.q1, &f.w20, &f.w24);
        func_0019C9C8(x, f.w20, &f.q1);
    }
}

void func_0019D338(void* self, void* dst, PathCurveObject* src, f32* k)
{
    Frame_19D338 f;
    func_00128018(0, (s32)src->parent, (u8*)self + 0x140, &f.q0);
    PathCurve* o = src->curve;
    if (o->vt->m12 != 0) {
        o->vt->m12(o, *k, &f.q0, 0, (f32*)&f.q1, 0, 0, k);
    }
    func_00128018((void*)src->parent, (s32)self, &f.q1, &f.q2);
    func_0019D0E0(dst, &f.q2, &f.q3, &f.w40, &f.w44);
    func_0019C9C8(dst, f.w40, &f.q3);
}
