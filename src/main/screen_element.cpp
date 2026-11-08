// SPDX-License-Identifier: AGPL-3.0-or-later
// The source file from 0x1AA268 to 0x1AECB0, built whole (config/us/files.tsv): the screen
// elements' shared methods (func_001AA268 sets one up) and those of the screen elements built
// on them, up to the static initialiser that builds this file's text styles (func_001AEA70,
// still assembly) and its _GLOBAL_$I$ (func_001AEC90). Its .rodata (0x24CBD0 to 0x24CFBB) is the
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

extern void* const g_screenElements[];

// A 28-byte text style the static initialiser (func_001AEA70) clears (func_001F5C0C with 0x1C)
// and then fills.
struct TextStyle {
    void* f00;
    u8 f04;
    u8 pad05[3];
    f32 f08;
    f32 f0C;
    f32 f10;
    f32 f14;
    u32 f18;
};

// The font object's calls.
Font* GetFontById(s32 k);
void PushFontScale(Font* font, f32 x, f32 y);
f32 MeasureFontString(Font* font, void* text);
void DrawFontString(Font* font, void* text, void* out, s32 zero, void* d);
void PopFontScale(Font* font);
void* InitTextReader(void* out, void* text, Font* font);
void DrawAlignedText(void* buf, void* out, s32 zero, void* d);

void GetObjectWorldRotation(void* a, f32* out);
void TransformRotationBetweenFrames(int a, int b, void* c, f32* d);

extern f32 g_gameTime;
extern f32 g_frameDt;

void StepTimer(T217D_510* self, f32 value);

extern s32 g_defaultFont;

typedef void (*VirtualCall_1AA790)(void* a, void* b, void* c, void* d);


void SetTextLayoutPosition(void* out, f32 x, f32 y);
void SetTextLayoutSize(void* out, f32 x, f32 y);
void SetTextLayoutColor(void* out, s32* value);
void SetTextLayoutHorizontalAlign(void* out, s32 flag);
void SetTextLayoutVerticalAlign(void* out, s32 flag);

typedef void* (*VFn_1A9960)(void* self);

extern ElementPlaceTable g_elementPlaces;
s32 IsObjectOfKind(void* node, s32 kind);

void* FillMemory(void* p, s32 value, s32 size);

void GetObjectWorldRotation(void* self, void* arg);
void TransformRotationBetweenFrames(void* a0, void* a1, void* a2, void* a3);
void SetListLinkOffset(void* self, s32 value);


void SetTextLayoutColor(void* out, void* p);
void SetTextLayoutHorizontalAlign(void* out, s32 v);
void SetTextLayoutVerticalAlign(void* out, s32 v);

extern u8 g_padRouting[];

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();

extern s8 g_fontEscapeKeys[];
extern u8 g_charClassFlags[];
s32 FormatToString(char* dst, const char* fmt, ...);
void* CopyString(void* dst, void* src);
void SetListLinkOffset(void* p, s32 a);
PlacedObject* CreateObjectCopy(PlacedObject* a, World* b, BaseObject* c);

void DrawCyclingGlyphElement(u8* a);
extern f32 D_002743A0[4];

s32 FormatToStringBounded(char* dst, s32 cap, const char* fmt, ...);
extern s32 D_002751D4;

