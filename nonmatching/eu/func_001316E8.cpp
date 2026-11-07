// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 2125/2224 (95.5%), checked 2026-11-07
// NEAR (only in PAL): python3 tools/check.py build/swarm/palA/func_001316E8.cpp func_001316E8 --version eu --unit src/main/text_panel.cpp
// Still differs: registers and spill slots only (about 33 lines of ~560): PAL keeps &L (sp+0x240) and
// &col (sp+0x260) in spill slots 0x2B0/0x2B4 with self in s6, prev/next strings in s7/s8; ours puts &L in s6,
// self in s7 and spills &sNext.
// PAL: the object's font and scroll position sit 0x28C later (0x59C, 0x5A0), and each compass
// letter is first built into a 0xC0-byte string object (func_eu_0015DD18) that is measured
// (func_eu_0015E438) and drawn (func_eu_0015E7E0).
struct Obj_eu_1316E8 {
    u8 pad0[0x59C];
    Font* font;
    f32 f5A0;
};

struct Str_eu_1316E8 {
    u8 bytes[0xC0];
};

void func_eu_0015DD18(Str_eu_1316E8* out, const char* text, Font* font, s32 zero);
f32 func_eu_0015E438(Str_eu_1316E8* str);
void func_eu_0015E7E0(Str_eu_1316E8* str, Layout_137228* layout, s32 zero, PacketWriter* gs);
void func_eu_001374E0(Layout_137228* layout, s32 value);

struct Gfx_eu_1316E8 {
    static s32 ScreenX(f32 x)
    {
        return (s32)((x + 1728.0f) * 16.0f);
    }

    static s32 ScreenY(f32 y)
    {
        return (s32)((y * 0.5462963f + 1920.0f) * 16.0f);
    }
};

void DrawCompassStrip(Obj_eu_1316E8* self, PacketWriter* gs)
{
    Str_eu_1316E8 sCur;
    Str_eu_1316E8 sPrev;
    Str_eu_1316E8 sNext;
    Layout_137228 L;
    s32 i;
    f32 left = 273.0f;
    f32 bottom = 42.181820f;
    f32 top = 8.0f;
    f32 span = 94.0f;
    f32 step = 0.1f;
    f32 tick = 7.52000046f;

    BeginGifTag(gs, 0x46, 6, 0x441EEE);
    AddGifRegisterWrite(gs, 0x47, 0x31001);
    AddGifRegisterWrite(gs, 0x42, 0x5A);
    AddGifRegisterWrite(gs, 0x40, 0x160004016E0111);
    AddGifRgbaEntry(gs, 0);
    AddGifXyzfEntry(gs, 0x7D10, 0x7845, 0, 0);
    AddGifXyzfEntry(gs, 0x82F0, 0x7970, 0, 0);
    BeginGifTag(gs, 0x43, 4, 0x4441);
    AddGifRgbaEntry(gs, 0x80000000);
    AddGifXyzfEntry(gs, 0x7D10, 0x7845, 0, 0);
    AddGifXyzfEntry(gs, 0x82F0, 0x7845, 0, 0);
    AddGifXyzfEntry(gs, 0x8000, 0x7970, 0, 0);
    BeginGifTag(gs, 0, 3, 0x1EE);
    AddGifRegisterWrite(gs, 0x47, 0x3F001);
    AddGifRegisterWrite(gs, 0x42, 0x44);
    AddGifRgbaEntry(gs, *(u32*)&D_002610E0);
    BeginGifTag(gs, 0x84, 1, 4);

    for (i = 0; i < 11; i++) {
        f32 x = left + ((f32)i - self->f5A0) * step * span;
        s32 x0 = Gfx_eu_1316E8::ScreenX(x);
        x += tick;
        AddGifXyzfNoDrawEntry(gs, x0, Gfx_eu_1316E8::ScreenY(top), 0, 0);
        s32 x1 = Gfx_eu_1316E8::ScreenX(x);
        AddGifXyzfNoDrawEntry(gs, x1, Gfx_eu_1316E8::ScreenY(top), 0, 0);
        s32 y = Gfx_eu_1316E8::ScreenY(bottom);
        AddGifXyzfEntry(gs, x0, y, 0, 0);
        AddGifXyzfEntry(gs, x1, y, 0, 0);
    }

    s32 grey = 0xFF808080;
    f32 half = 0.5f;
    f32 row = 6.0f;
    f32 a = WrapModulo(g_camera->heading + 0.39269909f, 6.2831855f);
    f32 w = D_00261310 + 4.0f;
    s32 cur = (s32)(a / 0.78539819f);
    s32 prev = (cur + 7) & 7;
    s32 next = (cur + 1) & 7;
    f32 frac = WrapModulo(a, 0.78539819f) / 0.78539819f;
    func_eu_0015DD18(&sCur, D_00261128[cur], self->font, 0);
    func_eu_0015DD18(&sPrev, D_00261128[prev], self->font, 0);
    func_eu_0015DD18(&sNext, D_00261128[next], self->font, 0);
    f32 wCur = func_eu_0015E438(&sCur);
    f32 off = frac * w;
    f32 wPrev = func_eu_0015E438(&sPrev);
    f32 wNext = func_eu_0015E438(&sNext);
    f32 hPrev = (w - wPrev) * half;
    f32 hCur = (w - wCur) * half;
    f32 hNext = (w - wNext) * half;
    f32 xCur = 320.0f - (off - hCur);
    f32 xPrev = (320.0f - w) - (off - hPrev);
    f32 xNext = (w + 320.0f) - (off - hNext);

    L.Pos(0.0f, 0.0f);
    L.Size(640.0f, 468.610168f);
    {
        Quad4 col;
        col.w[0] = grey;
        L.Color(col.w);
    }
    L.SetF14(0);
    L.SetF18(0);
    func_eu_001374E0(&L, 0);

    L.h = (f32)self->font->height * self->font->sy;
    L.w = D_00261310;
    *(PanelColor*)&L.color = PanelColor(D_002610D8);
    L.x = xPrev;
    L.y = row;
    func_eu_0015E7E0(&sPrev, &L, 0, gs);
    L.x = xNext;
    L.y = row;
    func_eu_0015E7E0(&sNext, &L, 0, gs);

    {
        SpanHead q = { 0.0f, 4.0f, -4.0f };
        f32 t = q.c0 + frac * (q.c1 + frac * q.c2);
        *(PanelColor*)&L.color = BorderColorMix::Mix(D_002610D8, PanelColor(0x32, 0x84, 0xB0, 0x80), t);
    }
    L.x = xCur;
    L.y = row;
    func_eu_0015E7E0(&sCur, &L, 0, gs);

    BeginGifTag(gs, 0, 1, 0xE);
    AddGifRegisterWrite(gs, 0x40, 0xFF0000027F0000);
}
