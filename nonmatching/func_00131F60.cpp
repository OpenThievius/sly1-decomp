// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1420/1436 (98.9%), checked 2026-11-10
// NEAR (2026-11-10, w15): instruction order, frame, saved registers and the state-1 half are
// retail's; what differs is one swap of $f2 and $f3 in the gauge loop's first block: retail's
// `hi` is $f3 and the scratch `d` (1/15, then (1 - lo) * 55, then 372.8) with the (1 - lo)
// temporary is $f2; ours the other way round. What w15 found: `d` holds the product too (so `d =
// 372.8` has an anti dependence on `x0 = d - inset` and sched1 issues it after x0, as retail's
// sched2 order shows, and global-alloc gives d $f2), and x1 is computed before x0 (sched1 then
// matches retail's order and the 16.0/y1 ranking of w11's notes is retail's). What is left is
// local-alloc's ranking (docs/toolchain/long-block-constants.md, "A scratch float in a loop"):
// hi's quantity (hi tied to hi * height: 12 refs, born at insn 9 of the block, dying at y1's sub,
// insn 22) is 36/26 against the (1 - lo) temporary's 8/6, so hi takes $f2 first. With y1's sub at
// insn 23 or later the temporary wins (written `y1` before `y0`, sched1 puts y1's sub last:
// $f2/$f3 become retail's), but y1 then lives 35 insns or less and global-alloc puts it before
// 16.0 (8/35 against 39/174, 16.0's life doubled by its REG_EQUIV), the other swap. Both hold
// only with one more insn in y1's life than ours has (or one fewer before hi in block 1):
// retail's loop has an insn ours lacks that reload or flow2 deletes. Not found.
// Earlier (w11): the colours as named constant pointers at the top of the loop body (g++ folds
// their uses, so each arm keeps its own %lo with a REG_EQUAL note and jump.c does not hoist an
// arm before reload, while the dead declarations make both %hi's anticipated, so PRE hoists
// them: retail's s4 and s3, its bc1t with D8 in the delay slot), the camera's zoom read before
// them (PRE places the three %hi's in first-appearance order), the screen-x conversion named
// before the screen-y one (loop.c moves 1728 and 16 first), the five layout setters in
// ScreenLayout::Reset with the colour copied into its own local, `char buf[16]` before the
// layout, the layout's first two words stored through a pointer (`lay`), the move colour
// before PushFontScale, and "Move"'s alignment stored through a reference made there. The
// scratch floats `d` and `k` (55 then 0.5) keep those constants in the loop as retail does
// (set more than once, loop.c does not move them).
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

struct ScreenLayout {
    static void Reset(Layout_137228* l, s32 color)
    {
        l->Pos(0.0f, 0.0f);
        l->Size(640.0f, 492.800018f);
        s32 c = color;
        l->Color(&c);
        l->SetF14(0);
        l->SetF18(0);
    }
};

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
        f32 zoom = g_camera->f478;
        const PanelColor* const lit = &D_002610D8;
        const PanelColor* const dim = &D_002610E0;
        f32 lo = (f32)i * (1.0f / 9.0f);
        f32 d = 1.0f / 15.0f;
        f32 hi = lo + d;
        f32 k = 55.0f;
        f32 x1 = ((one - hi) * k + one) - inset;
        d = (one - lo) * k;
        f32 x0 = d - inset;
        d = 372.800018f;
        f32 y0 = d - lo * height;
        f32 y1 = d - hi * height;
        k = 0.5f;
        const PanelColor* src;
        if ((lo + hi) * k <= zoom) {
            src = lit;
        } else {
            src = dim;
        }
        PanelColor c = *src;
        AddGifRgbaEntry(gs, *(u32*)&c);
        s32 sx0 = CenterFrameMath::ScreenX(center - x0);
        s32 sy0 = CenterFrameMath::ScreenY(y0);
        AddGifXyzfNoDrawEntry(gs, sx0, sy0, 0, 0);
        AddGifXyzfNoDrawEntry(gs, CenterFrameMath::ScreenX(x0 + center), sy0, 0, 0);
        s32 sy1 = CenterFrameMath::ScreenY(y1);
        AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(center - x1), sy1, 0, 0);
        AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(x1 + center), sy1, 0, 0);
    }
    if (self->state != 1) {
        return;
    }
    char buf[16];
    Layout_137228 L;
    f32 row = 390.800018f;
    ScreenLayout::Reset(&L, 0xFF808080);
    PadRecord* pad = (g_padRouting & 2) ? &g_padRecord : &g_blankPadRecord;
    Font* glyphs = GetFontById(1);
    Font* text = GetFontById(0);
    FormatToString(buf, "%c", 0x28);
    Layout_137228* lay = &L;
    lay->f14 = 1;
    lay->f18 = (void*)1;
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
    *(PanelColor*)&L.color = PanelColor(0x32, 0x84, 0xB0, 0x80);
    PushFontScale(text, 0.6f, 0.6f);
    Layout_137228& move = L;
    move.f14 = 2;
    L.x = (f32)(320 - D_00261090[0]);
    L.y = row;
    DrawFontString(text, "Move", &L, 0, gs);
    L.f14 = 0;
    L.x = (f32)(D_00261090[0] + 320);
    L.y = row;
    DrawFontString(text, "Zoom", &L, 0, gs);
    PopFontScale(text);
}