void StartSoundEffect(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

f32 TruncateFloat(f32 x);
void DrawScreenElementText();
void GetScreenElementSlideInTime();
void GetScreenElementHoldTime();
void GetScreenElementSlideOutTime();
void ResetScreenElement();
void ShowScreenElement();
void HideScreenElement();
void SetScreenElementClock();
void AreScreenElementsTogether();
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

s32 GetStringLength(const char*);
void* CopyString(char*, const char*);
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

s32 GetStringLength(const char* p);
void* CopyString(char* dst, const char* p);
void MeasureText(void* out, f32 t, f32* a, f32* b);

void RebuildPromptText(T217D_4C0* self);


extern TextStyle D_002743D0;


extern TextStyle D_002743F0;

s32 CompareStrings(const char* a, const char* b);


extern u8 g_elementStack[];

s32 MatchesObjectId(void* key, s32 item);
s32 IsObjectOfKind(void* key, s32 item);


extern TextStyle D_00274410;

// NEAR: register and load order of D_00262C84 vs D_00269988 (retail keeps the x load in v1, ours in a0; xori placed differently)

struct Node_001AE178 { u8 pad0[0xC]; f32 f0C; };
extern s32 D_00275BF0;
extern s32 D_00262C84;
extern Node_001AE178* D_00269988;

// NEAR: the store of func_0015C1C0 result is before the float load and call; retail puts it in the delay slot of the func_001AA788 call

extern f32 D_002744AC;
// The letter func_001AEA08 picks: PAL reads the table's bytes unsigned (docs/VERSIONS.md).
#ifdef VERSION_EU
typedef u8 Letter_1AEA08;
#else
typedef s8 Letter_1AEA08;
#endif
Letter_1AEA08 GetCyclingGlyph(void);

extern f32 D_0027446C;
// The vertical scale of the clone func_001ADF28 makes of its font (D_0027446C is the
// horizontal one); the label runs on over a word nothing reads.
extern f32 D_00274470[2];
extern TextStyle D_00274488;

s32 MatchesObjectId(s32 value, s32 item);
s32 IsObjectOfKind(s32 value, s32 item);

s32 MatchesObjectId(void* a, s32 b);

typedef void (*VFn_1AF3B8)(void* self);
void* CreateObjectCopy(void* a, void* b, void* c);

extern f32 g_elapsedTime;
extern f32 D_0027240C;
extern s32 D_00272420;
extern u8 g_backgroundJob[];

s32 IsBackgroundJobRunning(void* p);
void* ComputeCompletionPercent(void* p);


void SetElementTextFromEntry(ScreenElement* self, s32 hi, s32 lo);


extern f32 D_00274448;
extern f32 D_0027444C;
extern TextStyle D_00274450;

void* FindAnimRecord(s32 key);

extern f32 D_002744A8;

struct ProgressEntry {
    u32 flags;
    u32 pad;
    f32 time;
};

extern s32 FormatToString(char*, const char*, ...);
extern s32 AppendString(char*, const char*);



u32 GetEntryFlags(u32 packed);
char* GetEntryName(u32 packed);

f32 WrapAngle(f32 a);
f32 Cosine(f32 x);

extern const char* D_00274478[];
extern const char* D_00274484;

// A colour and a text reader, one frame slot (func_001ADFF0).
struct ColoredText { T217D_Rgba col; u8 pad[12]; TextReader reader; };

s32 FormatToString(char *dst, const char *fmt, ...);
void* CopyString(char *dst, const char *src);
f32 MeasureTextWidth(void *obj);
f32 MeasureTextHeight(void *obj, f32 a);


extern const char* D_00274430[];

void CountCategoryFlags(s32 key, s32* a1, s32* a2, s32* a3);
s32 GetStringLength(void* p);

struct GlyphCycleTable { s8* p; s32 pad; };
extern GlyphCycleTable D_002744B0;



void BeginGifTag(PacketWriter* p, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* p, u64 a, u64 b);
void AddGifRgbaEntry(PacketWriter* p, u32 value);
void AddGifXyzfEntry(PacketWriter* p, s32 a1, s32 a2, s32 a3, s32 a4);


void BeginGifTag(PacketWriter* p, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* p, u64 a, u64 b);
void AddGifRgbaEntry(PacketWriter* p, u32 value);
void AddGifXyzfEntry(PacketWriter* p, s32 a1, s32 a2, s32 a3, s32 a4);
void CloseGifTag(PacketWriter* p, s32 a);

extern u8 D_00275B00[];

void SetTextLayoutPosition(Layout_137228* out, f32 x, f32 y);
void SetTextLayoutSize(Layout_137228* out, f32 x, f32 y);
void SetTextLayoutColor(Layout_137228* out, s32* value);
void SetTextLayoutHorizontalAlign(Layout_137228* out, s32 flag);
void SetTextLayoutVerticalAlign(Layout_137228* out, s32 flag);
// A layout with its setters as calls (SetTextLayoutPosition and the others).
struct LayoutBuilder : Layout_137228 {
    void Pos(f32 x, f32 y) { SetTextLayoutPosition(this, x, y); }
    void Size(f32 x, f32 y) { SetTextLayoutSize(this, x, y); }
    void Color(s32* c) { SetTextLayoutColor(this, c); }
    void FlagA(s32 f) { SetTextLayoutHorizontalAlign(this, f); }
    void FlagB(s32 f) { SetTextLayoutVerticalAlign(this, f); }
};
struct StyleDrawer {
    static void Draw(Font** h, LayoutBuilder* out, void* tbl)
    {
        if (*h != 0) {
            const FontVt* vt = (*h)->vt;
            vt->drawBox((Font*)((u8*)*h + vt->adj9), h, out, tbl);
        }
    }
};




void BeginGifTag(PacketWriter* p, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* p, u64 a, u64 b);
void AddGifRgbaEntry(PacketWriter* p, u32 rgba);
void AddGifUvEntry(PacketWriter* p, s32 a, s32 b);
void AddGifXyzfEntry(PacketWriter* p, s32 a, s32 b, s32 c, s32 d);
u64 GetTextureRegisterBits(TextureTable* t, s32 i, s32 j);



void BeginGifTag(PacketWriter* f, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* f, u64 a, u64 b);
void AddGifRgbaEntry(PacketWriter* f, u32 v);
void AddGifXyzfEntry(PacketWriter* f, s32 a, s32 b, s32 c, s32 d);
struct LayoutByValue : Layout_137228 {
    void Pos(f32 x, f32 y) { SetTextLayoutPosition(this, x, y); }
    void Size(f32 x, f32 y) { SetTextLayoutSize(this, x, y); }
    void Color(s32 c) { SetTextLayoutColor(this, &c); }
    void FlagA(s32 f) { SetTextLayoutHorizontalAlign(this, f); }
    void FlagB(s32 f) { SetTextLayoutVerticalAlign(this, f); }
};

struct FontCalls {
    static f32 Advance(Font* f, s32 ch) { return f->vt->width((Font*)((u8*)f + f->vt->adj3), ch); }
    static void Begin(Font* f, s32 a, void* d) { f->vt->begin((Font*)((u8*)f + f->vt->adj4), a, (s32)d); }
    static void Glyph(Font* f, s32 ch, s32 color, void* d, f32 x, f32 y) { f->vt->draw(x, y, (Font*)((u8*)f + f->vt->adj6), ch, color, (s32)d); }
    static void End(Font* f, s32 a, void* d) { f->vt->end((Font*)((u8*)f + f->vt->adj7), a, (s32)d); }
};

struct ClampFloat {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        return x < lo ? lo : (hi < x ? hi : x);
    }
};

