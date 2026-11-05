// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"

#include "list_iter.h"
#pragma implementation "layout_137228.h"
#include "layout_137228.h"
#include "screen_element.h"
#include "step_sequence.h"
#include "v24a0.h"
#include "pad_record.h"
#include "game_progress.h"

struct Quad_130F48 {
    f32 c0, c1, c2, c3;
} __attribute__((aligned(16)));

struct Span_130F48 {
    Quad_130F48 head;
    f32 len;
    f32 halfw;
    s32 lo;
    s32 mid;
    s32 hi;
    f32 p;
    f32 q;
};

void func_001365A0(T217D_440* self, s32 arg);

struct Rgba_130F48
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    Rgba_130F48() {}
    Rgba_130F48(const Rgba_130F48& o) { *this = o; }
    Rgba_130F48(u8 r_, u8 g_, u8 b_, u8 a_) : r(r_), g(g_), b(b_), a(a_) {}
};
struct Gs_133B58;

f32 func_00205210(f32 x);
void func_001613C0(Gs_133B58* gs, s32 a, s32 b, s32 c);
void func_00161458(Gs_133B58* gs, u32 c);
void func_00161670(Gs_133B58* gs, s32 x, s32 y, s32 a3, s32 a4);
void func_001615F0(Gs_133B58* gs, s32 x, s32 y, s32 a3, s32 a4);

struct Lerp_133B58
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

    static Rgba_130F48 Mix(Rgba_130F48 a, Rgba_130F48 b, f32 t)
    {
        Rgba_130F48 c;
        c.r = Channel(a.r, b.r, t);
        c.g = Channel(a.g, b.g, t);
        c.b = Channel(a.b, b.b, t);
        c.a = Channel(a.a, b.a, t);
        return c;
    }
};

struct Gs_132500;

struct Clock_132500 { u8 pad[0x478]; f32 f478; };

extern s32 D_00262C68;
extern f32 D_00261860;
extern Clock_132500* D_00261990;

void func_001613C0(Gs_132500* gs, s32 a, s32 b, u64 c);
void func_00161708(Gs_132500* gs, s32 reg, u64 value);
void func_00161458(Gs_132500* gs, u32 color);
void func_00161670(Gs_132500* gs, s32 x, s32 y, s32 z, s32 f);
void func_001615F0(Gs_132500* gs, s32 x, s32 y, s32 z, s32 f);
f32 func_001EA408(f32 a);
f32 func_00205210(f32 a);
void func_00136EC8(T217D_440* self, f32* x, f32* y);

struct Gfx_132500 {
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

    static Rgba_130F48 Lerp(Rgba_130F48 a, Rgba_130F48 b, f32 t)
    {
        Rgba_130F48 r;
        r.r = LerpU8(a.r, b.r, t);
        r.g = LerpU8(a.g, b.g, t);
        r.b = LerpU8(a.b, b.b, t);
        r.a = LerpU8(a.a, b.a, t);
        return r;
    }

