// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 421/436 (96.6%), checked 2026-11-04
#include "common.h"
// NEAR: only float register numbering of lo/hi (f2/f1 swapped, 8 instrs differ); rest matches
#include "g27c220.h"
#include "s1eb050.h"

typedef int V128_1DB290 __attribute__((mode(TI)));

struct Poly_1DB290 {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};
struct Range_1DB290 {
    f32 lo;
    f32 hi;
    f32 Clamp(f32 v)
    {
        f32 l = lo;
        f32 h = hi;
        if (v < l)
            v = l;
        else if (h < v)
            v = h;
        return v;
    }
};

struct Obj_1DB290 {
    u8 pad0[0x620];
    f32 f620;
    f32 f624;
    f32 f628;
    u8 pad62C[4];
    u8 v630[0x10];
    f32 f640;
    f32 f644;
    u8 pad648[8];
    u8 v650[0x10];
    f32 f660;
    f32 f664;
    u8 pad668[8];
    u8 v670[0x10];
    f32 f680;
    f32 f684;
    u8 pad688[0x854 - 0x688];
    f32 f854;
    s32 f858;
    f32 f85C;
    f32 f860;
    f32 f864;
    u8 pad868[4];
    f32 f86C;
    u8 pad870[0xAF4 - 0x870];
    s32 fAF4;
    s32 fAF8;
    u8 padAFC[4];
    s32 fB00;
    u8 padB04[0xB10 - 0xB04];
    f32 fB10;
};

void func_00118CF0(void* out, f32 f);
void func_00118D10(void* out, void* in);
void func_00118D20(void* dst, V128_1DB290 v);
V128_1DB290 func_001DB460(V128_1DB290 a, V128_1DB290 b, V128_1DB290 c, V128_1DB290 d);

void func_001DB290(Obj_1DB290* self)
{
    self->fB00 = 1;
    self->fAF8 = self->fAF4;
    self->f858 = 0;
    self->f854 = -10.0f;
    self->f864 = -10.0f;
    self->f86C = -10.0f;
    self->fB10 = -10.0f;
    G27C230* rec = D_002623C8;
    f32 t = ((Poly_1DB290*)&self->f620)->Eval(rec->dt);
    f32 l = D_00275C60.lo;
    f32 h = D_00275C60.hi;
    f32 x;
    if (t < l)
        x = l;
    else if (h < t)
        x = h;
    else
        x = t;
    f32 y = 1.0f - x;
    u8* p630 = self->v630;
    u8* p650 = self->v650;
    u8* p670 = self->v670;
    V128_1DB290 a, b, c, d;
    V128_1DB290 a2, b2, c2, d2;
    func_00118CF0(&a, y);
    a2 = a;
    func_00118D10(&b, p630);
    b2 = b;
    func_00118CF0(&c, x);
    c2 = c;
    func_00118D10(&d, p650);
    d2 = d;
    func_00118D20(p670, func_001DB460(a2, b2, c2, d2));
    self->f680 = y * self->f640 + x * self->f660;
    self->f684 = y * self->f644 + x * self->f664;
    f32 lo = self->f680;
    f32 hi = self->f684;
    f32 v = *(f32*)p670;
    f32 r;
    if (v < lo)
        r = lo;
    else if (hi < v)
        r = hi;
    else
        r = v;
    self->f860 = r;
    self->f85C = r;
}
