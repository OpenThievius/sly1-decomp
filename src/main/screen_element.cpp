// SPDX-License-Identifier: AGPL-3.0-or-later
// The source file from 0x1AA268 to 0x1AECB0, built whole (config/us/files.tsv): the screen
// elements' shared methods (func_001AA268 sets one up) and those of the screen elements built
// on them, up to the static initialiser that builds this file's text styles (func_001AEA70)
// and its _GLOBAL_$I$ (func_001AEC90). Its .rodata (0x24CBD0 to 0x24CFBB) is the
// strings, FLT_MAX literals and jump tables of its functions; its .data (0x2743A0 to 0x2744B8)
// is the globals below, each defined before the first function that reads it, so that the
// strings of the name tables land between their neighbours' as in retail. Named after the
// screen elements (screen_element.h) whose methods it holds.
#include "common.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "world.h"
#include "object_pool.h"
#include "screen_element.h"
#include "font.h"
#include "shapes.h"
#include "game_clock.h"
#include "game_progress.h"
#include "text_reader.h"
#include "globals.h"
#include "packet_writer.h"
#include "screen_fade.h"
#include "layout_137228.h"
#include "texture_table.h"
#include "cursor_animator.h"
#include "warp_page.h"
#include "ramp_profile.h"
#include "asm_func.h"
#include "fpu.h"
#include "functions/group_marker.h"
#include "functions/memory_card.h"
#include "functions/oscillator.h"
#include "functions/placed_object.h"
#include "functions/pooled_object.h"
#include "functions/warp_menu.h"
struct BaseObject;
struct Mat02;


// Types other files define, named by the parameters of their functions declared here.
struct BackgroundJob;

extern void* const g_screenElements[];

// A 28-byte text style the static initialiser (func_001AEA70) clears (func_001F5C0C with 0x1C)
// and then fills.
struct TextStyle {
    void* font;
    u8 f04;
    u8 pad05[3];
    f32 f08;
    f32 f0C;
    f32 f10;
    f32 f14;
    u32 color;
};

// The font object's calls.
struct Font;
Font* GetFontById(s32 k);
void PushFontScale(Font* font, f32 x, f32 y);
f32 MeasureFontString(Font* self, const char* s);
struct PacketWriter;
struct StringLayout;
struct Vec4U;
void DrawFontString(Font *self, const char *str, StringLayout *par, Vec4U *clip, PacketWriter *s);
void PopFontScale(Font* font);
void* InitTextReader(TextReader* self, char* text, Font* font);
void DrawAlignedText(TextReader* self, Layout_137228* p, Vec4U* clip, PacketWriter* s);


extern f32 g_gameTime;
extern f32 g_frameDt;

void StepTimer(T217D_510* self, f32 value);

extern s32 g_defaultFont;

typedef void (*VirtualCall_1AA790)(void* a, void* b, void* c, void* d);



typedef void* (*VFn_1A9960)(void* self);

extern ElementPlaceTable g_elementPlaces;

extern "C" void* FillMemory(void* p, s32 value, s32 size);




extern u8 g_padRouting[];

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();

extern s8 g_fontEscapeKeys[];
extern u8 g_charClassFlags[];
s32 FormatToString(char* dst, const char* fmt, ...);
void* CopyString(void* dst, const char* src);
PlacedObject* CreateObjectCopy(PlacedObject* a, World* b, BaseObject* c);

void DrawCyclingGlyphElement(u8* a);
extern Quadratic16 g_slideEaseOutCoefficients;

s32 FormatToStringBounded(char* dst, s32 cap, const char* fmt, ...);
extern s32 D_002751D4;

struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

void DrawScreenElementText();
f32 GetScreenElementSlideInTime();
f32 GetScreenElementHoldTime();
f32 GetScreenElementSlideOutTime();
void ResetScreenElement();
void ShowScreenElement();
void HideScreenElement();
void SetScreenElementClock();
s32 AreScreenElementsTogether();
void SetScreenElementText();
void SetScreenElementMode();
void UpdateCounterCaption();
void InitGauge();
void DrawGauge();
void InitPointerTextCaption();
void SetElementTextAfterSlideOut();
void SetElementModeApplyingPendingText();
s32 AreElementsTogetherOrPending();
void ShowElementUnlessTextPending();
void HideElementOrDropPendingText();
void DrawSlidingGlyphElement();
void InitCopiedTextCaption();
void SetElementTextCopiedAfterSlideOut();
void SetElementModeApplyingCopiedText();
void ShowElementUnlessCopiedTextPending();
void HideElementOrDropCopiedText();
void DrawMessageElement();
void InitHintGlyphElement();
void UpdateHintGlyphElement();
void DrawHintGlyphElement();
void InitTitleElement();
void DrawTitleElement();
void InitPromptElement();
void SetElementModeRebuildingText();
void UpdatePromptElement();
void DrawPromptElement();
void InitLetterboxElement();
void SetElementModeFollowingFade();
void DrawLetterboxElement();
void InitLetterGlyphElement();
void DrawLetterGlyphElement();
void InitCyclingGlyphElement();
void SetElementModeClearingFlag();

extern "C" s32 GetStringLength(const char* s);
void* CopyString(void* dst, const char* src);
void MeasureText(TextReader*, f32, f32*, f32*);

void FormatCounterCaption(T217D_E30* self);
f32 SumTextWidth(TextReader* loc);


s32 IsFontLoaded(s32 k);

// A text reader and the size MeasureText gives for it.
struct MeasuredText {
    TextReader reader;
    f32 x;
    f32 y;
};

extern "C" s32 GetStringLength(const char* s);
void* CopyString(void* dst, const char* src);
void MeasureText(TextReader* self, f32 f, f32* out1, f32* out2);

void RebuildPromptText(T217D_4C0* self);


extern TextStyle g_framedElementStyle;


extern TextStyle g_pointerCaptionStyle;

extern "C" s32 CompareStrings(const char* a, const char* b);


extern u8 g_elementStack[];

s32 MatchesObjectId(void* key, s32 item);


extern TextStyle g_copiedCaptionStyle;

// NEAR: register and load order of D_00262C84 vs D_00269988 (retail keeps the x load in v1, ours in a0; xori placed differently)

struct Node_001AE178 { u8 pad0[0xC]; f32 f0C; };
extern s32 D_00275BF0;
extern s32 D_00262C84;
extern Node_001AE178* D_00269988;

// NEAR: the store of func_0015C1C0 result is before the float load and call; retail puts it in the delay slot of the func_001AA788 call

extern f32 g_cyclingGlyphElementScale;
// The letter func_001AEA08 picks: PAL reads the table's bytes unsigned (docs/VERSIONS.md).
#ifdef VERSION_EU
typedef u8 Letter_1AEA08;
#else
typedef s8 Letter_1AEA08;
#endif
Letter_1AEA08 GetCyclingGlyph(void);

extern f32 g_promptFontScaleX;
// The vertical scale of the clone func_001ADF28 makes of its font (D_0027446C is the
// horizontal one); the label runs on over a word nothing reads.
extern f32 g_promptFontScaleY[2];
extern TextStyle g_promptStyle;

s32 MatchesObjectId(s32 value, s32 item);

s32 MatchesObjectId(void* a, s32 b);

typedef void (*VFn_1AF3B8)(void* self);
void* CreateObjectCopy(void* a, void* b, void* c);

extern f32 g_elapsedTime;
extern f32 D_0027240C;
extern s32 D_00272420;
extern u8 g_backgroundJob[];

void* ComputeCompletionPercent(GameProgress* progress);


void SetElementTextFromEntry(ScreenElement* self, s32 hi, s32 lo);


extern f32 g_titleFontScaleX;
extern f32 g_titleFontScaleY;
extern TextStyle g_titleStyle;

void* FindAnimRecord(s32 key);

extern f32 g_letterGlyphScale;

struct ProgressEntry {
    u32 flags;
    u32 pad;
    f32 time;
};

extern s32 FormatToString(char* dst, const char* fmt, ...);
extern s32 AppendString(void* dst, const char* src);



u32 GetEntryFlags(s32 id);
char* GetEntryName(s32 id);

extern "C" f32 Cosine(f32 x);

extern const char* g_promptTexts[];
extern const char* g_noControllerText;

// A colour and a text reader, one frame slot (func_001ADFF0).
struct ColoredText { T217D_Rgba col; u8 pad[12]; TextReader reader; };

s32 FormatToString(char* dst, const char* fmt, ...);
void* CopyString(void* dst, const char* src);
f32 MeasureTextWidth(TextReader* self);
f32 MeasureTextHeight(TextReader* self, f32 limit);


extern const char* g_worldTitles[];

void CountCategoryFlags(s32 key, s32* a1, s32* a2, s32* a3);
extern "C" s32 GetStringLength(const char* s);

struct GlyphCycleTable { s8* p; s32 pad; };
extern GlyphCycleTable g_cyclingGlyphSet;



void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* p, u64 a, u64 b);
void AddGifRgbaEntry(PacketWriter* p, u32 value);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);


void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* p, u64 a, u64 b);
void AddGifRgbaEntry(PacketWriter* p, u32 value);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
void CloseGifTag(PacketWriter* p, s32 a);

extern u8 D_00275B00[];

// A layout with its setters as calls (SetTextLayoutPosition and the others).
struct LayoutBuilder : Layout_137228 {
    void Pos(f32 x, f32 y) { ((Layout_137228*)this)->Pos(x, y); }
    void Size(f32 x, f32 y) { ((Layout_137228*)this)->Size(x, y); }
    void Color(s32* c) { ((Layout_137228*)this)->Color(c); }
    void FlagA(s32 f) { ((Layout_137228*)this)->SetF14(f); }
    void FlagB(s32 f) { ((Layout_137228*)this)->SetF18(f); }
};
struct StyleDrawerBuilder {
    static void Draw(Font** h, LayoutBuilder* out, void* tbl)
    {
        if (*h != 0) {
            const FontVt* vt = (*h)->vt;
            // the class's this-adjustment from its vtable, not a field
            vt->drawBox((Font*)((u8*)*h + vt->adj9), h, out, tbl);
        }
    }
};




void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* p, u64 a, u64 b);
void AddGifRgbaEntry(PacketWriter* p, u32 rgba);
void AddGifUvEntry(PacketWriter* p, s32 a, s32 b);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
u64 GetTextureRegisterBits(TextureTable* t, s32 i, s32 j);



void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* f, u64 a, u64 b);
void AddGifRgbaEntry(PacketWriter* f, u32 v);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
struct LayoutByValue : Layout_137228 {
    void Pos(f32 x, f32 y) { ((Layout_137228*)this)->Pos(x, y); }
    void Size(f32 x, f32 y) { ((Layout_137228*)this)->Size(x, y); }
    void Color(s32 c) { ((Layout_137228*)this)->Color(&c); }
    void FlagA(s32 f) { ((Layout_137228*)this)->SetF14(f); }
    void FlagB(s32 f) { ((Layout_137228*)this)->SetF18(f); }
};

