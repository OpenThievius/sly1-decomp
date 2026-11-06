// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: Mgr_16BDD0 fields x25C and x260 are at 0x56C and 0x570 (US 0x25C, 0x260).
typedef void (*VFn_16BDD0)(void* self);
struct Mgr_16BDD0_eu { VFn_16BDD0* vtbl; u8 pad0[0x56C - 4]; s32 x56C; s32 x570; };

void func_0016BDD0(Mgr_16BDD0_eu* self, s32 flag)
{
    if ((flag != 0) != (self->x56C == 0)) {
        return;
    }
    if (flag != 0) {
        s32 bit = 15;
        SetPadSelectFlags(1);
        ResetPadStepRepeat(&g_padRecord);
        self->vtbl[14](self);
        s32 mask = TestGridEntryBit(15);
        GameProgress* g = g_saveData;
        for (; bit > 0; bit--) {
            if (g->u19F4 & mask) {
                break;
            }
            mask >>= 1;
        }
        self->x570 = bit;
    } else {
        ClearPadSelectFlags(1);
        self->vtbl[15](self);
    }
    self->x56C = flag;
}

