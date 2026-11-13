// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the page and the cursor at 0x570 and 0x574, titles and labels as text ids (rows of
// D_eu_0026B308 by item, Row_193598_eu of the file's PAL GetMenuChoiceLabel), a language page (0x21) listing D_eu_002636D8, the cursor of that page
// from D_eu_00263710, no labels written ahead and no sound for page 20, and the title measured
// into the element (0x408).
struct Page_1936A0_eu { s32 title; f32 titleScale; f32 itemScale; s32 vertical; s32 count; s32* items; };
struct Size_1936A0_eu { s32 f0; f32 w; f32 h; };
// PAL's text reader is 0xC0 bytes (US 0xB0).
struct TextReader_1936A0_eu { u8 bytes[0xC0]; };
struct Self_1936A0_eu {
    u8 pad0[4];
    Font* font;                 // 0x04
    u8 pad8[0x408 - 0x8];
    Size_1936A0_eu size;        // 0x408
    u8 pad414[0x570 - 0x414];
    s32 page;                   // 0x570
    s32 cursor;                 // 0x574
};
extern s32 D_eu_002636EC;
extern s32 D_eu_002636D8[];
extern s32 D_eu_00263710;
void InitTextReaderFromTextTable(TextReader_1936A0_eu* out, s32 id, Font* font, s32 zero);
void BreakTextIntoLines(TextReader_1936A0_eu* buf, f32 w, Size_1936A0_eu* out);
f32 SumTextWidth(TextReader_1936A0_eu* buf);
void InitWideTextReader(TextReader_1936A0_eu* out, void* text, Font* font, s32 zero);
void* GetMenuChoiceLabel(s32 page, s32 index);
void SetScreenElementSize(Self_1936A0_eu* self, f32 w, f32 h);

void BuildPauseMenuPage(Self_1936A0_eu* self)
{
    s32 page = self->page;
    Page_1936A0_eu* row = &((Page_1936A0_eu*)g_pauseMenuPages)[page];
    switch (page) {
    case 0:
        row->count = 0;
        for (u32 i = 0; i < 8; i++) {
            s32 item = D_00269CD8[i];
            s32 show = 1;
            switch (item) {
            case 4:
                if (D_0026FA68 == 0) {
                    show = 0;
                }
                break;
            case 5:
                show = 1;
                break;
            case 18: {
                s32 key = (g_saveData->f19D8 << 8) | g_saveData->f19DC;
                if (key != 0x204 && key != 0x407) {
                    show = 0;
                    break;
                }
                show = 0;
                s32 walker = FindObject42CStateWalker();
                if (walker != 0) {
                    s32 code;
                    GetStateWalkerCurrentKey((void*)walker, &code);
                    if (code < 0x431) {
                        show = code >= 0x42F;
                    }
                }
                break;
            }
            case 19:
                show = D_0026EC58 == 2;
                break;
            case 20: {
                s32 key = (g_saveData->f19D8 << 8) | g_saveData->f19DC;
                show = 0;
                if (key == 0x304 || key == 0x307 || key == 0x502) {
                    show = 1;
                }
                break;
            }
            case 21:
                if (g_saveData->f19D8 == 0) {
                    show = 0;
                } else if (g_saveData->f19D8 == 5 || g_saveData->f19DC == 1 ||
                           (g_saveData->f19DC == 0 && (*(s32*)(g_currentLevelRecord->bits74 + 4) & 1) == 0)) {
                    item = 0x16;
                }
                break;
            }
            if (show != 0) {
                row->items[row->count++] = item;
            }
        }
        break;
    case 0x17:
        row->count = 0;
        for (u32 i = 0; i < 9; i++) {
            s32 item = D_00269D18[i];
            s32 show = 1;
            switch (item) {
            case 6:
                show = ((ElementStack*)g_elementStack)->resumeState == 1;
                break;
            case 7:
                break;
            case 8:
                show = ((ElementStack*)g_elementStack)->resumeState != 1;
                break;
            }
            if (show != 0) {
                row->items[row->count++] = item;
            }
        }
        break;
    case 0x21:
        row->count = 0;
        for (s32 i = 0; i < D_eu_002636EC; i++) {
            row->items[row->count++] = D_eu_002636D8[i] + 0x1B;
        }
        row->items[row->count++] = 0x11;
        break;
    }
    self->cursor = 0;
    switch (page) {
    case 16:
        for (self->cursor = 0; self->cursor < 3 && ((CardSlot*)g_memoryCard.slots)[self->cursor].f0C != 0.0f;
             self->cursor++) {
        }
        break;
    case 11:
    case 17:
        if (g_memoryCard.f4F44 != 0) {
            self->cursor = (CardSlot*)g_memoryCard.f4F44 - g_memoryCard.slots;
        }
        break;
    case 2:
    case 4:
    case 7:
    case 14:
    case 18:
        self->cursor = 1;
        break;
    case 0x21:
        self->cursor = D_eu_00263710;
        break;
    }
    f32 width = 0.0f;
    f32 items = width;
    f32 height = width;
    TextReader_1936A0_eu tr;
    if (row->title != -1) {
        PushFontScale(self->font, row->titleScale, row->titleScale);
        InitTextReaderFromTextTable(&tr, row->title, self->font, 0);
        BreakTextIntoLines(&tr, 500.0f, &self->size);
        PopFontScale(self->font);
        height = self->size.h;
        width = self->size.w >? width;
    }
    PushFontScale(self->font, row->itemScale, row->itemScale);
    if (row->vertical != 0) {
        height += (f32)self->font->height * self->font->sy * (f32)row->count;
    } else {
        height += (f32)self->font->height * self->font->sy;
    }
    for (s32 i = 0; i < row->count && row->items[i] != -1; i++) {
        Row_193598_eu* r = &D_eu_0026B308[row->items[i]];
        f32 w = 0.0f;
        if (r->mode != 0) {
            for (s32 j = 0; j < r->mode; j++) {
                InitTextReaderFromTextTable(&tr, r->ids[j], self->font, 0);
                w = SumTextWidth(&tr) >? w;
            }
        } else {
            InitWideTextReader(&tr, GetMenuChoiceLabel(page, row->items[i]), self->font, 0);
            w = SumTextWidth(&tr);
        }
        if (row->vertical != 0) {
            items = items >? w;
        } else {
            if (i != 0) {
                items += (f32)self->font->advance * self->font->sx * 2.0f;
            }
            items += w;
        }
    }
    PopFontScale(self->font);
    width = items >? width;
    SetScreenElementSize(self, width + 10.0f, height);
}
