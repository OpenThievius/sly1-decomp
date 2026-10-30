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
