// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: key is an unsigned 16-bit glyph, 576-line screen (468.6 limit, 0.5454 scale, 1920 offset)
V24A2_Glyph* func_0015DAB8(V24A2* self, u16 key);

f32 func_0015CD18(f32 x, f32 y, V24A2* self, u16 key, u32 color, V24A0* s)
{
    V24A2_Glyph* e = FindFontGlyph(self, key);
    if (e != 0) {
        s32 shift = (s32)((self->f60u >> 30) & 0xF);
        s32 s4 = 1 << shift;
        f32 h = (f32)self->height * self->sy;
        f32 w = (f32)e->w * self->sx;
        f32 px = x + w;
        f32 py = y + h;
        if (0.0f <= px && x <= 640.0f && 0.0f <= py && y <= 468.61017f) {
            u32 tag = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
            AddGifRegListFloat(s, tag, 0.0f);
            func_00161860(s, e->u << 4, (s4 - e->v) << 4);
            func_001618C0(s, (s32)((x + 1728.0f) * 16.0f),
                          (s32)((y * 0.5462963f + 1920.0f) * 16.0f), self->f40, 0);
            func_00161860(s, (e->u + e->w) << 4, (s4 - (e->v + self->height)) << 4);
            func_001618C0(s, (s32)((px + 1728.0f) * 16.0f),
                          (s32)((py * 0.5462963f + 1920.0f) * 16.0f), self->f40, 0);
        }
        return (f32)(e->w + 1) * self->sx;
    }
    return (f32)self->advance * self->sx;
}
