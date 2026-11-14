// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "game_clock.h"
#include "globals.h"
#include "vu0.h"
#include "placed_object.h"
#include "collider.h"
#include "aim_blend_grid.h"

// The file's .data, in retail's order. D_00274F0C holds two floats (0.3, 10) under one label, which
// GCC would align to 8 as one object: it stays included, and ControlPlayerOnPath reads its first.
float D_00274F00 = 35.0f;
float D_00274F04 = 100.0f;
float g_steepSlopeThreshold = 0.5f;
INCLUDE_DATA(D_00274F0C);
float D_00274F14 = 50.0f;
float D_00274F18 = 1.0f;
float g_pathTurnThreshold = 0.400000006f;
float g_pathPlaceStep[2] = {10.0f, 0.0f};
float g_pathVelocityRamp[4] = {1500.0f, 0.0f, 0.5f, 0.0f};

struct TwoEntryBlendEntry {
    u8 pad0[4];
    void* p4;
    u8 pad8[4];
    f32 fC;
};

struct BlendAnimation;
struct Collider;
void BuildCombinedBlendAnimation(Collider* ctx, s32 stride, s32 count, u8* items, s32 nkeys, s32* keyA, s32* keyB, BlendAnimation** out);

void CreatePlayerTwoEntryBlend(Player* self)
{
    f32 out[4];
    TwoEntryBlendEntry* e = (TwoEntryBlendEntry*)self->f103C;
    s32 i = 1;
    do {
        SampleAnimationFrameChain((BlendAnimationView*)e->p4, 0.0f, 1.0f, (PlacedObject*)self->f614, (PlacedObject*)self, 1, 0, 0, (Vec02*)out, 0);
        e->fC = out[2];
        e++;
        i--;
    } while (i >= 0);
    BuildCombinedBlendAnimation(self, 0x10, 2, self->f103C, 0, 0, 0, (BlendAnimation**)&self->f105C);
    SampleAnimationFrameChain((BlendAnimationView*)self->f1064, 0.0f, 1.0f, (PlacedObject*)self->f618, (PlacedObject*)self, 1, (Vec02*)&self->f23E0, 0, 0, 0);
    SampleAnimationFrameChain((BlendAnimationView*)self->f1064, 0.0f, 1.0f, (PlacedObject*)self->f614, (PlacedObject*)self, 1, (Vec02*)&self->f23F0, 0, 0, 0);
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
    void (*m2)(PathHolder* self, Vec02* pos, f32 t, Vec02* dir);      // 0x08
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
    PlacedObject* frame;    // 0x18
    u8 pad1C[0x34 - 0x1C];
    PathHolder* holder;     // 0x34
    u8 pad38[0x40 - 0x38];
    Vec02 v40;              // 0x40
    u8 pad50[0x68 - 0x50];
    PathObject* guide;      // 0x68: a path the camera follows instead (ControlPlayerOnPath)
};

void PlaceOnPathAt(Player* self, PathObject* path, Mat02* out, f32 length);

f32 WrapModulo(f32 x, f32 y);
void BuildShortestArcRotation(const Vec02* from, const Vec02* to, Mat02* out);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);

// v made unit length, or fallback when shorter than 0.0001, as an if with the fallback in its
// first arm: retail's bc1f to the divide, with the fallback's qmtc2 in the slot of the branch
// over it (Vu0::NormalizeOr's early return lays the arms out the other way).
static inline Vu0::Vec NormalizeOrElse(Vu0::Vec v, Vu0::Vec fallback)
{
    u128 len = Vu0::Length(v.q);
    Vu0::Vec r;
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        r = fallback;
    } else {
        r.q = Vu0::DivX(v.q, len);
    }
    return r;
}

