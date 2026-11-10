// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 488/492, checked 2026-11-10
// NEAR: everything but the product: retail computes f268 = f260 * f264 into LO (mult $zero,
//       v0,v1 and a later mflo a0, the two-operand form, its result allocated to LO); ours
//       writes it with the three-operand mult straight into a0, one instruction less.
// Mechanism (docs/toolchain/cse.md "A stored product's two-operand mult"): combine re-recognises
// the bare SET (mulsi3_internal) only through a register copy of the product that survives CSE
// and is not the next insn after the mult. CSE keeps the copy only when its destination is
// referenced outside the tail's CSE block (REGNO_FIRST_UID, from reg_scan before cse1, so a dead
// reference counts). Test form, EXACT under check.py (2026-11-10), not landed as implausible:
// `s32 n = 0;` first in the function, `s32 m = self->f26C * self->f270;` before the letterX and
// letterY stores, then `n = m; self->f268 = n;`. Without either half it is mult3 again; a live
// early reference (n holding the switch's value) moves the switch's registers. No single-variable
// form gives a temporary product (expand writes a product straight into a variable target; an
// inline's return copy is adjacent; an inline's parameter copy is deleted by CSE). Also tried:
// the product first, last, of the stored copies, chained assignments, swapped operands, s64.
#include "common.h"
#include "screen_element.h"
#include "font.h"
#include "game_progress.h"

Font* GetFontById(s32 k);
void PushFontScale(Font* font, f32 x, f32 y);
void PopFontScale(Font* font);
void SetupScreenElementText(void* self);
void SetScreenElementSize(void* self, f32 x, f32 y);
extern f32 D_002743B0;
extern f32 D_002743B4;
extern f32 D_002743B8;
extern f32 D_002743BC;

void InitGauge(T217D_2E0* self)
{
    SetupScreenElementText(self);
    self->font = GetFontById(4);
    self->scale = 1.0f;
    self->fillTarget = 1.0f;
    self->fill = 0;
    switch (g_saveData->f19D8) {
    case 1:
        self->f260 = 4;
        self->f264 = 1;
        break;
    case 4:
        self->f260 = 5;
        self->f264 = 10;
        break;
    case 2:
        self->f260 = 3;
        self->f264 = 1;
        self->fill = 1.0f;
        break;
    case 3:
        self->f260 = 4;
        self->f264 = 1;
        self->fill = 1.0f;
        break;
    case 5:
        self->f260 = 4;
        self->f264 = 5;
        break;
    default:
        return;
    }
    f32 pad = 5.0f;
    self->barX = D_002743B0 * self->scale;
    self->barY = D_002743B4 * self->scale;
    self->barW = D_002743B8 * self->scale;
    self->barH = D_002743BC * self->scale;
    PushFontScale(self->font, self->scale, self->scale);
    f32 h = (f32)self->font->height * self->font->sy;
    f32 w = self->font->Width('z');
    f32 h2 = (f32)self->font->height * self->font->sy;
    SetScreenElementSize(self, h, w + h2 + pad);
    PopFontScale(self->font);
    self->changedAt = 0;
    self->f26C = self->f260;
    self->f270 = self->f264;
    self->letterX = h * 0.5f;
    self->letterY = w + pad + h2 * 0.5f;
    self->f268 = self->f26C * self->f270;
}
