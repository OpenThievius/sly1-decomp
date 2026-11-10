// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "vu0.h"
#include "list_iter.h"
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
#include "transform_object.h"
#include "ramp_profile.h"
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

// What func_00181BC8 builds on its stack: an owner message (InitOwnerMessage) whose function
// the player calls (slot 76), then the two words it tells its listeners (kind 0x17).
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

// The file's .data, 0x2640B0 to 0x264260, in retail's order. GCC puts an object of eight bytes
// or more on 8, so the words after D_00264128, D_00264154 and D_00264190 are padding: the three
// vectors at 0x264160 are on 16 (Vec02; func_00128018 loads D_00264180 with lqc2).
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

void RegisterListedKeepObject(ListedKeepObject* self)
{
    RegisterObject(self);
    AppendToList(&self->world->list1C9C, self);
}

void UnregisterListedKeepObject(ListedKeepObject* self)
{
    UnregisterObject(self);
    RemoveFromList(&self->world->list1C9C, self);
}

void CopyListedKeepObject(ListedKeepObject* self)
{
    PathCurveKeptBits saved = self->keep;
    CopyObjectData(self);
    self->keep = saved;
}

void InitModeWalkerObject(ModeWalker* self)
{
    InitPathFollower(self);
    self->fBF4 = -10.0f;
}

void StartModeWalkerObject(ModeWalker* self)
{
    StartPathFollower(self);
    ResolveObjectLinks(self, 0xA, g_modeWalkerLinks);
    self->fBBC = (StateWalker*)CreateStateWalker(self->fBB8, self, -1, 0);
    AddMatrixAttachment(self->fBCC, 5, &self->fBD0);
    ((u8*)self->fBD0)[0x10] = 9;
    ((u8*)self->fBD0)[0x11] = 9;
    ((PlacedObject*)self->fBCC)->desc02()->m2B((PlacedObject*)self->fBCC);
    TransformPointBetweenFrames(0, self->fBC0, (u8*)self->fBCC + 0x140, (u8*)self + 0xBE0);
    SetModeWalkerMode(self, 1);
    self->f864 = 3.4028234663852886e+38f;
    T217D_BF0* base = &D_00270650;
    ((T217D_Float*)&base->f288)->v = 0.0f;
    base->icon = FindAnimRecord(0x36A);
}

// A pad record's stick and buttons (PadRecord's 0x40, 0x44, 0xA8 and 0xAA: pad_record.h's ranges
// clash with this file's view of g_unitRange).
struct PadStick {
    u8 pad00[0x40];
    f32 x;                  // 0x40
    f32 y;                  // 0x44
    u8 pad48[0xA8 - 0x48];
    u16 held;               // 0xA8: func_00181078 tests 0x80
    u16 pressed;            // 0xAA: func_00181078 tests and clears 0x40
};

extern T217D_BF0 D_00270650;
extern u8 D_00262D38[];
extern u8 D_002708C0[];
void ControlPathFollower(PathFollower* self, PadStick* pad, f32 dt);
void GetStateWalkerCurrentKey(void* h, s32* out);
void GetStateWalkerTargetKey(void* h, s32* out);
void ClearPadPressedBits(PadStick* pad, s32 mask);
void UnprojectCameraPoint(void* camera, void* a, Vec02* out);
void BuildBasisFromXAndZHint(void* a, void* b, void* c);
void TransformRotationBetweenFrames(void* from, void* to, Mat02* in, Mat02* out);
void TransformDirectionBetweenFrames(void* from, void* to, Vec02* in, void* out);
void ApproachRotationWithRamp(f32 dt, void* rot, void* target, void* ramp, void* outRot, void* outSpin);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, Vec02* axis);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
void ClearRootTries(void* self);
void func_00181ED0(T217D_BF0* self, PadStick* pad);
typedef void (*FrameFn)(void* self, Mat02* m);

