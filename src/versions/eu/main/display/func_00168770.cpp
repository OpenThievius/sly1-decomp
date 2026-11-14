// SPDX-License-Identifier: AGPL-3.0-or-later
// Clears the screen with a colour: a GS packet of sprite-block fills; PAL uses other VRAM bases.
void FillScreenColor(u8* buffer, Rgba4* color, s32 flag)
{
    PacketWriter f;
    s32 x;

    InitGifPacket(&f);
    UsePacketBufferMemory(&f, 0x2C, buffer);
    BeginGifTag(&f, (s8)color->a >= 0 ? 0x46 : 6, 1, 0xE);
    AddGifRegisterWrite(&f, 1, (u64)color->r | ((u64)color->g << 8) | ((u64)color->b << 16) | ((u64)color->a << 24));
    AddGifRegisterWrite(&f, 0x47, flag != 0 ? 0x32001 : 0x32000);
    for (x = 0; x < 0x280; x += 0x20) {
        AddGifRegisterWrite(&f, 5, (u64)((0x6C0 + x) << 4) | ((u64)(0x780 << 4) << 16));
        AddGifRegisterWrite(&f, 5, (u64)((0x6E0 + x) << 4) | ((u64)(0x880 << 4) << 16));
    }
    AddGifRegisterWrite(&f, 0x47, 0x70000);
    EndGifPacket(&f);
}
