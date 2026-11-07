// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x146100 to 0x149398 (its .rodata from 0x249E50, its .data from 0x2619A0):
// class 0x39's methods (0x146100 to 0x146340), then class 0x55 and the classes 0x56 to 0x5B
// derived from it, with their helpers. Its name is ours, after the state notifiers it
// holds most of.
#include "common.h"
#include "asm_func.h"
#include "state_notifier.h"
#include "world.h"
#include "scaled_offset_object.h"
#include "game_progress.h"
#include "object_link.h"
#include "switched_collider.h"
#include "camera.h"
#include "effect.h"
#include "screen_element.h"
#include "font.h"
#include "flag_table.h"

void func_0012AA28(void* a, s32 b);
void func_001289C0(void* a, void* b);
void func_00124DF8(void* a, s32 b, void* c);
void func_00127048(void* a, void* b);
extern u8 D_00261420[];
void func_00124A48(void* a);
void* func_0015A838(void* a, s32 b, s32 c, void* d);
s32 func_00141008(void* a, s32 b);

extern s32 D_00270458;
extern f32 D_00261860;
void func_001BAC30(Collider* self, void* p);
f32 func_00137DF8(void* p);
void func_00124A48(void* self);
void func_00146298(ScaledOffsetObject* self);
void func_00138BE0(World* a, void* self, s32 n);
void func_00129DF8(void* self);
void func_001B7968(Collider* self);
void func_00127378(void* self, s32 kind, void* msg);
void func_001B6598(void* sub, s32* out);
void* func_001DBCC8(void* owner, void* fn, void* ctx, s32 a3, s32 a4);
void func_00147ED0(void* self);

// What a notifier tells the world's object (World::f1D60, its slot 27) or its listener (slot 31)
// when it fires: the state and itself.
struct StateMessage {
    s32 state;              // 0x00
    void* sender;           // 0x04
};

// The frame of a notifier's message handler (func_00147EF8, func_00148770, func_00148E40): the
// message it sends, and the code func_001B6598 gives it at 0x50.
struct NotifyFrame {
    StateMessage note;      // 0x00
    u8 pad08[0x50 - 0x08];
    s32 code;               // 0x50
    u8 pad54[0x60 - 0x54];
};

// The 0x50-byte message a notifier sends its listener's slot 31 (func_00148298, func_00148888,
// func_00148FF0): the new state and the sender.
struct ListenerMessage {
    s32 state;              // 0x00
    void* sender;           // 0x04
    u8 pad08[0x50 - 0x08];
};

s32 func_001300E8(void* node, s32 kind);
extern u8 D_00261420[];
void func_00123ED0(StateNotifier* self);
void func_00152470(List01* list, StateNotifier* item);
s32 func_00140FF8(FlagTable* p);

struct __attribute__((packed)) PSys_1481A0 {
    u8 pad0[0x26C];
    f32 f26C;
};

void func_00148038(World* self);
void func_00148178(void);
s32 func_00160D98(void);
typedef void (*VFn_148CE0)(void* self, s32 arg);

struct Node_148CE0 {
    VFn_148CE0* vtbl;
    u8 pad0[0x374 - 4];
    Node_148CE0* next;
};

extern s32 D_0026EC58;
s32 func_001300E8(void* node, s32 kind);
SwitchedCollider* func_001925F0(void);
typedef void (*VFn3_148598)(void* self, s32 a, void* b);

struct VObj3_148598 {
    VFn3_148598* vtbl;
};

extern s32 D_00275C34;
extern u8 D_00261EF0[];
extern u8 D_00264A40[];
void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_00151FC8(void* p);
void func_0018C7F8(void* p);
extern void* D_0026EC68;
void func_00127378(void* self, s32 kind, void* msg);
void func_001B6598(void* dev, s32* out);
void* func_001DBCC8(void* target, void* fn, void* ctx, s32 a, s32 b);

extern f32 D_0026185C;
void func_00152470(void* table, void* self);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_001E02C8(T217D_1380* self, s32 n);

