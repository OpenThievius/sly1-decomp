// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 357/368 (97.0%), checked 2026-11-07
#include "common.h"
#include "switched_collider.h"
#include "screen_element.h"
#include "object_event.h"
#include "object_message.h"
#include "globals.h"
#include "vu0.h"
// NEAR (2026-11-08, wave 4): all but two spots are retail's. The scheduler puts `li v1,6` (the
// message kind) before c.lt.s where retail has it after, and the final `ev->eventFlags &= ~0x20`
// loads the flags into v1 and -33 into v0 where retail uses v0 and v1. Orders of the three
// message stores, a local flags copy, `which` initialised, and the message at the top gave the
// same result.
typedef void (*VFn_1A9AE8)(void* self, SlotMessage* msg);
void DecrementGaugeCount(void* element);
s32 ReplaceAnimationPlayer(s32 a, void* b, s32 c, void* d, f32 e, f32 f);
s32 HandleAgentObjectEvent(GaugeBarAgent* self, ObjectEvent* ev);
extern Player* g_player;
extern const Vec02 g_unitXVector;

s32 func_001A9AE8(GaugeBarAgent* self, ObjectEvent* ev)
{
    if (self->fC14 != 0 && (ev->eventFlags & 0x20) != 0) {
        self->fC10 = self->fC10 + 1;
        DecrementGaugeCount(&g_gaugeBarElement);
        if (*(void**)((u8*)self + 0xB00) != 0) {
            SlotMessage msg;
            msg.kind = 6;
            msg.vb = ev->pos;
            Vu0::Set(msg.va, Vu0::NormalizeOr(Vu0::Q(ev->v30), Vu0::Q(g_unitXVector)));
            void* o = *(void**)((u8*)self + 0xB00);
            ((VFn_1A9AE8*)(*(void***)o))[0x7C / 4](o, &msg);
        }
        s32 which;
        if ((ev->extraFlags & 2) != 0) {
            if (g_player == 0 || g_player->f223C == 4 || g_player->f223C == 6)
                which = self->fC14;
            else
                which = self->fC18;
        } else if ((ev->extraFlags & 4) != 0) {
            which = self->fC1C;
        } else {
            which = self->fC14;
        }
        ReplaceAnimationPlayer(which, self, 1, (u8*)self + 0xC20, 0.0f, 1.0f);
        ev->eventFlags &= ~0x20;
    }
    return HandleAgentObjectEvent(self, ev);
}

