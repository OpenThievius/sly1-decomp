// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x1E08F8 to 0x1E2420 (its .rodata from 0x24E1C0, its .data from 0x275940): the
// text formatter (ParseFormatSpec to FormatToStringBounded, its digits D_00275940, its jump
// tables and strings), the string functions, the recursive lock and the render thread. It starts
// at an exact edge (commentary_best_time.cpp's end) and could itself be several files. Its end in
// the code is a choice: on_off_object.cpp's .data provably starts at 0x275970 (that file says why);
// this file's .rodata ends with FormatConversionArg's jump table (0x24E4A0), and no function from
// 0x1E1DB8 to 0x1E2420 reads the next file's data, so any function start in that range can begin
// the next file. The cut is at 0x1E2420, after CreateRenderThread, the last reader of this file's
// .data (g_mainAndRenderThreads), where the on-off objects begin. Its name is ours, after the text
// formatter, which holds most of its code.
#include "common.h"
#include "asm_func.h"
#include "on_off_object.h"
#include "collider.h"
#include "world.h"
#include "camera_controller.h"
#include "camera.h"
#include "globals.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "load_progress.h"
#include "output_buffer.h"
#include "game_progress.h"
#include "flag_table.h"
#include "semaphore_params.h"
#include "thread_params.h"
#include "memory_card.h"
#include "screen_element.h"
#include "vu0.h"
#include "fpu.h"
#include "pad_record.h"
#include "ramp_profile.h"
#include "value_range.h"


void* InitStringOutputBuffer(u8* buf, char* dst, s32 cap);
s32 FormatToOutputBuffer(u8* buf, s32 a, s32 b);
void DestroyOutputBuffer(u8* buf, s32 n);



void* FillMemory(void* p, s32 value, s32 size);
s32 NewSemaphore(void* self);







s32 PrintFormattedVa(void* self, void* ap);



// The stack room of an output buffer as the format functions declare one: its header and the
// 0x400 bytes AppendToOutputBuffer fills before it flushes.
struct OutputBufferStorage { u8 bytes[0x420]; };

void* InitStringOutputBuffer(void* stream, char* dst, s32 cap);
s32 FormatToOutputBuffer(void* stream, const char* fmt, void* ap);
void DestroyOutputBuffer(void* stream, s32 mode);



s32 FormatToStringVa(char* dst, const char* fmt, void* ap);



s32 FormatToStringBoundedVa(char* dst, s32 cap, const char* fmt, void* ap);




void* InitOutputBuffer(void* stream, s32 cap);
s32 FormatToOutputBuffer(void* stream, const char* fmt, void* ap);
void DestroyOutputBuffer(void* stream, s32 mode);



s32 GetStringLength(void* p);
void CopyMemory(void* dst, void* src, s32 count);



s32 GetStringLength(void* p);
void CopyMemory(void* dst, void* src, s32 count);





s32 CreateLockSemaphore(s32 a, s32 b);

// A lock one thread may take again (InitRecursiveLock, EnterRecursiveLock, LeaveRecursiveLock):
// how many times its holder took it, the holder's thread id (-1 for none) and the semaphore.
struct RecursiveLock { s32 count; s32 last; void* sema; };



extern void PostSemaphore(void* a);



void* FillMemory(void* p, s32 value, s32 size);

extern u8 D_00275940[0x18];

u64 DivideUnsigned64(u64 value, u64 radix);
s64 RemainderUnsigned64(u64 value, u64 radix);
void CopyMemory(void* dst, void* src, s32 count);




extern s32 GetCurrentThreadId(void);
extern s32 AwaitSemaphore(void* a);



