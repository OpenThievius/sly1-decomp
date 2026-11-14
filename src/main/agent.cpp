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
#include "state_reset_object.h"
#include "animation.h"
#include "attachment.h"
#include "aim_blend_grid.h"
#include "owner_message.h"
#include "anim_curve.h"
#include "vu0.h"
#include "object_finder.h"
struct GraphQueryOwner;

struct World;


// Types other files define, named by the parameters of their functions declared here.
struct ObjectLink;
struct TargetBinding;

extern f32 g_gameTime[];

// A quadratic in t (c[0] + t * (c[1] + t * c[2])) on 16 bytes, as in hit_count_collider: the file's
// .data starts on 16 (0x274C18 to 0x274C20 is padding after the previous file's), and 0x274C54
// to 0x274C5F is the quadratic's own.
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
f32 WrapAngle(f32 a);
void* ResolveAgentClip(Agent* self, s32 id);
void* ResolveAgentClip(Agent* self, s32 arg);

struct __attribute__((aligned(16))) PaddedQuadratic { f32 c[3]; };

// The file's .data, in retail's order; its assembly reads the quadratics.
s32 g_agentLoadLinks[4] = { 2, 0x195, 0x87C, 0 };
s32 g_agentStartLinks[8] = { 2, 0x194, 0x750, 6, 0x50, 0x734, 0, 0 };
PaddedQuadratic g_agentTurnBlendCoefficients = { { 1.0f, -1.0f, 0.0f } };
PaddedQuadratic g_agentSteerBlendCoefficients = { { 0.0f, 0.0f, 1.0f } };
PaddedQuadratic g_agentSteerRatesA = { { 0.0f, 15.0f, 1.5f } };
PaddedQuadratic g_agentSteerRatesB = { { 0.0f, 2.5f, 0.25f } };
float g_agentGoalFarDistance = 40.0f;
float g_agentFacingFarDistance = 50.0f;
float g_agentPathRetryDelay[2] = {0.5f, 0.0f};
PaddedQuadratic g_agentPitchDistanceCoefficients = { { 1.0f, -0.00100000005f, 0.0f } };
PaddedQuadratic g_agentPitchDistanceLimits = { { 0.25f, 1.0f, 0.0f } };
PaddedQuadratic g_agentPitchHeightCoefficients = { { 0.0f, 0.00499999989f, 0.0f } };
float g_agentPitchHeightLimits[2] = {0.0f, 1.0f};
float g_agentPitchScale[2] = {1.0f, 0.0f};
PaddedQuadratic g_agentTargetRangeCoefficients = { { 0.0f, 0.00499999989f, 0.0f } };
float D_00274CF0 = 0.349999994f;
f32 D_00274CF4 = 0.85f;
f32 D_00274CF8[1] = { 0 };
float g_agentHitVelocityBoost = 0.25f;
float g_agentHitMinUpSpeed = 700.0f;
float g_agentHitMaxSpeed = 1200.0f;
f32 D_00274D08[2] = { 0.0f, 4.0f };
f32 D_00274D10[2] = { 0.0f, 1.5f };
f32 D_00274D18[2] = { 0.0f, 0.3f };
float g_itemKeeperMemberSpacing[2] = {700.0f, 0.0f};
float g_itemKeeperPlaceAngleJitter[2] = {-0.200000003f, 0.200000003f};
PaddedQuadratic g_itemKeeperPlaceRadiusScale = { { 0.800000012f, 1.20000005f, 0.0f } };

extern u8 g_flagTable[];
void InitTurningCollider(TurningCollider* self);
s32 TakeFlagTableIndex(FlagTable* p);
void SetSwitchedColliderEnabled(SwitchedCollider* self, s32 value);

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

struct BufferedStream;
struct Collider;
void LoadCollider(Collider* self, BufferedStream* in);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
void ResolveAgentClips(Agent* self);
void ResolveAgentSecondaryClips(Agent* self);

void LoadAgent(Agent* self, void* a1)
{
    LoadCollider(self, (BufferedStream*)a1);
    ResolveObjectLinks(self, 1, (ObjectLink*)g_agentLoadLinks);
    ResolveAgentClips(self);
    ResolveAgentSecondaryClips(self);
}

void CopySwitchedCollider(Agent* self, void* src);

void CopyAgent(Agent* self, void* src)
{
    s32 b = self->flagIndex;
    s32 a = (s32)self->roster;
    CopySwitchedCollider(self, src);
    self->flagIndex = b;
    self->roster = (void*)a;
    self->copySource = src;
}

void PostLoadPlacedObject(PlacedObject* self);
void PickAgentSecondaryTarget(Agent* self);
void FindOrBuildMemberGroup(void** out, void* self);

void PostLoadAgent(Agent* self)
{
    s32 v;
    PostLoadPlacedObject(self);
    if (self->pathGraphId != -1) {
        self->pathGraph = (PointGraphObject*)FindFirstObjectByIdMode4(self->world, self->pathGraphId, self);
    }
    if (self->secondaryTargetKey != -1) {
        PickAgentSecondaryTarget(self);
    }
    v = self->hasMemberGroupId;
    if (v != 0) {
        if (self->memberGroupId != -1) {
            self->memberGroup = FindFirstObjectById(self->world, 0x101, self->memberGroupId, self);
        }
    } else {
        FindOrBuildMemberGroup((void**)&self->memberGroup, self);
    }
}

void RemoveAgentFromParent(Agent* self)
{
    self->desc->m03(self);
}

void StartTurningCollider(TurningCollider* self);
void* CreateItemKeeper(void* host);
void AddItemKeeperMember(ItemKeeper* self, Agent* value);
void ResolveAgentClips(void* self);
void SetTurningColliderGravityScale(TurningCollider* self, f32 s);
void ChangeAgentState(Agent* self, s32 state, void* context);
s32 TestFlagTableBit(FlagTable* table, s32 index);
void* AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);

extern u8 g_flagTable[];

void StartAgent(Agent* self)
{
    StartTurningCollider(self);
    ResolveObjectLinks(self, 2, (ObjectLink*)g_agentStartLinks);
    if (self->roster == 0) {
        void* t = CreateItemKeeper(self->world);
        self->roster = t;
        AddItemKeeperMember((ItemKeeper*)t, self);
    }
    ResolveAgentClips(self);
    for (s32 i = 0; i < 17; i++) {
        void* item = self->secondaryClips[i].obj;
        if (item != 0) {
            self->followedMesh = item;
            self->defaultSecondaryClip = item;
            self->desc03()->m34(self, item, 1);
            break;
        }
    }
    s32 j = 0;
    if (self->meshKeyCount > 0) {
        u64 bit = 0x8000;
        bit <<= 28;
        Elem08* e = self->meshKeys;
        do {
            Collider* o = (Collider*)FindFirstObjectById(self->world, 0x101, e->key, self);
            e->obj = o;
            if (o != 0) {
                o->flags538 |= bit;
                ((Collider*)e->obj)->desc->m03((Collider*)e->obj);
            }
            e++;
            j++;
        } while (j < self->meshKeyCount);
    }
    if (self->hasTargetSetId != 0) {
        if (self->targetSetId != -1) {
            self->targetSet = FindFirstObjectById(self->world, 0x101, self->targetSetId, self);
        }
    } else {
        self->targetSet = FindFirstObjectByIdGathered(self->world, 0x101, 0x8C, self);
    }
    SetTurningColliderGravityScale(self, self->gravityScale);
    ChangeAgentState(self, 0, 0);
    if (TestFlagTableBit((FlagTable*)g_flagTable, self->flagIndex)) {
        AppendQueuedCall(self->world, (void*)RemoveAgentFromParent, self, 0, 0);
    }
}

s32 TestCollidersMayContact(Collider* a, Collider* b);
s32 IsObjectInPool(ObjectPool* list, BaseObject* query);

s32 TestAgentMayContact(Agent* self, Collider* obj)
{
    if (TestCollidersMayContact(self, obj) != 0) {
        return 1;
    }
    if (self->targetSet != 0) {
        if (IsObjectInPool((ObjectPool*)self->targetSet, obj) != 0) {
            return 1;
        }
    }
    if (self->state == 0xB) {
        if ((obj->flags538 & ((u64)1 << 55)) == 0) {
            return 1;
        }
    }
    return 0;
}

void RegisterSwitchedCollider(SwitchedCollider* self);
void AddItemKeeperMember(ItemKeeper* self, Agent* value);

void RegisterAgent(Agent* self)
{
    RegisterSwitchedCollider(self);
    if (self->roster != 0) {
        AddItemKeeperMember((ItemKeeper*)self->roster, self);
    }
}


void UnregisterSwitchedCollider(SwitchedCollider* self);
void StopAnimationPlayer(AnimationPlayer* self);
void RemoveItemKeeperMember(ItemKeeper* self, Agent* value);

void UnregisterAgent(Agent* self)
{
    UnregisterSwitchedCollider(self);
    if (self->statePlayer != 0) {
        StopAnimationPlayer(self->statePlayer);
        self->statePlayer = 0;
    }
    if (self->mainPlayer != 0) {
        StopAnimationPlayer(self->mainPlayer);
        self->mainPlayer = 0;
    }
    if (self->roster != 0) {
        RemoveItemKeeperMember((ItemKeeper*)self->roster, self);
    }
    self->requestBits = 0;
    self->pathValid = 0;
    self->targetReadyTime = 0;
    self->arrivalTime = 0;
    self->state6Deadline = 3.4028235e+38f;
    self->fBF8 = 3.4028235e+38f;
    self->clip10Deadline = 3.4028235e+38f;
    self->state8Deadline = 3.4028235e+38f;
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
void *StoreFloatAsQuadword(u128* out, f32 f);
void* CopyQuadword(u128* out, void* src);
Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);
void* StoreQuadword(u128* out, u128 v);

