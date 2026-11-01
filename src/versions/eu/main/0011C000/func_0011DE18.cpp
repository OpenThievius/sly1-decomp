// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the debug print is skipped when the PAL-only flag D_eu_0025D6B8 is set.
extern s32 D_eu_0025D6B8;

void func_0011DE18(void)
{
    func_0011D110(D_0025C378[D_0025C380], *D_0025C360[D_0025C380]);
    while (func_001F8480((Sync_11DE18*)D_0027B4C8)) {
        if (D_eu_0025D6B8 == 0) {
            func_001E1F10((Cfg_11DE18*)D_002494E8);
        }
        func_001F6C20(0);
    }
    (void)func_001F8290((Sync_11DE18*)D_0027B4C8, 0x4D, 1, D_0025C360[D_0025C380],
                  0x1000 - D_0025C368[D_0025C380], D_0025C378[D_0025C380],
                  *D_0025C360[D_0025C380] * 4 + 8, 0, 0);
    s32 n = (D_0025C380 ^ 1) != 0;
    D_0025C380 = n;
    *D_0025C360[n] = 0;
    D_0025C368[n] = 0xFFC;
}
