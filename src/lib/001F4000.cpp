// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct RandomState_1F6708 { u8 pad[0x58]; u32 state; };
extern RandomState_1F6708* D_0027696C;

u32 func_001F6708(void)
{
    u32 state = D_0027696C->state * 0x41C64E6Du + 0x3039u;
    D_0027696C->state = state;
    return state & 0x7FFFFFFFu;
}

// NEAR: loop tail keeps addiu a0 before bnez with a nop in its slot; ours fills the slot, so the beqz target is one word short

s32 func_001F6F00(s32* dst, const s32* src, u32 bytes)
{
    u32 n = bytes >> 2;
    u32 i = 0;
    if (n != 0) {
        do {
            s32 v = *src;
            i++;
            src++;
            *dst++ = v;
        } while (i < n);
    }
    return 0;
}

// NEAR: retail saves ra with sd and has no float spills (ours spills $f12-$f18 for the variadic wrapper, 72 vs 56 bytes); ap offset matches

struct Out_1F7B50;
s32 func_001F7588(Out_1F7B50* out, void* ap);

s32 func_001F7B50(Out_1F7B50* out, ...)
{
    void* ap = (char*)__builtin_next_arg(out) - 56;
    return func_001F7588(out, ap);
}

// NEAR: frame layout and a1..a7 spill match; ours adds swc1 spills of f12..f18 (varargs floats) and saves s0/s1/ra with sq instead of sd

typedef void (*PutChar_1F7588)(s32 c);
extern PutChar_1F7588 D_00277130;
void func_001F72A8(s32 c);
s32 func_001F7588(void* self, void* ap);

s32 func_001F7B88(void* self, ...)
{
    void* ap = (char*)__builtin_next_arg(self) - 56;
    PutChar_1F7588 saved = D_00277130;
    D_00277130 = func_001F72A8;
    s32 r = func_001F7588(self, ap);
    D_00277130 = saved;
    return r;
}

// NEAR: retail saves $ra with sd (Sony 2.9-ee-991111 library code, 0x1F59C4 on); the default compiler saves it with sq. Nothing else differs.

void func_001FA468();
extern u32 D_00277134;

void func_001F7D88() { func_001FA468(); D_00277134 = 0; }

// NEAR: body EXACT; only the save/restore ops differ: retail sd/ld, default flags give sq/lq

typedef void (*Fn_1F7EA8)(s32 arg);
struct Node_1F7EA8 {
    s32 f0;
    u8 pad4[4];
    s32 f8;
    u8 pad12[8];
    s32 f14;
    s32 f18;
    Fn_1F7EA8 f1C;
    s32 f20;
    s32 f24;
};
struct Obj_1F7EA8 { u8 pad[0x1C]; Node_1F7EA8* node; s32 tag; s32 v24; s32 v28; s32 v2C; };
struct Ref_1F7EA8;
void func_001F6B50(Ref_1F7EA8* a);
void func_001F7E58(Ref_1F7EA8* a);

void func_001F7EA8(Obj_1F7EA8* obj) {
    Node_1F7EA8* s0;
    u32 tag = obj->tag;
    if (tag == 0x8000000A) goto call_path;
    if (tag > 0x8000000A) {
        s0 = obj->node;
        goto after;
    }
    if (tag == 0x80000009) goto set_fields;
    s0 = obj->node;
    goto after;
call_path:
    s0 = obj->node;
    if (s0->f1C != 0) {
        s0->f1C(s0->f20);
        s0 = obj->node;
    }
    goto after;
set_fields:
    s0 = obj->node;
    s0->f24 = obj->v24;
    s0->f14 = obj->v28;
    s0->f18 = obj->v2C;
after:
    s32 a0 = s0->f8;
    if (a0 >= 0) func_001F6B50((Ref_1F7EA8*)a0);
    func_001F7E58((Ref_1F7EA8*)s0->f0);
    s0->f0 = 0;
}

struct Ctx_1F70F8 { s32 f0; void* f4; void* f8; s32 fC; void* f10; s32 f14; };
struct Init_1F70F8 { s32 a; s32 b; s32 c; };
struct Blk_1F70F8 { s32 a; s32 b; };
struct Frame_1F70F8 { Ctx_1F70F8 ctx; u8 pad[0x18]; Init_1F70F8 init; u8 pad2[0x14]; };

