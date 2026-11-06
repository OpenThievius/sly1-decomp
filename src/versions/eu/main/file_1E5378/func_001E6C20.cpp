// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields 0x310 further on (0x920 for the tail), and PAL's screen scale and centre.
struct Elem_1E6C20 { f32 f0; f32 f4; f32 f8; f32 fC; u8 pad[0x2C - 0x10]; };
struct Self_eu_1E6C20 {
    u8 pad0[0x52C]; f32 f52C; f32 f530;
    u8 pad1[0x570 - 0x534]; s32 f570; f32 f574;
    u8 pad2[0x590 - 0x578]; Elem_1E6C20 elems[69];
    f32 f116C; f32 f1170; f32 f1174;
};

void func_001E6268(Self_eu_1E6C20* self, s32* first, s32* last);

#define SX_eu_1E6C20(x) ((s32)(((x) + 1728.0f) * 16.0f))
#define SY_eu_1E6C20(y) ((s32)(((y) * 0.5462963f + 1920.0f) * 16.0f))

void func_001E6C20(Self_eu_1E6C20* self, Buf_1E6C20* buf)
{
    Rgba4 c;
    f32 t;
    switch (self->f570) {
    case 0:
        t = Clamp_1E6C20::Of((g_elapsedTime - self->f574) * 5.0f, 0.0f, 1.0f);
        break;
    case 1:
        t = Clamp_1E6C20::Of(1.0f - (g_elapsedTime - self->f574) * 5.0f, 0.0f, 1.0f);
        break;
    }
    BeginGifTag(buf, 0, 1, 1);
    {
        Rgba4 a = D_002610D8;
        Rgba4 b = D_002610E0;
        Rgba4 r;
        r.r = Lerp_1E6C20::Of(a.r, b.r, t);
        r.g = Lerp_1E6C20::Of(a.g, b.g, t);
        r.b = Lerp_1E6C20::Of(a.b, b.b, t);
        r.a = Lerp_1E6C20::Of(a.a, b.a, t);
        c = r;
    }
    AddGifRgbaEntry(buf, *(u32*)&c);
    BeginGifTag(buf, 0x44, 1, 4);
    f32 x0 = self->f52C + self->f116C;
    f32 y0 = self->f530 + 63.152542f;
    f32 xe = self->f52C + self->f1170;
    s32 first, last;
    GetArcVisibleRange(self, &first, &last);
    Elem_1E6C20* e = &self->elems[first];
    f32 len = self->f1174;
    f32 xa = x0 + e->f0 * 63.152542f;
    f32 xb = x0 + (len + 63.152542f) * e->f0;
    f32 ya = y0 + e->f8 * 63.152542f;
    f32 yb = ya - len;
    AddGifXyzfEntry(buf, SX_eu_1E6C20(xe), SY_eu_1E6C20(ya), 0, 0);
    AddGifXyzfEntry(buf, SX_eu_1E6C20(xe), SY_eu_1E6C20(yb), 0, 0);
    AddGifXyzfEntry(buf, SX_eu_1E6C20(xa), SY_eu_1E6C20(ya), 0, 0);
    AddGifXyzfEntry(buf, SX_eu_1E6C20(xb), SY_eu_1E6C20(yb), 0, 0);
    for (s32 i = first; i < last; i++) {
        e = &self->elems[i];
        xa = x0 + e->f0 * 63.152542f;
        ya = y0 + e->f8 * 63.152542f;
        xb = x0 + (self->f1174 + 63.152542f) * e->f0;
        yb = y0 + (self->f1174 + 63.152542f) * e->f8;
        AddGifXyzfEntry(buf, SX_eu_1E6C20(xa), SY_eu_1E6C20(ya), 0, 0);
        AddGifXyzfEntry(buf, SX_eu_1E6C20(xb), SY_eu_1E6C20(yb), 0, 0);
    }
    xa = x0 + e->f4 * 63.152542f;
    ya = y0 + e->fC * 63.152542f;
    yb = ya + self->f1174;
    xb = x0 + (self->f1174 + 63.152542f) * e->f4;
    AddGifXyzfEntry(buf, SX_eu_1E6C20(xa), SY_eu_1E6C20(ya), 0, 0);
    AddGifXyzfEntry(buf, SX_eu_1E6C20(xb), SY_eu_1E6C20(yb), 0, 0);
    AddGifXyzfEntry(buf, SX_eu_1E6C20(xe), SY_eu_1E6C20(ya), 0, 0);
    AddGifXyzfEntry(buf, SX_eu_1E6C20(xe), SY_eu_1E6C20(yb), 0, 0);
}
