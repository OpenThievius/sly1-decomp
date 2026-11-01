// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001ACEE0.cpp func_eu_001ACEE0 --unit src/main/001A8000.cpp
// Still differs: Gauge box with lerped bar colour and shaking glyph; 15 lines differ in last block only: retail loads f52C before f5A4 and schedules the 2-byte string stores after the rect stores.
// PAL: draws a gauge box (dark frame, a bar fading from red to grey), then one glyph over it that shakes while the timer runs.
// NEAR: 15 lines differ, last block only: retail stores the two string bytes (sb 0x30/0x31) after the rect stores and the text load, and loads f52C before f5A4.

struct Rgba_eu_1ACEE0 { u8 c[4]; };
struct Rect_eu_1ACEE0 { f32 x; f32 y; f32 w; f32 h; s32 f10; s32 f14; s32 f18; s32 f1C; };
struct VEnt_eu_1ACEE0 { s16 delta; s16 index; void (*fn)(void* self, f32 x, f32 y, s32 a, s32 b, void* c); };
struct Text_eu_1ACEE0 { u8 pad[0x4C]; VEnt_eu_1ACEE0* vtbl; };
struct Self_eu_1ACEE0 {
    u8 pad0[4]; Text_eu_1ACEE0* text;
    u8 pad1[0x51C - 8]; f32 f51C;
    u8 pad2[0x52C - 0x520]; f32 f52C; f32 f530;
    u8 pad3[0x57C - 0x534]; u8 f57C;
    u8 pad4[0x584 - 0x57D]; f32 f584; f32 f588; f32 f58C; f32 f590; f32 f594; f32 f598; f32 f59C; f32 f5A0; f32 f5A4;
};
struct Q3_eu_1ACEE0;
struct Clock_eu_1ACEE0 { f32 f0; f32 f4; f32 f8; f32 fC; f32 f10; };
struct Str2_eu_1ACEE0 { s8 c[2]; };

extern Q3_eu_1ACEE0 D_eu_0027DB10;

f32 func_001EA4B8(Q3_eu_1ACEE0* p, s32 a1, f32 f12, f32 f13, f32 f14);
void func_00137228(Rect_eu_1ACEE0* out, f32 x, f32 y);
void func_00137238(Rect_eu_1ACEE0* out, f32 x, f32 y);
void func_00137248(Rect_eu_1ACEE0* out, Rgba_eu_1ACEE0* value);
void func_00137260(Rect_eu_1ACEE0* out, s32 flag);
void func_00137268(Rect_eu_1ACEE0* out, s32 flag);
void func_eu_001374E0(Rect_eu_1ACEE0* out, s32 flag);
void func_0019DDA0(f32 x0, f32 y0, f32 x1, f32 y1, s32 r, s32 g, s32 b, s32 a, u8* d);
void func_0015C8B8(Text_eu_1ACEE0* handle, f32 a, f32 b);
void func_eu_0015C778(Text_eu_1ACEE0* handle, char* str, Rect_eu_1ACEE0* r, s32 zero, u8* d);
void func_0015C900(Text_eu_1ACEE0* handle);
f32 func_00205400(f32 x);
f32 func_00205210(f32 x);

static inline u8 Lerp_eu_1ACEE0(s32 a, s32 b, f32 t)
{
    if (a == b) return b;
    if (a < b) return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
    return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
}

void func_eu_001ACEE0(Self_eu_1ACEE0* self)
{

    Rect_eu_1ACEE0 out;
    Rgba_eu_1ACEE0 col;
    f32 t = 0.0f;
    s32 flag = 0;
    if (self->f58C != t) {
        f32 d = ((Clock_eu_1ACEE0*)&D_00261858)->f4 - self->f58C;
        if (d < 0.5f) t = 1.0f - (d + d);
        flag = d < 0.75f;
    }
    u32 grey = 0xFF808080;
    self->f584 = func_001EA4B8(&D_eu_0027DB10, 0, self->f584, self->f588, ((Clock_eu_1ACEE0*)&D_00261858)->f8);
    f32 y = self->f59C;
    f32 h = self->f584 * y;
    y -= h;
    f32 w = self->f598;
    func_00137228(&out, self->f52C + self->f590, self->f530 + self->f594);
    func_00137238(&out, w, y);
    *(u32*)&col = grey;
    func_00137248(&out, &col);
    func_00137260(&out, 0);
    func_00137268(&out, 0);
    func_eu_001374E0(&out, 0);
    col.c[0] = 0x20; col.c[1] = 0x20; col.c[2] = 0x20; col.c[3] = 0xC0;
    func_0019DDA0(out.x, out.y, out.x + out.w, out.y + out.h, 0x20, 0x20, 0x20, 0xC0, D_00262280);
    {
        out.x = self->f52C + self->f590;
        out.y = self->f530 + self->f594 + y;
        out.w = self->f598;
        out.h = h;
        Rgba_eu_1ACEE0 a, b, r;
        a.c[0] = 0x60; a.c[1] = 0; a.c[2] = 0; a.c[3] = 0xC0;
        b.c[0] = 0xC0; b.c[1] = 0xC0; b.c[2] = 0xC0; b.c[3] = 0xFF;
        r.c[0] = Lerp_eu_1ACEE0(a.c[0], b.c[0], t);
        r.c[1] = Lerp_eu_1ACEE0(a.c[1], b.c[1], t);
        r.c[2] = Lerp_eu_1ACEE0(a.c[2], b.c[2], t);
        r.c[3] = Lerp_eu_1ACEE0(a.c[3], b.c[3], t);
        col = r;
    }
    func_0019DDA0(out.x, out.y, out.x + out.w, out.y + out.h, col.c[0], col.c[1], col.c[2], col.c[3], D_00262280);
    func_0015C8B8(self->text, self->f51C, self->f51C);
    VEnt_eu_1ACEE0* ve = &self->text->vtbl[8];
    ve->fn((u8*)self->text + ve->delta, self->f52C, self->f530, 0x7A, out.f10, D_00262280);
    f32 dx = 0.0f;
    f32 dy = dx;
    if (flag) {
        dx = func_00205400(((Clock_eu_1ACEE0*)&D_00261858)->f10 * 40.0f) * 8.0f;
        dy = func_00205210(((Clock_eu_1ACEE0*)&D_00261858)->f10 * 15.0f) * 4.0f;
    }
    out.x = self->f52C + self->f5A0 + dx;
    out.y = self->f530 + self->f5A4 + dy;
    out.w = 0.0f;
    out.h = 0.0f;
    out.f18 = 1;
    out.f1C = 1;
    {
        Str2_eu_1ACEE0 s;
        s.c[0] = self->f57C + 0x72;
        s.c[1] = 0;
        *(Str2_eu_1ACEE0*)&col = s;
    }
    func_eu_0015C778(self->text, (char*)&col, &out, 0, D_00262280);
    func_0015C900(self->text);
}
