// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 488/492, checked 2026-11-07
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001ACC68.cpp func_eu_001ACC68 --unit src/main/screen_element.cpp
// Still differs: Menu object init; only the multiply differs (retail mult v0,v1 + mflo a0 with the store later, ours 3-operand mult a0,v0,v1).
// Mechanism (2026-11-10, combine.c and cse.c, docs/TOOLCHAIN.md "A stored product's two-operand
// mult"): only a mult that combine re-recognises from its bare SET (its clobbers dropped) is
// mulsi3_internal, the two-operand form. That needs the product substituted into a register copy
// that survives CSE and is not the next real insn after the mult (the adjacent copy keeps the
// mult3 PARALLEL). CSE keeps the copy only if its destination lives outside CSE's block (the tail
// after the switch's join). Proven: `s32 m = cols * rows;` before the cols2/rows2 stores, then
// `n = m; self->cells = n;` with n the switch's variable gives retail's whole tail, but n moves the
// switch's registers and is not plausible. Ruled out: locals, chained assignments, inline getters
// (copies replaced and deleted by CSE), s64/u64 locals and casts (truncdisi2 stays), a reused
// switch variable assigned the product directly (expand multiplies straight into it).
// 0x1AC01C (US twin func_001ABE70) is the only stored product of the ten mult $zero sites in US;
// the other nine are products by a constant or of a dying operand, copied to call arguments.
// Initialises a menu object: sets up its font, grid size from the mode and the label sizes.
struct Game_eu_1AE6D0;
extern Game_eu_1AE6D0* D_eu_002636F0;
struct Vt_eu_1ACC68 { u8 pad0[0x18]; s16 off; u8 pad1[2]; f32 (*width)(void* at, s32 ch); };
struct Font_eu_1ACC68 { u8 pad0[8]; s32 units; u8 pad1[0x3C]; f32 scale; Vt_eu_1ACC68* vt; };
struct Menu_eu_1ACC68 {
    u8 pad0[4];
    Font_eu_1ACC68* font;
    u8 pad1[0x51C - 8];
    f32 a51C;
    u8 pad2[0x570 - 0x520];
    s32 cols; s32 rows; s32 cells; s32 cols2; s32 rows2;
    f32 a584; f32 a588; s32 a58C;
    f32 b590; f32 b594; f32 b598; f32 b59C; f32 c5A0; f32 c5A4;
};
struct Mode_eu_1ACC68 { u8 pad0[0x19D8]; s32 mode; };
struct Consts_eu_1ACC68 { f32 a; f32 b; f32 c; f32 d; };
extern f32 D_eu_0027DB00;
extern f32 D_eu_0027DB04;
extern f32 D_eu_0027DB08;
extern f32 D_eu_0027DB0C;

void func_eu_001AAFB0(void* self);
void PushFontScale(void* obj, f32 a, f32 b);
void SetScreenElementSize(void* self, f32 a, f32 b);
void PopFontScale(void* obj);

void func_eu_001ACC68(Menu_eu_1ACC68* self)
{
    func_eu_001AAFB0(self);
    self->font = (Font_eu_1ACC68*)GetFontById(4);
    self->a51C = 1.0f;
    self->a588 = 1.0f;
    self->a584 = 0.0f;
    switch (((Mode_eu_1ACC68*)D_eu_002636F0)->mode) {
    case 1:
        self->cols = 4;
        self->rows = 1;
        break;
    case 4:
        self->cols = 5;
        self->rows = 10;
        break;
    case 2:
        self->cols = 3;
        self->rows = 1;
        self->a584 = 1.0f;
        break;
    case 3:
        self->cols = 4;
        self->rows = 1;
        self->a584 = 1.0f;
        break;
    case 5:
        self->cols = 4;
        self->rows = 5;
        break;
    default:
        return;
    }
    f32 t = self->a51C;
    self->b590 = D_eu_0027DB00 * t;
    self->b594 = D_eu_0027DB04 * t;
    self->b598 = D_eu_0027DB08 * t;
    self->b59C = D_eu_0027DB0C * t;
    PushFontScale(self->font, t, t);
    f32 h = (f32)self->font->units * self->font->scale;
    f32 w = self->font->vt->width((u8*)self->font + self->font->vt->off, 0x7A);
    f32 h2 = (f32)self->font->units * self->font->scale;
    SetScreenElementSize(self, h, (w + h2) + 5.0f);
    PopFontScale(self->font);
    self->a58C = 0;
    self->cols2 = self->cols;
    self->rows2 = self->rows;
    self->cells = self->cols * self->rows;
    self->c5A0 = h * 0.5f;
    self->c5A4 = (w + 5.0f) + h2 * 0.5f;
}