s32 D_00277128 = 0;
extern s32 D_00625B70;
extern Blk_1F70F8 D_00625B78;
extern u8 D_00625770[];
extern u8 D_002832F0[];

s32 func_001F6B20(Init_1F70F8* p);
s32 func_001F6A10(Ctx_1F70F8* p);
void func_001F6B30(s32 h);
void func_001F6A20(s32 h, Blk_1F70F8* b);
s32 func_001F6A90(void);
void func_001F6A50(s32 h, s32 v);
void func_001F7020(void);

s32 func_001F70F8(void)
{
    Frame_1F70F8 f;
    if (D_00277128 > 0) {
        return -1;
    }
    f.init.c = 0;
    f.init.b = 0xFF;
    D_00625B70 = func_001F6B20(&f.init);
    if (D_00625B70 < 0) {
        return -1;
    }
    f.ctx.f4 = (void*)func_001F7020;
    f.ctx.f8 = D_00625770;
    f.ctx.fC = 0x400;
    f.ctx.f10 = D_002832F0;
    f.ctx.f14 = 0;
    D_00277128 = func_001F6A10(&f.ctx);
    if (D_00277128 < 0) {
        func_001F6B30(D_00625B70);
        return -1;
    }
    D_00625B78.a = 0;
    D_00625B78.b = 0;
    func_001F6A20(D_00277128, &D_00625B78);
    func_001F6A50(func_001F6A90(), 1);
    return D_00277128;
}

struct Buf_1F72A8;
void func_001FA140(Buf_1F72A8* b);
extern u8 D_00625F80[];
s32 D_0027712C;

void func_001F72A8(s32 c)
{
    s32 pos = D_0027712C;
    if (pos >= 0x7E) {
        D_0027712C = 0;
        D_00625F80[0x7F] = 0;
        func_001FA140((Buf_1F72A8*)D_00625F80);
        pos = D_0027712C;
    }
    if (c == 0xA) {
        D_0027712C = 0;
        D_00625F80[pos] = (u8)c;
        D_00625F80[pos + 1] = 0;
        func_001FA140((Buf_1F72A8*)D_00625F80);
        return;
    }
    D_0027712C = pos + 1;
    D_00625F80[pos] = (u8)c;
}

struct Ring_001F7E78 {
    u8 pad_00[0x14];
    s32 base;
    s32 count;
    u8 pad_1c[0x08];
    s32 cursor;
};

s32 func_001F7E78(Ring_001F7E78* r)
{
    s32 index = r->cursor % r->count;
    s32 off = index << 6;
    r->cursor = index + 1;
    return r->base + off;
}

// A small formatter: %c %d %u %o %x %s %e %f, the length modifiers l and h and a
// zero-padded width of one or two digits, written one character at a time through
// the output hook. Arguments come from 8-byte slots.

typedef void (*PutChar_1F7588)(s32 c);
extern PutChar_1F7588 D_00277130;

void func_001F7420(double value);

#define NEXT_ARG_1F7588(ap, T) (ap += 8, *(T*)(ap - 8))

