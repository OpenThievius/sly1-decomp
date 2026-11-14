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
            ComputeObjectFrameAtTime((PlacedObject*)obj, 0, &pos, 0, 0, 0, 0.1f);
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
            self->g1C = ApproachValueWithRamp(self->g1C, 0.0f, dt, (RampProfile*)D_00261C60, 0);
            self->g18 = ClampFloat(self->g18 + self->g1C * dt, 0.0f, 1.0f);
        }
        break;
    }
    case 3: {
        f32 v = ClampFloat(ApproachValueWithRamp(self->g18, D_002704F8, dt, (RampProfile*)D_00261C70, 0), 0.0f, 1.0f);
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
            SetSoundRecordPitch((PlayingSound*)self->p48, ClampFloat(__builtin_fabsf(self->g1C), -1.0f, 1.0f));
            SetSoundRecordVolume((PlayingSound*)self->p48, ClampFloat(__builtin_fabsf(self->g1C) * 0.5f + 0.5f, 0.0f, 1.0f));
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
        self->g0C = ApproachValueWithRamp(self->g0C, zero, dt, (RampProfile*)D_00261C80, 0);
        self->g14 = ApproachValueWithRamp(self->g14, zero, dt, (RampProfile*)D_00261C80, 0);
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
            ProjectPointToCamera(*(Camera**)g_camera, &ahead, (f32*)&screen);
            push.x = pad->f40;
            if (g_saveData->f19EC & 0x400) {
                push.y = pad->f44;
            } else {
                push.y = -pad->f44;
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
        if (self->f5C != 0) {
            ConvertPositionToWorld((BaseObject*)self->f5C, (Vec02*)&target);
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
        f32 z = cam->f1C4;
        f32 a = heading + 3.1415927f + sx * z * cam->f1E0 * 0.5f;
        f32 b = -tilt - sy * z * 0.5f;
        Vec02 off;
        ComputeDirectionFromAngles((Vec3*)&off, heading, tilt, length);
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
    UpdateOrbitCameraPlacement(cam, flag, (const Vec02*)&eye, (const Vec02*)&target, 0, Blend(blend, 20.0f, far), Blend(blend, -7.0f, rise),
                  Blend(blend, 1.0f, 0.25f), 0.0f, ease, dt);
}
