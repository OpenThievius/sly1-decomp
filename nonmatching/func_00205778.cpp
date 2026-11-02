// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 288/296 (97.3%), checked 2026-11-02
#include "common.h"
// NEAR: only the prologue order differs: retail saves f21 before f20 and copies b (f13->f21) before the first call with a's copy (f12->f20) in the jal delay slot; ours does the reverse. Tried r/mode order, a bb copy of b, r declared first.

struct Exc_205778 {
    s32 type;
    const char* name;
    s64 arg1;
    s64 arg2;
    double ret;
    s32 err;
};

extern s32 D_0024FF78;
extern u8 D_0024F900[];
f32 func_00206A68(f32 x);
s32 func_00209238(f32 x);
s64 func_001FD868(f32 x);
s32 func_00208FE8(Exc_205778* e);
s32* func_002014F0();
f32 func_001FD578(double v);

f32 func_00205778(f32 a, f32 b)
{
    f32 r = func_00206A68(a);
    s32 mode = D_0024FF78;
    if (mode != -1) {
        if (func_00209238(b) == 0) {
            if (func_00209238(a) == 0) {
                if (b == 0.0f) {
                    if (a == 0.0f) {
                        Exc_205778 e;
                        e.arg1 = func_001FD868(a);
                        e.arg2 = func_001FD868(b);
                        e.type = 1;
                        e.name = (const char*)D_0024F900;
                        e.ret = 0.0;
                        e.err = 0;
                        if (mode == 2 || func_00208FE8(&e) == 0) {
                            *func_002014F0() = 0x21;
                        }
                        if (e.err != 0) {
                            *func_002014F0() = e.err;
                        }
                        return func_001FD578(e.ret);
                    }
                }
            }
        }
    }
    return r;
}
