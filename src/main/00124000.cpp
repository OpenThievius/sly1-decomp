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

struct Ent_1249A8 { u8 pad[0x20]; s32 f20; };
struct Ptr_1249A8 { u8 pad[0x4]; };
struct Node_1249A8;
typedef void (*VFn_1249A8)(Node_1249A8* self);
struct Node_1249A8 { VFn_1249A8* vtbl; u8 pad[0x18]; Node_1249A8* f1C; };
struct Obj_1249A8 { u8 pad[0x14]; void* f14; u8 pad2[0x1C]; Node_1249A8* f34; u8 pad3[0x1C8]; Ent_1249A8* f200; };

void func_00128DB8(Obj_1249A8* self);
void func_00124540(Obj_1249A8* self);
void* func_0015A448(void* obj, s32 id, Obj_1249A8* self);
void func_0012A860(Obj_1249A8* self, void* v);
void func_00165828(Ptr_1249A8* a, Obj_1249A8* self);

void func_001249A8(Obj_1249A8* self)
{
    s32 scratch[4];
    (void)scratch;
    func_00128DB8(self);
    func_00124540(self);
    Ent_1249A8* a1 = self->f200;
    if (a1 != 0 && a1->f20 != -1) {
        void* v = func_0015A448(self->f14, a1->f20, self);
        if (v != 0) {
            func_0012A860(self, v);
        }
    }
    func_00165828((Ptr_1249A8*)((u8*)self + 0x22C), self);
    Node_1249A8* n = self->f34;
    if (n != 0) {
        do {
            VFn_1249A8 fn = n->vtbl[19];
            if (fn != 0) {
                fn(n);
            }
            n = n->f1C;
        } while (n != 0);
    }
}

typedef u64 Quad_1261C0 __attribute__((mode(TI)));

struct Obj_1261C0 {
    u8* vt;
    u8 pad4[0x224 - 0x04];
    u8* f224;
};

typedef void (*Slot_1261C0)(void* self, void* a, void* b);

void func_001261C0(Obj_1261C0* self, void* a1, void* a2)
{
    (*(Slot_1261C0*)(self->vt + 0xC0))(self, a1, a2);
    u8* ch = self->f224;
    if (ch != 0 && (*(u32*)(ch + 0xB0) & 0x80) != 0) {
        if (a2 != 0) {
            *(s32*)(ch + 0xA4) = 1;
            u8* dst = self->f224;
            *(Quad_1261C0*)(dst + 0x60) = *(Quad_1261C0*)((u8*)a2 + 0x00);
            *(Quad_1261C0*)(dst + 0x70) = *(Quad_1261C0*)((u8*)a2 + 0x10);
            *(Quad_1261C0*)(dst + 0x80) = *(Quad_1261C0*)((u8*)a2 + 0x20);
            *(Quad_1261C0*)(dst + 0x90) = *(Quad_1261C0*)((u8*)a2 + 0x30);
        } else {
            *(s32*)(ch + 0xA4) = 0;
        }
    }
    (*(Slot_1261C0*)(self->vt + 0xA8))(self, a1, a2);
}
