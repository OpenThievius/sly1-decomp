// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Item_2619A0 { u32 flags, id, off8; };
extern Item_2619A0 D_002619A0[5];
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

struct Obj_00146100 {
    u8 pad_000[0x550];
    f32 value_550;
};

void func_001B7968(void* self);

void func_00146100(Obj_00146100* self)
{
    func_001B7968(self);
    self->value_550 = 100.0f;
}

void func_00127378(void* self, s32 kind, void* msg);
void func_001B6598(void* sub, s32* out);
void func_001DBCC8(void* owner, void* fn, void* ctx, s32 a3, s32 a4);
void func_00147ED0(void* self);

typedef void (*VFn_147EF8)(void* self, void* args);
struct Obj_147EF8 { VFn_147EF8* vtbl; };
struct Mid_147EF8 { u8 pad0[0x1D60]; Obj_147EF8* p1D60; };
struct Self_147EF8 {
    u8 pad0[0x14];
    Mid_147EF8* p14;
    u8 pad1[0x2D0];
    s32 f2E8;
};
struct Args_147EF8 { s32 flag; void* self; };

void func_00147EF8(Self_147EF8* self, s32 kind, void* target)
{
    Args_147EF8 args;
    s32 code;
    u8 pad[0x40];
    func_00127378(self, kind, target);
    if (kind != 0x14) return;
    if ((s32)target != self->f2E8) return;
    func_001B6598(target, &code);
    if (code != 0x263) return;
    Obj_147EF8* obj = self->p14->p1D60;
    if (obj != 0) {
        args.flag = 1;
        args.self = self;
        obj->vtbl[31](obj, &args);
    }
    func_001DBCC8(self->p14, (void*)(void (*)(void*))func_00147ED0, self, 0, 0);
}

void func_00146340(void* self);

struct Self_147E40 {
    u8 pad0[0x320];
    f32 f320;
    u8 pad1[0x20];
    f32 f344;
    f32 f348;
    f32 f34C;
    f32 f350;
    f32 f354;
    f32 f358;
    u8 pad2[0x34];
    f32 f390;
    f32 f394;
};

void func_00147E40(Self_147E40* self)
{
    func_00146340(self);
    f32 k = 50.0f;
    self->f34C = 45.0f;
    self->f344 = 250.0f;
    self->f348 = self->f350 = k;
    self->f358 = 0.6f;
    self->f354 = 0.75f;
    self->f320 = 0.25f;
    self->f390 = 8.0f;
    self->f394 = 10.0f;
}

struct Obj_146D10 {
    u8 pad0[0x50];
    void* list;
    u8 pad1[0x538 - 0x54];
    u64 flags;
};

s32 func_001300E8(void* node, s32 kind);

s32 func_00146D10(void* unused, Obj_146D10* self)
{
    u64 bit = 0x8000;
    bit <<= 28;
    if (self->flags & bit) {
        return 0;
    }
    if (func_001300E8(self->list, 5) != 0 || func_001300E8(self->list, 0x27) != 0 ||
        func_001300E8(self->list, 0x3B) != 0 || func_001300E8(self->list, 0x40) != 0 ||
        func_001300E8(self->list, 0x2E) != 0) {
        return 0;
    }
    return 1;
}

struct Elem_146298 { u8 pad0[8]; s32 tag; u8 pad1[0x20]; f32 x; f32 y; };
struct Obj_146298 { u8 pad0[0x27C]; s32 count; Elem_146298** list; u8 pad1[0x550 - 0x284]; f32 f550; f32 f554; f32 f558; };

void func_00146298(Obj_146298* self)
{
    for (s32 i = 0; i < self->count; i++) {
        if (self->list[i]->tag == 6) {
            Elem_146298* e = self->list[i];
            e->x = -(self->f550 * self->f554);
            e->y = -(self->f550 * self->f558);
            break;
        }
    }
}

extern u8 D_00261420[];

struct Lst_146340;
struct Self_146340;
struct Ptr_146340;

struct Self_146340 {
    u8 pad0[0x14];
    u8* f14;
    u8 pad18[0x2B0 - 0x18];
    u8 f2B0;
    u8 f2B1;
    u8 f2B2;
    u8 f2B3;
    u8 pad2B4[0x2D0 - 0x2B4];
    s32 f2D0;
    u8 pad2D4[0x2D8 - 0x2D4];
    s32 f2D8;
    s32 f2DC;
    u8 pad2E0[0x340 - 0x2E0];
    s32 f340;
    u8 pad344[0x37C - 0x344];
    s32 f37C;
    u8 pad380[0x388 - 0x380];
    f32 f388;
};

void func_00123ED0(Self_146340* self);
void func_00152470(Lst_146340* list, Self_146340* item);
s32 func_00140FF8(Ptr_146340* p);

void func_00146340(Self_146340* self)
{
    self->f2D8 = 0;
    self->f388 = 30.0f;
    self->f2D0 = self->f2DC = -1;
    func_00123ED0(self);
    func_00152470((Lst_146340*)(self->f14 + 0x1C54), self);
    s32 v = func_00140FF8((Ptr_146340*)D_00261420);
    self->f37C = v;
    self->f2B2 = 0x10;
    self->f2B1 = 0x10;
    self->f2B0 = 0x10;
    self->f2B3 = 0x10;
    self->f340 = 1;
}

Item_2619A0 D_002619A0[5] = {
    { 0, 0x25F, 0x2E4 },
    { 2, 0x25B, 0x324 },
    { 2, 0x25C, 0x328 },
    { 2, 0x25E, 0x380 },
    { 2, 0x25D, 0x384 },
};

// Data of src/main/file_143140.cpp, defined here until the file's own data is proved.
f32 D_002618A0 = 5e+02f;
f32 D_002618A4 = 2e+04f;
