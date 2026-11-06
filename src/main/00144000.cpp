// SPDX-License-Identifier: AGPL-3.0-or-later
#include "state_notifier.h"
#include "world.h"
#include "scaled_offset_object.h"
#include "game_progress.h"
#include "object_link.h"

void func_0012AA28(void* a, s32 b);
void func_001289C0(void* a, void* b);
void func_00124DF8(void* a, s32 b, void* c);

void func_001463C0(StateNotifier* self, void* arg)
{
    func_0012AA28(self, 1);
    LoadPlacedObject(self, arg);
    ResolveObjectLinks(self, 5, g_stateNotifierLinks);
}

void func_00127048(void* a, void* b);

void func_00146418(StateNotifier* self, void* arg)
{
    s32 keep = self->f37C;
    u64 tmp;
    __builtin_memcpy(&tmp, self->tail374, 8);
    CopyPlacedObject(self, arg);
    __builtin_memcpy(self->tail374, &tmp, 8);
    self->f37C = keep;
}


extern u8 D_00261420[];
void func_00124A48(void* a);
void* func_0015A838(void* a, s32 b, s32 c, void* d);
s32 func_00141008(void* a, s32 b);

void func_00146470(StateNotifier* self)
{
    StartPlacedObject(self);
    void* r = FindFirstObjectByIdGathered(self->world, 1, 0x75, self);
    self->f2EC = r;
    if (r != 0) {
        ((void (*)(void*))((void**)*(void***)r)[7])(r);
    }
    GameProgress* g = g_saveData;
    if (((g->f19D8 << 8) | g->f19DC) != 0x308) {
        if (TestFlagTableBit(g_flagTable, self->f37C)) {
            self->initialMode = 2;
        }
    }
    self->desc02()->m2F(self, self->initialMode);
}

s32 func_001473E0(StateNotifier* self, ContactObject* b)
{
    if (self->armed != 0) {
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
    UpdateStateNotifier(self);
    if (self->state != 0) return;
    if (self->f338 == 0) return;
    if (D_00270458 != 2) {
        self->timeLeft = self->timeLeft - g_frameDt;
    }
    if (self->timeLeft <= 0.0f) {
        self->desc02()->m2F(self, 6);
    }
}

void func_001BAC30(Collider* self, void* p);
f32 func_00137DF8(void* p);

void func_00146130(ScaledOffsetObject* self, void* p)
{
    LoadCollider(self, p);
    self->factorX = ReadBufferedFloat(p);
    self->factorY = ReadBufferedFloat(p);
}

void func_00124A48(void* self);
void func_00146298(ScaledOffsetObject* self);

void func_00146178(ScaledOffsetObject* self)
{
    StartPlacedObject(self);
    ApplyScaledOffset(self);
}

void func_00138BE0(World* a, void* self, s32 n);
void func_00129DF8(void* self);

void func_00146240(ScaledOffsetObject* self, f32 v)
{
    if (v != self->scale) {
        self->scale = v;
        ClearRootObjectStateBits(self->world, self, 7);
        ApplyScaledOffset(self);
        func_00129DF8(self);
    }
}

void func_001B7968(Collider* self);

void func_00146100(ScaledOffsetObject* self)
{
    InitCollider(self);
    self->scale = 100.0f;
}

void func_00127378(void* self, s32 kind, void* msg);
void func_001B6598(void* sub, s32* out);
void* func_001DBCC8(void* owner, void* fn, void* ctx, s32 a3, s32 a4);
void func_00147ED0(void* self);

struct Args_147EF8 { s32 flag; void* self; };

void func_00147EF8(C58* self, s32 kind, void* target)
{
    Args_147EF8 args;
    s32 code;
    u8 pad[0x40];
    HandlePlacedObjectNotification(self, kind, target);
    if (kind != 0x14) return;
    if (target != self->f2E8) return;
    func_001B6598(target, &code);
    if (code != 0x263) return;
    BaseObject* obj = self->world->f1D60;
    if (obj != 0) {
        args.flag = 1;
        args.self = self;
        obj->desc->m1B(obj, &args);
    }
    AppendQueuedCall(self->world, (void*)(void (*)(void*))func_00147ED0, self, 0, 0);
}


void func_00147E40(C58* self)
{
    InitStateNotifier(self);
    f32 k = 50.0f;
    self->f34C = 45.0f;
    self->f344 = 250.0f;
    self->f348 = self->f350 = k;
    self->f358 = 0.6f;
    self->f354 = 0.75f;
    self->f320 = 0.25f;
    self->timeMin = 8.0f;
    self->timeMax = 10.0f;
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
    if (IsObjectOfKind(self->list, 5) != 0 || IsObjectOfKind(self->list, 0x27) != 0 ||
        IsObjectOfKind(self->list, 0x3B) != 0 || IsObjectOfKind(self->list, 0x40) != 0 ||
        IsObjectOfKind(self->list, 0x2E) != 0) {
        return 0;
    }
    return 1;
}


void func_00146298(ScaledOffsetObject* self)
{
    for (s32 i = 0; i < self->elemCount; i++) {
        if (self->elems[i]->kind == 6) {
            Elem02* e = self->elems[i];
            e->x = -(self->scale * self->factorX);
            e->y = -(self->scale * self->factorY);
            break;
        }
    }
}

extern u8 D_00261420[];

struct Ptr_146340;

void func_00123ED0(StateNotifier* self);
void func_00152470(List01* list, StateNotifier* item);
s32 func_00140FF8(Ptr_146340* p);

void func_00146340(StateNotifier* self)
{
    self->initialMode = 0;
    self->f388 = 30.0f;
    self->state = self->f2DC = -1;
    InitPlacedObject(self);
    AppendToList(&self->world->list1C54, self);
    s32 v = TakeFlagTableIndex((Ptr_146340*)g_flagTable);
    self->f37C = v;
    self->tint[2] = 0x10;
    self->tint[1] = 0x10;
    self->tint[0] = 0x10;
    self->tint[3] = 0x10;
    self->armed = 1;
}

ObjectLink D_002619A0[5] = {

    { 0, 0x25F, 0x2E4 },
    { 2, 0x25B, 0x324 },
    { 2, 0x25C, 0x328 },
    { 2, 0x25E, 0x380 },
    { 2, 0x25D, 0x384 },
};

// Data of src/main/file_143140.cpp, defined here until the file's own data is proved.