struct FontCalls {
    // the class's this-adjustment from its vtable, not a field
    static f32 Advance(Font* f, s32 ch) { return f->vt->width((Font*)((u8*)f + f->vt->adj3), ch); }
    // the class's this-adjustment from its vtable, not a field
    static void Begin(Font* f, Vec4U* clip, PacketWriter* d) { f->vt->begin((Font*)((u8*)f + f->vt->adj4), clip, d); }
    // the class's this-adjustment from its vtable, not a field
    static void Glyph(Font* f, s32 ch, s32 color, PacketWriter* d, f32 x, f32 y) { f->vt->draw(x, y, (Font*)((u8*)f + f->vt->adj6), ch, color, d); }
    // the class's this-adjustment from its vtable, not a field
    static void End(Font* f, Vec4U* clip, PacketWriter* d) { f->vt->end((Font*)((u8*)f + f->vt->adj7), clip, d); }
};

struct ClampFloatSelect {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        return x < lo ? lo : (hi < x ? hi : x);
    }
};

struct VEnt_1AC0E8 { s16 delta; s16 index; void (*fn)(void* self, f32 x, f32 y, s32 a, s32 b, void* c); };
struct Text_1AC0E8 { u8 pad[0x4C]; VEnt_1AC0E8* vtbl; };
extern RampProfile g_gaugeFillRamp;

extern "C" f32 Sine(f32 x);

struct ChannelLerp {
    static u8 Of(s32 a, s32 b, f32 t)
    {
        if (a == b) return b;
        if (a < b) return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
        return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
    }
};

struct LerpRgba4 {
    static void Do(Rgba4* out, Rgba4* a, Rgba4* b, f32 t)
    {
        Rgba4 r;
        r.r = ChannelLerp::Of(a->r, b->r, t);
        r.g = ChannelLerp::Of(a->g, b->g, t);
        r.b = ChannelLerp::Of(a->b, b->b, t);
        r.a = ChannelLerp::Of(a->a, b->a, t);
        *out = r;
    }
};

void ConstructScreenTextStyles(s32 a, s32 b);

// Gives a text element the defaults: the default font, scale 1.0, colour 0xFF808080 and an
// empty text.
void SetupScreenElementText(ScreenElement* self)
{
    s32 value = g_defaultFont;
    u32 flags = 0xFF808080;
    self->font = (Font*)value;
    self->scale = 1.0f;
    self->color = flags;
    self->text[0] = 0;
}

// The slide's easing, 2p - p * p: a quadratic's coefficients, constant first, as Quadratic16
// (include/shapes.h) holds them. Its alignment to 16 starts the file's .data on 16, 8 bytes after
// object_pool.cpp's last screen element (D_00274118, 0x280 bytes) ends: the linker's padding.
Quadratic16 g_slideEaseOutCoefficients = { { 0.0f }, 2.0f, -1.0f, 0.0f };

// Per-frame slide of a screen element between its hidden and shown positions. Mode 1 slides in
// (blend rising 0 to 1 over the time slot 17 gives), 2 holds (ends after the hold time of slot
// 18), 3 slides out (time of slot 19); the position follows an ease-out curve of the blend. It
// calls slot 22 with the new mode.
void UpdateScreenElementSlide(ScreenElement* self) {
    f32 t = *self->clock;
    s32 s = self->mode;
    switch (s) {
    case 2: {
        f32 d = self->vt->m12(self);
        if (d != 0.0f) {
            if (d <= t - self->since) s = 3;
        }
        break; }
    case 1: {
        f32 d = self->vt->m11(self);
        f32 zero = 0.0f;
        f32 x;
        if (d != zero) {
            f32 one = 1.0f;
            x = (t - self->since + self->offset) / d;
            if (x < zero) x = zero;
            else if (one < x) x = one;
            self->blend = x;
        }
        if (self->blend >= 1.0f) s = 2;
        break; }
    case 3: {
        f32 d = self->vt->m13(self);
        f32 zero = 0.0f;
        f32 x;
        if (d != zero) {
            f32 one = 1.0f;
            x = (t - self->since + self->offset) / d;
            f32 y = x < zero ? zero : (one < x ? one : x);
            self->blend = 1.0f - y;
        }
        if (self->blend <= 0.0f) s = 0;
        break; }
    }
    if (s == self->mode) {
        f32 p = self->blend;
        f32 k = g_slideEaseOutCoefficients.x + p * (g_slideEaseOutCoefficients.y + p * g_slideEaseOutCoefficients.z);
        self->x = self->hiddenX + k * (self->shownX - self->hiddenX);
        self->y = self->hiddenY + k * (self->shownY - self->hiddenY);
        PlaceAnchoredScreenElements(self);
    }
    self->vt->m16(self, s);
}

// Copies the text into the element (or clears it) and sizes the element to the text measured at
// its scale.
void SetScreenElementText(ScreenElement* self, const char* arg)
{
    if (arg && GetStringLength(arg)) {
        CopyString(self->text, arg);
    } else {
        self->text[0] = 0;
    }
    PushFontScale(self->font, self->scale, self->scale);
    TextReader m;
    InitTextReader(&m, self->text, self->font);
    f32 x, y;
    MeasureText(&m, 0.0f, &x, &y);
    SetScreenElementSize(self, x, y);
    PopFontScale(self->font);

}

// Rewrites the element's text: a character the element's font lacks is wrapped in an escape that
// selects font 3 or 4 where that has it, and a '/' followed by digits gets a small-digits escape.
// The result replaces the text.
void SubstituteScreenElementGlyphs(ScreenElement* self)
{
    char buf[0x200];
    char* s = self->text;
    char* d = buf;
    if (*s != 0) {
        do {
            if (self->font->Has(*s) == 0) {
                if (GetFontById(3)->Has(*s) != 0) {
                    d += FormatToString(d, "&%c%c&.", g_fontEscapeKeys[3], *s);
                    goto next;
                }
                if (GetFontById(4)->Has(*s) != 0) {
                    d += FormatToString(d, "&%c%c&.", g_fontEscapeKeys[4], *s);
                    goto next;
                }
            }
            if (*s == 0x2F) {
                if (g_charClassFlags[s[1]] & 4) {
                    d += FormatToString(d, "^05~b2a83d/");
                    s++;
                    while (*s != 0 && (g_charClassFlags[*s] & 4)) {
                        *d = *s;
                        s++;
                        d++;
                    }
                    d += FormatToString(d, "~.^.");
                    s--;
                } else {
                    *d = *(u8*)s;
                    d++;
                }
            } else {
                *d = *(u8*)s;
                d++;
            }
        next:
            s++;
        } while (*s != 0);
    }
    *d = 0;
    CopyString(self->text, buf);
}

void SetScreenElementScale(ScreenElement* self, f32 v)
{
    self->scale = v;
}

// Draws the element's frame, if any, and its text at its position and size.
void DrawScreenElementText(ScreenElement* self)
{
    u8 out[32];
    s32 tmp;
    void* handle;
    f32 x;

    if (self->text[0] != 0) {
        f32 p = self->w;
        f32 q = self->h;
        s32 held = self->color;
        ((Layout_137228*)out)->Pos(self->x, self->y);
        ((Layout_137228*)out)->Size(p, q);
        tmp = held;
        ((Layout_137228*)out)->Color(&tmp);
        ((Layout_137228*)out)->SetF14(0);
        ((Layout_137228*)out)->SetF18(0);

        handle = self->frame;
        if (handle != 0) {
            void* obj = *(void**)handle;
            if (obj != 0) {
                const FontVt* vt = ((Font*)obj)->vt;
                // the class's this-adjustment from its vtable, not a field
                vt->drawBox((Font*)((u8*)obj + vt->adj9), handle, out, &g_gsPacketWriter);
            }
        }
        x = self->scale;
        PushFontScale(self->font, x, x);
        DrawFontString(self->font, &self->text[0], (StringLayout*)out, 0, &g_gsPacketWriter);
        PopFontScale(self->font);
    }
}

LINKER_REMNANT(func_001AA890);

f32 GetScreenElementSlideInTime(ScreenElement* self)
{
    return self->inTime;
}

f32 GetScreenElementHoldTime(ScreenElement* self)
{
    return self->holdTime;
}

f32 GetScreenElementSlideOutTime(ScreenElement* self)
{
    return self->outTime;
}

void SetScreenElementSlideInTime(ScreenElement* self, f32 v)
{
    self->inTime = v;
}

void SetScreenElementHoldTime(ScreenElement* self, f32 v)
{
    self->holdTime = v;
}

void SetScreenElementSlideOutTime(ScreenElement* self, f32 v)
{
    self->outTime = v;
}

// Puts the element back to mode 0 (m16, 0).
void ResetScreenElement(ScreenElement* self)
{
    self->vt->m16(self, 0);
}

// Shows the element: in mode 0 or 3 it starts the slide-in (m16, 1), in mode 2 it only restarts
// its hold timer.
void ShowScreenElement(ScreenElement* self)
{
    s32 s = self->mode;
    if (s == 2) {
        goto store;
    }
    if (s < 3) {
        if (s == 0) {
            goto call;
        }
        return;
    }
    if (s != 3) {
        return;
    }
call:
    self->vt->m16(self, 1);
    return;
store:
    self->since = *self->clock;
}

// Starts the slide-out (m16, 3) of an element in mode 1 or 2.
void HideScreenElement(ScreenElement* self)
{
    s32 m = self->mode;
    if (m < 3) {
        if (m > 0) {
            self->vt->m16(self, 3);
        }
    }
}

// Changes a screen element's mode (0 hidden, 1 sliding in, 2 shown, 3 sliding out): computes how
// far into the slide it is, snaps the position for 0 and 2, remembers the time and places the
// element again when it was fully hidden or shown.
void SetScreenElementMode(ScreenElement* self, s32 mode)
{
    if (self->mode == mode) {
        return;
    }
    s32 notify = 0;
    switch (mode) {
    case 1:
    case 3:
        if (mode == 1) {
            self->offset = self->blend * self->vt->m11(self);
        } else {
            self->offset = (1.0f - self->blend) * self->vt->m13(self);
        }
        if (self->mode == 0 || self->mode == 2) {
            notify = 1;
        }
        break;
    case 2:
        notify = 1;
        self->x = self->shownX;
        self->y = self->shownY;
        self->blend = 1.0f;
        self->offset = 0.0f;
        break;
    case 0:
        notify = 1;
        self->x = self->hiddenX;
        self->y = self->hiddenY;
        self->blend = 0.0f;
        self->offset = 0.0f;
        break;
    }
    self->mode = mode;
    self->since = *self->clock;
    if (notify) {
        PlaceScreenElement(self);
    }
}

