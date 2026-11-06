// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "world_listed_object.h"
#include "effect_spawner.h"
#include "world.h"
#include "child_group_object.h"
#include "c8b.h"
#include "v24a0.h"
#include "owned_record.h"
#include "object_message.h"
#include "globals.h"

void func_001389C8(World* a0)
{
    a0->f1AEC = 0;
}

void func_00138BE0(void* a0, Collider* owner, u32 mask)
{
    Collider* n = owner->root03();
    if (n) {
        n->f4B8 &= ~mask;
    }
}

struct Sub_139B38 { u8 pad[0x18]; s32 flag; };
struct Owner_139B38 { u8 pad[8]; Sub_139B38* sub; };

void* func_0012CCE8(void);

void func_00139B38(void)
{
    Owner_139B38* o = (Owner_139B38*)FindEntryByObjectId();
    if (o) {
        if (o->sub) {
            o->sub->flag = 1;
        }
    }
}

extern u8 D_00261314[];
extern u8 D_00261318[];

void func_00139B70(s32 idx, void* arg);

void func_00139C38(void)
{
    func_00139B70(1, D_00261314);
    func_00139B70(2, D_00261318);
}

struct Obj_139C70 { u8 pad0[0x14]; u8* ctx; u8 pad1[0x320 - 0x18]; s32 mode; };

void* func_001B5EA0(void* p);
void func_001B5F28(void* p, void* q);
void func_001F5C0C(void* p, s32 v, s32 n);
void func_00152470(void* list, void* item);

OwnedRecord* func_00139C70(Obj_139C70* o)
{
    OwnedRecord* s = (OwnedRecord*)PopFreeSlot(o->ctx + 0x1B40);
    if (!s) {
        return 0;
    }
    func_001F5C0C(s, 0, 0x10C0);
    if (o->mode != 2) {
        s->owner = o;
    } else {
        void* r = PopFreeSlot(o->ctx + 0x1B4C);
        s->extraRecord = r;
        if (r) {
            func_001F5C0C(r, 0, 0x580);
            s->owner = o;
        } else {
            PushFreeSlot(o->ctx + 0x1B40, s);
            return 0;
        }
    }
    AppendToList((u8*)o + 0x624, s);
    return s;
}

struct Sub_139D28 { u8 pad[0x108C]; struct Obj_139D28* owner; };
struct Obj_139D28 { u8 pad[0x1]; };


void func_00152600(void* list, void* item);
void func_00152470(void* list, void* item);

void func_00139D28(Sub_139D28* o)
{
    RemoveFromList((u8*)o->owner + 0x624, o);
    AppendToList(&D_002622F0, o);
}

struct In_138278 { u8 pad0[0x10]; s32 base; };

s32 func_00137BE0(void* self);
void* func_0018D5C0(s32 size);

void func_00138278(void* self, In_138278* in, Tree03* out)
{
    s32 x = ReadBufferedU16(self);
    out->count = x;
    s32 y = ReadBufferedU16(self);
    out->count2 = y;
    out->nodes = (TreeNode03*)AllocateZeroedFrontMemory(12 * out->count);
    for (s32 i = 0; i < out->count; i++) {
        TreeNode03* e = out->nodes + i;
        s32 v = ReadBufferedU16(self);
        e->face = (void*)(in->base + (v << 5));
        s32 w = ReadBufferedU16(self);
        if ((w & 0xFFFF) != 0xFFFF) {
            e->back = out->nodes + w;
        }
        s32 z = ReadBufferedU16(self);
        if ((z & 0xFFFF) != 0xFFFF) {
            e->front = out->nodes + z;
        }
    }
}

void func_001832F0(WorldListedObject* self, BaseObject* src);
s32 func_001300E8(BaseObject* src, s32 kind);
s32 func_00152720(void* sub);

void func_0013A418(WorldListedObject* self, BaseObject* src)
{
    AddObjectListener(self, src);
    if (IsObjectOfKind(src, 0x50) != 0) {
        EffectSpawner* from = (EffectSpawner*)src;
        self->source = from;
        self->f80 = from->f80;
        if (IsListEmpty(from->list314) == 0) {
            self->flags &= 0xFFFFFFFFF3FFFFFFULL;
            self->flags &= 0xFFFFFFFFCFFFFFFFULL;
        }
    }
}

void* func_001387C0(void* self, void* other);

