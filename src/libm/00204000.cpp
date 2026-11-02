// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

f32 func_00205318(f32 x)
{
    s32 i0 = *(s32*)&x;
    s32 j0 = ((i0 >> 23) & 0xff) - 0x7f;
    s32 i;

    if (j0 < 0x17) {
        if (j0 < 0) {
            if (1.0e30f + x > 0.0f) {
                if (i0 >= 0) {
                    i0 = 0;
                } else if ((i0 & 0x7fffffff) != 0) {
                    i0 = 0xbf800000;
                }
            }
        } else {
            i = 0x7fffff >> j0;
            if ((i0 & i) == 0) {
                return x;
            }
            if (1.0e30f + x > 0.0f) {
                if (i0 < 0) {
                    i0 += 0x800000 >> j0;
                }
                i0 &= ~i;
            }
        }
    } else {
        if (j0 == 0x80) {
            return x + x;
        }
        return x;
    }
    *(s32*)&x = i0;
    return x;
}

struct Exc_205578 {
    s32 type;
    const char* name;
    s64 arg2;
    s64 arg1;
    double ret;
    s32 err;
};

extern s32 D_0024FF78;
extern u8 D_0024F8F0[];
f32 func_00206298(f32 x);
s32 func_00209238(f32 x);
f32 func_002052F8(f32 x);
s64 func_001FD868(f32 x);
s32 func_00208FE8(Exc_205578* e);
s32* func_002014F0();
f32 func_001FD578(double v);

f32 func_00205578(f32 x) {
    f32 r = func_00206298(x);
    s32 mode = D_0024FF78;
    if (mode != -1) {
        if (func_00209238(x) == 0) {
            if (func_002052F8(x) > 1.0f) {
                Exc_205578 e;
                e.type = 1;
                e.name = (const char*)D_0024F8F0;
                e.err = 0;
                e.arg1 = func_001FD868(x);
                e.ret = 0.0;
                e.arg2 = e.arg1;
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
    return r;
}