// Whether both elements are shown together: modes 1 or 2 with 1 or 2, or 3 with 3, or 2 with 3.
s32 AreScreenElementsTogether(ScreenElement* a, ScreenElement* b)
{
    s32 r = 0;
    s32 am = a->mode;
    if ((u32)(am - 1) < 2) { if ((u32)(b->mode - 1) < 2) goto yes; }
    if (am == 3) { if (b->mode == 3) goto yes; }
    if (b->mode == 3) { if (am == 2) goto yes; }
    goto done;
yes:
    r = 1;
done:
    return r;
}

// Sets the element's width and height (a negative value leaves that one as it is) and places it
// again.
void SetScreenElementSize(ScreenElement *self, f32 x, f32 y) {
    if (0.0f <= x) {
        self->w = x;
    }
    if (0.0f <= y) {
        self->h = y;
    }
    PlaceScreenElement(self);
}

// Works out where a screen element shows and hides: it is placed inside the 640 x 492.8 screen,
// after the other elements it is anchored to (relation 0 to 3 is right, left, below, above them),
// with dx and dy as margins (0 centres; negative counts from the far edge). Then sets the hidden
// position from the side it slides in from and moves the element to match its mode.
void PlaceScreenElement(ScreenElement* self) {
    T217D_Place* r = self->place;
    f32 x0 = 0.0f;
    f32 x1 = 640.0f;
    f32 y1 = 492.80002f;
    f32 y0 = x0;

    if (r->anchor != -1) {
        ScreenElement** objs = (ScreenElement**)g_screenElements;
        T217D_Place* recs = (T217D_Place*)&g_elementPlaces;
        do {
            ScreenElement* o = objs[r->anchor];
            if (o->vt->m18(o, self)) {
                switch (r->relation) {
                case 0:
                    if (o->w != 0.0f) x0 = o->x + o->w;
                    break;
                case 1:
                    if (o->w != 0.0f) x1 = o->x;
                    break;
                case 2:
                    if (o->h != 0.0f) y0 = o->y + o->h;
                    break;
                case 3:
                    if (o->h != 0.0f) y1 = o->y;
                    break;
                }
                break;
            }
            r = &recs[r->anchor];
        } while (r->anchor != -1);
    }
    f32 a = self->place->dx;
    if (a == 0.0f) {
        self->shownX = (x1 - x0 - self->w) * 0.5f;
    } else if (0.0f < a) {
        self->shownX = x0 + a;
    } else {
        self->shownX = x1 + a - self->w;
    }
    f32 b = self->place->dy;
    if (b == 0.0f) {
        self->shownY = (y1 - y0 - self->h) * 0.5f;
    } else if (0.0f < b) {
        self->shownY = y0 + b;
    } else {
        self->shownY = y1 + b - self->h;
    }
    f32 t = TruncateFloat(self->shownY * 0.9090909f) * 1.1f;
    self->hiddenX = self->shownX;
    self->shownY = t;
    self->hiddenY = t;
    switch (self->place->from) {
    case 0: self->hiddenX = -self->w; break;
    case 1: self->hiddenX = 640.0f; break;
    case 2: self->hiddenY = -self->h; break;
    case 3: self->hiddenY = 492.80002f; break;
    }
    s32 m = self->mode;
    if (m != 0) {
        if (m == 2) {
            self->x = self->shownX;
            self->y = self->shownY;
        }
    } else {
        self->x = self->hiddenX;
        self->y = self->hiddenY;
    }
    PlaceAnchoredScreenElements(self);
}

// Places again every element (of 0x25) that is anchored to the element that changed.
void PlaceAnchoredScreenElements(ScreenElement* changed)
{
    T217D_Place* e = (T217D_Place*)&g_elementPlaces;
    s32 i;

    for (i = 0; i < 0x25; i++, e++) {
        s32 v = e->anchor;
        if (v != -1) {
            if (((ScreenElement**)g_screenElements)[v] == changed) {
                PlaceScreenElement(((ScreenElement**)g_screenElements)[i]);
            }
        }
    }
}

// Chooses the clock the element reads its times from (the elapsed-time clock for 0), restarting
// its timer when it changes.
void SetScreenElementClock(ScreenElement* self, f32* p)
{
    if (self->clock != p) {
        if (p == 0) {
            p = &g_elapsedTime;
        }
        self->since = *p;
    }
    self->clock = p;
}

// Sets up a counter caption (font 2, rate 6000) and points its value at the counter its index
// names: reserve count (3), current entry's count (4, limit in the world), level record field
// (5), pickup count (6), or its own shown value for the other indices.
void InitCounterCaption(T217D_E30* self)
{
    SetupScreenElementText(self);
    self->font = GetFontById(2);
    self->shown = -1;
    self->rate = 6000.0f;
    switch (self->index) {
    case 3:
        self->target = &g_saveData->reserveCount;
        break;
    case 4:
        self->target = &g_currentEntry->count64;
        self->limit = &g_currentWorld->count2300;
        break;
    case 5:
        self->target = &g_currentLevelRecord->f438;
        break;
    case 6:
        self->target = &g_saveData->pickupCount;
        break;
    case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
    case 28: case 29:
    case 36:
        self->target = &self->shown;
        break;
    }
}

// Per-frame update of a counter caption: slides it, makes the shown value approach the target by
// rate per second (at once for a negative value), calls the done callback once when it arrives,
// rebuilds the text and sets the element's size to the text's.
void UpdateCounterCaption(T217D_E30* self)
{
    TextReader loc;
    f32 frac;
    s32 n;
    s32 first;
    s32* p;

    UpdateScreenElementSlide(self);
    p = self->target;
    if (self->shown == *p) {
        return;
    }
    if (self->shown >= 0) {
        frac = g_frameDt * self->rate + self->fraction;
        n = (s32)frac;
        self->fraction = frac - (f32)n;
        first = *self->target;
        if (first < self->shown) {
            s32 lo = self->shown - n;
            self->shown = first < lo ? lo : first;
        } else {
            s32 hi = self->shown + n;
            self->shown = hi < first ? hi : first;
        }
    } else {
        self->shown = *p;
    }
    if (self->shown == *self->target && self->onDone != 0) {
        self->onDone(self->doneArg);
        self->onDone = 0;
        self->doneArg = 0;
    }
    FormatCounterCaption(self);
    if (self->text[0] != 0) {
        PushFontScale(self->font, self->scale, self->scale);
        InitTextReader(&loc, &self->text[0], self->font);
        f32 x = SumTextWidth(&loc);
        f32 y = (f32)self->font->height * self->font->sy;
        SetScreenElementSize(self, x, y);
        PopFontScale(self->font);
    } else {
        SetScreenElementSize(self, 0.0f, 0.0f);
    }
}

// Draws the counter caption's text, faded by the pause menu's fade when that is up.
void DrawCounterCaption(T217D_E30* self)
{
    u8 out[0x20];
    T217D_Word packed;
    s32 held;
    s32 tmp[4];
    u8 buf[0xB0];
    f32 scale;
    f32 px;
    f32 py;
    T217D_6D0* g;

    if (self->text[0] == 0) {
        return;
    }
    g = &g_pauseMenuElement;
    scale = 1.0f;
    if (g->mode != 0) {
        scale = g->fade;
    }
    packed = self->colorWord;
    ((u8*)&packed)[3] = (u8)(s32)(scale * 255.0f);
    held = packed.v;
    px = self->w;
    py = self->h;
    ((Layout_137228*)out)->Pos(self->x, self->y);
    ((Layout_137228*)out)->Size(px, py);
    tmp[0] = held;
    ((Layout_137228*)out)->Color(&tmp[0]);
    ((Layout_137228*)out)->SetF14(0);
    ((Layout_137228*)out)->SetF18(0);
    PushFontScale(self->font, self->scale, self->scale);
    InitTextReader((TextReader*)buf, &self->text[0], self->font);
    DrawAlignedText((TextReader*)buf, (Layout_137228*)out, 0, &g_gsPacketWriter);
    PopFontScale(self->font);
}

// Builds the text of a counter caption from its kind (index) and the shown value: the value with
// its limit and a one-letter glyph suffix or prefix, a row of icons for kind 13, a percent for
// 36, and empty text where the kind does not apply; then substitutes glyph escapes.
void FormatCounterCaption(T217D_E30* self)
{
    switch (self->index) {
    case 3:
        FormatToStringBounded(self->text, 0x200, "%c%d", 0x4C, self->shown);
        break;
    case 4:
        if (*self->limit != 0) {
            FormatToStringBounded(self->text, 0x200, "%d/%d%c", self->shown, *self->limit,
                          self->shown < *self->limit ? 0x3F : 0x21);
        } else {
            self->text[0] = 0;
        }
        break;
    case 5:
        if ((u32)(g_saveData->levelIndex - 1) < 4) {
            FormatToStringBounded(self->text, 0x200, "%d%c", self->shown, 0x4B);
        } else {
            self->text[0] = 0;
        }
        break;
    case 6:
        if (g_currentWorld->f2354 != 0) {
            FormatToStringBounded(self->text, 0x200, "%c%d", 0x43, self->shown);
        } else {
            self->text[0] = 0;
        }
        break;
    case 7:
        FormatToStringBounded(self->text, 0x200, "%d/%d%c", self->shown, *self->limit, 0x56);
        break;
    case 8:
        FormatToStringBounded(self->text, 0x200, "%d/%d%c", self->shown, *self->limit, 0x4E);
        break;
    case 9:
        FormatToStringBounded(self->text, 0x200, "%c%d/%d", 0x46, self->shown, *self->limit);
        break;
    case 10:
        FormatToStringBounded(self->text, 0x200, "%c%d", 0x4E, self->shown);
        break;
    case 11:
        FormatToStringBounded(self->text, 0x200, "%d/%d%c", self->shown, *self->limit, 0x56);
        break;
    case 28:
        FormatToStringBounded(self->text, 0x200, "%d/%d%c", self->shown, D_002751D4, 0x56);
        break;
    case 29:
        FormatToStringBounded(self->text, 0x200, "%c%d/%d", 0x4E, self->shown, D_002751D4);
        break;
    case 12:
        FormatToStringBounded(self->text, 0x200, "%d/%d%c", self->shown, *self->limit, 0x64);
        break;
    case 13:
        FormatToStringBounded(self->text, 0x200, "%c%c%c%c%c%c", 's',
                      self->shown >= 1 ? 'b' : 'm', self->shown >= 2 ? 'b' : 'm',
                      self->shown >= 3 ? 'b' : 'm', self->shown >= 4 ? 'b' : 'm',
                      self->shown >= 5 ? 'b' : 'm');
        break;
    case 14:
        FormatToStringBounded(self->text, 0x200, "rstuv");
        break;
    case 15:
        FormatToStringBounded(self->text, 0x200, "%c%d/5", 0x46, self->shown);
        break;
    case 36:
        FormatToStringBounded(self->text, 0x200, "%d%%", self->shown);
        break;
    }
    SubstituteScreenElementGlyphs(self);
}

