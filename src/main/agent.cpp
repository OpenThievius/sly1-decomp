// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "shapes.h"
#include "vu0.h"
#include "object_message.h"
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
#include "owner_message.h"
#include "anim_curve.h"
#include "vu0.h"

extern f32 g_gameTime[];

// A quadratic in t (c[0] + t * (c[1] + t * c[2])) on 16 bytes, as in hit_count_collider: the file's
// .data starts on 16 (0x274C18 to 0x274C20 is padding after the previous file's), and 0x274C54
// to 0x274C5F is the quadratic's own.
f32 ArctangentOfRatio(f32 a, f32 b);
f32 WrapAngle(f32 a);
void* ResolveAgentClip(Agent* self, void* arg);
void* ResolveAgentClip(Agent* self, s32 arg);

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

extern u8 g_flagTable[];
void InitTurningCollider(TurningCollider* self);
s32 TakeFlagTableIndex(FlagTable* p);
void SetSwitchedColliderEnabled(Agent* self, s32 a);

#define F(T, o) (*(T*)((u8*)self + (o)))

void InitAgent(Agent* self)
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

void LoadCollider(Agent* self, void* a1);
void ResolveObjectLinks(Agent* self, s32 a1, void* a2);
void ResolveAgentClips(Agent* self);
void ResolveAgentSecondaryClips(Agent* self);

void LoadAgent(Agent* self, void* a1)
{
    LoadCollider(self, a1);
    ResolveObjectLinks(self, 1, D_00274C20);
    ResolveAgentClips(self);
    ResolveAgentSecondaryClips(self);
}

void CopySwitchedCollider(Agent* self, s32 v);

void CopyAgent(Agent* self, s32 v)
{
    s32 b = self->fB10;
    s32 a = (s32)self->f720;
    CopySwitchedCollider(self, v);
    self->fB10 = b;
    self->f720 = (void*)a;
    self->fB74 = v;
}

void PostLoadPlacedObject(Agent* self);
s32 FindFirstObjectByIdMode4(s32 a, s32 b, Agent* self);
void PickAgentSecondaryTarget(Agent* self);
s32 FindFirstObjectById(s32 a, s32 b, s32 c, Agent* self);
void FindOrBuildMemberGroup(s32* p, Agent* self);

void PostLoadAgent(Agent* self)
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

void RemoveAgentFromParent(Agent* self)
{
    self->desc->m03(self);
}

void StartTurningCollider(TurningCollider* self);
void* CreateItemKeeper(void* host);
void AddItemKeeperMember(void* a, void* b);
void ResolveAgentClips(void* self);
void* FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
void* FindFirstObjectByIdGathered(void* host, s32 a1, s32 a2, void* ctx);
void SetTurningColliderGravityScale(void* self, f32 v);
void ChangeAgentState(void* node, s32 kind, s32 flag);
s32 TestFlagTableBit(u8* table, s32 v);
void* AppendQueuedCall(void* host, void* fn, void* ctx, s32 a3, s32 a4);

extern u8 g_flagTable[];

void StartAgent(Agent* self)
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
        AppendQueuedCall(self->world, (void*)RemoveAgentFromParent, self, 0, 0);
    }
}

s32 TestCollidersMayContact(Agent* self, Collider* obj);
s32 IsObjectInPool(void* p, Collider* obj);

s32 TestAgentMayContact(Agent* self, Collider* obj)
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

void RegisterSwitchedCollider(void* self);
void AddItemKeeperMember(void* list, void* value);

void RegisterAgent(Agent* self)
{
    RegisterSwitchedCollider(self);
    if (self->f720 != 0) {
        AddItemKeeperMember(self->f720, self);
    }
}


void UnregisterSwitchedCollider(Agent* self);
void StopAnimationPlayer(void* obj);
void RemoveItemKeeperMember(void* a, Agent* b);

void UnregisterAgent(Agent* self)
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

extern f32 g_gameClock[];
extern f32 g_unitRange[];

static inline f32 LimitToUnitRange(f32 g)
{
    f32* range = g_unitRange;
    f32 lo = range[0];
    f32 hi = range[1];
    f32 r;
    if (g < lo) {
        r = lo;
    } else if (hi < g) {
        r = hi;
    } else {
        r = g;
    }
    return r;
}

typedef int Quadword128 __attribute__((mode(TI)));
void StoreFloatAsQuadword(void* out, f32 f);
void* CopyQuadword(void* out, void* in);
Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);
void* StoreQuadword(void* dst, Quadword128 v);

// k times the vector at p, into dst (the quadword helpers' product).
static inline void StoreScaledQuadword(Vec02* dst, f32 k, u8* p)
{
    Quadword128 t;
    StoreFloatAsQuadword(&t, k);
    Quadword128 tv = t;
    Quadword128 u;
    CopyQuadword(&u, p);
    StoreQuadword(dst, ScaleQuadword(tv, u));
}
f32 Arccosine(f32 x);
void AddColliderForce(Agent* self, Vec02* v);
void TurnColliderTowardRotation(Agent* self, Mat02* m, void* rate, f32 dt);
void SteerColliderTowardPosition(Agent* self, s32 a, s32 b, Vec02* target, s32 c, f32 dt);
void SteerColliderTowardRotation(Agent* self, Mat02* m, void* a, const Vec02* b, void* c, f32 dt);
void StepTurningCollider(Agent* self, f32 dt);
void* CopyBytes(void* dst, void* src, s32 n);
void ClampVectorLength(Vec02* in, Vec02* out, f32 max);
void func_00130540(Vec02* a, Vec02* b, Vec02* c, Vec02* d, Vec02* outA, Vec02* outB, s32 e, f32 t, f32 u, f32 w);
typedef void (*AgentMotionFn)(void* self, Agent* agent, s32 a, s32 b, Vec02* out, f32 t, f32 u);

void func_001C75B0(Agent* self, f32 dt)
{
    if (F(s32, 0xB78) != 0) {
        Vec02 motion;
        Vec02 v;
        u8* ap = (u8*)self->f7E0;
        u8* src = *(u8**)(*(u8**)(*(u8**)(ap + 8) + 0x9C) + 4);
        (**(AgentMotionFn**)src)(src, self, 0, 0, &motion, *(f32*)(ap + 0x14), *(f32*)(ap + 0x18));
        Vu0::Q(v) = Vu0::DivX(Vu0::Add(Vu0::Vec::Of(motion), Vu0::Vec::Of(self->v640)), Vu0::Vec::Scalar(dt)).q;
        Vu0::Q(v) = Vu0::RotateMembers(self->m660, Vu0::Q(v));
        AddColliderForce(self, &v);
        TurnColliderTowardRotation(self, &self->m660, &self->f6E0, g_gameClock[2]);
    } else if (self->fB1C != 0) {
        Vec02 v;
        Mat02 m2;
        Mat02 m;
        f32 a = __builtin_fabsf(Arccosine(Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->rot.r[0]), Vu0::Q(self->m660.r[0])))));
        f32 k = LimitToUnitRange(D_00274C50.c[0] + a * (D_00274C50.c[1] + a * D_00274C50.c[2]));
        if (self->f724 == 12) {
            f32 d = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->vA50), Vu0::Q(self->v140))));
            f32* q = &F(f32, 0xB30);
            k = k * LimitToUnitRange(q[0] + d * (q[1] + d * q[2]));
        }
        u128 s = Vu0::Scalar(-k);
        Vu0::Q(m.r[0]) = Vu0::MulX(Vu0::Q(self->m110.r[0]), s);
        Vu0::Q(m.r[1]) = Vu0::MulX(Vu0::Q(self->m110.r[1]), s);
        Vu0::Q(m.r[2]) = Vu0::MulX(Vu0::Q(self->m110.r[2]), s);
        CopyBytes(&m2, &m, 0x30);
        Vu0::Q(v) = Vu0::Rotate(m2, Vu0::Q(self->v640));
        SteerColliderTowardPosition(self, 0, 0, &v, F(s32, 0x210), dt);
        TurnColliderTowardRotation(self, &self->m660, &self->f6E0, g_gameClock[2]);
    } else if (g_gameTime[0] < F(f32, 0xBA4)) {
        Vec02 p;
        Vec02 w;
        Vec02 v;
        f32 left = F(f32, 0xBA4) - g_gameTime[0];
        func_00130540(&self->pos, &self->v150, &F(Vec02, 0xBB0), &F(Vec02, 0xBC0), &p, &w, 0, left, left <? dt, 1.0f);
        Vu0::Q(v) = Vu0::DivX(Vu0::Sub(Vu0::Q(w), Vu0::Q(self->v150)), Vu0::Scalar(dt));
        ClampVectorLength(&v, &v, 20000.0f);
        AddColliderForce(self, &v);
        TurnColliderTowardRotation(self, &self->m660, &self->f6E0, dt);
    } else if (self->f724 == 16 && self->fA6C != 0) {
        Vec02 q2;
        Vec02 q;
        f32 x;
        u8* ap = (u8*)self->f7E0;
        if (ap != 0) {
            x = *(f32*)(ap + 0x14) / *(f32*)(*(u8**)(ap + 8) + 0x34);
        } else {
            x = 1.0f;
        }
        f32 k = LimitToUnitRange(D_00274C60.c[0] + x * (D_00274C60.c[1] + x * D_00274C60.c[2]));
        StoreScaledQuadword(&q, k, (u8*)&D_00274C70);
        StoreScaledQuadword(&q2, k, (u8*)&D_00274C80);
        SteerColliderTowardRotation(self, &self->m660, &q, &D_00248D30, &q2, dt);
        AddColliderForce(self, &self->gravity);
    } else {
        StepTurningCollider(self, dt);
    }
}