struct VEnt_1AC0E8 { s16 delta; s16 index; void (*fn)(void* self, f32 x, f32 y, s32 a, s32 b, void* c); };
struct Text_1AC0E8 { u8 pad[0x4C]; VEnt_1AC0E8* vtbl; };
extern RampProfile D_002743C0;

f32 ApproachValueWithRamp(RampProfile* p, s32 a1, f32 f12, f32 f13, f32 f14);
void SetTextLayoutColor(Layout_137228* out, Quad4* value);
void WriteColoredSpritePacket(f32 x0, f32 y0, f32 x1, f32 y1, s32 r, s32 g, s32 b, s32 a, PacketWriter* d);
f32 Sine(f32 x);

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

void SetupScreenElementText(ScreenElement* self)
{
    s32 value = g_defaultFont;
    u32 flags = 0xFF808080;
    self->font = (Font*)value;
    self->scale = 1.0f;
    self->color = flags;
    self->text[0] = 0;
}

f32 D_002743A0[4] = { 0.0f, 2.0f, -1.0f, 0.0f };

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
        f32 k = D_002743A0[0] + p * (D_002743A0[1] + p * D_002743A0[2]);
        self->x = self->hiddenX + k * (self->shownX - self->hiddenX);
        self->y = self->hiddenY + k * (self->shownY - self->hiddenY);
        PlaceAnchoredScreenElements(self);
    }
    self->vt->m16(self, s);
}

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
        SetTextLayoutPosition(out, self->x, self->y);
        SetTextLayoutSize(out, p, q);
        tmp = held;
        SetTextLayoutColor(out, &tmp);
        SetTextLayoutHorizontalAlign(out, 0);
        SetTextLayoutVerticalAlign(out, 0);

        handle = self->frame;
        if (handle != 0) {
            void* obj = *(void**)handle;
            if (obj != 0) {
                void* vt = *(void**)((u8*)obj + 76);
                VirtualCall_1AA790 fn = *(VirtualCall_1AA790*)((u8*)vt + 76);
                s16 adj = *(s16*)((u8*)vt + 72);
                fn((u8*)obj + adj, handle, out, &g_gsPacketWriter);
            }
        }
        x = self->scale;
        PushFontScale(self->font, x, x);
        DrawFontString(self->font, &self->text[0], out, 0, &g_gsPacketWriter);
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

