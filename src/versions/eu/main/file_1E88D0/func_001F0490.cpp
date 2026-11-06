// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's own definition: reports whether an action is allowed, with the selector and index it used.
s32 func_001F0490(C67* self, s32 kind, s32* outA, s32* outB)
{
    s32 sel = -1;
    s32 idx = -1;
    s32 flag = 0;
    if (kind == 10) {
        sel = 0;
        idx = 4;
        flag = 1;
    } else {
        s32 mode = self->slot;
        s32 allowed = 1;
        if (mode == 5 && (kind == 1 || kind == 7)) {
            allowed = 0;
        }
        if (kind == 9) {
            if (allowed != 0) {
                s32 m = mode * 0x44C;
                if (*(s32*)((u8*)g_saveData + m + 0x88) & 1) {
                    s32 q = g_saveData->levels[mode].f448;
                    flag = (q & D_00275FC8[mode]) != 0;
                }
            }
        } else {
            s32 c = kind < 9;
            idx = -1;
            if (c) {
                idx = kind;
            }
            sel = mode;
            flag = 0;
            if (allowed != 0) {
                flag = *(s32*)((u8*)g_saveData + (sel * 0x44C + idx * 0x78) + 0x10) & 1;
            }
        }
    }
    if (outA != 0) {
        *outA = sel;
    }
    if (outB != 0) {
        *outB = idx;
    }
    return flag;
}
