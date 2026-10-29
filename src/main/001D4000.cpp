// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

typedef void (*VFn_D5418)(void* self);
struct Obj_D5418 {
    VFn_D5418* vtbl;
};

s32 func_00160C58(void* a);
void func_00175170(void* a, s32 b, s32 c);

void func_001D5418(Obj_D5418* a0)
{
    if (func_00160C58(a0)) {
        a0->vtbl[84](a0);
    } else {
        func_00175170(a0, 4, 0x2D);
    }
}

extern f32 D_00261858[];

typedef void (*VFnA)(void* self);
typedef void (*VFnB)(void* self, void* arg);

struct Node_1D6CB0 {
    void** vtbl;
};

struct Obj_1D6CB0 {
    void** vtbl;
    u8 pad4[0x68C];
    f32 f690;
    s32 f694;
};

struct Owner_1D6CB0 {
    u8 pad0[0x1504];
    Node_1D6CB0* fallback;
    Node_1D6CB0* slots[4];
    Obj_1D6CB0* obj;
};

s32 func_00182FC8(void* node);

void func_001D6CB0(Owner_1D6CB0* self)
{
    Obj_1D6CB0* obj = self->obj;
    if (obj != 0) {
        Node_1D6CB0* s0 = 0;
        u32 i = 0;
        while (i < 4) {
            s0 = self->slots[i];
            if (s0 != 0 && func_00182FC8(s0) != 0) {
                break;
            }
            i++;
        }
        if (i >= 4) {
            s0 = self->fallback;
        }
        ((VFnA)obj->vtbl[6])(obj);
        ((VFnB)obj->vtbl[25])(obj, 0);
        ((VFnB)obj->vtbl[35])(obj, s0);
        obj->f690 = D_00261858[1];
        obj->f694 = 1;
        if (s0 != self->fallback) {
            ((VFnA)s0->vtbl[7])(s0);
        }
    }
}

extern s32 D_00262E10;

s32 func_001B8A08(void* self, s32 value);

s32 func_001D6DA0(void* self, s32 value)
{
    if (value == D_00262E10) {
        return 1;
    }
    return func_001B8A08(self, value);
}

struct Obj_1D7018 {
    u8 pad0[0x694];
    s32 f694;
};

void func_0013BA70(void* self);

void func_001D7018(Obj_1D7018* self)
{
    func_0013BA70(self);
    self->f694 = 0;
}

struct Node_1D7100 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
};

Node_1D7100* func_001D7100(Node_1D7100* self, s32 value)
{
    self->fC = value;
    self->f0 = 0;
    self->f4 = 0;
    self->f8 = 0;
    self->f10 = 0;
    self->f14 = 0;
    return self;
}

struct Ctx_1D65D8 {
    u8 pad0[0x2220];
    s32 mode;
    u8 pad1[0x2228 - 0x2224];
    s32 level;
    u8 pad2[0x26C4 - 0x222C];
    s32 flag;
};

s32 func_001D65D8(Ctx_1D65D8* self)
{
    if (self->mode != 4) {
        return self->flag != 0;
    }
    if (self->level < 45) {
        return 1;
    }
    return 2;
}

struct Ctx_1D4C90 { u8 pad[0x26B0]; s32 f26B0; };

void func_001D4C90(Ctx_1D4C90* self, s32 value)
{
    self->f26B0 = value;
}

typedef void (*VFnA_1D5398)(void* self);
struct Obj_1D5398 { VFnA_1D5398* vtbl; };

void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void func_00175170(void* self, s32 mode, s32 count);
void func_001D4C90(void* self, s32 value);

void func_001D5398(Obj_1D5398* self)
{
    func_001BFCD8(0xA6, 0, 0, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f);
    func_00175170(self, 4, 0x2A);
    func_001D4C90(self, (s32)func_001D5418);
}

typedef void (*VFnA_1D5468)(void* self);
typedef void (*VFnB_1D5468)(void* self, void* arg);
struct Obj_1D5468 { void** vtbl; };

s32 func_00160C58();
void func_00175170(void* self, s32 mode, s32 count);

void func_001D5468(Obj_1D5468* self)
{
    ((VFnB_1D5468)self->vtbl[36])(self, (u8*)self + 0x2BB0);
    ((VFnB_1D5468)self->vtbl[37])(self, (u8*)self + 0x2BC0);
    if (func_00160C58()) {
        ((VFnA_1D5468)self->vtbl[84])(self);
    } else {
        func_00175170(self, 4, 0x2D);
    }
}

struct Obj_001D5650 { u8 pad[0x10]; f32 value; };
s32 func_001D5650(Obj_001D5650* a, Obj_001D5650* b) { if (a->value < b->value) return -1; return 1; }

struct Obj_001D7120 { s32 a; s32 b; s32 c; s32 d; s32 e; s32 f; };
Obj_001D7120* func_001D7120(Obj_001D7120* self, s32 a, s32 b) { self->a = a; self->b = b; self->c = 0; self->d = -1; self->e = 0; self->f = 0; return self; }

struct Owner_1D40A0 {
    u8 pad0[0x638];
    f32 f638;
    u8 f63C[0x4];
    u8 f640[0x4];
};

struct Obj_1D40A0 {
    f32 f0;
    u8 pad4[0x4C];
    f32 f50;
    s32 f54;
    u8 pad58[0x48];
    s32 fA0;
    u8 padA4[0x4C];
    s32 fF0;
    u8 padF4[0x4C];
    s32 f140;
    u8 pad144[0x4C];
    s32 f190;
};

struct Sub_1D40A0 {
    u8 pad0[0x8];
    s32 f8;
};

struct Ctx_1D40A0 {
    u8 pad0[0xC0];
    Sub_1D40A0* sub;
};

void func_001399F8(void* obj, s32 a1, s32 a2, void* a3);
void func_001D39E0(s32 a0, void* a1, s32 a2, void* a3);

void func_001D40A0(Owner_1D40A0* a0, Obj_1D40A0* a1, Ctx_1D40A0* a2, f32 f12, f32 f13)
{
    a0->f638 = f12;
    if (a1->f54 == 0) {
        a1->f0 = 1.0f;
        a1->f50 = 0.0f;
    } else {
        f32 one = 1.0f;
        a1->f50 = f13;
        a1->f0 = one - f13;
    }
    a1->fA0 = 0;
    a1->f140 = 0;
    a1->fF0 = 0;
    a1->f190 = 0;
    func_001399F8(a2, 0x50, 6, a1);
    func_001D39E0(6, a1, a2->sub->f8, &a0->f640);
}

extern u8 D_00274FC0[];

struct Item_1D4848 { s32 f0; u8 pad4[4]; s32 f8; };
struct Obj_1D4848 { u8 pad0[0x14]; void* f14; u8 pad1[0x2690]; s32 f26A8; Item_1D4848* f26AC; };

u8* func_0018D568(s32 size, void* src);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

void func_001D4848(Obj_1D4848* self)
{
    self->f26A8 = 7;
    self->f26AC = (Item_1D4848*)func_0018D568(0x54, D_00274FC0);
    for (s32 i = 0; i < self->f26A8; i++) {
        Item_1D4848* it = self->f26AC + i;
        it->f8 = func_0015A418(self->f14, 1, it->f0, self);
    }
}

void func_0012AAE8(void* self, f32 value);
void func_00160DA0(void);

void func_001D5620(void* self)
{
    func_0012AAE8(self, 1.0f);
    func_00160DA0();
}