// The rotation's weight is a Scalar passed straight to MulX (its expand-time slot, a scalar's
// memory, stored after the product as retail's is), and m2 and the axis are declared after
// that statement: the slot is freed there and the axis takes it (retail's 0x50, between d and m2).
void func_00181078(ModeWalker* self, PadStick* pad, f32 dt)
{
    s32 cur;
    s32 target;
    Mat02 m;
    Vec02 pos;
    Vec02 d;
    f32 angle;
    ControlPathFollower(self, pad, dt);
    GetStateWalkerCurrentKey(self->fBBC, &cur);
    GetStateWalkerTargetKey(self->fBBC, &target);
    switch (self->fBB0) {
    case 1:
        if ((pad->held & 0x80) != 0) {
            SetStateWalkerTarget(self->fBBC, 0x360);
        } else {
            SetStateWalkerTarget(self->fBBC, 0x35F);
        }
        break;
    case 2:
        if (cur == 0x35F) {
            self->desc05()->m50(self);
        } else {
            if ((pad->pressed & 0x40) != 0) {
                ClearPadPressedBits(pad, 0x40);
                self->fBFC = g_gameTime;
            }
            if (self->fC00 != 0 && g_gameTime - self->fBFC < D_00264128) {
                self->desc05()->m50(self);
                TeleportStateWalker(self->fBBC, 0x35F);
                GetStateWalkerCurrentKey(self->fBBC, &cur);
                GetStateWalkerTargetKey(self->fBBC, &target);
            }
        }
        break;
    }
    if ((u32)(cur - 0x35F) < 2) {
        if (target == -1 || target == 0x35F || target == 0x360) {
            if (self->fBB0 == 2) {
                pad = (PadStick*)D_00262D38;
            }
            func_00181ED0(&D_00270650, pad);
            Vu0::Q(m.r[2]) = Vu0::Q(self->m110.r[2]);
            u128 n = Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(m.r[2]), Vu0::Q(((Vec02*)((u8*)g_camera + 0x80))[0])), *(u128*)&self->m110.r[1]);
            Vu0::Q(m.r[1]) = n;
            Vu0::Q(m.r[0]) = Vu0::Cross(n, Vu0::Q(m.r[2]));
            TransformRotationBetweenFrames(0, ((PlacedObject*)self->fBC4)->parent, &m, &m);
            ApproachRotationWithRamp(dt, (u8*)self->fBC4 + 0xD0, &m, D_00264130, &m, 0);
            (*(FrameFn**)self->fBC4)[34](self->fBC4, &m);
            UnprojectCameraPoint(g_camera, D_002708C0, &pos);
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(((PlacedObject*)self->fBC0)->v140));
            BuildBasisFromXAndZHint(&d, (void*)&g_unitZVector, &m);
            TransformRotationBetweenFrames(0, ((PlacedObject*)self->fBC0)->parent, &m, &m);
            (*(FrameFn**)self->fBC0)[34](self->fBC0, &m);
            u128 v = Vu0::Q(self->vBE0);
            u128 rot = Vu0::RotateUntied(m, v);
            Vu0::Q(d) = Vu0::MulX(Vu0::Sub(rot, v), Vu0::ScalarAt(D_0026413C));
            Mat02 m2;
            Vec02 k;
            TransformDirectionBetweenFrames(((PlacedObject*)self->fBC0)->parent, ((PlacedObject*)self->fBCC)->parent, &d, (u8*)self->fBD0 + 0x20);
            MultiplyMatrices3x3((Mat02*)((u8*)self->fBC0 + 0x1A0), &m, &m2);
            TransformRotationBetweenFrames(((PlacedObject*)self->fBC0)->parent, ((PlacedObject*)self->fBCC)->parent, &m2, &m2);
            MatrixToAxisAngle(&m2, &angle, &k);
            BuildAxisAngleMatrix(&k, (Mat02*)((u8*)self->fBD0 + 0x40), D_0026413C * angle);
            ClearRootTries(self);
        }
    }
}

