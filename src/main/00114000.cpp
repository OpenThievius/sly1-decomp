// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_00115CA0(void* self, s32 value, s32 mode);

void* func_00115D78(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 1);
    return self;
}

void func_00115CA0(void* self, s32 value, s32 mode);

void* func_00115DA8(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 2);
    return self;
}

void func_00115CA0(void* self, s32 value, s32 mode);

void* func_00115DD8(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 3);
    return self;
}

void func_00115CA0(void* self, s32 value, s32 mode);

void* func_00115E08(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 4);
    return self;
}

void func_00115CA0(void* self, s32 value, s32 mode);

void* func_00115E38(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 5);
    return self;
}

void func_00115CA0(void* self, s32 value, s32 mode);

void* func_00115E68(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 6);
    return self;
}

void func_00115CA0(void* self, s32 value, s32 mode);

void* func_00115E98(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 7);
    return self;
}

struct Entry_115EC8 {
    s32 tag;
    union {
        s32 i;
        f32 f;
    } v;
};

struct Frame_115EC8 {
    u8 obj[0x10];
    f32 xy[2];
};

void func_0011B008(void* obj);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);
f32 func_00205778(f32 x, f32 y);
void* func_0011B5B0(void* obj, f32 x);

void* func_00115EC8(void* self, s32 unused, Entry_115EC8* e)
{
    Frame_115EC8 f;
    func_0011B008(&f);
    f32* out = f.xy;
    for (s32 i = 1; i >= 0; i--, e++) {
        if (e->tag == 0x15) {
            *out = e->v.f;
        } else {
            *out = (f32)e->v.i;
        }
        out++;
    }
    f32 d = func_00205778(f.xy[0], f.xy[1]);
    func_0011B5B0(&f, d);
    func_0011B018(self, &f);
    func_0011B060(&f, 2);
    return self;
}

struct Node_116600 {
    u8 pad[8];
    void* link;
};

struct Tmp_116600 {
    u8 bytes[0x10];
};

struct Src_116600 {
    s32 pad0;
    s32 a;
    s32 pad2;
    s32 b;
};

