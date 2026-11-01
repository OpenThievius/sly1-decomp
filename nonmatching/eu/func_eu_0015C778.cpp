// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_0015C778.cpp func_eu_0015C778 --unit src/main/0015C000.cpp
// Still differs: Draws a multi-line string aligned in a box; 3 lines differ: the load of halign before the ==2 compare uses v1/v0 swapped versus retail.
// Draws a multi-line string aligned inside a box, glyph by glyph through the font's virtual calls.
struct Vt_eu_15C778 {
    u8 pad0[0x20];
    s16 o20; u8 padA[2]; void (*f24)(void* at, s32 a, s32 b);
    u8 pad1[0x30 - 0x28];
    s16 o30; u8 padB[2]; f32 (*f34)(void* at, f32 x, f32 y, s32 ch, s32 style, s32 arg);
    s16 o38; u8 padC[2]; void (*f3C)(void* at, s32 a, s32 b);
};
struct VtW_eu_15C778 {
    u8 pad0[0x18];
    s16 o18; u8 padA[2]; f32 (*f1C)(void* at, s32 ch);
};
struct Font_eu_15C778 { u8 pad0[8]; s32 units; u8 pad1[0x3C]; f32 scale; Vt_eu_15C778* vt; };
struct Font2_eu_15C778 { u8 pad0[8]; s32 units; u8 pad1[0x3C]; f32 scale; VtW_eu_15C778* vt; };
struct Box_eu_15C778 { f32 x; f32 y; f32 w; f32 h; s32 style; s32 pad14; s32 halign; s32 valign; };

void func_eu_0015C778(Font_eu_15C778* self, u8* str, Box_eu_15C778* box, s32 a, s32 b)
{
    f32 x;
    f32 y;
    s32 first = 1;
    self->vt->f24((u8*)self + self->vt->o20, a, b);
    if (box->valign == 0) {
        y = box->y;
    } else {
        f32 height = (f32)self->units * self->scale;
        u8* p = str;
        while (*p) {
            if (*p++ == 10) {
                height += (f32)self->units * self->scale;
            }
        }
        if (box->valign == 2) {
            y = (box->y + box->h) - height;
        } else {
            y = box->y + (box->h - height) * 0.5f;
        }
    }
    u8* s = str;
    s32 v;
    for (; (v = *s) != 0; s = s + 1) {
        f32 half = 0.5f;
        s32 c = v & 0xff;
        u8* next = s + 1;
        if (c == 10) {
            y += (f32)self->units * self->scale;
            first = 1;
        } else {
            if (first) {
                if (box->halign == 0) {
                    x = box->x;
                } else {
                    u8* q = s;
                    x = 0.0f;
                    if (c != 0 && c != 10) {
                        do {
                            Font2_eu_15C778* f = (Font2_eu_15C778*)self;
                            x += f->vt->f1C((u8*)self + f->vt->o18, *q++);
                        } while (*q != 0 && *q != 10);
                    }
                    if (box->halign == 2) {
                        x = (box->x + box->w) - x;
                    } else {
                        x = box->x + (box->w - x) * half;
                    }
                }
                first = 0;
            }
            x += self->vt->f34((u8*)self + self->vt->o30, x, y, *s, box->style, b);
        }
    }
    self->vt->f3C((u8*)self + self->vt->o38, a, b);
}