void ResetScreenElement(ScreenElement* self)
{
    self->vt->m16(self, 0);
}

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

void HideScreenElement(ScreenElement* self)
{
    s32 m = self->mode;
    if (m < 3) {
        if (m > 0) {
            self->vt->m16(self, 3);
        }
    }
}

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

void SetScreenElementSize(ScreenElement *self, f32 x, f32 y) {
    if (0.0f <= x) {
        self->w = x;
    }
    if (0.0f <= y) {
        self->h = y;
    }
    PlaceScreenElement(self);
}

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

void InitCounterCaption(T217D_E30* self)
{
    SetupScreenElementText(self);
    self->font = GetFontById(2);
    self->shown = -1;
    self->rate = 6000.0f;
    switch (self->index) {
    case 3:
        self->target = &g_saveData->f19E0;
        break;
    case 4:
        self->target = &g_currentEntry->count64;
        self->limit = &g_currentWorld->count2300;
        break;
    case 5:
        self->target = &g_currentLevelRecord->f438;
        break;
    case 6:
        self->target = &g_saveData->f19E8;
        break;
    case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
    case 28: case 29:
    case 36:
        self->target = &self->shown;
        break;
    }
}

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
    SetTextLayoutPosition(out, self->x, self->y);
    SetTextLayoutSize(out, px, py);
    tmp[0] = held;
    SetTextLayoutColor(out, &tmp[0]);
    SetTextLayoutHorizontalAlign(out, 0);
    SetTextLayoutVerticalAlign(out, 0);
    PushFontScale(self->font, self->scale, self->scale);
    InitTextReader(buf, &self->text[0], self->font);
    DrawAlignedText(buf, out, 0, &g_gsPacketWriter);
    PopFontScale(self->font);
}

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
        if ((u32)(g_saveData->f19D8 - 1) < 4) {
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

f32 GetCaptionHoldTime(void)
{
    return g_gameClock.running != 0 ? 2.5f : 0.0f;
}

void InitTimerElement(T217D_510* self)
{
    SetupScreenElementText(self);
    self->font = GetFontById(2);
    self->lastTenth = self->lastSecond = -1;
    self->warnAt = 3.4028235e+38f;
    self->f290 = 1;
    SetTimerState(self, 0);
}

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

void DrawTimerElement(T217D_510* self)
{
    Layout_137228 L;
    Quad4 tag;
    T217D_Word warn;
    if (self->text[0] != 0) {
        f32 f234 = self->w;
        f32 f238 = self->h;
        s32 s0v = self->color;
        SetTextLayoutPosition(&L, self->x, self->y);
        SetTextLayoutSize(&L, f234, f238);
        tag.w[0] = s0v;
        SetTextLayoutColor(&L, &tag.w[0]);
        SetTextLayoutHorizontalAlign(&L, 0);
        SetTextLayoutVerticalAlign(&L, 0);
        void* obj = self->frame;
        if (obj != 0) {
            Font* sub = *(Font**)obj;
            if (sub != 0) {
                const FontVt* d = sub->vt;
                d->drawBox((Font*)((u8*)sub + d->adj9), obj, &L, &g_gsPacketWriter);
            }
        }
        f32 v = self->scale;
        u8* dp = (u8*)&g_gsPacketWriter;
        PushFontScale(self->font, v, v);
        ((u8*)&tag)[0] = 0x54;
        ((u8*)&tag)[1] = 0;
        DrawFontString(self->font, &tag, &L, 0, dp);
        f32 r = MeasureFontString(self->font, &tag);
        f32 a = self->x + r;
        L.y = self->y;
        L.x = a;
        if (self->warned != 0) {
            warn = self->warnColor;
            *(T217D_Word*)&L.color = warn;
        }
        DrawFontString(self->font, (u8*)self + 9, &L, 0, dp);
        PopFontScale(self->font);
    }
}

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

void SetTimerLimit(T217D_510* self, T217D_510_Fn onEnd, f32 limit)
{
    self->limit = limit;
    self->onEnd = onEnd;
}

void StartTimerCounting(T217D_510* self)
{
    SetTimerState(self, 2);
}

void StopTimer(T217D_510* self)
{
    self->f290 = 1;
    SetTimerState(self, 0);
}

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

f32 D_002743B0 = 18.0f;
f32 D_002743B4 = 8.0f;
f32 D_002743B8 = 26.0f;
f32 D_002743BC = 340.0f;

INCLUDE_RODATA(jtbl_0024CD70);
INCLUDE_ASM(func_001ABE70);

void DecrementGaugeCount(T217D_2E0* self)
{
    s32 n = self->f270 - 1;
    self->f270 = n;
    if (n <= 0) {
        n = self->f26C - 1;
        self->f26C = n;
        if (n <= 0) {
            self->f270 = 0;
            self->f26C = 0;
        } else {
            self->f270 = self->f264;
        }
    }

    s32 a = self->f264;
    f32 d = (f32)self->f268;
    s32 v0 = self->f26C - 1;
    s32 b = self->f270;
    v0 = (-1 < v0) ? v0 : 0;
    self->fillTarget = (f32)(v0 * a + b) / d;
    self->changedAt = g_gameClock.time;
}

RampProfile D_002743C0 = { 0.5f, 0.25f, 0.2f, 0.0f };

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
    self->fill = ApproachValueWithRamp(&D_002743C0, 0, self->fill, self->fillTarget, g_gameClock.dt);
    f32 y = self->barH;
    f32 h = self->fill * y;
    y -= h;
    f32 w = self->barW;
    SetTextLayoutPosition(&out, self->x + self->barX, self->y + self->barY);
    SetTextLayoutSize(&out, w, y);
    {
        Quad4 tmp;
        tmp.w[0] = grey;
        SetTextLayoutColor(&out, &tmp);
    }
    SetTextLayoutHorizontalAlign(&out, 0);
    SetTextLayoutVerticalAlign(&out, 0);
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
    out.f18 = (void*)1;
    char str[2] = { self->letter + 0x72, 0 };
    DrawFontString(self->font, str, &out, 0, &g_gsPacketWriter);
    PopFontScale(self->font);
}

