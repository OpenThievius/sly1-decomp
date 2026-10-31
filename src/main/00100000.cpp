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

struct Quad_001027C0 { s32 a, b, c, d; };
struct Frame_001027C0 { Quad_001027C0 q; Quad_001027C0 t; s32 n; f32 out; };

void func_0011B008(Quad_001027C0* q);
void func_0011B018(void* dst, Quad_001027C0* src);
void func_0011B060(Quad_001027C0* q, int mode);
void func_0011B0A8(Quad_001027C0* a, Quad_001027C0* b);
void func_0011B538(Quad_001027C0* q, int n);
void func_001C23B0(Quad_001027C0* t, int mode, int c, void* z, void* z2);
s32 func_001B0488(void* p, f32 x);

void* func_001027C0(void* self, void* x, int unused, int c)
{
    Frame_001027C0 f;
    func_0011B008(&f.q);
    f.n = 1;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_001B0488(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_00102870 { s32 a, b, c, d; };
struct Frame_00102870 { Quad_00102870 q; Quad_00102870 t; s32 n; f32 out; };

void func_0011B008(Quad_00102870* q);
void func_0011B018(void* dst, Quad_00102870* src);
void func_0011B060(Quad_00102870* q, int mode);
void func_0011B0A8(Quad_00102870* a, Quad_00102870* b);
void func_0011B538(Quad_00102870* q, int n);
void func_001C23B0(Quad_00102870* t, int mode, int c, void* z, void* z2);
s32 func_001B0470(void* p, f32 x);

void* func_00102870(void* self, void* x, int unused, int c)
{
    Frame_00102870 f;
    func_0011B008(&f.q);
    f.n = 1;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_001B0470(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_00102920 { s32 a, b, c, d; };
struct Frame_00102920 { Quad_00102920 q; Quad_00102920 t; s32 n; f32 out; };

void func_0011B008(Quad_00102920* q);
void func_0011B018(void* dst, Quad_00102920* src);
void func_0011B060(Quad_00102920* q, int mode);
void func_0011B0A8(Quad_00102920* a, Quad_00102920* b);
void func_0011B538(Quad_00102920* q, int n);
void func_001C23B0(Quad_00102920* t, int mode, int c, void* z, void* z2);
s32 func_00155F78(void* p, f32 x);

void* func_00102920(void* self, void* x, int unused, int c)
{
    Frame_00102920 f;
    func_0011B008(&f.q);
    f.n = 1;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_00155F78(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_100FA8 { s32 a, b, c, d; };
struct Frame_100FA8 { Quad_100FA8 q; Quad_100FA8 t; s32 n; f32 f; };

void func_0011B008(Quad_100FA8* q);
void func_0011B018(void* out, Quad_100FA8* q);
void func_0011B060(Quad_100FA8* q, int mode);
void func_0011B0A8(Quad_100FA8* a, Quad_100FA8* b);
void func_0011B538(Quad_100FA8* q, int n);
void func_001C23B0(Quad_100FA8* t, int mode, int c, void* z, void* z2);
s32 func_0012AAE8(void* self, f32 value);

void* func_00100FA8(void* self, void* x, int unused, int c)
{
    Frame_100FA8 f;
    func_0011B008(&f.q);
    f.n = 1;
    func_001C23B0(&f.t, 1, c, &f.n, &f.f);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0012AAE8(x, f.f);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_101208 { s32 a, b, c, d; };
struct Frame_101208 { Quad_101208 q; Quad_101208 t; s32 n; f32 f; };

void func_0011B008(Quad_101208* q);
void func_0011B018(void* out, Quad_101208* q);
void func_0011B060(Quad_101208* q, int mode);
void func_0011B0A8(Quad_101208* a, Quad_101208* b);
void func_0011B538(Quad_101208* q, int n);
void func_001C23B0(Quad_101208* t, int mode, int c, void* z, void* z2);
s32 func_00126CB8(void* self, f32 value);

void* func_00101208(void* self, void* x, int unused, int c)
{
    Frame_101208 f;
    func_0011B008(&f.q);
    f.n = 1;
    func_001C23B0(&f.t, 1, c, &f.n, &f.f);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_00126CB8(x, f.f);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_1012B8 { s32 a, b, c, d; };
struct Frame_1012B8 { Quad_1012B8 q; Quad_1012B8 t; s32 n; f32 f; };

void func_0011B008(Quad_1012B8* q);
void func_0011B018(void* out, Quad_1012B8* q);
void func_0011B060(Quad_1012B8* q, int mode);
void func_0011B0A8(Quad_1012B8* a, Quad_1012B8* b);
void func_0011B538(Quad_1012B8* q, int n);
void func_001C23B0(Quad_1012B8* t, int mode, int c, void* z, void* z2);
s32 func_00126D60(void* self, f32 value);

void* func_001012B8(void* self, void* x, int unused, int c)
{
    Frame_1012B8 f;
    func_0011B008(&f.q);
    f.n = 1;
    func_001C23B0(&f.t, 1, c, &f.n, &f.f);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_00126D60(x, f.f);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_101568 { s32 a, b, c, d; };
struct Frame_101568 { Quad_101568 q; Quad_101568 t; s32 x; s32 y; };

typedef void (*VFn_101568)(void* self, s32 v);
struct Obj_101568 { VFn_101568* vtbl; };

void func_0011B008(Quad_101568* q);
void func_0011B018(void* out, Quad_101568* q);
void func_0011B060(Quad_101568* q, int mode);
void func_0011B0A8(Quad_101568* a, Quad_101568* b);
void func_0011B538(Quad_101568* q, int n);
int func_001C23B0(Quad_101568* t, int mode, int c, s32* x, s32* y);

void* func_00101568(void* out, void* self, int unused, int c)
{
    Frame_101568 f;
    func_0011B008(&f.q);
    s32* px = &f.x;
    s32* py = &f.y;
    *px = 0x2000;
    (void)func_001C23B0(&f.t, 1, c, px, py);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    ((Obj_101568*)self)->vtbl[35](self, f.y);
    func_0011B538(&f.q, 0x22);
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

struct Quad_1016F0 { s32 a, b, c, d; };
struct Frame_1016F0 { Quad_1016F0 q; Quad_1016F0 t; s32 x; s32 y; };

void func_0011B008(Quad_1016F0* q);
void func_0011B018(void* out, Quad_1016F0* q);
void func_0011B060(Quad_1016F0* q, int mode);
void func_0011B0A8(Quad_1016F0* a, Quad_1016F0* b);
void func_0011B538(Quad_1016F0* q, int n);
int func_001C23B0(Quad_1016F0* t, int mode, int c, s32* x, s32* y);
void func_001BB1E0(void* self, u32 value);

void* func_001016F0(void* out, void* self, int unused, int c)
{
    Frame_1016F0 f;
    func_0011B008(&f.q);
    s32* px = &f.x;
    s32* py = &f.y;
    *px = 0x1000;
    (void)func_001C23B0(&f.t, 1, c, px, py);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001BB1E0(self, f.y);
    func_0011B538(&f.q, 0x22);
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

struct Quad_101C88 { s32 a, b, c, d; };
struct Frame_101C88 { Quad_101C88 q; Quad_101C88 t; s32 n; s32 v; };

void func_0011B008(Quad_101C88* q);
void func_0011B018(void* out, Quad_101C88* q);
void func_0011B060(Quad_101C88* q, int mode);
void func_0011B0A8(Quad_101C88* a, Quad_101C88* b);
void func_0011B5B0(void* obj, f32 x);
int func_001C23B0(Quad_101C88* t, int mode, int c, void* z, void* z2);
f32 func_0012CCC0(void* obj, s32 id);

void* func_00101C88(void* self, void* x, int unused, int c)
{
    Frame_101C88 f;
    func_0011B008(&f.q);
    f.n = 6;
    (void)func_001C23B0(&f.t, 1, c, &f.n, &f.v);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    f32 r = func_0012CCC0(x, f.v);
    func_0011B5B0(&f.q, r);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_101EB0 { s32 a, b, c, d; };
struct Frame_101EB0 { Quad_101EB0 q; Quad_101EB0 t; s32 n; s32 out; };

void func_0011B008(Quad_101EB0* q);
void func_0011B018(void* dst, Quad_101EB0* src);
void func_0011B060(Quad_101EB0* q, int mode);
void func_0011B0A8(Quad_101EB0* a, Quad_101EB0* b);
void func_0011B538(Quad_101EB0* q, int n);
int func_001C23B0(Quad_101EB0* t, int mode, int c, void* z, void* z2);
void func_0012F190(void* obj, s32 v);

void* func_00101EB0(void* self, void* x, int unused, int c)
{
    Frame_101EB0 f;
    func_0011B008(&f.q);
    f.n = 5;
    (void)func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0012F190(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_1023F8 { s32 a, b, c, d; };
struct Frame_1023F8 { Quad_1023F8 q; Quad_1023F8 t; s32 n; s32 out; };

void func_0011B008(Quad_1023F8* q);
void func_0011B018(void* dst, Quad_1023F8* src);
void func_0011B060(Quad_1023F8* q, int mode);
void func_0011B0A8(Quad_1023F8* a, Quad_1023F8* b);
s32 func_0011B5F0(Quad_1023F8* q, s32 flag);
s32 func_001C23B0(Quad_1023F8* t, int mode, int c, void* z, void* z2);

typedef s32 (*VFn_1023F8)(void* self, s32 v);
struct Obj_1023F8 { VFn_1023F8* vtbl; };

void* func_001023F8(void* self, void* x, int unused, int c)
{
    Frame_1023F8 f;
    func_0011B008(&f.q);
    f.n = 0x1000;
    (void)func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 flag = ((Obj_1023F8*)x)->vtbl[79](x, f.out);
    (void)func_0011B5F0(&f.q, flag);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_1024B0 { s32 a, b, c, d; };
struct Frame_1024B0 { Quad_1024B0 q; Quad_1024B0 t; s32 n; s32 out; };

void func_0011B008(Quad_1024B0* q);
void func_0011B018(void* dst, Quad_1024B0* src);
void func_0011B060(Quad_1024B0* q, int mode);
void func_0011B0A8(Quad_1024B0* a, Quad_1024B0* b);
void func_0011B538(Quad_1024B0* q, int n);
s32 func_001C23B0(Quad_1024B0* t, int mode, int c, void* z, void* z2);
void func_00123AB0(void* object, s32 mode);

void* func_001024B0(void* self, void* x, int unused, int c)
{
    Frame_1024B0 f;
    func_0011B008(&f.q);
    f.n = 0x1000;
    (void)func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00123AB0(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_102650 { s32 a, b, c, d; };
struct Frame_102650 { Quad_102650 q; Quad_102650 t; s32 n; s32 out; };

void func_0011B008(Quad_102650* q);
void func_0011B018(void* dst, Quad_102650* src);
void func_0011B060(Quad_102650* q, int mode);
void func_0011B0A8(Quad_102650* a, Quad_102650* b);
void func_0011B538(Quad_102650* q, int n);
s32 func_001C23B0(Quad_102650* t, int mode, int c, void* z, void* z2);

typedef void (*VFn_102650)(void* self, s32 v);
struct Obj_102650 { VFn_102650* vtbl; };

void* func_00102650(void* self, void* x, int unused, int c)
{
    Frame_102650 f;
    func_0011B008(&f.q);
    f.n = 0x1000;
    (void)func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    VFn_102650 fn = ((Obj_102650*)x)->vtbl[77];
    if (fn != 0) {
        fn(x, f.out);
    }
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_100438 { s32 a, b, c, d; };
struct Frame_100438 { Quad_100438 q; Quad_100438 t; s32 n; s32 out; };

void func_0011B008(Quad_100438* q);
void func_0011B018(void* dst, Quad_100438* src);
void func_0011B060(Quad_100438* q, int mode);
void func_0011B0A8(Quad_100438* a, Quad_100438* b);
void func_0011B538(Quad_100438* q, int n);
s32 func_001C23B0(Quad_100438* t, int mode, int c, void* z, void* z2);

typedef void (*VFn_100438)(void* self, s32 v);
struct Obj_100438 { VFn_100438* vtbl; };

void* func_00100438(void* self, void* x, int unused, int c)
{
    Frame_100438 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    (void)func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    ((Obj_100438*)x)->vtbl[25](x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_100368 { s32 a, b, c, d; };
struct Blob_100368 { u8 b[8]; };
struct Ctx_100368 { s32 pad; };

extern Blob_100368 D_00248D80;

void func_0011B008(Quad_100368* q);
void func_0011B0A8(Quad_100368* a, Quad_100368* b);
void func_0011B060(Quad_100368* q, s32 mode);
void func_0011B018(void* out, Quad_100368* q);
s32 func_0011B8A8(Quad_100368* q, s32 v);
void func_001C23B0(Quad_100368* t, s32 mode, s32 c, Blob_100368* z, s32* o1, s32* o2);
s32 func_00183058(Ctx_100368* x, s32 a, s32 b);

void* func_00100368(void* self, void* x, s32 unused, s32 c)
{
    Quad_100368 q;
    Blob_100368 blob;
    Quad_100368 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    blob = D_00248D80;
    func_001C23B0(&t, 2, c, &blob, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B8A8(&q, func_00183058((Ctx_100368*)x, o1, o2));
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_00100650 { s32 a, b, c, d; };
struct Blob_00100650 { u8 b[8]; };
struct Ctx_00100650 { s32 pad; };

extern Blob_00100650 D_00248D88;

void func_0011B008(Quad_00100650* q);
void func_0011B0A8(Quad_00100650* a, Quad_00100650* b);
void func_0011B060(Quad_00100650* q, s32 mode);
void func_0011B018(void* out, Quad_00100650* q);
void func_0011B538(Quad_00100650* q, s32 n);
void func_001C23B0(Quad_00100650* t, s32 mode, s32 c, Blob_00100650* z, s32* o1, s32* o2);
s32 func_00183910(Ctx_00100650* x, s32 a, s32 b);

void* func_00100650(void* self, void* x, s32 unused, s32 c)
{
    Quad_00100650 q;
    Blob_00100650 blob;
    Quad_00100650 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    blob = D_00248D88;
    func_001C23B0(&t, 2, c, &blob, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_00183910((Ctx_00100650*)x, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_00100720 { s32 a, b, c, d; };
struct Blob_00100720 { u8 b[8]; };
struct Ctx_00100720 { s32 pad; };

extern Blob_00100720 D_00248D90;

void func_0011B008(Quad_00100720* q);
void func_0011B0A8(Quad_00100720* a, Quad_00100720* b);
void func_0011B060(Quad_00100720* q, s32 mode);
void func_0011B018(void* out, Quad_00100720* q);
void func_0011B538(Quad_00100720* q, s32 n);
void func_001C23B0(Quad_00100720* t, s32 mode, s32 c, Blob_00100720* z, s32* o1, s32* o2);
s32 func_00183990(Ctx_00100720* x, s32 a, s32 b);

void* func_00100720(void* self, void* x, s32 unused, s32 c)
{
    Quad_00100720 q;
    Blob_00100720 blob;
    Quad_00100720 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    blob = D_00248D90;
    func_001C23B0(&t, 2, c, &blob, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_00183990((Ctx_00100720*)x, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_00100A78 { s32 a, b, c, d; };
struct Blob_00100A78 { u8 b[8]; };
struct Ctx_00100A78 { s32 pad; };

extern Blob_00100A78 D_00248DB0;

void func_0011B008(Quad_00100A78* q);
void func_0011B0A8(Quad_00100A78* a, Quad_00100A78* b);
void func_0011B060(Quad_00100A78* q, s32 mode);
void func_0011B018(void* out, Quad_00100A78* q);
void func_0011B538(Quad_00100A78* q, s32 n);
void func_001C23B0(Quad_00100A78* t, s32 mode, s32 c, Blob_00100A78* z, s32* o1, s32* o2);
s32 func_00183BB8(Ctx_00100A78* x, s32 a, s32 b);

void* func_00100A78(void* self, void* x, s32 unused, s32 c)
{
    Quad_00100A78 q;
    Blob_00100A78 blob;
    Quad_00100A78 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    blob = D_00248DB0;
    func_001C23B0(&t, 2, c, &blob, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_00183BB8((Ctx_00100A78*)x, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_00101620 { s32 a, b, c, d; };
struct Blob_00101620 { u8 b[8]; };
struct Ctx_00101620 { s32 pad; };


void func_0011B008(Quad_00101620* q);
void func_0011B0A8(Quad_00101620* a, Quad_00101620* b);
void func_0011B060(Quad_00101620* q, s32 mode);
void func_0011B018(void* out, Quad_00101620* q);
void func_0011B538(Quad_00101620* q, s32 n);
void func_001C23B0(Quad_00101620* t, s32 mode, s32 c, Blob_00101620* z, s32* o1, s32* o2);
s32 func_0012B5B8(Ctx_00101620* x, s32 a, s32 b);

void* func_00101620(void* self, void* x, s32 unused, s32 c)
{
    Quad_00101620 q;
    Blob_00101620 blob;
    Quad_00101620 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    blob = *(Blob_00101620*)&D_00248D80;
    func_001C23B0(&t, 2, c, &blob, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_0012B5B8((Ctx_00101620*)x, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_00101F60 { s32 a, b, c, d; };
struct Blob_00101F60 { u8 b[8]; };
struct Ctx_00101F60 { s32 pad; };

extern Blob_00101F60 D_00248E38;

void func_0011B008(Quad_00101F60* q);
void func_0011B0A8(Quad_00101F60* a, Quad_00101F60* b);
void func_0011B060(Quad_00101F60* q, s32 mode);
void func_0011B018(void* out, Quad_00101F60* q);
void func_0011B538(Quad_00101F60* q, s32 n);
void func_001C23B0(Quad_00101F60* t, s32 mode, s32 c, Blob_00101F60* z, s32* o1, s32* o2);
s32 func_0012E928(Ctx_00101F60* x, s32 a, s32 b);

void* func_00101F60(void* self, void* x, s32 unused, s32 c)
{
    Quad_00101F60 q;
    Blob_00101F60 blob;
    Quad_00101F60 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    blob = D_00248E38;
    func_001C23B0(&t, 2, c, &blob, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_0012E928((Ctx_00101F60*)x, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_00103350 { s32 a, b, c, d; };
struct Blob_00103350 { u8 b[8]; };
struct Ctx_00103350 { s32 pad; };

extern Blob_00103350 D_00248E90;

void func_0011B008(Quad_00103350* q);
void func_0011B0A8(Quad_00103350* a, Quad_00103350* b);
void func_0011B060(Quad_00103350* q, s32 mode);
void func_0011B018(void* out, Quad_00103350* q);
void func_0011B538(Quad_00103350* q, s32 n);
void func_001C23B0(Quad_00103350* t, s32 mode, s32 c, Blob_00103350* z, s32* o1, s32* o2);
s32 func_001C09D8(Ctx_00103350* x, s32 a, s32 b);

void* func_00103350(void* self, void* x, s32 unused, s32 c)
{
    Quad_00103350 q;
    Blob_00103350 blob;
    Quad_00103350 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    blob = D_00248E90;
    func_001C23B0(&t, 2, c, &blob, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_001C09D8((Ctx_00103350*)x, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_00103420 { s32 a, b, c, d; };
struct Blob_00103420 { u8 b[8]; };
struct Ctx_00103420 { s32 pad; };


void func_0011B008(Quad_00103420* q);
void func_0011B0A8(Quad_00103420* a, Quad_00103420* b);
void func_0011B060(Quad_00103420* q, s32 mode);
void func_0011B018(void* out, Quad_00103420* q);
void func_0011B538(Quad_00103420* q, s32 n);
void func_001C23B0(Quad_00103420* t, s32 mode, s32 c, Blob_00103420* z, s32* o1, s32* o2);
s32 func_001C08B0(Ctx_00103420* x, s32 a, s32 b);

void* func_00103420(void* self, void* x, s32 unused, s32 c)
{
    Quad_00103420 q;
    Blob_00103420 blob;
    Quad_00103420 t;
    s32 o1;
    s32 o2;
    func_0011B008(&q);
    blob = *(Blob_00103420*)&D_00248E90;
    func_001C23B0(&t, 2, c, &blob, &o1, &o2);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    (void)func_001C08B0((Ctx_00103420*)x, o1, o2);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

extern u8 D_00248DF0[];

struct Quad_101860 { s32 a, b, c, d; };
struct Frame_101860 { Quad_101860 q; Quad_101860 blk; Quad_101860 t; s32 o0, o1, o2, o3; };
struct Self_101860;

void func_0011B008(Quad_101860* q);
void func_0011B018(void* dst, Quad_101860* src);
void func_0011B060(Quad_101860* q, int mode);
void func_0011B0A8(Quad_101860* a, Quad_101860* b);
void func_0011B538(Quad_101860* q, int n);
void func_001C23B0(Quad_101860* t, int mode, int c, void* z, s32* o0, s32* o1, s32* o2, s32* o3);
s32 func_001F42D0(Self_101860* self, s32 a1, s32 a2, s32 a3, s32 a4);

void* func_00101860(void* self, void* x, int unused, int c)
{
    Frame_101860 f;
    func_0011B008(&f.q);
    *(Quad_101860*)&f.blk = *(Quad_101860*)D_00248DF0;
    func_001C23B0(&f.t, 4, c, &f.blk, &f.o0, &f.o1, &f.o2, &f.o3);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 r = func_001F42D0((Self_101860*)x, f.o0, f.o1, f.o2, f.o3);
    (void)r;
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

extern u8 D_00248E00[];

struct Quad_101A90 { s32 a, b, c, d; };
struct Frame_101A90 { Quad_101A90 q; Quad_101A90 blk; Quad_101A90 t; s32 o0, o1, o2, o3; };
struct Self_101A90;

void func_0011B008(Quad_101A90* q);
void func_0011B018(void* dst, Quad_101A90* src);
void func_0011B060(Quad_101A90* q, int mode);
void func_0011B0A8(Quad_101A90* a, Quad_101A90* b);
s32 func_0011B8A8(Quad_101A90* q, s32 v);
void func_001C23B0(Quad_101A90* t, int mode, int c, void* z, s32* o0, s32* o1, s32* o2, s32* o3);
s32 func_0012C7D8(Self_101A90* self, s32 a1, f32 f1, f32 f2, s32 a2);

void* func_00101A90(void* self, void* x, int unused, int c)
{
    Frame_101A90 f;
    func_0011B008(&f.q);
    *(Quad_101A90*)&f.blk = *(Quad_101A90*)D_00248E00;
    func_001C23B0(&f.t, 4, c, &f.blk, &f.o0, &f.o1, &f.o2, &f.o3);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 r = func_0012C7D8((Self_101A90*)x, f.o0, *(f32*)&f.o1, *(f32*)&f.o2, f.o3);
    func_0011B8A8(&f.q, r);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

extern u8 D_00248DF0[];

struct Quad_102178 { s32 a, b, c, d; };
struct Frame_102178 { Quad_102178 q; Quad_102178 blk; Quad_102178 t; s32 o0, o1, o2, o3; };
struct Self_102178;

void func_0011B008(Quad_102178* q);
void func_0011B018(void* dst, Quad_102178* src);
void func_0011B060(Quad_102178* q, int mode);
void func_0011B0A8(Quad_102178* a, Quad_102178* b);
void func_0011B538(Quad_102178* q, int n);
void func_001C23B0(Quad_102178* t, int mode, int c, void* z, s32* o0, s32* o1, s32* o2, s32* o3);
s32 func_00140750(Self_102178* self, s32 a1, s32 a2, s32 a3, s32 a4);

void* func_00102178(void* self, void* x, int unused, int c)
{
    Frame_102178 f;
    func_0011B008(&f.q);
    *(Quad_102178*)&f.blk = *(Quad_102178*)D_00248DF0;
    func_001C23B0(&f.t, 4, c, &f.blk, &f.o0, &f.o1, &f.o2, &f.o3);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 r = func_00140750((Self_102178*)x, f.o0, f.o1, f.o2, f.o3);
    (void)r;
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

extern u8 D_00248DF0[];

struct Quad_102268 { s32 a, b, c, d; };
struct Frame_102268 { Quad_102268 q; Quad_102268 blk; Quad_102268 t; s32 o0, o1, o2, o3; };
struct Self_102268;

void func_0011B008(Quad_102268* q);
void func_0011B018(void* dst, Quad_102268* src);
void func_0011B060(Quad_102268* q, int mode);
void func_0011B0A8(Quad_102268* a, Quad_102268* b);
void func_0011B538(Quad_102268* q, int n);
void func_001C23B0(Quad_102268* t, int mode, int c, void* z, s32* o0, s32* o1, s32* o2, s32* o3);
s32 func_00140770(Self_102268* self, s32 a1, s32 a2, s32 a3, s32 a4);

void* func_00102268(void* self, void* x, int unused, int c)
{
    Frame_102268 f;
    func_0011B008(&f.q);
    *(Quad_102268*)&f.blk = *(Quad_102268*)D_00248DF0;
    func_001C23B0(&f.t, 4, c, &f.blk, &f.o0, &f.o1, &f.o2, &f.o3);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 r = func_00140770((Self_102268*)x, f.o0, f.o1, f.o2, f.o3);
    (void)r;
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

extern u8 D_00248DF0[];

struct Quad_102560 { s32 a, b, c, d; };
struct Frame_102560 { Quad_102560 q; Quad_102560 blk; Quad_102560 t; s32 o0, o1, o2, o3; };
struct Self_102560;

void func_0011B008(Quad_102560* q);
void func_0011B018(void* dst, Quad_102560* src);
void func_0011B060(Quad_102560* q, int mode);
void func_0011B0A8(Quad_102560* a, Quad_102560* b);
void func_0011B538(Quad_102560* q, int n);
void func_001C23B0(Quad_102560* t, int mode, int c, void* z, s32* o0, s32* o1, s32* o2, s32* o3);
s32 func_00123D08(Self_102560* self, s32 a1, s32 a2, s32 a3, s32 a4);

void* func_00102560(void* self, void* x, int unused, int c)
{
    Frame_102560 f;
    func_0011B008(&f.q);
    *(Quad_102560*)&f.blk = *(Quad_102560*)D_00248DF0;
    func_001C23B0(&f.t, 4, c, &f.blk, &f.o0, &f.o1, &f.o2, &f.o3);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 r = func_00123D08((Self_102560*)x, f.o0, f.o1, f.o2, f.o3);
    (void)r;
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// Callee declared s32 and called as (void): schedules the three address adds before the 8-byte copy.

struct Quad_1007F0 { s32 a, b, c, d; };
struct Pair_1007F0 { s32 a, b; };
struct Frame_1007F0 { Quad_1007F0 q; Pair_1007F0 n; s32 pad[2]; Quad_1007F0 t; s32 a; f32 b; };

extern u8 D_00248D98[];

void func_0011B008(Quad_1007F0* q);
void func_0011B018(void* out, Quad_1007F0* q);
void func_0011B060(Quad_1007F0* q, int mode);
void func_0011B0A8(Quad_1007F0* a, Quad_1007F0* b);
void func_0011B538(Quad_1007F0* q, int n);
s32 func_001C23B0(Quad_1007F0* t, int mode, int c, void* z, void* z2, void* z3);
void func_00183A10(void* a0, s32 a1, f32 x);

void* func_001007F0(void* self, void* x, int unused, int c)
{
    Frame_1007F0 f;
    func_0011B008(&f.q);
    f.n = *(Pair_1007F0*)D_00248D98;
    (void)func_001C23B0(&f.t, 2, c, &f.n, &f.a, &f.b);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00183A10(x, f.a, f.b);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// Retail sets the frame addresses before the 8-byte rodata copy; the void call of an s32-returning callee keeps that order.

struct __attribute__((packed)) Pack_001008B8 { s32 a, b; };
struct __attribute__((aligned(16))) Quad_001008B8 { s32 w[4]; };
struct __attribute__((aligned(16))) Frame_001008B8 {
    Quad_001008B8 q;
    Pack_001008B8 rod;
    s32 pad0[2];
    Quad_001008B8 b;
    Quad_001008B8 t;
    s32 out;
};

extern u8 D_00248DA0[];

void func_0011B008(Quad_001008B8* q);
void func_0011B018(void* dst, Quad_001008B8* src);
void func_0011B060(Quad_001008B8* q, s32 mode);
void func_0011B0A8(Quad_001008B8* a, Quad_001008B8* b);
void func_0011B538(Quad_001008B8* q, s32 n);
s32 func_001C23B0(Quad_001008B8* t, s32 mode, s32 c, void* z, void* z2, void* z3);
void func_00183A90(void* a0, s32 a1, Quad_001008B8* a2);

void* func_001008B8(void* self, void* x, s32 unused, s32 c)
{
    Frame_001008B8 f;
    func_0011B008(&f.q);
    f.rod = *(Pack_001008B8*)D_00248DA0;
    (void)func_001C23B0(&f.t, 2, c, &f.rod, &f.out, &f.b);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00183A90(x, f.out, &f.b);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// Callee declared s32 and called as (void): schedules the three address adds before the 8-byte copy.

struct Quad_100EE0 { s32 a, b, c, d; };
struct Pair_100EE0 { s32 a, b; };
struct Frame_100EE0 { Quad_100EE0 q; Pair_100EE0 n; s32 pad[2]; Quad_100EE0 t; f32 x; f32 y; };

extern u8 D_00248DD0[];

void func_0011B008(Quad_100EE0* q);
void func_0011B018(void* out, Quad_100EE0* q);
void func_0011B060(Quad_100EE0* q, int mode);
void func_0011B0A8(Quad_100EE0* a, Quad_100EE0* b);
void func_0011B538(Quad_100EE0* q, int n);
s32 func_001C23B0(Quad_100EE0* t, int mode, int c, void* z, void* z2, void* z3);
void func_0012AA50(void* self, f32 a, f32 b);

void* func_00100EE0(void* self, void* x, int unused, int c)
{
    Frame_100EE0 f;
    func_0011B008(&f.q);
    f.n = *(Pair_100EE0*)D_00248DD0;
    (void)func_001C23B0(&f.t, 2, c, &f.n, &f.x, &f.y);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0012AA50(x, f.x, f.y);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// Retail computes the argument addresses before the 24-byte blob copy; a void call of an s32-returning callee and a pre-taken &t.i1 keep that order.

struct Quad_102DE0 { s32 a; s32 b; s32 c; s32 d; };
struct Blob_102DE0 { u8 bytes[24]; };
struct Tail_102DE0 { s32 i0; s32 i1; f32 f0; f32 f1; };
struct Obj_102DE0 { u8 pad0[4]; };

extern u8 D_00248E58[];
void func_0011B008(Quad_102DE0* q);
void func_0011B060(Quad_102DE0* q, s32 mode);
void func_0011B0A8(Quad_102DE0* a, Quad_102DE0* b);
void func_0011B018(void* out, Quad_102DE0* src);
void func_0011B538(Quad_102DE0* q, s32 n);
s32 func_001C23B0(Quad_102DE0* t, s32 mode, s32 c, Blob_102DE0* z, s32* p4, s32* p5, Quad_102DE0* p6, Quad_102DE0* p7, f32* p8, f32* p9);
void func_00158778(Obj_102DE0* a0, s32 a1, s32 a2, Quad_102DE0* a3, Quad_102DE0* a4, f32 x, f32 y);

void* func_00102DE0(void* out, Obj_102DE0* self, s32 unused, s32 c)
{
    Quad_102DE0 r;
    Blob_102DE0 blob;
    Quad_102DE0 q40;
    Quad_102DE0 q50;
    Quad_102DE0 q60;
    Tail_102DE0 t;

    func_0011B008(&r);
    s32* p5 = &t.i1;
    blob = *(Blob_102DE0*)D_00248E58;
    (void)func_001C23B0(&q60, 6, c, &blob, &t.i0, p5, &q40, &q50, &t.f0, &t.f1);
    func_0011B0A8(&r, &q60);
    func_0011B060(&q60, 2);
    func_00158778(self, t.i0, t.i1, &q40, &q50, t.f0, t.f1);
    func_0011B538(&r, 0x22);
    func_0011B018(out, &r);
    func_0011B060(&r, 2);
    return out;
}

// Retail copies the 12-byte rodata as ldl/ldr plus lw and sets the frame addresses first; a non-packed 12-byte struct gives that copy, and a void call of an s32-returning callee keeps the order.

struct Pair_001030E0 { s32 a, b; };
struct Rod_001030E0 { Pair_001030E0 p; s32 c; };
struct __attribute__((aligned(16))) Quad_001030E0 { s32 w[4]; };
struct __attribute__((aligned(16))) Frame_001030E0 {
    Quad_001030E0 q;
    Rod_001030E0 rod;
    s32 pad0;
    Quad_001030E0 b;
    s32 o1;
    s32 o2;
    s32 o3;
};

struct Obj_001030E0;

extern u8 D_00248E70[];

void func_0011B008(Quad_001030E0* q);
void func_0011B018(void* dst, Quad_001030E0* src);
void func_0011B060(Quad_001030E0* q, s32 mode);
void func_0011B0A8(Quad_001030E0* a, Quad_001030E0* b);
s32 func_0011B8A8(Quad_001030E0* q, s32 v);
s32 func_001C23B0(Quad_001030E0* t, s32 mode, s32 c, void* z, void* z2, void* z3, void* z4);
void* func_001B6290(Obj_001030E0* a, s32 b, s32 c, s32 d);

void* func_001030E0(void* self, void* x, s32 unused, s32 c)
{
    Frame_001030E0 f;
    func_0011B008(&f.q);
    f.rod = *(Rod_001030E0*)D_00248E70;
    (void)func_001C23B0(&f.b, 3, c, &f.rod, &f.o1, &f.o2, &f.o3);
    func_0011B0A8(&f.q, &f.b);
    func_0011B060(&f.b, 2);
    s32 v = (s32)func_001B6290((Obj_001030E0*)x, f.o1, f.o2, f.o3);
    func_0011B8A8(&f.q, v);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// Frame, the seven-argument call and the tail; the argument addresses are formed before the copy from D_00248DC0.

struct Quad_100E08 { s32 a, b, c, d; };
struct Trip_100E08 { s32 a, b, c; };
struct Frame_100E08 { Quad_100E08 q; Trip_100E08 n; s32 pad; Quad_100E08 t; f32 o0; f32 o1; s32 o2; };
struct Obj_100E08;

void func_0011B008(Quad_100E08* q);
void func_0011B018(void* dst, Quad_100E08* src);
void func_0011B060(Quad_100E08* q, s32 mode);
void func_0011B0A8(Quad_100E08* a, Quad_100E08* b);
void func_0011B538(Quad_100E08* q, s32 n);
s32 func_001C23B0(Quad_100E08* t, s32 mode, s32 c, void* z, void* z2, void* z3, void* z4);
void func_0012A8D8(Obj_100E08* self, s32 a, f32 x, f32 y);

extern u8 D_00248DC0[];

void* func_00100E08(void* self, Obj_100E08* x, s32 unused, s32 c)
{
    Frame_100E08 f;
    Trip_100E08* np;
    f32* o0p;
    f32* o1p;
    s32* o2p;
    func_0011B008(&f.q);
    np = &f.n;
    o0p = &f.o0;
    o1p = &f.o1;
    o2p = &f.o2;
    f.n = *(Trip_100E08*)D_00248DC0;
    (void)func_001C23B0(&f.t, 3, c, np, o0p, o1p, o2p);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0012A8D8((Obj_100E08*)x, f.o2, f.o0, f.o1);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_101058 { s32 a, b, c, d; } __attribute__((aligned(16)));
struct Blob_101058 { s32 a, b, c, d, e; };
struct Host_101058;

void func_0011B008(Quad_101058* q);
void func_0011B018(void* out, Quad_101058* q);
void func_0011B060(Quad_101058* q, int mode);
void func_0011B0A8(Quad_101058* a, Quad_101058* b);
void func_0011B538(Quad_101058* q, int n);
s32 func_001C23B0(Quad_101058* t, int mode, int c, Blob_101058* z, s32* i0, f32* f0, f32* f1, f32* f2, Quad_101058* extra);
void func_0012AF38(Host_101058* self, s32 value, Quad_101058* src, f32 x, f32 y, f32 z);
extern u8 D_00248DD8[];

void* func_00101058(void* out, Host_101058* host, int unused, int c)
{
    Quad_101058 q;
    Blob_101058 blob;
    Quad_101058 t;
    Quad_101058 u;
    s32 i0;
    f32 f0, f1, f2;
    func_0011B008(&q);
    blob = *(Blob_101058*)D_00248DD8;
    func_001C23B0(&u, 5, c, &blob, &i0, &f0, &f1, &f2, &t);
    func_0011B0A8(&q, &u);
    func_0011B060(&u, 2);
    func_0012AF38(host, i0, &t, f0, f1, f2);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

// Matched with func_001C23B0 declared s32 and called as (void); the copy stays before the call.

struct Quad_101D38 { s32 a, b, c, d; };
struct Trip_101D38 { s32 a, b, c; };
struct Frame_101D38 { Quad_101D38 q; Trip_101D38 n; s32 pad; Quad_101D38 t; s32 o0; f32 o1; f32 o2; };
struct Obj_101D38;

void func_0011B008(Quad_101D38* q);
void func_0011B018(void* dst, Quad_101D38* src);
void func_0011B060(Quad_101D38* q, s32 mode);
void func_0011B0A8(Quad_101D38* a, Quad_101D38* b);
void func_0011B538(Quad_101D38* q, s32 n);
s32 func_001C23B0(Quad_101D38* t, s32 mode, s32 c, void* z, void* z2, void* z3, void* z4);
void func_0012F0A0(Obj_101D38* self, s32 a, f32 x, f32 y);

extern u8 D_00248E28[];

void* func_00101D38(void* self, Obj_101D38* x, s32 unused, s32 c)
{
    Frame_101D38 f;
    func_0011B008(&f.q);
    f.n = *(Trip_101D38*)D_00248E28;
    (void)func_001C23B0(&f.t, 3, c, &f.n, &f.o0, &f.o1, &f.o2);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0012F0A0((Obj_101D38*)x, f.o0, f.o1, f.o2);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// EXACT: func_001C23B0 declared s32 and called as (void); that alone moved the copy of D_00248E40 after the out-pointer addiu.
struct Quad_102B10 { s32 a, b, c, d; } __attribute__((aligned(16)));
struct Blob_102B10 { s32 a, b, c, d, e, f; };

void func_0011B008(Quad_102B10* q);
void func_0011B018(void* out, Quad_102B10* q);
void func_0011B060(Quad_102B10* q, int mode);
void func_0011B0A8(Quad_102B10* a, Quad_102B10* b);
void func_0011B538(Quad_102B10* q, int n);
s32 func_001C23B0(Quad_102B10* t, int mode, int c, Blob_102B10 z, s32* i0, s32* i1, f32* f0, f32* f1, f32* f2, f32* f3);
void func_001557D0(void* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w);
extern u8 D_00248E40[];

void* func_00102B10(void* self, void* x, int unused, int c)
{
    Quad_102B10 q;
    Blob_102B10 blob;
    Quad_102B10 t;
    s32 i0, i1;
    f32 f0, f1, f2, f3;
    func_0011B008(&q);
    blob = *(Blob_102B10*)D_00248E40;
    (void)func_001C23B0(&t, 6, c, blob, &i0, &i1, &f0, &f1, &f2, &f3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001557D0(x, i0, i1, f0, f1, f2, f3);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

// EXACT: func_001C23B0 declared s32 and called as (void); the copy of D_00248E80 then follows the argument addiu.

struct Quad_103260 { s32 a, b, c, d; };
struct Key_103260 { s32 a, b, c; };
struct Frame_103260 { Quad_103260 q; Key_103260 k; s32 pad; s32 out[4]; Quad_103260 t; s32 a; s32 b; };
struct Obj_103260 { s32 unused; };

void func_0011B008(Quad_103260* q);
void func_0011B018(void* dst, Quad_103260* src);
void func_0011B060(Quad_103260* q, int mode);
void func_0011B0A8(Quad_103260* a, Quad_103260* b);
void func_0011B538(Quad_103260* q, int n);
s32 func_001C23B0(Quad_103260* t, int mode, int c, void* z, void* z2, void* z3, void* z4);
void func_001DD950(Obj_103260* unused, s32 a, s32 b, void* c);
extern u8 D_00248E80[];

void* func_00103260(void* self, void* p, int unused, int c)
{
    Frame_103260 f;
    func_0011B008(&f.q);
    f.k = *(Key_103260*)D_00248E80;
    (void)func_001C23B0(&f.t, 3, c, &f.k, &f.a, &f.b, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001DD950((Obj_103260*)p, f.a, f.b, &f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_00103B40 { s32 a, b, c, d; };
struct __attribute__((packed)) Pair_00103B40 { s32 a, b; };
struct Frame_00103B40 { Quad_00103B40 q; Pair_00103B40 p; s32 pad[2]; Quad_00103B40 t; s32 out1; s32 out2; };
struct Callee_00103B40;

extern u8 D_00248EA8[];

void func_0011B008(Quad_00103B40* q);
void func_0011B018(void* dst, Quad_00103B40* src);
void func_0011B060(Quad_00103B40* q, int mode);
void func_0011B0A8(Quad_00103B40* a, Quad_00103B40* b);
void func_0011B538(Quad_00103B40* q, int n);
s32 func_0011B570(Quad_00103B40* q, s32 v);
void func_001C23B0(Quad_00103B40* t, int mode, int c, void* z, void* z2, void* z3);
s32 func_001DD888(Callee_00103B40* self, s32 a, s32 b);

void* func_00103B40(void* self, void* x, int unused, int c)
{
    Frame_00103B40 f;
    func_0011B008(&f.q);
    f.p = *(Pair_00103B40*)&D_00248EA8;
    func_001C23B0(&f.t, 2, c, &f.p, &f.out1, &f.out2);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 r = func_001DD888((Callee_00103B40*)x, f.out1, f.out2);
    func_0011B570(&f.q, r);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// EXACT: func_001C23B0 declared s32 and called as (void); the copy from D_00248EB0 then follows the three out-pointer addiu.

struct Quad_00103EB0 { s32 a, b, c, d; };
struct __attribute__((packed)) Pair_00103EB0 { s32 a, b; };
struct Frame_00103EB0 { Quad_00103EB0 q; Pair_00103EB0 p; s32 pad[2]; Quad_00103EB0 t; s32 out1; s32 out2; };
struct Callee_00103EB0;

extern u8 D_00248EB0[];

void func_0011B008(Quad_00103EB0* q);
void func_0011B018(void* dst, Quad_00103EB0* src);
void func_0011B060(Quad_00103EB0* q, int mode);
void func_0011B0A8(Quad_00103EB0* a, Quad_00103EB0* b);
void func_0011B538(Quad_00103EB0* q, int n);
s32 func_001C23B0(Quad_00103EB0* t, int mode, int c, void* z, void* z2, void* z3);
void func_001DDB20(Callee_00103EB0* self, s32 a, s32 b);

void* func_00103EB0(void* self, void* x, int unused, int c)
{
    Frame_00103EB0 f;
    func_0011B008(&f.q);
    f.p = *(Pair_00103EB0*)&D_00248EB0;
    (void)func_001C23B0(&f.t, 2, c, &f.p, &f.out1, &f.out2);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001DDB20((Callee_00103EB0*)x, f.out1, f.out2);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// NEAR: the 8-byte rodata copy into the frame is emitted before the a3/a4 stack addresses; retail sets a3/a4 first (7 diff lines, same size 220 B)

struct __attribute__((packed)) Pack_00100998 { s32 a, b; };
struct __attribute__((aligned(16))) Quad_00100998 { s32 w[4]; };
struct __attribute__((aligned(16))) Frame_00100998 {
    Quad_00100998 q;
    Pack_00100998 rod;
    s32 pad0[2];
    Quad_00100998 b;
    Quad_00100998 t;
    s32 out;
};

extern u8 D_00248DA8[];

void func_0011B008(Quad_00100998* q);
void func_0011B018(void* dst, Quad_00100998* src);
void func_0011B060(Quad_00100998* q, s32 mode);
void func_0011B0A8(Quad_00100998* a, Quad_00100998* b);
void func_0011B538(Quad_00100998* q, s32 n);
s32 func_001C23B0(Quad_00100998* t, s32 mode, s32 c, void* z, void* z2, void* z3);
void func_00183B20(void* a0, s32 a1, Quad_00100998* a2);

void* func_00100998(void* self, void* x, s32 unused, s32 c)
{
    Frame_00100998 f;
    func_0011B008(&f.q);
    f.rod = *(Pack_00100998*)D_00248DA8;
    (void)func_001C23B0(&f.t, 2, c, &f.rod, &f.out, &f.b);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00183B20(x, f.out, &f.b);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// NEAR: the 8-byte rodata copy into the frame is emitted before the a3/a4 stack addresses; retail sets a3/a4 first (7 diff lines, same size 220 B)

struct __attribute__((packed)) Pack_00100B48 { s32 a, b; };
struct __attribute__((aligned(16))) Quad_00100B48 { s32 w[4]; };
struct __attribute__((aligned(16))) Frame_00100B48 {
    Quad_00100B48 q;
    Pack_00100B48 rod;
    s32 pad0[2];
    Quad_00100B48 b;
    Quad_00100B48 t;
    s32 out;
};

extern u8 D_00248DB8[];

void func_0011B008(Quad_00100B48* q);
void func_0011B018(void* dst, Quad_00100B48* src);
void func_0011B060(Quad_00100B48* q, s32 mode);
void func_0011B0A8(Quad_00100B48* a, Quad_00100B48* b);
void func_0011B538(Quad_00100B48* q, s32 n);
s32 func_001C23B0(Quad_00100B48* t, s32 mode, s32 c, void* z, void* z2, void* z3);
void func_00183C38(void* a0, s32 a1, Quad_00100B48* a2);

void* func_00100B48(void* self, void* x, s32 unused, s32 c)
{
    Frame_00100B48 f;
    func_0011B008(&f.q);
    f.rod = *(Pack_00100B48*)D_00248DB8;
    (void)func_001C23B0(&f.t, 2, c, &f.rod, &f.out, &f.b);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00183C38(x, f.out, &f.b);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// NEAR: call sequence, frame and the 24-byte blob copy match; retail computes &sp[0x74] and the blob-copy addresses earlier, so about 18 lines of instruction order differ

struct Quad_102FB0 { s32 a; s32 b; s32 c; s32 d; };
struct Blob_102FB0 { u8 bytes[24]; };
struct Tail_102FB0 { s32 i0; s32 i1; f32 f0; f32 f1; };
struct Obj_102FB0 { u8 pad0[4]; };

extern u8 D_00248E58[];
void func_0011B008(Quad_102FB0* q);
void func_0011B060(Quad_102FB0* q, s32 mode);
void func_0011B0A8(Quad_102FB0* a, Quad_102FB0* b);
void func_0011B018(void* out, Quad_102FB0* src);
void func_0011B538(Quad_102FB0* q, s32 n);
s32 func_001C23B0(Quad_102FB0* t, s32 mode, s32 c, Blob_102FB0* z, s32* p4, s32* p5, Quad_102FB0* p6, Quad_102FB0* p7, f32* p8, f32* p9);
void func_00158778(Obj_102FB0* a0, s32 a1, s32 a2, Quad_102FB0* a3, Quad_102FB0* a4, f32 x, f32 y);

void* func_00102FB0(void* out, Obj_102FB0* self, s32 unused, s32 c)
{
    Quad_102FB0 r;
    Blob_102FB0 blob;
    Quad_102FB0 q40;
    Quad_102FB0 q50;
    Quad_102FB0 q60;
    Tail_102FB0 t;

    func_0011B008(&r);
    blob = *(Blob_102FB0*)D_00248E58;
    (void)func_001C23B0(&q60, 6, c, &blob, &t.i0, &t.i1, &q40, &q50, &t.f0, &t.f1);
    func_0011B0A8(&r, &q60);
    func_0011B060(&q60, 2);
    func_00158778(self, t.i0, t.i1, &q40, &q50, t.f0, t.f1);
    func_0011B538(&r, 0x22);
    func_0011B018(out, &r);
    func_0011B060(&r, 2);
    return out;
}

struct __attribute__((packed)) Pair_00103A60 { s32 a, b; };
struct Rod_00103A60 { Pair_00103A60 p; s32 c; };
struct __attribute__((aligned(16))) Quad_00103A60 { s32 w[4]; };
struct __attribute__((aligned(16))) Frame_00103A60 {
    Quad_00103A60 q;
    Rod_00103A60 rod;
    s32 pad0;
    Quad_00103A60 b;
    s32 o1;
    s32 o2;
    s32 o3;
};

struct Obj_00103A60;

extern u8 D_00248E98[];

void func_0011B008(Quad_00103A60* q);
void func_0011B018(void* dst, Quad_00103A60* src);
void func_0011B060(Quad_00103A60* q, s32 mode);
void func_0011B0A8(Quad_00103A60* a, Quad_00103A60* b);
s32 func_001C23B0(Quad_00103A60* t, s32 mode, s32 c, void* z, void* z2, void* z3, void* z4);
void func_001DD7E8(Obj_00103A60* self, void* obj, s32 key, s32 value);
void func_0011B538(Quad_00103A60* q, s32 n);

void* func_00103A60(void* self, void* x, s32 unused, s32 c)
{
    Frame_00103A60 f;
    func_0011B008(&f.q);
    f.rod = *(Rod_00103A60*)D_00248E98;
    (void)func_001C23B0(&f.b, 3, c, &f.rod, &f.o1, &f.o2, &f.o3);
    func_0011B0A8(&f.q, &f.b);
    func_0011B060(&f.b, 2);
    func_001DD7E8((Obj_00103A60*)x, (void*)f.o1, f.o2, f.o3);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void func_0011B008(Quad_102B10* q);
void func_0011B018(void* out, Quad_102B10* q);
void func_0011B060(Quad_102B10* q, int mode);
void func_0011B0A8(Quad_102B10* a, Quad_102B10* b);
void func_0011B538(Quad_102B10* q, int n);
s32 func_001C23B0(Quad_102B10* t, int mode, int c, Blob_102B10* z, s32* i0, s32* i1, f32* f0, f32* f1, f32* f2, f32* f3);
void func_00158D40(void* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w);
extern u8 D_00248E40[];

void* func_00102C28(void* self, void* x, int unused, int c)
{
    Quad_102B10 q;
    Blob_102B10 blob;
    Quad_102B10 t;
    s32 i0, i1;
    f32 f0, f1, f2, f3;
    func_0011B008(&q);
    blob = *(Blob_102B10*)D_00248E40;
    (void)func_001C23B0(&t, 6, c, &blob, &i0, &i1, &f0, &f1, &f2, &f3);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00158D40(x, i0, i1, f0, f1, f2, f3);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}
