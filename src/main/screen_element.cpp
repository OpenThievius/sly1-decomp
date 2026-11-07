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
#include "asm_func.h"

extern void* const D_002486B0[];

// A 28-byte text style the static initialiser (func_001AEA70) clears (func_001F5C0C with 0x1C)
// and then fills.
struct Obj_2743D0 {
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
Font* func_0015C1C0(s32 k);
void func_0015C8B8(Font* font, f32 x, f32 y);
f32 func_0015C418(Font* font, void* text);
void func_0015C638(Font* font, void* text, void* out, s32 zero, void* d);
void func_0015C900(Font* font);
void* func_0015DB28(void* out, void* text, Font* font);
void func_0015E318(void* buf, void* out, s32 zero, void* d);

void func_001F3C08(void* a, f32* out);
void func_00128150(int a, int b, void* c, f32* d);

extern f32 D_0026185C;
extern f32 D_00261860;

void func_001AB980(T217D_510* self, f32 value);

extern s32 D_0026227C;

typedef void (*VirtualCall_1AA790)(void* a, void* b, void* c, void* d);


void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, s32* value);
void func_00137260(void* out, s32 flag);
void func_00137268(void* out, s32 flag);

typedef void* (*VFn_1A9960)(void* self);

extern ElementPlaceTable D_0026C3E0;
s32 func_001300E8(void* node, s32 kind);

void func_001F5C0C(void* p, s32 value, s32 size);

struct Entry_1A8718 { s32 key; s32 pad[3]; s32 flags; };

Entry_1A8718* func_001A8718(ObjectPool* table, s32 key);

struct Entry_1A87E0 { s32 pad0; s32 f4; s32 pad1; s32 fC; };

Entry_1A87E0* func_001A8718(void* table, s32 key);
void func_001F3C08(void* self, void* arg);
void func_00128150(void* a0, void* a1, void* a2, void* a3);
void func_00152438(void* self, s32 value);


struct Local_001AB710 { f32 x; f32 y; u8 pad0[0x8]; T217D_Word w10; u8 pad1[0xC]; s32 tag; u8 pad2[0xC]; T217D_Word w30; };
void func_00137248(void* out, void* p);
void func_00137260(void* out, s32 v);
void func_00137268(void* out, s32 v);

extern u8 D_00262C68[];

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();

extern s8 D_00262250[];
extern u8 D_0024E879[];
s32 func_001E1FD0(char* dst, const char* fmt, ...);
void* func_001E2138(void* dst, void* src);
void func_00152438(void* p, s32 a);
PlacedObject* func_00183058(PlacedObject* a, World* b, BaseObject* c);

struct Tab_1A87A8;
struct Ent_1A87A8 { s32 pad[4]; s32 flags; };

Ent_1A87A8* func_001A8718(Tab_1A87A8* table, s32 key);

struct Obj_1A93E8;
void func_001F5C0C(Obj_1A93E8* p, s32 zero, s32 size);
void func_001AE820(u8* a);
extern f32 D_002743A0[4];

s32 func_001E20B8(char* dst, s32 cap, const char* fmt, ...);
extern s32 D_002751D4;

