// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: draws a menu box with its title (laid out into the owner's line table), its items and a separator line.
// PAL's layout record is 0x20 bytes (its setters differ): its own type, not Layout_137228.
struct Out_eu_194F80 { u8 b[0x20]; };
struct Menu_eu_194F80 { s32 title; f32 titleScale; f32 itemScale; s32 vertical; s32 count; s32* items; };
struct Buf_eu_194F80 { u8 b[0xC0]; };
struct Lines_eu_194F80 { f32 f0; f32 f4; f32 height; };
struct Self_eu_194F80 {
    u8 pad0[4];
    Font* f4;
    u8 pad1[0x408 - 8];
    Lines_eu_194F80 lines;
    u8 pad1b[0x520 - 0x414];
    MenuBoxStyle* f210;
    u8 pad2[0x534 - 0x524];
    f32 f224;
    f32 f228;
    u8 pad3[0x544 - 0x53C];
    f32 f234;
    f32 f238;
    f32 f23C;
    u8 pad4[0x560 - 0x550];
    s32 f250;
    u8 pad5[0x570 - 0x564];
    s32 f260;
    s32 f264;
    u8 pad6[0x594 - 0x578];
    f32 f284;
};
void SetTextLayoutVerticalPlacement(Out_eu_194F80* out, s32 v);
Buf_eu_194F80* InitTextReaderFromTextTable(Buf_eu_194F80* out, s32 id, Font* font, s32 zero);
Buf_eu_194F80* InitWideTextReader(Buf_eu_194F80* out, void* str, Font* font, s32 zero);
// PAL hands the layout's word at 0x14 the lines it wraps where the US build passes flags: left as
// the free function it was on that word (a 64-bit hazard for a port), not a cast to the method's s32.
void SetTextLayoutHorizontalAlign(Out_eu_194F80* out, Lines_eu_194F80* lines);
void BreakTextIntoLines(Buf_eu_194F80* buf, Lines_eu_194F80* lines, f32 w);
void DrawWrappedAlignedText(Buf_eu_194F80* buf, Out_eu_194F80* out, s32 zero, void* data);
f32 SumTextWidth(Buf_eu_194F80* buf);
void* GetMenuChoiceLabel(s32 menu, s32 id);

struct Setup_eu_194F80 { static void Do(Out_eu_194F80* out, f32 x, f32 y, f32 w, f32 h, s32 color, Lines_eu_194F80* lines, s32 flag)
{
    ((Layout_137228*)out)->Pos(x, y);
    ((Layout_137228*)out)->Size(w, h);
    Rgba_137248 tmp;
    tmp.value = color;
    ((Layout_137228*)out)->Color((s32*)&tmp);
    SetTextLayoutHorizontalAlign(out, lines);
    ((Layout_137228*)out)->SetF18(flag);
    SetTextLayoutVerticalPlacement(out, 0);
} };

