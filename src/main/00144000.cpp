// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern u8 D_002619A0[];
void func_0012AA28(void* a, s32 b);
void func_001289C0(void* a, void* b);
void func_00124DF8(void* a, s32 b, void* c);

void func_001463C0(void* self, void* arg)
{
    func_0012AA28(self, 1);
    func_001289C0(self, arg);
    func_00124DF8(self, 5, D_002619A0);
}

struct Obj_146418 {
    u8 pad0[0x374];
    u8 tail[8];      // 0x374: copied unaligned, 8 bytes
    s32 f37C;
};

void func_00127048(void* a, void* b);

void func_00146418(Obj_146418* self, void* arg)
{
    s32 keep = self->f37C;
    u64 tmp;
    __builtin_memcpy(&tmp, self->tail, 8);
    func_00127048(self, arg);
    __builtin_memcpy(self->tail, &tmp, 8);
    self->f37C = keep;
}

struct Obj_146470;
struct Glob_146470 {
    u8 pad0[0x19D8];
    s32 f19D8;
    s32 f19DC;
};

extern Glob_146470* D_002623C0;
extern u8 D_00261420[];
void func_00124A48(void* a);
void* func_0015A838(void* a, s32 b, s32 c, void* d);
s32 func_00141008(void* a, s32 b);

struct Obj_146470 {
    void** vtbl;
    u8 pad04[0x10];
    void* f14;
    u8 pad18[0x2D8 - 0x18];
    s32 f2D8;
    u8 pad2DC[0x2EC - 0x2DC];
    void* f2EC;
    u8 pad2F0[0x37C - 0x2F0];
    s32 f37C;
};

void func_00146470(Obj_146470* self)
{
    func_00124A48(self);
    void* r = func_0015A838(self->f14, 1, 0x75, self);
    self->f2EC = r;
    if (r != 0) {
        ((void (*)(void*))((void**)*(void***)r)[7])(r);
    }
    Glob_146470* g = D_002623C0;
    if (((g->f19D8 << 8) | g->f19DC) != 0x308) {
        if (func_00141008(D_00261420, self->f37C)) {
            self->f2D8 = 2;
        }
    }
    ((void (*)(void*, s32))self->vtbl[51])(self, self->f2D8);
}

struct Obj_1473E0;
struct Other_1473E0 {
    u8 pad0[0xC];
    s32 fC;
};
struct Obj_1473E0 {
    void** vtbl;
    u8 pad04[0x340 - 4];
    s32 f340;
};

s32 func_001473E0(Obj_1473E0* self, Other_1473E0* b)
{
    if (self->f340 != 0) {
        if (b->fC & 0x10) {
            ((void (*)(void*, s32))self->vtbl[51])(self, 1);
        }
    }
    return 1;
}

struct Obj_147ED0 {
    void** vtbl;
};

void func_00147ED0(Obj_147ED0* self)
{
    ((void (*)(void*, s32))self->vtbl[51])(self, 2);
}

extern s32 D_00270458;
extern f32 D_00261860;
void func_00147428(void* a);

void func_00147FB0(void* self)
{
    func_00147428(self);
    if (*(s32*)((u8*)self + 0x2D0) != 0) return;
    if (*(void**)((u8*)self + 0x338) == 0) return;
    if (D_00270458 != 2) {
        *(f32*)((u8*)self + 0x398) = *(f32*)((u8*)self + 0x398) - D_00261860;
    }
    if (*(f32*)((u8*)self + 0x398) <= 0.0f) {
        void** vt = *(void***)self;
        ((void (*)(void*, s32))vt[51])(self, 6);
    }
}

struct Obj_146130 {
    u8 pad0[0x554];
    f32 f554;
    f32 f558;
};

void func_001BAC30(void* self, void* p);
f32 func_00137DF8(void* p);

void func_00146130(void* self, void* p)
{
    Obj_146130* o = (Obj_146130*)self;
    func_001BAC30(self, p);
    o->f554 = func_00137DF8(p);
    o->f558 = func_00137DF8(p);
}

void func_00124A48(void* self);
void func_00146298(void* self);

void func_00146178(void* self)
{
    func_00124A48(self);
    func_00146298(self);
}

struct Obj_146240 {
    u8 pad0[0x14];
    void* p14;
    u8 pad1[0x538];
    f32 f550;
};

void func_00138BE0(void* a, void* self, s32 n);
void func_00146298(void* self);
void func_00129DF8(void* self);

void func_00146240(void* self, f32 v)
{
    Obj_146240* o = (Obj_146240*)self;
    if (v != o->f550) {
        o->f550 = v;
        func_00138BE0(o->p14, o, 7);
        func_00146298(o);
        func_00129DF8(o);
    }
}
