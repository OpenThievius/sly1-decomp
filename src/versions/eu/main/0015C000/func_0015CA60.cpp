// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the key is passed zero-extended to 16 bits
V24A2_Glyph* func_0015DAB8(V24A2* self, u16 key);
f32 func_0015CA60(V24A2* self, s32 key)
{
    V24A2_Glyph* e = FindFontGlyph(self, (u16)key);
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