void func_001F7588(const char* fmt, char* ap)
{
    char buf[32];
    char* p;
    u64 val;
    char* pad;
    s32 mod;
    s32 width;
    char c;

    for (; *fmt; fmt++)
    {
        pad = 0;
        mod = 0;
        if (*fmt == '%')
        {
        next:
            fmt++;
            switch (*fmt)
            {
            case '0':
                width = fmt[1] - '0';
                c = fmt[2];
                if ((u8)width < 10)
                {
                    if ((u32)(c - '0') < 10)
                    {
                        width = width * 10 + (c - '0');
                        if (width >= 32)
                        {
                            width = 31;
                        }
                        fmt += 2;
                    }
                    else
                    {
                        fmt += 1;
                    }
                    pad = &buf[31 - width];
                    for (; width > 0; width--)
                    {
                        buf[31 - width] = '0';
                    }
                }
                goto next;
            case 'l':
                mod = 'l';
                goto next;
            case 'h':
                mod = 'h';
                goto next;
            case 'o':
                if (mod == 'l')
                {
                    val = NEXT_ARG_1F7588(ap, u64);
                }
                else if (mod == 'h')
                {
                    val = NEXT_ARG_1F7588(ap, u16);
                }
                else
                {
                    val = NEXT_ARG_1F7588(ap, u32);
                }
                p = &buf[31];
                *p = 0;
                if (val == 0)
                {
                    *--p = '0';
                }
                else
                {
                    while (val)
                    {
                        *--p = (val & 7) + '0';
                        val >>= 3;
                    }
                }
                if (pad && pad < p)
                {
                    p = pad;
                }
                while (*p)
                {
                    D_00277130(*p++);
                }
                break;
            case 'x':
                if (mod == 'l')
                {
                    val = NEXT_ARG_1F7588(ap, u64);
                }
                else if (mod == 'h')
                {
                    val = NEXT_ARG_1F7588(ap, u16);
                }
                else
                {
                    val = NEXT_ARG_1F7588(ap, u32);
                }
                p = &buf[31];
                *p = 0;
                if (val == 0)
                {
                    *--p = '0';
                }
                else
                {
                    while (val)
                    {
                        u64 digit = val & 15;
                        if (digit < 10)
                        {
                            *--p = digit + '0';
                        }
                        else
                        {
                            *--p = digit + 'a' - 10;
                        }
                        val >>= 4;
                    }
                }
                if (pad && pad < p)
                {
                    p = pad;
                }
                while (*p)
                {
                    D_00277130(*p++);
                }
                break;
            case 'd':
                if (mod == 'l')
                {
                    val = NEXT_ARG_1F7588(ap, s64);
                }
                else if (mod == 'h')
                {
                    val = NEXT_ARG_1F7588(ap, s16);
                }
                else
                {
                    val = NEXT_ARG_1F7588(ap, s32);
                }
                p = &buf[31];
                *p = 0;
                if (val == 0)
                {
                    *--p = '0';
                }
                else
                {
                    if ((s64)val < 0)
                    {
                        val = -val;
                        D_00277130('-');
                    }
                    while (val)
                    {
                        *--p = (s64)val % 10 + '0';
                        val = (s64)val / 10;
                    }
                }
                if (pad && pad < p)
                {
                    p = pad;
                }
                while (*p)
                {
                    D_00277130(*p++);
                }
                break;
            case 'u':
                if (mod == 'l')
                {
                    val = NEXT_ARG_1F7588(ap, u64);
                }
                else if (mod == 'h')
                {
                    val = NEXT_ARG_1F7588(ap, u16);
                }
                else
                {
                    val = NEXT_ARG_1F7588(ap, u32);
                }
                p = &buf[31];
                *p = 0;
                if (val == 0)
                {
                    *--p = '0';
                }
                else
                {
                    while (val)
                    {
                        *--p = val % 10 + '0';
                        val /= 10;
                    }
                }
                if (pad && pad < p)
                {
                    p = pad;
                }
                while (*p)
                {
                    D_00277130(*p++);
                }
                break;
            case 'e':
            case 'f':
            {
                f32 f = NEXT_ARG_1F7588(ap, f32);
                if (f == 0.0f)
                {
                    D_00277130('0');
                    }
                else
                {
                        func_001F7420(f);
                }
                break;
            }
            case 's':
            {
                char* str = NEXT_ARG_1F7588(ap, char*);
                if (*str == 0)
                {
                    D_00277130('(');
                    D_00277130('n');
                    D_00277130('u');
                    D_00277130('l');
                    D_00277130('l');
                    D_00277130(')');
                }
                else
                {
                    p = str;
                    while (*p)
                    {
                        D_00277130(*p);
                        p++;
                    }
                }
                break;
            }
            case 'c':
                val = NEXT_ARG_1F7588(ap, char);
                D_00277130(val);
                break;
            }
        }
        else
        {
            D_00277130(*fmt);
        }
    }
}

void func_001F7270(s32 c);
void func_001F7358(s32 c)
{
    if (c == 10) {
        func_001F7270(13);
        func_001F7270(10);
    } else {
        func_001F7270(c);
    }
}

typedef void (*PutChar_1F7420)(s32 c);
PutChar_1F7420 D_00277130 = func_001F7358;  // where formatted output sends each character

