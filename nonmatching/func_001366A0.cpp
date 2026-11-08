// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 2160/2088, checked 2026-11-08
// NEAR: register allocation. offX and the width swap f24 and f25; ours keeps &box in s1 where
// retail rebuilds sp+0x20 before each setter call; the text block's s-registers differ (retail:
// s4 total, s5 the typed reader, s6 &box, s7 the lines layout, fp the clock's %hi). The control
// flow matches: the state switch with case 4 for retail's tree, the offsets' switch, the alpha
// fade as a byte lerp on the integer difference (retail has no `- (f32)a` term), the frame
// colour swapped as an Rgba4 around the style's box.
#include "common.h"
#include "screen_element.h"
#include "packet_writer.h"
#include "font.h"
#include "shapes.h"
#include "layout_137228.h"

struct PanelStyle { s32 f0; u8 f4; f32 f8; f32 fC; f32 f10; f32 f14; u32 f18; };
struct TextScratch { u8 bytes[0xB0]; };
extern f32 g_gameTime;
extern f32 g_gameClock[];
Font* InitTextReader(void* out, void* p, Font* font);
s32 CountTextChars(void* self);
void* CopyString(void* dst, const char* src);
void PushFontScale(Font* font, f32 x, f32 y);
void PopFontScale(Font* font);
f32 WrapAngle(f32 a);
void DrawFontString(Font* font, const char* text, Layout_137228* layout, s32 zero, PacketWriter* gs);
void DrawTextPanelCenterFrame(T217D_440* self, PacketWriter* gs);
void DrawCompassStrip(T217D_440* self, PacketWriter* gs);
void DrawTextPanelBorders(T217D_440* self, PacketWriter* gs);
void DrawTextPanelBlocks(T217D_440* self, PacketWriter* q);
extern PacketWriter g_gsPacketWriter;
s32 AreMenusClosed(void);
void DrawTextPanelControlLabels(T217D_440* self, PacketWriter* gs);
Font* GetFontById(s32 id);
void AddDmaRefTag(PacketWriter* gs, void* data, s32 size);
void SeekTextReader(void* reader, s32 n);
void AppendString(char* dst, const char* src);
void DrawAlignedText(void* reader, Layout_137228* layout, Layout_137228* frame, PacketWriter* gs);
f32 Cosine(f32 x);

// A byte from a toward b by t, as the panel fades its alpha (the difference taken as an integer).
struct ByteLerp {
    static u8 Of(u8 a, u8 b, f32 t)
    {
        if (a == b) {
            return b;
        }
        if (a < b) {
            return a + (s32)(t * ((f32)(b - a) + 0.999f));
        }
        return b + (s32)((1.0f - t) * (0.999f - (f32)(b - a)));
    }
};

// The one-character string the panel's button glyph is drawn from.
struct PanelGlyph {
    char c[2];
    static PanelGlyph Of(char ch)
    {
        PanelGlyph g;
        g.c[0] = ch;
        g.c[1] = 0;
        return g;
    }
};

