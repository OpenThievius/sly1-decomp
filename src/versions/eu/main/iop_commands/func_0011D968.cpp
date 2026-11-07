// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL prints the RPC collision message only while a PAL-only flag is clear.
extern s32 D_eu_0025D6B8;

s32 func_0011D968(s32 id, s32 size, void* data)
{
    s32 i;
    s32 r;
    for (i = 0; i < size; i++)
        g_iopCommandArgs[i] = ((u8*)data)[i];
    while ((s32)g_iopReplyBuffer) {
        PollIopCommands();
        func_001F6C20(0);
    }
    ArmIopReplyBuffer(&D_0025C3C0, 1);
    while (func_001F8480(&g_iopCommandRpc)) {
        if (D_eu_0025D6B8 == 0)
            PrintFormatted(D_002494E8);
        PollIopCommands();
        func_001F6C20(0);
    }
    if (size)
        func_001F8290(&g_iopCommandRpc, id, 1, g_iopCommandArgs, size, &D_0025C3C0, 0xC, 0, 0);
    else
        func_001F8290(&g_iopCommandRpc, id, 1, 0, 0, &D_0025C3C0, 0xC, 0, 0);
    while (!IsIopReplyReady()) {
    }
    r = D_0025C3C0.result;
    if (*g_iopCommandBuffers[g_iopBufferIndex] != 0 && D_0025C384 == 0)
        FlushIopCommandBuffer();
    return r;
}
