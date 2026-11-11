// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "gauge_mode_object.h"
#include "countdown_collider.h"
#include "globals.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "placed_object.h"
#include "asm_func.h"
#include "vu0.h"
#include "pad_record.h"
#include "game_progress.h"
#include "attachment.h"
#include "mul_rotation.h"
#include "memory_card.h"

// Classes 0x1B, 0x4A and 0x4B (the countdown). Its .rodata is func_0017ABE8's FLT_MAX literal
// at 0x24AFF4; its .data runs from 0x263AC0 to 0x263E34, in retail's order.

// The float func_0017AF38 reads as zero; the word after it is padding before the link table.
f32 D_00263AC0 = 0.0f;

ObjectLink g_modeColliderLinks[26] = {
    { 0, 0x453, 0x688 },
    { 0, 0x454, 0x694 },
    { 0, 0x455, 0x6A0 },
    { 0, 0x456, 0x6AC },
    { 0, 0x457, 0x6B8 },
    { 0, 0x458, 0x6C4 },
    { 0, 0x459, 0x6C8 },
    { 0, 0x45A, 0x6CC },
    { 0, 0x44E, 0x654 },
    { 4, 0x50, 0x67C },
    { 4, 0x45, 0x680 },
    { 4, 0x44C, 0x6E4 },
    { 4, 0x44D, 0x6E8 },
    { 0, 0x162, 0x58C },
    { 0, 0x163, 0x590 },
    { 4, 0x160, 0x584 },
    { 32, 0x18D, 0x604 },
    { 4, 0x45B, 0x674 },
    { 4, 0x45C, 0x678 },
    { 4, 0x465, 0x66C },
    { 4, 0x466, 0x670 },
    { 4, 0x45D, 0x650 },
    { 5, 0x461, 0x65C },
    { 5, 0x45F, 0x660 },
    { 5, 0x45E, 0x664 },
    { 5, 0x460, 0x668 }
};
f32 D_00263C00[4] = { 0.0f, -600.0f, 0.0f, 0.0f };
f32 D_00263C10[4] = { 0.0f, -300.0f, 0.0f, 0.0f };

f32 D_00263C20[4] = { 0.0f, 20.0f, 0.0f, 0.0f };
f32 D_00263C30[4] = { 0.0f, 10.0f, 0.0f, 0.0f };
f32 D_00263C40[3] = { 25.0f, 0.0f, 0.5f };
f32 D_00263C4C = 0.699999988f;
f32 D_00263C50[2] = { 0.150000006f, 0.0f };
f32 D_00263C58[4] = { 1.5f, 0.0f, 0.75f, 0.0f };
f32 D_00263C68[4] = { 20.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00263C78[2] = { -1.0f, 1.0f };
f32 D_00263C80[4] = { 10.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00263C90[4] = { -1.0f, 1.0f, 0.0f, 0.0f };
f32 D_00263CA0[4] = { 0.0f, -750.0f, 0.0f, 0.0f };
f32 D_00263CB0[4] = { 0.0f, -450.0f, 0.0f, 0.0f };
f32 D_00263CC0[4] = { 0.0f, 2.0f, -1.0f, 0.0f };
f32 D_00263CD0[4] = { 0.0f, 0.5f, 0.0f, 0.0f };
f32 D_00263CE0[4] = { 0.0f, 0.300000012f, 0.0f, 0.0f };
f32 D_00263CF0[4] = { 0.0f, 0.00100000005f, 0.0f, 0.0f };
f32 D_00263D00[2] = { 0.0f, 0.300000012f };
f32 D_00263D08[4] = { 30.0f, 0.0f, 0.5f, 0.0f };
f32 D_00263D18[6] = { 30.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f };

extern f32 g_gameClock[];
f32 D_00263D30[4] = { 1.0f, 0.0f, -0.75f, 0.0f };
f32 D_00263D40[6] = { 0.7f, 0.3f, 0.0f, 0.0f, 7e+02f, 6.5e+02f };

ObjectLink g_gaugeHolderLinks[13] = {
    { 0, 0x468, 0x584 },
    { 0, 0x469, 0x56C },
    { 0, 0x46A, 0x560 },
    { 0, 0x46B, 0x578 },
    { 0, 0x46C, 0x594 },
    { 0, 0x46D, 0x5A0 },
    { 0, 0x46E, 0x5AC },
    { 0, 0x46F, 0x5B8 },
    { 2, 0x470, 0x5C8 },
    { 2, 0x471, 0x5D4 },
    { 2, 0x472, 0x5E0 },
    { 2, 0x473, 0x5EC },
    { 2, 0x474, 0x5F8 }
};
f32 D_00263DF4 = 0.5f;
f32 D_00263DF8 = 1250.0f;
f32 D_00263DFC = 750.0f;
f32 D_00263E00 = 750.0f;

extern s32 D_00263E2C;
extern s32 g_timeoutFired;
f32 g_timeoutLimit = 3.0f;

ObjectLink g_countdownTable[3] = {
    { 0, 0x478, 0x55C },
    { 0, 0x479, 0x560 },
    { 0, 0x47A, 0x564 }
};
// size: s32, word load/store only
s32 D_00263E2C = 0;

extern s32 D_00263E2C;
s32 g_timeoutFired = 0;

void InitSwitchedCollider(void* self);

void InitModeCollider(ModeCollider* self)
{
    InitSwitchedCollider(self);
    self->f610 = -1;
}

struct Sub_1793F0 { u8 pad0[0xE0]; void* fE0; };

void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 a1, void* a2);
void SetFollowObjects(void* a, s32 b, s32 c);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);
void BuildCombinedBlendAnimation(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void SetBlendItemWeights(void* obj, s32 a1, s32 a2, void* a3);
void SetModeColliderMode(ModeCollider* self, s32 mode);
s32 FindAnimRecord(s32 key);

void StartModeCollider(ModeCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0x1A, g_modeColliderLinks);
    SetFollowObjects(self->f6E8, self->f680, self->f680);
    ((Sub_1793F0*)self->f650)->fE0 = self->f660;
    self->f658 = CreateStateWalker(self->f654, self, -1, 0);
    BuildCombinedBlendAnimation(self, 0xC, 5, &self->f684, 0, 0, 0, &self->f6C0);
    self->f684 = 1.0f;
    SetBlendItemWeights(self->f6C0, 0xC, 5, &self->f684);
    SetModeColliderMode(self, 2);
    T217D_BF0* base = &D_00270650;
    ((T217D_Float*)&base->f288)->v = 0.0f;
    base->icon = FindAnimRecord(0x36A);
}

