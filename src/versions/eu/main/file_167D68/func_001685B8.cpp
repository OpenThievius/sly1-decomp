// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: func_00201A18 is called with 3 where US passes 2.

void ResetDisplayBuffers(void)
{
    D_002BE470 = 1;
    SendDisplayResetPacket();
    SignalDisplaySync();
    D_002BE470 = 0;
    ResetGs(0, 1, 3, 1);
    u32 flag = (*(u32*)0x12001000 >> 13) & 1;
    s32 cnt = g_displayFrameCounter;
    D_002626CC = 0;
    D_00262484 = 0;
    D_002626C8 = flag;
    D_002626C4 = (flag == 0);
    u8* ptr;
    if (cnt & 1) {
        ptr = D_002624F0;
    } else {
        ptr = D_002625E0;
    }
    s16 half = *(s16*)&D_002626C4;
    SetFieldDrawOffset(ptr, 0x800, 0x800, half);
    SyncDataCache(0);
    g_displayFrameCounter = g_displayFrameCounter + 1;
    SwapDoubleBuffer(D_00262490, g_displayFrameCounter);
}

