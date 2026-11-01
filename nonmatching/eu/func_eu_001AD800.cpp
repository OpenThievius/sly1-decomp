// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 760/780, checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001AD800.cpp func_eu_001AD800 --unit src/main/001A8000.cpp
// Still differs: Per-character fade-in text draw; now matches through the first division (lenF as (f32)n twice) but the clamp shape (retail: f0 result then mov f1,f0) and float/saved register allocation still differ (145 lines).
// Draws a string character by character with a per-character fade: positions interpolate between two corners by the fade phase.
struct Vt_eu_1AD800 {
    u8 pad0[0x18];
    s16 o18; u8 padA[2]; f32 (*width)(void* at, s32 ch);
    s16 o20; u8 padB[2]; void (*begin)(void* at, s32 a, void* d);
    u8 pad1[0x30 - 0x28];
    s16 o30; u8 padC[2]; f32 (*draw)(void* at, f32 x, f32 y, s32 ch, s32 arg, void* d);
    s16 o38; u8 padD[2]; void (*end)(void* at, s32 a, void* d);
};
struct Font_eu_1AD800 { u8 pad0[0x4C]; Vt_eu_1AD800* vt; };
struct Local_eu_1AD800 { f32 x; f32 y; u8 pad0[8]; PackedWord_001AB710 w10; u8 pad1[0xC]; };
struct Label_eu_1AD800 {
    u8 pad0[4]; Font_eu_1AD800* font; u16 text[1];
    u8 pad1[0x518 - 0xA]; s32 f518; u8 pad2[4]; void* f520;
    u8 pad3[0x530 - 0x524]; f32 f530; f32 f534; f32 f538; f32 f53C;
    u8 pad4[0x544 - 0x540]; f32 f544; f32 f548; f32 f54C;
    u8 pad6[0x560 - 0x550]; s32 state;
};
extern u8 D_eu_00263590[];
void func_eu_001AB558(void* self);
s32 func_eu_001E3018(u16* text);
void func_eu_001374E0(void* out, s32 v);

static inline f32 clamp_eu_1AD800(f32 v, f32 lo, f32 hi)
{
    f32 r;
    if (v < lo) {
        r = lo;
    } else if (hi < v) {
        r = hi;
    } else {
        r = v;
    }
    return r;
}

void func_eu_001AD800(Label_eu_1AD800* self)
{
    Local_eu_1AD800 L;
    s32 n;
    u16* text;
    f32 x0;
    f32 x1;
    f32 c;
    switch (self->state) {
    case 2:
        func_eu_001AB558(self);
        return;
    case 1:
    case 3:
        break;
    default:
        return;
    }
    n = func_eu_001E3018(text = self->text);
    if (n == 0) {
        return;
    }
    x0 = self->f534;
    x1 = self->f53C;
    c = clamp_eu_1AD800(self->f54C / (1.0f / (f32)n), 0.0f, 1.0f);
    if (self->f520 != 0) {
        f32 y = self->f530;
        f32 px = x0 * c + x1 * (1.0f - c);
        f32 qx = (x0 * self->f54C + x1 * (1.0f - self->f54C)) + self->f544;
        f32 qy = self->f548;
        s32 color = (s32)0xFF808080;
        func_00137228(&L, px, y);
        func_00137238(&L, qx, qy);
        {
            s32 tag = color;
            func_00137248(&L, &tag);
        }
        func_00137260(&L, 0);
        func_00137268(&L, 0);
        func_eu_001374E0(&L, 0);
        SubObj_001AB710* sub = *(SubObj_001AB710**)self->f520;
        if (sub != 0) {
            VDesc_001AB710* d = sub->desc4C;
            d->fn4C((u8*)sub + d->off48, self->f520, &L, D_eu_00263590);
        }
    }
    {
        Vt_eu_1AD800* vt = self->font->vt;
        vt->begin((u8*)self->font + vt->o20, 0, D_eu_00263590);
    }
    for (s32 i = 0; i < n; i++) {
        s32 next = i + 1;
        u16 ch = text[i];
        f32 k = clamp_eu_1AD800(self->f54C / ((f32)next / (f32)n), 0.0f, 1.0f);
        Vt_eu_1AD800* vt = self->font->vt;
        vt->draw((u8*)self->font + vt->o30, k * x0 + (1.0f - k) * x1, self->f538, ch, self->f518, D_eu_00263590);
        vt = self->font->vt;
        f32 w = vt->width((u8*)self->font + vt->o18, ch);
        x1 += w;
        x0 += w;
    }
    {
        Vt_eu_1AD800* vt = self->font->vt;
        vt->end((u8*)self->font + vt->o38, 0, D_eu_00263590);
    }
}
