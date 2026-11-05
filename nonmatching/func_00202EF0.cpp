// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 131/148 (88.5%), checked 2026-11-05
// NEAR: order: the body is retail's (a 6-word struct, three calls to func_001F6B20); only `move
//       a0,sp` and the store to D_00279428 around the second jal are scheduled differently.
#include "common.h"
struct Buf_00202EF0 { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; };
s32 func_001F6B20(Buf_00202EF0* self);
extern s32 D_00279420;
extern s32 D_00279428;
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