// k times the vector at p, into dst (the quadword helpers' product).
static inline void StoreScaledQuadword(Vec02* dst, f32 k, u8* p)
{
    Quadword128 t;
    StoreFloatAsQuadword((u128*)&t, k);
    Quadword128 tv = t;
    Quadword128 u;
    CopyQuadword((u128*)&u, p);
    StoreQuadword((u128*)dst, ScaleQuadword(tv, u));
}
extern "C" f32 Arccosine(f32 x);
void AddColliderForce(Agent* self, Vec02* v);
void TurnColliderTowardRotation(Collider* self, f32 dt, Mat02* target, f32* gain);
void SteerColliderTowardPosition(Collider* self, Vec02* target, f32* pull, Vec02* aim, f32* turn, f32 limit);
void SteerColliderTowardRotation(Collider* self, Mat02* target, f32* pull, Vec02* aim, f32* turn, f32 limit);
void StepTurningCollider(TurningCollider* self, f32 dt);
extern "C" void* CopyBytes(void* dst, void* src, s32 n);
void ClampVectorLength(Vec02* in, Vec02* out, f32 max);
void EvaluateHermiteVectorSegment(f32 dur, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, f32 t, f32 k, Vec02* pos, Vec02* vel, Vec02* acc);
typedef void (*AgentMotionFn)(void* self, Agent* agent, s32 a, s32 b, Vec02* out, f32 t, f32 u);

void StepAgent(Agent* self, f32 dt)
{
    if (F(s32, 0xB78) != 0) {
        Vec02 motion;
        Vec02 v;
        u8* ap = (u8*)self->statePlayer;
        u8* src = *(u8**)(*(u8**)(*(u8**)(ap + 8) + 0x9C) + 4);
        (**(AgentMotionFn**)src)(src, self, 0, 0, &motion, *(f32*)(ap + 0x14), *(f32*)(ap + 0x18));
        Vu0::Q(v) = Vu0::DivX(Vu0::Add(Vu0::Vec::Of(motion), Vu0::Vec::Of(self->headingVelocity)), Vu0::Vec::Scalar(dt)).q;
        Vu0::Q(v) = Vu0::RotateMembers(self->headingMatrix, Vu0::Q(v));
        AddColliderForce(self, &v);
        TurnColliderTowardRotation(self, g_gameClock[2], &self->headingMatrix, &self->turnGain);
    } else if (self->usesPitch != 0) {
        Vec02 v;
        Mat02 m2;
        Mat02 m;
        f32 a = __builtin_fabsf(Arccosine(Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->rot.r[0]), Vu0::Q(self->headingMatrix.r[0])))));
        f32 k = LimitToUnitRange(g_agentTurnBlendCoefficients.c[0] + a * (g_agentTurnBlendCoefficients.c[1] + a * g_agentTurnBlendCoefficients.c[2]));
        if (self->state == 12) {
            f32 d = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->snappedGoal), Vu0::Q(self->v140))));
            f32* q = &F(f32, 0xB30);
            k = k * LimitToUnitRange(q[0] + d * (q[1] + d * q[2]));
        }
        u128 s = Vu0::Scalar(-k);
        Vu0::Q(m.r[0]) = Vu0::MulX(Vu0::Q(self->m110.r[0]), s);
        Vu0::Q(m.r[1]) = Vu0::MulX(Vu0::Q(self->m110.r[1]), s);
        Vu0::Q(m.r[2]) = Vu0::MulX(Vu0::Q(self->m110.r[2]), s);
        CopyBytes(&m2, &m, 0x30);
        Vu0::Q(v) = Vu0::Rotate(m2, Vu0::Q(self->headingVelocity));
        SteerColliderTowardPosition(self, 0, 0, &v, F(f32*, 0x210), dt);
        TurnColliderTowardRotation(self, g_gameClock[2], &self->headingMatrix, &self->turnGain);
    } else if (g_gameTime[0] < F(f32, 0xBA4)) {
        Vec02 p;
        Vec02 w;
        Vec02 v;
        f32 left = F(f32, 0xBA4) - g_gameTime[0];
        EvaluateHermiteVectorSegment(left, &self->pos, &self->v150, &F(Vec02, 0xBB0), &F(Vec02, 0xBC0), left <? dt, 1.0f, &p, &w, 0);
        Vu0::Q(v) = Vu0::DivX(Vu0::Sub(Vu0::Q(w), Vu0::Q(self->v150)), Vu0::Scalar(dt));
        ClampVectorLength(&v, &v, 20000.0f);
        AddColliderForce(self, &v);
        TurnColliderTowardRotation(self, dt, &self->headingMatrix, &self->turnGain);
    } else if (self->state == 16 && self->fA6C != 0) {
        Vec02 q2;
        Vec02 q;
        f32 x;
        u8* ap = (u8*)self->statePlayer;
        if (ap != 0) {
            x = *(f32*)(ap + 0x14) / *(f32*)(*(u8**)(ap + 8) + 0x34);
        } else {
            x = 1.0f;
        }
        f32 k = LimitToUnitRange(g_agentSteerBlendCoefficients.c[0] + x * (g_agentSteerBlendCoefficients.c[1] + x * g_agentSteerBlendCoefficients.c[2]));
        StoreScaledQuadword(&q, k, (u8*)&g_agentSteerRatesA);
        StoreScaledQuadword(&q2, k, (u8*)&g_agentSteerRatesB);
        SteerColliderTowardRotation(self, &self->headingMatrix, (f32*)&q, (Vec02*)&D_00248D30, (f32*)&q2, dt);
        AddColliderForce(self, &self->gravity);
    } else {
        StepTurningCollider(self, dt);
    }
}

f32 ComputeAgentTargetBearing(Agent* self)
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

s32 IsAgentFacingBlocked(Agent* self);
void BuildYawPitchMatrix(f32 yaw, f32 pitch, Mat02* out);
// The definition takes the angle last; the EE passes it in its own register, and retail's
// callers evaluate it before the matrix, as this order does.
void BuildAxisAngleMatrix(const Vec02* v, f32 angle, Mat02* out);

void SetAgentFacingAngles(Agent* self, f32 x, f32 y)
{
    if (IsAgentFacingBlocked(self) != 0) return;
    s32 t = self->usesPitch;
    self->heading = x;
    self->pitch = y;
    if (t != 0) {
        BuildYawPitchMatrix(x, y, (Mat02*)((u8*)self + 0x660));
    } else {
        BuildAxisAngleMatrix((const Vec02*)&g_unitZVector, x, (Mat02*)((u8*)self + 0x660));
    }
}

void ChangeAgentState(Agent* self, s32 state, void* context);

void SettleAgentState(Agent* self)
{
    if (self->stateLocked != 0) return;
    if (self->stateForced != 0) return;
    if (g_player != 0 && g_player->animSeekValue != 0) return;
    for (;;) {
        s32 v = self->desc08()->m59(self);
        if (v == self->state) break;
        ChangeAgentState(self, v, 0);
    }
}

extern f32 g_frameDt;
void ComputeObjectSteeringHeading(f32 a, f32 b, PlacedObject* self, f32* p1, f32* p3, f32* out0, f32* out1, f32* out2);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);

void FaceAgentFromAnimationMotion(Agent* self)
{
    f32 out[3];
    f32 zero = 0.0f;
    out[1] = zero;
    ComputeObjectSteeringHeading(g_frameDt, self->heading, self, 0, 0, &out[0], self->usesPitch ? &out[1] : 0, &out[2]);
    f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(self->headingVelocity)));
    if (0.0001f < out[2] && 0.0001f < len) {
        self->mainPlayer->speed *= len / out[2];
    }
    f32 y = out[1];
    SetAgentFacingAngles(self, out[0], y);
}

void UpdateTurningCollider(TurningCollider* self, f32 dt);
void* FindColliderFloorContact(void* self, s32 key, s32* out);
void DispatchAgentContactHits(Agent* self);
void ClearRootTries(PlacedObject* self);
void BuildShortestArcRotation(const Vec02* from, const Vec02* to, Mat02* out);
extern f32 g_contactSideSigns[];
extern const Vec02 D_00248D30;
s32 IsObjectAttached(BaseObject* self);
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
    self->headingMatrix = r;
}

