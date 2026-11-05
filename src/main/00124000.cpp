// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "c02.h"
#include "t2195.h"
#include "s1291d0.h"
#include "s1be4d8.h"
#include "s124df8.h"
#include "s12c288.h"
#include "c83.h"
#include "globals.h"

#include "c6c.h"
#include "object_cycler.h"
#include "paired_object.h"

void func_00182ED0(C01* self);
void func_00152600(void* list, void* item);
void func_00152440(void* a);
void func_0015F710(C6C* world, void* b);
void func_00143B20(void* a, C02* b);
void func_00129DF8(C02* self);
void func_001837E0(C02* self, s32 a1, s32 a2, s32 a3);

void func_001243E0(C02* self)
{
    func_00182ED0(self);
    C6C* s1 = self->world;
    if (self->parent == 0) {
        if (self->f294 != 0) {
            func_00152600(&s1->list78, self);
        } else {
            func_00152600(&s1->list54, self);
            u64 fl = self->flags;
            if ((fl & (1ull << 37)) != 0) {
                self->flags = fl & ~(1ull << 37);
                func_00152600(&s1->list60, self);
                if ((self->desc->flags & 2) != 0) {
                    func_00152600(&s1->list6C, self);
                }
            }
            func_0015F710(s1, self->f54);
            self->f54 = 0;
            func_00152440(&self->list60);
        }
    }
    if ((self->flags & (1ull << 36)) != 0) {
        func_00143B20(D_00261990, self);
    }
    if (self->f284 != 0) {
        func_00152600(&self->world->list1C00, self->f284);
    }
    if ((self->flags & (1ull << 38)) != 0) {
        void (*fn)(C01* self, s32 on) = self->desc->m14;
        if (fn != 0) {
            fn(self, 0);
        }
    }
    func_00129DF8(self);
    self->root = 0;
    func_001837E0(self, 5, 0, 0);
}

extern void* func_00159BB0();
extern s32 func_00182FC8(void*);

extern void func_00188FD8(void*, void*);

void func_00124540(C02* object)
{
	object->v190 = object->pos;
	object->m1A0.r[0] = object->rot.r[0];
	object->m1A0.r[1] = object->rot.r[1];
	object->m1A0.r[2] = object->rot.r[2];
	object->desc02()->m2A(object, &object->m1A0);
	func_00188FD8(&object->m1A0, &object->v1D0);
}

void func_00125108(C02* self)
{
    void (*fn)(C01* self) = self->desc->m13;
    if (fn != 0) {
        fn(self);
    }
}

void func_00125438(C02* self)
{
    (void)self;
}

void func_00126AB0(C02* state, u32 value)
{
	*(u32*)(state->sub22C + 0x3C) = value;
	*(u32*)(state->sub22C + 0x38) |= 2;
}

void* func_00159BB0(void);
s32 func_00182FC8(void* self);

struct Sub_126C58 {
    s32 f0;
    f32 f4;
};

void func_00126C58(C02* self)
{
    if (self->f298 == 0) {
        self->f298 = func_00159BB0();
        if (func_00182FC8(self) != 0) {
            ((Sub_126C58*)self->f298)->f4 = 1.0f;
        } else {
            ((Sub_126C58*)self->f298)->f4 = 0.0f;
        }
    }
}

// What slot 29 tells the object's listeners (kind 3): the position before, and the object.
struct Frame_1273F0 {
    void* self;
    u8 pad[0xC];
    Vec02 q;
};

void func_001226D8(void* p);

void func_001273F0(C02* self, Vec02* src)
{
    Frame_1273F0 f;
    f.q = self->v140;
    f.self = self;
    self->pos = *src;
    if (self->desc->m12 != 0) {
        self->desc->m12(self);
    }
    if (self->f1EC != 0) {
        func_001226D8(self->f1EC);
    }
    self->desc->m0E(self, 3, &f);
}

void func_001226D8(void* p);
s32 func_00123DC0(void* a);
void func_00129DF8(void* self);

