// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "globals.h"
#include "item_keeper.h"
#include "c62.h"
#include "animation.h"
#include "attachment.h"

extern f32 D_0026185C[];

// A quadratic in t (c[0] + t * (c[1] + t * c[2])) on 16 bytes, as in file_1C3390: the file's
// .data starts on 16 (0x274C18 to 0x274C20 is padding after the previous file's), and 0x274C54
// to 0x274C5F is the quadratic's own.
void* func_001CA758(Agent* self, void* arg);
void* func_001CA758(Agent* self, s32 arg);

struct __attribute__((aligned(16))) Quad_1C6F48 { f32 c[3]; };

// The file's .data, in retail's order; its assembly reads the quadratics.
s32 D_00274C20[4] = { 2, 0x195, 0x87C, 0 };
s32 D_00274C30[8] = { 2, 0x194, 0x750, 6, 0x50, 0x734, 0, 0 };
Quad_1C6F48 D_00274C50 = { { 1.0f, -1.0f, 0.0f } };
Quad_1C6F48 D_00274C60 = { { 0.0f, 0.0f, 1.0f } };
Quad_1C6F48 D_00274C70 = { { 0.0f, 15.0f, 1.5f } };
Quad_1C6F48 D_00274C80 = { { 0.0f, 2.5f, 0.25f } };
float D_00274C90 = 40.0f;
float D_00274C94 = 50.0f;
float D_00274C98[2] = {0.5f, 0.0f};
Quad_1C6F48 D_00274CA0 = { { 1.0f, -0.00100000005f, 0.0f } };
Quad_1C6F48 D_00274CB0 = { { 0.25f, 1.0f, 0.0f } };
Quad_1C6F48 D_00274CC0 = { { 0.0f, 0.00499999989f, 0.0f } };
float D_00274CD0[2] = {0.0f, 1.0f};
float D_00274CD8[2] = {1.0f, 0.0f};
Quad_1C6F48 D_00274CE0 = { { 0.0f, 0.00499999989f, 0.0f } };
float D_00274CF0 = 0.349999994f;
f32 D_00274CF4 = 0.85f;
f32 D_00274CF8[1] = { 0 };
float D_00274CFC = 0.25f;
float D_00274D00 = 700.0f;
float D_00274D04 = 1200.0f;
f32 D_00274D08[2] = { 0.0f, 4.0f };
f32 D_00274D10[2] = { 0.0f, 1.5f };
f32 D_00274D18[2] = { 0.0f, 0.3f };
float D_00274D20[2] = {700.0f, 0.0f};
float D_00274D28[2] = {-0.200000003f, 0.200000003f};
Quad_1C6F48 D_00274D30 = { { 0.800000012f, 1.20000005f, 0.0f } };

extern u8 D_00261420[];
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
    f32 d = 3.4028235e+38f;
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

void func_001C7140(Agent* self, void* a1)
{
    LoadCollider(self, a1);
    ResolveObjectLinks(self, 1, D_00274C20);
    ResolveAgentClips(self);
    ResolveAgentSecondaryClips(self);
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
        self->f928 = FindFirstObjectByIdMode4((s32)self->world, self->f924, self);
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

typedef void (*VFnSelf_1C72A0)(void* self, void* item, s32 flag);
void func_001C44F0(TurningCollider* self);
void* func_001CB5B8(void* host);
void func_001CB648(void* a, void* b);
void func_001CA7C0(void* self);
void* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void* func_0015A838(void* host, s32 a1, s32 a2, void* ctx);
void func_001C5EA8(void* self, f32 v);
void func_001C8F20(void* node, s32 kind, s32 flag);
s32 func_00141008(u8* table, s32 v);
void* func_001DBCC8(void* host, void* fn, void* ctx, s32 a3, s32 a4);
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

void func_00192820(void* self);
void func_001CB648(void* list, void* value);

void func_001C74E8(Agent* self)
{
    RegisterSwitchedCollider(self);
    if (self->f720 != 0) {
        func_001CB648(self->f720, self);
    }
}


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
    self->fBF4 = 3.4028235e+38f;
    self->fBF8 = 3.4028235e+38f;
    self->fBFC = 3.4028235e+38f;
    self->fC00 = 3.4028235e+38f;
}

ASM_FUNC(func_001C75B0);

ASM_FUNC(func_001C7A60);

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

ASM_FUNC(func_001C7BE8);

ASM_FUNC(func_001C7CB8);

extern f32 D_00261858[];
s32 func_001C96B8(Agent* self);
s32 func_001C84C0(Agent* self);

s32 func_001C8010(Agent* self)
{
    s32 s = self->f724;
    s32 m = func_001C96B8(self);

    if (self->fBFC < g_gameClock[1]) {
        if (self->f724 != 0xB && self->f724 != 0x10) {
            if (self->f758[10].obj != 0) {
                s = 0xA;
                goto done;
            }
        }
    }

    switch (self->f724) {
    case 0:
        switch (m) {
        case 1:
            s = 5;
            break;
        case 0:
            s = 4;
            break;
        case 2:
            s = 7;
            break;
        }
        break;
    case 1:
        switch (m) {
        case 1:
            if (self->fBF8 < g_gameClock[1]) {
                s = 5;
            }
            break;
        case 0:
            if (self->f754 != 0) {
                if ((self->flags & 0xC0000000) == 0x40000000) {
                    s = 2;
                }
            } else {
                s = 2;
            }
            break;
        case 2:
            if (self->fBF8 < g_gameClock[1]) {
                s = 7;
            }
            break;
        }
        break;
    case 2:
        switch (m) {
        case 1:
            if (self->fBF8 < g_gameClock[1]) {
                s = 5;
            }
            break;
        case 0:
            if (self->f754 != 0) {
                if ((self->flags & 0xC0000000) == 0) {
                    s = 1;
                }
            }
            break;
        case 2:
            if (self->fBF8 < g_gameClock[1]) {
                s = 7;
            }
            break;
        }
        break;
    case 3:
        switch (m) {
        case 0:
            break;
        case 1:
            if (self->fBF8 < g_gameClock[1]) {
                s = 5;
            }
            break;
        case 2:
            if (self->fBF8 < g_gameClock[1]) {
                s = 7;
            }
            break;
        }
        break;
    case 5:
        switch (m) {
        case 1:
            if (HasAgentReachedPathEnd(self)) {
                s = 6;
            }
            break;
        case 0:
            s = 9;
            break;
        case 2:
            s = 7;
            break;
        }
        break;
    case 6:
        switch (m) {
        case 0:
            if (self->fBF4 < g_gameClock[1]) {
                s = 9;
            }
            break;
        case 1:
            if (self->fA60 == 0) {
                s = 5;
            }
            break;
        case 2:
            s = 7;
            break;
        }
        break;
    case 4:
        switch (m) {
        case 0:
            if (HasAgentReachedPathEnd(self)) {
                s = 1;
            }
            break;
        case 1:
            if (self->fBF8 < g_gameClock[1]) {
                s = 5;
            }
            break;
        case 2:
            if (self->fBF8 < g_gameClock[1]) {
                s = 7;
            }
            break;
        }
        break;
    case 9:
        switch (m) {
        case 1:
            s = 5;
            break;
        case 0:
            if (self->f7E0 == 0) {
                s = 4;
            }
            break;
        case 2:
            if (self->fBF8 < g_gameClock[1]) {
                s = 7;
            }
            break;
        }
        break;
    case 8:
    case 10:
    case 16:
        if (self->f7E0 == 0) {
            s = 0;
        }
        break;
    case 12:
        if (m < 0) {
            break;
        }
        if (m < 2) {
            goto c83D0;
        } else if (m == 2) {
            if (self->f7E0 == 0) {
                s = 0xD;
                break;
            } else {
                if (self->f758[14].obj != 0) {
                    if (self->desc08()->m5D(self) != 0) {
                        s = 0xE;
                        break;
                    }
                }
                if (HasAgentReachedPathEnd(self) != 0) {
                    if (self->f758[13].obj != 0) {
                        s = 0xD;
                    }
                }
            }
        }
        break;
    case 13:
        if (m < 0) {
            break;
        }
        if (m < 2) {
            goto c83D0;
        } else if (m == 2) {
            if (self->f758[14].obj != 0) {
                if (self->desc08()->m5D(self) != 0) {
                    s = 0xE;
                    break;
                }
            }
            if (self->fA60 == 0) {
                if (self->f758[12].obj != 0) {
                    s = 0xC;
                }
            }
        }
        break;
    case 14:
        if (m < 0) {
            break;
        }
        if (m < 2) {
            goto c83D0;
        } else if (m == 2) {
            goto c7;
        }
        break;
c83D0:
        if (self->fC00 < g_gameClock[1]) {
            s = 8;
        }
        break;
    case 7:
c7:
        if (self->f7E0 == 0) {
            s = 0xC;
        }
        break;
    }
done:
    return s;
}