void UpdateAgent(Agent* self, f32 dt)
{
    Vec02 push;
    Mat02 spin;
    Mat02 arc;
    s32 kind;
    UpdateTurningCollider(self, dt);
    if (*(s32*)((u8*)self + 0xB44) != 0) {
        PickAgentSecondaryTarget(self);
    }
    void* held = self->primaryTarget;
    if (held == 0) {
        if (((AgentLinks*)self->roster)->state != 2) {
            Player* target = (Player*)self->desc08()->m62(self);
            if (target != 0 && target == g_player) {
                if (target->contactOwner != 0 && IsObjectAttached((Collider*)target->contactOwner) != 0) {
                    SetAgentPrimaryTarget(self, (s32)g_player->contactOwner);
                    if (self->desc08()->m57(self) == 0) {
                        SetAgentPrimaryTarget(self, 0);
                    } else {
                        for (s32 i = 0; i < ((AgentLinks*)self->roster)->count; i++) {
                            if (((AgentLinks*)self->roster)->found[i] != self) {
                                SetAgentPrimaryTarget(self, (s32)g_player->contactOwner);
                            }
                        }
                    }
                }
            }
        }
    } else if (IsObjectAttached((Collider*)held) == 0 || ((AgentLinks*)self->roster)->state != 2) {
        SetAgentPrimaryTarget(self, 0);
    }
    if (self->loopBackArmed != 0 && FindColliderFloorContact(self, 0, 0) != 0) {
        ((void (*)(Agent*))((void**)self->desc)[100])(self);
    }
    ApplyPendingAgentChanges(self);
    SettleAgentState(self);
    AnimationPlayer* player = self->statePlayer;
    if (player != 0 && player->anim->movedTrack != 0) {
        PositionCurve* curve = player->anim->movedTrack->pos;
        if (curve != 0) {
            curve->vt->eval(curve, self, player->time, player->speed, 0, 0, &self->headingVelocity);
            u128 neg = Vu0::FromFloat(-1.0f);
            Vu0::Q(self->headingVelocity) = Vu0::MulX(Vu0::Q(self->headingVelocity), neg);
            Vu0::Q(push) = neg;
        } else {
            self->headingVelocity = D_00248D30;
        }
    } else {
        self->headingVelocity = D_00248D30;
    }
    self->desc08()->m5E(self, 0);
    ((void (*)(Agent*))self->desc08()->m5A)(self);
    if (self->roster != 0) {
        QueueItemKeeperUpdate((ItemKeeper*)self->roster);
    }
    DispatchAgentContactHits(self);
    if (*(s32*)((u8*)self + 0xC08) != 0) {
        AgentBody* floor = (AgentBody*)FindColliderFloorContact(self, 0, &kind);
        if (floor != 0) {
            Vec02 scale;
            u128 k = Vu0::FromFloatAt(g_contactSideSigns[kind]);
            Vu0::Q(push) = Vu0::MulX(Vu0::Q(floor->v80), k);
            Vu0::Q(scale) = k;
        } else {
            push = g_unitZVector;
        }
        BuildAxisAngleMatrix((const Vec02*)&g_unitZVector, self->heading, &spin);
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
    s32 s = self->state;
    s32 m = GetAgentRosterState(self);

    if (self->clip10Deadline < g_gameClock[1]) {
        if (self->state != 0xB && self->state != 0x10) {
            if (self->stateClips[10].obj != 0) {
                s = 0xA;
                goto done;
            }
        }
    }

    switch (self->state) {
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
            if (self->mainPlayer != 0) {
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
            if (self->mainPlayer != 0) {
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
            if (self->state6Deadline < g_gameClock[1]) {
                s = 9;
            }
            break;
        case 1:
            if (self->pathValid == 0) {
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
            if (self->statePlayer == 0) {
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
        if (self->statePlayer == 0) {
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
            if (self->statePlayer == 0) {
                s = 0xD;
                break;
            } else {
                if (self->stateClips[14].obj != 0) {
                    if (self->desc08()->m5D(self) != 0) {
                        s = 0xE;
                        break;
                    }
                }
                if (HasAgentReachedPathEnd(self) != 0) {
                    if (self->stateClips[13].obj != 0) {
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
            if (self->stateClips[14].obj != 0) {
                if (self->desc08()->m5D(self) != 0) {
                    s = 0xE;
                    break;
                }
            }
            if (self->pathValid == 0) {
                if (self->stateClips[12].obj != 0) {
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
        if (self->state8Deadline < g_gameClock[1]) {
            s = 8;
        }
        break;
    case 7:
c7:
        if (self->statePlayer == 0) {
            s = 0xC;
        }
        break;
    }
done:
    return s;
}

void SnapPointToOwnerGraph(PointGraphObject* self, Vec02* p, Vec02* out);

void SetAgentGoalPoint(Agent* self, Vec02* p)
{
    Vec02 t;
    self->goalPoint = *p;
    t = self->goalPoint;
    if (self->pathGraph != 0) {
        SnapPointToOwnerGraph(self->pathGraph, &t, &t);
    }
    if (self->pathValid != 0) {
        u128 d = Vu0::Sub(Vu0::Q(self->snappedGoal), Vu0::Q(t));
        s32 far = g_agentGoalFarDistance < Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
        if (far) {
            self->pathValid = 0;
        }
    }
    if (self->pathValid == 0) {
        self->snappedGoal = t;
    }
}

s32 HasAgentReachedPathEnd(Agent* self)
{
    s32 result = 0;
    if (self->pathValid != 0) {
        result = self->pathIndex == self->pathCount;
    }
    return result;
}


s32 IsObjectOfKind(BaseObject* list, s32 key);

s32 IsAgentPathBlocker(void* unused, Collider* self)
{
    if ((self->flags538 & (1ULL << 43)) != 0) {
        if ((self->desc->flags & 0x80) == 0)
            return 0;
        if (self->pushFactor == 0.0f)
            return 0;
    }
    if (IsObjectOfKind(self->root, 5) != 0 || IsObjectOfKind(self->root, 0x40) != 0 || IsObjectOfKind(self->root, 0x41) != 0)
        return 0;
    return 1;
}

s32 FindOwnerGraphPath(PointGraphObject* self, Vec02* start, Vec02* goal, s32 maxOut, Vec02* out);
void GatherCollidersInBox(World* world, Collider* skip, Vec02* a, Vec02* b, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);
s32 FindNearestSpanObject(s32 flags, Vec02* a1, Vec02* a2, s32 count, Collider** list, ColliderSpan* out);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);

// Whether two points are within reach of each other in the ground plane (x and y).
static inline s32 IsNearPoint(Vu0::Vec a, Vu0::Vec b, f32 reach)
{
    return Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(a, b), Vu0::Sub(a, b)))) < reach;
}

// The game clock's time (its second word), read through the clock's address.
static inline f32 ClockTime(const f32* clock) { return clock[1]; }

void BuildAgentPath(Agent* self)
{
    if (F(s32, 0xA60) != 0) {
        if (!(g_agentPathRetryDelay[0] < ClockTime(g_gameClock) - F(f32, 0xA64))) return;
    }
    if (F(s32, 0xB90) != 0) {
        F(s32, 0x92C) = 2;
        u128 pos = Vu0::Q(self->v140);
        Vu0::Q(F(Vec02, 0x940)) = pos;
        f32 maxLen = __builtin_fabsf(F(f32, 0xB94));
        u128 goal = Vu0::Q(self->snappedGoal);
        f32 len = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(goal, pos), Vu0::Sub(goal, pos))));
        Vec02 a;
        if (maxLen < len) {
            f32 t = maxLen / len;
            Vu0::Q(a) = Vu0::MulXSum(goal, Vu0::Scalar(t), pos, Vu0::Scalar(1.0f - t));
        } else {
            Vu0::Q(a) = goal;
        }
        Vec02 b;
        if (self->pathGraph != 0) {
            SnapPointToOwnerGraph(self->pathGraph, &a, &b);
        } else {
            b = a;
        }
        f32 reach = (maxLen <? len) * 0.5f;
        Vec02 c = b;
        while (IsNearPoint(Vu0::Vec::Of(c), Vu0::Vec::Of(self->v140), reach)) {
            f32 next = maxLen + 100.0f;
            maxLen = next <? len;
            f32 t = maxLen / len;
            Vu0::Q(c) = Vu0::MulXSum(Vu0::Q(self->snappedGoal), Vu0::Scalar(t), Vu0::Q(self->v140), Vu0::Scalar(1.0f - t));
            SnapPointToOwnerGraph(self->pathGraph, &c, &c);
        }
        PushBackMemoryMark();
        Vec02 d1;
        Vec02 d4;
        ColliderSpan span;
        s32 count;
        Collider** list;
        Vu0::Set(d1, Vu0::MulAddX(Vu0::Q(c), Vu0::Q(g_unitZVector), Vu0::Scalar(-500.0f)));
        Vu0::Set(d4, Vu0::MulAddX(Vu0::Q(c), Vu0::Q(g_unitZVector), Vu0::Scalar(500.0f)));
        GatherCollidersInBox(self->world, self, &d1, &d4, IsAgentPathBlocker, self, &count, &list);
        if (FindNearestSpanObject(1, &d4, &d1, count, list, &span) != 0) {
            f32 h = -((f32*)F(void*, 0x388))[(F(s32, 0x6D0) << 2) + 2] - 1.0f;
            if (F(s32, 0xC04) != 0) h += F(f32, 0x6CC);
            Vu0::Q(c) = Vu0::MulAddX(Vu0::Q(span.q[0]), Vu0::Q(g_unitZVector), Vu0::Scalar(h));
        }
        PopBackMemoryMark();
        F(Vec02, 0x950) = c;
    } else {
        F(s32, 0x92C) = 0;
        if (self->pathGraph != 0) {
            F(s32, 0x92C) = FindOwnerGraphPath(self->pathGraph, &self->v140, &self->snappedGoal, 0x10, (Vec02*)((u8*)self + 0x940));
        }
        if (F(s32, 0x92C) == 0) {
            F(s32, 0x92C) = 2;
            F(Vec02, 0x940) = self->v140;
            F(Vec02, 0x950) = self->snappedGoal;
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

void FaceAgentAlongPath(Agent* self)
{
    ((void (*)(Agent*))self->desc08()->m5F)(self);
    for (;;) {
        if (!(self->pathIndex < self->pathCount)) break;
        s32 i = self->pathIndex;
        u128 d = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*(Vec02*)((u8*)self + 0x940 + (i << 4))));
        s32 far = g_agentFacingFarDistance < Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
        if (far) break;
        self->pathIndex = i + 1;
    }
    Vec02 dir;
    if (self->pathIndex < self->pathCount) {
        Vu0::Set(dir, Vu0::Sub(Vu0::Q(*(Vec02*)((u8*)self + 0x940 + (self->pathIndex << 4))), Vu0::Q(self->v140)));
    } else {
        s32 m = self->pathCount;
        Vu0::Set(dir, Vu0::Sub(Vu0::Q(*(Vec02*)((u8*)self + 0x930 + (m << 4))), Vu0::Q(*(Vec02*)((u8*)self + 0x920 + (m << 4)))));
    }
    f32 yaw;
    if (1.0f < Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(dir), Vu0::Q(dir))))) {
        yaw = ArctangentOfRatio(dir.y, dir.x);
    } else {
        yaw = self->heading;
    }
    f32 pitch;
    if (F(s32, 0xB1C) == 0) {
        pitch = 0.0f;
    } else {
        u128 e = Vu0::Sub(Vu0::Q(self->snappedGoal), Vu0::Q(self->v140));
        f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(e, e)));
        f32 dz = self->snappedGoal.z - self->v140.z;
        switch (self->state) {
        case 5: case 6: case 7: case 10: case 12: case 13: case 14: case 15:
            dz += F(f32, 0xB20);
            break;
        }
        f32 g1 = g_agentPitchDistanceCoefficients.c[0] + dist * (g_agentPitchDistanceCoefficients.c[1] + dist * g_agentPitchDistanceCoefficients.c[2]);
        g1 = ClampTo(g1, g_agentPitchDistanceLimits.c);
        f32 adz = __builtin_fabsf(dz);
        f32 g2 = g_agentPitchHeightCoefficients.c[0] + adz * (g_agentPitchHeightCoefficients.c[1] + adz * g_agentPitchHeightCoefficients.c[2]);
        g2 = ClampTo(g2, g_agentPitchHeightLimits);
        pitch = g1 * g2 * g_agentPitchScale[0];
        if (dz < 0.0f) pitch = -pitch;
    }
    SetAgentFacingAngles(self, yaw, pitch);
}

