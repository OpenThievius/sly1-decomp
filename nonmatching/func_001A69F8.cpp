// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 484/488, checked 2026-11-07
// NEAR: every case but 4 is retail's, the jump table included (cases 0, 7, 8 and 10 named so that it starts at 0). In case 4 retail branches to the else path (bc1fl, lw a0 in the slot) and falls into s = 4 (b, li s1, 4); here the compiler branches to the end with li s1, 4 in a bc1t's slot, one instruction shorter. An early break, if/else, the test inverted with ||, and the compare written with >: no change.
#include "common.h"
#include "placed_object.h"
#include "paired_object.h"
#include "pair_controller.h"
#include "vu0.h"

void ConvertPositionToWorld(void* frame, Vec02* out);
void LinkPairedObjects(u8* self, PairedObject* obj, PairedObject* node);
s32 PairWithNearestFreeObject(void* self, void* child);
s32 func_001A6328(PairController* self, PairedObject* obj);

static inline f32 GroundDistance(u128 a, u128 b)
{
    u128 d = Vu0::Sub(a, b);
    return Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
}

void* FindHitTargetChild(Collider* self);

// The state the paired object should be in: free (1) until it reaches its attachment and a
// free partner takes it (3) or none (2); while paired (2, 3) until a hit target child links
// it (4); then back to an attachment (5) and close in on it (6, then 0); 9 ends in 10.
s32 ChoosePairedObjectState(PairedObject* self)
{
    Vec02 v;
    s32 s = self->state;
    switch (s) {
    case 1: {
        void* h = FindHitTargetChild(self);
        if (h != 0) {
            LinkPairedObjects((u8*)self->controller, self, (PairedObject*)h);
            s = 4;
            break;
        }
        ConvertPositionToWorld(*(void**)((u8*)self->attachment + 0x564), &v);
        if (GroundDistance(Vu0::Q(v), Vu0::Q(self->v140)) < 10.0f) {
            s = 2;
            if (PairWithNearestFreeObject(self->controller, self) != 0) {
                s = 3;
            }
        }
        break;
    }
    case 2:
    case 3: {
        void* h = FindHitTargetChild(self);
        if (h != 0) {
            LinkPairedObjects((u8*)self->controller, self, (PairedObject*)h);
            s = 4;
        }
        break;
    }
    case 4: {
        u8* p = (u8*)self->activeHandle;
        if (p != 0 && *(f32*)(p + 0x14) < *(f32*)((u8*)self->f594 + 0x34)) {
            s = 4;
            break;
        }
        s = 2;
        if (func_001A6328((PairController*)self->controller, self) != 0) {
            s = 5;
        }
        break;
    }
    case 5:
        ConvertPositionToWorld(*(void**)((u8*)self->attachment + 0x564), &v);
        if (GroundDistance(Vu0::Q(self->v140), Vu0::Q(v)) < 10.0f) {
            s = 6;
        }
        break;
    case 6:
        if (GroundDistance(Vu0::Q(self->v140), Vu0::Q(((PlacedObject*)self->attachment)->v140)) < 10.0f) {
            s = 0;
        }
        break;
    case 0:
    case 7:
    case 8:
    case 10:
        break;
    case 9:
        s = 10;
        break;
    }
    return s;
}
