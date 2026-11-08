// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 670/1436 (46.7%), checked 2026-11-08
// NEAR (2026-11-08, night-sizex2): the same size as retail now (was 1448). The gauge loop's
// constants: retail keeps 1, 9, 60, 320 and the screen mapping's 1728, 16, 0.4545 and 1936 in
// f23..f31 and loads 1/9, 1/15, 55, 0.5 and 372.8 inside the loop. The loop pass (-dL) showed
// why ours moved 55 and 372.8 out: each was one pseudo used twice (life 5 and 4), which loop.c
// moves at 90 insns; one float temporary assigned 55 and then 372.8 is set twice in the loop,
// so neither is a movable and both stay, as retail's. The colour as a pointer chosen by an if
// (D_002610D8, else D_002610E0) and copied gives retail's bc1t over the second address. Still
// differs: retail also keeps the high halves of both colours' addresses in s4 and s3 (loop.c
// moved them; here only &D_002610D8 is kept, whole, in a saved register), so its frame is 16
// bytes larger and the saved registers and FPRs of the rest are numbered
// differently; the ternary, an if/else of pointers and a struct copy in each arm were tried.
#include "common.h"
#include "screen_element.h"
#include "packet_writer.h"
#include "font.h"
#include "pad_record.h"
#include "shapes.h"
#include "layout_137228.h"

struct PanelColor
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    PanelColor() {}
    PanelColor(const PanelColor& o) { *this = o; }
    PanelColor(u8 r_, u8 g_, u8 b_, u8 a_) : r(r_), g(g_), b(b_), a(a_) {}
};
struct CenterFrameMath {
    static s32 ScreenX(f32 x)
    {
        return (s32)((x + 1728.0f) * 16.0f);
    }
    static s32 ScreenY(f32 y)
    {
        return (s32)((y * 0.45454547f + 1936.0f) * 16.0f);
    }
};
struct CameraHeading { u8 pad0[0x40]; s32 f40[4]; u8 pad[0x468 - 0x50]; f32 heading; u8 pad46C[0x478 - 0x46C]; f32 f478; };
extern s32 g_padRouting;
extern CameraHeading* g_camera;
extern PadRecord g_blankPadRecord;
extern PanelColor D_002610D8;
extern PanelColor D_002610E0;
void BeginGifTag(PacketWriter* gs, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* gs, s32 reg, u64 value);
void AddGifRgbaEntry(PacketWriter* gs, u32 color);
void AddGifXyzfNoDrawEntry(PacketWriter* gs, s32 x, s32 y, s32 z, s32 f);
void AddGifXyzfEntry(PacketWriter* gs, s32 x, s32 y, s32 z, s32 f);
void PushFontScale(Font* font, f32 x, f32 y);
void PopFontScale(Font* font);
void DrawFontString(Font* font, const char* text, Layout_137228* layout, s32 zero, PacketWriter* gs);
s32 FormatToString(void* dst, const char* fmt, ...);
Font* GetFontById(s32 id);
extern s32 D_00261090[4];

// The panel's control labels: eight bands of the zoom gauge (lit up to the camera's zoom), and in
// state 1 the two button glyphs (larger while held) with "Move" and "Zoom" beside them.
void DrawTextPanelControlLabels(T217D_440* self, PacketWriter* gs)
{
    BeginGifTag(gs, 0, 1, 0xE);
    AddGifRegisterWrite(gs, 0x47, 0x31001);
    AddGifRegisterWrite(gs, 0x42, 0x44);
    f32 one = 1.0f;
    f32 inset = 9.0f;
    f32 height = 60.0f;
    f32 center = 320.0f;
    BeginGifTag(gs, 0x84, 5, 0x44441);
    for (s32 i = 0; i < 8; i++) {
        f32 lo = (f32)i * (1.0f / 9.0f);
        f32 hi = lo + 1.0f / 15.0f;
        f32 k = 55.0f;
        f32 x0 = (one - lo) * k - inset;
        f32 x1 = ((one - hi) * k + one) - inset;
        k = 372.800018f;
        f32 y0 = k - lo * height;
        f32 y1 = k - hi * height;
        const PanelColor* src = &D_002610D8;
        if (!((lo + hi) * 0.5f <= g_camera->f478)) {
            src = &D_002610E0;
        }
        PanelColor c = *src;
        AddGifRgbaEntry(gs, *(u32*)&c);
        s32 sy0 = CenterFrameMath::ScreenY(y0);
        AddGifXyzfNoDrawEntry(gs, CenterFrameMath::ScreenX(center - x0), sy0, 0, 0);
        AddGifXyzfNoDrawEntry(gs, CenterFrameMath::ScreenX(x0 + center), sy0, 0, 0);
        s32 sy1 = CenterFrameMath::ScreenY(y1);
        AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(center - x1), sy1, 0, 0);
        AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(x1 + center), sy1, 0, 0);
    }
    if (self->state != 1) {
        return;
    }
    Layout_137228 L;
    f32 row = 390.800018f;
    L.Pos(0.0f, 0.0f);
    L.Size(640.0f, 492.800018f);
    {
        Quad4 col;
        col.w[0] = 0xFF808080;
        L.Color(col.w);
    }
    L.SetF14(0);
    L.SetF18(0);
    PadRecord* pad = (g_padRouting & 2) ? &g_padRecord : &g_blankPadRecord;
    Font* glyphs = GetFontById(1);
    Font* text = GetFontById(0);
    char buf[16];
    FormatToString(buf, "%c", 0x28);
    L.f18 = (void*)1;
    L.f14 = 1;
    L.w = 0.0f;
    L.h = 0.0f;
    f32 s = 0.4f;
    if (self->open != 0 && pad->f48 != 0.0f) {
        s = 0.5f;
    }
    PushFontScale(glyphs, s, s);
    L.x = 265.0f;
    L.y = row;
    DrawFontString(glyphs, buf, &L, 0, gs);
    PopFontScale(glyphs);
    FormatToString(buf, "%c", 0x29);
    s = 0.4f;
    if (self->open != 0 && pad->f7C != 0.0f) {
        s = 0.5f;
    }
    PushFontScale(glyphs, s, s);
    L.x = 375.0f;
    L.y = row;
    DrawFontString(glyphs, buf, &L, 0, gs);
    PopFontScale(glyphs);
    PushFontScale(text, 0.6f, 0.6f);
    *(PanelColor*)&L.color = PanelColor(0x32, 0x84, 0xB0, 0x80);
    L.f14 = 2;
    L.x = (f32)(320 - D_00261090[0]);
    L.y = row;
    DrawFontString(text, "Move", &L, 0, gs);
    L.f14 = 0;
    L.x = (f32)(D_00261090[0] + 320);
    L.y = row;
    DrawFontString(text, "Zoom", &L, 0, gs);
    PopFontScale(text);
}
