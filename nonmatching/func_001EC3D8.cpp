// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 140/156 (89.7%), checked 2026-11-08
// NEAR: same instructions; the compiler loads the callback address into v0 and the group 13 into v1, retail the reverse, and the four stores to the request come out in another order (retail: group at 8, object at 0x60, float at 4, callback at 0). All 24 orders of the stores and a local float for the dot product were tried.
// permute.py --auto (2026-11-08, night-orders): 1 run of 7 lines (5040 orders): best 6 bytes differ (16 as it stands), by storing the group, object, float, callback in that order after the others; not EXACT.
#include "common.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "fpu.h"
#include "world.h"
#include "warp_page.h"
#include "screen_element.h"
#include "globals.h"
#include "shapes.h"
#include "object_link.h"
#include "owner_message.h"
#include "game_clock.h"
#include "pad_record.h"
#include "memory_card.h"
#include "timeline.h"
#include "value_list_object.h"
#include "c62.h"
#include "attached_set.h"
#include "packet_writer.h"
#include "screen_fade.h"
#include "transform_object.h"
#include "oscillator.h"
#include "camera.h"
#include "game_progress.h"
#include "item_keeper.h"
#include "attachment.h"
#include "animation.h"
#include "ramp_profile.h"
#include "asm_func.h"
#include "vu0.h"

// Stands in for the static objects of the file: the check names its compiler-made functions.
struct NmInit {
    NmInit();
};
NmInit::NmInit() {}
NmInit g_nmInit;



typedef void (*PlayerSlotFn)(Player* g, void* arg);
typedef void (*AttachNotifyFn)(void* self, void* arg);
typedef void (*TempoCallFn)(void);
s32 FillMemory(Entry90* dst, s32 value, s32 size);
void FillMemory(void* p, s32 v, s32 size);

#include "deferred_request.h"
#include "camera.h"
void FillMemory(void* p, s32 v, s32 size);
void DrawAgent(TempoAgent* self, Camera* cam);
void QueueDeferredRequest(DeferredRequest* r);
void DrawTempoAgentRing(DeferredRequest* self);

void DrawTempoAgent(TempoAgent* self, Camera* cam)
{
    DrawAgent(self, cam);
    if (self->f724 == 16) {
        DeferredRequest r;
        FillMemory(&r, 0, 0x80);
        f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(cam->f40)), Vu0::Q(cam->f80)));
        r.callback = (void*)DrawTempoAgentRing;
        r.f04 = d;
        r.group = 0xD;
        r.arg = self;
        QueueDeferredRequest(&r);
    }
}
