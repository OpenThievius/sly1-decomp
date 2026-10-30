// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Config_1E0848 { u8 pad000[4]; s8 marker04; u8 pad005[3]; f32 value08; f32 value0C; f32 value10; f32 value14; s32 value18; };
extern Config_1E0848 D_002758E0;
void func_001F5C0C(void* dst, s32 value, s32 size);
void func_001E0848(void* self, u32 mode)
{
	if (mode != 0xFFFF || self == 0) return;
	func_001F5C0C(&D_002758E0, 0, 0x1C);
	D_002758E0.marker04 = 0x2D;
	D_002758E0.value08 = 2.0f;
	D_002758E0.value0C = 1.0f;
	D_002758E0.value10 = 0.3f;
	D_002758E0.value14 = 0.3f;
	D_002758E0.value18 = 0xFF7D4B00;
}

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

s32 func_001E2268(s32 a, s32 b);

struct IntPair_1E22C0 { u8 pad0[4]; s32 a; s32 b; };

void func_001E22C0(IntPair_1E22C0* self)
{
    self->a = -1;
    self->b = func_001E2268(1, 1);
}

struct Actor_1E2778 { u8 pad000[0x2D0]; s32 f2D0; u8 pad2D4[0x388 - 0x2D4]; s32 f388; u8 pad38C[0x394 - 0x38C]; s32 state394; u8 pad398[0x39C - 0x398]; f32 f39C; };

void func_001451F0(u32 a0, int a1, int a2, void* a3, int a4, void* a5);
void func_00145088(u32 a0, int a1, void* a2, int a3, void* a4);
void func_001837E0(void* self, s32 a, s32 b, s32 c);
extern u32 D_00261990;
extern f32 D_0026185C;

void func_001E2778(void* selfv, s32 state)
{
    Actor_1E2778* self = (Actor_1E2778*)selfv;
    if (self->state394 == state) return;
    if (state != 0) {
        if (state != 1) {
            self->state394 = state;
            goto tail;
        }
        u32 base = D_00261990;
        func_00145088(base, self->f388 + 2, (void*)(base + 0x520), self->f2D0, self);
        func_001837E0(self, 2, 0, 0);
    } else {
        u32 base = D_00261990;
        func_001451F0(base, 8, -1, 0, 0, self);
        func_001837E0(self, 3, 0, 0);
    }
    self->state394 = state;
tail:
    self->f39C = D_0026185C;
}

struct Actor_1E2840 { u8 pad000[0x398]; s32 f398; };

void func_001E2870(void* self, s32 a, s32 b);

void func_001E2840(void* selfv, s32 value)
{
    Actor_1E2840* self = (Actor_1E2840*)selfv;
    if (value == self->f398) return;
    self->f398 = value;
    func_001E2870(self, 0, 0);
}

struct Tally_1E2358 { s32 count; s32 last; void* ptr; };
extern void func_001F6B40(void* a);

void func_001E2358(Tally_1E2358* self)
{
    if (--self->count == 0) {
        self->last = -1;
        func_001F6B40(self->ptr);
    }
}

struct Actor_1E2940 { u8 pad000[0x14]; void* f14; u8 pad018[0x398 - 0x18]; s32 f398; };

void func_00124FC0(void* self);
void func_001E2870(void* self, s32 a, s32 b);
void func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);

void func_001E2940(void* selfv)
{
    Actor_1E2940* self = (Actor_1E2940*)selfv;
    func_00124FC0(self);
    if (self->f398 != 0) {
        func_001DBCC8(self->f14, (void*)func_001E2870, self, 0, 0);
    }
}

void func_001261C0(void);

void func_001E2988(void)
{
    func_001261C0();
}

s32 func_001E2100(const char* s) { s32 length = 0; while (*s) { s++; length++; } return length; }

extern u8 D_00275980[];
void* func_001E2420(void* self) { return self ? (u8*)self + 0x2F0 : D_00275980; }

struct Obj_001E29E8 { u8 pad[0x360]; f32 a; f32 b; f32 c; };
void func_001E29E8(Obj_001E29E8* self, f32 value) { self->b = value; self->c = 1.0f; self->a = value; }

void func_001E30E0(void) {}

void func_001243E0(void* self);
void func_001E2778(void* self, s32 state);
void func_001DBD40(void* a, s32 b, s32 c, void* d, s32 e, s32 f);

void func_001E25F8(void* self)
{
    func_001243E0(self);
    func_001E2778(self, 0);
    func_001DBD40(*(void**)((u8*)self + 0x14), 2, 0, self, -1, 0);
}

void func_00124A48(void* self);

void func_001E2758(void* self)
{
    func_00124A48(self);
}

void func_0015FBB8(void* self, void* p);
void func_001E2778(void* selfv, s32 state);

void func_001E29A8(void* self, void* p)
{
    func_0015FBB8(self, p);
    if (p != 0) {
        func_001E2778(self, 0);
    }
}

void func_00137EB0(void* a, void* b);
void func_00137E70(void* a, void* b);
s32 func_001E4C48(void* a, void* b, void* c, void* d, void* e);
s32 func_00137CC0(void* a);
void* func_0014D9A8(s32 idx);
void func_0011EC40(void* a, void* b);

struct Arr_1E2648 { u8 pad0[0xC]; s32 count; u8 pad1[4]; f32* data; };
struct Obj_1E2648 {
    void** vtbl;
    u8 pad0[0x2E4 - 4];
    Arr_1E2648* obj;
    u8 pad1[0x3F0 - 0x2E8];
    f32 f3F0;
    u8 pad2[0x414 - 0x3F4];
    s32 i414;
};

void func_001E2648(Obj_1E2648* self, void* a1)
{
    func_00137EB0(a1, (u8*)self + 0xD0);
    func_00137E70(a1, (u8*)self + 0x100);
    void** vt = self->vtbl;
    if (vt[22] != 0) {
        ((void (*)(void*))vt[22])(self);
    }
    func_001E4C48(a1, (u8*)self + 0x2D4, (u8*)self + 0x2D8, (u8*)self + 0x2DC, (u8*)self + 0x2E0);
    s32 idx = func_00137CC0(a1);
    if (idx != -1) {
        Arr_1E2648* o = (Arr_1E2648*)func_0014D9A8(idx);
        self->obj = o;
        void** ovt = *(void***)o;
        if (ovt[0] != 0) {
            ((void (*)(void*, void*))ovt[0])(o, a1);
        }
        Arr_1E2648* p = self->obj;
        self->f3F0 = p->data[p->count - 1];
    } else {
        func_00137EB0(a1, (u8*)self + 0x3B0);
        func_00137E70(a1, (u8*)self + 0x3E0);
        *(s32*)&self->f3F0 = 0;
    }
    self->i414 = (self->obj != 0) ? 7 : 5;
    func_0011EC40(self, a1);
}


struct Sub_1E30A0 { u8 pad[0x438]; f32 f438; f32 f43C; };
struct Obj_1E30A0 { u8 pad[0x8]; Sub_1E30A0* sub; };
struct Glob_1E30A0 { u8 pad[0x1C8]; f32 f1C8; };

void func_001E30A0(Obj_1E30A0* self)
{
    Sub_1E30A0* s = self->sub;
    if (s != 0) {
        if (s->f438 != 0.0f) {
            Glob_1E30A0* g = (Glob_1E30A0*)D_00261990;
            g->f1C8 = s->f43C;
        }
    }
    self->sub = 0;
}

void func_001F5C0C(void* p, s32 zero, s32 size);

