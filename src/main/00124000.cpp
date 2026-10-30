// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

typedef void (*VFn_1243E0)(void* self, s32 a);
struct Self_1243E0 {
    VFn_1243E0* vt;
    u8 pad0[0x14 - 4];
    u8* p14;
    s32 f18;
    u8 pad1[0x50 - 0x1C];
    s32 f50;
    void* p54;
    u8 pad2[0x284 - 0x58];
    void* p284;
    u8 pad3[0x294 - 0x288];
    s32 f294;
    u8 pad4[0x2C8 - 0x298];
    u64 flags2C8;
};

extern void* D_00261990;

void func_00182ED0(Self_1243E0* self);
void func_00152600(void* list, void* item);
void func_00152440(void* a);
void func_0015F710(u8* a, void* b);
void func_00143B20(void* a, Self_1243E0* b);
void func_00129DF8(Self_1243E0* self);
void func_001837E0(Self_1243E0* self, s32 a1, s32 a2, s32 a3);

void func_001243E0(Self_1243E0* self)
{
    func_00182ED0(self);
    u8* s1 = self->p14;
    if (self->f18 == 0) {
        if (self->f294 != 0) {
            func_00152600(s1 + 0x78, self);
        } else {
            func_00152600(s1 + 0x54, self);
            u64 fl = self->flags2C8;
            if ((fl & (1ull << 37)) != 0) {
                self->flags2C8 = fl & ~(1ull << 37);
                func_00152600(s1 + 0x60, self);
                if ((((s32*)self->vt)[2] & 2) != 0) {
                    func_00152600(s1 + 0x6C, self);
                }
            }
            func_0015F710(s1, self->p54);
            self->p54 = 0;
            func_00152440((u8*)self + 0x60);
        }
    }
    if ((self->flags2C8 & (1ull << 36)) != 0) {
        func_00143B20(D_00261990, self);
    }
    if (self->p284 != 0) {
        func_00152600(self->p14 + 0x1C00, self->p284);
    }
    if ((self->flags2C8 & (1ull << 38)) != 0) {
        VFn_1243E0 fn = self->vt[0x60 / 4];
        if (fn != 0) {
            fn(self, 0);
        }
    }
    func_00129DF8(self);
    self->f50 = 0;
    func_001837E0(self, 5, 0, 0);
}

struct Flags_00126AB0 { u8 pad[0x264]; u32 flags; u32 value; };

extern void* func_00159BB0();
extern s32 func_00182FC8(void*);
struct State_00126C58 { u8 pad[0x298]; void* resource; };
struct Resource_00126C58 { s32 unknown; f32 value; };

struct Callback_00125108 { u8 pad[0x5C]; void (*function)(); };
struct Root_00125108 { Callback_00125108* callback; };

struct Quad_00124540 { s32 a, b, c, d; } __attribute__((aligned(16)));
typedef void (*Callback_00124540)(void*, void*);
struct Object_00124540 {
	Callback_00124540* vtable;
	u8 pad004[0xCC];
	Quad_00124540 sourceD0;
	Quad_00124540 sourceE0;
	Quad_00124540 sourceF0;
	Quad_00124540 source100;
	u8 pad110[0x80];
	Quad_00124540 destination190;
	Quad_00124540 destination1A0;
	Quad_00124540 destination1B0;
	Quad_00124540 destination1C0;
};
extern void func_00188FD8(void*, void*);

void func_00124540(Object_00124540* object)
{
	object->destination190 = object->source100;
	object->destination1A0 = object->sourceD0;
	object->destination1B0 = object->sourceE0;
	object->destination1C0 = object->sourceF0;
	object->vtable[46](object, (u8*)object + 0x1A0);
	func_00188FD8((u8*)object + 0x1A0, (u8*)object + 0x1D0);
}

typedef void (*VFn_125108)(void* self);

struct Vtbl_125108 {
    u8 pad0[0x5C];
    VFn_125108 f5C;
};

struct Obj_125108 {
    Vtbl_125108* vt;
};

void func_00125108(Obj_125108* self)
{
    VFn_125108 fn = self->vt->f5C;
    if (fn != 0) {
        fn(self);
    }
}

void func_00125438()
{
}

void func_00126AB0(Flags_00126AB0* state, u32 value)
{
	state->value = value;
	state->flags |= 2;
}

