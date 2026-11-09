// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1635/1660 (98.5%), checked 2026-11-08
#include "common.h"
#include "shapes.h"
#include "vu0.h"
#include "switched_collider.h"
#include "globals.h"
#include "item_keeper.h"
#include "c62.h"
#include "animation.h"
#include "attachment.h"
#include "anim_curve.h"
// NEAR (2026-11-08, night-large4, w4-1C9DE0): every instruction is retail's but for the
// registers of kind 0x13's player and animation and what follows from them: retail gives the
// player (msg->source) s0 and its animation s3, here the other way round, which moves the
// 0x1AC markers' registers (from and to: retail s2 and s0, here s3 and s2).
// Mechanism: global.c's allocno_compare orders by floor_log2(refs) * refs / live length, the
// lengths sched1's update_reg_usage leaves. The animation (13 refs over 84 insns, 0.464) goes
// before the player (4 over 34, 0.235) and the 0x1AC `to` (6 over 39, 0.308), and pass 0 of
// find_reg gives it s0, the first saved register already in use (local-alloc put `kind` there).
// Retail's order needs the player or `to` before the animation: the player with 8 refs or a
// life of at most 17 insns, `to` with 8 refs, or the animation with at most 7 refs or a life of
// 166 insns. Pinning the animation to s3 (a diagnostic only) gives retail's registers here.
// Ruled out: s0 in regs_someone_prefers (no pseudo relates to s0 but `kind`, in block 0); the
// player through msg->source again, read after the test, declared after the animation, or as
// self->f7E0 (cse folds them all into one pseudo: same counts); an if around the inner switch;
// a copy of the animation in 0x1AC, or 0x1AC as an inline helper (cse/cprop fold the copy, the
// helper changes code); the 0x138 test through player->anim (code changes).
// Levers that gave the rest: the -1.0 weight as a u128 stored to its slot after the rotation
// (as func_001C9AF8), the colliders' ternaries with the sender's first, the item keeper's test
// as if/else with state = 2 in the else; the curve's eval with its floats after the owner
// (include/anim_curve.h: the first call in 0x1AC then sets $f13 before $a2, a LUID tie in
// sched1); and the curve read inside each eval call in 0x1AC instead of a local `c`, which
// keeps sched1 from loading anim->f9C before the alternative marker's conditional move: the
// load's pseudo then no longer conflicts with the alternative, whose regs_someone_prefers lost
// $v1, so the alternative is in $v1 as retail's and sched2 fills the fourth call's slot with
// li a1 (the a1 output dependence gone).
#define F(T, o) (*(T*)((u8*)self + (o)))
extern f32 g_gameClock[];
f32 RandomFloatInRange(f32 a, f32 b);
void SetStateAndNotify(C62* p, s32 z);
void CreateAgentAnimationPlayer(Agent* self);
void SeekAnimationPlayer(void* obj, s32 a1, f32 fa, f32 fb);
s32 TestAgentTargetContact(Agent* self, s32 key, Collider* other);

// What HandleAgentNotification is handed with a notification: the sender first, then a time or
// an object, then an event code.
struct AgentNotification {
    void* source;           // 0x00
    union {
        f32 time;           // 0x04
        void* obj;          // 0x04
    };
    s32 code;               // 0x08
};

void HandleSwitchedColliderNotification(Agent* self, s32 kind, void* msg);
void SetAgentMainClip(Agent* self, s32 clip);
AnimEvent* FindAnimationMarkerEvent(Animation* self, s32 key);
s32 func_001A8C90(void* a, s32 b);
s32 GatherObjectsById(void* host, s32 a1, s32 a2, void* ctx, s32 a4, void* out);
typedef void (*AgentSlotFn)(Agent* self);

