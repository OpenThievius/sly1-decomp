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

struct Quad_108498 { s32 a, b, c, d; };
struct Frame_108498 { Quad_108498 q; Quad_108498 t; s32 n; f32 out; };

void func_0011B008(Quad_108498* q);
void func_0011B018(void* dst, Quad_108498* src);
void func_0011B060(Quad_108498* q, int mode);
void func_0011B0A8(Quad_108498* a, Quad_108498* b);
void func_0011B538(Quad_108498* q, int n);
int func_001C23B0(Quad_108498* t, int mode, int c, void* z, void* z2);
void func_0017D1E8(void* x, f32 f);

void* func_00108498(void* self, void* x, int unused, int c)
{
    Frame_108498 f;
    func_0011B008(&f.q);
    f.n = 1;
    (void)func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0017D1E8(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// NEAR: the 0x2000 store to the frame lands before the argument addresses (addiu a3, addiu t0); retail stores it after them. The 6 variant (func_00107EC0) matches.

struct Quad_1091A8 { s32 a, b, c, d; };
struct Frame_1091A8 { Quad_1091A8 q; Quad_1091A8 t; s32 n; s32 out; };

void func_0011B008(Quad_1091A8* q);
void func_0011B018(void* dst, Quad_1091A8* src);
void func_0011B060(Quad_1091A8* q, int mode);
void func_0011B0A8(Quad_1091A8* a, Quad_1091A8* b);
void func_0011B538(Quad_1091A8* q, int n);
s32 func_001C23B0(Quad_1091A8* t, int mode, int c, void* z, void* z2);
void func_001C3F68(void* self, s32 value);

void* func_001091A8(void* self, void* x, int unused, int c)
{
    Frame_1091A8 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    (void)func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_001C3F68(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// NEAR: the 0x2000 store to the frame lands before the argument addresses (addiu a3, addiu t0); retail stores it after them. The 6 variant (func_00107EC0) matches.

struct Quad_109258 { s32 a, b, c, d; };
struct Frame_109258 { Quad_109258 q; Quad_109258 t; s32 n; s32 out; };

void func_0011B008(Quad_109258* q);
void func_0011B018(void* dst, Quad_109258* src);
void func_0011B060(Quad_109258* q, int mode);
void func_0011B0A8(Quad_109258* a, Quad_109258* b);
void func_0011B538(Quad_109258* q, int n);
s32 func_001C23B0(Quad_109258* t, int mode, int c, void* z, void* z2);
void func_001C4180(void* self, s32 value);

void* func_00109258(void* self, void* x, int unused, int c)
{
    Frame_109258 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    (void)func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_001C4180(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// NEAR: the 0x2000 store to the frame lands before the argument addresses (addiu a3, addiu t0); retail stores it after them. The 6 variant (func_00107EC0) matches.

struct Quad_109308 { s32 a, b, c, d; };
struct Frame_109308 { Quad_109308 q; Quad_109308 t; s32 n; s32 out; };

void func_0011B008(Quad_109308* q);
void func_0011B018(void* dst, Quad_109308* src);
void func_0011B060(Quad_109308* q, int mode);
void func_0011B0A8(Quad_109308* a, Quad_109308* b);
void func_0011B538(Quad_109308* q, int n);
s32 func_001C23B0(Quad_109308* t, int mode, int c, void* z, void* z2);
void func_001C41A0(void* self, s32 value);

void* func_00109308(void* self, void* x, int unused, int c)
{
    Frame_109308 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    (void)func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_001C41A0(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct __attribute__((aligned(16))) Quad_001083C8 { s32 a, b, c, d; };
struct __attribute__((packed)) Key8_001083C8 { u8 b[8]; };
struct Frame_001083C8 { Quad_001083C8 q; Key8_001083C8 k; Quad_001083C8 t; s32 o1; s32 o2; };
struct Arg_001083C8;
extern Key8_001083C8 D_00248F90;

void func_0011B008(Quad_001083C8* q);
void func_0011B018(void* dst, Quad_001083C8* q);
void func_0011B060(Quad_001083C8* q, int mode);
void func_0011B0A8(Quad_001083C8* a, Quad_001083C8* b);
void func_0011B538(Quad_001083C8* q, int n);
s32 func_001C23B0(Quad_001083C8* t, int mode, int c, void* k, void* o1, void* o2);
void func_0017D0D8(Arg_001083C8* p, s32 a, s32 b);

void* func_001083C8(void* self, Arg_001083C8* p, int unused, int c)
{
    Frame_001083C8 f;
    func_0011B008(&f.q);
    f.k = D_00248F90;
    (void)func_001C23B0(&f.t, 2, c, &f.k, &f.o1, &f.o2);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0017D0D8(p, f.o1, f.o2);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct __attribute__((aligned(16))) Quad_001089C8 { s32 a, b, c, d; };
struct __attribute__((packed)) Key8_001089C8 { u8 b[8]; };
struct Frame_001089C8 { Quad_001089C8 q; Key8_001089C8 k; Quad_001089C8 t; s32 o1; s32 o2; };
struct Arg_001089C8;
extern Key8_001089C8 D_00248F98;

void func_0011B008(Quad_001089C8* q);
void func_0011B018(void* dst, Quad_001089C8* q);
void func_0011B060(Quad_001089C8* q, int mode);
void func_0011B0A8(Quad_001089C8* a, Quad_001089C8* b);
void func_0011B538(Quad_001089C8* q, int n);
s32 func_001C23B0(Quad_001089C8* t, int mode, int c, void* k, void* o1, void* o2);
void func_001ED090(Arg_001089C8* p, s32 a, s32 b);

void* func_001089C8(void* self, Arg_001089C8* p, int unused, int c)
{
    Frame_001089C8 f;
    func_0011B008(&f.q);
    f.k = D_00248F98;
    (void)func_001C23B0(&f.t, 2, c, &f.k, &f.o1, &f.o2);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001ED090(p, f.o1, f.o2);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// Callee declared s32 and called as (void): schedules the three address adds before the 8-byte copy.

struct Quad_00108DA8 { s32 a, b, c, d; };
struct __attribute__((packed)) Pk_00108DA8 { u8 b[8]; };
struct Frame_00108DA8 { Quad_00108DA8 q; Pk_00108DA8 k; u8 pad[8]; Quad_00108DA8 t; s32 n; f32 out; };
struct Obj_00108DA8 { u8 pad[0x1]; };

extern u8 D_00248FC0[];

void func_0011B008(Quad_00108DA8* q);
void func_0011B018(void* dst, Quad_00108DA8* src);
void func_0011B060(Quad_00108DA8* q, int mode);
void func_0011B0A8(Quad_00108DA8* a, Quad_00108DA8* b);
void func_0011B538(Quad_00108DA8* q, int n);
s32 func_001C23B0(Quad_00108DA8* t, int mode, int c, void* z, s32* n, f32* out);
void func_001ED5B8(Obj_00108DA8* self, s32 p, f32 v);

void* func_00108DA8(void* self, Obj_00108DA8* x, int unused, int c)
{
    Frame_00108DA8 f;
    func_0011B008(&f.q);
    f.k = *(Pk_00108DA8*)D_00248FC0;
    (void)func_001C23B0(&f.t, 2, c, &f.k, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001ED5B8(x, f.n, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct __attribute__((aligned(16))) Quad_1082E8 { s32 a, b, c, d; };
struct __attribute__((packed)) Key8_1082E8 { u64 v; };
struct Key_1082E8 { Key8_1082E8 v; s32 w; };
struct Frame_1082E8 { Quad_1082E8 q; Key_1082E8 k; Quad_1082E8 t; s32 o0, o1, o2; };

extern u8 D_00248F80[];

void func_0011B008(Quad_1082E8* q);
void func_0011B018(void* out, Quad_1082E8* q);
void func_0011B060(Quad_1082E8* q, int mode);
void func_0011B0A8(Quad_1082E8* a, Quad_1082E8* b);
void func_0011B538(Quad_1082E8* q, int n);
s32 func_001C23B0(Quad_1082E8* t, int mode, int c, void* z, s32* o0, s32* o1, s32* o2);
void func_0017D1B8(void* self, s32 b, s32 c, s32 d);

void* func_001082E8(void* self, void* x, int unused, int c)
{
    Frame_1082E8 f;
    func_0011B008(&f.q);
    f.k = *(Key_1082E8*)D_00248F80;
    func_001C23B0(&f.t, 3, c, &f.k, &f.o0, &f.o1, &f.o2);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0017D1B8(x, f.o0, f.o1, f.o2);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// EXACT: func_001C23B0 declared s32 and called as (void); the 12-byte copy of D_00248FB0 then follows the out-pointer addiu.

struct __attribute__((aligned(16))) Quad_00108CC8 { s32 a, b, c, d; };
struct __attribute__((packed)) Key8_00108CC8 { u64 v; };
struct Key_00108CC8 { Key8_00108CC8 v; s32 w; };
struct Frame_00108CC8 { Quad_00108CC8 q; Key_00108CC8 k; Quad_00108CC8 t; s32 o0, o1, o2; };
struct Obj_00108CC8;

extern u8 D_00248FB0[];

void func_0011B008(Quad_00108CC8* q);
void func_0011B018(void* out, Quad_00108CC8* q);
void func_0011B060(Quad_00108CC8* q, int mode);
void func_0011B0A8(Quad_00108CC8* a, Quad_00108CC8* b);
void func_0011B538(Quad_00108CC8* q, int n);
s32 func_001C23B0(Quad_00108CC8* t, int mode, int c, void* z, s32* o0, s32* o1, s32* o2);
void func_001ED588(Obj_00108CC8* self, s32 p, f32 f, s32 q);

void* func_00108CC8(void* self, void* x, int unused, int c)
{
    Frame_00108CC8 f;
    func_0011B008(&f.q);
    f.k = *(Key_00108CC8*)D_00248FB0;
    (void)func_001C23B0(&f.t, 3, c, &f.k, &f.o0, &f.o1, &f.o2);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001ED588((Obj_00108CC8*)x, f.o0, *(f32*)&f.o1, f.o2);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// Matched: the out-pointer call is declared s32 and called as (void); the 12-byte copy of D_00248FC8 stays where it is.

struct __attribute__((aligned(16))) Quad_001090C8 { s32 a, b, c, d; };
struct __attribute__((packed)) Key8_001090C8 { u64 v; };
struct Key_001090C8 { Key8_001090C8 v; s32 w; };
struct Frame_001090C8 { Quad_001090C8 q; Key_001090C8 k; Quad_001090C8 t; s32 o0, o1, o2; };
struct Obj_001090C8;

extern u8 D_00248FC8[];

void func_0011B008(Quad_001090C8* q);
void func_0011B018(void* out, Quad_001090C8* q);
void func_0011B060(Quad_001090C8* q, int mode);
void func_0011B0A8(Quad_001090C8* a, Quad_001090C8* b);
void func_0011B538(Quad_001090C8* q, int n);
s32 func_001C23B0(Quad_001090C8* t, int mode, int c, void* z, s32* o0, s32* o1, s32* o2);
void func_001A9C58(Obj_001090C8* self, s32 a, s32 b, s32 c);

void* func_001090C8(void* self, void* x, int unused, int c)
{
    Frame_001090C8 f;
    func_0011B008(&f.q);
    f.k = *(Key_001090C8*)D_00248FC8;
    (void)func_001C23B0(&f.t, 3, c, &f.k, &f.o0, &f.o1, &f.o2);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001A9C58((Obj_001090C8*)x, f.o0, f.o1, f.o2);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// Matched: the out-pointer call is declared s32 and called as (void); the 8-byte copy stays where it is.

struct Quad_1093B8 { s32 a, b, c, d; };
struct Pair_1093B8 { s32 a, b; };
struct Frame_1093B8 { Quad_1093B8 q; Pair_1093B8 n; s32 pad[2]; Quad_1093B8 t; s32 o0; s32 o1; };
struct Obj_1093B8;

void func_0011B008(Quad_1093B8* q);
void func_0011B018(void* dst, Quad_1093B8* src);
void func_0011B060(Quad_1093B8* q, s32 mode);
void func_0011B0A8(Quad_1093B8* a, Quad_1093B8* b);
void func_0011B538(Quad_1093B8* q, s32 n);
s32 func_001C23B0(Quad_1093B8* t, s32 mode, s32 c, void* z, void* z2, void* z3);
void func_001D32D8(Obj_1093B8* self, s32 a, s32 b);

extern u8 D_00248FD8[];

void* func_001093B8(void* self, Obj_1093B8* x, s32 unused, s32 c)
{
    Frame_1093B8 f;
    func_0011B008(&f.q);
    (void)func_001C23B0(&f.t, 2, c, (f.n = *(Pair_1093B8*)D_00248FD8, &f.n), &f.o0, &f.o1);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001D32D8((Obj_1093B8*)x, f.o0, f.o1);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// EXACT: func_001C23B0 declared s32 and called as (void)

struct Quad_00108E70 { s32 a, b, c, d; };
struct __attribute__((packed)) Pk_00108E70 { u8 b[8]; };
struct Frame_00108E70 { Quad_00108E70 q; Pk_00108E70 k; u8 pad[8]; Quad_00108E70 t; s32 n; f32 out; };
struct Obj_00108E70 { u8 pad[0x1]; };

extern u8 D_00248FC0[];

void func_0011B008(Quad_00108E70* q);
void func_0011B018(void* dst, Quad_00108E70* src);
void func_0011B060(Quad_00108E70* q, int mode);
void func_0011B0A8(Quad_00108E70* a, Quad_00108E70* b);
void func_0011B538(Quad_00108E70* q, int n);
s32 func_001C23B0(Quad_00108E70* t, int mode, int c, void* z, s32* n, f32* out);
void func_001ED5D8(Obj_00108E70* self, s32 p, f32 v);

void* func_00108E70(void* self, Obj_00108E70* x, int unused, int c)
{
    Frame_00108E70 f;
    func_0011B008(&f.q);
    f.k = *(Pk_00108E70*)D_00248FC0;
    (void)func_001C23B0(&f.t, 2, c, &f.k, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001ED5D8(x, f.n, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_00108F38 { s32 a, b, c, d; };
struct __attribute__((packed)) Pk_00108F38 { u8 b[8]; };
struct Frame_00108F38 { Quad_00108F38 q; Pk_00108F38 k; u8 pad[8]; Quad_00108F38 t; s32 n; f32 out; };
struct Obj_00108F38 { u8 pad[0x1]; };

extern u8 D_00248FC0[];

void func_0011B008(Quad_00108F38* q);
void func_0011B018(void* dst, Quad_00108F38* src);
void func_0011B060(Quad_00108F38* q, int mode);
void func_0011B0A8(Quad_00108F38* a, Quad_00108F38* b);
void func_0011B538(Quad_00108F38* q, int n);
s32 func_001C23B0(Quad_00108F38* t, int mode, int c, void* z, s32* n, f32* out);
void func_001ED5F8(Obj_00108F38* self, s32 p, f32 v);

void* func_00108F38(void* self, Obj_00108F38* x, int unused, int c)
{
    Frame_00108F38 f;
    func_0011B008(&f.q);
    f.k = *(Pk_00108F38*)D_00248FC0;
    (void)func_001C23B0(&f.t, 2, c, &f.k, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001ED5F8(x, f.n, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// NEAR: the 8-byte constant copy is scheduled after the address of its argument (retail computes the argument addresses first); same in all four siblings.

struct Quad_00109000 { s32 a, b, c, d; };
struct __attribute__((packed)) Pk_00109000 { u8 b[8]; };
struct Frame_00109000 { Quad_00109000 q; Pk_00109000 k; u8 pad[8]; Quad_00109000 t; s32 n; f32 out; };
struct Obj_00109000 { u8 pad[0x1]; };

extern u8 D_00248FC0[];

void func_0011B008(Quad_00109000* q);
void func_0011B018(void* dst, Quad_00109000* src);
void func_0011B060(Quad_00109000* q, int mode);
void func_0011B0A8(Quad_00109000* a, Quad_00109000* b);
void func_0011B538(Quad_00109000* q, int n);
s32 func_001C23B0(Quad_00109000* t, int mode, int c, void* z, s32* n, f32* out);
void func_001ED618(Obj_00109000* self, s32 p, f32 v);

void* func_00109000(void* self, Obj_00109000* x, int unused, int c)
{
    Frame_00109000 f;
    func_0011B008(&f.q);
    f.k = *(Pk_00109000*)D_00248FC0;
    (void)func_001C23B0(&f.t, 2, c, &f.k, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001ED618(x, f.n, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// NEAR: the 12-byte copy of D_00248FA0 is scheduled before the three out-pointer addiu (sp+48/52/56); retail computes those first. Only instruction order differs.

struct __attribute__((aligned(16))) Quad_00108BE8 { s32 a, b, c, d; };
struct __attribute__((packed)) Key8_00108BE8 { u64 v; };
struct Key_00108BE8 { Key8_00108BE8 v; s32 w; };
struct Frame_00108BE8 { Quad_00108BE8 q; Key_00108BE8 k; Quad_00108BE8 t; s32 o0, o1, o2; };
struct Obj_00108BE8;

extern u8 D_00248FA0[];

void func_0011B008(Quad_00108BE8* q);
void func_0011B018(void* out, Quad_00108BE8* q);
void func_0011B060(Quad_00108BE8* q, int mode);
void func_0011B0A8(Quad_00108BE8* a, Quad_00108BE8* b);
void func_0011B538(Quad_00108BE8* q, int n);
s32 func_001C23B0(Quad_00108BE8* t, int mode, int c, void* z, s32* o0, s32* o1, s32* o2);
void func_001ED558(Obj_00108BE8* self, s32 p, f32 f, s32 q);

void* func_00108BE8(void* self, void* x, int unused, int c)
{
    Frame_00108BE8 f;
    func_0011B008(&f.q);
    f.k = *(Key_00108BE8*)D_00248FA0;
    (void)func_001C23B0(&f.t, 3, c, &f.k, &f.o0, &f.o1, &f.o2);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001ED558((Obj_00108BE8*)x, f.o0, *(f32*)&f.o1, f.o2);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct __attribute__((packed)) Pair_00108128 { s32 a, b; };
struct Rod_00108128 { Pair_00108128 p; s32 c; };
struct __attribute__((aligned(16))) Quad_00108128 { s32 w[4]; };
struct __attribute__((aligned(16))) Frame_00108128 {
    Quad_00108128 q;
    Rod_00108128 rod;
    s32 pad0;
    Quad_00108128 b;
    s32 o1;
    f32 o2;
    s32 o3;
};

struct Obj_00108128;

extern u8 D_00248F70[];

void func_0011B008(Quad_00108128* q);
void func_0011B018(void* dst, Quad_00108128* src);
void func_0011B060(Quad_00108128* q, s32 mode);
void func_0011B0A8(Quad_00108128* a, Quad_00108128* b);
void func_0011B538(Quad_00108128* q, s32 n);
s32 func_001C23B0(Quad_00108128* t, s32 mode, s32 c, void* z, void* z2, void* z3, void* z4);
void func_0017D148(Obj_00108128* self, s32 a, s32 b, f32 value);

void* func_00108128(void* self, void* x, s32 unused, s32 c)
{
    Frame_00108128 f;
    func_0011B008(&f.q);
    f.rod = *(Rod_00108128*)D_00248F70;
    (void)func_001C23B0(&f.b, 3, c, &f.rod, &f.o1, &f.o2, &f.o3);
    func_0011B0A8(&f.q, &f.b);
    func_0011B060(&f.b, 2);
    func_0017D148((Obj_00108128*)x, f.o1, f.o3, f.o2);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}
