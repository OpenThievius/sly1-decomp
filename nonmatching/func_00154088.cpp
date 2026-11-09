// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 590/744 (79.3%), checked 2026-11-08
// CONV-SWAP (2026-11-08): ToFloat and ToFloatMoved swapped at call 0 (source line 63); 77 differing lines before, 76 now.
// NEAR: same instructions as retail but for the registers of the outer loop: retail keeps the contact search's i in a3, the best contact in a4 and the best index in a6, leaving a0-a2 for the inner sum; here the best index takes a0 and the inner loop moves up. Needs ActiveSetItem::twin at 0x48 (include/active_set_solver.h).
#include "common.h"
#include "collider.h"
#include "active_set_solver.h"
#include "vu0.h"
#include "fpu.h"
void RunActiveSetSolver(ActiveSetSolver* loc, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

struct ContactSample {
    u8 pad00[0x80];
    Vec02 v80;              // 0x80
    u8 pad90[0x94 - 0x90];
    f32 f94;                // 0x94
    u8 pad98[0xB0 - 0x98];
    Vec02 vB0;              // 0xB0
};

typedef void (*HandlerFn)(void* handler, f32 dt, s32 flags, ActiveSetItem* item, s32 end);
void* FindHandlerForSlot(void* part, s32 slot);
void AddActiveSetItem(ActiveSetSolver* self, ActiveSetItem* item);

void func_00154088(ActiveSetSolver* self, s32 a1, s32 n, ContactSample** contacts, s32 a4, s32 a5, f32 dt)
{
    u128 zero = Vu0::Zero();
    Vec02 best;
    Vec02 acc;
    for (;;) {
        RunActiveSetSolver(self, a1, n, (s32)contacts, a4, a5);
        Vu0::Q(best) = zero;
        f32 top = 0.01f;
        s32 bestIndex = -1;
        ContactSample* bestContact = 0;
        for (s32 i = 0; i < n; i++) {
            ActiveSetItem* item = (ActiveSetItem*)(self->items + i * 0x60);
            if (item->twin != 0) {
                continue;
            }
            if (item->x < 0.0001f) {
                continue;
            }
            if (item->kind == 2) {
                continue;
            }
            ContactSample* c = contacts[i];
            if (c->f94 < 0.0001f) {
                continue;
            }
            Vu0::Q(acc) = Vu0::Q(c->vB0);
            ActiveSetItem* other = (ActiveSetItem*)self->items;
            for (s32 k = self->count; k > 0; k--) {
                if (other->x != 0.0f) {
                    Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(acc), Vu0::Q(((Vec02*)other->axes)[i]), Vu0::Scalar(other->x));
                }
                other++;
            }
            u128 normal = Vu0::Q(c->v80);
            u128 v = Vu0::Q(acc);
            u128 tangent = Vu0::Sub(v, Vu0::MulX(normal, Vu0::Dot(v, normal)));
            u128 len2 = Vu0::Dot(tangent, tangent);
            Vu0::Q(acc) = tangent;
            f32 len = Vu0::ToFloat(len2);
            if (top < len) {
                Vu0::Q(best) = tangent;
                top = len;
                bestIndex = i;
                bestContact = c;
            }
        }
        if (bestContact == 0) {
            return;
        }
        ActiveSetItem* twin = (ActiveSetItem*)(self->items + bestIndex * 0x60);
        ActiveSetItem* it = (ActiveSetItem*)(self->items + self->count * 0x60);
        it->twin = twin;
        twin->twin = it;
        f32 mag = -Fpu::Sqrt(top);
        it->owner = bestContact;
        ContactEnd03* end = ((Contact03*)bestContact)->end;
        it->val = mag;
        Vu0::Q(acc) = Vu0::FromFloat(1.0f / mag);
        Vu0::Q(it->axis) = Vu0::MulX(Vu0::Q(best), Vu0::Q(acc));
        it->kind = 1;
        it->bounded = 1;
        it->limit = it->twin->x * bestContact->f94;
        for (s32 j = 0; j < 2; j++) {
            void* h = FindHandlerForSlot(end[j].part, 0x108);
            if (h != 0) {
                HandlerFn fn = *(HandlerFn*)(*(u8**)h + 0x108);
                if (fn != 0) {
                    fn(h, dt, a1 | 0x10, it, j);
                }
            }
        }
        AddActiveSetItem(self, it);
    }
}
