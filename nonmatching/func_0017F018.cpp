// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 2740/2728, checked 2026-11-08
// NEAR (2026-11-08, night-large3): func_0017F018, the airborne player's step (91.8% of the
// words): both jump tables, every case in retail's block order and the leap-record updates
// follow retail. Left: state 6 jumps into state 7's compare (sub.s, c.lt.s) by cross-jumping in
// retail, after loading 0x2224 into $f2 and the 0.15 into $f1 with the clock in the delay slot;
// ours loads the clock first and keeps its own sub.s and c.lt.s, 12 bytes longer.
#include "common.h"
#include "point_object.h"
#include "collider.h"
#include "globals.h"
#include "shapes.h"
#include "placed_object.h"
#include "asm_func.h"
#include "fpu.h"
#include "vu0.h"
#include "switched_collider.h"

extern f32 D_00263E50;
extern f32 D_00263E54;
extern f32 D_00263E70;
extern f32 D_00263E74;
extern f32 D_00264040;
extern f32 D_00264044;
extern f32 D_00264048[2];
void PlaceOnTargetCurve(void* curve, Vec02* out, s32 a, f32 t);
void PlaceOnTargetPoint(void* point, Vec02* out, s32 a, f32 t);
s32 AimPlayerAtTarget(void* self);
Contact03* func_0017E3C8(Player* self, s32* end, Vec02* at);
s32 func_0017ECE8(Player* self);
void LaunchPlayerAtTarget(Player* self, void* s2, f32 f);
void ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, s32 c, Vec02* vel, s32 d, f32 t);
s32 ChoosePlayerNextState(Player* self);
f32 GetAnimationMarkerTime(void* obj, s32 id);
void func_0017E710(Player* self);
void SeekAnimationPlayer(void* obj, s32 a1, f32 fa, f32 fb);
void TransformPointAtTime(void* frame, s32 a, Vec02* point, s32 b, Vec02* vel, s32 d, f32 t);
void func_001CEB18(f32 t, Player* p, void* frame, void* point, s32 a, Vec02* aim, Vec02* land);
void EvaluateHermiteVectorSegment(f32 t, f32 u, f32 v, void* p0, void* v0, void* p1, void* v1, Vec02* pos, s32 a, Vec02* vel);
void SetPlayerState(Player* self, s32 a, s32 b);
void TransformPointBetweenFrames(void* a, void* b, void* c, void* d);
f32 ArctangentOfRatio(f32 a, f32 b);
extern f32 g_gameTime;
extern f32 g_gameClock[];
extern u16 D_00262D18;

struct Leap_17F018 { u8 pad00[0x18]; f32 time; u8 pad1C[0x20 - 0x1C]; Vec02 aim; Vec02 land; };
struct Track_17F018;
struct TrackDesc_17F018 { void* m0; void (*m1)(Track_17F018* self, f32 t, Vec02* out, s32 a); };
struct Track_17F018 { TrackDesc_17F018* desc; };
struct TrackOwner_17F018 { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; Track_17F018* track; };
struct LeapTarget_17F018 { u8 pad00[0x18]; void* frame; u8 pad1C[0x40 - 0x1C]; union { Vec02 pos; s32 f40; }; u8 pad50[0x58 - 0x50]; s32 f58; };
struct Anim_17F018 { u8 pad00[0x14]; f32 f14; f32 f18; };

