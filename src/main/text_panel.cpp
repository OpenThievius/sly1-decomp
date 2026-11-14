// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "object_finder.h"

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
#include "vu0.h"
#include "camera.h"
#include "point_object.h"
#include "value_range.h"
struct BaseObject;
struct Vec02;

struct BaseObject;

struct Effect;
struct PlacedObject;


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

void SetTextPanelSubject(T217D_440* self, BaseObject* arg);

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

extern "C" f32 Cosine(f32 x);
void ConvertPositionToWorld(BaseObject* self, Vec02* out);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRgbaEntry(PacketWriter* gs, u32 c);
void AddGifXyzfNoDrawEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);

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


struct CameraHeading {
    u8 pad0[0x40];
    s32 f40[4];             // 0x40: the eye
    f32 planes[3][4];       // 0x50: the view planes' normals, as columns (camera.h)
    u8 pad80[0x1C4 - 0x80];
    f32 f1C4;               // 0x1C4
    u8 pad1C8[0x1E0 - 0x1C8];
    f32 f1E0;               // 0x1E0
    u8 pad1E4[0x468 - 0x1E4];
    f32 heading;            // 0x468
    u8 pad46C[0x470 - 0x46C];
    f32 pitch;              // 0x470
    u8 pad474[0x478 - 0x474];
    f32 f478;
};

extern s32 g_padRouting;
extern f32 g_frameDt;
extern CameraHeading* g_camera;

void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void AddGifRgbaEntry(PacketWriter* gs, u32 color);
void AddGifXyzfNoDrawEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
f32 WrapAngle(f32 a);
extern "C" f32 Cosine(f32 x);
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

void SetTextPanelState(T217D_440* self, s32 mode);
void SetStepSequenceState(StepSequence* obj, s32 mode);

struct SortEntry {
    void* obj;
    f32 key;
};

s32 IsObjectAttached(BaseObject* self);

struct NumberedItem;
void GetNumberedItemFlag(NumberedItem* self, s32* out);

void RemoveEffect(Effect* self);
void SetEffectPhase(Effect* self, s32 mode);
extern "C" void* FillMemory(void* p, s32 value, s32 size);

// Newly matched US functions from the small-function wave.
struct BufferedStream;
extern void CloseBufferedStream(BufferedStream* self);
extern void FreeObjectMemory(void*);
extern void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out);

struct PercentClamp {
    static void Set(T217D_440* self, f32 x, f32 lo, f32 hi) {
        if (x < lo) x = lo;
        else if (hi < x) x = hi;
        self->value = x;
    }
};

extern f32 g_gameTime;

struct TextReader;
struct StringLayout;
struct Vec4U;
Font* InitTextReader(TextReader* self, char* text, Font* font);
s32 CountTextChars(void* self);

extern f32 g_gameClock[];

struct TextScratch {
    u8 bytes[0xB0];
};

extern "C" s32 GetStringLength(const char* s);
void* CopyString(void* dst, const char* src);
void PushFontScale(Font* font, f32 x, f32 y);
s32 WrapTextLines(TextReader* self, f32 limit);
void PopFontScale(Font* font);
void RewindTextReader(TextReader* self);
s32 ReadTextChar(TextReader* self);

struct __attribute__((packed)) Tail_1356C0 { u8 pad0[0x464]; s32 v; };
extern f32 g_gameTime;

void ClearTextPanel(T217D_440* self);
struct PlayingSound;
struct BaseObject;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

extern World* g_currentWorld;
extern u8 func_00135E20[];
extern u8 func_00135E40[];



// The bit of the current level GetCurrentLevelBit (func_00160D30) gives back.
struct LevelBit { s32 v; };
void GetCurrentLevelBit(u32* out);
s32 MaskWorldBitsBySave(void);
void CollectPanelEntriesOfClass(T217D_440* self, s32 a1, void* a2, void* a3, s32 a4, s32 a5, f32 f);

struct StickLimits { u64 a __attribute__((packed)); u32 b; };
typedef u64 Quad_136040 __attribute__((mode(TI)));
struct __attribute__((aligned(16))) Vec_136040 { f32 x, y, z, w; };

extern const StickLimits D_00249D00;
extern const StickLimits D_00249D10;

struct RampProfile;
Quad_136040 ApproachPointWithRamp(u128 from, u128 to, f32 limit, RampProfile* ramp, Vec02* vel);
f32 WrapModulo(f32 x, f32 y);
void RefreshPanelEntries(T217D_440* self, PadRecord* p);

struct __attribute__((aligned(16))) PanelEntryPosition { s32 a, b, c, d; };
struct PanelEntrySource { char pad[0x140]; PanelEntryPosition v; };


s32 ComputeHullSeenFromCamera(PanelEntryPosition* v, s32 mode);

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

