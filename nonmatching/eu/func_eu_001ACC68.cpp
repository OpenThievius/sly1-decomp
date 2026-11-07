// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 488/492, checked 2026-11-07
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001ACC68.cpp func_eu_001ACC68 --unit src/main/screen_element.cpp
// Still differs: Menu object init; only the multiply differs (retail mult v0,v1 + mflo a0 with the store later, ours 3-operand mult a0,v0,v1; moving the statement or s64/u32 casts did not help).
// Mechanism (from -dr/-dc/-dl/-dg dumps of this file and of func_0012D2A8): mulsi3 expands to
// mulsi3_mult3_r5900, whose hi/lo/accum clobbers are explicit pseudos; its alternatives are
// "=d,l,d,v" for the product, so it prints the two-operand form only if the product ends up in
// LO, which regclass never prefers when the only use is a store. Every two-operand mult in
// matched C comes from combine instead: when combine rebuilds the mult from its bare SET (a
// three-insn combine whose result is split again, or a PARALLEL of two SETs split in two), the
// explicit clobbers are lost, recog_for_combine adds scratch ones, and the insn becomes
// mulsi3_internal ("=l" only): mult rs,rt with the result in LO, and reload's output copy
// mflo rd, which sched2 then delays past the mult's latency. In func_0012D2A8 the product's
// use is a copy into a2 (a call argument, a hard register CSE cannot propagate away). Here the
// product is only stored: (set mem (mult ..)) is never valid, so combine needs a register copy of
// the product that survives CSE (a pseudo live outside CSE's block, or a hard register), or a
// second use of the product. Not reproduced: a local, chained assignment, inline getter/setter
// (CSE deletes their copies), a reused switch variable (expand multiplies straight into it),
// s64/u64 locals and casts. 0x1AC01C (US twin func_001ABE70) is the only stored product of the
// ten mult $zero sites in US; the other nine feed call arguments.
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
