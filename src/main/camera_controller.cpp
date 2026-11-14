// SPDX-License-Identifier: AGPL-3.0-or-later
// The camera's controllers, 0x149398 to 0x14ABD0 (its .rodata from 0x249EA0, its .data from
// 0x261BF0): the base controller and its value stack, and the target, frame and value
// controllers (their method tables D_00217398 to D_002173E0). Its .rodata (func_00149760's
// constants and two jump tables, 0x249EA0 to 0x249EE4) is followed by 12 bytes of zeros and
// func_0014B6A8's FLT_MAX on 16 at 0x249EF0, the .rodata of gauge_manager.cpp, so a file ends
// between func_00149760 and func_0014B6A8. Any function start from 0x14A7B8 to 0x14B6A8 links to
// the same bytes: the functions between read no .rodata or .data of either file, their code is
// on 8 as every file's is, and the one .bss they use, D_0027C008, can be a file's whole .bss (a
// file of words aligns its .bss to 4). Built whole, the cuts at 0x14A7B8, 0x14A888, 0x14ABD0,
// 0x14B608 and 0x14B6A8 all printed MATCH (docs/AGENT_WORKFLOW.md, "Finding and proving a
// file"). The functions between are now three files cut by role only (item_column.cpp,
// symmetric_solve.cpp, agent_registration.cpp); this one ends at 0x14ABD0, where the item column, a
// screen element, begins. The name is ours, after its role.
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
struct BaseObject;
struct Vec02;

struct BaseObject;

struct Mat02;
struct Vec02;


extern Player* g_player;
extern s32 D_00275BEC;
extern f32 g_timeScale;

void SetCameraControllerOwner(CameraController* self, Camera* owner);

void VectorToAngles(Vec3* v, f32* a1, f32* a2);
s32 GetCameraControllerTargetPoint(void* out, TargetCameraController* self);
void BuildYawPitchMatrix(f32 yaw, f32 pitch, Mat02* out);
void SetCameraLookAnchor(Camera* self, Quad16* arg);
void SetCameraNearDistance(void* eng, f32 x);
void RegisterAgent(Agent* self);
void AppendToList(List01* self, void* item);

// What SetSinCosPair fills: the two results of ComputeSinCos and a word it clears.
struct SinCosPair { f32 a; f32 b; s32 value; };

void ComputeSinCos(f32* sinOut, f32* cosOut, f32 angle);
void UnregisterAgent(Agent* self);
void RemoveFromList(List01* list, void* item);
void CopyAgent(Agent* self, void* src);
void InitAgent(Agent* self);
void StartAgent(Agent* self);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

s32 GetCameraControllerTargetPoint(void* out, TargetCameraController* self);
void StopSoundRecord(PlayingSound* self, s32 n);
void PlaceCameraLookingAt(Camera* self, const Vec02* target, const Vec02* focus);
void StopSoundRecord(void* self, s32 n);
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 c);
void SnapCameraZoom(void* self, f32 x);
void SetCameraNearDistance(void* self, f32 x);

void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
void PauseIopVoice(s32 a);

// What StartCameraSounds keeps of each sound it starts: the IOP voice at +0x18 it pauses.
struct CameraSound {
    u8 pad000[0x18];
    s32 voice;
};

// The object StartCameraSounds fills (g_camera): two sounds and a flag it sets.
struct CameraSoundOwner {
    u8 pad000[0x44];
    s32 soundPaused;
    CameraSound* sound;
    s32 secondSound;
};

extern u8 g_camera[];
void ConvertPositionToWorld(BaseObject* self, Vec02* out);
extern u8 g_identityMatrix[];
extern u8 g_identityMatrix[];
extern u8 g_identityMatrix[];
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
extern T217D_Vt D_00218330;
void RemoveFromList(List01* list, void* item);

void* GetActiveSwitchedCollider(void);

extern f32 g_gameTime[];

void AppendToList(List01* self, void* item);

extern f32 g_gameTime[];