// The player's frame on its path at a length: the path's start direction, then lengths stepped
// out on both sides until the direction there turns less than 0.9 away from it, the shortest-arc
// rotation of the path's offset, and the frame built from the first direction and that offset,
// turned about when 0x221C is set.
void PlaceOnPathAt(Player* self, PathObject* path, Mat02* out, f32 length)
{
    Vec02 start;
    Vec02 first;
    Vec02 dir;
    Vec02 ahead;
    PathHolder* h = path->holder;
    f32 total = h->desc->m8(h);
    if (h->desc->m1 != 0) {
        h->desc->m1(h, 0, *h->start, &start);
    }
    Vu0::Q(start) = Vu0::NormalizeOr(Vu0::Q(start), Vu0::Q(g_unitXVector));
    s32 i = 0;
    for (;; i++) {
        f32 step;
        if (i & 1) {
            step = (f32)(i + 1) * g_pathPlaceStep[0];
        } else {
            step = (f32)i * -g_pathPlaceStep[0];
        }
        f32 at = length + step;
        if (h->closed == 0) {
            if (at < *h->first) {
                continue;
            }
            if (total < length) {
                continue;
            }
        } else {
            at = WrapModulo(at, total);
        }
        Vec02 behind;
        if (h->desc->m2 != 0) {
            h->desc->m2(h, &ahead, at + D_00274F14, 0);
            if (h->desc->m2 != 0) {
                h->desc->m2(h, &behind, at - D_00274F14, 0);
            }
        }
        Vu0::Vec d = NormalizeOrElse(Vu0::Sub(Vu0::Vec::Of(ahead), Vu0::Vec::Of(behind)), Vu0::Vec::Of(g_unitZVector));
        Vu0::Q(dir) = d.q;
        if (i == 0) {
            *(Vu0::Vec*)&first = d;
        }
        if (-0.9f < Vu0::ToFloat(Vu0::Dot(Vu0::Q(start), Vu0::Q(dir)))) {
            break;
        }
    }
    Mat02 arc;
    BuildShortestArcRotation(&start, &dir, &arc);
    Vu0::Q(ahead) = Vu0::Rotate(arc, Vu0::Q(path->v40));
    TransformDirectionBetweenFrames(path->frame, 0, &first, &first);
    TransformDirectionBetweenFrames(path->frame, 0, &ahead, &ahead);
    Mat02 m;
    u128 z = Vu0::NormalizeOr(Vu0::Q(first), Vu0::Q(g_unitZVector));
    Vu0::Q(m.r[2]) = z;
    u128 c = Vu0::Cross(z, Vu0::Q(ahead));
    u128 fy = Vu0::Q(g_unitYVector);
    u128 cl = Vu0::Length(c);
    Vu0::Vec y;
    if (Vu0::ToFloatMoved(cl) < 0.0001f) {
        y.q = fy;
    } else {
        y.q = Vu0::DivX(c, cl);
    }
    Vu0::Q(m.r[0]) = Vu0::Cross(y.q, Vu0::Q(m.r[2]));
    Vu0::Q(m.r[1]) = y.q;
    if (self->pathFlipped != 0) {
        // The -1 vector is stored to a local of its own after the two products (retail's sqc2
        // to the frame before the rows' stores, scheduled after both vmulx).
        Vec02 flip;
        Vu0::Vec k;
        k.q = Vu0::FromFloat(-1.0f);
        Vu0::Vec a2 = Vu0::MulX(Vu0::Vec::Of(m.r[2]), k);
        Vu0::Vec a1 = Vu0::MulX(Vu0::Vec::Of(m.r[1]), k);
        *(Vu0::Vec*)&flip = k;
        *(Vu0::Vec*)&m.r[1] = a1;
        *(Vu0::Vec*)&m.r[2] = a2;
    }
    if (out != 0) {
        *out = m;
    }
}

// What the player watches while it follows the path (+0x2230) in states 0x17 and 0x1B: a record
// whose second word points to an object with a float at +0x34, and a float at +0x14.
struct PathWatch { u8 pad00[8]; struct PathWatchTarget* target; u8 pad0C[8]; f32 f14; };
struct PathWatchTarget { u8 pad00[0x34]; f32 f34; };

void BlendRotationsWithSpin(f32 dur, f32 t, f32 e, Mat02* a, const Vec02* wa, Mat02* b, const Vec02* wb, Mat02* out, Vec02* outW,
                            s32 unused6);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, Vec02* axis);

