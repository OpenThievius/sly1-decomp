// SPDX-License-Identifier: AGPL-3.0-or-later
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
#include "asm_func.h"

f32 func_001EAAE0(f32 a, f32 b);
extern f32 D_0026185C;
struct Vec2_1B55A8 { f32 x; f32 y; };
struct Walk_1B5D80 { s32 a; u32 b; u32 c; };
struct Obj_1B65F8 {
    u8 pad0[0x24];
    void* f24;
    u8 pad1[0x10];
    f32 f38;
};
void func_0012F6B0(void* p);
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
s32 func_001300E8(void* a, s32 b);
s32 func_00182F40(Collider* e, void* b);
void func_0015FCD8(C09* self, void* p);
void func_001BF048(void* p);
struct Node_1B6C68 {
    u8 pad[0x28];
    s32 f28;
    s32 index;
};
void func_001B6E28(Node_1B6C68* self, s32 a, s32 b);
struct Node_1B6CA8 {
    u8 pad[0x24];
    s32 f24;
};
void func_001B6C68(Node_1B6CA8* self);
void func_001B66A0(Node_1B6CA8* self);
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
struct Node_1B6E28 { u8 pad[0x18]; StateGraph* host; };
void func_001837E0(StateGraph* host, s32 a, s32 b, void** args);
struct Node_1B5EA0 { Node_1B5EA0* next; };
struct Pool_1B5EA0 { u8 pad[8]; Node_1B5EA0* head; };
struct Node_1B5EC0 { Node_1B5EC0* next; };
struct Pool_1B5EC0 { u8 pad[8]; Node_1B5EC0* head; };
void* func_001B5EA0(Pool_1B5EC0* pool);
struct Node_1B5EE0 { Node_1B5EE0* next; };
struct Pool_1B5EE0 { s32 count; u8 pad[4]; Node_1B5EE0* head; };
void* func_001B5EA0(Pool_1B5EE0* pool);
void func_001F5C0C(void* p, int zero, s32 count);
void func_00152470(void* p, void* self);
void func_00152600(void* p, void* self);
void func_00182C58(void* self);
void func_001B61F0(void* self);
void* func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
struct Pair_1B63C0 {
    s32 key_00;
    s32 value_04;
};
s32 func_001B63C0(void* self, s32 key);
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
void func_0012E760(void* p);
void func_001DBC18(void* a, void* b);
void func_00152600(void* a, void* b);
void func_001B5F28(void* a, void* b);
void func_001837E0(void* a, s32 b, s32 c, s32 d);
struct Vec3_1B5588 { f32 x; f32 y; f32 z; };
struct __attribute__((aligned(16))) Quad_001B4580 { f32 v[4]; };
struct Slot_1B70B0 { s32 value; s32 pad4; };
struct Self_1B70B0 { u8 pad0[0xC38]; Slot_1B70B0 slots[1]; };
s32 func_001CA600(s32 index);
void func_00124A48(void* self);
struct Walk_1B5DD0 { s32 a; void* b; s32 c; };
void* func_0018D500(s32 size);
void func_001B5D80(void* s, s32 v, s32 n);
struct Walk_1B5E30 { s32 a; void* b; s32 c; };
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
struct Holder_1B6DF8 {
    u8 pad0[0x14];
    void* ptr;
};
struct Self_1B6DF8 {
    u8 pad0[0x18];
    Holder_1B6DF8* holder;
};
void func_001831E8(void* a, void* b, s32 c, void* d);
struct Pair_1B7128 {
    s32 key;
    s32 value;
};
void func_001C72A0(void* self);
void func_001B6F50(void* self);
s32 func_0015A448(void* host, s32 id, void* ctx);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_001C7CB8(void* self);
void func_001B7638(void* self);
typedef void (*VFn_1B7790)(void* self);
struct Sub_1B7790 { VFn_1B7790* vtbl; };
void func_001C91C8(void* self);
typedef s32 (*VFn_1B7818)(void* self);
s32 func_001CA468(void* self);
void func_001C9DE0(void* self, s32 code, void* req);
void func_00124FC0(void* self);
void func_001C6F48(void* self);
struct Ent_1B6EC8 { s32 v; s32 pad; };
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
s32 func_0015A448(void* owner, s32 value, void* bank);
void* func_001B6290(void* bank, s32 r, s32 minus_one, s32 zero);
u16 func_001B5B58(u8 ch);
s32 func_001E2100(void* p);
struct Inner_1B6CF0 { u8 pad[0x34]; f32 f34; };
struct Item_1B6CF0 {
    u8 pad[0x8];
    Inner_1B6CF0* inner;
    u8 pad2[0x14 - 0x0C];
    f32 f14;
};
struct Node_1B6CF0 { u8 pad[0x24]; s32 f24; };
f32 func_001B6C68(Node_1B6CF0* self);
void func_001B66A0(Node_1B6CF0* self);
void func_0012F0A0(void* a, f32 b, f32 c, s32 d);
s32 func_001B63F8(void* self, s32 key);
void func_001B6E28(StateWalker* self, s32 a, s32 b);
void func_001B66A0(StateWalker* self);
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
s32 func_001B63F8(StateGraph* self, s32 key);
void func_001B6C68(Node_1B64D8* self);
void func_0012E760(AnimationPlayer* obj);
void func_001B66A0(Node_1B64D8* self);
struct Entry_2198E8 { const u8* f0; s32 f4; };
extern const Entry_2198E8 D_002198E8;
void* func_001B5EE0(Pool6C* pool);
void func_00152470(List01* list, StateWalker* item);
void func_001837E0(StateGraph* self, s32 a, s32 b, void* c);
struct Hdr_1B6F50;
struct Elem_1B6F50;
struct Sub_1B6F50 { u8 p0[0x11]; u8 f11; u8 p1[0x0A]; s32 f1C; u8 p2[0x60]; s32 f80; s32 f84; };
typedef void (*VFn_1B6F50)(void* self);
struct Elem_1B6F50 { VFn_1B6F50* vtbl; };
struct Ent_1B6F50 { s32 key; void* val; };
extern u8 D_0021A790[];
void* func_0015A448(Hdr_1B6F50* obj, s32 id, C09* flags);
s32 func_0015A4F0(Hdr_1B6F50* a0, s32 a1, s32 a2, C09* a3, s32 a4, void* a5);
s32 func_001833F0(Elem_1B6F50* a, s32 b);
void func_0018D608(void);
void func_0018D6F0(void);
void* func_0018D658(u32 bytes);
void* func_00121228(Hdr_1B6F50* root, s32 value, void* table);
void func_001299E0(Hdr_1B6F50* self, void* src);
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
s32 func_001C96B8(C09 *self);
s32 func_001CB578(C09 *self);
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
void* func_0018D658(s32 size);
void func_001B6E28(Mover_1B66A0* self, s32 a, s32 b);
s32 func_0012C7B0(Track_1B66A0* track, s32 a1, s32 a2, void** out, f32 fa, f32 fb);
void func_0012F7E0(void* obj, void (*fn)(Mover_1B66A0*, s32, s32), Mover_1B66A0* self);
void func_001B6CA8(Mover_1B66A0* self, s32 a, s32 b);
void func_0012F190(void* obj, s32 zero);
void func_0012E760(void* obj);
void func_001B6D78(Mover_1B66A0* self, s32 a, Mover_1B66A0* b);