void ConvertOffsetToSpherical(const Vec02* a, const Vec02* b, f32* heading, f32* pitch, f32* dist);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);

void FaceAgentTowardGoalPoint(Agent* self)
{
    f32 x;
    f32 y;
    ConvertOffsetToSpherical((const Vec02*)((u8*)self + 0xA40), (const Vec02*)((u8*)self + 0x140), &x, &y, 0);
    SetAgentFacingAngles(self, x, y);
}

void SetAgentGoalPoint(Agent* self, Vec02* p);
void FindNearestAnimationPathTime(Animation* self, PlacedObject* owner, f32 start, Vec02* point, f32* outT, Vec02* outPos, Vec02* outDir);
BlendSourceEntry* FindEntryByObjectId(BlendAnimationView* self, BaseObject* key);

void UpdateAgentGoal(Agent* self, s32 flag)
{
    Vec02 q;
    switch (self->state) {
    case 7:
    case 10:
    case 12:
    case 13:
    case 14: {
        void* v = self->desc08()->m62(self);
        if (v != 0) SetAgentGoalPoint(self, (Vec02*)((u8*)v + 0x140));
        break;
    }
    case 4:
        if (flag != 0) {
            if (self->mainClip != 0) {
                switch (self->f920) {
                case 0:
                    FindNearestAnimationPathTime((Animation*)self->mainClip, self, self->savedClipTime, (Vec02*)((u8*)self + 0x140), (f32*)((u8*)self + 0x914), &q, 0);
                    break;
                case 1: {
                    self->resumeTime = self->savedClipTime;
                    PoseSource* t = FindEntryByObjectId((BlendAnimationView*)self->mainClip, self)->mover;
                    t->vtbl[0](t, self, self->resumeTime, 1.0f, 0, &q, 0);
                    break;
                }
                }
                self->savedClipSpeed = 1.0f;
            } else {
                q = self->v190;
            }
            SetAgentGoalPoint(self, &q);
        }
        break;
    case 5:
        if (flag != 0) SetAgentGoalPoint(self, (Vec02*)((u8*)self + 0x900));
        break;
    }
}

void IsAgentNearPathEnd(Agent* self, s32* out) { if (self->pathValid && self->pathIndex >= self->pathCount - 2) { *out = 1; return; } *out = 0; }

void CreateAnimationPlayer(Animation* self, BaseObject* alt, s32 npairs, TargetBinding* pairs, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);
void AddAnimationPlayerRecordCallback(AnimationPlayer* a0, PlacedObject** a1);
s32 GetEffectiveObjectId(BaseObject* a);
Attachment* FindPlayerAttachmentByOwner(AnimationPlayer* a0, s32 owner);

void CreateAgentAnimationPlayer(Agent* self)
{
    StateResetObject* sub = ((StateResetObject*)self->stateObject);
    if (sub->id2DC != 0) {
        s32 pair[2];
        pair[0] = sub->id;
        pair[1] = (s32)self;
        CreateAnimationPlayer((Animation*)sub->id2DC, self, 1, (TargetBinding*)pair, 1, &self->mainPlayer, 0.0f, 1.0f);
        AddAnimationPlayerRecordCallback(self->mainPlayer, (PlacedObject**)((self->stateObject)));
        Attachment* node = FindPlayerAttachmentByOwner(self->mainPlayer, GetEffectiveObjectId(self));
        if ((void*)node == self->positionAttachment) {
            node->mode0 = 5;
        }
        if ((void*)node == self->orientationAttachment) {
            node->mode1 = 5;
        }
    }
}

extern f32 g_frameDt;
s32 HasAnimationDrivenAttachment(SwitchedCollider *self);
void FaceAgentFromAnimationMotion(Agent* self);
void ComputeObjectSteeringHeading(f32 a, f32 b, PlacedObject* self, f32* p1, f32* p3, f32* out0, f32* out1, f32* out2);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);
void ScheduleItemTimeouts(StateResetGroup* self);
void FaceAgentAlongPath(Agent* self);
void FaceAgentTowardGoalPoint(Agent* self);