ASM_FUNC(func_001794E0);

// NEAR: last call (func_001B9D10) loads a2 before $f12 is moved; retail moves $f12 first. Otherwise every instruction matches.

extern f32 D_00263C20[];
extern f32 D_00263C30[];
extern f32 D_00263C40[];

void StepCollider(ModeCollider* self, f32 t);
void ComputeModeColliderAnchors(ModeCollider* self, Vec02* a, Vec02* b);
void TransformStateToAncestorFrame(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void SteerColliderTowardPosition(ModeCollider* self, void* buf, f32 f, void* d1, void* d2, void* d3);
void TurnColliderTowardRotation(ModeCollider* self, f32 scale, void* out, void* data);

void StepModeCollider(ModeCollider* self, f32 f)
{
    Vec02 a;
    Vec02 b;
    s32 mode = self->f610;
    if (mode < 2) {
        goto single;
    }
    if (mode < 4) {
        goto path2;
    }
    if (mode == 4) {
        goto path3;
    }
single:
    StepCollider(self, f);
    return;
path2:
    ComputeModeColliderAnchors(self, &a, &b);
    b = D_00248D30;
    TransformStateToAncestorFrame(self->f668, 0, &a, 0, &b, 0);
    goto tail;
path3:
    a = *(Vec02*)&self->pos;
    b = D_00248D30;
tail:
    SteerColliderTowardPosition(self, &a, f, D_00263C20, &b, D_00263C30);
    TurnColliderTowardRotation(self, f, (u8*)self + 0x620, D_00263C40);
}

void MoveCollider(void* self, void* b);

void MoveModeCollider(ModeCollider* self)
{
    MoveCollider(self, 0);
    void (*fn)(BaseObject*) = self->desc->m12;
    if (fn != 0) fn(self);
}

extern T217D_BF0 D_00270650;
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
void ClearRootObjectStateBits(void* a, void* b, s32 c);

static inline f32 ClampBetween(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

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
    wx = d.y * -0.0016666667f;
    wy = d.z * -0.0033333334f;
    f32 k = D_00263C4C;
    f32 m = 1.0f - k;
    wx = k * wx + m * self->f704;
    wy = k * wy + m * self->f708;
    TransformPointBetweenFrames(0, self->f668, (u8*)self->f660 + 0x140, &tmp);
    if (tmp.x < 0.0f) {
        wx = -wx;
    }
    f32 sum = __builtin_fabsf(wx) + __builtin_fabsf(wy);
    if (1.0f < sum) {
        wx = wx / sum;
        wy = wy / sum;
    }
    self->f690 = ClampBetween(-wx, 0.0f, 1.0f);
    self->f69C = ClampBetween(wx, 0.0f, 1.0f);
    self->f6A8 = ClampBetween(-wy, 0.0f, 1.0f);
    self->f6B4 = ClampBetween(wy, 0.0f, 1.0f);
    self->f684 = 1.0f - self->f690 - self->f69C - self->f6A8 - self->f6B4;
    SetBlendItemWeights(self->f6C0, 0xC, 5, &self->f684);
}

// The record ModeCollider::f618 points at in mode 3: a value tested against zero and an object
// whose 0x34 is the mode's length.
struct ModeColliderLength {
    u8 pad00[0x34];
    f32 length;             // 0x34
};
struct ModeColliderSource {
    u8 pad00[0x08];
    ModeColliderLength* f08; // 0x08
    u8 pad0C[0x18 - 0x0C];
    f32 f18;                // 0x18: 0.0 ends the mode at once
};

// The three floats of a ramp profile ApproachValueWithRamp reads, copied whole.
struct RampProfile3 {
    f32 maxSpeed;
    f32 endSpeed;
    f32 rampTime;
};

s32 HasSpareCount(void);
void ClearPadPressedBits(PadRecord* pad, s32 bits);
void GetStateWalkerCurrentKey(void* walker, s32* out);
void SetStateWalkerTarget(void* walker, s32 key);
f32 ApproachValueWithRamp(f32 value, f32 target, f32 dt, void* profile, f32* speed);
void ProjectPointToCamera(Camera* camera, Vec02* pos, f32* out);
void BuildBasisFromXAndZHint(Vec02* x, const Vec02* z, Mat02* out);
void TransformRotationBetweenFrames(void* from, void* to, Mat02* in, Mat02* out);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
void ApproachRotationWithRamp(Mat02* rot, Mat02* target, void* profile, f32 dt, Mat02* out, s32 flags);
void HandleStepSequenceSkipButtons(ModeCollider* self, PadRecord* pad);
void ClearRootTries(void* self);

// The product a b of two rotations into out: a's rows loaded once, b's rows each rotated by
// them, each result row stored to its vector local and then to out's row.
static inline void RotationProductInto(Mat02* out, const Mat02& a, const Mat02& b)
{
    Vu0::Vec a0 = Vu0::Vec::Of(a.r[0]);
    Vu0::Vec a1 = Vu0::Vec::Of(a.r[1]);
    Vu0::Vec a2 = Vu0::Vec::Of(a.r[2]);
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(out->r[0]) = Vu0::Q(x) = Vu0::RotateRows(a0.q, a1.q, a2.q, Vu0::Q(b.r[0]));
    Vu0::Q(out->r[1]) = Vu0::Q(y) = Vu0::RotateRows(a0.q, a1.q, a2.q, Vu0::Q(b.r[1]));
    Vu0::Q(out->r[2]) = Vu0::Q(z) = Vu0::RotateRows(a0.q, a1.q, a2.q, Vu0::Q(b.r[2]));
}

// Every clamp returns its result (ClampBetween): the sum it is given is then a pseudo set once,
// which sched1's adjust_priority raises when it becomes ready, so the f700 sum is added before
// the bound's load and the bound takes the product's $f0 (docs/TOOLCHAIN.md, "sched1").
// The function's insn count at GCSE sets the hash table, and with it the order of the address
// spill slots: the last `to` stored through Vu0::Q keeps it in retail's range.
void ControlModeCollider(ModeCollider* self, f32 dt, PadRecord* pad)
{
    Mat02 mats[2];
    s32 i;
    Mat02 aim;
    s32 key;
    f32 hiX;
    f32 loX;
    f32 hiY;
    f32 loY;

    if (self->f610 == 3 && HasSpareCount() != 0) {
        ModeColliderSource* src = (ModeColliderSource*)self->f618;
        if (src == 0 || src->f18 == 0.0f) {
            self->desc05()->m50(self);
        } else {
            if (pad->flags & 0x40) {
                ClearPadPressedBits(pad, 0x40);
                self->f6DC = g_gameTime;
            }
            if (self->f6E0 != 0 && g_gameTime - self->f6DC < D_00263C50[0]) {
                self->desc05()->m50(self);
            }
        }
    }
    if (pad->keyA8 & 0x80) {
        GetStateWalkerCurrentKey(self->f658, &key);
        if (key >= 0x44F) {
            if (key < 0x451) {
                key = 0x451;
            } else if (key < 0x453) {
                key = 0x44F;
            }
        }
        SetStateWalkerTarget(self->f658, key);
    }
    switch (self->f610) {
    case 2:
    case 3:
    case 4: {
        Vec02 at;
        Vec02 pos;
        TransformPointBetweenFrames(0, self->f660, &self->f664->v140, &at);
        f32 u = (at.y - D_00263CA0[0]) / D_00263CA0[1];
        f32 v = (at.z - D_00263CB0[0]) / D_00263CB0[1];
        ApproachValueWithRamp(self->f6EC, u + D_00263C78[1], 0.0f, D_00263C58, &hiX);
        ApproachValueWithRamp(self->f6EC, u + D_00263C78[0], 0.0f, D_00263C58, &loX);
        ApproachValueWithRamp(self->f6F0, v + D_00263C78[1], 0.0f, D_00263C58, &hiY);
        ApproachValueWithRamp(self->f6F0, v + D_00263C78[0], 0.0f, D_00263C58, &loY);
        f32 stickY = pad->f44;
        if (g_saveData->f19EC & 0x800) {
            stickY = -stickY;
        }
        f32 tx;
        f32 ty;
        if (self->f610 == 2) {
            tx = loX + (pad->f40 + 1.0f) * ((hiX - loX) * 0.5f);
            ty = loY + (stickY + 1.0f) * ((hiY - loY) * 0.5f);
        } else {
            tx = (loX + hiX) * 0.5f;
            ty = (loY + hiY) * 0.5f;
        }
        self->f6F4 = ApproachValueWithRamp(self->f6F4, tx, dt, D_00263C68, 0);
        self->f6F8 = ApproachValueWithRamp(self->f6F8, ty, dt, D_00263C68, 0);
        self->f6EC = ClampBetween(self->f6EC + dt * self->f6F4, u + D_00263C78[0], u + D_00263C78[1]);
        f32 w = ClampBetween(self->f6F0 + dt * self->f6F8, v + D_00263C78[0], v + D_00263C78[1]);
        self->f6F0 = w;
        f32 h = self->f6EC;
        Vu0::Q(pos) = Vu0::FromFloats(at.x, D_00263CA0[0] + h * (D_00263CA0[1] + h * D_00263CA0[2]),
                                      D_00263CB0[0] + w * (D_00263CB0[1] + w * D_00263CB0[2]));
        TransformPointBetweenFrames(self->f660, 0, &pos, &pos);
        TransformPointBetweenFrames(0, self->f660, &pos, (u8*)self->f650 + 0xF0);
        ProjectPointToCamera(g_camera, &pos, D_00270650.aim);
        for (i = 0; i < 2; i++) {
            Vec02 dir;
            *(Vu0::Vec*)&dir = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(self->f674[i]->v140));
            BuildBasisFromXAndZHint(&dir, &g_unitZVector, &mats[i]);
            TransformRotationBetweenFrames(0, self->f674[i]->parent, &mats[i], &mats[i]);
        }
        ApproachValueWithRamp(self->f6FC, D_00263C90[1], 0.0f, D_00263C58, &hiX);
        ApproachValueWithRamp(self->f6FC, D_00263C90[0], 0.0f, D_00263C58, &loX);
        ApproachValueWithRamp(self->f700, D_00263C90[1], 0.0f, D_00263C58, &hiY);
        ApproachValueWithRamp(self->f700, D_00263C90[0], 0.0f, D_00263C58, &loY);
        RampProfile3 prof = *(RampProfile3*)D_00263C80;
        if (self->f610 == 2) {
            tx = loX + (pad->f40 + 1.0f) * ((hiX - loX) * 0.5f);
            ty = loY + (stickY + 1.0f) * ((hiY - loY) * 0.5f);
        } else {
            f32 k = (g_gameTime - self->f614) / ((ModeColliderSource*)self->f618)->f08->length;
            f32 s = D_00263CC0[0] + k * (D_00263CC0[1] + k * D_00263CC0[2]);
            tx = (loX + hiX) * 0.5f;
            ty = hiY;
            s = ClampBetween(s, g_unitRange.lo, g_unitRange.hi);
            prof.maxSpeed *= s;
            prof.endSpeed *= s;
        }
        self->f704 = ApproachValueWithRamp(self->f704, tx, dt, &prof, 0);
        self->f708 = ApproachValueWithRamp(self->f708, ty, dt, &prof, 0);
        self->f6FC = ClampBetween(self->f6FC + dt * self->f704, D_00263C90[0], D_00263C90[1]);
        self->f700 = ClampBetween(self->f700 + dt * self->f708, D_00263C90[0], D_00263C90[1]);

        Mat02 pitch;
        Mat02 yaw;
        Mat02 face;
        Vec02 to;
        Vec02 rel;
        Mat02 tilt;
        Vec02 axis;
        TransformPointBetweenFrames(0, self->f668, &((PlacedObject*)self->f660)->v140, &rel);
        f32 sx = pad->f40;
        if (rel.x < 0.0f) {
            sx = -sx;
        }
        BuildAxisAngleMatrix(&g_unitXVector, &pitch, D_00263CD0[0] + sx * (D_00263CD0[1] + sx * D_00263CD0[2]));
        f32 sy = pad->f44;
        BuildAxisAngleMatrix(&g_unitYVector, &yaw, D_00263CE0[0] + sy * (D_00263CE0[1] + sy * D_00263CE0[2]));
        *(Vu0::Vec*)&to = Vu0::Sub(Vu0::Vec::Of(((PlacedObject*)self->f660)->v140), Vu0::Vec::Of(self->v140));
        BuildBasisFromXAndZHint(&to, &g_unitZVector, &face);
        f32 speed = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(self->v150), Vu0::Q(self->v150))));
        f32 angle = ClampBetween(D_00263CF0[0] + speed * (D_00263CF0[1] + speed * D_00263CF0[2]), D_00263D00[0], D_00263D00[1]);
        Vu0::Vec n;
        n.q = Vu0::FromFloats(-self->v150.y, self->v150.x, 0.0f);
        *(Vu0::Vec*)&axis = n;
        *(Vu0::Vec*)&axis = Vu0::NormalizeOr(Vu0::Vec::Of(axis), Vu0::Vec::Of(g_unitXVector));
        BuildAxisAngleMatrix(&axis, &tilt, angle);
        Mat02 m3;
        Mat02 m2;
        Mat02 m1;
        RotationProductInto(&m1, tilt, face);
        RotationProductInto(&m2, m1, yaw);
        RotationProductInto(&m3, m2, pitch);
        self->m620 = m3;
        Vu0::Q(to) = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(self->f67C->v140)).q;
        BuildBasisFromXAndZHint(&to, &g_unitZVector, &aim);
        TransformRotationBetweenFrames(0, self->f67C->f224->p60, &aim, &aim);
        break;
    }
    default:
        BuildAxisAngleMatrix(&g_unitZVector, &self->m620, self->f61C);
        for (i = 0; i < 2; i++) {
            mats[i] = self->f674[i]->m1A0;
        }
        aim = g_identityMatrix;
        break;
    }
    Mat02 rot;
    for (i = 0; i < 2; i++) {
        ApproachRotationWithRamp(&self->f674[i]->rot, &mats[i], D_00263D08, dt, &rot, 0);
        self->f674[i]->desc02()->m1E(self->f674[i], &rot);
    }
    if (self->f67C->f1F0 == 0) {
        MulRotationRowsIndexed(&aim, aim, self->f67C->m1A0);
        ApproachRotationWithRamp(&self->f67C->rot, &aim, D_00263D18, dt, &rot, 0);
        self->f67C->desc02()->m1E(self->f67C, &rot);
    }
    HandleStepSequenceSkipButtons(self, pad);
    ClearRootTries(self);
}

