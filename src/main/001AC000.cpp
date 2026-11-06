// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "screen_element.h"
#include "v24a0.h"
#include "v24a2.h"
#include "globals.h"
#include "game_progress.h"
#include "screen_fade.h"
#include "layout_137228.h"
#include "texture_table.h"
#include "shapes.h"

// The font object's calls (include/v24a2.h will declare them).
V24A2* func_0015C1C0(s32 k);
s32 func_0015C188(s32 k);
void func_0015C8B8(V24A2* font, f32 x, f32 y);
f32 func_0015C418(V24A2* font, void* text);
void func_0015C638(V24A2* font, void* text, void* out, s32 zero, void* d);
void func_0015C900(V24A2* font);
void* func_0015DB28(void* out, void* text, V24A2* font);
void func_0015E318(void* buf, void* out, s32 zero, void* d);

struct Loc_1AC638 {
    u8 data[0xB0];
    f32 x;
    f32 y;
};

s32 func_001E2100(const char* p);
void* func_001E2138(char* dst, const char* p);
void func_0015E290(void* out, f32 t, f32* a, f32* b);

void func_001AC638(T217D_330* self, const char* p)
{
    Loc_1AC638 loc;

    if (p != 0 && GetStringLength(p)) {
        CopyString(self->text, p);
    } else {
        self->text[0] = 0;
    }
    f32 v = self->scale;
    PushFontScale(self->font, v, v);
    InitTextReader(&loc, &self->text[0], self->font);
    f32 zero = 0.0f;
    MeasureText(&loc, zero, &loc.x, &loc.y);
    f32 x = loc.x;
    SetScreenElementSize(self, x, (self->text[0] != 0) ? loc.y : 0.0f);
    PopFontScale(self->font);
}

void func_001ACA30(T217D_380* self)
{
    if (self->mode != 3 || self->pending == 0) {
        ShowScreenElement(self);
    }
}

void func_001AD3B0(T217D_3D0* self)
{
    if (self->mode == 3 && self->pending != 0) {
        self->pending = 0;
    } else {
        HideScreenElement(self);
    }
}

void func_001ADFF0(T217D_4C0* self);

void func_001AE130(T217D_4C0* self, s32 force)
{
    if (self->pending != 0 && force == 0) {
        self->pending = 0;
        RebuildPromptText(self);
        force = 1;
    }
    SetScreenElementMode(self, force);
}

struct Node_129CA8 {
    u8 pad0[0x18];
    union {
        s32 w;
        f32 f;
    } f18;
};

struct Sink_001AEFA0 { u8 pad0[0x18]; f32 value; };


extern u8 D_002743D0[];

void func_001AC5C0(T217D_330* self)
{
    const V24A2_Vt* vt;

    SetupScreenElementText(self);
    vt = self->font->vt;
    self->font = vt->clone((V24A2*)((u8*)self->font + vt->adj1), 1.25f, 1.25f);
    if (IsFontLoaded(2)) {
        self->frame = (V24A2**)D_002743D0;
        *self->frame = GetFontById(2);
    }
}


extern u8 D_002743F0[];

void func_001AC888(T217D_380* self)
{
    const V24A2_Vt* vt;

    SetupScreenElementText(self);
    vt = self->font->vt;
    self->font = vt->clone((V24A2*)((u8*)self->font + vt->adj1), 0.9f, 0.9f);
    self->color = 0xDF7F7F7Fu;
    if (IsFontLoaded(2)) {
        self->frame = (V24A2**)D_002743F0;
        *self->frame = GetFontById(2);
    }
}

void func_001AECB0(void* self);

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 n, void* table);

s32 func_001F6738(const char* a, const char* b);

void func_001AC910(T217D_380* self, const char* v)
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
    if (func_001F6738(self->text, v) != 0) {
        self->pendingText = v;
        self->pending = 1;
        self->vt->m16(self, 3);
    }
done:
    return;
}

void func_001AC990(T217D_380* self, s32 v)
{
    if (self->pending != 0 && v == 0) {
        const char* x = self->pendingText;
        self->pending = 0;
        SetScreenElementText(self, x);
        v = 1;
    }
    SetScreenElementMode(self, v);
}

void func_001AD320(T217D_3D0* self, s32 flag)
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

void func_001AD378(T217D_3D0* self)
{
    if (self->mode == 3 && self->pending != 0) return;
    ShowScreenElement(self);
}

struct Mgr_001AD718 { u8 pad0[4]; s32 f4; u8 pad1[0x2C - 8]; s32 f2C; };

extern u8 D_00275BC0[];

void func_001AD718(T217D_420* self)
{
    Player* g;
    Mgr_001AD718* m;

    UpdateScreenElementSlide(self);
    if (self->flag == 0) goto tail;
    g = g_player;
    if (g != 0 && g->f2220 == 6) goto tail;
    m = (Mgr_001AD718*)g_elementStack;
    if (m->f4 == 3 && m->f2C < 2) {
        self->vt->m14(self);
        return;
    }
tail:
    self->vt->m15(self);
}

void func_001AD940(T217D_560* self)
{
    SetupScreenElementText(self);
    self->outTime = 0.5f;
}

void func_001ACA68(T217D_380* self)
{
    if (self->mode == 3 && self->pending != 0) {
        self->pending = 0;
    } else {
        HideScreenElement(self);
    }
}

