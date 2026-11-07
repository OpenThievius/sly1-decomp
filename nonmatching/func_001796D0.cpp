// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 916/920, checked 2026-11-07
// NEAR: the whole function is right up to the four clamps of the blend weights: retail stores the first clamp (f690) before it compares the next, jumps the second (f69C, a zero-initialised value) past its body with a branch-likely whose delay slot is the next clamp's first neg.s, and writes the second store after that neg.s; the third and fourth clamps differ in where their stores sit. Ours stores each clamp in the delay slot of its own branch. Same size and every other instruction match.
#include "common.h"
#include "switched_collider.h"
#include "globals.h"
#include "screen_element.h"
#include "placed_object.h"
#include "vu0.h"

extern T217D_BF0 D_00270650;
extern f32 D_00263C4C;
extern f32 g_gameTime;
extern s32 g_padSelectFlags;
void UpdateSwitchedCollider(void* self);
void SetSwitchedColliderEnabled(void* self, s32 on);
void SetPlayerState(void* self, s32 a, s32 b);
void ActivateSwitchedCollider(void* self);
void InitOwnerMessage(void* out, s32 mode, void* owner);
void* GetActiveSwitchedCollider();
void ComputeObjectMotionInFrame(void* obj, s32 b, void* c, void* out, s32 d, s32 e, s32 f);
void TransformDirectionBetweenFrames(void* a, void* b, void* c, void* d);
void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);
void SetBlendItemWeights(void* ctx, s32 n, s32 m, f32* out);
void ClearRootObjectStateBits(void* a, void* b, s32 c);

void UpdateModeCollider(ModeCollider* self)
{
    Vec02 a;
    Vec02 d;
    Vec02 tmp;
    f32 wx;
    f32 wy;
    UpdateSwitchedCollider(self);
    if (self->f70C != 0) {
        self->f70C = 0;
        if (g_player != 0) {
            g_player->desc->m02(g_player);
            SetSwitchedColliderEnabled(g_player, 1);
            SetPlayerState(g_player, 2, 2);
            g_player->desc02()->m1F(g_player, (PlacedObject*)self->f6E4);
            g_player->v560 = g_player->v140;
            ActivateSwitchedCollider(g_player);
            InitOwnerMessage(&a, 5, self);
            g_player->desc05()->m4C(g_player, &a);
        }
        ((BaseObject*)self->f6E4)->desc->m03((BaseObject*)self->f6E4);
        self->flags538 = self->flags538 | (0x8000ULL << 27);
        ClearRootObjectStateBits(self->world, self, 7);
    }
    if (self->f6D0 != 0 && self->f610 != 3) {
        if (g_gameTime - self->f6D8 > 2.0f) {
            self->f6D0 = 0;
        }
    }
    if (self == GetActiveSwitchedCollider() && (g_padSelectFlags & 2) == 0) {
        D_00270650.vt->m16(&D_00270650, 2);
    } else {
        D_00270650.vt->m16(&D_00270650, 0);
    }
    ComputeObjectMotionInFrame(self->f668, 0, (u8*)self + 0x100, &a, 0, 0, 0);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(self->v150), Vu0::Q(a));
    TransformDirectionBetweenFrames(0, self->f668, &d, &d);
    f32 x = d.y * -0.0016666667f;
    f32 y = d.z * -0.0033333334f;
    f32 k = D_00263C4C;
    f32 m = 1.0f - k;
    wx = k * x + m * *(f32*)&self->f704;
    wy = k * y + m * self->f708;
    TransformPointBetweenFrames(0, self->f668, (u8*)self->f660 + 0x140, &tmp);
    if (tmp.x < 0.0f) {
        wx = -wx;
    }
    f32 sum = __builtin_fabsf(wx) + __builtin_fabsf(wy);
    if (1.0f < sum) {
        wx = wx / sum;
        wy = wy / sum;
    }
    f32 c1 = -wx;
    if (c1 < 0.0f) {
        c1 = 0.0f;
    } else if (1.0f < c1) {
        c1 = 1.0f;
    }
    self->f690 = c1;
    f32 c2;
    if (wx < 0.0f) {
        c2 = 0.0f;
    } else if (1.0f < wx) {
        c2 = 1.0f;
    } else {
        c2 = wx;
    }
    self->f69C = c2;
    f32 c3 = -wy;
    if (c3 < 0.0f) {
        c3 = 0.0f;
    } else if (1.0f < c3) {
        c3 = 1.0f;
    }
    self->f6A8 = c3;
    f32 c4 = 0.0f;
    if (!(wy < 0.0f)) {
        c4 = wy;
        if (1.0f < wy) {
            c4 = 1.0f;
        }
    }
    self->f6B4 = c4;
    self->f684 = 1.0f - self->f690 - self->f69C - self->f6A8 - self->f6B4;
    SetBlendItemWeights(self->f6C0, 0xC, 5, &self->f684);
}
