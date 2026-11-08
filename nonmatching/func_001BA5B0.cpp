// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1587/1656 (95.8%), checked 2026-11-08
// NEAR (2026-11-08, night-large3): the whole function is right but for registers in two places:
// the six step addresses kept in s1, s4..s7, fp are hoisted before the first gain loop with
// &spin (sp+0x30) and &spinAlong (sp+0xB0) in s5 and s4, where retail has s4 and s5; and in the
// rotation of the three rows by the shortest arc, retail's rows take vf2, vf6, vf5 and the third
// row's vector vf3 (ours: vf3, vf5, vf4, and vf2), which moves the stores of the rotated rows.
// Tried: RotateUntied (gives retail's ties; Rotate does not), the rows as values (RotateRows),
// Vec::Of for the vectors: no change. Night-close7: func_00156288 declared with its floats after
// the two pointers (retail sets a0 and a1 before $f12) fixes the last call's argument order.
#include "common.h"
#include "sound_record.h"
#include "script_value.h"
#include "cursor_animator.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "collider.h"
#include "state_graph.h"
#include "camera_positioned_object.h"
#include "world.h"
#include "attachment.h"
#include "state_walker.h"
#include "globals.h"
#include "buffered_stream.h"
#include "object_event.h"
#include "key_record.h"
#include "key_id.h"
#include "base_object.h"
#include "fpu.h"
#include "asm_func.h"
#include "point_object.h"
#include "id_linked_object.h"
#include "game_progress.h"
#include "shapes.h"
#include "property_descriptor.h"
#include "vu0.h"
#include "attached_set.h"

extern f32 D_002746C0[4];
extern f32 D_002746D0[4];
f32 func_001EF5B8(AttachedSet* self, Collider* o, Vec02* nOut, Vec02* hitOut);
void func_001EED68(AttachedSet* self, void* in, Vec02* outA, Vec02* outB);
void BuildPerpendicularPair(Vec02* in, Vec02* out, const Vec02* a, const Vec02* b);
void ComputeOscillatorDisplacement(f32 f, void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5);
void ConstrainColliderVector(void* self, void* a, void* b, void* c, s32 d);
void AddColliderForce(void* a, void* b);
void AddColliderTorque(void* target, void* slot);
f32 SplitVectorAlongAxis(Vec02* v, Vec02* axis, Vec02* along, Vec02* rest);
void SteerColliderTowardPosition(Collider* self, s32 a, s32 b, Vec02* target, f32* gains, f32 dt);
void SteerColliderTowardRotation(Collider* self, s32 a, s32 b, Vec02* target, f32* gains, f32 dt);
void BuildShortestArcRotation(const Vec02* from, Vec02* to, Mat02* out);
f32 Arccosine(f32 x);
void func_00156288(Collider* self, AttachedSet* other, f32 dt, f32 a, f32 b, Vec02* hit, Vec02* point);
void StopSoundRecord(void* self, s32 n);

struct Oscillated_1BA5B0 { u8 pad00[0xC]; void* oscillator; };
struct SoundOwner_1BA5B0 { u8 pad00[0x574]; void* sound; };

// The rows of m, each turned by r.
static inline Mat02 RotateRowsBy(const Mat02& r, const Mat02& m)
{
    Mat02 out;
    Vu0::Q(out.r[0]) = Vu0::RotateUntied(r, Vu0::Vec::Of(m.r[0])).q;
    Vu0::Q(out.r[1]) = Vu0::RotateUntied(r, Vu0::Vec::Of(m.r[1])).q;
    Vu0::Q(out.r[2]) = Vu0::RotateUntied(r, Vu0::Vec::Of(m.r[2])).q;
    return out;
}

