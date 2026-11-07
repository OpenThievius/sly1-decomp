// SPDX-License-Identifier: AGPL-3.0-or-later
// Draws a pulsing centred text label (scale follows a sine of the clock) at an offset from the owner's position.
struct Font_eu_1AE500 { u8 pad0[8]; s32 units; u8 pad1[0x3C]; f32 scale; };
struct Obj_eu_1AE500 { u8 pad0[0x52C]; f32 f52C; f32 f530; u8 pad1[0x544 - 0x534]; f32 f544; f32 f548; };
extern f32 D_eu_00262B68;
extern char D_eu_0024E350[];
extern u8 D_eu_00263590[];
void func_eu_001AB558(void* self);
f32 WrapAngle(f32 x);
f32 Cosine(f32 x);
f32 func_eu_0015C6F0(void* font, char* text);
void func_eu_001374E0(void* out, s32 v);
void func_eu_0015C778(void* font, char* text, void* out, s32 zero, void* d);

void func_eu_001AE500(Obj_eu_1AE500* self)
{
    u8 out[0x20];
    s32 tmp[4];
    Font_eu_1AE500* font;
    f32 s;
    f32 w;
    f32 h;
    s32 color = (s32)0xFF808080;
    func_eu_001AB558(self);
    f32 half = 0.5f;
    f32 s1 = Cosine(WrapAngle(D_eu_00262B68 * 8.0f)) * half + half;
    font = (Font_eu_1AE500*)GetFontById(1);
    s = s1 * 0.1f + 0.5f;
    PushFontScale((Font*)font, s, s);
    w = func_eu_0015C6F0(font, D_eu_0024E350);
    h = (f32)font->units * font->scale;
    SetTextLayoutPosition(out, ((self->f52C + 2.0f) + self->f544 * half) - w * half,
                  ((self->f530 + 14.0f) + self->f548 * half) - h * half);
    SetTextLayoutSize(out, w, h);
    tmp[0] = color;
    SetTextLayoutColor(out, tmp);
    SetTextLayoutHorizontalAlign(out, 0);
    SetTextLayoutVerticalAlign(out, 0);
    func_eu_001374E0(out, 0);
    func_eu_0015C778(font, D_eu_0024E350, out, 0, D_eu_00263590);
    PopFontScale((Font*)font);
}
