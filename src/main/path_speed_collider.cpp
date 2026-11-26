// SPDX-License-Identifier: AGPL-3.0-or-later
// The path-speed collider (class 0x24, under 0x21), 0x182470 to 0x182C18 (its .data from
// 0x264230): its set-up, start, update and per-frame motion, and BuildPathSpeedProfile, the
// travel-time table its motion steps through. Its end is base_object.cpp's proved start; its
// start is not proved by retail, only by the change of role from mode_walker.cpp's mode walker
// (class 0x1A) and its sprite element: none of these functions reads the other side's .data,
// which follows the code's order (this file's from D_00264230, its link table), and neither
// side has .rodata here, so the cut could lie from 0x1821B0 to 0x182470. The name is ours,
// after its role.
#include "common.h"
#include "vu0.h"
#include "list_iter.h"
#include "screen_element.h"
#include "switched_collider.h"
#include "path_curve_object.h"
#include "cone_volume.h"
#include "world.h"
#include "masked_collider.h"
#include "object_link.h"
#include "message_body.h"
#include "shapes.h"
#include "game_progress.h"
#include "globals.h"
#include "script_value.h"
#include "fpu.h"
#include "collider.h"
#include "state_walker.h"
#include "asm_func.h"
#include "transform_object.h"
#include "ramp_profile.h"
#include "path_curve.h"
#include "list_walk.h"
#include "functions/base_object.h"
#include "functions/effect_spawner.h"
#include "functions/matrix.h"
#include "functions/path_follower.h"
#include "functions/placed_object.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/warp_menu.h"
#include "functions/zone_collider.h"
struct Mat3;






struct WeightCurve;
WeightCurve* CreateWeightCurve(u32 kind);

void* AllocateFrontMemory(s32 size);


struct OwnerMessage;





// The file's .data, 0x264230 to 0x264260, in retail's order.
ObjectLink g_pathSpeedColliderLinks[2] = { { 0, 0x36B, 0x6C4 }, { 0x20, 0x36C, 0x6EC } };
f32 D_00264248 = 2.5f;
f32 D_0026424C = 300.0f;
f32 g_pathSpeedColliderRotationRamp[4] = { 20.0f, 0.0f, 0.5f, 0.0f };

// Initialises a path-speed collider: the player-flagged collider's defaults, then its level limit
// 10, level rate 1 and the fields at 0x6CC-0x6D8 (1000, 0, 0.5, 3000).
void InitC24Object(PathSpeedCollider* self)
{
    InitPlayerFlaggedCollider(self);
    self->levelLimit = 10.0f;
    self->levelRate = 1.0f;
    self->f6D8 = 3000.0f;
    self->f6CC = 1000.0f;
    self->f6D0 = 0;
    self->f6D4 = 0.5f;
}

// Starts a path-speed collider: starts it as a masked collider, resolves its links, creates its
// state walker and allocates a 0xC00-byte curve table (an empty weight curve plus its storage).
void StartC24Object(PathSpeedCollider* self)
{
    StartMaskedCollider(self);
    ResolveObjectLinks(self, 2, g_pathSpeedColliderLinks);
    self->walker = (StateWalker*)CreateStateWalker((StateGraph*)self->stateGraph, self, 0x36E, 0);
    PathSpeedCurveTable* n = (PathSpeedCurveTable*)CreateWeightCurve(0);
    self->curveTable = n;
    n->field8 = 0;
    self->curveTable->field_c = AllocateFrontMemory(0xC00);
}




// Per-frame update of the path-speed object: advances its level by levelRate (kept between 0 and
// levelLimit), and when it reaches the limit (or the player is near the end, in state key 0x36F)
// sends the player a message, notifies its member, calls slot 3 on itself and sends script event
// 2; near the end it moves its state walker to key 0x36F.
void UpdateC24Object(PathSpeedCollider* self, f32 dt)
{
    SwitchedCollider* target;
    u8 msg[0x10];
    s32 key;
    UpdateMaskedCollider(self, dt);
    if (self->curveTable != 0) {
        target = (SwitchedCollider*)GetActiveSwitchedCollider();
        if (IsObjectOfKind(target, 0x16) != 0) {
            target = (SwitchedCollider*)((PlayerLinkedCollider*)target)->target;
        }
        f32 v = self->level + dt * self->levelRate;
        f32 hi = self->levelLimit;
        if (v < 0.0f) {
            v = 0.0f;
        } else if (hi < v) {
            v = hi;
        }
        self->level = v;
        GetStateWalkerTargetKey(self->walker, &key);
        if (key == -1) {
            GetStateWalkerCurrentKey(self->walker, &key);
        }
        s32 hold = 0;
        if (key == 0x36F && target != 0 &&
            Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(target->v140)))) < D_0026424C) {
            hold = 1;
        } else if (self->level >= self->levelLimit) {
            hold = 1;
        }
        if (hold) {
            InitOwnerMessage((OwnerMessage*)msg, ((g_saveData->levelIndex << 8) | g_saveData->entryIndex) == 0x505 ? 2 : 0, self);
            target->desc05()->m4C(target, msg);
            SendEmptyMessage((MemberObject*)self->x6EC);
            self->desc->m03(self);
            TriggerScriptEvent(self, 2, 0, 0);
            return;
        }
        if (self->walker != 0 && self->levelLimit - self->level < D_00264248) {
            SetStateWalkerTarget(self->walker, 0x36F);
        }
    }
    ClearRootTries(self);
}