f32 func_001C7A60(Agent* self)
{
    PlacedObject* other = (PlacedObject*)self->desc08()->m62(self);
    if (other == 0) {
        return 0.0f;
    }
    Vec02 d;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(other->v140), Vu0::Q(self->v140));
    f32 a = ArctangentOfRatio(d.y, d.x);
    return WrapAngle(a - ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x));
}

s32 IsAgentFacingBlocked(void* self);
void BuildYawPitchMatrix(f32 a, f32 b, void* out);
void BuildAxisAngleMatrix(void* table, f32 x, void* out);

void SetAgentFacingAngles(Agent* self, f32 x, f32 y)
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

void ChangeAgentState(Agent* self, s32 a1, s32 a2);

void SettleAgentState(Agent* self)
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

extern f32 g_frameDt;
void func_00128598(f32 a, f32 b, Agent* self, s32 c, s32 d, f32* e, f32* f, f32* g);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);

void func_001C7BE8(Agent* self)
{
    f32 out[3];
    f32 zero = 0.0f;
    out[1] = zero;
    func_00128598(g_frameDt, self->f638, self, 0, 0, &out[0], self->fB1C ? &out[1] : 0, &out[2]);
    f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(self->v640)));
    if (0.0001f < out[2] && 0.0001f < len) {
        self->f754->speed *= len / out[2];
    }
    f32 y = out[1];
    SetAgentFacingAngles(self, out[0], y);
}

void UpdateTurningCollider(Collider* self);
s32 FindColliderFloorContact(Agent* self, s32 a, s32* out);
void func_001CAF38(Agent* self);
void ClearRootTries(Agent* self);
void BuildShortestArcRotation(const Vec02* from, Vec02* to, Mat02* out);
extern f32 D_00274AD0[];
extern const Vec02 D_00248D30;
s32 IsObjectAttached(Collider* a);
void QueueItemKeeperUpdate(ItemKeeper* a0);
void SetAgentPrimaryTarget(Agent* self, s32 value);
void ApplyPendingAgentChanges(Agent* self);

struct AgentBody {
    u8 pad00[0x80];
    Vec02 v80;              // 0x80
};

struct AgentLinks {
    u8 pad00[0x50];
    s32 state;              // 0x50
    u8 pad54[0x58 - 0x54];
    s32 count;              // 0x58
    Agent* found[16];       // 0x5C
};

static inline void MulRotationInto(Agent* self, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::RotateUntied(a, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateUntied(a, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateUntied(a, Vu0::Q(b.r[2]));
    r.r[2] = z;
    self->m660 = r;
}

void UpdateAgent(Agent* self)
{
    Vec02 push;
    Mat02 spin;
    Mat02 arc;
    s32 kind;
    UpdateTurningCollider(self);
    if (*(s32*)((u8*)self + 0xB44) != 0) {
        PickAgentSecondaryTarget(self);
    }
    void* held = self->fB50;
    if (held == 0) {
        if (((AgentLinks*)self->f720)->state != 2) {
            Player* target = (Player*)self->desc08()->m62(self);
            if (target != 0 && target == g_player) {
                if (target->f2750 != 0 && IsObjectAttached((Collider*)target->f2750) != 0) {
                    SetAgentPrimaryTarget(self, (s32)g_player->f2750);
                    if (self->desc08()->m57(self) == 0) {
                        SetAgentPrimaryTarget(self, 0);
                    } else {
                        for (s32 i = 0; i < ((AgentLinks*)self->f720)->count; i++) {
                            if (((AgentLinks*)self->f720)->found[i] != self) {
                                SetAgentPrimaryTarget(self, (s32)g_player->f2750);
                            }
                        }
                    }
                }
            }
        }
    } else if (IsObjectAttached((Collider*)held) == 0 || ((AgentLinks*)self->f720)->state != 2) {
        SetAgentPrimaryTarget(self, 0);
    }
    if (self->fB8C != 0 && FindColliderFloorContact(self, 0, 0) != 0) {
        ((void (*)(Agent*))((void**)self->desc)[100])(self);
    }
    ApplyPendingAgentChanges(self);
    SettleAgentState(self);
    AnimationPlayer* player = self->f7E0;
    if (player != 0 && player->anim->f9C != 0) {
        PositionCurve* curve = player->anim->f9C->pos;
        if (curve != 0) {
            curve->vt->eval(curve, self, player->time, player->speed, 0, 0, &self->v640);
            u128 neg = Vu0::FromFloat(-1.0f);
            Vu0::Q(self->v640) = Vu0::MulX(Vu0::Q(self->v640), neg);
            Vu0::Q(push) = neg;
        } else {
            self->v640 = D_00248D30;
        }
    } else {
        self->v640 = D_00248D30;
    }
    self->desc08()->m5E(self, 0);
    ((void (*)(Agent*))self->desc08()->m5A)(self);
    if (self->f720 != 0) {
        QueueItemKeeperUpdate((ItemKeeper*)self->f720);
    }
    func_001CAF38(self);
    if (*(s32*)((u8*)self + 0xC08) != 0) {
        AgentBody* floor = (AgentBody*)FindColliderFloorContact(self, 0, &kind);
        if (floor != 0) {
            Vec02 scale;
            u128 k = Vu0::FromFloatAt(D_00274AD0[kind]);
            Vu0::Q(push) = Vu0::MulX(Vu0::Q(floor->v80), k);
            Vu0::Q(scale) = k;
        } else {
            push = g_unitZVector;
        }
        BuildAxisAngleMatrix((void*)&g_unitZVector, self->f638, &spin);
        BuildShortestArcRotation(&g_unitZVector, &push, &arc);
        MulRotationInto(self, arc, spin);
    }
    ClearRootTries(self);
    self->fB14 = 0;
}

extern f32 g_gameClock[];
s32 GetAgentRosterState(Agent* self);
s32 HasAgentReachedPathEnd(Agent* self);

s32 ChooseAgentState(Agent* self)
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

void SnapPointToOwnerGraph(s32 graph, Vec02* in, Vec02* out);

void func_001C8418(Agent* self, Vec02* p)
{
    Vec02 t;
    self->vA40 = *p;
    t = self->vA40;
    if (self->f928 != 0) {
        SnapPointToOwnerGraph(self->f928, &t, &t);
    }
    if (self->fA60 != 0) {
        u128 d = Vu0::Sub(Vu0::Q(self->vA50), Vu0::Q(t));
        s32 far = D_00274C90 < Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
        if (far) {
            self->fA60 = 0;
        }
    }
    if (self->fA60 == 0) {
        self->vA50 = t;
    }
}

s32 HasAgentReachedPathEnd(Agent* self)
{
    s32 result = 0;
    if (self->fA60 != 0) {
        result = self->f930 == self->f92C;
    }
    return result;
}


s32 IsObjectOfKind(void* node, s32 kind);

s32 IsAgentPathBlocker(void* unused, Collider* self)
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

s32 FindOwnerGraphPath(s32 graph, Vec02* a, Vec02* b, s32 max, Vec02* out);
void GatherCollidersInBox(World* world, s32 p1, Vec02* lo, Vec02* hi, s32 (*filter)(void*, Collider*), Agent* self, s32* n, Collider*** list);
s32 FindNearestSpanObject(s32 flags, Vec02* a, Vec02* b, s32 count, Collider** list, ColliderSpan* out);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);

// Whether two points are within reach of each other in the ground plane (x and y).
static inline s32 IsNearPoint(Vu0::Vec a, Vu0::Vec b, f32 reach)
{
    return Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(a, b), Vu0::Sub(a, b)))) < reach;
}

