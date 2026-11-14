// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the object's fields are at 0x518 to 0x570 (US 0x208 to 0x260); the alignment flags are
// (0, 1) and PAL's third flag (func_eu_001374E0) is cleared; the layout's alignment words are at
// +0x18 and +0x1C (CaptionLayout's VERSION_EU word); the default title is text 0xAC
// (func_eu_001DDAB0), drawn through a text reader (func_eu_0015DCB8, func_eu_0015E7E0) whose
// 0xC0-byte buffer is declared after the colour's block; the cells go through DrawFontString;
// the line's y is scaled by 0.5462963f and offset by 1920.0f.
struct __attribute__((packed)) Pk4_16BEA0 { s32 v; };
struct Obj_16BEA0_eu {
    u8 pad0[4];
    Font* font;
    u8 pad8[0x518 - 0x8];
    Pk4_16BEA0 colorWord;
    u8 pad51c[0x520 - 0x51C];
    Font** frame;
    u8 pad524[0x52C - 0x524];
    f32 x;
    f32 y;
    u8 pad534[0x544 - 0x534];
    f32 w;
    f32 h;
    f32 blend;
    u8 pad550[0x570 - 0x550];
    s32 cursor;
};

const char* GetTextTableEntry(s32 id);
void InitWideTextReader(void* out, const char* p, Font* font, s32 z);
void DrawWrappedAlignedText(void* a, CaptionLayout* b, s32 c, void* d);
void SetTextLayoutVerticalPlacement(CaptionLayout* out, s32 v);
void DrawFontString(Font *self, const char *str, StringLayout *par, Vec4U *clip, PacketWriter *s);
struct Out_eu_16BEA0 : CaptionLayout {
    void Mode(s32 v) { SetTextLayoutVerticalPlacement(this, v); }
    void Draw(void* loc, s32 z, void* tbl) { DrawWrappedAlignedText(loc, this, z, tbl); }
};

void DrawGridSelector(Obj_16BEA0_eu* self)
{
    Pk4_16BEA0 tmp;
    Out_eu_16BEA0 out;

    tmp = self->colorWord;
    ((u8*)&tmp)[3] = (u8)((f32)((u8*)&tmp)[3] * self->blend);
    f32 p = self->w;
    f32 q = self->h;
    s32 held = tmp.v;
    out.Pos(self->x, self->y);
    out.Size(p, q);
    {
        Pk4_16BEA0 slot;
        slot.v = held;
        s32* color = &slot.v;
        out.Color(color);
        out.FlagA(0);
        out.FlagB(1);
        out.Mode(0);
        u8* h = (u8*)self->frame;
        if (h != 0) {
            slot = *(Pk4_16BEA0*)(h + 0x18);
            h[0x1B] = (u8)((f32)h[0x1B] * self->blend);
            CaptionDrawer::Draw(self->frame, &out, &g_gsPacketWriter);
            *(Pk4_16BEA0*)((u8*)self->frame + 0x18) = slot;
        }
    }
    const char* title = GetTextTableEntry(0xAC);
    if (TestGridEntryBit(self->cursor) != 0)
        title = GetMovieTitle(self->cursor);
    f32 half = 0.5f;
    u8 loc[0xC0];
    InitWideTextReader(loc, title, self->font, 0);
    Out_eu_16BEA0* o = &out;
    o->Draw(loc, 0, &g_gsPacketWriter);
    f32 left = 18.0f;
    f32 gap = 12.0f;
    Font* f = GetFontById(4);
    PushUniformFontScale(f, 1.3f);
    f32 cellW = f->Width('_');
    f32 cellH = (f32)f->height * f->sy;
    f32 y0 = self->y + (f32)self->font->height * self->font->sy + gap + cellH * half;
    f32 x0 = self->x + left + cellW * half;
    f32 dx = f->Width('_') + left;
    f32 dy = (f32)f->height * f->sy + gap;
    out.w = 0;
    out.h = 0;
    o->hAlign = 1;
    o->vAlign = 1;
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
                k = (k - (Sine(g_gameClock[4] * 10.0f) * 0.5f + 0.5f)) * 0.1f + k;
            f32 v = self->blend * (k * 1.3f);
            PushFontScale(f, v, v);
            DrawFontString(f, s, (StringLayout*)&out, 0, &g_gsPacketWriter);
            PopFontScale(f);
        }
    }
    PopFontScale(f);
    s32 y = (s32)(((self->y + (f32)self->font->height * self->font->sy + -1.0f) * 0.5462963f + 1920.0f) * 16.0f);
    Pk4_16BEA0 slot = *(Pk4_16BEA0*)((u8*)&g_gridSelectorFrame + 0x18);
    DrawLineSegment((s32)((self->x + 1728.0f) * 16.0f), y, 0, (s32)((self->x + self->w + 1728.0f) * 16.0f), y, 0,
                    (T217D_Word*)&slot, 0);
}