void UpdateAgentState(Agent* self)
{
    self->desc08()->m62(self);
    switch (self->state) {
    case 0:
    case 16:
        break;
    case 1:
    case 2:
        if (HasAnimationDrivenAttachment(self) != 0)
            FaceAgentFromAnimationMotion(self);
        break;
    case 3:
        if (self->mainPlayer != 0) {
            f32 out[3];
            f32 zero = 0.0f;
            out[1] = zero;
            ComputeObjectSteeringHeading(g_frameDt, self->heading, self, 0, 0, &out[0], self->usesPitch ? &out[1] : 0, &out[2]);
            f32 y = out[1];
            SetAgentFacingAngles(self, out[0], y);
        }
        ScheduleItemTimeouts((StateResetGroup*)(((StateResetObject*)self->stateObject)->group));
        break;
    case 4:
    case 5:
    case 12:
        FaceAgentAlongPath(self);
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
void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);

void ChangeAgentState(Agent* self, s32 state, void* context)
{
    self->requestBits &= -2;
    if (self->state == state) return;
    s32 old = self->state;
    self->desc08()->m5B(self, state, context);
    self->state = state;
    self->stateTime = g_gameClock[1];
    self->desc08()->m5C(self, old, context);
    StateChangeArgs frame;
    frame.oldSlot = &old;
    frame.stateSlot = &self->state;
    TriggerScriptEvent(self, 15, 2, &frame);
}

void ChangeAgentState(Agent* self, s32 state, void* context);

void ForceAgentState(Agent* self, s32 mode, void* value)
{
    if (mode == -1) {
        self->stateForced = 0;
    } else {
        self->stateForced = 1;
        ChangeAgentState(self, mode, value);
    }
}

void StopAnimationPlayer(AnimationPlayer* self);
f32 RandomFloatInRange(f32 a, f32 b);
void SetStateAndNotify(StateResetObject* p, s32 z);
void InitContactPairFlags(World* self, Collider* obj);

void LeaveAgentState(Agent* self, s32 mode)
{
    s32 i;
    if (self->statePlayer != 0) {
        self->lastClipPhase = self->statePlayer->time / self->statePlayer->anim->length;
    }
    self->followsClipMotion = 0;
    self->facingLocked = 0;
    self->stateLocked = 0;
    self->loopBackArmed = 0;
    for (i = 0; i < self->meshKeyCount; i++) {
        ((BaseObject*)self->meshKeys[i].obj)->desc->m03((BaseObject*)self->meshKeys[i].obj);
    }
    switch (self->state) {
    case 1:
        if (self->mainPlayer != 0 && mode != 2) {
            self->savedClipTime = self->mainPlayer->time;
            self->savedClipSpeed = self->mainPlayer->speed;
            StopAnimationPlayer(self->mainPlayer);
            self->mainPlayer = 0;
        }
        break;
    case 3:
        if (self->mainPlayer != 0) {
            StopAnimationPlayer(self->mainPlayer);
            self->mainPlayer = 0;
        }
        ((StateResetObject*)self->stateObject)->desc->m18(((StateResetObject*)self->stateObject), self);
        SetStateAndNotify(((StateResetObject*)self->stateObject), 0);
        self->stateObject = 0;
        if (mode == 1) {
            self->resumeTime = self->savedClipTime;
        }
        break;
    case 14:
        self->targetReadyTime = g_gameTime[0] + RandomFloatInRange(self->retargetDelayMin, self->retargetDelayMax);
        break;
    case 11:
        self->state = mode;
        InitContactPairFlags(g_currentWorld, self);
    case 16:
        self->contactsDisabled = 0;
        break;
    case 8:
        self->state8Deadline = 3.4028235e+38f;
        break;
    }
    if (self->statePlayer != 0) {
        StopAnimationPlayer(self->statePlayer);
        self->statePlayer = 0;
        self->requestBits &= ~2;
    }
}



void SetTurningColliderFollowedMesh(TurningCollider* self, Collider* other, s32 all);
void SetAnimationPlayerSpeed(AnimationPlayer* t, f32 x);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);
void CreateAgentAnimationPlayer(Agent* self);
struct ScatterController;
void CreateAnimationPlayerWithoutPresetTargets(Animation* self, BaseObject* alt, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);
void CreateAnimationPlayer(Animation* self, BaseObject* alt, s32 npairs, TargetBinding* pairs, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);
s32 GetEffectiveObjectId(BaseObject* a);
Attachment* FindPlayerAttachmentByOwner(AnimationPlayer* a0, s32 owner);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void ScatterObjectsAtPoint(ScatterController* self, void* p, s32 n, s32 flag);
void InitContactPairFlags(World* self, Collider* obj);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherAnimationEventObjects(Animation* self, BaseObject* ctx, s32* outCount, BaseObject*** outArr);
void RemoveFromSmallList(StateResetGroup* self, StateResetObject* value);
void SetFlagTableBit(FlagTable* self, s32 bit);
void FadeOutPlacedObject(Collider* self, f32 time);
f32 RandomFloatInRange(f32 x, f32 y);
void FaceAgentAlongPath(Agent* self);
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
        tgt = (Animation*)self->stateClips[self->state].obj;
    }
    t = (Animation*)self->secondaryClips[self->state].obj;
    if (t == 0) {
        t = ((Animation*)self->defaultSecondaryClip);
    }
    SetTurningColliderFollowedMesh(self, (Collider*)t, 0);
    self->desc08()->m5E(self, 1);

    switch (self->state) {
    case 2:
        if (self->mainPlayer != 0) {
            SetAnimationPlayerSpeed(self->mainPlayer, 1.0f);
        } else {
            SetAgentFacingAngles(self, self->v1D0.z, 0.0f);
        }
        break;
    case 3:
        if (((StateResetObject*)self->stateObject)->id2D0 == 2) {
            CreateAgentAnimationPlayer(self);
        }
        break;
    case 1:
        if (((Animation*)self->mainClip) != 0 && evt != 2) {
            Attachment* v;
            CreateAnimationPlayerWithoutPresetTargets(((Animation*)self->mainClip), self, 1, &self->mainPlayer, self->resumeTime, self->savedClipSpeed);
            v = FindPlayerAttachmentByOwner(self->mainPlayer, GetEffectiveObjectId(self));
            if ((void*)v == self->positionAttachment) {
                v->mode0 = 5;
            }
            if ((void*)v == self->orientationAttachment) {
                v->mode1 = 5;
            }
        }
        break;
    case 11: {
        Quad4 vec;
        s32 count;
        BaseObject** list;
        TransformPointBetweenFrames(self, 0, (Vec02*)self->scatterPoint, (Vec02*)&vec);
        ScatterObjectsAtPoint((ScatterController*)g_scatterController, &vec, self->fB58, self->fB70);
        InitContactPairFlags(g_currentWorld, self);
        if (((Animation*)self->mainClip) != 0) {
            s32 i;
            PushBackMemoryMark();
            i = 0;
            GatherAnimationEventObjects(((Animation*)self->mainClip), self, &count, &list);
            while (i < count) {
                BaseObject* e = list[i++];
                RemoveFromSmallList((StateResetGroup*)(*(s32*)((u8*)e + 0x328)), (StateResetObject*)e);
            }
            PopBackMemoryMark();
        }
        SetFlagTableBit((FlagTable*)g_flagTable, self->flagIndex);
        if (((BaseObject*)self->target) != 0) {
            ((BaseObject*)self->target)->desc->m18(((BaseObject*)self->target), self);
            self->target = 0;
        }
        if (self->fadesOut != 0) {
            f32 f = self->fadeDelay;
            if (tgt != 0) {
                f += tgt->length;
            }
            FadeOutPlacedObject(self, f);
        }
        self->contactsDisabled = 1;
        break;
    }
    case 16:
        self->contactsDisabled = 1;
        self->hitsLeft--;
        break;
    case 6:
        self->state6Deadline = 3.4028235e+38f;
        SetAgentFacingAngles(self, self->placeHeading, 0.0f);
        break;
    case 7:
        self->fBF8 = 3.4028235e+38f;
        break;
    case 10:
        self->clip10Deadline = 3.4028235e+38f;
        break;
    }

    if (tgt != 0) {
        f32 w;
        s32 mode;
        if (self->state == 2 && self->fB14 != 0) {
            f32 t = self->startPhase;
            w = (0.0f <= t) ? t : RandomFloatInRange(0.0f, 1.0f);
        } else {
            Animation* cur = ((Animation*)self->lastClip);
            if (cur == 0) {
                w = 0.0f;
            } else if (tgt == cur) {
                w = self->lastClipPhase;
            } else {
                s32 i;
                w = 0.0f;
                for (i = 0; i < self->clipGroupCount; i++) {
                    Group08* g = &self->clipGroups[i];
                    u32 j;
                    for (j = 0; j < 4; j++) {
                        if (((BaseObject*)self->lastClip)->id == g->ids[j]) {
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
                            w = self->lastClipPhase;
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
        if (self->bindingKey == -1 || self->bindingObject == 0) {
            CreateAnimationPlayerWithoutPresetTargets(tgt, self, mode, &self->statePlayer, w * tgt->length, 1.0f);
        } else {
            CreateAnimationPlayer(tgt, self, 1, (TargetBinding*)&self->bindingKey, mode, &self->statePlayer, w * tgt->length, 1.0f);
        }
        self->lastClip = tgt;
        self->lastClipPhase = 0.0f;
    }

    switch (self->state) {
    case 1:
    case 4:
    case 5:
    case 12:
        FaceAgentAlongPath(self);
        break;
    case 7:
    case 10:
    case 13:
    case 14:
        FaceAgentTowardGoalPoint(self);
        break;
    }
}

s32 GetAgentRosterState(Agent* self) { if (!self->roster) return 3; return *(s32*)((u32)self->roster + 0x50); }

#include "object_message.h"
struct TrackedNodeOffer;

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

struct ObjectEvent;
s32 HandleObjectEvent(Collider* self, ObjectEvent* shape);
void TurnColliderTowardHeading(TurningCollider* self);
void ChangeAgentState(Agent* self, s32 state, void* arg);
extern const Vec02 g_unitXVector;

s32 HandleAgentObjectEvent(Agent* self, AgentHit* ev)
{
    SlotMessage msg;
    if (self->requestsBlocked != 0) {
        return 1;
    }
    if (self->targetSet != 0 && (ev->obj->desc->flags & 2) != 0 && IsObjectInPool((ObjectPool*)self->targetSet, (Collider*)ev->obj) != 0) {
        return 1;
    }
    s32 handled = HandleObjectEvent(self, (ObjectEvent*)ev);
    if (handled == 0 || (ev->flags & 0x20) == 0) {
        return handled;
    }
    void* key = 0;
    s32 i = self->extraClipCount;
    while (--i >= 0) {
        Pend08* r = &self->extraClips[i];
        if (r->mask & ev->mask) {
            key = r->obj;
            break;
        }
    }
    if (*(s32*)((u8*)self + 0xBDC) != 0) {
        if (0.0001f < Vu0::ToFloat(Vu0::Length(Vu0::Q(ev->push)))) {
            self->facingLocked = 0;
            f32 heading = ArctangentOfRatio(-ev->push.y, -ev->push.x);
            f32 turn = WrapAngle(heading - self->heading);
            SetAgentFacingAngles(self, WrapAngle(self->heading + turn * *(f32*)&self->fBD0), self->pitch);
            TurnColliderTowardHeading(self);
        }
    }
    ChangeAgentState(self, self->hitsLeft > 0 ? 16 : 11, key);
    if (self->memberGroup != 0) {
        msg.kind = 6;
        Vu0::Q(msg.vb) = Vu0::Q(self->v140);
        msg.vb.z = ev->height;
        if (ev->obj != 0 && (ev->obj->desc->flags & 1) != 0) {
            Vu0::Q(msg.va) = Vu0::DivX(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(ev->obj->v140)), Vu0::Length(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(ev->obj->v140))));
        } else {
            Vu0::Set(msg.va, Vu0::NormalizeOrMoved(Vu0::Q(ev->push), Vu0::Q(g_unitXVector)));
        }
        self->memberGroup->desc->m1B(self->memberGroup, &msg);
    }
    ((AgentNotice*)&msg)->self = self;
    ((AgentNotice*)&msg)->obj = ev->obj;
    self->desc->m0E(self, 0x17, &msg);
    return handled;
}

// What slot 76 is asked about: a kind and the object concerned.
#include "agent_request.h"

extern "C" void* FillMemory(void* p, s32 value, s32 size);
s32 FindNodeForQuery(NodeQuery* q, s32 n, PlacedObject** list);

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

s32 IsAgentRequestBlocked(Agent* self, s32 unused1) { return self->requestsBlocked != 0; }



void StopAnimationPlayer(AnimationPlayer* self);
void ChangeAgentState(Agent* self, s32 state, void* context);

void ApplyPendingAgentChanges(Agent* self) {
    if (self->requestBits == 0) {
        return;
    }
    if (self->requestBits & 2) {
        if (self->statePlayer != 0) {
            if (self->state != 0xB) {
                StopAnimationPlayer(self->statePlayer);
                self->statePlayer = 0;
            } else {
                self->statePlayer->time = self->statePlayer->anim->length;
                self->statePlayer->f10 = 3.4028235e+38f;
            }
        }
        s32 m = -3;
        self->requestBits &= m;
    }
    if (self->requestBits & 1) {

        ChangeAgentState(self, self->requestedState, 0);
    }
}

struct ValueRange;
f32 ClampToRange(ValueRange* span, f32 x);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);

void SteerAgentAlongPath(Agent* self)
{
    s32 last = self->pathCount - 1;
    s32 n = self->pathIndex;
    n = (n < last) ? n : last;
    Vec02 target;
    Vu0::Q(target) = Vu0::Q(*(Vec02*)((u8*)self + 0x940 + (n << 4)));
    Vec02 d;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(target), Vu0::Q(self->v140));
    f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(d), Vu0::Q(d))));
    f32 t = ClampToRange((ValueRange*)((u8*)self + 0xB9C), dist / __builtin_fabsf(F(f32, 0xB94)));
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

f32 GetAnimationMarkerTime(Animation* self, s32 key);
void SeekAnimationPlayer(AnimationPlayer* self, s32 mode, f32 a, f32 b);

void RestartAgentClip(Agent* self)
{
    self->loopBackArmed = 0;
    self->pathValid = 0;
    f32 r = GetAnimationMarkerTime(self->statePlayer->anim, 0x1B1);
    SeekAnimationPlayer(self->statePlayer, 0, r, 1.0f);
    self->arrivalTime = 0;
}

s32 IsObjectInPool(ObjectPool* list, BaseObject* query);