s32 func_001387F8(void* self, void* other)
{
    s32* p = (s32*)FindContactRow(self, other);
    s32 r = 0;
    if (p != 0) {
        r = *p;
    }
    return r;
}

struct Slot_138828 {
    s32 flag;
    void* owner;
    void* link;
};

void func_001389C8(void* self);

void func_00138828(World* self, void* arg)
{
    World* t = self;
    s32 stride = 24;
    s32 one = 1;
    u8* a3 = (u8*)arg + 0x430;
    u8* a2 = (u8*)arg + 0x420;
    s32 off = 0;
    s32 n = 2;
    do {
        n--;
        Slot_138828* e = (Slot_138828*)((u8*)t->buf1AD8 + off + t->count38 * stride);
        off += 0x1800;
        e->link = a2;
        e->flag = 0;
        e->owner = arg;
        a2 += 4;
        e++;
        e->link = a3;
        e->owner = arg;
        e->flag = one;
        a3 += 4;
    } while (n >= 0);
    func_001389C8(self);
}

void func_00152600(void* sub, void* self);
void func_00152470(void* sub, void* self);
void func_001240F8(void* self);

void func_00139E80(WorldListedObject* self)
{
    RemoveFromList(&self->world->list1CC0, self);
    AppendToList(&self->world->list1CB4, self);
    RegisterPlacedObject(self);
}

extern f32 D_0026185C;


void func_001BAC30(void* self);
void func_00159478(void* sub, void* self);


s32 func_00137BE0(void* src);
void func_00137A60(void* self, s32 size, void* obj);

void func_00138518(void* self)
{
    s32 n = ReadBufferedU16(self);
    ReadBufferedStreamBytes(self, n, 0);
}

struct Range_138550 {
    s32 w[8];
};

void func_00137A60(void* self, s32 size, void* obj);
u32 func_0018D568(s32 size, void* src);

void func_00138550(void* self, u32* out)
{
    Range_138550 r;
    ReadBufferedStreamBytes(self, 0x20, &r);
    if (r.w[1] != r.w[7]) {
        *out = CopyToFrontMemory(0x20, &r);
    } else {
        *out = 0;
    }
}

struct Node_138738 { s32 a0; Node_138738* next; void* a8; s32 value; };
struct List_138738 { Node_138738* head; };
struct Src_138738 { u8 pad0[4]; s32 value4; };

void* func_001B5EC0(void* pool);

Node_138738* func_00138738(World* self, List_138738* list, Src_138738* src)
{
    Node_138738* n = (Node_138738*)func_001B5EC0((u8*)self + 0x1AF0);
    n->a0 = 0;
    n->value = src->value4;
    n->next = list->head;
    list->head = n;
    return n;
}

void* func_001387C0(Collider* self, Collider* other)
{
    ContactRow03* cur = self->root03()->contacts->head;
    PlacedObject* key = other->root;
    if (cur != 0) {
        do {
            if (cur->other != key) {
                cur = cur->next;
            } else {
                return cur;
            }
        } while (cur != 0);
    }
    return 0;
}

void* func_0018D500(s32 size);
void func_001384A0(void* self, u8** out)
{
    s32 size = ReadBufferedU16(self);
    u8* buffer = (u8*)AllocateFrontMemory(size + 1);
    ReadBufferedStreamBytes(self, size, buffer);
    buffer[size] = 0;
    *out = buffer;
}

ContactRow03* func_00138788(void* unused, ContactRow03** head, Contacts03* key)
{
    ContactRow03* node = *head;
    Collider* wanted = key->owner;
    while (node) {
        if (node->other == wanted) {
            *head = node->next;
            break;
        }
        head = &node->next;
        node = node->next;
    }
    return node;
}

void func_001BA130(void* self, void* other);

struct Item_138398 {
    u8 pad0[0x10];
    f32 f10;
    s32 f14;
    s32 f18;
    u8 pad1[0x20 - 0x1C];
};

s32 func_00137BE0(void* src);
void* func_0018D5C0(s32 bytes);
void func_00137E70(void* src, void* item);
f32 func_00137DF8(void* src);
s32 func_00137C40(void* src);

