// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "game_clock.h"
#include "globals.h"
#include "vu0.h"

// The file's .data, in retail's order. D_00274F0C holds two floats (0.3, 10) under one label, which
// GCC would align to 8 as one object: it stays included, and ControlPlayerOnPath reads its first.
float D_00274F00 = 35.0f;
float D_00274F04 = 100.0f;
float D_00274F08 = 0.5f;
INCLUDE_DATA(D_00274F0C);
float D_00274F14 = 50.0f;
float D_00274F18 = 1.0f;
float D_00274F1C = 0.400000006f;
float D_00274F20[2] = {10.0f, 0.0f};
float D_00274F28[4] = {1500.0f, 0.0f, 0.5f, 0.0f};

struct TwoEntryBlendEntry {
    u8 pad0[4];
    void* p4;
    u8 pad8[4];
    f32 fC;
};

void BuildCombinedBlendAnimation(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);
void func_0012CD78(f32 f12, f32 f13, void* a0, void* a1, void* a2, s32 a3, void* a4, s32 a5, void* a6, s32 a7);

void CreatePlayerTwoEntryBlend(Player* self)
{
    f32 out[4];
    TwoEntryBlendEntry* e = (TwoEntryBlendEntry*)self->f103C;
    s32 i = 1;
    do {
        func_0012CD78(0.0f, 1.0f, e->p4, self->f614, self, 1, 0, 0, out, 0);
        e->fC = out[2];
        e++;
        i--;
    } while (i >= 0);
    BuildCombinedBlendAnimation(self, 0x10, 2, self->f103C, 0, 0, 0, &self->f105C);
    func_0012CD78(0.0f, 1.0f, self->f1064, self->f618, self, 1, &self->f23E0, 0, 0, 0);
    func_0012CD78(0.0f, 1.0f, self->f1064, self->f614, self, 1, &self->f23F0, 0, 0, 0);
    f32 avg = (self->f23E0 + self->f23F0) * 0.5f;
    self->f23F4 = 0.0f;
    self->f23E4 = 0.0f;
    self->f23F0 = avg;
    self->f23E0 = avg;
}

// The path object (+0x2208): a frame at +0x18, a holder at +0x34 whose descriptor has the
// methods the player calls (slots 1, 2, 8 and 10), and an offset at +0x40 (func_001D1630).
struct PathHolder;
struct PathHolderDesc {
    u8 pad00[4];
    void (*m1)(PathHolder* self, Vec02* pos, f32 t, Vec02* tangent);  // 0x04
    void (*m2)(PathHolder* self, Vec02* out, f32 t, s32 a);           // 0x08
    u8 pad0C[0x20 - 0x0C];
    f32 (*m8)(PathHolder* self);                                      // 0x20: the length
    u8 pad24[0x28 - 0x24];
    void (*m10)(PathHolder* self, Vec02* in, s32 a, s32 b, s32 c, s32 d, f32* out);
};
struct PathHolder {
    PathHolderDesc* desc;
    u8 pad04[4];
    s32 closed;             // 0x08: set, a length wraps around the path (func_001D1630)
    s32 count;              // 0x0C: the number of lengths at first
    f32* start;             // 0x10: the length the path starts at (func_001D1630)
    f32* first;             // 0x14: the smallest length it takes (func_001D1630)
};
struct PathObject {
    const Desc01* desc;
    u8 pad04[0x14];
    void* frame;            // 0x18
    u8 pad1C[0x34 - 0x1C];
    PathHolder* holder;     // 0x34
    u8 pad38[0x40 - 0x38];
    Vec02 v40;              // 0x40
    u8 pad50[0x68 - 0x50];
    PathObject* guide;      // 0x68: a path the camera follows instead (ControlPlayerOnPath)
};

void func_001D1630(Player* self, PathObject* path, Mat02* out, f32 length);

INCLUDE_ASM(func_001D1630);

// What the player watches while it follows the path (+0x2230) in states 0x17 and 0x1B: a record
// whose second word points to an object with a float at +0x34, and a float at +0x14.
struct PathWatch { u8 pad00[8]; struct PathWatchTarget* target; u8 pad0C[8]; f32 f14; };
struct PathWatchTarget { u8 pad00[0x34]; f32 f34; };

