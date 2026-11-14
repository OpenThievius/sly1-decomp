// SPDX-License-Identifier: AGPL-3.0-or-later
// From 0x1793C0 to 0x17B998: the mode collider, the gauge mode object and the countdown. Its name
// is ours, after the mode collider, which holds most of its code.
#include "common.h"
#include "switched_collider.h"
#include "world5_boss.h"
#include "world5_countdown.h"
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
#include "object_finder.h"
#include "functions/base_object.h"
#include "functions/blend_animation.h"
#include "functions/camera.h"
#include "functions/collider.h"
#include "functions/game_progress.h"
#include "functions/matrix.h"
#include "functions/memory_card.h"
#include "functions/pad_input.h"
#include "functions/path_follower.h"
#include "functions/placed_object.h"
#include "functions/player.h"
#include "functions/screen_element.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
#include "functions/world_contacts.h"

// Types other files define, named by the parameters of their functions declared here.
struct ScaledTransform;

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
f32 g_world5AimSmoothing = 0.699999988f;
f32 g_world5ButtonWindow[2] = { 0.150000006f, 0.0f };
f32 g_world5AimBoundsRamp[4] = { 1.5f, 0.0f, 0.75f, 0.0f };
f32 g_world5AimSpeedRamp[4] = { 20.0f, 0.0f, 0.100000001f, 0.0f };
f32 g_world5AimMargin[2] = { -1.0f, 1.0f };
f32 g_world5SteerRamp[4] = { 10.0f, 0.0f, 0.100000001f, 0.0f };
f32 g_world5SteerLimits[4] = { -1.0f, 1.0f, 0.0f, 0.0f };
f32 g_world5AimMapY[4] = { 0.0f, -750.0f, 0.0f, 0.0f };
f32 g_world5AimMapZ[4] = { 0.0f, -450.0f, 0.0f, 0.0f };
f32 g_world5SteerProgressCoefficients[4] = { 0.0f, 2.0f, -1.0f, 0.0f };
f32 g_world5PitchCoefficients[4] = { 0.0f, 0.5f, 0.0f, 0.0f };
f32 g_world5YawCoefficients[4] = { 0.0f, 0.300000012f, 0.0f, 0.0f };
f32 g_world5TiltCoefficients[4] = { 0.0f, 0.00100000005f, 0.0f, 0.0f };
f32 g_world5TiltLimits[2] = { 0.0f, 0.300000012f };
f32 g_world5PartRotationRamp[4] = { 30.0f, 0.0f, 0.5f, 0.0f };
f32 g_world5AimRotationRamp[6] = { 30.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f };

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

extern s32 g_world5CountdownRequest;
extern s32 g_timeoutFired;
f32 g_timeoutLimit = 3.0f;

ObjectLink g_countdownTable[3] = {
    { 0, 0x478, 0x55C },
    { 0, 0x479, 0x560 },
    { 0, 0x47A, 0x564 }
};
// size: s32, word load/store only
s32 g_world5CountdownRequest = 0;

extern s32 g_world5CountdownRequest;
s32 g_timeoutFired = 0;


// Initialiser of the mode collider: a switched collider with no mode yet (-1).
void InitWorld5ModeCollider(World5ModeCollider* self)
{
    InitSwitchedCollider(self);
    self->mode = -1;
}

// The object the link at 0x650 of a World5ModeCollider resolves to: it keeps the frame object of the
// collider (0x660) at 0xE0 and, at 0xF0, a position in that frame (StartWorld5ModeCollider, UpdateWorld5ModeCollider).
struct World5ModeColliderLinked {
    u8 pad0[0xE0];
    void* frame;            // 0xE0
};
typedef char check_World5ModeColliderLinked[sizeof(World5ModeColliderLinked) == 0xE4 ? 1 : -1];

struct StateGraph;
struct BlendAnimation;
struct Collider;
struct BlendAnimationView;
void SetWorld5ModeColliderMode(World5ModeCollider* self, s32 mode);
s32 FindAnimRecord(s32 key);

// Starts the world 5 mode collider: resolves its links, makes its follow objects and state
// walker, builds the five-weight blend animation (rest, minus and plus x and y) with the rest
// weight at 1, enters mode 2 and gives the spinning sprite element its icon (animation record
// 0x36A).
void StartWorld5ModeCollider(World5ModeCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0x1A, g_modeColliderLinks);
    SetFollowObjects((PlacedObject*)self->f6E8, self->f680, self->f680);
    ((World5ModeColliderLinked*)self->f650)->frame = self->aimFrame;
    self->stateWalker = CreateStateWalker((StateGraph*)self->stateGraph, self, -1, 0);
    BuildCombinedBlendAnimation(self, 0xC, 5, (u8*)&self->restWeight, 0, 0, 0, (BlendAnimation**)&self->weightBlend);
    self->restWeight = 1.0f;
    SetBlendItemWeights((BlendAnimationView*)self->weightBlend, 0xC, 5, &self->restWeight);
    SetWorld5ModeColliderMode(self, 2);
    AimReticle* base = &g_spinningSpriteElement;
    ((T217D_Float*)&base->alphaScale)->v = 0.0f;
    base->icon = FindAnimRecord(0x36A);
}

