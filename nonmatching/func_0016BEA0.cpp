// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1208/1216, checked 2026-11-08
// NEAR (src/main/file_16AA18.cpp, where it is INCLUDE_RODATA(D_0024A7D8) and INCLUDE_ASM; the
// file's CaptionLayout needs the field view below): the frame (0x140, the colour slot's block
// scope frees 0x30 for the 2-character string) and the calls are retail's; registers and the
// order of the float constants are not. Retail loads 0.5 before the title's DrawFontString,
// 18.0 and 12.0 after it, then 10.0, 1.3 (twice: the push's argument and the loop's, f12 and
// f27) and 0.1 after GetFontById, copies 0.5 to f25 for the loop, and keeps &out in s0 and
// s8; ours schedules 1.3 first and keeps one copy. Sibling of DrawSelectionCaption (matched).
#include "common.h"
#include "screen_element.h"
#include "font.h"
#include "globals.h"

extern f32 g_gameClock[];
struct BoxStyle;
extern BoxStyle D_002629A8;
struct CaptionLayout;
void SetTextLayoutPosition(CaptionLayout* out, f32 x, f32 y);
void SetTextLayoutSize(CaptionLayout* out, f32 x, f32 y);
void SetTextLayoutColor(CaptionLayout* out, s32* value);
void SetTextLayoutHorizontalAlign(CaptionLayout* out, s32 flag);
void SetTextLayoutVerticalAlign(CaptionLayout* out, s32 flag);
struct CaptionLayout {
    union {
        u8 b[32];
        struct {
            f32 x, y;
            f32 w, h;
            u32 color;
            s32 hAlign;
            s32 vAlign;
        };
    };
    void Pos(f32 x, f32 y) { SetTextLayoutPosition(this, x, y); }
    void Size(f32 x, f32 y) { SetTextLayoutSize(this, x, y); }
    void Color(s32* c) { SetTextLayoutColor(this, c); }
    void FlagA(s32 f) { SetTextLayoutHorizontalAlign(this, f); }
    void FlagB(s32 f) { SetTextLayoutVerticalAlign(this, f); }
};
struct CaptionDrawer {
    static void Draw(Font** h, CaptionLayout* out, void* tbl)
    {
        if (*h != 0) {
            const FontVt* vt = (*h)->vt;
            vt->drawBox((Font*)((u8*)*h + vt->adj9), h, out, tbl);
        }
    }
};
f32 Sine(f32 x);
void PushFontScale(Font* font, f32 x, f32 y);
void PopFontScale(Font* font);
Font* GetFontById(s32 index);
u32 TestGridEntryBit(u32 bit);
void DrawFontString(Font* font, const char* text, CaptionLayout* out, s32 zero, void* d);
const char* GetMovieTitle(s32 index);
void DrawLineSegment(s32 x0, s32 y0, s32 z0, s32 x1, s32 y1, s32 z1, T217D_Word* color, s32 k);

void DrawGridSelector(T217D_1330* self)
{
    T217D_Word tmp;
    CaptionLayout out;

    tmp = self->colorWord;
    ((u8*)&tmp)[3] = (u8)((f32)((u8*)&tmp)[3] * self->blend);
    f32 p = self->w;
    f32 q = self->h;
    s32 held = tmp.v;
    out.Pos(self->x, self->y);
    out.Size(p, q);
    {
        T217D_Word slot;
        slot.v = held;
        out.Color(&slot.v);
        out.FlagA(1);
        out.FlagB(0);
        u8* h = (u8*)self->frame;
        if (h != 0) {
            slot = *(T217D_Word*)(h + 0x18);
            h[0x1B] = (u8)((f32)h[0x1B] * self->blend);
            CaptionDrawer::Draw(self->frame, &out, &g_gsPacketWriter);
            *(T217D_Word*)((u8*)self->frame + 0x18) = slot;
        }
    }
    const char* title = "???";
    if (TestGridEntryBit(self->cursor) != 0)
        title = GetMovieTitle(self->cursor);
    CaptionLayout* o = &out;
    f32 half = 0.5f;
    DrawFontString(self->font, title, o, 0, &g_gsPacketWriter);
    f32 left = 18.0f;
    f32 gap = 12.0f;
    Font* f = GetFontById(4);
    f32 rate = 10.0f;
    f32 depth = 0.1f;
    f32 big = 1.3f;
    PushFontScale(f, 1.3f, 1.3f);
    f32 x0 = self->x + left + f->Width('_') * half;
    f32 y0 = self->y + (f32)self->font->height * self->font->sy + gap
             + (f32)f->height * f->sy * half;
    f32 dx = f->Width('_') + left;
    f32 dy = (f32)f->height * f->sy + gap;
    out.w = 0;
    out.h = 0;
    o->vAlign = 1;
    o->hAlign = 1;
    for (s32 i = 0; i < 4; i++) {
        f32 y = y0 + (f32)i * dy;
        for (s32 j = 0; j < 4; j++) {
            f32 x = x0 + (f32)j * dx;
            s32 n = i * 4 + j;
            char s[2] = { TestGridEntryBit(n) != 0 ? 'a' + n : '_', 0 };
            out.x = x;
            out.y = y;
            f32 k = 1.0f;
            if (n == self->cursor)
                k = (k - (Sine(g_gameClock[4] * rate) * half + half)) * depth + k;
            f32 v = self->blend * (k * big);
            PushFontScale(f, v, v);
            DrawFontString(f, s, o, 0, &g_gsPacketWriter);
            PopFontScale(f);
        }
    }
    PopFontScale(f);
    T217D_Word slot = *(T217D_Word*)((u8*)&D_002629A8 + 0x18);
    s32 y = (s32)(((self->y + (f32)self->font->height * self->font->sy + -1.0f) * 0.454545f + 1936.0f) * 16.0f);
    DrawLineSegment((s32)((self->x + 1728.0f) * 16.0f), y, 0, (s32)((self->x + self->w + 1728.0f) * 16.0f), y, 0,
                    &slot, 0);
}