void func_00130748(f32 a, f32 b, f32 c, Mat02* rot, Vec02* vel, Mat02* target, const Vec02* zero, Mat02* out, s32 d, s32 e);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, Vec02* angle, Vec02* axis);

void func_001D1A80(Player* self)
{
    Mat02 placed;
    Mat02 goal;
    Mat02 delta;
    Vec02 axis;
    Vec02 k;
    Vec02 angle;
    func_001D1630(self, (PathObject*)self->f2208, &placed, self->f2410);
    if (self->f2228 == 0x17 || self->f2228 == 0x1B) {
        PathWatch* w = (PathWatch*)self->watched2230;
        f32 dt = g_gameClock.dt;
        f32 t = w->target->f34 - w->f14;
        func_00130748(dt >? t, dt, 1.0f, &self->rot, &self->v160, &placed, &D_00248D30, &goal, 0, 0);
    } else {
        goal = placed;
    }
    MultiplyMatrices3x3(&self->rot, &goal, &delta);
    MatrixToAxisAngle(&delta, &angle, &axis);
    Vu0::Q(k) = Vu0::FromFloat(angle.x / g_gameClock.dt);
    Vu0::Q(self->v160) = Vu0::MulX(Vu0::Q(axis), Vu0::Q(k));
}

extern f32 D_00274F0C;

// The pad's stick (+0x40, +0x44) as ControlPlayerOnPath reads it.
struct PathPad { u8 pad00[0x40]; f32 x; f32 y; };

// The easing ApproachValueWithRamp takes: a rate, then two more values.
struct PathRamp { f32 rate; f32 f04; f32 f08; f32 f0C; };

u128 ApproachPointWithRamp(u128 cur, u128 goal, const f32* params, s32 flag, f32 dt);
void ProjectPointToCamera(Camera* cam, Vec02* in, Vec02* out);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, PathRamp* p, f32* out);
f32 WrapModulo(f32 a, f32 b);
void SetBlendItemWeights(void* item, s32 a, s32 n, void* entries);
void SetPlayerState(void* self, s32 mode, s32 count);
void TransformPointBetweenFrames(void* a, void* b, void* c, void* d);
void SetPlayerPadSelectMode(Player* a0, s32 a1);

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

// v made unit length, or fallback when shorter than 0.0001; returns its length.
static inline f32 NormalizeVector(Vec02& v, const Vec02& fallback)
{
    u128 len = Vu0::Length(Vu0::Q(v));
    if (Vu0::ToFloat(len) < 0.0001f) {
        v = fallback;
    } else {
        Vu0::Set(v, Vu0::DivX(Vu0::Q(v), len));
    }
    return Vu0::ToFloatMoved(len);
}

