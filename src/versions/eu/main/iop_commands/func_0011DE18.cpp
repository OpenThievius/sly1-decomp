// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the debug print is skipped when the PAL-only flag D_eu_0025D6B8 is set.
extern s32 D_eu_0025D6B8;

void func_0011DE18(void)
{
    ArmIopReplyBuffer(g_iopReplyTables[g_iopBufferIndex], *g_iopCommandBuffers[g_iopBufferIndex]);
    while (func_001F8480(&g_iopCommandRpc)) {
        if (D_eu_0025D6B8 == 0) {
            PrintFormatted(D_002494E8);
        }
        func_001F6C20(0);
    }
    (void)func_001F8290(&g_iopCommandRpc, 0x4D, 1, g_iopCommandBuffers[g_iopBufferIndex],
                  0x1000 - g_iopCommandSpace[g_iopBufferIndex], g_iopReplyTables[g_iopBufferIndex],
                  *g_iopCommandBuffers[g_iopBufferIndex] * 4 + 8, 0, 0);
    s32 n = (g_iopBufferIndex ^ 1) != 0;
    g_iopBufferIndex = n;
    *g_iopCommandBuffers[n] = 0;
    g_iopCommandSpace[n] = 0xFFC;
}
