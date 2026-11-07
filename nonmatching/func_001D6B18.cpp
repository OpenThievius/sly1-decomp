// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 412/404, checked 2026-11-07
// NEAR: same instructions in retail's order but 8 bytes longer, and the registers differ: retail keeps self in s0 and the other collider in s1 (and numbers the VU0 registers vf1/vf2/vf3 in the order of the loads); ours has them the other way round and loads the force's operands in another order.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "child_group_object.h"
#include "screen_element.h"
#include "object_link.h"
#include "object_message.h"
#include "owner_message.h"
#include "output_buffer.h"
#include "shapes.h"
#include "globals.h"
#include "world.h"
#include "queued_call.h"
#include "effect.h"
#include "game_progress.h"
#include "buffered_stream.h"
#include "value_range.h"
#include "script_value.h"
#include "cone_volume.h"
#include "redirect_object.h"
#include "font.h"
#include "level_entry.h"
#include "message_body.h"
#include "path_curve_object.h"
#include "state_notifier.h"

s32 func_001D6A18(Player* self, Collider* col, Vec02* out);
extern float D_0027516C;
extern float D_00275170[2];
extern float D_00275178[4];

void func_001BA5B0(Player* self, void* other, f32 t);
void func_001EED68(void* obj, Vec02* p, Vec02* out1, Vec02* out2);
f32 ApproachValueClampingVelocity(void* table, f32* out, f32 a, f32 b, f32 c, f32 d);
void AddColliderForce(void* a, void* b);

void func_001D6B18(Player* self, Collider* other, f32 t)
{
    switch (self->f2228) {
    case 6:
    case 0x2B:
        if (self->v150.z < 0.0f) {
            func_001BA5B0(self, other, t);
        }
        return;
    case 0x27:
    case 0x2F: {
        Vec02 point;
        Vec02 local;
        Vec02 q2;
        Vec02 q3;
        Vec02 force;
        Vec02 k;
        f32 next;
        if (func_001D6A18(self, other, &point) == 0) {
            return;
        }
        Vu0::Q(local) = Vu0::Rotate(self->m660, Vu0::Q(self->v640));
        func_001EED68(other, &point, &q2, &q3);
        Vu0::Q(k) = Vu0::FromFloat(D_00275170[0]);
        Vu0::Q(force) = Vu0::MulX(Vu0::Sub(Vu0::Add(Vu0::Q(self->v150), Vu0::Q(local)), Vu0::Q(q2)), Vu0::Q(k));
        ApproachValueClampingVelocity(D_00275178, &next, self->v140.z + D_0027516C, self->v150.z - q2.z, point.z, t);
        force.z = (next - self->v150.z) / t - self->gravity.z >? force.z;
        AddColliderForce(self, &force);
        return;
    }
    }
    func_001BA5B0(self, other, t);
}