void* GetActiveSwitchedCollider(void);
extern f32 g_gameTime[];


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
    if (self->anchorObject != 0) {
        ConvertPositionToWorld((BaseObject*)self->anchorObject, (Vec02*)&r);
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
    if (g_player != 0 && g_player->subState == 0x22) {
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
    StartSoundEffect(0x71, (PlayingSound**)&self->sound, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    if (self->sound != 0) {
        PauseIopVoice(self->sound->voice);
    }
    StartSoundEffect(0x70, (PlayingSound**)&self->secondSound, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    self->soundPaused = 1;
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
    self->sizeOverride = -1.0f;
    self->f50 = 0;
}

void ActivateTargetCameraController(TargetCameraController* self)
{
    Quad4 tmp;
    Camera* eng = (Camera*)self->owner;
    VectorToAngles((Vec3*)((u8*)eng + 0x80), (f32*)((u8*)self + 8), (f32*)((u8*)self + 0x10));
    f32 d = self->f20;
    self->f10 = D_00261BF0;
    self->f0C = 0;
    self->f14 = 0;
    self->f18 = 0;
    self->f1C = 0;
    f32 a = eng->zoomGoal;
    self->zoomMax = a;
    self->zoomMin = a / d;
    GetCameraControllerTargetPoint(&tmp, self);
    SetCameraLookAnchor(eng, (Quad16*)&tmp);
    self->savedNearDistance = eng->nearDistance;
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
void ConvertPositionToWorld(BaseObject* self, Vec02* out);
void* GetActiveSwitchedCollider(void);
void VectorToAngles(Vec3* v, f32* a1, f32* a2);

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
extern "C" f32 Arctangent(f32 x);
void ComputeObjectFrameAtTime(PlacedObject* self, PlacedObject* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin, f32 t);
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
f32 ApproachValueClampingVelocity(f32 value, f32 speed, f32 target, f32 dt, void* profile, f32* out);
void ResumeIopVoice(s32 a0);
void SetSoundRecordPitch(PlayingSound* p, f32 a);
void SetSoundRecordVolume(PlayingSound* self, f32 a);
f32 ClampToMagnitude(f32 a, f32 b);
f32 WrapAngle(f32 a);
f32 ClampToRange(ValueRange* span, f32 x);
void BuildBasisFromX(Vec02* x, Mat02* out);
void ProjectPointToCamera(Camera* camera, Vec02* in, f32* out);
void UnprojectCameraPoint(Camera* camera, f32* a, Vec02* out);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
void ConvertOffsetToSpherical(const Vec02* a, const Vec02* b, f32* heading, f32* pitch, f32* dist);
void ComputeDirectionFromAngles(Vec3* out, f32 first, f32 second, f32 scale);
void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);
void UpdateCameraMatrices(Camera* self);
void UpdateOrbitCameraPlacement(Camera* self, s32 flags, const Vec02* target, const Vec02* focus, s32 e, f32 gain, f32 damp,
                   f32 unused, f32 yawOffset, f32 pitchOffset, f32 dt);

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
        f32 t = self->zoomFraction;
        f32 speed = (D_00261C30[0] + t * (D_00261C30[1] + t * D_00261C30[2])) * pad->secondStickY * __builtin_fabsf(pad->secondStickY);
        self->zoomSpeed = speed;
        self->zoomFraction = ClampFloat(t + speed * dt, 0.0f, 1.0f);
        break;
    }
    case 1:
    case 2: {
        u8* obj = self->keptObject;
        s32 near = 0;
        f32 zoom;
        if (obj != 0) {
            Vec02 pos;
            Vec02 span;
            Vec02 mid;
            Vec02 d;
            Vec02 e;
            f32 size = (0.0f < self->sizeOverride) ? self->sizeOverride : *(f32*)(obj + 0x2A8);
            f32 dist = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Vec::Of((*(Camera**)g_camera)->position), Vu0::Vec::Of(*(Vec02*)(obj + 0x140)))));
            f32 fov = 2.0f * Arctangent(size / (self->f54 * dist));
            fov = self->zoomMin >? fov;
            ComputeObjectFrameAtTime((PlacedObject*)obj, 0, &pos, 0, 0, 0, 0.1f);
            Vu0::Q(span) = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(*(Vec02*)(obj + 0x140))).q;
            Camera* gc = *(Camera**)g_camera;
            Vu0::Q(mid) = Vu0::Add(Vu0::Vec::Of(*(Vec02*)(obj + 0x140)), Vu0::MulX(Vu0::Vec::Of(span), Vu0::Vec::Scalar(0.5f))).q;
            f32 reach = size + Vu0::ToFloatMoved(Vu0::Length(Vu0::Vec::Of(span))) * 0.5f;
            Vu0::Q(d) = Vu0::Sub(Vu0::Vec::Of(mid), Vu0::Vec::Of(gc->position)).q;
            Vu0::Q(d) = Vu0::RotateTransposed(*(Mat02*)gc->f80, Vu0::Vec::Of(d)).q;
            e.x = -d.y;
            e.y = d.z;
            e.z = d.x;
            f32 fit;
            if (0.0001f < e.z) {
                f32 a = 2.0f * Arctangent((__builtin_fabsf(e.x) + reach) / (e.z * gc->aspectScale));
                f32 b = 2.0f * Arctangent((__builtin_fabsf(e.y) + reach) / e.z);
                fit = self->zoomMax <? (b >? a);
            } else {
                fit = self->zoomMax;
            }
            zoom = ClampFloat(1.0f - RangeFraction(&self->zoomMin, fov >? fit), 0.0f, 1.0f);
            if (fov < fit && zoom < self->zoomFraction) {
                near = 1;
            }
        } else {
            zoom = 0.0f;
        }
        if ((D_00270518 != 1 && (near || (zoom < self->zoomFraction && (self->zoomSpeed < 0.0f || 0.025f < self->zoomFraction - zoom))))
            || (self->zoomFraction < zoom && (0.0f < self->zoomSpeed || 0.035f < zoom - self->zoomFraction))) {
            void* profile;
            RampProfile scaled;
            if (!near) {
                f32 gap = __builtin_fabsf(zoom - self->zoomFraction);
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
            self->zoomFraction = ApproachValueClampingVelocity(self->zoomFraction, self->zoomSpeed, zoom, dt, profile, &self->zoomSpeed);
        } else {
            self->zoomSpeed = ApproachValueWithRamp(self->zoomSpeed, 0.0f, dt, (RampProfile*)D_00261C60, 0);
            self->zoomFraction = ClampFloat(self->zoomFraction + self->zoomSpeed * dt, 0.0f, 1.0f);
        }
        break;
    }
    case 3: {
        f32 v = ClampFloat(ApproachValueWithRamp(self->zoomFraction, D_002704F8, dt, (RampProfile*)D_00261C70, 0), 0.0f, 1.0f);
        f32 prev = self->zoomFraction;
        self->zoomFraction = v;
        self->zoomSpeed = (v - prev) / dt;
        break;
    }
    case 4:
        break;
    }

    CameraSound* sound = (CameraSound*)self->zoomSound;
    if (sound != 0) {
        if (self->zoomSpeed != 0.0f) {
            if (self->soundPaused != 0) {
                ResumeIopVoice(sound->voice);
                self->soundPaused = 0;
            }
            SetSoundRecordPitch((PlayingSound*)self->zoomSound, ClampFloat(__builtin_fabsf(self->zoomSpeed), -1.0f, 1.0f));
            SetSoundRecordVolume((PlayingSound*)self->zoomSound, ClampFloat(__builtin_fabsf(self->zoomSpeed) * 0.5f + 0.5f, 0.0f, 1.0f));
        } else if (self->soundPaused == 0) {
            PauseIopVoice(sound->voice);
            self->soundPaused = 1;
        }
    }

    f32 zoom = RangeLerp(&self->zoomMin, 1.0f - self->zoomFraction);
    if (AreFloatsNearlyEqual(cam->zoom, zoom, 0.0001f) == 0) {
        SnapCameraZoom(cam, zoom);
    }

    switch (mode) {
    case 0:
    case 1: {
        f32 x = ClampToMagnitude(pad->stickX + pad->secondStickX, 1.0f);
        f32 y = ClampToMagnitude(pad->stickY, 1.0f);
        if (g_player != 0 && g_player == GetActiveSwitchedCollider() && g_player->subState != 0x22) {
            y = 0.0f;
            x = 0.0f;
        }
        f32 z = (*(Camera**)g_camera)->zoom;
        f32 limit = z * 1.3f;
        f32 scale = (1.0f - z) * 0.5f + z;
        if (mode == 0) {
            scale = 1.0f;
        }
        f32 yaw = -x * x * x * (scale * 10.0f);
        if (yaw * self->yawSpeed <= 0.0f) {
            self->yawSpeed = 0.0f;
        }
        f32 pitch = y * y * y * (scale * 10.0f);
        if ((mode == 0 && (g_saveData->optionFlags & 0x200) == 0) || (mode == 1 && (g_saveData->optionFlags & 0x400) == 0)) {
            pitch = -pitch;
        }
        f32 zero = 0.0f;
        if (pitch * self->pitchSpeed <= zero) {
            self->pitchSpeed = zero;
        }
        self->yawSpeed = ApproachValueWithRamp(self->yawSpeed, zero, dt, (RampProfile*)D_00261C80, 0);
        self->pitchSpeed = ApproachValueWithRamp(self->pitchSpeed, zero, dt, (RampProfile*)D_00261C80, 0);
        self->yawSpeed = ClampToMagnitude(self->yawSpeed + yaw * dt, limit * 0.9f);
        self->pitchSpeed = ClampToMagnitude(self->pitchSpeed + pitch * dt, limit * 0.8f);
        self->g08 = WrapAngle(self->g08 + self->yawSpeed * dt);
        self->f10 = ClampFloat(self->f10 + self->pitchSpeed * dt, D_00261BFC, D_00261C00);
        eye = GetTargetCameraControllerEyePoint(self);
        f32 since = (g_gameTime[0] - cam->controllerSwitchTime) * 2.0f;
        blend = ClampFloat(since, 0.0f, 1.0f);
        if (g_player != 0 && g_player->subState == 0x22) {
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
            Vu0::Q(dir) = Vu0::Sub(Vu0::Vec::Of(*(Vec02*)(self->keptObject + 0x140)), Vu0::Vec::Of(pt)).q;
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
            ProjectPointToCamera(*(Camera**)g_camera, &ahead, (f32*)&screen);
            push.x = pad->stickX;
            if (g_saveData->optionFlags & 0x400) {
                push.y = pad->stickY;
            } else {
                push.y = -pad->stickY;
            }
            push.z = 0.0f;
            Vu0::Q(moved) = Vu0::MulAddX(Vu0::Vec::Of(screen), Vu0::Vec::Of(push), Vu0::Vec::Scalar(D_00261C8C * dt)).q;
            UnprojectCameraPoint(*(Camera**)g_camera, (f32*)&moved, &world);
            Vu0::Q(dir) = Vu0::Sub(Vu0::Vec::Of(world), Vu0::Vec::Of(pt)).q;
        }
        BuildBasisFromX(&dir, &basis);
        f32 yaw;
        f32 pitch;
        VectorToAngles((Vec3*)&basis, &yaw, &pitch);
        flag = 1;
        far = 20.0f;
        rise = -7.0f;
        blend = 0.0f;
        f32 dy = ClampToRange((ValueRange*)(coll + 0x658), WrapAngle(yaw - *(f32*)(coll + 0x648)));
        f32 dp = ClampToRange((ValueRange*)(coll + 0x650), WrapAngle(pitch - *(f32*)(coll + 0x64C)));
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
        if (self->anchorObject != 0) {
            ConvertPositionToWorld((BaseObject*)self->anchorObject, (Vec02*)&target);
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
        ConvertOffsetToSpherical((const Vec02*)&target, (const Vec02*)&pos, &heading, &tilt, &length);
        f32 z = cam->zoom;
        f32 a = heading + 3.1415927f + sx * z * cam->aspectScale * 0.5f;
        f32 b = -tilt - sy * z * 0.5f;
        Vec02 off;
        ComputeDirectionFromAngles((Vec3*)&off, heading, tilt, length);
        Vu0::Q(cam->position) = Vu0::Add(Vu0::Vec::Of(pos), Vu0::Vec::Of(off)).q;
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
    UpdateOrbitCameraPlacement(cam, flag, (const Vec02*)&eye, (const Vec02*)&target, 0, Blend(blend, 20.0f, far), Blend(blend, -7.0f, rise),
                  Blend(blend, 1.0f, 0.25f), 0.0f, ease, dt);
}


void DeactivateTargetCameraController(TargetCameraController* self)
{
    Quad16 a = GetCameraControllerTargetPoint(self);
    Quad16 b = GetTargetCameraControllerEyePoint(self);
    Camera* n;
    n = (Camera*)self->owner;
    StopSoundRecord((PlayingSound*)self->zoomSound, 0);
    StopSoundRecord((PlayingSound*)self->p4C, 500);
    PlaceCameraLookingAt(n, (const Vec02*)&b, (const Vec02*)&a);
    if (AreFloatsNearlyEqual(n->zoom, self->zoomMax, 1e-4f) == 0) {
        SnapCameraZoom(n, self->zoomMax);
    }
    self->anchorObject = 0;
    if (n->nearDistance == 49.0f) {
        SetCameraNearDistance(n, self->savedNearDistance);
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
    SetCameraLookAnchor(parent, (Quad16*)((u8*)parent->stack[0].target + 0x370));
}

void UpdateOrbitCameraPlacement(Camera* self, s32 flags, const Vec02* target, const Vec02* focus, s32 e, f32 gain, f32 damp,
                   f32 unused, f32 yawOffset, f32 pitchOffset, f32 dt);

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
    f32 d = g_gameTime[0] - cam->controllerSwitchTime;
    f32 t;
    if (d < 0.0f) {
        t = 0.0f;
    } else if (one < d) {
        t = one;
    } else {
        t = d;
    }
    f32 u = 1.0f - t;
    UpdateOrbitCameraPlacement(cam, 1, &target, &eye, 0, t * 100.0f + u * 20.0f, t * -15.0f + u * -7.0f, t * 0.25f + u, 0.0f, 0.0f, dt);
}

void ActivateValueCameraController(ValueCameraController* obj, s32 value) { obj->value = value; }

void DeactivateValueCameraController(ValueCameraController* obj) { obj->value = 0; }

void ConvertPositionToWorld(BaseObject* self, Vec02* out);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void BuildBasisFromX(Vec02* x, Mat02* out);
void BuildBasisFromXAndZHint(const Vec02* x, const Vec02* hint, Mat02* out);
void SetCameraPlacement(Camera* self, Quad16* a, Quad16* b);

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
    TransformPointBetweenFrames((PlacedObject*)o, 0, (Vec02*)(o + 0x2E0), &pos);
    if (*(u8**)(o + 0x2D8) != 0) {
        Vu0::Q(v40) = Vu0::Sub(Vu0::Q(((PlacedObject*)*(u8**)(o + 0x2D8))->v140), Vu0::Q(pos));
        BuildBasisFromX(&v40, &basis);
    } else if (*(u8**)(o + 0x2D4) != 0) {
        ConvertPositionToWorld((BaseObject*)(*(u8**)(o + 0x2D4)), &v40);
        Vu0::Q(v50) = Vu0::Sub(Vu0::Q(v40), Vu0::Q(pos));
        BuildBasisFromX(&v50, &basis);
    } else {
        BuildBasisFromXAndZHint((const Vec02*)(o + 0x2F0), (const Vec02*)(o + 0x300), &basis);
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
    SetCameraPlacement(cam, (Quad16*)(o + 0x140), (Quad16*)&basis);
}
