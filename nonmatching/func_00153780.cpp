// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 724/716, checked 2026-11-07
// NEAR: the loops and calls are retail's; left: register pressure (retail keeps the contact pointer in a stack slot and a1 in s7; here the contact gets s8 and a1 is spilled) and the Zero vector hoisted to the function start instead of before the second loop. Needs ActiveSetItem::rows at 0x20 (include/active_set_solver.h).
#include "common.h"
#include "collider.h"
#include "active_set_solver.h"
#include "vu0.h"
#include "placed_object.h"
struct Contact03;

typedef void (*EndRowsFn)(Collider* body, s32 a1, void* contact, s32 end, ActiveSetItem* item, f32* rows);
typedef void (*EndFillFn)(Collider* body, s32 a1, s32 size, s32 extra, f32* rows);
void* AllocateZeroedBackMemory(s32 bytes);
void* AllocateBackMemory(s32 bytes);
void ComputeColliderPointVelocity(Collider* part, Vec02* pos, f32* row, Vec02* out);

void func_00153780(ActiveSetSolver* self, s32 a1, ActiveSetItem* n, s32 a3, s32 a4, s32 a5, s32 a6)
{
    Contact03* contact = (Contact03*)n->owner;
    s32 i;
    ContactEnd03* end = contact->end;
    for (i = 0; i < 2; i++, end++) {
        Collider* body = end->body;
        if (body != 0 && body->f4BC >= 0) {
            s32 idx = body->f4BC << 2;
            s32* size = (s32*)(idx + a5);
            f32* r = (f32*)AllocateZeroedBackMemory(*size << 5);
            n->rows[i] = r;
            ((EndRowsFn*)body->desc)[58](body, a1, contact, i, n, r);
            ((EndFillFn*)body->desc)[59](body, a1, *size, *(s32*)(idx + a6), r);
        }
    }
    Vec02* axes = (Vec02*)AllocateBackMemory(a3 << 4);
    n->axes = (u8(*)[16])axes;
    Vec02 out[2];
    u128 zero = Vu0::Zero();
    for (i = 0; i < a3; i++) {
        ContactEnd03* e = *(ContactEnd03**)(i * 4 + a4);
        for (s32 j = 0; j < 2; j++) {
            Collider* body = e[j].body;
            if (body != 0 && body->f4BC >= 0) {
                if (body == contact->end[0].body) {
                    Collider* part = e[j].part;
                    ComputeColliderPointVelocity(part, &e[j].v10, (f32*)((u8*)n->rows[0] + (part->index << 5)), &out[j]);
                } else if (body == contact->end[1].body) {
                    Collider* part = e[j].part;
                    ComputeColliderPointVelocity(part, &e[j].v10, (f32*)((u8*)n->rows[1] + (part->index << 5)), &out[j]);
                } else {
                    Vu0::Q(out[j]) = zero;
                }
            } else {
                Vu0::Q(out[j]) = zero;
            }
        }
        Vu0::Q(axes[i]) = Vu0::Sub(Vu0::Q(out[0]), Vu0::Q(out[1]));
    }
    f32* row = (f32*)AllocateBackMemory(self->slots << 2);
    n->row = row;
    for (i = 0; i < self->count; i++) {
        ActiveSetItem* it = (ActiveSetItem*)(self->items + i * 0x60);
        *(u32*)row++ = Vu0::ToBits(Vu0::Dot(Vu0::Q(it->axis), Vu0::Q(((Vec02*)n->axes)[*(s32*)((u8*)it->owner + 0xCC)])));
    }
}
