// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: initialises the IOP command buffers and RPC channels; takes a flags word (bit 1 sets D_eu_0025D6B8) that is passed on to the IOP.
extern s32 D_eu_0025D6B8;

void InitIopCommandChannels(s32 flags)
{
    s32 n;
    s32 args[2];

    g_iopCommandBuffers[0] = (s32*)g_iopCommandBuffer0;
    g_iopCommandBuffers[1] = (s32*)g_iopCommandBuffer1;
    g_iopReplyTables[0] = g_iopReplyTable0;
    g_iopReplyTables[1] = g_iopReplyTable1;
    ((s32**)&g_iopCallbackTables)[0] = g_iopCallbackTable0;
    ((s32**)&g_iopCallbackTables)[1] = g_iopCallbackTable1;
    if (flags & 2) {
        D_eu_0025D6B8 = 1;
    } else {
        D_eu_0025D6B8 = 0;
    }
    InitRemoteCalls(0);
    do {
        ASSERT_0011CBB8(BindRemoteService(&g_iopCommandRpc, 0x123456, 0) >= 0, 0xAF);
        for (n = 10000; --n != -1;) {
        }
    } while (g_iopCommandRpc.server == 0);
    g_soundBankLoadBusy.busy = 0;
    g_soundBankLoadCallback.fn = 0;
    g_soundBankLoadCallback.arg = 0;
    g_iopChannel2Result.result = 0;
    do {
        ASSERT_0011CBB8(BindRemoteService(&g_iopBankLoadRpc, 0x123457, 0) >= 0, 0xC4);
        for (n = 10000; --n != -1;) {
        }
    } while (g_iopBankLoadRpc.server == 0);
    g_iopSharedPacket.busy = 0;
    g_iopCommandBuffer0[0] = 0;
    g_iopCommandBuffer1[0] = 0;
    g_iopCommandSpace[0] = 0xFFC;
    g_iopCommandSpace[1] = 0xFFC;
    g_iopSharedPacket.result = 0;
    args[0] = (s32)&g_iopSharedPacket;
    args[1] = flags;
    SendIopCommandAndWait(0, 8, args);
}
