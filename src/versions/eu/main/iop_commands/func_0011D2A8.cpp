// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: each debug print is skipped when the PAL-only flag D_eu_0025D6B8 is set.
extern s32 D_eu_0025D6B8;

void func_0011D2A8(void* a0, s32 a1, s32 a2, s64 a3)
{
    D_0025C348 = 0;
    if (D_0025C388.busy != 0) {
        if (D_eu_0025D6B8 == 0) {
            PrintFormatted(D_00249570);
        }
        return;
    }
    if (SyncDiscRead(1) == 1) {
        if (D_eu_0025D6B8 == 0) {
            PrintFormatted(D_002495A0);
        }
        return;
    }
    (*(u32*)&g_iopChannel2Result.result) = 0xFFFFFFFF;
    (*(WordPairArgs*)&g_iopChannel2Args).a = (s32)a0;
    (*(WordPairArgs*)&g_iopChannel2Args).b = a1;
    D_0025C390.fn = a2;
    D_0025C390.arg = a3;
    while (func_001F8480(&g_iopBankLoadRpc)) {
        if (D_eu_0025D6B8 == 0) {
            PrintFormatted(D_002494E8);
        }
        PollIopCommands();
        func_001F6C20(0);
    }
    D_0025C388.busy = 1;
    func_001F8290(&g_iopBankLoadRpc, 3, 1, ((WordPairArgs*)&g_iopChannel2Args), 8, ((u32*)&g_iopChannel2Result.result), 4, 0, 0);
}