void func_00138398(void* src, s32* count, Item_138398** out)
{
    s32 n = ReadBufferedU16(src);
    *count = n;
    *out = (Item_138398*)AllocateZeroedFrontMemory(n << 5);

    for (s32 i = 0; i < *count; i++) {
        Item_138398* item = &(*out)[i];
        ReadBufferedVector3(src, item);
        item->f10 = ReadBufferedFloat(src);

        s32 v = ReadBufferedU32(src);
        if ((v & 0x80000000) != 0) {
            item->f14 = v;
        } else {
            item->f14 = (s32)((*out) + v);
        }
        v = ReadBufferedU32(src);
        if ((v & 0x80000000) != 0) {
            item->f18 = v;
        } else {
            item->f18 = (s32)((*out) + v);
        }
    }
}

struct Pair_139970 { f32 a; f32 b; };

s32 func_00139970(s32 count, Pair_139970* p, f32 x, f32 period, f32* out)
{
    s32 i;
    for (i = 0; i < count; p++, i++) {
        if (p->b != 0.0f) {
            f32 d = x - p->a;
            if (d < 0.0f) {
                d += period;
            }
            if (d < p->b + 0.0001f) {
                if (out != 0) {
                    *out = d;
                }
                break;
            }
        }
    }
    return i;
}

typedef void (*VFn_139D68)(void* self);

struct Obj_139D68 {
    VFn_139D68* vtbl;
    u8 pad04[0x80 - 4];
    f32 f80;
    u8 pad84[0x2C8 - 0x84];
    u64 bits2C8;
    s32 w2D0;
    u8 pad2D4[0x620 - 0x2D4];
    s32 w620;
};

struct Outer_139D68 {
    u8 pad0[0x1CC0];
    Obj_139D68* obj1CC0;
};

Obj_139D68* func_00139D68(Outer_139D68* self)
{
    Obj_139D68* s0 = self->obj1CC0;
    if (s0 != 0) {
        u64 b = ((s0->bits2C8 & 0xFFFFFFFFF3FFFFFFull) | 0x08000000ull) & 0xFFFFFFFFCFFFFFFFull | 0x20000000ull;
        s0->w2D0 = 0;
        s0->f80 = 1e10f;
        s0->bits2C8 = b;
        s0->w620 = 0;
        s0->vtbl[6](s0);
    }
    return s0;
}

struct Obj_139F80 { u8 pad0[0x380]; s32 f380; u8 pad1[0x20C]; s32 f590; u8 f594[4]; };

extern s32 D_002744FC;
s32 func_001B4688(void* x);
void func_0013A008(Obj_139F80* self);

void func_00139F80(Obj_139F80* self, void* x)
{
    s32 r = FindAnimRecord(x);
    self->f380 = r;
    if (r == 0) {
        self->f380 = g_animRecords;
    }
    if (self->f590 == 0) {
        self->f590 = 1;
        s32 i = 0;
        u8* dst = self->f594;
        do {
            u8* src = (u8*)self->f380 + i;
            dst[i] = (u8)((src[4] + 1) >> 1);
            i++;
        } while (i < 4);
    }
    func_0013A008(self);
}


void func_00127378(ChildGroupObject* self, s32 kind, ObjectMessage* msg);
void func_0013BE00(ChildGroupObject* p, f32 delta);


void func_00152470(void* list, void* item);
void func_00152438(void* self, s32 value);
void func_00123ED0(void* self);

void func_00139DE8(WorldListedObject* self)
{
    AppendToList(&self->world->list1CC0, self);
    InitPlacedObject(self);
    func_00152438(&self->members, 0x1090);
    u64 b = self->flags;
    b &= 0xFFFFFFFFCFFFFFFFull;
    b |= 0x20000000ull;
    b &= 0xFFFFFCFFFFFFFFFFull;
    self->f80 = 1e10f;
    b |= 0x10000000000ull;
    self->flags = b;
}

void func_00124FC0(void* self);
void func_00129DF8(void* self);

void func_0013A3A0(WorldListedObject* self)
{
    UpdatePlacedObject(self);
    func_00129DF8(self);
    FlagRecord* sub = self->flagRecord;
    Camera* g = g_camera;
    s32 hit = 0;
    u32 flags = sub->flags;
    u32 mask = g->f21C;

    if ((flags & 0x10000000) != 0 || (mask & flags) == mask)
        hit = 1;
    if (hit == 0)
        self->desc->m03(self);
}

void* func_001611B8(V24A0* f);
void func_001528F0(V24A0* f, s32 n);
void func_001613C0(V24A0* f, s32 a, s32 b, s32 c);
void func_00161708(V24A0* f, s32 a, u64 b);
void func_001612F8(V24A0* f, s32 a, s32 b, s32 c, u64 d, s32 e);
void func_00152D70(V24A0* f);
void func_001529E0(V24A0* f, s32 a, void* b);