void* func_00159BB0(void);
s32 func_00182FC8(void* self);

struct Sub_126C58 {
    s32 f0;
    f32 f4;
};

struct Obj_126C58 {
    u8 pad0[0x298];
    Sub_126C58* f298;
};

void func_00126C58(Obj_126C58* self)
{
    if (self->f298 == 0) {
        self->f298 = (Sub_126C58*)func_00159BB0();
        if (func_00182FC8(self) != 0) {
            self->f298->f4 = 1.0f;
        } else {
            self->f298->f4 = 0.0f;
        }
    }
}

struct __attribute__((aligned(16))) Quad_1273F0 {
    s32 w[4];
};

struct Frame_1273F0 {
    void* self;
    u8 pad[0xC];
    Quad_1273F0 q;
};

struct Vtbl_1273F0 {
    u8 pad[0x48];
    void (*f48)(void* self, s32 n, void* frame);
    u8 pad2[0x58 - 0x4C];
    void (*f58)(void* self);
};

struct Obj_1273F0 {
    Vtbl_1273F0* vt;
    u8 pad0[0x100 - 4];
    Quad_1273F0 q100;
    u8 pad1[0x140 - 0x110];
    Quad_1273F0 q140;
    u8 pad2[0x1EC - 0x150];
    void* p1EC;
};

void func_001226D8(void* p);

void func_001273F0(Obj_1273F0* self, Quad_1273F0* src)
{
    Frame_1273F0 f;
    f.q = self->q140;
    f.self = self;
    self->q100 = *src;
    if (self->vt->f58 != 0) {
        self->vt->f58(self);
    }
    if (self->p1EC != 0) {
        func_001226D8(self->p1EC);
    }
    self->vt->f48(self, 3, &f);
}

struct __attribute__((aligned(16))) Quad_1274F8 { s32 w[4]; };
struct Obj_1274F8 {
    u8 pad0[0x150];
    Quad_1274F8 q150;
    u8 pad1[0x1EC - 0x160];
    void* p1EC;
};

void func_001226D8(void* p);
s32 func_00123DC0(void* a);
void func_00129DF8(void* self);

void func_001274F8(Obj_1274F8* self, Quad_1274F8* src)
{
    self->q150 = *src;
    if (self->p1EC != 0) {
        func_001226D8(self->p1EC);
    }
    if (func_00123DC0(src) == 0) {
        func_00129DF8(self);
    }
}

struct __attribute__((aligned(16))) Quad_127590 { s32 w[4]; };
struct Obj_127590 {
    u8 pad0[0x160];
    Quad_127590 q160;
    u8 pad1[0x1F0 - 0x170];
    void* p1F0;
};

void func_001226D8(void* p);
s32 func_00123E00(void* a);
void func_00129DF8(void* self);

void func_00127590(Obj_127590* self, Quad_127590* src)
{
    self->q160 = *src;
    if (self->p1F0 != 0) {
        func_001226D8(self->p1F0);
    }
    if (func_00123E00(src) == 0) {
        func_00129DF8(self);
    }
}

struct Vec3_127558 { f32 x; f32 y; f32 z; };
typedef void (*VFn_127558)(void* self, void* v);
struct Obj_127558 { VFn_127558* vtbl; };

void func_00127558(void* self, f32 x, f32 y, f32 z)
{
    Vec3_127558 v;
    v.x = x;
    v.y = y;
    v.z = z;
    Obj_127558* o = (Obj_127558*)self;
    o->vtbl[36](self, &v);
}

typedef void (*VFn_001275F0)(void* self, f32* v);
struct Obj_001275F0 { VFn_001275F0* vtbl; };

void func_001275F0(Obj_001275F0* self, f32 x, f32 y, f32 z)
{
    f32 v[3];
    v[0] = x;
    v[1] = y;
    v[2] = z;
    self->vtbl[37](self, v);
}

extern u8 D_0027B314[];

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
    s32 old = *(s32*)D_0027B314;
    s32 link = *(s32*)(e + 8);
    fr.prev = old;
    fr.link = link;
    *(s32*)D_0027B314 = (s32)&fr;
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
    *(s32*)D_0027B314 = fr.prev;
}