ASM_FUNC(func_001C8418);

s32 func_001C84C0(Agent* self)
{
    s32 result = 0;
    if (self->fA60 != 0) {
        result = self->f930 == self->f92C;
    }
    return result;
}

struct Inner_1C84E8 { u8 pad[8]; u32 flags; };
struct Obj_1C84E8 { Inner_1C84E8* inner; u8 pad0[0x50 - 4]; void* p50; u8 pad1[0x360 - 0x54]; f32 f360; u8 pad2[0x538 - 0x364]; u64 f538; };

s32 func_001300E8(void* node, s32 kind);

s32 func_001C84E8(void* unused, Obj_1C84E8* self)
{
    if ((self->f538 & (1ULL << 43)) != 0) {
        if ((self->inner->flags & 0x80) == 0)
            return 0;
        if (self->f360 == 0.0f)
            return 0;
    }
    if (IsObjectOfKind(self->p50, 5) != 0 || IsObjectOfKind(self->p50, 0x40) != 0 || IsObjectOfKind(self->p50, 0x41) != 0)
        return 0;
    return 1;
}

ASM_FUNC(func_001C8590);

INCLUDE_RODATA(jtbl_0024D6B0);

ASM_FUNC(func_001C8920);

void func_001454E0(void* a, void* b, f32* x, f32* y, s32 flag);
void func_001C7AE0(void* self, f32 x, f32 y);

void func_001C8BC0(Agent* self)
{
    f32 x;
    f32 y;
    func_001454E0((u8*)self + 0xA40, (u8*)self + 0x140, &x, &y, 0);
    SetAgentFacingAngles(self, x, y);
}

struct __attribute__((aligned(16))) Quad_1C8C08 { s32 a, b, c, d; };
struct Tgt_1C8C08;
typedef void (*TFn_1C8C08)(Tgt_1C8C08* t, Agent* s, f32 x, f32 y, s32 z, void* out, s32 w);
struct Tgt_1C8C08 { TFn_1C8C08* vtbl; };
struct Res_1C8C08 { s32 pad0; Tgt_1C8C08* t; };
typedef s32 (*VFn_1C8C08)(Agent* s);
void func_001C8418(Agent* self, void* p);
void func_0012C9E8(f32 c, void* a, Agent* b, void* d, void* e, void* f, s32 g);
Res_1C8C08* func_0012CCE8(void* a, Agent* b);

void func_001C8C08(Agent* self, s32 flag)
{
    Quad_1C8C08 q;
    switch (self->f724) {
    case 7:
    case 10:
    case 12:
    case 13:
    case 14: {
        s32 v = ((VFn_1C8C08*)self->desc)[0x198 / 4](self);
        if (v != 0) func_001C8418(self, (u8*)v + 0x140);
        break;
    }
    case 4:
        if (flag != 0) {
            if (self->f750 != 0) {
                switch (self->f920) {
                case 0:
                    func_0012C9E8(self->f918, self->f750, self, (u8*)self + 0x140, (u8*)self + 0x914, &q, 0);
                    break;
                case 1: {
                    self->f914 = self->f918;
                    Tgt_1C8C08* t = FindEntryByObjectId(self->f750, self)->t;
                    t->vtbl[0](t, self, self->f914, 1.0f, 0, &q, 0);
                    break;
                }
                }
                self->f91C = 1.0f;
            } else {
                q = (*(Quad_1C8C08*)&self->v190);
            }
            func_001C8418(self, &q);
        }
        break;
    case 5:
        if (flag != 0) func_001C8418(self, (u8*)self + 0x900);
        break;
    }
}

void func_001C8D40(Agent* self, s32* out) { if (self->fA60 && self->f930 >= self->f92C - 2) { *out = 1; return; } *out = 0; }

struct Sub_1C8D78 {
    u8 pad0[0x8];
    s32 f8;
    u8 pad1[0x2D0];
    void* f2DC;
};

void func_0012C288(void* self, void* a1, s32 a2, void* a3, s32 a4, void* a5, f32 f0, f32 f1);
void func_0012F810(void* a0, Sub_1C8D78* a1);
s32 func_00183458(Agent* a);
Attachment* func_0012D570(AnimationPlayer* a0, s32 a1);

