// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Quad_1085E8 { s32 a, b, c, d; };

void func_0011B008(Quad_1085E8* q);
void func_0011B018(void* out, Quad_1085E8* q);
void func_0011B060(Quad_1085E8* q, int mode);
void func_0011B0A8(Quad_1085E8* a, Quad_1085E8* b);
void func_0011B538(Quad_1085E8* q, int n);
void func_001C23B0(Quad_1085E8* t, int mode, int c, void* z);
void func_00159ED0(void* x);

void* func_001085E8(void* self, void* x, int unused, int c)
{
    Quad_1085E8 q;
    Quad_1085E8 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00159ED0(x);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_108548 { s32 a, b, c, d; };
struct Frame_108548 { Quad_108548 q; Quad_108548 t; };

void func_0011B008(Quad_108548* q);
void func_0011B018(void* dst, Quad_108548* src);
void func_0011B060(Quad_108548* q, int mode);
void func_0011B0A8(Quad_108548* a, Quad_108548* b);
void func_0011B538(Quad_108548* q, int n);
void func_001C23B0(Quad_108548* t, int mode, int c, void* z);
void func_0017D220(void* x);

void* func_00108548(void* self, void* x, int unused, int c)
{
    Frame_108548 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0017D220(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_108688 { s32 a, b, c, d; };
struct Frame_108688 { Quad_108688 q; Quad_108688 t; };

void func_0011B008(Quad_108688* q);
void func_0011B018(void* dst, Quad_108688* src);
void func_0011B060(Quad_108688* q, int mode);
void func_0011B0A8(Quad_108688* a, Quad_108688* b);
void func_0011B538(Quad_108688* q, int n);
void func_001C23B0(Quad_108688* t, int mode, int c, void* z);
void func_0017B598(void* x);

void* func_00108688(void* self, void* x, int unused, int c)
{
    Frame_108688 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0017B598(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_1087D8 { s32 a, b, c, d; };
struct Frame_1087D8 { Quad_1087D8 q; Quad_1087D8 t; };

void func_0011B008(Quad_1087D8* q);
void func_0011B018(void* dst, Quad_1087D8* src);
void func_0011B060(Quad_1087D8* q, int mode);
void func_0011B0A8(Quad_1087D8* a, Quad_1087D8* b);
void func_0011B538(Quad_1087D8* q, int n);
void func_001C23B0(Quad_1087D8* t, int mode, int c, void* z);
void func_0017AD50(void* x);

void* func_001087D8(void* self, void* x, int unused, int c)
{
    Frame_1087D8 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0017AD50(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_108928 { s32 a, b, c, d; };
struct Frame_108928 { Quad_108928 q; Quad_108928 t; };

void func_0011B008(Quad_108928* q);
void func_0011B018(void* dst, Quad_108928* src);
void func_0011B060(Quad_108928* q, int mode);
void func_0011B0A8(Quad_108928* a, Quad_108928* b);
void func_0011B538(Quad_108928* q, int n);
void func_001C23B0(Quad_108928* t, int mode, int c, void* z);
void func_001ED020(void* x);

void* func_00108928(void* self, void* x, int unused, int c)
{
    Frame_108928 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001ED020(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_108728 { s32 a, b, c, d; };
struct Frame_108728 { Quad_108728 q; Quad_108728 t; s32 n; s32 out; };

void func_0011B008(Quad_108728* q);
void func_0011B018(void* dst, Quad_108728* src);
void func_0011B060(Quad_108728* q, int mode);
void func_0011B0A8(Quad_108728* a, Quad_108728* b);
void func_0011B538(Quad_108728* q, int n);
void func_001C23B0(Quad_108728* t, int mode, int c, void* z, void* z2);
s32 func_0017B550(void* self, s32 index);

void* func_00108728(void* self, void* x, int unused, int c)
{
    Frame_108728 f;
    func_0011B008(&f.q);
    f.n = 6;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0017B550(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_108878 { s32 a, b, c, d; };
struct Frame_108878 { Quad_108878 q; Quad_108878 t; s32 n; s32 out; };

void func_0011B008(Quad_108878* q);
void func_0011B018(void* dst, Quad_108878* src);
void func_0011B060(Quad_108878* q, int mode);
void func_0011B0A8(Quad_108878* a, Quad_108878* b);
void func_0011B538(Quad_108878* q, int n);
void func_001C23B0(Quad_108878* t, int mode, int c, void* z, void* z2);
s32 func_001ED018(void* self, s32 value);

void* func_00108878(void* self, void* x, int unused, int c)
{
    Frame_108878 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_001ED018(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_108A98 { s32 a, b, c, d; };
struct Frame_108A98 { Quad_108A98 q; Quad_108A98 t; s32 n; s32 out; };

void func_0011B008(Quad_108A98* q);
void func_0011B018(void* dst, Quad_108A98* src);
void func_0011B060(Quad_108A98* q, int mode);
void func_0011B0A8(Quad_108A98* a, Quad_108A98* b);
void func_0011B538(Quad_108A98* q, int n);
void func_001C23B0(Quad_108A98* t, int mode, int c, void* z, void* z2);
s32 func_001ED0D8(void* self, s32 value);

void* func_00108A98(void* self, void* x, int unused, int c)
{
    Frame_108A98 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_001ED0D8(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_108B48 { s32 a, b, c, d; };
struct Frame_108B48 { Quad_108B48 q; Quad_108B48 t; };

void func_0011B008(Quad_108B48* q);
void func_0011B018(void* dst, Quad_108B48* src);
void func_0011B060(Quad_108B48* q, int mode);
void func_0011B0A8(Quad_108B48* a, Quad_108B48* b);
void func_0011B538(Quad_108B48* q, int n);
void func_001C23B0(Quad_108B48* t, int mode, int c, void* z);
void func_001EC528(void* x);

void* func_00108B48(void* self, void* x, int unused, int c)
{
    Frame_108B48 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001EC528(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}