// A conversion of the formatter (func_001E1DB8): func_001E0978 parses it from a '%' on, and
// func_001E1A08 hands it to the writer of its kind (func_001E0CD0 strings, func_001E1028
// integers, func_001E17A8 floats).
struct FormatSpec {
    s32 left;       // 0x00: '-'
    s32 plus;       // 0x04: '+'
    s32 space;      // 0x08: ' '
    s32 alt;        // 0x0C: '#'
    s32 zero;       // 0x10: '0'
    s32 noprec;     // 0x14: the precision given as zero
    s32 width;      // 0x18
    s32 prec;       // 0x1C
    s32 length;     // 0x20: 1 'h', 2 'l' or 'L'
    s32 f24;        // 0x24: a vector's count (3, or 4 for an upper-case letter)
    s32 f28;        // 0x28: a matrix's rows ('v' for one)
    u8 conv;        // 0x2C: the conversion letter, in lower case
    s8 pad2D[3];
    s32 upper;      // 0x30: the letter was upper case
};




// func_001E1DB8's frame: the conversion it parses, then the argument pointer.
struct FormatFrame {
    FormatSpec spec;    // the conversion spec, at sp + 0
    u8 pad34[0x40 - 0x34];
    void* va;           // the argument pointer, at sp + 0x40
    u8 pad44[0xC];
};

void FlushOutputBuffer(OutputBuffer* ctx);
s32 AppendToOutputBuffer(OutputBuffer* ctx, const char* p, s32 n);
char* FindCharInString(const char* s, s32 c);
s32 GetStringLength(const char* s);
s32 ParseFormatSpec(const char* at, FormatSpec* spec, void* va);
void FormatConversionArg(FormatSpec* spec, OutputBuffer* ctx, void* va, const char* at, s32 len);



extern u8 g_charClassFlags[];





struct IntegerArg {
    u64 v;
};








s32 ExtractIntegerSign(FormatSpec* self, IntegerArg* v);
s32 GetStringLength(char* p);
s32 GetConversionRadix(s8 c);
s32 WriteIntegerDigits(char* buf, s32 len, u64 value, u32 radix);
s32 AppendToOutputBuffer(OutputBuffer* sink, const char* p, s32 n);
void UppercaseString(char* p);




void* FillMemory(void* p, s32 value, s32 size);
s32 ParseSignedDecimal(s8* s, s32* out);
extern u8 g_charClassFlags[];






s32 GetStringLength(const char* s);
s32 AppendToOutputBuffer(OutputBuffer* c, const char* s, s32 n);
void FormatStringArg(FormatSpec* sp, OutputBuffer* c, const char* s);
void FormatIntegerArg(FormatSpec* sp, OutputBuffer* c, u64 v);
void FormatFloatArg(FormatSpec* sp, OutputBuffer* c, s64 s);
void FormatFloatArg(FormatSpec* sp, OutputBuffer* c, double value);
s32 FormatFloatDigits(char* buf, s32 n, FormatSpec* sp, double value);
void UppercaseString(char* p);
double ConvertFloatToDouble(f32 f);



struct PaddedOutput : OutputBuffer {
    void Pad(u8 ch, s32 count)
    {
        u8 buf = ch;
        while (count-- > 0) {
            if (AppendToOutputBuffer(this, (const char*)&buf, 1) != 1) {
                break;
            }
        }
    }
};










struct RegDouble { u8 pad; };


f32 Power(f32 a, f32 b);
RegDouble* MultiplyDoubles(RegDouble* self, u64 v);
RegDouble* MultiplyDoubles(RegDouble* self, double v); // soft-float double in a1
RegDouble* TruncateDouble(RegDouble* self);
RegDouble* SubtractDoubles(RegDouble* self, RegDouble* v);
s32 ConvertDoubleToS32(RegDouble* self);




extern u8 D_00275940[];



void* CopyString(char* dst, char* src);
s32 GetStringLength(char* p);
s32 GetDecimalExponent(double v);
u8 GetDecimalDigit(double v, s32 e, s32 i);
f32 Power(f32 a, f32 b);
double ConvertFloatToDouble(f32 f);
double MultiplyDoubles(double a, double b);
double AddDoubles(double a, double b);

union DoubleBits {
    double d;
    u64 u;
};




extern u8 g_renderThreadStack[];
extern u8 D_002832F0[];
// The ids of the main thread and of the render thread func_001E2398 starts.
struct ThreadIds { s32 main; s32 render; };
extern ThreadIds g_mainAndRenderThreads;