// The game clock's time (its second word), read through the clock's address.
static inline f32 ClockTime(const f32* clock) { return clock[1]; }

void func_001C8590(Agent* self)
{
    if (F(s32, 0xA60) != 0) {
        if (!(D_00274C98[0] < ClockTime(g_gameClock) - F(f32, 0xA64))) return;
    }
    if (F(s32, 0xB90) != 0) {
        F(s32, 0x92C) = 2;
        u128 pos = Vu0::Q(self->v140);
        Vu0::Q(F(Vec02, 0x940)) = pos;
        f32 maxLen = __builtin_fabsf(F(f32, 0xB94));
        u128 goal = Vu0::Q(self->vA50);
        f32 len = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(goal, pos), Vu0::Sub(goal, pos))));
        Vec02 a;
        if (maxLen < len) {
            f32 t = maxLen / len;
            Vu0::Q(a) = Vu0::MulXSum(goal, Vu0::Scalar(t), pos, Vu0::Scalar(1.0f - t));
        } else {
            Vu0::Q(a) = goal;
        }
        Vec02 b;
        if (self->f928 != 0) {
            SnapPointToOwnerGraph(self->f928, &a, &b);
        } else {
            b = a;
        }
        f32 reach = (maxLen <? len) * 0.5f;
        Vec02 c = b;
        while (IsNearPoint(Vu0::Vec::Of(c), Vu0::Vec::Of(self->v140), reach)) {
            f32 next = maxLen + 100.0f;
            maxLen = next <? len;
            f32 t = maxLen / len;
            Vu0::Q(c) = Vu0::MulXSum(Vu0::Q(self->vA50), Vu0::Scalar(t), Vu0::Q(self->v140), Vu0::Scalar(1.0f - t));
            SnapPointToOwnerGraph(self->f928, &c, &c);
        }
        PushBackMemoryMark();
        Vec02 d1;
        Vec02 d4;
        ColliderSpan span;
        s32 count;
        Collider** list;
        Vu0::Set(d1, Vu0::MulAddX(Vu0::Q(c), Vu0::Q(D_00248D20), Vu0::Scalar(-500.0f)));
        Vu0::Set(d4, Vu0::MulAddX(Vu0::Q(c), Vu0::Q(D_00248D20), Vu0::Scalar(500.0f)));
        GatherCollidersInBox(self->world, (s32)self, &d1, &d4, IsAgentPathBlocker, self, &count, &list);
        if (FindNearestSpanObject(1, &d4, &d1, count, list, &span) != 0) {
            f32 h = -((f32*)F(void*, 0x388))[(F(s32, 0x6D0) << 2) + 2] - 1.0f;
            if (F(s32, 0xC04) != 0) h += F(f32, 0x6CC);
            Vu0::Q(c) = Vu0::MulAddX(Vu0::Q(span.q[0]), Vu0::Q(D_00248D20), Vu0::Scalar(h));
        }
        PopBackMemoryMark();
        F(Vec02, 0x950) = c;
    } else {
        F(s32, 0x92C) = 0;
        if (self->f928 != 0) {
            F(s32, 0x92C) = FindOwnerGraphPath(self->f928, &self->v140, &self->vA50, 0x10, (Vec02*)((u8*)self + 0x940));
        }
        if (F(s32, 0x92C) == 0) {
            F(s32, 0x92C) = 2;
            F(Vec02, 0x940) = self->v140;
            F(Vec02, 0x950) = self->vA50;
        }
    }
    F(s32, 0x930) = 0;
    F(s32, 0xA60) = 1;
    F(f32, 0xA64) = ClockTime(g_gameClock);
}

static inline f32 ClampTo(f32 v, const f32* r)
{
    f32 l = r[0];
    f32 h = r[1];
    f32 out;
    if (v < l)
        out = l;
    else if (h < v)
        out = h;
    else
        out = v;
    return out;
}

void func_001C8920(Agent* self)
{
    ((void (*)(Agent*))self->desc08()->m5F)(self);
    for (;;) {
        if (!(self->f930 < self->f92C)) break;
        s32 i = self->f930;
        u128 d = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*(Vec02*)((u8*)self + 0x940 + (i << 4))));
        s32 far = D_00274C94 < Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
        if (far) break;
        self->f930 = i + 1;
    }
    Vec02 dir;
    if (self->f930 < self->f92C) {
        Vu0::Set(dir, Vu0::Sub(Vu0::Q(*(Vec02*)((u8*)self + 0x940 + (self->f930 << 4))), Vu0::Q(self->v140)));
    } else {
        s32 m = self->f92C;
        Vu0::Set(dir, Vu0::Sub(Vu0::Q(*(Vec02*)((u8*)self + 0x930 + (m << 4))), Vu0::Q(*(Vec02*)((u8*)self + 0x920 + (m << 4)))));
    }
    f32 yaw;
    if (1.0f < Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(dir), Vu0::Q(dir))))) {
        yaw = ArctangentOfRatio(dir.y, dir.x);
    } else {
        yaw = self->f638;
    }
    f32 pitch;
    if (F(s32, 0xB1C) == 0) {
        pitch = 0.0f;
    } else {
        u128 e = Vu0::Sub(Vu0::Q(self->vA50), Vu0::Q(self->v140));
        f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(e, e)));
        f32 dz = self->vA50.z - self->v140.z;
        switch (self->f724) {
        case 5: case 6: case 7: case 10: case 12: case 13: case 14: case 15:
            dz += F(f32, 0xB20);
            break;
        }
        f32 g1 = D_00274CA0.c[0] + dist * (D_00274CA0.c[1] + dist * D_00274CA0.c[2]);
        g1 = ClampTo(g1, D_00274CB0.c);
        f32 adz = __builtin_fabsf(dz);
        f32 g2 = D_00274CC0.c[0] + adz * (D_00274CC0.c[1] + adz * D_00274CC0.c[2]);
        g2 = ClampTo(g2, D_00274CD0);
        pitch = g1 * g2 * D_00274CD8[0];
        if (dz < 0.0f) pitch = -pitch;
    }
    SetAgentFacingAngles(self, yaw, pitch);
}

void ConvertOffsetToSpherical(void* a, void* b, f32* x, f32* y, s32 flag);
void SetAgentFacingAngles(void* self, f32 x, f32 y);

void FaceAgentTowardGoalPoint(Agent* self)
{
    f32 x;
    f32 y;
    ConvertOffsetToSpherical((u8*)self + 0xA40, (u8*)self + 0x140, &x, &y, 0);
    SetAgentFacingAngles(self, x, y);
}

void func_001C8418(Agent* self, void* p);
void func_0012C9E8(f32 c, void* a, Agent* b, void* d, void* e, void* f, s32 g);
Entry8B* FindEntryByObjectId(void* a, Agent* b);