void func_001C8D78(Agent* self)
{
    Sub_1C8D78* sub = ((Sub_1C8D78*)self->fA74);
    if (sub->f2DC != 0) {
        s32 pair[2];
        pair[0] = sub->f8;
        pair[1] = (s32)self;
        CreateAnimationPlayer(sub->f2DC, self, 1, pair, 1, &self->f754, 0.0f, 1.0f);
        func_0012F810(self->f754, ((Sub_1C8D78*)self->fA74));
        Attachment* node = FindPlayerAttachmentByOwner(self->f754, GetEffectiveObjectId(self));
        if ((void*)node == self->f1EC) {
            node->mode0 = 5;
        }
        if ((void*)node == self->f1F0) {
            node->mode1 = 5;
        }
    }
}

typedef s32 (*VFn_1C8E28)(Agent*);
extern f32 D_00261860;
s32 func_00128230(Agent* self);
void func_001C7BE8(Agent* self);
void func_00128598(f32 a, f32 b, Agent* self, s32 c, s32 d, f32* e, f32* f, f32* g);
void func_001C7AE0(Agent* self, f32 x, f32 y);
void func_001EFC98(void* n);
void func_001C8920(Agent* self);
void func_001C8BC0(Agent* self);

void func_001C8E28(Agent* self)
{
    ((VFn_1C8E28*)self->desc)[102](self);
    switch (self->f724) {
    case 0:
    case 16:
        break;
    case 1:
    case 2:
        if (func_00128230(self) != 0)
            func_001C7BE8(self);
        break;
    case 3:
        if (self->f754 != 0) {
            f32 out[3];
            f32 zero = 0.0f;
            out[1] = zero;
            func_00128598(g_frameDt, self->f638, self, 0, 0, &out[0], self->fB1C ? &out[1] : 0, &out[2]);
            f32 y = out[1];
            SetAgentFacingAngles(self, out[0], y);
        }
        ScheduleItemTimeouts(*(void**)(((u8*)self->fA74) + 0x328));
        break;
    case 4:
    case 5:
    case 12:
        func_001C8920(self);
        break;
    case 7:
    case 10:
    case 13:
    case 14:
        func_001C8BC0(self);
        break;
    }
}

typedef void (*Method0_1C8F20)(void*, s32, void*);
typedef void (*Method2_1C8F20)(void*, s32, void*);
struct Frame_1C8F20 { s32* oldSlot; s32* stateSlot; };
extern f32 D_00261858[];
void func_001837E0(void*, s32, s32, void*);

void func_001C8F20(Agent* self, s32 state, void* context)
{
    self->f72C &= -2;
    if (self->f724 == state) return;
    s32 old = self->f724;
    ((Method0_1C8F20)self->desc08()->m5B)(self, state, context);
    self->f724 = state;
    self->f728 = g_gameClock[1];
    ((Method2_1C8F20)self->desc08()->m5C)(self, old, context);
    Frame_1C8F20 frame;
    frame.oldSlot = &old;
    frame.stateSlot = &self->f724;
    TriggerScriptEvent(self, 15, 2, &frame);
}

void func_001C8F20(Agent* self, s32 mode, s32 value);

void func_001C8FD0(Agent* self, s32 mode, s32 value)
{
    if (mode == -1) {
        self->fB88 = 0;
    } else {
        self->fB88 = 1;
        ChangeAgentState(self, mode, value);
    }
}

void func_0012E760(AnimationPlayer* p);
f32 func_001EAAE0(f32 a, f32 b);
void func_001EF900(C62* p, s32 z);
void func_00138F28(void* world, Agent* self);

void func_001C9008(Agent* self, s32 mode)
{
    s32 i;
    if (self->f7E0 != 0) {
        self->f86C = self->f7E0->time / self->f7E0->anim->length;
    }
    self->fB78 = 0;
    self->fB7C = 0;
    self->fB84 = 0;
    self->fB8C = 0;
    for (i = 0; i < self->fA78; i++) {
        ((BaseObject*)self->fA7C[i].obj)->desc->m03((BaseObject*)self->fA7C[i].obj);
    }
    switch (self->f724) {
    case 1:
        if (self->f754 != 0 && mode != 2) {
            self->f918 = self->f754->time;
            self->f91C = self->f754->speed;
            StopAnimationPlayer(self->f754);
            self->f754 = 0;
        }
        break;
    case 3:
        if (self->f754 != 0) {
            StopAnimationPlayer(self->f754);
            self->f754 = 0;
        }
        ((C62*)self->fA74)->desc->m18(((C62*)self->fA74), self);
        func_001EF900(((C62*)self->fA74), 0);
        self->fA74 = 0;
        if (mode == 1) {
            self->f914 = self->f918;
        }
        break;
    case 14:
        self->f748 = g_gameTime[0] + RandomFloatInRange(self->f740, self->f744);
        break;
    case 11:
        self->f724 = mode;
        InitContactPairFlags((void*)g_currentWorld, self);
    case 16:
        self->fC04 = 0;
        break;
    case 8:
        self->fC00 = 3.4028235e+38f;
        break;
    }
    if (self->f7E0 != 0) {
        StopAnimationPlayer(self->f7E0);
        self->f7E0 = 0;
        self->f72C &= ~2;
    }
}

struct Sub_1C91C8 {
    u8 pad0[0x2D0];
    s32 f2D0;
};
struct HookVT_1C91C8;
struct Hook_1C91C8 {
    HookVT_1C91C8* vt;
};
struct HookVT_1C91C8 {
    u8 pad0[0x70];
    void (*f70)(Hook_1C91C8* hook, Agent* owner);
};
struct Vec_1C91C8 {
    s32 v[4];
};


void func_001C4D60(Agent* self, Animation* t, s32 z);
void func_0012F6B0(AnimationPlayer* t, f32 x);
void func_001C7AE0(Agent* self, f32 x, f32 y);
void func_001C8D78(Agent* self);
s32 func_0012C7B0(Animation* t, Agent* self, s32 mode, void* out, f32 x, f32 y);
void func_0012C288(Animation* t, Agent* self, s32 one, s32* p, s32 mode, void* out, f32 x, f32 y);
s32 func_00183458(Agent* self);
Attachment* func_0012D570(AnimationPlayer* t, s32 q);
void func_00128018(Agent* self, s32 z, u8* p, Vec_1C91C8* out);
void func_00152010(u8* p, Vec_1C91C8* v, s32 a, s32 b);
void func_00138F28(s32 p, Agent* self);
void func_0018D608(void);
void func_0018D6F0(void);
void func_0012D1B0(Animation* t, Agent* self, s32* count, BaseObject*** list);
void func_001EFA88(s32 x, BaseObject* t);
void func_00141040(u8* p, s32 x);
void func_00126D60(Agent* self, f32 x);
f32 func_001EAAE0(f32 x, f32 y);
void func_001C8920(Agent* self);
void func_001C8BC0(Agent* self);

extern u8 D_00261420[];
extern u8 D_00261EF0[];