// Draws the panel: its frames by state, then its box, the text typed so far (a cursor blinking
// at its end) scrolled to the line being typed, and the pulsing button glyph.
void DrawTextPanel(T217D_440* self)
{
    if (AreMenusClosed() == 0) {
        return;
    }
    switch (self->state) {
    case 1:
    case 2:
        DrawTextPanelCenterFrame(self, &g_gsPacketWriter);
        AddDmaRefTag(&g_gsPacketWriter, self->bands, self->bandsSize);
        DrawCompassStrip(self, &g_gsPacketWriter);
        DrawTextPanelControlLabels(self, &g_gsPacketWriter);
        DrawTextPanelBorders(self, &g_gsPacketWriter);
        DrawTextPanelBlocks(self, &g_gsPacketWriter);
        break;
    case 4:
        break;
    case 5:
        DrawTextPanelCenterFrame(self, &g_gsPacketWriter);
        break;
    }
    f32 scale = 1.0f;
    if (self->state == 4) {
        scale = 0.8f;
    }
    if (self->state == 3 && self->text[0] == 0) {
        return;
    }
    PushFontScale(self->font, scale, scale);
    Rgba4 color = *(Rgba4*)&self->highlight;
    Rgba4 frameColor;
    if (self->frame != 0) {
        frameColor = *(Rgba4*)&((PanelStyle*)self->frame)->f18;
    } else {
        *(u32*)&frameColor = 0;
    }
    f32 offY = 0.0f;
    f32 offX = offY;
    f32 line = (f32)self->font->height * self->font->sy;
    f32 width = 280.0f;
    f32 height = line * 3.0f;
    switch (self->state) {
    case 3:
        offY = -8.0f;
        break;
    case 4:
        height = line + line;
        width = 380.0f;
        offX = -50.0f;
        offY = 40.0f;
        break;
    }
    s32 grey = 0xFF808080;
    Layout_137228 box;
    box.Pos(offX + 180.0f, offY + 386.800018f);
    box.Size(width, height);
    {
        Quad4 col;
        col.w[0] = grey;
        box.Color(col.w);
    }
    box.SetF14(0);
    box.SetF18(0);
    f32 fade = 1.0f;
    if (D_002708E0.target != 0) {
        fade = D_002708E0.blend <? fade;
    }
    if (D_00271558.target != 0) {
        fade = D_00271558.blend <? fade;
    }
    if (fade < 1.0f) {
        u8 a = ByteLerp::Of(0, color.a, fade);
        Rgba4 t = color;
        t.a = a;
        color = t;
        a = ByteLerp::Of(0, frameColor.a, fade);
        Rgba4 u = frameColor;
        u.a = a;
        frameColor = u;
    }
    if (self->state == 3 && self->frame != 0) {
        PanelStyle* style = (PanelStyle*)self->frame;
        Rgba4 saved = *(Rgba4*)&style->f18;
        *(Rgba4*)&style->f18 = frameColor;
        Font* f = *self->frame;
        if (f != 0) {
            f->vt->drawBox((Font*)((u8*)f + f->vt->adj9), self->frame, &box, &g_gsPacketWriter);
        }
        *(Rgba4*)&((PanelStyle*)self->frame)->f18 = saved;
    }
    if (self->text[0] != 0) {
        TextScratch all;
        InitTextReader(&all, self->text, self->font);
        s32 total = CountTextChars(&all);
        s32 shown = (s32)((g_gameClock[1] - self->textSince) * self->charsPerSecond);
        if (!(shown < total)) {
            shown = total;
        }
        s32 row = 0;
        while (row < self->lineCount && !(shown < self->lineBreaks[row])) {
            row++;
        }
        f32 scroll;
        if (row > 0 && row < self->lineCount) {
            f32 end = (f32)self->lineBreaks[row] / self->charsPerSecond;
            f32 start = (f32)self->lineBreaks[row - 1] / self->charsPerSecond;
            scroll = ((g_gameClock[1] - self->textSince) - start) / (end - start);
        } else {
            scroll = 0.0f;
        }
        char text[0x200];
        CopyString(text, self->text);
        row++;
        TextScratch typed;
        InitTextReader(&typed, text, self->font);
        SeekTextReader(&typed, shown);
        s32 cursor = 1;
        if (!(shown < total)) {
            cursor = (s32)(g_gameClock[1] * 4.0f) & 1;
        }
        if (cursor != 0) {
            AppendString(text, "&.~fffffff|");
        }
        f32 y = ((f32)row + scroll) * ((f32)self->font->height * self->font->sy);
        Layout_137228 lines;
        lines.Pos(offX + 180.0f, (offY + 386.800018f) - (0.0f >? (y - height)));
        lines.Size(width, y);
        {
            Quad4 col;
            col.w[0] = *(u32*)&color;
            lines.Color(col.w);
        }
        lines.SetF14(0);
        lines.SetF18(0);
        DrawAlignedText(&typed, &lines, &box, &g_gsPacketWriter);
    }
    PopFontScale(self->font);
    if (self->f2F8 != 0) {
        PanelGlyph glyph = PanelGlyph::Of(self->f2F8);
        f32 s = Cosine(WrapAngle(g_gameTime * 10.0f)) * 0.5f + 0.5f;
        f32 size = (1.0f - s) * 0.3f + s * 0.4f;
        Font* font = GetFontById(1);
        f32 x;
        f32 y;
        if (self->state == 4) {
            x = 533.0f;
            y = 472.800018f;
        } else {
            x = offX + 482.0f;
            y = offY + 472.800018f;
        }
        PushFontScale(font, size, size);
        Layout_137228 at;
        at.Pos(x, y);
        at.Size(0.0f, 0.0f);
        {
            Quad4 col;
            col.w[0] = 0xFF808080;
            at.Color(col.w);
        }
        at.SetF14(0);
        at.SetF18(0);
        at.f18 = (void*)1;
        at.f14 = 1;
        DrawFontString(font, glyph.c, &at, 0, &g_gsPacketWriter);
        PopFontScale(font);
    }
}
