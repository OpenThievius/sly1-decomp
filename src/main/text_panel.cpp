// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"

#include "list_iter.h"
#pragma implementation "layout_137228.h"
#include "layout_137228.h"
#include "screen_element.h"
#include "step_sequence.h"
#include "packet_writer.h"
#include "font.h"
#include "shapes.h"
#include "pad_record.h"
#include "game_progress.h"
#include "world.h"

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

void SetTextPanelSubject(T217D_440* self, s32 arg);

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

f32 Cosine(f32 x);
void BeginGifTag(PacketWriter* gs, s32 a, s32 b, u64 c);
void AddGifRgbaEntry(PacketWriter* gs, u32 c);
void AddGifXyzfNoDrawEntry(PacketWriter* gs, s32 x, s32 y, s32 a3, s32 a4);
void AddGifXyzfEntry(PacketWriter* gs, s32 x, s32 y, s32 a3, s32 a4);

struct BorderColorMix
{
    static s32 Channel(s32 a, s32 b, f32 t)
    {
        if (a == b)
        {
            return b;
        }
        if (a < b)
        {
            return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
        }
        return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
    }

    static PanelColor Mix(PanelColor a, PanelColor b, f32 t)
    {
        PanelColor c;
        c.r = Channel(a.r, b.r, t);
        c.g = Channel(a.g, b.g, t);
        c.b = Channel(a.b, b.b, t);
        c.a = Channel(a.a, b.a, t);
        return c;
    }
};


struct CameraHeading { u8 pad[0x468]; f32 heading; u8 pad46C[0x478 - 0x46C]; f32 f478; };

extern s32 g_padRouting;
extern f32 g_frameDt;
extern CameraHeading* g_camera;

void BeginGifTag(PacketWriter* gs, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* gs, s32 reg, u64 value);
void AddGifRgbaEntry(PacketWriter* gs, u32 color);
void AddGifXyzfNoDrawEntry(PacketWriter* gs, s32 x, s32 y, s32 z, s32 f);
void AddGifXyzfEntry(PacketWriter* gs, s32 x, s32 y, s32 z, s32 f);
f32 WrapAngle(f32 a);
f32 Cosine(f32 a);
void GetTextPanelCenter(T217D_440* self, f32* x, f32* y);

struct CenterFrameMath {
    static s32 LerpU8(s32 a, s32 b, f32 t)
    {
        if (a == b) {
            return b;
        }
        if (a < b) {
            return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
        }
        return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
    }

    static PanelColor Lerp(PanelColor a, PanelColor b, f32 t)
    {
        PanelColor r;
        r.r = LerpU8(a.r, b.r, t);
        r.g = LerpU8(a.g, b.g, t);
        r.b = LerpU8(a.b, b.b, t);
        r.a = LerpU8(a.a, b.a, t);
        return r;
    }

    static f32 Wave(f32 x, f32 period, f32 phase)
    {
        return Cosine(phase + (x / period) * 2.0f * 3.1415927f);
    }

    static s32 ScreenX(f32 x)
    {
        return (s32)((x + 1728.0f) * 16.0f);
    }

    static s32 ScreenY(f32 y)
    {
        return (s32)((y * 0.45454547f + 1936.0f) * 16.0f);
    }
};

void ResetScreenElement(void* self);
s32 SetStepSequenceState(void* obj, s32 mode);

void SetTextPanelState(T217D_440* self, s32 mode);
void SetStepSequenceState(StepSequence* obj, s32 mode);

struct SortEntry {
    void* obj;
    f32 key;
};

s32 IsObjectAttached(void* obj);

void GetNumberedItemFlag(void* obj, s32* out);

void RemoveEffect(void* handle);
void SetEffectPhase(void* handle, s32 mode);
void* FillMemory(void* block, s32 value, s32 size);

// func_00136FA8 keeps its own view: it uses the result of func_001356C0, which returns nothing.
struct Owner_136FA8 { u8 pad0[0x324]; void* child; };

s32 SetTextPanelState(Owner_136FA8* self, s32 mode);

// Newly matched US functions from the small-function wave.
extern void CloseBufferedStream(void*);
extern void FreeObjectMemory(void*);
extern void ReadBufferedStreamBytes(void*, s32, void*);

struct PercentClamp {
    static void Set(T217D_440* self, f32 x, f32 lo, f32 hi) {
        if (x < lo) x = lo;
        else if (hi < x) x = hi;
        self->value = x;
    }
};

extern f32 g_gameTime;

Font* InitTextReader(void* out, void* p, Font* font);
s32 CountTextChars(void* self);

extern f32 g_gameClock[];

struct TextScratch {
    u8 bytes[0xB0];
};

s32 GetStringLength(const char* s);
void* CopyString(void* dst, const char* src);
void PushFontScale(Font* font, f32 x, f32 y);
s32 WrapTextLines(void* buf, f32 x);
void PopFontScale(Font* font);
void RewindTextReader(void* buf);
s32 ReadTextChar(void* buf);

struct __attribute__((packed)) Tail_1356C0 { u8 pad0[0x464]; s32 v; };
extern f32 g_gameTime;

void ClearTextPanel(T217D_440* self);
void StartSoundEffect(s32 a, s32 b, s32 c, s32 d, f32 g, f32 h, f32 i, f32 j, f32 k, s32 e, s32 f);

extern u8 g_currentWorld[];
extern u8 func_00135E20[];
extern u8 func_00135E40[];



// The bit of the current level GetCurrentLevelBit (func_00160D30) gives back.
struct LevelBit { s32 v; };
void GetCurrentLevelBit(LevelBit* p);
s32 MaskWorldBitsBySave(void);
void CollectPanelEntriesOfClass(T217D_440* self, s32 a1, void* a2, void* a3, s32 a4, s32 a5, f32 f);

