// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 157/160 (98.1%), checked 2026-11-05
#include "common.h"

extern volatile s32 D_00279454;
extern volatile s32 D_00279458;
extern volatile s32 D_00279430;
extern volatile s32 D_00279428;
extern volatile s32 D_00279420;
extern volatile s32 D_00279414;
extern volatile s32 D_0062A7C0;

void func_001F6B50(s32 a);

void func_00202DA0(s32* code) {
    D_00279454 = *code;
    D_00279458 = D_00279454;
    if (D_00279454 == 11) {
        D_00279454 = 0;
        D_00279430 = 0;
    } else {
        func_001F6B50(D_00279428);
        if (D_00279414 && D_0062A7C0) {
            func_001F6B50(D_00279420);
        } else {
            D_00279430 = 0;
        }
        D_00279454 = 0;
    }
}
