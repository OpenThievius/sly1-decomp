// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 398/528 (75.4%), checked 2026-11-07
// NEAR: the shape is retail's (jump table, registers, the tail); left: the conditional-branch layout of the 5.0 test and the delay slots of the player branch (ours hoists li v0,2 into them), and the f570 == 0 fall-off is a goto to a label after the return (a bare return; is an error in this compiler).
#include "common.h"
#include "target_follower.h"
#include "collider.h"
#include "zone_collider.h"
#include "globals.h"
#include "placed_object.h"
#include "vu0.h"
void ConvertPositionToWorld(void* arg, f32* out);
void* GetActiveSwitchedCollider(void);
void SetFollowedObject(TargetFollower* self, FollowableObject* x);

extern f32 g_gameTime;
s32 HasObjectPoolChoice(void* p);
typedef s32 (*VFnRet_16D1E0)(void* self);
void* ChooseEntryTableObject(void* x);

s32 ChooseTargetFollowerMode(TargetFollower* self)
{
    FollowableObject* next;
    Collider* c;
    s32 mode = self->f598;
    switch (mode) {
    case 2:
    case 4: {
        next = (FollowableObject*)self->list55C.tail;
        if (next != self->f558) {
            if (next == 0) {
                mode = 4;
            } else if (self->f558 == 0 || next->f7A4 != self->f558->f7A4) {
                Vec02 v;
                ConvertPositionToWorld(next->f7A4, (f32*)&v);
                u128 d = Vu0::Sub(Vu0::Q(v), Vu0::Q(self->v140));
                f32 len = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
                if (len < 5.0f) {
                    mode = 4;
                    if (next->f7AC != 0) {
                        mode = 2;
                    }
                } else {
                    mode = 0;
                }
            } else {
                mode = 4;
                if (next->f7AC != 0) {
                    mode = 2;
                }
            }
            SetFollowedObject(self, next);
        }
        next = (FollowableObject*)GetActiveSwitchedCollider();
        c = next;
        if (c == 0) {
            break;
        }
        if (c == (Collider*)g_player) {
            if (((VFnRet_16D1E0*)c->desc)[81](c) == 0) {
                if (mode == 4 && self->f558 != 0) {
                    if (self->f558->f7AC != 0) {
                        mode = 2;
                    }
                }
            } else if (mode == 2) {
                mode = 4;
            }
        }
        if (mode == 2 && self->f574 < g_gameTime) {
            if (self->f570 == 0) {
                goto end;
            }
            if (HasObjectPoolChoice(self->f570) != 0) {
                void* t = ChooseEntryTableObject(self->f558->f7AC);
                if (t != 0) {
                    self->f590 = t;
                    mode = 3;
                    break;
                }
            }
        }
        break;
    }
    case 1:
        if (self->f5AC <= g_gameTime) {
            mode = 4;
            if (self->f558->f7AC != 0) {
                mode = 2;
            }
        }
        break;
    case 0:
        if (self->f5A8 <= g_gameTime) {
            mode = 1;
        }
        break;
    case 3:
    default:
        break;
    }
    return mode;
end:;
}
