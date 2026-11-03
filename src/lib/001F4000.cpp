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

extern s32 D_00277128;
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
