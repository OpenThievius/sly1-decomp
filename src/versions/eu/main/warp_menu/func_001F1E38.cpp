// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's own definition: draws a ring of vertices around a centre, in PAL's screen scale.
void DrawColoredCircle(f32 cx, f32 cy, f32 radius, f32 angle, s32 n, s32* c1, s32* c2, s32 flags)
{
    FanPoint loc;
    s32 i;
    f32 step = 6.2831855f / (f32)n;
    BeginGifTag(&g_gsPacketWriter, 0, 1, 0xE);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x47, 0x31001);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x42, (flags & 1) ? 0x48 : 0x44);
    BeginGifTag(&g_gsPacketWriter, 0x4D, 2, 0x41);
    AddGifRgbaEntry(&g_gsPacketWriter, *c1);
    AddGifXyzfEntry(&g_gsPacketWriter, (u32)(s32)((cx + 1728.0f) * 16.0f),
                  (u32)(s32)((cy * 0.546296298f + 1920.0f) * 16.0f), 0, 0);
    loc.k = 0;
    for (i = 0; i < n + 1; i++) {
        ComputeSinCos(WrapAngle(angle), &loc.x, &loc.y);
        loc.x = loc.x * radius + cx;
        loc.y = loc.y * radius + cy;
        if ((i & 1) && (flags & 2)) {
            AddGifRgbaEntry(&g_gsPacketWriter, loc.k);
        } else {
            AddGifRgbaEntry(&g_gsPacketWriter, *c2);
        }
        angle += step;
        AddGifXyzfEntry(&g_gsPacketWriter, (u32)(s32)((loc.x + 1728.0f) * 16.0f),
                      (u32)(s32)((loc.y * 0.546296298f + 1920.0f) * 16.0f), 0, 0);
    }
}