void func_001274F8(C02* self, Vec02* src)
{
    self->v150 = *src;
    if (self->f1EC != 0) {
        func_001226D8(self->f1EC);
    }
    if (func_00123DC0(src) == 0) {
        func_00129DF8(self);
    }
}

void func_001226D8(void* p);
s32 func_00123E00(void* a);
void func_00129DF8(void* self);

void func_00127590(C02* self, Vec02* src)
{
    self->v160 = *src;
    if (self->f1F0 != 0) {
        func_001226D8(self->f1F0);
    }
    if (func_00123E00(src) == 0) {
        func_00129DF8(self);
    }
}

struct Vec3_127558 { f32 x; f32 y; f32 z; };
void func_00127558(ObjectCycler* self, f32 x, f32 y, f32 z)
{
    Vec3_127558 v;
    v.x = x;
    v.y = y;
    v.z = z;
    self->desc02()->m20(self, (Vec02*)&v);
}

void func_001275F0(PairedObject* self, f32 x, f32 y, f32 z)
{
    f32 v[3];
    v[0] = x;
    v[1] = y;
    v[2] = z;
    self->desc02()->m21(self, (Vec02*)v);
}

typedef void (*VFn0_124EE8)(void* self);

struct Info_124EE8 {
    u8 pad0[8];
    s32 flags;
};

struct Node_124EE8 {
    Info_124EE8* info;
};

struct List_124EE8 {
    s32 head;
    u8 pad4[0x4];
    s32 link;
};

struct Obj_124EE8 {
    void** vt;
    u8 pad4[0x30];
    List_124EE8 list;
};

struct Frame_124EE8 {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};

s32 func_00182FC8(void* self);
void func_00124EE8(void* self, f32 f);

void func_00124EE8(void* self, f32 f)
{
    Obj_124EE8* obj = (Obj_124EE8*)self;
    Frame_124EE8 fr;
    f32 saved = f;
    VFn0_124EE8 pre = (VFn0_124EE8)obj->vt[21];
    if (pre != 0) {
        pre(self);
    }
    if (func_00182FC8(self) == 0) {
        return;
    }
    s32 e = (s32)&obj->list;
    fr.list = e;
    fr.cursor = e;
    s32 old = *(s32*)&D_0027B314;
    s32 link = *(s32*)(e + 8);
    fr.prev = old;
    fr.link = link;
    *(s32*)&D_0027B314 = (s32)&fr;
    s32 head = obj->list.head;
    fr.cursor = head + fr.link;
    Node_124EE8* node = (Node_124EE8*)head;
    while (node != 0) {
        if ((node->info->flags & 1) != 0) {
            func_00124EE8(node, saved);
        }
        s32 nx = *(s32*)fr.cursor;
        fr.cursor = nx + fr.link;
        node = (Node_124EE8*)nx;
    }
    *(s32*)&D_0027B314 = fr.prev;
}

struct __attribute__((aligned(16))) Quad_1261C0 { s32 w[4]; };
struct Inner_1261C0 { u8 pad0[0x60]; Quad_1261C0 q60[4]; u8 pad1[4]; s32 fA4; u8 pad2[8]; s32 fB0; };

void func_001261C0(C02* self, void* b, void* m)
{
    Quad_1261C0* src = (Quad_1261C0*)m;
    self->desc02()->m2C(self);
    Inner_1261C0* in = (Inner_1261C0*)self->f224;
    if (in != 0 && (in->fB0 & 0x80) != 0) {
        if (src != 0) {
            in->fA4 = 1;
            Inner_1261C0* p = (Inner_1261C0*)self->f224;
            p->q60[0] = src[0];
            p->q60[1] = src[1];
            p->q60[2] = src[2];
            p->q60[3] = src[3];
        } else {
            in->fA4 = 0;
        }
    }
    self->desc02()->m26(self, b, src);
}

void func_00128DB8(void* self);
void func_00124540(void* self);
void* func_0015A448(void* a, s32 b, void* c);
void func_0012A860(void* self, void* v);
void func_00165828(void* a, void* b);

