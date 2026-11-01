// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL returns 0 early when a PAL-only flag is set, before the final func_001E1F10 call.
extern s32 D_eu_0025D6B8;

s32 func_0011D078(void)
{
    u32* table;

    func_001F6C20(0);
    if (D_0025C340 == 0) {
        return 1;
    }
    if (func_001F8480((Arg_0011D078*)D_0027B4C8) != 0) {
        return 0;
    }
    table = (u32*)D_0025C340;
    if (table[0] == 0xFFFFFFFF) {
        if (table[D_0025C344 + 1] == table[0]) {
            D_0025C340 = 0;
            return 1;
        }
    }
    if (D_eu_0025D6B8 != 0) {
        return 0;
    }
    func_001E1F10((Arg_0011D078*)D_00249460);
    return 0;
}