void ControlPlayerOnPath(Player* self, PathPad* pad)
{
    PathObject* path = (PathObject*)self->f2208;
    PathHolder* holder = path->holder;
    Vec02 a;
    Vec02 b;
    Vec02 pa;
    Vec02 pb;
    Vec02 dir;
    f32 t;
    f32 lo;
    f32 hi;
    s32 state;
    f32 amount;
    f32 vel;
    s32 rev;
    f32 k;

    Vu0::Q(self->v2400) = ApproachPointWithRamp(Vu0::Q(self->v2400), Vu0::Q(D_00248D30), D_00274F28, 0,
                                                g_gameClock.dt);
    if (self->f2228 == 0x17 || self->f2228 == 0x1B) {
        Vu0::Set(self->v640, Vu0::Zero());
        return;
    }
    if (holder->desc->m2) {
        holder->desc->m2(holder, &a, self->f2410 + D_00274F14, 0);
    }
    if (holder->desc->m2) {
        holder->desc->m2(holder, &b, self->f2410 - D_00274F14, 0);
    }
    TransformPointBetweenFrames(path->frame, 0, &a, &a);
    TransformPointBetweenFrames(path->frame, 0, &b, &b);
    Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Sub(Vu0::Q(a), Vu0::Q(b)), Vu0::Q(g_unitZVector)));
    if (self->f2718 == -1) {
        if (D_00274F08 < __builtin_fabsf(dir.z)) {
            if (0.0f < dir.z) {
                if (self->f221C != 0) {
                    SetPlayerState(self, 7, 0x1B);
                    return;
                }
            } else if (self->f221C == 0) {
                SetPlayerState(self, 7, 0x1B);
                return;
            }
        }
        if (D_00274F1C < self->f2418 && self->f221C != 0 && -D_00274F0C < dir.z) {
            SetPlayerState(self, 7, 0x1B);
            return;
        }
        if (self->f2418 < -D_00274F1C && self->f221C == 0 && dir.z < D_00274F0C) {
            SetPlayerState(self, 7, 0x1B);
            return;
        }
    }
    if (path->guide == 0) {
        ProjectPointToCamera(g_camera, &a, &pa);
        ProjectPointToCamera(g_camera, &b, &pb);
    } else {
        Vec02 c;
        Vec02 d;
        void* frame = path->guide->frame;
        PathHolder* guide = path->guide->holder;
        TransformPointBetweenFrames(0, frame, &self->v140, &c);
        if (guide->desc->m10) {
            guide->desc->m10(guide, &c, 0, 0, 0, 0, &t);
        }
        t = ClampBetween(t, D_00274F14, guide->desc->m8(guide) - D_00274F14);
        if (guide->desc->m2) {
            guide->desc->m2(guide, &c, t + D_00274F14, 0);
        }
        TransformPointBetweenFrames(frame, 0, &c, &d);
        ProjectPointToCamera(g_camera, &c, &pa);
        if (guide->desc->m2) {
            guide->desc->m2(guide, &c, t - D_00274F14, 0);
        }
        TransformPointBetweenFrames(frame, 0, &c, &d);
        ProjectPointToCamera(g_camera, &c, &pb);
    }
    Vu0::Set(dir, Vu0::Sub(Vu0::Q(pa), Vu0::Q(pb)));
    dir.z = 0.0f;
    Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Q(dir), Vu0::Q(g_unitYVector)));
    switch (self->f2718) {
    case 0:
        state = self->f221C ? 0x1A : 0x19;
        amount = 1.0f;
        break;
    case 1:
        state = self->f221C ? 0x19 : 0x1A;
        amount = 1.0f;
        break;
    default: {
        Vec02 stick;
        Vu0::Set(stick, Vu0::FromFloats(pad->x, pad->y, 0.0f));
        f32 mag = NormalizeVector(stick, D_00248D30);
        amount = Vu0::ToFloat(Vu0::Dot(Vu0::Q(dir), Vu0::Q(stick)));
        switch (self->f241C) {
        case 0:
            if (mag < 0.25f) {
                self->f241C = -1;
            } else if (amount < -0.7f) {
                self->f241C = 1;
            }
            break;
        case 1:
            if (mag < 0.25f) {
                self->f241C = -1;
            } else if (0.7f < amount) {
                self->f241C = 0;
            }
            break;
        case -1:
            if (0.35f < mag) {
                if (0.0f <= amount) {
                    self->f241C = 0;
                } else {
                    self->f241C = 1;
                }
            }
            break;
        }
        switch (self->f241C) {
        case 0:
            state = self->f221C ? 0x1A : 0x19;
            amount = mag;
            break;
        case 1:
            state = self->f221C ? 0x19 : 0x1A;
            amount = mag;
            break;
        case -1:
            state = 0x18;
            amount = 0.0f;
            break;
        }
        break;
    }
    }
    rev = self->f221C;
    if (0.01f < amount) {
        vel = (1.0f - amount) * self->blend103C[0].speed + amount * self->blend103C[1].speed;
        if (state == 0x1A) {
            vel = -vel;
        }
    } else {
        vel = 0.0f;
        state = 0x18;
    }
    if (rev != 0) {
        vel = -vel;
    }
    PathRamp ramp;
    k = D_00274F18 * g_gameClock.dt;
    ramp.rate = __builtin_fabsf(self->blend103C[1].speed);
    ramp.f04 = 0.0f;
    ramp.f08 = 0.2f;
    self->f2418 = -k * vel / ramp.rate + (1.0f - k) * self->f2418;
    if (holder->closed == 0) {
        f32 start;
        f32 end;
        if (rev != 0) {
            start = holder->first[0] + D_00274F00;
            end = holder->first[holder->count - 1] - D_00274F04;
        } else {
            start = holder->first[0] + D_00274F04;
            end = holder->first[holder->count - 1] - D_00274F00;
        }
        ApproachValueWithRamp(self->f2410, start, g_gameClock.dt, &ramp, &lo);
        ApproachValueWithRamp(self->f2410, end, g_gameClock.dt, &ramp, &hi);
        vel = ClampBetween(vel, -hi, -lo);
    }
    self->f2414 = -vel;
    self->f2410 += -vel * g_gameClock.dt;
    if (holder->closed != 0) {
        self->f2410 = WrapModulo(self->f2410, holder->desc->m8(holder));
    }
    if (__builtin_fabsf(vel) < 0.01f) {
        state = 0x18;
        SetPlayerPadSelectMode(self, -1);
    } else {
        amount = (__builtin_fabsf(vel) - __builtin_fabsf(self->blend103C[0].speed)) /
                 (__builtin_fabsf(self->blend103C[1].speed) - __builtin_fabsf(self->blend103C[0].speed));
        amount = ClampBetween(amount, 0.0f, 1.0f);
        self->blend103C[1].weight = amount;
        self->blend103C[0].weight = 1.0f - amount;
        SetBlendItemWeights(self->f105C, 0x10, 2, self->f103C);
    }
    SetPlayerState(self, 7, state);
}