// How long a caption is held: 2.5 s while the game clock runs, otherwise 0.
f32 GetCaptionHoldTime(void)
{
    return g_gameClock.running != 0 ? 2.5f : 0.0f;
}

// Sets up a timer element in font 2 with no seconds or tenths shown yet, no warning time and
// the stopped state.
void InitTimerElement(T217D_510* self)
{
    SetupScreenElementText(self);
    self->font = GetFontById(2);
    self->lastTenth = self->lastSecond = -1;
    self->warnAt = 3.4028235e+38f;
    self->f290 = 1;
    SetTimerState(self, 0);
}

// Per-frame update of a timer element: updates the slide; while the timer is stopped (state 0)
// in mode 1 or 2 it hides itself after a second or when f290 is set, otherwise it steps the
// timer by the frame time.
void UpdateTimerElement(T217D_510* self)
{
    UpdateScreenElementSlide(self);
    if (self->mode == 0) {
        return;
    }
    if (self->state == 0) {
        s32 close = (1.0f <= g_gameTime - self->stateSince);
        if ((u32)(self->mode - 1) < 2) {
            if (self->f290 != 0 || close) {
                self->vt->m15(self);
            }
        }
    } else {
        StepTimer(self, g_frameDt);
    }
}

// Draws the timer: a frame box, the first character (a fixed glyph), then the time text after it,
// in the warning colour once the timer has warned.
void DrawTimerElement(T217D_510* self)
{
    Layout_137228 L;
    Quad4 tag;
    T217D_Word warn;
    if (self->text[0] != 0) {
        f32 f234 = self->w;
        f32 f238 = self->h;
        s32 s0v = self->color;
        ((Layout_137228*)&L)->Pos(self->x, self->y);
        ((Layout_137228*)&L)->Size(f234, f238);
        tag.w[0] = s0v;
        ((Layout_137228*)&L)->Color(&tag.w[0]);
        ((Layout_137228*)&L)->SetF14(0);
        ((Layout_137228*)&L)->SetF18(0);
        void* obj = self->frame;
        if (obj != 0) {
            Font* sub = *(Font**)obj;
            if (sub != 0) {
                const FontVt* d = sub->vt;
                // the class's this-adjustment from its vtable, not a field
                d->drawBox((Font*)((u8*)sub + d->adj9), obj, &L, &g_gsPacketWriter);
            }
        }
        f32 v = self->scale;
        u8* dp = (u8*)&g_gsPacketWriter;
        PushFontScale(self->font, v, v);
        ((u8*)&tag)[0] = 0x54;
        ((u8*)&tag)[1] = 0;
        DrawFontString(self->font, (const char*)&tag, (StringLayout*)&L, 0, (PacketWriter*)dp);
        f32 r = MeasureFontString(self->font, (const char*)&tag);
        f32 a = self->x + r;
        L.y = self->y;
        L.x = a;
        if (self->warned != 0) {
            warn = self->warnColor;
            *(T217D_Word*)&L.color = warn;
        }
        DrawFontString(self->font, &self->text[1], (StringLayout*)&L, 0, (PacketWriter*)dp);
        PopFontScale(self->font);
    }
}

// Starts the timer at x with no limit, warnings or callbacks, a falling rate of -1 per second
// and grey colour, and shows it.
void StartTimer(T217D_510* self, f32 x)
{
    self->onWarn = 0;
    self->warned = 0;
    self->limit = 0;
    self->onEnd = 0;
    self->f290 = 0;
    self->color = 0xFF808080;
    self->rate = -1.0f;
    self->lastSecond = -1;
    self->lastTenth = -1;
    self->warnAt = 3.4028235e+38f;
    self->time = x;
    SetTimerState(self, 1);
    StepTimer(self, 0.0f);
    self->vt->m14(self);
}

void SetTimerRate(T217D_510* self, f32 value)
{
    self->rate = value;
}

// Sets the time at which the timer ends and the function to call then.
void SetTimerLimit(T217D_510* self, f32 limit, T217D_510_Fn onEnd)
{
    self->limit = limit;
    self->onEnd = onEnd;
}

// Puts the timer in state 2, counting.
void StartTimerCounting(T217D_510* self)
{
    SetTimerState(self, 2);
}

// Stops the timer element (state 0) and sets its f290 flag.
void StopTimer(T217D_510* self)
{
    self->f290 = 1;
    SetTimerState(self, 0);
}