void func_0011B008(void* obj);
Node_116600* func_0011AF28(void);
void* func_0011C508(void);
void func_0011B740(void* a, void* b);
f32 func_001ED908(s32 a, s32 b, void* c);
void func_0011B6C0(void* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

void* func_00116600(void* ret, s32 unused, Src_116600* src)
{
    Tmp_116600 t;
    func_0011B008(&t);
    Node_116600* a = func_0011AF28();
    void* b = func_0011AF28();
    a->link = b;
    void* c = func_0011C508();
    func_0011B740(b, c);
    f32 d = func_001ED908(src->a, src->b, c);
    func_0011B5B0(a, d);
    func_0011B6C0(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Tmp_1166C0 {
    u8 bytes[0x10];
};

struct Src_1166C0 {
    s32 pad0;
    s32 a;
};

void func_0011B008(void* obj);
void* func_0011C618(void);
void func_00188770(s32 a, void* b);
void func_0011B788(void* obj, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

void* func_001166C0(void* ret, s32 unused, Src_1166C0* src)
{
    Tmp_1166C0 t;
    func_0011B008(&t);
    void* a = func_0011C618();
    func_00188770(src->a, a);
    func_0011B788(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Tmp_116740 {
    u8 bytes[0x10];
};

struct Src_116740 {
    s32 pad0;
    s32 a;
};

void func_0011B008(void* obj);
void* func_0011C618(void);
void func_00189AF0(s32 a, void* b);
void func_0011B788(void* obj, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

void* func_00116740(void* ret, s32 unused, Src_116740* src)
{
    Tmp_116740 t;
    func_0011B008(&t);
    void* a = func_0011C618();
    func_00189AF0(src->a, a);
    func_0011B788(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Tmp_1167C0 {
    u8 bytes[0x10];
};

struct Src_1167C0 {
    s32 pad0;
    s32 a;
    s32 pad2;
    s32 b;
};

void func_0011B008(void* obj);
void* func_0011C618(void);
void func_001891C0(s32 a, s32 b, void* c);
void func_0011B788(void* obj, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

void* func_001167C0(void* ret, s32 unused, Src_1167C0* src)
{
    Tmp_1167C0 t;
    func_0011B008(&t);
    void* a = func_0011C618();
    func_001891C0(src->a, src->b, a);
    func_0011B788(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Quad_114018 { s32 a, b, c, d; };

void func_0011B008(Quad_114018* q);
void func_0011B5F0(Quad_114018* q, int flag);
void func_0011B018(void* out, Quad_114018* q);
void func_0011B060(Quad_114018* q, int mode);

void* func_00114018(void* self, int unused, s32* kind)
{
    Quad_114018 q;
    func_0011B008(&q);
    func_0011B5F0(&q, *kind == 0x1C);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_114288 { s32 a, b, c, d; };

void func_0011B008(Quad_114288* q);
void func_0011B5F0(Quad_114288* q, int flag);
void func_0011B018(void* out, Quad_114288* q);
void func_0011B060(Quad_114288* q, int mode);

void* func_00114288(void* self, int unused, s32* kind)
{
    Quad_114288 q;
    func_0011B008(&q);
    s32 v = *kind;
    func_0011B5F0(&q, v == 0x1E || v == 0);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void func_001147B8(void* self, int a, void* b, void* c, int n);

void* func_00114858(void* self, int a, void* b, void* c)
{
    func_001147B8(self, a, b, c, 0x23);
    return self;
}

struct Vec_1158B8 { f32 x, y, z, w; };

void func_0011B008(void* self);
void* func_0011C968(void);
void func_0011B9A8(void* out, void* src);
void func_0011B0A8(void* self, void* other);
void func_0011B060(void* self, s32 n);
void func_0011B860(void* a, void* b);
void func_0011B018(void* dst, void* src);

void* func_001158B8(void* ret, s32 unused, void* src)
{
    Vec_1158B8 t;
    Vec_1158B8 u;
    func_0011B008(&t);
    f32* out = (f32*)func_0011C968();
    func_0011B9A8(&u, src);
    func_0011B0A8(&t, &u);
    func_0011B060(&u, 2);
    out[0] = t.y;
    func_0011B9A8(&u, (u8*)src + 8);
    func_0011B0A8(&t, &u);
    func_0011B060(&u, 2);
    out[1] = t.y;
    func_0011B9A8(&u, (u8*)src + 0x10);
    func_0011B0A8(&t, &u);
    func_0011B060(&u, 2);
    out[2] = t.y;
    func_0011B860(&t, out);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Vec_116DC8 { f32 x, y, z, w; };
struct Src_116DC8 { s32 pad0; f32* poly; s32 pad8; f32* range; };
void func_0011B008(void* self);
void func_0011B9A8(void* out, void* src);
void* func_0011B5B0(void* obj, f32 x);
void func_0011B060(void* self, s32 n);
void func_0011B018(void* dst, void* src);
void* func_00116DC8(void* ret, s32 unused, Src_116DC8* src)
{
    Vec_116DC8 t;
    Vec_116DC8 u;
    func_0011B008(&t);
    f32* poly = src->poly;
    f32* range = src->range;
    func_0011B9A8(&u, (u8*)src + 0x10);
    f32 k = u.y;
    f32 v = poly[0] + k * (poly[1] + k * poly[2]);
    f32 lo = range[0];
    f32 hi = range[1];
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    func_0011B5B0(&t, v);
    func_0011B060(&u, 2);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Tmp_1171F0 { s32 w[4]; };
struct Src_1171F0 { s32 pad0; f32 v; };

void func_0011B008(void* self);
void func_0011B570(void* self, s32 n);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* self, s32 n);

void* func_001171F0(void* ret, s32 unused, Src_1171F0* src)
{
    Tmp_1171F0 t;
    func_0011B008(&t);
    s32 n = (s32)(src->v + 0.5f);
    func_0011B570(&t, n);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Tmp_117880 { s32 w[4]; };
struct Obj_117880 { u8 pad[0x29C]; f32 value; };
struct Src_117880 { s32 pad0; Obj_117880* obj; };

void func_0011B008(void* self);
void func_0011B9A8(void* out, void* src);
void func_0011B060(void* self, s32 n);
void func_0011B018(void* dst, void* src);

void* func_00117880(void* ret, s32 unused, Src_117880* src)
{
    Tmp_117880 t;
    Tmp_117880 u;
    func_0011B008(&t);
    Obj_117880* obj = src->obj;
    func_0011B9A8(&u, (u8*)src + 8);
    f32 f = ((f32*)&u)[1];
    func_0011B060(&u, 2);
    obj->value = f;
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Quad_114080 { s32 a, b, c, d; };
struct Tag_114080 { s32 tag; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B5F0(void* q, s32 flag);

void* func_00114080(void* self, s32 unused, Tag_114080* p)
{
    Quad_114080 q;
    func_0011B008(&q);
    func_0011B5F0(&q, p->tag == 0x16);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_1140E8 { s32 a, b, c, d; };
struct Tag_1140E8 { s32 tag; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B5F0(void* q, s32 flag);

void* func_001140E8(void* self, s32 unused, Tag_1140E8* p)
{
    Quad_1140E8 q;
    func_0011B008(&q);
    func_0011B5F0(&q, p->tag == 0x17);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_114150 { s32 a, b, c, d; };
struct Tag_114150 { s32 tag; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B5F0(void* q, s32 flag);

void* func_00114150(void* self, s32 unused, Tag_114150* p)
{
    Quad_114150 q;
    func_0011B008(&q);
    func_0011B5F0(&q, p->tag == 0x18);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

// Calls the common builder with kind 0x63 and returns its first argument.
void* func_00117910(void* ret, s32 a1, void* src, s32 a3, s32 kind);

void* func_00117A30(void* ret, s32 a1, void* src, s32 a3)
{
    func_00117910(ret, a1, src, a3, 0x63);
    return ret;
}

// Calls the common builder with kind 0x64 and returns its first argument.
void* func_00117910(void* ret, s32 a1, void* src, s32 a3, s32 kind);

void* func_00117A60(void* ret, s32 a1, void* src, s32 a3)
{
    func_00117910(ret, a1, src, a3, 0x64);
    return ret;
}

// Calls the common builder with kind 0x65 and returns its first argument.
void* func_00117910(void* ret, s32 a1, void* src, s32 a3, s32 kind);

void* func_00117A90(void* ret, s32 a1, void* src, s32 a3)
{
    func_00117910(ret, a1, src, a3, 0x65);
    return ret;
}

// Calls the common builder with kind 0x66 and returns its first argument.
void* func_00117910(void* ret, s32 a1, void* src, s32 a3, s32 kind);

void* func_00117AC0(void* ret, s32 a1, void* src, s32 a3)
{
    func_00117910(ret, a1, src, a3, 0x66);
    return ret;
}

struct Handle_1141B8 { s32 word; u8 pad[12]; };

void func_0011B008(Handle_1141B8* h);
void func_0011B018(void* dst, Handle_1141B8* src);
void func_0011B060(Handle_1141B8* h, int mode);
void func_0011B5F0(Handle_1141B8* h, int flag);

void* func_001141B8(void* dst, int unused, s32* key)
{
    Handle_1141B8 a;
    func_0011B008(&a);
    func_0011B5F0(&a, *key == 0x19);
    func_0011B018(dst, &a);
    func_0011B060(&a, 2);
    return dst;
}

struct Handle_114220 { s32 word; u8 pad[12]; };

void func_0011B008(Handle_114220* h);
void func_0011B018(void* dst, Handle_114220* src);
void func_0011B060(Handle_114220* h, int mode);
void func_0011B5F0(Handle_114220* h, int flag);

void* func_00114220(void* dst, int unused, s32* key)
{
    Handle_114220 a;
    func_0011B008(&a);
    func_0011B5F0(&a, *key == 0x1A);
    func_0011B018(dst, &a);
    func_0011B060(&a, 2);
    return dst;
}

struct Entry_1156B0 { u8 pad0[4]; s32 index; u8 pad1[4]; s32 value; };
struct Var_1156B0 { s32 tag; s32 value; u8 pad[8]; };

void func_0011B008(void* self);
void func_0011B538(void* self, s32 n);
void func_0011B018(void* out, void* src);
void func_0011B060(void* self, s32 mode);
void func_001C0C08(s32 index, s32 value);

void* func_001156B0(void* self, s32, Entry_1156B0* src)
{
    Var_1156B0 q;
    func_001C0C08(src->index, src->value);
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Entry_115710 { s32 tag; s32 word; };
struct Var_115710 { s32 tag; f32 value; u8 pad[8]; };

void* func_0011C748();
void func_0011B9A8(void* out, void* src);
void func_0011B0A8(void* dst, void* src);
void func_0011B060(void* self, s32 mode);
void func_0011B7D0(void* self, void* ptr);
void func_0011B018(void* out, void* src);
void func_0011B008(void* self);

void* func_00115710(void* self, s32, Entry_115710* in)
{
    Var_115710 a;
    Var_115710 b;
    f32* base;
    f32* out;
    s32 n = 2;
    func_0011B008(&a);
    Entry_115710* p = in;
    base = (f32*)func_0011C748();
    out = base;
    do {
        func_0011B9A8(&b, p);
        p++;
        func_0011B0A8(&a, &b);
        n--;
        func_0011B060(&b, 2);
        *out++ = a.value;
    } while (n >= 0);
    func_0011B7D0(&a, base);
    func_0011B018(self, &a);
    func_0011B060(&a, 2);
    return self;
}

struct Entry_1157E0 { s32 tag; s32 word; };
struct Var_1157E0 { s32 tag; f32 value; u8 pad[8]; };

void* func_0011C858();
void func_0011B9A8(void* out, void* src);
void func_0011B0A8(void* dst, void* src);
void func_0011B060(void* self, s32 mode);
void func_0011B818(void* self, void* ptr);
void func_0011B018(void* out, void* src);
void func_0011B008(void* self);

void* func_001157E0(void* self, s32, Entry_1157E0* in)
{
    Var_1157E0 a;
    Var_1157E0 b;
    f32* out;
    func_0011B008(&a);
    out = (f32*)func_0011C858();
    func_0011B9A8(&b, in);
    func_0011B0A8(&a, &b);
    func_0011B060(&b, 2);
    out[0] = a.value;
    func_0011B9A8(&b, in + 1);
    func_0011B0A8(&a, &b);
    func_0011B060(&b, 2);
    out[1] = a.value;
    func_0011B818(&a, out);
    func_0011B018(self, &a);
    func_0011B060(&a, 2);
    return self;
}

union Word_115B78 { s32 i; f32 f; };
struct Entry_115B78 { s32 tag; Word_115B78 word; };
struct Var_115B78 { s32 tag; f32 value; u8 pad[8]; };

void func_0011B008(void* self);
void func_0011B018(void* out, void* src);
void func_0011B060(void* self, s32 mode);
void func_001F66F8(s32 v);

void* func_00115B78(void* self, s32, Entry_115B78* e)
{
    Var_115B78 q;
    func_0011B008(&q);
    if (e->tag == 0x14) {
        func_001F66F8(e->word.i);
    } else {
        func_001F66F8((s32)e->word.f);
    }
    q.tag = 0x22;
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_1146E0 { s32 a, b, c, d; };
struct Src_1146E0 { s32 pad0; Quad_1146E0* other; };

void func_0011B008(Quad_1146E0* q);
void func_0011B018(void* dst, Quad_1146E0* src);
void func_0011B060(Quad_1146E0* q, int mode);
void func_0011B0A8(Quad_1146E0* a, Quad_1146E0* b);

void* func_001146E0(void* self, void* unused, Src_1146E0* src)
{
    Quad_1146E0 q;
    func_0011B008(&q);
    func_0011B0A8(&q, src->other);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_147B8 { s32 a, b, c, d; };
struct Args_147B8 { s32 pad0; Quad_147B8* p; Quad_147B8 q; };

void func_0011B008(Quad_147B8* q);
void func_0011B018(void* dst, Quad_147B8* src);
void func_0011B060(Quad_147B8* q, int mode);
void func_0011B0A8(Quad_147B8* a, Quad_147B8* b);
void func_0011B538(Quad_147B8* q, int n);

void* func_001147B8(void* self, s32 u1, Args_147B8* src, s32 u3, s32 mode)
{
    Quad_147B8 q;
    Quad_147B8* p;
    func_0011B008(&q);
    p = src->p;
    if (mode == 0x23) {
        func_0011B0A8(p, &src->q);
    } else {
        if (src->q.a == 0x1E) {
            p->c = src->q.b;
        } else {
            p->c = 0;
        }
    }
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_001147B8(void* self, s32 u1, void* src, s32 u3, s32 mode);

void* func_00114888(void* self, s32 u1, void* src, s32 u3)
{
    (void)func_001147B8(self, u1, src, u3, 0x24);
    return self;
}

struct Src_116A88 { s32 pad0; void* p; };
struct Tmp_116A88 { u8 bytes[0x10]; };

void func_0011B008(void* obj);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);
void func_0011B740(void* a, void* b);
void* func_0011C508(void);
void func_00188FD8(void* a, void* b);

void* func_00116A88(void* ret, s32 unused, Src_116A88* src)
{
    Tmp_116A88 t;
    func_0011B008(&t);
    void* c = func_0011C508();
    func_00188FD8(src->p, c);
    func_0011B740(&t, c);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Src_116B08 { s32 pad0; void* p; };
struct Tmp_116B08 { u8 bytes[0x10]; };
struct Vec_116B08 { f32 v[4]; };

void func_0011B008(void* obj);
void* func_0011C508(void);
void func_0011B740(void* a, void* b);
void func_00188D28(void* a, void* b, void* c);
void func_0011B6C0(void* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

void* func_00116B08(void* ret, s32 unused, Src_116B08* src)
{
    Tmp_116B08 t;
    Vec_116B08 vec;
    func_0011B008(&t);
    void* a = func_0011AF28();
    void* b = func_0011AF28();
    void* c = func_0011C508();
    func_0011B740(b, c);
    *(void**)((u8*)a + 8) = b;
    func_00188D28(src->p, &vec, c);
    func_0011B5B0(a, vec.v[0]);
    func_0011B6C0(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Src_116C80 { s32 pad0; void* p; };
struct Tmp_116C80 { u8 bytes[0x10]; };
struct Vec_116C80 { u8 bytes[0x30]; };

void func_0011B008(void* obj);
void* func_0011C618(void);
void func_00189378(void* sub, s32 zero, void* out);
void func_00188B08(void* a, void* b, void* c);
void func_0011B788(void* obj, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

void* func_00116C80(void* ret, s32 unused, Src_116C80* src)
{
    Tmp_116C80 t;
    Vec_116C80 v;
    func_0011B008(&t);
    void* a = func_0011C618();
    func_00189378(src->p, 0, &v);
    func_00188B08((u8*)src->p + 0x30, &v, a);
    func_0011B788(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Coef_116D20 { f32 a; f32 b; f32 c; };
struct Src_116D20 { s32 pad0; Coef_116D20* coef; };
struct Tmp_116D20 { u8 bytes[0x10]; };
struct Vec_116D20 { f32 v[4]; };

void func_0011B008(void* obj);
void func_0011B9A8(void* out, void* src);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

void* func_00116D20(void* ret, s32 unused, Src_116D20* src)
{
    Tmp_116D20 t;
    Vec_116D20 v;
    func_0011B008(&t);
    Coef_116D20* k = src->coef;
    func_0011B9A8(&v, (u8*)src + 8);
    f32 x = v.v[1];
    f32 r = k->a + x * (k->b + x * k->c);
    func_0011B5B0(&t, r);
    func_0011B060(&v, 2);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Quad_1148B8 { s32 a, b, c, d; };
struct Node_1148B8 { s32 a, b; Node_1148B8* next; };
struct Rec_1148B8 { s32 tag; Node_1148B8* head; };

void func_0011B008(Quad_1148B8* q);
void func_0011B570(Quad_1148B8* q, int n);
void func_0011B018(void* self, Quad_1148B8* q);
void func_0011B060(Quad_1148B8* q, int mode);

void* func_001148B8(void* self, void* unused, Rec_1148B8* p)
{
    Quad_1148B8 q;
    func_0011B008(&q);
    s32 n = 0;
    if (p->tag == 0x1E && p->head) {
        Node_1148B8* node = p->head;
        do {
            node = node->next;
            n++;
        } while (node);
    }
    func_0011B570(&q, n);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_114950 { s32 a, b, c, d; };
struct Node_114950 { s32 a, b; Node_114950* next; };
struct Sub_114950 { s32 pad; s32 idx; };
struct Rec_114950 { s32 tag; Node_114950* head; Sub_114950 sub; };

void func_0011B008(Quad_114950* q);
void func_0011B538(Quad_114950* q, int n);
void func_0011B0A8(Quad_114950* a, Node_114950* b);
void func_0011B018(void* self, Quad_114950* q);
void func_0011B060(Quad_114950* q, int mode);

void* func_00114950(void* self, void* unused, Rec_114950* p)
{
    Quad_114950 q;
    func_0011B008(&q);
    func_0011B538(&q, 0);
    if (p->tag == 0x1E) {
        Node_114950* node = p->head;
        Sub_114950* sub = &p->sub;
        s32 i = 0;
        while (node != 0) {
            if (i == sub->idx) {
                func_0011B0A8(&q, node);
                break;
            }
            node = node->next;
            i++;
        }
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Vec_116EA8 { f32 x, y, z, w; };

void* func_0011C748();
void func_0011B008(void* v);
void* func_0011B9A8(void* out, u8* src);
void func_0011B060(void* v, int mode);
void func_0011B018(void* dst, void* src);
void func_0011B7D0(void* self, void* ptr);
void func_001EB018(void* a0, f32 x, f32 y, f32 z, f32 w);

void* func_00116EA8(void* self, s32 unused, u8* src)
{
    Vec_116EA8 q0;
    Vec_116EA8 q1;
    Vec_116EA8 q2;
    Vec_116EA8 q3;
    Vec_116EA8 q4;
    func_0011B008(&q0);
    void* p = func_0011C748();
    (void)func_0011B9A8(&q1, src);
    f32 x = q1.y;
    (void)func_0011B9A8(&q2, src + 8);
    f32 y = q2.y;
    (void)func_0011B9A8(&q3, src + 0x10);
    f32 z = q3.y;
    (void)func_0011B9A8(&q4, src + 0x18);
    f32 w = q4.y;
    func_001EB018(p, x, y, z, w);
    func_0011B060(&q4, 2);
    func_0011B060(&q3, 2);
    func_0011B060(&q2, 2);
    func_0011B060(&q1, 2);
    func_0011B7D0(&q0, p);
    func_0011B018(self, &q0);
    func_0011B060(&q0, 2);
    return self;
}

struct Vec_116FE8 { f32 x, y, z, w; };
struct Src_116FE8 { s32 pad0; void* p4; };

void func_0011B008(void* v);
void* func_0011B9A8(void* out, u8* src);
f32 func_001EB0F8(void* span, f32 x);
void* func_0011B5B0(void* obj, f32 x);
void func_0011B060(void* v, int mode);
void func_0011B018(void* dst, void* src);
void* func_00116FE8(void* self, s32 unused, Src_116FE8* src)
{
    Vec_116FE8 q0;
    Vec_116FE8 q1;
    func_0011B008(&q0);
    void* span = src->p4;
    (void)func_0011B9A8(&q1, (u8*)src + 8);
    f32 r = func_001EB0F8(span, q1.y);
    (void)func_0011B5B0(&q0, r);
    func_0011B060(&q1, 2);
    func_0011B018(self, &q0);
    func_0011B060(&q0, 2);
    return self;
}

struct Quad_1143C8 { s32 a, b, c, d; };

void func_0011B008(Quad_1143C8* q);
void func_0011B5F0(Quad_1143C8* q, int flag);
void func_0011B018(void* out, Quad_1143C8* q);
void func_0011B060(Quad_1143C8* q, int mode);

void* func_001143C8(void* self, int unused, s32* value)
{
    Quad_1143C8 q;
    func_0011B008(&q);
    int flag = 0;
    if (value[0] == 0x20) {
        flag = value[1] == 0;
    }
    func_0011B5F0(&q, flag);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_114438 { s32 a, b, c, d; };

void func_0011B008(Quad_114438* q);
void func_0011B5F0(Quad_114438* q, int flag);
void func_0011B018(void* out, Quad_114438* q);
void func_0011B060(Quad_114438* q, int mode);

void* func_00114438(void* self, int unused, s32* value)
{
    Quad_114438 q;
    func_0011B008(&q);
    func_0011B5F0(&q, value[0] == 0x21);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Pair_115440 { s32 a; s32 b; };
struct Frame_115440 { s32 w[4]; };

void func_0011B008(Frame_115440* f);
void func_0011B018(void* dst, Frame_115440* src);
void func_0011B060(Frame_115440* f, s32 mode);
void func_0011B9A8(Frame_115440* out, Pair_115440* src);
void func_0011B0A8(Frame_115440* a, Frame_115440* b);
void func_0011B740(Frame_115440* a, f32* out);
void* func_0011C508(void);

void* func_00115440(void* self, void* unused, Pair_115440* src)
{
    Frame_115440 a;
    Frame_115440 b;
    s32 count = 2;
    func_0011B008(&a);
    Pair_115440* in = src;
    f32* base = (f32*)func_0011C508();
    f32* out = base;
    do {
        func_0011B9A8(&b, in);
        in++;
        func_0011B0A8(&a, &b);
        count--;
        func_0011B060(&b, 2);
        *out = *(f32*)&a.w[1];
        out++;
    } while (count >= 0);
    func_0011B740(&a, base);
    func_0011B018(self, &a);
    func_0011B060(&a, 2);
    return self;
}

union Cell_115C00 { f32 f; s32 i; };
struct Tagged_115C00 { s32 tag; Cell_115C00 cell; };
struct Pair_115C00 { Tagged_115C00 x; Tagged_115C00 y; };
struct Frame_115C00 { s32 w[4]; };

void func_0011B008(Frame_115C00* f);
void func_0011B018(void* dst, Frame_115C00* src);
void func_0011B060(Frame_115C00* f, s32 mode);
void func_0011B5B0(Frame_115C00* f, f32 v);
f32 func_001EAAE0(f32 a, f32 b);

void* func_00115C00(void* self, void* unused, Pair_115C00* p)
{
    Frame_115C00 f;
    func_0011B008(&f);
    f32 x;
    f32 y;
    if (p->x.tag == 0x14) {
        x = (f32)p->x.cell.i;
    } else {
        x = p->x.cell.f;
    }
    if (p->y.tag == 0x14) {
        y = (f32)p->y.cell.i;
    } else {
        y = p->y.cell.f;
    }
    f32 r = func_001EAAE0(x, y);
    func_0011B5B0(&f, r);
    func_0011B018(self, &f);
    func_0011B060(&f, 2);
    return self;
}

struct Tmp_117180 { s32 w[4]; };
struct Src_117180 { s32 pad0; f32 v; };

void func_0011B008(void* self);
void func_0011B570(void* self, s32 n);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* self, s32 n);

void* func_00117180(void* ret, s32 unused, Src_117180* src)
{
    Tmp_117180 t;
    func_0011B008(&t);
    s32 n = (s32)(src->v + 1.0f);
    func_0011B570(&t, n);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Tmp_117260 { s32 w[4]; };
struct Src_117260 { s32 pad0; f32 v; };

void func_0011B008(void* self);
void func_0011B570(void* self, s32 n);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* self, s32 n);

void* func_00117260(void* ret, s32 unused, Src_117260* src)
{
    Tmp_117260 t;
    func_0011B008(&t);
    s32 n = (s32)src->v;
    func_0011B570(&t, n);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Quad_1144A0 { s32 a, b, c, d; };

void func_0011B008(Quad_1144A0* q);
void func_0011B5F0(Quad_1144A0* q, int flag);
void func_0011B018(void* out, Quad_1144A0* q);
void func_0011B060(Quad_1144A0* q, int mode);

void* func_001144A0(void* self, int unused, s32* p)
{
    Quad_1144A0 q;
    func_0011B008(&q);
    s32 v = *p;
    int flag = (v == 0x1F || v == 0x1D);
    func_0011B5F0(&q, flag);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_1145C8 { s32 a, b, c, d; };

void func_0011B008(Quad_1145C8* q);
void func_0011B5F0(Quad_1145C8* q, int flag);
void func_0011B018(void* out, Quad_1145C8* q);
void func_0011B060(Quad_1145C8* q, int mode);

void* func_001145C8(void* self, int unused, s32* p)
{
    Quad_1145C8 q;
    func_0011B008(&q);
    int flag = 0;
    if (p[0] == 0x1B) {
        flag = (u32)p[1] < 1;
    }
    func_0011B5F0(&q, flag);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

union Cell_115CA0 { f32 f; s32 i; };
struct Tagged_115CA0 { s32 tag; Cell_115CA0 cell; };
struct Frame_115CA0 { s32 w[4]; };
typedef f32 (*FloatFn_115CA0)(f32 v);
extern FloatFn_115CA0 D_00259938[];

void func_0011B008(Frame_115CA0* f);
void func_0011B018(void* dst, Frame_115CA0* src);
void func_0011B060(Frame_115CA0* f, s32 mode);
void func_0011B5B0(Frame_115CA0* f, f32 v);

void* func_00115CA0(void* self, Tagged_115CA0* src, s32 index)
{
    Frame_115CA0 f;
    func_0011B008(&f);
    f32 v;
    if (src->tag == 0x15) {
        v = src->cell.f;
    } else {
        v = (f32)src->cell.i;
    }
    f32 r = D_00259938[index](v);
    func_0011B5B0(&f, r);
    func_0011B018(self, &f);
    func_0011B060(&f, 2);
    return self;
}

union Cell_115D48 { f32 f; s32 i; };
struct Tagged_115D48 { s32 tag; Cell_115D48 cell; };

void* func_00115CA0(void* self, Tagged_115D48* src, s32 index);

void* func_00115D48(void* self, s32 unused, Tagged_115D48* src)
{
    func_00115CA0(self, src, 0);
    return self;
}

union Num_1172C8 { s32 i; f32 f; };
struct Value_1172C8 { s32 type; Num_1172C8 num; s32 pad8; s32 padC; };
struct Quad_1172C8 { s32 type; Num_1172C8 num; s32 c; s32 d; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 mode);
void func_0011B570(void* q, s32 v);

void* func_001172C8(void* dst, int unused, Value_1172C8* p)
{
    Quad_1172C8 q;
    func_0011B008(&q);
    if (p->type == 20) {
        s32 v = p->num.i; v = v < 0 ? -v : v;
        func_0011B570(&q, v);
    } else {
        f32 v = p->num.f;
        if (v < 0.0f) {
            v = -v;
        }
        func_0011B5B0(&q, v);
    }
    func_0011B018(dst, &q);
    func_0011B060(&q, 2);
    return dst;
}

void* func_00114B80(void* self, void* unused, void* value)
{
    func_0011B018(self, value);
    return self;
}

struct Quad_114300 { s32 a, b, c, d; };
struct Src_114300 { s32 flag; };

void func_0011B008(Quad_114300* q);
s32 func_0011B5F0(Quad_114300* q, s32 flag);
void func_0011B018(void* dst, Quad_114300* src);
void func_0011B060(Quad_114300* q, int mode);

void* func_00114300(void* self, s32 unused, Src_114300* src)
{
    Quad_114300 q;
    func_0011B008(&q);
    (void)func_0011B5F0(&q, src->flag == 0);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_114360 { s32 a, b, c, d; };
struct Src_114360 { s32 flag; };

void func_0011B008(Quad_114360* q);
s32 func_0011B5F0(Quad_114360* q, s32 flag);
void func_0011B018(void* dst, Quad_114360* src);
void func_0011B060(Quad_114360* q, int mode);

void* func_00114360(void* self, s32 unused, Src_114360* src)
{
    Quad_114360 q;
    func_0011B008(&q);
    (void)func_0011B5F0(&q, (src->flag ^ 0x20) == 0);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_114638 { s32 a, b, c, d; };
struct Node_114638 { u8 pad[8]; s32 val; };
struct Src_114638 { u8 pad[8]; s32 kind; s32 val; };
struct Sub_114638 { s32 pad; s32 val; };

void func_0011B008(Quad_114638* q);
void func_0011B0A8(void* node, Src_114638* src);
void func_0011B6C0(Quad_114638* q, void* node);
void func_0011B018(void* dst, Quad_114638* src);
void func_0011B060(Quad_114638* q, int mode);

void* func_00114638(void* self, s32 unused, Src_114638* src)
{
    Quad_114638 q;
    func_0011B008(&q);
    Node_114638* node = (Node_114638*)func_0011AF28();
    func_0011B0A8(node, src);
    s32 kind = src->kind;
    src = (Src_114638*)((u8*)src + 8);
    if (kind == 0) {
        node->val = 0;
    } else if (kind == 0x1E) {
        node->val = ((Sub_114638*)src)->val;
    }
    func_0011B6C0(&q, node);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Tmp_115398 { u8 bytes[0x10]; };

void func_0011B008(void* obj);
void func_0011B0A8(void* a, void* b);
void func_0011A080(void* t, void* n, s32 c);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

void* func_00115398(void* ret, s32 unused, void* src, s32 c)
{
    Tmp_115398 t;
    Tmp_115398 u;
    func_0011B008(&t);
    void* n = func_0011AF28();
    func_0011B0A8(n, src);
    func_0011A080(&u, n, c);
    func_0011B0A8(&t, &u);
    func_0011B060(&u, 2);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Quad_1169E8 { s32 a, b, c, d; };
struct __attribute__((aligned(16))) Block_1169E8 { s32 w[16]; };
struct Src_1169E8 { s32 f0; Block_1169E8* f4; };

void func_0011B008(Quad_1169E8* q);
void func_0011B018(void* dst, Quad_1169E8* src);
void func_0011B060(Quad_1169E8* q, int mode);
void* func_0011C618(void);
void func_001884C0(void* p);
void func_0011B788(Quad_1169E8* q, void* b);

void* func_001169E8(void* self, void* x, Src_1169E8* src)
{
    Quad_1169E8 q;
    void* obj;
    func_0011B008(&q);
    obj = func_0011C618();
    *(Block_1169E8*)obj = *src->f4;
    func_001884C0(obj);
    func_0011B788(&q, obj);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_117E20 { s32 a, b, c, d; };

void func_0011B008(Quad_117E20* q);
void func_0011B018(void* dst, Quad_117E20* src);
void func_0011B060(Quad_117E20* q, int mode);
s32 func_0011B8A8(Quad_117E20* q, s32 v);
void* func_001925F0(void);

void* func_00117E20(void* self)
{
    Quad_117E20 q;
    func_0011B008(&q);
    (void)func_0011B8A8(&q, (s32)func_001925F0());
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_114518 { s32 a, b, c, d; };
struct Frame_114518 { Quad_114518 q; f32 out[3]; };
union Bits_114518 { s32 i; f32 f; };
struct Elem_114518 { s32 tag; Bits_114518 v; };

void func_0011B008(Quad_114518* q);
void func_0011B018(void* dst, Quad_114518* src);
void func_0011B060(Quad_114518* q, int mode);
s32 func_001EAC68(f32 a, f32 b, f32 c);
s32 func_0011B5F0(Quad_114518* q, s32 flag);

void* func_00114518(void* self, s32 unused, Elem_114518* e)
{
    Frame_114518 f;
    func_0011B008(&f.q);
    for (s32 k = 0; k < 3; k++) {
        if (e[k].tag == 0x14) {
            f.out[k] = (f32)e[k].v.i;
        } else {
            f.out[k] = e[k].v.f;
        }
    }
    s32 flag = func_001EAC68(f.out[0], f.out[1], f.out[2]);
    (void)func_0011B5F0(&f.q, flag);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_116520 { s32 a, b, c, d; };
struct Value_116520 { s32 tag; f32 payload; };
struct Obj4_116520 { s32 pad0; void* f4; };
struct Src_116520 { s32 pad0; void* f4; s32 pad8; void* fC; Value_116520 f10; void* f18; void* f1C; };
struct Frame_116520 { Quad_116520 q; Value_116520 v; };

void func_0011B008(Quad_116520* q);
void func_0011B018(void* dst, Quad_116520* src);
void func_0011B060(void* q, int mode);
void func_0011B9A8(void* out, void* src);
void func_0011B740(Quad_116520* q, void* p);
void* func_0011C508(void);
void func_001EDEF0(void* a0, void* a1, void* a2, void* a3, f32 f);

void* func_00116520(void* self, s32 unused, Src_116520* src)
{
    Frame_116520 f;
    func_0011B008(&f.q);
    void* p = func_0011C508();
    void* s3;
    if (src->f18 == 0) {
        s3 = 0;
    } else {
        s3 = ((Obj4_116520*)src->f1C)->f4;
    }
    void* s1 = src->f4;
    void* fc = src->fC;
    func_0011B9A8(&f.v, &src->f10);
    func_001EDEF0(s1, fc, p, s3, f.v.payload);
    func_0011B060(&f.v, 2);
    func_0011B740(&f.q, p);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_117080 { s32 a, b, c, d; };
struct Value_117080 { s32 tag; f32 payload; };
struct Src_117080 { s32 pad0; void* f4; Value_117080 f8; };
struct Frame_117080 { Quad_117080 q; Value_117080 v; };

void func_0011B008(Quad_117080* q);
void func_0011B018(void* dst, Quad_117080* src);
void func_0011B060(void* q, int mode);
void func_0011B9A8(void* out, void* src);
s32 func_001EB050(void* target, f32 scale);
s32 func_0011B5F0(Quad_117080* q, s32 flag);

void* func_00117080(void* self, s32 unused, Src_117080* src)
{
    Frame_117080 f;
    func_0011B008(&f.q);
    void* s1 = src->f4;
    func_0011B9A8(&f.v, &src->f8);
    s32 flag = func_001EB050(s1, f.v.payload);
    (void)func_0011B5F0(&f.q, flag);
    func_0011B060(&f.v, 2);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_117118 { s32 a, b, c, d; };
struct In_117118 { s32 pad0; f32 f4; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, int mode);
void func_0011B570(void* q, s32 v);

void* func_00117118(void* self, s32 unused, In_117118* x)
{
    Quad_117118 q;
    func_0011B008(&q);
    func_0011B570(&q, (s32)x->f4);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_117BC8 { s32 a, b, c, d; };
struct In_117BC8 { u8 pad0[4]; s32 w4; s32 w8; s32 wc; };

extern void* D_00275710;

void func_0011B008(Quad_117BC8* q);
s32 func_0011B8A8(Quad_117BC8* q, s32 v);
void func_0011B018(void* dst, Quad_117BC8* src);
void func_0011B060(Quad_117BC8* q, int mode);
s32 func_0015A418(void* host, s32 a1, s32 a2, s32 ctx);

void* func_00117BC8(void* out, s32 unused, In_117BC8* in)
{
    Quad_117BC8 q;
    s32 r;
    func_0011B008(&q);
    s32 flag = 0x105;
    s32 k = 0x101;
    if (in->wc != 0) flag = k;
    r = func_0015A418(D_00275710, flag, in->w4, in->wc);
    func_0011B8A8(&q, r);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_117D00 { s32 a, b, c, d; };
struct In_117D00 { u8 pad0[4]; s32 w4; s32 w8; s32 wc; };

extern void* D_00275710;

void func_0011B008(Quad_117D00* q);
s32 func_0011B8A8(Quad_117D00* q, s32 v);
void func_0011B018(void* dst, Quad_117D00* src);
void func_0011B060(Quad_117D00* q, int mode);
s32 func_0015A418(void* host, s32 a1, s32 a2, s32 ctx);

void* func_00117D00(void* out, s32 unused, In_117D00* in)
{
    Quad_117D00 q;
    s32 r;
    func_0011B008(&q);
    r = func_0015A418(D_00275710, 0x104, in->w4, in->wc);
    func_0011B8A8(&q, r);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_117E78 { s32 a, b, c, d; };


s32 func_0011B008(Quad_117E78* q);
void func_0011B018(void* dst, Quad_117E78* src);
void func_0011B060(Quad_117E78* q, int mode);
void func_0011B8A8(Quad_117E78* q, s32 v);

void* func_00117E78(void* self)
{
    Quad_117E78 q;
    s32 r = func_0011B008(&q);
    func_0011B8A8(&q, (s32)D_00275710);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_117ED0 { s32 a, b, c, d; };

extern s32 D_00261990;

s32 func_0011B008(Quad_117ED0* q);
void func_0011B018(void* dst, Quad_117ED0* src);
void func_0011B060(Quad_117ED0* q, int mode);
void func_0011B8A8(Quad_117ED0* q, s32 v);

void* func_00117ED0(void* self)
{
    Quad_117ED0 q;
    s32 r = func_0011B008(&q);
    func_0011B8A8(&q, D_00261990);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_114740 { s32 a, b, c, d; };
struct Inner_114740 { u8 pad[8]; s32 val; };
struct Src_114740 { u8 pad[4]; Inner_114740* inner; };

s32 func_0011B008(Quad_114740* q);
void func_0011B6C0(Quad_114740* q, s32 v);
void func_0011B538(Quad_114740* q, s32 n);
void func_0011B018(void* dst, Quad_114740* src);
void func_0011B060(Quad_114740* q, int mode);

void* func_00114740(void* self, s32 unused, Src_114740* src)
{
    Quad_114740 q;
    (void)func_0011B008(&q);
    Inner_114740* in = src->inner;
    s32 v = in->val;
    if (v != 0) {
        func_0011B6C0(&q, v);
    } else {
        func_0011B538(&q, 0);
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Tmp_116978 { u8 bytes[0x10]; };
struct __attribute__((aligned(16))) Quad_116978 { s32 a, b, c, d; };
struct Src_116978 { s32 pad0; void* p; };

void func_0011B008(void* obj);
void* func_0011C508(void);
s32 func_0011B740(Tmp_116978* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

void* func_00116978(void* ret, s32 unused, Src_116978* src)
{
    Tmp_116978 t;
    func_0011B008(&t);
    void* c = func_0011C508();
    *(Quad_116978*)c = *(Quad_116978*)((u8*)src->p + 0x30);
    (void)func_0011B740(&t, c);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

struct Node_117360 { s32 tag; union { s32 i; f32 f; } v; Node_117360* next; Node_117360* child; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, int mode);
s32 func_0011B0A8(Node_117360* a, void* b);

void* func_00117360(void* self, s32 unused, Node_117360* x)
{
    Node_117360 q;
    func_0011B008(&q);
    (void)func_0011B0A8(&q, x);
    if (x->next == 0) {
        x = 0;
    } else {
        x = x->child;
    }
    if (x != 0) {
        do {
            if (q.tag == 0x14) {
                if (x->tag == 0x14) {
                    if (q.v.i < x->v.i) {
                        func_0011B0A8(&q, x);
                    }
                } else {
                    if ((f32)q.v.i < x->v.f) {
                        func_0011B0A8(&q, x);
                    }
                }
            } else {
                if (x->tag == 0x14) {
                    if (q.v.f < (f32)x->v.i) {
                        func_0011B0A8(&q, x);
                    }
                } else {
                    f32 pf = x->v.f;
                    if (q.v.f < pf) {
                        func_0011B0A8(&q, x);
                    }
                }
            }
            x = x->next;
        } while (x != 0);
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Node_117478 { s32 tag; union { s32 i; f32 f; } v; Node_117478* next; Node_117478* child; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, int mode);
s32 func_0011B0A8(Node_117478* a, void* b);

void* func_00117478(void* self, s32 unused, Node_117478* x)
{
    Node_117478 q;
    func_0011B008(&q);
    (void)func_0011B0A8(&q, x);
    if (x->next == 0) {
        x = 0;
    } else {
        x = x->child;
    }
    if (x != 0) {
        do {
            if (q.tag == 0x14) {
                if (x->tag == 0x14) {
                    if (x->v.i < q.v.i) {
                        func_0011B0A8(&q, x);
                    }
                } else {
                    if (x->v.f < (f32)q.v.i) {
                        func_0011B0A8(&q, x);
                    }
                }
            } else {
                if (x->tag == 0x14) {
                    if ((f32)x->v.i < q.v.f) {
                        func_0011B0A8(&q, x);
                    }
                } else {
                    f32 pf = x->v.f;
                    if (pf < q.v.f) {
                        func_0011B0A8(&q, x);
                    }
                }
            }
            x = x->next;
        } while (x != 0);
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

// NEAR: the lui/lwc1 pair of D_0026185C uses $v1 in retail, $v0 here (scalar and array externs and a local float all tried).

struct Quad_117610 { s32 a, b, c, d; };

extern f32 D_0026185C;

s32 func_0011B008(Quad_117610* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, int mode);
void func_0011B5B0(Quad_117610* q, f32 v);

void* func_00117610(void* self)
{
    Quad_117610 q;
    func_0011B008(&q);
    func_0011B5B0(&q, D_0026185C);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct __attribute__((aligned(16))) Quad_115510 { f32 f[4]; };
struct Node_115510 { s32 pad0; Quad_115510* f4; Node_115510* f8; };
struct List_115510 { s32 pad0; Node_115510* f4; };

s32 func_0011B008(Quad_115510* q);
void func_0011B018(void* out, Quad_115510* q);
void func_0011B060(Quad_115510* q, s32 mode);
void func_0011B0A8(Quad_115510* a, Quad_115510* b);
void func_0011B788(Quad_115510* q, Quad_115510* v);
void func_0011B9A8(Quad_115510* out, Node_115510* n);
void func_001884C0(Quad_115510* v);

void* func_00115510(void* self, s32 kind, List_115510* list)
{
    Quad_115510 t, u;
    func_0011B008(&t);
    Quad_115510* a = (Quad_115510*)func_0011C618();
    Node_115510* n = list->f4;
    switch (kind) {
    case 3:
    case 4: {
        func_001884C0(a);
        for (s32 i = 0; i < kind; i++) {
            a[i] = *n->f4;
            n = n->f8;
        }
        break;
    }
    case 9:
        func_001884C0(a);
    case 16: {
        s32 m = kind == 9 ? 3 : 4;
        for (s32 i = 0; i < m; i++) {
            for (s32 j = 0; j < m; j++) {
                func_0011B9A8(&u, n);
                func_0011B0A8(&t, &u);
                func_0011B060(&u, 2);
                a[i].f[j] = t.f[1];
                n = n->f8;
            }
        }
        break;
    }
    }
    func_0011B788(&t, a);
    func_0011B018(self, &t);
    func_0011B060(&t, 2);
    return self;
}

struct Quad_117668;
void func_0011B008(Quad_117668* q);
void func_0011B060(Quad_117668* q, s32 mode);
struct Quad_117668 {
    s32 a, b, c, d;
    Quad_117668() { func_0011B008(this); }
    ~Quad_117668() { func_0011B060(this, 2); }
};
struct QP_117668 { s32 a, b, c, d; };
struct TQ_117668 { s32 a; f32 f4; s32 c, d; };
struct Node_117668 { s32 type; Node_117668* head; Node_117668* next; };
struct Ent_117668 { s32 pad0; Node_117668* node; };
struct Src_117668 { Ent_117668 e[1]; };
struct Self_117668 { u8 pad0[0x2C]; void* f2C; u8 pad30[0x1EF8 - 0x30]; s32 f1EF8; };

void func_0011B008(QP_117668* q);
void func_0011B060(QP_117668* q, s32 mode);
void func_0011B6C0(QP_117668* q, Node_117668* v);
s32 func_0011A498(void* a, s32 b, s32 c, QP_117668* d);
void func_0011A400(TQ_117668* self, void* table, s32 key, QP_117668* item);
void func_0011B018(void* out, Quad_117668* q);
void func_0011B060(TQ_117668* q, s32 mode);
void func_0011B538(Node_117668* q, s32 n);
void func_0011B538(Quad_117668* q, s32 n);
void func_0011B5B0(Node_117668* obj, f32 x);
void func_0011B6C0(Node_117668* q, Node_117668* v);
void func_0011B6C0(Quad_117668* q, Node_117668* v);
void func_0011B700(Node_117668* n, s32 v);
void func_0011B9A8(TQ_117668* t, Src_117668* s);
s32 func_0011A498(void* a, s32 b, s32 c, Quad_117668* d);
void func_0011A400(TQ_117668* self, void* table, s32 key, Quad_117668* item);
extern s32 D_00259DE8;

void* func_00117668(void* ret, s32 limit, Src_117668* src)
{
    Quad_117668 q;
    QP_117668 r;
    TQ_117668 t;
    func_0011B008(&r);
    Node_117668* a = (Node_117668*)func_0011AF28();
    Node_117668* b = (Node_117668*)func_0011AF28();
    Node_117668* c = (Node_117668*)func_0011AF28();
    Node_117668* d = (Node_117668*)func_0011AF28();
    Node_117668* e;
    Node_117668* f;
    e = (Node_117668*)func_0011AF28();
    f = (Node_117668*)func_0011AF28();
    func_0011B6C0(a, b);
    func_0011B9A8(&t, src);
    func_0011B5B0(b, t.f4);
    func_0011B060(&t, 2);
    b->next = c;
    func_0011B6C0(c, d);
    func_0011B6C0(d, e);
    func_0011B538(e, 0x11);
    e->next = f;
    func_0011B700(f, ((s32*)src)[3]);
    s32 idx = D_00259DE8;
    if (idx < limit) {
        Node_117668* n = *(Node_117668**)(idx * 8 + (u8*)src + 4);
        if (n) {
            Node_117668* prev = d;
            do {
                d = (Node_117668*)func_0011AF28();
                e = (Node_117668*)func_0011AF28();
                func_0011B6C0(d, e);
                func_0011B538(e, 0x11);
                e->next = n;
                prev->next = d;
                Node_117668* nx = n->next;
                n->next = 0;
                n = nx;
                prev = d;
            } while (n);
        }
    }
    func_0011A498(((Self_117668*)D_00275710)->f2C, ((Self_117668*)D_00275710)->f1EF8, 0, &r);
    if (r.a == 0x1E) {
        a->next = (Node_117668*)r.b;
    }
    func_0011B6C0(&r, a);
    func_0011A400(&t, ((Self_117668*)D_00275710)->f2C, ((Self_117668*)D_00275710)->f1EF8, &r);
    func_0011B060(&t, 2);
    func_0011B018(ret, &q);
    func_0011B060(&r, 2);
    return ret;
}

struct __attribute__((aligned(16))) Quad_1149F0 { s32 a, b, c, d; };
struct Pair_1149F0 { s32 a, b; };
struct Frame_1149F0 {
    Quad_1149F0 A;
    Quad_1149F0 B;
    Pair_1149F0 C[2];
    Quad_1149F0 D;
};
struct Node_1149F0 { s32 pad0; s32 pad1; Node_1149F0* next; };
struct Src_1149F0 { s32 pad0; s32 pad1; s32 kind; Node_1149F0* head; };

void func_0011B008(Pair_1149F0* obj);
void func_0011B008(Quad_1149F0* obj);
s32 func_0011B5F0(Quad_1149F0* q, s32 flag);
void func_0011B0A8(Pair_1149F0* a, void* b);
void func_0011B0A8(Quad_1149F0* a, void* b);
void func_00113E48(Quad_1149F0* a, s32 mode, Pair_1149F0* b, void* c);
void func_0011B018(void* dst, Quad_1149F0* src);
void func_0011B060(Pair_1149F0* obj, s32 n);
void func_0011B060(Quad_1149F0* obj, s32 n);

void* func_001149F0(void* ret, s32 unused, Src_1149F0* src, void* arg3)
{
    Frame_1149F0 f;
    s32 n;
    Node_1149F0* cur;

    func_0011B008(&f.A);
    func_0011B008(&f.B);
    Pair_1149F0* q = f.C;
    n = 1;
    do {
        func_0011B008(q);
        n--;
        q++;
    } while (n != -1);
    (void)func_0011B5F0(&f.A, 0);
    if (src->kind == 0x1E) {
        func_0011B0A8(f.C, src);
        cur = src->head;
        while (cur != 0) {
            func_0011B0A8(&f.C[1], cur);
            func_00113E48(&f.D, 2, f.C, arg3);
            func_0011B0A8(&f.B, &f.D);
            func_0011B060(&f.D, 2);
            if (f.B.a == 0x1B) {
                if (f.B.b != 0) {
                    (void)func_0011B5F0(&f.A, 1);
                    break;
                }
            }
            cur = cur->next;
        }
    }
    func_0011B018(ret, &f.A);
    q = (Pair_1149F0*)&f.D;
    if (f.C != q) {
        do {
            q--;
            func_0011B060(q, 0);
        } while (f.C != q);
    }
    func_0011B060(&f.B, 2);
    func_0011B060(&f.A, 2);
    return ret;
}

struct Quad_117C48 { s32 a, b, c, d; };
struct In_117C48 { u8 pad0[4]; s32 w4; s32 w8; s32 wc; };

extern void* D_00275710;

s32 func_0011B008(Quad_117C48* q);
void func_00117AF0(Quad_117C48* t, s32 a, void* b);
s32 func_0011B0A8(Quad_117C48* a, Quad_117C48* b);
s32 func_0011B060(Quad_117C48* q, int mode);
s32 func_0011B018(void* dst, Quad_117C48* src);
s32 func_0015A198(void* host, s32 a1, s32 a2, void* ctx, s32 a4, void* a5);

void* func_00117C48(void* out, s32 unused, In_117C48* in)
{
    Quad_117C48 q;
    u8 buf[0x100];
    Quad_117C48 t;
    (void)func_0011B008(&q);
    s32 r = func_0015A198(D_00275710, in->wc ? 0x101 : 0x105, in->w4, (void*)in->wc, 0x40, buf);
    func_00117AF0(&t, r, buf);
    (void)func_0011B0A8(&q, &t);
    (void)func_0011B060(&t, 2);
    (void)func_0011B018(out, &q);
    (void)func_0011B060(&q, 2);
    return out;
}

struct __attribute__((aligned(16))) Quad_1159B8 { s32 a, b, c, d; };
struct Idx_1159B8 { s32 f0; s32 f4; Idx_1159B8* f8; };
struct __attribute__((aligned(16))) Arr_1159B8 { f32 v[4]; };
struct Mat_1159B8 { Arr_1159B8 row[4]; };
struct Src_1159B8 { s32 type; f32* f4; s32 f8; Idx_1159B8* fC; };

void func_0011B008(Quad_1159B8* q);
void func_0011B018(Quad_1159B8* out, Quad_1159B8* q);
void func_0011B060(Quad_1159B8* q, s32 mode);
void func_0011B5B0(Quad_1159B8* q, f32 x);
void func_0011B740(Quad_1159B8* q, Arr_1159B8* c);

Quad_1159B8* func_001159B8(Quad_1159B8* out, s32 mode, Src_1159B8* s)
{
    Quad_1159B8 q;
    func_0011B008(&q);
    Idx_1159B8* ix = s->fC;
    switch (s->type) {
    case 0x16:
        func_0011B5B0(&q, ((Arr_1159B8*)s->f4)->v[ix->f4]);
        break;
    case 0x17: {
        s32 i = ix->f4;
        Arr_1159B8* v;
        if (mode == 2) {
            v = (Arr_1159B8*)func_0011C508();
            *v = ((Arr_1159B8*)s->f4)[i];
            func_0011B740(&q, v);
        } else {
            ix = ix->f8;
            v = &((Mat_1159B8*)s->f4)->row[i];
            func_0011B5B0(&q, v->v[ix->f4]);
        }
        break;
    }
    case 0x18:
        func_0011B5B0(&q, ((Arr_1159B8*)s->f4)->v[ix->f4]);
        break;
    case 0x19:
        func_0011B5B0(&q, ix->f4 == 0 ? s->f4[0] : s->f4[1]);
        break;
    case 0x1A:
        switch (ix->f4) {
        case 0:
            func_0011B5B0(&q, s->f4[0]);
            break;
        case 1:
            func_0011B5B0(&q, s->f4[1]);
            break;
        case 2:
            func_0011B5B0(&q, s->f4[2]);
            break;
        }
        break;
    }
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}
