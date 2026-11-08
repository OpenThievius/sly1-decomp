// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1290/1944 (66.4%), checked 2026-11-08
// NEAR (2026-11-08, night-large3): UpdateObjectGatherer (func_0019B378), 88.9% of the words. The
// logic, both switches (retail's jump tables) and the list walks follow retail; the frame is
// 0x10 larger: retail keeps the push vector at 0x20 with both MulXSum weights at 0x30 and the
// floor record at 0x40, and the list frames and the target point of state 2 at 0x20 too, which
// no scoping of these locals here has given (the Scalar slots land after the floor record).
// Also left: the go-path's hoisted lui of g_unitZVector, a few scheduling swaps.
#include "common.h"
#include "switched_collider.h"
#include "object_set.h"
#include "object_gatherer.h"
#include "path_curve_object.h"
#include "c5c.h"
#include "c5d.h"
#include "effect_owner.h"
#include "effect_spawner.h"
#include "c8b.h"
#include "world.h"
#include "effect.h"
#include "list_iter.h"
#include "globals.h"
#include "game_progress.h"
#include "object_message.h"
#include "object_event.h"
#include "object_link.h"
#include "camera.h"
#include "packet_writer.h"
#include "screen_element.h"
#include "step_sequence.h"
#include "asm_func.h"
#include "vu0.h"

extern f32 g_gameTime[];
extern f32 g_gameClock[];
void func_0019C1C0(void* self, s32 mode);
f32 RandomFloatInRange(f32 a, f32 b);
extern f32 D_0026ABC0[4];
void TransformPointBetweenFrames(void *a, s32 b, void *c, Quad4 *d);
// A walk of a list that RemoveFromList keeps valid: the frame is pushed on g_activeListFrames
// (list_iter.h) and each step reads the next item through the link.
struct BeginListWalk {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};

