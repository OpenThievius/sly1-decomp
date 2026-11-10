// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x149398 to 0x14B6A8 (its .rodata from 0x249EA0, its .data from 0x261BF0, its
// .bss from 0x27C008): the camera's controllers (0x149398 to 0x14ABD0, the method tables
// D_00217398 to D_002173E0), a screen element's methods and the helpers after them (0x14ABD0 to
// 0x14B550), class 0x10's methods, class 0x11's first two and SetSinCosPair (0x14B550 to 0x14B6A8).
// Where it ends, retail proves only to a range. Its .rodata (func_00149760's constants and two
// jump tables, 0x249EA0 to 0x249EE4) is followed by 12 bytes of zeros and func_0014B6A8's
// FLT_MAX on 16 at 0x249EF0, the next file's .rodata (file_14B6A8.cpp), so a file ends between
// func_00149760 and func_0014B6A8. But any function start from 0x14A7B8 to 0x14B6A8 links to the
// same bytes: the functions between them read no .rodata or .data of either file, their code is
// on 8 as every file's is, and the one .bss they use, D_0027C008 (func_0014B608, func_0014B640),
// can be a file's whole .bss (a file of words aligns its .bss to 4), so it may lie in this file
// or the next. Built whole, the cuts at 0x14A7B8, 0x14A888, 0x14ABD0, 0x14B608 and 0x14B6A8 all
// printed MATCH (docs/AGENT_WORKFLOW.md, "Finding and proving a file"). The cut is at 0x14B6A8,
// where the next file's data provably begins; the functions from 0x14A7B8 to 0x14B6A8 could
// belong to either file or to a third. Its name is ours, after its first address.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_notifier.h"
#include "world.h"
#include "camera.h"
#include "game_progress.h"
#include "effect.h"
#include "screen_element.h"
#include "font.h"
#include "gauge_manager.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "object_link.h"
#include "scatter_controller.h"
#include "shapes.h"
#include "object_pool.h"
#include "owner_message.h"
#include "vu0.h"
#include "scope_marker.h"
#include "mul_rotation.h"
#include "pad_record.h"
#include "ramp_profile.h"

extern Player* g_player;
extern s32 D_00275BEC;
extern f32 g_timeScale;

void SetCameraControllerOwner(CameraController* self, Camera* owner);

void VectorToAngles(void* a, void* b, void* c);
s32 GetCameraControllerTargetPoint(void* out, TargetCameraController* self);
void BuildYawPitchMatrix(f32 yaw, f32 pitch, Mat02* out);
void SetCameraLookAnchor(void* eng, void* tmp);
void SetCameraNearDistance(void* eng, f32 x);
void RegisterAgent(void* self);
void AppendToList(void* table, void* self);

// What SetSinCosPair fills: the two results of ComputeSinCos and a word it clears.
struct SinCosPair { f32 a; f32 b; s32 value; };

void ComputeSinCos(void* a, void* b, f32 value);
void UnregisterAgent(void*);
void RemoveFromList(void*, void*);
void CopyAgent(void*, void*);
void InitAgent(void*);
void StartAgent(void*);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);

s32 GetCameraControllerTargetPoint(void* out, TargetCameraController* self);
void GetTargetCameraControllerEyePoint(void* out, void* self);
void StopSoundRecord(void* self, s32 n);
void PlaceCameraLookingAt(void* self, void* a, void* b);
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 c);
void SnapCameraZoom(void* self, f32 x);
void SetCameraNearDistance(void* self, f32 x);

void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void PauseIopVoice(s32 a);

// What StartCameraSounds keeps of each sound it starts: the IOP voice at +0x18 it pauses.
struct CameraSound {
    u8 pad000[0x18];
    s32 voice;
};

// The object StartCameraSounds fills (g_camera): two sounds and a flag it sets.
struct CameraSoundOwner {
    u8 pad000[0x44];
    s32 f44;
    CameraSound* f48;
    s32 f4C;
};

extern u8 g_camera[];
void ConvertPositionToWorld(void* n, void* out);
extern u8 g_identityMatrix[];
extern u8 g_identityMatrix[];
extern u8 g_identityMatrix[];
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
extern T217D_Vt D_00218330;
void RemoveFromList(void* a, void* b);

void* GetActiveSwitchedCollider(void);

extern f32 g_gameTime[];

void AppendToList(void*,void*);

extern f32 g_gameTime[];

void* GetActiveSwitchedCollider(void);
extern f32 g_gameTime[];

// The file's statics (.bss from 0x27C008).
static s32 D_0027C008;  // a running count, reset by func_0014B608

