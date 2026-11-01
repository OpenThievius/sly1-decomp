// SPDX-License-Identifier: AGPL-3.0-or-later
// When flagged, adds a GIF tag (0, 1, 0xE) and a register write of 0x40 to the packet.
void func_eu_0015C698(void* unused, s32 flag, void* p)
{
    if (flag != 0) {
        func_001613C0(p, 0, 1, 0xE);
        func_00161708(p, 0x40, 0x00FF0000027F0000);
    }
}