void UpdateAgentGoal(Agent* self, s32 flag)
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

void IsAgentNearPathEnd(Agent* self, s32* out) { if (self->fA60 && self->f930 >= self->f92C - 2) { *out = 1; return; } *out = 0; }

void CreateAnimationPlayer(void* self, void* a1, s32 a2, void* a3, s32 a4, void* a5, f32 f0, f32 f1);
void AddAnimationPlayerRecordCallback(void* a0, C62* a1);
s32 GetEffectiveObjectId(Agent* a);
Attachment* FindPlayerAttachmentByOwner(AnimationPlayer* a0, s32 a1);

void CreateAgentAnimationPlayer(Agent* self)
{
    C62* sub = ((C62*)self->fA74);
    if (sub->id2DC != 0) {
        s32 pair[2];
        pair[0] = sub->id;
        pair[1] = (s32)self;
        CreateAnimationPlayer((void*)sub->id2DC, self, 1, pair, 1, &self->f754, 0.0f, 1.0f);
        AddAnimationPlayerRecordCallback(self->f754, ((C62*)self->fA74));
        Attachment* node = FindPlayerAttachmentByOwner(self->f754, GetEffectiveObjectId(self));
        if ((void*)node == self->f1EC) {
            node->mode0 = 5;
        }
        if ((void*)node == self->f1F0) {
            node->mode1 = 5;
        }
    }
}

extern f32 g_frameDt;
s32 HasAnimationDrivenAttachment(Agent* self);
void func_001C7BE8(Agent* self);
void func_00128598(f32 a, f32 b, Agent* self, s32 c, s32 d, f32* e, f32* f, f32* g);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);
void ScheduleItemTimeouts(void* n);
void func_001C8920(Agent* self);
void FaceAgentTowardGoalPoint(Agent* self);

void UpdateAgentState(Agent* self)
{
    self->desc08()->m62(self);
    switch (self->f724) {
    case 0:
    case 16:
        break;
    case 1:
    case 2:
        if (HasAnimationDrivenAttachment(self) != 0)
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
extern f32 g_gameClock[];
void TriggerScriptEvent(void*, s32, s32, void*);

void ChangeAgentState(Agent* self, s32 state, void* context)
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

void ChangeAgentState(Agent* self, s32 mode, s32 value);

void ForceAgentState(Agent* self, s32 mode, s32 value)
{
    if (mode == -1) {
        self->fB88 = 0;
    } else {
        self->fB88 = 1;
        ChangeAgentState(self, mode, value);
    }
}

void StopAnimationPlayer(AnimationPlayer* p);
f32 RandomFloatInRange(f32 a, f32 b);
void SetStateAndNotify(C62* p, s32 z);
void InitContactPairFlags(void* world, Agent* self);

void LeaveAgentState(Agent* self, s32 mode)
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
void SetAnimationPlayerSpeed(AnimationPlayer* t, f32 x);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);
void CreateAgentAnimationPlayer(Agent* self);
s32 CreateAnimationPlayerWithoutPresetTargets(Animation* t, Agent* self, s32 mode, void* out, f32 x, f32 y);
void CreateAnimationPlayer(Animation* t, Agent* self, s32 one, s32* p, s32 mode, void* out, f32 x, f32 y);
s32 GetEffectiveObjectId(Agent* self);
Attachment* FindPlayerAttachmentByOwner(AnimationPlayer* t, s32 q);
void TransformPointBetweenFrames(Agent* self, s32 z, u8* p, Quad4* out);
void ScatterObjectsAtPoint(u8* p, Quad4* v, s32 a, s32 b);
void InitContactPairFlags(s32 p, Agent* self);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherAnimationEventObjects(Animation* t, Agent* self, s32* count, BaseObject*** list);
void RemoveFromSmallList(s32 x, BaseObject* t);
void SetFlagTableBit(u8* p, s32 x);
void FadeOutPlacedObject(Agent* self, f32 x);
f32 RandomFloatInRange(f32 x, f32 y);
void func_001C8920(Agent* self);
void FaceAgentTowardGoalPoint(Agent* self);

extern u8 g_flagTable[];
extern u8 g_scatterController[];

void EnterAgentState(Agent* self, s32 evt, Animation* arg)
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
            CreateAgentAnimationPlayer(self);
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
        TransformPointBetweenFrames(self, 0, self->fB60, &vec);
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
            FadeOutPlacedObject(self, f);
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

s32 GetAgentRosterState(Agent* self) { if (!self->f720) return 3; return *(s32*)((u32)self->f720 + 0x50); }

#include "object_message.h"

struct AgentHit {
    PlacedObject* obj;      // 0x00: what was hit
    u8 pad04[0x0C - 0x04];
    s32 flags;              // 0x0C
    s32 mask;               // 0x10
    u8 pad14[0x28 - 0x14];
    f32 height;             // 0x28
    u8 pad2C[0x30 - 0x2C];
    Vec02 push;             // 0x30
};

struct AgentNotice {
    Agent* self;
    PlacedObject* obj;
};

s32 HandleObjectEvent(Agent* self, AgentHit* ev);
void TurnColliderTowardHeading(Agent* self);
void ChangeAgentState(Agent* self, s32 state, void* arg);
extern const Vec02 g_unitXVector;

s32 HandleAgentObjectEvent(Agent* self, AgentHit* ev)
{
    SlotMessage msg;
    if (self->fBD8 != 0) {
        return 1;
    }
    if (self->fB0C != 0 && (ev->obj->desc->flags & 2) != 0 && IsObjectInPool(self->fB0C, (Collider*)ev->obj) != 0) {
        return 1;
    }
    s32 handled = HandleObjectEvent(self, ev);
    if (handled == 0 || (ev->flags & 0x20) == 0) {
        return handled;
    }
    void* key = 0;
    s32 i = self->fAC4;
    while (--i >= 0) {
        Pend08* r = &self->fAC8[i];
        if (r->f00 & ev->mask) {
            key = r->obj;
            break;
        }
    }
    if (*(s32*)((u8*)self + 0xBDC) != 0) {
        if (0.0001f < Vu0::ToFloat(Vu0::Length(Vu0::Q(ev->push)))) {
            self->fB7C = 0;
            f32 heading = ArctangentOfRatio(-ev->push.y, -ev->push.x);
            f32 turn = WrapAngle(heading - self->f638);
            SetAgentFacingAngles(self, WrapAngle(self->f638 + turn * *(f32*)&self->fBD0), self->fB24);
            TurnColliderTowardHeading(self);
        }
    }
    ChangeAgentState(self, self->fA68 > 0 ? 16 : 11, key);
    if (self->fB00 != 0) {
        msg.kind = 6;
        Vu0::Q(msg.vb) = Vu0::Q(self->v140);
        msg.vb.z = ev->height;
        if (ev->obj != 0 && (ev->obj->desc->flags & 1) != 0) {
            Vu0::Q(msg.va) = Vu0::DivX(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(ev->obj->v140)), Vu0::Length(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(ev->obj->v140))));
        } else {
            Vu0::Set(msg.va, Vu0::NormalizeOrMoved(Vu0::Q(ev->push), Vu0::Q(g_unitXVector)));
        }
        ((BaseObject*)self->fB00)->desc->m1B((BaseObject*)self->fB00, &msg);
    }
    ((AgentNotice*)&msg)->self = self;
    ((AgentNotice*)&msg)->obj = ev->obj;
    self->desc->m0E(self, 0x17, &msg);
    return handled;
}

// What slot 76 is asked about: a kind and the object concerned.
struct AgentRequest { s32 kind00; BaseObject* ref04; };

void* FillMemory(void* p, s32 v, s32 n);
s32 FindNodeForQuery(void* p, s32 a, s32 b);

s32 AcceptAgentRequest(Agent* self, AgentRequest* req)
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

s32 IsAgentRequestBlocked(Agent* self) { return self->fBD8 != 0; }