void FinishSwitchedCollider(void* self);
void HandleSwitchedColliderActivation(void* a, s32 b);
void SetModeColliderMode(ModeCollider* self, s32 mode);

void FinishModeCollider(ModeCollider* self)
{
    FinishSwitchedCollider(self);
    SetModeColliderMode(self, 2);
}

void HandleModeColliderActivation(ModeCollider* self, s32 active)
{
    HandleSwitchedColliderActivation(self, active);
    if (active) {
        Vu0::Q(D_00270650.aim) = Vu0::FromFloats(0.0f, 0.0f, 2000.0f);
    } else {
        D_00270650.vt->m16(&D_00270650, 0);
        self->f6D0 = 0;
    }
}
extern Rgba4 D_002623E0;

f32 Cosine(f32 x);
void SetObjectTreeRecordValue(ModeCollider* o, u32 value);
void PrepareFadedObjectDraw(ModeCollider* o, void* s, void* out);

void ApplyModeColliderTint(ModeCollider* self, void* s, void* out)
{
    Rgba4 res;
    f32 t;
    f32 u;
    f32 a;
    f32 b;
    f32 k;
    f32 c1;
    f32 lo;
    f32 hi;
    u8 col[4];

    if ((self->flags & 0x100000000ULL) != 0) return;
    *(u32*)col = 0x800000A0;
    if (self->f6D0 != 0) {
        if (self->f610 != 3) {
            t = (g_gameClock[1] - self->f6D8) * 0.5f;
        } else {
            t = 0.0f;
        }
        u = Cosine((g_gameClock[1] - self->f6D4) * 10.0f);
        a = D_00263D30[0] + t * (D_00263D30[1] + t * D_00263D30[2]);
        hi = g_unitRange.hi;
        if (a < g_unitRange.lo) {
            c1 = g_unitRange.lo;
        } else if (hi < a) {
            c1 = hi;
        } else {
            c1 = a;
        }
        b = D_00263D40[0] + u * (D_00263D40[1] + u * D_00263D40[2]);
        lo = g_unitRange.lo;
        hi = g_unitRange.hi;
        if (b < lo) {
            b = lo;
        } else if (hi < b) {
            b = hi;
        }
        k = c1 * b;
        res.r = (s32)((1.0f - k) * D_002623E0.r + k * col[0]);
        res.g = (s32)((1.0f - k) * D_002623E0.g + k * col[1]);
        res.b = (s32)((1.0f - k) * D_002623E0.b + k * col[2]);
        res.a = D_002623E0.a;
    } else {
        res = D_002623E0;
    }
    SetObjectTreeRecordValue(self, *(u32*)&res);
    PrepareFadedObjectDraw(self, s, out);
}

