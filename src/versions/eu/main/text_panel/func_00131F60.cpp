// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the panel's open flag and state sit 0x310 later (0x56C, 0x570); the gauge's top and the
// label row are 24.19 less and the screen is PAL's 512 lines high (the screen y scale); the layout
// has a fourth word (0x1C, func_eu_001374E0), and the words US writes at 0x14 and 0x18 are at 0x18
// and 0x1C; "%c" is at an address the tools do not pair; and "Move" and "Zoom" are text ids (0x4F,
// 0x50) read into text readers (0xC0 bytes, func_eu_0015DD18) and drawn with func_eu_0015E7E0, in
// the player's language.
struct Obj_eu_131F60 {
    u8 pad0[0x56C];
    s32 open;
    s32 state;
};

struct Layout_eu_131F60 : Layout_137228 {
    void* f1C;
};

struct TextReader_eu_131F60 { u8 bytes[0xC0]; };

extern const char D_eu_0024C520[]; // "%c", US D_00249CE0

void InitTextReaderFromTextTable(TextReader_eu_131F60* out, s32 id, Font* font, s32 zero);
void DrawWrappedAlignedText(TextReader_eu_131F60* reader, Layout_137228* layout, s32 zero, PacketWriter* gs);
void SetTextLayoutVerticalPlacement(Layout_137228* layout, s32 value);

struct Gfx_eu_131F60 {
    static s32 ScreenX(f32 x)
    {
        return (s32)((x + 1728.0f) * 16.0f);
    }

    static s32 ScreenY(f32 y)
    {
        return (s32)((y * 0.5462963f + 1920.0f) * 16.0f);
    }
};

// The full-screen layout, its colour written into a four-word buffer. The buffer is the inline
// function's own frame, which is allocated when the inline is expanded (so before the text readers,
// at 0x40) and whose address integration keeps in a pseudo with the address as its equivalent: a
// first reference that copies it (`word`) lets the store and the argument take the address itself,
// so retail forms it again (addiu a1, sp, 0x40) and stores at 0x40(sp); with `col.w` at each use
// the pseudo carries the address across Pos and Size in a saved register.
struct ScreenLayout_eu_131F60 {
    static void Reset(Layout_137228* l, s32 color)
    {
        Quad4 col;
        l->Pos(0.0f, 0.0f);
        l->Size(640.0f, 468.610168f);
        s32* word = col.w;
        *word = color;
        l->Color(word);
        l->SetF14(0);
        l->SetF18(0);
        SetTextLayoutVerticalPlacement(l, 0);
    }
};

void DrawTextPanelControlLabels(Obj_eu_131F60* self, PacketWriter* gs)
{
    BeginGifTag(gs, 0, 1, 0xE);
    AddGifRegisterWrite(gs, 0x47, 0x31001);
    AddGifRegisterWrite(gs, 0x42, 0x44);
    BeginGifTag(gs, 0x84, 5, 0x44441);
    for (s32 i = 0; i < 8; i++) {
        f32 zoom = g_camera->f478;
        const PanelColor* const lit = &D_002610D8;
        const PanelColor* const dim = &D_002610E0;
        f32 step = 1.0f / 15.0f;
        f32 top = 348.610168f;
        f32 half = 0.5f;
        f32 lo = (f32)i * (1.0f / 9.0f);
        f32 hi = lo + step;
        f32 x0 = (1.0f - lo) * 55.0f - 9.0f;
        f32 x1 = ((1.0f - hi) * 55.0f + 1.0f) - 9.0f;
        f32 y0 = top - lo * 60.0f;
        f32 y1 = top - hi * 60.0f;
        PanelColor c = (lo + hi) * half <= zoom ? *lit : *dim;
        AddGifRgbaEntry(gs, *(u32*)&c);
        s32 sx0 = Gfx_eu_131F60::ScreenX(320.0f - x0);
        s32 sy0 = Gfx_eu_131F60::ScreenY(y0);
        AddGifXyzfNoDrawEntry(gs, sx0, sy0, 0, 0);
        AddGifXyzfNoDrawEntry(gs, Gfx_eu_131F60::ScreenX(x0 + 320.0f), sy0, 0, 0);
        s32 sy1 = Gfx_eu_131F60::ScreenY(y1);
        AddGifXyzfEntry(gs, Gfx_eu_131F60::ScreenX(320.0f - x1), sy1, 0, 0);
        AddGifXyzfEntry(gs, Gfx_eu_131F60::ScreenX(x1 + 320.0f), sy1, 0, 0);
    }
    if (self->state != 1) {
        return;
    }
    char buf[16];
    Layout_eu_131F60 L;
    f32 row = 366.610168f;
    ScreenLayout_eu_131F60::Reset(&L, 0xFF808080);
    PadRecord* pad = (g_padRouting & 2) ? &g_padRecord : &g_blankPadRecord;
    Font* glyphs = GetFontById(1);
    Font* text = GetFontById(0);
    FormatToString(buf, D_eu_0024C520, 0x28);
    Layout_eu_131F60* lay = &L;
    lay->f18 = (void*)1;
    lay->f1C = (void*)1;
    L.w = 0.0f;
    L.h = 0.0f;
    f32 s = 0.4f;
    if (self->open != 0 && pad->f48 != 0.0f) {
        s = 0.5f;
    }
    PushFontScale(glyphs, s, s);
    L.x = 265.0f;
    L.y = row;
    DrawFontString(glyphs, buf, &L, 0, gs);
    PopFontScale(glyphs);
    FormatToString(buf, D_eu_0024C520, 0x29);
    s = 0.4f;
    if (self->open != 0 && pad->f7C != 0.0f) {
        s = 0.5f;
    }
    PushFontScale(glyphs, s, s);
    L.x = 375.0f;
    L.y = row;
    DrawFontString(glyphs, buf, &L, 0, gs);
    PopFontScale(glyphs);
    *(PanelColor*)&L.color = PanelColor(0x32, 0x84, 0xB0, 0x80);
    PushFontScale(text, 0.6f, 0.6f);
    Layout_eu_131F60& move = L;
    move.f18 = (void*)2;
    L.x = (f32)(320 - D_00261090[0]);
    L.y = row;
    TextReader_eu_131F60 moveText;
    InitTextReaderFromTextTable(&moveText, 0x4F, text, 0);
    DrawWrappedAlignedText(&moveText, &L, 0, gs);
    L.f18 = 0;
    L.x = (f32)(D_00261090[0] + 320);
    L.y = row;
    TextReader_eu_131F60 zoomText;
    InitTextReaderFromTextTable(&zoomText, 0x50, text, 0);
    DrawWrappedAlignedText(&zoomText, &L, 0, gs);
    PopFontScale(text);
}