void UpdateModeWalkerObject(ModeWalker* self, f32 dt)
{
    s32 buf[4];
    UpdatePathFollower(self, dt);
    if (self->fC04 != 0) {
        Contact03* n = (Contact03*)self->fC04;
        do {
            s32 j = (n->end[0].body != self);
            Collider* c = n->end[1 - j].part;
            while (c != 0 && c->f4E0 == 0) c = (Collider*)c->parent;
            if (c != 0 && (c->f4E0 == 1 || c->f4E0 == 4)) {
                InitOwnerMessage(buf, 0, c);
                while (c != 0) {
                    if (((s32 (*)(Collider*, Contact03*, void*))c->desc03()->m47)(c, n, buf) != 0) break;
                    c = (Collider*)c->parent;
                }
                ((Desc05*)self->desc)->m4C(self, buf);
            }
            n = n->next;
        } while (n != 0);
        FreePooledContactChain(self->world, self->fC04);
        self->fC04 = 0;
    }
    f32 t = g_gameClock[1] - self->fBF4;
    f32 v = D_00264140[0] + t * (D_00264140[1] + t * D_00264140[2]);
    f32* r = g_unitRange;
    f32 lo = g_unitRange[0];
    f32 hi = r[1];
    f32 x;
    if (v < lo) x = lo;
    else if (hi < v) x = hi;
    else x = v;
    SetScaledPositionSpring(self->fBCC, x * D_00264150);
    SetScaledRotationSpring(self->fBCC, x * D_00264154);
    if (self->fBF0 != 0 && self->fBB0 != 2 && g_gameClock[1] - self->fBF8 > 2.0f) self->fBF0 = 0;
}

void RecomputePathFollowerFrame(PathFollower* self);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void BuildBasisFromXAndZHint(void* a, void* b, void* c);
typedef void (*PathSampleFn)(PathCurve* self, f32 t, Vec02* pos, Vec02* dir);

// A matrix set from three rows passed by reference as the signed 128-bit type: the unsigned rows
// the caller passes are each copied to a temporary of their own, a scalar's memory, which retail's
// frame keeps after the matrix locals (docs/TOOLCHAIN.md, "Rows bound by reference as s128").
static inline void SetMatrixRows(Mat02& m, const s128& a, const s128& b, const s128& c)
{
    Vu0::Q(m.r[0]) = (u128)a;
    Vu0::Q(m.r[1]) = (u128)b;
    Vu0::Q(m.r[2]) = (u128)c;
}

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
        u128 r0 = Vu0::Q(m1.r[0]);
        u128 r1 = Vu0::Q(m1.r[1]);
        u128 r2 = Vu0::Q(m1.r[2]);
        u128 x = Vu0::RotateRows(r0, r1, r2, Vu0::Q(m2.r[0]));
        u128 y = Vu0::RotateRows(r0, r1, r2, Vu0::Q(m2.r[1]));
        u128 z = Vu0::RotateRows(r0, r1, r2, Vu0::Q(m2.r[2]));
        Mat02 rot;
        SetMatrixRows(rot, x, y, z);
        m2 = rot;
        self->fC08->desc02()->m1D(self->fC08, &pos);
        self->fC08->desc02()->m1E(self->fC08, &m2);
    }
}

void HandlePathFollowerActivation(void* self, s32 active);

void HandleModeWalkerActivation(ModeWalker* self, s32 active)
{
    HandlePathFollowerActivation(self, active);
    if (active) {
        T217D_BF0* e = &D_00270650;
        e->vt->m16(e, 2);
        Vu0::Q(e->aim) = Vu0::FromFloats(0.0f, 0.0f, 2000.0f);
    } else {
        D_00270650.vt->m16(&D_00270650, 0);
        self->fBF0 = 0;
    }
}

void ApplyModeWalkerTint(ModeWalker* o, void* a, void* b)
{
    Rgba4 c;
    u8 from[4];
    *(u32*)from = 0x800000A0;
    if (o->fBF0) {
        f32 t;
        if (o->fBB0 != 2) {
            t = (g_gameClock[1] - o->fBF8) * 0.5f;
        } else {
            t = 0.0f;
        }
        f32 s = Cosine((g_gameClock[1] - o->fBF4) * 10.0f);
        f32 p = D_00264160.x + t * (D_00264160.y + t * D_00264160.z);
        f32 x = ClampHelper::Of(p, g_unitRange[0], g_unitRange[1]);
        f32 q = D_00264170.x + s * (D_00264170.y + s * D_00264170.z);
        f32 y = ClampHelper::Of(q, g_unitRange[0], g_unitRange[1]);
        f32 w = x * y;
        f32 u = 1.0f - w;
        c.r = (u8)(u * D_002623E0[0].r + w * from[0]);
        c.g = (u8)(u * D_002623E0[0].g + w * from[1]);
        c.b = (u8)(u * D_002623E0[0].b + w * from[2]);
        c.a = D_002623E0[0].a;
    } else {
        c = D_002623E0[0];
    }
    SetObjectTreeRecordValue(o, *(u32*)&c);
    func_00125C90(o, a, b);
}

