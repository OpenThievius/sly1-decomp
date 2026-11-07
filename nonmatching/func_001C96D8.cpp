// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 682/692 (98.6%), checked 2026-11-07
// NEAR: four lines: retail loads the fallback vector (lq v0,0(v0)) before the length test of the normalisation, ours puts it in the branch's delay slot; the rest matches.
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
extern f32 g_gameClock[];
s32 GetAgentRosterState(Agent* self);
s32 HasAgentReachedPathEnd(Agent* self);
s32 IsObjectOfKind(void* node, s32 kind);
void ConvertOffsetToSpherical(void* a, void* b, f32* x, f32* y, s32 flag);
void SetAgentFacingAngles(void* self, f32 x, f32 y);
void func_001C8418(Agent* self, void* p);
void func_0012C9E8(f32 c, void* a, Agent* b, void* d, void* e, void* f, s32 g);
Entry8B* FindEntryByObjectId(void* a, Agent* b);
void CreateAnimationPlayer(void* self, void* a1, s32 a2, void* a3, s32 a4, void* a5, f32 f0, f32 f1);
void AddAnimationPlayerRecordCallback(void* a0, C62* a1);
s32 GetEffectiveObjectId(Agent* a);
Attachment* FindPlayerAttachmentByOwner(AnimationPlayer* a0, s32 a1);
extern f32 g_frameDt;
s32 HasAnimationDrivenAttachment(Agent* self);
void func_001C7BE8(Agent* self);
void func_00128598(f32 a, f32 b, Agent* self, s32 c, s32 d, f32* e, f32* f, f32* g);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);
void ScheduleItemTimeouts(void* n);
void func_001C8920(Agent* self);
void FaceAgentTowardGoalPoint(Agent* self);
struct StateChangeArgs { s32* oldSlot; s32* stateSlot; };
extern f32 g_gameClock[];
void TriggerScriptEvent(void*, s32, s32, void*);
void ChangeAgentState(Agent* self, s32 mode, s32 value);
void StopAnimationPlayer(AnimationPlayer* p);
f32 RandomFloatInRange(f32 a, f32 b);
void SetStateAndNotify(C62* p, s32 z);
void InitContactPairFlags(void* world, Agent* self);
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
            Vu0::Set(msg.va, Vu0::NormalizeOr(Vu0::Q(ev->push), Vu0::Q(g_unitXVector)));
        }
        ((BaseObject*)self->fB00)->desc->m1B((BaseObject*)self->fB00, &msg);
    }
    ((AgentNotice*)&msg)->self = self;
    ((AgentNotice*)&msg)->obj = ev->obj;
    self->desc->m0E(self, 0x17, &msg);
    return handled;
}