void func_001C91C8(Agent* self, s32 evt, Animation* arg)
{
    Animation* tgt;
    Animation* t;

    if (arg != 0) {
        tgt = arg;
    } else {
        tgt = (Animation*)self->f758[self->f724].obj;
    }
    t = (Animation*)self->f870[self->f724].obj;
    if (t == 0) {
        t = ((Animation*)self->f8F8);
    }
    func_001C4D60(self, t, 0);
    self->desc08()->m5E(self, 1);

    switch (self->f724) {
    case 2:
        if (self->f754 != 0) {
            SetAnimationPlayerSpeed(self->f754, 1.0f);
        } else {
            SetAgentFacingAngles(self, self->v1D0.z, 0.0f);
        }
        break;
    case 3:
        if (((Sub_1C91C8*)self->fA74)->f2D0 == 2) {
            func_001C8D78(self);
        }
        break;
    case 1:
        if (((Animation*)self->f750) != 0 && evt != 2) {
            Attachment* v;
            CreateAnimationPlayerWithoutPresetTargets(((Animation*)self->f750), self, 1, &self->f754, self->f914, self->f91C);
            v = FindPlayerAttachmentByOwner(self->f754, GetEffectiveObjectId(self));
            if ((void*)v == self->f1EC) {
                v->mode0 = 5;
            }
            if ((void*)v == self->f1F0) {
                v->mode1 = 5;
            }
        }
        break;
    case 11: {
        Vec_1C91C8 vec;
        s32 count;
        BaseObject** list;
        func_00128018(self, 0, self->fB60, &vec);
        ScatterObjectsAtPoint(g_scatterController, &vec, self->fB58, self->fB70);
        InitContactPairFlags((s32)g_currentWorld, self);
        if (((Animation*)self->f750) != 0) {
            s32 i;
            PushBackMemoryMark();
            i = 0;
            GatherAnimationEventObjects(((Animation*)self->f750), self, &count, &list);
            while (i < count) {
                BaseObject* e = list[i++];
                RemoveFromSmallList(*(s32*)((u8*)e + 0x328), e);
            }
            PopBackMemoryMark();
        }
        SetFlagTableBit(g_flagTable, self->fB10);
        if (((Hook_1C91C8*)self->fB54) != 0) {
            ((Hook_1C91C8*)self->fB54)->vt->f70(((Hook_1C91C8*)self->fB54), self);
            self->fB54 = 0;
        }
        if (self->fBD4 != 0) {
            f32 f = self->fA70;
            if (tgt != 0) {
                f += tgt->length;
            }
            func_00126D60(self, f);
        }
        self->fC04 = 1;
        break;
    }
    case 16:
        self->fC04 = 1;
        self->fA68--;
        break;
    case 6:
        self->fBF4 = 3.4028235e+38f;
        SetAgentFacingAngles(self, self->f910, 0.0f);
        break;
    case 7:
        self->fBF8 = 3.4028235e+38f;
        break;
    case 10:
        self->fBFC = 3.4028235e+38f;
        break;
    }

    if (tgt != 0) {
        f32 w;
        s32 mode;
        if (self->f724 == 2 && self->fB14 != 0) {
            f32 t = self->fB18;
            w = (0.0f <= t) ? t : RandomFloatInRange(0.0f, 1.0f);
        } else {
            Animation* cur = ((Animation*)self->f868);
            if (cur == 0) {
                w = 0.0f;
            } else if (tgt == cur) {
                w = self->f86C;
            } else {
                s32 i;
                w = 0.0f;
                for (i = 0; i < self->f7E4; i++) {
                    Group08* g = &self->f7E8[i];
                    u32 j;
                    for (j = 0; j < 4; j++) {
                        if (((BaseObject*)self->f868)->id == g->ids[j]) {
                            break;
                        }
                    }
                    if (j < 4) {
                        for (j = 0; j < 4; j++) {
                            if (((BaseObject*)tgt)->id == g->ids[j]) {
                                break;
                            }
                        }
                        if (j < 4) {
                            w = self->f86C;
                            break;
                        }
                    }
                }
            }
        }
        mode = (w != 0.0f) ? 3 : 1;
        if ((evt ^ 0xB) == 0) {
            mode |= 4;
        }
        if (self->fBEC == -1 || self->fBF0 == 0) {
            CreateAnimationPlayerWithoutPresetTargets(tgt, self, mode, &self->f7E0, w * tgt->length, 1.0f);
        } else {
            CreateAnimationPlayer(tgt, self, 1, &self->fBEC, mode, &self->f7E0, w * tgt->length, 1.0f);
        }
        self->f868 = tgt;
        self->f86C = 0.0f;
    }

    switch (self->f724) {
    case 1:
    case 4:
    case 5:
    case 12:
        func_001C8920(self);
        break;
    case 7:
    case 10:
    case 13:
    case 14:
        func_001C8BC0(self);
        break;
    }
}

s32 func_001C96B8(Agent* self) { if (!self->f720) return 3; return *(s32*)((u32)self->f720 + 0x50); }

ASM_FUNC(func_001C96D8);

struct Obj_1C9990 { u8 pad00[8]; s32 flags08; };
struct __attribute__((aligned(16))) Quad_1C9990 { s32 a, b, c, d; };
struct Req_1C9990 { s32 kind00; Obj_1C9990** ref04; };
struct Frame_1C9990 { Obj_1C9990** ref00; Agent* self04; u8 pad08[8]; s32 code10; u8 pad14[0x0C]; Quad_1C9990 q20; s32 tail30[4]; };

void func_001F5C0C(void* p, s32 v, s32 n);
s32 func_00177838(void* p, s32 a, s32 b);

s32 func_001C9990(Agent* self, Req_1C9990* req)
{
    Frame_1C9990 f;

    if (self->desc05()->m4B(self, req->kind00) != 0) return 0;
    func_001F5C0C(&f, 0, 0x40);
    f.ref00 = req->ref04;
    f.self04 = self;
    if (req->kind00 == 4) {
        f.code10 = req->kind00;
    } else if (f.ref00 == 0) {
        f.code10 = 2;
    } else if ((*f.ref00)->flags08 & 0x20) {
        f.code10 = 0x10;
    } else {
        f.code10 = 2;
    }
    f.q20 = (*(Quad_1C9990*)&self->v140);
    return FindNodeForQuery(&f, 0, 0) != 0;
}

s32 func_001C9A48(Agent* self) { return self->fBD8 != 0; }



void func_0012E760(AnimationPlayer* c);
void func_001C8F20(Agent* self, void* arg, s32 mode);