void CaptureModeWalkerTarget(ModeWalker* self, void* outv)
{
    Vec02* out = (Vec02*)((u8*)outv + 0x10);
    CapturePathFollowerPose();
    *out = ((PlacedObject*)self->fBC0)->v140;
}

s32 IsModeWalkerRequestBlocked(ModeWalker* self)
{
    if (self->fBB0 != 1 || self->fBF0 != 0 || IsPadSelectFlagHeld(self->world) != 0) return 1;
    return 0;
}

s32 HasModeWalkerAcceptedRequest(ModeWalker* p) { return p->fBF0 != 0; }

void FinishModeWalker(ModeWalker* self)
{
    FinishSwitchedCollider(self);
    SetModeWalkerMode(self, 1);
}

void LaunchPlayerFromModeWalker(void* unused, void* obj_)
{
    Player* obj = (Player*)obj_;
    Vec02 first;
    Vec02 second;

    TransformPointBetweenFrames(unused, 0, &D_00264180, &first);
    ComputeColliderJumpVelocity(D_00264190, obj, &first, &second);
    obj->desc02()->m20(obj, &second);
    f32 r = ArctangentOfRatio(second.y, second.x);
    obj->f638 = WrapAngle(r + 3.1415927f);
    TurnColliderTowardHeading(obj);
    SetPlayerState(obj, 4, 0x2B);
}

s32 AcceptModeWalkerRequest(ModeWalker* self, s32* arg)
{
    LaunchMessage loc;
    s32 r;
    Player* g;
    Player* gp;

    if (self->desc05()->m4B(self, arg[0])) {
        return 0;
    }
    if (HasSpareCount()) {
        self->fBF0 = 1;
    }
    self->fBF4 = g_gameTime;
    r = HasSpareCount();
    if (r == 0) {
        g = g_player;
        if (g != 0) {
            goto then_block;
        }
    }
    SetModeWalkerMode(self, 2);
    goto tail;
then_block:
    g_player->desc->m02(g_player);
    g_player->desc02()->m1F(g_player, (PlacedObject*)self->fBC8);
    ((BaseObject*)self->fBC8)->desc->m03((BaseObject*)self->fBC8);
    SetSwitchedColliderEnabled((void*)g_player, 1);
    SetPlayerState((void*)g_player, 2, 2);
    ActivateSwitchedCollider((void*)g_player);
    SetModeWalkerMode(self, 3);
    InitOwnerMessage(&loc, 0, self);
    gp = g_player;
    gp = g_player;
    loc.fn = LaunchPlayerFromModeWalker;
    (void)gp->desc05()->m4C(gp, &loc);
tail:
    loc.self = self;
    loc.val = arg[1];
    self->desc->m0E(self, 0x17, &loc);
    return 1;
}

void HandleModeWalkerNotification(ModeWalker* self, s32 code, MessageBody* rec)
{
    if (code == 0x13) {
        StateWalker* sub = self->fBBC;
        s32 key = rec->sourceId;
        if (sub != 0 && key == (s32)sub->player) {
            s32 kind = rec->code;
            if (kind != 0x15E) {
                if (kind == 0x15F) {
                    self->fC00 = 0;
                }
            } else {
                self->fC00 = 1;
            }
        }
    }
    HandlePathFollowerNotification(self, code, rec);
}

void ExtractModeWalkerContacts(ModeWalker* self)
{
    ExtractContactsByPartMode(self, (u8*)self + 0xC04);
}

