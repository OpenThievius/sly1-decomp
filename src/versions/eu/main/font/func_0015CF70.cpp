// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: key is an unsigned 16-bit glyph, 576-line screen (468.6 limit, 0.5463 scale, 1920 offset)
FontGlyph* FindFontGlyph(Font* self, u16 key);
extern s32 D_eu_00263564;
extern s32 D_eu_00263568;

void DrawFontGlyphTurned(Font* self, u16 key, u32 color, PacketWriter* s, f32 x, f32 y)
{
    FontGlyph* e = FindFontGlyph(self, key);
    if (e != 0) {
        s32 shift = (s32)((self->texWordU >> 30) & 0xF);
        s32 s4 = 1 << shift;
        f32 h = (f32)self->height * self->sy;
        f32 w = (f32)e->w * self->sx;
        f32 px = x + h;
        f32 py = y + w;
        if (0.0f <= px && x <= 640.0f && 0.0f <= py && y <= 468.61017f) {
            s32 u0 = (e->u << 4) + D_eu_00263564;
            s32 v0 = ((s4 - e->v) << 4) + D_eu_00263568;
            s32 u1 = ((e->u + e->w) << 4) + D_eu_00263564;
            s32 v1 = ((s4 - (e->v + self->height)) << 4) + D_eu_00263568;
            s32 ok = AddFontImagesToFrame(self, s);
            BeginGifTag(s, 6, 1, 0xE);
            if (ok != 0) {
                AddGifRegisterWrite(s, 0x3F, (u64)0);
            }
            u64 v = 0x31001;
            if (self->useTestWord != 0) {
                v = self->testWord;
            }
            AddGifRegisterWrite(s, 0x47, (u64)v);
            AddGifRegisterWrite(s, 0x42, (u64)0x44);
            AddGifRegisterWrite(s, 6, (u64)self->texWordU);
            AddGifRegisterWrite(s, 0x14, (u64)0x60);
            AddGifRegisterWrite(s, 8, (u64)5);
            AddGifRegisterWrite(s, 0, (u64)0x1D4);
            BeginGifRegListTag(s, 9, 0x434343431ULL);
            u32 tag = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
            AddGifRegListFloat(s, tag, 0.0f);
            AddGifUvRegListEntry(s, u0, v0);
            s32 sx = (s32)((x + 1728.0f) * 16.0f);
            s32 sy = (s32)((py * 0.5462963f + 1920.0f) * 16.0f);
            AddGifXyzfRegListEntry(s, sx, sy, self->drawZ, 0);
            AddGifUvRegListEntry(s, u1, v0);
            s32 sy2 = (s32)((y * 0.5462963f + 1920.0f) * 16.0f);
            AddGifXyzfRegListEntry(s, sx, sy2, self->drawZ, 0);
            AddGifUvRegListEntry(s, u0, v1);
            s32 sx2 = (s32)((px + 1728.0f) * 16.0f);
            AddGifXyzfRegListEntry(s, sx2, sy, self->drawZ, 0);
            AddGifUvRegListEntry(s, u1, v1);
            AddGifXyzfRegListEntry(s, sx2, sy2, self->drawZ, 0);
            self->vt->end((Font*)((u8*)self + self->vt->adj7), 0, &g_gsPacketWriter);
        }
    }
}
