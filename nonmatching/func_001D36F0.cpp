// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 740/752, checked 2026-11-07
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "child_group_object.h"
#include "screen_element.h"
#include "object_link.h"
#include "object_message.h"
#include "owner_message.h"
#include "output_buffer.h"
#include "shapes.h"
#include "globals.h"
#include "game_clock.h"
#include "c8b.h"
#include "vu0.h"
// NEAR (2026-11-08, worker vu0w4-e1; tools/regdiff.py: code 70.7%): the structure is retail's, as is
// the vector sequence. Not retail's yet: the loop. Retail keeps 1.0 in $f20 across the six mover calls
// (swc1 $f0,0($s3); mov.s $f20,$f0) and recomputes the item's address from the index each time
// (`li v0,80`; `mult v1,s4,v0`; `addu s1,v1,s3`), the C here materialises the 1.0 at each call and
// strength-reduces the address. Tried: the 1.0 stored first, read back, chained, an unsigned
// index, a byte pointer with the multiplication, `continue`. (func_001D4148, the same family, steps by
// 0x20 and has none of this.) NOTE: tools/check.py reports EXACT for this body while the stub
// INCLUDE_ASM(func_001D36F0) is in the file, because it then compares the stub's own bytes.
extern s32 D_00274FA0[2];
extern s32 D_00274FA8[2];
extern s32 D_00274FB0[2];
extern s32 D_00274FB8[2];
// The eight blend slots func_001D4148 fills (0x20 bytes each), the weight of slot 6 first.
struct BlendSlotObject;
struct BlendSlot {
    f32 weight;             // 0x00
    BlendSlotObject* object; // 0x04
    u8 pad08[0x10 - 0x08];
    Vec02 v10;              // 0x10: where the object's mover puts it
};

typedef void (*SlotMoveFn)(Mover8B* m, void* body, f32 x, f32 y, s32 z, Vec02* out, Vec02* out2);
struct SlotMover { SlotMoveFn* vtbl; };
struct SlotMoverHolder { u8 pad00[4]; SlotMover* mover; };
struct BlendSlotObject {
    u8 pad00[0x34];
    f32 f34;                // 0x34
    u8 pad38[0x9C - 0x38];
    SlotMoverHolder* holder; // 0x9C
};

Entry8B* FindEntryByObjectId(void* object, void* body);
void BuildCombinedBlendAnimation(TurningCollider* self, s32 stride, s32 count, BlendSlot* slots, s32 a, s32 b, s32 c, Gr8B** gr);

struct PlayerBlendItem {
    f32 weight;             // 0x00
    BlendSlotObject* object; // 0x04
    u8 pad08[0x10 - 0x08];
    Vec02 v10;              // 0x10
    Vec02 v20;              // 0x20
    f32 f30;                // 0x30
    u8 pad34[0x40 - 0x34];
    f32 f40;                // 0x40
    u8 pad44[0x50 - 0x44];
};
struct PlayerBlendCurve { u8 pad00[0x10]; void* f10; };

void ComputeWrappedDeltas(s32 stride, s32 count, void* base, s32 off, s32 mode, void* table);
void SetBlendItemWeights(Gr8B* obj, s32 a1, s32 a2, void* a3);

void func_001D36F0(TurningCollider* self, PlayerBlendItem* items, Gr8B** out)
{
    Vec02 a0;
    Vec02 a10;
    Vec02 a20;
    Vec02 a30;
    Gr8B* blend;
    f32 one;
    s32 i;

    if (items[0].object == 0) {
        *out = 0;
        return;
    }
    one = 1.0f;
    items[0].weight = one;
    ComputeWrappedDeltas(0x50, 6, items, 0x30, 2, D_00274FA0);
    ComputeWrappedDeltas(0x50, 6, items, 0x40, 2, D_00274FA8);
    for (i = 0; i < 6; i++) {
        PlayerBlendItem* it = &items[i];
        BlendSlotObject* o = it->object;
        if (o != 0) {
            SlotMover* m = o->holder->mover;
            (*m->vtbl)((Mover8B*)m, self, 0.0f, one, 0, &a0, 0);
            m = o->holder->mover;
            (*m->vtbl)((Mover8B*)m, self, o->f34, one, 0, &a10, 0);
            Vu0::Q(it->v10) = Vu0::DivX(Vu0::Sub(Vu0::Q(a0), Vu0::Q(a10)), Vu0::FromFloatAt(o->f34));
            m = (SlotMover*)FindEntryByObjectId(it->object, self->f610)->mover;
            (*m->vtbl)((Mover8B*)m, self->f610, it->f30, one, 0, &a20, 0);
            m = (SlotMover*)FindEntryByObjectId(it->object, self->f614)->mover;
            (*m->vtbl)((Mover8B*)m, self->f614, it->f40, one, 0, &a30, 0);
            u128 h = Vu0::FromFloat(0.5f);
            Vu0::Q(it->v20) = Vu0::MulXSum(Vu0::Q(a20), h, Vu0::Q(a30), h);
        }
    }
    BuildCombinedBlendAnimation((TurningCollider*)self, 0x50, 6, (BlendSlot*)items, 2, (s32)D_00274FB8, (s32)D_00274FB0, &blend);
    for (i = 0; i < blend->f38; i++) {
        Entry8B* e = (Entry8B*)(blend->f3C + i * 0x1C);
        s32 k = e->key;
        if (k >= 0x37) {
            if (k < 0x3A) {
                continue;
            }
            if (k < 0x3D) {
                if (e->mover != 0) {
                    ((PlayerBlendCurve*)e->mover)->f10 = blend->pC0 + 1;
                }
                if (e->sub != 0) {
                    ((PlayerBlendCurve*)e->sub)->f10 = blend->pC0 + 1;
                }
                continue;
            }
        }
        if (e->mover != 0) {
            ((PlayerBlendCurve*)e->mover)->f10 = 0;
        }
        if (e->sub != 0) {
            ((PlayerBlendCurve*)e->sub)->f10 = 0;
        }
    }
    SetBlendItemWeights(blend, 0x50, 6, items);
    if (out != 0) {
        *out = blend;
    }
}

