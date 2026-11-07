// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 848/856, checked 2026-11-07
// NEAR: registers and one branch form: retail keeps the held target in s2 and the player table in s3 across the calls (four saved registers), ours shares s0; the three vector products and the scales match.
#include "common.h"
#include "shapes.h"
#include "vu0.h"
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
#include "vu0.h"
extern f32 g_gameTime[];
f32 ArctangentOfRatio(f32 a, f32 b);
f32 WrapAngle(f32 a);
void* ResolveAgentClip(Agent* self, void* arg);
void* ResolveAgentClip(Agent* self, s32 arg);
struct __attribute__((aligned(16))) PaddedQuadratic { f32 c[3]; };
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
void LoadCollider(Agent* self, void* a1);
void ResolveObjectLinks(Agent* self, s32 a1, void* a2);
void ResolveAgentClips(Agent* self);
void ResolveAgentSecondaryClips(Agent* self);
void CopySwitchedCollider(Agent* self, s32 v);
void PostLoadPlacedObject(Agent* self);
s32 FindFirstObjectByIdMode4(s32 a, s32 b, Agent* self);
void PickAgentSecondaryTarget(Agent* self);
s32 FindFirstObjectById(s32 a, s32 b, s32 c, Agent* self);
void FindOrBuildMemberGroup(s32* p, Agent* self);
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
s32 TestCollidersMayContact(Agent* self, Collider* obj);
s32 IsObjectInPool(void* p, Collider* obj);
void RegisterSwitchedCollider(void* self);
void AddItemKeeperMember(void* list, void* value);
void UnregisterSwitchedCollider(Agent* self);
void StopAnimationPlayer(void* obj);
void RemoveItemKeeperMember(void* a, Agent* b);
s32 IsAgentFacingBlocked(void* self);
void BuildYawPitchMatrix(f32 a, f32 b, void* out);
void BuildAxisAngleMatrix(void* table, f32 x, void* out);
void ChangeAgentState(Agent* self, s32 a1, s32 a2);
extern f32 g_frameDt;
void func_00128598(f32 a, f32 b, Agent* self, s32 c, s32 d, f32* e, f32* f, f32* g);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);

void UpdateTurningCollider(Collider* self);
void PickAgentSecondaryTarget(Agent* self);
void SetAgentPrimaryTarget(Agent* self, s32 value);
s32 FindColliderFloorContact(Agent* self, s32 a, s32* out);
void ApplyPendingAgentChanges(Agent* self);
void SettleAgentState(Agent* self);
void QueueItemKeeperUpdate(void* keeper);
void func_001CAF38(Agent* self);
void ClearRootTries(Agent* self);
s32 IsObjectAttached(void* obj);
void BuildAxisAngleMatrix(const Vec02* axis, f32 angle, Mat02* out);
void BuildShortestArcRotation(const Vec02* from, Vec02* to, Mat02* out);
extern f32 D_00274AD0[];
extern const Vec02 D_00248D30;

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
                if (target->f2750 != 0 && IsObjectAttached(target->f2750) != 0) {
                    SetAgentPrimaryTarget(self, (s32)g_player->f2750);
                    if (self->desc08()->m57(self) == 0) {
                        SetAgentPrimaryTarget(self, 0);
                    } else if ((s32)held < ((AgentLinks*)self->f720)->count) {
                        for (s32 i = 0; i < ((AgentLinks*)self->f720)->count; i++) {
                            if (((AgentLinks*)self->f720)->found[i] != self) {
                                SetAgentPrimaryTarget(self, (s32)g_player->f2750);
                            }
                        }
                    }
                }
            }
        }
    } else if (IsObjectAttached(held) == 0 || ((AgentLinks*)self->f720)->state != 2) {
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
            curve->vt->eval(curve, self, 0, 0, &self->v640, player->time, player->speed);
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
        QueueItemKeeperUpdate(self->f720);
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
        BuildAxisAngleMatrix(&g_unitZVector, self->f638, &spin);
        BuildShortestArcRotation(&g_unitZVector, &push, &arc);
        MulRotationInto(self, arc, spin);
    }
    ClearRootTries(self);
    self->fB14 = 0;
}
