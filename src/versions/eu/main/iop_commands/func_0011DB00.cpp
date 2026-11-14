// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the three debug messages are only printed while a global (US 0x25C3B8) is zero
extern s32 D_0025C3B8;

void QueueIopCommand(s32 cmd, s32 len, void* data, IopCallbackFn arg, u64 val)
{
    s32 flag = 0;
    s32 i;

    if (g_iopFlushDeferred == 0 && g_iopReplyBuffer == 0 && len == 0 && arg == 0) {
        ArmIopReplyBuffer((s32*)&g_iopCommandReply, 1);
        while (IsRemoteCallPending(&g_iopCommandRpc) != 0) {
            if (D_0025C3B8 == 0)
                PrintFormatted("989snd.c: RPC collision!\n");
            PollIopCommands();
            SyncDataCache(0);
        }
        CallRemoteService(&g_iopCommandRpc, cmd, 1, 0, 0, (&g_iopCommandReply), 12, 0, 0);
        return;
    }

    s32 size = len + 4;
    i = 0;
    if ((size & 3) != 0)
    {
        s32 t = len + 8;
        size = t - size % 4;
    }

    for (;; i++) {
        if (*g_iopCommandBuffers[g_iopBufferIndex] != 0x100 && g_iopCommandSpace[g_iopBufferIndex] >= size)
            break;
        if (g_iopFlushDeferred != 0) {
            g_iopFlushDeferred = 0;
            flag = 1;
        }
        PollIopCommands();
        if (i == 1 && D_0025C3B8 == 0)
            PrintFormatted("snd_SendIOPCommandNoWait: BUFFER %d FULL(%d)! Sound stalled waiting for IOP comands to finish!\n", g_iopBufferIndex, *g_iopCommandBuffers[g_iopBufferIndex]);
    }
    if (i != 0 && D_0025C3B8 == 0)
        PrintFormatted("snd_SendIOPCommandNoWait: continuing (%d).\n", i);
    if (flag != 0)
        g_iopFlushDeferred = 1;

    {
        s16* p = (s16*)(((u8*)g_iopCommandBuffers[g_iopBufferIndex]) - (g_iopCommandSpace[g_iopBufferIndex] - 0x1000));
        s32 j;
        *p = cmd;
        p++;
        *p = len;
        p++;
        for (j = 0; j < len; j++)
            ((u8*)p)[j] = ((u8*)data)[j];
    }
    {
        s32 k = g_iopBufferIndex;
        g_iopCommandSpace[k] -= size;
        *(IopCallbackFn*)(((u8**)g_iopCallbackTables)[k] + *g_iopCommandBuffers[k] * 16) = arg;
        *(u64*)(((u8**)g_iopCallbackTables)[k] + *g_iopCommandBuffers[k] * 16 + 8) = val;
    }
    CommitQueuedIopCommand();
}