void SetModeWalkerMode(ModeWalker* self, s32 mode)
{
    s32 old;

    if (mode == self->fBB0) {
        return;
    }
    old = self->fBB0;
    if (old < 4) {
        if (old >= 2) {
            self->fBF8 = g_gameClock[1];
        }
    }
    switch (mode) {
    case 0:
        SetStateWalkerTarget(self->fBBC, 0x35E);
        break;
    case 1:
        SetStateWalkerTarget(self->fBBC, 0x35F);
        break;
    case 2:
        TeleportStateWalker(self->fBBC, 0x361);
        self->fBF8 = 3.40282347e+38f;
        break;
    case 3:
        TeleportStateWalker(self->fBBC, 0x362);
        self->fBF8 = 3.40282347e+38f;
        break;
    }
    if (mode == 0) {
        self->f580 = 0;
    } else if (mode < 0) {
        self->f580 = 1;
    } else if (mode >= 4) {
        self->f580 = 1;
    } else if (mode >= 2) {
        self->f580 = 0;
    } else {
        self->f580 = 1;
    }
    self->fBB0 = mode;
    self->fBB4 = g_gameClock[1];
}

extern u8 g_class75List[];
void GetObjectWorldPosition(void* obj, Vec02* out);
void ProjectPointToCamera(Camera* cam, void* pos, Vec02* out);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, f32* p, f32* out);


void func_00181ED0(T217D_BF0* self, PadStick* pad)
{
    Vec02 p;
    Vec02 best;
    f32 bestScore = 3.40282347e+38f;
    Vu0::Q(best) = Vu0::FromFloats(0.0f, 0.0f, 2000.0f);
    Class75Object* chosen = 0;
    for (Class75Object* o = *(Class75Object**)g_class75List; o != 0; o = *(Class75Object**)&o->link) {
        GetObjectWorldPosition(o, &p);
        ProjectPointToCamera(g_camera, &p, &p);
        if (p.z < 100.0f) {
            continue;
        }
        f32 r = o->scale / (p.z * *(f32*)((u8*)g_camera + 0x1F0));
        u128 d = Vu0::Sub(Vu0::Q(p), Vu0::Q(self->aim));
        f32 eps = 0.0001f;
        f32 score = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(d, d))) - r;
        score = eps >? score;
        if (o == self->target) {
            score *= 0.5f;
        }
        if (score < bestScore || (score == bestScore && p.z < best.z)) {
            Vu0::Q(best) = Vu0::Q(p);
            bestScore = score;
            chosen = o;
        }
    }
    self->rateX = ApproachValueWithRamp(self->rateX, pad->x, g_gameClock[2], D_00264198, 0);
    f32 y = pad->y;
    if (g_saveData->f19EC & 0x400) {
        y = -y;
    }
    self->rateY = ApproachValueWithRamp(self->rateY, y, g_gameClock[2], D_00264198, 0);
    self->aim[0] = ClampHelper::Of(self->aim[0] + g_gameClock[2] * self->rateX * D_002641A4, -1.0f, 1.0f);
    self->aim[1] = ClampHelper::Of(self->aim[1] - g_gameClock[2] * self->rateY * D_002641A4, -1.0f, 1.0f);
    f32 far = 1000.0f;
    self->aim[2] = ApproachValueWithRamp(self->aim[2], far >? best.z, g_gameClock[2], D_002641A8, 0);
    self->target = chosen;
}

struct SpritePackets {
    s32 count;
    s32 data;
};

struct SpriteIcon {
    u8 pad00[0x1C];
    SpritePackets* packets;     // 0x1C
};

extern f32 g_frameStep;
s32 AreMenusAndFadeClear(void);
void AppendPacketQuadwords(PacketWriter* w, s32 count, s32 data);
void BeginGifTag(PacketWriter* b, s32 a, s32 c, u64 d);
void AddGifRegisterWrite(PacketWriter* b, s32 reg, u64 v);
void AddGifStEntry(PacketWriter* b, f32 x, f32 y, f32 z);
void AddGifRgbaEntry(PacketWriter* b, u32 c);
void AddGifXyzfEntry(PacketWriter* b, s32 x, s32 y, s32 z, s32 f);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);

