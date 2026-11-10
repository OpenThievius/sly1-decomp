// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1824/2428 (75.1%), checked 2026-11-10
// BYTES 0/0, checked 2026-11-10
// NEAR (PAL's own definition): python3 tools/check.py nonmatching/eu/func_001366A0.cpp func_001366A0 --version eu --unit src/main/text_panel.cpp
// Still differs (2026-11-10, w13): the size and every block but the line search match. The cut
// loop over the copied lines record (`for (i = 1; i < lines.count; i++) if (at < start[i]) { cut;
// break; }`) rolls its body into the exit test (stmt.c expand_end_loop), jump.c copies that test
// before the loop (retail's peeled i = 1 with the height unmultiplied), and the copy's jump back
// to the increment enters the loop from outside: loop.c says "ignored due to multiple entry
// points" and leaves the index unreduced (`sll; addu sp`), where retail walks a pointer from
// s5 + 24 (`addiu a0,s5,24`, `addiu a0,a0,8`), s5 being the record copy's address kept from the
// block move (`move s5,a2`). An explicit walk (`for (s32* start = &lines.lines[1].start; ...;
// i++, start += 2)`, build/swarm/w13-1366A0/T5.cpp) gives retail's loop exactly but from the
// frame (`addiu a0,sp,0x538`, 608 bytes): the base must be a pointer CSE cannot fold to the frame.
// `goto` instead of break keeps the loop valid but hoists the count (598 bytes). Also: the
// clock's %hi in s7 where retail has s8 (ours hoists the packet writer's %hi into s8 over the
// text block, as the US near miss did before StyleDrawer).
// PAL: the panel's fields sit later (state 0x570, frame 0x520, colour 0x580, glyph 0x584, bands
// 0x5A4); its text is 16-bit (a reader of 0xC0 bytes, func_eu_0015DCB8, and PAL's copy and append,
// func_eu_001E3050, func_eu_001E3178); the line breaks are a record of their own (0x408, laid out by
// func_eu_0015E4A8 in SetTextPanelText), copied whole and cut at the line being typed when the text
// is taller than the panel (0x548); the layout has a fourth word (func_eu_001374E0), the text's
// layout takes the copied record in its first word, and the screen is PAL's 512 lines high.
struct TextLines_eu_1367B8 {
    u8 pad0[8];
    f32 height;                 // 0x08: the lines' height, cut with the count
    s32 count;                  // 0x0C: lines laid out
    struct {
        s32 start;              // the character index the line starts at
        s32 f4;
    } lines[32];                // 0x10
};

struct Sparkle_eu_1367B8 {
    u8 pad0[0x54C];
    f32 blend;
    u8 pad550[0x580 - 0x550];
    s32* target;
};

struct Obj_eu_1367B8 {
    u8 pad0[4];
    Font* font;                 // 0x004
    u16 text[0x200];            // 0x008
    TextLines_eu_1367B8 lines;  // 0x408
    u8 pad518[0x520 - 0x518];
    Font** frame;               // 0x520
    u8 pad524[0x548 - 0x524];
    f32 textHeight;             // 0x548: the laid-out text's height
    u8 pad54C[0x570 - 0x54C];
    s32 state;                  // 0x570
    u8 pad574[4];
    f32 textSince;              // 0x578
    f32 charsPerSecond;         // 0x57C
    u32 highlight;              // 0x580
    u8 glyph;                   // 0x584
    u8 pad585[0x5A4 - 0x585];
    void* bands;                // 0x5A4
    s32 bandsSize;              // 0x5A8
};

// PAL's layout, a word longer.
struct Layout_eu_1367B8 : Layout_137228 {
    s32 f1C;
};

struct TextReader_eu_1367B8 { u8 bytes[0xC0]; };

void* func_eu_0015DCB8(void* buf, void* name, Font* v, s32 zero);  // returns buf
s32 func_eu_001E3050(void* dst, const char* src);
void func_eu_0015E3E0(void* reader, s32 n);
s32 func_eu_0015DE58(void* reader);
void func_eu_001E3178(u16* dst, const u8* src);
void func_eu_0015E7E0(void* reader, Layout_137228* layout, Layout_137228* frame, PacketWriter* gs);
void func_eu_0015C778(Font* font, const char* text, Layout_137228* out, s32 zero, void* d);
void func_eu_001374E0(Layout_137228* layout, s32 value);

struct PanelLayout_eu_1367B8 {
    static s32* Words(Quad4& q)
    {
        return q.w;
    }

    static Layout_137228* Set(Layout_137228* l, f32 x, f32 y, f32 w, f32 h, s32 color, s32 first)
    {
        Quad4 col;
        l->Pos(x, y);
        l->Size(w, h);
        col.w[0] = color;
        l->Color(Words(col));
        l->SetF14(first);
        l->SetF18(0);
        func_eu_001374E0(l, 0);
        return l;
    }
};