f32 D_00261BF0 = 0.0f;
f32 D_00261BF4 = 0.300000012f;
f32 D_00261BF8 = 7e+01f;
f32 D_00261BFC = -1.0f;
// The upper bound of the tilt, a float of its own: func_00149760 reads it as a scalar (the alias
// rule, docs/TOOLCHAIN.md). The 16-aligned offsets after it pad it to 0x261C10.
f32 D_00261C00 = 1.0f;
Vec02 D_00261C10 = { -150.0f, 0.0f, 0.0f, 0.0f };
Vec02 D_00261C20 = { -25.0f, 0.0f, 0.0f, 0.0f };
f32 D_00261C30[4] = { 2.0f, 0.0f, -1.0f, 0.0f };
f32 D_00261C40[4] = { 0.200000003f, 0.0f, 0.5f, 1.0f };
f32 D_00261C50[4] = { 0.25f, 0.0f, 0.75f, 2.25f };
f32 D_00261C60[4] = { 10.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00261C70[4] = { 1.0f, 0.400000006f, 1.5f, 0.0f };
f32 D_00261C80[3] = { 5.0f, 0.0f, 0.5f };
f32 D_00261C8C = 24.0f;

void SetCameraControllerOwner(CameraController* self, Camera* owner)
{
    self->owner = owner;
}

s32 IsTopCameraController(CameraController* self)
{
    return self->owner->stack[0].ctl == self;
}

void SetCameraControllerValue(CameraController* self, s32 value)
{
    self->value = value;
}

void UpdateIdleCameraController(CameraController* self, u8* eye, u8* tail, f32 dt)
{
}


Quad16 GetCameraControllerTargetPoint(TargetCameraController* self)
{
    Quad16 r;
    if (self->f5C != 0) {
        ConvertPositionToWorld(self->f5C, &r);
    } else {
        if (GetActiveSwitchedCollider() != 0) {
            r = *(Quad16*)((u8*)GetActiveSwitchedCollider() + 0x140);
            *(f32*)&r.w[2] = *(f32*)&r.w[2] + D_00261BF8;
        } else {
            r = *(Quad16*)(*(u8**)g_camera + 0x40);
        }
    }
    return r;
}

Quad16 GetTargetCameraControllerEyePoint(TargetCameraController* self)
{
    Quad16 r;
    Mat02 m;
    Vec02* offset;
    if (g_player != 0 && g_player->f2228 == 0x22) {
        offset = &D_00261C20;
    } else {
        offset = &D_00261C10;
    }
    BuildYawPitchMatrix(*(f32*)&self->value, self->f10, &m);
    Quad16 target = GetCameraControllerTargetPoint(self);
    Vu0::Q(r) = Vu0::Add(Vu0::Q(target), Vu0::Rotate(m, Vu0::Q(*(Quad16*)offset)));
    return r;
}

void StartCameraSounds(CameraSoundOwner* self)
{
    StartSoundEffect(0x71, &self->f48, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    if (self->f48 != 0) {
        PauseIopVoice(self->f48->voice);
    }
    StartSoundEffect(0x70, &self->f4C, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    self->f44 = 1;
}

void PushStackValue(TargetCameraController* s, s32 value)
{
    s32 n = s->count;
    if ((u32)n < 4) {
        s->items[n] = value;
        s->count = n + 1;
    }
}

s32 PopStackValue(TargetCameraController* s)
{
    s32 n = s->count;
    if (n <= 0) {
        return -1;
    }
    n = n - 1;
    s->count = n;
    return s->items[n];
}

s32 PeekStackValue(TargetCameraController* s)
{
    s32 n = s->count;
    if (n <= 0) {
        return -1;
    }
    return s->items[n - 1];
}

void InitTargetCameraController(TargetCameraController* self, Camera* owner)
{
    SetCameraControllerOwner(self, owner);
    self->count = 0;
    self->f20 = 10.0f;
    PushStackValue(self, 0);
    self->f54 = 0.5f;
    self->f58 = -1.0f;
    self->f50 = 0;
}

void ActivateTargetCameraController(TargetCameraController* self)
{
    Quad4 tmp;
    Camera* eng = (Camera*)self->owner;
    VectorToAngles((u8*)eng + 0x80, (u8*)self + 8, (u8*)self + 0x10);
    f32 d = self->f20;
    self->f10 = D_00261BF0;
    self->f0C = 0;
    self->f14 = 0;
    self->f18 = 0;
    self->f1C = 0;
    f32 a = eng->f1C8;
    self->f28 = a;
    self->f24 = a / d;
    GetCameraControllerTargetPoint(&tmp, self);
    SetCameraLookAnchor(eng, &tmp);
    self->f2C = eng->f1E4;
    SetCameraNearDistance(eng, 49.0f);
}

// v limited to [lo, hi].
static inline f32 ClampFloat(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}
extern Player* g_player;
extern u8 g_camera[];
extern f32 g_gameTime[];
extern f32 D_00261BF4;
extern f32 D_00261BFC;
extern f32 D_00261C00;
extern Vec02 D_00261C20;
extern f32 D_00261C30[4];
extern f32 D_00261C40[4];
extern f32 D_00261C50[4];
extern f32 D_00261C60[4];
extern f32 D_00261C70[4];
extern f32 D_00261C80[3];
extern f32 D_00261C8C;
Quad16 GetCameraControllerTargetPoint(TargetCameraController* self);
Quad16 GetTargetCameraControllerEyePoint(TargetCameraController* self);
s32 PeekStackValue(TargetCameraController* s);
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 c);
void SnapCameraZoom(void* self, f32 x);
void PauseIopVoice(s32 a);
void ConvertPositionToWorld(void* n, void* out);
void* GetActiveSwitchedCollider(void);
void VectorToAngles(void* a, void* b, void* c);

// The fraction of the way v lies from r[0] to r[1], 0 when the two are equal.
static inline f32 RangeFraction(const f32* r, f32 v)
{
    if (r[0] == r[1]) {
        return 0.0f;
    }
    return (v - r[0]) / (r[1] - r[0]);
}

// The point a fraction t of the way from r[0] to r[1].
static inline f32 RangeLerp(const f32* r, f32 t)
{
    return (1.0f - t) * r[0] + t * r[1];
}



// v made unit length.
static inline Vu0::Vec Normalized(Vu0::Vec v)
{
    return Vu0::DivX(v, Vu0::Length(v));
}

// Vu0::Vec::Scalar with its slot written straight through the frame: Scalar's reference keeps the
// slot's address in a register that CSE later reuses for a local at the same place (the &off
// passed to ComputeDirectionFromAngles), where retail forms that address afresh.
static inline Vu0::Vec ScalarHere(f32 f)
{
    Vu0::Slot t;
    *(u128*)&t = Vu0::FromFloat(f);
    Vu0::Vec r;
    r.q = *(u128*)&t;
    return r;
}

static inline f32 Blend(f32 t, f32 a, f32 b)
{
    return (1.0f - t) * a + t * b;
}

extern const Vec02 g_unitXVector;
extern const Vec02 g_unitYVector;
extern const Vec02 g_unitZVector;
extern void* D_002704F4;
extern f32 D_002704F8;
extern s32 D_00270518;
f32 Arctangent(f32 x);
void ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, s32 e, s32 f, f32 t);
f32 ApproachValueWithRamp(f32 value, f32 target, f32 dt, void* profile, f32* speed);
f32 ApproachValueClampingVelocity(f32 value, f32 speed, f32 target, f32 dt, void* profile, f32* out);
void ResumeIopVoice(s32 voice);
void SetSoundRecordPitch(void* record, f32 x);
void SetSoundRecordVolume(void* record, f32 x);
f32 ClampToMagnitude(f32 a, f32 b);
f32 WrapAngle(f32 a);
f32 ClampToRange(void* range, f32 v);
void BuildBasisFromX(Vec02* v, Mat02* out);
void ProjectPointToCamera(Camera* cam, void* point, void* out);
void UnprojectCameraPoint(Camera* cam, void* point, void* out);
f32 ArctangentOfRatio(f32 y, f32 x);
void ConvertOffsetToSpherical(void* a, void* b, f32* heading, f32* pitch, f32* length);
void ComputeDirectionFromAngles(Vec02* out, f32 first, f32 second, f32 scale);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
void UpdateCameraMatrices(Camera* self);
void func_00144BE8(Camera* cam, s32 mode, void* eye, void* target, s32 e, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);

void UpdateTargetCameraController(TargetCameraController* self, u8* eye0, PadRecord* pad, f32 dt)
{
    Quad16 target = GetCameraControllerTargetPoint(self);
    Quad16 eye;
    Camera* cam = self->owner;
    f32 ease = D_00261BF4;
    s32 mode;
    s32 flag;
    f32 blend;
    f32 far;
    f32 rise;

    if (dt == 0.0f) {
        return;
    }
    mode = PeekStackValue(self);
    switch (mode) {
    case 0: {
        f32 t = self->g18;
        f32 speed = (D_00261C30[0] + t * (D_00261C30[1] + t * D_00261C30[2])) * pad->f78 * __builtin_fabsf(pad->f78);
        self->g1C = speed;
        self->g18 = ClampFloat(t + speed * dt, 0.0f, 1.0f);
        break;
    }
    case 1:
    case 2: {
        u8* obj = self->obj50;
        s32 near = 0;
        f32 zoom;
        if (obj != 0) {
            Vec02 pos;
            Vec02 span;
            Vec02 mid;
            Vec02 d;
            Vec02 e;
            f32 size = (0.0f < self->f58) ? self->f58 : *(f32*)(obj + 0x2A8);
            f32 dist = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Vec::Of((*(Camera**)g_camera)->f40), Vu0::Vec::Of(*(Vec02*)(obj + 0x140)))));
            f32 fov = 2.0f * Arctangent(size / (self->f54 * dist));
            fov = self->f24 >? fov;
            ComputeObjectFrameAtTime(obj, 0, &pos, 0, 0, 0, 0.1f);
            Vu0::Q(span) = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(*(Vec02*)(obj + 0x140))).q;
            Camera* gc = *(Camera**)g_camera;
            Vu0::Q(mid) = Vu0::Add(Vu0::Vec::Of(*(Vec02*)(obj + 0x140)), Vu0::MulX(Vu0::Vec::Of(span), Vu0::Vec::Scalar(0.5f))).q;
            f32 reach = size + Vu0::ToFloatMoved(Vu0::Length(Vu0::Vec::Of(span))) * 0.5f;
            Vu0::Q(d) = Vu0::Sub(Vu0::Vec::Of(mid), Vu0::Vec::Of(gc->f40)).q;
            Vu0::Q(d) = Vu0::RotateTransposed(*(Mat02*)gc->f80, Vu0::Vec::Of(d)).q;
            e.x = -d.y;
            e.y = d.z;
            e.z = d.x;
            f32 fit;
            if (0.0001f < e.z) {
                f32 a = 2.0f * Arctangent((__builtin_fabsf(e.x) + reach) / (e.z * gc->f1E0));
                f32 b = 2.0f * Arctangent((__builtin_fabsf(e.y) + reach) / e.z);
                fit = self->f28 <? (b >? a);
            } else {
                fit = self->f28;
            }
            zoom = ClampFloat(1.0f - RangeFraction(&self->f24, fov >? fit), 0.0f, 1.0f);
            if (fov < fit && zoom < self->g18) {
                near = 1;
            }
        } else {
            zoom = 0.0f;
        }
        if ((D_00270518 != 1 && (near || (zoom < self->g18 && (self->g1C < 0.0f || 0.025f < self->g18 - zoom))))
            || (self->g18 < zoom && (0.0f < self->g1C || 0.035f < zoom - self->g18))) {
            void* profile;
            RampProfile scaled;
            if (!near) {
                f32 gap = __builtin_fabsf(zoom - self->g18);
                f32 w[2] = { 1.0f, 4.0f };
                f32 s = (1.0f - gap) * w[0] + gap * w[1];
                scaled = *(RampProfile*)D_00261C40;
                scaled.maxAccel *= s;
                scaled.maxSpeed *= s;
                scaled.endSpeed *= s;
                profile = &scaled;
            } else {
                profile = D_00261C50;
            }
            self->g18 = ApproachValueClampingVelocity(self->g18, self->g1C, zoom, dt, profile, &self->g1C);
        } else {
            self->g1C = ApproachValueWithRamp(self->g1C, 0.0f, dt, D_00261C60, 0);
            self->g18 = ClampFloat(self->g18 + self->g1C * dt, 0.0f, 1.0f);
        }
        break;
    }
    case 3: {
        f32 v = ClampFloat(ApproachValueWithRamp(self->g18, D_002704F8, dt, D_00261C70, 0), 0.0f, 1.0f);
        f32 prev = self->g18;
        self->g18 = v;
        self->g1C = (v - prev) / dt;
        break;
    }
    case 4:
        break;
    }

    CameraSound* sound = (CameraSound*)self->p48;
    if (sound != 0) {
        if (self->g1C != 0.0f) {
            if (self->f44 != 0) {
                ResumeIopVoice(sound->voice);
                self->f44 = 0;
            }
            SetSoundRecordPitch(self->p48, ClampFloat(__builtin_fabsf(self->g1C), -1.0f, 1.0f));
            SetSoundRecordVolume(self->p48, ClampFloat(__builtin_fabsf(self->g1C) * 0.5f + 0.5f, 0.0f, 1.0f));
        } else if (self->f44 == 0) {
            PauseIopVoice(sound->voice);
            self->f44 = 1;
        }
    }

    f32 zoom = RangeLerp(&self->f24, 1.0f - self->g18);
    if (AreFloatsNearlyEqual(cam->f1C4, zoom, 0.0001f) == 0) {
        SnapCameraZoom(cam, zoom);
    }

    switch (mode) {
    case 0:
    case 1: {
        f32 x = ClampToMagnitude(pad->f40 + pad->f74, 1.0f);
        f32 y = ClampToMagnitude(pad->f44, 1.0f);
        if (g_player != 0 && g_player == GetActiveSwitchedCollider() && g_player->f2228 != 0x22) {
            y = 0.0f;
            x = 0.0f;
        }
        f32 z = (*(Camera**)g_camera)->f1C4;
        f32 limit = z * 1.3f;
        f32 scale = (1.0f - z) * 0.5f + z;
        if (mode == 0) {
            scale = 1.0f;
        }
        f32 yaw = -x * x * x * (scale * 10.0f);
        if (yaw * self->g0C <= 0.0f) {
            self->g0C = 0.0f;
        }
        f32 pitch = y * y * y * (scale * 10.0f);
        if ((mode == 0 && (g_saveData->f19EC & 0x200) == 0) || (mode == 1 && (g_saveData->f19EC & 0x400) == 0)) {
            pitch = -pitch;
        }
        f32 zero = 0.0f;
        if (pitch * self->g14 <= zero) {
            self->g14 = zero;
        }
        self->g0C = ApproachValueWithRamp(self->g0C, zero, dt, D_00261C80, 0);
        self->g14 = ApproachValueWithRamp(self->g14, zero, dt, D_00261C80, 0);
        self->g0C = ClampToMagnitude(self->g0C + yaw * dt, limit * 0.9f);
        self->g14 = ClampToMagnitude(self->g14 + pitch * dt, limit * 0.8f);
        self->g08 = WrapAngle(self->g08 + self->g0C * dt);
        self->f10 = ClampFloat(self->f10 + self->g14 * dt, D_00261BFC, D_00261C00);
        eye = GetTargetCameraControllerEyePoint(self);
        f32 since = (g_gameTime[0] - cam->f364) * 2.0f;
        blend = ClampFloat(since, 0.0f, 1.0f);
        if (g_player != 0 && g_player->f2228 == 0x22) {
            flag = 0;
            rise = 0.0f;
            far = 0.0f;
        } else {
            rise = -50.0f;
            far = 400.0f;
            flag = 1;
        }
        break;
    }
    case 2: {
        ease = 0.0f;
        Quad16 pt;
        pt = GetCameraControllerTargetPoint(self);
        u8* coll = (u8*)GetActiveSwitchedCollider();
        Mat02 basis;
        Vec02 dir;
        if (*(s32*)(coll + 0x634) != 0) {
            Vu0::Q(dir) = Vu0::Sub(Vu0::Vec::Of(*(Vec02*)(self->obj50 + 0x140)), Vu0::Vec::Of(pt)).q;
        } else {
            Vec02 screen;
            Vec02 moved;
            Vec02 ahead;
            Vec02 world;
            Vec02 push;
            const u128* rows = (const u128*)cam->f80;
            Vu0::Vec r0, r1, r2;
            r0.q = rows[0];
            r1.q = rows[1];
            r2.q = rows[2];
            Vu0::Q(ahead) = Vu0::Add(Vu0::Vec::Of(pt), Vu0::RotateRowsTied(r0, r1, r2, Vu0::MulX(Vu0::Vec::Of(g_unitXVector), Vu0::Vec::Scalar(100.0f)))).q;
            ProjectPointToCamera(*(Camera**)g_camera, &ahead, &screen);
            push.x = pad->f40;
            if (g_saveData->f19EC & 0x400) {
                push.y = pad->f44;
            } else {
                push.y = -pad->f44;
            }
            push.z = 0.0f;
            Vu0::Q(moved) = Vu0::MulAddX(Vu0::Vec::Of(screen), Vu0::Vec::Of(push), Vu0::Vec::Scalar(D_00261C8C * dt)).q;
            UnprojectCameraPoint(*(Camera**)g_camera, &moved, &world);
            Vu0::Q(dir) = Vu0::Sub(Vu0::Vec::Of(world), Vu0::Vec::Of(pt)).q;
        }
        BuildBasisFromX(&dir, &basis);
        f32 yaw;
        f32 pitch;
        VectorToAngles(&basis, &yaw, &pitch);
        flag = 1;
        far = 20.0f;
        rise = -7.0f;
        blend = 0.0f;
        f32 dy = ClampToRange(coll + 0x658, WrapAngle(yaw - *(f32*)(coll + 0x648)));
        f32 dp = ClampToRange(coll + 0x650, WrapAngle(pitch - *(f32*)(coll + 0x64C)));
        self->g08 = WrapAngle(*(f32*)(coll + 0x648) + dy);
        self->f10 = WrapAngle(*(f32*)(coll + 0x64C) + dp);
        eye = GetTargetCameraControllerEyePoint(self);
        break;
    }
    case 3: {
        u8* obj = (u8*)D_002704F4;
        if (obj != 0) {
            Vec02 n;
            Vu0::Q(n) = Normalized(Vu0::Sub(Vu0::Vec::Of(*(Vec02*)(obj + 0x140)), Vu0::Vec::Of(target))).q;
            self->g08 = ArctangentOfRatio(n.y, n.x);
            Vu0::Q(eye) = Vu0::Add(Vu0::Vec::Of(target), Vu0::MulX(Vu0::Vec::Of(n), Vu0::Vec::Scalar(-Vu0::ToFloat(Vu0::Length(Vu0::Vec::Of(D_00261C20)))))).q;
        } else {
            eye = GetTargetCameraControllerEyePoint(self);
        }
        blend = 0.5f;
        rise = -7.0f;
        far = 20.0f;
        flag = 1;
        break;
    }
    case 4: {
        T217D_3F0* s;
        if (D_002708E0.fade == 1) {
            s = &D_002708E0;
        } else {
            s = (D_00271558.fade == 1) ? &D_00271558 : 0;
        }
        u8* obj = (u8*)D_002704F4;
        if (obj == 0 && s != 0) {
            obj = (u8*)s->special;
        }
        if (s == 0 || s->target == 0 || obj == 0) {
            return;
        }
        Quad16 pos = *(Quad16*)(obj + 0x140);
        f32 sy = *(f32*)((u8*)s->target + 0x324) * 2.0f - 1.0f;
        f32 sx = *(f32*)((u8*)s->target + 0x320) * 2.0f - 1.0f;
        f32 reach = *(f32*)((u8*)s->target + 0x2D8) * 0.22222222f;
        Vec02 dir;
        if (self->f5C != 0) {
            ConvertPositionToWorld(self->f5C, &target);
            Vu0::Q(dir) = Normalized(Vu0::Sub(Vu0::Vec::Of(target), Vu0::Vec::Of(pos))).q;
        } else {
            Vu0::Vec fwd = Vu0::Vec::Of(*(Vec02*)(obj + 0x110));
            Vu0::Vec k = Vu0::Vec::Scalar(sx);
            Vu0::Q(dir) = Normalized(Vu0::MulAddX(fwd, Vu0::Vec::Of(*(Vec02*)(obj + 0x120)), k)).q;
        }
        u8* tg = (u8*)s->target;
        Vu0::Q(target) = Vu0::Add(Vu0::Add(Vu0::Vec::Of(pos), Vu0::MulX(Vu0::Vec::Of(dir), ScalarHere(reach * 2.0f))), Vu0::Vec::Of(*(Vec02*)(tg + 0x310))).q;
        f32 heading;
        f32 tilt;
        f32 length;
        ConvertOffsetToSpherical(&target, &pos, &heading, &tilt, &length);
        f32 z = cam->f1C4;
        f32 a = heading + 3.1415927f + sx * z * cam->f1E0 * 0.5f;
        f32 b = -tilt - sy * z * 0.5f;
        Vec02 off;
        ComputeDirectionFromAngles(&off, heading, tilt, length);
        Vu0::Q(cam->f40) = Vu0::Add(Vu0::Vec::Of(pos), Vu0::Vec::Of(off)).q;
        Mat02 mz;
        Mat02 my;
        Mat02 mx;
        BuildAxisAngleMatrix(&g_unitZVector, &mz, a);
        BuildAxisAngleMatrix(&g_unitYVector, &my, -b);
        BuildAxisAngleMatrix(&g_unitXVector, &mx, *(f32*)((u8*)s->target + 0x328));
        Mat02 rot;
        Mat02 m;
        MulRotationThenCopy(&m, mz, my);
        MulRotationThenCopyVia((Mat02*)cam->f80, rot, m, mx);
        UpdateCameraMatrices(cam);
        *(Quad16*)cam->f2D0 = pos;
        return;
    }
    }
    func_00144BE8(cam, flag, &eye, &target, 0, Blend(blend, 20.0f, far), Blend(blend, -7.0f, rise),
                  Blend(blend, 1.0f, 0.25f), 0.0f, ease, dt);
}


