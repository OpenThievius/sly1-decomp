// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 136/144, checked 2026-11-07
#include "common.h"
#include "switched_collider.h"
#include "attachment.h"
#include "animation.h"
#include "vu0.h"
// NEAR (2026-11-07, worker vu0-a): the instructions are retail's but scheduled and allocated
// differently. Retail divides and moves the scale into the VU (qmtc2 vf4, stored to k) before
// it loads the entry's position: the velocity and self's position are loaded first (vf3, vf5),
// so the Dot's scratch is vf6, and self is copied to a3 (the player takes a0). Here sched1 puts
// the division's mfc1/qmtc2 last, after vmulq, and loads self's position first. The same as
// func_0018DDD8 and func_001C3EB0: retail moves a float into the VU early, the compiler here
// late. Tried: the scale kept in a u128, the entry as a pointer or indexed twice, the
// normalisation as Length and DivX or as Normalize (the same code).

struct ContactEntry40 {
    u8 pad00[0x10];
    Vec02 pos;              // 0x10
    u8 pad20[0x30 - 0x20];
    Vec02 vel;              // 0x30
};

extern f32 D_00274A44;

void func_001C3C98(HitCountCollider* self, ContactEntry40* entries, s32 i)
{
    AnimationPlayer* p = self->f67C;
    if (p != 0) {
        Vec02 k;
        Vu0::Q(k) = Vu0::FromFloat((D_00274A44 - self->f68C) / p->anim->length);
        ContactEntry40* e = &entries[i];
        u128 d = Vu0::Sub(Vu0::Q(e->pos), Vu0::Q(self->v140));
        Vu0::Q(e->vel) = Vu0::MulAddX(Vu0::Q(e->vel), Vu0::DivX(d, Vu0::Length(d)), Vu0::Q(k));
    }
}