void func_001ACE38(T217D_3D0* self, const char* v)
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
        if (func_001F6738(self->text, v) == 0) {
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

void func_001AE7F8(T217D_600* self, s32 flag)
{
    if (flag == 0) {
        self->flag = 0;
    }
    SetScreenElementMode(self, flag);
}

s32 func_001833F0(void* key, s32 item);
s32 func_001300E8(void* key, s32 item);


extern u8 D_00274410[];

void func_001ACDA0(T217D_3D0* self)
{
    V24A2* o;
    const V24A2_Vt* vt;

    SetupScreenElementText(self);
    o = GetFontById(0);
    vt = o->vt;
    self->font = vt->clone((V24A2*)((u8*)o + vt->adj1), 1.0f, 1.0f);
    self->scale = 0.8f;
    self->outTime = 0.5f;
    if (IsFontLoaded(2)) {
        self->frame = (V24A2**)D_00274410;
        *self->frame = GetFontById(2);
    }
}

extern f32 D_00261858[];
extern s32 D_002744D0;

extern s32 D_002744D0;
void func_0015FCD8(void* self, void* p);
void func_00152470(void* list, void* item);
void func_00152600(void* list, void* item);

// NEAR: register and load order of D_00262C84 vs D_00269988 (retail keeps the x load in v1, ours in a0; xori placed differently)

struct Node_001AE178 { u8 pad0[0xC]; f32 f0C; };
extern s32 D_00275BF0;
extern s32 D_00262C84;
extern Node_001AE178* D_00269988;

void func_001AE178(T217D_4C0* self)
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

// NEAR: the store of func_0015C1C0 result is before the float load and call; retail puts it in the delay slot of the func_001AA788 call

struct Flags_1AE758 { u8 a; u8 b; };
extern f32 D_002744AC;

// The letter func_001AEA08 picks: PAL reads the table's bytes unsigned (docs/VERSIONS.md).
#ifdef VERSION_EU
typedef u8 Letter_1AEA08;
#else
typedef s8 Letter_1AEA08;
#endif
Letter_1AEA08 func_001AEA08(void);
void func_001AE758(T217D_600* self)
{
    f32 k = 0.25f;
    Flags_1AE758 fl;
    s32 v;

    SetupScreenElementText(self);
    SetScreenElementSlideInTime(self, k);
    SetScreenElementSlideOutTime(self, k);
    SetScreenElementHoldTime(self, 0.0f);
    V24A2* r = GetFontById(1);
    f32 g = D_002744AC;
    self->font = r;
    SetScreenElementScale(self, g);
    v = GetCyclingGlyph();
    fl.b = 0;
    fl.a = v;
    self->vt->m08(self, (const char*)&fl);
    self->text[0] = 0;
}

struct Flt_1ADF28 { u8 pad[0xC]; f32 v; };

f32 D_0027446C = 0.7f;
struct Pair_274470 { f32 a; f32 b; };
extern Pair_274470 D_00274470;
extern u8 D_00274488[];
extern s32 D_00262C84;

void func_001ADF28(T217D_4C0* self)
{
    const V24A2_Vt* vt;

    SetupScreenElementText(self);
    vt = self->font->vt;
    self->font = vt->clone((V24A2*)((u8*)self->font + vt->adj1), D_0027446C, D_00274470.a);
    if (GetFontById(2)) {
        self->frame = (V24A2**)D_00274488;
        *self->frame = GetFontById(2);
    }
    s32 a1 = 0;
    self->flagB = 0; *(s32*)&self->flagA = (D_00262C84 == 3);
    if (D_00269988 != 0) {
        if (((Flt_1ADF28*)(void*)D_00269988)->v != 0.0f) {
            a1 = 1;
        }
    }
    self->flagB = a1;
    RebuildPromptText(self);
}

s32 func_001833F0(s32 value, s32 item);
s32 func_001300E8(s32 value, s32 item);

s32 func_001833F0(void* a, s32 b);

typedef void (*VFn_1AF3B8)(void* self);

struct Child_1AF3B8 { VFn_1AF3B8* vtbl; };

struct Entry_1AF3B8 { void* obj; s32 value; };

struct Group_1AF3B8 {
    Child_1AF3B8* child;
    u8 pad0[0x24 - 4];
    s32 count;
    Entry_1AF3B8 items[5];
};

void func_00124A48(void* self);
void* func_00183058(void* a, void* b, void* c);

extern f32 D_00261868;
extern f32 D_0027240C;
extern s32 D_00272420;
extern u8 D_00269990[];

s32 func_0018B770(void* p);
void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, s32* value);
void func_00137260(void* out, s32 flag);
void func_00137268(void* out, s32 flag);
void* func_00160B28(void* p);
s32 func_001E1FD0(char* dst, const char* fmt, ...);

void func_001AE820(T217D_600* self)
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
    func_00137228(out, self->x, self->y + adj);
    func_00137238(out, px, py);
    tmp[0] = held;
    func_00137248(out, tmp);
    func_00137260(out, 0);
    func_00137268(out, 0);
    fmt = "%c&1^07~b2a83d%d%%&.";
    sp = str;
    c = GetCyclingGlyph();
    FormatToString(sp, fmt, c, ComputeCompletionPercent(g_saveData));
    PushFontScale(self->font, self->scale, self->scale);
    InitTextReader(buf, sp, self->font);
    DrawAlignedText(buf, out, 0, &g_gsPacketWriter);
    PopFontScale(self->font);
}