s32 TestAgentTargetContact(Agent* self, s32 key, Collider* other)
{
    if (key != (s32)self->target)
        return 0;
    switch (self->state) {
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
    if (!self->targetSet)
        goto ret0;
    if (!IsObjectInPool((ObjectPool*)self->targetSet, other))
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

void HandleSwitchedColliderNotification(SwitchedCollider* self, s32 kind, void* msg);
void SetAgentMainClip(Agent* self, void* value);
AnimEvent* FindAnimationMarkerEvent(Animation* self, s32 key);
s32 LaunchChosenPoolObject(ObjectPool* pool, s32 aim);
typedef void (*AgentSlotFn)(Agent* self);

void HandleAgentNotification(Agent* self, s32 kind, AgentNotification* msg)
{
    HandleSwitchedColliderNotification(self, kind, msg);
    switch (kind) {
    case 5:
        if ((void*)msg == self->statePlayer) {
            self->requestBits |= 2;
        } else if ((void*)msg == self->mainPlayer) {
            SetAgentMainClip(self, 0);
        }
        break;
    case 0x15: {
        if (msg->source != self->mainPlayer) {
            break;
        }
        StateResetObject* obj = (StateResetObject*)msg->obj;
        self->stateObject = obj;
        obj->desc->m17(obj, self);
        self->requestBits |= 1;
        self->requestedState = 3;
        s32 state;
        s32 id = ((StateResetObject*)self->stateObject)->id2E0;
        ItemKeeper* keeper;
        if (id != -1 && (keeper = (ItemKeeper*)self->roster) != 0) {
            if (keeper->selectedId == -1) {
                keeper->selectedId = id;
            }
            state = ((ItemKeeper*)self->roster)->selectedId == ((StateResetObject*)self->stateObject)->id2E0 ? 1 : 2;
        } else {
            state = 2;
        }
        SetStateAndNotify((StateResetObject*)self->stateObject, state);
        break;
    }
    case 0x16:
        if (msg->source != self->stateObject) {
            break;
        }
        switch (msg->code) {
        case 2:
            if (self->state == 3) {
                CreateAgentAnimationPlayer(self);
            }
            break;
        case 0:
            self->requestedState = 1;
            self->requestBits |= 1;
            break;
        }
        break;
    case 0x13: {
        AnimationPlayer* player = (AnimationPlayer*)msg->source;
        Animation* anim = player->anim;
        if (player != self->statePlayer) {
            break;
        }
        switch (msg->code) {
        case 0x138:
            if (anim->movedTrack == 0) {
                break;
            }
        slope: {
            Vec02 v;
            Vec02 w;
            PositionCurve* c = anim->movedTrack->pos;
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
            if (anim->movedTrack == 0 || anim->movedTrack->pos == 0) {
                break;
            }
            self->followsClipMotion = 1;
            goto slope;
        case 0x1A7:
            self->followsClipMotion = 0;
            break;
        case 0x1AC: {
            F(s32, 0xB90) = 1;
            self->pathValid = 0;
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
            anim->movedTrack->pos->vt->eval(anim->movedTrack->pos, self, from->a0.f, zero, 0, &p0, 0);
            anim->movedTrack->pos->vt->eval(anim->movedTrack->pos, self, end->a0.f, zero, 0, &p1, 0);
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
            self->loopBackArmed = 1;
            break;
        case 0x1B1:
            if (self->loopBackArmed != 0) {
                AnimEvent* e = FindAnimationMarkerEvent(anim, 0x1B0);
                f32 t = e != 0 ? e->a0.f : msg->time;
                SeekAnimationPlayer(self->statePlayer, 0, t, e != 0 ? 1.0f : 0.0f);
            }
            break;
        case 0x1AA:
            self->stateLocked = 1;
            break;
        case 0x1AB:
            self->stateLocked = 0;
            break;
        case 0x1A8:
            self->facingLocked = 1;
            break;
        case 0x1A9:
            self->facingLocked = 0;
            break;
        case 0x1B2:
            self->requestsBlocked = 1;
            break;
        case 0x1B3:
            self->requestsBlocked = 0;
            break;
        case 0x1A5: {
            u8* g = (u8*)self->targetSet;
            if (g != 0) {
                if (*(s32*)(g + 0x50) == -1) {
                    *(void**)(g + 0xE0) = self->desc08()->m62(self);
                }
                LaunchChosenPoolObject((ObjectPool*)self->targetSet, 1);
            }
            break;
        }
        }
        break;
    }
    case 0xA:
        if (msg->obj == self && self->loopBackArmed != 0) {
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
            self->clip10Deadline = g_gameClock[1] + F(f32, 0xBE0);
        } else {
            f32 r = RandomFloatInRange((f32)(nearer - 1) / (f32)count, (f32)nearer / (f32)count);
            self->clip10Deadline = g_gameClock[1] + (1.0f - r) * F(f32, 0xBE0) + r * F(f32, 0xBE4);
        }
        break;
    }
    }
}

s32 AnswerAgentRosterPoll(void)
{
    return 2;
}

s32 IsInsideRange(ValueRange* span, f32 x);
s32 HasObjectPoolChoice(ObjectPool* self);
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
    if (IsInsideRange((ValueRange*)&self->targetRangeMin, dist) == 0) {
        return 0;
    }
    f32 bearing = __builtin_fabsf(ComputeAgentTargetBearing(self));
    f32 g = g_agentTargetRangeCoefficients.c[0] + dist * (g_agentTargetRangeCoefficients.c[1] + dist * g_agentTargetRangeCoefficients.c[2]);
    g = Limit(g, g_unitRange[0], g_unitRange[1]);
    if (self->targetAngleLimit < g * bearing) {
        return 0;
    }
    if (g_gameTime[0] < self->targetReadyTime) {
        return 0;
    }
    if (self->targetSet != 0 && HasObjectPoolChoice((ObjectPool*)self->targetSet) == 0) {
        return 0;
    }
    return 1;
}

void DrawTurningCollider(TurningCollider* self, void* unused1, void* unused2);

void DrawAgent(Agent* self, void* unused1, void* unused2)
{
    DrawTurningCollider(self, unused1, unused2);
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
        Slot08* p = &self->stateClips[index];
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
    return (s32)self->stateClips[index].obj;
}

void AddAgentExtraClip(Agent* self, s32 a1, s32 a2)
{
    s32 n = self->extraClipCount;
    if ((u32)n < 4) {
        self->extraClipCount = n + 1;
        Pend08* p = &self->extraClips[n];
        p->mask = a1;
        p->id = a2;

    }
}

void MoveObjectAnimationTrackToEnd(Animation* a0, BaseObject* owner);
void ResolveAndStartObject(BaseObject* self);

void* ResolveAgentClip(Agent* self, s32 id)
{
    Animation* item = (Animation*)FindFirstObjectById(self->world, 0x101, id, self->copySource);
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
    Slot08* slot = self->stateClips;
    do {
        if (slot->id != -1) {
            slot->obj = ResolveAgentClip(self, slot->id);
            slot->id = -1;
        }
        i--;
        slot++;
    } while (i >= 0);

    s32 j = 0;
    if (self->extraClipCount > 0) {
        do {
            Pend08* late = &self->extraClips[j];
            if (late->id != -1) {
                late->obj = ResolveAgentClip(self, late->id);
                late->id = -1;
            }
            j++;
        } while (j < self->extraClipCount);

    }
}

void SetAgentMemberGroupId(Agent* self, s32 v)
{
    self->memberGroupId = v;
    self->hasMemberGroupId = 1;
}

void SetAgentTargetSetId(Agent* self, s32 v)
{
    self->targetSetId = v;
    self->hasTargetSetId = 1;
}

s32 IsAgentSlotIndex(s32 index);

void SetAgentSecondaryClipId(Agent* self, s32 index, s32 value)
{
    if (IsAgentSlotIndex(index))
        self->secondaryClips[index].id = value;
}

void ResolveAndStartObject(BaseObject* self);

void ResolveAgentSecondaryClips(Agent* self)
{
    for (s32 i = 16; i >= 0; i--) {
        Slot08* e = &self->secondaryClips[16 - i];
        if (e->id != -1) {
            void* r = FindFirstObjectById(self->world, 0x101, e->id, self);
            e->obj = r;
            if (r != 0) ResolveAndStartObject((BaseObject*)r);
        }
    }
}

void AddAgentMeshKey(Agent* self, s32 a, s32 b)
{
    u32 n = self->meshKeyCount;
    if (n < 4) {
        self->meshKeyCount = n + 1;
        Elem08* e = &self->meshKeys[n];
        e->key = a;
        e->messageKind = b;
    }
}


void SetAgentPathObjectId(Agent* self, s32 index)
{
    PointGraphObject* v;
    if (index == -1) {
        v = 0;
    } else {
        v = (PointGraphObject*)FindFirstObjectByIdMode4(self->world, index, self);
        if (v == 0)
            return;
    }
    if (v != self->pathGraph)
        self->pathValid = 0;
    self->pathGraphId = index;
    self->pathGraph = v;
}

void* GetActiveSwitchedCollider(void);

void* SelectAgentTarget(Agent* self)
{
    void* s0;
    if (self->primaryTarget != 0) {
        s0 = self->primaryTarget;
    } else if (self->hasSecondaryTarget != 0) {
        s0 = self->secondaryTarget;
    } else {
        s0 = GetActiveSwitchedCollider();
    }
    void* v = GetActiveSwitchedCollider();
    if (v != 0 && v == s0) {
        s32 r = ((SwitchedCollider*)s0)->desc05()->m4D((SwitchedCollider*)s0);
        s0 = (r == 2) ? 0 : s0;
    }
    void* a0 = self->target;
    if (s0 == a0) {
        return s0;
    }
    if (a0 != 0) {
        ((BaseObject*)a0)->desc->m18((BaseObject*)a0, self);
    }
    if (s0 != 0) {
        ((BaseObject*)s0)->desc->m17((BaseObject*)s0, self);
    }
    self->target = s0;
    return s0;
}

void StoreAgentTarget(Agent* self, s32* out)
{
    *out = (s32)self->desc08()->m62(self);
}

void SetAgentSecondaryTarget(Agent* self, s32 value)
{
    self->secondaryTarget = (void*)value;
    self->hasSecondaryTarget = 1;

}


void PickAgentSecondaryTarget(Agent* self)
{
    PlacedObject* found[0x20];
    Vec02 vel;
    Vec02 here;
    Vec02 there;
    Vec02 lead;
    s32 n = GatherObjectsByMode(self->world, 5, self->secondaryTargetKey, 0, 0x20, found);
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
        if (obj == self->secondaryTarget) {
            d *= 0.5f;
        }
        if (d < best) {
            best = d;
            pick = obj;
        }
    }
    self->secondaryTarget = pick;
    self->hasSecondaryTarget = 1;
}

void SetAgentPrimaryTarget(Agent* self, s32 value)
{
    self->primaryTarget = (void*)value;
}



void ComputeAgentContactValue(Agent* self, Contact03* out)
{
    if (self->contactsDisabled != 0) {
        f32 a = D_00274CF4;
        f32 b = D_00274CF8[0];
        out->friction = a;
        out->bounce = b;
    } else {
        if (((s32 (*)(Agent*, void*))self->desc06()->m56)(self, out) != 0) {
            f32 t = self->contactValue;
            out->bounce = 0.0f;
            out->friction = t;
        } else {
            out->friction = 0.0f;
            out->bounce = 0.0f;
        }
    }
}

void ClampTurningColliderContactLimit(TurningCollider* self, s32 flags, ContactLimit03* limit);

void ClampAgentContactLimit(Agent* self, s32 flags, ContactLimit03* out)
{ ClampTurningColliderContactLimit(self, flags, out);
    if (self->contactsDisabled != 0) { if ((flags & 0x12) == 0x12) { if (0.7f < out->contact->normal.z) { out->limit = 0; } } } }

void SetAgentAngleLimitDegrees(Agent* self, f32 value) { self->targetAngleLimit = value * 0.017453294f; }

void AddItemKeeperStateTrigger(ItemKeeper* self, StateTrigger* value);

void AddAgentStateTrigger(Agent* self, StateTrigger* value)
{
    AddItemKeeperStateTrigger((ItemKeeper*)self->roster, value);
}

void AddAgentClipGroup(Agent* self, s32 a, s32 b, s32 c, s32 d) { if ((u32)self->clipGroupCount < 8) { Group08* e = &self->clipGroups[self->clipGroupCount]; self->clipGroupCount++; e->ids[0] = a; e->ids[1] = b; e->ids[2] = c; e->ids[3] = d; } }

struct FaceRef;
struct PooledContact;
void AddTurningColliderProbeContact(TurningCollider* self, Collider* obj, void* filter, void* out);
s32 IsObjectOfKind(BaseObject* list, s32 key);
s32 IsObjectAttached(BaseObject* self);
void AddMeshContacts(Collider* a0, f32 radius, Vec02* a1, Collider* a2, s32 a3, FaceRef* a4, FaceRef* a5, PooledContact** a6);
void CreateMeshPairContacts(Collider* self, Collider* other, s32 a2, FaceRef* a3, u8* ctx, PooledContact** list);

void CollideAgentWithObject(Agent* a0, Collider* a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    if (a0->contactsDisabled == 0) {
        AddTurningColliderProbeContact(a0, a1, (void*)a4, (void*)a5);
    }
    if (a1 != a0->desc08()->m62(a0)) {
        if (a1->parent != 0) {
            return;
        }
        if (IsObjectOfKind(a1, 0x4C) == 0) {
            return;
        }
    }
    for (s32 i = 0; i < a0->meshKeyCount; i++) {
        Elem08* e = &a0->meshKeys[i];
        if (IsObjectAttached((Collider*)e->obj) != 0) {
            if (a1->flags538 & 0x10000000000ULL) {
                AddMeshContacts(a1, a1->radius3CC, (Vec02*)((u8*)a1 + 0x140), (Collider*)e->obj,
                              ((Collider*)e->obj)->tree.count,
                              (FaceRef*)((Collider*)e->obj)->tree.nodes, 0, (PooledContact**)((u8*)a0 + 0xAAC));
            } else if (a3 != 0) {
                CreateMeshPairContacts((Collider*)e->obj, a1, a2, (FaceRef*)a3, (u8*)a4, (PooledContact**)((u8*)a0 + 0xAAC));
            }
        }
    }
}

s32 IsObjectOfKind(BaseObject* list, s32 key);
void SetPlayerState(Player* self, s32 state, s32 sub);

void LaunchObjectWithAgentVelocity(u8* self, PlacedObject* other)
{
    other->desc02()->m20(other, (Vec02*)(self + 0xAB0));
    if (IsObjectOfKind(other, 7) != 0) {
        SetPlayerState((Player*)other, 4, 0x2B);
    }
}

void InitOwnerMessage(OwnerMessage* self, s32 mode, void* owner);
void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec02* origin, Vec02* vel, Vec02* velSum, Vec02* spin, Vec02* spinSum);
void ClampVectorLength(Vec02* in, Vec02* out, f32 max);
void FreePooledContactChain(World* world, Contact03* head);

