// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: func_00201A18 is called with 3 where US passes 2.

void ResetDisplayBuffers(void)
{
    g_displayFlipBusy = 1;
    SendDisplayResetPacket();
    SignalDisplaySync();
    g_displayFlipBusy = 0;
    ResetGs(0, 1, 3, 1);
    u32 flag = (*(u32*)0x12001000 >> 13) & 1;
    s32 cnt = g_displayFrameCounter;
    D_002626CC = 0;
    g_displayFieldCountdown = 0;
    g_displayFieldParity = flag;
    g_drawFieldParity = (flag == 0);
    u8* ptr;
    if (cnt & 1) {
        ptr = g_fieldOffsetPacket0;
    } else {
        ptr = g_fieldOffsetPacket1;
    }
    s16 half = *(s16*)&g_drawFieldParity;
    SetFieldDrawOffset((GsOffset*)ptr, 0x800, 0x800, half);
    SyncDataCache(0);
    g_displayFrameCounter = g_displayFrameCounter + 1;
    SwapDoubleBuffer(g_displayRegisters, g_displayFrameCounter);
}