void func_001C9A58(Agent* self) {
    if (self->f72C == 0) {
        return;
    }
    if (self->f72C & 2) {
        if (self->f7E0 != 0) {
            if (self->f724 != 0xB) {
                StopAnimationPlayer(self->f7E0);
                self->f7E0 = 0;
            } else {
                self->f7E0->time = self->f7E0->anim->length;
                self->f7E0->f10 = 3.4028235e+38f;
            }
        }
        s32 m = -3;
        self->f72C &= m;
    }
    if (self->f72C & 1) {

        ChangeAgentState(self, self->f730, 0);
    }
}

ASM_FUNC(func_001C9AF8);

struct Inner_001C9CF8 { u8 pad0[0x8]; void* p8; };
f32 func_0012CCC0(void* obj, s32 id);
void func_0012F0A0(void* obj, s32 a1, f32 fa, f32 fb);

void func_001C9CF8(Agent* self)
{
    self->fB8C = 0;
    self->fA60 = 0;
    f32 r = func_0012CCC0(((Inner_001C9CF8*)self->f7E0)->p8, 0x1B1);
    SeekAnimationPlayer(((Inner_001C9CF8*)self->f7E0), 0, r, 1.0f);
    self->fBA4 = 0;
}

s32 func_001A8820(void* p, Collider* v);

s32 func_001C9D50(Agent* self, s32 key, Collider* other)
{
    if (key != (s32)self->fB54)
        return 0;
    switch (self->f724) {
    case 10:
    case 11:
    case 16:
        goto ret0;
    case 12:
    case 13:
    case 14:
        goto ret1;
    }
    if (!other)
        goto ret0;
    if (other->root == self->root)
        goto ret1;
    if (!self->fB0C)
        goto ret0;
    if (!func_001A8820(self->fB0C, other))
        goto ret0;
ret1:
    return 1;
ret0:
    return 0;
}

INCLUDE_RODATA(jtbl_0024D850);

INCLUDE_RODATA(jtbl_0024D8A0);

ASM_FUNC(func_001C9DE0);

s32 func_001CA460(void)
{
    return 2;
}

ASM_FUNC(func_001CA468);

void func_001C49C8(void);

void func_001CA5E0(void)
{
    func_001C49C8();
}

s32 func_001CA600(s32 index)
{
    return (u32)index < 17;
}

s32 func_001CA600(s32 index);

void func_001CA608(u8* self, s32 index, s32 value)
{
    if (IsAgentSlotIndex(index)) {
        *(s32*)(self + (index << 3) + 0x758) = value;
    }
}

s32 func_001CA600(s32 index);

void func_001CA658(Agent* self, s32 index, s32 value)
{
    if (IsAgentSlotIndex(index)) {
        Slot08* p = &self->f758[index];
        p->id = value;
        if (value == -1) {
            p->obj = 0;
        } else {
            p->obj = ResolveAgentClip(self, value);
        }
    }
}

s32 func_001CA600(s32 index);

s32 func_001CA6D0(Agent* self, s32 index)
{
    if (IsAgentSlotIndex(index) == 0)
        return 0;
    return (s32)self->f758[index].obj;
}

void func_001CA720(Agent* self, s32 a1, s32 a2)
{
    s32 n = self->fAC4;
    if ((u32)n < 4) {
        self->fAC4 = n + 1;
        Pend08* p = &self->fAC8[n];
        p->f00 = a1;
        p->id = a2;

    }
}

struct Item_001CA758 { u8 pad0[0x48]; s32 state; };

void* func_0015A418(void* source, s32 kind, void* arg, s32 mode);
void func_0012D398(void* item, Agent* host);
void func_00182ED8(void* item);

void* func_001CA758(Agent* self, void* arg)
{
    Item_001CA758* item = (Item_001CA758*)FindFirstObjectById(self->world, 0x101, arg, self->fB74);
    if (item != 0) {
        item->state = 0;
        func_0012D398(item, self);
        func_00182ED8(item);
    }
    return item;
}

void* func_001CA758(Agent* self, s32 arg);

void func_001CA7C0(Agent* self)
{
    s32 i = 16;
    Slot08* slot = self->f758;
    do {
        if (slot->id != -1) {
            slot->obj = ResolveAgentClip(self, slot->id);
            slot->id = -1;
        }
        i--;
        slot++;
    } while (i >= 0);

    s32 j = 0;
    if (self->fAC4 > 0) {
        do {
            Pend08* late = &self->fAC8[j];
            if (late->id != -1) {
                late->obj = ResolveAgentClip(self, late->id);
                late->id = -1;
            }
            j++;
        } while (j < self->fAC4);

    }
}

void func_001CA878(Agent* self, s32 v)
{
    self->fAFC = v;
    self->fAF8 = 1;
}

void func_001CA888(Agent* self, s32 v)
{
    self->fB08 = v;
    self->fB04 = 1;
}

s32 func_001CA600(s32 index);

void func_001CA898(Agent* self, s32 index, s32 value)
{
    if (IsAgentSlotIndex(index))
        self->f870[index].id = value;
}

void* func_0015A418(void* a, s32 b, s32 key, void* self);
void func_00182ED8(void* p);

void func_001CA8E8(Agent* self)
{
    for (s32 i = 16; i >= 0; i--) {
        Slot08* e = &self->f870[16 - i];
        if (e->id != -1) {
            void* r = FindFirstObjectById(self->world, 0x101, e->id, self);
            e->obj = r;
            if (r != 0) func_00182ED8(r);
        }
    }
}

void func_001CA960(Agent* self, s32 a, s32 b)
{
    u32 n = self->fA78;
    if (n < 4) {
        self->fA78 = n + 1;
        Elem08* e = &self->fA7C[n];
        e->key = a;
        e->f08 = b;
    }
}

s32 func_0015A448(void* owner, s32 index, Agent* self);

void func_001CA998(Agent* self, s32 index)
{
    s32 v;
    if (index == -1) {
        v = 0;
    } else {
        v = FindFirstObjectByIdMode4(self->world, index, self);
        if (v == 0)
            return;
    }
    if (v != self->f928)
        self->fA60 = 0;
    self->f924 = index;
    self->f928 = v;
}

struct Obj_1CAA08 {
    void* vtbl;
};

typedef s32 (*VFnA_1CAA08)(void* self);
typedef void (*VFnB_1CAA08)(void* self, void* arg);

void* func_001925F0(void);

void* func_001CAA08(Agent* self)
{
    void* s0;
    if (self->fB50 != 0) {
        s0 = self->fB50;
    } else if (self->fB40 != 0) {
        s0 = self->fB48;
    } else {
        s0 = GetActiveSwitchedCollider();
    }
    void* v = GetActiveSwitchedCollider();
    if (v != 0 && v == s0) {
        s32 r = ((VFnA_1CAA08*)((Obj_1CAA08*)s0)->vtbl)[81](s0);
        s0 = (r == 2) ? 0 : s0;
    }
    void* a0 = self->fB54;
    if (s0 == a0) {
        return s0;
    }
    if (a0 != 0) {
        ((VFnB_1CAA08*)((Obj_1CAA08*)a0)->vtbl)[28](a0, self);
    }
    if (s0 != 0) {
        ((VFnB_1CAA08*)((Obj_1CAA08*)s0)->vtbl)[27](s0, self);
    }
    self->fB54 = s0;
    return s0;
}