void func_001BA5B0(Collider* self, AttachedSet* other, f32 dt)
{
    Vec02 hit;
    Vec02 hitVel;
    Vec02 force;
    Vec02 spin;
    Vec02 point;
    Vec02 normal;
    f32 gains[3];
    f32 depth = func_001EF5B8(other, self, &point, &normal);
    if (depth < 0.0001f) {
        return;
    }
    if (other->f278 != 0) {
        Vec02 axes[2];
        Vec02 dir = normal;
        BuildPerpendicularPair(&dir, &axes[0], &g_unitXVector, &g_unitZVector);
        ComputeOscillatorDisplacement(50.0f, ((Oscillated_1BA5B0*)other->f278)->oscillator, &point, &axes[0], 0, &axes[0], 0);
        Vu0::Set(normal, Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(axes[0]), Vu0::Q(axes[1])), Vu0::Q(g_unitZVector)));
    }
    f32 push;
    if ((self->flags538 & (0x8000ULL << 36)) == 0) {
        push = self->f360 * other->f360;
    } else {
        push = 0.0f;
    }
    f32 drag = self->f364 * other->f364;
    if (push != 0.0f) {
        Vu0::Q(force) = Vu0::MulX(Vu0::Q(self->gravity), Vu0::Scalar(-push * depth));
        ConstrainColliderVector(self, &self->v440, &force, &force, 0);
        AddColliderForce(self, &force);
    }
    if (drag != 0.0f) {
        Vec02 along;
        Vec02 rest;
        Vec02 target;
        Vec02 target2;
        Vec02 spinAlong;
        Vec02 spinRest;
        Vec02 target3;
        Vec02 target4;
        func_001EED68(other, &self->v140, &hit, &hitVel);
        Vu0::Q(force) = Vu0::Sub(Vu0::Q(hit), Vu0::Q(self->v150));
        f32 dot = SplitVectorAlongAxis(&force, &normal, &along, &rest);
        f32 scale = 1.0f;
        if (depth != 1.0f && !(0.0f < dot)) {
            scale = depth * 0.5f + 0.5f;
        }
        for (s32 i = 0; i < 3; i++) {
            gains[i] = D_002746C0[i] * scale * drag;
        }
        Vu0::Q(target) = Vu0::Add(Vu0::Q(self->v150), Vu0::Q(along));
        SteerColliderTowardPosition(self, 0, 0, &target, gains, dt);
        for (s32 i = 0; i < 3; i++) {
            gains[i] = D_002746C0[i] * depth * drag;
        }
        Vu0::Q(target2) = Vu0::Add(Vu0::Q(self->v150), Vu0::Q(rest));
        SteerColliderTowardPosition(self, 0, 0, &target2, gains, dt);
        Vu0::Q(spin) = Vu0::Sub(Vu0::Q(D_00248D30), Vu0::Q(self->v160));
        SplitVectorAlongAxis(&spin, &normal, &spinAlong, &spinRest);
        for (s32 i = 0; i < 3; i++) {
            gains[i] = D_002746D0[i] * depth * drag;
        }
        Vu0::Q(target3) = Vu0::Add(Vu0::Q(self->v160), Vu0::Q(spinAlong));
        SteerColliderTowardRotation(self, 0, 0, &target3, gains, dt);
        for (s32 i = 0; i < 3; i++) {
            gains[i] = D_002746D0[i] * drag;
        }
        Vu0::Q(target4) = Vu0::Add(Vu0::Q(self->v160), Vu0::Q(spinRest));
        SteerColliderTowardRotation(self, 0, 0, &target4, gains, dt);
    }
    if (push != 0.0f) {
        Mat02 m = self->m1A0;
        Mat02 r;
        Vec02 axis;
        Vec02 torque;
        self->desc03()->m29(self, &m, 0);
        BuildShortestArcRotation(&g_unitZVector, &normal, &r);
        m = RotateRowsBy(r, m);
        f32 angle = Arccosine(Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->m110.r[2]), Vu0::Q(m.r[2]))));
        Vu0::Set(axis, Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(self->m110.r[2]), Vu0::Q(m.r[2])), Vu0::Q(g_unitXVector)));
        Vu0::Q(torque) = Vu0::MulX(Vu0::Q(axis), Vu0::Scalar(angle * (push * 3.0f) * depth));
        AddColliderTorque(self, &torque);
    }
    if (0.0f < depth && depth < 1.0f && 0.9f < normal.z) {
        func_00156288(self, other, dt, 0.1f, ((self->boundsMax.x - self->boundsMin.x) + (self->boundsMax.y - self->boundsMin.y)) * 0.25f, &hit, &point);
    } else if (self->desc->flags & 8) {
        StopSoundRecord(((SoundOwner_1BA5B0*)self)->sound, 0);
    }
}