void func_00127378(void* self, s32 kind, void* msg);
void func_001B6598(void* dev, s32* out);
void* func_001DBCC8(void* target, void* fn, void* ctx, s32 a, s32 b);
void func_00148E18(void* self);

extern s32 D_00270458;
extern f32 D_00261860;

extern void* D_00261B60[28];
extern u8 D_00261420[];
f32 func_001EAAE0(f32 a, f32 b);
Effect* func_0019EA78(s32 kind, EffectOwner* sys);
void func_00141040(void* table, s32 v);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00148F80(void* self);

void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
extern u8 D_0026EC60[];

extern u8 D_00261990[];
extern u8 D_002483D0[];
struct Obj_148AC0;

struct Vt_148AC0 {
    u8 pad00[0x18];
    void (*f18)(Obj_148AC0* self);
    u8 pad1C[0x64 - 0x1C];
    void (*f64)(Obj_148AC0* self, s32 a);
    u8 pad68[0x84 - 0x68];
    void (*f84)(Obj_148AC0* self, s32 a);
    void (*f88)(Obj_148AC0* self, void* a);
    u8 pad8C[4];
    void (*f90)(Obj_148AC0* self, void* a);
    void (*f94)(Obj_148AC0* self, void* a);
    u8 pad98[0xCC - 0x98];
    void (*fCC)(Obj_148AC0* self, s32 a);
};

struct Obj_148AC0 {
    Vt_148AC0* vt;
    u8 pad04[0x88 - 0x04];
    u8 f88[0x2A8 - 0x88];
    f32 f2A8;
    u8 pad2AC[0x2E0 - 0x2AC];
    f32 f2E0;
    u8 pad2E4[0x33C - 0x2E4];
    s32 f33C;
};

extern u8 D_002483D0[];
extern u8 D_00248D30[];
extern f32 D_00261B40;
void func_0018D608(void);
Obj_148AC0** func_0018D658(s32 size);
s32 func_00148938(World* self, s32 a1, s32 n, Obj_148AC0** arr);
f32 func_001EAAE0(f32 a, f32 b);
void func_001ED650(void* out, f32 x, f32 y, f32 z);
void func_001EEB60(World* a, f32 f, void* b, void* c);
void func_0018D6F0(void);

struct Obj_148038 {
    void** vtbl;
    u8 pad0[0x2A8 - 4];
    f32 f2A8;
};

struct __attribute__((aligned(16))) Quad_148038 {
    s32 a, b, c, d;
};

struct Ctx_148038;
typedef void (*Fn0_148038)(void* self);
typedef void (*Fn1_148038)(void* self, void* a);
typedef void (*Fn1s_148038)(void* self, s32 a);
extern f32 D_00261AB0[4];
extern u8 D_002483D0[];
extern u8 D_00248D30[];
extern Quad_148038 D_00261AC0;
s32 func_00148938(World* self, s32 a1, s32 a2, void** out);
s32 func_00160D98(void);
void func_00144128(Ctx_148038* a, void* b, void* c);
s32 func_001EEB60(Ctx_148038* self, f32 x, void* vec, void* out);

extern void* D_00261AD0[28];
Effect* func_0019EA78(s32 kind, EffectOwner* sys);
void func_001481A0(void* self);
f32 func_001EAAE0(f32 a, f32 b);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