TextStyle D_002743D0 = {0};

void InitFramedElement(T217D_330* self)
{
    const FontVt* vt;

    SetupScreenElementText(self);
    vt = self->font->vt;
    self->font = vt->clone((Font*)((u8*)self->font + vt->adj1), 1.25f, 1.25f);
    if (IsFontLoaded(2)) {
        self->frame = (Font**)&D_002743D0;
        *self->frame = GetFontById(2);
    }
}

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

        u8* h = (u8*)self->frame;
        if (h != 0) {
            slot = *(T217D_Word*)(h + 0x18);
            h[0x1B] = (u8)((f32)h[0x1B] * self->blend);
            StyleDrawer::Draw(self->frame, &out, &g_gsPacketWriter);
            *(T217D_Word*)((u8*)self->frame + 0x18) = slot;
        }
        PushFontScale(self->font, self->scale, self->scale);
        InitTextReader(loc, &self->text[0], self->font);
        DrawAlignedText(loc, &out, 0, &g_gsPacketWriter);
        PopFontScale(self->font);
    }
}

TextStyle D_002743F0 = {0};

void InitPointerTextCaption(T217D_380* self)
{
    const FontVt* vt;

    SetupScreenElementText(self);
    vt = self->font->vt;
    self->font = vt->clone((Font*)((u8*)self->font + vt->adj1), 0.9f, 0.9f);
    self->color = 0xDF7F7F7Fu;
    if (IsFontLoaded(2)) {
        self->frame = (Font**)&D_002743F0;
        *self->frame = GetFontById(2);
    }
}

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

s32 AreElementsTogetherOrPending(T217D_380* self, ScreenElement* other)
{
    s32 r = 0;
    if (AreScreenElementsTogether(self, other) != 0 || self->pending != 0) {
        r = 1;
    }
    return r;
}

void ShowElementUnlessTextPending(T217D_380* self)
{
    if (self->mode != 3 || self->pending == 0) {
        ShowScreenElement(self);
    }
}

