// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 112/128 (87.5%), checked 2026-11-02
#include "common.h"

// NEAR: 5 lines differ. Retail stores -1 to D_00279454 before it loads D_00279420
// (lui s0; lw a0 in the jal delay slot); this schedules lui s0/lw a0 ahead of the store.
// Wrapping the store in do { } while (0) gives EXACT (func_00202F88_dowhile.cpp), which the
// rules forbid; volatile on D_00279454 and/or D_00279420 does not fix it (and breaks the
// delay-slot fill); decomp-permuter (8.5k iterations, no empty-stmt/ins-block) found nothing.

extern s32 D_00279414;
extern s32 D_00279454;
extern s32 D_00279420;
extern s32 D_00279428;
extern s32 D_0027942C;

s32 func_001F6B40(s32 a);
s32 func_001F6B30(s32 a);
s32 func_001F9D60(void);
s32 func_001FA4D0(u32 a);
s32 func_001F9DA8(void);

void func_00202F88(void) {
    if (D_00279414) {
        D_00279454 = -1;
        func_001F6B40(D_00279420);
    }
    func_001F6B30(D_00279428);
    func_001F6B30(D_0027942C);
    func_001F6B30(D_00279420);
    func_001F9D60();
    func_001FA4D0(0x80000012);
    func_001F9DA8();
}
