// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 429/456 (94.1%), checked 2026-11-07
#include "common.h"
#include "masked_collider.h"
#include "switched_collider.h"
#include "object_message.h"
#include "vu0.h"
// NEAR (2026-11-08, wave 3 retry): FromFloatAt gives retail's lw. Left: self lives in s2 and
// the loop counter in s1 (retail the other way round); every other instruction is retail's. The
// declaration of i first, a while loop and ++i give the same allocation.
struct PathFollower;
void* GetActiveSwitchedCollider(void);
s32 IsObjectOfKind(MaskedCollider* n, s32 kind);
void TriggerScriptEvent(void* obj, s32 kind, s32 a, s32 b);

// The contact event func_0013D0B0 takes: the object that touched, a strength, two flag words and
// two vectors.
struct ContactEvent_0013D0B0 {
    PlacedObject* obj;      // 0x00
    u8 pad04[4];
    f32 f08;                // 0x08
    u32 flags;              // 0x0C
    u32 flags10;            // 0x10
    u8 pad14[0x20 - 0x14];
    Vec02 v20;              // 0x20
    Vec02 v30;              // 0x30
};

extern u8 g_padRecord[];
void StartPadRecordPattern(void* record, f32 x, s32 n);
void SetColliderAnchors(Collider* self, s32 a, s32 b, s32 c, s32 d);
void func_001BC0E0(Collider* self, Vec02* v, Vec02* w, f32 x);
s32 IsObjectAccepted(MaskedCollider* self, PathFollower* msg);
void* GetActiveSwitchedCollider(void);

s32 func_0013D0B0(MaskedCollider* self, ContactEvent_0013D0B0* ev)
{
    Vec02 push;
    Vec02 k;
    s32* counter;
    s32 i;

    if (self->hold != 0) {
        return 1;
    }
    if (ev->flags == 0) {
        return 0;
    }
    if (ev->obj == 0) {
        return 0;
    }
    if ((ev->obj->desc->flags & 2) == 0) {
        return 0;
    }
    for (i = 0; i < self->count668; i++) {
        if (IsObjectOfKind((MaskedCollider*)ev->obj, (s32)self->list66C[i]) != 0) {
            break;
        }
    }
    if (i >= self->count668) {
        if (IsObjectAccepted(self, (PathFollower*)ev->obj) == 0) {
            return 0;
        }
    }
    if ((ev->flags & 4) != 0) {
        return 1;
    }
    if ((ev->flags & 8) != 0) {
        Vu0::Q(k) = Vu0::FromFloatAt(self->f624);
        Vu0::Q(push) = Vu0::MulX(Vu0::Q(ev->v30), Vu0::Q(k));
        SetColliderAnchors(self, 0, 0, 0, 0);
        func_001BC0E0(self, &ev->v20, &push, ev->f08);
    }
    if ((ev->flags & 0x10) == 0) {
        return 1;
    }
    if (ev->obj == GetActiveSwitchedCollider()) {
        if ((ev->flags10 & 0x10) == 0) {
            StartPadRecordPattern(g_padRecord, 0.3f, 9);
        }
    }
    counter = &(*(s32*)((u8*)self + 0x690));
    (*(s32*)((u8*)self + 0x690))++;
    TriggerScriptEvent(self, 0x14, 1, (s32)&counter);
    if ((*(s32*)((u8*)self + 0x690)) >= self->f68C) {
        self->desc20()->m48(self);
    }
    return 1;
}

