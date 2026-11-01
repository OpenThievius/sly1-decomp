// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: key is an unsigned 16-bit glyph, 576-line screen (468.6 limit, 0.5454 scale, 1920 offset)
Entry_15CD18* func_0015DAB8(Self_15CD18* self, u16 key);

f32 func_0015CD18(f32 x, f32 y, Self_15CD18* self, u16 key, u32 color, Stream_15CD18* s)
{
    Entry_15CD18* e = func_0015DAB8(self, key);
    if (e != 0) {
        s32 shift = (s32)((self->m60 >> 30) & 0xF);
        s32 s4 = 1 << shift;
        f32 h = (f32)self->m8 * self->f48;
        f32 w = (f32)e->a6 * self->f44;
        f32 px = x + w;
        f32 py = y + h;
        if (0.0f <= px && x <= 640.0f && 0.0f <= py && y <= 468.61017f) {
            u32 tag = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
            func_001617E8(s, tag, 0.0f);
            func_00161860(s, e->a2 << 4, (s4 - e->a4) << 4);
            func_001618C0(s, (s32)((x + 1728.0f) * 16.0f),
                          (s32)((y * 0.5462963f + 1920.0f) * 16.0f), self->m40, 0);
            func_00161860(s, (e->a2 + e->a6) << 4, (s4 - (e->a4 + self->m8)) << 4);
            func_001618C0(s, (s32)((px + 1728.0f) * 16.0f),
                          (s32)((py * 0.5462963f + 1920.0f) * 16.0f), self->m40, 0);
        }
        return (f32)(e->a6 + 1) * self->f44;
    }
    return (f32)self->m4 * self->f44;
}
