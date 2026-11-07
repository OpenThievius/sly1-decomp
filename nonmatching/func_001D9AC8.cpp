// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 476/464, checked 2026-11-07
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
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
// NEAR (2026-11-07, worker vu0-c): the whole function but for the two floats made vectors and
// the VU0 registers after them. Retail loads D_00275610 and D_00275614 with lw straight into v0
// for the qmtc2; FromFloat on a float gives lwc1 and mfc1 (8 bytes longer). With a FromFloat that
// passes the float's bits (a union) the loads are lw, but into v1, and retail's order of the
// unit vector's load and the registers (k vf4, pos vf3, the unit vector vf2, the second k vf1)
// still differ: here vf3, vf2, vf1, vf4. That form also moves func_001BC828's mfc1 from v0 to v1,
// so the header keeps the float form (docs/TOOLCHAIN.md, "The VU0 helpers").

extern f32 D_00275600[4];
extern f32 D_00275610;
extern f32 D_00275614;
extern f32 g_gameClock[];
void FreePooledContactChain(World* a0, Contact03* a1);
void TransformDirectionBetweenFrames(void* self, void* frame, void* in, Vec02* out);
s32 IsObjectOfKind(void* obj, s32 kind);
void ChangeAgentState(void* node, s32 kind, s32 flag);

void func_001D9AC8(PathFollower* self)
{
    Vec02 pos;
    Vec02 spin;
    Vec02 k;
    if (self->contacts == 0) {
        return;
    }
    for (Contact03* c = self->contacts; c != 0; c = c->next) {
        s32 side = c->end[0].body == (Collider*)self;
        Collider* other = c->end[side].body;
        s32 i;
        for (i = 0; i < self->pushedCount; i++) {
            if (other == self->pushed[i]) {
                break;
            }
        }
        if (i < self->pushedCount) {
            continue;
        }
        TransformDirectionBetweenFrames(self, 0, D_00275600, &pos);
        Vu0::Q(k) = Vu0::FromFloat(D_00275610);
        Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(pos), Vu0::Q(self->v150), Vu0::Q(k));
        Vu0::Q(k) = Vu0::FromFloat(D_00275614);
        Vu0::Set(spin, Vu0::MulX(Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(pos)), Vu0::Q(k)));
        other->desc02()->m20(other, &pos);
        other->desc02()->m21(other, &spin);
        if ((u32)self->pushedCount < 8) {
            self->pushed[self->pushedCount++] = other;
        }
        if (IsObjectOfKind(other, 0x19)) {
            ((PathFollower*)other)->f86C = g_gameClock[1];
        } else if (IsObjectOfKind(other, 8)) {
            ChangeAgentState(other, 0x10, 0);
        }
    }
    FreePooledContactChain(self->world, self->contacts);
    self->contacts = 0;
}