ASM_FUNC(func_001794E0);

// NEAR: last call (func_001B9D10) loads a2 before $f12 is moved; retail moves $f12 first. Otherwise every instruction matches.

extern f32 D_00263C20[];
extern f32 D_00263C30[];
extern f32 D_00263C40[];

void ComputeWorld5ModeColliderAnchors(World5ModeCollider* self, Vec4* a, Vec4* b);

// Per-frame forces of the world 5 mode collider: in modes 0 and 1 the ordinary collider step; in
// modes 2 and 3 it steers toward the anchor point (taken to the frame of its parent object), in
// mode 4 toward its own current position, and always turns toward its target rotation.
void StepWorld5ModeCollider(World5ModeCollider* self, f32 f)
{
    Vec4 a;
    Vec4 b;
    s32 mode = self->mode;
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
    ComputeWorld5ModeColliderAnchors(self, &a, &b);
    b = g_zeroVector;
    TransformStateToAncestorFrame((PlacedObject*)self->f668, 0, &a, 0, &b, 0);
    goto tail;
path3:
    a = *(Vec4*)&self->pos;
    b = g_zeroVector;
tail:
    SteerColliderTowardPosition(self, &a, D_00263C20, &b, D_00263C30, f);
    TurnColliderTowardRotation(self, f, &self->m620, D_00263C40);
}


// Moves the collider, then calls slot 0x12 of its descriptor if it has one.
void MoveWorld5ModeCollider(World5ModeCollider* self, f32 t, void* arg)
{
    MoveCollider(self, t, 0);
    void (*fn)(BaseObject*) = self->desc->m12;
    if (fn != 0) fn(self);
}

extern AimReticle g_spinningSpriteElement;
extern f32 g_gameTime;
extern s32 g_padSelectFlags;
struct OwnerMessage;

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

// Per-frame update of the world 5 mode collider: when a release is pending it hands control back
// to the player; fades out the pulse after 2 s; shows or hides the spinning sprite by whether
// this is the active collider; and turns its motion relative to the parent into the weights of
// its five-way blend animation.
void UpdateWorld5ModeCollider(World5ModeCollider* self, f32 dt)
{
    Vec4 a;
    Vec4 d;
    Vec4 tmp;
    f32 wx;
    f32 wy;
    UpdateSwitchedCollider(self, dt);
    if (self->releasePending != 0) {
        self->releasePending = 0;
        if (g_player != 0) {
            g_player->desc->m02(g_player);
            SetSwitchedColliderEnabled(g_player, 1);
            SetPlayerState(g_player, 2, 2);
            g_player->desc02()->m1F(g_player, (PlacedObject*)self->playerFrameObject);
            g_player->focusPoint = g_player->v140;
            ActivateSwitchedCollider(g_player);
            InitOwnerMessage((OwnerMessage*)&a, 5, self);
            g_player->desc05()->m4C(g_player, &a);
        }
        ((BaseObject*)self->playerFrameObject)->desc->m03((BaseObject*)self->playerFrameObject);
        self->flags538 = self->flags538 | (0x8000ULL << 27);
        ClearRootObjectStateBits(self->world, self, 7);
    }
    if (self->pulseActive != 0 && self->mode != 3) {
        if (g_gameTime - self->pulseFadeStart > 2.0f) {
            self->pulseActive = 0;
        }
    }
    if (self == GetActiveSwitchedCollider() && (g_padSelectFlags & 2) == 0) {
        g_spinningSpriteElement.vt->m16(&g_spinningSpriteElement, 2);
    } else {
        g_spinningSpriteElement.vt->m16(&g_spinningSpriteElement, 0);
    }
    ComputeObjectMotionInFrame((PlacedObject*)self->f668, 0, &self->pos, &a, 0, 0, 0);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(self->v150), Vu0::Q(a));
    TransformDirectionBetweenFrames(0, (PlacedObject*)self->f668, &d, &d);
    wx = d.y * -0.0016666667f;
    wy = d.z * -0.0033333334f;
    f32 k = g_world5AimSmoothing;
    f32 m = 1.0f - k;
    wx = k * wx + m * self->poseRateX;
    wy = k * wy + m * self->poseRateY;
    TransformPointBetweenFrames(0, (PlacedObject*)self->f668, &((PlacedObject*)self->aimFrame)->v140, &tmp);
    if (tmp.x < 0.0f) {
        wx = -wx;
    }
    f32 sum = __builtin_fabsf(wx) + __builtin_fabsf(wy);
    if (1.0f < sum) {
        wx = wx / sum;
        wy = wy / sum;
    }
    self->negXWeight = ClampBetween(-wx, 0.0f, 1.0f);
    self->posXWeight = ClampBetween(wx, 0.0f, 1.0f);
    self->negYWeight = ClampBetween(-wy, 0.0f, 1.0f);
    self->posYWeight = ClampBetween(wy, 0.0f, 1.0f);
    self->restWeight = 1.0f - self->negXWeight - self->posXWeight - self->negYWeight - self->posYWeight;
    SetBlendItemWeights((BlendAnimationView*)self->weightBlend, 0xC, 5, &self->restWeight);
}

