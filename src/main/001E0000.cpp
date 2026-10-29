// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_001E02C8(void* self, s32 n);

void func_001E0828(void* self)
{
    func_001E02C8(self, 3);
}

void func_001D7120(u8* buf, char* dst, s32 cap);
s32 func_001E1DB8(u8* buf, s32 a, s32 b);
void func_001D7148(u8* buf, s32 n);

s32 func_001E2018(char* dst, s32 cap, s32 a, s32 b)
{
    u8 buf[0x420];
    s32 n;

    func_001D7120(buf, dst, cap);
    n = func_001E1DB8(buf, a, b);
    if (n >= cap) {
        n = -1;
        dst[cap - 1] = 0;
    } else {
        dst[n] = 0;
    }
    func_001D7148(buf, 2);
    return n;
}

void func_001F5C0C(void* p, s32 v, s32 n);
void func_001F6B20(void* self);

struct Ctor_1E2268 {
    u8 pad0[4];
    void* b;
    void* a;
    u8 pad1[0x14];
};

void func_001E2268(void* a, void* b)
{
    Ctor_1E2268 tmp;

    func_001F5C0C(&tmp, 0, 0x18);
    tmp.a = a;
    tmp.b = b;
    func_001F6B20(&tmp);
}

void func_001E30D8(void* self)
{
}

s32 func_001E1EB0(void* self, void* ap);

s32 func_001E1F10(void* self, ...)
{
    void* ap = (char*)__builtin_next_arg(self) - 56;
    return func_001E1EB0(self, ap);
}

struct Stream_001E1F58 { u8 bytes[0x420]; };

void func_001D7120(void* stream, char* dst, s32 cap);
s32 func_001E1DB8(void* stream, const char* fmt, void* ap);
void func_001D7148(void* stream, s32 mode);

s32 func_001E1F58(char* dst, const char* fmt, void* ap)
{
    Stream_001E1F58 buf;
    func_001D7120(&buf, dst, 0);
    s32 n = func_001E1DB8(&buf, fmt, ap);
    dst += n;
    *dst = 0;
    func_001D7148(&buf, 2);
    return n;
}

s32 func_001E1F58(char* dst, const char* fmt, void* ap);

s32 func_001E1FD0(char* dst, const char* fmt, ...)
{
    void* ap = (char*)__builtin_next_arg(fmt) - 48;
    return func_001E1F58(dst, fmt, ap);
}

s32 func_001E2018(char* dst, s32 cap, const char* fmt, void* ap);

s32 func_001E20B8(char* dst, s32 cap, const char* fmt, ...)
{
    void* ap = (char*)__builtin_next_arg(fmt) - 40;
    return func_001E2018(dst, cap, fmt, ap);
}

struct Stream_1E1EB0 { u8 bytes[0x420]; };

void func_001D7100(void* stream, s32 cap);
s32 func_001E1DB8(void* stream, const char* fmt, void* ap);
void func_001D7148(void* stream, s32 mode);

s32 func_001E1EB0(const char* fmt, void* ap)
{
    Stream_1E1EB0 buf;
    func_001D7100(&buf, -1);
    s32 n = func_001E1DB8(&buf, fmt, ap);
    func_001D7148(&buf, 2);
    return n;
}

s32 func_001E2100(void* p);
void func_0018D800(void* dst, void* src, s32 count);

void* func_001E2138(void* dst, void* src)
{
    s32 n = func_001E2100(src);
    func_0018D800(dst, src, n + 1);
    return dst;
}

s32 func_001E2100(void* p);
void func_0018D800(void* dst, void* src, s32 count);

void* func_001E2180(void* dst, void* src)
{
    s32 len = func_001E2100(dst);
    s32 n = func_001E2100(src);
    func_0018D800((u8*)dst + len, src, n + 1);
    return dst;
}

char* func_001E21D8(char* s, s32 c)
{
    while (*s != 0) {
        if ((s8)*s == c) {
            return s;
        }
        s++;
    }
    return 0;
}
