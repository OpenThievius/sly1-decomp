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

static u8 g_outputLine[0x80];
s32 g_outputLineLength = 0;

s32 WriteSerialChar(s32 c)
{
    while (*(volatile u32*)0x1000F130 & 0x8000) {
    }
    *(volatile u8*)0x1000F180 = c;
    return c;
}

void PrintToDebugConsole(Buf_1F72A8* b);

void BufferOutputChar(s32 c)
{
    s32 pos = g_outputLineLength;
    if (pos >= 0x7E) {
        g_outputLineLength = 0;
        g_outputLine[0x7F] = 0;
        PrintToDebugConsole((Buf_1F72A8*)g_outputLine);
        pos = g_outputLineLength;
    }
    if (c == 0xA) {
        g_outputLineLength = 0;
        g_outputLine[pos] = (u8)c;
        g_outputLine[pos + 1] = 0;
        PrintToDebugConsole((Buf_1F72A8*)g_outputLine);
        return;
    }
    g_outputLineLength = pos + 1;
    g_outputLine[pos] = (u8)c;
}

void WriteConsoleChar(s32 c)
{
    if (c == 10) {
        WriteSerialChar(13);
        WriteSerialChar(10);
    } else {
        WriteSerialChar(c);
    }
}

PutChar_1F7588 g_outputHook = WriteConsoleChar;  // where formatted output sends each character

s32 func_001F7390(double a)
{
    union {
        double d;
        u64 u;
    } v;
    u64 m;
    s64 e;

    v.d = a;
    m = v.u;
    e = (m << 1) >> 53;
    e -= 0x433;
    if (e < -0x35) {
        return 0;
    }
    if (e >= 13) {
        return 9999;
    }
    m = (m << 12) >> 12;
    m |= (u64)1 << 52;
    if (e < 0) {
        e = -e;
        m >>= e - 2;
        if ((m & 3) == 3) {
            m = (m >> 2) + 1;
        } else {
            m >>= 2;
        }
    } else {
        m <<= e;
    }
    return m;
}

s32 func_001FD308(double a, double b);
double func_001FCD78(double a, double b);
double func_001FCDE0(double a, double b);
double DivideDoubles(double a, double b);
double ConvertDoubleToU64(double a);
s32 func_001F7390(double a);
void PrintToOutputHook(const char* fmt, ...);

void FormatExponent(double value)
{
    s32 exp10 = 0;
    if (func_001FD308(value, 0.0) < 0) {
        value = func_001FCD78(0.0, value);
        g_outputHook('-');
    }
    if (func_001FD308(value, 0.1) < 0) {
        while (func_001FD308(value, 0.1) < 0) {
            value = func_001FCDE0(value, 10.0);
            exp10--;
        }
    } else if (func_001FD308(value, 1.0) >= 0) {
        while (func_001FD308(value, 1.0) >= 0) {
            exp10++;
            value = DivideDoubles(value, 10.0);
        }
    }
    s32 digits = func_001F7390(ConvertDoubleToU64(func_001FCDE0(value, 1000000.0)));
    PrintToOutputHook("0.%d", digits);
    if (exp10 >= 0)
        PrintToOutputHook("e+%d", exp10);
    else
        PrintToOutputHook("e%d", exp10);
}

// A small formatter: %c %d %u %o %x %s %e %f, the length modifiers l and h and a
// zero-padded width of one or two digits, written one character at a time through
// the output hook. Arguments come from 8-byte slots.

#define NEXT_ARG_1F7588(ap, T) (ap += 8, *(T*)(ap - 8))

void FormatOutput(const char* fmt, char* ap)
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
                    g_outputHook(*p++);
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
                    g_outputHook(*p++);
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
                        g_outputHook('-');
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
                    g_outputHook(*p++);
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
                    g_outputHook(*p++);
                }
                break;
            case 'e':
            case 'f':
            {
                f32 f = NEXT_ARG_1F7588(ap, f32);
                if (f == 0.0f)
                {
                    g_outputHook('0');
                    }
                else
                {
                        FormatExponent(f);
                }
                break;
            }
            case 's':
            {
                char* str = NEXT_ARG_1F7588(ap, char*);
                if (*str == 0)
                {
                    g_outputHook('(');
                    g_outputHook('n');
                    g_outputHook('u');
                    g_outputHook('l');
                    g_outputHook('l');
                    g_outputHook(')');
                }
                else
                {
                    p = str;
                    while (*p)
                    {
                        g_outputHook(*p);
                        p++;
                    }
                }
                break;
            }
            case 'c':
                val = NEXT_ARG_1F7588(ap, char);
                g_outputHook(val);
                break;
            }
        }
        else
        {
            g_outputHook(*fmt);
        }
    }
}

void PrintToOutputHook(const char* fmt, ...)
{
    char* ap = (char*)__builtin_next_arg(fmt) - 56;
    FormatOutput(fmt, ap);
}

void BufferOutputChar(s32 c);

void PrintBuffered(const char* fmt, ...)
{
    char* ap = (char*)__builtin_next_arg(fmt) - 56;
    PutChar_1F7588 saved = g_outputHook;
    g_outputHook = BufferOutputChar;
    FormatOutput(fmt, ap);
    g_outputHook = saved;
}
