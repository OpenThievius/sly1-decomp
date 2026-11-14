// SPDX-License-Identifier: AGPL-3.0-or-later
// From 0x1D8E40 to 0x1D9AC8: five of class 0x19's helpers (the wheels' particles, the laps, the
// entry markers and the sound), called from UpdatePathFollower and ControlPathFollower in
// world.cpp but func_001D9338, which func_001D9488 and func_00195958 call. Built at
// -mvu0-use-vf0-vf30 (config/cflags.tsv), a threshold of 94 for loop.c, where the files around
// it take the default (79).
// Evidence: func_001D9488 is retail's code only at N = 30 or 31, while func_001D7778 before it
// matches only up to N = 19 and func_001D9AC8 after it only up to 24, so no one unit at one N
// holds the three (docs/toolchain/loops.md, "The threshold by function"); func_001D8E40 matches
// at 12 to 31 and the other three at any N.
// Choice: no boundary signal shows either edge; the cut was decided on 2026-11-12 on the threshold
// evidence. The edges are where the data cuts with the fewest crossings. This file's .data runs
// from 0x275500 (func_001D8E40's ranges) to 0x2755FC (func_001D9678's curves) and starts on 16
// because it holds the Vec02 at 0x275530 (retail's eight zero bytes before it show an object on
// 16 or a new file there; the type is ours). Starting it at 0x275518, past func_001D8E40's ranges,
// would need D_00275524 to be a 12-byte object no reader shows; starting at 0x275530 would leave
// D_00275518 and D_00275524 in path_follower.cpp, read only here. As cut, D_002751D8 (also read
// there) and D_00275240 are path_follower.cpp's, declared extern; world.cpp starts its .data
// at 0x275600. No .rodata, no .bss. Its name is ours, after its role: five of the path follower's
// helpers.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "globals.h"
#include "game_progress.h"
#include "value_range.h"
#include "object_finder.h"
struct Mat02;


extern f32 g_gameTime;

f32 RandomFloatInRange(f32 a, f32 b);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);

struct WalkerHolder { u8 pad[0x48]; void* f48; };

void GetStateWalkerTargetKey(StateWalker* a0, s32* out);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void SetStateWalkerTarget(StateWalker* self, s32 key);
void* GetActiveSwitchedCollider(void);
struct RampProfile;
f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);

extern u8 g_scatterController[];

struct ScatterController;
void RaiseScatterLevels(ScatterController* self, f32 amount);

// A quadratic by its three coefficients (func_001D8E40, func_001D9678).
struct QuadraticCurve {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};

extern float D_002751D8;
extern float D_00275240[4];

