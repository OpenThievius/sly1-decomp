// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 528/520, checked 2026-11-07
// NEAR: all calls and the vector code match; differs in (1) retail's constant 250000.0f is rebuilt (lui/ori/mtc1) inside the loop where ours keeps it in $f21, (2) FromFloat of D_00261BE0 is lw in retail, lwc1+mfc1 here, (3) the clamp of +0x858 to 99 is `li 98; slt; movz` in retail but slti 100 here. Constants hoisting and the clamp tried in about 15 forms.
#include "common.h"
#include "state_notifier.h"
#include "world.h"
#include "switched_collider.h"
#include "camera.h"
#include "vu0.h"
extern u8 g_camera[];
#include "placed_object.h"
extern f32 D_00261BD0[4];
extern f32 D_00261BE0;
extern f32 D_00261BE4;
f32 D_00261BD0[4] = { 0.0f, 0.0f, 200.0f, 0.0f };
f32 D_00261BE0 = 0.75f;
f32 D_00261BE4 = -1.0f;
void UpdateStateNotifier(StateNotifier* self);
struct ListenerMessage {
    s32 state;              // 0x00
    void* sender;           // 0x04
    u8 pad08[0x50 - 0x08];
};
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void* GetActiveSwitchedCollider(void);

s32 GatherObjectsById(void* world, s32 a, s32 b, s32 c, s32 d, PlacedObject** out);
s32 CollectMeshHits(Vec02* probe, s32 a, s32 b, s32 c, void* d, s32 e, void* out, f32 radius);

void func_00149190(ArmedStateNotifier* self)
{
    Vec02 probe;
    PlacedObject* found[6];
    u8 hit[0x30];
    Vec02 push;
    Vec02 k;
    ListenerMessage msg;
    s32 n;
    PlacedObject** p;

    UpdateStateNotifier(self);
    Vu0::Q(probe) = Vu0::Add(Vu0::Q(self->v140), Vu0::Q(*(Vec02*)D_00261BD0));
    n = GatherObjectsById(self->world, 5, 0x19, 0, 6, found);
    if (n > 0) {
        f32 zero = 0.0f;
        p = found;
        do {
            PlacedObject* o = *p;
            u128 d = Vu0::Sub(Vu0::Q(o->v140), Vu0::Q(probe));
            if (250000.0f < Vu0::ToFloat(Vu0::Dot(d, d))) {
                continue;
            }
            if (CollectMeshHits(&probe, *(s32*)((u8*)o + 0x3F4), *(s32*)((u8*)o + 0x3F8), 0, (u8*)o + 0x3A4, 1, hit, 100.0f) <= 0) {
                continue;
            }
            if ((void*)o == (void*)GetActiveSwitchedCollider()) {
                s32 c = *(s32*)((u8*)o + 0x858) + 1;
                *(s32*)((u8*)o + 0x858) = (c > 98) ? 99 : c;
            }
            Vu0::Q(k) = Vu0::FromFloat(D_00261BE0);
            Vu0::Q(push) = Vu0::MulX(Vu0::Q(o->v150), Vu0::Q(k));
            push.z = zero >? push.z;
            self->desc02()->m20(self, &push);
            if (self->listener != 0) {
                msg.state = 1;
                msg.sender = self;
                self->listener->vtbl[31](self->listener, &msg);
            }
            StartSoundEffect(0x2C, 0, 0, (s32)&self->v140, 7500.0f, 2500.0f, 2.0f, D_00261BE4, 0.0f, 0, 0);
            self->desc02()->m2F(self, 2);
        } while (p++, --n != 0);
    }
}

