// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_0015E7E0.cpp func_eu_0015E7E0 --unit src/main/0015C000.cpp
// Still differs: Word-wrapped text draw; down to 6 lines: halign in v0 vs v1 and lineStart in a2 vs v0 in the per-line alignment block.
// Draws a word-wrapped string aligned inside a box, one character at a time through the font's virtual calls.
struct Entry_eu_15E7E0 { s32 start; f32 width; };
struct Table_eu_15E7E0 { u8 pad0[0xC]; s32 count; Entry_eu_15E7E0 entries[1]; };
struct Rgba_eu_15E7E0 { u8 c[4]; };
struct Box_eu_15E7E0 { f32 x; f32 y; f32 w; f32 h; Rgba_eu_15E7E0 color; Table_eu_15E7E0* lines; s32 halign; s32 valign; };
struct Vt_eu_15E7E0 {
    u8 pad0[0x20];
    s16 o20; u8 padA[2]; void (*f24)(void* at, s32 a, s32 b);
    s16 o28; u8 padB[2]; void (*f2C)(void* at, s32 b);
    s16 o30; u8 padC[2]; f32 (*f34)(void* at, f32 x, f32 y, s32 ch, s32 arg, s32 b);
    s16 o38; u8 padD[2]; void (*f3C)(void* at, s32 a, s32 b);
};
struct Holder_eu_15E7E0 { u8 pad0[0x4C]; Vt_eu_15E7E0* vt; };
struct Font_eu_15E7E0 { u8 pad0[8]; s32 units; u8 pad1[0x3C]; f32 scale; };
struct Text_eu_15E7E0 {
    u8 pad0[0xC]; Holder_eu_15E7E0* holder; Font_eu_15E7E0* font;
    u8 pad1[0xA0 - 0x14]; s32 flagA0; s32 argA4;
};

f32 func_eu_0015E438(void* self);
void func_eu_0015DDF0(void* self, void* color);
void func_eu_0015DDA0(void* self);
s32 func_eu_0015DE18(void* self);
s32 func_eu_0015DF58(void* self);
s32 func_eu_001E31E0(s32 ch);

void func_eu_0015E7E0(Text_eu_15E7E0* self, Box_eu_15E7E0* box, s32 a, s32 b)
{
    Entry_eu_15E7E0 local;
    Entry_eu_15E7E0* e;
    Entry_eu_15E7E0* end;
    s32 n;
    f32 x;
    f32 y;
    s32 lineStart = 1;
    s32 pending = 1;
    s32 ch;
    Table_eu_15E7E0* tbl = box->lines;
    if (tbl != 0) {
        s32 cnt = tbl->count;
        e = tbl->entries;
        end = e + cnt;
        n = cnt;
    } else {
        local.start = 0;
        f32 w = func_eu_0015E438(self);
        local.width = w;
        e = &local;
        end = &local + 1;
        n = 1;
    }
    if (box->valign == 0) {
        y = box->y;
    } else {
        f32 h = (f32)n * ((f32)self->font->units * self->font->scale);
        if (box->valign == 2) {
            y = (box->y + box->h) - h;
        } else {
            y = box->y + (box->h - h) * 0.5f;
        }
    }
    Rgba_eu_15E7E0 color = box->color;
    func_eu_0015DDF0(self, &color);
    s32 started = 0;
    func_eu_0015DDA0(self);
    while ((ch = func_eu_0015DF58(self)) != 0) {
        s32 pos = func_eu_0015DE18(self);
        if (lineStart == 0) {
            if (e < end && pos >= e->start) {
                lineStart = 1;
                pending = 1;
                y += (f32)self->font->units * self->font->scale;
            }
        }
        if (lineStart != 0) {
            if (box->halign == 0) {
                x = box->x;
            } else if (box->halign == 2) {
                x = (box->x + box->w) - e->width;
            } else {
                x = box->x + (box->w - e->width) * 0.5f;
            }
            e++;
            lineStart = 0;
        }
        if (started == 0) {
            Holder_eu_15E7E0* h = self->holder;
            h->vt->f24((u8*)h + h->vt->o20, a, b);
            started = (s32)self->holder;
        } else if (self->flagA0 != 0) {
            Holder_eu_15E7E0* h = self->holder;
            h->vt->f2C((u8*)h + h->vt->o28, b);
            self->flagA0 = 0;
        }
        if (pending != 0) {
            if (func_eu_001E31E0(ch) != 0) {
                continue;
            }
        }
        Holder_eu_15E7E0* h = self->holder;
        pending = 0;
        x += h->vt->f34((u8*)h + h->vt->o30, x, y, ch, self->argA4, b);
    }
    Holder_eu_15E7E0* h = self->holder;
    h->vt->f3C((u8*)h + h->vt->o38, a, b);
}
