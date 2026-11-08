// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 921/984 (93.6%), checked 2026-11-07
#include "common.h"
#include "vu0.h"
#include "list_iter.h"
#include "c8b.h"
#include "effect_owner.h"
#include "effect_spawner.h"
#include "world.h"
#include "camera.h"
#include "object_gatherer.h"
#include "switched_collider.h"
#include "packet_writer.h"
#include "effect.h"
#include "globals.h"
#include "group_marker.h"
#include "deferred_request.h"
#include "color_fade.h"
#include "paired_object.h"
#include "hit_target.h"
#include "sound_state_object.h"
#include "object_creator.h"
#include "object_pool.h"
#include "pair_controller.h"
#include "screen_element.h"
#include "shapes.h"
#include "object_link.h"
#include "target_binding.h"
#include "game_progress.h"
#include "object_message.h"
#include "object_event.h"
#include "pad_record.h"
#include "animation.h"
#include "attachment.h"
#include "message_body.h"
#include "asm_func.h"
#include "mul_rotation.h"
// NEAR (2026-11-08, worker vu0w4-e1): same instructions, tools/regdiff.py says `order` (238 of 246 in
// place): the frame, the registers, the four overlap tests (the first on the player's collider and
// three list walks; each sets a flag with `li 1; bc1fl; move 0`), the spawn calls. Eight instructions
// are placed differently around the overlap tests' two radius loads (retail loads the entry's radius before the
// subtraction of the first test and the pair around it in the loops) and the first
// call of the spawn tail (retail's mtc1 zero,$f12 before the jal, then lui s1). Reversing the
// compares, computing the reach first and passing the distance through a local did not move them.
extern float g_gameClock[];
extern f32 g_gameTime;
f32 RandomFloatInRange(f32 a, f32 b);
void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
void SetHitTargetState(void* self, int flag);
void RemoveFromList(void* a, void* b);
void AppendToList(void* a, void* b);
s32 PairWithNearestWaitingObject(void* self, void* child);

extern const f32 D_0024CAEC;
void ComputePolarOffset(Vec02* out, f32 angle, f32 radius, f32 height);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
void* GetActiveSwitchedCollider(void);
extern const Vec02 D_00248D20;

// Whether the spot is within reach of n: the xy distance to its position is less than the two radii.
static inline s32 IsNearSpot(const Vec02& pos, PairedObject* n, PairedObject* o)
{
    s32 near = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(Vu0::Q(pos), Vu0::Q(n->v140)), Vu0::Sub(Vu0::Q(pos), Vu0::Q(n->v140))))) < o->radius3D0 + n->radius3D0;
    return near;
}

static inline s32 IsNearSpotOf(const Vec02& pos, PairedObject* n, PairedObject* o)
{
    s32 near = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(Vu0::Q(pos), Vu0::Q(n->v140)), Vu0::Sub(Vu0::Q(pos), Vu0::Q(n->v140))))) < n->radius3D0 + o->radius3D0;
    return near;
}

void func_001A5120(PairController* self)
{
    Vec02 pos;
    Vec02 spare;
    Mat02 turn;
    PairedObject* o;
    PairedObject* n;
    PairedObject* m;
    PairedObject* other;
    s32 i;

    if (self->count380 >= self->limit624) {
        self->f634 = D_0024CAEC;
        return;
    }
    o = *(PairedObject**)self->list374;
    for (i = 0; i < 8; i++) {
        f32 angle = RandomFloatInRange(0.0f, 6.2831855f);
        f32 radius = RandomFloatInRange(*(f32*)((u8*)self + 0x340) + o->radius3D0, *(f32*)((u8*)self + 0x344));
        other = (PairedObject*)GetActiveSwitchedCollider();
        ComputePolarOffset(&pos, angle, radius, 0.0f);
        pos.y = pos.y * self->tune34C;
        Vu0::Q(pos) = Vu0::Add(Vu0::Q(*(Vec02*)((u8*)self + 0x330)), Vu0::Q(pos));
        if (other != 0 && IsNearSpot(pos, other, o)) {
            continue;
        }
        for (n = *(PairedObject**)self->list384; n != 0; n = *(PairedObject**)((u8*)n + 0x5B0)) {
            if (IsNearSpotOf(pos, n, o)) {
                break;
            }
        }
        if (n != 0) {
            continue;
        }
        for (m = *(PairedObject**)self->list35C; m != 0; m = *(PairedObject**)((u8*)m + 0x5A0)) {
            if (m->parent == 0 && IsNearSpotOf(pos, m, o)) {
                break;
            }
        }
        if (m != 0) {
            continue;
        }
        for (m = *(PairedObject**)self->list368; m != 0; m = *(PairedObject**)((u8*)m + 0x5A0)) {
            if (m != o && IsNearSpotOf(pos, m, o)) {
                break;
            }
        }
        if (m == 0) {
            break;
        }
    }
    if (i < 8) {
        self->count3BC++;
        self->count380++;
        o->desc->m02(o);
        pos.z = self->tune350;
        o->desc02()->m1D(o, &pos);
        BuildAxisAngleMatrix(&D_00248D20, &turn, RandomFloatInRange(0.0f, 6.2831855f));
        o->desc02()->m1E(o, &turn);
        o->desc02()->m20(o, (Vec02*)&D_00248D30);
        o->desc02()->m21(o, (Vec02*)&D_00248D30);
        SetColliderAnchors(o, 2, (s32)&D_00248D20, 3, 0);
        SetHitTargetState(o, 0);
        RemoveFromList(self->list374, o);
        AppendToList(self->list368, o);
        PairWithNearestWaitingObject(self, o);
        self->f634 = g_gameTime + RandomFloatInRange(self->f62C, self->f630);
    }
}