s32 func_001FD308(double a, double b);
double func_001FCD78(double a, double b);
double func_001FCDE0(double a, double b);
double func_001FD088(double a, double b);
double func_001FB528(double a);
s32 func_001F7390(double a);
extern const char D_0024E9B0[];
extern const char D_0024E9B8[];
extern const char D_0024E9C0[];
s32 func_001F7B50(const char* fmt, ...);

void func_001F7420(double value)
{
    s32 exp10 = 0;
    if (func_001FD308(value, 0.0) < 0) {
        value = func_001FCD78(0.0, value);
        D_00277130('-');
    }
    if (func_001FD308(value, 0.1) < 0) {
        while (func_001FD308(value, 0.1) < 0) {
            value = func_001FCDE0(value, 10.0);
            exp10--;
        }
    } else if (func_001FD308(value, 1.0) >= 0) {
        while (func_001FD308(value, 1.0) >= 0) {
            exp10++;
            value = func_001FD088(value, 10.0);
        }
    }
    s32 digits = func_001F7390(func_001FB528(func_001FCDE0(value, 1000000.0)));
    func_001F7B50(D_0024E9B0, digits);
    if (exp10 >= 0)
        func_001F7B50(D_0024E9B8, exp10);
    else
        func_001F7B50(D_0024E9C0, exp10);
}

struct Ring_1F7F60;
struct Msg_1F7F60 { u8 p0[0x14]; s32 f14; u8 p18[4]; s32 f1C; u32 f20; };
struct Src_1F7F60 { u8 p0[0x14]; s32 f14; u8 p18[4]; s32 f1C; s32 f20; s32 f24; s32 f28; };
struct Ctx_1FA670;

Msg_1F7F60* func_001F7E78(Ring_1F7F60* r);
s32 func_001FA670(Ctx_1FA670* a, Msg_1F7F60* b, s32 c, s32 d, s32 e, s32 f);

void func_001F7F60(Src_1F7F60* src, Ring_1F7F60* ring)
{
    Msg_1F7F60* m = func_001F7E78(ring);
    s32 a = src->f14;
    s32 b = src->f1C;
    m->f14 = a;
    m->f1C = b;
    m->f20 = 0x8000000C;
    func_001FA670((Ctx_1FA670*)0x80000008, m, 0x40, src->f20, src->f24, src->f28);
}

struct Entry_1F7020 { u8 kind; u8 arg; };
struct Queue_1F7020 { u32 head; u32 pad; Entry_1F7020 e[0x200]; };

extern s32 D_00625B70;
s32 func_001F6B60(s32 h);
void func_001F6A70(s32 v);
void func_001F6AC0(s32 v);
void func_001F6AF0(s32 v);
extern const char D_0024E988[];
s32 func_001F7B50(const char* fmt, ...);

void func_001F7020(Queue_1F7020* q)
{
    for (;;) {
        func_001F6B60(D_00625B70);
        u32 i = q->head & 0x1FF;
        q->head = i + 1;
        switch (q->e[i].kind) {
        case 0:
            func_001F6AC0(q->e[i].arg);
            break;
        case 1:
            func_001F6A70(q->e[i].arg);
            break;
        case 2:
            func_001F6AF0(q->e[i].arg);
            break;
        default:
            func_001F7B50(D_0024E988);
            break;
        }
    }
}

char* func_001F6880(char* s, char* t)
{
    int i;
    if (*s == 0) {
        if (*t) {
            return 0;
        }
        return s;
    }
    while (*s) {
        i = 0;
        while (1) {
            if (t[i] == 0) {
                return s;
            }
            if (t[i] != s[i]) {
                break;
            }
            i++;
        }
        s++;
    }
    return 0;
}

struct Item_1F7DB0 { u8 pad00[0x10]; u32 flags; Item_1F7DB0* next; s32 state; };
struct Owner_1F7DB0 { s32 index; Item_1F7DB0* items; s32 count; };
s32 func_001F9D60(Owner_1F7DB0*);
void func_001F9DA8(void);