// Matches retail's bytes (EXACT us and eu): the call result is tested directly with a goto to the zero return.

s32 IsPadSelectFlagHeld(World* world);
s32 IsModeColliderRequestBlocked(ModeCollider* self, s32 a1)
{
    if (a1 == 5) goto one;
    if (self->f610 == 3) goto one;
    if (self->f610 == 0) goto one;
    if (self->f610 == 4) goto one;
    if (self->f6D0 != 0) goto one;
    if (IsPadSelectFlagHeld(self->world) == 0) goto zero;
one:
    return 1;
zero:
    return 0;
}

// NEAR: the float store of f6D4 is scheduled before the li/sw of f6D0; retail stores f6D0 first

// What func_0017AA40 tells its listeners (kind 0x17): itself and the second word of its argument.
struct SenderValueMessage {
    void* self;
    s32 v;
};

s32 HasSpareCount(void);
void ComputeModeColliderAnchors(void* self, void* a, void* b);
void TransformStateToAncestorFrame(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void SetModeColliderMode(ModeCollider* self, s32 mode);

extern f32 g_gameTime;

s32 AcceptModeColliderRequest(ModeCollider* self, s32* arg)
{
    u8 bufA[16];
    u8 bufB[16];

    if (self->desc05()->m4B(self, *arg) != 0) {
        return 0;
    }
    if (HasSpareCount() != 0) {
        self->f6D0 = 1;
        self->f6D4 = *(f32*)&g_gameTime;
    }
    if (self->f6D0 != 0) {
        self->f704 = 0.0f;
        self->f708 = 3.0f;
        ComputeModeColliderAnchors(self, bufA, bufB);
        TransformStateToAncestorFrame(self->f668, 0, bufA, 0, bufB, 0);
        self->desc02()->m20(self, (Vec02*)bufB);
    }
    if (HasSpareCount() != 0) {
        SetModeColliderMode(self, 3);
    } else {
        SetModeColliderMode(self, 4);
    }
    {
        SenderValueMessage* m = (SenderValueMessage*)bufA;
        m->self = self;
        m->v = arg[1];
        self->desc->m0E(self, 0x17, bufA);
    }
    return 1;
}

void HandleSwitchedColliderNotification(void* self, s32 kind, MessageBody* rec);

void HandleModeColliderNotification(ModeCollider* self, s32 kind, MessageBody* rec)
{
    if (kind == 0x13 && rec->sourceId == self->f618) {
        switch (rec->code) {
        case 0x15E:
            self->f6E0 = 1;
            break;
        case 0x15F:
            self->f6E0 = 0;
            break;
        case 0x467:
            self->f70C = 1;
            break;
        }
    }
    HandleSwitchedColliderNotification(self, kind, rec);
}

s32 HasModeColliderAcceptedRequest(ModeCollider* self)
{
    return self->f6D0 != 0;
}

void ReplaceAnimationPlayer(void* a, void* b, s32 c, void* d, f32 e, f32 f);

void SetModeColliderMode(ModeCollider* self, s32 mode)
{
    s32 old = self->f610;
    if (mode == old) return;
    switch (old) {
    case 3:
    case 4:
        self->f6D8 = g_gameClock[1];
        break;
    }
    void* anim = 0;
    switch (mode) {
    case 2: {
        Vu0::Q(D_00270650.aim) = Vu0::FromFloats(0.0f, 0.0f, 2000.0f);
        *(Vec02*)&D_00270650.rateX = D_00248D30;
        D_00270650.vt->m16(&D_00270650, 2);
        anim = self->f6C0;
        break;
    }
    case 1:
        anim = self->f6C4;
        break;
    case 3:
        anim = self->f6C8;
        self->f6D8 = 3.4028235e+38f;
        break;
    case 4:
        anim = self->f6CC;
        self->f6D8 = 3.4028235e+38f;
        SetFollowObjects(self->f6E8, (s32)self, (s32)self);
        break;
    }
    self->f610 = mode;
    self->f614 = g_gameClock[1];
    ReplaceAnimationPlayer(anim, self, 1, &self->f618, 0.0f, 1.0f);
}

void ComputeModeColliderAnchors(void* self, void* a, void* b);
void TransformStateToAncestorFrame(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);

void PlaceModeColliderAtAnchor(ModeCollider* self)
{
    u8 bufA[16];
    u8 bufB[16];
    ComputeModeColliderAnchors(self, bufA, bufB);
    TransformStateToAncestorFrame(self->f668, 0, bufA, 0, bufB, 0);
    self->desc02()->m1D(self, (Vec02*)bufA);
    self->desc02()->m20(self, (Vec02*)bufB);
}

void InitCollider(void* self);

void InitGaugeModeObject(GaugeModeObject* self)
{
    InitCollider(self);
    self->mode = -1;
}

void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 a1, void* a2);
void BuildCombinedBlendAnimation(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void SetBlendItemWeights(void* obj, s32 a1, s32 a2, void* a3);
void SetGaugeModeObjectMode(GaugeModeObject* self, s32 a1);
s32 PlayGaugeModeObjectLoop(GaugeModeObject* self, s32 a1);

void StartGaugeModeObject(GaugeModeObject* self)
{
    StartPlacedObject(self);
    f32 one = 1.0f;
    ResolveObjectLinks(self, 13, g_gaugeHolderLinks);

    BuildCombinedBlendAnimation(self, 12, 4, self->grpA, 0, 0, 0, &self->mode0Handle);
    self->fA = one;
    SetBlendItemWeights(self->mode0Handle, 12, 4, self->grpA);

    BuildCombinedBlendAnimation(self, 12, 4, &self->fB, 0, 0, 0, &self->mode1Handle);
    self->fB = one;
    SetBlendItemWeights(self->mode1Handle, 12, 4, &self->fB);

    BuildCombinedBlendAnimation(self, 12, 5, &self->fC, 0, 0, 0, &self->loopHandle);
    self->fC = one;
    SetBlendItemWeights(self->loopHandle, 12, 5, &self->fC);

    SetGaugeModeObjectMode(self, 0);
    PlayGaugeModeObjectLoop(self, 1);
}

void UpdateCollider(GaugeModeObject* self);
void ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, Vec02* e, Vec02* f, f32 t);
f32 ComputeAngleBetweenVectors(const Vec02* a, const Vec02* b, Vec02* out);
void StopAnimationPlayer(void* p);