void func_00139B70(s32 idx, void* arg)
{
    V24A0 f;

    InitGifPacket(&f);
    AllocatePacketBuffer(&f, 4);
    BeginGifTag(&f, 0, 1, 0xE);
    AddGifRegisterWrite(&f, 0x47, 0x7180B);
    AddGifRegisterWrite(&f, 0x42, ((u64)(s64)idx << 2) | 0x40);
    ReserveGifPackedData(&f, 0x54, 0, 0xA, 0x424242412EULL, 0);
    CloseDmaTag(&f);
    DetachPacketBuffer(&f, 0, arg);
}

struct ParamBlock_13AD08 { void (*fn)(void* self); s32 zero; s32 count; u8 pad0[0x50 - 0x0C]; f32 radius; u8 pad1[0x60 - 0x54]; void* owner; u8 pad2[0x80 - 0x64]; };
struct Src_13AD08 { u8 pad[0x40]; f32 scale; };

void* func_001F5C0C(void* dst, s32 value, u32 size);
void func_0019D410(void* block);
void func_0013AD80(void* self);

void func_0013AD08(WorldListedObject* owner, s32 unused, Src_13AD08* src)
{
    ParamBlock_13AD08 blk;
    func_001F5C0C(&blk, 0, (u32)0x80);
    blk.count = 0xF;
    blk.fn = func_0013AD80;
    blk.zero = 0;
    if (src != 0) {
        blk.radius = src->scale;
    } else {
        blk.radius = 1.0f;
    }
    blk.owner = owner;
    QueueDeferredRequest(&blk);
}




void func_00139D28(void* a);
void func_00152600(u8* a, void* b);
void func_00152470(u8* a, void* b);
void func_001243E0(void* self);

struct Frame_139EC8 {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};

void func_00139EC8(WorldListedObject* self)
{
    WorldListedObject* obj = self;
    Frame_139EC8 fr;
    s32 e = (s32)&obj->members.head;
    fr.list = e;
    fr.cursor = e;
    s32 old = *(s32*)&g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    fr.prev = old;
    fr.link = link;
    *(s32*)&g_activeListFrames = (s32)&fr;
    s32 head = obj->members.head;
    fr.cursor = head + fr.link;
    s32 node = head;
    while (node != 0) {
        DetachOwnedRecord((void*)node);
        s32 nx = *(s32*)fr.cursor;
        fr.cursor = nx + fr.link;
        node = nx;
    }
    RemoveFromList(&obj->world->list1CB4, self);
    AppendToList(&D_002622E0, self);

    UnregisterPlacedObject(self);
    *(s32*)&g_activeListFrames = fr.prev;
}

// NEAR: frame and loop shape right; retail tests the call condition as a 0/1 value (li a0,1 / beqzl) and orders registers differently

struct Sub_13B430 { u8 pad0[0xC]; s32 next_0C; };
struct Node_13B430 { u8 pad0[0x380]; Sub_13B430* sub_380; u8 pad1[0x630 - 0x384]; Node_13B430* next_630; };


void func_0013A008(Node_13B430* node);

void func_0013B430(s32 mask)
{
    Node_13B430* node;
    s32 v;
    s32 go;
    ListFrame frame;

    if (mask != 0) {
        node = (Node_13B430*)g_currentWorld->list1CB4.head;

        if (node != 0) {
            do {
                v = node->sub_380->next_0C;
                go = 0;
                if ((v & 0x10000000) != 0 || (mask & v) == mask) {
                    go = 1;
                }
                if (go) {
                    func_0013A008(node);
                }
                node = node->next_630;
            } while (node != 0);
        }
    }
}

void func_001385A0(World* a0, s32 a1, Contacts03* a2, s32 a3, s32 a4);

void func_00138F28(World* self, Collider* obj)
{
    obj->f4B8 = 0;
    Contacts03* n = self->usedTables;
    while (n != 0) {
        if (n->owner != obj) {
            s32 s2 = 0;
            if (obj->desc03()->m38(obj, n->owner) || n->owner->desc03()->m38(n->owner, obj)) {
                s2 = 1;
            }
            SetContactPairFlags(self, (s32)obj->contacts, n, s2 == 0 ? 8 : 0, s2 ? 8 : 0);
        }
        n = n->next;
    }
}

