// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1781/1916 (93.0%), checked 2026-11-08
// CONV-SWAP (2026-11-08): ToFloat and ToFloatMoved swapped at call combo (source line 1+2+4); 64 differing lines before, 41 now.
#include "common.h"
#include "vu0.h"
#include "globals.h"
#include "switched_collider.h"
#include "attachment.h"
#include "value_range.h"
// NEAR (2026-11-08, night-large7): 81 instructions differ, the size and frame retail's. Found:
// the clock read through inline accessors taking its address (ClockDt, ClockTime) gives retail's
// form, the address formed from a high part kept in s6 (addiu s0, s6, %lo) and the fields read
// at their offsets, where a plain read folds the offset into the address and takes a register
// more; the first direction normalised in place by an inline function (NormalizeInPlace) loads
// the fallback's address before the difference, as retail; the direction read at each use;
// ValueRange::Limit for the clamp. Still differs: scheduling around the first split (the &dir
// argument and the length's mtc1 come earlier in retail), the length's division before the
// second square root, the dt Scalar's load after w2's, the curve's address before its first
// product, and at the end retail loads dt's bits into the clock pointer's own register as it dies
// (lw s0, 8(s0); qmtc2 s0) and schedules the final block otherwise.

extern f32 D_00274D40;
extern f32 D_00274D44;
extern f32 D_00274D48;
extern f32 D_00274D4C;
extern f32 D_00274D50[4];
extern f32 D_00274D60[4];
extern f32 D_00274D70[4];
extern f32 D_00274D80;
extern f32 D_00274D84;
extern f32 g_gameClock[];
// The game clock as the link reads it.
struct LinkClock { s32 running; f32 time; f32 dt; };
static inline const f32& ClockDt(const LinkClock* c) { return c->dt; }
static inline f32 ClockTime(const LinkClock* c) { return c->time; }
struct LinkAnchor { u8 pad0[0x18]; void* parent; u8 pad1C[0xB0 - 0x1C]; f32 fB0; };
struct LinkSystem { u8 pad0[4]; PlacedObject* object; };

s32 GetObjectWorldPosition(void* self, Vec02* out);
void GetObjectWorldRotation(void* obj, Mat02* out);
void ComputeObjectMotionInFrame(void* obj, s32 b, Vec02* pos, Vec02* vel, s32 e, s32 f, s32 g);
f32 SplitVectorAlongAxis(Vec02* v, Vec02* axis, Vec02* along, Vec02* across);
f32 ApproachValueClampingVelocity(f32 a, f32 b, f32 c, f32 d, f32* params, f32* out);
void ComputePositionSpringAcceleration(PlacedObject* obj, Vec02* pos, Vec02* vel, Vec02* out, f32 dt);
void ComputeRotationSpringAcceleration(PlacedObject* obj, Mat02* rot, Vec02* vel, Vec02* out, f32 dt);
void TransformDirectionBetweenFrames(void* from, void* to, Vec02* in, Vec02* out);
void BuildRotationFromVector(Vec02* in, Mat02* out);
void SolvePlayerLinkSystem(Player* self, PlacedObject* obj, Vec02* pos, Vec02* accel, Vec02* out);

// The player swinging on the link (states 0x32 and 0x34 pump it): the anchor's frame and
// motion, the swing's turning about the anchor eased and damped, its length kept, and the
// acceleration that gives it, handed to the link's system when there is one.
// v made unit length in place, or the fallback when it is shorter than 0.0001; its length.
static inline f32 NormalizeInPlace(Vec02* v, const Vec02& fallback)
{
    u128 len = Vu0::Length(Vu0::Q(*v));
    if (Vu0::ToFloat(len) < 0.0001f) {
        *v = fallback;
    } else {
        Vu0::Q(*v) = Vu0::DivX(Vu0::Q(*v), len);
    }
    return Vu0::ToFloatMoved(len);
}

