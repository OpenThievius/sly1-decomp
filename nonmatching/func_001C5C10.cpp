// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 316/324 (97.5%), checked 2026-11-08
// NEAR: identical but for two instructions in the kind-1 call: retail sets f12 with neg.s before the call and fills the delay slot with move t2,a2 (the a6 argument); ours puts neg.s in the delay slot and move t2,a2 before the call. Every form of the negation tried (-d, d = -d, in the argument) schedules the same.
// Still differs (2026-11-08, night-close1): the float last or before a7 in the prototype, -ToFloat(...) in the initialiser and ToFloatMoved (which moves the VU0 registers) leave neg.s in the delay slot too.
// Still differs (2026-11-08, night-close5): a named from, the negation inline and CreatePooledContact void leave neg.s in the slot; ToFloatMoved gives retail's order (the asm mtc1's latency lets neg.s issue sooner) but renumbers the VU0 registers of both cases.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "vu0.h"
#include "globals.h"
#include "object_link.h"
#include "attachment.h"
#include "pad_record.h"
#include "game_clock.h"

s32 CollectColliderSpansInTree(void* obj, void* a, void* to, void* from, s32 n, ColliderSpan* out);
s32 CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, void* a5, s32 a6, s32 a7);

void func_001C5C10(void* a, s32 b, s32 c, s32 d)
{
    TurningCollider* self = (TurningCollider*)a;
    if (self->f6DC != 0) {
        ColliderSpan span;
        void* obj = (void*)b;
        if (CollectColliderSpansInTree(obj, (void*)c, &self->v140, (void*)self->f6D4, 1, &span) > 0 && span.time[0] > 0.0f) {
            Vec02 diff;
            Vu0::Q(diff) = Vu0::Sub(Vu0::Q(*(Vec02*)self->f6D4), Vu0::Q(span.q[0]));
            switch (span.f48) {
            case 0: {
                f32 d0 = Vu0::ToFloat(Vu0::Dot(Vu0::Q(diff), Vu0::Q(span.q[2])));
                CreatePooledContact(d0, self, obj, (void*)self->f6D4, &span.q[2], 1, (void*)self->f6D4, *(s32*)((u8*)&span + 0x50), d);
                break;
            }
            case 1: {
                Vec02 k;
                Vu0::Q(k) = Vu0::FromFloat(-1.0f);
                Vu0::Q(span.q[2]) = Vu0::MulX(Vu0::Q(span.q[2]), Vu0::Q(k));
                f32 d1 = Vu0::ToFloat(Vu0::Dot(Vu0::Q(diff), Vu0::Q(span.q[2])));
                d1 = -d1;
                CreatePooledContact(d1, obj, self, (void*)self->f6D4, &span.q[2], 4, 0, self->f6D4, d);
                break;
            }
            }
        }
    }
}
