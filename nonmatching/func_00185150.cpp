// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 524/516, checked 2026-11-08
// NEAR: control flow, the vi2/vi3/vi4 moves, vnop, vcallms 0x60/0x168 and the light loop are retail's (about 435 of 516 bytes by instruction). Left: the loop variable is a0 in ours and a1 in retail (retail's kind is a0), s5/s6 swapped (the light table address and the out-count pointer), the order of the group's field loads (lhu 14, lw 4, lhu 12) and a few delay-slot placements; the prev test is a beqzl with a duplicated move in ours.
// Still differs (2026-11-08, vcallms worker): the group computed inside the else branch, the nested ifs and a keepOut mask local moved the allocation without improving it.
#include "common.h"
#include "vu0.h"
#include "placed_object.h"

struct LightGroup { void** lights; s32 count; s32 flags; u16 kind; s16 fE; };
extern s32 g_lightGroupCount;
extern LightGroup g_lightGroups[16];

struct LightMode { u8 pad[0x2D4]; s32 mode; };

s32 func_00185150(u8* scene, const Vec02* centre, u32 skipMask, s32 maxLights, s32* flagged, s32* outCount, LightMode** out, f32 radius)
{
    u32 keepOut = ~skipMask;
    s32 num = 0;
    s32 flaggedCount = 0;
    LightGroup* prev = 0;
    u32 mask;
    s32 strongest = *(f32*)(scene + 0x1D6C) != 0.0f;
    Vec02 sphere = *centre;
    sphere.w = radius;
    Vu0::LoadVf<31>(&sphere);
    for (s32 i = 0; i < g_lightGroupCount + 1; i++) {
        LightGroup* grp = &g_lightGroups[i];
        if (i == g_lightGroupCount) {
            mask = Vu0::ReadViWait<2>();
        } else {
            if (grp->flags & keepOut) {
                continue;
            }
            Vu0::MoveToViWait<3>((u16)grp->fE);
            Vu0::MoveToVi<4>(grp->count);
            mask = Vu0::ReadVi<2>();
            Vu0::VuNop();
            switch (grp->kind) {
            case 0:
                Vu0::MoveToVi<2>(0xFFFF);
                break;
            case 1:
                Vu0::CallMs<0x60>();
                break;
            case 2:
                Vu0::CallMs<0x168>();
                break;
            }
        }
        if (prev && prev->count > 0) {
            s32 bit = (1 << prev->count) >> 1;
            for (s32 k = 0; k < prev->count; k++) {
                if (((s32)mask & bit) && num < maxLights) {
                    LightMode* l = (LightMode*)prev->lights[k];
                    out[num++] = l;
                    if (strongest < l->mode) {
                        strongest = l->mode;
                    }
                    flaggedCount += prev->flags & 1;
                }
                bit >>= 1;
            }
        }
        prev = grp;
    }
    *outCount = num;
    if (flagged) {
        *flagged = flaggedCount;
    }
    return strongest;
}
