// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's DrawPromptElement (US func_001AE220): the element's fields 0x310 further on for its wide
// text, the layout linked to the record at +0x408 with the alignments one setter later and the
// extra func_eu_001374E0 call, and the text drawn through PAL's func_eu_0015DCB8 and
// func_eu_0015E7E0. D_eu_0027A42C is PAL's D_00272B6C (the blend's upper limit).
struct Prompt_eu_1AEF48 {
    void* vt;               // 0x000
    Font* font;             // 0x004
    u16 text[0x200];        // 0x008: the text, wide
    T217D_Word link;        // 0x408
    u8 pad40C[0x518 - 0x40C];
    T217D_Word colorWord;   // 0x518
    f32 scale;              // 0x51C
    Font** frame;           // 0x520
    u8 pad524[0x534 - 0x524];
    f32 shownX;             // 0x534
    f32 shownY;             // 0x538
    f32 hiddenX;            // 0x53C
    f32 hiddenY;            // 0x540
    f32 w;                  // 0x544
    f32 h;                  // 0x548
    f32 blend;              // 0x54C
};

extern u8 D_eu_00263590[];
extern f32 D_eu_0027A42C;
void func_eu_001374E0(void* out, s32 v);
void func_eu_0015DCB8(void* buf, void* name, void* p, s32 zero);
void func_eu_0015E7E0(void* buf, void* out, s32 zero, void* d);

void DrawPromptElement(Prompt_eu_1AEF48* self)
{
    LayoutBuilder out;
    T217D_Word tmp;
    T217D_Word slot;
    u8 loc[0xC0];
    T217D_Word* link = &self->link;

    f32 s = Sine(g_elapsedTime * 3.0f);
    tmp = self->colorWord;
    ((u8*)&tmp)[3] = (u8)(s32)((s * 0.5f + 0.5f) * 255.0f);
    f32 t = D_eu_0027A42C <? self->blend;
    f32 u = 1.0f - t;
    f32 w = self->w;
    f32 h = self->h;
    s32 held = tmp.v;
    out.Pos(u * self->hiddenX + t * self->shownX, u * self->hiddenY + t * self->shownY);
    out.Size(w, h);
    slot.v = held;
    out.Color(&slot.v);
    out.FlagA((s32)link);
    out.FlagB(2);
    func_eu_001374E0(&out, 0);
    if (self->frame != 0) {
        StyleDrawer::Draw(self->frame, &out, D_eu_00263590);
    }
    PushFontScale(self->font, self->scale, self->scale);
    func_eu_0015DCB8(loc, &self->text[0], self->font, 0);
    func_eu_0015E7E0(loc, &out, 0, D_eu_00263590);
    PopFontScale(self->font);
}
