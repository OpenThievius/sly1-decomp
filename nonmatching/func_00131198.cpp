// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1255/1356 (92.6%), checked 2026-11-08
// NEAR: scheduling only, before the GIF packet: ours places the 0.171875 of InitCurveSpan (f20)
// above the SetTextPanelState call, with each loop constant one call earlier, and the
// `state = -1` store before `move a0`; retail starts them after the call (sw state in its delay
// slot), as if a block began there. The fonts, the compass loop and both band loops match (the
// x scale computed before EvalCurveSpan, the rest after it; one `step` local for both loops).
// Tried: state and child stores swapped, `step` declared earlier, t initialised in the for.
// Tried (order-class pass): step declared just before the loops, the child store after SetTextPanelState, the two stores swapped: 26 words or worse.
#include "common.h"
#include "screen_element.h"
#include "packet_writer.h"
#include "font.h"

struct SpanHead {
    f32 c0, c1, c2, c3;
} __attribute__((aligned(16)));
struct CurveSpan {
    SpanHead head;
    f32 len;
    f32 halfw;
    s32 lo;
    s32 mid;
    s32 hi;
    f32 p;
    f32 q;
};
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
extern PanelColor D_002610D0;
extern const char* D_00261128[8];
extern u8 D_00261148[];
extern f32 D_002610A0[4];
extern f32 D_002610B0[4];
extern f32 D_002610C0[4];
extern CurveSpan D_00261280;
extern CurveSpan D_002612B0;
extern CurveSpan D_002612E0;
extern f32 D_00261310;
void InitCurveSpan(CurveSpan* d, const SpanHead* src, s32 n, f32 x, f32 y);
f32 EvalCurveSpan(const CurveSpan* s, s32 x);
void ClearTextPanel(T217D_440* self);
void SetTextPanelState(T217D_440* self, s32 mode);
void BeginGifTag(PacketWriter* gs, s32 a, s32 b, u64 c);
void AddGifRgbaEntry(PacketWriter* gs, u32 c);
void AddGifXyzfNoDrawEntry(PacketWriter* gs, s32 x, s32 y, s32 a3, s32 a4);
void AddGifXyzfEntry(PacketWriter* gs, s32 x, s32 y, s32 a3, s32 a4);
void SetupScreenElementText(T217D_440* self);
s32 IsFontLoaded(s32 id);
Font* GetFontById(s32 id);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
void InitGifPacket(PacketWriter* gs);
void UsePacketBufferMemory(PacketWriter* gs, s32 n, void* mem);
void DetachPacketBufferCopy(PacketWriter* gs, void* a, s32 b, void* c, s32 d);
void AddGifRegisterWrite(PacketWriter* gs, s32 reg, u64 value);
f32 MeasureFontString(Font* font, const char* text);

// Sets a text panel up: its two fonts, the widest compass point, and the GS packet of the two
// curved bands drawn behind it.
void SetupTextPanel(T217D_440* self)
{
    SetupScreenElementText(self);
    ClearTextPanel(self);
    f32 sy = 0.8f;
    Font* small = self->font->Clone(0.7f, sy);
    self->smallFont = small;
    small->f30 = 1;
    small->f38 = 0x3F001;
    self->font = self->font->Clone(0.75f, sy);
    if (IsFontLoaded(2) != 0) {
        self->frame = (Font**)&D_00261148;
        *self->frame = GetFontById(2);
    }
    D_00261310 = MeasureFontString(self->smallFont, D_00261128[0]);
    for (u32 i = 1; i < 8; i++) {
        D_00261310 = MeasureFontString(self->smallFont, D_00261128[i]) >? D_00261310;
    }
    self->state = -1;
    self->child = 0;
    SetTextPanelState(self, 0);
    PushBackMemoryMark();
    f32 step = 1.0f / 24.0f;
    PacketWriter gs;
    InitGifPacket(&gs);
    UsePacketBufferMemory(&gs, 0x800, AllocateBackMemory(0x8000));
    BeginGifTag(&gs, 0, 3, 0x1EE);
    AddGifRegisterWrite(&gs, 0x47, 0x70000);
    AddGifRegisterWrite(&gs, 0x42, 0x44);
    PanelColor c = D_002610D0;
    c.a = 0x60;
    AddGifRgbaEntry(&gs, *(u32*)&c);
    BeginGifTag(&gs, 0x44, 1, 4);
    InitCurveSpan(&D_00261280, (const SpanHead*)D_002610A0, 0x18, 0.171875f, 40.0f);
    InitCurveSpan(&D_002612B0, (const SpanHead*)D_002610B0, 0x18, 0.171875f, -60.0f);
    InitCurveSpan(&D_002612E0, (const SpanHead*)D_002610C0, 0x18, 0.2857143f, 8.0f);
    s32 i;
    f32 t;
    AddGifXyzfNoDrawEntry(&gs, 0x6C00, 0x7900, 0x0FFFFFF0, 0);
    AddGifXyzfNoDrawEntry(&gs, 0x6C00, 0x7B45, 0x0FFFFFF0, 0);
    for (i = 1, t = step; i < 24; i++) {
        f32 u = t * 640.0f;
        f32 y = EvalCurveSpan(&D_00261280, i);
        t += step;
        s32 x = (s32)((u + 1728.0f) * 16.0f);
        AddGifXyzfEntry(&gs, x, 0x7900, 0x0FFFFFF0, 0);
        AddGifXyzfEntry(&gs, x, (s32)((y * 0.45454547f + 1936.0f) * 16.0f), 0x0FFFFFF0, 0);
    }
    AddGifXyzfEntry(&gs, 0x9400, 0x7900, 0x0FFFFFF0, 0);
    AddGifXyzfEntry(&gs, 0x9400, 0x7B45, 0x0FFFFFF0, 0);
    AddGifXyzfNoDrawEntry(&gs, 0x6C00, 0x8700, 0x0FFFFFF0, 0);
    AddGifXyzfNoDrawEntry(&gs, 0x6C00, 0x80FA, 0x0FFFFFF0, 0);
    t = 1.0f / 24.0f;
    for (i = 1; i < 24; i++) {
        f32 u = t * 640.0f;
        f32 y = EvalCurveSpan(&D_002612B0, i);
        t += step;
        s32 x = (s32)((u + 1728.0f) * 16.0f);
        AddGifXyzfEntry(&gs, x, 0x8700, 0x0FFFFFF0, 0);
        AddGifXyzfEntry(&gs, x, (s32)((y * 0.45454547f + 1936.0f) * 16.0f), 0x0FFFFFF0, 0);
    }
    AddGifXyzfEntry(&gs, 0x9400, 0x8700, 0x0FFFFFF0, 0);
    AddGifXyzfEntry(&gs, 0x9400, 0x80FA, 0x0FFFFFF0, 0);
    DetachPacketBufferCopy(&gs, &self->bands, 0, &self->bandsSize, 0x15);
    PopBackMemoryMark();
}