void DeactivateTargetCameraController(TargetCameraController* self)
{
    Quad4 a;
    Quad4 b;
    Camera* n;

    GetCameraControllerTargetPoint(&a, self);
    GetTargetCameraControllerEyePoint(&b, self);
    n = (Camera*)self->owner;
    StopSoundRecord(self->p48, 0);
    StopSoundRecord(self->p4C, 500);
    PlaceCameraLookingAt(n, &b, &a);
    if (AreFloatsNearlyEqual(n->f1C4, self->f28, 1e-4f) == 0) {
        SnapCameraZoom(n, self->f28);
    }
    self->f5C = 0;
    if (n->f1E4 == 49.0f) {
        SetCameraNearDistance(n, self->f2C);
    }
}

void InitFrameCameraController(FrameCameraController* self, Camera* a1)
{
    SetCameraControllerOwner(self, a1);
    CameraFrameBlock* dst = &self->frame20;
    *dst = *(CameraFrameBlock*)g_identityMatrix;
}

void ActivateFrameCameraController(FrameCameraController* self)
{
    Camera* parent = self->owner;
    SetCameraLookAnchor(parent, (u8*)parent->stack[0].target + 0x370);
}

void func_00144BE8(Camera* a, s32 b, void* c, s32 d, s32 e, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);