void StepPlayerOnPath(Player* self)
{
    Mat02 placed;
    Mat02 goal;
    Mat02 delta;
    Vec02 axis;
    Vec02 k;
    Vec02 angle;
    PlaceOnPathAt(self, (PathObject*)self->aimCurve, &placed, self->pathPos);
    if (self->subState == 0x17 || self->subState == 0x1B) {
        PathWatch* w = (PathWatch*)self->stateAnimPlayer;
        f32 dt = g_gameClock.dt;
        f32 t = w->target->f34 - w->f14;
        BlendRotationsWithSpin(dt >? t, dt, 1.0f, &self->rot, &self->v160, &placed, &D_00248D30, &goal, 0, 0);
    } else {
        goal = placed;
    }
    MultiplyMatrices3x3(&self->rot, &goal, &delta);
    MatrixToAxisAngle(&delta, (f32*)&angle, &axis);
    Vu0::Q(k) = Vu0::FromFloat(angle.x / g_gameClock.dt);
    Vu0::Q(self->v160) = Vu0::MulX(Vu0::Q(axis), Vu0::Q(k));
}

extern f32 D_00274F0C;

// The pad's stick (+0x40, +0x44) as ControlPlayerOnPath reads it.
struct PathPad { u8 pad00[0x40]; f32 x; f32 y; };

// The easing ApproachValueWithRamp takes: a rate, then two more values.
struct PathRamp { f32 rate; f32 f04; f32 f08; f32 f0C; };