void RunRenderThread(void);
s32 GetCurrentThreadId(void);
void SetThreadPriority(s32 a, s32 b);
void* FillMemory(void* p, s32 value, s32 size);
s32 MakeThread(ThreadParams* p);



s32 CompareDoubles(double a, double b);
f32 ConvertDoubleToFloat(double a);
f32 LogarithmBase10(f32 x);
double ConvertFloatToDouble(f32 x);
s32 ConvertDoubleToS32(double a);
double ConvertS32ToDouble(s32 a);



void* FillMemory(void* p, s32 value, s32 size);

// The file's .data, in retail's order; the labels only its assembly reads are included.
u8 D_00275940[0x18] = "0123456789abcdef";
ThreadIds g_mainAndRenderThreads = { 0, 0 };
u8 D_00275960[4] = { 0 };
s32 g_movieDecodeThread = 0;

s32 ParseSignedDecimal(s8* s, s32* out)
{
    s8* p = s;
    s32 sign = 1;
    s32 value = 0;
    s32 count = 0;
    u8 c;

    if (*p == 0x2D) {
        sign = -1;
    }
    if (sign == -1) {
        p++;
        count = 1;
    }
    c = *p;
    if ((u32)(c - 0x30) < 10) {
        do {
            value = value * 10 + ((s8)c - 0x30);
            p++;
            c = *p;
            count++;
        } while ((u32)(c - 0x30) < 10);
    }
    *out = value * sign;
    return count;
}

s32 ParseFormatSpec(s8* at, FormatSpec* spec, s32** va)
{
    s32 state = 0;
    s8* p = at;
    s32 next;

    FillMemory(spec, 0, 0x34);
    if (*at != 0) {
        for (;;) {
            s32 adv = 0;
            next = state;
            switch (state) {
            case 0: {
                s8 c = *p;
                if (c != 0x25) {
                    next = 6;
                } else {
                    s8 d = p[1];
                    next = 1;
                    if (d == c) {
                        spec->conv = d;
                        next = 6;
                        adv = 2;
                    } else {
                        adv = 1;
                    }
                }
                break;
            }
            case 1:
                switch ((s8)((u8)*p - 0x20)) {
                case 13:
                    spec->left = 1;
                    adv = 1;
                    break;
                case 11:
                    spec->plus = 1;
                    adv = 1;
                    break;
                case 0:
                    spec->space = 1;
                    adv = 1;
                    break;
                case 3:
                    spec->alt = 1;
                    adv = 1;
                    break;
                case 16:
                    spec->zero = 1;
                    adv = 1;
                    break;
                default:
                    next = 2;
                    break;
                }
                break;
            case 2:
                if (*p == 0x2A) {
                    s32* ap = *va;
                    s32 w;
                    *va = ap + 2;
                    w = *ap;
                    spec->width = w;
                    if (w < 0) {
                        w = (w < 0) ? -w : w;
                        spec->left = 1;
                        spec->width = w;
                    }
                    adv = 1;
                } else {
                    adv = ParseSignedDecimal(p, &spec->width);
                }
                if (p[adv] == 0x2E) {
                    next = 3;
                    adv++;
                } else {
                    next = 4;
                }
                break;
            case 3:
                if (*p == 0x2A) {
                    s32* ap = *va;
                    s32 w;
                    *va = ap + 2;
                    w = *ap;
                    adv = 1;
                    w = (w < 0) ? -w : w;
                    spec->prec = w;
                } else {
                    adv = ParseSignedDecimal(p, &spec->prec);
                }
                spec->noprec = spec->prec == 0;
                next = 4;
                break;
            case 4: {
                switch ((s8)((u8)*p - 0x4C)) {
                case 28:
                    spec->length = 1;
                    adv = 1;
                    break;
                case 32:
                    adv = 1;
                    if (p[1] != 0x6C) {
                        spec->length = 2;
                        break;
                    }
                    // fall through
                case 0:
                case 37:
                    spec->length = 2;
                    adv++;
                    break;
                case 1:
                case 10:
                case 33:
                case 42: {
                    s32 a = 3;
                    s32 r = 1;
                    s32 d;
                    s32 l;
                    if (g_charClassFlags[(s8)(u8)*p] & 1) {
                        a = 4;
                    }
                    spec->f24 = a;
                    d = *p;
                    l = (g_charClassFlags[d] & 1) ? d + 0x20 : d;
                    if (l ^ 0x76) {
                        r = a;
                    }
                    spec->f28 = r;
                    adv = 1;
                    break;
                }
                default:
                    break;
                }
                next = 5;
                break;
            }
            case 5:
                if (*p != 0x25) {
                    s32 e = *p;
                    s32 f;
                    s32 l;
                    spec->upper = g_charClassFlags[e] & 1;
                    f = *p;
                    l = (g_charClassFlags[f] & 1) ? f + 0x20 : f;
                    spec->conv = l;
                }
                adv = 1;
                next = 6;
                break;
            default:
                return p - at;
            }
            p += adv;
            state = next;
            if (*p == 0 || next == 6) {
                break;
            }
        }
    }
    return p - at;
}