void func_001CAAD0(Agent* self, s32* out)
{
    *out = (s32)self->desc08()->m62(self);
}

void func_001CAB00(Agent* self, s32 value)
{
    self->fB48 = (void*)value;
    self->fB40 = 1;

}

extern const f32 D_0024DA90 = 3.40282347e+38f;

ASM_FUNC(func_001CAB10);

void func_001CAC28(Agent* self, s32 value)
{
    self->fB50 = (void*)value;
}

typedef s32 (*VFn_1CAC30)(void* self, void* out);

struct Out_1CAC30 {
    u8 pad0[0x94];
    f32 f94;
    f32 f98;
};


void func_001CAC30(Agent* self, Out_1CAC30* out)
{
    if (self->fC04 != 0) {
        f32 a = D_00274CF4;
        f32 b = D_00274CF8[0];
        out->f94 = a;
        out->f98 = b;
    } else {
        if (((VFn_1CAC30*)self->desc)[90](self, out) != 0) {
            f32 t = self->fBE8;
            out->f98 = 0.0f;
            out->f94 = t;
        } else {
            out->f94 = 0.0f;
            out->f98 = 0.0f;
        }
    }
}

struct Inner_1CACB0 { u8 pad0[0x88]; f32 f88; };
struct Out_1CACB0 { Inner_1CACB0* p0; u8 pad1[0x30 - 4]; s32 f30; };
void func_001C5388(Agent*, s32, Out_1CACB0*);

void func_001CACB0(Agent* self, s32 flags, Out_1CACB0* out)
{ func_001C5388(self, flags, out);
    if (self->fC04 != 0) { if ((flags & 0x12) == 0x12) { if (0.7f < out->p0->f88) { out->f30 = 0; } } } }

void func_001CAD28(Agent* self, f32 value) { self->f74C = value * 0.017453294f; }

void func_001CBE20(void* self, s32 value);

struct Obj_1CAD40 { u8 pad0[0x720]; void* f720; };

void func_001CAD40(Obj_1CAD40* self, s32 value)
{
    func_001CBE20(self->f720, value);
}

void func_001CAD60(Agent* self, s32 a, s32 b, s32 c, s32 d) { if ((u32)self->f7E4 < 8) { Group08* e = &self->f7E8[self->f7E4]; self->f7E4++; e->ids[0] = a; e->ids[1] = b; e->ids[2] = c; e->ids[3] = d; } }

void func_001C5C10(Agent* a, Collider* b, s32 c, s32 d);
s32 func_001300E8(Collider* a, s32 b);
s32 func_00182FC8(Collider* a);
void func_001879C0(f32 f, Collider* a, void* b, Collider* c, s32 d, s32 e, s32 g, void* h);
void func_00186BA8(Collider* a, Collider* b, s32 c, s32 d, s32 e, void* f);

void func_001CAD98(Agent* a0, Collider* a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    if (a0->fC04 == 0) {
        func_001C5C10(a0, a1, a4, a5);
    }
    if (a1 != a0->desc08()->m62(a0)) {
        if (a1->parent != 0) {
            return;
        }
        if (IsObjectOfKind(a1, 0x4C) == 0) {
            return;
        }
    }
    for (s32 i = 0; i < a0->fA78; i++) {
        Elem08* e = &a0->fA7C[i];
        if (IsObjectAttached((Collider*)e->obj) != 0) {
            if (a1->flags538 & 0x10000000000ULL) {
                func_001879C0(a1->radius3CC, a1, (u8*)a1 + 0x140, (Collider*)e->obj,
                              ((Collider*)e->obj)->tree.count,
                              (s32)((Collider*)e->obj)->tree.nodes, 0, (u8*)a0 + 0xAAC);
            } else if (a3 != 0) {
                func_00186BA8((Collider*)e->obj, a1, a2, a3, a4, (u8*)a0 + 0xAAC);
            }
        }
    }
}

struct Obj_1CAEE0;
typedef void (*VFn_1CAEE0)(void* self, void* arg);

struct Obj_1CAEE0 {
    VFn_1CAEE0* vtbl;
};

s32 func_001300E8(void* obj, s32 kind);
void func_00175170(void* obj, s32 a, s32 b);

void func_001CAEE0(u8* self, Obj_1CAEE0* other)
{
    other->vtbl[0x90 / 4](other, self + 0xAB0);
    if (IsObjectOfKind(other, 7) != 0) {
        SetPlayerState(other, 4, 0x2B);
    }
}

ASM_FUNC(func_001CAF38);

void func_0012E760(void* p);
s32 func_001C96B8(void* self);
void func_0012C9E8(void* a, void* b, f32 c, void* d, void* e, s32 f, s32 g);

void func_001CB328(Agent* self, void* value)
{
    void* p;

    if (value == self->f750) {
        return;
    }
    p = self->f754;
    if (p != 0) {
        StopAnimationPlayer(p);
        self->f754 = 0;
    }
    self->f750 = value;
    if (func_001C96B8(self) == 0) {
        self->f730 = 0;
        self->f72C = self->f72C | 1;
    }
    p = self->f750;
    if (p != 0) {
        func_0012C9E8(p, self, 0.0f, (u8*)self + 0x140, (u8*)self + 0x918, 0, 0);
    }
}

s32 func_001CB3C0(void)
{
    return 1;
}

s32 func_001CB3C8(void)
{
    return 0;
}

ASM_FUNC(func_001CB3D0);


struct Glob_1CB578 { u8 pad0[0x275C]; s32 f275C; };

s32 func_001CB578(Agent* self)
{
    s32 r = 0;
    Glob_1CB578* g;
    if (self->fB7C != 0) {
        goto set;
    }
    if (self->fB80 != 0) {
        r = 1;
    } else {
        g = (Glob_1CB578*)g_player;
        if (g != 0 && g->f275C != 0) {
set:
            r = 1;
        }
    }
    return r;
}


void* func_0011E580(s32 a, void* b, s32 c, s32 d, s32 e);
void* func_001DBCC8(u32 a, void* fn, void* obj, s32 c, s32 d);
void func_001CB8B8(void);

void* func_001CB5B8(void* a0)
{
    void* obj = CreateTypedRecord(0x89, a0, 0, 0x436, -1);
    AppendQueuedCall((u32)g_currentWorld, (void*)GroupAnimationEventObjects, obj, 0, 0);
    return obj;
}

