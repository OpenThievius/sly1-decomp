// SPDX-License-Identifier: AGPL-3.0-or-later
// Draws a two-point sprite/line packet: header, colour, then two scaled vertices.
void WriteColoredSpritePacket(f32 x0, f32 y0, f32 x1, f32 y1, s32 r, s32 g, s32 b, s32 a, PacketWriter* p)
{
    u32 col;
    BeginGifTag(p, a <= 0xFE ? 0x46 : 6, 5, 0x441EE);
    col = (((a + 1) & 0x1FE) << 23) | (b << 16) | (g << 8) | r;
    AddGifRegisterWrite(p, 0x47, 0x31001);
    AddGifRegisterWrite(p, 0x42, 0x44);
    AddGifRgbaEntry(p, col);
    AddGifXyzfEntry(p, (s32)((x0 + 1728.0f) * 16.0f), (s32)((y0 * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
    AddGifXyzfEntry(p, (s32)((x1 + 1728.0f) * 16.0f), (s32)((y1 * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
}