// A query for the node an agent's contact leads to: the agent, the part it touched and where
// the agent is.
inline void InitAgentContactQuery(NodeQuery* q, Agent* self, Collider* part)
{
    FillMemory(q, 0, 0x40);
    q->pos = self->v140;
    q->hold = part;
    q->p00 = self;
}

void DispatchAgentContactHits(Agent* self)
{
    void* target = self->desc08()->m62(self);
    if (target == 0) {
        return;
    }
    if (self->contactsDisabled == 0) {
        Contact03* head = self->hitContacts;
        if (head == 0) {
            goto out;
        }
        Player* p = g_player;
        if (target == p || target == self->primaryTarget) {
            if (self->sparePlayerContacts == 0) {
                void* h = p->aimTarget;
                if (h != 0) {
                    h = *(void**)((u8*)h + 0x18);
                    if (h != 0 && *(Agent**)((u8*)h + 0x50) == self) {
                        switch (p->aimMode) {
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                            if (g_gameTime[0] - p->aimStartTime < 0.25f) {
                                goto out;
                            }
                        }
                        if (g_player->state == 10 && g_gameTime[0] - g_player->stateStartTime < 0.25f) {
                            goto out;
                        }
                        switch (g_player->subState) {
                        case 7:
                        case 8:
                            if (g_gameTime[0] - g_player->subStateStartTime < 0.25f) {
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
            for (i = 0; i < self->meshKeyCount; i++) {
                e = &self->meshKeys[i];
                if (e->obj == c->end[j].part && IsObjectAttached((Collider*)e->obj) != 0) {
                    break;
                }
            }
            if (i < self->meshKeyCount) {
                ContactEnd03* other = &c->end[1 - j];
                Collider* part = other->part;
                OwnerMessage msg;
                Vec02 vel;
                if (IsObjectOfKind(part, 5) != 0) {
                    InitOwnerMessage(&msg, e->messageKind, self);
                    switch (msg.mode) {
                    case 6:
                        if (self->usesPitch != 0) {
                            msg.fn = (void (*)(void))LaunchObjectWithAgentVelocity;
                            self->launchVelocity = D_00248D30;
                            break;
                        }
                    case 0:
                        ComputeObjectMotionInFrame(c->end[j].part, 0, &c->end[1 - j].point, &vel, 0, 0, 0);
                        Vu0::Q(vel) = Vu0::MulX(Vu0::Vec::Of(vel), Vu0::Vec::Scalar(g_agentHitVelocityBoost + 1.0f)).q;
                        ClampVectorLength(&vel, &vel, g_agentHitMaxSpeed);
                        vel.z = g_agentHitMinUpSpeed >? vel.z;
                        msg.fn = (void (*)(void))LaunchObjectWithAgentVelocity;
                        self->launchVelocity = vel;
                        break;
                    }
                    ((SwitchedCollider*)part)->desc05()->m4C((SwitchedCollider*)part, &msg);
                } else {
                    NodeQuery q;
                    InitAgentContactQuery(&q, self, part);
                    ComputeObjectMotionInFrame(c->end[j].part, 0, &other->point, &q.dir, 0, 0, 0);
                    q.kind = 2;
                    FindNodeForQuery(&q, 0, 0);
                }
                for (i = 0; i < self->meshKeyCount; i++) {
                    ((BaseObject*)self->meshKeys[i].obj)->desc->m03((BaseObject*)self->meshKeys[i].obj);
                }
                break;
            }
        }
    }
out:
    FreePooledContactChain(self->world, self->hitContacts);
    self->hitContacts = 0;
}

void StopAnimationPlayer(AnimationPlayer* self);
s32 GetAgentRosterState(Agent* self);
void FindNearestAnimationPathTime(Animation* self, PlacedObject* owner, f32 start, Vec02* point, f32* outT, Vec02* outPos,
                   Vec02* outDir);

void SetAgentMainClip(Agent* self, void* value)
{
    void* p;

    if (value == self->mainClip) {
        return;
    }
    p = self->mainPlayer;
    if (p != 0) {
        StopAnimationPlayer((AnimationPlayer*)p);
        self->mainPlayer = 0;
    }
    self->mainClip = value;
    if (GetAgentRosterState(self) == 0) {
        self->requestedState = 0;
        self->requestBits = self->requestBits | 1;
    }
    p = self->mainClip;
    if (p != 0) {
        FindNearestAnimationPathTime((Animation*)p, self, 0.0f, (Vec02*)((u8*)self + 0x140), (f32*)((u8*)self + 0x918), 0, 0);
    }
}

s32 RequestAgentLaunch(Agent* self, void* source, TrackedNodeOffer* offer)
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
    s32 untargetable;       // 0x54: non-zero when the object the player holds stops agents targeting it
};
struct Blocker_23A8 {
    u8 pad00[0x6C];
    s32 untargetable;       // 0x6C: non-zero when the object the player holds stops agents targeting it
};

s32 MaskWorldBitsBySave(void);
s32 IsObjectOfKind(BaseObject* list, s32 key);

s32 IsPlayerUntargetableByAgent(Agent* self)
{
    Player* t = (Player*)self->desc08()->m62(self);
    if (IsObjectOfKind(t, 7) == 0) {
        return 0;
    }
    if (t->state != 6) {
        return 0;
    }
    Vec02 d;
    // The difference is kept, and a copy of it stored and used up in case 0 (vmove).
    u128 diff = Vu0::Sub(Vu0::Q(t->v140), Vu0::Q(self->v140));
    u128 dv = Vu0::Copy(diff);
    Vu0::Q(d) = dv;
    switch (t->targetMode) {
    case 3:
        if (MaskWorldBitsBySave() & 0x12000) {
            return 1;
        }
        break;
    case 0:
        if (t->targetCurve != 0 && ((Blocker_23A0*)t->targetCurve)->untargetable != 0) {
            return 0;
        }
        if (t->targetPoint != 0 && ((Blocker_23A8*)t->targetPoint)->untargetable != 0) {
            return 0;
        }
        if (Vu0::ToFloat(Vu0::Dot(dv, Vu0::Q(t->m110.r[0]))) > 0.0f) {
            return 1;
        }
        break;
    case 1:
        if (t->targetCurve != 0 && ((Blocker_23A0*)t->targetCurve)->untargetable != 0) {
            return 0;
        }
        if (t->targetPoint != 0 && ((Blocker_23A8*)t->targetPoint)->untargetable != 0) {
            return 0;
        }
        if (Vu0::ToFloat(Vu0::Dot(diff, Vu0::Q(t->m110.r[0]))) < 0.0f) {
            return 1;
        }
        break;
    case 2:
        if (t->subState == 0x10) {
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
    if (self->facingLocked != 0) {
        goto set;
    }
    if (self->fB80 != 0) {
        r = 1;
    } else {
        g = g_player;
        if (g != 0 && g->animSeekValue != 0) {
set:
            r = 1;
        }
    }
    return r;
}


void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);
void* AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);
void GroupAnimationEventObjects(ItemKeeper* self);

void* CreateItemKeeper(void* a0)
{
    void* obj = CreateTypedRecord(0x89, a0, 0, 0x436, -1);
    AppendQueuedCall(g_currentWorld, (void*)GroupAnimationEventObjects, obj, 0, 0);
    return obj;
}

void InitObject(BaseObject* self);

void InitItemKeeper(ItemKeeper* self)
{
    InitObject(self);
    self->selectedId = -1;
}

void SetItemKeeperState(ItemKeeper* self, s32 ns);

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

void SetItemKeeperState(ItemKeeper* self, s32 ns);
void CopyMemory(void* dst, void* src, u32 size);

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



void FindWantedItems(ItemKeeper* a0)
{
    for (s32 i = 0; i < a0->owned.wantedCount; i++) {
        Agent* r = (Agent*)FindFirstObjectByIdMode4(g_currentWorld, a0->owned.wanted[i], a0);
        if (r != 0) {
            s32 n = a0->owned.count;
            if ((u32)n < 16) {
                a0->owned.found[n] = r;
                a0->owned.count = n + 1;
                r->roster = a0;
            }
        }
    }
    for (s32 i = 0; i < a0->listed.wantedCount; i++) {
        Agent* r = (Agent*)FindFirstObjectByIdMode4(g_currentWorld, a0->listed.wanted[i], a0);
        if (r != 0) {
            s32 n = a0->listed.count;
            if ((u32)n < 16) {
                a0->listed.found[n] = r;
                a0->listed.count = n + 1;
                            }
        }
    }
}

// The 48-byte record CreateRecord2505C0 makes for a group of StateResetObject objects: the keeper at +0x2C.
struct ItemTimeoutGroup {
    u8 pad0[0x2C];
    void* keeper;           // 0x2C
};
// What GatherAnimationEventObjects hands back for one agent: the objects and their count.
struct GatheredObjects {
    s32 count;
    StateResetObject** items;
};

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateZeroedBackMemory(s32 size);
void GatherAnimationEventObjects(Animation* self, BaseObject* ctx, s32* outCount, BaseObject*** outArr);
void* CreateRecord2505C0(void);
void AppendToSmallList(StateResetGroup* self, StateResetObject* value);

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
        if (agent->mainClip != 0) {
            GatherAnimationEventObjects((Animation*)agent->mainClip, agent, &arr[i].count, (BaseObject***)&arr[i].items);
        }
    }
    for (i = 0; i < self->owned.count; i++) {
        GatheredObjects* e = &arr[i];
        for (j = 0; j < e->count; j++) {
            StateResetObject* node = e->items[j];
            if (node->group == 0) {
                node->group = CreateRecord2505C0();
                ((ItemTimeoutGroup*)node->group)->keeper = self;
                AppendToSmallList((StateResetGroup*)node->group, node);
                if (node->id2E0 != -1) {
                    for (k = i + 1; k < self->owned.count; k++) {
                        GatheredObjects* e2 = &arr[k];
                        for (m = 0; m < e2->count; m++) {
                            StateResetObject* item = e2->items[m];
                            if (item->id2E0 == node->id2E0) {
                                item->group = node->group;
                                AppendToSmallList((StateResetGroup*)node->group, item);
                            }
                        }
                    }
                }
            }
        }
    }
    PopBackMemoryMark();
}

void* AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);
void UpdateItemKeeper(ItemKeeper* self);


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
        AppendQueuedCall((World*)owner, (void*)(void (*)(void*))UpdateItemKeeper, self, -1, 0);
    }
}