s32 func_001AC9E0(T217D_380* self, ScreenElement* other)
{
    s32 r = 0;
    if (AreScreenElementsTogether(self, other) != 0 || self->pending != 0) {
        r = 1;
    }
    return r;
}

s32 func_001AEE50(void* self, void* key);
s32 func_00160D10();

extern f32 D_0026185C[];

void func_001AC060(T217D_2E0* self)
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
    self->changedAt = g_gameTime[0];
}

extern const char D_0024CE00[];
void func_001AD0D0(ScreenElement* self, s32 hi, s32 lo);

void func_001AD088(ScreenElement* self, s32 value)
{
    if (value != -1) {
        SetElementTextFromEntry(self, value >> 8, (u8)value);
    } else {
        self->vt->m08(self, D_0024CE00);
    }
}


extern const char D_0024CEE0[];

void func_001AD6A8(T217D_420* self)
{
    V24A2* o;
    const V24A2_Vt* vt;

    SetupScreenElementText(self);
    o = GetFontById(2);
    vt = o->vt;
    self->font = vt->clone((V24A2*)((u8*)o + vt->adj1), 1.0f, 1.0f);
    self->vt->m08(self, D_0024CEE0);
    self->flag = 0;
}


f32 D_00274448 = 0.9f;
f32 D_0027444C = 0.9f;
extern u8 D_00274450[];
extern const char D_0024CEF0[];

void* func_001B4688(s32 key);

void func_001ADC60(T217D_470* self)
{
    SetupScreenElementText(self);
    V24A2* in = self->font;
    self->font = in->vt->clone((V24A2*)((u8*)in + in->vt->adj1), D_00274448, D_0027444C);
    if (GetFontById(2) != 0) {
        self->frame = (V24A2**)D_00274450;
        *self->frame = GetFontById(2);
    }
    self->icon = FindAnimRecord(0x493);
    if (self->icon != 0) {
        SetScreenElementSize(self, 366.75f, 165.75f);
    } else {
        self->vt->m08(self, D_0024CEF0);
    }
}

extern const char D_0024CF98[];
extern f32 D_002744A8;

s32 func_001E1FD0(char* dst, const char* fmt, ...);

void func_001AE510(T217D_5B0* self)
{
    SetupScreenElementText(self);
    self->font = GetFontById(2);
    if (self == &D_00273C50) {
        FormatToString(self->text, D_0024CF98, 0x4C);
    } else if (self == &D_002739F0) {
        FormatToString(self->text, D_0024CF98, 0x4B);
    }
    PushFontScale(self->font, D_002744A8, D_002744A8);
    self->w = MeasureFontString(self->font, self->text);
    V24A2* in = self->font;
    self->h = (f32)in->height * in->sy;
    PopFontScale(self->font);
}

struct Mixer_001AF5C8;
struct MixVt_001AF5C8 {
    u8 pad0[0x130];
    void (*hook)(Mixer_001AF5C8*, s32*);
    u8 pad1[0x144 - 0x134];
    void (*done)(Mixer_001AF5C8*, s32);
};
struct Mixer_001AF5C8 {
    MixVt_001AF5C8* vt;
    u8 pad4[0x554 - 4];
    s32 f554;
    s32 state;
    f32 f55C;
    u8 pad560[0x5B8 - 0x560];
    f32 f5B8;
    f32 f5BC;
    u8 pad5C0[0xAEC - 0x5C0];
    f32 fAEC;
    u8 padAF0[0xB04 - 0xAF0];
    f32 fB04;
    f32 fB08;
};

extern s32 D_002744D0;
extern f32 D_0026185C[];
void func_001AEFA0(Mixer_001AF5C8* self, f32 a);
void func_001AF508();

struct Info_1ACEE0 {
    u32 flags;
    u32 pad;
    f32 time;
};

extern s32 func_001E1FD0(char*, const char*, ...);
extern s32 func_001E2180(char*, const char*);
extern const char D_0024CD88[];
extern const char D_0024CD90[];
extern const char D_0024CD98[];
extern const char D_0024CDA0[];
extern const char D_0024CDA8[];
extern const char D_0024CDB0[];
extern const char D_0024CDB8[];
extern const char D_0024CDC0[];
extern const char D_0024CDC8[];
extern const char D_0024CDE0[];
extern const char D_0024CDF8[];

void func_001ACEE0(char* buf, Info_1ACEE0* info, u32 mask)
{
    u32 flags = info->flags;
    *buf = 0;
    if (mask & 2) {
        buf += FormatToString(buf, D_0024CD88, (flags & 2) ? D_0024CD90 : D_0024CD98);
    }
    if (mask & 4) {
        if (mask & 2) {
            *buf++ = ' ';
        }
        buf += FormatToString(buf, D_0024CD88, (flags & 4) ? D_0024CDA0 : D_0024CDA8);
    }
    if (mask & 8) {
        u32 f8;
        if (mask & 6) {
            *buf++ = ' ';
        }
        f8 = flags & 8;
        buf += FormatToString(buf, D_0024CDB0, f8 ? D_0024CDB8 : D_0024CDC0);
        if (f8) {
            f32 t = info->time;
            if (t < 1.0f) {
                (void)FormatToString(buf, D_0024CDC8, (s32)(t * 10.0f));
            } else {
                s32 s = (s32)t;
                s32 m = s / 60;
                s32 r = s % 60;
                (void)FormatToString(buf, D_0024CDE0, m, r);
            }
        }
        AppendString(buf, D_0024CDF8);
    }
}