static inline f32 MaxF(f32 a, f32 b) { return a >? b; }
static inline f32 MinF(f32 a, f32 b) { return a <? b; }

// Mode 0 stores its weights unscaled and then scales them by 1 - D_00263AC0 in place: the
// stores before the scaling stay until flow2, so the remainder's product takes k's register.
void UpdateGaugeModeObject(GaugeModeObject* self)
{
    Vec02 v0;
    Vec02 local;
    Vec02 vel;
    Vec02 local2;
    Vec02 pos;
    Mat02 rot;

    UpdateCollider(self);
    if (self->mode >= 0) {
    if (self->mode < 2) {
        ComputeObjectMotionInFrame(self, 0, &self->v140, &v0, 0, 0, 0);
        Vu0::Q(local) = Vu0::RotateTransposed(self->m110, Vu0::Q(v0));
        ComputeObjectFrameAtTime(self, 0, &pos, &rot, &vel, 0, D_00263DF4);
        Vu0::Q(local2) = Vu0::RotateTransposed(rot, Vu0::Q(vel));
        if (self->mode == 0) {
            f32 c = ClampBetween(local2.x / D_00263DF8, -1.0f, 1.0f);
            f32 a = MaxF(0.0f, c);
            f32 b = MaxF(0.0f, -c);
            self->wA[0].w = a;
            self->wA[1].w = 1.0f - a - b;
            self->wA[2].w = b;
            self->wA[3].w = D_00263AC0;
            f32 k = 1.0f - D_00263AC0;
            self->wA[0].w *= k;
            self->wA[2].w *= k;
            self->wA[1].w *= k;
            SetBlendItemWeights(self->mode0Handle, 12, 4, self->wA);
        } else {
            f32 a = ClampBetween(local2.x / D_00263DFC, 0.0f, 1.0f);
            f32 b = ClampBetween(local2.y / D_00263E00, -1.0f, 1.0f);
            f32 s = 1.0f / MaxF(1.0f, __builtin_fabsf(a) + __builtin_fabsf(b));
            s = s * (1.0f - D_00263AC0);
            b *= s;
            a *= s;
            self->wB[1].w = a;
            self->wB[2].w = ClampBetween(b, 0.0f, 1.0f);
            self->wB[3].w = ClampBetween(-b, 0.0f, 1.0f);
            self->wB[0].w = 1.0f - a - __builtin_fabsf(b);
            SetBlendItemWeights(self->mode1Handle, 12, 4, self->wB);
        }
    }
    }
    PlacedObject* p = (PlacedObject*)GetActiveSwitchedCollider();
    if (p != 0) {
        TransformPointBetweenFrames(0, self, &p->v140, &v0);
        f32 t = ComputeAngleBetweenVectors(&g_unitXVector, &v0, &local);
        t = MinF(1.0f, t);
        f32 y = -t * local.y;
        f32 z = t * local.z;
        f32 zp = z >? 0.0f;
        f32 yp = y >? 0.0f;
        f32 zn = -z >? 0.0f;
        f32 yn = -y >? 0.0f;
        self->wC[3].w = zp;
        self->wC[1].w = yp;
        self->wC[4].w = zn;
        self->wC[2].w = yn;
        self->wC[0].w = 1.0f - yp - yn - zp - zn;
        SetBlendItemWeights(self->loopHandle, 12, 5, self->wC);
    }
    void* target = *(void**)self->targetPlayer;
    if (target != 0) {
        if (*(f32*)((u8*)target + 0x18) == 0.0f) {
            StopAnimationPlayer(target);
            *(void**)self->targetPlayer = 0;
        }
    }
}

