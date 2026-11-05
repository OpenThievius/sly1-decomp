// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c05.h"
#include "c2c.h"
#include "object_gatherer.h"
#include "c6e.h"
#include "c5c.h"
#include "c5d.h"
#include "c1e.h"
#include "c50.h"
#include "c8b.h"
#include "c6c.h"
#include "t219c.h"
#include "list_iter.h"
#include "globals.h"
#include "g27c220.h"
#include "object_message.h"
#include "object_event.h"

void func_001B7968(void* self);

void func_00198980(C2C* self)
{
    func_001B7968(self);
    self->f554 = 1;
}

void func_001249A8(void* self);
void* func_0015A448(void* a, void* b, void* c);

void func_00198A88(C2C* self)
{
    s32 i;

    func_001249A8(self);
    for (i = 0; i < self->n55C; i++) {
        void* r = func_0015A448(self->world, self->keys560[i], self);
        if (r != 0) {
            self->found574[self->count570++] = r;
        }
    }
}

typedef s32 (*VFn_198B28)(void* self);
void func_00124A48(void* self);
s32 func_0012C9A8(void* node);
void func_00182ED8(void* node);

void func_00198B28(C2C* self)
{
    s32 i;

    func_00124A48(self);
    for (i = 0; i < self->count570; i++) {
        void* node = self->found574[i];
        if (func_0012C9A8(node)) {
            self->f558 = 1;
        }
        func_00182ED8(node);
    }
    if (((VFn_198B28*)self->desc)[76](self) == 0) {
        ((VFn_198B28*)self->desc)[7](self);
    }
}

typedef void (*VFn_198DA8)(void* self);

void func_0012C8F8(void* item, s32 a, f32 x, s32 b, f32 y, s32 c);
void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_00198DA8(C2C* self)
{
    VFn_198DA8 fn = ((VFn_198DA8*)self->desc)[7];
    fn(self);
    s32 i = self->count570;
    i--;
    for (; i >= 0; i--) {
        (void)func_0012C8F8(self->found574[i], 0, 0.0f, 1, 1.0f, 0);
    }
    ((VFn_198DA8*)self->desc)[78](self);
    (void)func_001837E0(self, 2, 0, 0);
}

typedef void (*VFn_198E58)(void* self, void* msg);

struct Msg_198E58 {
    s32 kind;
    void* owner;
    u8 pad_08[0x50 - 8];
};

struct Target_198E58 {
    VFn_198E58* vtbl;
};

void func_00198E58(C2C* self)
{
    Target_198E58* t = (Target_198E58*)self->f584;
    if (t != 0) {
        Msg_198E58 msg;
        msg.kind = 1;
        msg.owner = self;
        t->vtbl[31](t, &msg);
    }
}

s32 func_00182FC8(void* self);

s32 func_00198E98(C2C* self)
{
    if (func_00182FC8(self)) {
        return (self->f554 != 0) ? 1 : 2;
    }
    return 0;
}

void func_001BA130(void*);
void func_00198980(C2C*);
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
void func_00144848(void*);
void func_0015EAE0(void*, void*, void*);
void func_0019D860(void);
void func_0019D968(void);
void func_0019D930(void);
void func_0019EBE8(T219C*);
void func_001831E8(void*, void*, s32, void*);
void func_001831E8(void*, void*, void*, void*);
void func_00183238(void*, void*, void*, void*);
void func_0019F9D0(T219C*, s32);

void func_00198ED8(C2C* queue, void* item)
{
    queue->keys560[queue->n55C++] = item;
}

typedef void (*VFn_198EF8)(void* self, void* other);

struct Ctx_198EF8 {
    VFn_198EF8* vtbl;
    u8 pad_04[0x2230 - 4];
    ObjectMessage* watched_2230;
};


void func_00127378(C2C* self, s32 msg, ObjectMessage* m);

void func_00198EF8(C2C* self, s32 msg, ObjectMessage* m)
{
    (void)func_00127378(self, msg, m);
    if (msg == 5) {
        for (s32 i = 0; i < self->count570; i++) {
            if (m->key == (s32)self->found574[i]) {
                self->marks588[i] = 1;
            }
        }
        Ctx_198EF8* g = (Ctx_198EF8*)D_00262E10;
        if (g != 0) {
            if (m == g->watched_2230) {
                g->vtbl[28](g, self);
                self->done598 = 1;
            }
        }
    }
}

s32 func_001300E8(void* obj, s32 kind);

s32 func_00198FB0(C2C* unused, void* obj)
{
    if (func_001300E8(obj, 8) != 0 || func_001300E8(obj, 0x3B) != 0) {
        return 1;
    }
    return 0;
}

