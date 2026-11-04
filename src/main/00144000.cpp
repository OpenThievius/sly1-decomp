// SPDX-License-Identifier: AGPL-3.0-or-later
#include "c55.h"
#include "c6c.h"
#include "c39.h"

struct Item_2619A0 { u32 flags, id, off8; };
extern Item_2619A0 D_002619A0[5];
void func_0012AA28(void* a, s32 b);
void func_001289C0(void* a, void* b);
void func_00124DF8(void* a, s32 b, void* c);

void func_001463C0(C55* self, void* arg)
{
    func_0012AA28(self, 1);
    func_001289C0(self, arg);
    func_00124DF8(self, 5, D_002619A0);
}

void func_00127048(void* a, void* b);

void func_00146418(C55* self, void* arg)
{
    s32 keep = self->f37C;
    u64 tmp;
    __builtin_memcpy(&tmp, self->tail374, 8);
    func_00127048(self, arg);
    __builtin_memcpy(self->tail374, &tmp, 8);
    self->f37C = keep;
}

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

void func_00146470(C55* self)
{
    func_00124A48(self);
    void* r = func_0015A838(self->world, 1, 0x75, self);
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
    self->desc02()->m2F(self, self->f2D8);
}

s32 func_001473E0(C55* self, Other55* b)
{
    if (self->f340 != 0) {
        if (b->fC & 0x10) {
            self->desc02()->m2F(self, 1);
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

void func_00147FB0(C58* self)
{
    func_00147428(self);
    if (self->state != 0) return;
    if (self->f338 == 0) return;
    if (D_00270458 != 2) {
        self->f398 = self->f398 - D_00261860;
    }
    if (self->f398 <= 0.0f) {
        self->desc02()->m2F(self, 6);
    }
}

void func_001BAC30(C03* self, void* p);
f32 func_00137DF8(void* p);

void func_00146130(C39* self, void* p)
{
    func_001BAC30(self, p);
    self->factorX = func_00137DF8(p);
    self->factorY = func_00137DF8(p);
}

void func_00124A48(void* self);
void func_00146298(C39* self);

void func_00146178(C39* self)
{
    func_00124A48(self);
    func_00146298(self);
}

void func_00138BE0(C6C* a, void* self, s32 n);
void func_00129DF8(void* self);

void func_00146240(C39* self, f32 v)
{
    if (v != self->scale) {
        self->scale = v;
        func_00138BE0(self->world, self, 7);
        func_00146298(self);
        func_00129DF8(self);
    }
}

void func_001B7968(C03* self);

void func_00146100(C39* self)
{
    func_001B7968(self);
    self->scale = 100.0f;
}

void func_00127378(void* self, s32 kind, void* msg);
void func_001B6598(void* sub, s32* out);
void func_001DBCC8(void* owner, void* fn, void* ctx, s32 a3, s32 a4);
void func_00147ED0(void* self);

struct Args_147EF8 { s32 flag; void* self; };

void func_00147EF8(C58* self, s32 kind, void* target)
{
    Args_147EF8 args;
    s32 code;
    u8 pad[0x40];
    func_00127378(self, kind, target);
    if (kind != 0x14) return;
    if (target != self->f2E8) return;
    func_001B6598(target, &code);
    if (code != 0x263) return;
    C01* obj = self->world->f1D60;
    if (obj != 0) {
        args.flag = 1;
        args.self = self;
        obj->desc->m1B(obj, &args);
    }
    func_001DBCC8(self->world, (void*)(void (*)(void*))func_00147ED0, self, 0, 0);
}


void func_00147E40(C58* self)
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
// The element list the object keeps in the common block (0x27C, 0x280).
struct List_146298 { s32 count; Elem_146298** list; };

void func_00146298(C39* self)
{
    for (s32 i = 0; i < ((List_146298*)((u8*)self + 0x27C))->count; i++) {
        if (((List_146298*)((u8*)self + 0x27C))->list[i]->tag == 6) {
            Elem_146298* e = ((List_146298*)((u8*)self + 0x27C))->list[i];
            e->x = -(self->scale * self->factorX);
            e->y = -(self->scale * self->factorY);
            break;
        }
    }
}

extern u8 D_00261420[];

struct Ptr_146340;

void func_00123ED0(C55* self);
void func_00152470(List01* list, C55* item);
s32 func_00140FF8(Ptr_146340* p);

void func_00146340(C55* self)
{
    self->f2D8 = 0;
    self->f388 = 30.0f;
    self->state = self->f2DC = -1;
    func_00123ED0(self);
    func_00152470(&self->world->list1C54, self);
    s32 v = func_00140FF8((Ptr_146340*)D_00261420);
    self->f37C = v;
    self->tint[2] = 0x10;
    self->tint[1] = 0x10;
    self->tint[0] = 0x10;
    self->tint[3] = 0x10;
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