typedef void (*VFn_1261C0)(void* self, void* b, void* m);
struct __attribute__((aligned(16))) Quad_1261C0 { s32 w[4]; };
struct Inner_1261C0 { u8 pad0[0x60]; Quad_1261C0 q60[4]; u8 pad1[4]; s32 fA4; u8 pad2[8]; s32 fB0; };
struct Self_1261C0 { VFn_1261C0* vt; u8 pad0[0x224 - 4]; Inner_1261C0* p224; };

void func_001261C0(void* obj, void* b, void* m)
{
    Self_1261C0* self = (Self_1261C0*)obj;
    Quad_1261C0* src = (Quad_1261C0*)m;
    self->vt[0xC0 / 4](self, b, src);
    Inner_1261C0* in = self->p224;
    if (in != 0 && (in->fB0 & 0x80) != 0) {
        if (src != 0) {
            in->fA4 = 1;
            Inner_1261C0* p = self->p224;
            p->q60[0] = src[0];
            p->q60[1] = src[1];
            p->q60[2] = src[2];
            p->q60[3] = src[3];
        } else {
            in->fA4 = 0;
        }
    }
    self->vt[0xA8 / 4](self, b, src);
}

void func_00128DB8(void* self);
void func_00124540(void* self);
void* func_0015A448(void* a, s32 b, void* c);
void func_0012A860(void* self, void* v);
void func_00165828(void* a, void* b);

typedef void (*VFn_1249A8)(void* self);

struct Vtbl_1249A8 {
    u8 pad0[0x4C];
    VFn_1249A8 f4C;
};

struct Node_1249A8 {
    Vtbl_1249A8* vt;
    u8 pad1[0x1C - 4];
    Node_1249A8* next1C;
};

struct Sub_1249A8 {
    u8 pad0[0x20];
    s32 f20;
};

struct Obj_1249A8 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x34 - 0x18];
    Node_1249A8* f34;
    u8 pad2[0x200 - 0x38];
    Sub_1249A8* f200;
};

void func_001249A8(Obj_1249A8* self)
{
    s32 scratch[4];
    (void)scratch;
    func_00128DB8(self);
    func_00124540(self);
    Sub_1249A8* sub = self->f200;
    if (sub != 0 && sub->f20 != -1) {
        void* v = func_0015A448(self->f14, sub->f20, self);
        if (v != 0) {
            func_0012A860(self, v);
        }
    }
    func_00165828((u8*)self + 0x22C, self);
    for (Node_1249A8* p = self->f34; p != 0; p = p->next1C) {
        VFn_1249A8 fn = p->vt->f4C;
        if (fn != 0) {
            fn(p);
        }
    }
}

struct Sub_127378 {
    s32 f0;
    f32 fx;
    f32 fy;
    f32 fz;
    f32 fw;
    u8 pad14[8];
    s32 f1C;
    f32 f20;
};

struct Obj_127378 {
    u8 pad[0x2AC];
    Sub_127378* sub;
};

extern f32 D_0026185C;

void func_001BFCD8(s32 a0, void* a1, void* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a4, s32 a5);

void func_00127378(Obj_127378* self, s32 mode)
{
    if (mode == 1) {
        Sub_127378* s = self->sub;
        if (s != 0) {
            if (D_0026185C != 0.0f) {
                if (s->f1C == 0) {
                    func_001BFCD8(s->f0, &s->f1C, self, 0, s->fx, s->fy, s->fz, s->fw, s->f20, &s->pad14, 0);
                }
            }
        }
    }
}