Item_1F7DB0* func_001F7DB0(Owner_1F7DB0* self)
{
    func_001F9D60(self);
    s32 count = self->count;
    s32 index = 0;
    Item_1F7DB0* item = self->items;
    if (count > 0) {
        do {
            if ((item->flags & 1) == 0) {
                item->flags = (index << 16) | 5;
                s32 state;
                self->index++;
                if (self->index == 1) {
                    state = self->index++;
                } else {
                    state = self->index;
                }
                item->next = item;
                item->state = state;
                func_001F9DA8();
                return item;
            }
            index++;
            item = (Item_1F7DB0*)((u8*)item + 0x40);
        } while (index < count);
    }
    func_001F9DA8();
    return 0;
}

struct Slot_1F6F48 {
    s32 key;
    void* value;
};

extern Slot_1F6F48 D_002770E8[];
extern u32 D_00276980[];
extern u32 D_002770C0[];
void func_001F6EE0(s32 a, s32 b);
void func_001F6EF0(u32 a, void* b, s32 c);
void func_001F6C20(s32 a);
s32 func_001F6F38(s32 key);

void func_001F6F48(void)
{
    if ((*(volatile u32*)0x10001810 & 0x100) != 0) {
        return;
    }
    func_001F6EE0(D_002770E8[0].key, (s32)D_002770E8[0].value);
    func_001F6EF0(0x80076000, D_00276980, 0x740);
    func_001F6EF0(0x82000, D_002770C0, 0x28);
    func_001F6C20(0);
    func_001F6C20(2);
    func_001F6EE0(D_002770E8[1].key, (s32)D_002770E8[1].value);
    for (u32 i = 2; i < 8; i++) {
        func_001F6EE0(D_002770E8[i].key, func_001F6F38(D_002770E8[i].key));
    }
}

Slot_1F6F48 D_002770E8[8] = {
    { 0x5A, (void*)func_001F6F00 },
    { 0x5B, (void*)0x80076000 },
    { 0xFC, 0 },
    { 0xFE, 0 },
    { 0xFD, 0 },
    { 0xFF, 0 },
    { 0x12C, 0 },
    { 0x8, 0 },
};