void* func_001929F8();
s32 func_00182F40(void* e, void* b);

struct Rec_199000 {
    u8 pad0[0x18];
    void* f18;
};

struct Elem_199000 {
    u8 pad0[0x4];
    void* f4;
    u8 pad1[0x40 - 0x8];
};

void func_00199000(C2C* self, Elem_199000* elems, s32 idx)
{
    Rec_199000* r = (Rec_199000*)func_001929F8();
    if (r->f18 == 0) return;
    {
        s32 one = 1;
        Elem_199000* e = (Elem_199000*)((u8*)elems + ((one - idx) << 6));
        if (func_00182F40(e->f4, r->f18) != 0) {
            self->f59C = one;
        }
    }
}

void func_001990A8(C2D* obj)
{
    s32 value = obj->f5A0;
    func_001BA130(obj);
    obj->f5A0 = value;
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

void func_001993F0(C2E* obj)
{
    func_00198980(obj);
    obj->f5A0 = obj->world->count2300++;
}

void func_001994C8(C2E* obj)
{
    s32 value = obj->f5A0;
    func_001BA130(obj);
    obj->f5A0 = value;
}


void func_00199C10(C2E* self, s32* out)
{
    s32 n = self->f5A0;
    s32 byte = n / 8;
    s32 bit = n & 7;
    u8 b = D_002623C8->bits68[byte];
    s32 mask = 1;
    mask <<= bit;
    *out = (b & mask) != 0;
}

void func_00199C58(void)
{
    func_001B7F78();
}

void func_00199FF0(u32 value)
{
    D_002623C0->u19F0 = value;
}

struct Rec_19A088 { s32 flags; u8 rest[0x74]; };

void func_0019A088(s32 index)
{
    if (index == -1) index = D_002623C0->f19D8;
    u8* base = (u8*)D_002623C0 + (index * 0x44C + 0x10);
    Rec_19A088* p = (Rec_19A088*)base;
    Rec_19A088* end = (Rec_19A088*)(base + 0x438);
    do {
        p->flags |= 1;
        p++;
    } while ((s32)p < (s32)end);
    *(s32*)(base + 0x448) |= 0x1F;
}

struct Obj_19A0F0 { u8 pad0[0x30]; s32 f30; };
extern Obj_19A0F0 D_00275BC0;
void func_0019A088(s32 index);
void func_001E5278(s32 mode);

void func_0019A0F0()
{
    for (s32 i = 0; i < 6; i++) func_0019A088(i);
    if (D_00275BC0.f30 == 2) func_001E5278(0);
}

void func_001921A8(C17* self);

void func_0019A148(C17* self)
{
    func_001921A8(self);
    self->f64C = -1;
    self->f644 = -1;
}

struct Obj_19A178 { s32 f0; s32 f4; s32 f8; };
s32 func_0015A418(s32 a, s32 b, s32 c, s32 d);
void func_00182ED8(s32 a);
s32 func_001B6290(s32 a, s32 b, s32 c, s32 d);

void func_0019A178(Obj_19A178* self, s32 x)
{
    self->f4 = func_0015A418((s32)D_00275710, 0x101, 0x37A, self->f0);
    func_00182ED8(self->f4);
    self->f8 = func_001B6290(self->f4, self->f0, x, 0);
}

void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);
void func_0016EC88(void* p);
s32 func_001602A0(void);
void func_00160578(s32 value);
void* func_0015A448(void* a, s32 code, void* c);

extern u8 D_00262C70[];

