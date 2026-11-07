// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 223/228 (97.8%), checked 2026-11-07
#include "common.h"
// NEAR: both loops, the key and the 0x88/0x18 float tests match; float registers are swapped (retail keeps best in $f2 and -0.7 in $f1, ours the other way round). Global-alloc order from the RTL dumps: bestF (pri 2*7/42) beats the hoisted -0.7 (2*5/62, live length doubled by its REG_EQUIV); retail needs -0.7 first and 0.7 after bestF. Tried j39o03: constants as locals before/after bestF, for-loop with continue, merged ?: test, swapped if arms, bestF > f0, bestF declared first, if+do-while outer, goto outer loop. j40o06: for-loop with key||match nesting and ?:/&&-|| threshold tests, constants as locals inside the outer loop, bestF assigned last, bestF declared first, separate local for the 0x18 value, 0x88 re-read in each arm: all keep bestF (2*7/37) above -0.7 (2*5/52). greg shows no FP preferences, so only the priority order decides; retail needs -0.7 > bestF > 0.7, a window that the two constants (equal refs, lengths 2 apart) leave almost no room for. Looks out of reach of plain C rewording.

extern f32 D_0024D2A0;

void* FindColliderFloorContact(void* self, s32 key, s32* out)
{
    u8* n = *(u8**)(*(u8**)((u8*)self + 0x480));
    u8* bestIt = 0;
    s32 bestSel = 0;
    f32 bestF = D_0024D2A0;
    while (n) {
        u8* it = *(u8**)n;
        u8* nxt = *(u8**)(n + 4);
        while (it) {
            s32 sel = *(u32*)it != (u32)self;
            if (key != 0) {
                if (*(s32*)(it + (sel << 6) + 4) != key) {
                    it = *(u8**)(it + 0xD0);
                    continue;
                }
            }
            f32 f0 = *(f32*)(it + 0x88);
            if (sel == 0) {
                if (!(0.7f < f0)) {
                    it = *(u8**)(it + 0xD0);
                    continue;
                }
            } else {
                if (!(f0 < -0.7f)) {
                    it = *(u8**)(it + 0xD0);
                    continue;
                }
            }
            f0 = *(f32*)(it + (sel << 6) + 0x18);
            if (f0 < bestF) {
                bestF = f0;
                bestSel = sel;
                bestIt = it;
            }
            it = *(u8**)(it + 0xD0);
        }
        n = nxt;
    }
    if (out != 0) {
        *out = bestSel;
    }
    return bestIt;
}
