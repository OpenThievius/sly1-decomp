// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL definition: draws a nine-patch box of font glyph tiles around a rectangle.
typedef void (*Fn_eu_15D4E0)(void* at, s32 a, void* b);
struct Disp_eu_15D4E0 {
    u8 pad[0x20];
    s16 offA;
    u8 padA[2];
    Fn_eu_15D4E0 fnA;
    u8 padB[0x38 - 0x28];
    s16 offB;
    u8 padC[2];
    Fn_eu_15D4E0 fnB;
};
struct Self_eu_15D4E0 {
    u8 p0[8];
    s32 m8;
    u8 p0c[0x44 - 0x0C];
    f32 f44;
    f32 f48;
    Disp_eu_15D4E0* disp;
    u8 p50[0x60 - 0x50];
    u64 m60;
};
struct Font_eu_15D4E0;
struct Item_eu_15D4E0 {
    Font_eu_15D4E0* f0;
    u8 key;
    u8 p5[3];
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u32 color;
};
struct Rect_eu_15D4E0 { f32 x, y, w, h; };
struct Entry_eu_15D4E0 { u8 p0[2]; u16 a2; u16 a4; u16 a6; };
struct Strm_eu_15D4E0 { u8 pad[4]; };

Entry_eu_15D4E0* func_0015DAB8(Self_eu_15D4E0* self, u8 key);
void func_0015C8B8(Font_eu_15D4E0* p, f32 a, f32 b);
void func_0015C900(Font_eu_15D4E0* p);
void func_0015D338(Self_eu_15D4E0* self, u32 color, f32 x0, f32 y0, f32 x1, f32 y1,
                   f32 u0, f32 v0, f32 u1, f32 v1, Strm_eu_15D4E0* s);

void func_0015D4E0(Self_eu_15D4E0* self, Item_eu_15D4E0* item, Rect_eu_15D4E0* r, Strm_eu_15D4E0* s)
{
    Entry_eu_15D4E0* e = func_0015DAB8(self, item->key);
    if (e != 0) {
        func_0015C8B8(item->f0, item->f10, item->f14);
        f32 top = r->y;
        f32 sx = self->f44;
        f32 left = r->x;
        s32 u2i = e->a2 + e->a6;
        f32 x2 = left + r->w + item->f8 * sx;
        f32 cw = (f32)e->a6 * sx;
        f32 x1 = left - item->f8 * sx;
        s32 sz = 1 << (s32)((self->m60 >> 30) & 0xF);
        s32 height = self->m8;
        f32 sy = self->f48;
        s32 v0i = sz - e->a4;
        f32 x0 = x1 - cw;
        s32 v2i = sz - (e->a4 + height);
        f32 u1 = (f32)((e->a2 + u2i) / 2);
        f32 v1 = (f32)((v0i + v2i) / 2);
        f32 u0 = (f32)e->a2;
        f32 y1 = top - item->fC * sy;
        f32 v0 = (f32)v0i;
        f32 x3 = x2 + cw;
        f32 y2 = top + r->h + item->fC * sy;
        f32 y0 = y1 - (f32)height * sy;
        f32 y3 = y2 + (f32)height * sy;
        self->disp->fnA((u8*)self + self->disp->offA, 0, s);
        f32 v2 = (f32)v2i;
        f32 u2 = (f32)u2i;
        func_0015D338(self, item->color, x0, y0, x1, y1, u0, v0, u1, v1, s);
        func_0015D338(self, item->color, x2, y0, x3, y1, u1, v0, u2, v1, s);
        func_0015D338(self, item->color, x0, y2, x1, y3, u0, v1, u1, v2, s);
        func_0015D338(self, item->color, x2, y2, x3, y3, u1, v1, u2, v2, s);
        func_0015D338(self, item->color, x1, y0, x2, y1, u1, v0, u1, v1, s);
        func_0015D338(self, item->color, x1, y2, x2, y3, u1, v1, u1, v2, s);
        func_0015D338(self, item->color, x0, y1, x1, y2, u0, v1, u1, v1, s);
        func_0015D338(self, item->color, x2, y1, x3, y2, u1, v1, u2, v1, s);
        func_0015D338(self, item->color, x1, y1, x2, y2, u1, v1, u1, v1, s);
        func_0015C900(item->f0);
        self->disp->fnB((u8*)self + self->disp->offB, 0, s);
    }
}