struct Obj_1240F8;
struct Sub_1240F8;
struct SubVT_1240F8 {
    u8 pad0[0x10];
    void (*f10)(Sub_1240F8* s, f32 t, f32* a, f32* b);
    void (*f14)(Sub_1240F8* s, f32 t, f32* a, f32* b);
};
struct Sub_1240F8 {
    SubVT_1240F8* vt;
};
struct VT_1240F8 {
    u8 pad0[8];
    s32 flags;
    u8 pad1[0x4C];
    void (*f58)(Obj_1240F8* s);
    u8 pad2[4];
    void (*f60)(Obj_1240F8* s, s32 v);
    u8 pad3[0x20];
    void (*f84)(Obj_1240F8* s, f32* v);
    void (*f88)(Obj_1240F8* s, f32* v);
    u8 pad4[4];
    void (*f90)(Obj_1240F8* s, f32* v);
    void (*f94)(Obj_1240F8* s, f32* v);
};
struct Ctx_1240F8 {
    u8 pad[1];
};
struct Obj_1240F8 {
    VT_1240F8* vt;
    u8 pad0[0x10];
    u8* ctx;
    Obj_1240F8* parent;
    u8 pad1[0x34];
    Obj_1240F8* l50;
    Obj_1240F8* l54;
    u8 pad2[4];
    Obj_1240F8* l5c;
    Obj_1240F8* l60;
    Obj_1240F8* l64;
    u8 pad3[4];
    s32 count;
    Obj_1240F8* items[1];
    u8 pad4[0x178];
    Sub_1240F8* subA;
    Sub_1240F8* subB;
    u8 pad5[0x90];
    Obj_1240F8* l284;
    u8 pad6[0xC];
    s32 f290;
    u8 pad7[0x30];
    u64 flags;
};

void func_00182D48(Obj_1240F8* self);
void func_00152470(u8* list, Obj_1240F8* item);
void func_0015F7D8(u8* ctx, Obj_1240F8* item);
void func_00143AF8(Obj_1240F8* a, Obj_1240F8* self);
void func_001837E0(Obj_1240F8* self, s32 a, s32 b, s32 c);
void func_00129DF8(Obj_1240F8* self);

void func_001240F8(Obj_1240F8* self)
{
    f32 v0[4];
    f32 v1[4];
    f32 v2[4];
    s32 scratch[8];
    (void)scratch;
    func_00182D48(self);
    u8* ctx = self->ctx;
    if (!self->parent) {
        self->l50 = self;
        if (self->f290) {
            func_00152470(ctx + 0x78, self);
        } else {
            func_00152470(ctx + 0x54, self);
            self->flags |= 0x2000000000ULL;
            func_00152470(ctx + 0x60, self);
            if (self->vt->flags & 2) func_00152470(ctx + 0x6C, self);
            s32 n = self->count;
            self->l54 = self;
            self->l64 = self;
            n--;
            self->l60 = self;
            for (; n >= 0; n--) func_0015F7D8(ctx, self->items[n]);
        }
    } else {
        self->l50 = self->parent->l50;
        if (self->parent->flags & 0x4000000000ULL) {
            if (self->vt->f60) self->vt->f60(self, 1);
        }
    }
    if (self->subA) {
        self->subA->vt->f10(self->subA, 0.0f, v0, v1);
        self->vt->f84(self, v0);
        self->vt->f90(self, v1);
    }
    if (self->subB) {
        self->subB->vt->f14(self->subB, 0.0f, v2, v0);
        self->vt->f88(self, v2);
        self->vt->f94(self, v0);
    }
    if (self->flags & 0x1000000000ULL) func_00143AF8((Obj_1240F8*)D_00261990, self);
    if (self->l284) func_00152470(self->ctx + 0x1C00, self->l284);
    if (self->vt->f58) self->vt->f58(self);
    func_001837E0(self, 4, 0, 0);
    func_00129DF8(self);
}

struct Self_124A48;
struct Vt_124A48 {
    u8 pad00[0x1C];
    void (*f1C)(Self_124A48* self);
    u8 pad20[0x50 - 0x20];
    void (*f50)(Self_124A48* self);
};
struct Sub284_124A48 {
    u8 padB0[0xB0];
    s32 fB0;
    void* fB4;
};
struct Pair_124A48 {
    s32 a;
    s32 b;
};
struct Eff_124A48 {
    s32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    f32 f10;
    u8 f14[8];
    u8 f1C[4];
    f32 f20;
};
struct Key_124A48 {
    s32 key;
    Key_124A48* next;
};
struct Self_124A48 {
    Vt_124A48* vt;
    u8 pad04[0x10];
    void* f14;
    u8 pad18[0x1C];
    u8 f34[0x1F8 - 0x34];
    void* f1F8;
    u8 pad1FC[0x22C - 0x1FC];
    u8 f22C[0x26C - 0x22C];
    s32 f26C;
    u8 pad270[0x284 - 0x270];
    Sub284_124A48* f284;
    u8 pad288[0x2A0 - 0x288];
    Pair_124A48* f2A0;
    u8 pad2A4[4];
    f32 f2A8;
    Eff_124A48* f2AC;
    u8 pad2B0[0x2C4 - 0x2B0];
    Key_124A48* f2C4;
};
struct Frame_124A48 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
};