struct Sub_1249A8 {
    u8 pad0[0x20];
    s32 f20;
};

void func_001249A8(C02* self)
{
    ListFrame frame;
    func_00128DB8(self);
    func_00124540(self);
    Sub_1249A8* sub = (Sub_1249A8*)self->f200;
    if (sub != 0 && sub->f20 != -1) {
        void* v = func_0015A448(self->world, sub->f20, self);
        if (v != 0) {
            func_0012A860(self, v);
        }
    }
    func_00165828(self->sub22C, self);
    for (C01* p = (C01*)self->children.head; p != 0; p = p->next) {
        void (*fn)(C01* self) = p->desc->m0F;
        if (fn != 0) {
            fn(p);
        }
    }
}

extern f32 D_0026185C;

void func_001BFCD8(s32 a0, void* a1, void* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a4, s32 a5);

void func_00127378(C02* self, s32 mode)
{
    if (mode == 1) {
        S1BE4D8* s = self->f2AC;
        if (s != 0) {
            if (D_0026185C != 0.0f) {
                if (s->f1C == 0) {
                    func_001BFCD8(s->f00, &s->f1C, self, 0, s->f04, s->f08, s->f0C, s->f10, s->f20, &s->b14, 0);
                }
            }
        }
    }
}


void func_00182D48(C01* self);
void func_00152470(void* list, void* item);
void func_0015F7D8(C6C* world, C02* item);
void func_00143AF8(C02* a, C02* self);

void func_001240F8(C02* self)
{
    f32 v0[4];
    f32 v1[4];
    f32 v2[4];
    s32 scratch[8];
    (void)scratch;
    func_00182D48(self);
    C6C* ctx = self->world;
    if (!self->parent) {
        self->root = self;
        if (self->f294) {
            func_00152470(&ctx->list78, self);
        } else {
            func_00152470(&ctx->list54, self);
            self->flags |= 0x2000000000ULL;
            func_00152470(&ctx->list60, self);
            if (self->desc->flags & 2) func_00152470(&ctx->list6C, self);
            s32 n = self->count6C;
            self->f54 = self;
            self->list60.tail = self;
            n--;
            self->list60.head = self;
            for (; n >= 0; n--) func_0015F7D8(ctx, self->items70[n]);
        }
    } else {
        self->root = ((C02*)self->parent)->root;
        if (((C02*)self->parent)->flags & 0x4000000000ULL) {
            if (self->desc->m14) self->desc->m14(self, 1);
        }
    }
    if (self->f1EC) {
        self->f1EC->vt->getPos(self->f1EC, 0.0f, (Vec02*)v0, (Vec02*)v1);
        self->desc02()->m1D(self, (Vec02*)v0);
        self->desc02()->m20(self, (Vec02*)v1);
    }
    if (self->f1F0) {
        self->f1F0->vt->getRot(self->f1F0, 0.0f, (Mat02*)v2, (Vec02*)v0);

        self->desc02()->m1E(self, (Mat02*)v2);
        self->desc02()->m21(self, (Vec02*)v0);
    }
    if (self->flags & 0x1000000000ULL) func_00143AF8((C02*)D_00261990, self);
    if (self->f284) func_00152470(&self->world->list1C00, self->f284);
    if (self->desc->m12) self->desc->m12(self);
    func_001837E0(self, 4, 0, 0);
    func_00129DF8(self);
}

struct Pair_124A48 {
    s32 a;
    s32 b;
};
struct Frame_124A48 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
};

void func_00182C58(C01* self);
void func_00124CC0(C02* self);
void func_001DBCC8(void* owner, void* fn, C02* arg, s32 a3, s32 a4);
void func_00165728(void* a, C02* b);
s32 func_001B1D38(S1291D0* p);
void func_001B1D70(S1291D0* p, f32 v);
void func_001B1DA8(S1291D0* p, f32 v);
void* func_0015A448(void* a, s32 b, C02* c);
void func_00152E48(void* a, S1291D0* b);
void func_001B1B38(S1291D0* p);
void func_001BFCD8(s32 a0, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a1, C02* a2, s32 a3, void* a4, s32 a5);
void* func_0018D5C0(s32 bytes);
s32 func_001833F0(C01* a, s32 b);
C01* func_0015A418(void* host, s32 a1, s32 a2, C02* ctx);
s32 func_00182FC8(C01* p);