void func_00182C18(void* self);

void func_001CB618(ItemKeeper* self)
{
    InitObject(self);
    self->f180 = -1;
}

struct List_1CB648 {
    u8 pad0[0x58];
    u32 count;
    void* items[16];
};

void func_001CBEE8(void* self, s32 arg);

void func_001CB648(List_1CB648* self, void* value)
{
    u32 n;

    if (self->count == 0) {
        func_001CBEE8(self, 0);
    }
    n = self->count;
    if (n < 0x10) {
        self->items[n] = value;
        self->count = n + 1;
    }
}

void func_001CB6A8(ItemKeeper* self, s32 value) { u32 i = self->owned.wantedCount; if (i < 16) { self->owned.wanted[i] = (FoundItem*)value; self->owned.wantedCount = i + 1; } }

void func_001CB6D0(ItemKeeper* self, s32 value) { u32 i = self->listed.wantedCount; if (i < 16) { self->listed.wanted[i] = (FoundItem*)value; self->listed.wantedCount = i + 1; } }

struct List_1CB6F8 { u8 pad0[0x58]; s32 count; s32 items[16]; };

void func_001CBEE8(void* self, s32 arg);
void func_0018D800(void* dst, void* src, s32 count);

void func_001CB6F8(List_1CB6F8* self, s32 value)
{
    s32 i = 0;
    if (self->count > 0) {
        for (; i < self->count; i++) {
            if (self->items[i] == value) break;
        }
        if (i >= self->count) return;
        s32 n = self->count;
        if (i < n) {
            s32 m = n - 1;
            self->count = m;
            s32* d = &self->items[i];
            CopyMemory(d, d + 1, (m - i) * 4);
            if (self->count <= 0) {
                func_001CBEE8(self, 3);
            }
        }
    }
}


FoundItem* func_0015A448(u32 a, FoundItem* b, ItemKeeper* c);

void func_001CB7A0(ItemKeeper* a0)
{
    for (s32 i = 0; i < a0->owned.wantedCount; i++) {
        FoundItem* r = FindFirstObjectByIdMode4((u32)g_currentWorld, a0->owned.wanted[i], a0);
        if (r != 0) {
            s32 n = a0->owned.count;
            if ((u32)n < 16) {
                a0->owned.found[n] = r;
                a0->owned.count = n + 1;
                r->owner = a0;
            }
        }
    }
    for (s32 i = 0; i < a0->listed.wantedCount; i++) {
        FoundItem* r = FindFirstObjectByIdMode4((u32)g_currentWorld, a0->listed.wanted[i], a0);
        if (r != 0) {
            s32 n = a0->listed.count;
            if ((u32)n < 16) {
                a0->listed.found[n] = r;
                a0->listed.count = n + 1;
                            }
        }
    }
}

struct Node_1CB8B8 {
    u8 pad0[0x2C];
    void* f2C;
    u8 pad1[0x2E0 - 0x30];
    s32 f2E0;
    u8 pad2[0x328 - 0x2E4];
    void* f328;
    u8 pad3[0x750 - 0x32C];
    void* f750;
};
struct Self_1CB8B8 {
    u8 pad0[0x58];
    s32 count;
    Node_1CB8B8* list[16];
};
struct Ent_1CB8B8 {
    s32 count;
    Node_1CB8B8** items;
};

void func_0018D608(void);
void func_0018D6F0(void);
void* func_0018D6A8(s32 size);
void func_0012D1B0(void* a, void* b, s32* c, void** d);
void* func_001EFA30(void);
void func_001EFA60(void* a, void* b);

void func_001CB8B8(Self_1CB8B8* self)
{
    Ent_1CB8B8* arr;
    s32 i;
    s32 j;
    s32 k;
    s32 m;

    PushBackMemoryMark();
    arr = (Ent_1CB8B8*)AllocateZeroedBackMemory(self->count * 8);
    for (i = 0; i < self->count; i++) {
        Node_1CB8B8* node = self->list[i];
        if (node->f750 != 0) {
            GatherAnimationEventObjects(node->f750, node, &arr[i].count, (void**)&arr[i].items);
        }
    }
    for (i = 0; i < self->count; i++) {
        Ent_1CB8B8* e = &arr[i];
        for (j = 0; j < e->count; j++) {
            Node_1CB8B8* node = e->items[j];
            if (node->f328 == 0) {
                node->f328 = func_001EFA30();
                ((Node_1CB8B8*)node->f328)->f2C = self;
                AppendToSmallList(node->f328, node);
                if (node->f2E0 != -1) {
                    for (k = i + 1; k < self->count; k++) {
                        Ent_1CB8B8* e2 = &arr[k];
                        for (m = 0; m < e2->count; m++) {
                            Node_1CB8B8* item = e2->items[m];
                            if (item->f2E0 == node->f2E0) {
                                item->f328 = node->f328;
                                AppendToSmallList(node->f328, item);
                            }
                        }
                    }
                }
            }
        }
    }
    PopBackMemoryMark();
}

void* func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void func_001CBB20(void* self);

struct Obj_1CBAA0 { u8 pad0[0x50]; s32 f50; u8 pad1[0x17C - 0x54]; s32 f17C; };

void func_001CBAA0(Obj_1CBAA0* a0)
{
    Obj_1CBAA0* self = a0;
    if (self->f50 == 3) {
        return;
    }
    if (self->f17C != 0) {
        return;
    }
    {
        s32 one = 1;
        void* owner = *(void**)&g_currentWorld;
        self->f17C = one;
        AppendQueuedCall(owner, (void*)(void (*)(void*))func_001CBB20, self, -1, 0);
    }
}

typedef s32 (*VFn_1CBAF8)(void* self);
struct Item_1CBAF8 { VFn_1CBAF8* vtbl; };
struct Obj_1CBAF8 { u8 pad0[0x5C]; Item_1CBAF8* f5C; };

s32 func_001CBAF8(Obj_1CBAF8* self)
{
    Item_1CBAF8* item = self->f5C;
    return item->vtbl[102](item);
}

struct Obj_1CBB20 { u8 pad0[0x50]; s32 f50; u8 pad1[0x17C - 0x54]; s32 f17C; u8 pad2[0x188 - 0x180]; s32 f188; };

s32 func_001CBCB8(void* self);
s32 func_001CBB88(void* self);
void func_001CBEE8(void* self, s32 arg);

void func_001CBB20(Obj_1CBB20* self)
{
    s32 v;

    self->f17C = 0;
    if (self->f50 != 3) {
        self->f188 = func_001CBCB8(self);
        for (;;) {
            v = func_001CBB88(self);
            if (v == self->f50) {
                break;
            }
            func_001CBEE8(self, v);
        }
    }
}