struct Buf_1AD0D0 { s32 w[16]; };
struct Str_1AD0D0 { s32 w[16]; };
struct Idx_1AD0D0;

extern const char D_0024CE10[];
extern const char D_0024CE18[];
extern u8 D_0024CD68[];

u32 func_001601D8(Idx_1AD0D0* idx);
void* func_00160148(Idx_1AD0D0* idx);
void func_001ACEE0(Buf_1AD0D0* buf, void* p, u32 n);
s32 func_001E2100(Buf_1AD0D0* buf);
void* func_001E2138(Str_1AD0D0* dst, void* src);
s32 func_001E1FD0(Str_1AD0D0* dst, const char* fmt, ...);

void func_001AD0D0(ScreenElement* self, s32 a1, s32 a2)
{
    Buf_1AD0D0 buf;
    Str_1AD0D0 str;
    u8* p;
    u32 packed;

    p = *(u8**)((u8*)&g_saveData);
    p += a1 * 0x44C + 0x10;
    p += a2 * 0x78;
    packed = (a1 << 8) | a2;
    FormatFlagGlyphs(&buf, p, GetEntryFlags((Idx_1AD0D0*)packed));
    if (GetStringLength(&buf)) {
        FormatToString(&str, (const char*)D_0024CE10, GetEntryName((Idx_1AD0D0*)packed),
                      GetStringLength(&buf) ? (const char*)D_0024CE18 : (const char*)D_0024CD68, &buf);
    } else {
        CopyString(&str, GetEntryName((Idx_1AD0D0*)packed));
    }
    self->vt->m08(self, (const char*)&str);
}

struct Buf_001AD7B0 { u8 pad[0x30]; };

extern f32 D_00261868;
extern const char D_0024CEE8[];

f32 func_001EA408(f32 a);
f32 func_00205210(f32 x);
void func_00137228(Buf_001AD7B0* out, f32 x, f32 y);
void func_00137238(Buf_001AD7B0* out, f32 x, f32 y);
void func_00137248(Buf_001AD7B0* out, s32* value);
void func_00137260(Buf_001AD7B0* out, s32 flag);
void func_00137268(Buf_001AD7B0* out, s32 flag);

void func_001AD7B0(T217D_420* self)
{
    Buf_001AD7B0 buf;
    s32 mask = (s32)0xFF808080;
    DrawScreenElementText(self);
    f32 half = 0.5f;
    f32 sc = func_00205210(WrapAngle(g_elapsedTime * 8.0f)) * half + half;
    V24A2* h = GetFontById(1);
    f32 s2 = sc * 0.1f + half;
    PushFontScale(h, s2, s2);
    f32 w = MeasureFontString(h, (void*)D_0024CEE8);
    f32 ht = (f32)h->height * h->sy;
    func_00137228(&buf, self->x + 2.0f + self->w * half - w * half,
                  self->y + 14.0f + self->h * half - ht * half);
    func_00137238(&buf, w, ht);
    *(s32*)((u8*)&buf + 0x20) = mask;
    func_00137248(&buf, (s32*)((u8*)&buf + 0x20));
    func_00137260(&buf, 0);
    func_00137268(&buf, 0);
    DrawFontString(h, (void*)D_0024CEE8, &buf, 0, &g_gsPacketWriter);
    PopFontScale(h);
}

extern const char D_0024CF90[];
extern const char* D_00274478[];
extern const char* D_00274484;

struct Loc_1ADFF0 { T217D_Rgba col; u8 pad[12]; u8 obj[0xB0]; };

s32 func_001E1FD0(char *dst, const char *fmt, ...);
void* func_001E2138(char *dst, const char *src);
f32 func_0015E1F0(void *obj);
f32 func_0015E1B0(void *obj, f32 a);

void func_001ADFF0(T217D_4C0 *self)
{
    struct Loc_1ADFF0 loc;
    f32 y;

    if (self->flagA != 0) {
        loc.col.c[0] = 0x6F;
        loc.col.c[1] = 0x6F;
        loc.col.c[2] = 0x6F;
        loc.col.c[3] = 0xFF;
        self->rgba = loc.col;
        u8 *tbl = (u8*)D_00274478;
        s32 off = self->flagB ? 4 : 0;
        FormatToString(self->text, (const char *)D_0024CF90, *(s32 *)(tbl + off), *(s32 *)(tbl + 8));
    } else {
        loc.col.c[0] = 0x6F;
        loc.col.c[1] = 0x1F;
        loc.col.c[2] = 0x1F;
        loc.col.c[3] = 0xFF;
        self->rgba = loc.col;
        CopyString(self->text, (const char *)D_00274484);
    }
    PushFontScale(self->font, self->scale, self->scale);
    InitTextReader(&loc.obj, self->text, self->font);
    {
        f32 x = func_0015E1F0(&loc.obj);
        y = MeasureTextHeight(&loc.obj, 0.0f);
        SetScreenElementSize(self, x, y);
    }
    PopFontScale(self->font);
}

struct Buf_1AD1E8;
struct Sub_1AD1E8 {
    u8 pad0[0x438];
    s32 f438;
    s32 f43C;
    s32 f440;
    u8 pad444[0x8];
};
struct Mgr_1AD1E8 {
    u8 pad0[0x10];
    Sub_1AD1E8 ents[1];
};

extern const char* D_00274430[];
extern const char D_0024CE80[];
extern const char D_0024CEA0[];
extern const char D_0024CEC0[];