void func_0017F018(Player* p)
{
    Vec02 at;
    Vec02 b;
    Vec02 c;
    s32 end;
    if (p->f223C == -1) {
        switch (p->f2228) {
        case 13:
            ((void (*)(void*, s32, f32*, f32))PlaceOnTargetPoint)(p->f23A8, 0, &p->f638, p->f23AC);
            break;
        case 12:
            ((void (*)(void*, s32, f32*, f32))PlaceOnTargetCurve)(p->f23A0, 0, &p->f638, p->f23A4);
            break;
        default:
            if (D_00263E54 < Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(p->v150), Vu0::Q(p->v150))))) {
                p->f638 = ArctangentOfRatio(p->v150.y, p->v150.x);
            }
            break;
        case 0:
            p->f638 = p->f630;
            break;
        case 7:
        case 8:
            break;
        }
    } else if (AimPlayerAtTarget(p) == 0) {
        p->f638 = p->f630;
    }
    switch (p->f2270) {
    case 0:
        if (p->f634 == 1.0f) {
            p->f2270 = 1;
            p->f2278 = g_gameTime;
        } else if (D_00263E70 < g_gameTime - p->f2274) {
            p->f2268 = 1;
        }
        break;
    case 1:
        if (p->f634 < 1.0f) {
            p->f2270 = 2;
            p->f227C = g_gameClock[1];
            if (g_gameClock[1] - p->f2278 < D_00263E74) {
                p->f2268 = 1;
            }
        }
        break;
    case 3:
        if (0.0f < p->f634) {
            p->f2268 = 1;
        }
        break;
    }
    Contact03* hit = func_0017E3C8(p, &end, &at);
    if (hit != 0) {
        ContactEnd03* e = &hit->end[1 - end];
        void* part = e->part;
        p->f24A0 = part;
        TransformPointBetweenFrames(0, part, &e->v10, p->f24B0);
        p->f24F0 = hit->kind;
        s32 key;
        if (end == 0) {
            key = hit->fA4;
        } else {
            key = hit->fA0;
        }
        p->f24F4 = key;
        p->v24C0 = at;
        SetPlayerState(p, 8, -1);
        return;
    }
    if (func_0017ECE8(p) != 0) {
        LaunchPlayerAtTarget(p, 0, 0.0f);
        return;
    }
    Leap_17F018* rec;
    switch (p->f2228) {
    case 0:
        if (p->v150.z < 0.0f) {
            SetPlayerState(p, 2, 2);
        } else if (D_00263E50 < g_gameTime - p->f222C) {
            if (!(D_00262D18 & 0x40) && p->f2270 != 3) {
                p->f2268 = 1;
            }
            SetPlayerState(p, 2, 1);
        }
        break;
    case 1:
    case 5:
        if (p->f690 != 0 && 0.15f < g_gameTime - p->f2224) {
            SetPlayerState(p, ChoosePlayerNextState(p), -1);
        } else if (p->v150.z < 0.0f) {
            SetPlayerState(p, 2, 2);
        }
        break;
    case 6:
        if (p->f690 != 0 && 0.15f < g_gameTime - p->f2224) {
            SetPlayerState(p, ChoosePlayerNextState(p), -1);
        }
        break;
    case 2:
        if (p->f690 != 0) {
            SetPlayerState(p, ChoosePlayerNextState(p), -1);
        }
        break;
    case 4:
        rec = (Leap_17F018*)p->f2514;
        if (rec->time < g_gameClock[1]) {
            p->f239C = 2;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        ComputeObjectFrameAtTime(p->heldObject, 0, &b, 0, &c, 0, rec->time - g_gameClock[1]);
        ((Leap_17F018*)p->f2514)->aim = b;
        ((Leap_17F018*)p->f2514)->aim.z += 75.0f;
        ((Leap_17F018*)p->f2514)->land = c;
        ((Leap_17F018*)p->f2514)->land.z = p->v150.z + (((Leap_17F018*)p->f2514)->time - g_gameClock[1]) * p->gravity.z;
        break;
    case 7:
        if (p->f690 != 0 && D_00264040 < g_gameTime - p->f222C) {
            SetPlayerState(p, ChoosePlayerNextState(p), -1);
        }
        break;
    case 8:
        if (p->f690 != 0 && D_00264044 < g_gameTime - p->f222C) {
            f32 t = GetAnimationMarkerTime(p->f25C8, 0x1BB);
            if (((Anim_17F018*)p->watched2230)->f14 < t) {
                func_0017E710(p);
                SeekAnimationPlayer(p->watched2230, 0, t, ((Anim_17F018*)p->watched2230)->f18);
            }
        }
        break;
    case 9:
        rec = (Leap_17F018*)p->f2514;
        if (rec->time < g_gameClock[1]) {
            SetPlayerState(p, 2, 2);
            break;
        }
        b = ((LeapTarget_17F018*)p->f23B4)->pos;
        c = D_00248D30;
        TransformPointAtTime(((LeapTarget_17F018*)p->f23B4)->frame, 0, &b, 0, &c, 0, rec->time - g_gameClock[1]);
        ((Leap_17F018*)p->f2514)->aim = b;
        ((Leap_17F018*)p->f2514)->aim.z += 75.0f;
        ((Leap_17F018*)p->f2514)->land = c;
        ((Leap_17F018*)p->f2514)->land.z = p->v150.z + (((Leap_17F018*)p->f2514)->time - g_gameClock[1]) * p->gravity.z;
        break;
    case 10:
        rec = (Leap_17F018*)p->f2514;
        if (rec->time < g_gameClock[1]) {
            p->f239C = 5;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        b = ((LeapTarget_17F018*)p->f23B8)->pos;
        c = D_00248D30;
        TransformPointAtTime(((LeapTarget_17F018*)p->f23B8)->frame, 0, &b, 0, &c, 0, rec->time - g_gameClock[1]);
        ((Leap_17F018*)p->f2514)->aim = b;
        ((Leap_17F018*)p->f2514)->aim.z += 75.0f;
        ((Leap_17F018*)p->f2514)->land = c;
        ((Leap_17F018*)p->f2514)->land.z = p->v150.z + (((Leap_17F018*)p->f2514)->time - g_gameClock[1]) * p->gravity.z;
        break;
    case 11: {
        rec = (Leap_17F018*)p->f2514;
        if (rec->time < g_gameClock[1]) {
            p->f239C = 4;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        Track_17F018* t = ((TrackOwner_17F018*)p->f23BC)->track;
        if (t->desc->m1 != 0) {
            t->desc->m1(t, p->f23C0, &b, 0);
        }
        TransformPointAtTime(((TrackOwner_17F018*)p->f23BC)->frame, 0, &b, 0, 0, 0, ((Leap_17F018*)p->f2514)->time - g_gameClock[1]);
        ((Leap_17F018*)p->f2514)->aim = b;
        ((Leap_17F018*)p->f2514)->aim.z += 75.0f;
        break;
    }
    case 13:
        rec = (Leap_17F018*)p->f2514;
        if (rec->time < g_gameClock[1]) {
            p->f239C = ((LeapTarget_17F018*)p->f23A8)->f58;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        PlaceOnTargetPoint(p->f23A8, &b, 0, p->f23AC);
        TransformPointBetweenFrames(0, ((LeapTarget_17F018*)p->f23A8)->frame, &b, &b);
        c = D_00248D30;
        TransformPointAtTime(((LeapTarget_17F018*)p->f23A8)->frame, 0, &b, 0, &c, 0, ((Leap_17F018*)p->f2514)->time - g_gameClock[1]);
        ((Leap_17F018*)p->f2514)->aim = b;
        ((Leap_17F018*)p->f2514)->aim.z += 75.0f;
        ((Leap_17F018*)p->f2514)->land = c;
        ((Leap_17F018*)p->f2514)->land.z = p->v150.z + (((Leap_17F018*)p->f2514)->time - g_gameClock[1]) * p->gravity.z;
        break;
    case 12:
        rec = (Leap_17F018*)p->f2514;
        if (rec->time < g_gameClock[1]) {
            p->f239C = ((LeapTarget_17F018*)p->f23A0)->f40;
            SetPlayerState(p, 6, 0x10);
            break;
        }
        PlaceOnTargetCurve(p->f23A0, &b, 0, p->f23A4);
        TransformPointBetweenFrames(0, ((LeapTarget_17F018*)p->f23A0)->frame, &b, &b);
        c = D_00248D30;
        TransformPointAtTime(((LeapTarget_17F018*)p->f23A0)->frame, 0, &b, 0, &c, 0, ((Leap_17F018*)p->f2514)->time - g_gameClock[1]);
        ((Leap_17F018*)p->f2514)->aim = b;
        ((Leap_17F018*)p->f2514)->aim.z += 75.0f;
        ((Leap_17F018*)p->f2514)->land = c;
        ((Leap_17F018*)p->f2514)->land.z = p->v150.z + (((Leap_17F018*)p->f2514)->time - g_gameClock[1]) * p->gravity.z;
        break;
    case 14:
        rec = (Leap_17F018*)p->f2514;
        if (rec->time < g_gameTime) {
            SetPlayerState(p, 3, 0x33);
        } else {
            func_001CEB18(rec->time - g_gameTime, p, ((TrackOwner_17F018*)p->f2204)->frame, (u8*)p->f2204 + 0x40, 0, &rec->aim, &rec->land);
        }
        break;
    case 15:
        if (((Leap_17F018*)p->f2514)->time < g_gameTime) {
            SetPlayerState(p, 7, 0x17);
        }
        break;
    case 3:
        if (p->f690 != 0) {
            SetPlayerState(p, ChoosePlayerNextState(p), -1);
        }
        break;
    }
    if (p->f2228 < 16) {
        if (p->f2228 >= 9) {
            f32 t = ((Leap_17F018*)p->f2514)->time - g_gameClock[1] + g_gameClock[2];
            EvaluateHermiteVectorSegment(t, 0.0f, 1.0f, &p->pos, &p->v150, &((Leap_17F018*)p->f2514)->aim, &((Leap_17F018*)p->f2514)->land, 0, 0, &b);
            EvaluateHermiteVectorSegment(t, t, 1.0f, &p->pos, &p->v150, &((Leap_17F018*)p->f2514)->aim, &((Leap_17F018*)p->f2514)->land, 0, 0, &c);
            if (D_00264048[0] < (Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(b))) + Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(c)))) * (t * 0.5f)) {
                SetPlayerState(p, 2, 2);
            }
        }
    }
}