void DrawSpinningSpriteElement(T217D_BF0* self)
{
    Rgba4 col;
    Mat02 m;
    Vec02 p;
    if (self->icon == 0) {
        return;
    }
    f32 target = AreMenusAndFadeClear() != 0 ? 1.0f : 0.0f;
    if (g_camera->f224 != 0) {
        self->f288 = target;
    } else {
        self->f288 = ApproachValueWithRamp(self->f288, target, g_frameStep, D_002641B8, 0);
    }
    if (self->f288 == 0.0f) {
        return;
    }
    AppendPacketQuadwords(&g_gsPacketWriter, ((SpriteIcon*)self->icon)->packets->count - 1, ((SpriteIcon*)self->icon)->packets->data + 0x10);
    BeginGifTag(&g_gsPacketWriter, 0, 1, 0xE);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x47, 0x30000);
    *(u32*)&col = 0x80FFFFFF;
    BuildAxisAngleMatrix(&g_unitZVector, &m, g_gameTime * D_002641C4);
    BeginGifTag(&g_gsPacketWriter, 0x5C, 3, 0x412);
    col.a = (u8)(s32)(self->f288 * (f32)col.a);
    for (u32 i = 0; i < 4; i++) {
        f32 sx = self->aim[0] * 320.0f + 320.0f;
        f32 sy = self->aim[1] * -246.400009f + 246.400009f;
        Vu0::Q(p) = Vu0::Rotate(m, Vu0::Q(D_002641F0[i * 4]));
        p.x = p.x + sx;
        p.y = p.y + sy;
        AddGifStEntry(&g_gsPacketWriter, D_002641C8[i * 2], D_002641C8[i * 2 + 1], 1.0f);
        AddGifRgbaEntry(&g_gsPacketWriter, *(u32*)&col);
        f32 left = 1728.0f;
        s32 px = (s32)((p.x + left) * 16.0f);
        s32 py = (s32)((p.y * 0.45454547f + 1936.0f) * 16.0f);
        AddGifXyzfEntry(&g_gsPacketWriter, px, py, 0, 0);
    }
}

void InitC24Object(C24* self)
{
    InitPlayerFlaggedCollider(self);
    self->f6DC = 10.0f;
    self->f6E0 = 1.0f;
    self->f6D8 = 3000.0f;
    self->f6CC = 1000.0f;
    self->f6D0 = 0;
    self->f6D4 = 0.5f;
}

void StartC24Object(C24* self)
{
    StartMaskedCollider(self);
    ResolveObjectLinks(self, 2, D_00264230);
    self->x6C8 = (StateWalker*)CreateStateWalker(self->x6C4, self, 0x36E, 0);
    Alloc24* n = (Alloc24*)CreateWeightCurve(0);
    self->x6E8 = n;
    n->field8 = 0;
    self->x6E8->field_c = AllocateFrontMemory(0xC00);
}

void UpdateMaskedCollider(C24* self, f32 dt);
void* GetActiveSwitchedCollider(void);
s32 IsObjectOfKind(void* obj, s32 kind);
void GetStateWalkerTargetKey(void* h, s32* out);
void GetStateWalkerCurrentKey(void* h, s32* out);
void SendEmptyMessage(void* p);
void TriggerScriptEvent(void* obj, s32 a, s32 b, s32 c);
void ClearRootTries(void* self);
void SetStateWalkerTarget(void* p, s32 n);

void UpdateC24Object(C24* self, f32 dt)
{
    SwitchedCollider* target;
    u8 msg[0x10];
    s32 key;
    UpdateMaskedCollider(self, dt);
    if (self->x6E8 != 0) {
        target = (SwitchedCollider*)GetActiveSwitchedCollider();
        if (IsObjectOfKind(target, 0x16) != 0) {
            target = *(SwitchedCollider**)((u8*)target + 0x620);
        }
        f32 v = self->f6E4 + dt * self->f6E0;
        f32 hi = self->f6DC;
        if (v < 0.0f) {
            v = 0.0f;
        } else if (hi < v) {
            v = hi;
        }
        self->f6E4 = v;
        GetStateWalkerTargetKey(self->x6C8, &key);
        if (key == -1) {
            GetStateWalkerCurrentKey(self->x6C8, &key);
        }
        s32 hold = 0;
        if (key == 0x36F && target != 0 &&
            Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(target->v140)))) < D_0026424C) {
            hold = 1;
        } else if (self->f6E4 >= self->f6DC) {
            hold = 1;
        }
        if (hold) {
            InitOwnerMessage(msg, ((g_saveData->f19D8 << 8) | g_saveData->f19DC) == 0x505 ? 2 : 0, self);
            target->desc05()->m4C(target, msg);
            SendEmptyMessage(self->x6EC);
            self->desc->m03(self);
            TriggerScriptEvent(self, 2, 0, 0);
            return;
        }
        if (self->x6C8 != 0 && self->f6DC - self->f6E4 < D_00264248) {
            SetStateWalkerTarget(self->x6C8, 0x36F);
        }
    }
    ClearRootTries(self);
}

