// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: toggles a screen's mode (offsets 0x56C/0x570 in PAL).
struct Obj_1940E8_eu {
    void** vtbl;
    u8 pad_004[0x56C - 4];
    s32 f56C;
    s32 f570;
};
typedef void (*VFn_1940E8_eu)(Obj_1940E8_eu* self);
void func_001E96F8(Obj_1940E8_eu* self, s32 mode);
void func_00193EE8(Obj_1940E8_eu* self, s32 a, s32 b);

void func_001940E8(Obj_1940E8_eu* self, s32 mode) {
    if (self->f56C == mode) return;
    if (mode != 0) {
        s32 key = (g_saveData->f19D8 << 8) | g_saveData->f19DC;
        if (key == 0x308) {
            func_001BED48();
            SetElementStackState((Obj_1940E8_eu*)g_elementStack, 5);
        } else if (D_0027051C != 0) {
            SetElementStackState((Obj_1940E8_eu*)g_elementStack, 5);
        } else {
            u8* base = g_elementStack;
            if (((s32*)base)[1] == 3) {
                SetElementStackState((Obj_1940E8_eu*)base, 4);
            } else {
                SetElementStackState((Obj_1940E8_eu*)base, 5);
            }
        }
        ChangePauseMenuPage(self, -1, self->f570);
        ((VFn_1940E8_eu)self->vtbl[14])(self);
        SetPadSelectFlags((Bits_1940E8)1);
        ResetPadStepRepeat(&g_padRecord);
    } else {
        s32 key = (g_saveData->f19D8 << 8) | g_saveData->f19DC;
        if (key == 0x308) {
            func_001BED70();
            SetElementStackState((Obj_1940E8_eu*)g_elementStack, 3);
        } else if (D_0027051C != 0) {
            SetElementStackState((Obj_1940E8_eu*)g_elementStack, 3);
        } else if (self->f570 != 0) {
            SetElementStackState((Obj_1940E8_eu*)g_elementStack, 3);
        } else {
            SetElementStackState((Obj_1940E8_eu*)g_elementStack, 6);
        }
        ChangePauseMenuPage(self, self->f570, -1);
        ((VFn_1940E8_eu)self->vtbl[15])(self);
        ClearPadSelectFlags((Bits_1940E8)1);
    }
    self->f56C = mode;
}