void func_001BFCD8(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

f32 func_001EAF28(f32 x);
void func_001AA790();
void func_001AA898();
void func_001AA8A0();
void func_001AA8A8();
void func_001AA8C8();
void func_001AA8F0();
void func_001AA958();
void func_001AAF58();
void func_001AAAC8();
void func_001AA4F0();
void func_001AA998();
void func_001AB058();
void func_001ABE70();
void func_001AC0E8();
void func_001AC888();
void func_001AC910();
void func_001AC990();
s32 func_001AC9E0();
void func_001ACA30();
void func_001ACA68();
void func_001ACAA8();
void func_001ACDA0();
void func_001ACE38();
void func_001AD320();
void func_001AD378();
void func_001AD3B0();
void func_001AD3F0();
void func_001AD6A8();
void func_001AD718();
void func_001AD7B0();
void func_001ADC60();
void func_001ADD28();
void func_001ADF28();
void func_001AE130();
void func_001AE178();
void func_001AE220();
void func_001AD940();
void func_001AD970();
void func_001ADB00();
void func_001AE510();
void func_001AE5E0();
void func_001AE758();
void func_001AE7F8();

s32 func_001E2100(const char*);
void* func_001E2138(char*, const char*);
void func_0015E290(TextReader*, f32, f32*, f32*);

void func_001AB2B8(T217D_E30* self);
f32 func_0015DFF8(TextReader* loc);


struct PoolCandidate { u8 pad0[0x678]; s32 f678; u8 pad1[4]; s32 f680; };
struct List_1A88A0 { u8* head; u8 pad4[4]; s32 offset; };
struct Iter_1A88A0 { List_1A88A0* list; u8* link; s32 offset; Iter_1A88A0* prev; };
s32 func_001300E8(PoolCandidate* p, s32 kind);
s32 func_0015C188(s32 k);

struct Loc_1AC638 {
    u8 data[0xB0];
    f32 x;
    f32 y;
};

s32 func_001E2100(const char* p);
void* func_001E2138(char* dst, const char* p);
void func_0015E290(void* out, f32 t, f32* a, f32* b);

void func_001ADFF0(T217D_4C0* self);


extern Obj_2743D0 D_002743D0;


extern Obj_2743D0 D_002743F0;

s32 func_001F6738(const char* a, const char* b);

struct Mgr_001AD718 { u8 pad0[4]; s32 f4; u8 pad1[0x2C - 8]; s32 f2C; };

extern u8 D_00275BC0[];

s32 func_001833F0(void* key, s32 item);
s32 func_001300E8(void* key, s32 item);


extern Obj_2743D0 D_00274410;

// NEAR: register and load order of D_00262C84 vs D_00269988 (retail keeps the x load in v1, ours in a0; xori placed differently)

struct Node_001AE178 { u8 pad0[0xC]; f32 f0C; };
extern s32 D_00275BF0;
extern s32 D_00262C84;
extern Node_001AE178* D_00269988;

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

struct Flt_1ADF28 { u8 pad[0xC]; f32 v; };
extern f32 D_0027446C;
struct Pair_274470 { f32 a; f32 b; };
extern Pair_274470 D_00274470;
extern Obj_2743D0 D_00274488;

s32 func_001833F0(s32 value, s32 item);
s32 func_001300E8(s32 value, s32 item);

s32 func_001833F0(void* a, s32 b);

typedef void (*VFn_1AF3B8)(void* self);
void* func_00183058(void* a, void* b, void* c);

extern f32 D_00261868;
extern f32 D_0027240C;
extern s32 D_00272420;
extern u8 D_00269990[];

s32 func_0018B770(void* p);
void* func_00160B28(void* p);


void func_001AD0D0(ScreenElement* self, s32 hi, s32 lo);


extern f32 D_00274448;
extern f32 D_0027444C;
extern Obj_2743D0 D_00274450;

void* func_001B4688(s32 key);

extern f32 D_002744A8;

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

struct Info_1ACEE0 {
    u32 flags;
    u32 pad;
    f32 time;
};

extern s32 func_001E1FD0(char*, const char*, ...);
extern s32 func_001E2180(char*, const char*);

struct Buf_1AD0D0 { s32 w[16]; };
struct Str_1AD0D0 { s32 w[16]; };
struct Idx_1AD0D0;


u32 func_001601D8(Idx_1AD0D0* idx);
void* func_00160148(Idx_1AD0D0* idx);
void func_001ACEE0(Buf_1AD0D0* buf, void* p, u32 n);
s32 func_001E2100(Buf_1AD0D0* buf);
void* func_001E2138(Str_1AD0D0* dst, void* src);
s32 func_001E1FD0(Str_1AD0D0* dst, const char* fmt, ...);

struct Buf_001AD7B0 { u8 pad[0x30]; };

f32 func_001EA408(f32 a);
f32 func_00205210(f32 x);
void func_00137228(Buf_001AD7B0* out, f32 x, f32 y);
void func_00137238(Buf_001AD7B0* out, f32 x, f32 y);
void func_00137248(Buf_001AD7B0* out, s32* value);
void func_00137260(Buf_001AD7B0* out, s32 flag);
void func_00137268(Buf_001AD7B0* out, s32 flag);

extern const char* D_00274478[];
extern const char* D_00274484;

struct Loc_1ADFF0 { T217D_Rgba col; u8 pad[12]; u8 obj[0xB0]; };

s32 func_001E1FD0(char *dst, const char *fmt, ...);
void* func_001E2138(char *dst, const char *src);
f32 func_0015E1F0(void *obj);
f32 func_0015E1B0(void *obj, f32 a);

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

void func_00160208(s32 key, s32* a1, s32* a2, s32* a3);
char* func_001E2138(Buf_1AD1E8* dst, const char* src);
s32 func_001E2100(void* p);
s32 func_001E1FD0(Buf_1AD1E8* dst, const char* fmt, ...);

struct Table_001AEA08 {
    s32 pad_00;
};
struct Ptr_2744B0 { s8* p; s32 pad; };
extern Ptr_2744B0 D_002744B0;

u32 func_001E2100(Table_001AEA08* t);

struct Ctx_1ADB00;

void func_001613C0(Ctx_1ADB00* p, s32 a, s32 b, u64 c);
void func_00161708(Ctx_1ADB00* p, u64 a, u64 b);
void func_00161458(Ctx_1ADB00* p, u32 value);
void func_001615F0(Ctx_1ADB00* p, s32 a1, s32 a2, s32 a3, s32 a4);

struct Ctx_1AE3B8;

void func_001613C0(Ctx_1AE3B8* p, s32 a, s32 b, u64 c);
void func_00161708(Ctx_1AE3B8* p, u64 a, u64 b);
void func_00161458(Ctx_1AE3B8* p, u32 value);
void func_001615F0(Ctx_1AE3B8* p, s32 a1, s32 a2, s32 a3, s32 a4);
void func_00161278(Ctx_1AE3B8* p, s32 a);

extern u8 D_00275B00[];

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


struct Buf_1AD3F0 { u8 d[0xB0]; };

struct Inner_1AD3F0 {
    u8 pad[0x2D0];
    s32 f2D0;
};
struct Out_1AD3F0 : Layout_137228 {
    void Pos(f32 x, f32 y) { func_00137228(this, x, y); }
    void Size(f32 x, f32 y) { func_00137238(this, x, y); }
    void Color(s32* c) { func_00137248(this, c); }
    void FlagA(s32 f) { func_00137260(this, f); }
    void FlagB(s32 f) { func_00137268(this, f); }
};
void func_001613C0(PacketWriter* f, s32 a, s32 b, u64 c);
void func_00161708(PacketWriter* f, u64 a, u64 b);
void func_00161458(PacketWriter* f, u32 v);
void func_001615F0(PacketWriter* f, s32 a, s32 b, s32 c, s32 d);
struct Out_1ACAA8 : Layout_137228 {
    void Pos(f32 x, f32 y) { func_00137228(this, x, y); }
    void Size(f32 x, f32 y) { func_00137238(this, x, y); }
    void Color(s32 c) { func_00137248(this, &c); }
    void FlagA(s32 f) { func_00137260(this, f); }
    void FlagB(s32 f) { func_00137268(this, f); }
};

struct Font_1ACAA8 {
    static f32 Advance(Font* f, s32 ch) { return f->vt->width((Font*)((u8*)f + f->vt->adj3), ch); }
    static void Begin(Font* f, s32 a, void* d) { f->vt->begin((Font*)((u8*)f + f->vt->adj4), a, (s32)d); }
    static void Glyph(Font* f, s32 ch, s32 color, void* d, f32 x, f32 y) { f->vt->draw(x, y, (Font*)((u8*)f + f->vt->adj6), ch, color, (s32)d); }
    static void End(Font* f, s32 a, void* d) { f->vt->end((Font*)((u8*)f + f->vt->adj7), a, (s32)d); }
};

struct Clamp_1ACAA8 {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        return x < lo ? lo : (hi < x ? hi : x);
    }
};

