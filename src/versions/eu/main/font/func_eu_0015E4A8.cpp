// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: lays the reader's text out in lines no wider than the limit (0 for no limit),
// breaking after the last space or hyphen that fits, and records each line's start and width (less
// its trailing spaces), the widest line, the line count and the text's height, for func_eu_0015E7E0.
// The newline label is shared by a newline in the text and by the two ways a line is broken.
struct GlyphVt_eu_15E4A8 {
    u8 pad0[0x18];
    s16 off;
    u8 pad1A[2];
    f32 (*width)(void* self, s32 ch);
};
struct Font_eu_15E4A8 {
    u8 pad0[4];
    s32 cellWidth;
    s32 cellHeight;
    u8 padC[0x44 - 0xC];
    f32 sx;
    f32 sy;
    GlyphVt_eu_15E4A8* vt;
};
struct Reader_eu_15E4A8 {
    u8 pad0[0xC];
    Font_eu_15E4A8* font;
    Font_eu_15E4A8* defaultFont;
};
struct Line_eu_15E4A8 { s32 start; f32 width; };
struct Lines_eu_15E4A8 {
    f32 limit;
    f32 widest;
    f32 height;
    u32 count;
    Line_eu_15E4A8 lines[32];
};

void* FillMemory(void* p, s32 v, s32 n);
void RewindTextReader(void* self);
s32 func_eu_0015DE18(void* self);
s32 func_eu_0015DEA0(void* self, s32 i);
s32 func_eu_0015DF18(void* self, s32 n);
s32 func_eu_0015DF58(void* self);
s32 func_eu_001E31E0(s32 ch);

void func_eu_0015E4A8(Reader_eu_15E4A8* self, Lines_eu_15E4A8* t, f32 limit)
{
    f32 width = 0.0f;
    f32 trail = width;
    FillMemory(t, 0, sizeof(Lines_eu_15E4A8));
    Line_eu_15E4A8* e = t->lines;
    Line_eu_15E4A8* end = t->lines + 32;
    RewindTextReader(self);
    s32 c;
    while ((c = func_eu_0015DF58(self)) != 0) {
        s32 pos = func_eu_0015DE18(self);
        Font_eu_15E4A8* f = self->font;
        f32 w = f->vt->width((u8*)f + f->vt->off, c);
        if (func_eu_001E31E0(c) != 0) {
            if (c == '\n') {
            newline:
                if (e >= end) {
                    break;
                }
                if (width != 0.0f && trail != 0.0f) {
                    width -= trail;
                    trail = 0.0f;
                }
                e->width = width;
                e++;
                t->widest = width >? t->widest;
                width = 0.0f;
                if (e < end) {
                    e->start = pos + 1;
                }
                continue;
            }
            trail += w;
            if (width != 0.0f) {
                width += w;
            }
        } else {
            width += w;
            trail = 0.0f;
        }
        if (limit == 0.0f || !(limit < width)) {
            continue;
        }
        if (t->count >= 32) {
            break;
        }
        {
            w = width - w;
            f32 before = w;
            s32 k = -1;
            for (;;) {
                if (pos + k < e->start) {
                    break;
                }
                s32 ch = func_eu_0015DEA0(self, k - 1);
                if (ch == '\n') {
                    break;
                }
                if (func_eu_001E31E0(ch) != 0 || ch == '-') {
                    width = w;
                    if (func_eu_001E31E0(ch) != 0) {
                        Font_eu_15E4A8* s = self->font;
                        trail = (f32)s->cellWidth * s->sx;
                    } else {
                        trail = 0.0f;
                    }
                    func_eu_0015DF18(self, k);
                    pos = func_eu_0015DE18(self);
                    goto newline;
                }
                k--;
                Font_eu_15E4A8* g = self->font;
                w -= g->vt->width((u8*)g + g->vt->off, ch);
            }
            if (!(0.0f < w)) {
                continue;
            }
            func_eu_0015DF18(self, -1);
            width = before;
            pos = func_eu_0015DE18(self);
            goto newline;
        }
    }
    if (e < end) {
        if (width != 0.0f && trail != 0.0f) {
            width -= trail;
        }
        e->width = width;
        e++;
        t->widest = width >? t->widest;
    }
    t->limit = limit;
    s32 n = e - t->lines;
    t->count = n;
    Font_eu_15E4A8* d = self->defaultFont;
    t->height = (f32)n * ((f32)d->cellHeight * d->sy);
}