void UpdateFrameCameraController(FrameCameraController* self, f32 dt)
{
    Camera* cam = self->owner;
    PlacedObject* frame = (PlacedObject*)cam->stack[0].target;
    Mat02 basis;
    Vec02 rv;
    Vec02 eye;
    Vec02 target;
    MulRotationCopied(&basis, frame->m110, *(Mat02*)&self->frame20);
    Vu0::Q(eye) = Vu0::MulAddX(Vu0::Vec::Of(frame->v140), Vu0::Vec::Of(basis.r[0]), Vu0::Vec::Scalar(10.0f)).q;
    Vu0::Q(rv) = Vu0::Rotate(frame->m110, Vu0::Q(*(Vec02*)((u8*)self + 0x10)));
    Vu0::Q(target) = Vu0::Add(Vu0::Q(frame->v140), Vu0::Q(rv));
    Vu0::Q(eye) = Vu0::Add(Vu0::Q(eye), Vu0::Q(rv));
    f32 one = 1.0f;
    f32 d = g_gameTime[0] - cam->f364;
    f32 t;
    if (d < 0.0f) {
        t = 0.0f;
    } else if (one < d) {
        t = one;
    } else {
        t = d;
    }
    f32 u = 1.0f - t;
    func_00144BE8(cam, 1, &target, (s32)&eye, 0, t * 100.0f + u * 20.0f, t * -15.0f + u * -7.0f, t * 0.25f + u, 0.0f, 0.0f, dt);
}

