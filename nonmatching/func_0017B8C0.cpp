// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 185/212 (87.3%), checked 2026-11-07
#include "common.h"
// Tried night-close8, 6 compiles and tools/permute.py --auto: the 1.0 as a named float local gives retail's -1.0 register and the 1.0's mtc1 next to it, 12 differing words down to 9 (permute.py's order). Both constants named, the 4 named, the local before t: no closer.
// NEAR: retail forms the table's address (lui v0) before the 1.0's lui and stores in source order (f270 first after f27C); here the 1.0 is loaded first and sched2 orders the eight stores otherwise.
// Before: NEAR: the switch on state gives retail branch layout; the float constants and field stores in the state-1 block are scheduled in a different order

struct Obj_17B8C0 {
    u8 pad0[0x14];
    void* f14;
    u8 pad18[0x550 - 0x18];
    s32 f550;
    f32 f554;
};

struct Table_17B8C0 {
    u8 pad0[0x260];
    s32 f260;
    s32 f264;
    s32 f268;
    s32 f26C;
    s32 f270;
    s32 f274;
    f32 f278;
    f32 f27C;
};

extern s32 D_00263E2C;
extern f32 g_gameTime;
extern u8 g_gaugeBarElement[];
extern u8 g_memoryCard[];

void SetWorldActiveFollower(void* a, void* b);
void MarkLevelDone(s32 n);
void StartMemoryCardSave(void* p);

void SetCountdownState(Obj_17B8C0* self, s32 state)
{
    Table_17B8C0* t;

    if (state == self->f550) {
        return;
    }
    D_00263E2C = -1;
    switch (state) {
    case 1:
        t = (Table_17B8C0*)g_gaugeBarElement;
        {
        f32 one = 1.0f;
        t->f27C = -1.0f;
        t->f270 = 4;
        t->f278 = one;
        t->f268 = 0x10;
        t->f260 = 4;
        t->f26C = 4;
        t->f264 = 4;
        t->f274 = 0;
        }
        SetWorldActiveFollower(self->f14, self);
        self->f550 = state;
        break;
    case 2:
        MarkLevelDone(5);
        StartMemoryCardSave(g_memoryCard);
        self->f550 = state;
        break;
    default:
        self->f550 = state;
        break;
    }
    self->f554 = g_gameTime;
}
