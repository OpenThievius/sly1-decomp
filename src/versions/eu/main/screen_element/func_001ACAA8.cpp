// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's DrawSlidingGlyphElement (US func_001ACAA8): the fields moved (+0x310) for a wide text at
// +8, its length by func_eu_001E3018, and the extra func_eu_001374E0 call on the frame's layout.
struct Element_eu_1AD800 {
    void* vt;               // 0x000
    Font* font;             // 0x004
    u16 text[0x288];        // 0x008: the text, wide
    s32 color;              // 0x518
    f32 scale;              // 0x51C
    Font** frame;           // 0x520
    u8 pad524[0x530 - 0x524];
    f32 y;                  // 0x530
    f32 shownX;             // 0x534
    f32 shownY;             // 0x538
    f32 hiddenX;            // 0x53C
    f32 hiddenY;            // 0x540
    f32 w;                  // 0x544
    f32 h;                  // 0x548
    f32 blend;              // 0x54C
    u8 pad550[0x560 - 0x550];
    s32 mode;               // 0x560
};

void DrawScreenElementText(void* self);
s32 GetWideStringLength(u16* text);
void SetTextLayoutVerticalPlacement(void* out, s32 v);

void DrawSlidingGlyphElement(Element_eu_1AD800* self)
{
    LayoutByValue out;
    s32 n;
    s32 i;
    f32 c;
    f32 rest;
    f32 x;
    f32 y;

    switch (self->mode) {
    case 2:
        DrawScreenElementText(self);
        return;
    case 1:
    case 3:
        break;
    default:
        return;
    }
    n = GetWideStringLength(self->text);
    if (n == 0) {
        return;
    }
    x = self->shownX;
    y = self->hiddenX;
    c = ClampFloat::Of(self->blend / (1.0f / (f32)n), 0.0f, 1.0f);
    rest = 1.0f - c;
    if (self->frame != 0) {
        s32 grey = 0xFF808080;
        f32 w = x * self->blend + y * (1.0f - self->blend) + self->w;
        f32 h = self->h;
        out.Pos(x * c + y * rest, self->y);
        out.Size(w, h);
        out.Color(grey);
        out.FlagA(0);
        out.FlagB(0);
        SetTextLayoutVerticalPlacement(&out, 0);
        Font* o = *self->frame;
        if (o != 0) {
            o->vt->drawBox((Font*)((u8*)o + o->vt->adj9), self->frame, &out, &g_gsPacketWriter);
        }
    }
    FontCalls::Begin(self->font, 0, &g_gsPacketWriter);
    for (i = 0; i < n; i++) {
        s32 ch = self->text[i];
        f32 d;
        c = ClampFloat::Of(self->blend / ((f32)(i + 1) / (f32)n), 0.0f, 1.0f);
        rest = 1.0f - c;
        FontCalls::Glyph(self->font, ch, self->color, &g_gsPacketWriter, c * x + rest * y, self->shownY);
        d = FontCalls::Advance(self->font, ch);
        x += d;
        y += d;
    }
    FontCalls::End(self->font, 0, &g_gsPacketWriter);
}
