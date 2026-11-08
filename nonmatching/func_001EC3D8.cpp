// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 140/156 (89.7%), checked 2026-11-07
// NEAR: same instructions and registers (stores written group, object, float, callback); only the schedule of `move a0,sp` against `swc1 $f0,4(sp)` differs (retail puts the move after the swc1). Tried the float as a local or inline, other store orders, a pointer local for &r.
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
        r.group = 0xD;
        r.arg = self;
        r.f04 = d;
        r.callback = (void*)DrawTempoAgentRing;
        QueueDeferredRequest(&r);
    }
}
