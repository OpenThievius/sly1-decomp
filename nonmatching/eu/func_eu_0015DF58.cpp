// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_0015DF58.cpp func_eu_0015DF58 --unit src/main/0015C000.cpp
// Still differs: Reads next text character after markup codes; only s5/s6 swapped (retail keeps 0x2E in s5 and constant 1 in s6).
// PAL: reads the next character of a text, first applying the markup codes before it (~colour, &font, ^size).
// NEAR: only s5/s6 swapped: retail keeps 0x2E in s5 and the constant 1 (stored to fA0) in s6.

struct Font_eu_15DF58 { u8 pad0[8]; s32 f8; u8 pad1[0x38]; f32 f44; f32 f48; };
struct Rgba_eu_15DF58 { u8 r, g, b, a; };
struct Text_eu_15DF58 {
    s32 kind; s32 f4; u8* cur;
    Font_eu_15DF58* font;
    Font_eu_15DF58* base;
    u8 pad14[4];
    Font_eu_15DF58 own;
    u8 pad64[0xA0 - 0x18 - sizeof(Font_eu_15DF58)];
    s32 fA0;
    Rgba_eu_15DF58 colour;
    Rgba_eu_15DF58 tint;
    Rgba_eu_15DF58 deftint;
    Rgba_eu_15DF58 fontcol;
    s32 done;
};

s32 func_eu_0015DEA0(Text_eu_15DF58* t, s32 i);
void func_eu_0015DF18(Text_eu_15DF58* t, s32 n);
s32 func_eu_001E3210(s32 c);
void func_0015C9B0(Font_eu_15DF58* src, Font_eu_15DF58* dst);
void func_0015C900(Font_eu_15DF58* f);
void func_0015C8B8(Font_eu_15DF58* f, f32 x, f32 y);

s32 func_eu_0015DF58(Text_eu_15DF58* t)
{
    s32 done = t->done;
    while (!done) {
        s32 c = func_eu_0015DEA0(t, 0);
        switch (c) {
        case '~':
            if (func_eu_0015DEA0(t, 1) == c) {
                func_eu_0015DF18(t, 1);
                done = 1;
            } else if (func_eu_0015DEA0(t, 1) == '.') {
                t->tint = t->deftint;
                t->colour = t->tint;
                func_eu_0015DF18(t, 2);
            } else {
                s32 i = 1;
                u32 v = 0;
                s32 d = func_eu_0015DEA0(t, 1);
                while (d != 0 && i < 7) {
                    if ((u16)(d - '0') < 10) {
                        d = d - '0';
                    } else if ((u16)(d - 'A') < 6) {
                        d = d - 'A' + 10;
                    } else if ((u16)(d - 'a') < 6) {
                        d = d - 'a' + 10;
                    } else {
                        break;
                    }
                    v = v * 16 + d;
                    i++;
                    d = func_eu_0015DEA0(t, i);
                }
                if (i >= 7) {
                    t->tint.r = (((v >> 16) & 0xFF) + 1) >> 1;
                    t->tint.g = (((v & 0xFF00) >> 8) + 1) >> 1;
                    t->tint.b = ((v & 0xFF) + 1) >> 1;
                    t->colour = t->tint;
                    func_eu_0015DF18(t, 7);
                } else {
                    t->font = t->base;
                    t->colour = t->deftint;
                    done = 1;
                }
            }
            break;
        case '&':
            if (func_eu_0015DEA0(t, 1) == c) {
                func_eu_0015DF18(t, 1);
                done = 1;
            } else if (func_eu_0015DEA0(t, 1) == '.') {
                t->font = t->base;
                t->colour = t->tint;
                t->fA0 = 1;
                func_eu_0015DF18(t, 2);
            } else if (func_eu_001E3210(func_eu_0015DEA0(t, 1))) {
                Font_eu_15DF58* f = (Font_eu_15DF58*)func_0015C200(func_eu_0015DEA0(t, 1));
                if (f) {
                    Font_eu_15DF58* own = &t->own;
                    func_0015C9B0(f, own);
                    func_eu_0015DF18(t, 2);
                    Font_eu_15DF58* b = t->base;
                    f32 r = ((f32)b->f8 * b->f48) / ((f32)own->f8 * own->f48);
                    t->own.f44 *= r;
                    t->own.f48 *= r;
                    t->font = own;
                    Rgba_eu_15DF58 col = t->fontcol;
                    col.a = t->colour.a;
                    t->colour = col;
                    t->fA0 = 1;
                } else {
                    t->font = t->base;
                    t->colour = t->deftint;
                    t->fA0 = 1;
                    done = 1;
                }
            } else {
                done = 1;
            }
            break;
        case '^':
            if (func_eu_0015DEA0(t, 1) == c) {
                func_eu_0015DF18(t, 1);
                done = 1;
            } else if (func_eu_0015DEA0(t, 1) == '.') {
                func_0015C900(t->font);
                func_eu_0015DF18(t, 2);
            } else if (func_eu_001E3210(func_eu_0015DEA0(t, 1)) && func_eu_001E3210(func_eu_0015DEA0(t, 2))) {
                s32 a = func_eu_0015DEA0(t, 1);
                s32 b = func_eu_0015DEA0(t, 2);
                f32 s = (f32)(a - '0') + (f32)(b - '0') * 0.1f;
                func_0015C8B8(t->font, s * t->font->f44, s * t->font->f48);
                func_eu_0015DF18(t, 3);
            } else {
                done = 1;
            }
            break;
        default:
            done = 1;
            break;
        }
    }
    s32 c = func_eu_0015DEA0(t, 0);
    func_eu_0015DF18(t, 1);
    return c;
}