ObjectLink D_002619A0[5] = {

    { 0, 0x25F, 0x2E4 },
    { 2, 0x25B, 0x324 },
    { 2, 0x25C, 0x328 },
    { 2, 0x25E, 0x380 },
    { 2, 0x25D, 0x384 },
};
f32 D_002619DC = -5.0f;
f32 D_002619E0 = 0.25f;
f32 D_002619E4 = 1.0f;
f32 D_002619E8 = 0.25f;
f32 D_002619EC = 5.0f;
f32 D_002619F0[4] = { 0.0f, 0.0f, -2250.0f, 0.0f };
f32 D_00261A00[4] = { 0.0f, 75.0f, 85.0f, 0.0f };
f32 D_00261A10[4] = { 10.0f, 0.0f, 0.25f, 0.0f };
f32 D_00261A20[12] = { 20.0f, 5.0f, 0.150000006f, 120.0f, 800.0f, 50.0f, 0.25f, 4500.0f, 800.0f, 50.0f, 0.25f, 4500.0f };
f32 D_00261A50 = 300.0f;
INCLUDE_DATA(D_00261A54);
f32 D_00261A60[4] = { 1.0f, 1.0f, 0.0f, 0.0f };
f32 D_00261A70[4] = { -250.0f, 0.0f, 600.0f, 0.0f };
f32 D_00261A80[4] = { 1.0f, -0.300000012f, 0.0f, 0.0f };
f32 D_00261A90[4] = { 0.699999988f, -0.400000006f, 0.0f, 0.0f };
f32 D_00261AA0[4] = { 0.0f, 800.0f, 1200.0f, 0.0f };
f32 D_00261AB0[4] = { -0.6f, 0.85f, 300.0f, 0.0f };
Quad_148038 D_00261AC0 = { 0x40A00000, (s32)0xC3FA0000, 0, 0 };
void* D_00261AD0[28] = {
    (void*)0xBF59999A, (void*)0x3F4CCCCD, (void*)0x42C80000, 0,
    (void*)0xBF800000, (void*)0xBF800000, 0, 0,
    (void*)0xBF800000, (void*)0x40000000, 0, 0,
    (void*)0x3F800000, (void*)0x40400000, 0, 0,
    0, 0, (void*)0x3F800000, 0,
    (void*)0x3F800000, (void*)0xBF4CCCCD, 0, 0,
    (void*)CountPickupTowardHundred, 0, 0, 0
};
f32 D_00261B40 = 0.05f;
f32 D_00261B48[2] = { 75.0f, 1e+02f };
f32 D_00261B50[4] = { 1e+03f, 1.3e+03f, 0.0f, 0.0f };
void* D_00261B60[28] = {
    (void*)0xBD4CCCCD, (void*)0x3F4CCCCD, (void*)0x42C80000, 0,
    (void*)0xBF800000, (void*)0xBF800000, 0, 0,
    (void*)0xBF800000, (void*)0x40000000, 0, 0,
    (void*)0x3F800000, (void*)0x40400000, 0, 0,
    0, 0, (void*)0x3F800000, 0,
    (void*)0x3F800000, (void*)0xBF4CCCCD, 0, 0,
    (void*)(void (*)(void))AddReserveUnitNow, 0, 0, 0
};
f32 D_00261BD0[4] = { 0.0f, 0.0f, 200.0f, 0.0f };
f32 D_00261BE0 = 0.75f;
INCLUDE_DATA(D_00261BE4);

void func_00146100(ScaledOffsetObject* self)
{
    InitCollider(self);
    self->scale = 100.0f;
}

void func_00146130(ScaledOffsetObject* self, void* p)
{
    LoadCollider(self, p);
    self->factorX = ReadBufferedFloat(p);
    self->factorY = ReadBufferedFloat(p);
}

void func_00146178(ScaledOffsetObject* self)
{
    StartPlacedObject(self);
    ApplyScaledOffset(self);
}

ASM_FUNC(func_001461A8);

