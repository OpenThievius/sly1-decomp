// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 296/292, checked 2026-11-07
// NEAR (2026-11-08, vu0w3-e1): the structure is right (the frame, the two calls, three groups of nine stores, the registers of the prologue and the tail); the three rotated rows take other vector registers (retail: the matrix's rows in vf3, vf2, vf1, the results in vf5, vf6, vf3) and the nine stores of the two copies are scheduled all before the first call, where retail's last one fills its delay slot. Tried RotateUntied and RotateRows with the rows loaded in both orders, the copies as initialisers or assignments, and MulRotation (placed_object.cpp's form).
#include "common.h"
#include "screen_element.h"
#include "switched_collider.h"
#include "path_curve_object.h"
#include "cone_volume.h"
#include "world.h"
#include "masked_collider.h"
#include "object_link.h"
#include "message_body.h"
#include "shapes.h"
#include "game_progress.h"
#include "globals.h"
#include "script_value.h"
#include "fpu.h"
#include "collider.h"
#include "state_walker.h"
#include "asm_func.h"
#include "vu0.h"
#include "path_curve.h"

void CopyObjectData(void* self);

void FinishSwitchedCollider(void* self);

void SetModeWalkerMode(ModeWalker* self, s32 n);

void RemoveFromList(void* a, void* b);

void TransformPointBetweenFrames(void* a0, s32 zero, void* table, void* out);

void ComputeColliderJumpVelocity(f32 t, void* obj, void* a, void* b);

f32 ArctangentOfRatio(f32 a, f32 b);

f32 WrapAngle(f32 a);

void TurnColliderTowardHeading(void* obj);

void SetPlayerState(void* obj, s32 a, s32 b);

void ExtractContactsByPartMode(void* self, void* sub);

void StartMaskedCollider(void* self);

void ResolveObjectLinks(void* self, s32 a, void* table);

s32 CreateStateWalker(void* a0, void* self, s32 b, s32 c);

s32 CreateWeightCurve(s32 a);

void* AllocateFrontMemory(s32 size);

void RemoveFromList(u8* p, void* self);

void AppendToList(u8* p, void* self);

void AppendToList(void* sub, void* self);

void RegisterObject(void* self);

void AppendToList(u8* table, void* self);

void RemoveFromList(List01* list, BaseObject* item);

void UnregisterObject(void* self);

void RemoveFromList(u8* table, void* self);

void InitPathFollower(void* self);

void CapturePathFollowerPose(void);

void HandlePathFollowerNotification(void* self, s32 code, MessageBody* rec);

void InitPlayerFlaggedCollider(void* self);

void AppendToList(List01* list, BaseObject* item);

typedef void (*LaunchFn)(void);

s32 HasSpareCount();

void SetSwitchedColliderEnabled(void* self, s32 value);

void SetPlayerState(void* self, s32 a, s32 b);

void ActivateSwitchedCollider(void* value);

void InitOwnerMessage(void* out, s32 mode, void* owner);

void LaunchPlayerFromModeWalker(void);

extern f32 g_gameTime;

struct LaunchMessage { void* self; s32 val; s32 pad8; LaunchFn fn; };

extern f32 g_gameClock[];

extern f32 g_unitRange[];

void UpdatePathFollower(ModeWalker* self, f32 dt);

void InitOwnerMessage(void* out, s32 mode, Collider* c);

void FreePooledContactChain(void* a, void* head);

void SetScaledPositionSpring(void* o, f32 v);

void SetScaledRotationSpring(void* o, f32 v);

s32 IsPadSelectFlagHeld(void* p);


void StartPathFollower(void* self);

void ResolveObjectLinks(void* self, s32 a1, void* a2);

void AddMatrixAttachment(void* a, s32 b, void* c);

void TransformPointBetweenFrames(void* a, void* b, void* c, void* d);

s32 FindAnimRecord(s32 key);

void SetStateWalkerTarget(void* p, s32 n);

void TeleportStateWalker(void* p, s32 n);

struct ClampHelper
{
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo)
        {
            return lo;
        }
        if (hi < x)
        {
            return hi;
        }
        return x;
    }
};