extern u8 D_0027B314[];
void func_00182C58(Self_124A48* self);
void func_00124CC0(Self_124A48* self);
void func_001DBCC8(void* owner, void* fn, Self_124A48* arg, s32 a3, s32 a4);
void func_00165728(void* a, Self_124A48* b);
s32 func_001B1D38(Sub284_124A48* p);
void func_001B1D70(Sub284_124A48* p, f32 v);
void func_001B1DA8(Sub284_124A48* p, f32 v);
void* func_0015A448(void* a, s32 b, Self_124A48* c);
void func_00152E48(void* a, Sub284_124A48* b);
void func_001B1B38(Sub284_124A48* p);
void func_001BFCD8(s32 a0, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a1, Self_124A48* a2, s32 a3, void* a4, s32 a5);
void* func_0018D5C0(s32 bytes);
s32 func_001833F0(Self_124A48* a, s32 b);
Self_124A48* func_0015A418(void* host, s32 a1, s32 a2, Self_124A48* ctx);
s32 func_00182FC8(Self_124A48* p);

void func_00124A48(Self_124A48* self)
{
    Frame_124A48 fr;
    Key_124A48* k;
    Self_124A48* s0;
    s32 old = *(s32*)D_0027B314;
    s32 e = (s32)self->f34;
    fr.f00 = e;
    fr.f04 = e;
    fr.f08 = *(s32*)(e + 8);
    fr.f0C = old;
    *(s32*)D_0027B314 = (s32)&fr;
    func_00182C58(self);
    if (self->f2A0 != 0) {
        if (self->f2A0->a != 0 || self->f2A0->b != -1) {
            func_001DBCC8(self->f14, (void*)func_00124CC0, self, 0, 0);
        }
    }
    func_00165728(self->f22C, self);
    if (self->f284 != 0) {
        if (func_001B1D38(self->f284) == 0) {
            func_001B1D70(self->f284, self->f2A8);
            func_001B1DA8(self->f284, self->f2A8 * 0.5f);
        }
        if (self->f284->fB0 != -1) {
            self->f284->fB4 = func_0015A448(self->f14, self->f284->fB0, self);
            if (self->f284->fB4 != 0) {
                func_00152E48(self->f284->fB4, self->f284);
            }
        }
        func_001B1B38(self->f284);
    }
    if (self->f2AC != 0) {
        if (self->f2AC->f00 == -1) {
            self->f2AC = 0;
        }
        if (self->f2AC != 0) {
            Eff_124A48* q = self->f2AC;
            func_001BFCD8(q->f00, q->f04, q->f08, q->f0C, q->f10, q->f20, q->f1C, self, 0, q->f14, 0);
        }
    }
    if (self->f26C != 0) {
        self->f1F8 = func_0018D5C0(self->f26C << 2);
    }
    for (k = self->f2C4; k != 0; k = k->next) {
        if (func_001833F0(self, k->key) != 0) {
            s0 = self;
        } else {
            s0 = func_0015A418(self->f14, 1, k->key, self);
            if (s0 == 0) {
                continue;
            }
        }
        if (func_00182FC8(s0) != 0 && s0 != self) {
            s0->vt->f50(s0);
        }
        s0->vt->f1C(s0);
    }
    self->f2C4 = 0;
    {
        s32 head = *(s32*)fr.f04;
        s32 p;
        fr.f04 = head + fr.f08;
        p = head;
        while (p != 0) {
            ((Self_124A48*)p)->vt->f50((Self_124A48*)p);
            s32 nx = *(s32*)fr.f04;
            fr.f04 = nx + fr.f08;
            p = nx;
        }
    }
    *(s32*)D_0027B314 = fr.f0C;
}

struct A8_127048 { u32 a, b; } __attribute__((packed));
struct A12_127048 { A8_127048 a; u32 c; };