struct StickLimits { u64 a __attribute__((packed)); u32 b; };
typedef u64 Quad_136040 __attribute__((mode(TI)));
struct __attribute__((aligned(16))) Vec_136040 { f32 x, y, z, w; };

extern const StickLimits D_00249D00;
extern const StickLimits D_00249D10;

Quad_136040 ApproachPointWithRamp(Quad_136040 a, Quad_136040 b, StickLimits* c, s32 d, f32 f12);
f32 WrapModulo(f32 x, f32 y);
void RefreshPanelEntries(T217D_440* self, PadRecord* p);

struct __attribute__((aligned(16))) PanelEntryPosition { s32 a, b, c, d; };
struct PanelEntrySource { char pad[0x140]; PanelEntryPosition v; };


void ComputeHullSeenFromCamera(PanelEntryPosition* v, s32 mode);

struct PlayerListHolder { u8 pad0[0x6C]; List01 list; };

struct ListWalkNext {
    static AnimationPlayer* Of(ListFrame* it)
    {
        AnimationPlayer* obj = *(AnimationPlayer**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct ListWalkBegin {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = (ListFrame*)it;
    }
};

PlayerListHolder* FindFirstObjectById(World* host, s32 a1, s32 a2, void* ctx);
void SetAnimationPlayerSpeed(AnimationPlayer* item, f32 x);


extern u8 g_currentWorld[];

void ResumeStreamVoice(void);
void PauseStreamVoice(void);
void GetCurrentLevelBit(LevelBit* p);
s32 MaskWorldBitsBySave(void);
void ReleasePanelEntries(T217D_440* self, s32 state, s32 flag);
s32 GatherObjectsById(s32 a, s32 b, s32 c, void* d, s32 e, void* f);
void ResetTextPointToHalf(void* p);

struct ClampBelow { static s32 Of(s32 a, s32 b) { if (b - 1 < a) return b; return a; } };

void GetCurrentLevelBit(u32* out);
void func_00134B48(T217D_440* self, PacketWriter* q);
f32 Cosine(f32 x);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, f32* p, s32 zero);
void BeginGifTag(PacketWriter* q, s32 a, s32 b, u64 c);
void AddGifRgbaEntry(PacketWriter* q, u32 v);
void AddGifXyzfEntry(PacketWriter* q, s32 a, s32 b, s32 c, s32 d);

// The file's .data, in retail's order from 0x261090. The colours and the two styles are built
// by the static initialiser (func_00136FE8); their bytes are zero until then.
struct PanelStyle {
    s32 f0;
    u8 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u32 f18;
    PanelStyle(f32 w)
    {
        FillMemory(this, 0, 0x1C);
        f4 = 0x2D;
        f8 = w;
        f10 = 0.3f;
        f14 = 0.3f;
        f18 = 0xFF7D4B00;
    }
    PanelStyle(s32 w, s32 h)
    {
        FillMemory(this, 0, 0x1C);
        f4 = 0x2D;
        f8 = w;
        fC = h;
        f14 = f10 = 0.3f;
        f18 = 0xFF7D4B00;
    }
};

s32 D_00261090[4] = { 75, 0, 0, 0 };
f32 D_002610A0[4] = { 80.0f, -288.0f, 288.0f, 0.0f };
f32 D_002610B0[4] = { 280.800018f, 376.0f, -376.0f, 0.0f };
f32 D_002610C0[4] = { -8.0f, -40.0f, 40.0f, 0.0f };
PanelColor D_002610D0(0x00, 0x00, 0x00, 0x80);
PanelColor D_002610D8(0x00, 0x52, 0x7E, 0x80);
PanelColor D_002610E0(0x19, 0x1E, 0x6E, 0x80);
PanelColor D_002610E8(0x7E, 0x28, 0x0A, 0x80);
PanelColor D_002610F0(0x50, 0x28, 0x28, 0x80);
PanelColor D_002610F8(0xF0, 0xF0, 0x00, 0x80);
PanelColor D_00261100(0x28, 0x28, 0x00, 0x80);
PanelColor D_00261108(0xFF, 0xFF, 0xFF, 0x80);
PanelColor D_00261110(0xE6, 0xE6, 0xE6, 0x80);
PanelColor D_00261118(0x2F, 0x72, 0x3E, 0x80);
s32 D_00261120[2] = { -268435456, -268435456 };
// The eight compass points, read by func_00131198 and func_001316E8.
const char* D_00261128[8] = { "N", "NW", "W", "SW", "S", "SE", "E", "NE" };
PanelStyle D_00261148(2.0f);
PanelStyle D_00261168(32, 16);
f32 D_00261184 = 1.0f;
f32 D_00261188 = 0.5f;
f32 D_00261190[4] = { 0.0f, 0.300000012f, 0.0f, 0.0f };
f32 D_002611A0[4] = { 1.5f, -1.5f, 0.0f, 0.0f };
f32 D_002611B0[3] = { 5.0f, 0.0f, 0.100000001f };
f32 D_002611BC = 0.5f;
f32 D_002611C0[3] = { 5.0f, 0.0f, 0.100000001f };
f32 D_002611CC = 250.0f;
f32 D_002611D0 = 40.0f;
f32 D_002611D4 = -20.0f;
f32 D_002611D8 = -15.0f;
f32 D_002611DC = 1.0f;
f32 D_002611E0[4][4] = {
    { -5.0f, -15.0f, -35.0f, -15.0f },
    { 5.0f, 15.0f, 35.0f, 15.0f },
    { 0.0f, 10.0f, 0.0f, -10.0f },
    { 0.0f, -10.0f, 0.0f, 10.0f },
};
f32 D_00261220[4][4] = {
    { 0.0f, -11.0f, 0.0f, 11.0f },
    { 0.0f, 11.0f, 0.0f, -11.0f },
    { -4.4f, -15.4f, -35.2f, -15.4f },
    { 4.4f, 15.4f, 35.2f, 15.4f },
};
f32 D_00261260[2] = { 8.0f, 0.0f };
f32 D_00261268[3] = { 8.0f, 0.0f, 0.150000006f };
f32 D_00261274 = 0.25f;
CurveSpan D_00261280;
CurveSpan D_002612B0;
CurveSpan D_002612E0;
f32 D_00261310;

void InitCurveSpan(CurveSpan* d, const SpanHead* src, s32 n, f32 x, f32 y);
f32 EvalCurveSpan(const CurveSpan* s, s32 x);
void InitTextPanel(T217D_440* self, s32 a1);
void ClearTextPanel(T217D_440* self);
void DrawTextPanelCenterFrame(T217D_440* self, PacketWriter* gs);
void DrawTextPanelBorders(T217D_440* self, PacketWriter* gs);
void DrawTextPanelBlocks(T217D_440* self, PacketWriter* q);
void SetTextPanelMode(T217D_440* self, s32 value);
void SetTextPanelState(T217D_440* self, s32 mode);
s32 CompareEntriesByAttachedKey(SortEntry* a, SortEntry* b);
s32 CompareEntriesFlaggedLast(SortEntry* a, SortEntry* b);
void ReadPanelEntryPosition(PanelEntrySource* self, PanelEntryPosition* out, s32* flag);
void ReadAdjustedPanelEntryPosition(PanelEntrySource* self, s32 unused, PanelEntryPosition* out);
void ReleasePanelEntries(T217D_440* self, s32 state, s32 flag);
void RefreshPanelEntries(T217D_440* self);
void UpdatePanelStick(T217D_440* self, PadRecord* p);
void SetTextPanelOpen(T217D_440* self, s32 on);
void ResetTextPanel(T217D_440* self);
void SetTextPanelText(T217D_440* self, const char* name);
s32 IsTextPanelTextTyped(T217D_440* self);
void SetTextPanelSubject(T217D_440* self, s32 value);
void SetTextPanelValuePercent(T217D_440* self, f32 value);
f32 GetTextPanelSlideInTime(T217D_440* self);
f32 GetTextPanelSlideOutTime(T217D_440* s);
void GetTextPanelCenter(T217D_440* self, f32* x, f32* y);
void ChooseTextPanelState(T217D_440* self);
s32 EndTextPanelState(Owner_136FA8* self);

void InitCurveSpan(CurveSpan* d, const SpanHead* src, s32 n, f32 x, f32 y)
{
    f32 fn = (f32)n;
    f32 inv = 1.0f / fn;
    s32 half = n / 2;
    s32 t;
    s32 lo;
    f32 u;

    d->head = *src;
    d->len = fn;
    d->mid = half;
    t = (s32)(x / inv) >> 1;
    d->hi = half + t;
    d->halfw = (f32)t;
    lo = half - t;
    d->lo = lo;
    u = (f32)lo / fn;
    d->p = src->c0 + u * (src->c1 + u * src->c2);
    d->q = src->c0 + 0.5f * (src->c1 + 0.5f * src->c2) + y;
}

f32 EvalCurveSpan(const CurveSpan* s, s32 x)
{
    if (x < s->lo || s->hi < x) {
        f32 u = (f32)x / s->len;
        return s->head.c0 + u * (s->head.c1 + u * s->head.c2);
    }
    if (x == s->lo || x == s->hi) {
        return s->p;
    }
    if (x < s->mid) {
        f32 t = (f32)(x - s->lo) / s->halfw;
        return (1.0f - t) * s->p + t * s->q;
    }
    if (s->mid < x) {
        f32 t = (f32)(x - s->mid) / s->halfw;
        return (1.0f - t) * s->q + t * s->p;
    }
    return s->q;
}

void InitTextPanel(T217D_440* self, s32 a1)
{
    self->w = 640.0f;
    self->h = 492.800018f;
    self->charsPerSecond = 15.0f;
    self->highlight = 0x80FFFFFF;
    InitScreenElement(self, a1);
}

void ClearTextPanel(T217D_440* self)
{
    self->vt->m08(self, 0);
    SetTextPanelSubject(self, 0);
    self->value = 0;
    self->stickX = 0;
    self->stickY = 0;
    self->f314 = 0.4f;
}

INCLUDE_ASM(func_00131198);




struct PanelFont {
    static Font* Of(T217D_440* self) { return *(Font**)((u8*)self + 0x310); }
};

f32 MeasureFontString(Font* font, const char* text);
void DrawFontString(Font* font, const char* text, Layout_137228* layout, s32 zero, PacketWriter* gs);

void DrawCompassStrip(T217D_440* self, PacketWriter* gs)
{
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
    AddGifRegisterWrite(gs, 0x40, 0x120003016E0111);
    AddGifRgbaEntry(gs, 0);
    AddGifXyzfEntry(gs, 0x7D10, 0x793A, 0, 0);
    AddGifXyzfEntry(gs, 0x82F0, 0x7A32, 0, 0);
    BeginGifTag(gs, 0x43, 4, 0x4441);
    AddGifRgbaEntry(gs, 0x80000000);
    AddGifXyzfEntry(gs, 0x7D10, 0x793A, 0, 0);
    AddGifXyzfEntry(gs, 0x82F0, 0x793A, 0, 0);
    AddGifXyzfEntry(gs, 0x8000, 0x7A32, 0, 0);
    BeginGifTag(gs, 0, 3, 0x1EE);
    AddGifRegisterWrite(gs, 0x47, 0x3F001);
    AddGifRegisterWrite(gs, 0x42, 0x44);
    AddGifRgbaEntry(gs, *(u32*)&D_002610E0);
    BeginGifTag(gs, 0x84, 1, 4);

    for (i = 0; i < 11; i++) {
        f32 x = left + ((f32)i - self->f314) * step * span;
        s32 x0 = CenterFrameMath::ScreenX(x);
        x += tick;
        AddGifXyzfNoDrawEntry(gs, x0, CenterFrameMath::ScreenY(top), 0, 0);
        s32 x1 = CenterFrameMath::ScreenX(x);
        AddGifXyzfNoDrawEntry(gs, x1, CenterFrameMath::ScreenY(top), 0, 0);
        s32 y = CenterFrameMath::ScreenY(bottom);
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
    Font* font;
    f32 wCur = MeasureFontString(PanelFont::Of(self), D_00261128[cur]);
    f32 off = frac * w;
    f32 wPrev = MeasureFontString(PanelFont::Of(self), D_00261128[prev]);
    f32 wNext = MeasureFontString(PanelFont::Of(self), D_00261128[next]);
    f32 hPrev = (w - wPrev) * half;
    f32 hCur = (w - wCur) * half;
    f32 hNext = (w - wNext) * half;
    f32 xCur = 320.0f - (off - hCur);
    f32 xPrev = (320.0f - w) - (off - hPrev);
    f32 xNext = (w + 320.0f) - (off - hNext);

    L.Pos(0.0f, 0.0f);
    L.Size(640.0f, 492.800018f);
    {
        Quad4 col;
        col.w[0] = grey;
        L.Color(col.w);
    }
    L.SetF14(0);
    L.SetF18(0);

    font = PanelFont::Of(self);
    L.h = (f32)font->height * font->sy;
    L.w = D_00261310;
    *(PanelColor*)&L.color = PanelColor(D_002610D8);
    L.x = xPrev;
    L.y = row;
    DrawFontString(PanelFont::Of(self), D_00261128[prev], &L, 0, gs);
    L.x = xNext;
    L.y = row;
    DrawFontString(PanelFont::Of(self), D_00261128[next], &L, 0, gs);

    {
        SpanHead q = { 0.0f, 4.0f, -4.0f };
        f32 t = q.c0 + frac * (q.c1 + frac * q.c2);
        *(PanelColor*)&L.color = BorderColorMix::Mix(D_002610D8, PanelColor(0x32, 0x84, 0xB0, 0x80), t);
    }
    L.x = xCur;
    L.y = row;
    DrawFontString(PanelFont::Of(self), D_00261128[cur], &L, 0, gs);

    BeginGifTag(gs, 0, 1, 0xE);
    AddGifRegisterWrite(gs, 0x40, 0xDF0000027F0000);
}


INCLUDE_RODATA(D_00249CE0);
INCLUDE_RODATA(D_00249CE8);
INCLUDE_RODATA(D_00249CF0);
INCLUDE_ASM(func_00131F60);

void DrawTextPanelCenterFrame(T217D_440* self, PacketWriter* gs)
{
    PanelColor c0;
    PanelColor c1;
    f32 k;
    PadRecord* pad;
    u8 alpha;
    f32 posX;
    f32 posY;
    f32 scale;
    f32 offX;
    f32 offY;

    BeginGifTag(gs, 0, 1, 0xE);
    AddGifRegisterWrite(gs, 0x47, 0x31001);
    AddGifRegisterWrite(gs, 0x42, 0x44);
    AddGifRegisterWrite(gs, 0x40, 0xA90003027F0000);

    pad = (g_padRouting & 2) ? &g_padRecord : &g_blankPadRecord;
    k = 3.0f;
    if (0.0f < pad->f78) {
        k = 6.0f;
    } else if (pad->f78 < 0.0f) {
        k = -6.0f;
    }
    self->spin = WrapAngle(self->spin + g_frameDt * k);

    alpha = (s32)(g_camera->f478 * 24.999f) + 0x30;
    switch (self->palette) {
    case 0:
        if (self->state == 5) {
            PanelColor t = D_00261110;
            t.a = alpha;
            c0 = t;
            t = D_00261108;
            t.a = alpha;
            c1 = t;
        } else {
            PanelColor t = (*(PanelColor*)&D_002610E0);
            t.a = alpha;
            c0 = t;
            t = (*(PanelColor*)&D_002610D8);
            t.a = alpha;
            c1 = t;
        }
        break;
    case 1: {
        PanelColor t = D_00261100;
        t.a = alpha;
        c0 = t;
        t = D_002610F8;
        t.a = alpha;
        c1 = t;
        break;
    }
    case 2: {
        PanelColor t = D_002610F0;
        t.a = alpha;
        c0 = t;
        t = D_002610E8;
        t.a = alpha;
        c1 = t;
        break;
    }
    }

    GetTextPanelCenter(self, &posX, &posY);
    scale = g_camera->f478 + 1.0f;

    {
        f32 step = 1.0f / 24.0f;
        f32 period = 256.0f;
        f32 wide = 512.0f;
        f32 s = CenterFrameMath::Wave(-8.0f, period, self->spin);
        PanelColor colA = CenterFrameMath::Lerp(c0, c1, 0.5f - s * 0.5f);
        s = CenterFrameMath::Wave(-18.0f, period, self->spin);
        PanelColor colB = CenterFrameMath::Lerp(c0, c1, 0.5f - s * 0.5f);
        f32 x0 = posX - scale * 35.0f;
        f32 x1 = x0 + scale * 70.0f;
        f32 u;
        s32 i;

        BeginGifTag(gs, 0x4C, 2, 0x41);

        AddGifRgbaEntry(gs, *(u32*)&colB);
        AddGifXyzfNoDrawEntry(gs, CenterFrameMath::ScreenX(x0), CenterFrameMath::ScreenY(posY + scale * -8.0f), 0, 0);
        AddGifRgbaEntry(gs, *(u32*)&colA);
        AddGifXyzfNoDrawEntry(gs, CenterFrameMath::ScreenX(x0), CenterFrameMath::ScreenY(posY + scale * -3.0f), 0, 0);
        u = step;
        for (i = 1; i < 24; i++) {
            f32 x = x0 + scale * u * 70.0f;
            f32 y;
            f32 y2;
            u += step;
            y = posY + scale * EvalCurveSpan(&D_002612E0, i);
            y2 = y + scale * 5.0f;
            AddGifRgbaEntry(gs, *(u32*)&colB);
            AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(x), CenterFrameMath::ScreenY(y), 0, 0);
            AddGifRgbaEntry(gs, *(u32*)&colA);
            AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(x), CenterFrameMath::ScreenY(y2), 0, 0);
        }
        AddGifRgbaEntry(gs, *(u32*)&colB);
        AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(x1), CenterFrameMath::ScreenY(posY + scale * -8.0f), 0, 0);
        AddGifRgbaEntry(gs, *(u32*)&colA);
        AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(x1), CenterFrameMath::ScreenY(posY + scale * -4.0f), 0, 0);

        AddGifRgbaEntry(gs, *(u32*)&colB);
        AddGifXyzfNoDrawEntry(gs, CenterFrameMath::ScreenX(x0), CenterFrameMath::ScreenY(posY - scale * -8.0f), 0, 0);
        AddGifRgbaEntry(gs, *(u32*)&colA);
        AddGifXyzfNoDrawEntry(gs, CenterFrameMath::ScreenX(x0), CenterFrameMath::ScreenY(posY - scale * -3.0f), 0, 0);
        u = step;
        for (i = 1; i < 24; i++) {
            f32 x = x0 + scale * u * 70.0f;
            f32 y;
            f32 y2;
            u += step;
            y = posY - scale * EvalCurveSpan(&D_002612E0, i);
            y2 = y - scale * 5.0f;
            AddGifRgbaEntry(gs, *(u32*)&colB);
            AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(x), CenterFrameMath::ScreenY(y), 0, 0);
            AddGifRgbaEntry(gs, *(u32*)&colA);
            AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(x), CenterFrameMath::ScreenY(y2), 0, 0);
        }
        AddGifRgbaEntry(gs, *(u32*)&colB);
        AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(x1), CenterFrameMath::ScreenY(posY - scale * -8.0f), 0, 0);
        AddGifRgbaEntry(gs, *(u32*)&colA);
        AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(x1), CenterFrameMath::ScreenY(posY - scale * -4.0f), 0, 0);

        if (self->state != 5) {
            s32 n;

            offX = 41.0f;
            offY = -5.0f;
            BeginGifTag(gs, 0xC6, 5, 0x44441);
            for (n = 0; n < 64; n++) {
                f32 px, py;
                f32 s = CenterFrameMath::Wave(offX, wide, self->spin);
                px = posX + scale * offX;
                py = posY + scale * offY;
                PanelColor col = CenterFrameMath::Lerp(c0, c1, 0.5f - s * 0.5f);
                AddGifRgbaEntry(gs, *(u32*)&col);
                AddGifXyzfNoDrawEntry(gs, CenterFrameMath::ScreenX(px), CenterFrameMath::ScreenY(py), 0, 0);
                AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(px + scale * 2.0f), CenterFrameMath::ScreenY(py + scale * 10.0f), 0, 0);
                py = posY + scale * offY;
                px = posX - scale * offX;
                AddGifXyzfNoDrawEntry(gs, CenterFrameMath::ScreenX(px), CenterFrameMath::ScreenY(py), 0, 0);
                AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(px - scale * 2.0f), CenterFrameMath::ScreenY(py + scale * 10.0f), 0, 0);
                offX += 8.0f;
            }

            offX = -5.0f;
            offY = 24.0f;
            for (n = 0; n < 32; n++) {
                f32 px, py;
                f32 s = CenterFrameMath::Wave(offY, period, self->spin);
                px = posX + scale * offX;
                py = posY + scale * offY;
                PanelColor col = CenterFrameMath::Lerp(c0, c1, 0.5f - s * 0.5f);
                AddGifRgbaEntry(gs, *(u32*)&col);
                AddGifXyzfNoDrawEntry(gs, CenterFrameMath::ScreenX(px), CenterFrameMath::ScreenY(py), 0, 0);
                AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(px + scale * 10.0f), CenterFrameMath::ScreenY(py + scale * 2.0f), 0, 0);
                py = posY - scale * offY;
                px = posX + scale * offX;
                AddGifXyzfNoDrawEntry(gs, CenterFrameMath::ScreenX(px), CenterFrameMath::ScreenY(py), 0, 0);
                AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(px + scale * 10.0f), CenterFrameMath::ScreenY(py - scale * 2.0f), 0, 0);
                offY += 8.0f;
            }
        }
    }

    BeginGifTag(gs, 0, 1, 0xE);
    AddGifRegisterWrite(gs, 0x40, 0xDF0000027F0000);
}