void func_001B7968(Collider* self);


struct Link_1385A0 { s32 f0; s32 f4; Link_1385A0* f8; Collider* fC; };

Link_1385A0* func_00138738(World* w, s32 a, s32 b);
Link_1385A0* func_00138788(World* w, s32 a, s32 b);
void func_001861E8(World* w, s32 a);
void func_00129DF8(Collider* e);
void func_001B5F28(u8* w, Link_1385A0* l);

void func_001385A0(World* w, s32 a, s32 b, u8 set, u8 clr) {
    Link_1385A0* n1;
    Link_1385A0* n2;
    s32 ia = (a - (s32)w->tables) >> 4;
    s32 ib = (b - (s32)w->tables) >> 4;
    u8* p = (u8*)w->buf1ADC + (ia << 8) + ib;
    u8* q = (u8*)w->buf1ADC + (ib << 8) + ia;
    u8 v = (set | *p) & ~clr;
    *q = v;
    *p = v;
    if ((v & 0xF) == 0xF || (v & 0x40)) {
        if (v & 0x80) return;
        u8 v2 = v | 0x80;
        *p = v2;
        *q = v2;
        n1 = PushContactRow(w, a, b);
        n2 = PushContactRow(w, b, a);
        n1->f8 = n2;
        n2->f8 = n1;
    } else if (v & 0x80) {
        u8 v2 = v & 0x7F;
        *p = v2;
        *q = v2;
        n1 = UnlinkContactRow(w, a, b);
        n2 = UnlinkContactRow(w, b, a);
        if (n1->f0) {
            u64 m = (u64)0x8000 << 40;
            FreePooledContactChain(w, n1->f0);
            if (!(n1->fC->flags538 & m)) func_00129DF8(n1->fC);
            if (!(n2->fC->flags538 & m)) func_00129DF8(n2->fC);
        }
        PushFreeSlot((u8*)w + 0x1AF0, n1);
        PushFreeSlot((u8*)w + 0x1AF0, n2);
    }
}

struct Obj_139600 { u8 pad0[0x34]; f32 f34; };
struct Elem_139600 { s32 w0; Obj_139600* p4; };
struct Pair_139600 { f32 a; f32 b; };

f32 func_0012CCC0(Obj_139600* a, s32 b);

void func_00139600(s32 stride, s32 count, u8* base, s32 off, s32 count2, s32* vals)
{
    s32 i;
    for (i = 0; i < count; i++) {
        Elem_139600* e = (Elem_139600*)(base + i * stride);
        if (e->p4 == 0) {
            continue;
        }
        Pair_139600* s1 = (Pair_139600*)((u8*)e + off);
        Pair_139600* s5 = s1;
        s32 n;
        s32 bytes = count2 * 8;
        if (count2 > 0) {
            s32* v = vals;
            n = count2;
            do {
                n--;
                s1->a = func_0012CCC0(e->p4, *v);
                v++;
                s1++;
            } while (n != 0);
        }
        s1 = s5;
        Pair_139600* prev = (Pair_139600*)((u8*)s1 + (bytes - 8));
        if (count2 > 0) {
            n = count2;
            do {
                f32 d = s1->a - prev->a;
                prev->b = d;
                if (d < 0.0f) {
                    prev->b = d + e->p4->f34;
                }
                prev = s1;
                n--;
                s1++;
            } while (n != 0);
        }
    }
}

struct Track_139038 { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; };
struct Grp_139038 {
    s32 key; Track_139038* a; Track_139038* b; s32 fC; Track_139038* c; s32 n; Track_139038** d;
};
struct Src_139038 {
    u8 pad0[0x38]; s32 count; Grp_139038* grps; u8 pad40[4]; s32 f44;
    u8 pad48[0x54 - 0x48]; s32 f54; s32 f58; s32 f5C; s32 f60; s32 f64; s32 f68;
    u8 pad6C[0x78 - 0x6C]; s32 f78; f32 f7C;
};
struct Item_139038 { s32 f0; Src_139038* src; };
struct Key_139038 { s32 f0; s32 f4; void* f8; };
struct Anim_139038;
typedef void (*VFn_139038)(Anim_139038*);
struct Anim_139038 {
    VFn_139038* vtbl; u8 pad4[0x34]; s32 count; Grp_139038* grps; u8 pad40[4]; s32 f44;
    u8 pad48[0x54 - 0x48]; s32 f54; s32 f58; s32 f5C; s32 f60; s32 f64; s32 f68;
    u8 pad6C[0x78 - 0x6C]; s32 f78; f32 f7C;
    u8 pad80[0xB0 - 0x80]; s32 stride; s32 nitems; void* data; s32 nkeys; Key_139038* keys;
};