void SetAnimationPlayerSpeed(AnimationPlayer* item, f32 x);


extern World* g_currentWorld;

void ResumeStreamVoice(void);
void PauseStreamVoice(void);
void GetCurrentLevelBit(u32* out);
s32 MaskWorldBitsBySave(void);
void ReleasePanelEntries(T217D_440* self, s32 state, s32 flag);
void ResetTextPointToHalf(TextPointObject* self);

struct ClampBelow { static s32 Of(s32 a, s32 b) { if (b - 1 < a) return b; return a; } };

void GetCurrentLevelBit(u32* out);
void DrawTextPanelMarkers(T217D_440* self, PacketWriter* q);
extern "C" f32 Cosine(f32 x);
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
void AddGifRgbaEntry(PacketWriter* q, u32 v);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);

// The file's .data, in retail's order from 0x261090. The colours and the two styles are built
// by the static initialiser (func_00136FE8); their bytes are zero until then.
struct PanelStyle {
    s32 font;
    u8 f4;
    f32 paddingX;
    f32 paddingY;
    f32 scaleX;
    f32 scaleY;
    u32 color;
    PanelStyle()
    {
    }
    PanelStyle(f32 w)
    {
        FillMemory(this, 0, 0x1C);
        f4 = 0x2D;
        paddingX = w;
        scaleX = 0.3f;
        scaleY = 0.3f;
        color = 0xFF7D4B00;
    }
    PanelStyle(s32 w, s32 h)
    {
        FillMemory(this, 0, 0x1C);
        f4 = 0x2D;
        paddingX = w;
        paddingY = h;
        scaleY = scaleX = 0.3f;
        color = 0xFF7D4B00;
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

void InitCurveSpan(CurveSpan* d, const SpanHead* src, f32 x, f32 y, s32 n);
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
void RefreshPanelEntries(T217D_440* self, PadRecord* pad);
void UpdatePanelStick(T217D_440* self, PadRecord* p);
void SetTextPanelOpen(T217D_440* self, s32 on);
void ResetTextPanel(T217D_440* self);
void SetTextPanelText(T217D_440* self, const char* name);
s32 IsTextPanelTextTyped(T217D_440* self);
void SetTextPanelSubject(T217D_440* self, BaseObject* value);
void SetTextPanelValuePercent(T217D_440* self, f32 value);
f32 GetTextPanelSlideInTime(T217D_440* self);
f32 GetTextPanelSlideOutTime(T217D_440* s);
void GetTextPanelCenter(T217D_440* self, f32* x, f32* y);
void ChooseTextPanelState(T217D_440* self);
void EndTextPanelState(T217D_440* self);

void InitCurveSpan(CurveSpan* d, const SpanHead* src, f32 x, f32 y, s32 n)
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
    self->tickScroll = 0.4f;
}

void SetupScreenElementText(ScreenElement* self);
s32 IsFontLoaded(s32 id);
Font* GetFontById(s32 id);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
// Returns its writer (retail sets v0 from it), as a constructor does.
void* InitGifPacket(PacketWriter* gs);
void UsePacketBufferMemory(PacketWriter* gs, s32 n, void* mem);
void DetachPacketBufferCopy(PacketWriter* self, s32* count, u32* begin, s32* out, s32 flags);
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
    small->useTestWord = 1;
    small->testWord = 0x3F001;
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
    InitCurveSpan(&D_00261280, (const SpanHead*)D_002610A0, 0.171875f, 40.0f, 0x18);
    InitCurveSpan(&D_002612B0, (const SpanHead*)D_002610B0, 0.171875f, -60.0f, 0x18);
    InitCurveSpan(&D_002612E0, (const SpanHead*)D_002610C0, 0.2857143f, 8.0f, 0x18);
    s32 i;
    f32 t;
    AddGifXyzfNoDrawEntry(&gs, 0x6C00, 0x7900, 0x0FFFFFF0, 0);
    AddGifXyzfNoDrawEntry(&gs, 0x6C00, 0x7B45, 0x0FFFFFF0, 0);
    for (t = step, i = 1; i < 24; i++) {
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
    DetachPacketBufferCopy(&gs, (s32*)&self->bands, 0, &self->bandsSize, 0x15);
    PopBackMemoryMark();
}




struct PanelFont {
    static Font* Of(T217D_440* self) { return *(Font**)((u8*)self + 0x310); }
};

f32 MeasureFontString(Font* font, const char* text);
void DrawFontString(Font *self, const char *str, StringLayout *par, Vec4U *clip, PacketWriter *s);

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
        f32 x = left + ((f32)i - self->tickScroll) * step * span;
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
    DrawFontString(PanelFont::Of(self), D_00261128[prev], (StringLayout*)&L, 0, gs);
    L.x = xNext;
    L.y = row;
    DrawFontString(PanelFont::Of(self), D_00261128[next], (StringLayout*)&L, 0, gs);