void HideElementOrDropPendingText(T217D_380* self)
{
    if (self->mode == 3 && self->pending != 0) {
        self->pending = 0;
    } else {
        HideScreenElement(self);
    }
}

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
    c = ClampFloat::Of(self->blend / (1.0f / (f32)n), 0.0f, 1.0f);
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
            o->vt->drawBox((Font*)((u8*)o + o->vt->adj9), self->frame, &out, &g_gsPacketWriter);
        }
    }
    FontCalls::Begin(self->font, 0, &g_gsPacketWriter);
    for (i = 0; i < n; i++) {
        s32 ch = self->text[i];
        f32 d;
        c = ClampFloat::Of(self->blend / ((f32)(i + 1) / (f32)n), 0.0f, 1.0f);
        rest = 1.0f - c;
        FontCalls::Glyph(self->font, ch, self->color, &g_gsPacketWriter, c * x + rest * y, self->shownY);
        d = FontCalls::Advance(self->font, ch);
        x += d;
        y += d;
    }
    FontCalls::End(self->font, 0, &g_gsPacketWriter);
}

TextStyle D_00274410 = {0};

void InitCopiedTextCaption(T217D_3D0* self)
{
    Font* o;
    const FontVt* vt;

    SetupScreenElementText(self);
    o = GetFontById(0);
    vt = o->vt;
    self->font = vt->clone((Font*)((u8*)o + vt->adj1), 1.0f, 1.0f);
    self->scale = 0.8f;
    self->outTime = 0.5f;
    if (IsFontLoaded(2)) {
        self->frame = (Font**)&D_00274410;
        *self->frame = GetFontById(2);
    }
}

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

void SetElementTextFromPackedEntry(ScreenElement* self, s32 value)
{
    if (value != -1) {
        SetElementTextFromEntry(self, value >> 8, (u8)value);
    } else {
        self->vt->m08(self, "<unknown>");
    }
}

void SetElementTextFromEntry(ScreenElement* self, s32 a1, s32 a2)
{
    char buf[64];
    char str[64];
    u8* p;
    u32 packed;

    p = *(u8**)((u8*)&g_saveData);
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
const char* D_00274430[6] = { "", "Tide of Terror", "Sunset Snake Eyes", "Vicious Voodoo", "Fire in the Sky", "The Cold Heart of Hate" };

void SetElementTextFromIndexedCounts(ScreenElement* self, s32 idx)
{
    char buf[0x200];
    s32 a, b, c;
    CountCategoryFlags(idx, &a, &b, &c);
    G27C230* s1 = &g_saveData->levels[idx];
    CopyString(buf, D_00274430[idx]);
    char* d = buf + GetStringLength(buf);
    if (a)
        d += FormatToString(d, " &1%d^10~b2a83d/%d~.^.&.&3k&.", s1->f438, a);
    if (b)
        d += FormatToString(d, "%s&1%d^10~b2a83d/%d~.^.&.&3v&.", a ? ((char*)" ") : ((char*)""), s1->f43C, b);
    if (c)
        FormatToString(d, "%s&1%d^10~b2a83d/%d~.^.h&.", (a || b) ? ((char*)" ") : ((char*)""), s1->f440, c);
    self->vt->m08(self, buf);
}

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

void ShowElementUnlessCopiedTextPending(T217D_3D0* self)
{
    if (self->mode == 3 && self->pending != 0) return;
    ShowScreenElement(self);
}

void HideElementOrDropCopiedText(T217D_3D0* self)
{
    if (self->mode == 3 && self->pending != 0) {
        self->pending = 0;
    } else {
        HideScreenElement(self);
    }
}

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

void InitHintGlyphElement(T217D_420* self)
{
    Font* o;
    const FontVt* vt;

    SetupScreenElementText(self);
    o = GetFontById(2);
    vt = o->vt;
    self->font = vt->clone((Font*)((u8*)o + vt->adj1), 1.0f, 1.0f);
    self->vt->m08(self, "B");
    self->flag = 0;
}

void UpdateHintGlyphElement(T217D_420* self)
{
    Player* g;
    ElementStack* m;

    UpdateScreenElementSlide(self);
    if (self->flag == 0) goto tail;
    g = g_player;
    if (g != 0 && g->f2220 == 6) goto tail;
    m = (ElementStack*)g_elementStack;
    if (m->state == 3 && m->count < 2) {
        self->vt->m14(self);
        return;
    }
tail:
    self->vt->m15(self);
}

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
    f32 w = MeasureFontString(h, (void*)"L");
    f32 ht = (f32)h->height * h->sy;
    SetTextLayoutPosition(&buf, self->x + 2.0f + self->w * half - w * half,
                  self->y + 14.0f + self->h * half - ht * half);
    SetTextLayoutSize(&buf, w, ht);
    tmp.w[0] = mask;
    SetTextLayoutColor(&buf, &tmp.w[0]);
    SetTextLayoutHorizontalAlign(&buf, 0);
    SetTextLayoutVerticalAlign(&buf, 0);
    DrawFontString(h, (void*)"L", &buf, 0, &g_gsPacketWriter);
    PopFontScale(h);
}