void ActivateValueCameraController(ValueCameraController* obj, s32 value) { obj->value = value; }

void DeactivateValueCameraController(ValueCameraController* obj) { obj->value = 0; }

void ConvertPositionToWorld(void* n, void* out);
void TransformPointBetweenFrames(void* a0, s32 a1, void* a2, void* a3);
void BuildBasisFromX(void* self, void* value);
void BuildBasisFromXAndZHint(void* a, void* b, void* out);
void SetCameraPlacement(Camera* cam, void* pos, void* basis);

void UpdateValueCameraController(ValueCameraController* ctl)
{
    Vec02 pos;
    Mat02 basis;
    Vec02 v40;
    Vec02 v50;
    Mat02 t1;
    Mat02 t2;
    u8* o = (u8*)ctl->ptr;
    Camera* cam = ctl->owner;
    TransformPointBetweenFrames(o, 0, o + 0x2E0, &pos);
    if (*(u8**)(o + 0x2D8) != 0) {
        Vu0::Q(v40) = Vu0::Sub(Vu0::Q(((PlacedObject*)*(u8**)(o + 0x2D8))->v140), Vu0::Q(pos));
        BuildBasisFromX(&v40, &basis);
    } else if (*(u8**)(o + 0x2D4) != 0) {
        ConvertPositionToWorld(*(u8**)(o + 0x2D4), &v40);
        Vu0::Q(v50) = Vu0::Sub(Vu0::Q(v40), Vu0::Q(pos));
        BuildBasisFromX(&v50, &basis);
    } else {
        BuildBasisFromXAndZHint(o + 0x2F0, o + 0x300, &basis);
        const Mat02& m = *(Mat02*)(o + 0x110);
        u128 r0 = Vu0::RotateUntied(m, Vu0::Q(basis.r[0]));
        u128 r1 = Vu0::RotateUntied(m, Vu0::Q(basis.r[1]));
        u128 r2 = Vu0::RotateUntied(m, Vu0::Q(basis.r[2]));
        Vu0::Q(t2.r[0]) = r0;
        Vu0::Q(t1.r[0]) = r0;
        Vu0::Q(t2.r[1]) = r1;
        Vu0::Q(t1.r[1]) = r1;
        Vu0::Q(t2.r[2]) = r2;
        Vu0::Q(t1.r[2]) = r2;
        Vu0::Q(basis.r[0]) = r0;
        Vu0::Q(basis.r[1]) = r1;
        Vu0::Q(basis.r[2]) = r2;
    }
    SetCameraPlacement(cam, o + 0x140, &basis);
}