void FormatStringArg(FormatSpec* self, PaddedOutput* ctx, const char* str) {
    s32 n;
    s32 right;
    s32 left;
    u8 pad;

    if (str == 0) {
        str = "(null)";
    }
    right = 0;
    n = GetStringLength(str);
    left = 0;
    if (self->prec != 0 && self->prec < n) {
        n = self->prec;
    } else if (self->noprec != 0) {
        n = 0;
    }
    if (n < self->width) {
        pad = (self->zero != 0) ? 0x30 : 0x20;
        s32 d = self->width - n;
        if (self->left != 0) {
            right = d;
        } else {
            left = d;
        }
    }
    ctx->Pad(pad, left);
    AppendToOutputBuffer(ctx, str, n);
    ctx->Pad(0x20, right);
}


s32 ExtractIntegerSign(FormatSpec* self, void* dst)
{
    s32 ret = 0;
    if (self->length != 1) {
        if (self->length < 2) {
            if (self->length == 0) {
                *(u32*)((u8*)dst + 4) = 0;
            }
        }
    } else {
        *(u64*)dst = *(u16*)dst;
    }
    if (self->conv == 'd' || self->conv == 'i') {
        switch (self->length) {
        case 0:
            if (*(s32*)dst < 0) {
                *(s32*)dst = -*(s32*)dst;
                ret = 1;
            }
            break;
        case 1:
            if (*(s16*)dst < 0) {
                *(s16*)dst = -*(u16*)dst;
                ret = 1;
            }
            break;
        case 2:
            if (*(s64*)dst < 0) {
                *(s64*)dst = -*(s64*)dst;
                ret = 1;
            }
            break;
        }
    }
    return ret;
}

s32 GetConversionRadix(s8 c)
{
    switch (c) {
    case 0x64:
    case 0x69:
    case 0x75:
        return 10;
    case 0x42:
    case 0x62:
        return 2;
    case 0x6F:
        return 8;
    case 0x78:
        return 16;
    }
    return 10;
}

s32 WriteIntegerDigits(u8* buf, s32 len, u64 value, u32 radixArg)
{
    u64 radix = radixArg;
    u8* end = buf + len;
    u8* stop = end;
    u64 v = value;
    do {
        s64 digit = RemainderUnsigned64(v, radix);
        end--;
        *end = D_00275940[(s32)digit];
        v = DivideUnsigned64(v, radix);
    } while (v != 0 && end >= buf);
    s32 count = stop - end;
    if (count != 0 && buf < end) {
        CopyMemory(buf, end, count);
    }
    return count;
}