void StopAnimationPlayer(AnimationPlayer* c);
void ChangeAgentState(Agent* self, void* arg, s32 mode);

void ApplyPendingAgentChanges(Agent* self) {
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

f32 ClampToRange(void* range, f32 x);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);

void func_001C9AF8(Agent* self)
{
    s32 last = self->f92C - 1;
    s32 n = self->f930;
    n = (n < last) ? n : last;
    Vec02 target;
    Vu0::Q(target) = Vu0::Q(*(Vec02*)((u8*)self + 0x940 + (n << 4)));
    Vec02 d;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(target), Vu0::Q(self->v140));
    f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(d), Vu0::Q(d))));
    f32 t = ClampToRange((u8*)self + 0xB9C, dist / __builtin_fabsf(F(f32, 0xB94)));
    f32 time = t * F(f32, 0xB98);
    Vec02 vel;
    Vu0::Q(vel) = Vu0::MulXSum(Vu0::Q(d), Vu0::Scalar(1.0f / time), Vu0::Q(F(Vec02, 0x350)), Vu0::Scalar(time * -0.5f));
    self->desc02()->m20(self, &vel);
    F(f32, 0xBA4) = g_gameTime[0] + time;
    f32 speed = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(d), Vu0::Q(d))));
    F(Vec02, 0xBB0) = target;
    u128 pos = Vu0::MulAddX(Vu0::Q(vel), Vu0::Q(F(Vec02, 0x350)), Vu0::Scalar(time));
    Vu0::Q(F(Vec02, 0xBC0)) = pos;
    if (1.0f < speed) {
        f32 ang = ArctangentOfRatio(d.y, d.x);
        if (F(f32, 0xB94) < 0.0f) ang += 3.14159265f;
        SetAgentFacingAngles(self, ang, 0.0f);
        Vec02 w;
        u128 s = Vu0::FromFloat(-1.0f);
        u128 r = Vu0::RotateTransposed(F(Mat02, 0x660), Vu0::MulX(Vu0::Q(vel), s));
        Vu0::Q(w) = s;
        Vu0::Q(F(Vec02, 0x640)) = r;
    } else {
        F(Vec02, 0x640) = D_00248D30;
    }
}

f32 GetAnimationMarkerTime(void* obj, s32 id);
void SeekAnimationPlayer(void* obj, s32 a1, f32 fa, f32 fb);

void RestartAgentClip(Agent* self)
{
    self->fB8C = 0;
    self->fA60 = 0;
    f32 r = GetAnimationMarkerTime(self->f7E0->anim, 0x1B1);
    SeekAnimationPlayer(self->f7E0, 0, r, 1.0f);
    self->fBA4 = 0;
}

s32 IsObjectInPool(void* p, Collider* v);

s32 TestAgentTargetContact(Agent* self, s32 key, Collider* other)
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

// What HandleAgentNotification is handed with a notification: the sender first, then a time or
// an object, then an event code.
struct AgentNotification {
    void* source;           // 0x00
    union {
        f32 time;           // 0x04
        void* obj;          // 0x04
    };
    s32 code;               // 0x08
};

void HandleSwitchedColliderNotification(Agent* self, s32 kind, void* msg);
void SetAgentMainClip(Agent* self, void* value);
AnimEvent* FindAnimationMarkerEvent(Animation* self, s32 key);
s32 func_001A8C90(void* a, s32 b);
s32 GatherObjectsById(void* host, s32 a1, s32 a2, void* ctx, s32 a4, void* out);
typedef void (*AgentSlotFn)(Agent* self);

void HandleAgentNotification(Agent* self, s32 kind, AgentNotification* msg)
{
    HandleSwitchedColliderNotification(self, kind, msg);
    switch (kind) {
    case 5:
        if ((void*)msg == self->f7E0) {
            self->f72C |= 2;
        } else if ((void*)msg == self->f754) {
            SetAgentMainClip(self, 0);
        }
        break;
    case 0x15: {
        if (msg->source != self->f754) {
            break;
        }
        C62* obj = (C62*)msg->obj;
        self->fA74 = obj;
        obj->desc->m17(obj, self);
        self->f72C |= 1;
        self->f730 = (void*)3;
        s32 state;
        s32 id = ((C62*)self->fA74)->id2E0;
        ItemKeeper* keeper;
        if (id != -1 && (keeper = (ItemKeeper*)self->f720) != 0) {
            if (keeper->f180 == -1) {
                keeper->f180 = id;
            }
            state = ((ItemKeeper*)self->f720)->f180 == ((C62*)self->fA74)->id2E0 ? 1 : 2;
        } else {
            state = 2;
        }
        SetStateAndNotify((C62*)self->fA74, state);
        break;
    }
    case 0x16:
        if (msg->source != self->fA74) {
            break;
        }
        switch (msg->code) {
        case 2:
            if (self->f724 == 3) {
                CreateAgentAnimationPlayer(self);
            }
            break;
        case 0:
            self->f730 = (void*)1;
            self->f72C |= 1;
            break;
        }
        break;
    case 0x13: {
        AnimationPlayer* player = (AnimationPlayer*)msg->source;
        Animation* anim = player->anim;
        if (player != self->f7E0) {
            break;
        }
        switch (msg->code) {
        case 0x138:
            if (anim->f9C == 0) {
                break;
            }
        slope: {
            Vec02 v;
            Vec02 w;
            PositionCurve* c = anim->f9C->pos;
            c->vt->eval(c, self, msg->time, player->speed, 0, 0, &v);
            u128 s = Vu0::FromFloat(-1.0f);
            Vu0::Q(F(Vec02, 0x640)) = Vu0::MulX(Vu0::Q(v), s);
            Vu0::Q(v) = Vu0::Rotate(F(Mat02, 0x660), Vu0::Q(v));
            Vu0::Q(w) = s;
            self->desc02()->m20(self, &v);
            break;
        }
        case 0x1A6:
            if (FindAnimationMarkerEvent(anim, 0x1A7) == 0) {
                break;
            }
            if (anim->f9C == 0 || anim->f9C->pos == 0) {
                break;
            }
            self->fB78 = 1;
            goto slope;
        case 0x1A7:
            self->fB78 = 0;
            break;
        case 0x1AC: {
            F(s32, 0xB90) = 1;
            self->fA60 = 0;
            AnimEvent* from = FindAnimationMarkerEvent(anim, 0x1AE);
            AnimEvent* mid = FindAnimationMarkerEvent(anim, 0x1AF);
            AnimEvent* to = FindAnimationMarkerEvent(anim, 0x1B1);
            AnimEvent* alt = FindAnimationMarkerEvent(anim, 0x1B0);
            if (from == 0 || to == 0 || mid == 0) {
                break;
            }
            // The end marker in a variable of its own: local-alloc gives it s0 in this block,
            // which keeps the animation out of s0 (docs/TOOLCHAIN.md, global-alloc).
            AnimEvent* end = alt != 0 ? alt : to;
            Vec02 p0;
            Vec02 p1;
            f32 zero = 0.0f;
            anim->f9C->pos->vt->eval(anim->f9C->pos, self, from->a0.f, zero, 0, &p0, 0);
            anim->f9C->pos->vt->eval(anim->f9C->pos, self, end->a0.f, zero, 0, &p1, 0);
            F(f32, 0xB94) = p1.x - p0.x;
            F(f32, 0xB98) = (end->a0.f - from->a0.f) / *(f32*)&anim->props6C[0x10];
            break;
        }
        case 0x1AD:
            F(s32, 0xB90) = 0;
            break;
        case 0x1AE:
            ((AgentSlotFn)self->desc08()->m61)(self);
            break;
        case 0x1AF:
            self->fB8C = 1;
            break;
        case 0x1B1:
            if (self->fB8C != 0) {
                AnimEvent* e = FindAnimationMarkerEvent(anim, 0x1B0);
                f32 t = e != 0 ? e->a0.f : msg->time;
                SeekAnimationPlayer(self->f7E0, 0, t, e != 0 ? 1.0f : 0.0f);
            }
            break;
        case 0x1AA:
            self->fB84 = 1;
            break;
        case 0x1AB:
            self->fB84 = 0;
            break;
        case 0x1A8:
            self->fB7C = 1;
            break;
        case 0x1A9:
            self->fB7C = 0;
            break;
        case 0x1B2:
            self->fBD8 = 1;
            break;
        case 0x1B3:
            self->fBD8 = 0;
            break;
        case 0x1A5: {
            u8* g = (u8*)self->fB0C;
            if (g != 0) {
                if (*(s32*)(g + 0x50) == -1) {
                    *(void**)(g + 0xE0) = self->desc08()->m62(self);
                }
                func_001A8C90(self->fB0C, 1);
            }
            break;
        }
        }
        break;
    }
    case 0xA:
        if (msg->obj == self && self->fB8C != 0) {
            ((AgentSlotFn)self->desc08()->m60)(self);
        }
        break;
    case 0x17: {
        Collider* mine = (((Collider*)msg->source)->desc->flags & 2) ? (Collider*)msg->source : 0;
        Collider* other = (((Collider*)msg->obj)->desc->flags & 2) ? (Collider*)msg->obj : 0;
        if (TestAgentTargetContact(self, (s32)mine, other) == 0) {
            break;
        }
        Collider* found[32];
        f32 dist = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(mine->v140))));
        s32 count = 0;
        s32 nearer = 0;
        s32 n = GatherObjectsById(self->world, 5, 8, 0, 0x20, found);
        for (s32 i = 0; i < n; i++) {
            Agent* o = (Agent*)found[i];
            if (o == self) {
                continue;
            }
            if (TestAgentTargetContact(o, (s32)mine, other) == 0) {
                continue;
            }
            count++;
            s32 closer = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(o->v140), Vu0::Q(mine->v140)))) < dist;
            nearer += closer;
        }
        if (nearer == 0) {
            self->fBFC = g_gameClock[1] + F(f32, 0xBE0);
        } else {
            f32 r = RandomFloatInRange((f32)(nearer - 1) / (f32)count, (f32)nearer / (f32)count);
            self->fBFC = g_gameClock[1] + (1.0f - r) * F(f32, 0xBE0) + r * F(f32, 0xBE4);
        }
        break;
    }
    }
}

