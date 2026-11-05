// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: draws a menu box with its title (laid out into the owner's line table), its items and a separator line.
// PAL's layout record is 0x20 bytes (its setters differ): its own type, not Layout_137228.
struct Out_eu_194F80 { u8 b[0x20]; };
struct Menu_eu_194F80 { s32 title; f32 titleScale; f32 itemScale; s32 vertical; s32 count; s32* items; };
struct Buf_eu_194F80 { u8 b[0xC0]; };
struct Lines_eu_194F80 { f32 f0; f32 f4; f32 height; };
struct Self_eu_194F80 {
    u8 pad0[4];
    V24A2* f4;
    u8 pad1[0x408 - 8];
    Lines_eu_194F80 lines;
    u8 pad1b[0x520 - 0x414];
    Owner_194F80* f210;
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
void func_00137228(Out_eu_194F80* out, f32 x, f32 y);
void func_00137238(Out_eu_194F80* out, f32 x, f32 y);
void func_00137248(Out_eu_194F80* out, Rgba_137248* value);
void func_00137268(Out_eu_194F80* out, s32 flag);
void func_eu_001374E0(Out_eu_194F80* out, s32 v);
void func_00137260(Out_eu_194F80* out, Lines_eu_194F80* lines);
Buf_eu_194F80* func_eu_0015DD18(Buf_eu_194F80* out, s32 id, V24A2* font, s32 zero);
Buf_eu_194F80* func_eu_0015DCB8(Buf_eu_194F80* out, void* str, V24A2* font, s32 zero);
void func_eu_0015E4A8(Buf_eu_194F80* buf, Lines_eu_194F80* lines, f32 w);
void func_eu_0015E7E0(Buf_eu_194F80* buf, Out_eu_194F80* out, s32 zero, void* data);
f32 func_eu_0015E438(Buf_eu_194F80* buf);
void* func_00193598(s32 menu, s32 id);

struct Setup_eu_194F80 { static void Do(Out_eu_194F80* out, f32 x, f32 y, f32 w, f32 h, s32 color, Lines_eu_194F80* lines, s32 flag)
{
    func_00137228(out, x, y);
    func_00137238(out, w, h);
    Rgba_137248 tmp;
    tmp.value = color;
    func_00137248(out, &tmp);
    func_00137260(out, lines);
    func_00137268(out, flag);
    func_eu_001374E0(out, 0);
} };

void func_00194F80(Self_eu_194F80* self)
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
    pulse = func_00205400(D_00261858[4] * 10.0f) * 0.5f + 0.5f;
    page = self->f260;
    menu = &((Menu_eu_194F80*)&D_00269D50)[page];
    fade = 1.0f;
    if (page == 0 && D_00275BEC == 2) {
        fade = 1.0f - D_00262CEC;
    }
    self->f284 = func_001EA4B8(D_00260ED0, 0, self->f284, fade, D_00261858[5]);
    alpha = (u8)(s32)(self->f284 * 255.0f);
    if (self->f210 != 0) {
        Out_eu_194F80 out;
        s32 backColor = 0xFF808080;
        func_00137228(&out, cx, cy);
        func_00137238(&out, w, h);
        {
            Rgba_137248 tmp;
            tmp.value = backColor;
            func_00137248(&out, &tmp);
        }
        func_00137260(&out, 0);
        func_00137268(&out, 0);
        func_eu_001374E0(&out, 0);
        Rgba_194F80 saved = self->f210->f18;
        {
            Rgba_194F80 t = saved;
            t.a = alpha;
            self->f210->f18 = t;
        }
        if (menu->count == 0) {
            Owner_194F80* cur = self->f210;
            Rgba_194F80 gray;
            gray.r = 0x6F; 
            gray.g = 0x6F; 
            gray.b = 0x6F; 
            gray.a = alpha; 
            Rgba_194F80 res;
            Lerp_194F80::Do(&res, cur->f18, gray, pulse * pulse);
            cur->f18 = res;
        }
        CallHook_194F80::Do(self->f210, (Layout_137228*)&out, D_00262280);
        self->f210->f18 = saved;
    }
    if (menu->title != -1) {
        Buf_eu_194F80 buf;
        Out_eu_194F80 out;
        Rgba_194F80 c;
        f32 sc = menu->titleScale * self->f23C;
        func_0015C8B8(self->f4, sc, sc);
        func_eu_0015DD18(&buf, menu->title, self->f4, 0);
        func_eu_0015E4A8(&buf, &self->lines, self->f23C * 500.0f);
        c.r = 0x7F;
        c.g = 0x7F;
        c.b = 0x7F;
        c.a = alpha;
        Setup_eu_194F80::Do(&out, cx, cy, w, h, *(s32*)&c, &self->lines, 1);
        func_eu_0015E7E0(&buf, &out, 0, D_00262280);
        cy += self->lines.height;
        func_0015C900(self->f4);
    }
    base = cy + -1.0f;
    {
        f32 sc = menu->itemScale * self->f23C;
        func_0015C8B8(self->f4, sc, sc);
    }
    lineH = (f32)self->f4->height * self->f4->sy;
    if (menu->vertical == 0) {
        f32 total = 0.0f;
        for (s32 k = 0; k < menu->count; k++) {
            Buf_eu_194F80 buf;
            if (k != 0) {
                total += (f32)self->f4->advance * self->f4->sx + (f32)self->f4->advance * self->f4->sx;
            }
            void* str = func_00193598(page, menu->items[k]);
            func_eu_0015DCB8(&buf, str, self->f4, 0);
            total += func_eu_0015E438(&buf);
        }
        x = cx + (w - total) * 0.5f;
    }
    for (i = 0; i < menu->count; i++) {
        Rgba_194F80 col;
        f32 grow;
        f32 width;
        void* str;
        f32 th;
        if (i == self->f264) {
            Rgba_194F80 c;
            c.r = 0x6F;
            c.g = 0x6F;
            c.b = (s32)(pulse * 64.0f) + 0x2F;
            c.a = alpha;
            col = c;
            grow = (1.0f - pulse) * 0.1f + 1.0f;
        } else {
            Rgba_194F80 c;
            c.r = 0x5F;
            c.g = 0x5F;
            c.b = 0x5F;
            c.a = alpha;
            col = c;
            grow = 1.0f;
        }
        Buf_eu_194F80 buf;
        str = func_00193598(page, menu->items[i]);
        func_eu_0015DCB8(&buf, str, self->f4, 0);
        width = func_eu_0015E438(&buf);
        if (menu->vertical != 0) {
            x = cx + (w - width) * 0.5f;
        }
        {
            f32 sc = menu->itemScale * self->f23C * grow;
            func_0015C8B8(self->f4, sc, sc);
        }
        func_eu_0015DCB8(&buf, str, self->f4, 0);
        f32 width2 = func_eu_0015E438(&buf);
        th = (f32)self->f4->height * self->f4->sy;
        Out_eu_194F80 out;
        Setup_eu_194F80::Do(&out, x + (width - width2) * 0.5f, cy + (lineH - th) * 0.5f, w, th, *(s32*)&col, 0, 0);
        func_eu_0015E7E0(&buf, &out, 0, D_00262280);
        func_0015C900(self->f4);
        if (menu->vertical != 0) {
            cy += (f32)self->f4->height * self->f4->sy;
        } else {
            x += width + ((f32)self->f4->advance * self->f4->sx + (f32)self->f4->advance * self->f4->sx);
        }
    }
    func_0015C900(self->f4);
    if (menu->title != -1 && menu->count != 0) {
        Rgba_194F80 c = *(Rgba_194F80*)&D_0026A210.f18;
        c.a = alpha;
        s32 y = (s32)((base * 0.5462963f + 1920.0f) * 16.0f);
        func_001AE3B8((s32)((cx + 1728.0f) * 16.0f), y, 0, (s32)((cx + w + 1728.0f) * 16.0f), y, 0, &c, 0);
    }
}