u32 D_00276980[464] = {
    0x3C028007, 0x0000282D, 0x24436710, 0x00000000, 0x8C620000, 0x14820003, 0x24A50001, 0x03E00008,
    0x8C620004, 0x2CA20006, 0x1440FFF9, 0x24630008, 0x03E00008, 0x0000102D, 0x00A4202A, 0x10800003,
    0x3C020001, 0x03E00008, 0x00A21025, 0x03E00008, 0x00A0102D, 0x00000000, 0x27BDFF80, 0xFFB30030,
    0x3C138007, 0xFFB60060, 0xFFB50050, 0x0080B02D, 0xFFB00000, 0x00A0A82D, 0x8E626700, 0x0000802D,
    0xFFBF0070, 0xFFB40040, 0xFFB20020, 0x18400028, 0xFFB10010, 0x3C148007, 0x24120014, 0x00000000,
    0x26916740, 0x02121018, 0x02C0202D, 0x00511021, 0x0C01D80E, 0x94450000, 0x02A2102A, 0x10400018,
    0x8E626700, 0x2444FFFF, 0x0090182A, 0x14600018, 0x00921018, 0x00511821, 0x68650007, 0x6C650000,
    0x6866000F, 0x6C660008, 0x8C670010, 0xB065001B, 0xB4650014, 0xB0660023, 0xB466001C, 0xAC670024,
    0x2484FFFF, 0x2463FFEC, 0x0090102A, 0x00000000, 0x1040FFF1, 0x00000000, 0x10000006, 0x0200102D,
    0x26100001, 0x0202102A, 0x1440FFDD, 0x24120014, 0x0200102D, 0xDFBF0070, 0xDFB60060, 0xDFB50050,
    0xDFB40040, 0xDFB30030, 0xDFB20020, 0xDFB10010, 0xDFB00000, 0x03E00008, 0x27BD0080, 0x00000000,
    0x27BDFF70, 0x3C02B000, 0xFFB70070, 0x34421800, 0xFFB60060, 0x00C0B82D, 0xFFB50050, 0x00A0B02D,
    0xFFB30030, 0x3C158007, 0xFFBF0080, 0x3093FFFF, 0xFFB20020, 0xFFB10010, 0xFFB00000, 0xFFB40040,
    0x8EA36700, 0x8C540000, 0x28630040, 0x14600008, 0x02749821, 0x1000002E, 0x2402FFFF, 0x0060902D,
    0x00621014, 0x00821025, 0x1000000D, 0xFCA26708, 0x3C058007, 0x0000182D, 0xDCA46708, 0x00641016,
    0x30420001, 0x1040FFF5, 0x24020001, 0x24630001, 0x28620040, 0x1440FFFA, 0x00641016, 0x2412FFFF,
    0x0640001B, 0x0240102D, 0x0380882D, 0x0260282D, 0x0C01D816, 0x0280202D, 0x24040014, 0x3C088007,
    0x00441018, 0x25036740, 0x8EA56700, 0x24700004, 0x24A50001, 0x00432021, 0x00623821, 0x00508021,
    0xA4940002, 0xA4930000, 0x00E0302D, 0xAE120000, 0x00C0182D, 0xACF10010, 0x95046740, 0xACD60008,
    0xAC77000C, 0x0C01D918, 0xAEA56700, 0x8E020000, 0xDFBF0080, 0xDFB70070, 0xDFB60060, 0xDFB50050,
    0xDFB40040, 0xDFB30030, 0xDFB20020, 0xDFB10010, 0xDFB00000, 0x03E00008, 0x27BD0090, 0x00000000,
    0x27BDFFD0, 0x3C0C8007, 0xFFB10010, 0x0080682D, 0x8D826700, 0x0180882D, 0xFFBF0020, 0x2406FFFF,
    0x18400058, 0xFFB00000, 0x18400056, 0x0000402D, 0x3C0B8007, 0x24030014, 0x25656740, 0x01032018,
    0x00A41021, 0x8C430004, 0x15A3004A, 0x8D826700, 0x3C03B000, 0x00852021, 0x34631820, 0x94850000,
    0x8C620000, 0x14A20008, 0x24030014, 0x3C021000, 0x3442F000, 0x8C430000, 0x30631000, 0x14600043,
    0x2402FFFF, 0x24030014, 0x8D896700, 0x01031818, 0x25646740, 0x2522FFFF, 0x0100382D, 0x0102102A,
    0x00641821, 0x10400019, 0x94700002, 0x3C0A8007, 0x24E30001, 0x24050014, 0x00651018, 0x00E52018,
    0x25666740, 0x0060382D, 0x00462821, 0x00862021, 0x2522FFFF, 0x68A30007, 0x6CA30000, 0x68A6000F,
    0x6CA60008, 0x8CAE0010, 0xB0830007, 0xB4830000, 0xB086000F, 0xB4860008, 0x00E2102A, 0x1440FFEC,
    0xAC8E0010, 0x10000003, 0x24020001, 0x3C0A8007, 0x24020001, 0x8D846700, 0xDD436708, 0x01A21014,
    0x00021027, 0x2484FFFF, 0x00621824, 0xAD846700, 0x15000003, 0xFD436708, 0x0C01D918, 0x95646740,
    0x8E226700, 0x14400004, 0x24030083, 0x3C02B000, 0x34421810, 0xAC430000, 0x3C02B000, 0x0200202D,
    0x34421800, 0x0C01D80E, 0x8C450000, 0x10000005, 0x00503023, 0x25080001, 0x0102102A, 0x1440FFAE,
    0x24030014, 0x0000000F, 0x00C0102D, 0xDFBF0020, 0xDFB10010, 0xDFB00000, 0x03E00008, 0x27BD0030,
    0x27BDFFF0, 0xFFBF0000, 0x0C01D858, 0x3084FFFF, 0x0000000F, 0xDFBF0000, 0x03E00008, 0x27BD0010,
    0x3C02B000, 0x34421820, 0xAC440000, 0x0000000F, 0x3C02B000, 0x24030583, 0x34421810, 0x03E00008,
    0xAC430000, 0x00000000, 0x27BDFF50, 0x0000402D, 0xFFBF00A0, 0xFFB70090, 0xFFB60080, 0xFFB50070,
    0xFFB40060, 0xFFB30050, 0xFFB20040, 0xFFB10030, 0xFFB00020, 0x3C118007, 0x3C128007, 0x00000000,
    0x8E226700, 0x0102102A, 0x1040000A, 0x24030014, 0x26446740, 0x01031818, 0x96456740, 0x00641821,
    0x94620000, 0x10A2FFF6, 0x25080001, 0x0C01D918, 0x0040202D, 0x3C028007, 0x0220B02D, 0x24546740,
    0x24130014, 0x3C158007, 0x10000004, 0x24170001, 0x96426740, 0x1462003E, 0x8E226700, 0x8EC26700,
    0x0000402D, 0x26466740, 0x68C30007, 0x6CC30000, 0x68C4000F, 0x6CC40008, 0x8CC50010, 0xB3A30007,
    0xB7A30000, 0xB3A4000F, 0xB7A40008, 0xAFA50010, 0x2442FFFF, 0x1840001A, 0xAEC26700, 0x8E296700,
    0x8FAA0010, 0x8FA60004, 0x97A70000, 0x00000000, 0x01131818, 0x25020001, 0x0040402D, 0x00742821,
    0x00531818, 0x00742021, 0x688B0007, 0x6C8B0000, 0x688C000F, 0x6C8C0008, 0x8C8D0010, 0xB0AB0007,
    0xB4AB0000, 0xB0AC000F, 0xB4AC0008, 0x0109182A, 0x1460FFEF, 0xACAD0010, 0x10000004, 0x00000000,
    0x8FAA0010, 0x8FA60004, 0x97A70000, 0x0380802D, 0x0140E02D, 0xDEA36708, 0x00D71014, 0x00021027,
    0x3C040008, 0x00621824, 0x8FA50008, 0x8FA8000C, 0x34842000, 0x0C01D9A0, 0xFEA36708, 0x0200E02D,
    0x8E226700, 0x1C40FFC2, 0x97A30000, 0x8E226700, 0x18400005, 0x24030483, 0x0C01D918, 0x96446740,
    0x10000004, 0x00000000, 0x3C02B000, 0x34421810, 0xAC430000, 0x0000000F, 0x42000038, 0xDFBF00A0,
    0xDFB70090, 0xDFB60080, 0xDFB50070, 0xDFB40060, 0xDFB30050, 0xDFB20040, 0xDFB10030, 0xDFB00020,
    0x03E00008, 0x27BD00B0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x3C1A8007, 0xAF5F6C40, 0x3C1A8007, 0xAF5D6C50, 0x40847000, 0x0000040F, 0x00A0182D, 0x00C0202D,
    0x00E0282D, 0x0100302D, 0x401A6000, 0x375A0012, 0x409A6000, 0x0000040F, 0x42000018, 0x00000000,
    0x40016000, 0x241AFFE4, 0x003A0824, 0x40816000, 0x0000040F, 0x3C1A8007, 0x8F5F6C40, 0x3C1A8007,
    0x03E00008, 0x8F5D6C50, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FC, 0x80076440, 0x000000FE, 0x80076440,
    0x000000FD, 0x800762A0, 0x000000FF, 0x800762A0, 0x0000012C, 0x80076488, 0x00000008, 0x800766C0,
};
u32 D_002770C0[10] = {
    0x3C1D0008, 0x0060F809, 0x27BD1FC0, 0x2403FFF8, 0x0000000C, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000,
};