s32 AnswerAgentRosterPoll(void)
{
    return 2;
}

s32 IsInsideRange(void* target, f32 scale);
s32 HasObjectPoolChoice(void* pool);
extern f32 g_unitRange[];

static inline f32 Limit(f32 g, f32 lo, f32 hi)
{
    if (g < lo) return lo;
    if (hi < g) return hi;
    return g;
}

s32 IsAgentTargetInRange(Agent* self)
{
    SwitchedCollider* target = (SwitchedCollider*)self->desc08()->m62(self);
    if (target == 0) {
        return 0;
    }
    if ((target->desc->flags & 8) != 0) {
        if (target->desc05()->m4D(target) != 0) {
            return 0;
        }
    }
    f32 dist = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(target->v140))));
    if (IsInsideRange(&self->f738, dist) == 0) {
        return 0;
    }
    f32 bearing = __builtin_fabsf(func_001C7A60(self));
    f32 g = D_00274CE0.c[0] + dist * (D_00274CE0.c[1] + dist * D_00274CE0.c[2]);
    g = Limit(g, g_unitRange[0], g_unitRange[1]);
    if (self->f74C < g * bearing) {
        return 0;
    }
    if (g_gameTime[0] < self->f748) {
        return 0;
    }
    if (self->fB0C != 0 && HasObjectPoolChoice(self->fB0C) == 0) {
        return 0;
    }
    return 1;
}

void DrawTurningCollider(void);

void DrawAgent(void)
{
    DrawTurningCollider();
}

s32 IsAgentSlotIndex(s32 index)
{
    return (u32)index < 17;
}

s32 IsAgentSlotIndex(s32 index);

void SetAgentStateClipId(u8* self, s32 index, s32 value)
{
    if (IsAgentSlotIndex(index)) {
        *(s32*)(self + (index << 3) + 0x758) = value;
    }
}

s32 IsAgentSlotIndex(s32 index);

void SetAgentStateClip(Agent* self, s32 index, s32 value)
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

s32 IsAgentSlotIndex(s32 index);

s32 GetAgentStateClip(Agent* self, s32 index)
{
    if (IsAgentSlotIndex(index) == 0)
        return 0;
    return (s32)self->f758[index].obj;
}

void AddAgentExtraClip(Agent* self, s32 a1, s32 a2)
{
    s32 n = self->fAC4;
    if ((u32)n < 4) {
        self->fAC4 = n + 1;
        Pend08* p = &self->fAC8[n];
        p->f00 = a1;
        p->id = a2;

    }
}

void* FindFirstObjectById(void* source, s32 kind, void* arg, s32 mode);
void MoveObjectAnimationTrackToEnd(void* item, Agent* host);
void ResolveAndStartObject(void* item);

void* ResolveAgentClip(Agent* self, void* arg)
{
    Animation* item = (Animation*)FindFirstObjectById(self->world, 0x101, arg, self->fB74);
    if (item != 0) {
        item->enabled = 0;
        MoveObjectAnimationTrackToEnd(item, self);
        ResolveAndStartObject(item);
    }
    return item;
}

void* ResolveAgentClip(Agent* self, s32 arg);

void ResolveAgentClips(Agent* self)
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

void SetAgentMemberGroupId(Agent* self, s32 v)
{
    self->fAFC = v;
    self->fAF8 = 1;
}

void SetAgentTargetSetId(Agent* self, s32 v)
{
    self->fB08 = v;
    self->fB04 = 1;
}

s32 IsAgentSlotIndex(s32 index);

void SetAgentSecondaryClipId(Agent* self, s32 index, s32 value)
{
    if (IsAgentSlotIndex(index))
        self->f870[index].id = value;
}

void* FindFirstObjectById(void* a, s32 b, s32 key, void* self);
void ResolveAndStartObject(void* p);

void ResolveAgentSecondaryClips(Agent* self)
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

void AddAgentMeshKey(Agent* self, s32 a, s32 b)
{
    u32 n = self->fA78;
    if (n < 4) {
        self->fA78 = n + 1;
        Elem08* e = &self->fA7C[n];
        e->key = a;
        e->f08 = b;
    }
}

s32 FindFirstObjectByIdMode4(void* owner, s32 index, Agent* self);

void SetAgentPathObjectId(Agent* self, s32 index)
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

void* GetActiveSwitchedCollider(void);

void* SelectAgentTarget(Agent* self)
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

void StoreAgentTarget(Agent* self, s32* out)
{
    *out = (s32)self->desc08()->m62(self);
}

void SetAgentSecondaryTarget(Agent* self, s32 value)
{
    self->fB48 = (void*)value;
    self->fB40 = 1;

}

s32 GatherObjectsByMode(World* host, s32 a1, s32 a2, s32 a3, s32 a4, PlacedObject** out);

void func_001CAB10(Agent* self)
{
    PlacedObject* found[0x20];
    Vec02 vel;
    Vec02 here;
    Vec02 there;
    Vec02 lead;
    s32 n = GatherObjectsByMode(self->world, 5, self->fB4C, 0, 0x20, found);
    PlacedObject* pick = 0;
    f32 best = 3.40282347e+38f;
    vel = self->v150;
    vel.z = 0.0f;
    Vu0::Vec k;
    k.q = Vu0::FromFloatAt(D_00274CF0);
    *(Vu0::Vec*)&lead = k;
    Vu0::Q(here) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(vel), Vu0::Q(lead));
    for (s32 i = 0; i < n; i++) {
        PlacedObject* obj = found[i];
        vel = obj->v150;
        vel.z = 0.0f;
        Vu0::Q(there) = Vu0::MulAddX(Vu0::Q(obj->pos), Vu0::Q(vel), k.q);
        *(Vu0::Vec*)&lead = k;
        u128 delta = Vu0::Sub(Vu0::Q(here), Vu0::Q(there));
        f32 d = Vu0::ToFloat(Vu0::Dot(delta, delta));
        if (obj == self->fB48) {
            d *= 0.5f;
        }
        if (d < best) {
            best = d;
            pick = obj;
        }
    }
    self->fB48 = pick;
    self->fB40 = 1;
}