void DrawTextPanelBorders(T217D_440* self, PacketWriter* gs)
{
    PanelColor c0;
    PanelColor c1;
    PanelColor c2;
    f32 step = 1.0f / 24.0f;
    f32 t;
    t = 0.5f - Cosine(self->spin) * 0.5f;
    c0 = BorderColorMix::Mix(D_002610E0, D_002610D8, t);
    t = 0.5f - Cosine(self->spin + 1.5707964f) * 0.5f;
    c1 = BorderColorMix::Mix(D_002610E0, D_002610D8, t);
    t = 0.5f - Cosine(self->spin + 3.1415927f) * 0.5f;
    c2 = BorderColorMix::Mix(D_002610E0, D_002610D8, t);
    s32 i;
    f32 x;

    BeginGifTag(gs, 0x8C, 2, 0x41);

    AddGifRgbaEntry(gs, *(u32*)&c2);
    AddGifXyzfNoDrawEntry(gs, 0x6C00, 0x7B45, 0, 0);
    AddGifRgbaEntry(gs, *(u32*)&c1);
    AddGifXyzfNoDrawEntry(gs, 0x6C00, 0x7B62, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 v = EvalCurveSpan(&D_00261280, i);
        f32 sx = x * 640.0f;
        f32 v2 = v + 4.0f;
        AddGifRgbaEntry(gs, *(u32*)&c2);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        AddGifXyzfEntry(gs, px, (s32)((v * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        AddGifRgbaEntry(gs, *(u32*)&c1);
        AddGifXyzfEntry(gs, px, (s32)((v2 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    }
    AddGifRgbaEntry(gs, *(u32*)&c2);
    AddGifXyzfEntry(gs, 0x9400, 0x7B45, 0, 0);
    AddGifRgbaEntry(gs, *(u32*)&c1);
    AddGifXyzfEntry(gs, 0x9400, 0x7B62, 0, 0);

    AddGifRgbaEntry(gs, *(u32*)&c2);
    AddGifXyzfNoDrawEntry(gs, 0x6C00, 0x80FA, 0, 0);
    AddGifRgbaEntry(gs, *(u32*)&c1);
    AddGifXyzfNoDrawEntry(gs, 0x6C00, 0x80DD, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 v = EvalCurveSpan(&D_002612B0, i);
        f32 sx = x * 640.0f;
        f32 v2 = v - 4.0f;
        AddGifRgbaEntry(gs, *(u32*)&c2);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        AddGifXyzfEntry(gs, px, (s32)((v * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        AddGifRgbaEntry(gs, *(u32*)&c1);
        AddGifXyzfEntry(gs, px, (s32)((v2 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    }
    AddGifRgbaEntry(gs, *(u32*)&c2);
    AddGifXyzfEntry(gs, 0x9400, 0x80FA, 0, 0);
    AddGifRgbaEntry(gs, *(u32*)&c1);
    AddGifXyzfEntry(gs, 0x9400, 0x80DD, 0, 0);

    AddGifRgbaEntry(gs, *(u32*)&c1);
    AddGifXyzfNoDrawEntry(gs, 0x6C00, 0x7B62, 0, 0);
    AddGifRgbaEntry(gs, *(u32*)&c0);
    AddGifXyzfNoDrawEntry(gs, 0x6C00, 0x7B80, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 r = EvalCurveSpan(&D_00261280, i);
        f32 sx = x * 640.0f;
        f32 v = r + 4.0f;
        f32 v2 = v + 4.0f;
        AddGifRgbaEntry(gs, *(u32*)&c1);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        AddGifXyzfEntry(gs, px, (s32)((v * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        AddGifRgbaEntry(gs, *(u32*)&c0);
        AddGifXyzfEntry(gs, px, (s32)((v2 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    }
    AddGifRgbaEntry(gs, *(u32*)&c1);
    AddGifXyzfEntry(gs, 0x9400, 0x7B62, 0, 0);
    AddGifRgbaEntry(gs, *(u32*)&c0);
    AddGifXyzfEntry(gs, 0x9400, 0x7B80, 0, 0);

    AddGifRgbaEntry(gs, *(u32*)&c1);
    AddGifXyzfNoDrawEntry(gs, 0x6C00, 0x80DD, 0, 0);
    AddGifRgbaEntry(gs, *(u32*)&c0);
    AddGifXyzfNoDrawEntry(gs, 0x6C00, 0x80C0, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 r = EvalCurveSpan(&D_002612B0, i);
        f32 sx = x * 640.0f;
        f32 v = r - 4.0f;
        f32 v2 = v - 4.0f;
        AddGifRgbaEntry(gs, *(u32*)&c1);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        AddGifXyzfEntry(gs, px, (s32)((v * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        AddGifRgbaEntry(gs, *(u32*)&c0);
        AddGifXyzfEntry(gs, px, (s32)((v2 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    }
    AddGifRgbaEntry(gs, *(u32*)&c1);
    AddGifXyzfEntry(gs, 0x9400, 0x80DD, 0, 0);
    AddGifRgbaEntry(gs, *(u32*)&c0);
    AddGifXyzfEntry(gs, 0x9400, 0x80C0, 0, 0);
}

INCLUDE_ASM(func_00134AA0);

INCLUDE_RODATA(D_00249CF8);
INCLUDE_ASM(func_00134B48);

void DrawTextPanelBlocks(T217D_440* self, PacketWriter* q)
{
    if (self->state == 1)
    {
        if ((u32)MaskWorldBitsBySave() & 0x800)
        {
            func_00134B48(self, q);
        }
        u32 mask;
        GetCurrentLevelBit(&mask);
        if ((u32)MaskWorldBitsBySave() & mask)
        {
            u8 c0[4];
            u8 c1[4];
            u8 c2[4];
            u8 out[4];
            *(u32*)c0 = 0xFF408080;
            *(u32*)c1 = 0xFF406060;
            *(u32*)c2 = 0xFF404040;
            f32 t = Cosine(g_gameClock[1] * D_00261260[0]) * 0.5f + 0.5f;
            for (u32 i = 0; i < 4; i++)
            {
                f32 r = ApproachValueWithRamp(self->blockB[i], self->blockA[i] ? 1.0f : 0.0f, g_gameClock[2], &D_00261260[2], 0);
                self->blockB[i] = r;
                for (s32 j = 0; j < 4; j++)
                {
                    out[j] = (s32)((1.0f - r) * (f32)c2[j] + r * t * (f32)c1[j] + r * (1.0f - t) * (f32)c0[j]);
                }
                out[3] = (out[3] + 1) >> 1;
                BeginGifTag(q, 0x4D, 5, 0x44441);
                AddGifRgbaEntry(q, *(u32*)out);
                for (s32 k = 0; k < 4; k++)
                {
                    s32 xi = (s32)(((D_002611E0[i][k] + 320.0f) + 1728.0f) * 16.0f);
                    s32 yi = (s32)(((D_00261220[i][k] + 415.8000183f) * 0.45454547f + 1936.0f) * 16.0f);
                    AddGifXyzfEntry(q, xi, yi, 0, 0);
                }
            }
        }
    }
}

void SetTextPanelMode(T217D_440* self, s32 value)
{
    if (value == self->mode) {
        return;
    }
    if (self->mode == 0) {
        PlayerListHolder* g = FindFirstObjectById((*(World**)&g_currentWorld), 0x105, 0x495, 0);
        if (g != 0) {
            ListFrame it;
            ListWalkBegin::Of(&it, &g->list);
            AnimationPlayer* obj;
            while ((obj = ListWalkNext::Of(&it)) != 0) {
                SetAnimationPlayerSpeed(obj, 0.0f);
            }
            g_activeListFrames = (ListFrame*)it.prev;
        }
    }
    if (value == 0) {
        PlayerListHolder* g = FindFirstObjectById((*(World**)&g_currentWorld), 0x105, 0x495, 0);
        if (g != 0) {
            ListFrame it;
            ListWalkBegin::Of(&it, &g->list);
            AnimationPlayer* obj;
            while ((obj = ListWalkNext::Of(&it)) != 0) {
                SetAnimationPlayerSpeed(obj, 1.0f);
            }
            g_activeListFrames = (ListFrame*)it.prev;
        }
    }
    SetScreenElementMode(self, value);
}

void SetTextPanelState(T217D_440* self, s32 mode)
{
    if (mode != self->state) {
        if (self->state != 1) {
            if (self->state < 2) {
                if (self->state == 0) {
                    ClearTextPanel(self);
                }
            }
        } else {
            StartSoundEffect(0x8F, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
        switch (mode) {
        case 1:
            StartSoundEffect(0x8E, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            self->state = mode;
            break;
        case 4:
            ((Tail_1356C0*)&D_0026F138)->v = 0;
            D_0026F138.vt->m15(&D_0026F138);
            self->state = mode;
            break;
        default:
            self->state = mode;
            break;
        }
        self->stateSince = g_gameTime;
    }
}

s32 CompareEntriesByAttachedKey(SortEntry* a, SortEntry* b)
{
    if (IsObjectAttached(a->obj) == 0) {
        return 1;
    }
    if (IsObjectAttached(b->obj) == 0) {
        return -1;
    }
    if (a->key < b->key) {
        return -1;
    }
    return 1;
}

s32 CompareEntriesFlaggedLast(SortEntry* a, SortEntry* b)
{
    s32 flag;

    GetNumberedItemFlag(a->obj, &flag);
    if (flag != 0) {
        return 1;
    }
    GetNumberedItemFlag(b->obj, &flag);
    if (flag != 0) {
        return -1;
    }
    if (a->key < b->key) {
        return -1;
    }
    return 1;
}

INCLUDE_ASM(func_001358D0);

LINKER_REMNANT(func_00135E20);

void ReadPanelEntryPosition(PanelEntrySource* self, PanelEntryPosition* out, s32* flag)
{
    *out = self->v;
    *flag = 0;
}

LINKER_REMNANT(func_00135E40);

void ReadAdjustedPanelEntryPosition(PanelEntrySource* self, s32 unused, PanelEntryPosition* out)
{
    *out = self->v;
    ComputeHullSeenFromCamera(out, 1);
}

LINKER_REMNANT(func_00135E70);

void ReleasePanelEntries(T217D_440* self, s32 state, s32 flag)
{
    if (state == self->bankState) return;
    s32 i = 0;
    void* blockA = self->blockA;
    if (self->count > 0) {
        T217D_440_Slot* e = self->entries;
        do {
            if (flag != 0) {
                RemoveEffect(e->handle);
                FillMemory(self->blockB, 0, 16);
            } else {
                SetEffectPhase(e->handle, 2);
            }
            i++;
            e++;
        } while (i < self->count);
    }
    self->count = 0;
    self->countA = 0;
    FillMemory(blockA, 0, 16);
    self->bankState = state;
}

void RefreshPanelEntries(T217D_440* self)
{
    LevelBit flag;
    GetCurrentLevelBit(&flag);
    if ((MaskWorldBitsBySave() & flag.v) == 0) {
        ReleasePanelEntries(self, 0, 1);
        return;
    }
    ReleasePanelEntries(self, 1, 0);
    if (self->bankState == 1) {
        f32 k = 3.4028235e38f;
        World* world = *(World**)g_currentWorld;
        CollectPanelEntriesOfClass(self, 0x2E, func_00135E20 + 0x10, func_00135E40 + 8, 5, (s32)world->slot1CE8[23], k);
        CollectPanelEntriesOfClass(self, 0x21, func_00135E20 + 0x10, func_00135E40 + 8, 5, (s32)(*(World**)g_currentWorld)->slot1CE8[27], k);
    }
}

void UpdatePanelStick(T217D_440* self, PadRecord* p)
{
    switch (self->state) {
    case 1: {
        Vec_136040 va;
        Vec_136040 vb;
        Vec_136040 r;
        f32 lo = -1.0f;
        f32 hi = 1.0f;
        f32 sum = p->f40 + p->f74;
        StickLimits t0 = D_00249D00;
        StickLimits t1 = D_00249D10;
        f32 u = (sum < lo) ? lo : ((hi < sum) ? hi : sum);
        f32 v = p->f44;
        f32 lo2 = -1.0f;
        f32 hi2 = 1.0f;
        if (v < lo2) {
            v = lo2;
        } else if (hi2 < v) {
            v = hi2;
        }
        if (g_saveData->u19EC & 0x200) v = -v;
        va.x = self->stickX;
        va.y = self->stickY;
        va.z = 0;
        vb.x = u * 50.0f;
        vb.y = v * 50.0f;
        vb.z = 0;
        f32* g = ((f32*)g_gameClock);
        *(Quad_136040*)&r = ApproachPointWithRamp(*(Quad_136040*)&va, *(Quad_136040*)&vb, (0.0001f < p->f48 + p->f7C) ? &t0 : &t1, 0, g[2]);
        self->f314 += u * -0.08f;
        self->stickX = r.x;
        self->stickY = r.y;
        self->f314 = WrapModulo(self->f314, 1.0f);
        break;
    }
    case 5:
        self->stickY = 50.0f;
        break;
    }
    RefreshPanelEntries(self, p);
}
extern const StickLimits D_00249D00 = { 0x4248000042A00000ULL, 0x3F000000 };
extern const StickLimits D_00249D10 = { 0x43480000437A0000ULL, 0x3DCCCCCD };

void SetTextPanelOpen(T217D_440* self, s32 on)
{
    LevelBit in;
    void* arr[0x100];
    s32 n;
    if ((on != 0) != (self->open == 0)) return;
    if (self->child != 0 && ((StepSequence*)self->child)->state2D4 == 3) {
        if (on != 0) ResumeStreamVoice();
        else PauseStreamVoice();
    }
    self->open = on;
    self->palette = 0;
    if (on != 0) {
        self->vt->m16(self, 2);
        GetCurrentLevelBit(&in);
        if (MaskWorldBitsBySave() & in.v) {
            if (MaskWorldBitsBySave() & D_00261120[self->savedBank]) ReleasePanelEntries(self, self->savedBank, 1);
        }
        if (MaskWorldBitsBySave() & 0x800) {
            n = GatherObjectsById(*(s32*)g_currentWorld, 0x205, 0x82, 0, 0x100, arr);
            n = ClampBelow::Of(n, 0x100);
            if (n > 0) {
                void** p = arr;
                s32 i = n;
                do { i--; ResetTextPointToHalf(*p); p++; } while (i != 0);
            }
        }
    } else {
        self->vt->m16(self, 0);
        self->savedBank = self->bankState;
        ReleasePanelEntries(self, 0, 1);
    }
}

void ResetTextPanel(T217D_440* self)
{
    ResetScreenElement(self);
    if (self->child != 0) {
        SetStepSequenceState(self->child, 2);
    }
}

void SetTextPanelText(T217D_440* self, const char* name)
{
    TextScratch buf;
    s32 s1;
    s32 r;
    s32 idx;
    f32 scale;
    f32 lim;
    f32* tab;

    self->lineCount = 0;
    if (name == 0) goto fail;
    if (GetStringLength(name) == 0) goto fail;
    CopyString(self->text, name);
    s1 = 4;
    scale = 1.0f;
    if ((r = self->state) == s1) scale = 0.8f;
    PushFontScale(self->font, scale, scale);
    InitTextReader(&buf, self->text, self->font);
    lim = 280.0f;
    if ((r = self->state) == s1) lim = 380.0f;
    s1 = 0;
    WrapTextLines(&buf, lim);
    PopFontScale(self->font);
    RewindTextReader(&buf);
    while ((r = ReadTextChar(&buf)) != 0) {
        if (r == 10) {
            idx = self->lineCount;
            self->lineBreaks[idx] = s1;
            self->lineCount = idx + 1;
        }
        s1++;
    }
    goto tail;
fail:
    self->text[0] = 0;
tail:
    tab = (f32*)g_gameClock;
    self->textSince = tab[1];
}

s32 IsTextPanelTextTyped(T217D_440* self)
{
    u8 buf[0xB0];

    if (self->text[0] == 0) {
        return 1;
    }
    InitTextReader(buf, &self->text[0], self->font);
    s32 n = CountTextChars(buf);
    s32 v = (s32)((g_gameTime - self->textSince) * self->charsPerSecond);
    return v >= n;
}

void SetTextPanelSubject(T217D_440* self, s32 value) { self->f2FC = value; }

void SetTextPanelValuePercent(T217D_440* self, f32 value)
{
    PercentClamp::Set(self, value * 0.01f, 0.0f, 1.0f);
}

f32 GetTextPanelSlideInTime(T217D_440* self)
{
    switch (self->state) {
    case 1:
    case 2:
    case 5:
        return 0.0f;
    case 3:
    case 4:
    default:
        return GetScreenElementSlideInTime(self);
    }
}

f32 GetTextPanelSlideOutTime(T217D_440* s) {
    switch (s->state) {
    case 1:
    case 2:
    case 5:
        return 0.0f;
    case 3:
    case 4:
    default:
        return GetScreenElementSlideOutTime(s);
    }
}

INCLUDE_RODATA(D_00249D58);
INCLUDE_ASM(func_001366A0);

void GetTextPanelCenter(T217D_440* self, f32* x, f32* y)
{
    *x = self->stickX + 320.0f;
    *y = self->stickY + 180.4000091552734375f;
}

void ChooseTextPanelState(T217D_440* self)
{
    if (self->child != 0) {
        switch (((StepSequence*)self->child)->mode2D0) {
        case 0:
            SetTextPanelState(self, 2);
            break;
        case 1:
            SetTextPanelState(self, 3);
            break;
        case 2:
            SetTextPanelState(self, 4);
            break;
        }
        SetStepSequenceState((StepSequence*)self->child, 3);
    } else {
        SetTextPanelState(self, 1);
    }
}

s32 EndTextPanelState(Owner_136FA8* self)
{
    s32 r;
    if (self->child != 0) {
        r = SetStepSequenceState(self->child, 4);
        goto done;
    }
    r = SetTextPanelState(self, 0);
done:
    return r;
}

// The text layout's setters (layout_137228.h): defined after their callers, which call them,
// and written out here at the end of the file, after the static initialiser.
inline void Layout_137228::Pos(f32 x_, f32 y_)
{
    x = x_;
    y = y_;
}

inline void Layout_137228::Size(f32 w_, f32 h_)
{
    w = w_;
    h = h_;
}

inline void Layout_137228::Color(s32* value)
{
    color = *(Rgba_137248*)value;
}

inline void Layout_137228::SetF14(s32 value) { f14 = value; }

inline void Layout_137228::SetF18(void* value)
{
    f18 = value;
}