// The record World5ModeCollider::modeAnimPlayer points at in mode 3: a value tested against zero and an object
// whose 0x34 is the mode's length.
struct World5ModeColliderLength {
    u8 pad00[0x34];
    f32 length;             // 0x34
};
struct World5ModeColliderSource {
    u8 pad00[0x08];
    World5ModeColliderLength* lengthRecord; // 0x08: the record whose word at 0x34 is the mode's length
    u8 pad0C[0x18 - 0x0C];
    f32 f18;                // 0x18: 0.0 ends the mode at once
};

// The three floats of a ramp profile ApproachValueWithRamp reads, copied whole.
struct RampProfile3 {
    f32 maxSpeed;
    f32 endSpeed;
    f32 rampTime;
};

struct RampProfile;
struct Vec4;
struct Mat3;
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
void ApproachRotationWithRamp(Mat3* from, Mat3* to, RampProfile* ramp, f32 limit, Mat3* outRot, Vec4* outSpin);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.

// The product a b of two rotations into out: a's rows loaded once, b's rows each rotated by
// them, each result row stored to its vector local and then to out's row.
static inline void RotationProductInto(Mat3* out, const Mat3& a, const Mat3& b)
{
    Vu0::Vec a0 = Vu0::Vec::Of(a.r[0]);
    Vu0::Vec a1 = Vu0::Vec::Of(a.r[1]);
    Vu0::Vec a2 = Vu0::Vec::Of(a.r[2]);
    Vec4 x;
    Vec4 y;
    Vec4 z;
    Vu0::Q(out->r[0]) = Vu0::Q(x) = Vu0::RotateRows(a0.q, a1.q, a2.q, Vu0::Q(b.r[0]));
    Vu0::Q(out->r[1]) = Vu0::Q(y) = Vu0::RotateRows(a0.q, a1.q, a2.q, Vu0::Q(b.r[1]));
    Vu0::Q(out->r[2]) = Vu0::Q(z) = Vu0::RotateRows(a0.q, a1.q, a2.q, Vu0::Q(b.r[2]));
}