extern Rgba4 D_002623E0[];

f32 Cosine(f32 x);

void SetObjectTreeRecordValue(ModeWalker* o, u32 c);

void func_00125C90(ModeWalker* o, void* a, void* b);

f32 Cosine(f32 value);

ObjectLink g_modeWalkerLinks[10] = {
    { 0, 0x35D, 0xBB8 }, { 4, 0x363, 0xBC0 }, { 4, 0x364, 0xBC4 }, { 4, 0x60, 0xBCC }, { 4, 0x365, 0xBC8 },
    { 2, 0x161, 0x588 }, { 2, 0x162, 0x58C }, { 2, 0x163, 0x590 }, { 4, 0x160, 0x584 }, { 7, 0x366, 0xC08 }
};
f32 D_00264128 = 0.150000006f;
f32 D_00264130[3] = { 30.0f, 0.0f, 0.5f };
f32 D_0026413C = 0.5f;
f32 D_00264140[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
f32 D_00264150 = 6.0f;
f32 D_00264154 = 3.0f;
Vec02 D_00264160 = { 1.0f, 0.0f, -0.75f, 0.0f };
Vec02 D_00264170 = { 0.699999988f, 0.300000012f, 0.0f, 0.0f };
Vec02 D_00264180 = { -300.0f, 0.0f, 200.0f, 0.0f };
f32 D_00264190 = 150.0f;
f32 D_00264198[3] = { 20.0f, 0.0f, 0.100000001f };
f32 D_002641A4 = 1.5f;
f32 D_002641A8[4] = { 5000.0f, 500.0f, 0.150000006f, 0.0f };
f32 D_002641B8[3] = { 5.0f, 0.0f, 0.100000001f };
f32 D_002641C4 = 3.0f;
f32 D_002641C8[10] = { 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_002641F0[16] = { 24.0f, -24.0f, 0.0f, 0.0f, 24.0f, 24.0f, 0.0f, 0.0f, -24.0f, -24.0f, 0.0f, 0.0f, -24.0f, 24.0f, 0.0f, 0.0f };
ObjectLink D_00264230[2] = { { 0, 0x36B, 0x6C4 }, { 0x20, 0x36C, 0x6EC } };
f32 D_00264248 = 2.5f;
f32 D_0026424C = 300.0f;
f32 D_00264250[4] = { 20.0f, 0.0f, 0.5f, 0.0f };


void RecomputePathFollowerFrame(PathFollower* self);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void BuildBasisFromXAndZHint(void* a, void* b, void* c);
typedef void (*PathSampleFn)(PathCurve* self, f32 t, Vec02* pos, Vec02* dir);

void RecomputeModeWalker(ModeWalker* self)
{
    RecomputePathFollowerFrame(self);
    if (self->f830 != 0 && self->fC08 != 0) {
        Vec02 pos;
        Vec02 dir;
        Mat02 m1;
        Mat02 m2;
        PathCurve* curve = self->f830->curve;
        PathSampleFn fn = (PathSampleFn)curve->vt->m01;
        if (fn) {
            fn(curve, self->f838, &pos, &dir);
        }
        MultiplyMatrices3x3(&self->m1A0, &self->fC08->m1A0, &m1);
        BuildBasisFromXAndZHint(&dir, (void*)&g_unitZVector, &m2);
        u128 r2 = Vu0::Q(m1.r[2]);
        u128 r1 = Vu0::Q(m1.r[1]);
        u128 r0 = Vu0::Q(m1.r[0]);
        Vu0::Q(m2.r[0]) = Vu0::RotateRows(r0, r1, r2, Vu0::Q(m2.r[0]));
        Vu0::Q(m2.r[1]) = Vu0::RotateRows(r0, r1, r2, Vu0::Q(m2.r[1]));
        Vu0::Q(m2.r[2]) = Vu0::RotateRows(r0, r1, r2, Vu0::Q(m2.r[2]));
        Mat02 t1 = m2;
        Mat02 t2 = m2;
        self->fC08->desc02()->m1D(self->fC08, &pos);
        self->fC08->desc02()->m1E(self->fC08, &m2);
    }
}