void FormatIntegerArg(FormatSpec* self, OutputBuffer* sink, u64 value)
{
    char buf[0x50];
    char pfx[0x10];
    char padc[0x10];
    IntegerArg val;
    s32 total;
    s32 lead;
    s32 trail;
    s32 zeros;
    s32 plen;
    s32 ndig;
    s32 n;

    val.v = value;
    if (self->noprec != 0 || self->prec != 0) {
        self->zero = 0;
    }
    if (self->noprec != 0 && val.v == 0) {
        plen = 0;
        zeros = 0;
        ndig = 0;
    } else {
        s32 neg = ExtractIntegerSign(self, &val);
        zeros = self->prec;
        pfx[0] = 0;
        switch ((u8)self->conv) {
        case 'd':
        case 'i':
            if (neg) {
                __builtin_strcpy(pfx, "-");
            } else if (self->plus) {
                __builtin_strcpy(pfx, "+");
            } else if (self->space) {
                __builtin_strcpy(pfx, " ");
            }
            zeros -= GetStringLength(pfx);
            break;
        case 'b':
            if (self->alt) {
                __builtin_strcpy(pfx, "0b");
            }
            break;
        case 'o':
            if (self->alt) {
                __builtin_strcpy(pfx, "0");
            }
            break;
        case 'x':
            if (self->alt) {
                __builtin_strcpy(pfx, "0x");
            }
            break;
        }
        plen = GetStringLength(pfx);
        ndig = WriteIntegerDigits(buf, 0x40, val.v, GetConversionRadix(self->conv));
        zeros -= ndig;
        zeros = zeros >= 0 ? zeros : 0;
    }
    buf[ndig] = 0;
    if (self->upper) {
        UppercaseString(pfx);
        UppercaseString(buf);
    }
    total = plen + zeros + ndig;
    lead = 0;
    trail = 0;
    if (total < self->width) {
        s32 rem = self->width - total;
        if (self->left) {
            trail = rem;
        } else if (self->zero == 0) {
            lead = rem;
        } else if (ndig != 0) {
            zeros += rem;
        } else {
            lead = rem;
        }
    }
    padc[0] = ' ';
    n = lead;
    while (n-- > 0) {
        if (AppendToOutputBuffer(sink, padc, 1) != 1) {
            break;
        }
    }
    AppendToOutputBuffer(sink, pfx, plen);
    padc[0] = '0';
    n = zeros;
    while (n-- > 0) {
        if (AppendToOutputBuffer(sink, padc, 1) != 1) {
            break;
        }
    }
    AppendToOutputBuffer(sink, buf, ndig);
    padc[0] = ' ';
    n = trail;
    while (n-- > 0) {
        if (AppendToOutputBuffer(sink, padc, 1) != 1) {
            break;
        }
    }
}


s32 GetDecimalExponent(double v)
{
    s32 i;
    if (CompareDoubles(v, 0.0) > 0) {
        double l = ConvertFloatToDouble(LogarithmBase10(ConvertDoubleToFloat(v)));
        i = ConvertDoubleToS32(l);
        if (CompareDoubles(l, 0.0) < 0 && CompareDoubles(l, ConvertS32ToDouble(i)) != 0)
            i--;
    } else {
        i = 0;
    }
    return i;
}

s8 GetDecimalDigit(RegDouble* self0, s32 a, s32 b)
{
    RegDouble* self = self0;
    s32 idx;
    if (a < b || a - 15 >= b) {
        idx = 0;
    } else {
        f32 t = Power(10.0f, (f32)(-b));
        RegDouble* p = MultiplyDoubles(self, ConvertFloatToDouble(t));
        self = TruncateDouble(p);
        p = TruncateDouble(MultiplyDoubles(self, 0.1));
        p = MultiplyDoubles(p, (u64)0x4024000000000000ULL);
        idx = ConvertDoubleToS32(SubtractDoubles(self, p));
    }
    return ((s8*)&D_00275940)[idx];
}