struct Vec02;
struct RampProfile;
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
u128 ApproachPointWithRamp(u128 from, u128 to, RampProfile* ramp, Vec02* vel, f32 limit);
void ProjectPointToCamera(Camera* camera, Vec02* in, f32* out);
struct RampProfile;
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
f32 WrapModulo(f32 a, f32 b);
void SetBlendItemWeights(BlendAnimationView* self, s32 a1, s32 a2, void* a3);
void SetPlayerState(Player* self, s32 state, s32 sub);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
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
    PathObject* path = (PathObject*)self->aimCurve;
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

    Vu0::Q(self->pathPoseOffset) = ApproachPointWithRamp(Vu0::Q(self->pathPoseOffset), Vu0::Q(D_00248D30), (RampProfile*)g_pathVelocityRamp, 0,
                                                g_gameClock.dt);
    if (self->subState == 0x17 || self->subState == 0x1B) {
        Vu0::Set(self->headingVelocity, Vu0::Zero());
        return;
    }
    if (holder->desc->m2) {
        holder->desc->m2(holder, &a, self->pathPos + D_00274F14, 0);
    }
    if (holder->desc->m2) {
        holder->desc->m2(holder, &b, self->pathPos - D_00274F14, 0);
    }
    TransformPointBetweenFrames(path->frame, 0, &a, &a);
    TransformPointBetweenFrames(path->frame, 0, &b, &b);
    Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Sub(Vu0::Q(a), Vu0::Q(b)), Vu0::Q(g_unitZVector)));
    if (self->padSelectMode == -1) {
        if (g_steepSlopeThreshold < __builtin_fabsf(dir.z)) {
            if (0.0f < dir.z) {
                if (self->pathFlipped != 0) {
                    SetPlayerState(self, 7, 0x1B);
                    return;
                }
            } else if (self->pathFlipped == 0) {
                SetPlayerState(self, 7, 0x1B);
                return;
            }
        }
        if (g_pathTurnThreshold < self->pathSpeedEased && self->pathFlipped != 0 && -D_00274F0C < dir.z) {
            SetPlayerState(self, 7, 0x1B);
            return;
        }
        if (self->pathSpeedEased < -g_pathTurnThreshold && self->pathFlipped == 0 && dir.z < D_00274F0C) {
            SetPlayerState(self, 7, 0x1B);
            return;
        }
    }
    if (path->guide == 0) {
        ProjectPointToCamera(g_camera, &a, (f32*)&pa);
        ProjectPointToCamera(g_camera, &b, (f32*)&pb);
    } else {
        Vec02 c;
        Vec02 d;
        void* frame = path->guide->frame;
        PathHolder* guide = path->guide->holder;
        TransformPointBetweenFrames(0, (PlacedObject*)frame, &self->v140, &c);
        if (guide->desc->m10) {
            guide->desc->m10(guide, &c, 0, 0, 0, 0, &t);
        }
        t = ClampBetween(t, D_00274F14, guide->desc->m8(guide) - D_00274F14);
        if (guide->desc->m2) {
            guide->desc->m2(guide, &c, t + D_00274F14, 0);
        }
        TransformPointBetweenFrames((PlacedObject*)frame, 0, &c, &d);
        ProjectPointToCamera(g_camera, &c, (f32*)&pa);
        if (guide->desc->m2) {
            guide->desc->m2(guide, &c, t - D_00274F14, 0);
        }
        TransformPointBetweenFrames((PlacedObject*)frame, 0, &c, &d);
        ProjectPointToCamera(g_camera, &c, (f32*)&pb);
    }
    Vu0::Set(dir, Vu0::Sub(Vu0::Q(pa), Vu0::Q(pb)));
    dir.z = 0.0f;
    Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Q(dir), Vu0::Q(g_unitYVector)));
    switch (self->padSelectMode) {
    case 0:
        state = self->pathFlipped ? 0x1A : 0x19;
        amount = 1.0f;
        break;
    case 1:
        state = self->pathFlipped ? 0x19 : 0x1A;
        amount = 1.0f;
        break;
    default: {
        Vec02 stick;
        Vu0::Set(stick, Vu0::FromFloats(pad->x, pad->y, 0.0f));
        f32 mag = NormalizeVector(stick, D_00248D30);
        amount = Vu0::ToFloat(Vu0::Dot(Vu0::Q(dir), Vu0::Q(stick)));
        switch (self->pathStickSide) {
        case 0:
            if (mag < 0.25f) {
                self->pathStickSide = -1;
            } else if (amount < -0.7f) {
                self->pathStickSide = 1;
            }
            break;
        case 1:
            if (mag < 0.25f) {
                self->pathStickSide = -1;
            } else if (0.7f < amount) {
                self->pathStickSide = 0;
            }
            break;
        case -1:
            if (0.35f < mag) {
                if (0.0f <= amount) {
                    self->pathStickSide = 0;
                } else {
                    self->pathStickSide = 1;
                }
            }
            break;
        }
        switch (self->pathStickSide) {
        case 0:
            state = self->pathFlipped ? 0x1A : 0x19;
            amount = mag;
            break;
        case 1:
            state = self->pathFlipped ? 0x19 : 0x1A;
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
    rev = self->pathFlipped;
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
    self->pathSpeedEased = -k * vel / ramp.rate + (1.0f - k) * self->pathSpeedEased;
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
        ApproachValueWithRamp(self->pathPos, start, g_gameClock.dt, (RampProfile*)&ramp, &lo);
        ApproachValueWithRamp(self->pathPos, end, g_gameClock.dt, (RampProfile*)&ramp, &hi);
        vel = ClampBetween(vel, -hi, -lo);
    }
    self->pathSpeed = -vel;
    self->pathPos += -vel * g_gameClock.dt;
    if (holder->closed != 0) {
        self->pathPos = WrapModulo(self->pathPos, holder->desc->m8(holder));
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
        SetBlendItemWeights((BlendAnimationView*)self->f105C, 0x10, 2, self->f103C);
    }
    SetPlayerState(self, 7, state);
}

void BuildPerpendicularPair(Vec02* dir, Vec02* a, const Vec02* b, const Vec02* c);
s32 CreatePooledContact(void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7, f32 f);

// The player held on its path: the contact row for the path's frame's root (or the player's own
// list at +0x4B4 when the frame has no flag 2), the point and direction at the player's length in
// world space, and three contacts of kind 0xB, along the two directions across the path and along
// it, each at the offset of the player's point from the path's. The float is the last parameter of
// CreatePooledContact here, as for func_0013B9D8: the $f12 move then follows the integer argument
// moves in insn order, which sched1's tie-break needs (docs/TOOLCHAIN.md, "local-alloc").
void PinPlayerToPath(Player* self)
{
    Vec02 pos;
    Vec02 dir;
    Vec02 local;
    Vec02 delta;
    Vec02 perp[2];
    PathObject* path = (PathObject*)self->aimCurve;
    Contact03** link;
    ContactRow03* row;
    if (path->frame != 0 && (path->frame->desc->flags & 2) != 0) {
        ContactRow03* r = self->contacts->head;
        Collider* key = (Collider*)path->frame->root;
        while (r != 0 && r->other != key) {
            r = r->next;
        }
        row = r;
        link = row->link;
    } else {
        link = &self->contacts4B4;
        row = (ContactRow03*)link;
    }
    if (((PathObject*)self->aimCurve)->holder->desc->m2 != 0) {
        ((PathObject*)self->aimCurve)->holder->desc->m2(((PathObject*)self->aimCurve)->holder, &pos, self->pathPos, &dir);
    }
    TransformPointBetweenFrames(((PathObject*)self->aimCurve)->frame, 0, &pos, &pos);
    TransformDirectionBetweenFrames(((PathObject*)self->aimCurve)->frame, 0, &dir, &dir);
    Vu0::Set(dir, Vu0::NormalizeOrMoved(Vu0::Q(dir), *(const u128*)&g_unitZVector));
    BuildPerpendicularPair(&dir, perp, &g_unitXVector, &g_unitZVector);
    TransformPointBetweenFrames(self, 0, (Vec02*)&self->f23E0, &local);
    Vu0::Q(delta) = Vu0::Sub(Vu0::Add(Vu0::Q(local), Vu0::Q(self->pathPoseOffset)), Vu0::Q(pos));
    CreatePooledContact(self, path->frame, &local, &perp[0], 0xB, 0, 0, row, Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(delta), Vu0::Q(perp[0]))));
    CreatePooledContact(self, path->frame, &local, &perp[1], 0xB, 0, 0, row, Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(delta), Vu0::Q(perp[1]))));
    CreatePooledContact(self, path->frame, &local, &dir, 0xB, 0, 0, row, Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(delta), Vu0::Q(dir))));
    *link = (Contact03*)row->head;
}