void DrawTextPanel(Obj_eu_1367B8* self)
{
    if (AreMenusClosed() == 0) {
        return;
    }
    switch (self->state) {
    case 1:
    case 2:
        DrawTextPanelCenterFrame((T217D_440*)self, &g_gsPacketWriter);
        AddDmaRefTag(&g_gsPacketWriter, self->bands, self->bandsSize);
        DrawCompassStrip((T217D_440*)self, &g_gsPacketWriter);
        DrawTextPanelControlLabels((T217D_440*)self, &g_gsPacketWriter);
        DrawTextPanelBorders((T217D_440*)self, &g_gsPacketWriter);
        DrawTextPanelBlocks((T217D_440*)self, &g_gsPacketWriter);
        break;
    case 4:
        break;
    case 5:
        DrawTextPanelCenterFrame((T217D_440*)self, &g_gsPacketWriter);
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
        offY = 54.0f;
        break;
    }
    s32 grey = 0xFF808080;
    Layout_eu_1367B8 box;
    PanelLayout_eu_1367B8::Set(&box, offX + 180.0f, offY + 362.610168f, width, height, grey, 0);
    f32 fade = 1.0f;
    if (((Sparkle_eu_1367B8*)&D_002708E0)->target != 0) {
        fade = ((Sparkle_eu_1367B8*)&D_002708E0)->blend <? fade;
    }
    if (((Sparkle_eu_1367B8*)&D_00271558)->target != 0) {
        fade = ((Sparkle_eu_1367B8*)&D_00271558)->blend <? fade;
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
        StyleDrawer::Draw(self->frame, &box, &g_gsPacketWriter);
        *(Rgba4*)&((PanelStyle*)self->frame)->f18 = saved;
    }
    if (self->text[0] != 0) {
        TextReader_eu_1367B8 all;
        func_eu_0015DCB8(&all, self->text, self->font, 0);
        s32 total = CountTextChars(&all);
        s32 shown = (s32)((g_gameClock[1] - self->textSince) * self->charsPerSecond);
        u16 text[0x200];
        TextLines_eu_1367B8 lines = self->lines;
        if (!(shown < total)) {
            shown = total;
        }
        f32 scroll = 0.0f;
        func_eu_001E3050(text, (const char*)self->text);
        TextReader_eu_1367B8 typed;
        func_eu_0015DCB8(&typed, text, self->font, 0);
        func_eu_0015E3E0(&typed, shown);
        if (height < self->textHeight) {
            s32 at = func_eu_0015DE58(&typed);
            for (s32 i = 1; i < lines.count; i++) {
                if (at < lines.lines[i].start) {
                    lines.count = i;
                    lines.height = (f32)i * ((f32)self->font->height * self->font->sy);
                    break;
                }
            }
            s32 row = lines.count;
            if (row > 0 && row < self->lines.count) {
                f32 start = (f32)self->lines.lines[row - 1].start / self->charsPerSecond;
                f32 end = (f32)self->lines.lines[row].start / self->charsPerSecond;
                scroll = ((g_gameClock[1] - self->textSince) - start) / (end - start);
            }
        }
        s32 cursor;
        if (shown < total) {
            cursor = 1;
        } else {
            cursor = (s32)(g_gameClock[1] * 4.0f) & 1;
        }
        if (cursor != 0) {
            func_eu_001E3178(text, (const u8*)"&.~ffffff|");
        }
        f32 y = ((f32)lines.count + scroll) * ((f32)self->font->height * self->font->sy);
        Layout_eu_1367B8 layout;
        f32 noScroll = 0.0f;
        PanelLayout_eu_1367B8::Set(&layout, offX + 180.0f, (offY + 362.610168f) - (noScroll >? (y - height)),
                                   width, y, *(s32*)&color, (s32)&lines);
        func_eu_0015E7E0(&typed, &layout, &box, &g_gsPacketWriter);
    }
    PopFontScale(self->font);
    if (self->glyph != 0) {
        char glyph[2] = { self->glyph, 0 };
        f32 s = Cosine(WrapAngle(g_gameTime * 10.0f)) * 0.5f + 0.5f;
        f32 size = (1.0f - s) * 0.3f + s * 0.4f;
        Font* font = GetFontById(1);
        f32 x;
        f32 y;
        if (self->state == 4) {
            x = 532.0f;
            y = 448.610168f;
        } else {
            x = offX + 482.0f;
            y = offY + 448.610168f;
        }
        PushFontScale(font, size, size);
        s32 glyphColor = 0xFF808080;
        Layout_eu_1367B8 at;
        Layout_eu_1367B8* l = (Layout_eu_1367B8*)PanelLayout_eu_1367B8::Set(&at, x, y, 0.0f, 0.0f, glyphColor, 0);
        l->f18 = (void*)1;
        l->f1C = 1;
        func_eu_0015C778(font, glyph, l, 0, &g_gsPacketWriter);
        PopFontScale(font);
    }
}