    {
        SpanHead q = { 0.0f, 4.0f, -4.0f };
        f32 t = q.c0 + frac * (q.c1 + frac * q.c2);
        *(PanelColor*)&L.color = BorderColorMix::Mix(D_002610D8, PanelColor(0x32, 0x84, 0xB0, 0x80), t);
    }
    L.x = xCur;
    L.y = row;
    DrawFontString(PanelFont::Of(self), D_00261128[cur], (StringLayout*)&L, 0, gs);

    BeginGifTag(gs, 0, 1, 0xE);
    AddGifRegisterWrite(gs, 0x40, 0xDF0000027F0000);
}


extern const char D_00249CE0[8] = "%c";
extern const char D_00249CE8[8] = "Move";
extern const char D_00249CF0[8] = "Zoom";
s32 FormatToString(char* dst, const char* fmt, ...);

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

    static s32* Words(Quad4& q)
    {
        return q.w;
    }

    // The same in grey, the colour in a 16-byte local (DrawTextPanelMarkers).
    static void Reset(Layout_137228* l)
    {
        Quad4 col;
        l->Pos(0.0f, 0.0f);
        l->Size(640.0f, 492.800018f);
        col.w[0] = 0xFF808080;
        l->Color(Words(col));
        l->SetF14(0);
        l->SetF18(0);
    }
};