void SetAgentPrimaryTarget(Agent* self, s32 value)
{
    self->fB50 = (void*)value;
}



void ComputeAgentContactValue(Agent* self, Contact03* out)
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

void ClampTurningColliderContactLimit(Agent*, s32, ContactLimit03*);

void ClampAgentContactLimit(Agent* self, s32 flags, ContactLimit03* out)
{ ClampTurningColliderContactLimit(self, flags, out);
    if (self->fC04 != 0) { if ((flags & 0x12) == 0x12) { if (0.7f < out->contact->v80.z) { out->limit = 0; } } } }

void SetAgentAngleLimitDegrees(Agent* self, f32 value) { self->f74C = value * 0.017453294f; }

void AddItemKeeperStateTrigger(void* self, s32 value);

void AddAgentStateTrigger(Agent* self, s32 value)
{
    AddItemKeeperStateTrigger(self->f720, value);
}

void AddAgentClipGroup(Agent* self, s32 a, s32 b, s32 c, s32 d) { if ((u32)self->f7E4 < 8) { Group08* e = &self->f7E8[self->f7E4]; self->f7E4++; e->ids[0] = a; e->ids[1] = b; e->ids[2] = c; e->ids[3] = d; } }

void AddTurningColliderProbeContact(Agent* a, Collider* b, s32 c, s32 d);
s32 IsObjectOfKind(Collider* a, s32 b);
s32 IsObjectAttached(Collider* a);
void AddMeshContacts(Collider* a, f32 f, void* b, Collider* c, s32 d, s32 e, s32 g, void* h);
void func_00186BA8(Collider* a, Collider* b, s32 c, s32 d, s32 e, void* f);

void CollideAgentWithObject(Agent* a0, Collider* a1, s32 a2, s32 a3, s32 a4, s32 a5)
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
                AddMeshContacts(a1, a1->radius3CC, (u8*)a1 + 0x140, (Collider*)e->obj,
                              ((Collider*)e->obj)->tree.count,
                              (s32)((Collider*)e->obj)->tree.nodes, 0, (u8*)a0 + 0xAAC);
            } else if (a3 != 0) {
                func_00186BA8((Collider*)e->obj, a1, a2, a3, a4, (u8*)a0 + 0xAAC);
            }
        }
    }
}

s32 IsObjectOfKind(void* obj, s32 kind);
void SetPlayerState(void* obj, s32 a, s32 b);

void LaunchObjectWithAgentVelocity(u8* self, PlacedObject* other)
{
    other->desc02()->m20(other, (Vec02*)(self + 0xAB0));
    if (IsObjectOfKind(other, 7) != 0) {
        SetPlayerState(other, 4, 0x2B);
    }
}

void InitOwnerMessage(void* out, s32 mode, Agent* owner);
void ComputeObjectMotionInFrame(void* a, s32 b, void* c, void* d, s32 e, s32 f, s32 g);
void ClampVectorLength(Vec02* in, Vec02* out, f32 max);
void FreePooledContactChain(World* w, Contact03* head);

// A query for the node an agent's contact leads to: the agent, the part it touched and where
// the agent is.
inline void InitAgentContactQuery(NodeQuery* q, Agent* self, Collider* part)
{
    FillMemory(q, 0, 0x40);
    q->pos = self->v140;
    q->hold = part;
    q->p00 = self;
}

void func_001CAF38(Agent* self)
{
    void* target = self->desc08()->m62(self);
    if (target == 0) {
        return;
    }
    if (self->fC04 == 0) {
        Contact03* head = self->fAAC;
        if (head == 0) {
            goto out;
        }
        Player* p = g_player;
        if (target == p || target == self->fB50) {
            if (self->fAC0 == 0) {
                void* h = p->f2200;
                if (h != 0) {
                    h = *(void**)((u8*)h + 0x18);
                    if (h != 0 && *(Agent**)((u8*)h + 0x50) == self) {
                        switch (p->f223C) {
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                            if (g_gameTime[0] - p->f2240 < 0.25f) {
                                goto out;
                            }
                        }
                        if (g_player->f2220 == 10 && g_gameTime[0] - g_player->f2224 < 0.25f) {
                            goto out;
                        }
                        switch (g_player->f2228) {
                        case 7:
                        case 8:
                            if (g_gameTime[0] - g_player->f222C < 0.25f) {
                                goto out;
                            }
                        }
                    }
                }
            }
        }
        for (Contact03* c = head; c != 0; c = c->next) {
            s32 j = (c->end[0].body != (Collider*)self);
            s32 i;
            Elem08* e;
            for (i = 0; i < self->fA78; i++) {
                e = &self->fA7C[i];
                if (e->obj == c->end[j].part && IsObjectAttached((Collider*)e->obj) != 0) {
                    break;
                }
            }
            if (i < self->fA78) {
                ContactEnd03* other = &c->end[1 - j];
                Collider* part = other->part;
                OwnerMessage msg;
                Vec02 vel;
                if (IsObjectOfKind(part, 5) != 0) {
                    InitOwnerMessage(&msg, e->f08, self);
                    switch (msg.mode) {
                    case 6:
                        if (self->fB1C != 0) {
                            msg.fn = (void (*)(void))LaunchObjectWithAgentVelocity;
                            self->vAB0 = D_00248D30;
                            break;
                        }
                    case 0:
                        ComputeObjectMotionInFrame(c->end[j].part, 0, &c->end[1 - j].v10, &vel, 0, 0, 0);
                        Vu0::Q(vel) = Vu0::MulX(Vu0::Vec::Of(vel), Vu0::Vec::Scalar(D_00274CFC + 1.0f)).q;
                        ClampVectorLength(&vel, &vel, D_00274D04);
                        vel.z = D_00274D00 >? vel.z;
                        msg.fn = (void (*)(void))LaunchObjectWithAgentVelocity;
                        self->vAB0 = vel;
                        break;
                    }
                    ((SwitchedCollider*)part)->desc05()->m4C((SwitchedCollider*)part, &msg);
                } else {
                    NodeQuery q;
                    InitAgentContactQuery(&q, self, part);
                    ComputeObjectMotionInFrame(c->end[j].part, 0, &other->v10, &q.dir, 0, 0, 0);
                    q.kind = 2;
                    FindNodeForQuery(&q, 0, 0);
                }
                for (i = 0; i < self->fA78; i++) {
                    ((BaseObject*)self->fA7C[i].obj)->desc->m03((BaseObject*)self->fA7C[i].obj);
                }
                break;
            }
        }
    }
out:
    FreePooledContactChain(self->world, self->fAAC);
    self->fAAC = 0;
}

void StopAnimationPlayer(void* p);
s32 GetAgentRosterState(void* self);
void func_0012C9E8(void* a, void* b, f32 c, void* d, void* e, s32 f, s32 g);

void SetAgentMainClip(Agent* self, void* value)
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

s32 RequestAgentLaunch(void)
{
    return 1;
}

s32 IsAgentFree(void)
{
    return 0;
}

// What func_001CB3D0 reads of the player's f23A0 and f23A8: a word that, set, ends the test.
struct Blocker_23A0 {
    u8 pad00[0x54];
    s32 f54;                // 0x54
};
struct Blocker_23A8 {
    u8 pad00[0x6C];
    s32 f6C;                // 0x6C
};

s32 MaskWorldBitsBySave(void);
s32 IsObjectOfKind(void* obj, s32 kind);