void HandleAgentNotification(Agent* self, s32 kind, AgentNotification* msg)
{
    HandleSwitchedColliderNotification(self, kind, msg);
    switch (kind) {
    case 5:
        if ((void*)msg == self->f7E0) {
            self->f72C |= 2;
        } else if ((void*)msg == self->f754) {
            SetAgentMainClip(self, 0);
        }
        break;
    case 0x15: {
        if (msg->source != self->f754) {
            break;
        }
        C62* obj = (C62*)msg->obj;
        self->fA74 = obj;
        obj->desc->m17(obj, self);
        self->f72C |= 1;
        self->f730 = (void*)3;
        s32 state;
        s32 id = ((C62*)self->fA74)->id2E0;
        ItemKeeper* keeper;
        if (id != -1 && (keeper = (ItemKeeper*)self->f720) != 0) {
            if (keeper->f180 == -1) {
                keeper->f180 = id;
            }
            state = ((ItemKeeper*)self->f720)->f180 == ((C62*)self->fA74)->id2E0 ? 1 : 2;
        } else {
            state = 2;
        }
        SetStateAndNotify((C62*)self->fA74, state);
        break;
    }
    case 0x16:
        if (msg->source != self->fA74) {
            break;
        }
        switch (msg->code) {
        case 2:
            if (self->f724 == 3) {
                CreateAgentAnimationPlayer(self);
            }
            break;
        case 0:
            self->f730 = (void*)1;
            self->f72C |= 1;
            break;
        }
        break;
    case 0x13: {
        AnimationPlayer* player = (AnimationPlayer*)msg->source;
        Animation* anim = player->anim;
        if (player != self->f7E0) {
            break;
        }
        switch (msg->code) {
        case 0x138:
            if (anim->f9C == 0) {
                break;
            }
        slope: {
            Vec02 v;
            Vec02 w;
            PositionCurve* c = anim->f9C->pos;
            c->vt->eval(c, self, msg->time, player->speed, 0, 0, &v);
            u128 s = Vu0::FromFloat(-1.0f);
            Vu0::Q(F(Vec02, 0x640)) = Vu0::MulX(Vu0::Q(v), s);
            Vu0::Q(v) = Vu0::Rotate(F(Mat02, 0x660), Vu0::Q(v));
            Vu0::Q(w) = s;
            self->desc02()->m20(self, &v);
            break;
        }
        case 0x1A6:
            if (FindAnimationMarkerEvent(anim, 0x1A7) == 0) {
                break;
            }
            if (anim->f9C == 0 || anim->f9C->pos == 0) {
                break;
            }
            self->fB78 = 1;
            goto slope;
        case 0x1A7:
            self->fB78 = 0;
            break;
        case 0x1AC: {
            F(s32, 0xB90) = 1;
            self->fA60 = 0;
            AnimEvent* from = FindAnimationMarkerEvent(anim, 0x1AE);
            AnimEvent* mid = FindAnimationMarkerEvent(anim, 0x1AF);
            AnimEvent* to = FindAnimationMarkerEvent(anim, 0x1B1);
            AnimEvent* alt = FindAnimationMarkerEvent(anim, 0x1B0);
            if (from == 0 || to == 0 || mid == 0) {
                break;
            }
            if (alt != 0) {
                to = alt;
            }
            Vec02 p0;
            Vec02 p1;
            f32 zero = 0.0f;
            anim->f9C->pos->vt->eval(anim->f9C->pos, self, from->a0.f, zero, 0, &p0, 0);
            anim->f9C->pos->vt->eval(anim->f9C->pos, self, to->a0.f, zero, 0, &p1, 0);
            F(f32, 0xB94) = p1.x - p0.x;
            F(f32, 0xB98) = (to->a0.f - from->a0.f) / *(f32*)&anim->props6C[0x10];
            break;
        }
        case 0x1AD:
            F(s32, 0xB90) = 0;
            break;
        case 0x1AE:
            ((AgentSlotFn)self->desc08()->m61)(self);
            break;
        case 0x1AF:
            self->fB8C = 1;
            break;
        case 0x1B1:
            if (self->fB8C != 0) {
                AnimEvent* e = FindAnimationMarkerEvent(anim, 0x1B0);
                f32 t = e != 0 ? e->a0.f : msg->time;
                SeekAnimationPlayer(self->f7E0, 0, t, e != 0 ? 1.0f : 0.0f);
            }
            break;
        case 0x1AA:
            self->fB84 = 1;
            break;
        case 0x1AB:
            self->fB84 = 0;
            break;
        case 0x1A8:
            self->fB7C = 1;
            break;
        case 0x1A9:
            self->fB7C = 0;
            break;
        case 0x1B2:
            self->fBD8 = 1;
            break;
        case 0x1B3:
            self->fBD8 = 0;
            break;
        case 0x1A5: {
            u8* g = (u8*)self->fB0C;
            if (g != 0) {
                if (*(s32*)(g + 0x50) == -1) {
                    *(void**)(g + 0xE0) = self->desc08()->m62(self);
                }
                func_001A8C90(self->fB0C, 1);
            }
            break;
        }
        }
        break;
    }
    case 0xA:
        if (msg->obj == self && self->fB8C != 0) {
            ((AgentSlotFn)self->desc08()->m60)(self);
        }
        break;
    case 0x17: {
        Collider* mine = (((Collider*)msg->source)->desc->flags & 2) ? (Collider*)msg->source : 0;
        Collider* other = (((Collider*)msg->obj)->desc->flags & 2) ? (Collider*)msg->obj : 0;
        if (TestAgentTargetContact(self, (s32)mine, other) == 0) {
            break;
        }
        Collider* found[32];
        f32 dist = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(mine->v140))));
        s32 count = 0;
        s32 nearer = 0;
        s32 n = GatherObjectsById(self->world, 5, 8, 0, 0x20, found);
        for (s32 i = 0; i < n; i++) {
            Agent* o = (Agent*)found[i];
            if (o == self) {
                continue;
            }
            if (TestAgentTargetContact(o, (s32)mine, other) == 0) {
                continue;
            }
            count++;
            s32 closer = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(o->v140), Vu0::Q(mine->v140)))) < dist;
            nearer += closer;
        }
        if (nearer == 0) {
            self->fBFC = g_gameClock[1] + F(f32, 0xBE0);
        } else {
            f32 r = RandomFloatInRange((f32)(nearer - 1) / (f32)count, (f32)nearer / (f32)count);
            self->fBFC = g_gameClock[1] + (1.0f - r) * F(f32, 0xBE0) + r * F(f32, 0xBE4);
        }
        break;
    }
    }
}
