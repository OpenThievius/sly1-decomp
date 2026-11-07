// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL prints the RPC collision message only while a PAL-only flag is clear.
extern s32 D_eu_0025D6B8;

s32 SendIopCommandAndWait(s32 id, s32 size, void* data)
{
    s32 i;
    s32 r;
    for (i = 0; i < size; i++)
        g_iopCommandArgs[i] = ((u8*)data)[i];
    while ((s32)g_iopReplyBuffer) {
        PollIopCommands();
        SyncDataCache(0);
    }
    ArmIopReplyBuffer(&g_iopCommandReply, 1);
    while (IsRemoteCallPending(&g_iopCommandRpc)) {
        if (D_eu_0025D6B8 == 0)
            PrintFormatted(D_002494E8);
        PollIopCommands();
        SyncDataCache(0);
    }
    if (size)
        CallRemoteService(&g_iopCommandRpc, id, 1, g_iopCommandArgs, size, &g_iopCommandReply, 0xC, 0, 0);
    else
        CallRemoteService(&g_iopCommandRpc, id, 1, 0, 0, &g_iopCommandReply, 0xC, 0, 0);
    while (!IsIopReplyReady()) {
    }
    r = g_iopCommandReply.result;
    if (*g_iopCommandBuffers[g_iopBufferIndex] != 0 && g_iopFlushDeferred == 0)
        FlushIopCommandBuffer();
    return r;
}