// Per-frame update of the timer element (state 2 is running): plays tick sounds (a 10-second
// countdown has its own pair of sounds at the tenths 9 and 4), advances the time by dt * rate,
// raises the warning once at warnAt, ends at the limit (sound, state 0, onEnd) and rebuilds its
// text when a displayed digit changes.
void StepTimer(T217D_510* self, f32 dt)
{
    f32 t = __builtin_fabsf(self->time);
    s32 sec = (s32)t;
    s32 hund = (s32)(t * 10.0f);
    s32 tenth = (s32)((t - (f32)sec) * 10.0f);

    if (self->state == 2)
    {
        f32 rate = self->rate;
        if (rate != 0.0f)
        {
            if (rate < 0.0f && 0.0f <= self->time && self->time < 10.0f)
            {
                if (tenth != self->lastTenth)
                {
                    if (tenth == 9)
                        StartSoundEffect(0x7E, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                    else if (tenth == 4)
                        StartSoundEffect(0x7F, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                }
            }
            else if (sec != self->lastSecond)
            {
                StartSoundEffect((sec & 1) ? 0x72 : 0x73, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        }
    }
    self->lastTenth = tenth;
    self->lastSecond = sec;

    if (g_gameClock.running != 0 && self->state == 2 && (*(s32*)g_padRouting & 2))
    {
        s32 warn = 0;
        s32 end = 0;
        f32 rate = self->rate;
        self->time = self->time + dt * rate;
        if (rate < 0.0f)
        {
            if (self->warnAt != 3.4028235e+38f && self->time <= self->warnAt)
                warn = 1;
            if (self->time <= self->limit)
                end = 1;
        }
        else if (rate > 0.0f)
        {
            if (self->warnAt != 3.4028235e+38f && self->warnAt <= self->time)
                warn = 1;
            if (self->time >= self->limit)
                end = 1;
        }
        if (warn && self->warned == 0)
        {
            self->warned = 1;
            if (self->onWarn != 0)
                self->onWarn(self, 0);
        }
        if (end)
        {
            self->time = self->limit;
            StartSoundEffect(1, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            SetTimerState(self, 0);
            if (self->onEnd != 0)
                self->onEnd(self, 1);
        }
        t = __builtin_fabsf(self->time);
    }

    s32 show = 0;
    s32 tenths = 0;
    s32 hi;
    s32 lo;
    s32 sep;
    s32 h;
    if (t < 10.0f && (h = (s32)(t * 10.0f)) != hund)
    {
        hi = h / 10;
        lo = h % 10;
        sep = '.';
        tenths = 1;
        show = 1;
    }
    else
    {
        s32 s = (s32)t;
        if (s != sec || (self->state == 1 && g_gameClock.time - self->stateSince <= g_gameClock.dt))
        {
            hi = s / 60;
            lo = s % 60;
            sep = ':';
            show = 1;
        }
    }
    if (show)
    {
        FormatToStringBounded(self->text, 0x200, "%c%d%c%s%d", 0x54, hi, sep, (lo < 10 && !tenths) ? "0" : "", lo);
        PushFontScale(self->font, self->scale, self->scale);
        f32 w = MeasureFontString(self->font, self->text);
        Font* f = self->font;
        SetScreenElementSize(self, w, (f32)f->height * f->sy);
        PopFontScale(self->font);
    }
}

// Changes the timer's state (0 stopped, 1 shown, 2 counting) and stamps the time of the change.
void SetTimerState(T217D_510* self, s32 state)
{
    if (self->state != state) {
        self->state = state;
        self->stateSince = g_gameTime;
    }
}

f32 GetPairCaptionHoldTime(void)
{
    return 0.0f;
}

f32 GetGaugeAmountCaptionHoldTime(void)
{
    return 0.0f;
}

f32 GetGaugeColliderCaptionHoldTime(void)
{
    return 0.0f;
}

f32 g_gaugeBarX = 18.0f;
f32 g_gaugeBarY = 8.0f;
f32 g_gaugeBarWidth = 26.0f;
f32 g_gaugeBarHeight = 340.0f;

// Starts the gauge's count from its mode's segments and returns the number of cells.
static inline s32 StartGaugeCount(T217D_2E0* g)
{
    s32 cells = g->segmentCount * g->cellsPerSegment;
    g->segmentsLeft = g->segmentCount;
    g->cellsLeft = g->cellsPerSegment;
    return cells;
}

// Sets up the gauge element: font, scale, bar size and position from the gauge constants, and the
// number of segments and cells per segment according to the current level index (the fill starts
// full for levels 2 and 3); the letter position is derived from the font's size.
void InitGauge(T217D_2E0* self)
{
    s32 n = 4;
    SetupScreenElementText(self);
    self->font = GetFontById(n);
    self->scale = 1.0f;
    self->fillTarget = 1.0f;
    self->fill = 0;
    switch (g_saveData->levelIndex) {
    case 1:
        self->segmentCount = 4;
        self->cellsPerSegment = 1;
        break;
    case 4:
        self->segmentCount = 5;
        self->cellsPerSegment = 10;
        break;
    case 2:
        self->segmentCount = 3;
        self->cellsPerSegment = 1;
        self->fill = 1.0f;
        break;
    case 3:
        self->segmentCount = 4;
        self->cellsPerSegment = 1;
        self->fill = 1.0f;
        break;
    case 5:
        self->segmentCount = 4;
        self->cellsPerSegment = 5;
        break;
    default:
        return;
    }
    f32 pad = 5.0f;
    self->barX = g_gaugeBarX * self->scale;
    self->barY = g_gaugeBarY * self->scale;
    self->barW = g_gaugeBarWidth * self->scale;
    self->barH = g_gaugeBarHeight * self->scale;
    PushFontScale(self->font, self->scale, self->scale);
    f32 h = (f32)self->font->height * self->font->sy;
    f32 w = self->font->Width('z');
    f32 h2 = (f32)self->font->height * self->font->sy;
    SetScreenElementSize(self, h, w + h2 + pad);
    PopFontScale(self->font);
    self->changedAt = 0;
    n = StartGaugeCount(self);
    self->letterX = h * 0.5f;
    self->letterY = w + pad + h2 * 0.5f;
    self->cellCount = n;
}

// Takes one cell off the gauge (moving to the next segment when a segment is used up),
// recomputes its fill target as a fraction of all cells and notes the time of the change.
void DecrementGaugeCount(T217D_2E0* self)
{
    s32 n = self->cellsLeft - 1;
    self->cellsLeft = n;
    if (n <= 0) {
        n = self->segmentsLeft - 1;
        self->segmentsLeft = n;
        if (n <= 0) {
            self->cellsLeft = 0;
            self->segmentsLeft = 0;
        } else {
            self->cellsLeft = self->cellsPerSegment;
        }
    }

    s32 a = self->cellsPerSegment;
    f32 d = (f32)self->cellCount;
    s32 v0 = self->segmentsLeft - 1;
    s32 b = self->cellsLeft;
    v0 = (-1 < v0) ? v0 : 0;
    self->fillTarget = (f32)(v0 * a + b) / d;
    self->changedAt = g_gameClock.time;
}

RampProfile g_gaugeFillRamp = { 0.5f, 0.25f, 0.2f, 0.0f };

// Draws the vertical gauge element: a dark background bar, a fill bar in proportion to the fill
// value (which eases toward its target), whose colour flashes from red toward grey for about half
// a second after a change, and the gauge's letter, which shakes for 0.75 s after a change.
void DrawGauge(T217D_2E0* self)
{
    Layout_137228 out;
    f32 t = 0.0f;
    s32 flag = 0;
    if (self->changedAt != t) {
        f32 d = g_gameClock.time - self->changedAt;
        if (d < 0.5f) t = 1.0f - (d + d);
        flag = d < 0.75f;
    }
    u32 grey = 0xFF808080;
    self->fill = ApproachValueWithRamp(&g_gaugeFillRamp, 0, self->fill, self->fillTarget, g_gameClock.dt);
    f32 y = self->barH;
    f32 h = self->fill * y;
    y -= h;
    f32 w = self->barW;
    ((Layout_137228*)&out)->Pos(self->x + self->barX, self->y + self->barY);
    ((Layout_137228*)&out)->Size(w, y);
    {
        Quad4 tmp;
        tmp.w[0] = grey;
        ((Layout_137228*)&out)->Color(tmp.w);
    }
    ((Layout_137228*)&out)->SetF14(0);
    ((Layout_137228*)&out)->SetF18(0);
    {
    Rgba4 col;
    col.r = 0x20; col.g = 0x20; col.b = 0x20; col.a = 0xC0;
    WriteColoredSpritePacket(out.x, out.y, out.x + out.w, out.y + out.h, 0x20, 0x20, 0x20, 0xC0, &g_gsPacketWriter);
    {
        out.x = self->x + self->barX;
        out.y = self->y + self->barY + y;
        out.w = self->barW;
        out.h = h;
        Rgba4 a, b;
        a.r = 0x60; a.g = 0; a.b = 0; a.a = 0xC0;
        b.r = 0xC0; b.g = 0xC0; b.b = 0xC0; b.a = 0xFF;
        LerpRgba4::Do(&col, &a, &b, t);
    }
    WriteColoredSpritePacket(out.x, out.y, out.x + out.w, out.y + out.h, col.r, col.g, col.b, col.a, &g_gsPacketWriter);
    }
    PushFontScale(self->font, self->scale, self->scale);
    Text_1AC0E8* text = (Text_1AC0E8*)self->font;
    VEnt_1AC0E8* ve = &text->vtbl[8];
    // the class's this-adjustment from its vtable, not a field
    ve->fn((u8*)self->font + ve->delta, self->x, self->y, 0x7A, out.color.value, &g_gsPacketWriter);
    f32 dx = 0.0f;
    f32 dy = dx;
    if (flag) {
        dx = Sine(g_gameClock.elapsed * 40.0f) * 8.0f;
        dy = Cosine(g_gameClock.elapsed * 15.0f) * 4.0f;
    }
    out.x = self->x + self->letterX + dx;
    out.y = self->y + self->letterY + dy;
    out.w = 0.0f;
    out.h = 0.0f;
    out.f14 = 1;
    out.f18 = 1;
    char str[2] = { self->letter + 0x72, 0 };
    DrawFontString(self->font, str, (StringLayout*)&out, 0, &g_gsPacketWriter);
    PopFontScale(self->font);
}

TextStyle g_framedElementStyle = {0};

// Sets up a framed element with a 1.25 scaled copy of its font and the frame font.
void InitFramedElement(T217D_330* self)
{
    const FontVt* vt;

    SetupScreenElementText(self);
    vt = self->font->vt;
    // the class's this-adjustment from its vtable, not a field
    self->font = vt->clone((Font*)((u8*)self->font + vt->adj1), 1.25f, 1.25f);
    if (IsFontLoaded(2)) {
        self->frame = (Font**)&g_framedElementStyle;
        *self->frame = GetFontById(2);
    }
}

// Copies the text (or clears it) and sizes the element to the text measured at the element's
// scale; an empty text has height 0.
void SetCaptionTextAndSize(T217D_330* self, const char* p)
{
    MeasuredText loc;

    if (p != 0 && GetStringLength(p)) {
        CopyString(self->text, p);
    } else {
        self->text[0] = 0;
    }
    f32 v = self->scale;
    PushFontScale(self->font, v, v);
    InitTextReader(&loc.reader, &self->text[0], self->font);
    f32 zero = 0.0f;
    MeasureText(&loc.reader, zero, &loc.x, &loc.y);
    f32 x = loc.x;
    SetScreenElementSize(self, x, (self->text[0] != 0) ? loc.y : 0.0f);
    PopFontScale(self->font);
}

// Draws the element's frame and text, both faded by multiplying their alpha by the element's
// blend.
void DrawElementWithFadedFrame(T217D_330* self)
{
    T217D_Word tmp;
    LayoutBuilder out;
    T217D_Word slot;
    u8 loc[0xB0];

    if (self->text[0] != 0) {
        tmp = self->colorWord;
        ((u8*)&tmp)[3] = (u8)((f32)((u8*)&tmp)[3] * self->blend);
        f32 p = self->w;
        f32 q = self->h;
        s32 held = tmp.v;
        out.Pos(self->x, self->y);
        out.Size(p, q);
        slot.v = held;
        out.Color(&slot.v);
        out.FlagA(0);
        out.FlagB(0);

        TextStyle* h = (TextStyle*)self->frame;
        if (h != 0) {
            slot = *(T217D_Word*)&h->color;
            ((u8*)&h->color)[3] = (u8)((f32)((u8*)&h->color)[3] * self->blend);
            StyleDrawerBuilder::Draw(self->frame, &out, &g_gsPacketWriter);
            *(T217D_Word*)&((TextStyle*)self->frame)->color = slot;
        }
        PushFontScale(self->font, self->scale, self->scale);
        InitTextReader((TextReader*)loc, &self->text[0], self->font);
        DrawAlignedText((TextReader*)loc, &out, 0, &g_gsPacketWriter);
        PopFontScale(self->font);
    }
}

TextStyle g_pointerCaptionStyle = {0};

// Sets up a caption with a 0.9 scaled copy of its font, a grey colour and the frame font.
void InitPointerTextCaption(T217D_380* self)
{
    const FontVt* vt;

    SetupScreenElementText(self);
    vt = self->font->vt;
    // the class's this-adjustment from its vtable, not a field
    self->font = vt->clone((Font*)((u8*)self->font + vt->adj1), 0.9f, 0.9f);
    self->color = 0xDF7F7F7Fu;
    if (IsFontLoaded(2)) {
        self->frame = (Font**)&g_pointerCaptionStyle;
        *self->frame = GetFontById(2);
    }
}

// Like SetElementTextCopiedAfterSlideOut but remembers only the pointer of the new text: sets
// it at once when hidden, and in modes 1 to 3 with a different text slides out first (m16, 3).
void SetElementTextAfterSlideOut(T217D_380* self, const char* v)
{
    s32 k = self->mode;
    if (k == 0) {
        SetScreenElementText(self, v);
        goto done;
    }
    if (k < 0) {
        goto done;
    }
    if (k >= 4) {
        goto done;
    }
    if (CompareStrings(self->text, v) != 0) {
        self->pendingText = v;
        self->pending = 1;
        self->vt->m16(self, 3);
    }
done:
    return;
}

// Sets the element's mode; a pending text is applied first when the mode is 0, which makes the
// mode 1 instead.
void SetElementModeApplyingPendingText(T217D_380* self, s32 v)
{
    if (self->pending != 0 && v == 0) {
        const char* x = self->pendingText;
        self->pending = 0;
        SetScreenElementText(self, x);
        v = 1;
    }
    SetScreenElementMode(self, v);
}

// Whether the two elements are together or this one has a text waiting.
s32 AreElementsTogetherOrPending(T217D_380* self, ScreenElement* other)
{
    s32 r = 0;
    if (AreScreenElementsTogether(self, other) != 0 || self->pending != 0) {
        r = 1;
    }
    return r;
}

// Shows the element, except that in mode 3 with a text waiting it does nothing.
void ShowElementUnlessTextPending(T217D_380* self)
{
    if (self->mode != 3 || self->pending == 0) {
        ShowScreenElement(self);
    }
}

// Hides the element, except that in mode 3 with a text waiting it only drops the waiting text.
void HideElementOrDropPendingText(T217D_380* self)
{
    if (self->mode == 3 && self->pending != 0) {
        self->pending = 0;
    } else {
        HideScreenElement(self);
    }
}

// Draws a text element whose characters slide in one by one, each blended from its hidden x to
// its shown x as the element's blend rises (the first character first), with the frame box
// stretching along. In mode 2 it is drawn as plain text.
void DrawSlidingGlyphElement(T217D_380* self)
{
    LayoutByValue out;
    s32 n;
    s32 i;
    f32 c;
    f32 rest;
    f32 x;
    f32 y;

    switch (self->mode) {
    case 2:
        DrawScreenElementText(self);
        return;
    case 1:
    case 3:
        break;
    default:
        return;
    }
    n = GetStringLength(self->text);
    if (n == 0) {
        return;
    }
    x = self->shownX;
    y = self->hiddenX;
    c = ClampFloatSelect::Of(self->blend / (1.0f / (f32)n), 0.0f, 1.0f);
    rest = 1.0f - c;
    if (self->frame != 0) {
        s32 grey = 0xFF808080;
        f32 w = x * self->blend + y * (1.0f - self->blend) + self->w;
        f32 h = self->h;
        out.Pos(x * c + y * rest, self->y);
        out.Size(w, h);
        out.Color(grey);
        out.FlagA(0);
        out.FlagB(0);
        Font* o = *self->frame;
        if (o != 0) {
            // the class's this-adjustment from its vtable, not a field
            o->vt->drawBox((Font*)((u8*)o + o->vt->adj9), self->frame, &out, &g_gsPacketWriter);
        }
    }
    FontCalls::Begin(self->font, 0, &g_gsPacketWriter);
    for (i = 0; i < n; i++) {
        s32 ch = self->text[i];
        f32 d;
        c = ClampFloatSelect::Of(self->blend / ((f32)(i + 1) / (f32)n), 0.0f, 1.0f);
        rest = 1.0f - c;
        FontCalls::Glyph(self->font, ch, self->color, &g_gsPacketWriter, c * x + rest * y, self->shownY);
        d = FontCalls::Advance(self->font, ch);
        x += d;
        y += d;
    }
    FontCalls::End(self->font, 0, &g_gsPacketWriter);
}

TextStyle g_copiedCaptionStyle = {0};

// Sets up a caption with a copy of font 0, scale 0.8, a slide-out time of 0.5 and the frame
// font.
void InitCopiedTextCaption(T217D_3D0* self)
{
    Font* o;
    const FontVt* vt;

    SetupScreenElementText(self);
    o = GetFontById(0);
    vt = o->vt;
    // the class's this-adjustment from its vtable, not a field
    self->font = vt->clone((Font*)((u8*)o + vt->adj1), 1.0f, 1.0f);
    self->scale = 0.8f;
    self->outTime = 0.5f;
    if (IsFontLoaded(2)) {
        self->frame = (Font**)&g_copiedCaptionStyle;
        *self->frame = GetFontById(2);
    }
}

// Sets the element's text at once when it is hidden (mode 0); in modes 1 to 3 and when the text
// differs it copies the new text aside and slides the element out (m16, 3), so the text is
// applied after the slide-out.
void SetElementTextCopiedAfterSlideOut(T217D_3D0* self, const char* v)
{
    s32 k = self->mode;
    if (k == 0) {
        SetScreenElementText(self, v);
        return;
    }
    if (k < 0) {
        return;
    }
    if (k >= 4) {
        return;
    }
    if (self->pending == 0) {
        if (CompareStrings(self->text, v) == 0) {
            return;
        }
    }
    self->pending = 1;
    if (v != 0) {
        CopyString(self->pendingText, v);
    } else {
        self->pendingText[0] = 0;
    }
    self->vt->m16(self, 3);
}

// Writes into buf the glyphs for the flags of a progress entry that mask asks for: bit 2 and bit
// 4 a glyph each for whether the flag is set, bit 8 a glyph and, when set, a time as seconds
// below 1, otherwise minutes and seconds.
void FormatFlagGlyphs(char* buf, ProgressEntry* info, u32 mask)
{
    u32 flags = info->flags;
    *buf = 0;
    if (mask & 2) {
        buf += FormatToString(buf, "&3%s&.", (flags & 2) ? "k" : "l");
    }
    if (mask & 4) {
        if (mask & 2) {
            *buf++ = ' ';
        }
        buf += FormatToString(buf, "&3%s&.", (flags & 4) ? "v" : "w");
    }
    if (mask & 8) {
        u32 f8;
        if (mask & 6) {
            *buf++ = ' ';
        }
        f8 = flags & 8;
        buf += FormatToString(buf, "&1%s", f8 ? "h" : "i");
        if (f8) {
            f32 t = info->time;
            if (t < 1.0f) {
                (void)FormatToString(buf, "^10~b2a83d0.%d~.^.", (s32)(t * 10.0f));
            } else {
                s32 s = (s32)t;
                s32 m = s / 60;
                s32 r = s % 60;
                (void)FormatToString(buf, "^10~b2a83d%d:%02d~.^.", m, r);
            }
        }
        AppendString(buf, "&.");
    }
}

// Sets the text from a packed entry (level in the bits above 8, entry in the low byte), or
// "<unknown>" for -1.
void SetElementTextFromPackedEntry(ScreenElement* self, s32 value)
{
    if (value != -1) {
        SetElementTextFromEntry(self, value >> 8, (u8)value);
    } else {
        self->vt->m08(self, "<unknown>");
    }
}

// Sets the element's text to the name of a level entry (level a1, entry a2) followed by its flag
// glyphs.
void SetElementTextFromEntry(ScreenElement* self, s32 a1, s32 a2)
{
    char buf[64];
    char str[64];
    u8* p;
    u32 packed;

    p = *(u8**)((u8*)&g_saveData);
    // address arithmetic over a variable index
    p += a1 * 0x44C + 0x10;
    p += a2 * 0x78;
    packed = (a1 << 8) | a2;
    FormatFlagGlyphs(buf, (ProgressEntry*)p, GetEntryFlags(packed));
    if (GetStringLength(buf)) {
        FormatToString(str, (const char*)"%s%s%s", GetEntryName(packed),
                      GetStringLength(buf) ? (const char*)" " : (const char*)"", buf);
    } else {
        CopyString(str, GetEntryName(packed));
    }
    self->vt->m08(self, (const char*)str);
}

// The names the level picker shows, by level (the first, empty, for none).
const char* g_worldTitles[6] = { "", "Tide of Terror", "Sunset Snake Eyes", "Vicious Voodoo", "Fire in the Sky", "The Cold Heart of Hate" };

// Sets the element's text to a world's title followed by its collected counts for each category
// that has any (count and total, with a glyph).
void SetElementTextFromIndexedCounts(ScreenElement* self, s32 idx)
{
    char buf[0x200];
    s32 a, b, c;
    CountCategoryFlags(idx, &a, &b, &c);
    G27C230* s1 = &g_saveData->levels[idx];
    CopyString(buf, g_worldTitles[idx]);
    char* d = buf + GetStringLength(buf);
    if (a)
        d += FormatToString(d, " &1%d^10~b2a83d/%d~.^.&.&3k&.", s1->f438, a);
    if (b)
        d += FormatToString(d, "%s&1%d^10~b2a83d/%d~.^.&.&3v&.", a ? ((char*)" ") : ((char*)""), s1->f43C, b);
    if (c)
        FormatToString(d, "%s&1%d^10~b2a83d/%d~.^.h&.", (a || b) ? ((char*)" ") : ((char*)""), s1->f440, c);
    self->vt->m08(self, buf);
}

// Sets the element's mode; a pending copied text is applied first when the mode is 0, which
// makes the mode 1 instead.
void SetElementModeApplyingCopiedText(T217D_3D0* self, s32 flag)
{
    if (self->pending != 0 && flag == 0) {
        self->pending = 0;
        SetScreenElementText(self, self->pendingText);
        flag = 1;
    }
    if (flag == 0) {
        self->announce = 0;
    }
    SetScreenElementMode(self, flag);
}

// Shows the element, except that in mode 3 with a copied text waiting it does nothing.
void ShowElementUnlessCopiedTextPending(T217D_3D0* self)
{
    if (self->mode == 3 && self->pending != 0) return;
    ShowScreenElement(self);
}

// Hides the element, except that in mode 3 with a copied text waiting it only drops that text.
void HideElementOrDropCopiedText(T217D_3D0* self)
{
    if (self->mode == 3 && self->pending != 0) {
        self->pending = 0;
    } else {
        HideScreenElement(self);
    }
}

// Draws a message element: its text, faded by the element's blend, with a translucent black bar
// behind it at the bottom of the screen when it is not an announcement; hidden while the typed-
// text caption box is on screen.
void DrawMessageElement(T217D_3D0* self)
{
    T217D_Word packed;
    LayoutBuilder out;
    T217D_Word slot;
    TextReader buf;
    f32 scale;
    f32 off;
    f32 px;
    f32 py;
    s32 held;
    T217D_440* g;

    if (self->text[0] == 0) {
        return;
    }
    g = &g_typedTextCaptionBox;
    if (g->mode != 0 && (u32)(g->state - 1) < 2) {
        return;
    }
    if (self->announce != 0) {
        scale = 1.0f;
        off = (1.0f - ((f32*)&D_0027240C)[0]) * 66.40001f;
    } else {
        scale = self->blend;
        off = 0.0f;
    }
    packed = self->colorWord;
    ((u8*)&packed)[3] = (u8)(s32)((f32)((u8*)&packed)[3] * scale);
    held = packed.v;
    px = self->w;
    py = self->h;
    out.Pos(self->shownX, self->shownY + off);
    out.Size(px, py);
    slot.v = held;
    out.Color(&slot.v);
    out.FlagA(0);
    out.FlagB(0);
    if (self->announce == 0) {
        T217D_0F0* g2 = &g_mapScreenList;
        PacketWriter* s = &g_gsPacketWriter;
        f32 sc = scale;
        f32 y;
        if (g2->open != 0 && g2->current != 0 && g2->current->mode == 2) {
            sc = 1.0f;
        }
        ((u8*)&slot)[0] = 0;
        ((u8*)&slot)[1] = 0;
        ((u8*)&slot)[2] = 0;
        ((u8*)&slot)[3] = (u8)(s32)(sc * 64.0f);
        y = off + 492.80002f - 66.40001f;
        BeginGifTag(s, 0x46, 5, 0x441EE);
        AddGifRegisterWrite(s, 0x47, 0x30000);
        AddGifRegisterWrite(s, 0x42, 0x44);
        AddGifRgbaEntry(s, (u32)slot.v);
        AddGifXyzfEntry(s, 0x6C00, (s32)((y * 0.45454547f + 1936.0f) * 16.0f), 0xFFFFFF0, 0);
        AddGifXyzfEntry(s, 0x9400, 0x8700, 0xFFFFFF0, 0);
    }
    PushFontScale(self->font, self->scale, self->scale);
    InitTextReader(&buf, &self->text[0], self->font);
    DrawAlignedText(&buf, &out, 0, &g_gsPacketWriter);
    PopFontScale(self->font);
}

// Sets up the hint glyph with a copy of font 2 and the text "B", initially off.
void InitHintGlyphElement(T217D_420* self)
{
    Font* o;
    const FontVt* vt;

    SetupScreenElementText(self);
    o = GetFontById(2);
    vt = o->vt;
    // the class's this-adjustment from its vtable, not a field
    self->font = vt->clone((Font*)((u8*)o + vt->adj1), 1.0f, 1.0f);
    self->vt->m08(self, "B");
    self->flag = 0;
}

// Per-frame update of the hint glyph: shown while its flag is set, the player is not in state 6
// and the element stack is in state 3 with fewer than 2 entries, hidden otherwise.
void UpdateHintGlyphElement(T217D_420* self)
{
    Player* g;
    ElementStack* m;

    UpdateScreenElementSlide(self);
    if (self->flag == 0) goto tail;
    g = g_player;
    if (g != 0 && g->state == 6) goto tail;
    m = (ElementStack*)g_elementStack;
    if (m->state == 3 && m->count < 2) {
        self->vt->m14(self);
        return;
    }
tail:
    self->vt->m15(self);
}

// Draws the element's text plus the glyph "L" of font 1 on top, with its size pulsing with the
// elapsed time.
void DrawHintGlyphElement(T217D_420* self)
{
    Layout_137228 buf;
    Quad4 tmp;
    s32 mask = (s32)0xFF808080;
    DrawScreenElementText(self);
    f32 half = 0.5f;
    f32 sc = Cosine(WrapAngle(g_elapsedTime * 8.0f)) * half + half;
    Font* h = GetFontById(1);
    f32 s2 = sc * 0.1f + half;
    PushFontScale(h, s2, s2);
    f32 w = MeasureFontString(h, (const char*)((void*)"L"));
    f32 ht = (f32)h->height * h->sy;
    ((Layout_137228*)&buf)->Pos(self->x + 2.0f + self->w * half - w * half, self->y + 14.0f + self->h * half - ht * half);
    ((Layout_137228*)&buf)->Size(w, ht);
    tmp.w[0] = mask;
    ((Layout_137228*)&buf)->Color(&tmp.w[0]);
    ((Layout_137228*)&buf)->SetF14(0);
    ((Layout_137228*)&buf)->SetF18(0);
    DrawFontString(h, "L", (StringLayout*)&buf, 0, &g_gsPacketWriter);
    PopFontScale(h);
}

// Sets up the letterbox element with a slide-out time of 0.5 s.
void InitLetterboxElement(T217D_560* self)
{
    SetupScreenElementText(self);
    self->outTime = 0.5f;
}

// Sets the mode of the element (a screen element 0x560) but lets the screen fade override it:
// while the fade is in mode 1 it ignores a change to 3 or 0; in mode 3 it shows or hides the
// element depending on a flag and, to show it, posts the caption of the current level entry.
// Closes the caption and the cycling glyph element when going to 0.
void SetElementModeFollowingFade(T217D_560* self, s32 newval)
{
    T217D_3D0* g;
    GameProgress* gg;

    if (self->mode != newval) {
        if (g_screenFade.mode == 1) {
            if (newval == 3 || newval == 0) {
                newval = self->mode;
            }
        }
        if (g_screenFade.mode == 3) {
            if ((u32)(newval - 1) < 2) {
                newval = 0;
                if ((*(s32*)D_00275B00 & 8) == 0) {
                    newval = 2;
                    if (g_saveData->levelIndex != 0 && g_activeStepSequence == 0) {
                        g = &g_copiedTextCaption;
                        g->pending = 0;
                        g->vt->m16(g, 0);
                        gg = g_saveData;
                        SetElementTextFromEntry(g, gg->levelIndex, gg->entryIndex);
                        g->announce = 1;
                        SetScreenElementHoldTime(g, 0.0f);
                        g->vt->m16(g, 2);
                    }
                }
            }
        }
        if (self->mode != newval && newval == 0) {
            T217D_3D0* a = &g_copiedTextCaption;
            if (a->announce != 0) {
                a->vt->m16(a, 0);
            }
            T217D_600* b = &g_cyclingGlyphElement;
            if (b->flag != 0) {
                b->vt->m16(b, 0);
            }
        }
    }
    SetScreenElementMode(self, newval);
}

// Draws the black bar at the bottom of the screen, 66.4 high at full blend (the screen is 492.8
// high), as one sprite on the GS.
void DrawLetterboxElement(T217D_560* self)
{
    f32 x = self->blend * 66.40001f;
    f32 y = 492.80002f - x;
    BeginGifTag(&g_gsPacketWriter, 6, 7, 0x044441EE);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x47, 0x30000);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x42, 0x44);
    AddGifRgbaEntry(&g_gsPacketWriter, 0x80000000);
    AddGifXyzfEntry(&g_gsPacketWriter, 0x6C00, 0x7900, 0x0FFFFFF0, 0);
    AddGifXyzfEntry(&g_gsPacketWriter, 0x9400, (s32)((x * 0.45454547f + 1936.0f) * 16.0f), 0x0FFFFFF0, 0);
    AddGifXyzfEntry(&g_gsPacketWriter, 0x6C00, (s32)((y * 0.45454547f + 1936.0f) * 16.0f), 0x0FFFFFF0, 0);
    AddGifXyzfEntry(&g_gsPacketWriter, 0x9400, 0x8700, 0x0FFFFFF0, 0);
}

f32 g_titleFontScaleX = 0.9f;
f32 g_titleFontScaleY = 0.9f;
TextStyle g_titleStyle = {0};

// Sets up the title element with a scaled copy of its font and the frame font; with the
// animation record 0x493 present it is sized 366.75 by 165.75, otherwise it shows the game's
// title as text.
void InitTitleElement(T217D_470* self)
{
    SetupScreenElementText(self);
    Font* in = self->font;
    // the class's this-adjustment from its vtable, not a field
    self->font = in->vt->clone((Font*)((u8*)in + in->vt->adj1), g_titleFontScaleX, g_titleFontScaleY);
    if (GetFontById(2) != 0) {
        self->frame = (Font**)&g_titleStyle;
        *self->frame = GetFontById(2);
    }
    self->icon = FindAnimRecord(0x493);
    if (self->icon != 0) {
        SetScreenElementSize(self, 366.75f, 165.75f);
    } else {
        self->vt->m08(self, "Sly Cooper
and the Thievius Raccoonus");
    }
}

// Draws a title element: as a textured sprite of its icon, with the size of the element, when it
// has one; otherwise as plain text.
void DrawTitleElement(T217D_470* self)
{
    if (self->icon != 0) {
        TextureTable* sub = ((AnimRecord*)self->icon)->elems;
        ImageRecord* pr = (ImageRecord*)*sub->p0c;
        u64 v = GetTextureRegisterBits(sub, 0, 0);
        u8 rgba[4];
        BeginGifTag(&g_gsPacketWriter, 0x156, 0xA, 0x43431EEEEEULL);
        AddGifRegisterWrite(&g_gsPacketWriter, 0x47, 0x33001);
        AddGifRegisterWrite(&g_gsPacketWriter, 0x42, 0x44);
        AddGifRegisterWrite(&g_gsPacketWriter, 6, v);
        AddGifRegisterWrite(&g_gsPacketWriter, 0x14, 0x60);
        AddGifRegisterWrite(&g_gsPacketWriter, 8, 5);
        *(u32*)rgba = 0x80808080;
        AddGifRgbaEntry(&g_gsPacketWriter, *(u32*)rgba);
        AddGifUvEntry(&g_gsPacketWriter, 0, pr->f2 << 4);
        AddGifXyzfEntry(&g_gsPacketWriter, (s32)((self->x + 1728.0f) * 16.0f), (s32)((self->y * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        AddGifUvEntry(&g_gsPacketWriter, pr->f0 << 4, 0);
        AddGifXyzfEntry(&g_gsPacketWriter, (s32)((self->x + self->w + 1728.0f) * 16.0f), (s32)(((self->y + self->h) * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    } else {
        DrawScreenElementText(self);
    }
}

f32 g_promptFontScaleX = 0.7f;
f32 g_promptFontScaleY[2] = { 0.6f, 0.0f };
const char* g_promptTexts[3] = { "Press START button for New Game", "Press START button to Resume Game", "Press SELECT button for Menu" };
const char* g_noControllerText = "No Controller";
TextStyle g_promptStyle = {0};

// Sets up the prompt element with a scaled copy of its font and the frame font, reads its two
// display flags (one from a global equal to 3, one from a nonzero field of another object) and
// builds its text.
void InitPromptElement(T217D_4C0* self)
{
    const FontVt* vt;

    SetupScreenElementText(self);
    vt = self->font->vt;
    // the class's this-adjustment from its vtable, not a field
    self->font = vt->clone((Font*)((u8*)self->font + vt->adj1), g_promptFontScaleX, g_promptFontScaleY[0]);
    if (GetFontById(2)) {
        self->frame = (Font**)&g_promptStyle;
        *self->frame = GetFontById(2);
    }
    s32 a1 = 0;
    self->flagB = 0; *(s32*)&self->flagA = (D_00262C84 == 3);
    if (D_00269988 != 0) {
        if (D_00269988->f0C != 0.0f) {
            a1 = 1;
        }
    }
    self->flagB = a1;
    RebuildPromptText(self);
}

// Rebuilds the prompt text: two lines from the prompt texts when a controller is present (grey),
// or the no-controller text (red); then sizes the element to the text.
void RebuildPromptText(T217D_4C0 *self)
{
    ColoredText loc;
    f32 y;

    if (self->flagA != 0) {
        loc.col.c[0] = 0x6F;
        loc.col.c[1] = 0x6F;
        loc.col.c[2] = 0x6F;
        loc.col.c[3] = 0xFF;
        self->rgba = loc.col;
        u8 *tbl = (u8*)g_promptTexts;
        s32 off = self->flagB ? 4 : 0;
        FormatToString(self->text, (const char *)"%s
%s", *(s32 *)(tbl + off), *(s32 *)(tbl + 8));
    } else {
        loc.col.c[0] = 0x6F;
        loc.col.c[1] = 0x1F;
        loc.col.c[2] = 0x1F;
        loc.col.c[3] = 0xFF;
        self->rgba = loc.col;
        CopyString(self->text, (const char *)g_noControllerText);
    }
    PushFontScale(self->font, self->scale, self->scale);
    InitTextReader(&loc.reader, self->text, self->font);
    {
        f32 x = MeasureTextWidth(&loc.reader);
        y = MeasureTextHeight(&loc.reader, 0.0f);
        SetScreenElementSize(self, x, y);
    }
    PopFontScale(self->font);
}

// Sets the element's mode; a pending change rebuilds the prompt text first when the mode is 0,
// which makes the mode 1 instead.
void SetElementModeRebuildingText(T217D_4C0* self, s32 force)
{
    if (self->pending != 0 && force == 0) {
        self->pending = 0;
        RebuildPromptText(self);
        force = 1;
    }
    SetScreenElementMode(self, force);
}

// Per-frame update of the prompt: when its two display flags have changed it rebuilds its text,
// then updates the slide.
void UpdatePromptElement(T217D_4C0* self)
{
    if (D_00275BF0 == 1) {
        s32 b = 0;
        s32 a = D_00262C84 == 3;
        if (D_00269988 != 0 && D_00269988->f0C != 0.0f) {
            b = 1;
        }
        if ((a == 0) != (self->flagA == 0) || (b == 0) != (self->flagB == 0)) {
            self->flagA = a;
            self->flagB = b;
            RebuildPromptText(self);
        }
    }
    UpdateScreenElementSlide(self);
}

extern f32 g_elementBlendLimit;

// Draws the prompt element: its frame and text, positioned between hidden and shown by the blend,
// with the colour's alpha pulsing as a sine of the elapsed time.
void DrawPromptElement(T217D_4C0* self)
{
    LayoutBuilder out;
    T217D_Word tmp;
    T217D_Word slot;
    u8 loc[0xB0];

    f32 s = Sine(g_elapsedTime * 3.0f);
    tmp = self->colorWord;
    ((u8*)&tmp)[3] = (u8)(s32)((s * 0.5f + 0.5f) * 255.0f);
    f32 t = g_elementBlendLimit <? self->blend;
    f32 u = 1.0f - t;
    f32 w = self->w;
    f32 h = self->h;
    s32 held = tmp.v;
    out.Pos(u * self->hiddenX + t * self->shownX, u * self->hiddenY + t * self->shownY);
    out.Size(w, h);
    slot.v = held;
    out.Color(&slot.v);
    out.FlagA(2);
    out.FlagB(0);
    if (self->frame != 0) {
        StyleDrawerBuilder::Draw(self->frame, &out, &g_gsPacketWriter);
    }
    PushFontScale(self->font, self->scale, self->scale);
    InitTextReader((TextReader*)loc, &self->text[0], self->font);
    DrawAlignedText((TextReader*)loc, &out, 0, &g_gsPacketWriter);
    PopFontScale(self->font);
}

// Draws one line between two points (a0 to a2 and a3 to a5 are the x, y and z of the ends in GS
// units) in the RGBA colour given, with alpha blending when the alpha is below 255; flag selects
// another register value.
void DrawLineSegment(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, void* color, s32 flag)
{
    u8* rgba = (u8*)color;
    BeginGifTag(&g_gsPacketWriter, rgba[3] < 0xFF ? 0x41 : 1, 4, 0x441E);

    AddGifRegisterWrite(&g_gsPacketWriter, 0x47, (u64)(flag ? 0x11001 : 0x11000) | (flag ? 0x60000 : 0x20000));

    AddGifRgbaEntry(&g_gsPacketWriter, ((u32)((rgba[3] + 1) & 0x1FE) << 23) | (rgba[2] << 16) | (rgba[1] << 8) | rgba[0]);
    AddGifXyzfEntry(&g_gsPacketWriter, a0, a1, a2, 0);
    AddGifXyzfEntry(&g_gsPacketWriter, a3, a4, a5, 0);
    CloseGifTag(&g_gsPacketWriter, 0);
}

f32 g_letterPopDuration = 0.1f;
f32 g_letterGlyphScale = 1.3f;

// Sets up a glyph element in font 2 with the letter 'L' or 'K' (by which of the two elements it
// is) and measures its width and height at the glyph scale.
void InitLetterGlyphElement(T217D_5B0* self)
{
    SetupScreenElementText(self);
    self->font = GetFontById(2);
    if (self == &g_beatPressGlyphElement) {
        FormatToString(self->text, "%c", 0x4C);
    } else if (self == &g_bossBeatGlyphElement) {
        FormatToString(self->text, "%c", 0x4B);
    }
    PushFontScale(self->font, g_letterGlyphScale, g_letterGlyphScale);
    self->w = MeasureFontString(self->font, self->text);
    Font* in = self->font;
    self->h = (f32)in->height * in->sy;
    PopFontScale(self->font);
}

// The curve func_001AE5E0 keeps in memory: where it starts, a floor stored as the word 0, and a rate.
struct PopCurve {
    f32 start;
    union {
        s32 none;
        f32 floor;
    };
    f32 k;
};

// Draws the element's text scaled by a popping curve of the time since it appeared (it shrinks
// from the start scale to a floor along a parabola); nothing is drawn when the size is 0.
void DrawLetterGlyphElement(ScreenElement* self)
{
    PopCurve curve;
    LayoutBuilder out;
    s32 tmp;
    f32 size = 1.0f;
    curve.start = g_letterGlyphScale;
    curve.none = 0;
    curve.k = (1.0f - g_letterGlyphScale) / (g_letterPopDuration * g_letterPopDuration);
    f32 peak = Fpu::Sqrt(g_letterGlyphScale / curve.k);
    f32 age = g_elapsedTime - self->since;
    if (!(peak + g_letterPopDuration < age)) {
        f32 t = age - peak;
        size = (curve.floor >? curve.start + t * (t * curve.k));
    }
    size *= self->scale;
    if (!(size <= 0.0f)) {
        PushFontScale(self->font, size, size);
        char* text = self->text;
        f32 w = MeasureFontString(self->font, text);
        Font* font = self->font;
        f32 h = (f32)font->height * font->sy;
        s32 held = self->color;
        out.Pos(self->x, self->y);
        out.Size(w, h);
        tmp = held;
        out.Color(&tmp);
        out.FlagA(0);
        out.FlagB(0);
        DrawFontString(self->font, text, (StringLayout*)&out, 0, &g_gsPacketWriter);
        PopFontScale(self->font);
    }
}

f32 g_cyclingGlyphElementScale = 0.7f;

// Sets up a glyph element in font 1 with 0.25 s slide times, no hold, and the current cycling
// glyph as its text.
void InitCyclingGlyphElement(T217D_600* self)
{
    f32 k = 0.25f;
    char fl[2];
    s32 v;

    SetupScreenElementText(self);
    SetScreenElementSlideInTime(self, k);
    SetScreenElementSlideOutTime(self, k);
    SetScreenElementHoldTime(self, 0.0f);
    Font* r = GetFontById(1);
    f32 g = g_cyclingGlyphElementScale;
    self->font = r;
    SetScreenElementScale(self, g);
    v = GetCyclingGlyph();
    fl[1] = 0;
    fl[0] = v;
    self->vt->m08(self, fl);
    self->text[0] = 0;
}

// Sets the element's mode; a mode of 0 also clears the element's flag.
void SetElementModeClearingFlag(T217D_600* self, s32 flag)
{
    if (flag == 0) {
        self->flag = 0;
    }
    SetScreenElementMode(self, flag);
}

// Draws the line of the completion percent with a changing glyph in front, using the current time
// to slide it in and out (it is kept shown for 2 seconds in mode 2, then closed after one second
// once the background job has ended).
void DrawCyclingGlyphElement(T217D_600* self)
{
    u8 out[0x20];
    s32 tmp[4];
    char str[0x20];
    u8 buf[0xB0];
    f32 adj;
    f32 d;
    s32 held;
    s32 c;
    const char* fmt;
    char* sp;
    f32 px;
    f32 py;

    if (self->mode == 0) {
        return;
    }
    d = g_elapsedTime - self->since;
    if (self->mode == 2) {
        if (D_00272420 == self->mode) {
            self->flag = d < 2.0f;
        }
    }
    if (self->flag != 0) {
        adj = (1.0f - D_0027240C) * 66.40000915527344f;
    } else {
        adj = 0.0f;
        if (self->mode == 2) {
            if (1.0f < d) {
                if (IsBackgroundJobRunning((BackgroundJob*)g_backgroundJob) == 0) {
                    self->vt->m15(self);
                }
            }
        }
    }
    held = self->color;
    px = self->w;
    py = self->h;
    ((Layout_137228*)out)->Pos(self->x, self->y + adj);
    ((Layout_137228*)out)->Size(px, py);
    tmp[0] = held;
    ((Layout_137228*)out)->Color(tmp);
    ((Layout_137228*)out)->SetF14(0);
    ((Layout_137228*)out)->SetF18(0);
    fmt = "%c&1^07~b2a83d%d%%&.";
    sp = str;
    c = GetCyclingGlyph();
    FormatToString(sp, fmt, c, ComputeCompletionPercent(g_saveData));
    PushFontScale(self->font, self->scale, self->scale);
    InitTextReader((TextReader*)buf, sp, self->font);
    DrawAlignedText((TextReader*)buf, (Layout_137228*)out, 0, &g_gsPacketWriter);
    PopFontScale(self->font);
}

GlyphCycleTable g_cyclingGlyphSet = { (s8*)"ab", 0 };

// The glyph of the cycling set to show now: one step every 0.2 s of elapsed time.
Letter_1AEA08 GetCyclingGlyph(void)
{
    s32 scaled = (s32)(g_elapsedTime * 5.0f);
    u32 divisor = GetStringLength((const char*)g_cyclingGlyphSet.p);
    return g_cyclingGlyphSet.p[(u32)scaled % divisor];
}

// The static initialiser GCC writes for this file's text styles (three empty array
// constructions, then the five styles), written as a function with the loops and stores it
// compiles to, as its _GLOBAL_$I$ below is, until the styles are built by constructors here; then
// the 16 bytes the linker left of two layout setters.
void ConstructScreenTextStyles(s32 initialize, s32 priority)
{
    if (priority == 0xFFFF && initialize) {
        s32 i;
        for (i = 0x38; i != -1; i--) {
        }
        for (i = 0x38; i != -1; i--) {
        }
        for (i = 3; i != -1; i--) {
        }
        FillMemory(&g_framedElementStyle, 0, 0x1C);
        g_framedElementStyle.f04 = 0x2D;
        g_framedElementStyle.f08 = 2.0f;
        g_framedElementStyle.f0C = 1.0f;
        g_framedElementStyle.f14 = g_framedElementStyle.f10 = 0.3f;
        g_framedElementStyle.color = 0xFF7D4B00;
        FillMemory(&g_pointerCaptionStyle, 0, 0x1C);
        g_pointerCaptionStyle.f04 = 0x2D;
        g_pointerCaptionStyle.f08 = 2.0f;
        g_pointerCaptionStyle.f0C = -4.0f;
        g_pointerCaptionStyle.f14 = g_pointerCaptionStyle.f10 = 0.3f;
        g_pointerCaptionStyle.color = 0xFF7D4B00;
        FillMemory(&g_copiedCaptionStyle, 0, 0x1C);
        g_copiedCaptionStyle.f04 = 0x3D;
        g_copiedCaptionStyle.f08 = 2.0f;
        g_copiedCaptionStyle.f0C = -4.0f;
        g_copiedCaptionStyle.f14 = g_copiedCaptionStyle.f10 = 0.3f;
        g_copiedCaptionStyle.color = 0xFF7D4B00;
        FillMemory(&g_titleStyle, 0, 0x1C);
        g_titleStyle.f04 = 0x2D;
        g_titleStyle.f08 = 2.0f;
        g_titleStyle.f0C = -4.0f;
        g_titleStyle.f14 = g_titleStyle.f10 = 0.3f;
        g_titleStyle.color = 0xFF7D4B00;
        FillMemory(&g_promptStyle, 0, 0x1C);
        g_promptStyle.f04 = 0x2D;
        g_promptStyle.f08 = 2.0f;
        g_promptStyle.f0C = -4.0f;
        g_promptStyle.f14 = g_promptStyle.f10 = 0.3f;
        g_promptStyle.color = 0xFF7D4B00;
    }
}

LINKER_REMNANT(func_001AEC80);

// Constructs the screen text styles once at startup.
void ConstructScreenTextStylesAtStartup(void)
{
    ConstructScreenTextStyles(1, 0xFFFF);
}
