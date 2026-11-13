// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's own definition: draws a rectangle outline, or the visible rows of a list, with PAL's object layout.
void GetArcVisibleRange(void* self, s32* first, s32* second);
struct Elem_1E62A8 { f32 f0; f32 f4; f32 f8; f32 fC; u8 pad10[0x1C]; };
struct Self_1E62A8_eu {
    u8 pad0[0x52C];
    f32 f52C; f32 f530; f32 f534; f32 f538;
    u8 pad53C[8];
    f32 f544; f32 f548;
    u8 pad54C[0x44];
    Elem_1E62A8 e[0x39];
    u8 padFBC[0x210];
    f32 f116C; f32 f1170;
};

void WriteArcOutlineVertices(Self_1E62A8_eu* self, PacketWriter* c, s32 k)
{
    if (D_00270458 == 4) {
        f32 y = self->f538;
        f32 x = self->f534;
        s32 x0 = (s32)((x + 1728.0f) * 16.0f);
        s32 y0 = (s32)((y * 0.5462963f + 1920.0f) * 16.0f);
        AddGifXyzfNoDrawEntry(c, x0, y0, k, 0);
        AddGifXyzfNoDrawEntry(c, x0, (s32)(((y + self->f548) * 0.5462963f + 1920.0f) * 16.0f), k, 0);
        AddGifXyzfEntry(c, (s32)(((x + self->f544) + 1728.0f) * 16.0f), y0, k, 0);
        y = y + self->f548;
        x = x + self->f544;
        AddGifXyzfEntry(c, (s32)((x + 1728.0f) * 16.0f), (s32)((y * 0.5462963f + 1920.0f) * 16.0f), k, 0);
    } else {
        s32 r[2];
        GetArcVisibleRange(self, &r[0], &r[1]);
        if (r[0] != r[1]) {
            f32 a = self->f530 + 63.152542f;
            f32 b = self->f52C + self->f1170;
            f32 bx = self->f52C + self->f116C;
            s32 x0, y0, i;
            f32 t;
            y0 = (s32)(((a + self->e[r[0]].f8 * 63.152542f) * 0.5462963f + 1920.0f) * 16.0f);
            x0 = (s32)((b + 1728.0f) * 16.0f);
            t = bx + self->e[r[0]].f0 * 63.152542f;
            AddGifXyzfNoDrawEntry(c, x0, y0, k, 0);
            AddGifXyzfNoDrawEntry(c, (s32)((t + 1728.0f) * 16.0f), y0, k, 0);
            for (i = r[0]; i < r[1]; i++) {
                Elem_1E62A8* p = &self->e[i];
                t = bx + p->f4 * 63.152542f;
                s32 x = (s32)((b + 1728.0f) * 16.0f);
                y0 = (s32)(((a + p->fC * 63.152542f) * 0.5462963f + 1920.0f) * 16.0f);
                AddGifXyzfEntry(c, x, y0, k, 0);
                AddGifXyzfEntry(c, (s32)((t + 1728.0f) * 16.0f), y0, k, 0);
            }
        }
    }
}