void func_0019A520(C17* self, s32 flag)
{
    s32 r;
    s32 flags;
    void* a;
    s32 n;

    func_001B6568(self->f614, &r);
    if (r == -1) {
        func_001B6598(self->f614, &r);
    }
    if (flag != 0) {
        if (r != 0x38F) {
            func_001B64D8(self->f614, 0x385);
        }
        func_0016EC88(D_00262C70);
        flags = D_002623C0->f19EC;
        if ((flags & 8) == 0) {
            a = func_0015A448((void*)D_00275710, 0x39A, self);
        } else {
            if ((flags & 0x10) != 0) {
                goto tail;
            }
            a = func_0015A448((void*)D_00275710, 0x39B, self);
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
        if (D_00262E10 != 0) {
            self->blk580 = D_00262E10->blk580;
            self->f604 = D_00262E10->f604;
        }
    } else {
        if (r != 0x38F) {
            func_001B64D8(self->f614, 0x384);
        }
        self->f7D8 = 0;
        if ((func_001602A0() & 4) != 0) {
            func_00160578(4);
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

void func_0019AF38(C71* obj)
{
    func_00182D48(obj);
    func_00152470(&obj->world->list1C90, obj);
}

void func_0019AF70(C71* obj)
{
    func_00182ED0(obj);
    func_00152600(&obj->world->list1C90, obj);
}

void func_0019AFA8(C71* obj)
{
    func_00182C58(obj);
    if (obj->id54 != -1)
        obj->found58 = (s32)func_0015A418(obj->world, 4, obj->id54, obj);
}

void func_001830D8(void* self);

void func_0019AFF0(C71* self)
{
    Keep6E tmp;

    tmp = self->keep;
    func_001830D8(self);
    self->keep = tmp;
}

void func_0019B1E0(ObjectGatherer* obj)
{
    func_001B7A98(obj);
    func_00152470(&obj->world->list1C60, obj);
}

void func_0019B218(ObjectGatherer* obj)
{
    func_001B7B78(obj);
    func_00152600(&obj->world->list1C60, obj);
}

struct Obj_0019C3D0 { u8 pad[0x14]; u8* owner; };

void func_0019C3D0(Obj_0019C3D0* obj)
{
    func_00182D48(obj);
    func_00152470(obj->owner + 0x1C6C, obj);
}

struct Obj_0019C408 { u8 pad[0x14]; u8* owner; };

void func_0019C408(Obj_0019C408* obj)
{
    func_00182ED0(obj);
    func_00152600(obj->owner + 0x1C6C, obj);
}

void func_0019C440(C8B* obj)
{
    func_00182C18(obj);
    obj->second38 = -1;
    obj->first34 = -1;
}

void func_0019CE28(C8B* value, f32 x, f32 y, f32 z)
{
    value->f54 = x;
    value->f58 = y;
    value->f5C = z;
}

struct Val_0019D468 { u8 pad[4]; f32 value; };
int func_0019D468(Val_0019D468** a, Val_0019D468** b)
{
    Val_0019D468* left = *a;
    Val_0019D468* right = *b;
    if (right->value < left->value) return -1;
    if (left->value < right->value) return 1;
    return ((s32)left - (s32)right) >> 7;
}

extern u32 D_00604788;

void func_0019D930(void)
{
    if (!D_00604788) {
        D_00604788 = 1;
        func_00144848((void*)D_00261990);
    }
}

extern u8 D_00212160[];
extern u8 D_00215C50[];

void func_0019DA30(void)
{
    func_0015EAE0(&D_002622A8, D_00212160, D_00215C50);
}

extern u8 D_00212160[];
extern u8 D_00215C50[];
extern u32 D_00604788;

void func_0019DAD8(void)
{
    func_0019D860();
    func_0019D968();
    func_0015EAE0(&D_002622A8, D_00212160, D_00215C50);
    D_00604788 = 0;
}

extern u8 D_00212160[];
extern u8 D_00215C50[];

void func_0019DB20(void)
{
    func_0019D860();
    func_0019D930();
    func_0019D968();
    func_0015EAE0(&D_002622A8, D_00212160, D_00215C50);
}

extern u8 D_00215C60[];
extern u8 D_00217348[];

void func_0019DB68(void)
{
    func_0019D860();
    func_0019D930();
    func_0019D968();
    func_0015EAE0(&D_002622A8, D_00215C60, D_00217348);
}

void func_0019E158(C1E* a, Rec50* b)
{
    a->f554 = b->f1E8;
}

void func_0019E418(void) {}

void func_0019EC20(T219C* counter)
{
    counter->uses++;
}

void func_0019ECE0(T219C* value, s32 enabled)
{
    if (enabled) func_0019EBE8(value);
}

struct Obj_0019F8E8 { u8 pad[0x44]; s32 value; };

void func_0019F8E8(void* obj, void* arg)
{
    Obj_0019F8E8* value = *(Obj_0019F8E8**)arg;
    func_001831E8((void*)D_00275710, (u8*)obj + 0x118, value->value, arg);
}

void func_0019F918(void* obj, void* a1, void* a2)
{
    func_001831E8((void*)D_00275710, (u8*)obj + 0x118, a1, a2);
}

void func_0019F950(void* obj, void* a1, void* a2)
{
    func_00183238((void*)D_00275710, (u8*)obj + 0x118, a1, a2);
}

void func_0019FCE8(T219C* value, u32 enabled)
{
    func_0019F9D0(value, enabled < 1);
}

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void* func_0015A838(void* a, s32 b, s32 c, void* d);

extern u8 D_00261420[];

void func_00198980(C2C* self);
void* func_00140FF8(void* p);

void func_00199070(C2D* self)
{
    func_00198980(self);
    self->f5A0 = (s32)func_00140FF8(D_00261420);
}

void func_001989B0(C2C* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void* func_0018D500(s32 size);
void func_00182ED8(s32 a);
extern s32 D_0026A948[4];

void func_00199428(C2E* self)
{
    func_001989B0(self);
    s32 i = 0x318;
    func_00124DF8(self, 1, (u8*)D_0026A948);
    self->f5B0 = func_0018D500(0x80);
    while (i < 0x338) {
        s32 r = (s32)func_0015A418(self->world, 1, i, self);
        if (r == 0) {
            break;
        }
        s32 count = self->n5AC;
        i++;
        ((s32*)self->f5B0)[count] = r;
        self->n5AC = count + 1;
        func_00182ED8(r);
    }
}

struct Vec4_19BE08 { s32 a, b, c, d; } __attribute__((aligned(16)));
struct Src_19BE08 { u8 pad[0x20]; Vec4_19BE08 q20; Vec4_19BE08 q30; };
struct Local_19BE08 { s32 mode; u8 pad[0xC]; Vec4_19BE08 qa; Vec4_19BE08 qb; u8 pad2[0x20]; };
typedef void (*VFn_19BE08)(void* self, void* arg);
struct Obj_19BE08 { VFn_19BE08* vtbl; };

void func_0019C1C0(void* self, s32 mode);

s32 func_0019BE08(ObjectGatherer* self, Src_19BE08* src)
{
    Local_19BE08 loc;
    if (self->state != 3) {
        func_0019C1C0(self, 3);
        Obj_19BE08* obj = (Obj_19BE08*)self->group;
        if (obj != 0) {
            loc.mode = 6;
            loc.qb = src->q20;
            loc.qa = src->q30;
            obj->vtbl[31](obj, &loc);
        }
    }
    return 1;
}

extern u8 D_00261420[];
s32 func_00198E98(C2C* self);
s32 func_00141008(void* table, s32 index);

s32 func_001990E0(C2D* self)
{
    s32 r = func_00198E98(self);
    if (r == 1) {
        r = func_00141008(D_00261420, self->f5A0) ? 0 : r;
    }
    return r;
}

extern u8 D_00261420[];
void func_00141040(void* table, s32 index);
void func_00198DA8(C2C* self);

void func_00199138(C2D* self)
{
    func_00141040(D_00261420, self->f5A0);
    func_00198DA8(self);
}

typedef void (*VFn_199AF0)(void* self);

void func_00199AF0(C2E* p)
{
    ((VFn_199AF0*)p->desc)[77](p);
}

void func_001C72A0(void* self);

struct __attribute__((aligned(16))) Quad_1984B8 { s32 a, b, c, d; };
typedef void (*VFn_1984B8)(void* self, void* ctx);

void* func_001925F0(void);
void func_00197A08(void* h, void* self);
void func_001C9008(void* self, void* arg);

void func_001C91C8(void* self);
void func_001C8920(void* self);

void func_001C9DE0(void* self, s32 code, void* req);

typedef void (*VFnA_199C78)(void* self, s32 a);
typedef void (*VFnB_199C78)(void* self);

void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
s32 func_001BC320(void* self, ObjectEvent* ev);

s32 func_00199C78(C2E* self, ObjectEvent* a1)
{
    if (a1->eventFlags & 0x8) {
        ((VFnA_199C78)((void**)self->desc)[25])(self, 0);
        func_001B9AE0(self, 0, 0, 3, 0);
    }
    func_001BC320(self, a1);
    if (a1->eventFlags & 0x10) {
        ((VFnB_199C78)((void**)self->desc)[77])(self);
    }
    return 1;
}

void func_001BA130(void* self);

void func_0019B250(ObjectGatherer* self)
{
    PackedS64 tmp;
    tmp = self->q600;
    func_001BA130(self);
    self->q600 = tmp;
}

extern s32 D_0026A918[4];

void func_001289C0(void* self);
void func_00124DF8(void* self, s32 n, void* table);

void func_00199170(C5C* self)
{
    func_001289C0(self);
    func_00124DF8(self, 1, (u8*)D_0026A918);
}

extern s32 D_0026A928[4];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);

void func_001991A8(C5C* self)
{
    func_00124A48(self);
    func_00124DF8(self, 1, (u8*)D_0026A928);
}

extern s32 D_0026A938[4];

void func_001289C0(void* self);
void func_00124DF8(void* self, s32 n, void* table);

void func_001991E0(C5D* self)
{
    func_001289C0(self);
    func_00124DF8(self, 1, (u8*)D_0026A938);
}

typedef void (*VFn_199F38)(void* self);

struct Obj_199F38 {
    VFn_199F38* vtbl;
};

struct Holder_199F38 {
    u8 pad0[0x18];
    Obj_199F38* sub;
};

extern u8 D_0026C948[];

s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void func_00199B18(void* obj);
s32 func_001300E8(void* node, s32 kind);

void func_00199F38(void)
{
    void* arr[0x100];
    s32 i = func_0015A4F0((void*)D_00275710, 0x105, 0x2E, 0, 0x100, arr) - 1;
    if (i >= 0) {
        void** p = (void**)(i * 4 + (s32)arr);
        do {
            func_00199B18(*p);
            if (((Holder_199F38*)*p)->sub != 0) {
                if (func_001300E8(((Holder_199F38*)*p)->sub, 0x20) != 0) {
                    Obj_199F38* s = ((Holder_199F38*)*p)->sub;
                    s->vtbl[7](s);
                }
            }
            i--;
            p--;
        } while (i >= 0);
    }
    VFn_199F38* vt = *(VFn_199F38**)D_0026C948;
    vt[14](D_0026C948);
}

s32 func_001602A0(void);

s32 func_0019A000(s32 bits)
{
    s64 mask = 0xF000;
    mask <<= 16;
    mask |= 0xFFFF;
    if ((D_002623C0->f19F0 & mask) == mask) {
        return 0;
    }
    if (func_001602A0() & 2) {
        return 0;
    }
    G27C220* c = D_002623C0;
    s64 v = c->f19F0 | bits;
    s32 r = 1;
    if ((v & mask) ^ mask) {
        r = 0;
    }
    return r;
}

extern f32 D_0026185C[];
void func_001B7968(void* self);
f32 func_001EAB48(f32 a, f32 b, f32 c);

void func_0019B038(ObjectGatherer* self)
{
    func_001B7968(self);
    self->f60C = 1.0f;
    self->f608 = 0.5f;
    self->f55C = func_001EAB48(*(f32*)D_0026185C + 3.0f, 1.0f, 2.5f);
    self->f664 = -1;
}

extern s32 D_0026AB90[4];

void func_001BAC30(void* self);
void func_00159478(void* sub, void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void* func_0015A480(void* self, s32 kind, void* arg);
void func_00182ED8(void* node);

void func_0019B0A0(ObjectGatherer* self)
{
    s32 k = 0x269;
    func_001BAC30(self);
    func_00159478(&self->group, self);
    func_00124DF8(self, 1, (u8*)D_0026AB90);
    for (; k < 0x288; k++) {
        void* node = func_0015A480(self->world, k, self);
        if (node != 0) {
            func_00182ED8(node);
            if (k < 0x279) {
                self->lowObjects[self->lowCount++] = node;
            } else {
                self->highObjects[self->highCount++] = node;
            }
        }
    }
}

extern s32 D_0026ABA0[4];

void func_0019C1C0(void* self, s32 mode);
void func_00124DF8(void* self, s32 n, void* table);
void func_00124A48(void* self);

void func_0019B188(ObjectGatherer* self)
{
    func_00124DF8(self, 1, (u8*)D_0026ABA0);
    func_00124A48(self);
    self->state = -1;
    func_0019C1C0(self, 1);
    self->v650 = self->v140;
}

extern s32 D_00270454;
extern u8 D_00264A40[];

void func_001B64D8(void* a, s32 b);
void func_001E9570(void* q);
s32 func_001602A0(void);
void func_001604B8(s32 mode);
void func_0018C7F8(void* p);
void* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

void func_0019AD68(C17* self)
{
    s32 sel;
    s32 idx;
    s32 n;
    s32 v;
    void* item;
    C01* r;

    func_001B64D8(self->f614, 0x38E);
    if (self->f650 == 0) {
        self->f7D8 = 0;
    } else {
        ((C01*)self->f650)->desc->m18((C01*)self->f650, self);
        self->f650 = 0;
        self->f7D8 = 0;
    }

    if (D_00270454 != 0) {
        func_001E9570((void*)&D_00275BC0);
    }
    if ((self->f760 & (s64)0xF000FFFF) != 0) {
        G27C230* ctx = D_002623C4;
        G27C220* g = D_002623C0;
        G27C230* ctl = D_002623C8;

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

        if (func_001602A0() & 4) {
            func_001604B8(4);
        }

        sel = 0x37E;
        if (self->f760 != 1) {
            sel = 0x37F;
            func_0018C7F8(D_00264A40);
        }

        r = (C01*)func_0015A418(self->world, 0x101, sel, self);
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

typedef void (*VFn_199500)(void* self);
extern s32 D_00275C34;
f32 D_0026A958[2] = { 0.8f, 1.2f };
f32 D_0026A960[2] = { 0.9f, 1.1f };

void func_00198B28(C2C* self);
f32 func_001EAAE0(f32 a, f32 b);
s32 func_001EAA70(s32 a, s32 b);

void func_00199500(C2E* self)
{
    s32 neg;
    s32 one;
    f32 r;

    func_00198B28(self);
    self->f5B8 = func_001EAAE0(-3.14159274f, 3.14159274f);
    self->f5B4 = func_001EAAE0(D_0026A958[0], D_0026A958[1]);
    if (func_001EAA70(0, 1) != 0) {
        self->f5B4 = -self->f5B4;
    }
    neg = -1;
    one = 1;
    r = func_001EAAE0(D_0026A960[0], D_0026A960[1]);
    self->f5A8 = self->f5A8 * r;
    self->f5A4 = func_001EAAE0(0.0f, self->f5A8 + self->f5A8);

    {
        s32 bit = self->f5A0;
        s32 mask = one << (bit & 7);
        if (D_002623C8->bits68[bit / 8] & mask) {
            ((VFn_199500*)self->desc)[7](self);
        }
    }

    if (D_00275C34 != 0) {
        if (func_001EAA70(0, 100) < 20) {
            G27C230* d = D_002623C8;
            s32 bit = self->f5A0;
            s32 mask = one << (bit & 7);
            if (d->bits68[bit / 8] & mask) {
                d->bits68[bit / 8] = d->bits68[bit / 8] & ~mask;
                d->count64--;
            }
            ((VFn_199500*)self->desc)[7](self);
        }
    }
}

extern u8 D_0026C948[];
extern u8 D_0026A970[];

typedef void (*VFn_1999D0)(void* self);

struct Obj_1999D0 { VFn_1999D0* vtbl; };
struct __attribute__((aligned(16))) Quad_1999D0 { s32 a, b, c, d; };

void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00128018(void* a0, s32 a1, void* a2, void* a3);
T219C* func_0019EA78(s32 kind, C1E* sys);
void func_00199850(C2E* self);
void func_00198DA8(C2C* self);

void func_001999D0(C2E* self)
{
    Quad_1999D0 loc;
    Obj_1999D0* g = (Obj_1999D0*)D_0026C948;
    g->vtbl[14](g);
    T219C* n = func_0019EA78(0x10, 0);
    if (n != 0) {
        if (D_002623C8->count64 + 1 >= D_00275710->count2300) {
            f32 z = 0.0f;
            func_001BFCD8(0x21, 0, 0, 0, 3000.0f, 300.0f, 1.0f, z, z, 0, 0);
        }
        n->p134 = self;
        n->params = (const T219C_Params*)D_0026A970;
        func_00128018(self, 0, self->f5BC + 0x100, &loc);
        n->vt->m00(n, &loc, 1.0f, 0);
        n->i20 = *(s32*)&self->f5BC;
    } else {
        func_00199850(self);
    }
    func_00198DA8(self);
}


void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001518B8(s32 x);

void func_00199850(C2E* self)
{
    f32 zf;
    G27C230* ctx = D_002623C8;
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
    s32 count = D_002623C8->count64;
    s32 s0 = -1;
    s32 s1 = 0;
    if (((D_002623C0->f19EC ^ 1) & 1) != 0) {
        if (count > 0) {
            s0 = 0x348;
            s1 = 1;
        }
    } else if ((D_002623C0->f19EC & 4) == 0) {
        if (count < D_00275710->count2300) {
            goto L980;
        }
        s0 = 0x34A;
        s1 = 4;
    }
    if (count < D_00275710->count2300) {
        goto L980;
    }
    func_001BFCD8(0x6A, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
L980:
    D_002623C0->f19EC = D_002623C0->f19EC | s1;
    s32 r = (s32)func_0015A418((void*)D_00275710, 1, s0, 0);
    if (r != 0) {
        func_001518B8(r);
    }
}

struct VObj_19A1E0 { s32 (**vtbl)(VObj_19A1E0*, C17*); };
struct Pad_19A1E0 { u32 flags; u8 pad[0x74]; };

extern u8 D_0026AA50[];
s32 D_0026A9E0[28] = { 2, 4, 8, 16, 65536, 32, 64, 128, 256, 512, 131072, 1024, 2048, 8192, 4096, 16384, 32768, 0, 0, 0, 0, 0, 0, 268435456, 536870912, 1073741824, (-2147483647 - 1), 1 };

void func_00124A48(C17* o);
void func_00124DF8(C17* o, s32 n, u8* t);
void func_0019A178(void* p, s32 x);
s32 func_001B6290(s32 a, C17* b, s32 c, s32 d);
void func_001B64D8(s32 a, s32 b);
VObj_19A1E0* func_0015A448(C6C* a, s32 b, C17* c);
s32 func_001EAA70(s32 a, s32 b);
void func_00160D30(s32* p);

void func_0019A1E0(C17* o)
{
    u32 i;
    func_00124A48(o);
    func_00124DF8(o, 0x1A, D_0026AA50);
    for (i = 0; i < 3; i++)
        func_0019A178(o->f61C + i * 12, 0x390);
    s32 h = func_001B6290(o->f610, o, 0x384, 1);
    o->f764 = -1;
    o->f614 = (S1B6290*)h;

    if (D_002623C8->bits & 4) {
        func_001B64D8(h, 0x38F);
        return;
    }
    o->world->f1CE4 = o;
    for (s32 e = 0; e < 6; e++) {
        Ent17* en = &o->f658[e];
        for (s32 k = 0; k < en->count; k++) {
            VObj_19A1E0* r = func_0015A448(o->world, en->keys[k], o);
            if (r) {
                en->list[en->n++] = r;
            }
        }
        if (en->n > 0)
            en->pick = func_001EAA70(0, en->n - 1);
    }
    o->f648 = (void*)func_0015A448(o->world, o->f644, o);
    o->f650 = func_0015A448(o->world, o->f64C, o);
    if (((VObj_19A1E0*)o->f650))
        ((VObj_19A1E0*)o->f650)->vtbl[0x6C / 4](((VObj_19A1E0*)o->f650), o);
    if (((D_002623C0->f19D8 << 8) | D_002623C0->f19DC) == 3) {
        o->f760 = 1;
    } else {
        func_00160D30(&o->f760);
        if (o->f760 & 0xF000FFFFl) {
            s32 cnt = 0;
            Pad_19A1E0* p = (Pad_19A1E0*)D_002623C4;
            Pad_19A1E0* end = p + 9;
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
        if (D_002623C0->u19F0 & 2) {
            do {
                o->f760 = o->f760 << 1;
            } while ((o->f760 & 0xF000FFFFl) && (D_002623C0->u19F0 & o->f760));
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

s32 func_001C96B8(void* self);
s32 func_001C8010(void* self);

struct Elem_199218 {
    u8 pad0[0x2D0];
    void* f2D0;
    void* f2D4;
};

void func_00124A48(void* self);
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_001B64D8(void* p, s32 n);

void func_00199218(C5D* self)
{
    func_00124A48(self);
    self->count300 = func_0015A4F0(self->world, 1, 0x5C, self, 8, self->objs304);
    s32 i;
    Elem_199218* e;
    for (i = 0; i < self->count2DC; i++) {
        e = (Elem_199218*)func_0015A418(self->world, 4, self->ids2E0[i], self);
        if (e != 0) {
            u32 k = self->count300;
            if (k < 8) {
                self->objs304[k] = (void*)e;
                self->count300 = k + 1;
            }
        }
    }
    s32 s4 = (D_002623C4->f448 & self->mask2D0) ? 0x22F : 0x22E;
    for (i = 0; i < self->count300; i++) {
        e = (Elem_199218*)self->objs304[i];
        e->f2D4 = func_001B6290(e->f2D0, e, -1, 0);
        func_001B64D8(e->f2D4, s4);
    }
    self->f2D8 = func_001B6290(self->f2D4, self, -1, 0);
    func_001B64D8(self->f2D8, s4);
}

// NEAR: global kept in $a1 not $t0 and the mask shift scheduled early; call and loop sequence match

typedef void (*VFn_199B18)(void* self);

struct Actor_199B18 {
    VFn_199B18* vtbl;
    u8 pad0[0x570 - 4];
    s32 n570;
    void* arr574[1];
    u8 pad1[0x5A0 - 0x578];
    s32 n5A0;
};

void* func_0012C8F8(void* self, s32 key, s32 a2, s32 a3, f32 fa, f32 fb);
void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_00199B18(Actor_199B18* self)
{
    self->vtbl[7](self);
    s32 n = self->n5A0;
    G27C230* m = D_002623C8;
    s32 idx = n / 8;
    u8 cur = m->bits68[idx];
    s32 mask = 1 << (n & 7);
    if (!(cur & mask)) {
        m->bits68[idx] = cur | mask;
        m->count64 = m->count64 + 1;
    }
    s32 i = self->n570;
    i--;
    while (i >= 0) {
        func_0012C8F8(self->arr574[i], 0, 1, 0, 0.0f, 1.0f);
        i--;
    }
    func_001837E0(self, 2, 0, 0);
}

struct Arg_001993C0;
s32 func_001781E0(Arg_001993C0* a, s32 v);

void func_001993C0(s32 a0) {
    if (D_00262E10 != 0) {
        (void)func_001781E0((Arg_001993C0*)D_00262E10, a0);
    }
}

extern f32 D_0024C8C4;

void func_0019AF00(C71* self)
{
    func_00182C18(self);
    self->id54 = -1;
    self->f4C = D_0024C8C4;
}

struct List_1989B0 { s32 head; s32 x; s32 link; };
struct Frame_1989B0 {
    s32 list; s32 cursor; s32 link; s32 prev;
    Frame_1989B0(List_1989B0* l) {
        cursor = (s32)l;
        list = (s32)l;
        link = l->link;
        prev = *(s32*)&D_0027B314;
        *(s32*)&D_0027B314 = (s32)this;
    }
};
void func_001BAC30(void* self);
void func_00159478(void* sub, void* self);
void func_00182ED8(C01* n);

void func_001989B0(C2C* self)
{
    func_001BAC30(self);
    func_00159478(&self->f584, self);
    Frame_1989B0 fr((List_1989B0*)&self->children);
    fr.cursor = (s32)self->children.head + fr.link;
    C01* p = (C01*)self->children.head;
    while (p != 0) {
        if (p->desc->flags & 0x40) {
            s32 i = self->count570;
            self->found574[i] = p;
            self->count570 = i + 1;
            func_00182ED8(p);
        }
        s32 nx = *(s32*)fr.cursor;
        fr.cursor = nx + fr.link;
        p = (C01*)nx;
    }
    *(s32*)&D_0027B314 = fr.prev;
}

s32 func_001300E8(void* key, s32 kind);
s32 func_00182FC8(void* p);
s32 func_00141170(void* self, void* value);

struct Slot_19AB78 { u8 pad[0x304]; s32* f304; };

struct Slot_19AB78;
struct Ent_19AB78 { u8 pad[0x14]; s32 f14; Slot_19AB78* f18[4]; s32 f28; };
struct Obj_19AB78 { void** vt; };
typedef void (*VFn_19AB78)(Obj_19AB78*);
struct Vi_19AB78 { u8 pad[0x239C]; s32 f239C; u8 p2[0x2C]; void* f23CC; };

void func_00192230(void* self, s32 code, s32* rec);
void func_00175170(void* self, s32 a, s32 b);
s32 func_0019A000(s32 bits);
void func_001518B8(Slot_19AB78* s);

void func_0019AB78(C17* self, s32 msg, s32* rec)
{
    func_00192230(self, msg, rec);
    if (msg == 12 && rec[1] == (s32)self->f650) {
        if (self->f654 != 0 && D_00262E10 != 0) {
            ((Vi_19AB78*)D_00262E10)->f23CC = self;
            ((Vi_19AB78*)D_00262E10)->f239C = 7;
            func_00175170((Vi_19AB78*)D_00262E10, 6, 16);
        } else {
            s32 k;
            s32 a;
            s32 b;
            ((VFn_19AB78)(*(Obj_19AB78*)&D_0026C948).vt[0x38 / 4])(((Obj_19AB78*)&D_0026C948));
            a = D_002623C8->count64;
            b = D_00275710->count2300;
            k = -1;
            if (a == b) {
                k = func_0019A000(*(s32*)((u8*)self + 0x760)) ? 5 : 4;
            } else if ((D_002623C0->u19F0 & 0xF0000000) == 0) {
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
                Ent_19AB78* e = (Ent_19AB78*)((u8*)self + (k * 0x2C + 0x658));
                e->f18[e->f28]->f304[0] = 0;
                func_001518B8(e->f18[e->f28]);
                e->f28 = (e->f28 + 1) % e->f14;
            }
        }
    }
}

s32 D_0026A918[4] = { 0x0, 0x22B, 0x2D0, 0x0 };
s32 D_0026A928[4] = { 0x0, 0x22D, 0x2D8, 0x0 };
s32 D_0026A938[4] = { 0x0, 0x22C, 0x2D4, 0x0 };
s32 D_0026A948[4] = { 0x0, 0x339, 0x5BC, 0x0 };
s32 D_0026AB90[4] = { 0x0, 0x268, 0x5EC, 0x0 };
s32 D_0026ABA0[4] = { 0x4, 0x267, 0x5FC, 0x0 };
