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
