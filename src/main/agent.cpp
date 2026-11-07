// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "shapes.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "globals.h"
#include "item_keeper.h"
#include "flag_table.h"
#include "node_query.h"
#include "c62.h"
#include "animation.h"
#include "attachment.h"
#include "c8b.h"

extern f32 D_0026185C[];

// A quadratic in t (c[0] + t * (c[1] + t * c[2])) on 16 bytes, as in hit_count_collider: the file's
// .data starts on 16 (0x274C18 to 0x274C20 is padding after the previous file's), and 0x274C54
// to 0x274C5F is the quadratic's own.
void* func_001CA758(Agent* self, void* arg);
void* func_001CA758(Agent* self, s32 arg);

struct __attribute__((aligned(16))) PaddedQuadratic { f32 c[3]; };

// The file's .data, in retail's order; its assembly reads the quadratics.
s32 D_00274C20[4] = { 2, 0x195, 0x87C, 0 };
s32 D_00274C30[8] = { 2, 0x194, 0x750, 6, 0x50, 0x734, 0, 0 };
PaddedQuadratic D_00274C50 = { { 1.0f, -1.0f, 0.0f } };
PaddedQuadratic D_00274C60 = { { 0.0f, 0.0f, 1.0f } };
PaddedQuadratic D_00274C70 = { { 0.0f, 15.0f, 1.5f } };
PaddedQuadratic D_00274C80 = { { 0.0f, 2.5f, 0.25f } };
float D_00274C90 = 40.0f;
float D_00274C94 = 50.0f;
float D_00274C98[2] = {0.5f, 0.0f};
PaddedQuadratic D_00274CA0 = { { 1.0f, -0.00100000005f, 0.0f } };
PaddedQuadratic D_00274CB0 = { { 0.25f, 1.0f, 0.0f } };
PaddedQuadratic D_00274CC0 = { { 0.0f, 0.00499999989f, 0.0f } };
float D_00274CD0[2] = {0.0f, 1.0f};
float D_00274CD8[2] = {1.0f, 0.0f};
PaddedQuadratic D_00274CE0 = { { 0.0f, 0.00499999989f, 0.0f } };
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
PaddedQuadratic D_00274D30 = { { 0.800000012f, 1.20000005f, 0.0f } };

extern u8 D_00261420[];
void func_001C4458(TurningCollider* self);
s32 func_00140FF8(FlagTable* p);
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
    s32 r = TakeFlagTableIndex((FlagTable*)g_flagTable);
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
        PickAgentSecondaryTarget(self);
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

void func_001C7278(Agent* self)
{
    self->desc->m03(self);
}

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

extern u8 D_00261420[];

