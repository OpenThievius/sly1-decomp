// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

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

extern const char D_0024E9B0[8] = "0.%d";
extern const char D_0024E9B8[8] = "e+%d";
extern const char D_0024E9C0[8] = "e%d";
