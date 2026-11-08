// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 936/972 (96.3%), checked 2026-11-07
// NEAR: all the calls and the control flow are retail's, the frame included (k is one 16-byte local the weight and the axis share); left: the order of the three row loads of the rotation (retail r0, r1, r2; here r2 first), the weight in vf5 (retail keeps it alive over the rows; here it takes the free vf2) and the temps of the call after it. Needs ModeWalker::fBC4, vBE0 and fBFC (include/switched_collider.h).
#include "common.h"
#include "switched_collider.h"
#include "screen_element.h"
#include "state_walker.h"
#include "globals.h"
#include "vu0.h"
#include "shapes.h"
extern f32 D_00264128;
extern f32 D_00264130[3];
extern f32 D_0026413C;
extern T217D_BF0 D_00270650;
extern f32 g_gameTime;
extern u8 D_002708C0[];
void SetStateWalkerTarget(void* p, s32 n);
void TeleportStateWalker(void* p, s32 n);

struct PadBits {
    u8 pad00[0xA8];
    u16 a8;
    u16 aa;
};
extern u8 D_00262D38[];
void ControlPathFollower(PathFollower* self, PadBits* pad, f32 dt);
void GetStateWalkerCurrentKey(void* walker, s32* out);
void GetStateWalkerTargetKey(void* walker, s32* out);
void ClearPadPressedBits(PadBits* pad, s32 mask);
void UnprojectCameraPoint(void* camera, void* a, Vec02* out);
void BuildBasisFromXAndZHint(void* x, const Vec02* z, void* out);
void TransformRotationBetweenFrames(void* from, void* to, Mat02* in, Mat02* out);
void TransformDirectionBetweenFrames(void* from, void* to, Vec02* in, void* out);
void ApproachRotationWithRamp(f32 dt, void* state, Mat02* target, f32* profile, Mat02* out, s32 zero);
void MultiplyMatrices3x3(void* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, Vec02* axis);
void BuildAxisAngleMatrix(const Vec02* axis, void* out, f32 angle);
void ClearRootTries(void* self);
void func_00181ED0(T217D_BF0* element, PadBits* pad);
typedef void (*FrameFn)(void* self, Mat02* m);

void func_00181078(ModeWalker* self, PadBits* pad, f32 dt)
{
    s32 cur;
    s32 target;
    Mat02 m;
    Vec02 pos;
    Vec02 d;
    Vec02 k;
    Mat02 m2;
    f32 angle;
    ControlPathFollower(self, pad, dt);
    GetStateWalkerCurrentKey(self->fBBC, &cur);
    GetStateWalkerTargetKey(self->fBBC, &target);
    switch (self->fBB0) {
    case 1:
        if ((pad->a8 & 0x80) != 0) {
            SetStateWalkerTarget(self->fBBC, 0x360);
        } else {
            SetStateWalkerTarget(self->fBBC, 0x35F);
        }
        break;
    case 2:
        if (cur == 0x35F) {
            self->desc05()->m50(self);
        } else {
            if ((pad->aa & 0x40) != 0) {
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
                pad = (PadBits*)D_00262D38;
            }
            func_00181ED0(&D_00270650, pad);
            Vu0::Q(m.r[2]) = Vu0::Q(self->m110.r[2]);
            u128 n = Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(m.r[2]), Vu0::Q(((Vec02*)((u8*)g_camera + 0x80))[0])), *(u128*)&self->m110.r[1]);
            Vu0::Q(m.r[1]) = n;
            Vu0::Q(m.r[0]) = Vu0::Cross(n, Vu0::Q(m.r[2]));
            TransformRotationBetweenFrames(0, *(void**)((u8*)self->fBC4 + 0x18), &m, &m);
            ApproachRotationWithRamp(dt, (u8*)self->fBC4 + 0xD0, &m, D_00264130, &m, 0);
            (*(FrameFn**)self->fBC4)[34](self->fBC4, &m);
            UnprojectCameraPoint(g_camera, D_002708C0, &pos);
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(((PlacedObject*)self->fBC0)->v140));
            BuildBasisFromXAndZHint(&d, &g_unitZVector, &m);
            TransformRotationBetweenFrames(0, *(void**)((u8*)self->fBC0 + 0x18), &m, &m);
            (*(FrameFn**)self->fBC0)[34](self->fBC0, &m);
            u128 v = Vu0::Q(self->vBE0);
            u128 w = Vu0::FromFloatAt(D_0026413C);
            u128 r0 = Vu0::Q(m.r[0]);
            u128 r1 = Vu0::Q(m.r[1]);
            u128 r2 = Vu0::Q(m.r[2]);
            u128 rot = Vu0::RotateRows(r0, r1, r2, v);
            Vu0::Set(k, w);
            Vu0::Q(d) = Vu0::MulX(Vu0::Sub(rot, v), w);
            TransformDirectionBetweenFrames(*(void**)((u8*)self->fBC0 + 0x18), *(void**)((u8*)self->fBCC + 0x18), &d, (u8*)self->fBD0 + 0x20);
            MultiplyMatrices3x3((u8*)self->fBC0 + 0x1A0, &m, &m2);
            TransformRotationBetweenFrames(*(void**)((u8*)self->fBC0 + 0x18), *(void**)((u8*)self->fBCC + 0x18), &m2, &m2);
            MatrixToAxisAngle(&m2, &angle, &k);
            BuildAxisAngleMatrix(&k, (u8*)self->fBD0 + 0x40, D_0026413C * angle);
            ClearRootTries(self);
        }
    }
}
