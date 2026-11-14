// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL starts the counter at 0x1D and calls func_00193288 only while D_eu_0026321C is non-zero.
extern s32 D_eu_0026321C;
void RunStartupInitializers(void)
{
    ProgressFrame fr;
    u32 i;
    s32 idx;
    StartupFn* tbl;

    fr.w[12] = 0x7F0000;
    fr.w[16] = 0x3F3F3F;
    fr.w[20] = 0x3F3F;
    fr.w[24] = 0x3F;
    (void)InitLoadProgress((LoadProgress*)&fr, (U32P*)&fr.w[12], (U32P*)&fr.w[16], (U32P*)&fr.w[20], (U32P*)&fr.w[24]);
    idx = 0x1D;
    SetScreenOwner(1);
    BeginLoadProgress((LoadProgress*)&fr);
    tbl = (StartupFn*)g_startupInitializers;
    i = 0;
    do {
        if (D_eu_0026321C != 0) {
            UpdateLoadProgress((LoadProgress*)&fr, idx);
        }
        tbl[i]();
        i++;
        idx--;
    } while (i < 0x1D);
    UpdateLoadProgress((LoadProgress*)&fr, 0);
    EndLoadProgress((LoadProgress*)&fr);
    ClearScreenOwner(1);
}
