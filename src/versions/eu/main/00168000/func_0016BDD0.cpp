// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: Mgr_16BDD0 fields x25C and x260 are at 0x56C and 0x570 (US 0x25C, 0x260).
struct Mgr_16BDD0_eu { VFn_16BDD0* vtbl; u8 pad0[0x56C - 4]; s32 x56C; s32 x570; };

void func_0016BDD0(Mgr_16BDD0_eu* self, s32 flag)
{
    if ((flag != 0) != (self->x56C == 0)) {
        return;
    }
    if (flag != 0) {
        s32 bit = 15;
        func_0016E0F0(1);
        func_0016EC88(D_00262C70);
        self->vtbl[14](self);
        s32 mask = func_0016BB78(15);
        Glob_16BDD0* g = (Glob_16BDD0*)D_002623C0;
        for (; bit > 0; bit--) {
            if (g->w19F4 & mask) {
                break;
            }
            mask >>= 1;
        }
        self->x570 = bit;
    } else {
        func_0016E118(1);
        self->vtbl[15](self);
    }
    self->x56C = flag;
}