void func_00124A48(C02* self)
{
    Frame_124A48 fr;
    Key02* k;
    C01* s0;
    s32 old = (s32)D_0027B314;
    s32 e = (s32)&self->children;
    fr.f00 = e;
    fr.f04 = e;
    fr.f08 = *(s32*)(e + 8);
    fr.f0C = old;
    D_0027B314 = (ListFrame*)&fr;
    func_00182C58(self);
    if (self->f2A0 != 0) {
        if (((Pair_124A48*)self->f2A0)->a != 0 || ((Pair_124A48*)self->f2A0)->b != -1) {
            func_001DBCC8(self->world, (void*)func_00124CC0, self, 0, 0);
        }
    }
    func_00165728(self->sub22C, self);
    if (self->f284 != 0) {
        if (func_001B1D38(self->f284) == 0) {
            func_001B1D70(self->f284, self->f2A8);
            func_001B1DA8(self->f284, self->f2A8 * 0.5f);
        }
        if ((self->f284)->fB0 != -1) {
            (self->f284)->fB4 = func_0015A448(self->world, (self->f284)->fB0, self);
            if ((self->f284)->fB4 != 0) {
                func_00152E48((self->f284)->fB4, self->f284);
            }
        }
        func_001B1B38(self->f284);
    }
    if (self->f2AC != 0) {
        if (self->f2AC->f00 == -1) {
            self->f2AC = 0;
        }
        if (self->f2AC != 0) {
            S1BE4D8* q = self->f2AC;
            func_001BFCD8(q->f00, q->f04, q->f08, q->f0C, q->f10, q->f20, &q->f1C, self, 0, q->b14, 0);
        }
    }
    if (self->f26C != 0) {
        self->f1F8 = (void**)func_0018D5C0(self->f26C << 2);
    }
    for (k = self->keys; k != 0; k = k->next) {
        if (func_001833F0(self, k->key) != 0) {
            s0 = self;
        } else {
            s0 = func_0015A418(self->world, 1, k->key, self);
            if (s0 == 0) {
                continue;
            }
        }
        if (func_00182FC8(s0) != 0 && s0 != self) {
            s0->desc->m10(s0);
        }
        s0->desc->m03(s0);
    }
    self->keys = 0;
    {
        s32 head = *(s32*)fr.f04;
        s32 p;
        fr.f04 = head + fr.f08;
        p = head;
        while (p != 0) {
            ((C01*)p)->desc->m10((C01*)p);
            s32 nx = *(s32*)fr.f04;
            fr.f04 = nx + fr.f08;
            p = nx;
        }
    }
    D_0027B314 = (ListFrame*)fr.f0C;
}

void func_001830D8(C01* self, C01* src);
void func_00165920(u8* a, C02* self, u8* src);
void* func_0018D568(s32 size, void* src);
void* func_00121280(void* src, C6C* world, C02* self);
void func_001299E0(C02* self, void* v);
u8* func_001B5EC0(Pool6C* pool);
void func_0018D800(u8* dst, void* src, s32 n);
void func_00152450(u8* p);
void func_00143AF8(void* list, C02* item);
extern u8 D_00260E70[];
extern u8 D_00260E80[];
extern u8 D_00260E90[];
extern u8 D_00260EA0[];