void func_00160208(s32 key, s32* a1, s32* a2, s32* a3);
char* func_001E2138(Buf_1AD1E8* dst, const char* src);
s32 func_001E2100(void* p);
s32 func_001E1FD0(Buf_1AD1E8* dst, const char* fmt, ...);

void func_001AD1E8(ScreenElement* self, s32 idx)
{
    char buf[0x200];
    s32 a, b, c;
    CountCategoryFlags(idx, &a, &b, &c);
    Sub_1AD1E8* s1 = &(*(Mgr_1AD1E8**)&g_saveData)->ents[idx];
    CopyString((Buf_1AD1E8*)buf, D_00274430[idx]);
    char* d = buf + GetStringLength(buf);
    if (a)
        d += FormatToString((Buf_1AD1E8*)d, D_0024CE80, s1->f438, a);
    if (b)
        d += FormatToString((Buf_1AD1E8*)d, D_0024CEA0, a ? ((char*)&D_0024CE18) : ((char*)&D_0024CD68), s1->f43C, b);
    if (c)
        FormatToString((Buf_1AD1E8*)d, D_0024CEC0, (a || b) ? ((char*)&D_0024CE18) : ((char*)&D_0024CD68), s1->f440, c);
    self->vt->m08(self, buf);
}

struct Table_001AEA08 {
    s32 pad_00;
};

extern f32 D_00261868;
struct Ptr_2744B0 { s8* p; s32 pad; };
extern Ptr_2744B0 D_002744B0;
extern const char D_0024CFA0[];

u32 func_001E2100(Table_001AEA08* t);

Letter_1AEA08 func_001AEA08(void)
{
    s32 scaled = (s32)(g_elapsedTime * 5.0f);
    u32 divisor = GetStringLength((Table_001AEA08*)D_002744B0.p);
    return D_002744B0.p[(u32)scaled % divisor];
}

struct Sub_1AECE8;
void func_00123AB0(Sub_1AECE8* object, s32 mode);
extern f32 D_0026185C[];

struct Ctx_1ADB00;

void func_001613C0(Ctx_1ADB00* p, s32 a, s32 b, u64 c);
void func_00161708(Ctx_1ADB00* p, u64 a, u64 b);
void func_00161458(Ctx_1ADB00* p, u32 value);
void func_001615F0(Ctx_1ADB00* p, s32 a1, s32 a2, s32 a3, s32 a4);

void func_001ADB00(T217D_560* self)
{
    f32 x = self->blend * 66.40001f;
    f32 y = 492.80002f - x;
    BeginGifTag((Ctx_1ADB00*)&g_gsPacketWriter, 6, 7, 0x044441EE);
    AddGifRegisterWrite((Ctx_1ADB00*)&g_gsPacketWriter, 0x47, 0x30000);
    AddGifRegisterWrite((Ctx_1ADB00*)&g_gsPacketWriter, 0x42, 0x44);
    AddGifRgbaEntry((Ctx_1ADB00*)&g_gsPacketWriter, 0x80000000);
    AddGifXyzfEntry((Ctx_1ADB00*)&g_gsPacketWriter, 0x6C00, 0x7900, 0x0FFFFFF0, 0);
    AddGifXyzfEntry((Ctx_1ADB00*)&g_gsPacketWriter, 0x9400, (s32)((x * 0.45454547f + 1936.0f) * 16.0f), 0x0FFFFFF0, 0);
    AddGifXyzfEntry((Ctx_1ADB00*)&g_gsPacketWriter, 0x6C00, (s32)((y * 0.45454547f + 1936.0f) * 16.0f), 0x0FFFFFF0, 0);
    AddGifXyzfEntry((Ctx_1ADB00*)&g_gsPacketWriter, 0x9400, 0x8700, 0x0FFFFFF0, 0);
}

struct Ctx_1AE3B8;

void func_001613C0(Ctx_1AE3B8* p, s32 a, s32 b, u64 c);
void func_00161708(Ctx_1AE3B8* p, u64 a, u64 b);
void func_00161458(Ctx_1AE3B8* p, u32 value);
void func_001615F0(Ctx_1AE3B8* p, s32 a1, s32 a2, s32 a3, s32 a4);
void func_00161278(Ctx_1AE3B8* p, s32 a);

void func_001AE3B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, u8* rgba, s32 flag)
{
    BeginGifTag((Ctx_1AE3B8*)&g_gsPacketWriter, rgba[3] < 0xFF ? 0x41 : 1, 4, 0x441E);

    AddGifRegisterWrite((Ctx_1AE3B8*)&g_gsPacketWriter, 0x47, (u64)(flag ? 0x11001 : 0x11000) | (flag ? 0x60000 : 0x20000));

    AddGifRgbaEntry((Ctx_1AE3B8*)&g_gsPacketWriter, ((u32)((rgba[3] + 1) & 0x1FE) << 23) | (rgba[2] << 16) | (rgba[1] << 8) | rgba[0]);
    AddGifXyzfEntry((Ctx_1AE3B8*)&g_gsPacketWriter, a0, a1, a2, 0);
    AddGifXyzfEntry((Ctx_1AE3B8*)&g_gsPacketWriter, a3, a4, a5, 0);
    CloseGifTag((Ctx_1AE3B8*)&g_gsPacketWriter, 0);
}

extern u8 D_00275B00[];

void func_001AD970(T217D_560* self, s32 newval)
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