f32 D_00275500[2] = { 0.400000006f, 0.800000012f };
f32 D_00275508[2] = { 0.0500000007f, 0.300000012f };
f32 D_00275510[2] = { 0.100000001f, 0.400000006f };
f32 D_00275518[3] = { 10.0f, 0.0f, 0.100000001f };
f32 D_00275524 = 4000.0f;
Vec02 D_00275530 = { -0.5f, 0.699999988f, 0.0f, 0.0f };
f32 D_00275540[4] = { 1.0f, -0.5f, 0.0f, 0.0f };
f32 D_00275550[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_00275560[4] = { -0.5f, 2.0f, 0.0f, 0.0f };
f32 D_00275570[4] = { 0.5f, 4.0f, 0.0f, 0.0f };
f32 D_00275580[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
f32 D_00275590[4] = { 1.0f, -0.600000024f, 0.0f, 0.0f };
f32 D_002755A0[2] = { 0.25f, 1.0f };
f32 D_002755A8 = 1.10000002f;
f32 D_002755AC = 1000.0f;
f32 D_002755B0[4] = { 0.5f, 0.25f, 0.0f, 0.0f };
f32 D_002755C0[4] = { 0.0f, 2.0f, -1.0f, 0.0f };
f32 D_002755D0[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_002755E0[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_002755F0[2] = { 0.0f, 1.0f };
f32 D_002755F8 = 0.75f;

// The record a wheel's emitter (PathEmitter's slot at 0x7C) takes: flags, the spawn data and
// how many to spawn.
struct WheelEmit {
    s32 flags;              // 0x00: 0xC0
    u8 pad04[0x3C - 0x04];
    void* spawn;            // 0x3C: the WheelSpawn
    s32 count;              // 0x40
    u8 pad44[0x50 - 0x44];
};

// Where and how a wheel's particles start: a point, a basis and a velocity.
struct WheelSpawn {
    Vec02 pos;              // 0x00
    Mat02 basis;            // 0x10
    Vec02 vel;              // 0x40
    u8 pad50[0x60 - 0x50];
};

typedef void (*EmitFn)(PathEmitter* self, WheelEmit* rec);
void TransformStateToAncestorFrame(PlacedObject* self, PlacedObject* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin);
void BuildBasisFromX(Vec02* x, Mat02* out);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);

// The wheels' particles: the lap timer's fade, then for each wheel the emitters of its two
// spawn counts (the first with a random turn and tilt, the second plain).
void EmitPathFollowerWheelParticles(PathFollower* self)
{
    if (self->lapObject != 0) {
        f32 t = (g_gameTime - self->lapTime) / D_002751D8;
        *(f32*)((u8*)self->lapObject + 0x334) = g_unitRange.Clamp(((QuadraticCurve*)D_00275240)->Eval(t));
        BaseObject* o = self->lapObject;
        if (*(f32*)((u8*)o + 0x334) == 0.0f) {
            ((void (*)(BaseObject*))o->desc->m03)(o);
        }
    }
    f32 one = 1.0f;
    f32 zero = 0.0f;
    WheelSpawn spawn;
    for (u32 i = 0; i < 4; i++) {
        Slot19* s = &self->wheels[i];
        if (one <= s->firstEmitterOwed) {
            if (500.0f < self->targetSpeed) {
                Vec02 off;
                Vec02 dir;
                Mat02 m;
                Mat02 n;
                f32* range = (g_currentWorld->soundBank == 3) ? D_00275508 : D_00275500;
                // The angle is a statement of its own: &m is formed at the call, after it.
                f32 a = RandomFloatInRange(range[0], range[1]);
                BuildAxisAngleMatrix(&g_unitYVector, &m, a);
                // The tilt's range through a pointer, as the turn's: loop.c then moves its
                // address out of the loop with the %hi of its first word.
                f32* tilt = D_00275510;
                f32 b = RandomFloatInRange(tilt[0], tilt[1]);
                switch ((s32)i) {
                case 0:
                    b = b + self->steerAngle;
                    break;
                case 1:
                    b = self->steerAngle - b;
                    break;
                case 2:
                    break;
                case 3:
                    b = -b;
                    break;
                }
                s32 front = (s32)i < 2;
                BuildAxisAngleMatrix(&g_unitZVector, &n, b);
                MulRotation(&m, n, m);
                TransformPointBetweenFrames(0, self, &s->contactPoint, &spawn.pos);
                // The offset stored in each arm: the join after them makes CSE read it back
                // from memory, as retail does; cross-jumping merges the two tails.
                if (front) {
                    Vu0::Q(off) = Vu0::FromFloats(zero, zero, self->frontWheelRadius);
                } else {
                    Vu0::Q(off) = Vu0::FromFloats(zero, zero, self->rearWheelRadius);
                }
                Vu0::Q(spawn.pos) = Vu0::Sub(Vu0::Add(Vu0::Q(spawn.pos), Vu0::Q(off)),
                                             Vu0::Rotate(m, Vu0::Q(off)));
                TransformDirectionBetweenFrames(0, self, &s->contactDirection, &dir);
                BuildBasisFromX(&dir, &spawn.basis);
                Vu0::Q(spawn.vel) = Vu0::FromFloats(-self->targetSpeed, zero, zero);
                Vu0::Q(spawn.vel) = Vu0::RotateUntied(m, Vu0::Q(spawn.vel));
                WheelEmit rec;
                rec.flags = 0xC0;
                rec.count = (s32)s->firstEmitterOwed;
                rec.spawn = &spawn;
                PathEmitter* e = (self->activeZone != 0) ? self->activeZone->firstEmitter : self->firstEmitter;
                if (e != 0) {
                    if (e->f18 == 0) {
                        TransformStateToAncestorFrame(self, 0, &spawn.pos, &spawn.basis, &spawn.vel, 0);
                    }
                    ((EmitFn)e->vt[0x7C / 4])(e, &rec);
                }
            }
            s->firstEmitterOwed = s->firstEmitterOwed - (f32)(s32)s->firstEmitterOwed;
        }
        if (one <= s->secondEmitterOwed) {
            Vec02 dir;
            WheelEmit rec;
            FillMemory(&spawn, 0, 0x60);
            TransformPointBetweenFrames(0, self, &s->contactPoint, &spawn.pos);
            TransformDirectionBetweenFrames(0, self, &s->contactDirection, &dir);
            BuildBasisFromX(&dir, &spawn.basis);
            rec.flags = 0xC0;
            rec.count = (s32)s->secondEmitterOwed;
            rec.spawn = &spawn;
            PathEmitter* e = (self->activeZone != 0) ? self->activeZone->secondEmitter : self->secondEmitter;
            if (e != 0) {
                ((EmitFn)e->vt[0x7C / 4])(e, &rec);
            }
            s->secondEmitterOwed = s->secondEmitterOwed - (f32)rec.count;
        }
    }
}

void CountDownPathFollowerLap(PathFollower* self)
{
    self->lapTime = g_gameTime;
    self->lapsLeft = self->lapsLeft - 1;
    BaseObject* s = self->lapObject;
    if (s != 0) {
        s->desc->m02(s);
    }
}

void RecordPathFollowerProgress(PathFollower* self)
{
    f32 lo = 0.0f;
    f32 hi = 1.0f;
    s32 idx = self->lap - 1;
    f32 f = (f32)(idx * 3 + self->currentMarker->index) * 0.1f;
    if (f < lo) {
        f = lo;
    } else if (hi < f) {
        f = hi;
    }
    s32 s0 = self->placeCount - self->place;
    s32 t = 0;
    if (s0 >= 3) {
        s32 mk = 1 << (s0 & 7);
        t = g_currentEntry->bits74[s0 / 8] & mk;
    }
    if (s0 < 3 || t) {
        RaiseScatterLevels((ScatterController*)g_scatterController, f);
    }
    if (s0 >= 0) {
        do {
            G27C230* g = g_currentEntry;
            u8* bb = g->bits74;
            u8* byte = bb + s0 / 8;
            s32 mask = 1 << (s0 & 7);
            if ((*byte & mask) == 0) {
                *byte = (u8)(*byte | mask);
                g->count70++;
            }
            s0--;
        } while (s0 >= 0);
    }
}

struct ObjectGatherer;
s32 TestPointAgainstObjectShape(ObjectGatherer* self, void* value);
void ResetScatterLevels(ScatterController* object);

// For each entry marker the follower moves into or out of: kind 0 advances the current entry,
// counts the laps and at the last one moves the state walker on; kind 1 holds the marker at +0xAFC
// while inside it. Its loop's constants leave the loop as retail's only at this file's threshold
// of 94 (docs/toolchain/loops.md, "A threshold of 94").
void AdvancePathFollowerEntry(PathFollower* self, s32 v)
{
    for (s32 i = 0; i < self->markerCount; i++) {
        PathMarker* e = &self->markers[i];
        s32 r = TestPointAgainstObjectShape((ObjectGatherer*)e->item, (u8*)self + 0x100);
        if (r == *(s32*)((u8*)e + 8)) {
            continue;
        }
        s32 kind = e->kind;
        *(s32*)((u8*)e + 8) = r;
        switch (kind) {
        case 0:
            if (r != 0 && e->next == self->currentMarker) {
                self->currentMarker = e;
                if (e == self->firstMarker) {
                    s32 n = self->lap + 1;
                    self->lap = n;
                    if (self->lapCount < n) {
                        void* w = ((WalkerHolder*)FindFirstObjectById(self->world, 4, 0x42C, self))->f48;
                        s32 key;
                        GetStateWalkerTargetKey((StateWalker*)w, &key);
                        if (key == -1) {
                            GetStateWalkerCurrentKey((StateWalker*)w, &key);
                        }
                        if (self == GetActiveSwitchedCollider()) {
                            self->lap = self->lapCount;
                        }
                        switch (key) {
                        case 0x42F:
                            if (self == GetActiveSwitchedCollider()) {
                                SetStateWalkerTarget((StateWalker*)w, 0x432);
                                ResetScatterLevels((ScatterController*)g_scatterController);
                            } else {
                                SetStateWalkerTarget((StateWalker*)w, 0x430);
                            }
                            break;
                        case 0x430:
                            if (self == GetActiveSwitchedCollider()) {
                                SetStateWalkerTarget((StateWalker*)w, 0x431);
                                RecordPathFollowerProgress(self);
                            }
                            break;
                        }
                    }
                }
            }
            break;
        case 1:
            if (r != 0) {
                *(PathMarker**)((u8*)self + 0xAFC) = e;
            } else {
                *(PathMarker**)((u8*)self + 0xAFC) = 0;
            }
            break;
        }
    }
}

struct PlayingSound;
void SetSoundRecordPitch(PlayingSound* self, f32 x);
void SetSoundRecordVolume(PlayingSound* self, f32 x);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
extern const Vec02 g_unitXVector;

void UpdatePathFollowerSound(PathFollower* self, f32 dt)
{
    typedef Vu0::Vec Vec;
    if (*(PlayingSound**)self->engineSoundA == 0) {
        return;
    }
    f32 t = self->targetSpeed / D_00275524;
    f32 lo = 0.0f;
    f32 hi = 1.0f;
    if (t < lo) {
        t = lo;
    } else if (hi < t) {
        t = hi;
    }
    self->soundSpeed = ApproachValueWithRamp((RampProfile*)D_00275518, 0, self->soundSpeed, t, dt);
    f32 fwd = Vu0::ToFloat(Vu0::Dot(Vec::Of(self->v150), Vec::Of(self->m110.r[0]))) / D_00275524;
    f32 lo1 = 0.0f;
    f32 hi1 = 1.0f;
    f32 share;
    if (fwd < lo1) {
        share = lo1;
    } else if (hi1 < fwd) {
        share = hi1;
    } else {
        share = fwd;
    }
    f32 mix = ((ValueRange*)D_002755A0)->Limit(((QuadraticCurve*)D_00275590)->Eval(self->drive));
    mix = (1.0f - mix) * share + mix * D_002755A8 * self->soundSpeed;
    SetSoundRecordPitch(*(PlayingSound**)self->engineSoundA, ((QuadraticCurve*)&D_00275530)->Eval(mix) + self->engineAPitchOffset);
    SetSoundRecordVolume(*(PlayingSound**)self->engineSoundA,
                         ((ValueRange*)D_00275550)->Clamp(((QuadraticCurve*)D_00275540)->Eval(mix)));
    SetSoundRecordPitch(*(PlayingSound**)self->engineSoundB, ((QuadraticCurve*)D_00275560)->Eval(mix) + self->engineBPitchOffset);
    SetSoundRecordVolume(*(PlayingSound**)self->engineSoundB,
                         ((ValueRange*)D_00275580)->Clamp(((QuadraticCurve*)D_00275570)->Eval(mix)));
    Vec02 local;
    Vec02 drift;
    TransformDirectionBetweenFrames(0, self, &self->v150, &local);
    Vu0::Q(drift) = Vu0::MulAddX(Vec::Of(local), Vec::Of(g_unitXVector), Vec::Scalar(-self->targetSpeed)).q;
    drift.x = drift.x * D_002755F8;
    f32 d = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(drift), Vu0::Q(drift)))) / D_002755AC;
    f32 lo2 = 0.0f;
    f32 hi2 = 1.0f;
    f32 slide;
    if (d < lo2) {
        slide = lo2;
    } else if (hi2 < d) {
        slide = hi2;
    } else {
        slide = d;
    }
    slide = slide * ((ValueRange*)D_002755F0)->Clamp(((QuadraticCurve*)D_002755E0)->Eval(self->drive));
    SetSoundRecordPitch(*(PlayingSound**)self->slideSound, ((QuadraticCurve*)D_002755B0)->Eval(slide) + self->slidePitchOffset);
    SetSoundRecordVolume(*(PlayingSound**)self->slideSound,
                         ((ValueRange*)D_002755D0)->Clamp(((QuadraticCurve*)D_002755C0)->Eval(slide)));
}