void InitItemColumn(T217D_720* self)
{
    u32 n;

    InitScreenElement(self, 0x20);
    T217D_330* e = self->items;
    for (n = 0; n < 4; n++) {
        e->vt = &D_00218330;
        D_00218330.m00(e, 0x12);
        e++;
    }
}

void SetupItemColumn(T217D_720* self)
{
    T217D_330* e;
    u32 i;

    e = (T217D_330*)self;
    SetupScreenElementText(e);
    e = self->items;
    for (i = 0; i < 4; i++) {
        e->vt->m01(e);
        e->frame = 0;
        e->font->sx = 0.8f;
        e->font->sy = 0.8f;
        SetScreenElementSlideInTime(e, 1.0f);
        SetScreenElementSlideOutTime(e, 1.0f);
        SetScreenElementHoldTime(e, 0.0f);
        e++;
    }
}

void UpdateItemColumn(T217D_720* self, f32* clock)
{
    SetScreenElementClock(self, clock);
    T217D_330* e = self->items;
    for (u32 i = 0; i < 4; i++) {
        e->vt->m17(e, clock);
        e++;
    }
}

void UpdateItemColumnSlide(T217D_720* self)
{
    UpdateScreenElementSlide(self);
    for (s32 i = 0; i < self->count; i++) {
        T217D_330* s = &self->items[i];
        s->vt->m02(s);
    }
}