s32 FormatFloatDigits(char* buf, s32 unused, FormatSpec* sp, double v)
{
    DoubleBits bits;
    bits.d = v;
    if ((bits.u & 0x7FF0000000000000UL) == 0x7FF0000000000000UL) {
        const char* s = (bits.u & 0x000FFFFFFFFFFFFFUL) ? "(nan)" : "(inf)";
        CopyString(buf, (char*)s);
        return GetStringLength(buf);
    }
    char* out = buf;
    s32 e = GetDecimalExponent(v);
    s32 isE = sp->conv == 'e';
    if (sp->conv == 'g') {
        if (e < -4 || e >= sp->prec) {
            isE = 1;
            sp->prec = sp->prec - 1;
        }
    }
    s32 base = 0;
    if (isE) base = e;
    s32 prec = sp->prec;
    f32 p = Power(10.0f, (f32)(base - prec));
    double r = AddDoubles(v, MultiplyDoubles(ConvertFloatToDouble(p), 0.5));
    s32 e2 = GetDecimalExponent(r);
    if (e < GetDecimalExponent(r)) e = e2;
    s32 n, i;
    if (isE) {
        n = 1;
        i = e;
    } else if (e >= 0) {
        i = e;
        n = e + 1;
    } else {
        n = 1;
        i = 0;
    }
    while (n-- > 0) {
        *out++ = GetDecimalDigit(r, e, i--);
    }
    if (sp->noprec == 0) {
        *out++ = '.';
        n = sp->prec;
        while (n-- > 0) {
            *out++ = GetDecimalDigit(r, e, i--);
        }
        if (sp->conv == 'g' && buf < out) {
            while (buf < out && out[-1] == '0') out--;
            if (buf < out && out[-1] == '.') out--;
        }
    }
    if (isE) {
        *out++ = 'e';
        if (e < 0) {
            *out++ = '-';
            e = -e;
        } else {
            *out++ = '+';
        }
        s32 d = (s32)Power(10.0f, 2.0f);
        for (s32 k = 2; k >= 0; k--) {
            *out++ = D_00275940[e / d];
            e = (e % d) * 10;
        }
    }
    return out - buf;
}


void FormatFloatArg(FormatSpec* spec, OutputBuffer* ctx, double value)
{
    char buf[0x1C0];
    char sign[16];
    char padc[16];
    s32 zeros = 0;
    s32 left;
    s32 lead;
    s32 n;
    s32 len;
    s32 slen;
    s32 width;
    s32 total;
    s32 neg;
    if (spec->prec == 0 && spec->noprec == 0) {
        spec->prec = 6;
    } else if (spec->noprec != 0 && spec->conv == 0x67) {
        spec->prec = 1;
    }
    neg = value < 0.0;
    if (neg) value = 0.0 - value;
    sign[0] = 0;
    if (neg) __builtin_strcpy(sign, "-");
    else if (spec->plus) __builtin_strcpy(sign, "+");
    else if (spec->space) __builtin_strcpy(sign, " ");
    slen = GetStringLength(sign);
    len = FormatFloatDigits(buf, 0x1B5, spec, value);
    buf[len] = 0;
    if (spec->upper) UppercaseString(buf);
    width = spec->width;
    total = slen + len;
    lead = 0;
    left = 0;
    if (total < width) {
        s32 pad = width - total;
        if (spec->left) left = pad;
        else if (spec->zero && len != 0) zeros = pad;
        else lead = pad;
    }
    padc[0] = ' ';
    n = lead;
    while (n-- > 0) {
        if (AppendToOutputBuffer(ctx, padc, 1) != 1) break;
    }
    n = zeros;
    AppendToOutputBuffer(ctx, sign, slen);
    padc[0] = '0';
    while (n-- > 0) {
        if (AppendToOutputBuffer(ctx, padc, 1) != 1) break;
    }
    AppendToOutputBuffer(ctx, buf, len);
    n = left;
    padc[0] = ' ';
    while (n-- > 0) {
        if (AppendToOutputBuffer(ctx, padc, 1) != 1) break;
    }
}