// Every clamp returns its result (ClampBetween): the sum it is given is then a pseudo set once,
// which sched1's adjust_priority raises when it becomes ready, so the f700 sum is added before
// the bound's load and the bound takes the product's $f0 (docs/TOOLCHAIN.md, "sched1").
// The function's insn count at GCSE sets the hash table, and with it the order of the address
// spill slots: the last `to` stored through Vu0::Q keeps it in retail's range.
void ControlWorld5ModeCollider(World5ModeCollider* self, f32 dt, PadRecord* pad)
{
    Mat3 mats[2];
    s32 i;
    Mat3 aim;
    s32 key;
    f32 hiX;
    f32 loX;
    f32 hiY;
    f32 loY;

    if (self->mode == 3 && HasSpareCount() != 0) {
        World5ModeColliderSource* src = (World5ModeColliderSource*)self->modeAnimPlayer;
        if (src == 0 || src->f18 == 0.0f) {
            self->desc05()->m50(self);
        } else {
            if (pad->flags & 0x40) {
                ClearPadPressedBits(pad, 0x40);
                self->buttonPressTime = g_gameTime;
            }
            if (self->pressArmed != 0 && g_gameTime - self->buttonPressTime < g_world5ButtonWindow[0]) {
                self->desc05()->m50(self);
            }
        }
    }
    if (pad->buttons & 0x80) {
        GetStateWalkerCurrentKey((StateWalker*)self->stateWalker, &key);
        if (key >= 0x44F) {
            if (key < 0x451) {
                key = 0x451;
            } else if (key < 0x453) {
                key = 0x44F;
            }
        }
        SetStateWalkerTarget((StateWalker*)self->stateWalker, key);
    }
    switch (self->mode) {
    case 2:
    case 3:
    case 4: {
        Vec4 at;
        Vec4 pos;
        TransformPointBetweenFrames(0, (PlacedObject*)self->aimFrame, &self->aimTargetObject->v140, &at);
        f32 u = (at.y - g_world5AimMapY[0]) / g_world5AimMapY[1];
        f32 v = (at.z - g_world5AimMapZ[0]) / g_world5AimMapZ[1];
        ApproachValueWithRamp(self->aimX, u + g_world5AimMargin[1], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &hiX);
        ApproachValueWithRamp(self->aimX, u + g_world5AimMargin[0], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &loX);
        ApproachValueWithRamp(self->aimY, v + g_world5AimMargin[1], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &hiY);
        ApproachValueWithRamp(self->aimY, v + g_world5AimMargin[0], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &loY);
        f32 stickY = pad->stickY;
        if (g_saveData->optionFlags & 0x800) {
            stickY = -stickY;
        }
        f32 tx;
        f32 ty;
        if (self->mode == 2) {
            tx = loX + (pad->stickX + 1.0f) * ((hiX - loX) * 0.5f);
            ty = loY + (stickY + 1.0f) * ((hiY - loY) * 0.5f);
        } else {
            tx = (loX + hiX) * 0.5f;
            ty = (loY + hiY) * 0.5f;
        }
        self->aimRateX = ApproachValueWithRamp(self->aimRateX, tx, dt, (RampProfile*)g_world5AimSpeedRamp, 0);
        self->aimRateY = ApproachValueWithRamp(self->aimRateY, ty, dt, (RampProfile*)g_world5AimSpeedRamp, 0);
        self->aimX = ClampBetween(self->aimX + dt * self->aimRateX, u + g_world5AimMargin[0], u + g_world5AimMargin[1]);
        f32 w = ClampBetween(self->aimY + dt * self->aimRateY, v + g_world5AimMargin[0], v + g_world5AimMargin[1]);
        self->aimY = w;
        f32 h = self->aimX;
        Vu0::Q(pos) = Vu0::FromFloats(at.x, g_world5AimMapY[0] + h * (g_world5AimMapY[1] + h * g_world5AimMapY[2]),
                                      g_world5AimMapZ[0] + w * (g_world5AimMapZ[1] + w * g_world5AimMapZ[2]));
        TransformPointBetweenFrames((PlacedObject*)self->aimFrame, 0, &pos, &pos);
        TransformPointBetweenFrames(0, (PlacedObject*)self->aimFrame, &pos, &((PlacedObject*)self->f650)->rot.r[2]);
        ProjectPointToCamera(g_camera, &pos, g_spinningSpriteElement.aim);
        for (i = 0; i < 2; i++) {
            Vec4 dir;
            *(Vu0::Vec*)&dir = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(self->turnedParts[i]->v140));
            BuildBasisFromXAndZHint(&dir, &g_unitZVector, &mats[i]);
            TransformRotationBetweenFrames(0, (PlacedObject*)self->turnedParts[i]->parent, &mats[i], &mats[i]);
        }
        ApproachValueWithRamp(self->poseX, g_world5SteerLimits[1], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &hiX);
        ApproachValueWithRamp(self->poseX, g_world5SteerLimits[0], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &loX);
        ApproachValueWithRamp(self->poseY, g_world5SteerLimits[1], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &hiY);
        ApproachValueWithRamp(self->poseY, g_world5SteerLimits[0], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &loY);
        RampProfile3 prof = *(RampProfile3*)g_world5SteerRamp;
        if (self->mode == 2) {
            tx = loX + (pad->stickX + 1.0f) * ((hiX - loX) * 0.5f);
            ty = loY + (stickY + 1.0f) * ((hiY - loY) * 0.5f);
        } else {
            f32 k = (g_gameTime - self->modeStartTime) / ((World5ModeColliderSource*)self->modeAnimPlayer)->lengthRecord->length;
            f32 s = g_world5SteerProgressCoefficients[0] + k * (g_world5SteerProgressCoefficients[1] + k * g_world5SteerProgressCoefficients[2]);
            tx = (loX + hiX) * 0.5f;
            ty = hiY;
            s = ClampBetween(s, g_unitRange.lo, g_unitRange.hi);
            prof.maxSpeed *= s;
            prof.endSpeed *= s;
        }
        self->poseRateX = ApproachValueWithRamp(self->poseRateX, tx, dt, (RampProfile*)&prof, 0);
        self->poseRateY = ApproachValueWithRamp(self->poseRateY, ty, dt, (RampProfile*)&prof, 0);
        self->poseX = ClampBetween(self->poseX + dt * self->poseRateX, g_world5SteerLimits[0], g_world5SteerLimits[1]);
        self->poseY = ClampBetween(self->poseY + dt * self->poseRateY, g_world5SteerLimits[0], g_world5SteerLimits[1]);

        Mat3 pitch;
        Mat3 yaw;
        Mat3 face;
        Vec4 to;
        Vec4 rel;
        Mat3 tilt;
        Vec4 axis;
        TransformPointBetweenFrames(0, (PlacedObject*)self->f668, &((PlacedObject*)self->aimFrame)->v140, &rel);
        f32 sx = pad->stickX;
        if (rel.x < 0.0f) {
            sx = -sx;
        }
        BuildAxisAngleMatrix(&g_unitXVector, &pitch, g_world5PitchCoefficients[0] + sx * (g_world5PitchCoefficients[1] + sx * g_world5PitchCoefficients[2]));
        f32 sy = pad->stickY;
        BuildAxisAngleMatrix(&g_unitYVector, &yaw, g_world5YawCoefficients[0] + sy * (g_world5YawCoefficients[1] + sy * g_world5YawCoefficients[2]));
        *(Vu0::Vec*)&to = Vu0::Sub(Vu0::Vec::Of(((PlacedObject*)self->aimFrame)->v140), Vu0::Vec::Of(self->v140));
        BuildBasisFromXAndZHint(&to, &g_unitZVector, &face);
        f32 speed = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(self->v150), Vu0::Q(self->v150))));
        f32 angle = ClampBetween(g_world5TiltCoefficients[0] + speed * (g_world5TiltCoefficients[1] + speed * g_world5TiltCoefficients[2]), g_world5TiltLimits[0], g_world5TiltLimits[1]);
        Vu0::Vec n;
        n.q = Vu0::FromFloats(-self->v150.y, self->v150.x, 0.0f);
        *(Vu0::Vec*)&axis = n;
        *(Vu0::Vec*)&axis = Vu0::NormalizeOr(Vu0::Vec::Of(axis), Vu0::Vec::Of(g_unitXVector));
        BuildAxisAngleMatrix(&axis, &tilt, angle);
        Mat3 m3;
        Mat3 m2;
        Mat3 m1;
        RotationProductInto(&m1, tilt, face);
        RotationProductInto(&m2, m1, yaw);
        RotationProductInto(&m3, m2, pitch);
        self->m620 = m3;
        Vu0::Q(to) = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(self->thirdTurnedPart->v140)).q;
        BuildBasisFromXAndZHint(&to, &g_unitZVector, &aim);
        TransformRotationBetweenFrames(0, (PlacedObject*)self->thirdTurnedPart->linkRecord->p60, &aim, &aim);
        break;
    }
    default:
        BuildAxisAngleMatrix(&g_unitZVector, &self->m620, self->heading);
        for (i = 0; i < 2; i++) {
            mats[i] = self->turnedParts[i]->m1A0;
        }
        aim = g_identityMatrix;
        break;
    }
    Mat3 rot;
    for (i = 0; i < 2; i++) {
        ApproachRotationWithRamp(&self->turnedParts[i]->rot, &mats[i], (RampProfile*)g_world5PartRotationRamp, dt, &rot, 0);
        self->turnedParts[i]->desc02()->m1E(self->turnedParts[i], &rot);
    }
    if (self->thirdTurnedPart->orientationAttachment == 0) {
        MulRotationRowsIndexed(&aim, aim, self->thirdTurnedPart->m1A0);
        ApproachRotationWithRamp(&self->thirdTurnedPart->rot, &aim, (RampProfile*)g_world5AimRotationRamp, dt, &rot, 0);
        self->thirdTurnedPart->desc02()->m1E(self->thirdTurnedPart, &rot);
    }
    HandleStepSequenceSkipButtons(self, pad);
    ClearRootTries(self);
}

