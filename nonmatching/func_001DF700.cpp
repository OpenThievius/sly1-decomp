// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 621/780 (79.6%), checked 2026-11-07
// BYTES 0/780, checked 2026-11-07
// NEAR: the calls, the launch block (the ground direction normalised with g_unitXVector as fallback, the ScalarAt speeds, the FromFloats perpendicular) and the frame (0x80, the message reusing the direction's slot) are retail's; retail forms g_unitXVector's address before the length test and takes other GPRs for the loads of the two speeds and of the perpendicular's weight, so a few registers and the order of some loads differ.
// In the context of its file, src/main/tint_blend_collider.cpp.
#include "common.h"
#include "switched_collider.h"
#include "world.h"
#include "globals.h"
#include "owner_message.h"
#include "vu0.h"

extern f32 g_gameClock[];
extern f32 D_0027589C;
extern f32 D_002758A0;
extern f32 D_002758A4;
extern f32 D_002758A8;
extern f32 D_002758AC;
void InitOwnerMessage(OwnerMessage* l, s32 zero, Collider* c);
void SetTintBlendColliderState(void* self, s32 flag);
s32 HasSpareCount();
void ClearRootObjectStateBits(void* owner, void* self, s32 n);
void TransformDirectionBetweenFrames(void* from, void* to, Vec02* in, Vec02* out);
void ActivateSwitchedCollider(SwitchedCollider* self);
void ContinueTintBlendColliderRequest(s32 c, void* receiver);

s32 AcceptTintBlendColliderRequest(TintBlendCollider* self, OwnerMessage* req)
{
    if (self->desc05()->m4B(self, req->mode)) {
        return 0;
    }
    if (HasSpareCount()) {
        self->f728 = 1;
    }
    self->f72C = g_gameClock[1];
    ClearRootObjectStateBits(self->world, self, 7);
    if (req->mode == 0 && req->reply != 0) {
        req->reply(req->c, self);
        {
        Vec02 dir;
        Vec02 v;
        Vec02 w;
        dir = self->v150;
        dir.z = 0.0f;
        u128 len = Vu0::Length(Vu0::Q(dir));
        if (Vu0::ToFloatMoved(len) < 0.0001f) {
            dir = g_unitXVector;
        } else {
            Vu0::Set(dir, Vu0::DivX(Vu0::Q(dir), len));
        }
        if (HasSpareCount()) {
            Vu0::Set(v, Vu0::MulX(Vu0::Q(dir), Vu0::ScalarAt(D_0027589C)));
        } else {
            Vu0::Set(v, Vu0::MulX(Vu0::Q(dir), Vu0::ScalarAt(D_002758A0)));
        }
        self->desc02()->m20(self, &v);
        Vu0::Set(v, Vu0::MulX(Vu0::Q(dir), Vu0::ScalarAt(D_002758A4)));
        v.z = D_002758A8;
        TransformDirectionBetweenFrames(0, ((PlacedObject*)self->f748)->parent, &v, &v);
        ((PlacedObject*)self->f748)->desc02()->m20((PlacedObject*)self->f748, &v);
        Vu0::Set(dir, Vu0::FromFloats(-dir.y, dir.x, 0.0f));
        Vu0::Set(w, Vu0::MulX(Vu0::Q(dir), Vu0::ScalarAt(D_002758AC)));
        TransformDirectionBetweenFrames(0, ((PlacedObject*)self->f748)->parent, &w, &w);
        ((PlacedObject*)self->f748)->desc02()->m21((PlacedObject*)self->f748, &w);
}
    }
    OwnerMessage msg;
    if (HasSpareCount() || g_player == 0) {
        SetTintBlendColliderState(self, 2);
    } else {
        g_player->desc->m02(g_player);
        g_player->desc02()->m1F(g_player, (PlacedObject*)self->f744);
        ((BaseObject*)self->f744)->desc->m03((BaseObject*)self->f744);
        ActivateSwitchedCollider(g_player);
        SetTintBlendColliderState(self, 3);
        InitOwnerMessage(&msg, 0, self);
        msg.reply = ContinueTintBlendColliderRequest;
        g_player->desc05()->m4C(g_player, &msg);
        self->f4E0 = 3;
    }
    msg.mode = (s32)self;
    msg.owner = req->owner;
    self->desc->m0E(self, 0x17, &msg);
    return 1;
}
