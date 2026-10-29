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

struct Quad_1004F0 { s32 a, b, c, d; };
struct Frame_1004F0 { Quad_1004F0 q; Quad_1004F0 t; s32 n; s32 out; };

void func_0011B008(Quad_1004F0* q);
void func_0011B018(void* dst, Quad_1004F0* src);
void func_0011B060(Quad_1004F0* q, int mode);
void func_0011B0A8(Quad_1004F0* a, Quad_1004F0* b);
s32 func_0011B5F0(Quad_1004F0* q, s32 flag);
void func_001C23B0(Quad_1004F0* t, int mode, int c, void* z, void* z2);
s32 func_00182F40(void* e, s32 v);

void* func_001004F0(void* self, void* x, int unused, int c)
{
    Frame_1004F0 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 flag = func_00182F40(x, f.out);
    (void)func_0011B5F0(&f.q, flag);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_1005A0 { s32 a, b, c, d; };
struct Frame_1005A0 { Quad_1005A0 q; Quad_1005A0 t; s32 n; s32 out; };

void func_0011B008(Quad_1005A0* q);
void func_0011B018(void* dst, Quad_1005A0* src);
void func_0011B060(Quad_1005A0* q, int mode);
void func_0011B0A8(Quad_1005A0* a, Quad_1005A0* b);
s32 func_0011B5F0(Quad_1005A0* q, s32 flag);
void func_001C23B0(Quad_1005A0* t, int mode, int c, void* z, void* z2);
s32 func_001833F0(void* key, s32 item);

void* func_001005A0(void* self, void* x, int unused, int c)
{
    Frame_1005A0 f;
    func_0011B008(&f.q);
    f.n = 0x6;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 flag = func_001833F0(x, f.out);
    (void)func_0011B5F0(&f.q, flag);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_101368 { s32 a, b, c, d; };
struct Frame_101368 { Quad_101368 q; Quad_101368 t; s32 n; s32 out; };

void func_0011B008(Quad_101368* q);
void func_0011B018(void* dst, Quad_101368* src);
void func_0011B060(Quad_101368* q, int mode);
void func_0011B0A8(Quad_101368* a, Quad_101368* b);
s32 func_0011B8A8(Quad_101368* q, s32 v);
void func_001C23B0(Quad_101368* t, int mode, int c, void* z, void* z2);
s32 func_00129C20(void* self, s32 key);

void* func_00101368(void* self, void* x, int unused, int c)
{
    Frame_101368 f;
    func_0011B008(&f.q);
    f.n = 0x6;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0011B8A8(&f.q, func_00129C20(x, f.out));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_101418 { s32 a, b, c, d; };
struct Frame_101418 { Quad_101418 q; Quad_101418 t; s32 x; s32 y; };

void func_0011B008(Quad_101418* q);
void func_0011B018(void* out, Quad_101418* q);
void func_0011B060(Quad_101418* q, int mode);
void func_0011B0A8(Quad_101418* a, Quad_101418* b);
s32 func_0011B8A8(Quad_101418* q, void* v);
void func_001C23B0(Quad_101418* t, int mode, int c, s32* x, s32* y);
void* func_00129B98(void* self, s32 key);

void* func_00101418(void* out, void* x, int unused, int c)
{
    Frame_101418 f;
    func_0011B008(&f.q);
    s32* px = &f.x;
    s32* py = &f.y;
    *px = 6;
    func_001C23B0(&f.t, 1, c, px, py);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0011B8A8(&f.q, func_00129B98(x, f.y));
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

struct Quad_1014C8 { s32 a, b, c, d; };
struct Frame_1014C8 { Quad_1014C8 q; Quad_1014C8 t; };

void func_0011B008(Quad_1014C8* q);
void func_0011B018(void* out, Quad_1014C8* q);
void func_0011B060(Quad_1014C8* q, int mode);
void func_0011B0A8(Quad_1014C8* a, Quad_1014C8* b);
s32 func_0011B8A8(Quad_1014C8* q, void* v);
void func_001C23B0(Quad_1014C8* t, int mode, int c, void* z);
void* func_00129CA8(void* self);

void* func_001014C8(void* out, void* x, int unused, int c)
{
    Frame_1014C8 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0011B8A8(&f.q, func_00129CA8(x));
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

struct Quad_1017A0 { s32 a, b, c, d; };
struct Frame_1017A0 { Quad_1017A0 q; Quad_1017A0 out; Quad_1017A0 t; s32 n; };

void func_0011B008(Quad_1017A0* q);
void func_0011B018(void* dst, Quad_1017A0* src);
void func_0011B060(Quad_1017A0* q, int mode);
void func_0011B0A8(Quad_1017A0* a, Quad_1017A0* b);
s32 func_0011B5F0(Quad_1017A0* q, s32 flag);
void func_001C23B0(Quad_1017A0* t, int mode, int c, void* z, void* z2);
s32 func_001BC670(void* x, void* out);

void* func_001017A0(void* self, void* x, int unused, int c)
{
    Frame_1017A0 f;
    func_0011B008(&f.q);
    f.n = 2;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 r = func_001BC670(x, &f.out);
    (void)func_0011B5F0(&f.q, r);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_101950 { s32 a, b, c, d; };
struct Frame_101950 { Quad_101950 q; Quad_101950 t; };

void func_0011B008(Quad_101950* q);
void func_0011B018(void* dst, Quad_101950* src);
void func_0011B060(Quad_101950* q, int mode);
void func_0011B0A8(Quad_101950* a, Quad_101950* b);
void func_0011B538(Quad_101950* q, int n);
void func_001C23B0(Quad_101950* t, int mode, int c, void* z);
void func_001F4008(void* x);

void* func_00101950(void* self, void* x, int unused, int c)
{
    Frame_101950 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001F4008(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_1019F0 { s32 a, b, c, d; };
struct Frame_1019F0 { Quad_1019F0 q; Quad_1019F0 t; };

void func_0011B008(Quad_1019F0* q);
void func_0011B018(void* dst, Quad_1019F0* src);
void func_0011B060(Quad_1019F0* q, int mode);
void func_0011B0A8(Quad_1019F0* a, Quad_1019F0* b);
void func_0011B538(Quad_1019F0* q, int n);
void func_001C23B0(Quad_1019F0* t, int mode, int c, void* z);
void func_001F4808(void* x);

void* func_001019F0(void* self, void* x, int unused, int c)
{
    Frame_1019F0 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001F4808(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_101E10 { s32 a, b, c, d; };
struct Frame_101E10 { Quad_101E10 q; Quad_101E10 t; };

void func_0011B008(Quad_101E10* q);
void func_0011B018(void* dst, Quad_101E10* src);
void func_0011B060(Quad_101E10* q, int mode);
void func_0011B0A8(Quad_101E10* a, Quad_101E10* b);
void func_0011B538(Quad_101E10* q, int n);
void func_001C23B0(Quad_101E10* t, int mode, int c, void* z);
void func_0012E760(void* obj);

void* func_00101E10(void* self, void* x, int unused, int c)
{
    Frame_101E10 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0012E760(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_102A70 { s32 a, b, c, d; };
struct Frame_102A70 { Quad_102A70 q; Quad_102A70 t; };

void func_0011B008(Quad_102A70* q);
void func_0011B018(void* out, Quad_102A70* q);
void func_0011B060(Quad_102A70* q, int mode);
void func_0011B0A8(Quad_102A70* a, Quad_102A70* b);
void func_0011B538(Quad_102A70* q, int n);
void func_001C23B0(Quad_102A70* t, int mode, int c, void* z);
void func_00155FA0(void* x);

void* func_00102A70(void* self, void* x, int unused, int c)
{
    Frame_102A70 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00155FA0(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_102D40 { s32 a, b, c, d; };
struct Frame_102D40 { Quad_102D40 q; Quad_102D40 t; };

void func_0011B008(Quad_102D40* q);
void func_0011B018(void* out, Quad_102D40* q);
void func_0011B060(Quad_102D40* q, int mode);
void func_0011B0A8(Quad_102D40* a, Quad_102D40* b);
void func_0011B538(Quad_102D40* q, int n);
void func_001C23B0(Quad_102D40* t, int mode, int c, void* z);
void func_00158730(void* x);

void* func_00102D40(void* self, void* x, int unused, int c)
{
    Frame_102D40 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00158730(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_102F10 { s32 a, b, c, d; };
struct Frame_102F10 { Quad_102F10 q; Quad_102F10 t; };

void func_0011B008(Quad_102F10* q);
void func_0011B018(void* out, Quad_102F10* q);
void func_0011B060(Quad_102F10* q, int mode);
void func_0011B0A8(Quad_102F10* a, Quad_102F10* b);
void func_0011B538(Quad_102F10* q, int n);
void func_001C23B0(Quad_102F10* t, int mode, int c, void* z);
void func_00158730(void* x);

void* func_00102F10(void* self, void* x, int unused, int c)
{
    Frame_102F10 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00158730(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_1031C0 { s32 a, b, c, d; };
struct Frame_1031C0 { Quad_1031C0 q; Quad_1031C0 t; };

void func_0011B008(Quad_1031C0* q);
void func_0011B018(void* out, Quad_1031C0* q);
void func_0011B060(Quad_1031C0* q, int mode);
void func_0011B0A8(Quad_1031C0* a, Quad_1031C0* b);
void func_0011B538(Quad_1031C0* q, int n);
void func_001C23B0(Quad_1031C0* t, int mode, int c, void* z);
void func_001B6438(void* x);

void* func_001031C0(void* self, void* x, int unused, int c)
{
    Frame_1031C0 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001B6438(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_1034F0 { s32 a, b, c, d; };
struct Frame_1034F0 { Quad_1034F0 q; Quad_1034F0 t; };

void func_0011B008(Quad_1034F0* q);
void func_0011B018(void* dst, Quad_1034F0* src);
void func_0011B060(Quad_1034F0* q, int mode);
void func_0011B0A8(Quad_1034F0* a, Quad_1034F0* b);
void func_0011B538(Quad_1034F0* q, int n);
void func_001C23B0(Quad_1034F0* t, int mode, int c, void* z);
void func_001C0950(void* p);

void* func_001034F0(void* self, void* x, int unused, int c)
{
    Frame_1034F0 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001C0950(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_00103640 { s32 a, b, c, d; };
struct Frame_00103640 { Quad_00103640 q; Quad_00103640 t; s32 n; s32 out; };

void func_0011B008(Quad_00103640* q);
void func_0011B018(void* dst, Quad_00103640* src);
void func_0011B060(Quad_00103640* q, int mode);
void func_0011B0A8(Quad_00103640* a, Quad_00103640* b);
s32 func_0011B5F0(Quad_00103640* q, s32 flag);
void func_001C23B0(Quad_00103640* t, int mode, int c, void* z, void* z2);
s32 func_001DD6B0(void* self, s32 obj);

void* func_00103640(void* self, void* x, int unused, int c)
{
    Frame_00103640 f;
    func_0011B008(&f.q);
    f.n = 0xF;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0011B5F0(&f.q, func_001DD6B0(x, f.out));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_001036F0 { s32 a, b, c, d; };
struct Frame_001036F0 { Quad_001036F0 q; Quad_001036F0 t; s32 n; s32 out; };

void func_0011B008(Quad_001036F0* q);
void func_0011B018(void* dst, Quad_001036F0* src);
void func_0011B060(Quad_001036F0* q, int mode);
void func_0011B0A8(Quad_001036F0* a, Quad_001036F0* b);
s32 func_0011B5F0(Quad_001036F0* q, s32 flag);
void func_001C23B0(Quad_001036F0* t, int mode, int c, void* z, void* z2);
s32 func_001DD6D0(void* self, s32 obj);

void* func_001036F0(void* self, void* x, int unused, int c)
{
    Frame_001036F0 f;
    func_0011B008(&f.q);
    f.n = 0xF;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0011B5F0(&f.q, func_001DD6D0(x, f.out));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_001037A0 { s32 a, b, c, d; };
struct Frame_001037A0 { Quad_001037A0 q; Quad_001037A0 t; s32 n; s32 out; };

void func_0011B008(Quad_001037A0* q);
void func_0011B018(void* dst, Quad_001037A0* src);
void func_0011B060(Quad_001037A0* q, int mode);
void func_0011B0A8(Quad_001037A0* a, Quad_001037A0* b);
s32 func_0011B5F0(Quad_001037A0* q, s32 flag);
void func_001C23B0(Quad_001037A0* t, int mode, int c, void* z, void* z2);
s32 func_001DD6F0(void* self, s32 obj);

void* func_001037A0(void* self, void* x, int unused, int c)
{
    Frame_001037A0 f;
    func_0011B008(&f.q);
    f.n = 0xF;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0011B5F0(&f.q, func_001DD6F0(x, f.out));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct __attribute__((aligned(16))) Quad_00103850 { s32 a, b, c, d; };
struct Frame_00103850 { Quad_00103850 q; Quad_00103850 t; s32 n; s32 out[3]; };

void func_0011B008(Quad_00103850* q);
void func_0011B018(void* dst, Quad_00103850* src);
void func_0011B060(Quad_00103850* q, int mode);
void func_0011B0A8(Quad_00103850* a, Quad_00103850* b);
s32 func_0011B5F0(Quad_00103850* q, s32 flag);
void func_001C23B0(Quad_00103850* t, int mode, int c, void* z, void* z2);
s32 func_001DD710(void* x, s32 v);

void* func_00103850(void* self, void* x, int unused, int c)
{
    Frame_00103850 f;
    func_0011B008(&f.q);
    f.n = 0xF;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0011B5F0(&f.q, func_001DD710(x, f.out[0]));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct __attribute__((aligned(16))) Quad_00103900 { s32 a, b, c, d; };
struct Frame_00103900 { Quad_00103900 q; Quad_00103900 t; s32 n; s32 out[3]; };

void func_0011B008(Quad_00103900* q);
void func_0011B018(void* dst, Quad_00103900* src);
void func_0011B060(Quad_00103900* q, int mode);
void func_0011B0A8(Quad_00103900* a, Quad_00103900* b);
s32 func_0011B5F0(Quad_00103900* q, s32 flag);
void func_001C23B0(Quad_00103900* t, int mode, int c, void* z, void* z2);
s32 func_001DD758(void* x, s32 v);

void* func_00103900(void* self, void* x, int unused, int c)
{
    Frame_00103900 f;
    func_0011B008(&f.q);
    f.n = 0xF;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0011B5F0(&f.q, func_001DD758(x, f.out[0]));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct __attribute__((aligned(16))) Quad_001039B0 { s32 a, b, c, d; };
struct Frame_001039B0 { Quad_001039B0 q; Quad_001039B0 t; s32 n; s32 out[3]; };

void func_0011B008(Quad_001039B0* q);
void func_0011B018(void* dst, Quad_001039B0* src);
void func_0011B060(Quad_001039B0* q, int mode);
void func_0011B0A8(Quad_001039B0* a, Quad_001039B0* b);
s32 func_0011B5F0(Quad_001039B0* q, s32 flag);
void func_001C23B0(Quad_001039B0* t, int mode, int c, void* z, void* z2);
s32 func_001DD7A0(void* x, s32 v);

void* func_001039B0(void* self, void* x, int unused, int c)
{
    Frame_001039B0 f;
    func_0011B008(&f.q);
    f.n = 0xF;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0011B5F0(&f.q, func_001DD7A0(x, f.out[0]));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct __attribute__((aligned(16))) Quad_00103C10 { s32 a, b, c, d; };
struct Frame_00103C10 { Quad_00103C10 q; Quad_00103C10 t; s32 n; s32 out[3]; };

void func_0011B008(Quad_00103C10* q);
void func_0011B018(void* dst, Quad_00103C10* src);
void func_0011B060(Quad_00103C10* q, int mode);
void func_0011B0A8(Quad_00103C10* a, Quad_00103C10* b);
s32 func_0011B5F0(Quad_00103C10* q, s32 flag);
void func_001C23B0(Quad_00103C10* t, int mode, int c, void* z, void* z2);
s32 func_001DD8E8(void* x, s32 v);

void* func_00103C10(void* self, void* x, int unused, int c)
{
    Frame_00103C10 f;
    func_0011B008(&f.q);
    f.n = 0x1000;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0011B5F0(&f.q, func_001DD8E8(x, f.out[0]));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_103CC0 { s32 a, b, c, d; };
struct Frame_103CC0 { Quad_103CC0 q; Quad_103CC0 t; s32 n; s32 out; };

void func_0011B008(Quad_103CC0* q);
void func_0011B018(void* dst, Quad_103CC0* src);
void func_0011B060(Quad_103CC0* q, int mode);
void func_0011B0A8(Quad_103CC0* a, Quad_103CC0* b);
s32 func_0011B5F0(Quad_103CC0* q, s32 flag);
void func_001C23B0(Quad_103CC0* t, int mode, int c, void* z, void* z2);
s32 func_001DD908(void* self, s32 index);

void* func_00103CC0(void* self, void* x, int unused, int c)
{
    Frame_103CC0 f;
    func_0011B008(&f.q);
    f.n = 0x1000;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0011B5F0(&f.q, func_001DD908(x, f.out));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_103D70 { s32 a, b, c, d; };
struct Frame_103D70 { Quad_103D70 q; Quad_103D70 t; };

void func_0011B008(Quad_103D70* q);
void func_0011B018(void* dst, Quad_103D70* src);
void func_0011B060(Quad_103D70* q, int mode);
void func_0011B0A8(Quad_103D70* a, Quad_103D70* b);
s32 func_0011B570(Quad_103D70* q, s32 v);
void func_001C23B0(Quad_103D70* t, int mode, int c, void* z);
s32 func_001DD928(void* self);

void* func_00103D70(void* self, void* x, int unused, int c)
{
    Frame_103D70 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0011B570(&f.q, func_001DD928(x));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_103E10 { s32 a, b, c, d; };
struct Frame_103E10 { Quad_103E10 q; Quad_103E10 t; };

void func_0011B008(Quad_103E10* q);
void func_0011B018(void* dst, Quad_103E10* src);
void func_0011B060(Quad_103E10* q, int mode);
void func_0011B0A8(Quad_103E10* a, Quad_103E10* b);
void func_0011B538(Quad_103E10* q, int n);
void func_001C23B0(Quad_103E10* t, int mode, int c, void* z);
void func_001DDAD0(void* x);

void* func_00103E10(void* self, void* x, int unused, int c)
{
    Frame_103E10 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001DDAD0(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}