INCLUDE_ASM(func_001D2518);

void AcquirePadSelectFlag(void* a);
void ShowCountedScreenElement(void* a);
void ReleasePadSelectFlag(void* a);
void HideCountedScreenElement(void* a);

void SetPlayerPadSelectMode(Player* a0, s32 a1)
{
    if (a0->f2718 != a1) {
        if (a0->f2718 == -1) {
            AcquirePadSelectFlag(a0->world);
            ShowCountedScreenElement(a0->world);
        }
        a0->f2718 = a1;
        if (a1 == -1) {
            ReleasePadSelectFlag(a0->world);
            HideCountedScreenElement(a0->world);
        }
    }
}

void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void TransformPointBetweenFrames(void* a, void* b, void* c, void* d);
void SetPlayerState(void* self, s32 mode, s32 count);

void func_001D2830(Player* self, PathObject* path)
{
    Vec02 pos;
    Mat02 rot;
    Vec02 local;
    Vec02 world;
    if ((PathObject*)self->f2208 != path) {
        if (self->f2220 == 7) {
            TriggerScriptEvent((void*)self->f2208, 3, 0, 0);
            ((PathObject*)self->f2208)->desc->m18((BaseObject*)self->f2208, self);
            TriggerScriptEvent(path, 2, 0, 0);
            path->desc->m17((BaseObject*)path, self);
        }
        self->f2208 = (s32)path;
        self->f2204 = 0;
        self->f2200 = 0;
        TransformPointBetweenFrames(0, path->frame, &self->v140, &pos);
        if (path->holder->desc->m10 != 0) {
            path->holder->desc->m10(path->holder, &pos, 0, 0, 0, 0, (f32*)((u8*)self + 0x220C));
        }
    }
    func_001D1630(self, path, &rot, *(f32*)((u8*)self + 0x220C));
    self->desc02()->m1E(self, &rot);
    if (path->holder->desc->m2 != 0) {
        path->holder->desc->m2(path->holder, &pos, *(f32*)((u8*)self + 0x220C), 0);
    }
    TransformPointBetweenFrames(path->frame, self, &pos, &local);
    Vu0::Q(local) = Vu0::Sub(Vu0::Q(local), Vu0::Q(*(Vec02*)((u8*)self + 0x23E0)));
    TransformPointBetweenFrames(self, 0, &local, &world);
    self->desc02()->m1D(self, &world);
    SetPlayerState(self, 7, 0x17);
}
