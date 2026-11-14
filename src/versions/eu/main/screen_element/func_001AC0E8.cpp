
struct PacketWriter;
// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: draws a gauge box (dark frame, a bar fading from red to grey), then one glyph over it that shakes while the timer runs.

struct Rgba_eu_1ACEE0 { u8 c[4]; };
struct Rect_eu_1ACEE0 { f32 x; f32 y; f32 w; f32 h; s32 f10; s32 f14; s32 f18; s32 f1C; };
struct VEnt_eu_1ACEE0 { s16 delta; s16 index; void (*fn)(void* self, f32 x, f32 y, s32 a, s32 b, void* c); };
struct Text_eu_1ACEE0 { u8 pad[0x4C]; VEnt_eu_1ACEE0* vtbl; };
struct Self_eu_1ACEE0 {
    u8 pad0[4]; Text_eu_1ACEE0* text;
    u8 pad1[0x51C - 8]; f32 f51C;
    u8 pad2[0x52C - 0x520]; f32 f52C; f32 f530;
    u8 pad3[0x57C - 0x534]; u8 f57C;
    u8 pad4[0x584 - 0x57D]; f32 f584; f32 f588; f32 f58C; f32 f590; f32 f594; f32 f598; f32 f59C; f32 f5A0; f32 f5A4;
};
struct Q3_eu_1ACEE0;
struct Clock_eu_1ACEE0 { f32 f0; f32 f4; f32 f8; f32 fC; f32 f10; };
struct Col_eu_1ACEE0 { s32 v[4]; };

extern Q3_eu_1ACEE0 D_eu_0027DB10;

f32 ApproachValueWithRamp(Q3_eu_1ACEE0* p, s32 a1, f32 f12, f32 f13, f32 f14);
void SetTextLayoutVerticalPlacement(Rect_eu_1ACEE0* out, s32 flag);
void WriteColoredSpritePacket(f32 x0, f32 y0, f32 x1, f32 y1, s32 r, s32 g, s32 b, s32 a, PacketWriter* p);
void PushFontScale(Text_eu_1ACEE0* handle, f32 a, f32 b);
void DrawFontString(Font *self, const char *str, StringLayout *par, Vec4U *clip, PacketWriter *s);
void PopFontScale(Text_eu_1ACEE0* handle);
f32 Sine(f32 x);
extern "C" f32 Cosine(f32 x);

struct Lerp_eu_1ACEE0 {
    static u8 Of(s32 a, s32 b, f32 t)
    {
        if (a == b) return b;
        if (a < b) return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
        return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
    }
};

struct LerpRgba_eu_1ACEE0 {
    static void Do(Rgba_eu_1ACEE0* out, Rgba_eu_1ACEE0* a, Rgba_eu_1ACEE0* b, f32 t)
    {
        Rgba_eu_1ACEE0 r;
        r.c[0] = Lerp_eu_1ACEE0::Of(a->c[0], b->c[0], t);
        r.c[1] = Lerp_eu_1ACEE0::Of(a->c[1], b->c[1], t);
        r.c[2] = Lerp_eu_1ACEE0::Of(a->c[2], b->c[2], t);
        r.c[3] = Lerp_eu_1ACEE0::Of(a->c[3], b->c[3], t);
        *out = r;
    }
};

void DrawGauge(Self_eu_1ACEE0* self)
{
    Rect_eu_1ACEE0 out;
    f32 t = 0.0f;
    s32 flag = 0;
    if (self->f58C != t) {
        f32 d = ((Clock_eu_1ACEE0*)&g_gameClock)->f4 - self->f58C;
        if (d < 0.5f) t = 1.0f - (d + d);
        flag = d < 0.75f;
    }
    u32 grey = 0xFF808080;
    self->f584 = ApproachValueWithRamp(&D_eu_0027DB10, 0, self->f584, self->f588, ((Clock_eu_1ACEE0*)&g_gameClock)->f8);
    f32 y = self->f59C;
    f32 h = self->f584 * y;
    y -= h;
    f32 w = self->f598;
    ((Layout_137228*)&out)->Pos(self->f52C + self->f590, self->f530 + self->f594);
    ((Layout_137228*)&out)->Size(w, y);
    {
        Col_eu_1ACEE0 tmp;
        tmp.v[0] = grey;
        ((Layout_137228*)&out)->Color((s32*)&tmp);
    }
    ((Layout_137228*)&out)->SetF14(0);
    ((Layout_137228*)&out)->SetF18(0);
    SetTextLayoutVerticalPlacement(&out, 0);
    {
    Rgba_eu_1ACEE0 col;
    col.c[0] = 0x20; col.c[1] = 0x20; col.c[2] = 0x20; col.c[3] = 0xC0;
    WriteColoredSpritePacket(out.x, out.y, out.x + out.w, out.y + out.h, 0x20, 0x20, 0x20, 0xC0, (PacketWriter*)&g_gsPacketWriter);
    {
        out.x = self->f52C + self->f590;
        out.y = self->f530 + self->f594 + y;
        out.w = self->f598;
        out.h = h;
        Rgba_eu_1ACEE0 a, b;
        a.c[0] = 0x60; a.c[1] = 0; a.c[2] = 0; a.c[3] = 0xC0;
        b.c[0] = 0xC0; b.c[1] = 0xC0; b.c[2] = 0xC0; b.c[3] = 0xFF;
        LerpRgba_eu_1ACEE0::Do(&col, &a, &b, t);
    }
    WriteColoredSpritePacket(out.x, out.y, out.x + out.w, out.y + out.h, col.c[0], col.c[1], col.c[2], col.c[3], (PacketWriter*)&g_gsPacketWriter);
    }
    PushFontScale(self->text, self->f51C, self->f51C);
    VEnt_eu_1ACEE0* ve = &self->text->vtbl[8];
    ve->fn((u8*)self->text + ve->delta, self->f52C, self->f530, 0x7A, out.f10, (u8*)&g_gsPacketWriter);
    f32 dx = 0.0f;
    f32 dy = dx;
    if (flag) {
        dx = Sine(((Clock_eu_1ACEE0*)&g_gameClock)->f10 * 40.0f) * 8.0f;
        dy = Cosine(((Clock_eu_1ACEE0*)&g_gameClock)->f10 * 15.0f) * 4.0f;
    }
    out.x = self->f52C + self->f5A0 + dx;
    out.y = self->f530 + self->f5A4 + dy;
    out.w = 0.0f;
    out.h = 0.0f;
    out.f18 = 1;
    out.f1C = 1;
    char str[2] = { self->f57C + 0x72, 0 };
    DrawFontString((Font*)self->text, str, (StringLayout*)&out, 0, (PacketWriter*)&g_gsPacketWriter);
    PopFontScale(self->text);
}