void func_0018D608(void);
void func_0018D6F0(void);
Anim_139038* func_0011E580(s32 kind, s32 a, Collider* ctx, s32 b, s32 c);
void* func_0018D500(s32 size);
void* func_0018D5C0(s32 size);
Grp_139038* func_0018D6A8(s32 size);
Grp_139038* func_0018D568(s32 size, Grp_139038* src);
Track_139038* func_00120FB0(s32 kind);
Track_139038* func_00121050(s32 kind);
Track_139038* func_00121160(s32 kind);
void func_00138FF0(s32 a, s32 b, s32 c, s32 d);

void func_00139038(Collider* ctx, s32 stride, s32 count, u8* items, s32 nkeys, s32* keyA, s32* keyB, Anim_139038** out)
{
    s32 i;
    Item_139038* item;
    Grp_139038* buf;
    for (i = 0; ; i++) {
        if (i >= count) {
            *out = 0;
            return;
        }
        item = (Item_139038*)(items + i * stride);
        if (item->src != 0) break;
    }
    Src_139038* src = item->src;
    PushBackMemoryMark();
    Anim_139038* anim = CreateTypedRecord(0x84, (s32)ctx->world, ctx, -1, -1);
    anim->vtbl[7](anim);
    anim->nitems = count;
    anim->stride = stride;
    anim->data = AllocateFrontMemory(count * stride);
    anim->nkeys = nkeys;
    anim->keys = (Key_139038*)AllocateFrontMemory(nkeys * 12);
    for (s32 k = 0; k < nkeys; k++) {
        Key_139038* key = &anim->keys[k];
        key->f0 = keyA[k];
        key->f4 = keyB[k];
        key->f8 = AllocateFrontMemory(key->f4 << 3);
    }
    s32 total = 0;
    for (i = 0; i < count; i++) {
        item = (Item_139038*)(items + i * stride);
        if (item->src != 0) total += item->src->count;
    }
    buf = AllocateZeroedBackMemory(total * 0x1C);
    s32 used = 0;
    for (i = 0; i < count; i++) {
        item = (Item_139038*)(items + i * stride);
        if (item->src == 0) continue;
        for (s32 j = 0; j < item->src->count; j++) {
            Grp_139038* g = &item->src->grps[j];
            if (g->a == 0 && g->b == 0 && g->c == 0 && g->d == 0) continue;
            Grp_139038* e;
            for (s32 m = 0; m < used; m++) {
                e = &buf[m];
                if (g->key == e->key) goto have;
            }
            e = &buf[used++];
            e->key = g->key;
        have:
            if (g->a != 0) {
                if (e->a == 0) {
                    Track_139038* t = CreatePositionCurve(2);
                    t->fC = (s32)anim;
                    t->f10 = (s32)anim->keys;
                    t->f14 = (s32)AllocateZeroedFrontMemory(count << 2);
                    t->f8 = 1;
                    e->a = t;
                }
                if (g->a->f8 == 0) e->a->f8 = 0;
                ((Track_139038**)e->a->f14)[i] = g->a;
            }
            if (g->b != 0) {
                if (e->b == 0) {
                    Track_139038* t = CreateRotationCurve(2);
                    t->fC = (s32)anim;
                    t->f10 = (s32)anim->keys;
                    t->f14 = (s32)AllocateZeroedFrontMemory(count << 2);
                    t->f8 = 1;
                    e->b = t;
                }
                if (g->b->f8 == 0) e->b->f8 = 0;
                ((Track_139038**)e->b->f14)[i] = g->b;
            }
            if (g->c != 0) {
                if (e->c == 0) {
                    Track_139038* t = CreateWeightCurve(3);
                    t->f8 = (s32)anim;
                    t->fC = (s32)anim->keys;
                    t->f10 = (s32)AllocateZeroedFrontMemory(count << 2);
                    e->c = t;
                }
                ((Track_139038**)e->c->f10)[i] = g->c;
            }
            if (g->d != 0) {
                if (e->d == 0) {
                    e->n = g->n;
                    e->d = (Track_139038**)AllocateZeroedFrontMemory(g->n << 2);
                }
                for (s32 q = 0; q < g->n; q++) {
                    Track_139038* v = g->d[q];
                    if (v != 0) {
                        Track_139038* t = e->d[q];
                        if (t == 0) {
                            Track_139038* nt = CreateWeightCurve(4);
                            nt->f8 = (s32)anim;
                            nt->fC = (s32)anim->keys;
                            nt->f10 = (s32)AllocateZeroedFrontMemory(count << 2);
                            nt->f14 = q;
                            e->d[q] = nt;
                            t = nt;
                        }
                        ((Track_139038**)t->f10)[i] = v;
                    }
                }
            }
        }
    }
    anim->count = used;
    anim->grps = CopyToFrontMemory(used * 0x1C, buf);
    anim->f44 = src->f44;
    anim->f78 = src->f78;
    anim->f7C = src->f7C;
    anim->f54 = src->f54;
    anim->f58 = src->f58;
    anim->f64 = src->f64;
    anim->f68 = src->f68;
    if (nkeys == 0) {
        anim->f5C = src->f5C;
        anim->f60 = src->f60;
        func_00138FF0(anim->f5C, anim->f60, src->f5C, src->f60);
    }
    *out = anim;
    PopBackMemoryMark();
}

