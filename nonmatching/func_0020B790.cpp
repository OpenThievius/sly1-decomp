// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 108/124 (87.1%), checked 2026-11-02
#include "common.h"
// NEAR: a3 = n-1 is computed before the lw of a1 and a2 = n-1 after (separate computations); ours merges them.

extern u8 D_00250118[];

struct Obj_0020B790 {
    u8 pad000[0x118];
    s32 f118;
    s32 f11C;
    s32 f120;
    u8 pad124[0x174 - 0x124];
    s32 f174;
    u8 pad178[0x1BC - 0x178];
    s32 f1BC;
    u8 pad1C0[0x1CC - 0x1C0];
    s32 f1CC;
    u8 pad1D0[0x1DC - 0x1D0];
    s32 f1DC;
};

void func_0020B978(struct Obj_0020B790 *self, void *a1, s32 a2);
void func_00210970(struct Obj_0020B790 *self, s32 a1, s32 a2, s32 a3);
void func_00210A80(struct Obj_0020B790 *self, s32 a1, s32 a2);

void func_0020B790(struct Obj_0020B790 *self)
{
    s32 n = self->f118;
    if (self->f120 != 0) {
        func_0020B978(self, D_00250118, n);
        self->f120 = 0;
    } else {
        s32 m = n - 1;
        if (self->f174 == 3) {
            func_00210970(self, self->f1BC, m, n - 1);
            self->f120 = 0;
        } else {
            func_00210A80(self, self->f1CC, self->f1DC);
            self->f120 = 0;
        }
    }
}