struct Sjis_274588 { u16 code; u16 id; };

// The file's .data, in retail's order.
s32 D_00274548[4] = { 0, 1, 2, 0 };
s32 D_00274558[4] = { 2, 0, 1, 0 };
s32 D_00274568[4] = { 0, 2, 1, 0 };
s32 D_00274578[4] = { 1, 0, 2, 0 };
Sjis_274588 D_00274588[34] = {
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
Sjis_274588 D_00274610[4] = {
    { 0x824F, 0x0030 }, { 0x8260, 0x0041 }, { 0x8281, 0x0061 }, { 0x0000, 0x0000 }
};
f32 D_00274620[16] = { 0.0f, 0.0f, -80.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, -70.0f, 40.0f, 0.0f, 0.0f, 70.0f, 40.0f, 0.0f };
f32 D_00274660[16] = { 0.0f, 0.0f, -20.0f, 0.0f, 0.0f, 0.0f, 70.0f, 0.0f, 0.0f, -30.0f, 30.0f, 0.0f, 0.0f, 30.0f, 30.0f, 0.0f };
f32 D_002746A0[8] = { 1000.0f, 0.0f, 0.0f, 0.0f, 2.0f, -2.0f, 0.0f, 0.0f };

void func_001B5588(Vec3_1B5588* dst, Vec3_1B5588* src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

void func_001B55A8(Vec2_1B55A8* a0, Vec2_1B55A8* a1)
{
    a0->x = a1->x;
    a0->y = a1->y;
}

INCLUDE_RODATA(D_0024D268);
ASM_FUNC(func_001B55C0);

LINKER_REMNANT(func_001B5B48);

INCLUDE_ASM(func_001B5B58);

void func_001B5C40(u8* src, u16* dst)
{
    s32 n = GetStringLength(src);
    s32 i;
    for (i = 0; i < n; i++) {
        u32 r = func_001B5B58(src[i]);
        u32 lo = (r & 0xFF) << 8;
        u32 hi = (r >> 8) & 0xFF;
        dst[i] = (u16)(hi | lo);
    }
    dst[i] = 0;
}

void func_001B5CD8(CameraPositionedObject* self)
{
    StartPlacedObject(self);
    self->flags = (self->flags & 0xFFFFFCFFFFFFFFFFULL) | 0x10000000000ULL;
}

void func_001B5D28(CameraPositionedObject* self)
{
    UpdatePlacedObject(self);
    Vec02* src = (Vec02*)g_camera->f40;
    Vec02 q = *src;
    if (self->followHeight == 0) {
        q.z = self->v140.z;
    }
    self->desc02()->m1D(self, &q);
}

void func_001B5D80(Walk_1B5D80* s, s32 v, s32 n)
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

void func_001B5DD0(Walk_1B5DD0* s, s32 size, s32 count)
{
    s32 stride = (size + 7) & ~7;
    s->b = AllocateFrontMemory(stride * count);
    BuildFreeList(s, stride, count);
}

void func_001B5E30(Walk_1B5E30* s, s32 size, s32 count)
{
    s32 addr = (s32)AllocateFrontMemory(size * count + 0x30);
    s->b = (void*)((addr + 0x3F) & -0x40);
    BuildFreeList(s, size, count);
}

LINKER_REMNANT(func_001B5E98);

void* func_001B5EA0(Pool_1B5EA0* pool)
{
    Node_1B5EA0* n = pool->head;
    if (n != 0) {
        pool->head = n->next;
    }
    return n;
}

void* func_001B5EC0(Pool_1B5EC0* pool)
{
    return PopFreeSlot(pool);
}

void* func_001B5EE0(Pool_1B5EE0* pool)
{
    void* p = PopFreeSlot(pool);
    FillMemory(p, 0, pool->count);
    return p;
}

void func_001B5F28(Pool6C* list, Attachment* item)
{
    if (item) {
        item->vt = (const T2195_Vt*)list->head;
        list->head = item;
    }
}

LINKER_REMNANT(func_001B5F48);

INCLUDE_ASM(func_001B5F50);

void func_001B61A8(StateGraph* self)
{
    StartObject(self);
    if (self->armed != 0) {
        AppendQueuedCall(self->world, (void*)SpawnInitialStateWalker, self, 0, 0);
    }
}

void func_001B61F0(Bank_1B61F0* self)
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

StateWalker* func_001B6290(StateGraph* self, s32 a1, s32 a2, s32 a3)
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

void* func_001B6388(Owner_1B6388* self, s32 key)
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

s32 func_001B63C0(StateGraph* self, s32 key)
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

s32 func_001B63F8(void* self, s32 key)
{
    s32 r = FindStateEntryIndex(self, key);
    return r < 0 ? 0 : r;
}

u32 func_001B6420(StateGraph* a0, s32 a1)
{
    a1 = (a1 << 3) + (u32)a0->f38;
    return *(u32*)a1;
}

void func_001B6438(Obj_001B6438* self)
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

void func_001B64D8(Node_1B64D8* self, s32 key)
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

void func_001B6568(StateWalker* a0, s32* out) {
    s32 idx = a0->index;
    s32 v;
    if (idx >= 0) {
        v = ((StateGraph*)a0->owner)->f38[idx].key;
    } else {
        v = -1;
    }
    *out = v;
}

void func_001B6598(StateWalker* a0, s32* out) {
    s32 idx = a0->f28;
    s32 v;
    if (idx >= 0) {
        v = ((StateGraph*)a0->owner)->f38[idx].key;
    } else {
        v = -1;
    }
    *out = v;
}

void func_001B65C8(StateWalker* self, s32* out)
{
    s32 value;
    if (self->f2C >= 0) {
        value = ((StateGraph*)self->owner)->f38[self->f2C].key;
    } else {
        value = -1;
    }
    *out = value;
}

void func_001B65F8(Obj_1B65F8* self, f32 v)
{
    self->f38 = v;
    if (self->f24 != 0) {
        SetAnimationPlayerSpeed(self->f24);
    }
}

void func_001B6628(StateWalker* self, s32 key)
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

void func_001B66A0(Mover_1B66A0* self)
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
                    func_0012F7E0(self->f24, HandleStateWalkerTrackEnd, self);
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

void func_001B6C68(Node_1B6C68* self)
{
    NotifyStateWalkerChange(self, self->f28, self->index);
    s32 v = self->index;
    self->index = -1;
    self->f28 = v;
}

void func_001B6CA8(Node_1B6CA8* self, s32 a, s32 b)
{
    if (a == 5 && b == self->f24) {
        CommitStateWalkerArrival(self);
        StartNextStateWalkerEdge(self);
    }
}

void func_001B6CF0(Node_1B6CF0* self, f32 t)
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

void func_001B6D78(Node_1B6D78* self, s32 a, s32 b)
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

void func_001B6DF8(Self_1B6DF8* self, PlacedObject** p)
{
    AddCallbackNode(self->holder->ptr, (u8*)self + 0x3C, (s32)(*p)->link40.prev, p);
}

void func_001B6E28(Node_1B6E28* self, s32 idx1, s32 idx2)
{
    void* args[3];
    s32 v1;
    s32 v2;
    if (idx1 >= 0) {
        v1 = self->host->f38[idx1].key;
    } else {
        v1 = -1;
    }
    if (idx2 >= 0) {
        v2 = self->host->f38[idx2].key;
    } else {
        v2 = -1;
    }
    args[0] = &self;
    args[1] = &v1;
    args[2] = &v2;
    TriggerScriptEvent(self->host, 0xE, 3, args);
}

void func_001B6EC8(C09* self)
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

void func_001B6F50(C09* self)
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

void func_001B70B0(Self_1B70B0* self, s32 index, s32 value)
{
    (void)IsAgentSlotIndex(index);
    self->slots[index].value = value;
}

void func_001B7100(C09* self, s32 value)
{
    s32 n = self->fCD4;
    if ((u32)n < 4) {
        self->fCD8[n].id = value;
        n++;
        self->fCD4 = n;
    }
}

void func_001B7128(C09* self)
{
    StartAgent(self);
    func_001B6F50(self);
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

s32 func_001B71C8(Self_1B71C8* self, Collider* ent)
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

ASM_FUNC(func_001B7280);

void func_001B7608(C09* self)
{
    UpdateAgent(self);
    func_001B7638(self);
}

void func_001B7638(C09 *self) {
    struct Target_1B7638 *t;
    s32 r;
    s32 res;
    f32 f;

    if (self->fC14 == 0) {
        return;
    }
    t = (struct Target_1B7638 *)self->fC34;
    r = func_001C96B8(self);
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

void func_001B7790(C09* self)
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

s32 func_001B7818(C09* self)
{
    if (IsAgentTargetInRange(self) == 0) {
        return 0;
    }
    return ((VFn_1B7818*)self->desc)[91](self);
}

s32 func_001B7860(C09* self)
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

void func_001B78C0(C09* self, s32 code, void* req)
{
    HandleAgentNotification(self, code, req);
    if (code == 7) {
        if (req == self->f7E0) {
            self->fCC4++;
        }
    }
}

void func_001B7920(C09* self, void* p)
{
    SetColliderFrozen(self, p);
    if (p != 0) {
        ReleaseSoundLevel(self->fCC0);
        self->fCC0 = 0;
    }
}