void DrawItemColumn(T217D_720* self)
{
    if (D_00275BEC == 1) {
        f32 acc = self->y;
        s32 i;
        for (i = 0; i < self->count; i++) {
            T217D_330* e = &self->items[i];
            f32 saved = e->blend;
            f32 base = self->x;
            f32 scaled = saved * g_timeScale;
            e->y = acc;
            e->x = base;
            e->blend = scaled;
            e->vt->m09(e);
            e->blend = saved;
            acc += e->h;
        }
    }
}

void ResizeItemColumn(T217D_720* self, s32 n, f32 x, f32 y)
{
    self->place->dx = x;
    self->place->dy = y;
    self->count = n;
    Font* q = self->font;
    SetScreenElementSize(self, self->w, (f32)q->height * q->sy * (f32)n);
    self->vt->m16(self, 2);
}

void ClearItemColumn(T217D_720* self)
{
    self->vt->m16(self, 0);
}

void func_0014AF38(T217D_720* self, s32 index, char* text, f32 hold)
{
    T217D_330* item = &self->items[index];
    for (char* p = text; *p != 0; p++) {
        if (*p == '_') {
            *p = ' ';
        }
    }
    item->vt->m08(item, text);
    f32 width = 0.0f;
    for (s32 i = 0; i < self->count; i++) {
        width = self->items[i].w >? width;
    }
    Font* q = self->font;
    SetScreenElementSize(self, width, (f32)q->height * q->sy * (f32)self->count);
    if (hold != 0.0f) {
        item = &self->items[index];
        f32 span = item->vt->m11(item);
        span += item->vt->m13(item);
        hold -= span;
        if (hold <= 0.0f) {
            hold = 0.016666668f;
        }
        SetScreenElementHoldTime(item, hold);
        item->vt->m14(item);
    }
}

