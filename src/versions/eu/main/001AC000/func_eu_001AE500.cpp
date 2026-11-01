// SPDX-License-Identifier: AGPL-3.0-or-later
// Draws a pulsing centred text label (scale follows a sine of the clock) at an offset from the owner's position.
struct Font_eu_1AE500 { u8 pad0[8]; s32 units; u8 pad1[0x3C]; f32 scale; };
struct Obj_eu_1AE500 { u8 pad0[0x52C]; f32 f52C; f32 f530; u8 pad1[0x544 - 0x534]; f32 f544; f32 f548; };
extern f32 D_eu_00262B68;
extern char D_eu_0024E350[];
extern u8 D_eu_00263590[];
void func_eu_001AB558(void* self);
f32 func_001EA408(f32 x);
f32 func_00205210(f32 x);
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
    f32 s1 = func_00205210(func_001EA408(D_eu_00262B68 * 8.0f)) * half + half;
    font = (Font_eu_1AE500*)func_0015C1C0(1);
    s = s1 * 0.1f + 0.5f;
    func_0015C8B8(font, s, s);
    w = func_eu_0015C6F0(font, D_eu_0024E350);
    h = (f32)font->units * font->scale;
    func_00137228(out, ((self->f52C + 2.0f) + self->f544 * half) - w * half,
                  ((self->f530 + 14.0f) + self->f548 * half) - h * half);
    func_00137238(out, w, h);
    tmp[0] = color;
    func_00137248(out, tmp);
    func_00137260(out, 0);
    func_00137268(out, 0);
    func_eu_001374E0(out, 0);
    func_eu_0015C778(font, D_eu_0024E350, out, 0, D_eu_00263590);
    func_0015C900(font);
}