struct Rgba_1AC0E8 { u8 c[4]; };
struct VEnt_1AC0E8 { s16 delta; s16 index; void (*fn)(void* self, f32 x, f32 y, s32 a, s32 b, void* c); };
struct Text_1AC0E8 { u8 pad[0x4C]; VEnt_1AC0E8* vtbl; };
struct Q3_1AC0E8 { f32 f0; f32 f4; f32 f8; f32 fC; };
extern Q3_1AC0E8 D_002743C0;

f32 func_001EA4B8(Q3_1AC0E8* p, s32 a1, f32 f12, f32 f13, f32 f14);
void func_00137248(Layout_137228* out, Quad4* value);
void func_0019DDA0(f32 x0, f32 y0, f32 x1, f32 y1, s32 r, s32 g, s32 b, s32 a, PacketWriter* d);
f32 func_00205400(f32 x);

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

void func_001AEA70(s32 a, s32 b);

void func_001AA268(ScreenElement* self)
{
    s32 value = g_defaultFont;
    u32 flags = 0xFF808080;
    self->font = (Font*)value;
    self->scale = 1.0f;
    self->color = flags;
    self->text[0] = 0;
}

f32 D_002743A0[4] = { 0.0f, 2.0f, -1.0f, 0.0f };

void func_001AA298(ScreenElement* self) {
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

void func_001AA4F0(ScreenElement* self, const char* arg)
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

void func_001AA5A0(ScreenElement* self)
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

void func_001AA788(ScreenElement* self, f32 v)
{
    self->scale = v;
}

void func_001AA790(ScreenElement* self)
{
    u8 out[32];
    s32 tmp;
    void* handle;
    f32 x;

    if (self->text[0] != 0) {
        f32 p = self->w;
        f32 q = self->h;
        s32 held = self->color;
        func_00137228(out, self->x, self->y);
        func_00137238(out, p, q);
        tmp = held;
        func_00137248(out, &tmp);
        func_00137260(out, 0);
        func_00137268(out, 0);

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

f32 func_001AA898(ScreenElement* self)
{
    return self->inTime;
}

f32 func_001AA8A0(ScreenElement* self)
{
    return self->holdTime;
}

f32 func_001AA8A8(ScreenElement* self)
{
    return self->outTime;
}

void func_001AA8B0(ScreenElement* self, f32 v)
{
    self->inTime = v;
}

void func_001AA8B8(ScreenElement* self, f32 v)
{
    self->holdTime = v;
}

void func_001AA8C0(ScreenElement* self, f32 v)
{
    self->outTime = v;
}

void func_001AA8C8(ScreenElement* self)
{
    self->vt->m16(self, 0);
}

void func_001AA8F0(ScreenElement* self)
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

void func_001AA958(ScreenElement* self)
{
    s32 m = self->mode;
    if (m < 3) {
        if (m > 0) {
            self->vt->m16(self, 3);
        }
    }
}

void func_001AA998(ScreenElement* self, s32 mode)
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

s32 func_001AAAC8(ScreenElement* a, ScreenElement* b)
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

void func_001AAB20(ScreenElement *self, f32 x, f32 y) {
    if (0.0f <= x) {
        self->w = x;
    }
    if (0.0f <= y) {
        self->h = y;
    }
    PlaceScreenElement(self);
}

void func_001AAB60(ScreenElement* self) {
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

void func_001AAEC0(ScreenElement* changed)
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

void func_001AAF58(ScreenElement* self, f32* p)
{
    if (self->clock != p) {
        if (p == 0) {
            p = &g_elapsedTime;
        }
        self->since = *p;
    }
    self->clock = p;
}

void func_001AAF88(T217D_E30* self)
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

void func_001AB058(T217D_E30* self)
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

void func_001AB198(T217D_E30* self)
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
    func_00137228(out, self->x, self->y);
    func_00137238(out, px, py);
    tmp[0] = held;
    func_00137248(out, &tmp[0]);
    func_00137260(out, 0);
    func_00137268(out, 0);
    PushFontScale(self->font, self->scale, self->scale);
    InitTextReader(buf, &self->text[0], self->font);
    DrawAlignedText(buf, out, 0, &g_gsPacketWriter);
    PopFontScale(self->font);
}

void func_001AB2B8(T217D_E30* self)
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

f32 func_001AB5D8(void)
{
    return g_gameClock.running != 0 ? 2.5f : 0.0f;
}

void func_001AB600(T217D_510* self)
{
    SetupScreenElementText(self);
    self->font = GetFontById(2);
    self->lastTenth = self->lastSecond = -1;
    self->warnAt = 3.4028235e+38f;
    self->f290 = 1;
    SetTimerState(self, 0);
}

void func_001AB660(T217D_510* self)
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

void func_001AB710(T217D_510* self)
{
    Local_001AB710 L;
    if (self->text[0] != 0) {
        f32 f234 = self->w;
        f32 f238 = self->h;
        s32 s0v = self->color;
        func_00137228(&L, self->x, self->y);
        func_00137238(&L, f234, f238);
        L.tag = s0v;
        func_00137248(&L, &L.tag);
        func_00137260(&L, 0);
        func_00137268(&L, 0);
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
        ((u8*)&L.tag)[0] = 0x54;
        ((u8*)&L.tag)[1] = 0;
        DrawFontString(self->font, &L.tag, &L, 0, dp);
        f32 r = MeasureFontString(self->font, &L.tag);
        f32 a = self->x + r;
        L.y = self->y;
        L.x = a;
        if (self->warned != 0) {
            L.w30 = self->warnColor;
            L.w10 = L.w30;
        }
        DrawFontString(self->font, (u8*)self + 9, &L, 0, dp);
        PopFontScale(self->font);
    }
}

void func_001AB890(T217D_510* self, f32 x)
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

void func_001AB920(T217D_510* self, f32 value)
{
    self->rate = value;
}

void func_001AB928(T217D_510* self, T217D_510_Fn onEnd, f32 limit)
{
    self->limit = limit;
    self->onEnd = onEnd;
}

void func_001AB938(T217D_510* self)
{
    SetTimerState(self, 2);
}

void func_001AB958(T217D_510* self)
{
    self->f290 = 1;
    SetTimerState(self, 0);
}

void func_001AB980(T217D_510* self, f32 dt)
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

void func_001ABE20(T217D_510* self, s32 state)
{
    if (self->state != state) {
        self->state = state;
        self->stateSince = g_gameTime;
    }
}

f32 func_001ABE40(void)
{
    return 0.0f;
}

f32 func_001ABE50(void)
{
    return 0.0f;
}

f32 func_001ABE60(void)
{
    return 0.0f;
}

f32 D_002743B0 = 18.0f;
f32 D_002743B4 = 8.0f;
f32 D_002743B8 = 26.0f;
f32 D_002743BC = 340.0f;

INCLUDE_RODATA(jtbl_0024CD70);
INCLUDE_ASM(func_001ABE70);

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
    self->changedAt = g_gameClock.time;
}

Q3_1AC0E8 D_002743C0 = { 0.5f, 0.25f, 0.2f, 0.0f };

void func_001AC0E8(T217D_2E0* self)
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

Obj_2743D0 D_002743D0 = {0};

void func_001AC5C0(T217D_330* self)
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

Obj_2743D0 D_002743F0 = {0};

void func_001AC888(T217D_380* self)
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
    if (CompareStrings(self->text, v) != 0) {
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

s32 func_001AC9E0(T217D_380* self, ScreenElement* other)
{
    s32 r = 0;
    if (AreScreenElementsTogether(self, other) != 0 || self->pending != 0) {
        r = 1;
    }
    return r;
}

void func_001ACA30(T217D_380* self)
{
    if (self->mode != 3 || self->pending == 0) {
        ShowScreenElement(self);
    }
}

void func_001ACA68(T217D_380* self)
{
    if (self->mode == 3 && self->pending != 0) {
        self->pending = 0;
    } else {
        HideScreenElement(self);
    }
}

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
        Font* o = *self->frame;
        if (o != 0) {
            o->vt->drawBox((Font*)((u8*)o + o->vt->adj9), self->frame, &out, &g_gsPacketWriter);
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

Obj_2743D0 D_00274410 = {0};

void func_001ACDA0(T217D_3D0* self)
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

void func_001ACEE0(char* buf, Info_1ACEE0* info, u32 mask)
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

void func_001AD088(ScreenElement* self, s32 value)
{
    if (value != -1) {
        SetElementTextFromEntry(self, value >> 8, (u8)value);
    } else {
        self->vt->m08(self, "<unknown>");
    }
}

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
        FormatToString(&str, (const char*)"%s%s%s", GetEntryName((Idx_1AD0D0*)packed),
                      GetStringLength(&buf) ? (const char*)" " : (const char*)"", &buf);
    } else {
        CopyString(&str, GetEntryName((Idx_1AD0D0*)packed));
    }
    self->vt->m08(self, (const char*)&str);
}

// The names the level picker shows, by level (the first, empty, for none).
const char* D_00274430[6] = { "", "Tide of Terror", "Sunset Snake Eyes", "Vicious Voodoo", "Fire in the Sky", "The Cold Heart of Hate" };

void func_001AD1E8(ScreenElement* self, s32 idx)
{
    char buf[0x200];
    s32 a, b, c;
    CountCategoryFlags(idx, &a, &b, &c);
    Sub_1AD1E8* s1 = &(*(Mgr_1AD1E8**)&g_saveData)->ents[idx];
    CopyString((Buf_1AD1E8*)buf, D_00274430[idx]);
    char* d = buf + GetStringLength(buf);
    if (a)
        d += FormatToString((Buf_1AD1E8*)d, " &1%d^10~b2a83d/%d~.^.&.&3k&.", s1->f438, a);
    if (b)
        d += FormatToString((Buf_1AD1E8*)d, "%s&1%d^10~b2a83d/%d~.^.&.&3v&.", a ? ((char*)" ") : ((char*)""), s1->f43C, b);
    if (c)
        FormatToString((Buf_1AD1E8*)d, "%s&1%d^10~b2a83d/%d~.^.h&.", (a || b) ? ((char*)" ") : ((char*)""), s1->f440, c);
    self->vt->m08(self, buf);
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

void func_001AD3B0(T217D_3D0* self)
{
    if (self->mode == 3 && self->pending != 0) {
        self->pending = 0;
    } else {
        HideScreenElement(self);
    }
}

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
        PacketWriter* s = &g_gsPacketWriter;
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

void func_001AD6A8(T217D_420* self)
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

void func_001AD7B0(T217D_420* self)
{
    Buf_001AD7B0 buf;
    s32 mask = (s32)0xFF808080;
    DrawScreenElementText(self);
    f32 half = 0.5f;
    f32 sc = Cosine(WrapAngle(g_elapsedTime * 8.0f)) * half + half;
    Font* h = GetFontById(1);
    f32 s2 = sc * 0.1f + half;
    PushFontScale(h, s2, s2);
    f32 w = MeasureFontString(h, (void*)"L");
    f32 ht = (f32)h->height * h->sy;
    func_00137228(&buf, self->x + 2.0f + self->w * half - w * half,
                  self->y + 14.0f + self->h * half - ht * half);
    func_00137238(&buf, w, ht);
    *(s32*)((u8*)&buf + 0x20) = mask;
    func_00137248(&buf, (s32*)((u8*)&buf + 0x20));
    func_00137260(&buf, 0);
    func_00137268(&buf, 0);
    DrawFontString(h, (void*)"L", &buf, 0, &g_gsPacketWriter);
    PopFontScale(h);
}

void func_001AD940(T217D_560* self)
{
    SetupScreenElementText(self);
    self->outTime = 0.5f;
}

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

f32 D_00274448 = 0.9f;
f32 D_0027444C = 0.9f;
Obj_2743D0 D_00274450 = {0};

void func_001ADC60(T217D_470* self)
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

f32 D_0027446C = 0.7f;
Pair_274470 D_00274470 = { 0.6f, 0.0f };
const char* D_00274478[3] = { "Press START button for New Game", "Press START button to Resume Game", "Press SELECT button for Menu" };
const char* D_00274484 = "No Controller";
Obj_2743D0 D_00274488 = {0};

void func_001ADF28(T217D_4C0* self)
{
    const FontVt* vt;

    SetupScreenElementText(self);
    vt = self->font->vt;
    self->font = vt->clone((Font*)((u8*)self->font + vt->adj1), D_0027446C, D_00274470.a);
    if (GetFontById(2)) {
        self->frame = (Font**)&D_00274488;
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
    InitTextReader(&loc.obj, self->text, self->font);
    {
        f32 x = MeasureTextWidth(&loc.obj);
        y = MeasureTextHeight(&loc.obj, 0.0f);
        SetScreenElementSize(self, x, y);
    }
    PopFontScale(self->font);
}

void func_001AE130(T217D_4C0* self, s32 force)
{
    if (self->pending != 0 && force == 0) {
        self->pending = 0;
        RebuildPromptText(self);
        force = 1;
    }
    SetScreenElementMode(self, force);
}

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

ASM_FUNC(func_001AE220);

void func_001AE3B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, u8* rgba, s32 flag)
{
    BeginGifTag((Ctx_1AE3B8*)&g_gsPacketWriter, rgba[3] < 0xFF ? 0x41 : 1, 4, 0x441E);

    AddGifRegisterWrite((Ctx_1AE3B8*)&g_gsPacketWriter, 0x47, (u64)(flag ? 0x11001 : 0x11000) | (flag ? 0x60000 : 0x20000));

    AddGifRgbaEntry((Ctx_1AE3B8*)&g_gsPacketWriter, ((u32)((rgba[3] + 1) & 0x1FE) << 23) | (rgba[2] << 16) | (rgba[1] << 8) | rgba[0]);
    AddGifXyzfEntry((Ctx_1AE3B8*)&g_gsPacketWriter, a0, a1, a2, 0);
    AddGifXyzfEntry((Ctx_1AE3B8*)&g_gsPacketWriter, a3, a4, a5, 0);
    CloseGifTag((Ctx_1AE3B8*)&g_gsPacketWriter, 0);
}

f32 D_002744A4 = 0.1f;
f32 D_002744A8 = 1.3f;

void func_001AE510(T217D_5B0* self)
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

ASM_FUNC(func_001AE5E0);

f32 D_002744AC = 0.7f;

void func_001AE758(T217D_600* self)
{
    f32 k = 0.25f;
    Flags_1AE758 fl;
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
    fl.b = 0;
    fl.a = v;
    self->vt->m08(self, (const char*)&fl);
    self->text[0] = 0;
}

void func_001AE7F8(T217D_600* self, s32 flag)
{
    if (flag == 0) {
        self->flag = 0;
    }
    SetScreenElementMode(self, flag);
}

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

Ptr_2744B0 D_002744B0 = { (s8*)"ab", 0 };

Letter_1AEA08 func_001AEA08(void)
{
    s32 scaled = (s32)(g_elapsedTime * 5.0f);
    u32 divisor = GetStringLength((Table_001AEA08*)D_002744B0.p);
    return D_002744B0.p[(u32)scaled % divisor];
}

// The static initialiser GCC writes for this file's text styles (three empty array
// constructions, then the five styles), still assembly; then the 16 bytes the linker left of two
// layout setters, and the file's _GLOBAL_$I$, written as a function until the styles are built by
// constructors here.
INCLUDE_ASM(func_001AEA70);

LINKER_REMNANT(func_001AEC80);

void func_001AEC90(void)
{
    func_001AEA70(1, 0xFFFF);
}
