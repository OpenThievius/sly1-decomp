// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: sets the word at 0x1C of a text layout (callers pass 0).
struct Layout_eu_1374E0 {
    u8 pad0[0x1C];
    s32 f1C;
};

void SetTextLayoutVerticalPlacement(Layout_eu_1374E0* self, s32 v)
{
    self->f1C = v;
}
