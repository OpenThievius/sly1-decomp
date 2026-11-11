// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL passes 2 to func_0011CBB8.
void InitIopCommandChannels(s32 a);
void InitSoundSystem(void)
{
    FillMemory(g_soundBankHandles, 0, 0x1C);
    InitIopCommandChannels(2);
    EnsureSoundBankLoaded(0);
    EnableIopDiscAccess(1, 0x2000, 1, 1);
    SendIopSoundLevel(0x14);
    ResetVolumeChannelFactors();
    QueueIopCommandD(0, 1);
    QueueIopChannelConfig(0, 0, 0x2F);
    QueueIopChannelConfig(1, 0x18, 0x2F);
    QueueIopChannelConfig(3, 0x18, 0x2F);
    QueueIopChannelConfig(2, 0x18, 0x2F);
    QueueIopCommand51(2, 4);
}
