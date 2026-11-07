// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: each debug print is skipped when the PAL-only flag D_eu_0025D6B8 is set.
extern s32 D_eu_0025D6B8;

s32 func_0011D140(s32 a0, s32 a1)
{
    s32 v;
    s32 w;
    s32 v1;
    u32 m;

    D_0025C348 = 0;
    if (D_0025C388.busy != 0) {
        if (D_eu_0025D6B8 == 0) {
            PrintFormatted(D_00249570);
        }
        return 0;
    }
    v = SyncDiscRead(1);
    if (v == 1) {
        if (D_eu_0025D6B8 == 0) {
            PrintFormatted(D_002495A0);
        }
        return 0;
    }
    s32* p = &g_iopChannel2Result.result;
    m = 0xFFFFFFFFu;
    *p = (s32)m;
    g_iopChannel2Args[1] = a1;
    g_iopChannel2Args[0] = a0;
    while (func_001F8480(&g_iopBankLoadRpc)) {
        if (D_eu_0025D6B8 == 0) {
            PrintFormatted(D_002494E8);
        }
        PollIopCommands();
        func_001F6C20(0);
    }
    w = func_001F8290(&g_iopBankLoadRpc, 3, 1, g_iopChannel2Args, 8, &g_iopChannel2Result.result, 4, 0, 0);
    v1 = g_iopChannel2Result.result;
    if (w < 0) {
        if (D_eu_0025D6B8 == 0) {
            PrintFormatted(D_002495C0);
        }
        D_0025C348 = 0x106;
        return 0;
    }
    if ((u32)v1 == 0xFFFFFFFFu) {
        do {
            func_001F6C20(0);
        } while ((u32)g_iopChannel2Result.result == 0xFFFFFFFFu);
    }
    return g_iopChannel2Result.result;
}