    static f32 Wave(f32 x, f32 period, f32 phase)
    {
        return func_00205210(phase + (x / period) * 2.0f * 3.1415927f);
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

void func_001AA8C8(void* self);
s32 func_00150790(void* obj, s32 mode);

void func_001356C0(T217D_440* self, s32 mode);
void func_00150790(StepSequence* obj, s32 mode);

struct Entry_1357F0 {
    void* obj;
    f32 key;
};

s32 func_00182FC8(void* obj);

struct Entry_135858 {
    void* obj;
    f32 key;
};

void func_00199C10(void* obj, s32* out);

void func_0019EBE8(void* handle);
void func_001A1DF0(void* handle, s32 mode);
void* func_001F5C0C(void* block, s32 value, s32 size);

// func_00136FA8 keeps its own view: it uses the result of func_001356C0, which returns nothing.
struct Owner_136FA8 { u8 pad0[0x324]; void* child; };

s32 func_001356C0(Owner_136FA8* self, s32 mode);

// Newly matched US functions from the small-function wave.
extern void func_001373D0(void*);
extern void func_0018D778(void*);
extern void func_00137A60(void*, s32, void*);

struct Value_1365A8 {
    static void Set(T217D_440* self, f32 x, f32 lo, f32 hi) {
        if (x < lo) x = lo;
        else if (hi < x) x = hi;
        self->value = x;
    }
};

extern f32 D_0026185C;

V24A2* func_0015DB28(void* out, void* p, V24A2* font);
s32 func_0015DF58(void* self);

extern f32 D_00261858[];

struct Scratch_00136408 {
    u8 bytes[0xB0];
};

s32 func_001E2100(const char* s);
void func_001E2138(void* dst, const char* src);
void func_0015C8B8(V24A2* font, f32 x, f32 y);
void func_0015E068(void* buf, f32 x);
void func_0015C900(V24A2* font);
void func_0015DB80(void* buf);
s32 func_0015DBE0(void* buf);

struct __attribute__((packed)) Tail_1356C0 { u8 pad0[0x464]; s32 v; };
extern f32 D_0026185C;

void func_00131140(T217D_440* self);
void func_001BFCD8(s32 a, s32 b, s32 c, s32 d, f32 g, f32 h, f32 i, f32 j, f32 k, s32 e, s32 f);

extern u8 D_00275710[];
extern u8 func_00135E20[];
extern u8 func_00135E40[];

struct Ctx_135F48 {
    u8 pad000[0x1D44];
    s32 f1D44;
    u8 pad1D48[0x0C];
    s32 f1D54;
};

struct Flag_135F48 { s32 v; };

void func_00160D30(Flag_135F48* p);
s32 func_00160D10(void);
void func_001358D0(T217D_440* self, s32 a1, void* a2, void* a3, s32 a4, s32 a5, f32 f);

struct Tri_136040 { u64 a __attribute__((packed)); u32 b; };
typedef u64 Quad_136040 __attribute__((mode(TI)));
struct __attribute__((aligned(16))) Vec_136040 { f32 x, y, z, w; };
struct Pad_136040 {
    u8 pad_00[0x40];
    f32 f40;
    f32 f44;
    f32 f48;
    u8 pad_4C[0x74 - 0x4C];
    f32 f74;
    u8 pad_78[4];
    f32 f7C;
};

extern const Tri_136040 D_00249D00;
extern const Tri_136040 D_00249D10;

Quad_136040 func_001EA818(Quad_136040 a, Quad_136040 b, Tri_136040* c, s32 d, f32 f12);
f32 func_001EAFE0(f32 x, f32 y);
void func_00135F48(T217D_440* self, Pad_136040* p);

struct __attribute__((aligned(16))) Vec_135E30 { s32 a, b, c, d; };
struct Obj_135E30 { char pad[0x140]; Vec_135E30 v; };

struct __attribute__((aligned(16))) Vec_135E48 { s32 a, b, c, d; };
struct Obj_135E48 { char pad[0x140]; Vec_135E48 v; };

void func_001A1F40(Vec_135E48* v, s32 mode);

struct Item_135550;
struct List_135550 { u8* head; u8 pad4[4]; s32 offset; };
struct Iter_135550 { List_135550* list; u8* link; s32 offset; Iter_135550* saved; };
struct Group_135550 { u8 pad0[0x6C]; List_135550 list; };
struct Host_135550;

struct Next_135550 {
    static Item_135550* Of(Iter_135550* it)
    {
        Item_135550* obj = *(Item_135550**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_135550 {
    static void Of(Iter_135550* it, List_135550* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_135550*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

Group_135550* func_0015A418(Host_135550* host, s32 a1, s32 a2, void* ctx);
void func_0012F6B0(Item_135550* item, f32 x);

struct Sub_136238 { u8 pad0[0x2D4]; s32 f2D4; };
struct In_136238 { s32 a; };

extern u8 D_00275710[];

void func_001BEA50(void);
void func_001BEA28(void);
void func_00160D30(In_136238* p);
s32 func_00160D10(void);
void func_00135E78(T217D_440* self, s32 state, s32 flag);
s32 func_0015A4F0(s32 a, s32 b, s32 c, void* d, s32 e, void* f);
void func_00192190(void* p);

struct Min_136238 { static s32 Of(s32 a, s32 b) { if (b - 1 < a) return b; return a; } };

void func_00160D30(u32* out);
void func_00134B48(T217D_440* self, V24A0* q);
f32 func_00205210(f32 x);
f32 func_001EA4B8(f32 a, f32 b, f32 c, f32* p, s32 zero);
void func_001613C0(V24A0* q, s32 a, s32 b, u64 c);
void func_00161458(V24A0* q, u32 v);
void func_001615F0(V24A0* q, s32 a, s32 b, s32 c, s32 d);

// The file's .data, in retail's order from 0x261090. The colours and the two styles are built
// by the static initialiser (func_00136FE8); their bytes are zero until then.
struct Style_136FE8 {
    s32 f0;
    u8 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u32 f18;
    Style_136FE8(f32 w)
    {
        func_001F5C0C(this, 0, 0x1C);
        f4 = 0x2D;
        f8 = w;
        f10 = 0.3f;
        f14 = 0.3f;
        f18 = 0xFF7D4B00;
    }
    Style_136FE8(s32 w, s32 h)
    {
        func_001F5C0C(this, 0, 0x1C);
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
Rgba_130F48 D_002610D0(0x00, 0x00, 0x00, 0x80);
Rgba_130F48 D_002610D8(0x00, 0x52, 0x7E, 0x80);
Rgba_130F48 D_002610E0(0x19, 0x1E, 0x6E, 0x80);
Rgba_130F48 D_002610E8(0x7E, 0x28, 0x0A, 0x80);
Rgba_130F48 D_002610F0(0x50, 0x28, 0x28, 0x80);
Rgba_130F48 D_002610F8(0xF0, 0xF0, 0x00, 0x80);
Rgba_130F48 D_00261100(0x28, 0x28, 0x00, 0x80);
Rgba_130F48 D_00261108(0xFF, 0xFF, 0xFF, 0x80);
Rgba_130F48 D_00261110(0xE6, 0xE6, 0xE6, 0x80);
Rgba_130F48 D_00261118(0x2F, 0x72, 0x3E, 0x80);
s32 D_00261120[2] = { -268435456, -268435456 };
// The eight compass points, read by func_00131198 and func_001316E8.
const char* D_00261128[8] = { "N", "NW", "W", "SW", "S", "SE", "E", "NE" };
Style_136FE8 D_00261148(2.0f);
Style_136FE8 D_00261168(32, 16);
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
Span_130F48 D_00261280;
Span_130F48 D_002612B0;
Span_130F48 D_002612E0;
f32 D_00261310;

void func_00130F48(Span_130F48* d, const Quad_130F48* src, s32 n, f32 x, f32 y);
f32 func_00131000(const Span_130F48* s, s32 x);
void func_001310F0(T217D_440* self, s32 a1);
void func_00131140(T217D_440* self);
void func_00132500(T217D_440* self, Gs_132500* gs);
void func_00133B58(T217D_440* self, Gs_133B58* gs);
void func_00135228(T217D_440* self, V24A0* q);
void func_00135550(T217D_440* self, s32 value);
void func_001356C0(T217D_440* self, s32 mode);
s32 func_001357F0(Entry_1357F0* a, Entry_1357F0* b);
s32 func_00135858(Entry_135858* a, Entry_135858* b);
void func_00135E30(Obj_135E30* self, Vec_135E30* out, s32* flag);
void func_00135E48(Obj_135E48* self, s32 unused, Vec_135E48* out);
void func_00135E78(T217D_440* self, s32 state, s32 flag);
void func_00135F48(T217D_440* self);
void func_00136040(T217D_440* self, Pad_136040* p);
void func_00136238(T217D_440* self, s32 on);
void func_001363D0(T217D_440* self);
void func_00136408(T217D_440* self, const char* name);
s32 func_00136530(T217D_440* self);
void func_001365A0(T217D_440* self, s32 value);
void func_001365A8(T217D_440* self, f32 value);
f32 func_001365F0(T217D_440* self);
f32 func_00136648(T217D_440* s);
void func_00136EC8(T217D_440* self, f32* x, f32* y);
void func_00136EF8(T217D_440* self);
s32 func_00136FA8(Owner_136FA8* self);

void func_00130F48(Span_130F48* d, const Quad_130F48* src, s32 n, f32 x, f32 y)
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

f32 func_00131000(const Span_130F48* s, s32 x)
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

void func_001310F0(T217D_440* self, s32 a1)
{
    self->w = 640.0f;
    self->h = 492.800018f;
    self->charsPerSecond = 15.0f;
    self->highlight = 0x80FFFFFF;
    func_001AA1F0(self, a1);
}

void func_00131140(T217D_440* self)
{
    self->vt->m08(self, 0);
    func_001365A0(self, 0);
    self->value = 0;
    self->stickX = 0;
    self->stickY = 0;
    self->f314 = 0.4f;
}

ASM_FUNC(func_00131198);

INCLUDE_ASM(func_001316E8);

INCLUDE_RODATA(D_00249CE0);
INCLUDE_RODATA(D_00249CE8);
INCLUDE_RODATA(D_00249CF0);
INCLUDE_ASM(func_00131F60);

void func_00132500(T217D_440* self, Gs_132500* gs)
{
    Rgba_130F48 c0;
    Rgba_130F48 c1;
    f32 k;
    PadRecord* pad;
    u8 alpha;
    f32 posX;
    f32 posY;
    f32 scale;
    f32 offX;
    f32 offY;

    func_001613C0(gs, 0, 1, 0xE);
    func_00161708(gs, 0x47, 0x31001);
    func_00161708(gs, 0x42, 0x44);
    func_00161708(gs, 0x40, 0xA90003027F0000);

    pad = (D_00262C68 & 2) ? &D_00262C70 : &D_00262D38;
    k = 3.0f;
    if (0.0f < pad->f78) {
        k = 6.0f;
    } else if (pad->f78 < 0.0f) {
        k = -6.0f;
    }
    self->spin = func_001EA408(self->spin + D_00261860 * k);

    alpha = (s32)(D_00261990->f478 * 24.999f) + 0x30;
    switch (self->palette) {
    case 0:
        if (self->state == 5) {
            Rgba_130F48 t = D_00261110;
            t.a = alpha;
            c0 = t;
            t = D_00261108;
            t.a = alpha;
            c1 = t;
        } else {
            Rgba_130F48 t = (*(Rgba_130F48*)&D_002610E0);
            t.a = alpha;
            c0 = t;
            t = (*(Rgba_130F48*)&D_002610D8);
            t.a = alpha;
            c1 = t;
        }
        break;
    case 1: {
        Rgba_130F48 t = D_00261100;
        t.a = alpha;
        c0 = t;
        t = D_002610F8;
        t.a = alpha;
        c1 = t;
        break;
    }
    case 2: {
        Rgba_130F48 t = D_002610F0;
        t.a = alpha;
        c0 = t;
        t = D_002610E8;
        t.a = alpha;
        c1 = t;
        break;
    }
    }

    func_00136EC8(self, &posX, &posY);
    scale = D_00261990->f478 + 1.0f;

    {
        f32 step = 1.0f / 24.0f;
        f32 period = 256.0f;
        f32 wide = 512.0f;
        f32 s = Gfx_132500::Wave(-8.0f, period, self->spin);
        Rgba_130F48 colA = Gfx_132500::Lerp(c0, c1, 0.5f - s * 0.5f);
        s = Gfx_132500::Wave(-18.0f, period, self->spin);
        Rgba_130F48 colB = Gfx_132500::Lerp(c0, c1, 0.5f - s * 0.5f);
        f32 x0 = posX - scale * 35.0f;
        f32 x1 = x0 + scale * 70.0f;
        f32 u;
        s32 i;

        func_001613C0(gs, 0x4C, 2, 0x41);

        func_00161458(gs, *(u32*)&colB);
        func_00161670(gs, Gfx_132500::ScreenX(x0), Gfx_132500::ScreenY(posY + scale * -8.0f), 0, 0);
        func_00161458(gs, *(u32*)&colA);
        func_00161670(gs, Gfx_132500::ScreenX(x0), Gfx_132500::ScreenY(posY + scale * -3.0f), 0, 0);
        u = step;
        for (i = 1; i < 24; i++) {
            f32 x = x0 + scale * u * 70.0f;
            f32 y;
            f32 y2;
            u += step;
            y = posY + scale * func_00131000(&D_002612E0, i);
            y2 = y + scale * 5.0f;
            func_00161458(gs, *(u32*)&colB);
            func_001615F0(gs, Gfx_132500::ScreenX(x), Gfx_132500::ScreenY(y), 0, 0);
            func_00161458(gs, *(u32*)&colA);
            func_001615F0(gs, Gfx_132500::ScreenX(x), Gfx_132500::ScreenY(y2), 0, 0);
        }
        func_00161458(gs, *(u32*)&colB);
        func_001615F0(gs, Gfx_132500::ScreenX(x1), Gfx_132500::ScreenY(posY + scale * -8.0f), 0, 0);
        func_00161458(gs, *(u32*)&colA);
        func_001615F0(gs, Gfx_132500::ScreenX(x1), Gfx_132500::ScreenY(posY + scale * -4.0f), 0, 0);

        func_00161458(gs, *(u32*)&colB);
        func_00161670(gs, Gfx_132500::ScreenX(x0), Gfx_132500::ScreenY(posY - scale * -8.0f), 0, 0);
        func_00161458(gs, *(u32*)&colA);
        func_00161670(gs, Gfx_132500::ScreenX(x0), Gfx_132500::ScreenY(posY - scale * -3.0f), 0, 0);
        u = step;
        for (i = 1; i < 24; i++) {
            f32 x = x0 + scale * u * 70.0f;
            f32 y;
            f32 y2;
            u += step;
            y = posY - scale * func_00131000(&D_002612E0, i);
            y2 = y - scale * 5.0f;
            func_00161458(gs, *(u32*)&colB);
            func_001615F0(gs, Gfx_132500::ScreenX(x), Gfx_132500::ScreenY(y), 0, 0);
            func_00161458(gs, *(u32*)&colA);
            func_001615F0(gs, Gfx_132500::ScreenX(x), Gfx_132500::ScreenY(y2), 0, 0);
        }
        func_00161458(gs, *(u32*)&colB);
        func_001615F0(gs, Gfx_132500::ScreenX(x1), Gfx_132500::ScreenY(posY - scale * -8.0f), 0, 0);
        func_00161458(gs, *(u32*)&colA);
        func_001615F0(gs, Gfx_132500::ScreenX(x1), Gfx_132500::ScreenY(posY - scale * -4.0f), 0, 0);

        if (self->state != 5) {
            s32 n;

            offX = 41.0f;
            offY = -5.0f;
            func_001613C0(gs, 0xC6, 5, 0x44441);
            for (n = 0; n < 64; n++) {
                f32 px, py;
                f32 s = Gfx_132500::Wave(offX, wide, self->spin);
                px = posX + scale * offX;
                py = posY + scale * offY;
                Rgba_130F48 col = Gfx_132500::Lerp(c0, c1, 0.5f - s * 0.5f);
                func_00161458(gs, *(u32*)&col);
                func_00161670(gs, Gfx_132500::ScreenX(px), Gfx_132500::ScreenY(py), 0, 0);
                func_001615F0(gs, Gfx_132500::ScreenX(px + scale * 2.0f), Gfx_132500::ScreenY(py + scale * 10.0f), 0, 0);
                py = posY + scale * offY;
                px = posX - scale * offX;
                func_00161670(gs, Gfx_132500::ScreenX(px), Gfx_132500::ScreenY(py), 0, 0);
                func_001615F0(gs, Gfx_132500::ScreenX(px - scale * 2.0f), Gfx_132500::ScreenY(py + scale * 10.0f), 0, 0);
                offX += 8.0f;
            }

            offX = -5.0f;
            offY = 24.0f;
            for (n = 0; n < 32; n++) {
                f32 px, py;
                f32 s = Gfx_132500::Wave(offY, period, self->spin);
                px = posX + scale * offX;
                py = posY + scale * offY;
                Rgba_130F48 col = Gfx_132500::Lerp(c0, c1, 0.5f - s * 0.5f);
                func_00161458(gs, *(u32*)&col);
                func_00161670(gs, Gfx_132500::ScreenX(px), Gfx_132500::ScreenY(py), 0, 0);
                func_001615F0(gs, Gfx_132500::ScreenX(px + scale * 10.0f), Gfx_132500::ScreenY(py + scale * 2.0f), 0, 0);
                py = posY - scale * offY;
                px = posX + scale * offX;
                func_00161670(gs, Gfx_132500::ScreenX(px), Gfx_132500::ScreenY(py), 0, 0);
                func_001615F0(gs, Gfx_132500::ScreenX(px + scale * 10.0f), Gfx_132500::ScreenY(py - scale * 2.0f), 0, 0);
                offY += 8.0f;
            }
        }
    }

    func_001613C0(gs, 0, 1, 0xE);
    func_00161708(gs, 0x40, 0xDF0000027F0000);
}

void func_00133B58(T217D_440* self, Gs_133B58* gs)
{
    Rgba_130F48 c0;
    Rgba_130F48 c1;
    Rgba_130F48 c2;
    f32 step = 1.0f / 24.0f;
    f32 t;
    t = 0.5f - func_00205210(self->spin) * 0.5f;
    c0 = Lerp_133B58::Mix(D_002610E0, D_002610D8, t);
    t = 0.5f - func_00205210(self->spin + 1.5707964f) * 0.5f;
    c1 = Lerp_133B58::Mix(D_002610E0, D_002610D8, t);
    t = 0.5f - func_00205210(self->spin + 3.1415927f) * 0.5f;
    c2 = Lerp_133B58::Mix(D_002610E0, D_002610D8, t);
    s32 i;
    f32 x;

    func_001613C0(gs, 0x8C, 2, 0x41);

    func_00161458(gs, *(u32*)&c2);
    func_00161670(gs, 0x6C00, 0x7B45, 0, 0);
    func_00161458(gs, *(u32*)&c1);
    func_00161670(gs, 0x6C00, 0x7B62, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 v = func_00131000(&D_00261280, i);
        f32 sx = x * 640.0f;
        f32 v2 = v + 4.0f;
        func_00161458(gs, *(u32*)&c2);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        func_001615F0(gs, px, (s32)((v * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        func_00161458(gs, *(u32*)&c1);
        func_001615F0(gs, px, (s32)((v2 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    }
    func_00161458(gs, *(u32*)&c2);
    func_001615F0(gs, 0x9400, 0x7B45, 0, 0);
    func_00161458(gs, *(u32*)&c1);
    func_001615F0(gs, 0x9400, 0x7B62, 0, 0);

    func_00161458(gs, *(u32*)&c2);
    func_00161670(gs, 0x6C00, 0x80FA, 0, 0);
    func_00161458(gs, *(u32*)&c1);
    func_00161670(gs, 0x6C00, 0x80DD, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 v = func_00131000(&D_002612B0, i);
        f32 sx = x * 640.0f;
        f32 v2 = v - 4.0f;
        func_00161458(gs, *(u32*)&c2);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        func_001615F0(gs, px, (s32)((v * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        func_00161458(gs, *(u32*)&c1);
        func_001615F0(gs, px, (s32)((v2 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    }
    func_00161458(gs, *(u32*)&c2);
    func_001615F0(gs, 0x9400, 0x80FA, 0, 0);
    func_00161458(gs, *(u32*)&c1);
    func_001615F0(gs, 0x9400, 0x80DD, 0, 0);

    func_00161458(gs, *(u32*)&c1);
    func_00161670(gs, 0x6C00, 0x7B62, 0, 0);
    func_00161458(gs, *(u32*)&c0);
    func_00161670(gs, 0x6C00, 0x7B80, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 r = func_00131000(&D_00261280, i);
        f32 sx = x * 640.0f;
        f32 v = r + 4.0f;
        f32 v2 = v + 4.0f;
        func_00161458(gs, *(u32*)&c1);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        func_001615F0(gs, px, (s32)((v * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        func_00161458(gs, *(u32*)&c0);
        func_001615F0(gs, px, (s32)((v2 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    }
    func_00161458(gs, *(u32*)&c1);
    func_001615F0(gs, 0x9400, 0x7B62, 0, 0);
    func_00161458(gs, *(u32*)&c0);
    func_001615F0(gs, 0x9400, 0x7B80, 0, 0);

    func_00161458(gs, *(u32*)&c1);
    func_00161670(gs, 0x6C00, 0x80DD, 0, 0);
    func_00161458(gs, *(u32*)&c0);
    func_00161670(gs, 0x6C00, 0x80C0, 0, 0);
    x = 1.0f / 24.0f;
    for (i = 1; i < 24; i++)
    {
        f32 r = func_00131000(&D_002612B0, i);
        f32 sx = x * 640.0f;
        f32 v = r - 4.0f;
        f32 v2 = v - 4.0f;
        func_00161458(gs, *(u32*)&c1);
        s32 px = (s32)((sx + 1728.0f) * 16.0f);
        x += step;
        func_001615F0(gs, px, (s32)((v * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
        func_00161458(gs, *(u32*)&c0);
        func_001615F0(gs, px, (s32)((v2 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    }
    func_00161458(gs, *(u32*)&c1);
    func_001615F0(gs, 0x9400, 0x80DD, 0, 0);
    func_00161458(gs, *(u32*)&c0);
    func_001615F0(gs, 0x9400, 0x80C0, 0, 0);
}

ASM_FUNC(func_00134AA0);

INCLUDE_RODATA(D_00249CF8);
ASM_FUNC(func_00134B48);

void func_00135228(T217D_440* self, V24A0* q)
{
    if (self->state == 1)
    {
        if ((u32)func_00160D10() & 0x800)
        {
            func_00134B48(self, q);
        }
        u32 mask;
        func_00160D30(&mask);
        if ((u32)func_00160D10() & mask)
        {
            u8 c0[4];
            u8 c1[4];
            u8 c2[4];
            u8 out[4];
            *(u32*)c0 = 0xFF408080;
            *(u32*)c1 = 0xFF406060;
            *(u32*)c2 = 0xFF404040;
            f32 t = func_00205210(D_00261858[1] * D_00261260[0]) * 0.5f + 0.5f;
            for (u32 i = 0; i < 4; i++)
            {
                f32 r = func_001EA4B8(self->blockB[i], self->blockA[i] ? 1.0f : 0.0f, D_00261858[2], &D_00261260[2], 0);
                self->blockB[i] = r;
                for (s32 j = 0; j < 4; j++)
                {
                    out[j] = (s32)((1.0f - r) * (f32)c2[j] + r * t * (f32)c1[j] + r * (1.0f - t) * (f32)c0[j]);
                }
                out[3] = (out[3] + 1) >> 1;
                func_001613C0(q, 0x4D, 5, 0x44441);
                func_00161458(q, *(u32*)out);
                for (s32 k = 0; k < 4; k++)
                {
                    s32 xi = (s32)(((D_002611E0[i][k] + 320.0f) + 1728.0f) * 16.0f);
                    s32 yi = (s32)(((D_00261220[i][k] + 415.8000183f) * 0.45454547f + 1936.0f) * 16.0f);
                    func_001615F0(q, xi, yi, 0, 0);
                }
            }
        }
    }
}

void func_00135550(T217D_440* self, s32 value)
{
    if (value == self->mode) {
        return;
    }
    if (self->mode == 0) {
        Group_135550* g = func_0015A418((*(Host_135550**)&D_00275710), 0x105, 0x495, 0);
        if (g != 0) {
            Iter_135550 it;
            Begin_135550::Of(&it, &g->list);
            Item_135550* obj;
            while ((obj = Next_135550::Of(&it)) != 0) {
                func_0012F6B0(obj, 0.0f);
            }
            D_0027B314 = (ListFrame*)it.saved;
        }
    }
    if (value == 0) {
        Group_135550* g = func_0015A418((*(Host_135550**)&D_00275710), 0x105, 0x495, 0);
        if (g != 0) {
            Iter_135550 it;
            Begin_135550::Of(&it, &g->list);
            Item_135550* obj;
            while ((obj = Next_135550::Of(&it)) != 0) {
                func_0012F6B0(obj, 1.0f);
            }
            D_0027B314 = (ListFrame*)it.saved;
        }
    }
    func_001AA998(self, value);
}

void func_001356C0(T217D_440* self, s32 mode)
{
    if (mode != self->state) {
        if (self->state != 1) {
            if (self->state < 2) {
                if (self->state == 0) {
                    func_00131140(self);
                }
            }
        } else {
            func_001BFCD8(0x8F, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
        switch (mode) {
        case 1:
            func_001BFCD8(0x8E, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
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
        self->stateSince = D_0026185C;
    }
}

s32 func_001357F0(Entry_1357F0* a, Entry_1357F0* b)
{
    if (func_00182FC8(a->obj) == 0) {
        return 1;
    }
    if (func_00182FC8(b->obj) == 0) {
        return -1;
    }
    if (a->key < b->key) {
        return -1;
    }
    return 1;
}

s32 func_00135858(Entry_135858* a, Entry_135858* b)
{
    s32 flag;

    func_00199C10(a->obj, &flag);
    if (flag != 0) {
        return 1;
    }
    func_00199C10(b->obj, &flag);
    if (flag != 0) {
        return -1;
    }
    if (a->key < b->key) {
        return -1;
    }
    return 1;
}

ASM_FUNC(func_001358D0);

LINKER_REMNANT(func_00135E20);

void func_00135E30(Obj_135E30* self, Vec_135E30* out, s32* flag)
{
    *out = self->v;
    *flag = 0;
}

LINKER_REMNANT(func_00135E40);

void func_00135E48(Obj_135E48* self, s32 unused, Vec_135E48* out)
{
    *out = self->v;
    func_001A1F40(out, 1);
}

LINKER_REMNANT(func_00135E70);

void func_00135E78(T217D_440* self, s32 state, s32 flag)
{
    if (state == self->bankState) return;
    s32 i = 0;
    void* blockA = self->blockA;
    if (self->count > 0) {
        T217D_440_Slot* e = self->entries;
        do {
            if (flag != 0) {
                func_0019EBE8(e->handle);
                func_001F5C0C(self->blockB, 0, 16);
            } else {
                func_001A1DF0(e->handle, 2);
            }
            i++;
            e++;
        } while (i < self->count);
    }
    self->count = 0;
    self->countA = 0;
    func_001F5C0C(blockA, 0, 16);
    self->bankState = state;
}

void func_00135F48(T217D_440* self)
{
    Flag_135F48 flag;
    func_00160D30(&flag);
    if ((func_00160D10() & flag.v) == 0) {
        func_00135E78(self, 0, 1);
        return;
    }
    func_00135E78(self, 1, 0);
    if (self->bankState == 1) {
        f32 k = 3.4028235e38f;
        Ctx_135F48* ctx = *(Ctx_135F48**)D_00275710;
        func_001358D0(self, 0x2E, func_00135E20 + 0x10, func_00135E40 + 8, 5, ctx->f1D44, k);
        func_001358D0(self, 0x21, func_00135E20 + 0x10, func_00135E40 + 8, 5, (*(Ctx_135F48**)D_00275710)->f1D54, k);
    }
}

void func_00136040(T217D_440* self, Pad_136040* p)
{
    switch (self->state) {
    case 1: {
        Vec_136040 va;
        Vec_136040 vb;
        Vec_136040 r;
        f32 lo = -1.0f;
        f32 hi = 1.0f;
        f32 sum = p->f40 + p->f74;
        Tri_136040 t0 = D_00249D00;
        Tri_136040 t1 = D_00249D10;
        f32 u = (sum < lo) ? lo : ((hi < sum) ? hi : sum);
        f32 v = p->f44;
        f32 lo2 = -1.0f;
        f32 hi2 = 1.0f;
        if (v < lo2) {
            v = lo2;
        } else if (hi2 < v) {
            v = hi2;
        }
        if (D_002623C0->u19EC & 0x200) v = -v;
        va.x = self->stickX;
        va.y = self->stickY;
        va.z = 0;
        vb.x = u * 50.0f;
        vb.y = v * 50.0f;
        vb.z = 0;
        f32* g = ((f32*)D_00261858);
        *(Quad_136040*)&r = func_001EA818(*(Quad_136040*)&va, *(Quad_136040*)&vb, (0.0001f < p->f48 + p->f7C) ? &t0 : &t1, 0, g[2]);
        self->f314 += u * -0.08f;
        self->stickX = r.x;
        self->stickY = r.y;
        self->f314 = func_001EAFE0(self->f314, 1.0f);
        break;
    }
    case 5:
        self->stickY = 50.0f;
        break;
    }
    func_00135F48(self, p);
}
extern const Tri_136040 D_00249D00 = { 0x4248000042A00000ULL, 0x3F000000 };
extern const Tri_136040 D_00249D10 = { 0x43480000437A0000ULL, 0x3DCCCCCD };

void func_00136238(T217D_440* self, s32 on)
{
    In_136238 in;
    void* arr[0x100];
    s32 n;
    if ((on != 0) != (self->open == 0)) return;
    if (self->child != 0 && ((Sub_136238*)self->child)->f2D4 == 3) {
        if (on != 0) func_001BEA50();
        else func_001BEA28();
    }
    self->open = on;
    self->palette = 0;
    if (on != 0) {
        self->vt->m16(self, 2);
        func_00160D30(&in);
        if (func_00160D10() & in.a) {
            if (func_00160D10() & D_00261120[self->savedBank]) func_00135E78(self, self->savedBank, 1);
        }
        if (func_00160D10() & 0x800) {
            n = func_0015A4F0(*(s32*)D_00275710, 0x205, 0x82, 0, 0x100, arr);
            n = Min_136238::Of(n, 0x100);
            if (n > 0) {
                void** p = arr;
                s32 i = n;
                do { i--; func_00192190(*p); p++; } while (i != 0);
            }
        }
    } else {
        self->vt->m16(self, 0);
        self->savedBank = self->bankState;
        func_00135E78(self, 0, 1);
    }
}

void func_001363D0(T217D_440* self)
{
    func_001AA8C8(self);
    if (self->child != 0) {
        func_00150790(self->child, 2);
    }
}

void func_00136408(T217D_440* self, const char* name)
{
    Scratch_00136408 buf;
    s32 s1;
    s32 r;
    s32 idx;
    f32 scale;
    f32 lim;
    f32* tab;

    self->lineCount = 0;
    if (name == 0) goto fail;
    if (func_001E2100(name) == 0) goto fail;
    func_001E2138(self->text, name);
    s1 = 4;
    scale = 1.0f;
    if ((r = self->state) == s1) scale = 0.8f;
    func_0015C8B8(self->font, scale, scale);
    func_0015DB28(&buf, self->text, self->font);
    lim = 280.0f;
    if ((r = self->state) == s1) lim = 380.0f;
    s1 = 0;
    func_0015E068(&buf, lim);
    func_0015C900(self->font);
    func_0015DB80(&buf);
    while ((r = func_0015DBE0(&buf)) != 0) {
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
    tab = (f32*)D_00261858;
    self->textSince = tab[1];
}

s32 func_00136530(T217D_440* self)
{
    u8 buf[0xB0];

    if (self->text[0] == 0) {
        return 1;
    }
    func_0015DB28(buf, &self->text[0], self->font);
    s32 n = func_0015DF58(buf);
    s32 v = (s32)((D_0026185C - self->textSince) * self->charsPerSecond);
    return v >= n;
}

void func_001365A0(T217D_440* self, s32 value) { self->f2FC = value; }

void func_001365A8(T217D_440* self, f32 value)
{
    Value_1365A8::Set(self, value * 0.01f, 0.0f, 1.0f);
}

f32 func_001365F0(T217D_440* self)
{
    switch (self->state) {
    case 1:
    case 2:
    case 5:
        return 0.0f;
    case 3:
    case 4:
    default:
        return func_001AA898(self);
    }
}

f32 func_00136648(T217D_440* s) {
    switch (s->state) {
    case 1:
    case 2:
    case 5:
        return 0.0f;
    case 3:
    case 4:
    default:
        return func_001AA8A8(s);
    }
}

INCLUDE_RODATA(D_00249D58);
ASM_FUNC(func_001366A0);

void func_00136EC8(T217D_440* self, f32* x, f32* y)
{
    *x = self->stickX + 320.0f;
    *y = self->stickY + 180.4000091552734375f;
}

void func_00136EF8(T217D_440* self)
{
    if (self->child != 0) {
        switch (((StepSequence*)self->child)->mode2D0) {
        case 0:
            func_001356C0(self, 2);
            break;
        case 1:
            func_001356C0(self, 3);
            break;
        case 2:
            func_001356C0(self, 4);
            break;
        }
        func_00150790((StepSequence*)self->child, 3);
    } else {
        func_001356C0(self, 1);
    }
}

s32 func_00136FA8(Owner_136FA8* self)
{
    s32 r;
    if (self->child != 0) {
        r = func_00150790(self->child, 4);
        goto done;
    }
    r = func_001356C0(self, 0);
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
