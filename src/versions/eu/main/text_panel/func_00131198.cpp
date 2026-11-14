// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the panel's fields 0x28C later (the small font at 0x59C, the frame cell at 0x520, the
// state at 0x570, the bands at 0x5A4, the child at 0x5B0); the compass points are text ids,
// read into a text reader (0xC0 bytes) and measured from it, the widest starting from 0; and
// the bands sit lower and are scaled for PAL's 512 lines.
struct Panel_131198_eu {
    u8 pad0[4];
    Font* font;                 // 0x04
    u8 pad8[0x520 - 0x8];
    Font** frame;               // 0x520
    u8 pad524[0x570 - 0x524];
    s32 state;                  // 0x570
    u8 pad574[0x59C - 0x574];
    Font* smallFont;            // 0x59C
    u8 pad5A0[0x5A4 - 0x5A0];
    void* bands;                // 0x5A4
    s32 bandsSize;              // 0x5A8
    u8 pad5AC[0x5B0 - 0x5AC];
    void* child;                // 0x5B0
};
struct TextReader_131198_eu { u8 bytes[0xC0]; };
void SetupScreenElementText(Panel_131198_eu* self);
void ClearTextPanel(Panel_131198_eu* self);
void SetTextPanelState(Panel_131198_eu* self, s32 mode);
void InitTextReaderFromTextTable(TextReader_131198_eu* out, s32 id, Font* font, s32 zero);
f32 SumTextWidth(TextReader_131198_eu* reader);

void SetupTextPanel(Panel_131198_eu* self)
{
    SetupScreenElementText(self);
    ClearTextPanel(self);
    f32 sy = 0.8f;
    Font* small = self->font->Clone(0.7f, sy);
    self->smallFont = small;
    small->useTestWord = 1;
    small->testWord = 0x3F001;
    self->font = self->font->Clone(0.75f, sy);
    if (IsFontLoaded(2) != 0) {
        self->frame = (Font**)&g_panelFrameStyle;
        *self->frame = GetFontById(2);
    }
    g_compassLabelWidth = 0.0f;
    for (u32 i = 0; i < 8; i++) {
        TextReader_131198_eu reader;
        InitTextReaderFromTextTable(&reader, ((s32*)g_compassDirectionNames)[i], self->smallFont, 0);
        g_compassLabelWidth = SumTextWidth(&reader) >? g_compassLabelWidth;
    }
    self->state = -1;
    self->child = 0;
    SetTextPanelState(self, 0);
    PushBackMemoryMark();
    f32 step = 1.0f / 24.0f;
    PacketWriter gs;
    InitGifPacket(&gs);
    UsePacketBufferMemory(&gs, 0x800, AllocateBackMemory(0x8000));
    BeginGifTag(&gs, 0, 3, 0x1EE);
    AddGifRegisterWrite(&gs, 0x47, 0x70000);
    AddGifRegisterWrite(&gs, 0x42, 0x44);
    PanelColor c = g_panelBackdropColor;
    c.a = 0x60;
    AddGifRgbaEntry(&gs, *(u32*)&c);
    BeginGifTag(&gs, 0x44, 1, 4);
    InitCurveSpan(&g_panelEdgeCurveA, (const SpanHead*)g_panelEdgeCurvePointsA, 0.171875f, 40.0f, 0x18);
    InitCurveSpan(&g_panelEdgeCurveB, (const SpanHead*)g_panelEdgeCurvePointsB, 0.171875f, -60.0f, 0x18);
    InitCurveSpan(&g_panelEdgeCurveC, (const SpanHead*)g_panelEdgeCurvePointsC, 0.2857143f, 8.0f, 0x18);
    s32 i;
    f32 t;
    AddGifXyzfNoDrawEntry(&gs, 0x6C00, 0x7800, 0x0FFFFFF0, 0);
    AddGifXyzfNoDrawEntry(&gs, 0x6C00, 0x7ABB, 0x0FFFFFF0, 0);
    for (t = step, i = 1; i < 24; i++) {
        f32 u = t * 640.0f;
        f32 y = EvalCurveSpan(&g_panelEdgeCurveA, i);
        t += step;
        s32 x = (s32)((u + 1728.0f) * 16.0f);
        AddGifXyzfEntry(&gs, x, 0x7800, 0x0FFFFFF0, 0);
        AddGifXyzfEntry(&gs, x, (s32)((y * 0.546296298f + 1920.0f) * 16.0f), 0x0FFFFFF0, 0);
    }
    AddGifXyzfEntry(&gs, 0x9400, 0x7800, 0x0FFFFFF0, 0);
    AddGifXyzfEntry(&gs, 0x9400, 0x7ABB, 0x0FFFFFF0, 0);
    AddGifXyzfNoDrawEntry(&gs, 0x6C00, 0x8800, 0x0FFFFFF0, 0);
    AddGifXyzfNoDrawEntry(&gs, 0x6C00, 0x80C2, 0x0FFFFFF0, 0);
    t = 1.0f / 24.0f;
    for (i = 1; i < 24; i++) {
        f32 u = t * 640.0f;
        f32 y = EvalCurveSpan(&g_panelEdgeCurveB, i);
        t += step;
        s32 x = (s32)((u + 1728.0f) * 16.0f);
        AddGifXyzfEntry(&gs, x, 0x8800, 0x0FFFFFF0, 0);
        AddGifXyzfEntry(&gs, x, (s32)((y * 0.546296298f + 1920.0f) * 16.0f), 0x0FFFFFF0, 0);
    }
    AddGifXyzfEntry(&gs, 0x9400, 0x8800, 0x0FFFFFF0, 0);
    AddGifXyzfEntry(&gs, 0x9400, 0x80C2, 0x0FFFFFF0, 0);
    DetachPacketBufferCopy(&gs, (s32*)&self->bands, 0, &self->bandsSize, 0x15);
    PopBackMemoryMark();
}