void func_00127048(C02* self, C02* src)
{
    void* s54 = self->f54;
    C02* s50 = self->root;
    Link02 t48 = self->link48;
    u64 bit = (self->flags >> 37) & 1;
    Link02 t40 = self->link40;
    Link02 t58 = self->link58;
    List01 t60 = self->list60;
    List01 t1E0 = self->list1E0;
    func_001830D8(self, src);
    func_00165920(self->sub22C, self, src->sub22C);
    if (self->f224) {
        self->f224 = (Rec2195_224*)func_0018D568(0xC0, self->f224);
    }
    func_00152440(&self->children);
    self->link48 = t48;
    self->link40 = t40;
    self->link58 = t58;
    self->list60 = t60;
    self->f54 = s54;
    self->root = s50;
    self->flags = (self->flags & ~(1ULL << 37)) | ((u64)bit << 37);
    self->list1E0 = t1E0;
    self->desc02()->m2B(self);
    if (src->f1FC) {
        self->f1FC = func_00121280(src->f1FC, self->world, self);
        func_001299E0(self, self->f1FC);
    }
    if (src->f200) {
        self->f200 = func_00121280(src->f200, self->world, self);
        func_001299E0(self, self->f200);
    }
    if (src->f204) {
        self->f204 = func_00121280(src->f204, self->world, self);
        func_001299E0(self, self->f204);
    }
    if (src->f284) {
        u8* p = func_001B5EC0(&self->world->pool1BF4);
        func_0018D800(p, src->f284, 0x2E0);
        func_00152450(p + 0xB8);
        self->f284 = (S1291D0*)p;
        func_00152470(&self->world->list1C00, p);
    }
    if (src->f2AC) {
        self->f2AC = (S1BE4D8*)func_0018D568(0x24, src->f2AC);

    }
    if (src->f288) {
        self->f288 = func_0018D568(0x40, src->f288);
    }
    if (self->flags & (1ULL << 36)) {
        if (func_00182FC8(self)) {
            func_00143AF8(D_00261990, self);
        }
    }
    if (self->p20C != D_00260E70) self->p20C = (u8*)func_0018D568(0x10, self->p20C);
    if (self->p210 != D_00260E80) self->p210 = (u8*)func_0018D568(0x10, self->p210);
    if (self->p214 != D_00260E90) self->p214 = (u8*)func_0018D568(0x10, self->p214);
    if (self->p218 != D_00260EA0) self->p218 = (u8*)func_0018D568(0x10, self->p218);
}

// NEAR: the branches and the 0x40-byte copy loop match; retail loads both quads of a pair before
// storing them (and computes the loop end in $v0), ours interleaves load and store.

struct __attribute__((aligned(16))) Quad_00125B70 { s32 w[4]; };
struct Dst_00125B70 {
    Quad_00125B70 q[4];
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4c;
};

extern u8 D_00248D40[];

void func_00188C10(Vec02* a, Mat02* b, u8* c, void* d);

void func_00125B70(C02* self, Quad_00125B70* src, Dst_00125B70* dst)
{
    if (src != 0) {
        if (src != (Quad_00125B70*)dst) {
            *dst = *(Dst_00125B70*)src;
        }
    } else {
        func_00188C10(&self->v140, &self->m110, D_00248D40, dst);
        dst->f44 = 1.0f;
        dst->f40 = 1.0f;
    }
}

void* func_0015A418(C6C* host, s32 kind, u32 id, C01* ctx);
void func_00182ED8(void* node);
void func_001832F0(void* node, C01* ctx);

void func_00124DF8(C01* self, s32 count, S124DF8* item)
{
    C6C* host = self->world;
    if (count <= 0) {
        return;
    }
    S124DF8* it = item;
    s32 n = count;
    do {
        u32 f = it->flags;
        s32 kind = (f & 1) ? 5 : 1;
        if (f & 0x20) {
            kind |= 0x100;
        }
        void* node = func_0015A418(host, kind, it->id, self);
        if (node) {
            if (!(it->flags & 8)) {
                *(void**)((u8*)self + it->offset) = node;
            }
            if (!(it->flags & 4)) {
                func_00182ED8(node);
            }
            if (it->flags & 0x10) {
                func_001832F0(node, self);
            }
        }
        n--;
        it++;
    } while (n != 0);
}

void func_001226D8(void* p);

void func_00127478(C02* self, Mat02* src)
{
    self->rot = *src;
    if (self->desc->m12)
        self->desc->m12(self);
    if (self->f1F0)
        func_001226D8(self->f1F0);
    self->desc->m0E(self, 4, self);
}

