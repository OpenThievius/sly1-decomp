// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 139/148 (93.9%), checked 2026-11-06
// NEAR: D_00279428 is volatile, as func_00202DA0 (the callback that sets it) reads it: that puts
//       the store of the first result in the second jal's delay slot, as retail has. Left: the
//       last two stores, where ours loads D_00279430's high half before the store to D_00279420
//       (into a0) and retail after it (into v0). Making D_00279420 volatile too lets CSE share
//       its high half with D_0027942C's and grows the frame.
#include "common.h"
struct Buf_00202EF0 { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; };
s32 func_001F6B20(Buf_00202EF0* self);
extern s32 D_00279420;
extern volatile s32 D_00279428;
extern s32 D_0027942C;
extern s32 D_00279430;
void func_00202EF0(void)
{
    if (D_00279428 == -1 || D_0027942C == -1) {
        Buf_00202EF0 b;
        b.f14 = 0;
        b.f8 = 1;
        b.f4 = 1;
        D_00279428 = func_001F6B20(&b);
        D_0027942C = func_001F6B20(&b);
        b.f8 = 0;
        D_00279420 = func_001F6B20(&b);
        D_00279430 = 0;
    }
}
