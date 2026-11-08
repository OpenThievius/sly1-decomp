// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 105/108 (97.2%), checked 2026-11-07
// NEAR: registers only: every instruction lines up; v0 and v1 are swapped in the lw/lbu pair.
//       Storing fB4, f94, fB0 in that order fixed the store order.
#include "common.h"
#include "id_lookup_object.h"

extern World* g_currentWorld;
s32 CollectLightsForSphere(void* a0, s32 a1, s32 a2, s32 a3, s32* a4, s32* a5, s32* a6);
struct Obj_161B10 {
    u8 pad0[0x94];
    s32 f94;
    u8 pad98[4];
    s32 f9C;
    u8 padA0[0xB0 - 0xA0];
    s32 fB0;
    s32 fB4;
    s32 fB8;
    u8 padBC[0xF8 - 0xBC];
    u8* fF8;
};
void SelectVertexBatchLights(Obj_161B10* self, s32 a1)
{
    if (*self->fF8 != 0) {
        self->fB4 = 0;
        self->f94 = -1;
        self->fB0 = 0;
    } else {
        self->f9C = CollectLightsForSphere(g_currentWorld, a1, 1, 0x10, &self->fB0, &self->fB4, &self->fB8);
        self->f94 = 4;
    }
}
