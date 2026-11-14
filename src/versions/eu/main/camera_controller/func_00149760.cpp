// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two arcs' fields are 0x310 later (their screen element is longer), fade at 0x570, the
// target at 0x580 and the special object at 0x588 (US 0x260, 0x270, 0x278).
struct Arc_149760_eu {
    u8 pad000[0x570];
    s32 fade;
    u8 pad574[0x580 - 0x574];
    void* target;
    void* current;
    void* special;
};

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
        Arc_149760_eu* s;
        if (((Arc_149760_eu*)&D_002708E0)->fade == 1) {
            s = (Arc_149760_eu*)&D_002708E0;
        } else {
            s = (((Arc_149760_eu*)&D_00271558)->fade == 1) ? (Arc_149760_eu*)&D_00271558 : 0;
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