s32 func_00185D20(void*, s32, void*, void*, s32, s32, s32, void*, f32);


struct __attribute__((aligned(16))) Entry_13A008 {
    u64 value;
    s32 tag;
    s32 pad;
};

struct StateB_13A008 {
    u8 pad0[0x4];
    u8 bits4;
};

struct StateA_13A008 {
    u8 pad0[0x14];
    StateB_13A008* p14;
};

struct Ctx_13A008 {
    u8 pad0[0x380];
    StateA_13A008* p380;
    s32 a384;
    u8 pad388[0x8];
    Entry_13A008 entries[1];
};

u64 func_001B2988(void* t, s32 i, s32 j);

void func_0013A008(Ctx_13A008* self)
{
    StateB_13A008* blk = self->p380->p14;
    s32 a = 1;
    s32 s4 = 0;
    s32 t = blk->bits4 >> 1;
    s32 b;
    s32 i;
    Entry_13A008* e;

    while (t != 0) {
        t >>= 1;
        a <<= 1;
    }
    a = a << (a < blk->bits4);
    while (a >= 0x20) {
        a >>= 1;
    }
    b = blk->bits4;
    if (b < a) {
        s4 = a - blk->bits4;
    }
    self->a384 = a;
    e = self->entries;
    for (i = 0; i < b; i++) {
        e->value = GetTextureRegisterBits(blk, i, 0);
        e->tag = 6;
        if (i < s4) {
            e[1] = *e;
            e++;
        }
        e++;
    }
}

struct Obj_138C00;
struct Child_138C00;

struct Vtbl_138C00
{
    u8 pad0[0x10C];
    void (*f10C)(Child_138C00* c);
    void (*f110)(Child_138C00* c);
};

struct Child_138C00
{
    Vtbl_138C00* vt;
    u8 pad[0x2E4 - 4];
    Child_138C00* next;
};

struct Pair_138C00
{
    Contact03* prev;
    Contact03* it;
};

struct Slot_138C00
{
    Contact03* f0;
};

struct Node_138C00
{
    Contact03* f0;
    Node_138C00* f4;
    Slot_138C00* f8;
    Obj_138C00* fC;
};

struct List_138C00
{
    Node_138C00* head;
};

struct Obj_138C00
{
    u8 pad0[0x2C8];
    u64 bits2C8;
    u8 pad1[0x2D8 - 0x2D0];
    Child_138C00* children;
    u8 pad2[0x414 - 0x2DC];
    Obj_138C00* next;
    u8 pad3[0x480 - 0x418];
    List_138C00* list;
    u8 pad4[0x4B8 - 0x484];
    s32 kind;
    u8 pad5[0x538 - 0x4BC];
    u64 bits538;
};

void func_001389D0(World* w);
void func_001861E8(World* w, Contact03* item);
Contact03* func_00188270(World* w, Obj_138C00** pair, s32 arg);
void func_001860A8(World* w, s32 one, Contact03** item);
void func_00129DF8(Obj_138C00* o);