void func_00146240(ScaledOffsetObject* self, f32 v)
{
    if (v != self->scale) {
        self->scale = v;
        ClearRootObjectStateBits(self->world, self, 7);
        ApplyScaledOffset(self);
        func_00129DF8(self);
    }
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

void func_00146340(StateNotifier* self)
{
    self->initialMode = 0;
    self->f388 = 30.0f;
    self->state = self->f2DC = -1;
    InitPlacedObject(self);
    AppendToList(&self->world->list1C54, self);
    s32 v = TakeFlagTableIndex((FlagTable*)g_flagTable);
    self->f37C = v;
    self->tint[2] = 0x10;
    self->tint[1] = 0x10;
    self->tint[0] = 0x10;
    self->tint[3] = 0x10;
    self->armed = 1;
}

void func_001463C0(StateNotifier* self, void* arg)
{
    func_0012AA28(self, 1);
    LoadPlacedObject(self, arg);
    ResolveObjectLinks(self, 5, g_stateNotifierLinks);
}

void func_00146418(StateNotifier* self, void* arg)
{
    s32 keep = self->f37C;
    u64 tmp;
    __builtin_memcpy(&tmp, self->tail374, 8);
    CopyPlacedObject(self, arg);
    __builtin_memcpy(self->tail374, &tmp, 8);
    self->f37C = keep;
}

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

ASM_FUNC(func_00146518);

s32 func_00146D10(void* unused, Collider* self)
{
    u64 bit = 0x8000;
    bit <<= 28;
    if (self->flags538 & bit) {
        return 0;
    }
    if (IsObjectOfKind(self->root, 5) != 0 || IsObjectOfKind(self->root, 0x27) != 0 ||
        IsObjectOfKind(self->root, 0x3B) != 0 || IsObjectOfKind(self->root, 0x40) != 0 ||
        IsObjectOfKind(self->root, 0x2E) != 0) {
        return 0;
    }
    return 1;
}

ASM_FUNC(func_00146DB0);

ASM_FUNC(func_001471B0);

s32 func_001473E0(StateNotifier* self, ContactObject* b)
{
    if (self->armed != 0) {
        if (b->fC & 0x10) {
            self->desc02()->m2F(self, 1);
        }
    }
    return 1;
}

INCLUDE_RODATA(jtbl_00249E50);

ASM_FUNC(func_00147428);

ASM_FUNC(func_001478F0);

INCLUDE_RODATA(jtbl_00249E70);

ASM_FUNC(func_00147AB0);

void func_00147E40(TimeRangeNotifier* self)
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

void func_00147ED0(TimeRangeNotifier* self)
{
    self->desc02()->m2F(self, 2);
}

void func_00147EF8(TimeRangeNotifier* self, s32 kind, void* target)
{
    NotifyFrame fr;
    HandlePlacedObjectNotification(self, kind, target);
    if (kind != 0x14) return;
    if (target != self->f2E8) return;
    func_001B6598(target, &fr.code);
    if (fr.code != 0x263) return;
    BaseObject* obj = self->world->f1D60;
    if (obj != 0) {
        fr.note.state = 1;
        fr.note.sender = self;
        obj->desc->m1B(obj, &fr.note);
    }
    AppendQueuedCall(self->world, (void*)(void (*)(void*))CompleteTimeRangeNotifier, self, 0, 0);
}

void func_00147FB0(TimeRangeNotifier* self)
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

void func_00148038(World* self)
{
    void* obj;
    s32 buf[4];
    GameProgress* g;
    s32 n;
    s32 c;

    if (GatherObjectsOfKind(self, 0x56, 1, &obj) == 0) {
        g = g_saveData;
        n = GetSpareCountLimit();
        c = g->f19E4 + 1;
        c = (c < n) ? c : n;
        g_saveData->f19E4 = c;
    } else {
        ((Fn0_148038)((Obj_148038*)obj)->vtbl[6])(obj);
        ((Fn1s_148038)((Obj_148038*)obj)->vtbl[25])(obj, 0);
        func_00144128(*(Ctx_148038**)g_camera, (void*)D_00261AB0, buf);
        ((Fn1_148038)((Obj_148038*)obj)->vtbl[33])(obj, buf);
        ((Fn1_148038)((Obj_148038*)obj)->vtbl[34])(obj, g_identityMatrix);
        ((Fn1_148038)((Obj_148038*)obj)->vtbl[36])(obj, D_00248D30);
        ((Fn1_148038)((Obj_148038*)obj)->vtbl[37])(obj, D_00248D30);
        ((Fn1s_148038)((Obj_148038*)obj)->vtbl[51])(obj, 4);
        *(Quad_148038*)((u8*)obj + 0x300) = D_00261AC0;
        func_001EEB60((Ctx_148038*)self->f1EC4, ((Obj_148038*)obj)->f2A8, (u8*)obj + 0x140, (u8*)obj + 0x88);
    }
}

void func_00148178(void)
{
    GameProgress* g = g_saveData;
    s32 r = 99;
    if (g->f19E0 + 1 <= 98) r = g->f19E0 + 1;
    g->f19E0 = r;
}

void func_001481A0(void* self)
{
    Effect* s = (Effect*)self;
    GameProgress* g = g_saveData;
    s32 c = g->f19E8 + 1;
    s32 r;
    g->f19E8 = c;
    if (c >= 100) {
        r = GetSpareCountLimit();
        if (g->f19E4 < r) {
            g_saveData->f19E8 = 0;
            ((PSys_1481A0*)&D_0026CE48)->f26C = 250.0f;
            D_0026CE48.onDone = (void (*)(void*))PlaceSpareSoundNotifier;
            D_0026CE48.doneArg = s->prev;
            return;
        }
        if (g_saveData->f19E0 < 99) {
            g_saveData->f19E8 = 0;
            D_0026CE48.rate = 250.0f;
            D_0026CE48.doneArg = 0;
            D_0026CE48.onDone = (void (*)(void*))AddReserveUnit;
            {
                D_0026C6C8.vt->m14(&D_0026C6C8);
            }
        } else {
            g_saveData->f19E8 = 99;
        }
    }
}

void func_00148298(TimeRangeNotifier* self, s32 mode)
{
    TimeRangeNotifier* s = self;
    if (s->state != mode) {
        switch (mode) {
        case 0:
            if (s->f338 != 0) {
                s->timeLeft = RandomFloatInRange(s->timeMin, s->timeMax);
            }
            break;
        case 1:
                Effect* n = CreateEffect(0x10, 0);
                if (n != 0) {
                    n->params = (const T219C_Params*)D_00261AD0;
                    n->p134 = self;
                    n->vt->m00(n, &s->v140, 1.0f, 0);
                    n->p20 = self;
                    n->rot50[0] = s->m110.r[0];
                    n->rot50[1] = s->m110.r[1];
                    n->rot50[2] = s->m110.r[2];
                } else {
                    CountPickupTowardHundred(self);
                }
                D_0026CE48.vt->m14(&D_0026CE48);
                f32 z = 0.0f;
                StartSoundEffect(0x78, 0, 0, 0, 3000.0f, 300.0f, 1.0f, z, z, 0, 0);
                if (s->listener != 0) {
                    ListenerMessage msg;
                    msg.state = 1;
                    msg.sender = self;
                    s->listener->vtbl[31](s->listener, &msg);
                }
                mode = 2;
            break;
        }
        SetStateNotifierState(self, mode);
    }
}

void func_00148400(SoundNotifier* self)
{
    SoundNotifier* o = self;
    InitStateNotifier(o);
    f32 k60 = 60.0f;
    f32 k300 = 300.0f;
    f32 k075 = 0.75f;
    f32 k05 = 0.5f;
    f32 k035 = 0.35f;
    o->f320 = k035;
    o->f344 = k300;
    o->f358 = k075;
    o->f354 = k05;
    o->f34C = k60;
    o->i348 = 0;
    o->f350 = k60;
}

void func_00148470(SoundNotifier* self, s32 mode)
{
    if (self->state == mode) return;
    if (mode == 1) {
        StartSoundEffect(0x74, 0, (s32)self, 0, 0, 0, 1500.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        mode = 4;
        TriggerScriptEvent(self, 2, 0, 0);
    }
    SetStateNotifierState(self, mode);
}

void func_00148510(SaveNotifier* self)
{
    SaveNotifier* o = self;
    InitStateNotifier(o);
    f32 k35 = 35.0f;
    f32 k06 = 0.6f;
    f32 k500 = 500.0f;
    f32 k250 = 250.0f;
    f32 k075 = 0.75f;
    G27C230* fl = g_currentEntry;
    o->f350 = o->f34C = k35;
    o->f344 = k500;
    o->f348 = k250;
    o->f354 = o->f358 = k06;
    o->f320 = k075;
    if (fl->flags & 2) {
        o->initialMode = 2;
    }
}

void func_00148598(SaveNotifier* self, s32 mode)
{
    if (self->state == mode) return;
    if (mode == 1) {
        G27C230* fl = g_currentEntry;
        s32 bits = fl->flags;
        if ((bits & 2) == 0) {
            G27C230* cx = g_currentLevelRecord;
            fl->flags = bits | 2;
            s32 g = D_00275C34; s32 old = cx->f438; cx->f438 = old + 1; if (g != 0) cx->f438 = old;
        }
        D_0026CBC8.vt->m14(&D_0026CBC8);
        void* r = (void*)GetActiveSwitchedCollider();
        if (r != 0) {
            ((VObj3_148598*)r)->vtbl[82](r, 0, self);
        }
        TriggerScriptEvent(self, 2, 0, 0);
        mode = 2;
        ResetScatterLevels(g_scatterController);
        StartMemoryCardSave(g_memoryCard);
    }
    SetStateNotifierState(self, mode);
}

void func_00148698(DeadlineNotifier* self)
{
    InitStateNotifier(self);
    self->f34C = 60.0f;
    self->f350 = 60.0f;
    self->f344 = 500.0f;
    self->f358 = 0.6f;
    self->f348 = 250.0f;
    self->f354 = 0.6f;
    self->f320 = 0.75f;
    if (*(s32*)D_0026EC60 == 0) {
        self->initialMode = 2;
    }
}

void func_00148718(DeadlineNotifier* self)
{
    StartStateNotifier(self);
    g_deadlineNotifier = self;
}

void func_00148748(DeadlineNotifier* self)
{
    self->desc02()->m2F(self, 2);
}

void func_00148770(DeadlineNotifier* self, s32 kind, void* msg)
{
    NotifyFrame fr;
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind != 0x14) return;
    if (msg != self->f2E8) return;
    func_001B6598(msg, &fr.code);
    if (fr.code != 0x263) return;
    BaseObject* dev = self->world->f1D60;
    if (dev != 0) {
        fr.note.state = 1;
        fr.note.sender = self;
        dev->desc->m1B(dev, &fr.note);
    }
    AppendQueuedCall(self->world, (void*)CompleteDeadlineNotifier, self, 0, 0);
}

void func_00148828(DeadlineNotifier* self)
{
    UpdateStateNotifier(self);
    if (self->state != 0) return;
    if (self->world->f2308 <= g_gameTime) self->desc02()->m2F(self, 6);
}

void func_00148888(DeadlineNotifier* self, s32 mode)
{
    ListenerMessage msg;
    if (self->state == mode) return;
    if (mode == 1) {
        SetBestTimeState(&g_timerCaption, 2);
        StateListener* dev = self->listener;
        if (dev != 0) {
            msg.state = mode;
            msg.sender = self;
            dev->vtbl[31](dev, &msg);
        }
        mode = 2;
    }
    SetStateNotifierState(self, mode);
}

s32 func_00148910(const f32* first, const f32* second)
{
    s32 result = -1;
    if (*first < *second) result = 1;
    return result;
}

INCLUDE_RODATA(D_00249E90);

ASM_FUNC(func_00148938);

s32 func_00148AC0(World* self, s32 a1, s32 a2, s32 n, Obj_148AC0** arr)
{
    Obj_148AC0** p;
    s32 i;
    s32 count;
    f32 ang;
    f32 step;
    PushBackMemoryMark();
    if (arr == 0) {
        arr = AllocateBackMemory(n * 4);
    }
    count = GatherObjectsOfKind(self, a1, n, arr);
    i = 0;
    step = 6.2831855f / (f32)n;
    ang = RandomFloatInRange(0.0f, 6.2831855f);
    {
        for (; i < count;) {
            Obj_148AC0* o = arr[i];
            u8* q = (u8*)o + 0x300;
            f32 a;
            f32 b;
            o->vt->f18(o);
            o->vt->f64(o, 0);
            o->vt->f84(o, a2);
            o->vt->f88(o, g_identityMatrix);
            o->vt->f90(o, D_00248D30);
            o->vt->f94(o, D_00248D30);
            o->f2E0 = (f32)i * D_00261B40;
            o->f33C = 0;
            i++;
            o->vt->fCC(o, 3);
            a = RandomFloatInRange(D_00261B48[0], D_00261B48[1]);
            b = RandomFloatInRange(D_00261B50[0], D_00261B50[1]);
            ComputePolarOffset(q, ang, a, b);
            ang += step;
            func_001EEB60((World*)self->f1EC4, o->f2A8, (u8*)o + 0x140, (u8*)o + 0x88);
        }
    }
    PopBackMemoryMark();
    return count;
}

void func_00148CE0(World* self)
{
    GameProgress* g = g_saveData;
    if (((g->f19D8 << 8) | g->f19DC) == 0x308) return;
    s32 r = GetSpareCountLimit();
    if (g->f19E4 < r) {
        if (D_0026EC58 < 2) return;
    }
    Node_148CE0* p = (Node_148CE0*)self->list1C54.head;
    if (p == 0) return;
    do {
        if (IsObjectOfKind(p, 0x56) != 0) {
            p->vtbl[51](p, 2);
        }
        p = p->next;
    } while (p != 0);
}

void func_00148D90(CountdownNotifier* self)
{
    InitStateNotifier(self);
    f32 k = 50.0f;
    self->f34C = 45.0f;
    self->f344 = 250.0f;
    self->f348 = self->f350 = k;
    self->f358 = 0.05f;
    self->f354 = 0.5f;
    self->timeMin = 4.0f;
    self->i320 = 0;
    self->timeMax = 6.0f;
}

void func_00148E18(CountdownNotifier* self)
{
    self->desc02()->m2F(self, 2);
}

void func_00148E40(CountdownNotifier* self, s32 kind, void* msg)
{
    NotifyFrame fr;
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind != 0x14) return;
    if (msg != self->f2E8) return;
    func_001B6598(msg, &fr.code);
    if (fr.code != 0x263) return;
    BaseObject* dev = self->world->f1D60;
    if (dev != 0) {
        fr.note.state = 1;
        fr.note.sender = self;
        dev->desc->m1B(dev, &fr.note);
    }
    AppendQueuedCall(self->world, (void*)(void (*)(void*))CompleteCountdownNotifier, self, 0, 0);
}