struct Key_1CBB88;
struct Obj_1CBB88;
s32 func_001300E8(Key_1CBB88* key, s32 kind);
s32 func_001CBD58(Obj_1CBB88* self);
void func_001BFCD8(Key_1CBB88* a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

struct Obj_1CBB88 {
    u8 pad0[0x50];
    s32 f50;
    s32 f54;
    s32 f58;
    void* f5C[75];
    u8 pad1[0x188 - 0x5C - 75 * 4];
    s32 f188;
};

s32 func_001CBB88(Obj_1CBB88* self)
{
    s32 state = self->f50;
    s32 i;

    switch (state) {
    case 0:
        if (self->f188 != 0) {
            for (i = 0; i < self->f58; i++) {
                if (IsObjectOfKind((Key_1CBB88*)self->f5C[i], 9) == 0) {
                    break;
                }
            }
            if (i >= self->f58) {
                StartSoundEffect((Key_1CBB88*)0x3F, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
            state = 2;
        }
        break;
    case 1:
        if (self->f188 != 0) {
            state = 2;
        } else if (func_001CBD58(self) != 0) {
            state = 0;
        }
        break;
    case 2:
        if (self->f188 == 0) {
            state = 1;
        }
        break;
    }
    return state;
}

struct __attribute__((aligned(16))) Quad_CBCB8 { s32 a, b, c, d; };

typedef s32 (*VFn_CBCB8)(void* self);

struct Item_CBCB8 {
    VFn_CBCB8* vtbl;
};

struct Self_CBCB8 {
    u8 pad0[0x40];
    Quad_CBCB8 f40;
    u8 pad1[0x58 - 0x50];
    s32 count;
    Item_CBCB8* items[1];
};

void* func_001CBAF8(Self_CBCB8* self);

s32 func_001CBCB8(Self_CBCB8* self)
{
    s32 i = 0;
    Item_CBCB8** p = self->items;
    for (;;) {
        if (!(i < self->count)) {
            return 0;
        }
        Item_CBCB8* it = *p;
        if (it->vtbl[91](it) != 0) {
            break;
        }
        p++;
        i++;
    }
    if (!(i < self->count)) {
        return 0;
    }
    {
        void* r = func_001CBAF8(self);
        if (r != 0) {
            self->f40 = *(Quad_CBCB8*)((u8*)r + 0x140);
        }
    }
    return 1;
}

struct Obj_CBD58;
typedef s32 (*VFn_CBD58)(void* self);

struct Obj_CBD58 {
    VFn_CBD58* vtbl;
};

struct Self_CBD58 {
    u8 pad0[0x58];
    s32 count;
    Obj_CBD58* items[1];
};

s32 func_001CBD58(Self_CBD58* a0)
{
    s32 result = 1;
    for (s32 i = 0; i < a0->count; i++) {
        Obj_CBD58* o = a0->items[i];
        s32 v = o->vtbl[92](o);
        switch (v) {
        case 1: break;
        case 0: result = 0; break;
        case 2: return 1;
        }
    }
    return result;
}

struct Obj_001CBE20 { u8 pad[0x168]; s32 count; s32 items[4]; };
void func_001CBE20(Obj_001CBE20* self, s32 value) { for (s32 i = 0; i < self->count; i++) if (value == self->items[i]) return; s32 i = self->count; if ((u32)i < 4) { s32 next = i + 1; self->items[i] = value; self->count = next; } }

struct Self_1CBE70 { u8 pad[0x168]; s32 count; void* items[1]; };

void func_00123AB0(void* object, s32 mode);

void func_001CBE70(Self_1CBE70* self, s32 mode)
{
    for (s32 i = 0; i < self->count; i++) {
        SetStateTriggerStateFromMessage(self->items[i], mode);
    }
}

struct Vt_1CBEE8 { u8 pad0[0x16C]; s32 (*fn16C)(void* self); };
struct Item_1CBEE8 {
    Vt_1CBEE8* vt;
    u8 pad4[0xBEC];
    f32 fBF0;
    f32 fBF4;
    f32 fBF8;
    f32 fBFC;
    f32 fC00;
};
struct Obj_1CBEE8 {
    u8 pad0[0x50];
    s32 f50;
    f32 f54;
    s32 cnt58;
    Item_1CBEE8* items[1];
    u8 pad60[0x124];
    void* f184;
};

extern f32 D_00261858[];

f32 func_001EAAE0(f32 a, f32 b);
void func_001BF0D8(void* p);
void* func_001BEEF8(s32 kind);
void func_001CBE70(Obj_1CBEE8* self, s32 a);
void func_001CC120(Obj_1CBEE8* self);

void func_001CBEE8(Obj_1CBEE8* self, s32 ns)
{
    s32 i;
    if (self->f50 == ns)
        return;
    switch (self->f50) {
    case 2:
        RemoveSoundLevelAndRecompute(self->f184);
        i = 0;
        self->f184 = 0;
        if (self->cnt58 > 0) {
            Item_1CBEE8** p = self->items;
            do {
                Item_1CBEE8* it = *p;
                f32 t = g_gameClock[1];
                i++;
                f32 r = RandomFloatInRange(D_00274D18[0], D_00274D18[1]);
                it->fC00 = g_gameClock[1] + r;
                p++;
            } while (i < self->cnt58);
        }
        break;
    case 1: {
        s32 j = 0;
        if (self->cnt58 > 0) {
            Item_1CBEE8** p = self->items;
            do {
                f32 t = g_gameClock[1];
                j++;
                f32 r = RandomFloatInRange(D_00274D08[0], D_00274D08[1]);
                (*p)->fBF4 = g_gameClock[1] + r;
                p++;
            } while (j < self->cnt58);
        }
        break;
    }
    }
    switch (ns) {
    case 2:
        i = 0;
        self->f184 = PushSoundLevel(0x6B);
        func_001CBE70(self, 0);
        if (self->cnt58 > 0) {
            Item_1CBEE8** p = self->items;
            do {
                Item_1CBEE8* it = *p;
                if (it->vt->fn16C(it) != 0) {
                    it->fBF8 = g_gameClock[1];
                } else {
                    f32 r = RandomFloatInRange(D_00274D10[0], D_00274D10[1]);
                    it->fBF8 = g_gameClock[1] + r;
                }
                i++;
                p++;
            } while (i < self->cnt58);
        }
        break;
    case 1:
        func_001CC120(self);
        break;
    case 0:
        func_001CBE70(self, 1);
        break;
    case 3:
        func_001CBE70(self, 2);
        break;
    }
    self->f50 = ns;
    self->f54 = g_gameClock[1];
}

INCLUDE_RODATA(D_0024DA94);

ASM_FUNC(func_001CC120);

ASM_FUNC(func_001CC3F8);




