// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 268/276 (97.1%), checked 2026-11-02
#include "common.h"

struct Exc_206180 {
    s32 type;
    const char *name;
    s64 a;
    s64 b;
    double r;
    s32 err;
};

extern s32 D_0024FF78;
extern char D_0024F958[];
extern double D_0024F960;

f32 func_00208068(void);
s32 func_00209238(f32 x);
s64 func_001FD868(f32 x);
s32 func_00208FE8(Exc_206180 *e);
s32 *func_002014F0(void);
f32 func_001FD578(double v);

f32 func_00206180(f32 x)
{
    s32 mode;
    f32 r = func_00208068();
    mode = D_0024FF78;
    if (mode != -1) {
        if (func_00209238(x) == 0) {
            if (x < 0.0f) {
                Exc_206180 e;
                e.type = 1;
                e.name = D_0024F958;
                e.err = 0;
                e.b = func_001FD868(x);
                e.a = e.b;
                if (mode == 0)
                    e.r = 0.0;
                else
                    e.r = D_0024F960;
                if (D_0024FF78 == 2 || func_00208FE8(&e) == 0)
                    *func_002014F0() = 0x21;
                if (e.err != 0)
                    *func_002014F0() = e.err;
                return func_001FD578(e.r);
            }
        }
    }
    return r;
}