s32 func_001CB3D0(Agent* self)
{
    Player* t = (Player*)self->desc08()->m62(self);
    if (IsObjectOfKind(t, 7) == 0) {
        return 0;
    }
    if (t->f2220 != 6) {
        return 0;
    }
    Vec02 d;
    // The difference is kept, and a copy of it stored and used up in case 0 (vmove).
    u128 diff = Vu0::Sub(Vu0::Q(t->v140), Vu0::Q(self->v140));
    u128 dv = Vu0::Copy(diff);
    Vu0::Q(d) = dv;
    switch (t->f239C) {
    case 3:
        if (MaskWorldBitsBySave() & 0x12000) {
            return 1;
        }
        break;
    case 0:
        if (t->f23A0 != 0 && ((Blocker_23A0*)t->f23A0)->f54 != 0) {
            return 0;
        }
        if (t->f23A8 != 0 && ((Blocker_23A8*)t->f23A8)->f6C != 0) {
            return 0;
        }
        if (Vu0::ToFloat(Vu0::Dot(dv, Vu0::Q(t->m110.r[0]))) > 0.0f) {
            return 1;
        }
        break;
    case 1:
        if (t->f23A0 != 0 && ((Blocker_23A0*)t->f23A0)->f54 != 0) {
            return 0;
        }
        if (t->f23A8 != 0 && ((Blocker_23A8*)t->f23A8)->f6C != 0) {
            return 0;
        }
        if (Vu0::ToFloat(Vu0::Dot(diff, Vu0::Q(t->m110.r[0]))) < 0.0f) {
            return 1;
        }
        break;
    case 2:
        if (t->f2228 == 0x10) {
            return 1;
        }
        break;
    }
    return 0;
}


s32 IsAgentFacingBlocked(Agent* self)
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


void* CreateTypedRecord(s32 a, void* b, s32 c, s32 d, s32 e);
void* AppendQueuedCall(u32 a, void* fn, void* obj, s32 c, s32 d);
void GroupAnimationEventObjects(void);

void* CreateItemKeeper(void* a0)
{
    void* obj = CreateTypedRecord(0x89, a0, 0, 0x436, -1);
    AppendQueuedCall((u32)g_currentWorld, (void*)GroupAnimationEventObjects, obj, 0, 0);
    return obj;
}

void InitObject(void* self);

void InitItemKeeper(ItemKeeper* self)
{
    InitObject(self);
    self->f180 = -1;
}

void SetItemKeeperState(void* self, s32 arg);

void AddItemKeeperMember(ItemKeeper* self, Agent* value)
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

void AddOwnedWantedId(ItemKeeper* self, s32 value) { u32 i = self->owned.wantedCount; if (i < 16) { self->owned.wanted[i] = value; self->owned.wantedCount = i + 1; } }

void AddListedWantedId(ItemKeeper* self, s32 value) { u32 i = self->listed.wantedCount; if (i < 16) { self->listed.wanted[i] = value; self->listed.wantedCount = i + 1; } }

void SetItemKeeperState(void* self, s32 arg);
void CopyMemory(void* dst, void* src, s32 count);

void RemoveItemKeeperMember(ItemKeeper* self, Agent* value)
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


Agent* FindFirstObjectByIdMode4(u32 a, s32 id, ItemKeeper* c);

void FindWantedItems(ItemKeeper* a0)
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

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateZeroedBackMemory(s32 size);
void GatherAnimationEventObjects(void* a, void* b, s32* c, void** d);
void* CreateRecord2505C0(void);
void AppendToSmallList(void* a, void* b);

void GroupAnimationEventObjects(ItemKeeper* self)
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

void* AppendQueuedCall(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void UpdateItemKeeper(void* self);


void QueueItemKeeperUpdate(ItemKeeper* a0)
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

void* GetItemKeeperTarget(ItemKeeper* self)
{
    Agent* item = self->owned.found[0];
    return item->desc08()->m62(item);
}


s32 IsAnyItemKeeperMemberFree(void* self);
s32 ChooseItemKeeperState(void* self);
void SetItemKeeperState(void* self, s32 arg);

void UpdateItemKeeper(ItemKeeper* self)
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

s32 PollItemKeeperMembers(ItemKeeper* self);
void StartSoundEffect(s32 sound, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);


s32 ChooseItemKeeperState(ItemKeeper* self)
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

s32 IsAnyItemKeeperMemberFree(ItemKeeper* self)
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

s32 PollItemKeeperMembers(ItemKeeper* a0)
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

void AddItemKeeperStateTrigger(ItemKeeper* self, s32 value) { for (s32 i = 0; i < self->triggerCount; i++) if (value == self->triggers[i]) return; s32 i = self->triggerCount; if ((u32)i < 4) { s32 next = i + 1; self->triggers[i] = value; self->triggerCount = next; } }

void SetStateTriggerStateFromMessage(void* object, s32 mode);

void SetItemKeeperTriggerStates(ItemKeeper* self, s32 mode)
{
    for (s32 i = 0; i < self->triggerCount; i++) {
        SetStateTriggerStateFromMessage((void*)self->triggers[i], mode);
    }
}


extern f32 g_gameClock[];

f32 RandomFloatInRange(f32 a, f32 b);
void RemoveSoundLevelAndRecompute(void* p);
void* PushSoundLevel(s32 kind);
void SetItemKeeperTriggerStates(ItemKeeper* self, s32 a);
void func_001CC120(ItemKeeper* self);

void SetItemKeeperState(ItemKeeper* self, s32 ns)
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

void GetObjectWorldPosition(void* obj, void* out);
void GetObjectWorldRotation(void* obj, void* out);
void ComputePolarOffset(void* out, f32 angle, f32 dist, f32 z);

static inline s32 MinOfCounts(s32 a, s32 b)
{
    return a < b ? a : b;
}

// Places the owned members: each of the first ones on the listed object nearest the target
// (taken once, in a zeroed back-memory array), with its heading; the rest at random around the
// target, on a ring whose radius grows with their count.
void func_001CC120(ItemKeeper* self)
{
    Vec02 offset;
    Mat02 rot;
    Vec02 pos;
    s32 i = 0;
    PushBackMemoryMark();
    s32* used = (s32*)AllocateZeroedBackMemory(self->listed.count << 2);
    while (i < MinOfCounts(self->owned.count, self->listed.count)) {
        Agent* member = self->owned.found[i];
        s32 best = -1;
        f32 bestDist = 3.4028235e+38f;
        for (s32 j = 0; j < self->listed.count; j++) {
            if (used[j] == 0) {
                GetObjectWorldPosition(self->listed.found[j], &pos);
                f32 d = Vu0::Distance(self->targetPos, pos);
                if (d < bestDist) {
                    bestDist = d;
                    best = j;
                }
            }
        }
        used[best] = 1;
        Agent* m = self->listed.found[best];
        i++;
        GetObjectWorldPosition(m, &member->v900);
        GetObjectWorldRotation(m, &rot);
        member->f910 = ArctangentOfRatio(rot.r[0].y, rot.r[0].x);
    }
    PopBackMemoryMark();
    if (i != self->owned.count) {
        f32 cnt = (f32)self->owned.count;
        f32 radius = cnt * D_00274D20[0] * 0.15915494f;
        f32 step = 6.2831855f / cnt;
        PlacedObject* target = (PlacedObject*)GetItemKeeperTarget(self);
        f32 ang0;
        if (target != 0) {
            ang0 = ArctangentOfRatio(target->v150.y, target->v150.x);
        } else {
            ang0 = 0.0f;
        }
        for (; i < self->owned.count; i++) {
            Agent* m = self->owned.found[i];
            f32 r = RandomFloatInRange(D_00274D28[0], D_00274D28[1]);
            f32 ang = WrapAngle(ang0 + r * step);
            f32 r2 = RandomFloatInRange(D_00274D30.c[0], D_00274D30.c[1]);
            ComputePolarOffset(&offset, ang, r2 * radius, 0.0f);
            u128 q = Vu0::Add(Vu0::Q(self->targetPos), Vu0::Q(offset));
            m->f910 = ang;
            Vu0::Q(m->v900) = q;
            ang0 = WrapAngle(ang0 + step);
        }
    }
}

ASM_FUNC(func_001CC3F8);




