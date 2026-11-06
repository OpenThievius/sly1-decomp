// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL passes 2 to func_0011CBB8.
void func_0011CBB8(s32 a);
void func_001BF130(void)
{
    func_001F5C0C(g_soundBankHandles, 0, 0x1C);
    InitIopCommandChannels(2);
    EnsureSoundBankLoaded(0);
    EnableIopDiscAccess(1, 0x2000, 1, 1);
    func_0011D928(0x14);
    ResetVolumeChannelFactors();
    func_0011D520(0, 1);
    func_0011D558(0, 0, 0x2F);
    func_0011D558(1, 0x18, 0x2F);
    func_0011D558(3, 0x18, 0x2F);
    func_0011D558(2, 0x18, 0x2F);
    func_0011E3A0(2, 4);
}