void AcquirePadSelectFlag(World* a0);
void ShowCountedScreenElement(World* self);
void ReleasePadSelectFlag(World* self);
void HideCountedScreenElement(World* self);

void SetPlayerPadSelectMode(Player* a0, s32 a1)
{
    if (a0->padSelectMode != a1) {
        if (a0->padSelectMode == -1) {
            AcquirePadSelectFlag(a0->world);
            ShowCountedScreenElement(a0->world);
        }
        a0->padSelectMode = a1;
        if (a1 == -1) {
            ReleasePadSelectFlag(a0->world);
            HideCountedScreenElement(a0->world);
        }
    }
}

void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void SetPlayerState(Player* self, s32 state, s32 sub);

void SetPlayerPath(Player* self, PathObject* path)
{
    Vec02 pos;
    Mat02 rot;
    Vec02 local;
    Vec02 world;
    if ((PathObject*)self->aimCurve != path) {
        if (self->state == 7) {
            TriggerScriptEvent((BaseObject*)self->aimCurve, 3, 0, 0);
            ((PathObject*)self->aimCurve)->desc->m18((BaseObject*)self->aimCurve, self);
            TriggerScriptEvent((BaseObject*)path, 2, 0, 0);
            path->desc->m17((BaseObject*)path, self);
        }
        self->aimCurve = (s32)path;
        self->boundObject = 0;
        self->aimTarget = 0;
        TransformPointBetweenFrames(0, path->frame, &self->v140, &pos);
        if (path->holder->desc->m10 != 0) {
            path->holder->desc->m10(path->holder, &pos, 0, 0, 0, 0, &self->aimCurvePos);
        }
    }
    PlaceOnPathAt(self, path, &rot, self->aimCurvePos);
    self->desc02()->m1E(self, &rot);
    if (path->holder->desc->m2 != 0) {
        path->holder->desc->m2(path->holder, &pos, self->aimCurvePos, 0);
    }
    TransformPointBetweenFrames(path->frame, self, &pos, &local);
    Vu0::Q(local) = Vu0::Sub(Vu0::Q(local), Vu0::Q(*(Vec02*)((u8*)self + 0x23E0)));
    TransformPointBetweenFrames(self, 0, &local, &world);
    self->desc02()->m1D(self, &world);
    SetPlayerState(self, 7, 0x17);
}