void SetWorld5ModeColliderMode(World5ModeCollider* self, s32 mode);

// Finishes the switched collider and puts it in mode 2.
void FinishWorld5ModeCollider(World5ModeCollider* self)
{
    FinishSwitchedCollider(self);
    SetWorld5ModeColliderMode(self, 2);
}

// Reacts to the mode collider becoming the active switched collider (or no longer being it): the
// spinning sprite is aimed at (0, 0, 2000) on activation, and hidden with the pulse cleared on
// deactivation.
void HandleWorld5ModeColliderActivation(World5ModeCollider* self, void* active)
{
    HandleSwitchedColliderActivation(self, active);
    if (active) {
        Vu0::Q(g_spinningSpriteElement.aim) = Vu0::FromFloats(0.0f, 0.0f, 2000.0f);
    } else {
        g_spinningSpriteElement.vt->m16(&g_spinningSpriteElement, 0);
        self->pulseActive = 0;
    }
}
extern Rgba4 g_defaultModelColor;

extern "C" f32 Cosine(f32 x);

// Draw-time tint of the world 5 mode collider: sets its object-tree colour to the base colour
// mixed toward a fixed colour by a pulse (a cosine of the time since the pulse started, faded by
// a curve), then applies the placed object's transform.
void ApplyWorld5ModeColliderTint(World5ModeCollider* self, void* s, void* out)
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
    if (self->pulseActive != 0) {
        if (self->mode != 3) {
            t = (g_gameClock[1] - self->pulseFadeStart) * 0.5f;
        } else {
            t = 0.0f;
        }
        u = Cosine((g_gameClock[1] - self->pulseStartTime) * 10.0f);
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
        res.r = (s32)((1.0f - k) * g_defaultModelColor.r + k * col[0]);
        res.g = (s32)((1.0f - k) * g_defaultModelColor.g + k * col[1]);
        res.b = (s32)((1.0f - k) * g_defaultModelColor.b + k * col[2]);
        res.a = g_defaultModelColor.a;
    } else {
        res = g_defaultModelColor;
    }
    SetObjectTreeRecordValue(self, *(u32*)&res);
    ApplyPlacedObjectTransform(self, (Camera*)s, (ScaledTransform*)out);
}

// Matches retail's bytes (EXACT us and eu): the call result is tested directly with a goto to the zero return.

