// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Quad_100178 { s32 a, b, c, d; };

void func_0011B008(Quad_100178* q);
void func_0011B018(void* out, Quad_100178* q);
void func_0011B060(Quad_100178* q, int mode);
void func_0011B0A8(Quad_100178* a, Quad_100178* b);
void func_0011B538(Quad_100178* q, int n);
void func_001C23B0(Quad_100178* t, int mode, int c, void* z);
void func_00182DD8(void* p);

void* func_00100178(void* out, void* x, int unused, int c)
{
    Quad_100178 q;
    Quad_100178 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00182DD8(x);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_100218 { s32 a, b, c, d; };

void func_0011B008(Quad_100218* q);
void func_0011B018(void* out, Quad_100218* q);
void func_0011B060(Quad_100218* q, int mode);
void func_0011B0A8(Quad_100218* a, Quad_100218* b);
void func_0011B538(Quad_100218* q, int n);

typedef void (*VFn_100218)(void* self);
struct Obj_100218 { VFn_100218* vtbl; };
void func_001C23B0(Quad_100218* t, int mode, int c, void* z);

void* func_00100218(void* out, void* x, int unused, int c)
{
    Quad_100218 q;
    Quad_100218 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    ((Obj_100218*)x)->vtbl[7](x);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_1002C0 { s32 a, b, c, d; };

void func_0011B008(Quad_1002C0* q);
void func_0011B018(void* out, Quad_1002C0* q);
void func_0011B060(Quad_1002C0* q, int mode);
void func_0011B0A8(Quad_1002C0* a, Quad_1002C0* b);
void func_0011B538(Quad_1002C0* q, int n);

typedef void (*VFn_1002C0)(void* self);
struct Obj_1002C0 { VFn_1002C0* vtbl; };
void func_001C23B0(Quad_1002C0* t, int mode, int c, void* z);

void* func_001002C0(void* out, void* x, int unused, int c)
{
    Quad_1002C0 q;
    Quad_1002C0 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    ((Obj_1002C0*)x)->vtbl[6](x);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_100C28 { s32 a, b, c, d; };

void func_0011B008(Quad_100C28* q);
void func_0011B018(void* out, Quad_100C28* q);
void func_0011B060(Quad_100C28* q, int mode);
void func_0011B0A8(Quad_100C28* a, Quad_100C28* b);
void func_0011B538(Quad_100C28* q, int n);

void func_001250C8(void* p);
void func_001C23B0(Quad_100C28* t, int mode, int c, void* z);

void* func_00100C28(void* out, void* x, int unused, int c)
{
    Quad_100C28 q;
    Quad_100C28 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001250C8(x);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_100CC8 { s32 a, b, c, d; };

void func_0011B008(Quad_100CC8* q);
void func_0011B018(void* out, Quad_100CC8* q);
void func_0011B060(Quad_100CC8* q, int mode);
void func_0011B0A8(Quad_100CC8* a, Quad_100CC8* b);
void func_0011B538(Quad_100CC8* q, int n);

void func_0012A8B8(void* p);
void func_001C23B0(Quad_100CC8* t, int mode, int c, void* z);

void* func_00100CC8(void* out, void* x, int unused, int c)
{
    Quad_100CC8 q;
    Quad_100CC8 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0012A8B8(x);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_100D68 { s32 a, b, c, d; };

void func_0011B008(Quad_100D68* q);
void func_0011B018(void* out, Quad_100D68* q);
void func_0011B060(Quad_100D68* q, int mode);
void func_0011B0A8(Quad_100D68* a, Quad_100D68* b);
void func_0011B538(Quad_100D68* q, int n);

void func_0012A8C8(void* p);
void func_001C23B0(Quad_100D68* t, int mode, int c, void* z);

void* func_00100D68(void* out, void* x, int unused, int c)
{
    Quad_100D68 q;
    Quad_100D68 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0012A8C8(x);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_101168 { s32 a, b, c, d; };

void func_0011B008(Quad_101168* q);
void func_0011B018(void* out, Quad_101168* q);
void func_0011B060(Quad_101168* q, int mode);
void func_0011B0A8(Quad_101168* a, Quad_101168* b);
void func_0011B538(Quad_101168* q, int n);

void func_0012B010(void* p);
void func_001C23B0(Quad_101168* t, int mode, int c, void* z);

void* func_00101168(void* out, void* x, int unused, int c)
{
    Quad_101168 q;
    Quad_101168 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0012B010(x);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_102030 { s32 a, b, c, d; };

void func_0011B008(Quad_102030* q);
void func_0011B018(void* out, Quad_102030* q);
void func_0011B060(Quad_102030* q, int mode);
void func_0011B0A8(Quad_102030* a, Quad_102030* b);
void func_0011B538(Quad_102030* q, int n);
void func_001C23B0(Quad_102030* t, int mode, int c, void* z);
void func_001EF830(void* o);

void* func_00102030(void* self, void* x, int unused, int c)
{
    Quad_102030 q;
    Quad_102030 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001EF830(x);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_1020D0 { s32 a, b, c, d; };
typedef void (*VFn_1020D0)(void* self);
struct Obj_1020D0 { VFn_1020D0* vtbl; };

void func_0011B008(Quad_1020D0* q);
void func_0011B018(void* out, Quad_1020D0* q);
void func_0011B060(Quad_1020D0* q, int mode);
void func_0011B0A8(Quad_1020D0* a, Quad_1020D0* b);
void func_0011B538(Quad_1020D0* q, int n);
void func_001C23B0(Quad_1020D0* t, int mode, int c, void* z);

void* func_001020D0(void* self, Obj_1020D0* x, int unused, int c)
{
    Quad_1020D0 q;
    Quad_1020D0 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    x->vtbl[76](x);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_102358 { s32 a, b, c, d; };

void func_0011B008(Quad_102358* q);
void func_0011B018(void* out, Quad_102358* q);
void func_0011B060(Quad_102358* q, int mode);
void func_0011B0A8(Quad_102358* a, Quad_102358* b);
void func_0011B538(Quad_102358* q, int n);
void func_001C23B0(Quad_102358* t, int mode, int c, void* z);
void func_00192418(void* o);

void* func_00102358(void* self, void* x, int unused, int c)
{
    Quad_102358 q;
    Quad_102358 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00192418(x);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_102710 { s32 a, b, c, d; };

void func_0011B008(Quad_102710* q);
void func_0011B018(void* out, Quad_102710* q);
void func_0011B060(Quad_102710* q, int mode);
void func_0011B0A8(Quad_102710* a, Quad_102710* b);
void func_0011B538(Quad_102710* q, int n);
void func_001C23B0(Quad_102710* t, int mode, int c, void* z);

typedef void (*VFn_102710)(void* self);
struct Obj_102710 { VFn_102710* vtbl; };

void* func_00102710(void* out, void* x, int unused, int c)
{
    Quad_102710 q;
    Quad_102710 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    VFn_102710 fn = ((Obj_102710*)x)->vtbl[78];
    if (fn != 0) {
        fn(x);
    }
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_103F80 { s32 a, b, c, d; };

void func_0011B008(Quad_103F80* q);
void func_0011B018(void* out, Quad_103F80* q);
void func_0011B060(Quad_103F80* q, int mode);
void func_0011B0A8(Quad_103F80* a, Quad_103F80* b);
void func_0011B538(Quad_103F80* q, int n);
void func_001C23B0(Quad_103F80* t, int mode, int c, void* z);
void func_001DDB58(void* x);

void* func_00103F80(void* self, void* x, int unused, int c)
{
    Quad_103F80 q;
    Quad_103F80 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DDB58(x);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_103590 { s32 a, b, c, d; };
struct Frame_103590 { Quad_103590 q; Quad_103590 t; s32 n; s32 out; };

void func_0011B008(Quad_103590* q);
void func_0011B018(void* dst, Quad_103590* src);
void func_0011B060(Quad_103590* q, int mode);
void func_0011B0A8(Quad_103590* a, Quad_103590* b);
s32 func_0011B5F0(Quad_103590* q, s32 flag);
void func_001C23B0(Quad_103590* t, int mode, int c, void* z, void* z2);
s32 func_001DD690(void* self, s32 obj);

void* func_00103590(void* self, void* x, int unused, int c)
{
    Frame_103590 f;
    func_0011B008(&f.q);
    f.n = 0xF;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0011B5F0(&f.q, func_001DD690(x, f.out));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_1029D0 { s32 a, b, c, d; };
struct Frame_1029D0 { Quad_1029D0 q; Quad_1029D0 t; };

void func_0011B008(Quad_1029D0* q);
void func_0011B018(void* dst, Quad_1029D0* src);
void func_0011B060(Quad_1029D0* q, int mode);
void func_0011B0A8(Quad_1029D0* a, Quad_1029D0* b);
void func_0011B538(Quad_1029D0* q, int n);
void func_001C23B0(Quad_1029D0* t, int mode, int c, void* z);
void func_00155F90(void* x);

void* func_001029D0(void* self, void* x, int unused, int c)
{
    Frame_1029D0 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00155F90(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}
