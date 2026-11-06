// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "fpu.h"
#include "globals.h"

extern f32 D_0026185C[];

typedef s32 (*VFn_C7B60)(void* self);
void func_001C8F20(Agent* self, s32 a1, s32 a2);

void func_001C7B60(Agent* self)
{
    if (self->fB84 != 0) return;
    if (self->fB88 != 0) return;
    if (g_player != 0 && g_player->f275C != 0) return;
    for (;;) {
        s32 v = ((VFn_C7B60*)self->desc)[0x174 / 4](self);
        if (v == self->f724) break;
        ChangeAgentState(self, v, 0);
    }
}

void func_001249A8(Agent* self);
s32 func_0015A448(s32 a, s32 b, Agent* self);
void func_001CAB10(Agent* self);
s32 func_0015A418(s32 a, s32 b, s32 c, Agent* self);
void func_00159478(s32* p, Agent* self);

void func_001C71E0(Agent* self)
{
    s32 v;
    PostLoadPlacedObject(self);
    if (self->f924 != -1) {
        self->f928 = func_0015A448((s32)self->world, self->f924, self);
    }
    if (self->fB4C != -1) {
        func_001CAB10(self);
    }
    v = self->fAF8;
    if (v != 0) {
        if (self->fAFC != -1) {
            self->fB00 = FindFirstObjectById((s32)self->world, 0x101, self->fAFC, self);
        }
    } else {
        FindOrBuildMemberGroup(&self->fB00, self);
    }
}

typedef s32 (*VFn_1C7278)(void* self);
struct Obj_1C7278 { VFn_1C7278* vtbl; };

s32 func_001C7278(Obj_1C7278* self)
{
    return self->vtbl[7](self);
}

void func_00192820(void* self);
void func_001CB648(void* list, void* value);

void func_001C74E8(Agent* self)
{
    RegisterSwitchedCollider(self);
    if (self->f720 != 0) {
        func_001CB648(self->f720, self);
    }
}

typedef void (*VFnSelf_1C72A0)(void* self, void* item, s32 flag);
void func_001C44F0(TurningCollider* self);
void func_00124DF8(void* self, s32 a1, u8* table);
void* func_001CB5B8(void* host);
void func_001CB648(void* a, void* b);
void func_001CA7C0(void* self);
void* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void* func_0015A838(void* host, s32 a1, s32 a2, void* ctx);
void func_001C5EA8(void* self, f32 v);
void func_001C8F20(void* node, s32 kind, s32 flag);
s32 func_00141008(u8* table, s32 v);
void* func_001DBCC8(void* host, void* fn, void* ctx, s32 a3, s32 a4);
extern s32 D_00274C30[8];
struct Ent_274AD8 { s32 a; s32 b; s32 c; };
extern Ent_274AD8 D_00274AD8[6];

extern u8 D_00261420[];

void func_001C72A0(Agent* self)
{
    StartTurningCollider(self);
    ResolveObjectLinks(self, 2, (u8*)D_00274C30);
    if (self->f720 == 0) {
        void* t = func_001CB5B8(self->world);
        self->f720 = t;
        func_001CB648(t, self);
    }
    ResolveAgentClips(self);
    for (s32 i = 0; i < 17; i++) {
        void* item = self->f870[i].obj;
        if (item != 0) {
            self->f6DC = item;
            self->f8F8 = item;
            ((VFnSelf_1C72A0*)self->desc)[0x38](self, item, 1);
            break;
        }
    }
    s32 j = 0;
    if (self->fA78 > 0) {
        u64 bit = 0x8000;
        bit <<= 28;
        Elem08* e = self->fA7C;
        do {
            Collider* o = (Collider*)FindFirstObjectById(self->world, 0x101, e->key, self);
            e->obj = o;
            if (o != 0) {
                o->flags538 |= bit;
                ((Collider*)e->obj)->desc->m03((Collider*)e->obj);
            }
            e++;
            j++;
        } while (j < self->fA78);
    }
    if (self->fB04 != 0) {
        if (self->fB08 != -1) {
            self->fB0C = FindFirstObjectById(self->world, 0x101, self->fB08, self);
        }
    } else {
        self->fB0C = FindFirstObjectByIdGathered(self->world, 0x101, 0x8C, self);
    }
    func_001C5EA8(self, self->f700);
    ChangeAgentState(self, 0, 0);
    if (TestFlagTableBit(g_flagTable, self->fB10)) {
        AppendQueuedCall(self->world, (void*)func_001C7278, self, 0, 0);
    }
}

void func_001921E8(Agent* self, s32 v);

void func_001C7188(Agent* self, s32 v)
{
    s32 b = self->fB10;
    s32 a = (s32)self->f720;
    CopySwitchedCollider(self, v);
    self->fB10 = b;
    self->f720 = (void*)a;
    self->fB74 = v;
}


s32 func_001CB578(void* self);
void func_001892A0(f32 a, f32 b, void* out);
void func_00188850(void* table, f32 x, void* out);

