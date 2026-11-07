// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the key is passed zero-extended to 16 bits
FontGlyph* FindFontGlyph(Font* self, u16 key);
f32 GetFontCharWidth(Font* self, s32 key)
{
    FontGlyph* e = FindFontGlyph(self, (u16)key);
    f32 x;
    f32 y;
    if (e == 0) {
        x = self->sx;
        y = (f32)self->advance;
    } else {
        x = (f32)(e->w + 1);
        y = self->sx;
    }
    return x * y;
}
