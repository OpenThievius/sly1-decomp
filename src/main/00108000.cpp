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