void func_001C72A0(Agent* self)
{
    StartTurningCollider(self);
    ResolveObjectLinks(self, 2, (u8*)D_00274C30);
    if (self->f720 == 0) {
        void* t = CreateItemKeeper(self->world);
        self->f720 = t;
        AddItemKeeperMember(t, self);
    }
    ResolveAgentClips(self);
    for (s32 i = 0; i < 17; i++) {
        void* item = self->f870[i].obj;
        if (item != 0) {
            self->f6DC = item;
            self->f8F8 = item;
            self->desc03()->m34(self, item, 1);
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
    SetTurningColliderGravityScale(self, self->f700);
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
        if (IsObjectInPool(self->fB0C, obj) != 0) {
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
        AddItemKeeperMember(self->f720, self);
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
        RemoveItemKeeperMember(self->f720, self);
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
        BuildYawPitchMatrix(x, y, (u8*)self + 0x660);
    } else {
        BuildAxisAngleMatrix((u8*)&g_unitZVector, x, (u8*)self + 0x660);
    }
}

void func_001C8F20(Agent* self, s32 a1, s32 a2);

void func_001C7B60(Agent* self)
{
    if (self->fB84 != 0) return;
    if (self->fB88 != 0) return;
    if (g_player != 0 && g_player->f275C != 0) return;
    for (;;) {
        s32 v = self->desc08()->m59(self);
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
    s32 m = GetAgentRosterState(self);

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


s32 func_001300E8(void* node, s32 kind);

s32 func_001C84E8(void* unused, Collider* self)
{
    if ((self->flags538 & (1ULL << 43)) != 0) {
        if ((self->desc->flags & 0x80) == 0)
            return 0;
        if (self->f360 == 0.0f)
            return 0;
    }
    if (IsObjectOfKind(self->root, 5) != 0 || IsObjectOfKind(self->root, 0x40) != 0 || IsObjectOfKind(self->root, 0x41) != 0)
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

void func_001C8418(Agent* self, void* p);
void func_0012C9E8(f32 c, void* a, Agent* b, void* d, void* e, void* f, s32 g);
Entry8B* func_0012CCE8(void* a, Agent* b);

void func_001C8C08(Agent* self, s32 flag)
{
    Vec02 q;
    switch (self->f724) {
    case 7:
    case 10:
    case 12:
    case 13:
    case 14: {
        void* v = self->desc08()->m62(self);
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
                    Mover8B* t = FindEntryByObjectId(self->f750, self)->mover;
                    t->vtbl[0](t, self, self->f914, 1.0f, 0, &q, 0);
                    break;
                }
                }
                self->f91C = 1.0f;
            } else {
                q = self->v190;
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

void func_0012C288(void* self, void* a1, s32 a2, void* a3, s32 a4, void* a5, f32 f0, f32 f1);
void func_0012F810(void* a0, C62* a1);
s32 func_00183458(Agent* a);
Attachment* func_0012D570(AnimationPlayer* a0, s32 a1);

void func_001C8D78(Agent* self)
{
    C62* sub = ((C62*)self->fA74);
    if (sub->id2DC != 0) {
        s32 pair[2];
        pair[0] = sub->id;
        pair[1] = (s32)self;
        CreateAnimationPlayer((void*)sub->id2DC, self, 1, pair, 1, &self->f754, 0.0f, 1.0f);
        func_0012F810(self->f754, ((C62*)self->fA74));
        Attachment* node = FindPlayerAttachmentByOwner(self->f754, GetEffectiveObjectId(self));
        if ((void*)node == self->f1EC) {
            node->mode0 = 5;
        }
        if ((void*)node == self->f1F0) {
            node->mode1 = 5;
        }
    }
}

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
    self->desc08()->m62(self);
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
        ScheduleItemTimeouts(((C62*)self->fA74)->group);
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
        FaceAgentTowardGoalPoint(self);
        break;
    }
}

// What a state change tells the script (event 15): the old state and where the new one is.
struct StateChangeArgs { s32* oldSlot; s32* stateSlot; };
extern f32 D_00261858[];
void func_001837E0(void*, s32, s32, void*);

void func_001C8F20(Agent* self, s32 state, void* context)
{
    self->f72C &= -2;
    if (self->f724 == state) return;
    s32 old = self->f724;
    self->desc08()->m5B(self, state, context);
    self->f724 = state;
    self->f728 = g_gameClock[1];
    self->desc08()->m5C(self, old, context);
    StateChangeArgs frame;
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
        SetStateAndNotify(((C62*)self->fA74), 0);
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



void func_001C4D60(Agent* self, Animation* t, s32 z);
void func_0012F6B0(AnimationPlayer* t, f32 x);
void func_001C7AE0(Agent* self, f32 x, f32 y);
void func_001C8D78(Agent* self);
s32 func_0012C7B0(Animation* t, Agent* self, s32 mode, void* out, f32 x, f32 y);
void func_0012C288(Animation* t, Agent* self, s32 one, s32* p, s32 mode, void* out, f32 x, f32 y);
s32 func_00183458(Agent* self);
Attachment* func_0012D570(AnimationPlayer* t, s32 q);
void func_00128018(Agent* self, s32 z, u8* p, Quad4* out);
void func_00152010(u8* p, Quad4* v, s32 a, s32 b);
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
        if (((C62*)self->fA74)->id2D0 == 2) {
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
        Quad4 vec;
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
        if (((BaseObject*)self->fB54) != 0) {
            ((BaseObject*)self->fB54)->desc->m18(((BaseObject*)self->fB54), self);
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
        FaceAgentTowardGoalPoint(self);
        break;
    }
}

s32 func_001C96B8(Agent* self) { if (!self->f720) return 3; return *(s32*)((u32)self->f720 + 0x50); }

ASM_FUNC(func_001C96D8);

// What slot 76 is asked about: a kind and the object concerned.
struct AgentRequest { s32 kind00; BaseObject* ref04; };

void func_001F5C0C(void* p, s32 v, s32 n);
s32 func_00177838(void* p, s32 a, s32 b);

s32 func_001C9990(Agent* self, AgentRequest* req)
{
    NodeQuery f;

    if (self->desc05()->m4B(self, req->kind00) != 0) return 0;
    FillMemory(&f, 0, 0x40);
    f.p00 = req->ref04;
    f.hold = self;
    if (req->kind00 == 4) {
        f.kind = req->kind00;
    } else if (f.p00 == 0) {
        f.kind = 2;
    } else if (((BaseObject*)f.p00)->desc->flags & 0x20) {
        f.kind = 0x10;
    } else {
        f.kind = 2;
    }
    f.pos = self->v140;
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

f32 func_0012CCC0(void* obj, s32 id);
void func_0012F0A0(void* obj, s32 a1, f32 fa, f32 fb);

void func_001C9CF8(Agent* self)
{
    self->fB8C = 0;
    self->fA60 = 0;
    f32 r = func_0012CCC0(self->f7E0->anim, 0x1B1);
    SeekAnimationPlayer(self->f7E0, 0, r, 1.0f);
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
    if (!IsObjectInPool(self->fB0C, other))
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
    DrawTurningCollider();
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

void* func_0015A418(void* source, s32 kind, void* arg, s32 mode);
void func_0012D398(void* item, Agent* host);
void func_00182ED8(void* item);

void* func_001CA758(Agent* self, void* arg)
{
    Animation* item = (Animation*)FindFirstObjectById(self->world, 0x101, arg, self->fB74);
    if (item != 0) {
        item->enabled = 0;
        func_0012D398(item, self);
        ResolveAndStartObject(item);
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
            if (r != 0) ResolveAndStartObject(r);
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
        s32 r = ((SwitchedCollider*)s0)->desc05()->m4D((SwitchedCollider*)s0);
        s0 = (r == 2) ? 0 : s0;
    }
    void* a0 = self->fB54;
    if (s0 == a0) {
        return s0;
    }
    if (a0 != 0) {
        ((BaseObject*)a0)->desc->m18((BaseObject*)a0, self);
    }
    if (s0 != 0) {
        ((BaseObject*)s0)->desc->m17((BaseObject*)s0, self);
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



void func_001CAC30(Agent* self, Contact03* out)
{
    if (self->fC04 != 0) {
        f32 a = D_00274CF4;
        f32 b = D_00274CF8[0];
        out->f94 = a;
        out->f98 = b;
    } else {
        if (((s32 (*)(Agent*, void*))self->desc06()->m56)(self, out) != 0) {
            f32 t = self->fBE8;
            out->f98 = 0.0f;
            out->f94 = t;
        } else {
            out->f94 = 0.0f;
            out->f98 = 0.0f;
        }
    }
}

void func_001C5388(Agent*, s32, ContactLimit03*);

void func_001CACB0(Agent* self, s32 flags, ContactLimit03* out)
{ func_001C5388(self, flags, out);
    if (self->fC04 != 0) { if ((flags & 0x12) == 0x12) { if (0.7f < out->contact->v80.z) { out->limit = 0; } } } }

void func_001CAD28(Agent* self, f32 value) { self->f74C = value * 0.017453294f; }

void func_001CBE20(void* self, s32 value);

void func_001CAD40(Agent* self, s32 value)
{
    AddItemKeeperStateTrigger(self->f720, value);
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
        AddTurningColliderProbeContact(a0, a1, a4, a5);
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
                AddMeshContacts(a1->radius3CC, a1, (u8*)a1 + 0x140, (Collider*)e->obj,
                              ((Collider*)e->obj)->tree.count,
                              (s32)((Collider*)e->obj)->tree.nodes, 0, (u8*)a0 + 0xAAC);
            } else if (a3 != 0) {
                func_00186BA8((Collider*)e->obj, a1, a2, a3, a4, (u8*)a0 + 0xAAC);
            }
        }
    }
}

s32 func_001300E8(void* obj, s32 kind);
void func_00175170(void* obj, s32 a, s32 b);

void func_001CAEE0(u8* self, PlacedObject* other)
{
    other->desc02()->m20(other, (Vec02*)(self + 0xAB0));
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
    if (GetAgentRosterState(self) == 0) {
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


s32 func_001CB578(Agent* self)
{
    s32 r = 0;
    Player* g;
    if (self->fB7C != 0) {
        goto set;
    }
    if (self->fB80 != 0) {
        r = 1;
    } else {
        g = g_player;
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

void func_001CBEE8(void* self, s32 arg);

void func_001CB648(ItemKeeper* self, Agent* value)
{
    u32 n;

    if (self->owned.count == 0) {
        SetItemKeeperState(self, 0);
    }
    n = self->owned.count;
    if (n < 0x10) {
        self->owned.found[n] = value;
        self->owned.count = n + 1;
    }
}

void func_001CB6A8(ItemKeeper* self, s32 value) { u32 i = self->owned.wantedCount; if (i < 16) { self->owned.wanted[i] = value; self->owned.wantedCount = i + 1; } }

void func_001CB6D0(ItemKeeper* self, s32 value) { u32 i = self->listed.wantedCount; if (i < 16) { self->listed.wanted[i] = value; self->listed.wantedCount = i + 1; } }

void func_001CBEE8(void* self, s32 arg);
void func_0018D800(void* dst, void* src, s32 count);

void func_001CB6F8(ItemKeeper* self, Agent* value)
{
    s32 i = 0;
    if (self->owned.count > 0) {
        for (; i < self->owned.count; i++) {
            if (self->owned.found[i] == value) break;
        }
        if (i >= self->owned.count) return;
        s32 n = self->owned.count;
        if (i < n) {
            s32 m = n - 1;
            self->owned.count = m;
            Agent** d = &self->owned.found[i];
            CopyMemory(d, d + 1, (m - i) * 4);
            if (self->owned.count <= 0) {
                SetItemKeeperState(self, 3);
            }
        }
    }
}


Agent* func_0015A448(u32 a, s32 id, ItemKeeper* c);

void func_001CB7A0(ItemKeeper* a0)
{
    for (s32 i = 0; i < a0->owned.wantedCount; i++) {
        Agent* r = FindFirstObjectByIdMode4((u32)g_currentWorld, a0->owned.wanted[i], a0);
        if (r != 0) {
            s32 n = a0->owned.count;
            if ((u32)n < 16) {
                a0->owned.found[n] = r;
                a0->owned.count = n + 1;
                r->f720 = a0;
            }
        }
    }
    for (s32 i = 0; i < a0->listed.wantedCount; i++) {
        Agent* r = FindFirstObjectByIdMode4((u32)g_currentWorld, a0->listed.wanted[i], a0);
        if (r != 0) {
            s32 n = a0->listed.count;
            if ((u32)n < 16) {
                a0->listed.found[n] = r;
                a0->listed.count = n + 1;
                            }
        }
    }
}

// The 48-byte record CreateRecord2505C0 makes for a group of C62 objects: the keeper at +0x2C.
struct ItemTimeoutGroup {
    u8 pad0[0x2C];
    void* keeper;           // 0x2C
};
// What GatherAnimationEventObjects hands back for one agent: the objects and their count.
struct GatheredObjects {
    s32 count;
    C62** items;
};

void func_0018D608(void);
void func_0018D6F0(void);
void* func_0018D6A8(s32 size);
void func_0012D1B0(void* a, void* b, s32* c, void** d);
void* func_001EFA30(void);
void func_001EFA60(void* a, void* b);

void func_001CB8B8(ItemKeeper* self)
{
    GatheredObjects* arr;
    s32 i;
    s32 j;
    s32 k;
    s32 m;

    PushBackMemoryMark();
    arr = (GatheredObjects*)AllocateZeroedBackMemory(self->owned.count * 8);
    for (i = 0; i < self->owned.count; i++) {
        Agent* agent = self->owned.found[i];
        if (agent->f750 != 0) {
            GatherAnimationEventObjects(agent->f750, agent, &arr[i].count, (void**)&arr[i].items);
        }
    }
    for (i = 0; i < self->owned.count; i++) {
        GatheredObjects* e = &arr[i];
        for (j = 0; j < e->count; j++) {
            C62* node = e->items[j];
            if (node->group == 0) {
                node->group = CreateRecord2505C0();
                ((ItemTimeoutGroup*)node->group)->keeper = self;
                AppendToSmallList(node->group, node);
                if (node->id2E0 != -1) {
                    for (k = i + 1; k < self->owned.count; k++) {
                        GatheredObjects* e2 = &arr[k];
                        for (m = 0; m < e2->count; m++) {
                            C62* item = e2->items[m];
                            if (item->id2E0 == node->id2E0) {
                                item->group = node->group;
                                AppendToSmallList(node->group, item);
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


void func_001CBAA0(ItemKeeper* a0)
{
    ItemKeeper* self = a0;
    if (self->state == 3) {
        return;
    }
    if (self->queued != 0) {
        return;
    }
    {
        s32 one = 1;
        void* owner = *(void**)&g_currentWorld;
        self->queued = one;
        AppendQueuedCall(owner, (void*)(void (*)(void*))UpdateItemKeeper, self, -1, 0);
    }
}

void* func_001CBAF8(ItemKeeper* self)
{
    Agent* item = self->owned.found[0];
    return item->desc08()->m62(item);
}


s32 func_001CBCB8(void* self);
s32 func_001CBB88(void* self);
void func_001CBEE8(void* self, s32 arg);

void func_001CBB20(ItemKeeper* self)
{
    s32 v;

    self->queued = 0;
    if (self->state != 3) {
        self->anyFree = IsAnyItemKeeperMemberFree(self);
        for (;;) {
            v = ChooseItemKeeperState(self);
            if (v == self->state) {
                break;
            }
            SetItemKeeperState(self, v);
        }
    }
}

s32 func_001CBD58(ItemKeeper* self);
void func_001BFCD8(s32 sound, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);


s32 func_001CBB88(ItemKeeper* self)
{
    s32 state = self->state;
    s32 i;

    switch (state) {
    case 0:
        if (self->anyFree != 0) {
            for (i = 0; i < self->owned.count; i++) {
                if (IsObjectOfKind(self->owned.found[i], 9) == 0) {
                    break;
                }
            }
            if (i >= self->owned.count) {
                StartSoundEffect(0x3F, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
            state = 2;
        }
        break;
    case 1:
        if (self->anyFree != 0) {
            state = 2;
        } else if (PollItemKeeperMembers(self) != 0) {
            state = 0;
        }
        break;
    case 2:
        if (self->anyFree == 0) {
            state = 1;
        }
        break;
    }
    return state;
}

s32 func_001CBCB8(ItemKeeper* self)
{
    s32 i = 0;
    Agent** p = self->owned.found;
    for (;;) {
        if (!(i < self->owned.count)) {
            return 0;
        }
        Agent* it = *p;
        if (it->desc08()->m57(it) != 0) {
            break;
        }
        p++;
        i++;
    }
    if (!(i < self->owned.count)) {
        return 0;
    }
    {
        PlacedObject* r = (PlacedObject*)GetItemKeeperTarget(self);
        if (r != 0) {
            self->targetPos = r->v140;
        }
    }
    return 1;
}

s32 func_001CBD58(ItemKeeper* a0)
{
    s32 result = 1;
    for (s32 i = 0; i < a0->owned.count; i++) {
        Agent* o = a0->owned.found[i];
        s32 v = o->desc08()->m58(o);
        switch (v) {
        case 1: break;
        case 0: result = 0; break;
        case 2: return 1;
        }
    }
    return result;
}

void func_001CBE20(ItemKeeper* self, s32 value) { for (s32 i = 0; i < self->triggerCount; i++) if (value == self->triggers[i]) return; s32 i = self->triggerCount; if ((u32)i < 4) { s32 next = i + 1; self->triggers[i] = value; self->triggerCount = next; } }

void func_00123AB0(void* object, s32 mode);

void func_001CBE70(ItemKeeper* self, s32 mode)
{
    for (s32 i = 0; i < self->triggerCount; i++) {
        SetStateTriggerStateFromMessage((void*)self->triggers[i], mode);
    }
}


extern f32 D_00261858[];

f32 func_001EAAE0(f32 a, f32 b);
void func_001BF0D8(void* p);
void* func_001BEEF8(s32 kind);
void func_001CBE70(ItemKeeper* self, s32 a);
void func_001CC120(ItemKeeper* self);

void func_001CBEE8(ItemKeeper* self, s32 ns)
{
    s32 i;
    if (self->state == ns)
        return;
    switch (self->state) {
    case 2:
        RemoveSoundLevelAndRecompute(self->soundLevel);
        i = 0;
        self->soundLevel = 0;
        if (self->owned.count > 0) {
            Agent** p = self->owned.found;
            do {
                Agent* it = *p;
                f32 t = g_gameClock[1];
                i++;
                f32 r = RandomFloatInRange(D_00274D18[0], D_00274D18[1]);
                it->fC00 = g_gameClock[1] + r;
                p++;
            } while (i < self->owned.count);
        }
        break;
    case 1: {
        s32 j = 0;
        if (self->owned.count > 0) {
            Agent** p = self->owned.found;
            do {
                f32 t = g_gameClock[1];
                j++;
                f32 r = RandomFloatInRange(D_00274D08[0], D_00274D08[1]);
                (*p)->fBF4 = g_gameClock[1] + r;
                p++;
            } while (j < self->owned.count);
        }
        break;
    }
    }
    switch (ns) {
    case 2:
        i = 0;
        self->soundLevel = PushSoundLevel(0x6B);
        SetItemKeeperTriggerStates(self, 0);
        if (self->owned.count > 0) {
            Agent** p = self->owned.found;
            do {
                Agent* it = *p;
                if (it->desc08()->m57(it) != 0) {
                    it->fBF8 = g_gameClock[1];
                } else {
                    f32 r = RandomFloatInRange(D_00274D10[0], D_00274D10[1]);
                    it->fBF8 = g_gameClock[1] + r;
                }
                i++;
                p++;
            } while (i < self->owned.count);
        }
        break;
    case 1:
        func_001CC120(self);
        break;
    case 0:
        SetItemKeeperTriggerStates(self, 1);
        break;
    case 3:
        SetItemKeeperTriggerStates(self, 2);
        break;
    }
    self->state = ns;
    self->stateSince = g_gameClock[1];
}

INCLUDE_RODATA(D_0024DA94);

ASM_FUNC(func_001CC120);

ASM_FUNC(func_001CC3F8);