void func_00138C00(World* w, s32 arg)
{
    Obj_138C00* pair[2];
    Obj_138C00* o;
    Child_138C00* ch;
    func_001389D0(w);
    for (o = (Obj_138C00*)w->list6C.head; o; o = o->next)
    {
        pair[0] = o;
        if (o->kind == 7)
        {
            continue;
        }
        if (o->bits538 & (0x8000ull << 27))
        {
            continue;
        }
        o->bits538 |= 0x8000ull << 46;
        Node_138C00* node = pair[0]->list->head;
        for (; node; node = node->f4)
        {
            s32 dead = 7;
            u64 linked = 0x8000ull << 22;
            u64 visited = 0x8000ull << 27;
            u64 marked = 0x8000ull << 46;
            pair[1] = node->fC;
            if (pair[1] < pair[0] && pair[1]->kind != dead && (pair[1]->bits2C8 & linked))
            {
                continue;
            }
            if (pair[1]->bits538 & visited)
            {
                continue;
            }
            pair[1]->bits538 |= marked;
            if (((pair[0]->kind ^ 1) & 1) || ((pair[1]->kind ^ 1) & 1))
            {
                Contact03* old = node->f0;
                if (old)
                {
                    FreePooledContactChain(w, old);
                }
                Contact03* nw = func_00188270(w, pair, arg);
                node->f0 = nw;
                node->f8->f0 = nw;
                if ((old == 0) != (node->f0 == 0))
                {
                    if (!(pair[0]->bits538 & (0x8000ull << 40)))
                    {
                        func_00129DF8(pair[0]);
                    }
                    if (!(pair[1]->bits538 & (0x8000ull << 40)))
                    {
                        func_00129DF8(pair[1]);
                    }
                }
            }
            else
            {
                Pair_138C00 p;
                for (p.it = node->f0; p.it; p.it = p.it->next)
                {
                    func_001860A8(w, 1, &p.it);
                }
            }
        }
    }
    for (o = (Obj_138C00*)w->list6C.head; o; o = o->next)
    {
        if (o->kind & 4)
        {
            continue;
        }
        for (ch = o->children; ch; ch = ch->next)
        {
            if (ch->vt->f110)
            {
                ch->vt->f110(ch);
            }
        }
        o->bits538 |= 0x8000ull << 46;
    }
    for (o = (Obj_138C00*)w->list6C.head; o; o = o->next)
    {
        if (o->bits538 & (0x8000ull << 46))
        {
            for (ch = o->children; ch; ch = ch->next)
            {
                if (ch->vt->f10C)
                {
                    ch->vt->f10C(ch);
                }
            }
            o->bits538 &= ~(0x8000ull << 46);
        }
        o->kind = 7;
    }
}

#include "list_iter.h"

struct Node_1399F8 { u8 pad0[0x14]; f32 f14; u8 pad18[0x3C - 0x18]; Node_1399F8* f3C; };
struct Ent_1399F8 { s32 a; s32 b; s32 c; };

void func_0018D800(void* a, void* b, s32 n);
void func_00139740(s32 a0, s32 a1, void* a2, s32 a3, s32 a4, s32 a5, void* a6);
void func_0012F1D8(void* node);

void func_001399F8(Gr8B* self, s32 a1, s32 a2, void* a3)
{
    Node_1399F8* node = (Node_1399F8*)self->f6C;
    s32 i;
    s32 count;
    Ent_1399F8* ent;
    ListFrame frame;

    if (node != 0) {
        do {
            node->f14 = node->f14 / self->f34;
            node = node->f3C;
        } while (node != 0);
    }
    CopyMemory(self->fB8, a3, a2 * a1);
    count = self->fBC;
    if (count == 0) {
        func_00139740(a1, a2, a3, 0, 0, 0, &self->f34);
    } else {
        for (i = 0; i < count; i++) {
            ent = (Ent_1399F8*)((u8*)self->pC0 + i * 12);
            func_00139740(a1, a2, a3, ent->a, ent->b, ent->c, &self->f34);
        }
    }
    node = (Node_1399F8*)self->f6C;
    if (node != 0) {
        do {
            node->f14 = node->f14 * self->f34;
            SettleListedPoseSources(node);
            node = node->f3C;
        } while (node != 0);
    }
}

void func_00138FF0(s32 a, s32 b, s32 c, s32 d)
{
    s32 i;
    for (i = 0; i < (a < c ? a : c); i++) {
    }
}