typedef void (*VFn_1AC700)(void* self, void* handle, void* out, void* tbl);
struct VTab_1AC700 { u8 pad0[0x48]; s16 adj; u8 pad1[0x4C - 0x4A]; VFn_1AC700 fn; };
void func_00137228(Layout_137228* out, f32 x, f32 y);
void func_00137238(Layout_137228* out, f32 x, f32 y);
void func_00137248(Layout_137228* out, s32* value);
void func_00137260(Layout_137228* out, s32 flag);
void func_00137268(Layout_137228* out, s32 flag);
struct Out_1AC700 : Layout_137228 {
    void Pos(f32 x, f32 y) { func_00137228(this, x, y); }
    void Size(f32 x, f32 y) { func_00137238(this, x, y); }
    void Color(s32* c) { func_00137248(this, c); }
    void FlagA(s32 f) { func_00137260(this, f); }
    void FlagB(s32 f) { func_00137268(this, f); }
};
struct Hd_1AC700 {
    static void Draw(void* h, Out_1AC700* out, void* tbl)
    {
        if (*(void**)h != 0) {
            VTab_1AC700* vt = *(VTab_1AC700**)((u8*)*(void**)h + 0x4C);
            vt->fn((u8*)*(void**)h + vt->adj, h, out, tbl);
        }
    }
};

void func_001AC700(T217D_330* self)
{
    T217D_Word tmp;
    Out_1AC700 out;
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
            Hd_1AC700::Draw(self->frame, &out, &g_gsPacketWriter);
            *(T217D_Word*)((u8*)self->frame + 0x18) = slot;
        }
        PushFontScale(self->font, self->scale, self->scale);
        InitTextReader(loc, &self->text[0], self->font);
        DrawAlignedText(loc, &out, 0, &g_gsPacketWriter);
        PopFontScale(self->font);
    }
}

struct Ctx_1ADD28;

struct Pair_1ADD28 {
    u16 a;
    u16 b;
};

struct Hold_1ADD28 {
    u8 pad0[0x14];
    TextureTable* p14;
};


void func_001613C0(Ctx_1ADD28* p, s32 a, s32 b, u64 c);
void func_00161708(Ctx_1ADD28* p, u64 a, u64 b);
void func_00161458(Ctx_1ADD28* p, u32 rgba);
void func_001614C8(Ctx_1ADD28* p, s32 a, s32 b);
void func_001615F0(Ctx_1ADD28* p, s32 a, s32 b, s32 c, s32 d);
u64 func_001B2988(TextureTable* t, s32 i, s32 j);