typedef void (*WeightCurveFn)(void* curve, void* owner, s32 a2, f32* out0, f32* out1, f32 x, f32 y);
typedef void (*CurveSampleDirFn)(PathCurve* self, f32 len, Vec02* pos, Vec02* dir);
typedef void (*ChildStepFn)(BaseObject* self, f32 dt, s32 flag);
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
        f32 o0, o1;
        ((WeightCurveFn)(*(void***)self->x6E8)[0])(self->x6E8, self, 0, &o0, &o1, self->f6E4, self->f6E0);
        PathCurve* curve = ((PathCurveObject*)self->x6C0)->curve;
        CurveSampleDirFn sample = (CurveSampleDirFn)curve->vt->m02;
        if (sample) {
            sample(curve, o0, &pos, &dir);
        }
        u128 w = Vu0::FromFloatAt(o1);
        Vu0::Q(vel) = Vu0::MulX(Vu0::Q(dir), w);
        void* o = *(void**)((u8*)self->x6C0 + 0x18);
        Vu0::Set(t, w);
        func_00127E60(o, 0, &pos, 0, &vel, 0);
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
            ((ChildStepFn)n->desc->m1B)(n, dt, 1);
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

struct CurveEntry {
    f32 a;                  // 0x00
    f32 b;                  // 0x04
    s32 k;                  // 0x08
    f32 c;                  // 0x0C
    s32 k2;                 // 0x10
    f32 d;                  // 0x14
};

typedef void (*CurveSampleFn)(PathCurve* self, s32 zero, Vec02* out, f32 t);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 bytes);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, RampProfile* p, f32* out);

void func_00182948(C24* self, PathCurveObject* path, f32 speed)
{
    Vec02 p0;
    Vec02 p1;
    f32 out;
    s32 i;
    PushBackMemoryMark();
    self->x6C0 = path;
    self->f6DC = speed;
    PathCurve* curve = path->curve;
    f32 total = curve->vt->m08(curve);
    s32 n = curve->count;
    CurveEntry* entries = (CurveEntry*)self->x6E8->field_c;
    self->x6E8->field8 = n;
    f32* lens = (f32*)AllocateBackMemory(n << 2);
    for (i = 0; i < n; i++) {
        if (curve->vt->m02 != 0) {
            ((CurveSampleFn)curve->vt->m02)(curve, 0, &p0, curve->lengths[i] - 0.5f);
            if (curve->vt->m02 != 0) {
                ((CurveSampleFn)curve->vt->m02)(curve, 0, &p1, curve->lengths[i] + 0.5f);
            }
        }
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(p0), Vu0::Q(p1))));
        lens[i] = Fpu::Sqrt(self->f6D8 / len);
        ApproachValueWithRamp(curve->lengths[i], total + 100.0f, 0.0f, (RampProfile*)&self->f6CC, &out);
        lens[i] = out <? lens[i];
    }
    CurveEntry* e;
    for (i = 0; i < n; i++) {
        e = &entries[i];
        e->b = curve->lengths[i];
        if (i == 0) {
            e->a = 0.0f;
        } else {
            e->a = e[-1].a + (e->b - e[-1].b) * 2.0f / (lens[i] + lens[i - 1]);
        }
        e->k = 4;
        e->c = lens[i];
    }
    f32 scale = speed / e->a;
    for (i = 0; i < n; i++) {
        e = &entries[i];
        e->a = e->a * scale;
        e->c = e->c / scale;
    }
    for (i = 0; i < n; i++) {
        e = &entries[i];
        e->k2 = 4;
        e->d = e->c;
    }
    self->f6E4 = 0.0f;
    TeleportStateWalker(self->x6C8, 0x36E);
    PopBackMemoryMark();
}