typedef void (*WeightCurveFn)(void* curve, void* owner, s32 a2, f32* out0, f32* out1, f32 x, f32 y);
typedef void (*CurveSampleDirFn)(PathCurve* self, f32 len, Vec4* pos, Vec4* dir);


// Moves the path-speed object to the point and velocity its curve table gives for the current
// level, turns it toward the velocity (with the acceleration relative to gravity as its up hint)
// through a rotation ramp, steps its children, and calls slot 18 unless a1 is set.
void MoveC24Object(PathSpeedCollider* self, s32 a1, f32 dt)
{
    if (self->curveTable != 0) {
        Vec4 pos;
        Vec4 dir;
        Vec4 vel;
        Vec4 t;
        Mat3 basis;
        f32 o0, o1;
        ((WeightCurveFn)(*(void***)self->curveTable)[0])(self->curveTable, self, 0, &o0, &o1, self->level, self->levelRate);
        PathCurve* curve = ((PathCurveObject*)self->path)->curve;
        CurveSampleDirFn sample = (CurveSampleDirFn)curve->vt->m02;
        if (sample) {
            sample(curve, o0, &pos, &dir);
        }
        u128 w = Vu0::FromFloatAt(o1);
        Vu0::Q(vel) = Vu0::MulX(Vu0::Q(dir), w);
        void* o = ((PathCurveObject*)self->path)->parent;
        Vu0::Set(t, w);
        TransformStateToAncestorFrame((PlacedObject*)o, 0, &pos, 0, &vel, 0);
        Vu0::Set(t, Vu0::MulXSum(Vu0::Q(self->gravity), Vu0::Scalar(-1.0f),
                                 Vu0::Sub(Vu0::Q(vel), Vu0::Q(self->v150)), Vu0::Scalar(1.0f / dt)));
        BuildBasisFromXAndZHint(&vel, &t, &basis);
        self->pos = pos;
        self->v150 = vel;
        ApproachRotationWithRamp(&self->rot, &basis, (RampProfile*)g_pathSpeedColliderRotationRamp, dt, &self->rot, &self->v160);
    }
    ScopedListFrame frame(&self->children);
    void* head = *(void**)&self->children;
    frame.cursor = (void*)((s32)head + frame.next_off);
    BaseObject* n = (BaseObject*)head;
    while (n != 0) {
        if (n->desc->flags & 1) {
            n->desc->step(n, dt, 1);
        }
        void* next = *(void**)frame.cursor;
        frame.cursor = (void*)((s32)next + frame.next_off);
        n = (BaseObject*)next;
    }
    if (a1 == 0) {
        void (*fn)(BaseObject*) = self->desc->m12;
        if (fn != 0) {
            fn(self);
        }
    }
}

struct CurveEntry {
    f32 a;                  // 0x00
    f32 b;                  // 0x04
    s32 k;                  // 0x08
    f32 c;                  // 0x0C
    s32 k2;                 // 0x10
    f32 d;                  // 0x14
};

typedef void (*CurveSampleFn)(PathCurve* self, s32 zero, Vec4* out, f32 t);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 bytes);

// Builds the speed table for travelling a path curve in a set time: at each curve node the speed
// is limited by the curve's sharpness (from points half a unit either side) and by a ramp toward
// the end; the times to each node are accumulated and the table is rescaled so the whole path
// takes the level range 0 to the given speed (levelLimit). Restarts the level at 0.
void BuildPathSpeedProfile(PathSpeedCollider* self, PathCurveObject* path, f32 speed)
{
    Vec4 p0;
    Vec4 p1;
    f32 out;
    s32 i;
    PushBackMemoryMark();
    self->path = path;
    self->levelLimit = speed;
    PathCurve* curve = path->curve;
    f32 total = curve->vt->m08(curve);
    s32 n = curve->count;
    CurveEntry* entries = (CurveEntry*)self->curveTable->field_c;
    self->curveTable->field8 = n;
    f32* lens = (f32*)AllocateBackMemory(n << 2);
    for (i = 0; i < n; i++) {
        if (curve->vt->m02 != 0) {
            ((CurveSampleFn)curve->vt->m02)(curve, 0, &p0, curve->lengths[i] - 0.5f);
            if (curve->vt->m02 != 0) {
                ((CurveSampleFn)curve->vt->m02)(curve, 0, &p1, curve->lengths[i] + 0.5f);
            }
        }
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(p0), Vu0::Q(p1))));
        lens[i] = Fpu::Sqrt(self->f6D8 / len);
        ApproachValueWithRamp(curve->lengths[i], total + 100.0f, 0.0f, (RampProfile*)&self->f6CC, &out);
        lens[i] = out <? lens[i];
    }
    CurveEntry* e;
    for (i = 0; i < n; i++) {
        e = &entries[i];
        e->b = curve->lengths[i];
        if (i == 0) {
            e->a = 0.0f;
        } else {
            e->a = e[-1].a + (e->b - e[-1].b) * 2.0f / (lens[i] + lens[i - 1]);
        }
        e->k = 4;
        e->c = lens[i];
    }
    f32 scale = speed / e->a;
    for (i = 0; i < n; i++) {
        e = &entries[i];
        e->a = e->a * scale;
        e->c = e->c / scale;
    }
    for (i = 0; i < n; i++) {
        e = &entries[i];
        e->k2 = 4;
        e->d = e->c;
    }
    self->level = 0.0f;
    TeleportStateWalker(self->walker, 0x36E);
    PopBackMemoryMark();
}
