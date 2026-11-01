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

extern u8 D_00275940[];

u64 func_001FBE00(u64 value, u64 radix);
s64 func_001FC3D0(u64 value, u64 radix);
void func_0018D800(void* dst, void* src, s32 count);

s32 func_001E0F58(u8* buf, s32 len, u64 value, u32 radixArg)
{
    u64 radix = radixArg;
    u8* end = buf + len;
    u8* stop = end;
    u64 v = value;
    do {
        s64 digit = func_001FC3D0(v, radix);
        end--;
        *end = D_00275940[(s32)digit];
        v = func_001FBE00(v, radix);
    } while (v != 0 && end >= buf);
    s32 count = stop - end;
    if (count != 0 && buf < end) {
        func_0018D800(buf, end, count);
    }
    return count;
}

extern u8 D_00275980[];
extern u8 D_00275A10[];
extern u8 D_00275A20[];

void func_00123ED0(void* self);

struct __attribute__((aligned(16))) Block_2520 {
    u8 d[0x90];
};

struct __attribute__((aligned(16))) Quad_2520 {
    u8 d[0x10];
};

struct __attribute__((packed)) Pack8_2520 {
    u64 v;
};

void func_001E2520(void* self)
{
    u8* p = (u8*)self;

    func_00123ED0(self);
    *(Block_2520*)(p + 0x2F0) = *(Block_2520*)D_00275980;
    *(f32*)(p + 0x428) = 2.0f;
    *(f32*)(p + 0x42C) = 1.0f;
    *(u64*)(p + 0x2C8) = (*(u64*)(p + 0x2C8) & 0xFFFFFCFFFFFFFFFFULL) | 0x10000000000ULL;
    *(f32*)(p + 0x420) = 2.0f;
    *(f32*)(p + 0x424) = 1.0f;
    *(s32*)(p + 0x430) = -1;
    *(Quad_2520*)(p + 0x450) = *(Quad_2520*)D_00275A10;
    {
        u8* src = D_00275A20;
        *(Pack8_2520*)(p + 0x460) = *(Pack8_2520*)src;
    }
    *(s32*)(p + 0x398) = -1;
}

struct Tally_1E22F8 { s32 count; s32 last; void* ptr; };
extern s32 func_001F6A90(void);
extern s32 func_001F6B60(void* a);

void func_001E22F8(Tally_1E22F8* self)
{
    s32 key = func_001F6A90();
    if (key != self->last) {
        (void)func_001F6B60(self->ptr);
        self->last = key;
        self->count = 1;
    } else {
        self->count++;
    }
}

struct Field_001E0E18 {
    u8 pad0[0x20];
    s32 kind;
    u8 pad1[0x8];
    u8 mode;
};

