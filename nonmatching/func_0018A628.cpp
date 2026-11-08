// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 136/148 (91.9%), checked 2026-11-08
// NEAR: the gauge agent's draw method. Everything matches except the order of the last stores before the call that queues the request: retail stores the object (0x60), then the float (0x04), moves the request's address into a0, and puts the callback store (0x00) in the call's delay slot; ours moves a0 first, stores the callback and the float, and leaves the object's store in the slot. All 24 orders of the four stores, with the float in a local or not, give ours.
// permute.py --auto (2026-11-08, night-orders): 1 run of 6 lines (720 orders): best 10 bytes differ (12 as it stands), none EXACT.
#include "common.h"
#include "switched_collider.h"
#include "deferred_request.h"
#include "vu0.h"

// The record an agent's draw method is given: the point and the weights it measures against.
struct AgentDrawArgs {
    u8 pad00[0x40];
    Vec02 point;            // 0x40
    u8 pad50[0x80 - 0x50];
    Vec02 weights;          // 0x80
};

void DrawAgent(Agent* self, AgentDrawArgs* args);
void QueueDeferredRequest(DeferredRequest* request);
void* FillMemory(void* p, s32 value, s32 size);
void func_0018A510();

void func_0018A628(GaugeAgent* self, AgentDrawArgs* args)
{
    DrawAgent(self, args);
    if (self->fE2C) {
        DeferredRequest request;
        FillMemory(&request, 0, 0x80);
        request.group = 0xD;
        request.arg = self;
        request.f04 = Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(args->point)), Vu0::Q(args->weights)));
        request.callback = (void*)func_0018A510;
        QueueDeferredRequest(&request);
    }
}