void func_001ADD28(T217D_470* self)
{
    if (self->icon != 0) {
        TextureTable* sub = ((Hold_1ADD28*)self->icon)->p14;
        Pair_1ADD28* pr = (Pair_1ADD28*)*sub->p0c;
        u64 v = GetTextureRegisterBits(sub, 0, 0);
        u8 rgba[4];
        BeginGifTag((Ctx_1ADD28*)&g_gsPacketWriter, 0x156, 0xA, 0x43431EEEEEULL);
        AddGifRegisterWrite((Ctx_1ADD28*)&g_gsPacketWriter, 0x47, 0x33001);
        AddGifRegisterWrite((Ctx_1ADD28*)&g_gsPacketWriter, 0x42, 0x44);
        AddGifRegisterWrite((Ctx_1ADD28*)&g_gsPacketWriter, 6, v);
        AddGifRegisterWrite((Ctx_1ADD28*)&g_gsPacketWriter, 0x14, 0x60);
        AddGifRegisterWrite((Ctx_1ADD28*)&g_gsPacketWriter, 8, 5);
        *(u32*)rgba = 0x80808080;
        AddGifRgbaEntry((Ctx_1ADD28*)&g_gsPacketWriter, *(u32*)rgba);
        AddGifUvEntry((Ctx_1ADD28*)&g_gsPacketWriter, 0, pr->b << 4);
        AddGifXyzfEntry((Ctx_1ADD28*)&g_gsPacketWriter, (s32)((self->x + 1728.0f) * 16.0f), (s32)((self->y * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        AddGifUvEntry((Ctx_1ADD28*)&g_gsPacketWriter, pr->a << 4, 0);
        AddGifXyzfEntry((Ctx_1ADD28*)&g_gsPacketWriter, (s32)((self->x + self->w + 1728.0f) * 16.0f), (s32)(((self->y + self->h) * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    } else {
        DrawScreenElementText(self);
    }
}


struct Buf_1AD3F0 { u8 d[0xB0]; };

struct Inner_1AD3F0 {
    u8 pad[0x2D0];
    s32 f2D0;
};

void func_00137228(Layout_137228* out, f32 x, f32 y);
void func_00137238(Layout_137228* out, f32 x, f32 y);
void func_00137248(Layout_137228* out, s32* value);
void func_00137260(Layout_137228* out, s32 flag);
void func_00137268(Layout_137228* out, s32 flag);
struct Out_1AD3F0 : Layout_137228 {
    void Pos(f32 x, f32 y) { func_00137228(this, x, y); }
    void Size(f32 x, f32 y) { func_00137238(this, x, y); }
    void Color(s32* c) { func_00137248(this, c); }
    void FlagA(s32 f) { func_00137260(this, f); }
    void FlagB(s32 f) { func_00137268(this, f); }
};
void func_001613C0(V24A0* f, s32 a, s32 b, u64 c);
void func_00161708(V24A0* f, u64 a, u64 b);
void func_00161458(V24A0* f, u32 v);
void func_001615F0(V24A0* f, s32 a, s32 b, s32 c, s32 d);

void func_001AD3F0(T217D_3D0* self)
{
    T217D_Word packed;
    Out_1AD3F0 out;
    T217D_Word slot;
    Buf_1AD3F0 buf;
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
        V24A0* s = &g_gsPacketWriter;
        f32 sc = scale;
        f32 y;
        if (g2->open != 0 && g2->current != 0 && ((Inner_1AD3F0*)g2->current)->f2D0 == 2) {
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


void func_00137228(Layout_137228* out, f32 x, f32 y);
void func_00137238(Layout_137228* out, f32 x, f32 y);
void func_00137248(Layout_137228* out, s32* value);
void func_00137260(Layout_137228* out, s32 flag);
void func_00137268(Layout_137228* out, s32 flag);
struct Out_1ACAA8 : Layout_137228 {
    void Pos(f32 x, f32 y) { func_00137228(this, x, y); }
    void Size(f32 x, f32 y) { func_00137238(this, x, y); }
    void Color(s32 c) { func_00137248(this, &c); }
    void FlagA(s32 f) { func_00137260(this, f); }
    void FlagB(s32 f) { func_00137268(this, f); }
};

struct Font_1ACAA8 {
    static f32 Advance(V24A2* f, s32 ch) { return f->vt->width((V24A2*)((u8*)f + f->vt->adj3), ch); }
    static void Begin(V24A2* f, s32 a, void* d) { f->vt->begin((V24A2*)((u8*)f + f->vt->adj4), a, (s32)d); }
    static void Glyph(V24A2* f, s32 ch, s32 color, void* d, f32 x, f32 y) { f->vt->draw(x, y, (V24A2*)((u8*)f + f->vt->adj6), ch, color, (s32)d); }
    static void End(V24A2* f, s32 a, void* d) { f->vt->end((V24A2*)((u8*)f + f->vt->adj7), a, (s32)d); }
};

struct Clamp_1ACAA8 {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        return x < lo ? lo : (hi < x ? hi : x);
    }
};

void func_001ACAA8(T217D_380* self)
{
    Out_1ACAA8 out;
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
    c = Clamp_1ACAA8::Of(self->blend / (1.0f / (f32)n), 0.0f, 1.0f);
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
        V24A2* o = *self->frame;
        if (o != 0) {
            o->vt->drawBox((V24A2*)((u8*)o + o->vt->adj9), self->frame, &out, &g_gsPacketWriter);
        }
    }
    Font_1ACAA8::Begin(self->font, 0, &g_gsPacketWriter);
    for (i = 0; i < n; i++) {
        s32 ch = self->text[i];
        f32 d;
        c = Clamp_1ACAA8::Of(self->blend / ((f32)(i + 1) / (f32)n), 0.0f, 1.0f);
        rest = 1.0f - c;
        Font_1ACAA8::Glyph(self->font, ch, self->color, &g_gsPacketWriter, c * x + rest * y, self->shownY);
        d = Font_1ACAA8::Advance(self->font, ch);
        x += d;
        y += d;
    }
    Font_1ACAA8::End(self->font, 0, &g_gsPacketWriter);
}

struct Rgba_1AC0E8 { u8 c[4]; };
struct VEnt_1AC0E8 { s16 delta; s16 index; void (*fn)(void* self, f32 x, f32 y, s32 a, s32 b, void* c); };
struct Text_1AC0E8 { u8 pad[0x4C]; VEnt_1AC0E8* vtbl; };
struct Q3_1AC0E8 { f32 f0; f32 f4; f32 f8; f32 fC; };

extern f32 D_00261858[];
extern Q3_1AC0E8 D_002743C0;

f32 func_001EA4B8(Q3_1AC0E8* p, s32 a1, f32 f12, f32 f13, f32 f14);
void func_00137228(Layout_137228* out, f32 x, f32 y);
void func_00137238(Layout_137228* out, f32 x, f32 y);
void func_00137248(Layout_137228* out, Quad4* value);
void func_00137260(Layout_137228* out, s32 flag);
void func_00137268(Layout_137228* out, s32 flag);
void func_0019DDA0(f32 x0, f32 y0, f32 x1, f32 y1, s32 r, s32 g, s32 b, s32 a, V24A0* d);
f32 func_00205400(f32 x);
f32 func_00205210(f32 x);

struct Lerp_1AC0E8 {
    static u8 Of(s32 a, s32 b, f32 t)
    {
        if (a == b) return b;
        if (a < b) return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
        return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
    }
};

struct LerpRgba_1AC0E8 {
    static void Do(Rgba_1AC0E8* out, Rgba_1AC0E8* a, Rgba_1AC0E8* b, f32 t)
    {
        Rgba_1AC0E8 r;
        r.c[0] = Lerp_1AC0E8::Of(a->c[0], b->c[0], t);
        r.c[1] = Lerp_1AC0E8::Of(a->c[1], b->c[1], t);
        r.c[2] = Lerp_1AC0E8::Of(a->c[2], b->c[2], t);
        r.c[3] = Lerp_1AC0E8::Of(a->c[3], b->c[3], t);
        *out = r;
    }
};

void func_001AC0E8(T217D_2E0* self)
{
    Layout_137228 out;
    f32 t = 0.0f;
    s32 flag = 0;
    if (self->changedAt != t) {
        f32 d = g_gameClock[1] - self->changedAt;
        if (d < 0.5f) t = 1.0f - (d + d);
        flag = d < 0.75f;
    }
    u32 grey = 0xFF808080;
    self->fill = ApproachValueWithRamp(&D_002743C0, 0, self->fill, self->fillTarget, g_gameClock[2]);
    f32 y = self->barH;
    f32 h = self->fill * y;
    y -= h;
    f32 w = self->barW;
    func_00137228(&out, self->x + self->barX, self->y + self->barY);
    func_00137238(&out, w, y);
    {
        Quad4 tmp;
        tmp.w[0] = grey;
        func_00137248(&out, &tmp);
    }
    func_00137260(&out, 0);
    func_00137268(&out, 0);
    {
    Rgba_1AC0E8 col;
    col.c[0] = 0x20; col.c[1] = 0x20; col.c[2] = 0x20; col.c[3] = 0xC0;
    WriteColoredSpritePacket(out.x, out.y, out.x + out.w, out.y + out.h, 0x20, 0x20, 0x20, 0xC0, &g_gsPacketWriter);
    {
        out.x = self->x + self->barX;
        out.y = self->y + self->barY + y;
        out.w = self->barW;
        out.h = h;
        Rgba_1AC0E8 a, b;
        a.c[0] = 0x60; a.c[1] = 0; a.c[2] = 0; a.c[3] = 0xC0;
        b.c[0] = 0xC0; b.c[1] = 0xC0; b.c[2] = 0xC0; b.c[3] = 0xFF;
        LerpRgba_1AC0E8::Do(&col, &a, &b, t);
    }
    WriteColoredSpritePacket(out.x, out.y, out.x + out.w, out.y + out.h, col.c[0], col.c[1], col.c[2], col.c[3], &g_gsPacketWriter);
    }
    PushFontScale(self->font, self->scale, self->scale);
    Text_1AC0E8* text = (Text_1AC0E8*)self->font;
    VEnt_1AC0E8* ve = &text->vtbl[8];
    ve->fn((u8*)self->font + ve->delta, self->x, self->y, 0x7A, out.color.value, &g_gsPacketWriter);
    f32 dx = 0.0f;
    f32 dy = dx;
    if (flag) {
        dx = func_00205400(g_gameClock[4] * 40.0f) * 8.0f;
        dy = func_00205210(g_gameClock[4] * 15.0f) * 4.0f;
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

// Data defined here (retail .rodata / .data).
extern const char D_0024CD88[8] = "&3%s&.";
extern const char D_0024CD90[8] = "k";
extern const char D_0024CD98[8] = "l";
extern const char D_0024CDA0[8] = "v";
extern const char D_0024CDA8[8] = "w";
extern const char D_0024CDB0[8] = "&1%s";
extern const char D_0024CDB8[8] = "h";
extern const char D_0024CDC0[8] = "i";
extern const char D_0024CDC8[24] = "^10~b2a83d0.%d~.^.";
extern const char D_0024CDE0[24] = "^10~b2a83d%d:%02d~.^.";
extern const char D_0024CDF8[8] = "&.";
extern const char D_0024CE00[16] = "<unknown>";
extern const char D_0024CE10[8] = "%s%s%s";
extern const char D_0024CE18[104] = " \0\0\0\0\0\0\0Tide of Terror\0\0Sunset Snake Eyes\0\0\0\0\0\0\0Vicious Voodoo\0\0Fire in the Sky\0The Cold Heart of Hate";
extern const char D_0024CE80[32] = " &1%d^10~b2a83d/%d~.^.&.&3k&.";
extern const char D_0024CEA0[32] = "%s&1%d^10~b2a83d/%d~.^.&.&3v&.";
extern const char D_0024CEC0[32] = "%s&1%d^10~b2a83d/%d~.^.h&.";
extern const char D_0024CEE0[8] = "B";
extern const char D_0024CEE8[8] = "L";
extern const char D_0024CEF0[160] = "Sly Cooper\nand the Thievius Raccoonus\0\0\0Press START button for New Game\0Press START button to Resume Game\0\0\0\0\0\0\0Press SELECT button for Menu\0\0\0\0No Controller";
extern const char D_0024CF90[8] = "%s\n%s";
extern const char D_0024CF98[8] = "%c";
extern const char D_0024CFA0[32] = "%c&1^07~b2a83d%d%%&.\0\0\0\0ab";
const char* D_00274430[6] = { (const char*)D_0024CD68, D_0024CE18 + 0x08, D_0024CE18 + 0x18, D_0024CE18 + 0x30, D_0024CE18 + 0x40, D_0024CE18 + 0x50 };
Pair_274470 D_00274470 = { 0.6f, 0.0f };
const char* D_00274478[3] = { D_0024CEF0 + 0x28, D_0024CEF0 + 0x48, D_0024CEF0 + 0x70 };
const char* D_00274484 = D_0024CEF0 + 0x90;
f32 D_002744AC = 0.7f;
Ptr_2744B0 D_002744B0 = { (s8*)(D_0024CFA0 + 0x18), 0 };
Q3_1AC0E8 D_002743C0 = { 0.5f, 0.25f, 0.2f, 0.0f };
extern Node_001AE178* D_00269988;

void func_001AEA70(s32 a, s32 b);
// _GLOBAL_$I$ of the file, after the 16 bytes the linker left of two layout setters.
void func_001AEC90(void)
{
    func_001AEA70(1, 0xFFFF);
}
