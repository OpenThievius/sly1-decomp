// SPDX-License-Identifier: AGPL-3.0-or-later
// The kernel library's formatted output, its own object from 0x1F7270 to 0x1F7BE8, built whole
// (config/us/files.tsv): the serial port's character output func_001F7270 (it waits on the
// status word at 0x1000F130 and writes to 0x1000F180), func_001F72A8, which gathers characters
// in the line D_00625F80 and hands each full line to func_001FA140, func_001F7358, which writes
// a newline as a carriage return and a line feed, the output hook D_00277130 (func_001F7358 by
// default), func_001F7390 and func_001F7420, which write a double in the form 0.ddddddde+n,
// the formatter func_001F7588, and the two entries func_001F7B50 (through the hook) and
// func_001F7B88 (through func_001F72A8 for the call). Its .rodata is the three formats, the
// constants of func_001F7420 and the formatter's jump table, its .data the line's length
// D_0027712C and the hook, its .bss the line.
#include "common.h"
#include "asm_func.h"

typedef void (*PutChar_1F7588)(s32 c);

struct Buf_1F72A8;

static u8 D_00625F80[0x80];
s32 D_0027712C = 0;

INCLUDE_ASM(func_001F7270);

void func_001FA140(Buf_1F72A8* b);

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

PutChar_1F7588 D_00277130 = func_001F7358;  // where formatted output sends each character

INCLUDE_ASM(func_001F7390);

s32 func_001FD308(double a, double b);
double func_001FCD78(double a, double b);
double func_001FCDE0(double a, double b);
double func_001FD088(double a, double b);
double func_001FB528(double a);
s32 func_001F7390(double a);
void func_001F7B50(const char* fmt, ...);

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
    func_001F7B50("0.%d", digits);
    if (exp10 >= 0)
        func_001F7B50("e+%d", exp10);
    else
        func_001F7B50("e%d", exp10);
}

// A small formatter: %c %d %u %o %x %s %e %f, the length modifiers l and h and a
// zero-padded width of one or two digits, written one character at a time through
// the output hook. Arguments come from 8-byte slots.

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

void func_001F7B50(const char* fmt, ...)
{
    char* ap = (char*)__builtin_next_arg(fmt) - 56;
    func_001F7588(fmt, ap);
}

void func_001F72A8(s32 c);

void func_001F7B88(const char* fmt, ...)
{
    char* ap = (char*)__builtin_next_arg(fmt) - 56;
    PutChar_1F7588 saved = D_00277130;
    D_00277130 = func_001F72A8;
    func_001F7588(fmt, ap);
    D_00277130 = saved;
}