s32 IsWorld5ModeColliderRequestBlocked(World5ModeCollider* self, s32 a1)
{
    if (a1 == 5) goto one;
    if (self->mode == 3) goto one;
    if (self->mode == 0) goto one;
    if (self->mode == 4) goto one;
    if (self->pulseActive != 0) goto one;
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

void ComputeWorld5ModeColliderAnchors(void* self, void* a, void* b);
void SetWorld5ModeColliderMode(World5ModeCollider* self, s32 mode);

extern f32 g_gameTime;

// The collider's answer to a request message: refuses when its own check (slot 75) says no;
// otherwise starts the pulse when a spare count is left, moves toward the anchor, enters mode 3
// (with a spare count) or 4 (without), and sends event 0x17. Gives 1 when accepted.
s32 AcceptWorld5ModeColliderRequest(World5ModeCollider* self, s32* arg)
{
    u8 bufA[16];
    u8 bufB[16];

    if (self->desc05()->m4B(self, *arg) != 0) {
        return 0;
    }
    if (HasSpareCount() != 0) {
        self->pulseActive = 1;
        self->pulseStartTime = *(f32*)&g_gameTime;
    }
    if (self->pulseActive != 0) {
        self->poseRateX = 0.0f;
        self->poseRateY = 3.0f;
        ComputeWorld5ModeColliderAnchors(self, bufA, bufB);
        TransformStateToAncestorFrame((PlacedObject*)self->f668, 0, (Vec4*)bufA, 0, (Vec4*)bufB, 0);
        self->desc02()->m20(self, (Vec4*)bufB);
    }
    if (HasSpareCount() != 0) {
        SetWorld5ModeColliderMode(self, 3);
    } else {
        SetWorld5ModeColliderMode(self, 4);
    }
    {
        SenderValueMessage* m = (SenderValueMessage*)bufA;
        m->self = self;
        m->v = arg[1];
        self->desc->m0E(self, 0x17, bufA);
    }
    return 1;
}


// Notification handler: for a kind 0x13 message from its mode animation player, codes 0x15E and
// 0x15F set and clear f6E0 and code 0x467 sets releasePending; then the switched collider's own
// handler runs.
void HandleWorld5ModeColliderNotification(World5ModeCollider* self, s32 kind, MessageBody* rec)
{
    if (kind == 0x13 && rec->sourceId == self->modeAnimPlayer) {
        switch (rec->code) {
        case 0x15E:
            self->pressArmed = 1;
            break;
        case 0x15F:
            self->pressArmed = 0;
            break;
        case 0x467:
            self->releasePending = 1;
            break;
        }
    }
    HandleSwitchedColliderNotification(self, kind, rec);
}

// Whether the mode collider's pulse is active.
s32 HasWorld5ModeColliderAcceptedRequest(World5ModeCollider* self)
{
    return self->pulseActive != 0;
}


// Changes the collider's mode (1 to 4) and starts the animation of the new mode (mode 2 the five-
// way blend); mode 2 resets and shows the spinning sprite, modes 3 and 4 hold the pulse, and mode
// 4 also sets its follow objects.
void SetWorld5ModeColliderMode(World5ModeCollider* self, s32 mode)
{
    s32 old = self->mode;
    if (mode == old) return;
    switch (old) {
    case 3:
    case 4:
        self->pulseFadeStart = g_gameClock[1];
        break;
    }
    void* anim = 0;
    switch (mode) {
    case 2: {
        Vu0::Q(g_spinningSpriteElement.aim) = Vu0::FromFloats(0.0f, 0.0f, 2000.0f);
        *(Vec4*)&g_spinningSpriteElement.rateX = g_zeroVector;
        g_spinningSpriteElement.vt->m16(&g_spinningSpriteElement, 2);
        anim = self->weightBlend;
        break;
    }
    case 1:
        anim = self->mode1Anim;
        break;
    case 3:
        anim = self->mode3Anim;
        self->pulseFadeStart = 3.4028235e+38f;
        break;
    case 4:
        anim = self->mode4Anim;
        self->pulseFadeStart = 3.4028235e+38f;
        SetFollowObjects((PlacedObject*)self->f6E8, self, self);
        break;
    }
    self->mode = mode;
    self->modeStartTime = g_gameClock[1];
    ReplaceAnimationPlayer((Animation*)anim, self, 1, (AnimationPlayer**)&self->modeAnimPlayer, 0.0f, 1.0f);
}

void ComputeWorld5ModeColliderAnchors(void* self, void* a, void* b);

// Computes the collider's two anchor points, converts them to the ancestor frame and passes them
// to descriptor slots 0x1D and 0x20 of the collider.
void PlaceWorld5ModeColliderAtAnchor(World5ModeCollider* self)
{
    u8 bufA[16];
    u8 bufB[16];
    ComputeWorld5ModeColliderAnchors(self, bufA, bufB);
    TransformStateToAncestorFrame((PlacedObject*)self->f668, 0, (Vec4*)bufA, 0, (Vec4*)bufB, 0);
    self->desc02()->m1D(self, (Vec4*)bufA);
    self->desc02()->m20(self, (Vec4*)bufB);
}


// Initialiser of the boss object: a collider with no mode yet (-1).
void InitWorld5Boss(World5Boss* self)
{
    InitCollider(self);
    self->mode = -1;
}

void SetWorld5BossMode(World5Boss* self, s32 a1);
s32 PlayWorld5BossLoop(World5Boss* self, s32 a1);

// Starts the world 5 boss: resolves its links, builds its three combined blend animations (mode
// 0, mode 1 and a loop) each at weight 1, enters mode 0 and starts the loop animation.
void StartWorld5Boss(World5Boss* self)
{
    StartPlacedObject(self);
    f32 one = 1.0f;
    ResolveObjectLinks(self, 13, g_gaugeHolderLinks);

    BuildCombinedBlendAnimation(self, 12, 4, self->grpA, 0, 0, 0, (BlendAnimation**)&self->mode0Handle);
    self->fA = one;
    SetBlendItemWeights((BlendAnimationView*)self->mode0Handle, 12, 4, self->grpA);

    BuildCombinedBlendAnimation(self, 12, 4, (u8*)&self->fB, 0, 0, 0, (BlendAnimation**)&self->mode1Handle);
    self->fB = one;
    SetBlendItemWeights((BlendAnimationView*)self->mode1Handle, 12, 4, &self->fB);

    BuildCombinedBlendAnimation(self, 12, 5, (u8*)&self->fC, 0, 0, 0, (BlendAnimation**)&self->loopHandle);
    self->fC = one;
    SetBlendItemWeights((BlendAnimationView*)self->loopHandle, 12, 5, &self->fC);

    SetWorld5BossMode(self, 0);
    PlayWorld5BossLoop(self, 1);
}


static inline f32 MaxF(f32 a, f32 b) { return a >? b; }
static inline f32 MinF(f32 a, f32 b) { return a <? b; }

// Mode 0 stores its weights unscaled and then scales them by 1 - D_00263AC0 in place: the
// stores before the scaling stay until flow2, so the remainder's product takes k's register.
void UpdateWorld5Boss(World5Boss* self, f32 dt)
{
    Vec4 v0;
    Vec4 local;
    Vec4 vel;
    Vec4 local2;
    Vec4 pos;
    Mat3 rot;

    UpdateCollider(self, dt);
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
            SetBlendItemWeights((BlendAnimationView*)self->mode0Handle, 12, 4, self->wA);
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
            SetBlendItemWeights((BlendAnimationView*)self->mode1Handle, 12, 4, self->wB);
        }
    }
    }
    PlacedObject* p = (PlacedObject*)GetActiveSwitchedCollider();
    if (p != 0) {
        TransformPointBetweenFrames(0, self, &p->v140, &v0);
        f32 t = ComputeAngleBetweenVectors((Vec4*)&g_unitXVector, &v0, &local);
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
        SetBlendItemWeights((BlendAnimationView*)self->loopHandle, 12, 5, self->wC);
    }
    void* target = *(void**)self->targetPlayer;
    if (target != 0) {
        if (((AnimationPlayer*)target)->speed == 0.0f) {
            StopAnimationPlayer((AnimationPlayer*)target);
            *(void**)self->targetPlayer = 0;
        }
    }
}

