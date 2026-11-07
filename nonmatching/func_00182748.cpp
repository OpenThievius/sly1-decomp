// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 483/512 (94.3%), checked 2026-11-07
// NEAR (2026-11-08, vu0w3-e1): same size, same code: 4 words of offsets and 2 schedule swaps. The Scalar's slot is at 0x70 and the weight curve's two output floats at 0x80 in retail; here the floats come first (declared before, as the call needs them) and the slot after at 0x80 (toy compiles: a Scalar's slot is freed after its statement and a later local reuses it, so no declaration order gives retail's). Also retail loads 0x6C0(self) after the vmulx, and sets a1 = 1 after the f12 move.
#include "common.h"
#include "vu0.h"
#include "list_iter.h"
#include "path_curve.h"
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


typedef void (*WeightCurveFn)(void* curve, void* owner, s32 a2, f32* out0, f32* out1, f32 x, f32 y);
typedef void (*CurveSampleFn)(PathCurve* self, f32 len, Vec02* pos, Vec02* dir);
typedef void (*ChildStepFn)(BaseObject* self, s32 flag, f32 dt);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void BuildBasisFromXAndZHint(void* a, void* b, void* c);
void ApproachRotationWithRamp(f32 dt, void* rot, void* target, void* ramp, void* outRot, void* outSpin);

struct ScopedListFrame {
    void* list;
    void* cursor;
    s32 next_off;
    ScopedListFrame* prev;
    ScopedListFrame(List01* l)
    {
        list = l;
        cursor = l;
        next_off = l->offset;
        prev = (ScopedListFrame*)g_activeListFrames;
        g_activeListFrames = (ListFrame*)this;
    }
    ~ScopedListFrame() { g_activeListFrames = (ListFrame*)prev; }
};

void MoveC24Object(C24* self, s32 a1, f32 dt)
{
    if (self->x6E8 != 0) {
        Vec02 pos;
        Vec02 dir;
        Vec02 vel;
        Vec02 t;
        Mat02 basis;
        f32 out[2];
        ((WeightCurveFn)(*(void***)self->x6E8)[0])(self->x6E8, self, 0, &out[0], &out[1], self->f6E4, self->f6E0);
        PathCurve* curve = ((PathCurveObject*)self->x6C0)->curve;
        CurveSampleFn sample = (CurveSampleFn)curve->vt->m02;
        if (sample) {
            sample(curve, out[0], &pos, &dir);
        }
        u128 w = Vu0::FromFloatAt(out[1]);
        Vu0::Set(t, w);
        Vu0::Q(vel) = Vu0::MulX(Vu0::Q(dir), w);
        func_00127E60(*(void**)((u8*)self->x6C0 + 0x18), 0, &pos, 0, &vel, 0);
        Vu0::Set(t, Vu0::MulXSum(Vu0::Q(self->gravity), Vu0::Scalar(-1.0f),
                                 Vu0::Sub(Vu0::Q(vel), Vu0::Q(self->v150)), Vu0::Scalar(1.0f / dt)));
        BuildBasisFromXAndZHint(&vel, &t, &basis);
        self->pos = pos;
        self->v150 = vel;
        ApproachRotationWithRamp(dt, &self->rot, &basis, D_00264250, &self->rot, &self->v160);
    }
    ScopedListFrame frame(&self->children);
    void* head = *(void**)((u8*)self + 0x34);
    frame.cursor = (void*)((s32)head + frame.next_off);
    BaseObject* n = (BaseObject*)head;
    while (n != 0) {
        if (n->desc->flags & 1) {
            ((ChildStepFn)n->desc->m1B)(n, 1, dt);
        }
        void* next = *(void**)frame.cursor;
        frame.cursor = (void*)((s32)next + frame.next_off);
        n = (BaseObject*)next;
    }
    if (a1 == 0) {
        void (*fn)(BaseObject*) = self->desc->m12;
        if (fn != 0) {
            fn(self);
        }
    }
}

