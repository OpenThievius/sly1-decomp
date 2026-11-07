// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 456/460, checked 2026-11-07
// NEAR: the tests, the reach compare (ToFloatMoved), NormalizeOr and the MulAddX2 of the base, the direction and g_unitZVector with their two ScalarAts are retail's, registers included. Still differs: retail is one instruction longer, forming d's address in a1 before the normalisation and storing the sum through it (here sqc2 to 0(sp)); the arguments of slot 21 (a1 before a0) and the registers of the slot loads for slots 36 and 77. Set for the first store and d through a pointer: no change.
#include "common.h"
#include "switched_collider.h"
#include "object_set.h"
#include "globals.h"
#include "vu0.h"

typedef s32 (*SlotTest)(void* self);
typedef void (*SlotFn)(void* self);
extern f32 D_0026A910;
extern f32 D_0026A914;

void UpdateCollider(void* self);
SwitchedCollider* GetActiveSwitchedCollider(void);

// The part of the active collider's block at 0x580 that UpdateObjectSet reads.
struct ActiveReach {
    s32 on;                 // 0x00
    u8 pad04[0x14 - 0x04];
    f32 reach;              // 0x14
    PlacedObject* target;   // 0x18
};

// Each frame while the active collider is near: the set moves to a point 100 out from its
// target, on the ground away from the set.
void UpdateObjectSet(ObjectSet* self)
{
    Vec02 d;
    UpdateCollider(self);
    s32 held = self->f59C;
    self->f59C = 0;
    SwitchedCollider* a = GetActiveSwitchedCollider();
    if (a == 0) {
        return;
    }
    if (((SlotTest*)self->desc)[76](self) != 1) {
        return;
    }
    ActiveReach* r = (ActiveReach*)&a->f580;
    if (r->on == 0) {
        return;
    }
    if (r->target == 0) {
        return;
    }
    if (held == 0) {
        f32 reach = r->reach + self->f550;
        u128 e = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(r->target->v140));
        s32 far = reach * reach <= Vu0::ToFloatMoved(Vu0::Dot(e, e));
        if (far) {
            return;
        }
    }
    self->desc->m15(self, 0);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(r->target->v140));
    d.z = 0.0f;
    u128 out = Vu0::ScalarAt(D_0026A910);
    u128 base = Vu0::Q(r->target->v150);
    u128 dir = Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(D_00248D30));
    u128 up = Vu0::ScalarAt(D_0026A914);
    Vu0::Q(d) = Vu0::MulAddX2(base, dir, out, Vu0::Q(g_unitZVector), up);
    self->desc02()->m20(self, &d);
    ((SlotFn*)self->desc)[77](self);
}