void InitLetterboxElement(T217D_560* self)
{
    SetupScreenElementText(self);
    self->outTime = 0.5f;
}

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
                    if (g_saveData->f19D8 != 0 && D_0027051C == 0) {
                        g = &D_0026F138;
                        g->pending = 0;
                        g->vt->m16(g, 0);
                        gg = g_saveData;
                        SetElementTextFromEntry(g, gg->f19D8, gg->f19DC);
                        g->announce = 1;
                        SetScreenElementHoldTime(g, 0.0f);
                        g->vt->m16(g, 2);
                    }
                }
            }
        }
        if (self->mode != newval && newval == 0) {
            T217D_3D0* a = &D_0026F138;
            if (a->announce != 0) {
                a->vt->m16(a, 0);
            }
            T217D_600* b = &D_00273EB0;
            if (b->flag != 0) {
                b->vt->m16(b, 0);
            }
        }
    }
    SetScreenElementMode(self, newval);
}

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

f32 D_00274448 = 0.9f;
f32 D_0027444C = 0.9f;
TextStyle D_00274450 = {0};

void InitTitleElement(T217D_470* self)
{
    SetupScreenElementText(self);
    Font* in = self->font;
    self->font = in->vt->clone((Font*)((u8*)in + in->vt->adj1), D_00274448, D_0027444C);
    if (GetFontById(2) != 0) {
        self->frame = (Font**)&D_00274450;
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

f32 D_0027446C = 0.7f;
f32 D_00274470[2] = { 0.6f, 0.0f };
const char* D_00274478[3] = { "Press START button for New Game", "Press START button to Resume Game", "Press SELECT button for Menu" };
const char* D_00274484 = "No Controller";
TextStyle D_00274488 = {0};

void InitPromptElement(T217D_4C0* self)
{
    const FontVt* vt;

    SetupScreenElementText(self);
    vt = self->font->vt;
    self->font = vt->clone((Font*)((u8*)self->font + vt->adj1), D_0027446C, D_00274470[0]);
    if (GetFontById(2)) {
        self->frame = (Font**)&D_00274488;
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
        u8 *tbl = (u8*)D_00274478;
        s32 off = self->flagB ? 4 : 0;
        FormatToString(self->text, (const char *)"%s
%s", *(s32 *)(tbl + off), *(s32 *)(tbl + 8));
    } else {
        loc.col.c[0] = 0x6F;
        loc.col.c[1] = 0x1F;
        loc.col.c[2] = 0x1F;
        loc.col.c[3] = 0xFF;
        self->rgba = loc.col;
        CopyString(self->text, (const char *)D_00274484);
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

void SetElementModeRebuildingText(T217D_4C0* self, s32 force)
{
    if (self->pending != 0 && force == 0) {
        self->pending = 0;
        RebuildPromptText(self);
        force = 1;
    }
    SetScreenElementMode(self, force);
}

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

extern f32 D_00272B6C;

void DrawPromptElement(T217D_4C0* self)
{
    LayoutBuilder out;
    T217D_Word tmp;
    T217D_Word slot;
    u8 loc[0xB0];

    f32 s = Sine(g_elapsedTime * 3.0f);
    tmp = self->colorWord;
    ((u8*)&tmp)[3] = (u8)(s32)((s * 0.5f + 0.5f) * 255.0f);
    f32 t = D_00272B6C <? self->blend;
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
        StyleDrawer::Draw(self->frame, &out, &g_gsPacketWriter);
    }
    PushFontScale(self->font, self->scale, self->scale);
    InitTextReader(loc, &self->text[0], self->font);
    DrawAlignedText(loc, &out, 0, &g_gsPacketWriter);
    PopFontScale(self->font);
}

void DrawLineSegment(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, u8* rgba, s32 flag)
{
    BeginGifTag(&g_gsPacketWriter, rgba[3] < 0xFF ? 0x41 : 1, 4, 0x441E);

    AddGifRegisterWrite(&g_gsPacketWriter, 0x47, (u64)(flag ? 0x11001 : 0x11000) | (flag ? 0x60000 : 0x20000));

    AddGifRgbaEntry(&g_gsPacketWriter, ((u32)((rgba[3] + 1) & 0x1FE) << 23) | (rgba[2] << 16) | (rgba[1] << 8) | rgba[0]);
    AddGifXyzfEntry(&g_gsPacketWriter, a0, a1, a2, 0);
    AddGifXyzfEntry(&g_gsPacketWriter, a3, a4, a5, 0);
    CloseGifTag(&g_gsPacketWriter, 0);
}

f32 D_002744A4 = 0.1f;
f32 D_002744A8 = 1.3f;

void InitLetterGlyphElement(T217D_5B0* self)
{
    SetupScreenElementText(self);
    self->font = GetFontById(2);
    if (self == &D_00273C50) {
        FormatToString(self->text, "%c", 0x4C);
    } else if (self == &D_002739F0) {
        FormatToString(self->text, "%c", 0x4B);
    }
    PushFontScale(self->font, D_002744A8, D_002744A8);
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

void DrawLetterGlyphElement(ScreenElement* self)
{
    PopCurve curve;
    LayoutBuilder out;
    s32 tmp;
    f32 size = 1.0f;
    curve.start = D_002744A8;
    curve.none = 0;
    curve.k = (1.0f - D_002744A8) / (D_002744A4 * D_002744A4);
    f32 peak = Fpu::Sqrt(D_002744A8 / curve.k);
    f32 age = g_elapsedTime - self->since;
    if (!(peak + D_002744A4 < age)) {
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
        DrawFontString(self->font, text, &out, 0, &g_gsPacketWriter);
        PopFontScale(self->font);
    }
}

f32 D_002744AC = 0.7f;

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
    f32 g = D_002744AC;
    self->font = r;
    SetScreenElementScale(self, g);
    v = GetCyclingGlyph();
    fl[1] = 0;
    fl[0] = v;
    self->vt->m08(self, fl);
    self->text[0] = 0;
}

void SetElementModeClearingFlag(T217D_600* self, s32 flag)
{
    if (flag == 0) {
        self->flag = 0;
    }
    SetScreenElementMode(self, flag);
}

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
                if (IsBackgroundJobRunning(g_backgroundJob) == 0) {
                    self->vt->m15(self);
                }
            }
        }
    }
    held = self->color;
    px = self->w;
    py = self->h;
    SetTextLayoutPosition(out, self->x, self->y + adj);
    SetTextLayoutSize(out, px, py);
    tmp[0] = held;
    SetTextLayoutColor(out, tmp);
    SetTextLayoutHorizontalAlign(out, 0);
    SetTextLayoutVerticalAlign(out, 0);
    fmt = "%c&1^07~b2a83d%d%%&.";
    sp = str;
    c = GetCyclingGlyph();
    FormatToString(sp, fmt, c, ComputeCompletionPercent(g_saveData));
    PushFontScale(self->font, self->scale, self->scale);
    InitTextReader(buf, sp, self->font);
    DrawAlignedText(buf, out, 0, &g_gsPacketWriter);
    PopFontScale(self->font);
}

GlyphCycleTable D_002744B0 = { (s8*)"ab", 0 };

Letter_1AEA08 GetCyclingGlyph(void)
{
    s32 scaled = (s32)(g_elapsedTime * 5.0f);
    u32 divisor = GetStringLength((const char*)D_002744B0.p);
    return D_002744B0.p[(u32)scaled % divisor];
}

// The static initialiser GCC writes for this file's text styles (three empty array
// constructions, then the five styles), still assembly; then the 16 bytes the linker left of two
// layout setters, and the file's _GLOBAL_$I$, written as a function until the styles are built by
// constructors here.
INCLUDE_ASM(func_001AEA70);

LINKER_REMNANT(func_001AEC80);

void ConstructScreenTextStylesAtStartup(void)
{
    ConstructScreenTextStyles(1, 0xFFFF);
}
