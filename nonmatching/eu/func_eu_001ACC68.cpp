// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 488/492, checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001ACC68.cpp func_eu_001ACC68 --unit src/main/001A8000.cpp
// Still differs: Menu object init; only the multiply differs (retail mult v0,v1 + mflo a0 with the store later, ours 3-operand mult a0,v0,v1; moving the statement or s64/u32 casts did not help).
// Initialises a menu object: sets up its font, grid size from the mode and the label sizes.
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
extern Mode_eu_1ACC68* D_eu_002636F0;
extern f32 D_eu_0027DB00;
extern f32 D_eu_0027DB04;
extern f32 D_eu_0027DB08;
extern f32 D_eu_0027DB0C;

void func_eu_001AAFB0(void* self);
void func_0015C8B8(void* obj, f32 a, f32 b);
void func_001AAB20(void* self, f32 a, f32 b);
void func_0015C900(void* obj);

void func_eu_001ACC68(Menu_eu_1ACC68* self)
{
    func_eu_001AAFB0(self);
    self->font = (Font_eu_1ACC68*)func_0015C1C0(4);
    self->a51C = 1.0f;
    self->a588 = 1.0f;
    self->a584 = 0.0f;
    switch (D_eu_002636F0->mode) {
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
    func_0015C8B8(self->font, t, t);
    f32 h = (f32)self->font->units * self->font->scale;
    f32 w = self->font->vt->width((u8*)self->font + self->font->vt->off, 0x7A);
    f32 h2 = (f32)self->font->units * self->font->scale;
    func_001AAB20(self, h, (w + h2) + 5.0f);
    func_0015C900(self->font);
    self->a58C = 0;
    self->cols2 = self->cols;
    self->rows2 = self->rows;
    self->cells = self->cols * self->rows;
    self->c5A0 = h * 0.5f;
    self->c5A4 = (w + 5.0f) + h2 * 0.5f;
}