void DrawPauseMenu(Self_eu_194F80* self)
{
    f32 cx;
    f32 cy;
    f32 h;
    f32 w;
    f32 pulse;
    f32 fade;
    s32 alpha;
    Menu_eu_194F80* menu;
    f32 lineH;
    f32 base;
    f32 x;
    s32 i;
    s32 page;

    if (self->f250 == 0) {
        return;
    }
    {
        f32 ww = self->f234;
        f32 hh = self->f238;
        f32 s = self->f23C;
        f32 x0 = self->f224 + ww * 0.5f; 
        f32 y0 = self->f228 + hh * 0.5f; 
        w = ww * s; 
        cx = self->f224 * s + x0 * (1.0f - s); 
        cy = self->f228 * s + y0 * (1.0f - s); 
        h = hh * s; 
    }
    pulse = Sine(g_gameClock[4] * 10.0f) * 0.5f + 0.5f;
    page = self->f260;
    menu = &((Menu_eu_194F80*)&g_pauseMenuPages)[page];
    fade = 1.0f;
    if (page == 0 && D_00275BEC == 2) {
        fade = 1.0f - D_00262CEC;
    }
    self->f284 = ApproachValueWithRamp((RampProfile*)g_fadeRampProfile, 0, self->f284, fade, g_gameClock[5]);
    alpha = (u8)(s32)(self->f284 * 255.0f);
    if (self->f210 != 0) {
        Out_eu_194F80 out;
        s32 backColor = 0xFF808080;
        ((Layout_137228*)&out)->Pos(cx, cy);
        ((Layout_137228*)&out)->Size(w, h);
        {
            Rgba_137248 tmp;
            tmp.value = backColor;
            ((Layout_137228*)&out)->Color((s32*)&tmp);
        }
        ((Layout_137228*)&out)->SetF14(0);
        ((Layout_137228*)&out)->SetF18(0);
        SetTextLayoutVerticalPlacement(&out, 0);
        Rgba4 saved = self->f210->color;
        {
            Rgba4 t = saved;
            t.a = alpha;
            self->f210->color = t;
        }
        if (menu->count == 0) {
            MenuBoxStyle* cur = self->f210;
            Rgba4 gray;
            gray.r = 0x6F; 
            gray.g = 0x6F; 
            gray.b = 0x6F; 
            gray.a = alpha; 
            Rgba4 res;
            LerpColor::Do(&res, cur->color, gray, pulse * pulse);
            cur->color = res;
        }
        DrawBoxWithFont::Do(self->f210, (Layout_137228*)&out, g_gsPacketWriter);
        self->f210->color = saved;
    }
    if (menu->title != -1) {
        Buf_eu_194F80 buf;
        Out_eu_194F80 out;
        Rgba4 c;
        f32 sc = menu->titleScale * self->f23C;
        PushFontScale(self->f4, sc, sc);
        InitTextReaderFromTextTable(&buf, menu->title, self->f4, 0);
        BreakTextIntoLines(&buf, &self->lines, self->f23C * 500.0f);
        c.r = 0x7F;
        c.g = 0x7F;
        c.b = 0x7F;
        c.a = alpha;
        Setup_eu_194F80::Do(&out, cx, cy, w, h, *(s32*)&c, &self->lines, 1);
        DrawWrappedAlignedText(&buf, &out, 0, g_gsPacketWriter);
        cy += self->lines.height;
        PopFontScale(self->f4);
    }
    base = cy + -1.0f;
    {
        f32 sc = menu->itemScale * self->f23C;
        PushFontScale(self->f4, sc, sc);
    }
    lineH = (f32)self->f4->height * self->f4->sy;
    if (menu->vertical == 0) {
        f32 total = 0.0f;
        for (s32 k = 0; k < menu->count; k++) {
            Buf_eu_194F80 buf;
            if (k != 0) {
                total += (f32)self->f4->advance * self->f4->sx + (f32)self->f4->advance * self->f4->sx;
            }
            void* str = GetMenuChoiceLabel(page, menu->items[k]);
            InitWideTextReader(&buf, str, self->f4, 0);
            total += SumTextWidth(&buf);
        }
        x = cx + (w - total) * 0.5f;
    }
    for (i = 0; i < menu->count; i++) {
        Rgba4 col;
        f32 grow;
        f32 width;
        void* str;
        f32 th;
        if (i == self->f264) {
            Rgba4 c;
            c.r = 0x6F;
            c.g = 0x6F;
            c.b = (s32)(pulse * 64.0f) + 0x2F;
            c.a = alpha;
            col = c;
            grow = (1.0f - pulse) * 0.1f + 1.0f;
        } else {
            Rgba4 c;
            c.r = 0x5F;
            c.g = 0x5F;
            c.b = 0x5F;
            c.a = alpha;
            col = c;
            grow = 1.0f;
        }
        Buf_eu_194F80 buf;
        str = GetMenuChoiceLabel(page, menu->items[i]);
        InitWideTextReader(&buf, str, self->f4, 0);
        width = SumTextWidth(&buf);
        if (menu->vertical != 0) {
            x = cx + (w - width) * 0.5f;
        }
        {
            f32 sc = menu->itemScale * self->f23C * grow;
            PushFontScale(self->f4, sc, sc);
        }
        InitWideTextReader(&buf, str, self->f4, 0);
        f32 width2 = SumTextWidth(&buf);
        th = (f32)self->f4->height * self->f4->sy;
        Out_eu_194F80 out;
        Setup_eu_194F80::Do(&out, x + (width - width2) * 0.5f, cy + (lineH - th) * 0.5f, w, th, *(s32*)&col, 0, 0);
        DrawWrappedAlignedText(&buf, &out, 0, g_gsPacketWriter);
        PopFontScale(self->f4);
        if (menu->vertical != 0) {
            cy += (f32)self->f4->height * self->f4->sy;
        } else {
            x += width + ((f32)self->f4->advance * self->f4->sx + (f32)self->f4->advance * self->f4->sx);
        }
    }
    PopFontScale(self->f4);
    if (menu->title != -1 && menu->count != 0) {
        Rgba4 c = g_pauseMenuBoxStyle.color;
        c.a = alpha;
        s32 y = (s32)((base * 0.5462963f + 1920.0f) * 16.0f);
        DrawLineSegment((s32)((cx + 1728.0f) * 16.0f), y, 0, (s32)((cx + w + 1728.0f) * 16.0f), y, 0, &c, 0);
    }
}