void func_001C7AE0(Agent* self, f32 x, f32 y)
{
    if (IsAgentFacingBlocked(self) != 0) return;
    s32 t = self->fB1C;
    self->f638 = x;
    self->fB24 = y;
    if (t != 0) {
        func_001892A0(x, y, (u8*)self + 0x660);
    } else {
        BuildAxisAngleMatrix((u8*)&g_unitZVector, x, (u8*)self + 0x660);
    }
}

s32 func_001B8A08(Agent* self, Collider* obj);
s32 func_001A8820(void* p, Collider* obj);

s32 func_001C7468(Agent* self, Collider* obj)
{
    if (TestCollidersMayContact(self, obj) != 0) {
        return 1;
    }
    if (self->fB0C != 0) {
        if (func_001A8820(self->fB0C, obj) != 0) {
            return 1;
        }
    }
    if (self->f724 == 0xB) {
        if ((obj->flags538 & ((u64)1 << 55)) == 0) {
            return 1;
        }
    }
    return 0;
}

extern f32 D_0024D654;

void func_00192850(Agent* self);
void func_0012E760(void* obj);
void func_001CB6F8(void* a, Agent* b);

void func_001C7520(Agent* self)
{
    UnregisterSwitchedCollider(self);
    if (self->f7E0 != 0) {
        StopAnimationPlayer(self->f7E0);
        self->f7E0 = 0;
    }
    if (self->f754 != 0) {
        StopAnimationPlayer(self->f754);
        self->f754 = 0;
    }
    if (self->f720 != 0) {
        func_001CB6F8(self->f720, self);
    }
    self->f72C = 0;
    self->fA60 = 0;
    self->f748 = 0;
    self->fBA4 = 0;
    self->fBF4 = D_0024D654;
    self->fBF8 = D_0024D654;
    self->fBFC = D_0024D654;
    self->fC00 = D_0024D654;
}

extern u8 D_00261420[];
extern const f32 D_0024D650 = 3.4028235e+38f;
void func_001C4458(TurningCollider* self);
struct Tbl_1C6F48;
s32 func_00140FF8(Tbl_1C6F48* p);
void func_00192990(Agent* self, s32 a);

#define F(T, o) (*(T*)((u8*)self + (o)))

void func_001C6F48(Agent* self)
{
    InitTurningCollider(self);
    f32 c300 = 300.0f;
    F(s32, 0x724) = -1;
    F(s32, 0x924) = -1;
    F(u64, 0x538) = (F(u64, 0x538) & ~((u64)0xF0 << 32)) | ((u64)1 << 37);
    F(f32, 0x73C) = c300;
    F(f32, 0x740) = 0.2f;
    F(f32, 0x744) = 0.5f;
    F(f32, 0x74C) = 0.17453294f;
    F(s32, 0x738) = 0;
    s32 i;
    for (i = 16; i >= 0; i--) F(s32, 0x758 + i * 8) = -1;
    f32* s3 = (f32*)((u8*)self + 0xB9C);
    f32* s4 = (f32*)((u8*)self + 0xBE0);
    s32 m = -1;
    for (i = 16; i >= 0; i--) F(s32, 0x870 + i * 8) = m;
    f32 one = 1.0f;
    s32 r = TakeFlagTableIndex((Tbl_1C6F48*)g_flagTable);
    s32 s1 = 1;
    s32 s0 = -1;
    F(s32, 0xB10) = r;
    F(u64, 0x538) = (F(u64, 0x538) & ~((u64)0xF0 << 32)) | ((u64)1 << 37);
    F(s32, 0xB14) = s1;
    F(s32, 0xB4C) = s0;
    F(f32, 0xB30) = one;
    F(s32, 0xB58) = s0;
    SetSwitchedColliderEnabled(self, 0);
    f32 d = D_0024D650;
    F(f32, 0x700) = 1.5f;
    F(f32, 0xB18) = -1.0f;
    F(f32, 0xB9C) = one;
    F(void*, 0xB74) = self;
    F(f32, 0xBFC) = d;
    F(f32, 0xC00) = d;
    F(u8, 0x2B3) = 0x20;
    s3[1] = 2.5f;
    F(s32, 0xBE0) = 0;
    s4[1] = 0.8f;
    F(s32, 0xBEC) = s0;
    F(f32, 0xBD0) = one;
    F(s32, 0xBD4) = s1;
    F(f32, 0xBE8) = 1.25f;
    F(s32, 0xBDC) = s1;
}

void func_001BAC30(Agent* self, void* a1);
void func_00124DF8(Agent* self, s32 a1, void* a2);
void func_001CA7C0(Agent* self);
void func_001CA8E8(Agent* self);
extern s32 D_00274C20[4];

void func_001C7140(Agent* self, void* a1)
{
    LoadCollider(self, a1);
    ResolveObjectLinks(self, 1, D_00274C20);
    ResolveAgentClips(self);
    ResolveAgentSecondaryClips(self);
}

s32 D_00274C20[4] = { 2, 0x195, 0x87C, 0 };
s32 D_00274C30[8] = { 2, 0x194, 0x750, 6, 0x50, 0x734, 0, 0 };