extern const char D_0024E988[40] = "## internel error in libkernl.a!\n";
extern const char D_0024E9B0[8] = "0.%d";
extern const char D_0024E9B8[8] = "e+%d";
extern const char D_0024E9C0[8] = "e%d";

// Sorts n elements of size bytes each in place with a three-way-partition quicksort:
// insertion sort below seven elements, a median of three (of nine above forty) as the
// pivot, elements equal to it gathered at both ends and moved to the middle afterwards.
typedef s32 (*Compare_1F5CD0)(const void* x, const void* y);

struct Sort_1F5CD0 {
    // Exchanges count bytes at x and y, by 64-bit words when kind allows it.
    static inline void Exchange(char* x, char* y, s32 count, s32 kind)
    {
        if (kind <= 1) {
            s64 i = count / sizeof(s64);
            s64* p = (s64*)x;
            s64* q = (s64*)y;
            do {
                s64 t = *p;
                *p++ = *q;
                *q++ = t;
            } while (--i > 0);
        } else {
            s64 i = count / sizeof(char);
            char* p = x;
            char* q = y;
            do {
                char t = *p;
                *p++ = *q;
                *q++ = t;
            } while (--i > 0);
        }
    }

    // The middle one of three elements.
    static inline char* Median(char* x, char* y, char* z, Compare_1F5CD0 compare)
    {
        return compare(x, y) < 0
            ? (compare(y, z) < 0 ? y : (compare(x, z) < 0 ? z : x))
            : (compare(y, z) > 0 ? y : (compare(x, z) < 0 ? x : z));
    }
};