extern s32 D_00270458;
extern s32 D_00270B54;
extern s32 D_002717CC;
s32 AreMenusAndFadeClear(void* self);

void ShowGaugeModeObjectBar(GaugeModeObject* self)
{
    s32 busy = 0;
    s32 mode = self->mode;
    if (mode < 2) {
        if (mode >= 0) {
            if (AreMenusAndFadeClear(self) != 0) {
                if (D_00270458 != 3 || (D_00270B54 == 0 && D_002717CC == 0)) busy = 1;
            }
        }
    }
    if (busy) g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    else g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
}

void DecrementGaugeCount(void* p);
void PlayGaugeModeObjectTarget(GaugeModeObject* self);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);

s32 HandleGaugeModeObjectEvent(GaugeModeObject* self, ObjectEvent* msg)
{
    if (msg->extraFlags & 0x10) {
        if (msg->id == self->f608) {
            DecrementGaugeCount(&g_gaugeBarElement);
            PlayGaugeModeObjectTarget(self);
            TriggerScriptEvent(self, 2, 0, 0);
        }
    }
    return 1;
}

extern f32 g_gameTime;

void SetWorldActiveFollower(void* a, void* b);
void ReplaceAnimationPlayer(void* a, void* b, s32 c, void* d, f32 e, f32 f);