void FormatConversionArg(FormatSpec* sp, OutputBuffer* c, u8** va, const char* fmt, s32 len) {
    u64 v;
    switch (sp->conv) {
    case '%':
        AppendToOutputBuffer(c, (const char*)&sp->conv, 1);
        return;
    case 'c': {
        signed char buf[16];
        u8* p = *va;
        *va = p + 8;
        s32 ch = *(s8*)p;
        buf[0] = ch;
        AppendToOutputBuffer(c, (const char*)buf, 1);
        return;
    }
    case 's': {
        u8* p = *va;
        *va = p + 8;
        FormatStringArg(sp, c, *(const char**)p);
        return;
    }
    case 'p':
        sp->prec = 8;
        sp->conv = 'x';
        sp->length = 0;
    case 'b': case 'd': case 'i': case 'o': case 'u': case 'x':
        switch (sp->length) {
        case 0: case 1: { u8* p = *va; *va = p + 8; v = *(u32*)p; break; }
        case 2: { u8* p = *va; *va = p + 8; v = *(u64*)p; break; }
        }
        FormatIntegerArg(sp, c, v);
        return;
    case 'e': case 'f': case 'g':
        if (sp->f24 != 0) {
            const char* s4 = "
";
            u8* a = *va;
            const char* s8 = ",
";
            const char* s7 = "{ ";
            *va = a + 8;
            const char* s5 = ", ";
            const char* s6 = " }";
            f32* fp = *(f32**)a;
            if (sp->f28 >= 2) {
                AppendToOutputBuffer(c, s4, GetStringLength(s4));
            }
            for (s32 i = 0; i < sp->f28; ) {
                s32 next;
                if (i != 0) {
                    AppendToOutputBuffer(c, s8, GetStringLength(s8));
                }
                next = i + 1;
                AppendToOutputBuffer(c, s7, GetStringLength(s7));
                for (s32 j = 0; j < sp->f24; j++) {
                    if (j != 0) {
                        AppendToOutputBuffer(c, s5, GetStringLength(s5));
                    }
                    FormatFloatArg(sp, c, ConvertFloatToDouble(*fp++));
                }
                AppendToOutputBuffer(c, s6, GetStringLength(s6));
                i = next;
            }
            if (sp->f28 >= 2) {
                AppendToOutputBuffer(c, s4, GetStringLength(s4));
            }
        } else {
            u8* p = *va;
            *va = p + 8;
            FormatFloatArg(sp, c, *(s64*)p);
        }
        return;
    case 'n':
        switch (sp->length) {
        case 0: { u8* p = *va; *va = p + 8; **(s32**)p = c->count; break; }
        case 1: { u8* p = *va; *va = p + 8; s16* q = *(s16**)p; s32 n = c->count; *q = n; break; }
        case 2: { u8* p = *va; *va = p + 8; **(s64**)p = c->count; break; }
        }
        return;
    default:
        AppendToOutputBuffer(c, fmt, len);
        return;
    }
}


s32 FormatToOutputBuffer(OutputBuffer* ctx, const char* fmt, void* a2)
{
    FormatFrame loc;
    const char* s1 = fmt;

    loc.va = a2;
    if (*s1 != 0) {
        do {
            char* s2 = FindCharInString(s1, '%');
            s32 n = (s32)s2 - (s32)s1;
            if (s2 == 0) {
                n = GetStringLength(s1);
                s2 = (char*)((s32)s1 + n);
            }
            if (n != 0) {
                if (AppendToOutputBuffer(ctx, s1, n) < n) {
                    break;
                }
                s1 = s2;
            }
            if (*s1 == '%') {
                s32 n2 = ParseFormatSpec(s1, &loc.spec, (void*)&loc.va);
                FormatConversionArg(&loc.spec, ctx, (void*)&loc.va, s1, n2);
                s1 = s1 + n2;
            }
        } while (*s1 != 0);
    }
    FlushOutputBuffer(ctx);
    return ctx->count;
}

s32 PrintFormattedVa(const char* fmt, void* ap)
{
    OutputBufferStorage buf;
    InitOutputBuffer(&buf, -1);
    s32 n = FormatToOutputBuffer(&buf, fmt, ap);
    DestroyOutputBuffer(&buf, 2);
    return n;
}

