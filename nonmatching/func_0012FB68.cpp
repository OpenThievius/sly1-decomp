// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 320/328 (97.6%), checked 2026-11-07
// NEAR: one swap: retail loads the target's reach (lwc1 f1,0x3D0(v0)) before the vsub.xyzw of the length; here after it. Six forms of the comparison and the radius (local before, after, doubled, reach+reach, reversed) tried.
// In the context of its file, src/main/placed_object.cpp.
// 0x1233C0 to 0x130F48: the state triggers (classes 0x22 and 0x2F), the placed object's set-up,
// update and loading (func_00123ED0 to func_001289C0), its range, sound and colour records, the
// code checksum, the animation players and their events, the id filter object, the sector stream
// reader and the curve segment helpers. One file between two edges; it could be several.
#include "common.h"
#include "vu0.h"
#include "id_filter_object.h"

void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);
void TriggerScriptEvent(void* self, s32 a, s32 b, void* c);

void func_0012FB68(IdFilterObject* self, u8* table, s32 which)
{
    Vec02 loc;
    u8* arg;
    TriggerScriptEvent(self, 2, 0, 0);
    arg = table + ((1 - which) << 6) + 4;
    TriggerScriptEvent(self, 0x1D, 1, (void**)&arg);
    if (self->mode != 0) {
        if (self->pendingTarget == 0) {
            if (self->placedTarget != 0) {
                s32 close;
                switch (self->mode) {
                case 1:
                    *(Quad16*)&loc = *(Quad16*)&self->pos;
                    break;
                case 2: {
                    PlacedObject* node = self->found;
                    TransformPointBetweenFrames(node->parent, 0, &node->link40, &loc);
                    break;
                }
                }
                f32 d = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->placedTarget->v140), Vu0::Q(loc))));
                close = d <= *(f32*)((u8*)self->placedTarget + 0x3D0) * 2.0f;
                if (close) {
                    return;
                }
            }
            self->pendingTarget = *(PlacedObject**)(table + ((1 - which) << 6));
        }
    }
}