void SetGaugeModeObjectMode(GaugeModeObject* self, s32 mode)
{
    void* x;
    if (mode == self->mode) {
        goto done;
    }
    x = 0;
    if (mode != 0) {
        if (mode == 1) {
            x = self->mode1Handle;
        }
    } else {
        x = self->mode0Handle;
    }
    if (mode >= 0) {
        if (mode < 2) {
            T217D_2E0* sys = &g_gaugeBarElement;
            sys->fillTarget = 1.0f;
            sys->f26C = sys->f260;
            sys->f270 = sys->f264;
            sys->fill = 0.0f;
            SetWorldActiveFollower(self->world, self);
        } else if (mode < 4) {
            T217D_2E0* sys = &g_gaugeBarElement;
            sys->vt->m15(sys);
            SetWorldActiveFollower(self->world, 0);
        }
    }
    (void)ReplaceAnimationPlayer(x, self, 1, self->modePlayer, 0.0f, 1.0f);
    *(s32*)((u8*)self + 0x550) = mode;
    self->modeTime = g_gameTime;
done:
    return;
}

void ReplaceAnimationPlayer(void* a, void* b, s32 c, void* d, f32 e, f32 f);

s32 PlayGaugeModeObjectLoop(GaugeModeObject* self, s32 flag)
{
    void* p = 0;
    if (flag != 0) {
        p = self->loopHandle;
    }
    ReplaceAnimationPlayer(p, self, 1, self->loopPlayer, 0.0f, 1.0f);
}