s32 func_001E0E18(Field_001E0E18* self, void* dst)
{
    s32 ret = 0;
    if (self->kind != 1) {
        if (self->kind < 2) {
            if (self->kind == 0) {
                *(u32*)((u8*)dst + 4) = 0;
            }
        }
    } else {
        *(u64*)dst = *(u16*)dst;
    }
    if (self->mode == 'd' || self->mode == 'i') {
        switch (self->kind) {
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

void func_001F5C0C(void* p, s32 zero, s32 size);

struct VT_1E00B0 { u8 pad[0x20]; void (*m20)(void*, void*); u8 pad24[0x14]; void (*m38)(void*); void (*m3C)(void*); };
struct Obj_1E00B0 { VT_1E00B0* vt; u8 pad04[0x25C]; s32 f260; u8 pad264[4]; f32 f268; s32 f26C; };
struct Glob_1E00B0 { u8 pad[0x2310]; s32 f2310; void* f2314; };
struct Cam_1E00B0 { s32 flags; u8 pad[4]; f32 f08; };
struct Pool_1E00B0 { u8 pad[0xAA]; u16 fAA; };
extern Obj_1E00B0 D_0026E760;
extern Obj_1E00B0 D_0026E9F8;
extern Glob_1E00B0* D_00275710;
extern Cam_1E00B0* D_002623C8;
extern Pool_1E00B0 D_00262C70;
extern f32 D_0026185C;
extern s32 D_002623DC;
extern s32 D_002701C4;
void func_001AA298(Obj_1E00B0* q);
void func_0016EC20(Pool_1E00B0* q, s32 n);
void func_001BE5F8(s32 q);
void func_001AA8B8(Obj_1E00B0* q, f32 v);
void func_001E02C8(Obj_1E00B0* q, s32 n);
f32 func_00205C78(f32 a, f32 b);
void func_001AB920(Obj_1E00B0* q, f32 v);
s32 func_001E9970(void);

void func_001E00B0(Obj_1E00B0* self)
{
    func_001AA298(self);
    switch (self->f260) {
    case 0:
    case 1:
    {
        if (self->f26C != 0) {
        if (D_00262C70.fAA & 4) {
            func_0016EC20(&D_00262C70, 4);
            func_001BE5F8(D_00275710->f2310);
            if (D_00275710->f2314 != 0) {
                func_001AA8B8(self, 15.0f);
                self->vt->m20(self, D_00275710->f2314);
            } else {
                self->vt->m3C(self);
            }
            self->f26C = 0;
        } else if (D_0026185C >= 5.0f) {
            self->vt->m3C(self);
            self->f26C = 0;
        }
        }
    break;
    }
    case 2:
    {
        Obj_1E00B0* o = &D_0026E760;
        s32 r;
        if (o->f260 == 0) {
            func_001E02C8(self, 3);
            return;
        }
        func_001AB920(o, -func_00205C78(2.0f, (f32)D_002623DC));
        r = func_001E9970();
        if (r) o->vt->m38(o); else o->vt->m3C(o);
        if (D_002623C8->flags & 8) {
            s32 b = 0;
            if (r && D_002701C4 == 0 && D_002623C8->f08 < D_0026E760.f268) b = 1;
            if (b) D_0026E9F8.vt->m38(&D_0026E9F8); else D_0026E9F8.vt->m3C(&D_0026E9F8);
        }
    }
    break;
    }
}

s32 func_001E08F8(s8* s, s32* out)
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

struct Obj_1E2870;
struct Sub_1E2870;
struct Mgr_1E2870;
struct Loc_1E2870 {
    s32 v[4];
};
struct Pq_1E2870 {
    u8 pad0[0x2220];
    s32 f2220;
};
struct Glob_1E2870 {
    u8 pad0[0x224];
    s32 f224;
};

extern u8* D_00262E10;

void* func_001925F0(void);
void func_00128018(Mgr_1E2870* a0, Obj_1E2870* a1, void* a2, Loc_1E2870* a3);
s32 func_001E4DC0(Sub_1E2870* self, Loc_1E2870* value);
void func_001E2778(Obj_1E2870* self, s32 state);

struct Obj_1E2870 {
    u8 pad0[0x2D0];
    void* f2D0;
    u8 pad1[0x2E0 - 0x2D4];
    Sub_1E2870* f2E0;
    u8 pad2[0x384 - 0x2E4];
    s32 f384;
    u8 pad3[0x398 - 0x388];
    s32 f398;
};

void func_001E2870(Obj_1E2870* self) {
    Loc_1E2870 loc;
    void* p = func_001925F0();
    if (p == 0) {
        return;
    }
    if (p != self->f2D0) {
        func_001E2778(self, 0);
        self->f2D0 = p;
    }
    s32 st;
    if (self->f398 == -1) {
        func_00128018(0, self, (u8*)p + 0x140, &loc);
        s32 r = func_001E4DC0(self->f2E0, &loc);
        st = (0u < (u32)r);
    } else {
        st = self->f398;
    }
    if (self->f384 == 0 && p == D_00262E10 && ((Pq_1E2870*)p)->f2220 == 2 &&
        ((Glob_1E2870*)D_00261990)->f224 == 0) {
        if (self->f398 == -1) {
            return;
        }
    }
    func_001E2778(self, st);
}

struct Ctx_1E1DB8 {
    u8 pad00[0x10];
    s32 count;      // 0x10
};

struct Locals_1E1DB8 {
    u8 spec[0x40];      // the conversion spec, at sp + 0
    void* va;           // the argument pointer, at sp + 0x40
    u8 pad44[0xC];
};

struct Str_1E1DB8;

void func_001D72C8(Ctx_1E1DB8* ctx);
s32 func_001D7190(Ctx_1E1DB8* ctx, const char* p, s32 n);
char* func_001E21D8(Str_1E1DB8* s, s32 c);
s32 func_001E2100(Str_1E1DB8* s);
s32 func_001E0978(const char* at, u8* spec, void* va);
void func_001E1A08(u8* spec, Ctx_1E1DB8* ctx, void* va, const char* at, s32 len);

s32 func_001E1DB8(Ctx_1E1DB8* ctx, const char* fmt, void* a2)
{
    Locals_1E1DB8 loc;
    const char* s1 = fmt;

    loc.va = a2;
    if (*s1 != 0) {
        do {
            char* s2 = func_001E21D8((Str_1E1DB8*)s1, '%');
            s32 n = (s32)s2 - (s32)s1;
            if (s2 == 0) {
                n = func_001E2100((Str_1E1DB8*)s1);
                s2 = (char*)((s32)s1 + n);
            }
            if (n != 0) {
                if (func_001D7190(ctx, s1, n) < n) {
                    break;
                }
                s1 = s2;
            }
            if (*s1 == '%') {
                s32 n2 = func_001E0978(s1, loc.spec, (void*)&loc.va);
                func_001E1A08(loc.spec, ctx, (void*)&loc.va, s1, n2);
                s1 = s1 + n2;
            }
        } while (*s1 != 0);
    }
    func_001D72C8(ctx);
    return ctx->count;
}

extern u8 D_0024E879[];

void func_001E2218(s8* p)
{
    while (*p != 0) {
        s32 c = *p;
        s32 r = c;
        if (D_0024E879[c] & 2) {
            r = c - 0x20;
        }
        *p = r;
        p++;
    }
}

s32 func_001E0EF8(s8 c)
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

struct Fmt_1E1028 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    u8 pad20[0xC];
    s8 mode;
    u8 pad2D[3];
    s32 f30;
};
struct Sink_1E1028 {
    s32 x;
};
struct Val_1E1028 {
    u64 v;
};

extern u16 D_0024E3D0;
extern u16 D_0024E3D8;
extern u16 D_0024E3E0;
extern u8 D_0024E3E8[];
extern u16 D_0024E3F0;
extern u8 D_0024E3F8[];

s32 func_001E0E18(Fmt_1E1028* self, Val_1E1028* v);
s32 func_001E2100(char* p);
s32 func_001E0EF8(s8 c);
s32 func_001E0F58(char* buf, s32 len, u64 value, u32 radix);
s32 func_001D7190(Sink_1E1028* sink, const char* p, s32 n);
void func_001E2218(char* p);

void func_001E1028(Fmt_1E1028* self, Sink_1E1028* sink, u64 value)
{
    char buf[0x50];
    char pfx[0x10];
    char padc[0x10];
    Val_1E1028 val;
    s32 total;
    s32 lead;
    s32 trail;
    s32 zeros;
    s32 plen;
    s32 ndig;
    s32 n;

    val.v = value;
    if (self->f14 != 0 || self->f1C != 0) {
        self->f10 = 0;
    }
    if (self->f14 != 0 && val.v == 0) {
        plen = 0;
        zeros = 0;
        ndig = 0;
    } else {
        s32 neg = func_001E0E18(self, &val);
        zeros = self->f1C;
        pfx[0] = 0;
        switch ((u8)self->mode) {
        case 'd':
        case 'i':
            if (neg) {
                *(u16*)pfx = D_0024E3D0;
            } else if (self->f4) {
                *(u16*)pfx = D_0024E3D8;
            } else if (self->f8) {
                *(u16*)pfx = D_0024E3E0;
            }
            zeros -= func_001E2100(pfx);
            break;
        case 'b':
            if (self->fC) {
                *(u16*)pfx = *(u16*)D_0024E3E8;
                pfx[2] = D_0024E3E8[2];
            }
            break;
        case 'o':
            if (self->fC) {
                *(u16*)pfx = D_0024E3F0;
            }
            break;
        case 'x':
            if (self->fC) {
                *(u16*)pfx = *(u16*)D_0024E3F8;
                pfx[2] = D_0024E3F8[2];
            }
            break;
        }
        plen = func_001E2100(pfx);
        ndig = func_001E0F58(buf, 0x40, val.v, func_001E0EF8(self->mode));
        zeros -= ndig;
        zeros = zeros >= 0 ? zeros : 0;
    }
    buf[ndig] = 0;
    if (self->f30) {
        func_001E2218(pfx);
        func_001E2218(buf);
    }
    total = plen + zeros + ndig;
    lead = 0;
    trail = 0;
    if (total < self->f18) {
        s32 rem = self->f18 - total;
        if (self->f0) {
            trail = rem;
        } else if (self->f10 == 0) {
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
        if (func_001D7190(sink, padc, 1) != 1) {
            break;
        }
    }
    func_001D7190(sink, pfx, plen);
    padc[0] = '0';
    n = zeros;
    while (n-- > 0) {
        if (func_001D7190(sink, padc, 1) != 1) {
            break;
        }
    }
    func_001D7190(sink, buf, ndig);
    padc[0] = ' ';
    n = trail;
    while (n-- > 0) {
        if (func_001D7190(sink, padc, 1) != 1) {
            break;
        }
    }
}

struct Spec_1E0978 {
    s32 left;       // 0x00
    s32 plus;       // 0x04
    s32 space;      // 0x08
    s32 alt;        // 0x0C
    s32 zero;       // 0x10
    s32 noprec;     // 0x14
    s32 width;      // 0x18
    s32 prec;       // 0x1C
    s32 length;     // 0x20
    s32 f24;        // 0x24
    s32 f28;        // 0x28
    s8 conv;        // 0x2C
    s8 pad2D[3];
    s32 upper;      // 0x30
};

void func_001F5C0C(Spec_1E0978* dst, s32 value, s32 size);
s32 func_001E08F8(s8* s, s32* out);
extern u8 D_0024E879[];

s32 func_001E0978(s8* at, Spec_1E0978* spec, s32** va)
{
    s32 state = 0;
    s8* p = at;
    s32 next;

    func_001F5C0C(spec, 0, 0x34);
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
                    adv = func_001E08F8(p, &spec->width);
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
                    adv = func_001E08F8(p, &spec->prec);
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
                    if (D_0024E879[(s8)(u8)*p] & 1) {
                        a = 4;
                    }
                    spec->f24 = a;
                    d = *p;
                    l = (D_0024E879[d] & 1) ? d + 0x20 : d;
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
                    spec->upper = D_0024E879[e] & 1;
                    f = *p;
                    l = (D_0024E879[f] & 1) ? f + 0x20 : f;
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

struct Ctx_001E1A08 { u8 pad[0x10]; s32 count; };
struct Spec_001E1A08 {
    s32 f00; s32 f04; s32 f08; u8 pad0C[4]; s32 f10; s32 f14; s32 f18;
    s32 i1C; s32 i20; s32 i24; s32 i28; u8 ch; u8 pad2D[3]; s32 f30;
};
extern char D_0024E478[]; extern char D_0024E480[]; extern char D_0024E488[];
extern char D_0024E490[]; extern char D_0024E498[];

s32 func_001E2100(const char* s);
s32 func_001D7190(Ctx_001E1A08* c, const char* s, s32 n);
void func_001E0CD0(Spec_001E1A08* sp, Ctx_001E1A08* c, const char* s);
void func_001E1028(Spec_001E1A08* sp, Ctx_001E1A08* c, u64 v);
void func_001E17A8(Spec_001E1A08* sp, Ctx_001E1A08* c, s64 s);
void func_001E17A8(Spec_001E1A08* sp, Ctx_001E1A08* c, double value);
s32 func_001E1498(char* buf, s32 n, Spec_001E1A08* sp, double value);
void func_001E2218(char* p);
s64 func_001FD868(f32 f);

void func_001E1A08(Spec_001E1A08* sp, Ctx_001E1A08* c, u8** va, const char* fmt, s32 len) {
    u64 v;
    switch (sp->ch) {
    case '%':
        func_001D7190(c, (const char*)sp + 0x2C, 1);
        return;
    case 'c': {
        signed char buf[16];
        u8* p = *va;
        *va = p + 8;
        s32 ch = *(s8*)p;
        buf[0] = ch;
        func_001D7190(c, (const char*)buf, 1);
        return;
    }
    case 's': {
        u8* p = *va;
        *va = p + 8;
        func_001E0CD0(sp, c, *(const char**)p);
        return;
    }
    case 'p':
        sp->i1C = 8;
        sp->ch = 'x';
        sp->i20 = 0;
    case 'b': case 'd': case 'i': case 'o': case 'u': case 'x':
        switch (sp->i20) {
        case 0: case 1: { u8* p = *va; *va = p + 8; v = *(u32*)p; break; }
        case 2: { u8* p = *va; *va = p + 8; v = *(u64*)p; break; }
        }
        func_001E1028(sp, c, v);
        return;
    case 'e': case 'f': case 'g':
        if (sp->i24 != 0) {
            const char* s4 = D_0024E478;
            u8* a = *va;
            const char* s8 = D_0024E480;
            const char* s7 = D_0024E488;
            *va = a + 8;
            const char* s5 = D_0024E490;
            const char* s6 = D_0024E498;
            f32* fp = *(f32**)a;
            if (sp->i28 >= 2) {
                func_001D7190(c, s4, func_001E2100(s4));
            }
            for (s32 i = 0; i < sp->i28; ) {
                s32 next;
                if (i != 0) {
                    func_001D7190(c, s8, func_001E2100(s8));
                }
                next = i + 1;
                func_001D7190(c, s7, func_001E2100(s7));
                for (s32 j = 0; j < sp->i24; j++) {
                    if (j != 0) {
                        func_001D7190(c, s5, func_001E2100(s5));
                    }
                    func_001E17A8(sp, c, func_001FD868(*fp++));
                }
                func_001D7190(c, s6, func_001E2100(s6));
                i = next;
            }
            if (sp->i28 >= 2) {
                func_001D7190(c, s4, func_001E2100(s4));
            }
        } else {
            u8* p = *va;
            *va = p + 8;
            func_001E17A8(sp, c, *(s64*)p);
        }
        return;
    case 'n':
        switch (sp->i20) {
        case 0: { u8* p = *va; *va = p + 8; **(s32**)p = c->count; break; }
        case 1: { u8* p = *va; *va = p + 8; s16* q = *(s16**)p; s32 n = c->count; *q = n; break; }
        case 2: { u8* p = *va; *va = p + 8; **(s64**)p = c->count; break; }
        }
        return;
    default:
        func_001D7190(c, fmt, len);
        return;
    }
}

struct Ctx_1E0CD0;
s32 func_001D7190(Ctx_1E0CD0* ctx, const char* p, s32 n);
struct Ctx_1E0CD0 {
    void Pad(u8 ch, s32 count)
    {
        u8 buf = ch;
        while (count-- > 0) {
            if (func_001D7190(this, (const char*)&buf, 1) != 1) {
                break;
            }
        }
    }
};
struct Str_1E0CD0;

struct Obj_1E0CD0 {
    s32 f00;
    u8 p04[0x10 - 0x04];
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
};

extern u8 D_0024E2E0[];

s32 func_001E2100(Str_1E0CD0* p);


void func_001E17A8(Spec_001E1A08* spec, Ctx_001E1A08* ctx, double value)
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
    if (spec->i1C == 0 && spec->f14 == 0) {
        spec->i1C = 6;
    } else if (spec->f14 != 0 && spec->ch == 0x67) {
        spec->i1C = 1;
    }
    neg = value < 0.0;
    if (neg) value = 0.0 - value;
    sign[0] = 0;
    if (neg) *(u16*)sign = D_0024E3D0;
    else if (spec->f04) *(u16*)sign = D_0024E3D8;
    else if (spec->f08) *(u16*)sign = D_0024E3E0;
    slen = func_001E2100(sign);
    len = func_001E1498(buf, 0x1B5, spec, value);
    buf[len] = 0;
    if (spec->f30) func_001E2218(buf);
    width = spec->f18;
    total = slen + len;
    lead = 0;
    left = 0;
    if (total < width) {
        s32 pad = width - total;
        if (spec->f00) left = pad;
        else if (spec->f10 && len != 0) zeros = pad;
        else lead = pad;
    }
    padc[0] = ' ';
    n = lead;
    while (n-- > 0) {
        if (func_001D7190(ctx, padc, 1) != 1) break;
    }
    n = zeros;
    func_001D7190(ctx, sign, slen);
    padc[0] = '0';
    while (n-- > 0) {
        if (func_001D7190(ctx, padc, 1) != 1) break;
    }
    func_001D7190(ctx, buf, len);
    n = left;
    padc[0] = ' ';
    while (n-- > 0) {
        if (func_001D7190(ctx, padc, 1) != 1) break;
    }
}

void func_001E0CD0(Obj_1E0CD0* self, Ctx_1E0CD0* ctx, const char* str) {
    s32 n;
    s32 right;
    s32 left;
    u8 pad;

    if (str == 0) {
        str = (const char*)D_0024E2E0;
    }
    right = 0;
    n = func_001E2100((Str_1E0CD0*)str);
    left = 0;
    if (self->f1C != 0 && self->f1C < n) {
        n = self->f1C;
    } else if (self->f14 != 0) {
        n = 0;
    }
    if (n < self->f18) {
        pad = (self->f10 != 0) ? 0x30 : 0x20;
        s32 d = self->f18 - n;
        if (self->f00 != 0) {
            right = d;
        } else {
            left = d;
        }
    }
    ctx->Pad(pad, left);
    func_001D7190(ctx, str, n);
    ctx->Pad(0x20, right);
}

struct Obj_1E13D0 { u8 pad; };


f32 func_00205C78(f32 a, f32 b);
Obj_1E13D0* func_001FCDE0(Obj_1E13D0* self, u64 v);
Obj_1E13D0* func_001FCDE0(Obj_1E13D0* self, double v); // soft-float double in a1
Obj_1E13D0* func_001EAE78(Obj_1E13D0* self);
Obj_1E13D0* func_001FCD78(Obj_1E13D0* self, Obj_1E13D0* v);
s32 func_001FD410(Obj_1E13D0* self);

s8 func_001E13D0(Obj_1E13D0* self0, s32 a, s32 b)
{
    Obj_1E13D0* self = self0;
    s32 idx;
    if (a < b || a - 15 >= b) {
        idx = 0;
    } else {
        f32 t = func_00205C78(10.0f, (f32)(-b));
        Obj_1E13D0* p = func_001FCDE0(self, (u64)func_001FD868(t));
        self = func_001EAE78(p);
        p = func_001EAE78(func_001FCDE0(self, 0.1));
        p = func_001FCDE0(p, (u64)0x4024000000000000ULL);
        idx = func_001FD410(func_001FCD78(self, p));
    }
    return ((s8*)&D_00275940)[idx];
}
