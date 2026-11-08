// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 678/756 (89.7%), checked 2026-11-07
// NEAR: the frame, the three branches, the calls and the weights are retail's; left: the allocation (retail keeps the follower in s3 and &b in s4; here the other way round, which moves every later register), the branch that follows tune->f328 (retail loads tune->f324 in its delay slot) and the order of the weights' stack stores. Needs nothing from the headers.
#include "common.h"
#include "switched_collider.h"
#include "target_follower.h"
#include "globals.h"
#include "vu0.h"
#include "placed_object.h"
#include "zone_collider.h"
extern f32 D_00262A28[2];
extern f32 g_gameTime;
extern const Vec02 D_00248D20;

struct FollowPoseA {
    u8 pad00[0x50];
    Vec02 v50;              // 0x50
    u8 pad60[0x78 - 0x60];
    f32 f78;                // 0x78
    u8 pad7C[0x80 - 0x7C];
};

struct FollowPoseB {
    u8 pad00[0x10];
    Vec02 v10;              // 0x10
};

struct ChaseObject;

struct FollowObject {
    u8 pad00[0x48];
    ChaseObject* f48;       // 0x48
    u8 pad4C[0xB0 - 0x4C];
    Vec02 vB0;              // 0xB0
};

struct ChaseObject {
    u8 pad00[0x350];
    Vec02 gravity;          // 0x350
    u8 pad360[0x690 - 0x360];
    f32 f690;               // 0x690
    u8 pad694[0x6F0 - 0x694];
    f32 f6F0;               // 0x6F0
    f32 f6F4;               // 0x6F4
    u8 pad6F8[0x700 - 0x6F8];
    Vec02 v700;             // 0x700
};

struct FollowTune {
    u8 pad00[0x31C];
    f32 f31C;               // 0x31C
    f32 f320;               // 0x320
    f32 f324;               // 0x324
    f32 f328;               // 0x328
    f32 f32C;               // 0x32C
    f32 f330;               // 0x330
    f32 f334;               // 0x334
};

void GetObjectWorldPosition(void* obj, void* out);
void GetPlacementRecordTransform(void* rec, Vec02* a, Mat02* b, s32 zero);
s32 IsObjectOfKind(void* obj, s32 kind);
s32 ComputeBallisticLaunchVelocity(Vec02* from, Vec02* to, Vec02* out, s32 zero, f32 t);
s32 func_001A8C90(void* obj, s32 zero);
extern f32 D_00262A28[2];
extern f32 g_gameTime;

void func_0016D490(TargetFollower* self)
{
    Vec02 a;
    Vec02 b;
    Mat02 c;
    Vec02 dir;
    GetObjectWorldPosition(self->f590, &a);
    FollowObject* obj = (FollowObject*)self->f570;
    ChaseObject* t = obj->f48;
    FollowPoseA* sa = (FollowPoseA*)((u8*)obj + 0x60);
    FollowPoseB* sb = (FollowPoseB*)((u8*)obj + 0xE0);
    if (t == 0) {
        return;
    }
    GetPlacementRecordTransform(sa, &b, &c, 0);
    FollowTune* tune = (FollowTune*)self->f558->f7AC;
    if (IsObjectOfKind(t, 0x3D) != 0) {
        const Vec02* fb = &g_unitXVector;
        Vu0::Q(dir) = Vu0::Sub(Vu0::Q(a), Vu0::Q(b));
        u128 len = Vu0::Length(Vu0::Q(dir));
        if (Vu0::ToFloat(len) < 0.0001f) {
            dir = *fb;
        } else {
            Vu0::Q(dir) = Vu0::DivX(Vu0::Q(dir), len);
        }
        f32 e = tune->f328;
        f32 l = Vu0::ToFloat(len);
        if (e == 1.0f) {
            t->f6F4 = 0.0f;
            t->f6F0 = t->f690 = l / tune->f320;
        } else {
            f32 f5 = tune->f324;
            f32 q = (l + l) / ((f5 - e * f5 + (e + e)) * tune->f320);
            t->f690 = q;
            t->f6F0 = q * e;
            t->f6F4 = (t->f6F0 - q) / (f5 * tune->f320);
        }
        Vu0::Q(sa->v50) = Vu0::MulX(Vu0::Q(dir), Vu0::ScalarAt(t->f690));
    } else if (IsObjectOfKind(t, 0x3E) != 0) {
        Vec02 k;
        Vu0::Q(k) = Vu0::FromFloatAt(tune->f330);
        Vu0::Q(obj->vB0) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Q(k));
        Vu0::Q(k) = Vu0::FromFloat(-tune->f334);
        Vu0::Q(t->v700) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Q(k));
        t->f6F0 = tune->f320;
    } else {
        if (ComputeBallisticLaunchVelocity(&b, &a, &dir, 0, tune->f32C) == 0) {
            return;
        }
        u128 d1 = Vu0::Sub(Vu0::Q(b), Vu0::Q(a));
        f32 l1 = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d1, d1)));
        f32 l2 = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(dir), Vu0::Q(dir))));
        f32 u = l1 / l2 / tune->f320;
        Vu0::Q(t->gravity) = Vu0::MulX(Vu0::Q(*(Vec02*)((u8*)self->world + 0x1EE0)), Vu0::Scalar(u * u));
        Vu0::Q(obj->vB0) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(u));
    }
    sa->f78 = tune->f320 * D_00262A28[0];
    sb->v10 = a;
    if (func_001A8C90(self->f570, 0) != 0) {
        self->f574 = g_gameTime + ((FollowTune*)self->f558->f7AC)->f31C;
    }
}