// The panel's control labels: eight bands of the zoom gauge (lit up to the camera's zoom), and in
// state 1 the two button glyphs (larger while held) with "Move" and "Zoom" beside them.
// The band's step, the gauge's top and the half are variables of the loop body: a variable has a
// life, so loop.c moves its constant out with the literals', and with every saved float register
// taken by the literals used more often, reload forms the three again in the loop
// (docs/toolchain/loops.md, "Named constants that lose their registers").
void DrawTextPanelControlLabels(T217D_440* self, PacketWriter* gs)
{
    BeginGifTag(gs, 0, 1, 0xE);
    AddGifRegisterWrite(gs, 0x47, 0x31001);
    AddGifRegisterWrite(gs, 0x42, 0x44);
    BeginGifTag(gs, 0x84, 5, 0x44441);
    for (s32 i = 0; i < 8; i++) {
        f32 zoom = g_camera->f478;
        const PanelColor* const lit = &D_002610D8;
        const PanelColor* const dim = &D_002610E0;
        f32 step = 1.0f / 15.0f;
        f32 top = 372.800018f;
        f32 half = 0.5f;
        f32 lo = (f32)i * (1.0f / 9.0f);
        f32 hi = lo + step;
        f32 x0 = (1.0f - lo) * 55.0f - 9.0f;
        f32 x1 = ((1.0f - hi) * 55.0f + 1.0f) - 9.0f;
        f32 y0 = top - lo * 60.0f;
        f32 y1 = top - hi * 60.0f;
        PanelColor c = (lo + hi) * half <= zoom ? *lit : *dim;
        AddGifRgbaEntry(gs, *(u32*)&c);
        s32 sx0 = CenterFrameMath::ScreenX(320.0f - x0);
        s32 sy0 = CenterFrameMath::ScreenY(y0);
        AddGifXyzfNoDrawEntry(gs, sx0, sy0, 0, 0);
        AddGifXyzfNoDrawEntry(gs, CenterFrameMath::ScreenX(x0 + 320.0f), sy0, 0, 0);
        s32 sy1 = CenterFrameMath::ScreenY(y1);
        AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(320.0f - x1), sy1, 0, 0);
        AddGifXyzfEntry(gs, CenterFrameMath::ScreenX(x1 + 320.0f), sy1, 0, 0);
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
    FormatToString(buf, D_00249CE0, 0x28);
    Layout_137228* lay = &L;
    lay->f14 = 1;
    lay->f18 = 1;
    L.w = 0.0f;
    L.h = 0.0f;
    f32 s = 0.4f;
    if (self->open != 0 && pad->stickMagnitude != 0.0f) {
        s = 0.5f;
    }
    PushFontScale(glyphs, s, s);
    L.x = 265.0f;
    L.y = row;
    DrawFontString(glyphs, buf, (StringLayout*)&L, 0, gs);
    PopFontScale(glyphs);
    FormatToString(buf, D_00249CE0, 0x29);
    s = 0.4f;
    if (self->open != 0 && pad->secondStickMagnitude != 0.0f) {
        s = 0.5f;
    }
    PushFontScale(glyphs, s, s);
    L.x = 375.0f;
    L.y = row;
    DrawFontString(glyphs, buf, (StringLayout*)&L, 0, gs);
    PopFontScale(glyphs);
    *(PanelColor*)&L.color = PanelColor(0x32, 0x84, 0xB0, 0x80);
    PushFontScale(text, 0.6f, 0.6f);
    Layout_137228& move = L;
    move.f14 = 2;
    L.x = (f32)(320 - D_00261090[0]);
    L.y = row;
    DrawFontString(text, D_00249CE8, (StringLayout*)&L, 0, gs);
    L.f14 = 0;
    L.x = (f32)(D_00261090[0] + 320);
    L.y = row;
    DrawFontString(text, D_00249CF0, (StringLayout*)&L, 0, gs);
    PopFontScale(text);
}

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
    if (0.0f < pad->secondStickY) {
        k = 6.0f;
    } else if (pad->secondStickY < 0.0f) {
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

s32 CompareEntriesFarthestFirst(void** a, void** b)
{
    Vec02 pa;
    Vec02 pb;
    ConvertPositionToWorld((BaseObject*)*a, &pa);
    ConvertPositionToWorld((BaseObject*)*b, &pb);
    u128 cam = Vu0::Q(g_camera->f40);
    u128 da = Vu0::Sub(cam, Vu0::Q(pa));
    u128 db = Vu0::Sub(cam, Vu0::Q(pb));
    s32 c = Vu0::ToFloat(Vu0::Dot(da, da)) < Vu0::ToFloat(Vu0::Dot(db, db));
    return c == 0 ? -1 : 1;
}

struct StyleDrawer {
    static void Draw(Font** h, Layout_137228* out, void* tbl)
    {
        if (*h != 0) {
            const FontVt* vt = (*h)->vt;
            vt->drawBox((Font*)((u8*)*h + vt->adj9), h, out, tbl);
        }
    }
};

void SortElements(void* base, u32 n, u32 size, s32 (*compare)(const void* x, const void* y));
void ProjectPointToCamera(Camera* camera, Vec02* in, f32* out);
f32 MeasureFontStringHeight(Font* self, u8* s, f32 width);

// The labels of the text points (class 0x82) in view: each gathered point the camera sees
// within 4000 is drawn at its place on the screen, its name with spaces for underscores, the
// one nearest the screen's centre larger and opaque; the rest are reset (ResetTextPointToHalf).
// The opacity's range is a pointer named beside the coefficient table's, before the projection:
// its life then spans the call, so loop.c moves its address in its first pass, ahead of the
// screen constants, and the second loop's preheader keeps retail's order
// (docs/toolchain/sched1.md, "Spill stores between float constants").
void DrawTextPanelMarkers(T217D_440* self, PacketWriter* q)
{
    TextPointObject* objs[32];
    Vec02 pos;
    Vec02 screen;
    s32 i;
    s32 shown = 0;
    TextPointObject* nearest = 0;
    s32 count = GatherObjectsById(g_currentWorld, 5, 0x82, 0, 0x20, objs);
    SortElements(objs, count, 4, (s32 (*)(const void*, const void*))CompareEntriesFarthestFirst);
    f32 best = 3.4028235e+38f;
    for (i = 0; i < count; i++) {
        TextPointObject* obj = objs[i];
        ConvertPositionToWorld(obj, &pos);
        Camera* cam = (Camera*)g_camera;
        Vu0::Vec d = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(cam->position));
        if (4000.0f < Vu0::ToFloat(Vu0::Length(d))) {
            continue;
        }
        u128 ones = Vu0::Ones();
        Vu0::Vec r = Vu0::Vec::Scalar(0.0f);
        if ((Vu0::PlaneSigns(Vu0::Vec::Of(cam->planes[0]).q, Vu0::Vec::Of(cam->planes[1]).q, Vu0::Vec::Of(cam->planes[2]).q, d.q, ones, r.q) ^ 0xF0) != 0) {
            ResetTextPointToHalf(obj);
        } else {
            objs[shown++] = obj;
            ProjectPointToCamera((Camera*)g_camera, &pos, (f32*)&screen);
            Vu0::Vec e = Vu0::Sub(Vu0::Vec::Of(screen), Vu0::Vec::Of(D_00261190));
            f32 c = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(e, e)));
            if (c < best) {
                nearest = obj;
                best = c;
            }
        }
    }
    for (i = 0; i < shown; i++) {
        TextPointObject* obj = objs[i];
        ConvertPositionToWorld(obj, &pos);
        char buf[0x100];
        Layout_137228 layout;
        const char* s = (const char*)obj->text;
        char* t = buf;
        for (; *s != 0; s++) {
            if (*s == '_') {
                *t = ' ';
            } else {
                *t = *s;
            }
            t++;
            if ((u32)(t - buf) >= 0xFF) {
                break;
            }
        }
        *t = 0;
        const f32* k = D_002611A0;
        const ValueRange* lim = &g_unitRange;
        ProjectPointToCamera((Camera*)g_camera, &pos, (f32*)&screen);
        Vu0::Vec e = Vu0::Vec::Of(screen);
        f32 len = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(e.q, e.q)));
        f32 scale = k[0] + len * (k[1] + len * k[2]);
        f32 alpha = lim->Limit(scale);
        if (obj != nearest) {
            alpha *= D_002611BC;
        }
        obj->f54 = ApproachValueWithRamp(obj->f54, alpha, g_gameClock[5], (RampProfile*)D_002611B0, 0);
        obj->f58 = ApproachValueWithRamp(obj->f58, obj == nearest ? D_00261184 : D_00261188, g_gameClock[5], (RampProfile*)D_002611C0, 0);
        PushFontScale(self->font, obj->f58, obj->f58);
        ScreenLayout::Reset(&layout);
        f32 h = MeasureFontStringHeight(self->font, (u8*)buf, D_002611CC * obj->f58);
        f32 x = screen.x * 320.0f + 320.0f + D_002611D0 * obj->f58;
        f32 y = screen.y * -246.400009f + 246.400009f + D_002611D4 * obj->f58 - h;
        layout.x = x;
        layout.y = y;
        layout.w = D_002611CC * obj->f58;
        layout.h = h;
        PanelStyle style(D_00261168);
        Font* font = GetFontById(2);
        style.font = (s32)font;
        ((u8*)&style.color)[3] = (s32)(alpha * (f32)((u8*)&style.color)[3]);
        style.paddingX *= obj->f58;
        style.paddingY *= obj->f58;
        StyleDrawer::Draw((Font**)&style, &layout, q);
        ((u8*)&layout.color)[3] = (s32)(alpha * (f32)((u8*)&layout.color)[3]);
        DrawFontString(self->font, buf, (StringLayout*)&layout, 0, q);
        BeginGifTag(q, 0xC1, 3, 0x441);
        AddGifRgbaEntry(q, ((u32*)self->frame)[6]);
        AddGifXyzfEntry(q, CenterFrameMath::ScreenX(x + D_002611D8 * obj->f58), CenterFrameMath::ScreenY(y + h + D_002611DC * obj->f58), 0, 0);
        y = screen.y * -246.400009f + 246.400009f;
        x = screen.x * 320.0f + 320.0f;
        AddGifXyzfEntry(q, CenterFrameMath::ScreenX(x), CenterFrameMath::ScreenY(y), 0, 0);
        PopFontScale(self->font);
    }
}

