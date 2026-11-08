// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 944/1036 (91.1%), checked 2026-11-08
// BYTES 0/0, checked 2026-11-07
// NEAR (2026-11-07, worker night-large1): the camera's placement toward a target with its angles
// blended by springs (flags bit 0), retail's code in every block but the blend's: there the
// differences of pitch and distance take f23/f22 for retail's f22/f23 (global allocation), and the
// final block (the five spring updates) is scheduled otherwise. The five updates in their natural
// order (f2B0..f2C0) leave 128 bytes off and dy/dt2 in f2/f11 (retail f7/f2); tools/permute.py's
// best order, kept here, leaves 92. Divisions written inside the updates are worse (105).
#include "common.h"
#include "shapes.h"
#include "collider.h"
#include "world.h"
#include "camera.h"
#include "pad_record.h"
#include "fpu.h"
#include "asm_func.h"
#include "vu0.h"
#include "ramp_profile.h"
#include "placed_object.h"
#include "switched_collider.h"

f32 WrapAngle(f32 a);
void UpdateCameraMatrices(Camera* self);

void ConvertOffsetToSpherical(const Vec02* a, const Vec02* b, f32* heading, f32* pitch, f32* dist);
void VectorToAngles(void* v, f32* yaw, f32* pitch);
void ComputeDirectionFromAngles(Vec02* out, f32 first, f32 second, f32 scale);
void BuildYawPitchMatrix(Mat02* out, f32 yaw, f32 pitch);

void func_00144BE8(Camera* self, s32 flags, void* c, s32 d, s32 e, f32 gain, f32 damp, f32 unused,
                   f32 yawOffset, f32 pitchOffset, f32 dt)
{
    const Vec02* target = (const Vec02*)c;
    const Vec02* focus = (const Vec02*)d;
    Vec02 dir;
    Vec02 pos;
    Mat02 m;
    f32 heading;
    f32 pitch;
    f32 dist;
    f32 curHeading;
    f32 curPitch;
    f32 curDist;
    f32 curYaw;
    f32 curTilt;
    f32 h;
    f32 p;
    f32 r;
    f32 y;
    f32 t;
    if (self->f224 != 0) {
        flags &= ~1;
    }
    ConvertOffsetToSpherical(target, focus, &heading, &pitch, &dist);
    f32 yaw = heading + 3.14159274f + yawOffset * self->f1C4 * self->f1E0 * 0.5f;
    f32 tilt = -pitch - pitchOffset * self->f1C4 * 0.5f;
    ConvertOffsetToSpherical((Vec02*)self->f40, (Vec02*)self->f2D0, &curHeading, &curPitch, &curDist);
    VectorToAngles(self->f80, &curYaw, &curTilt);
    if ((flags & 1) == 0) {
        y = yaw;
        t = tilt;
        h = heading;
        p = pitch;
        r = dist;
    } else {
        f32 dh = WrapAngle(heading - curHeading);
        f32 dp = pitch - curPitch;
        f32 dd = dist - curDist;
        f32 dy = WrapAngle(yaw - curYaw);
        f32 dt2 = tilt - curTilt;
        if (2.0f < __builtin_fabsf(dh) && 2.0f < __builtin_fabsf(dy) && dh * dy < 0.0f) {
            if (__builtin_fabsf(dy) < __builtin_fabsf(dh)) {
                if (dy < 0.0f) {
                    dy += 6.28318548f;
                } else {
                    dy -= 6.28318548f;
                }
            } else {
                if (dh < 0.0f) {
                    dh += 6.28318548f;
                } else {
                    dh -= 6.28318548f;
                }
            }
        }
        f32 s = 1.0f;
        f32 x = __builtin_fabsf(dh) * 0.666666687f;
        if (s < x) {
            s = x;
        }
        x = __builtin_fabsf(dp) * 1.33333337f;
        if (s < x) {
            s = x;
        }
        x = __builtin_fabsf(dd) * 0.00200000009f;
        if (s < x) {
            s = x;
        }
        x = __builtin_fabsf(dy) * 0.666666687f;
        if (s < x) {
            s = x;
        }
        x = __builtin_fabsf(dt2) * 1.33333337f;
        if (s < x) {
            s = x;
        }
        dt2 /= s;
        dy /= s;
        dh /= s;
        dp /= s;
        dd /= s;
        self->f2B8 += (dd * gain + self->f2B8 * damp) * dt;
        self->f2B4 += (dp * gain + self->f2B4 * damp) * dt;
        self->f2BC += (dy * gain + self->f2BC * damp) * dt;
        self->f2C0 += (dt2 * gain + self->f2C0 * damp) * dt;
        self->f2B0 += (dh * gain + self->f2B0 * damp) * dt;
        h = curHeading + self->f2B0 * dt;
        p = curPitch + self->f2B4 * dt;
        r = curDist + self->f2B8 * dt;
        y = curYaw + self->f2BC * dt;
        t = curTilt + self->f2C0 * dt;
    }
    ComputeDirectionFromAngles(&dir, h, p, r);
    Vu0::Q(pos) = Vu0::Add(Vu0::Q(*focus), Vu0::Q(dir));
    BuildYawPitchMatrix(&m, y, t);
    *(Vec02*)self->f40 = pos;
    *(Vec02*)self->f80 = m.r[0];
    *(Vec02*)self->f90 = m.r[1];
    *(Vec02*)self->fA0 = m.r[2];
    UpdateCameraMatrices(self);
    *(Vec02*)self->f2D0 = *focus;
}
