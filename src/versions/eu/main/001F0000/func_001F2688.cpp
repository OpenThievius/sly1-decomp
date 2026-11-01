// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: on the reset key only sets the scaled value to three quarters of its base; no table set-up.
// D_eu_0027FDAC and D_eu_0027FDB0 are US D_00276648 and D_00276650, at addresses the tools do not pair.

extern f32 D_eu_0027FDAC;
extern f32 D_eu_0027FDB0;

void func_001F2688(s32 a0, s32 a1)
{
    if (a1 != 0xFFFF) return;
    if (a0 == 0) return;
    D_eu_0027FDB0 = D_eu_0027FDAC * 0.75f;
}