void func_001CC818(Player* self)
{
    Vec02 pos;
    Vec02 delta;
    Vec02 vel;
    Vec02 dir;
    Mat02 rot;
    Vec02 rel;
    Vec02 across;
    Vec02 along;
    Vec02 n1;
    Vec02 w1;
    LinkAnchor* anchor = (LinkAnchor*)self->f2204;
    GetObjectWorldPosition(anchor, &pos);
    GetObjectWorldRotation((void*)self->f2204, &rot);
    ComputeObjectMotionInFrame(((LinkAnchor*)self->f2204)->parent, 0, &pos, &vel, 0, 0, 0);
    Vu0::Q(delta) = Vu0::Q(dir) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(pos));
    f32 dist = NormalizeInPlace(&dir, g_unitZVector);
    Vu0::Q(rel) = Vu0::Sub(Vu0::Q(self->v150), Vu0::Q(vel));
    f32 speed = SplitVectorAlongAxis(&rel, &dir, &along, &across);
    Vu0::Vec a1 = Vu0::NormalizeOr(Vu0::Cross(Vu0::Vec::Of(dir), Vu0::Vec::Of(across)), Vu0::Vec::Of(g_unitXVector));
    Vu0::Set(n1, a1.q);
    Vu0::Set(w1, Vu0::MulX(a1, Vu0::Vec::Scalar(Vu0::ToFloatMoved(Vu0::Length(Vu0::Vec::Of(across))) / dist)).q);
    Vu0::Vec gv = Vu0::Vec::Of(self->gravity);
    Vu0::Vec gp = Vu0::Sub(gv, Vu0::MulX(Vu0::Vec::Of(dir), Vu0::Dot(gv, Vu0::Vec::Of(dir))));
    Vec02 g;
    Vu0::Set(g, gp.q);
    Vu0::Vec a2 = Vu0::NormalizeOr(Vu0::Cross(Vu0::Vec::Of(dir), gp), Vu0::Vec::Of(g_unitYVector));
    Vec02 n2;
    Vu0::Set(n2, a2.q);
    Vec02 w2;
    Vu0::Set(w2, Vu0::MulX(a2, Vu0::Vec::Scalar(Vu0::ToFloat(Vu0::Length(Vu0::Vec::Of(g))) / dist)).q);
    f32 gain;
    if (self->f2228 == 0x32 || self->f2228 == 0x34) {
        gain = D_00274D44;
    } else {
        gain = D_00274D48;
    }
    Vec02 acc;
    Vec02 accAlong;
    Vec02 accAcross;
    Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(w1), Vu0::Q(w2), Vu0::ScalarAt(ClockDt((LinkClock*)g_gameClock)));
    SplitVectorAlongAxis(&acc, &rot.r[1], &accAlong, &accAcross);
    f32 dt = ClockDt((LinkClock*)g_gameClock);
    Vu0::Q(acc) = Vu0::MulXSum(Vu0::Q(accAlong), Vu0::Scalar(D_00274D40 * dt + 1.0f), Vu0::Q(accAcross), Vu0::Scalar(gain * dt + 1.0f));
    if (self->f2228 == 0x32 || self->f2228 == 0x34) {
        if (ClockTime((LinkClock*)g_gameClock) - self->f222C < D_00274D4C) {
            f32 push = dt * D_00274D50[0];
            if (self->f2228 == 0x32) {
                push = -push;
            }
            if (self->f22A8 != 0) {
                push = -push;
            }
            f32 l = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(across)));
            f32 gz = -self->gravity.z;
            f32 t = (gz * delta.z + l * (l * 0.5f)) / gz;
            push *= g_unitRange.Limit(D_00274D60[0] + t * (D_00274D60[1] + t * D_00274D60[2]));
            Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(acc), Vu0::Q(rot.r[1]), Vu0::Scalar(push));
        }
    }
    f32 rate;
    f32 r = ApproachValueClampingVelocity(dist, speed, D_00274D84 - ((LinkAnchor*)self->f2204)->fB0, ClockDt((LinkClock*)g_gameClock), D_00274D70, &rate);
    f32 lo = D_00274D80;
    f32 hi = D_00274D84;
    Vu0::Q(acc) = Vu0::MulX(Vu0::Q(acc), Vu0::Scalar((hi <? dist) / (lo >? r)));
    Vec02 v2;
    Vec02 lin;
    Vec02 ang;
    if (self->f22AC != 0) {
        PlacedObject* o = ((LinkSystem*)self->f22AC)->object;
        Attachment* a = o->f1EC;
        if (a != 0 && a->mode0 == 1) {
            Vec02 p;
            Vec02 v;
            a->vt->getPos(a, 0.0f, &p, &v);
            ComputePositionSpringAcceleration(o, &p, &v, &lin, ClockDt((LinkClock*)g_gameClock));
            TransformDirectionBetweenFrames(o->parent, 0, &lin, &lin);
        } else {
            lin = D_00248D30;
        }
        a = o->f1F0;
        if (a != 0 && a->mode1 == 1) {
            Mat02 m;
            Vec02 w;
            a->vt->getRot(a, 0.0f, &m, &w);
            ComputeRotationSpringAcceleration(o, &m, &w, &ang, ClockDt((LinkClock*)g_gameClock));
            TransformDirectionBetweenFrames(o->parent, 0, &ang, &ang);
        } else {
            ang = D_00248D30;
        }
        u128 h = Vu0::ScalarAt(ClockDt((LinkClock*)g_gameClock));
        Vu0::Q(v2) = Vu0::MulAddX2(Vu0::Q(vel), Vu0::Q(lin), h, Vu0::Cross(Vu0::Q(ang), Vu0::Sub(Vu0::Q(pos), Vu0::Q(o->v140))), h);
    } else {
        v2 = vel;
    }
    Vec02 p;
    Vec02 v;
    Mat02 m;
    Vu0::Q(lin) = Vu0::MulX(Vu0::Add(Vu0::Q(w1), Vu0::Q(acc)), Vu0::Scalar(ClockDt((LinkClock*)g_gameClock) * 0.5f));
    BuildRotationFromVector(&lin, &m);
    u128 nd = Vu0::Rotate(m, Vu0::Q(dir));
    u128 off = Vu0::MulX(nd, Vu0::Scalar(r));
    Vu0::Q(ang) = nd;
    Vu0::Q(v) = Vu0::Add(Vu0::Add(Vu0::Q(v2), Vu0::Cross(Vu0::Q(acc), off)), Vu0::MulX(nd, Vu0::ScalarAt(rate)));
    Vu0::Q(p) = Vu0::Add(Vu0::Q(pos), off);
    Vu0::Q(g) = Vu0::Sub(Vu0::DivX(Vu0::Sub(Vu0::Q(v), Vu0::Q(self->v150)), Vu0::ScalarAt(ClockDt((LinkClock*)g_gameClock))), Vu0::Q(self->gravity));
    if (self->f22AC != 0) {
        SolvePlayerLinkSystem(self, ((LinkSystem*)self->f22AC)->object, &pos, &g, &self->v22B0);
    } else {
        Vu0::Q(self->v22B0) = Vu0::Q(g);
    }
}
