// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 140/156 (89.7%), checked 2026-11-07
// NEAR: the same instructions; only the float registers differ. Retail holds the running width in $f21 and the best in $f20 (best is zeroed first); ours allocates the other way round whatever order the two are declared in (about ten forms tried: separate zero, copy of best, continue instead of else).
#include "common.h"
#include "fpu.h"
#include "font.h"
#include "text_reader.h"

void func_0015DB80(TextReader* self);
s32 func_0015DBE0(TextReader* self);

f32 func_0015E1F0(TextReader* self)
{
    f32 width = 0.0f;
    s32 newline = 10;
    f32 best = width;
    func_0015DB80(self);
    s32 c;
    while ((c = func_0015DBE0(self)) != 0) {
        if (c == newline) {
            best = (width >? best);
            width = 0.0f;
        } else {
            Font* holder = self->font;
            const FontVt* glyph = holder->vt;
            width += glyph->width((Font*)((u8*)holder + glyph->adj3), c);
        }
    }
    best = (width >? best);
    return best;
}