extern s32 g_displayMode;
extern s32 D_00270B54;
extern s32 D_002717CC;

// Shows the shared gauge bar while the boss object is in mode 0 or 1 and nothing else (menus, a
// fade) is covering the screen, otherwise hides it.
void ShowWorld5BossBar(World5Boss* self)
{
    s32 busy = 0;
    s32 mode = self->mode;
    if (mode < 2) {
        if (mode >= 0) {
            if (AreMenusAndFadeClear() != 0) {
                if (g_displayMode != 3 || (D_00270B54 == 0 && D_002717CC == 0)) busy = 1;
            }
        }
    }
    if (busy) g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    else g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
}

void PlayWorld5BossTarget(World5Boss* self);

// Event handler of the boss object: an event with flag 0x10 and the boss's own id takes one
// away from the gauge count, plays the target's animation and sends script event 2. Always gives
// 1.
s32 HandleWorld5BossEvent(World5Boss* self, ObjectEvent* msg)
{
    if (msg->extraFlags & 0x10) {
        if (msg->id == self->eventId) {
            DecrementGaugeCount(&g_gaugeBarElement);
            PlayWorld5BossTarget(self);
            TriggerScriptEvent(self, 2, 0, 0);
        }
    }
    return 1;
}

extern f32 g_gameTime;


// Changes the boss's mode (0 to 3) and starts the animation of the mode: modes 0 and 1 reset and
// show the gauge bar and make the boss the world's active follower, modes 2 and 3 hide the gauge
// and release the follower.
void SetWorld5BossMode(World5Boss* self, s32 mode)
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
            GaugeBar* sys = &g_gaugeBarElement;
            sys->fillTarget = 1.0f;
            sys->segmentsLeft = sys->segmentCount;
            sys->cellsLeft = sys->cellsPerSegment;
            sys->fill = 0.0f;
            SetWorldActiveFollower(self->world, self);
        } else if (mode < 4) {
            GaugeBar* sys = &g_gaugeBarElement;
            sys->vt->m15(sys);
            SetWorldActiveFollower(self->world, 0);
        }
    }
    (void)ReplaceAnimationPlayer((Animation*)x, self, 1, (AnimationPlayer**)self->modePlayer, 0.0f, 1.0f);
    // a field access here changes retail's code
    *(s32*)((u8*)self + 0x550) = mode;
    self->modeTime = g_gameTime;