#define SWAP_1F5CD0(x, y) \
    if (kind == 0) { \
        s64 t = *(s64*)(x); \
        *(s64*)(x) = *(s64*)(y); \
        *(s64*)(y) = t; \
    } else \
        Sort_1F5CD0::Exchange(x, y, size, kind)

#define BLOCKSWAP_1F5CD0(x, y, count) \
    if ((count) > 0) Sort_1F5CD0::Exchange(x, y, count, kind)

void func_001F5CD0(void* base, u32 n, u32 size, Compare_1F5CD0 compare)
{
    char *pa, *pb, *pc, *pd, *pl, *pm, *pn;
    s32 d, r, kind, swapped;

again:
    kind = ((u32)base % sizeof(s64)) || size % sizeof(s64) ? 2 : size == sizeof(s64) ? 0 : 1;
    swapped = 0;
    if (n < 7) {
        for (pm = (char*)base + size; pm < (char*)base + n * size; pm += size) {
            for (pl = pm; pl > (char*)base && compare(pl - size, pl) > 0; pl -= size) {
                SWAP_1F5CD0(pl, pl - size);
            }
        }
        return;
    }
    pm = (char*)base + (n / 2) * size;
    if (n > 7) {
        pl = (char*)base;
        pn = (char*)base + (n - 1) * size;
        if (n > 40) {
            d = (n / 8) * size;
            pl = Sort_1F5CD0::Median(pl, pl + d, pl + 2 * d, compare);
            pm = Sort_1F5CD0::Median(pm - d, pm, pm + d, compare);
            pn = Sort_1F5CD0::Median(pn - 2 * d, pn - d, pn, compare);
        }
        pm = Sort_1F5CD0::Median(pl, pm, pn, compare);
    }
    SWAP_1F5CD0((char*)base, pm);
    pa = pb = (char*)base + size;
    pc = pd = (char*)base + (n - 1) * size;
    for (;;) {
        while (pb <= pc && (r = compare(pb, base)) <= 0) {
            if (r == 0) {
                swapped = 1;
                SWAP_1F5CD0(pa, pb);
                pa += size;
            }
            pb += size;
        }
        while (pb <= pc && (r = compare(pc, base)) >= 0) {
            if (r == 0) {
                swapped = 1;
                SWAP_1F5CD0(pc, pd);
                pd -= size;
            }
            pc -= size;
        }
        if (pb > pc) {
            break;
        }
        SWAP_1F5CD0(pb, pc);
        swapped = 1;
        pb += size;
        pc -= size;
    }
    if (swapped == 0) {
        for (pm = (char*)base + size; pm < (char*)base + n * size; pm += size) {
            for (pl = pm; pl > (char*)base && compare(pl - size, pl) > 0; pl -= size) {
                SWAP_1F5CD0(pl, pl - size);
            }
        }
        return;
    }
    pn = (char*)base + n * size;
    r = pa - (char*)base < pb - pa ? pa - (char*)base : pb - pa;
    BLOCKSWAP_1F5CD0((char*)base, pb - r, r);
    if (pd - pc < pn - pd - (s32)size) {
        r = pd - pc;
    } else {
        r = pn - pd - (s32)size;
    }
    BLOCKSWAP_1F5CD0(pb, pn - r, r);
    if ((u32)(r = pb - pa) > size) {
        func_001F5CD0(base, r / size, size, compare);
    }
    if ((u32)(r = pd - pc) > size) {
        base = pn - r;
        n = r / size;
        goto again;
    }
}