void func_00148EF8(CountdownNotifier* self)
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

void func_00148F80(void)
{
    T217D_E30* obj = &D_0026C6C8;
    obj->vt->m14(obj);
    GameProgress* g = g_saveData;
    if (g->f19E0 < 0x63) {
        g->f19E0 = g->f19E0 + 1;
        obj->rate = 250.0f;
        obj->onDone = 0;
        obj->doneArg = 0;
    } else {
        g->f19E0 = 0x63;
    }
}

void func_00148FF0(CountdownNotifier* self, s32 mode)
{
    if (self->state == mode) return;
    if (mode == 0) goto zero_case;
    if (mode == 1) goto one_case;
    goto call_tail;

zero_case:
    if (self->f338 != 0) {
        self->timeLeft = RandomFloatInRange(self->timeMin, self->timeMax);
    }
    goto call_tail;

one_case:
    {
        Effect* c = CreateEffect(0x10, 0);
        if (c != 0) {
            c->p134 = self;
            c->params = (const T219C_Params*)D_00261B60;
            c->vt->m00(c, &self->v140, 1.0f, 0);
            c->p20 = self;
            c->rot50[0] = self->m110.r[0];
            c->rot50[1] = self->m110.r[1];
            c->rot50[2] = self->m110.r[2];
        } else {
            AddReserveUnitNow(self);
        }
        D_0026C6C8.vt->m14(&D_0026C6C8);
        SetFlagTableBit(g_flagTable, self->f37C);
        StartSoundEffect(0x69, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        if (self->listener != 0) {
            ListenerMessage fr;
            fr.state = 1;
            fr.sender = self;
            self->listener->vtbl[31](self->listener, &fr);
        }
        mode = 2;
    }

call_tail:
    SetStateNotifierState(self, mode);
}

void func_00149168(ArmedStateNotifier* self)
{
    InitStateNotifier(self);
    self->armed = 0;
}

ASM_FUNC(func_00149190);