struct Obj_127048;
typedef void (*VFn_127048)(Obj_127048* self);
struct Vt_127048 { u8 pad[0xBC]; VFn_127048 fBC; };
struct Obj_127048 {
    Vt_127048* vtbl;
    u8 pad4[0x14 - 4];
    u8* f14;
    u8 pad18[0x34 - 0x18];
    u8 f34[0xC];
    A8_127048 f40;
    A8_127048 f48;
    s32 f50;
    s32 f54;
    A8_127048 f58;
    A12_127048 f60;
    u8 pad6C[0x1E0 - 0x6C];
    A12_127048 f1E0;
    u8 pad1EC[0x1FC - 0x1EC];
    void* f1FC;
    void* f200;
    void* f204;
    u8 pad208[4];
    u8* f20C;
    u8* f210;
    u8* f214;
    u8* f218;
    u8 pad21C[0x224 - 0x21C];
    void* f224;
    u8 pad228[0x22C - 0x228];
    u8 f22C[0x284 - 0x22C];
    void* f284;
    void* f288;
    u8 pad28C[0x2AC - 0x28C];
    void* f2AC;
    u8 pad2B0[0x2C8 - 0x2B0];
    u64 bits;
};

void func_001830D8(Obj_127048* self, Obj_127048* src);
void func_00165920(u8* a, Obj_127048* self, u8* src);
void* func_0018D568(s32 size, void* src);
void func_00152440(u8* p);
void* func_00121280(void* src, u8* a, Obj_127048* self);
void func_001299E0(Obj_127048* self, void* v);
u8* func_001B5EC0(u8* p);
void func_0018D800(u8* dst, void* src, s32 n);
void func_00152450(u8* p);
void func_00152470(u8* list, u8* item);
s32 func_00182FC8(Obj_127048* self);
void func_00143AF8(void* list, Obj_127048* item);
extern u8 D_00260E70[];
extern u8 D_00260E80[];
extern u8 D_00260E90[];
extern u8 D_00260EA0[];

void func_00127048(Obj_127048* self, Obj_127048* src)
{
    s32 s54 = self->f54;
    s32 s50 = self->f50;
    A8_127048 t48 = self->f48;
    u64 bit = (self->bits >> 37) & 1;
    A8_127048 t40 = self->f40;
    A8_127048 t58 = self->f58;
    A12_127048 t60 = self->f60;
    A12_127048 t1E0 = self->f1E0;
    func_001830D8(self, src);
    func_00165920(self->f22C, self, src->f22C);
    if (self->f224) {
        self->f224 = func_0018D568(0xC0, self->f224);
    }
    func_00152440(self->f34);
    self->f48 = t48;
    self->f40 = t40;
    self->f58 = t58;
    self->f60 = t60;
    self->f54 = s54;
    self->f50 = s50;
    self->bits = (self->bits & ~(1ULL << 37)) | ((u64)bit << 37);
    self->f1E0 = t1E0;
    self->vtbl->fBC(self);
    if (src->f1FC) {
        self->f1FC = func_00121280(src->f1FC, self->f14, self);
        func_001299E0(self, self->f1FC);
    }
    if (src->f200) {
        self->f200 = func_00121280(src->f200, self->f14, self);
        func_001299E0(self, self->f200);
    }
    if (src->f204) {
        self->f204 = func_00121280(src->f204, self->f14, self);
        func_001299E0(self, self->f204);
    }
    if (src->f284) {
        u8* p = func_001B5EC0(self->f14 + 0x1BF4);
        func_0018D800(p, src->f284, 0x2E0);
        func_00152450(p + 0xB8);
        self->f284 = p;
        func_00152470(self->f14 + 0x1C00, p);
    }
    if (src->f2AC) {
        self->f2AC = func_0018D568(0x24, src->f2AC);
    }
    if (src->f288) {
        self->f288 = func_0018D568(0x40, src->f288);
    }
    if (self->bits & (1ULL << 36)) {
        if (func_00182FC8(self)) {
            func_00143AF8(D_00261990, self);
        }
    }
    if (self->f20C != D_00260E70) self->f20C = (u8*)func_0018D568(0x10, self->f20C);
    if (self->f210 != D_00260E80) self->f210 = (u8*)func_0018D568(0x10, self->f210);
    if (self->f214 != D_00260E90) self->f214 = (u8*)func_0018D568(0x10, self->f214);
    if (self->f218 != D_00260EA0) self->f218 = (u8*)func_0018D568(0x10, self->f218);
}