void* GetItemKeeperTarget(ItemKeeper* self)
{
    Agent* item = self->owned.found[0];
    return item->desc08()->m62(item);
}


s32 IsAnyItemKeeperMemberFree(ItemKeeper* self);
s32 ChooseItemKeeperState(ItemKeeper* self);
void SetItemKeeperState(ItemKeeper* self, s32 ns);

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
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);


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

void AddItemKeeperStateTrigger(ItemKeeper* self, StateTrigger* value) { for (s32 i = 0; i < self->triggerCount; i++) if (value == self->triggers[i]) return; s32 i = self->triggerCount; if ((u32)i < 4) { s32 next = i + 1; self->triggers[i] = value; self->triggerCount = next; } }

void SetStateTriggerStateFromMessage(StateTrigger* object, s32 mode);

void SetItemKeeperTriggerStates(ItemKeeper* self, s32 mode)
{
    for (s32 i = 0; i < self->triggerCount; i++) {
        SetStateTriggerStateFromMessage(self->triggers[i], mode);
    }
}


extern f32 g_gameClock[];

f32 RandomFloatInRange(f32 a, f32 b);
struct SoundLevelEntry;
void RemoveSoundLevelAndRecompute(SoundLevelEntry* self);
SoundLevelEntry* PushSoundLevel(s32 kind);
void SetItemKeeperTriggerStates(ItemKeeper* self, s32 a);
void AssignItemKeeperMemberPlaces(ItemKeeper* self);

void SetItemKeeperState(ItemKeeper* self, s32 ns)
{
    s32 i;
    if (self->state == ns)
        return;
    switch (self->state) {
    case 2:
        RemoveSoundLevelAndRecompute((SoundLevelEntry*)self->soundLevel);
        i = 0;
        self->soundLevel = 0;
        if (self->owned.count > 0) {
            Agent** p = self->owned.found;
            do {
                Agent* it = *p;
                f32 t = g_gameClock[1];
                i++;
                f32 r = RandomFloatInRange(D_00274D18[0], D_00274D18[1]);
                it->state8Deadline = g_gameClock[1] + r;
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
                (*p)->state6Deadline = g_gameClock[1] + r;
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
        AssignItemKeeperMemberPlaces(self);
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

void GetObjectWorldPosition(BaseObject* self, Vec02* out);
void GetObjectWorldRotation(BaseObject* self, Mat02* out);
void ComputePolarOffset(Vec3* out, f32 angle, f32 scale, f32 z);

static inline s32 MinOfCounts(s32 a, s32 b)
{
    return a < b ? a : b;
}

// Places the owned members: each of the first ones on the listed object nearest the target
// (taken once, in a zeroed back-memory array), with its heading; the rest at random around the
// target, on a ring whose radius grows with their count.
void AssignItemKeeperMemberPlaces(ItemKeeper* self)
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
        GetObjectWorldPosition(m, &member->placePosition);
        GetObjectWorldRotation(m, &rot);
        member->placeHeading = ArctangentOfRatio(rot.r[0].y, rot.r[0].x);
    }
    PopBackMemoryMark();
    if (i != self->owned.count) {
        f32 cnt = (f32)self->owned.count;
        f32 radius = cnt * g_itemKeeperMemberSpacing[0] * 0.15915494f;
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
            f32 r = RandomFloatInRange(g_itemKeeperPlaceAngleJitter[0], g_itemKeeperPlaceAngleJitter[1]);
            f32 ang = WrapAngle(ang0 + r * step);
            f32 r2 = RandomFloatInRange(g_itemKeeperPlaceRadiusScale.c[0], g_itemKeeperPlaceRadiusScale.c[1]);
            ComputePolarOffset((Vec3*)&offset, ang, r2 * radius, 0.0f);
            u128 q = Vu0::Add(Vu0::Q(self->targetPos), Vu0::Q(offset));
            m->placeHeading = ang;
            Vu0::Q(m->placePosition) = q;
            ang0 = WrapAngle(ang0 + step);
        }
    }
}

LINKER_REMNANT(func_001CC3F8);




