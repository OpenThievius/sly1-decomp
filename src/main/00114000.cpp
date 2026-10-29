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