done:
    return;
}


// Starts the boss's looping animation (or replaces it by none when flag is 0) on the loop player.
s32 PlayWorld5BossLoop(World5Boss* self, s32 flag)
{
    void* p = 0;
    if (flag != 0) {
        p = self->loopHandle;
    }
    ReplaceAnimationPlayer((Animation*)p, self, 1, (AnimationPlayer**)self->loopPlayer, 0.0f, 1.0f);
}


// Sets the object the boss plays animations on: the object found by id index, or none for -1.
void SetWorld5BossTarget(World5Boss* self, s32 index)
{
    if (index == -1) {
        self->target = 0;
    } else {
        self->target = (void*)FindFirstObjectById(self->world, 0x101, index, self);
    }
}

// Plays the target's animation on the target player.
void PlayWorld5BossTarget(World5Boss* self)
{
    ReplaceAnimationPlayer((Animation*)self->target, self, 1, (AnimationPlayer**)self->targetPlayer, 0.0f, 1.0f);
}

// Initialiser of the countdown: a count of 0x10, no pending request and the timeout not fired.
void InitWorld5Countdown(World5Countdown* self)
{
    InitCollider(self);
    self->countdown = 0x10;
    g_world5CountdownRequest = -1;
    g_timeoutFired = 0;
}


// Start of the countdown: the placed object's start, then resolves its three links.
void StartWorld5Countdown(World5Countdown* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 3, g_countdownTable);
}
extern f32 g_gameTime;

void SetWorld5CountdownState(World5Countdown* self, s32 state);

// Per-frame update of the countdown: ends its animation record once it has run out, applies a
// pending mode request (g_world5CountdownRequest), and in mode 2 queues a movie (after a fade)
// once g_timeoutLimit seconds have passed.
void UpdateWorld5Countdown(World5Countdown* self, f32 dt)
{
    World5CountdownRecord* p;

    UpdateCollider(self, dt);
    p = self->record;
    if (p != 0) {
        if (p->remaining == 0.0f) {
            StopAnimationPlayer((AnimationPlayer*)p);
            self->record = 0;
        }
    }
    if (g_world5CountdownRequest != -1) {
        SetWorld5CountdownState(self, g_world5CountdownRequest);
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

extern s32 g_displayMode;
extern s32 D_00270B54;
extern s32 D_002717CC;

// Same as ShowWorld5BossBar for the countdown object, which shows the bar in mode 1 only.
void UpdateWorld5CountdownVisibility(World5Countdown* self)
{
    s32 busy = 0;
    if (self->mode == 1 && AreMenusAndFadeClear() != 0) {
        if (g_displayMode != 3 || (D_00270B54 == 0 && D_002717CC == 0)) busy = 1;
    }
    if (busy) g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    else g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
}

// NEAR: 0x558 clamp uses movz with the operand order ours does not reproduce; msg->fC mask load goes to the other register

extern s32 g_world5CountdownRequest;


// Object event handler of the world 5 countdown object: on an event with flag 0x20 it decrements
// the countdown and the gauge, sets the world's request to 2 when it reaches 0, otherwise picks
// one of three animations by the event's extra flags and the player's aim mode, plays it and
// sends script event 2; then handles the event as an object.
s32 HandleWorld5CountdownObjectEvent(World5Countdown* self, ObjectEvent* msg)
{
    void* p;
    if (msg->eventFlags & 0x20) {
        s32 n = self->countdown - 1;
        s32 pos = (0 < n);
        self->countdown = pos ? n : 0;
        DecrementGaugeCount(&g_gaugeBarElement);
        if (self->countdown == 0) {
            g_world5CountdownRequest = 2;
            p = 0;
        } else {
            s32 flags = msg->extraFlags;
            if (flags & 2) {
                if (g_player == 0) {
                    p = self->f55C;
                } else {
                    s32 t = g_player->aimMode;
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
        ReplaceAnimationPlayer((Animation*)p, self, 1, (AnimationPlayer**)&self->record, 0.0f, 1.0f);
        msg->eventFlags &= ~0x20;
        TriggerScriptEvent(self, 2, 0, 0);
    }
    return HandleObjectEvent(self, msg);
}


// Switches the countdown object's mode. Mode 1 sets up the shared gauge bar (4 segments of 4
// cells, 0x10 in all, empty) and makes the object the world's active follower; mode 2 marks level
// 5 done and starts a memory card save. Records the time of the change.
void SetWorld5CountdownState(World5Countdown* self, s32 state)
{
    if (state == self->mode) {
        return;
    }
    g_world5CountdownRequest = -1;
    switch (state) {
    case 1:
        {
            GaugeBar* bar = &g_gaugeBarElement;
            bar->segmentsLeft = bar->segmentCount = 4;
            bar->cellsLeft = bar->cellsPerSegment = 4;
            bar->cellCount = 0x10;
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
