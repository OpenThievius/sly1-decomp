// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 4073/4184 (97.3%), checked 2026-11-08
// NEAR (2026-11-08, large-149760, mech-149760): regdiff "order", 1035 of 1046 aligned; every block
// is retail's but for registers and scheduling in three places. Fixed (mech-149760): the second
// switch's cases 0/1 store the WrapAngle result as a member (self->g08) and read the tilt's upper
// bound as a scalar (D_00261C00, now an f32 of its own): a struct member at a varying address never
// aliases a scalar at a fixed one (alias.c fixed_scalar_and_varying_struct_p), so sched1 loads both
// bounds before the store, as retail does. Still differs: (1) case 1, the 0.0 of the zoom clamp
// takes $f4 where retail has $f1: global-alloc's pass 0 skips $f1 because r386 (the RangeFraction
// result, lower priority, conflicting) has $f1 in its full preferences, merged by
// expand_preferences from zoom (sub.s $f1, zoom, g18) through v; retail must allocate r386 before
// the 0.0 (priority log2(refs)*refs/live length: 0.0 is 3/10, r386 3/12); (3) case 2: the 100.0
// scalar's slot store is a MEM with neither in_struct nor scalar set (stored through Vu0::Q), and
// the camera rows' loads (through Rotate's u128 pointer) neither: they may alias, so the store
// precedes the loads, gets their priority, and MulX's result takes the scalar's register. Retail
// keeps the scalar in $vf6 and stores it last. Rows loaded first as values (a tied RotateRows)
// give $vf6 and the late store but cost an instruction and change the address registers; the
// alias rule would need the store scalar-flagged (a scalar local's own MEM) and the row loads
// member accesses; (4) case 4's first rotation product: sched1 hoists the loads of my's rows above
// the first row's stores, so mz's third row outranks them in local-alloc ($vf1 where retail has
// $vf3) and the product's registers follow. Tried: every MulRotation* Into form, RotateUntied,
// named operands, u128 against Vec forms, clamp shapes (Limit, Clamp, bounds first,
// ValueRange::Clamp, the clamp written out, the fraction named).
// Build: put it in src/main/file_149398.cpp at its INCLUDE_ASM line (it replaces the three
// INCLUDE_RODATA lines before it: D_00249EA0 is its {1, 4} array, the jump tables are its).
#include "common.h"
#include "vu0.h"
#include "shapes.h"
#include "switched_collider.h"
#include "camera.h"
#include "game_progress.h"
#include "screen_element.h"
#include "pad_record.h"
#include "ramp_profile.h"
#include "mul_rotation.h"

struct CameraSound {
    u8 pad000[0x18];
    s32 voice;
};

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

static inline f32 ClampFloat(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    return v;
}

static inline f32 LimitFloat(f32 v, f32 lo, f32 hi)
{
    f32 r;
    if (v < lo) {
        r = lo;
    } else if (hi < v) {
        r = hi;
    } else {
        r = v;
    }
    return r;
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
            f32 zero = 0.0f;
            self->g1C = ApproachValueWithRamp(self->g1C, zero, dt, D_00261C60, 0);
            self->g18 = LimitFloat(self->g18 + self->g1C * dt, zero, 1.0f);
        }
        break;
    }
    case 3: {
        f32 v = LimitFloat(ApproachValueWithRamp(self->g18, D_002704F8, dt, D_00261C70, 0), 0.0f, 1.0f);
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
        f32 lo = 0.0f;
        f32 hi = 1.0f;
        if (since < lo) {
            blend = lo;
        } else if (hi < since) {
            blend = hi;
        } else {
            blend = since;
        }
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
            Vu0::Q(ahead) = Vu0::Add(Vu0::Vec::Of(pt), Vu0::Rotate(*(Mat02*)cam->f80, Vu0::MulX(Vu0::Vec::Of(g_unitXVector), Vu0::Vec::Scalar(100.0f)))).q;
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
        MulRotationRowsInto(&m, mz, my);
        MulRotationRowsInto(&rot, m, mx);
        *(Mat02*)cam->f80 = rot;
        UpdateCameraMatrices(cam);
        *(Quad16*)cam->f2D0 = pos;
        return;
    }
    }
    func_00144BE8(cam, flag, &eye, &target, 0, Blend(blend, 20.0f, far), Blend(blend, -7.0f, rise),
                  Blend(blend, 1.0f, 0.25f), 0.0f, ease, dt);
}

