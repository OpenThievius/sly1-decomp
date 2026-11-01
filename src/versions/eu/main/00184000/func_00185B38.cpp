// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL starts the counter at 0x1D and calls func_00193288 only while D_eu_0026321C is non-zero.
extern s32 D_eu_0026321C;
void func_00185B38(void)
{
    Frame_185B38 fr;
    u32 i;
    s32 idx;
    Fn_185B38* tbl;

    fr.w[12] = 0x7F0000;
    fr.w[16] = 0x3F3F3F;
    fr.w[20] = 0x3F3F;
    fr.w[24] = 0x3F;
    (void)func_00193210(&fr, &fr.w[12], &fr.w[16], &fr.w[20], &fr.w[24]);
    idx = 0x1D;
    func_00191E70(1);
    func_00193270(&fr);
    tbl = (Fn_185B38*)D_002647C0;
    i = 0;
    do {
        if (D_eu_0026321C != 0) {
            func_00193288(&fr, idx);
        }
        tbl[i]();
        i++;
        idx--;
    } while (i < 0x1D);
    func_00193288(&fr, 0);
    func_00193300(&fr);
    func_00191EB0(1);
}
