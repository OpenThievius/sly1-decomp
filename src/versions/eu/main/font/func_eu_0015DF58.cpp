// SPDX-License-Identifier: AGPL-3.0-or-later
// Reads the next character of a text, first applying the markup codes before it (~colour, &font, ^size).

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

s32 PeekTextReaderChar(Text_eu_15DF58* t, s32 i);
void AdvanceTextReader(Text_eu_15DF58* t, s32 n);
s32 IsWideCharDigit(s32 c);
void CopyFont(Font_eu_15DF58* src, Font_eu_15DF58* dst);
void PopFontScale(Font_eu_15DF58* f);
void PushFontScale(Font_eu_15DF58* f, f32 x, f32 y);

s32 ReadTextCharAnyWidth(Text_eu_15DF58* t)
{
    s32 done = t->done;
    while (!done) {
        s32 c = PeekTextReaderChar(t, 0);
        switch (c) {
        case '~':
            if (PeekTextReaderChar(t, 1) == c) {
                AdvanceTextReader(t, 1);
                done = 1;
            } else if (PeekTextReaderChar(t, 1) == '.') {
                t->tint = t->deftint;
                t->colour = t->tint;
                AdvanceTextReader(t, 2);
            } else {
                s32 i = 1;
                u32 v = 0;
                s32 d = PeekTextReaderChar(t, 1);
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
                    d = PeekTextReaderChar(t, i);
                }
                if (i >= 7) {
                    t->tint.r = (((v >> 16) & 0xFF) + 1) >> 1;
                    t->tint.g = (((v & 0xFF00) >> 8) + 1) >> 1;
                    t->tint.b = ((v & 0xFF) + 1) >> 1;
                    t->colour = t->tint;
                    AdvanceTextReader(t, 7);
                } else {
                    t->font = t->base;
                    t->colour = t->deftint;
                    done = 1;
                }
            }
            break;
        case '&':
            if (PeekTextReaderChar(t, 1) == c) {
                AdvanceTextReader(t, 1);
                done = 1;
            } else if (PeekTextReaderChar(t, 1) == '.') {
                t->font = t->base;
                t->colour = t->tint;
                t->fA0 = 1;
                AdvanceTextReader(t, 2);
            } else if (IsWideCharDigit(PeekTextReaderChar(t, 1))) {
                Font_eu_15DF58* f = (Font_eu_15DF58*)FindFontByKeyChar(PeekTextReaderChar(t, 1));
                if (f) {
                    Font_eu_15DF58* own = &t->own;
                    CopyFont(f, own);
                    AdvanceTextReader(t, 2);
                    Font_eu_15DF58* b = t->base;
                    f32 r = ((f32)b->f8 * b->f48) / ((f32)own->f8 * own->f48);
                    t->own.f44 *= r;
                    t->own.f48 *= r;
                    t->font = own;
                    Rgba_eu_15DF58 col = t->fontcol;
                    col.a = t->colour.a;
                    t->colour = col;
                } else {
                    t->font = t->base;
                    t->colour = t->deftint;
                    done = 1;
                }
                t->fA0 = 1;
            } else {
                done = 1;
            }
            break;
        case '^':
            if (PeekTextReaderChar(t, 1) == c) {
                AdvanceTextReader(t, 1);
                done = 1;
            } else if (PeekTextReaderChar(t, 1) == '.') {
                PopFontScale(t->font);
                AdvanceTextReader(t, 2);
            } else if (IsWideCharDigit(PeekTextReaderChar(t, 1)) && IsWideCharDigit(PeekTextReaderChar(t, 2))) {
                s32 a = PeekTextReaderChar(t, 1);
                s32 b = PeekTextReaderChar(t, 2);
                f32 s = (f32)(a - '0') + (f32)(b - '0') * 0.1f;
                PushFontScale(t->font, s * t->font->f44, s * t->font->f48);
                AdvanceTextReader(t, 3);
            } else {
                done = 1;
            }
            break;
        default:
            done = 1;
            break;
        }
    }
    s32 c = PeekTextReaderChar(t, 0);
    AdvanceTextReader(t, 1);
    return c;
}
