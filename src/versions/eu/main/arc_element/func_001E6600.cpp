// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's object has its position at 0x52C, its 69 points at 0x590 and its edges at 0x116C; the
// radius is 63.152542 and the screen's y maps by 0.5462963 and 1920.
struct ArcPoints_1E6600_eu {
    u8 pad0[0x52C];
    f32 x;                      // 0x52C
    f32 y;                      // 0x530
    u8 pad534[0x590 - 0x534];
    T217D_3F0_Pt pts[69];       // 0x590
    f32 edgeFrom;               // 0x116C
    f32 edgeTo;                 // 0x1170
};

void GetArcVisibleRange(ArcPoints_1E6600_eu* self, s32* first, s32* second);

void WriteArcPointVertices(ArcPoints_1E6600_eu* self, PacketWriter* buf)
{
    s32 first, last;
    GetArcVisibleRange(self, &first, &last);
    if (first == last) {
        return;
    }
    f32 x0 = self->x + self->edgeFrom;
    f32 y0 = self->y + 63.152542f;
    f32 xe = self->x + self->edgeTo;
    BeginGifTag(buf, 0x44, 5, 0x44441);
    for (s32 i = first; i < last; i++) {
        T217D_3F0_Pt* p = &self->pts[i];
        f32 xa = x0 + p->x * 63.152542f;
        f32 xb = x0 + p->nextX * 63.152542f;
        f32 ya = y0 + p->y * 63.152542f;
        f32 yb = y0 + p->nextY * 63.152542f;
        Rgba4 c;
        {
            Rgba4 a = *(Rgba4*)&p->colorB;
            Rgba4 b = *(Rgba4*)g_arcGreyColor;
            f32 t = p->level;
            Rgba4 m;
            m.r = ColorLerp::Of(a.r, b.r, t);
            m.g = ColorLerp::Of(a.g, b.g, t);
            m.b = ColorLerp::Of(a.b, b.b, t);
            m.a = ColorLerp::Of(a.a, b.a, t);
            c = m;
        }
        AddGifRgbaEntry(buf, *(u32*)&c);
        s32 sx = (s32)((xe + 1728.0f) * 16.0f);
        s32 sya = (s32)((ya * 0.5462963f + 1920.0f) * 16.0f);
        AddGifXyzfEntry(buf, sx, sya, 0, 0);
        AddGifXyzfEntry(buf, (s32)((xa + 1728.0f) * 16.0f), sya, 0, 0);
        s32 syb = (s32)((yb * 0.5462963f + 1920.0f) * 16.0f);
        AddGifXyzfEntry(buf, sx, syb, 0, 0);
        AddGifXyzfEntry(buf, (s32)((xb + 1728.0f) * 16.0f), syb, 0, 0);
    }
    BeginGifTag(buf, 0, 1, 1);
    AddGifRgbaEntry(buf, 0x80000000);
    BeginGifTag(buf, 0, 1, 4);
    for (s32 i = first; i < last; i++) {
        T217D_3F0_Pt* p = &self->pts[i];
        s32 n = (s32)(p->level * 3.999f) + 2;
        if (n != 0) {
            f32 xa = x0 + p->x * 63.152542f;
            f32 xb = x0 + p->nextX * 63.152542f;
            f32 lo = xb <? (xe < xa ? xe : xa);
            f32 hi = xb >? (xa < xe ? xe : xa);
            f32 ya = y0 + p->y * 63.152542f;
            f32 yb = y0 + p->nextY * 63.152542f;
            for (s32 j = 0; j < n; j++) {
                f32 x = RandomFloatInRange(lo, hi);
                f32 y = RandomFloatInRange(ya, yb);
                AddGifXyzfEntry(buf, (s32)((x + 1728.0f) * 16.0f), (s32)((y * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
            }
        }
    }
}