void DrawTextPanelBlocks(T217D_440* self, PacketWriter* q)
{
    if (self->state == 1)
    {
        if ((u32)MaskWorldBitsBySave() & 0x800)
        {
            DrawTextPanelMarkers(self, q);
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
                f32 r = ApproachValueWithRamp(self->blockB[i], self->blockA[i] ? 1.0f : 0.0f, g_gameClock[2], (RampProfile*)&D_00261260[2], 0);
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
        PlayerListHolder* g = (PlayerListHolder*)FindFirstObjectById(g_currentWorld, 0x105, 0x495, 0);
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
        PlayerListHolder* g = (PlayerListHolder*)FindFirstObjectById(g_currentWorld, 0x105, 0x495, 0);
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
    if (IsObjectAttached((BaseObject*)a->obj) == 0) {
        return 1;
    }
    if (IsObjectAttached((BaseObject*)b->obj) == 0) {
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

    GetNumberedItemFlag((NumberedItem*)a->obj, &flag);
    if (flag != 0) {
        return 1;
    }
    GetNumberedItemFlag((NumberedItem*)b->obj, &flag);
    if (flag != 0) {
        return -1;
    }
    if (a->key < b->key) {
        return -1;
    }
    return 1;
}

struct PanelEntry {
    void* obj;              // 0x00
    f32 key;                // 0x04
    f32 radius;             // 0x08
    u8 pad0C[4];
    PanelEntryPosition v;   // 0x10
};

typedef s32 (*SortCompareFn)(void* a, void* b);
void HeapSortRecords(void* records, s32 n, s32 size, SortCompareFn cmp);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
void CopyMemory(void* dst, void* src, u32 size);
void* CreateEffect(s32 kind, EffectOwner* sys);

void CollectPanelEntriesOfClass(T217D_440* self, s32 kind, void* a2, void* a3, s32 limit, s32 a5, f32 range)
{
    PanelEntry entries[0x80];
    void* objs[0x80];
    Vec02 d;
    s32 want;
    s32 i = 0;
    s32 n = GatherObjectsById(g_currentWorld, 0x105, kind, 0, 0x80, objs);
    PanelEntry* e;
    for (; i < n; i++) {
        e = &entries[i];
        e->obj = objs[i];
        ((void (*)(void*, PanelEntryPosition*, f32*))a2)(e->obj, &e->v, &e->radius);
        e->key = Vu0::Distance(e->v, *(PanelEntryPosition*)g_camera->f40) - e->radius;
    }
    HeapSortRecords(entries, n, 0x20, kind == 0x2E ? CompareEntriesFlaggedLast : CompareEntriesByAttachedKey);
    s32 mayStart = 1;
    FillMemory(self->blockA, 0, 0x10);
    if (!(D_00261274 < g_gameClock[1] - *(f32*)&self->countA)) {
        mayStart = 0;
    }
    for (i = 0; i < n;) {
        e = &entries[i];
        if (kind == 0x2E) {
            GetNumberedItemFlag((NumberedItem*)e->obj, &want);
            want = want == 0 && self->state == 1 && i < limit && e->key < range;
        } else {
            want = self->state == 1 && IsObjectAttached((BaseObject*)e->obj) && i < limit && e->key < range;
        }
        CameraHeading* cam = g_camera;
        u128 ones = Vu0::Ones();
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(e->v), Vu0::Q(cam->f40));
        u32 signs = Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), Vu0::Q(d), ones, Vu0::ScalarAt(e->radius)) ^ 0xF0;
        s32 visible = signs == 0;
        if (want && !visible) {
            f32 yaw = ArctangentOfRatio(d.y, d.x);
            u128 v = Vu0::Q(d);
            f32 rise = ArctangentOfRatio(d.z, Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(v, v))));
            yaw = WrapAngle(yaw - g_camera->heading);
            f32 pitch = WrapAngle(rise - g_camera->pitch);
            if (g_camera->f1C4 * (g_camera->f1E0 * 0.45f) < yaw) {
                self->blockA[0] = 1;
            } else if (yaw < g_camera->f1C4 * (g_camera->f1E0 * -0.45f)) {
                self->blockA[1] = 1;
            } else if (g_camera->f1C4 * 0.45f < pitch) {
                self->blockA[2] = 1;
            } else if (pitch < g_camera->f1C4 * -0.45f) {
                self->blockA[3] = 1;
            }
        }
        s32 next = i + 1;
        void* effect = 0;
        s32 j;
        for (j = 0; j < self->count; j++) {
            if (self->markers[j].obj == e->obj) {
                effect = self->markers[j].effect;
                break;
            }
        }
        if (effect != 0) {
            if (!want) {
                SetEffectPhase((Effect*)effect, 2);
                CopyMemory(&self->markers[j], &self->markers[j + 1], (self->count - j - 1) * 8);
                self->count--;
            }
        } else if (want && mayStart && visible) {
            void* fx = CreateEffect(0x12, 0);
            if (fx != 0) {
                mayStart = 0;
                (*(void (**)(void*, PanelEntryPosition*, s32, f32))*(void**)fx)(fx, &e->v, 0, 1.0f);
                *(s32*)((u8*)fx + 0x20) = a5;
                *(void**)((u8*)fx + 0x130) = a3;
                *(void**)((u8*)fx + 0x134) = e->obj;
                SetEffectPhase((Effect*)fx, 0);
                *(f32*)&self->countA = g_gameClock[1];
                self->markers[self->count].obj = e->obj;
                self->markers[self->count].effect = fx;
                self->count++;
            }
        }
        i = next;
    }
}

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
                RemoveEffect((Effect*)e->handle);
                FillMemory(self->blockB, 0, 16);
            } else {
                SetEffectPhase((Effect*)e->handle, 2);
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

void RefreshPanelEntries(T217D_440* self, PadRecord* pad)
{
    LevelBit flag;
    GetCurrentLevelBit((u32*)&flag);
    if ((MaskWorldBitsBySave() & flag.v) == 0) {
        ReleasePanelEntries(self, 0, 1);
        return;
    }
    ReleasePanelEntries(self, 1, 0);
    if (self->bankState == 1) {
        f32 k = 3.4028235e38f;
        World* world = g_currentWorld;
        CollectPanelEntriesOfClass(self, 0x2E, func_00135E20 + 0x10, func_00135E40 + 8, 5, (s32)world->slot1CE8[23], k);
        CollectPanelEntriesOfClass(self, 0x21, func_00135E20 + 0x10, func_00135E40 + 8, 5, (s32)(g_currentWorld)->slot1CE8[27], k);
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
        f32 sum = p->stickX + p->secondStickX;
        StickLimits t0 = D_00249D00;
        StickLimits t1 = D_00249D10;
        f32 u = (sum < lo) ? lo : ((hi < sum) ? hi : sum);
        f32 v = p->stickY;
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
        *(Quad_136040*)&r = ApproachPointWithRamp(*(Quad_136040*)&va, *(Quad_136040*)&vb, g[2], (RampProfile*)((0.0001f < p->stickMagnitude + p->secondStickMagnitude) ? &t0 : &t1), 0);
        self->tickScroll += u * -0.08f;
        self->stickX = r.x;
        self->stickY = r.y;
        self->tickScroll = WrapModulo(self->tickScroll, 1.0f);
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
        GetCurrentLevelBit((u32*)&in);
        if (MaskWorldBitsBySave() & in.v) {
            if (MaskWorldBitsBySave() & D_00261120[self->savedBank]) ReleasePanelEntries(self, self->savedBank, 1);
        }
        if (MaskWorldBitsBySave() & 0x800) {
            n = GatherObjectsById(g_currentWorld, 0x205, 0x82, 0, 0x100, arr);
            n = ClampBelow::Of(n, 0x100);
            if (n > 0) {
                void** p = arr;
                s32 i = n;
                do { i--; ResetTextPointToHalf((TextPointObject*)*p); p++; } while (i != 0);
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
        SetStepSequenceState((StepSequence*)self->child, 2);
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
    InitTextReader((TextReader*)&buf, self->text, self->font);
    lim = 280.0f;
    if ((r = self->state) == s1) lim = 380.0f;
    s1 = 0;
    WrapTextLines((TextReader*)&buf, lim);
    PopFontScale(self->font);
    RewindTextReader((TextReader*)&buf);
    while ((r = ReadTextChar((TextReader*)&buf)) != 0) {
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
    InitTextReader((TextReader*)buf, &self->text[0], self->font);
    s32 n = CountTextChars(buf);
    s32 v = (s32)((g_gameTime - self->textSince) * self->charsPerSecond);
    return v >= n;
}

void SetTextPanelSubject(T217D_440* self, BaseObject* value) { self->f2FC = value; }

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

extern PacketWriter g_gsPacketWriter;
s32 AreMenusClosed(void);
void DrawCompassStrip(T217D_440* self, PacketWriter* gs);
void DrawTextPanelControlLabels(T217D_440* self, PacketWriter* gs);
void AddDmaRefTag(PacketWriter* gs, void* data, s32 size);
void SeekTextReader(TextReader* self, s32 n);
void *AppendString(void* dst, const char* src);
void DrawAlignedText(TextReader* self, Layout_137228* p, Vec4U* clip, PacketWriter* s);

// A byte from a toward b by t, as the panel fades its alpha (the difference taken as an integer).
struct ByteLerp {
    static u8 Of(u8 a, u8 b, f32 t)
    {
        if (a == b) {
            return b;
        }
        if (a < b) {
            return a + (s32)(t * ((f32)(b - a) + 0.999f));
        }
        return b + (s32)((1.0f - t) * (0.999f - (f32)(b - a)));
    }
};

// A layout placed and sized, in a colour, its other words cleared.
struct PanelLayout {
    static s32* Words(Quad4& q)
    {
        return q.w;
    }

    static Layout_137228* Set(Layout_137228* l, f32 x, f32 y, f32 w, f32 h, s32 color)
    {
        Quad4 col;
        l->Pos(x, y);
        l->Size(w, h);
        col.w[0] = color;
        l->Color(Words(col));
        l->SetF14(0);
        l->SetF18(0);
        return l;
    }
};

// Draws the panel: its frames by state, then its box, the text typed so far (a cursor blinking
// at its end) scrolled to the line being typed, and the pulsing button glyph.
void DrawTextPanel(T217D_440* self)
{
    if (AreMenusClosed() == 0) {
        return;
    }
    switch (self->state) {
    case 1:
    case 2:
        DrawTextPanelCenterFrame(self, &g_gsPacketWriter);
        AddDmaRefTag(&g_gsPacketWriter, self->bands, self->bandsSize);
        DrawCompassStrip(self, &g_gsPacketWriter);
        DrawTextPanelControlLabels(self, &g_gsPacketWriter);
        DrawTextPanelBorders(self, &g_gsPacketWriter);
        DrawTextPanelBlocks(self, &g_gsPacketWriter);
        break;
    case 4:
        break;
    case 5:
        DrawTextPanelCenterFrame(self, &g_gsPacketWriter);
        break;
    }
    f32 scale = 1.0f;
    if (self->state == 4) {
        scale = 0.8f;
    }
    if (self->state == 3 && self->text[0] == 0) {
        return;
    }
    PushFontScale(self->font, scale, scale);
    Rgba4 color = *(Rgba4*)&self->highlight;
    Rgba4 frameColor;
    if (self->frame != 0) {
        frameColor = *(Rgba4*)&((PanelStyle*)self->frame)->color;
    } else {
        *(u32*)&frameColor = 0;
    }
    f32 offY = 0.0f;
    f32 offX = offY;
    f32 line = (f32)self->font->height * self->font->sy;
    f32 width = 280.0f;
    f32 height = line * 3.0f;
    switch (self->state) {
    case 3:
        offY = -8.0f;
        break;
    case 4:
        height = line + line;
        width = 380.0f;
        offX = -50.0f;
        offY = 40.0f;
        break;
    }
    s32 grey = 0xFF808080;
    Layout_137228 box;
    PanelLayout::Set(&box, offX + 180.0f, offY + 386.800018f, width, height, grey);
    f32 fade = 1.0f;
    if (D_002708E0.target != 0) {
        fade = D_002708E0.blend <? fade;
    }
    if (D_00271558.target != 0) {
        fade = D_00271558.blend <? fade;
    }
    if (fade < 1.0f) {
        u8 a = ByteLerp::Of(0, color.a, fade);
        Rgba4 t = color;
        t.a = a;
        color = t;
        a = ByteLerp::Of(0, frameColor.a, fade);
        Rgba4 u = frameColor;
        u.a = a;
        frameColor = u;
    }
    if (self->state == 3 && self->frame != 0) {
        PanelStyle* style = (PanelStyle*)self->frame;
        Rgba4 saved = *(Rgba4*)&style->color;
        *(Rgba4*)&style->color = frameColor;
        StyleDrawer::Draw(self->frame, &box, &g_gsPacketWriter);
        *(Rgba4*)&((PanelStyle*)self->frame)->color = saved;
    }
    if (self->text[0] != 0) {
        TextScratch all;
        InitTextReader((TextReader*)&all, self->text, self->font);
        s32 total = CountTextChars(&all);
        s32 shown = (s32)((g_gameClock[1] - self->textSince) * self->charsPerSecond);
        if (!(shown < total)) {
            shown = total;
        }
        s32 row;
        for (row = 0; row < self->lineCount; row++) {
            if (shown < self->lineBreaks[row]) {
                break;
            }
        }
        f32 scroll;
        if (row > 0 && row < self->lineCount) {
            f32 start = (f32)self->lineBreaks[row - 1] / self->charsPerSecond;
            f32 end = (f32)self->lineBreaks[row] / self->charsPerSecond;
            scroll = ((g_gameClock[1] - self->textSince) - start) / (end - start);
        } else {
            scroll = 0.0f;
        }
        char text[0x200];
        CopyString(text, self->text);
        row++;
        TextScratch typed;
        InitTextReader((TextReader*)&typed, text, self->font);
        SeekTextReader((TextReader*)&typed, shown);
        s32 cursor;
        if (shown < total) {
            cursor = 1;
        } else {
            cursor = (s32)(g_gameClock[1] * 4.0f) & 1;
        }
        if (cursor != 0) {
            AppendString(text, "&.~ffffff|");
        }
        f32 y = ((f32)row + scroll) * ((f32)self->font->height * self->font->sy);
        Layout_137228 lines;
        f32 noScroll = 0.0f;
        PanelLayout::Set(&lines, offX + 180.0f, (offY + 386.800018f) - (noScroll >? (y - height)), width, y,
                         *(s32*)&color);
        DrawAlignedText((TextReader*)&typed, &lines, (Vec4U*)&box, &g_gsPacketWriter);
    }
    PopFontScale(self->font);
    if (self->buttonGlyph != 0) {
        char glyph[2] = { self->buttonGlyph, 0 };
        f32 s = Cosine(WrapAngle(g_gameTime * 10.0f)) * 0.5f + 0.5f;
        f32 size = (1.0f - s) * 0.3f + s * 0.4f;
        Font* font = GetFontById(1);
        f32 x;
        f32 y;
        if (self->state == 4) {
            x = 532.0f;
            y = 472.800018f;
        } else {
            x = offX + 482.0f;
            y = offY + 472.800018f;
        }
        PushFontScale(font, size, size);
        s32 glyphColor = 0xFF808080;
        Layout_137228 at;
        Layout_137228* l = PanelLayout::Set(&at, x, y, 0.0f, 0.0f, glyphColor);
        l->f14 = 1;
        l->f18 = 1;
        DrawFontString(font, glyph, (StringLayout*)l, 0, &g_gsPacketWriter);
        PopFontScale(font);
    }
}

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

void EndTextPanelState(T217D_440* self)
{
    if (self->child != 0) {
        SetStepSequenceState((StepSequence*)self->child, 4);
    } else {
        SetTextPanelState(self, 0);
    }
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

inline void Layout_137228::SetF18(s32 value)
{
    f18 = value;
}