template <class T> struct NextInList {
    static T* Of(ListFrame* it)
    {
        T* obj = *(T**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct GatherCandidate {
    u8 pad00[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x40 - 0x1C];
    Vec02 pos;              // 0x40
};

void* GetActiveSwitchedCollider();
void UpdateCollider(Collider* self, f32 dt);
void StartSoundEffect(f32 f12, f32 f13, f32 f14, f32 f15, s32 a0, void* a1, void* a2, s32 a3, f32 f16, s32 a4, s32 a5);
f32 RandomGaussian(f32 a, f32 b, f32 c);
s32 FindColliderFloorContact(void* self, s32 a, void* out);
s32 TestPointAgainstObjectShape(void* obj, Vec02* p);
void ClearRootTries(void* self);
typedef void (*GathererVecFn_19B378)(ObjectGatherer* self, const Vec02* v);

void UpdateObjectGatherer(ObjectGatherer* self, f32 dt)
{
    Vec02 dir;
    Vec02 target;
    SwitchedCollider* act = (SwitchedCollider*)GetActiveSwitchedCollider();
    UpdateCollider(self, dt);
    s32 state = self->state;
    if (act != 0) {
        Vu0::Q(target) = Vu0::MulAddX(Vu0::Q(act->v140), Vu0::Q(act->v150), Vu0::Scalar(0.5f));
    }
    if (state < 3) {
        if (state >= 0 && self->f55C < g_gameClock[1]) {
            StartSoundEffect(3000.0f, 300.0f, 1.0f, 0.0f, 0x3B, 0, self, 0, 0.0f, 0, 0);
            self->f55C = RandomGaussian(g_gameClock[1] + 3.0f, 1.0f, 2.5f);
        }
    }
    if (act != 0 && (u32)state < 2 && Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(target), Vu0::Q(self->v140)), Vu0::Sub(Vu0::Q(target), Vu0::Q(self->v140)))) < 90000.0f) {
        ListFrame frame;
        BeginListWalk::Of(&frame, &self->world->list1C60);
        ObjectGatherer* n;
        while ((n = NextInList<ObjectGatherer>::Of(&frame)) != 0) {
            if (self != n) {
                s32 near = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(n->v140), Vu0::Q(self->v140)), Vu0::Sub(Vu0::Q(n->v140), Vu0::Q(self->v140)))) < self->f624 * self->f624;
                if (near) {
                    func_0019C1C0(n, 2);
                }
            }
        }
        state = 2;
        g_activeListFrames = frame.prev;
    } else {
        Vec02 push;
        Vec02 weight;
        u8 floor[0x10];
        f32 speed;
        f32 lift;
        s32 go;
        switch (state) {
        case 0:
            if (self->f558 < g_gameTime[0]) {
                state = 1;
            }
            break;
        case 1: {
            go = 0;
            if (self->ring == 0 && self->f554 + 0.5f < g_gameTime[0] && Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->v150))) < self->f614 * 0.1f) {
                go = FindColliderFloorContact(self, 0, floor) != 0;
            }
            if (go) {
                speed = self->f614;
                lift = 0.7f;
                goto push;
            }
            if (self->f558 < g_gameTime[0]) {
                state = 0;
                break;
            }
            if (Vu0::ToFloatMoved(Vu0::DotXY(Vu0::Sub(Vu0::Q(self->v640), Vu0::Q(self->v140)), Vu0::Sub(Vu0::Q(self->v640), Vu0::Q(self->v140)))) < 400.0f) {
                state = 0;
            }
            break;
        }
        case 2: {
            go = 0;
            if (self->ring == 0 && self->f554 + 0.7f < g_gameTime[0] && Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->v150))) < self->f618 * 0.3f) {
                go = FindColliderFloorContact(self, 0, floor) != 0;
            }
            if (go) {
                speed = self->f618;
                lift = 0.5f;
            push:
                Vu0::Q(push) = Vu0::MulXSum(Vu0::Q(self->m110.r[0]), Vu0::Scalar(speed * lift), Vu0::Q(g_unitZVector), Vu0::ScalarAt(self->f620));
                ((GathererVecFn_19B378*)self->desc)[36](self, &push);
                break;
            }
            if (self->f558 < g_gameTime[0]) {
                state = 1;
                break;
            }
            if (self->f660 != 0 && TestPointAgainstObjectShape(self->f660, &self->v140) != 0) {
                state = 4;
            }
            break;
        }
        case 3:
            break;
        case 4:
            if (self->f558 < g_gameClock[1] && act != 0 && 360000.0f < Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(act->v140)), Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(act->v140))))) {
                ListFrame frame;
                s32 any = 0;
                BeginListWalk::Of(&frame, &self->world->list1C60);
                while (NextInList<ObjectGatherer>::Of(&frame) != 0) {
                    if (Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(act->v140)), Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(act->v140)))) < 90000.0f) {
                        any = 1;
                        break;
                    }
                }
                if (any == 0) {
                    state = 1;
                } else {
                    self->f558 = g_gameClock[1] + RandomFloatInRange(0.2f, 3.0f);
                }
                g_activeListFrames = frame.prev;
            } else {
                ((GathererVecFn_19B378*)self->desc)[36](self, &D_00248D30);
                ((GathererVecFn_19B378*)self->desc)[37](self, &D_00248D30);
            }
            break;
        }
    }
    func_0019C1C0(self, state);
    switch (state) {
    case 1:
    case 2: {
        f32 speed;
        if (state == 1) {
            Vu0::Q(self->v630) = Vu0::Sub(Vu0::Q(self->v640), Vu0::Q(self->v140));
            speed = self->f614;
        } else {
            speed = self->f618;
            Vec02 at;
            TransformPointBetweenFrames(((GatherCandidate*)self->f660)->frame, 0, &((GatherCandidate*)self->f660)->pos, (Quad4*)&at);
            u128 d = Vu0::Sub(Vu0::Q(at), Vu0::Q(self->v140));
            f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(d, d)));
            if (dist < 500.0f) {
                speed = self->f618 <? (D_0026ABC0[0] + dist * (D_0026ABC0[1] + dist * D_0026ABC0[2]));
            }
            Vu0::Q(self->v630) = d;
        }
        dir = self->v630;
        Vu0::Q(dir) = Vu0::DivX(Vu0::Q(dir), Vu0::Length(Vu0::Q(dir)));
        f32 c = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(self->m110.r[0]), Vu0::Q(dir)));
        if (c < 0.0f) {
            c = 0.0f;
        } else if (1.0f < c) {
            c = 1.0f;
        }
        self->f61C = c * speed;
        ClearRootTries(self);
        return;
    }
    case 0:
    case 3:
    case 4:
        self->f61C = 0.0f;
        return;
    }
}