s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);

void SetGaugeModeObjectTarget(GaugeModeObject* self, s32 index)
{
    if (index == -1) {
        self->target = 0;
    } else {
        self->target = (void*)FindFirstObjectById(self->world, 0x101, index, self);
    }
}

void PlayGaugeModeObjectTarget(GaugeModeObject* self)
{
    ReplaceAnimationPlayer(self->target, self, 1, self->targetPlayer, 0.0f, 1.0f);
}

void InitCountdown(CountdownCollider* self)
{
    InitCollider(self);
    self->countdown = 0x10;
    D_00263E2C = -1;
    g_timeoutFired = 0;
}

void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, int n, void* table);

void StartCountdown(CountdownCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 3, g_countdownTable);
}
extern f32 g_gameTime;

void UpdateCollider(void* self);
void StopAnimationPlayer(void* p);
void SetCountdownState(CountdownCollider* self, s32 state);
void FadeOutAndQueueMovie(s32 n);

void UpdateCountdown(CountdownCollider* self)
{
    CountdownRecord* p;

    UpdateCollider(self);
    p = self->record;
    if (p != 0) {
        if (p->remaining == 0.0f) {
            StopAnimationPlayer(p);
            self->record = 0;
        }
    }
    if (D_00263E2C != -1) {
        SetCountdownState(self, D_00263E2C);
    }
    if (self->mode == 2) {
        if (g_timeoutLimit < g_gameTime - self->startTime) {
            if (g_timeoutFired == 0) {
                g_timeoutFired = 1;
                FadeOutAndQueueMovie(2);
            }
        }
    }
}

extern s32 D_00270458;
extern s32 D_00270B54;
extern s32 D_002717CC;
s32 AreMenusAndFadeClear(void* self);

void UpdateCountdownVisibility(CountdownCollider* self)
{
    s32 busy = 0;
    if (self->mode == 1 && AreMenusAndFadeClear(self) != 0) {
        if (D_00270458 != 3 || (D_00270B54 == 0 && D_002717CC == 0)) busy = 1;
    }
    if (busy) g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    else g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
}

// NEAR: 0x558 clamp uses movz with the operand order ours does not reproduce; msg->fC mask load goes to the other register

extern s32 D_00263E2C;

void DecrementGaugeCount(void* p);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void ReplaceAnimationPlayer(void* a, CountdownCollider* b, s32 c, void* d, f32 e, f32 f);
s32 HandleObjectEvent(void* self, ObjectEvent* msg);

s32 HandleCountdownObjectEvent(CountdownCollider* self, ObjectEvent* msg)
{
    void* p;
    if (msg->eventFlags & 0x20) {
        s32 n = self->countdown - 1;
        s32 pos = (0 < n);
        self->countdown = pos ? n : 0;
        DecrementGaugeCount(&g_gaugeBarElement);
        if (self->countdown == 0) {
            D_00263E2C = 2;
            p = 0;
        } else {
            s32 flags = msg->extraFlags;
            if (flags & 2) {
                if (g_player == 0) {
                    p = self->f55C;
                } else {
                    s32 t = g_player->f223C;
                    if (t == 4 || t == 6) {
                        p = self->f55C;
                    } else {
                        p = self->f560;
                    }
                }
            } else if (flags & 4) {
                p = self->f564;
            } else {
                p = self->f55C;
            }
        }
        ReplaceAnimationPlayer(p, self, 1, &self->record, 0.0f, 1.0f);
        msg->eventFlags &= ~0x20;
        TriggerScriptEvent(self, 2, 0, 0);
    }
    return HandleObjectEvent(self, msg);
}

void MarkLevelDone(s32 n);
void StartMemoryCardSave(MemoryCard* card);

void SetCountdownState(CountdownCollider* self, s32 state)
{
    if (state == self->mode) {
        return;
    }
    D_00263E2C = -1;
    switch (state) {
    case 1:
        {
            T217D_2E0* bar = &g_gaugeBarElement;
            bar->f26C = bar->f260 = 4;
            bar->f270 = bar->f264 = 4;
            bar->f268 = 0x10;
            bar->fillTarget = 1.0f;
            bar->fill = 0.0f;
            bar->changedAt = -1.0f;
        }
        SetWorldActiveFollower(self->world, self);
        break;
    case 2:
        MarkLevelDone(5);
        StartMemoryCardSave(&g_memoryCard);
        break;
    }
    self->mode = state;
    self->startTime = g_gameClock[1];
}
