// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's own definition: draws the four fading corner marks; the object's fields sit at other offsets.
struct Obj_eu_135228
{
    u8 pad0[0x570];
    s32 f570;
    u8 pad1[0x5BC - 0x574];
    s32 f5BC[4];
    f32 f5CC[4];
};

void DrawTextPanelBlocks(Obj_eu_135228* self, PacketWriter* q)
{
    if (self->f570 == 1)
    {
        if ((u32)MaskWorldBitsBySave() & 0x800)
        {
            DrawTextPanelMarkers((T217D_440*)self, q);
        }
        u32 mask;
        GetCurrentLevelBit(&mask);
        if ((u32)MaskWorldBitsBySave() & mask)
        {
            u8 c0[4];
            u8 c1[4];
            u8 c2[4];
            u8 out[4];
            *(u32*)c0 = 0xFF408080;
            *(u32*)c1 = 0xFF406060;
            *(u32*)c2 = 0xFF404040;
            f32 t = Cosine(g_gameClock[1] * D_00261260[0]) * 0.5f + 0.5f;
            for (u32 i = 0; i < 4; i++)
            {
                f32 r = ApproachValueWithRamp(self->f5CC[i], self->f5BC[i] ? 1.0f : 0.0f, g_gameClock[2], &D_00261260[2], 0);
                self->f5CC[i] = r;
                for (s32 j = 0; j < 4; j++)
                {
                    out[j] = (s32)((1.0f - r) * (f32)c2[j] + r * t * (f32)c1[j] + r * (1.0f - t) * (f32)c0[j]);
                }
                out[3] = (out[3] + 1) >> 1;
                BeginGifTag(q, 0x4D, 5, 0x44441);
                AddGifRgbaEntry(q, *(u32*)out);
                for (s32 k = 0; k < 4; k++)
                {
                    s32 xi = (s32)(((D_002611E0[i][k] + 320.0f) + 1728.0f) * 16.0f);
                    s32 yi = (s32)(((D_00261220[i][k] + 391.6101685f) * 0.5462963f + 1920.0f) * 16.0f);
                    AddGifXyzfEntry(q, xi, yi, 0, 0);
                }
            }
        }
    }
}