s32 PrintFormatted(void* self, ...)
{
    void* ap = (char*)__builtin_next_arg(self) - 56;
    return PrintFormattedVa(self, ap);
}

s32 FormatToStringVa(char* dst, const char* fmt, void* ap)
{
    OutputBufferStorage buf;
    InitStringOutputBuffer(&buf, dst, 0);
    s32 n = FormatToOutputBuffer(&buf, fmt, ap);
    dst += n;
    *dst = 0;
    DestroyOutputBuffer(&buf, 2);
    return n;
}

s32 FormatToString(char* dst, const char* fmt, ...)
{
    void* ap = (char*)__builtin_next_arg(fmt) - 48;
    return FormatToStringVa(dst, fmt, ap);
}

s32 FormatToStringBoundedVa(char* dst, s32 cap, s32 a, s32 b)
{
    u8 buf[0x420];
    s32 n;

    InitStringOutputBuffer(buf, dst, cap);
    n = FormatToOutputBuffer(buf, a, b);
    if (n >= cap) {
        n = -1;
        dst[cap - 1] = 0;
    } else {
        dst[n] = 0;
    }
    DestroyOutputBuffer(buf, 2);
    return n;
}

LINKER_REMNANT(func_001E20B0);

s32 FormatToStringBounded(char* dst, s32 cap, const char* fmt, ...)
{
    void* ap = (char*)__builtin_next_arg(fmt) - 40;
    return FormatToStringBoundedVa(dst, cap, fmt, ap);
}

LINKER_REMNANT(func_001E20F8);

s32 GetStringLength(const char* s) { s32 length = 0; while (*s) { s++; length++; } return length; }

void* CopyString(void* dst, void* src)
{
    s32 n = GetStringLength(src);
    CopyMemory(dst, src, n + 1);
    return dst;
}

void* AppendString(void* dst, void* src)
{
    s32 len = GetStringLength(dst);
    s32 n = GetStringLength(src);
    CopyMemory((u8*)dst + len, src, n + 1);
    return dst;
}

char* FindCharInString(char* s, s32 c)
{
    while (*s != 0) {
        if ((s8)*s == c) {
            return s;
        }
        s++;
    }
    return 0;
}

LINKER_REMNANT(func_001E2210);

void UppercaseString(s8* p)
{
    while (*p != 0) {
        s32 c = *p;
        s32 r = c;
        if (g_charClassFlags[c] & 2) {
            r = c - 0x20;
        }
        *p = r;
        p++;
    }
}

s32 CreateLockSemaphore(void* a, void* b)
{
    SemaphoreParams tmp;

    FillMemory(&tmp, 0, 0x18);
    tmp.initCount = (s32)a;
    tmp.maxCount = (s32)b;
    return NewSemaphore(&tmp);
}

LINKER_REMNANT(func_001E22B8);

void InitRecursiveLock(RecursiveLock* self)
{
    self->last = -1;
    self->sema = (void*)CreateLockSemaphore(1, 1);
}

void EnterRecursiveLock(RecursiveLock* self)
{
    s32 key = GetCurrentThreadId();
    if (key != self->last) {
        (void)AwaitSemaphore(self->sema);
        self->last = key;
        self->count = 1;
    } else {
        self->count++;
    }
}

void LeaveRecursiveLock(RecursiveLock* self)
{
    if (--self->count == 0) {
        self->last = -1;
        PostSemaphore(self->sema);
    }
}

LINKER_REMNANT(func_001E2390);

void CreateRenderThread(void)
{
    ThreadParams l;

    g_mainAndRenderThreads.main = GetCurrentThreadId();
    SetThreadPriority(g_mainAndRenderThreads.main, 4);
    (void)FillMemory(&l, 0, sizeof(l));
    l.stackSize = 0x20000;
    l.stack = g_renderThreadStack;
    l.priority = 2;
    l.gp = D_002832F0;
    l.entry = RunRenderThread;
    g_mainAndRenderThreads.render = MakeThread(&l);
}