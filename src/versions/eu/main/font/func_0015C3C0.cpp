// SPDX-License-Identifier: AGPL-3.0-or-later
// When flagged, adds a GIF tag (0, 1, 0xE) and a register write of 0x40 to the packet.
void ResetFontClipRect(void* unused, s32 flag, void* p)
{
    if (flag != 0) {
        BeginGifTag(p, 0, 1, 0xE);
        AddGifRegisterWrite(p, 0x40, 0x00FF0000027F0000);
    }
}