void FactorSymmetricMatrix(s32 n, f32* a, f32* l)
{
    s32 i;
    s32 j;
    s32 k;
    f32 sum;

    if (n == 0)
    {
        return;
    }
    for (i = 0; i < n; i++)
    {
        l[i] = a[i];
    }
    if (__builtin_fabsf(l[0]) < 1e-8f)
    {
        for (j = 0; j < n; j++)
        {
            l[j * n] = 0.0f;
        }
    }
    else
    {
        for (j = 1; j < n; j++)
        {
            l[j * n] = a[j * n] / l[0];
        }
    }
    for (j = 1; j < n - 1; j++)
    {
        for (i = j; i < n; i++)
        {
            sum = 0.0f;
            for (k = 0; k < j; k++)
            {
                sum += l[i + k * n] * l[j * n + k];
            }
            l[j * n + i] = a[j * n + i] - sum;
        }
        if (__builtin_fabsf(l[j * n + j]) < 1e-8f)
        {
            for (k = j; k < n; k++)
            {
                l[k * n + j] = 0.0f;
            }
        }
        else
        {
            for (k = j + 1; k < n; k++)
            {
                sum = 0.0f;
                for (i = 0; i < j; i++)
                {
                    sum += l[j + i * n] * l[k * n + i];
                }
                l[k * n + j] = (a[k * n + j] - sum) / l[j * n + j];
            }
        }
    }
    sum = 0.0f;
    for (k = 0; k < n - 1; k++)
    {
        sum += l[(n - 1) + k * n] * l[(n - 1) * n + k];
    }
    l[(n - 1) * n + (n - 1)] = a[(n - 1) * n + (n - 1)] - sum;
    if (__builtin_fabsf(l[(n - 1) * n + (n - 1)]) < 1e-8f)
    {
        l[(n - 1) * n + (n - 1)] = 0.0f;
    }
}

void SolveFactoredSystem(s32 n, f32* m, f32* b, f32* x)
{
    s32 i;
    s32 k;
    f32 sum;

    for (i = 0; i < n; i++) {
        if (m[i * n + i] == 0.0f) {
            x[i] = 0.0f;
        } else {
            sum = 0.0f;
            for (k = 0; k < i; k++) {
                sum += m[k * n + i] * x[k];
            }
            x[i] = (b[i] - sum) / m[i * n + i];
        }
    }

    for (i = n - 2; i >= 0; i--) {
        if (m[i * n + i] != 0.0f) {
            sum = 0.0f;
            for (k = i + 1; k < n; k++) {
                sum += m[k * n + i] * x[k];
            }
            x[i] -= sum;
        }
    }
}

void RegisterWorldListedAgent(WorldListedAgent* self)
{
    RegisterAgent(self);
    AppendToList(&self->world->list1CCC, self);
}

void UnregisterWorldListedAgent(WorldListedAgent* self) { UnregisterAgent(self); RemoveFromList(&self->world->list1CCC, self); }

void CopyWorldListedAgent(WorldListedAgent* self, void* other) { Pack10 save=self->fC10; CopyAgent(self,other); self->fC10=save; }

void InitNumberedAgent(NumberedAgent* self) { InitAgent(self); self->fC24=1; D_0027C008=0; }

void StartNumberedAgent(NumberedAgent* self) { StartAgent(self); self->fC2C=D_0027C008++; }

void SetSinCosPair(f32 value, SinCosPair* self)
{
    ComputeSinCos(&self->b, self, value);
    self->value = 0;
}