struct Iter_00124050 { List01* list; u8* link; s32 offset; Iter_00124050* saved; };

struct Next_00124050 {
    static C01* Of(Iter_00124050* it)
    {
        C01* obj = *(C01**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_00124050 {
    static void Of(Iter_00124050* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_00124050*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

void func_00124050(C02* self)
{
    Iter_00124050 it;
    Begin_00124050::Of(&it, &self->children);
    self->desc->m06(self);
    C01* obj;
    while ((obj = Next_00124050::Of(&it)) != 0) {
        obj->desc->m04(obj);
    }
    self->desc->m0E(self, 1, self);
    D_0027B314 = (ListFrame*)it.saved;
}

struct Iter_00124338 { List01* list; u8* link; s32 offset; Iter_00124338* saved; };

struct Next_00124338 {
    static C01* Of(Iter_00124338* it)
    {
        C01* obj = *(C01**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_00124338 {
    static void Of(Iter_00124338* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_00124338*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

void func_00124338(C02* self)
{
    Iter_00124338 it;
    Begin_00124338::Of(&it, &self->children);
    self->desc->m07(self);
    C01* obj;
    while ((obj = Next_00124338::Of(&it)) != 0) {
        obj->desc->m05(obj);
    }
    self->desc->m0E(self, 2, self);
    D_0027B314 = (ListFrame*)it.saved;
}

struct Iter_00126F78 { List01* list; u8* link; s32 offset; Iter_00126F78* saved; };

struct Next_00126F78 {
    static C01* Of(Iter_00126F78* it)
    {
        C01* obj = *(C01**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_00126F78 {
    static void Of(Iter_00126F78* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_00126F78*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

void* func_00183058(C01* item, C6C* world, C02* parent);
void func_001BB580(C02* self);

void func_00126F78(C02* self, C02* owner)
{
    Iter_00126F78 it;
    Begin_00126F78::Of(&it, &owner->children);
    self->desc->m09(self, owner);
    C01* obj = Next_00126F78::Of(&it);
    while (obj != 0) {
        (void)func_00183058(obj, self->world, self);
        obj = Next_00126F78::Of(&it);
    }
    if ((self->desc->flags & 2) && self->parent == 0) {
        func_001BB580(self);
    }
    D_0027B314 = (ListFrame*)it.saved;
}

struct Object_124FC0;
struct Vtable_124FC0 {
    u8 pad0[0xC];
    void (*update)(Object_124FC0*, f32);
};
struct Object_124FC0 { Vtable_124FC0* vtable; };
struct Iter_124FC0 { List01* list; u8* link; s32 offset; Iter_124FC0* saved; };

struct Next_124FC0 {
    static Object_124FC0* Of(Iter_124FC0* it)
    {
        Object_124FC0* obj = *(Object_124FC0**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_124FC0 {
    static void Of(Iter_124FC0* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = ((Iter_124FC0*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

void func_00165FE0(u8* sub, C02* self, f32 f);
void func_001B2140(void* p, f32 f);
void func_00126AC8(C02* self, f32 f);
void func_001837E0(C02* self, s32 a, s32 b, void** args);

void func_00124FC0(C02* self, f32 f)
{
    func_00165FE0(self->sub22C, self, f);
    if (self->f284 != 0) {
        func_001B2140(self->f284, f);
    }
    if (self->f288 != 0) {
        func_00126AC8(self, f);
    }
    Iter_124FC0 it;
    Begin_124FC0::Of(&it, &self->list1E0);
    Object_124FC0* obj;
    while ((obj = Next_124FC0::Of(&it)) != 0) {
        if (obj->vtable->update != 0) {
            obj->vtable->update(obj, f);
        }
    }
    D_0027B314 = (ListFrame*)it.saved;
    void* args[1];
    args[0] = &f;
    func_001837E0(self, 1, 1, args);
}

struct Ctx_124CC0 { C83* node; void* key; s32 mode; f32 value; f32 f10; };

C83* func_0015A418(void* a, s32 b, void* c, C02* d);
void func_0012C9E8(C83* a, C02* b, f32 c, void* d, f32* e, s32 f, s32 g);
void func_0012C288(C83* a, C02* b, s32 c, S12C288* d, f32 e, f32 f, s32 g, s32 h);

struct Clamp_124CC0 {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) {
            return lo;
        }
        if (hi < x) {
            return hi;
        }
        return x;
    }
};

struct Find_124CC0 {
    static C83* Of(C02* self, Ctx_124CC0* ctx)
    {
        if (ctx->node != 0) {
            return ctx->node;
        }
        return func_0015A418(self->world, 0x104, ctx->key, self);
    }
};

struct Frame_124CC0 : S12C288 { u8 pad0[8]; f32 tmp; };

void func_00124CC0(C02* self)
{
    Ctx_124CC0* ctx = (Ctx_124CC0*)self->f2A0;
    C83* node = Find_124CC0::Of(self, ctx);
    if (node == 0) {
        return;
    }
    Frame_124CC0 fr;
    switch (ctx->mode) {
    case 0:
        fr.tmp = ctx->value;
        break;
    case 1:
        fr.tmp = Clamp_124CC0::Of(ctx->value, 0.0f, 1.0f) * node->length;
        break;
    case 2:
        func_0012C9E8(node, self, 0.0f, (u8*)self + 0x100, &fr.tmp, 0, 0);
        break;
    default:
        return;
    }
    fr.key = node->id;
    fr.val = self;
    func_0012C288(node, self, 1, &fr, fr.tmp, ctx->f10, 0, 0);
}

struct Fl_1276C0 {
    u8 pad0[0x90];
    f32 f90;
    f32 f94;
    u8 pad98[0xB0 - 0x98];
    s32 fB0;
};

struct Locals_1276C0 {
    u8 a20[16];
    u8 a30[16];
    u8 a40[16];
    u8 a50[16];
    u8 pad60[0x30];
};

void func_00128018(C02* z, C01* frame, void* c, u8* d);
void func_00128150(C02* z, C01* frame, void* c, u8* d);
void func_00128330(C01* a, C01* b, void* c, void* d, void* e, s32 f, s32 g, u8* h, u8* i, s32 j, s32 k);
C02* func_0015A418(C6C* world, s32 a1, s32 a2, C02* ctx);

void func_001276C0(C02* self, C02* other)
{
    Locals_1276C0 L;
    func_00128018(0, self->parent, &other->v140, L.a20);
    func_00128150(0, self->parent, &other->m110, L.a50);
    func_00128330(other->parent, self->parent, &other->v140, &other->v150, &other->v160, 0, 0, L.a30, L.a40, 0, 0);
    self->desc02()->m1D(self, (Vec02*)L.a20);
    self->desc02()->m1E(self, (Mat02*)L.a50);
    self->desc02()->m20(self, (Vec02*)L.a30);
    self->desc02()->m21(self, (Vec02*)L.a40);
    Fl_1276C0* a = (Fl_1276C0*)self->f224;
    if (a != 0 && (a->fB0 & 0x20)) {
        Fl_1276C0* b = (Fl_1276C0*)other->f224;
        if (b != 0 && (b->fB0 & 0x20)) {
            a->f90 = b->f90;
            ((Fl_1276C0*)self->f224)->f94 = ((Fl_1276C0*)other->f224)->f94;
        }
    }
    C02* n = (C02*)self->children.head;
    if (n != 0) {
        do {
            if ((n->desc->flags ^ 1) & 1)
                continue;
            C02* h = func_0015A418(self->world, 2, n->id, other);
            if (h == 0)
                continue;
            if ((h->desc->flags ^ 1) & 1)
                continue;
            if (n->f224 != 0 && (((Fl_1276C0*)n->f224)->fB0 & 0xC))
                continue;
            n->desc02()->m1F(n, h);
        } while ((n = (C02*)n->next) != 0);
    }
}
