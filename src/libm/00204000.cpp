// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

f32 func_00205318(f32 x)
{
    s32 i0 = *(s32*)&x;
    s32 j0 = ((i0 >> 23) & 0xff) - 0x7f;
    s32 i;

    if (j0 < 0x17) {
        if (j0 < 0) {
            if (1.0e30f + x > 0.0f) {
                if (i0 >= 0) {
                    i0 = 0;
                } else if ((i0 & 0x7fffffff) != 0) {
                    i0 = 0xbf800000;
                }
            }
        } else {
            i = 0x7fffff >> j0;
            if ((i0 & i) == 0) {
                return x;
            }
            if (1.0e30f + x > 0.0f) {
                if (i0 < 0) {
                    i0 += 0x800000 >> j0;
                }
                i0 &= ~i;
            }
        }
    } else {
        if (j0 == 0x80) {
            return x + x;
        }
        return x;
    }
    *(s32*)&x = i0;
    return x;
}

struct Exc_205578 {
    s32 type;
    const char* name;
    double arg2;
    double arg1;
    double ret;
    s32 err;
};

extern const s32 D_0024FF78;
extern u8 D_0024F8F0[];
f32 func_00206298(f32 x);
s32 func_00209238(f32 x);
f32 func_002052F8(f32 x);
double func_001FD868(f32 x);
s32 func_00208FE8(Exc_205578* e);
s32* func_002014F0();
f32 func_001FD578(double v);

f32 func_00205578(f32 x) {
    f32 r = func_00206298(x);
    s32 mode = D_0024FF78;
    if (mode != -1) {
        if (func_00209238(x) == 0) {
            if (func_002052F8(x) > 1.0f) {
                Exc_205578 e;
                e.type = 1;
                e.name = (const char*)D_0024F8F0;
                e.err = 0;
                e.arg1 = func_001FD868(x);
                e.ret = 0.0;
                e.arg2 = e.arg1;
                if (mode == 2 || func_00208FE8(&e) == 0) {
                    *func_002014F0() = 0x21;
                }
                if (e.err != 0) {
                    *func_002014F0() = e.err;
                }
                return func_001FD578(e.ret);
            }
        }
    }
    return r;
}

struct Exc_205678 {
    s32 type;
    const char* name;
    double arg1;
    double arg2;
    double ret;
    s32 err;
};

extern const s32 D_0024FF78;
extern u8 D_0024F8F8[];
f32 func_002066C8(f32 x);
s32 func_00209238(f32 x);
f32 func_002052F8(f32 x);
double func_001FD868(f32 x);
s32 func_00208FE8(Exc_205678* e);
s32* func_002014F0();
f32 func_001FD578(double v);

f32 func_00205678(f32 x)
{
    f32 r = func_002066C8(x);
    s32 mode = D_0024FF78;
    if (mode != -1) {
        if (func_00209238(x) == 0) {
            if (1.0f < func_002052F8(x)) {
                Exc_205678 e;
                e.type = 1;
                e.name = (const char*)D_0024F8F8;
                e.err = 0;
                double v = func_001FD868(x);
                e.arg2 = v;
                e.arg1 = v;
                e.ret = 0.0;
                if (mode == 2 || func_00208FE8(&e) == 0) {
                    *func_002014F0() = 0x21;
                }
                if (e.err != 0) {
                    *func_002014F0() = e.err;
                }
                return func_001FD578(e.ret);
            }
        }
    }
    return r;
}

struct Exc_2058A0 {
    s32 type;
    const char *name;
    double a;
    double b;
    double r;
    s32 err;
};

extern const s32 D_0024FF78;
extern char D_0024F908[];
extern double D_0024F910;

f32 func_00206D50(f32 x, f32 y);
s32 func_00209238(f32 x);
double func_001FD868(f32 x);
s32 func_00208FE8(Exc_2058A0 *e);
s32 *func_002014F0(void);
f32 func_001FD578(double v);

f32 func_002058A0(f32 x, f32 y)
{
    f32 r = func_00206D50(x, y);
    s32 mode = D_0024FF78;
    if (mode != -1 && func_00209238(y) == 0 && func_00209238(x) == 0 && y == 0.0f) {
        Exc_2058A0 e;
        e.type = 1;
        e.name = D_0024F908;
        e.err = 0;
        e.a = func_001FD868(x);
        e.b = func_001FD868(y);
        if (mode == 0)
            e.r = func_001FD868(x);
        else
            e.r = D_0024F910;
        if (D_0024FF78 == 2 || func_00208FE8(&e) == 0)
            *func_002014F0() = 0x21;
        if (e.err != 0)
            *func_002014F0() = e.err;
        return func_001FD578(e.r);
    }
    return r;
}

struct Exc_2059E0 {
    s32 type;
    const char *name;
    double a;
    double b;
    double r;
    s32 err;
};

extern const s32 D_0024FF78;
extern char D_0024F918[];
extern const double D_0024FF70;

f32 func_00206FA0(f32 x);
s32 func_00209238(f32 x);
double func_001FD868(f32 x);
double func_001FCD78(double a, double b);
s32 func_00208FE8(Exc_2059E0 *e);
s32 *func_002014F0(void);
f32 func_001FD578(double v);

f32 func_002059E0(f32 x)
{
    f32 r = func_00206FA0(x);
    s32 mode = D_0024FF78;
    if (mode == -1 || func_00209238(x) != 0 || 0.0f < x)
        return r;
    Exc_2059E0 e;
    e.err = 0;
    e.name = D_0024F918;
    e.a = e.b = func_001FD868(x);
    if (mode == 0)
        e.r = -3.4028234663852886e38;
    else
        e.r = func_001FCD78(0.0, D_0024FF70);
    if (x == 0.0f) {
        e.type = 2;
        if (D_0024FF78 == 2)
            *func_002014F0() = 0x22;
        else if (func_00208FE8(&e) == 0)
            *func_002014F0() = 0x21;
    } else {
        e.type = 1;
        if (D_0024FF78 == 2 || func_00208FE8(&e) == 0)
            *func_002014F0() = 0x21;
    }
    if (e.err != 0)
        *func_002014F0() = e.err;
    return func_001FD578(e.r);
}

struct Exc_205B28 {
    s32 type;
    const char *name;
    double a;
    double b;
    double r;
    s32 err;
};

extern const s32 D_0024FF78;
extern char D_0024F928[];
extern const double D_0024FF70;

f32 func_002072C8(f32 x);
s32 func_00209238(f32 x);
double func_001FD868(f32 x);
double func_001FCD78(double a, double b);
s32 func_00208FE8(Exc_205B28 *e);
s32 *func_002014F0(void);
f32 func_001FD578(double v);

f32 func_00205B28(f32 x)
{
    f32 r = func_002072C8(x);
    s32 mode = D_0024FF78;
    if (mode != -1 && func_00209238(x) == 0 && x <= 0.0f) {
        Exc_205B28 e;
        e.err = 0;
        e.name = D_0024F928;
        e.a = e.b = func_001FD868(x);
        if (mode == 0)
            e.r = -3.4028234663852886e38;
        else
            e.r = func_001FCD78(0.0, D_0024FF70);
        if (x == 0.0f) {
            e.type = 2;
            if (D_0024FF78 == 2)
                *func_002014F0() = 0x22;
            else if (func_00208FE8(&e) == 0)
                *func_002014F0() = 0x21;
        } else {
            e.type = 1;
            if (D_0024FF78 == 2 || func_00208FE8(&e) == 0)
                *func_002014F0() = 0x21;
        }
        if (e.err != 0)
            *func_002014F0() = e.err;
        return func_001FD578(e.r);
    }
    return r;
}

struct Exc_205C78 {
    s32 type;
    const char* name;
    double arg1;
    double arg2;
    double ret;
    s32 err;
};

extern const s32 D_0024FF78;
extern u8 D_0024F938[];
extern const double D_0024FF70;
extern double D_0024F940;
f32 func_002073F8(f32 x, f32 y);
s32 func_00209238(f32 x);
s32 func_00209210(f32 x);
double func_001FD868(f32 x);
f32 func_001FD578(double v);
double func_001FCD78(double a, double b);
double func_001FCDE0(double a, double b);
s32 func_001FD308(double a, double b);
double func_00209010(double x);
s32 func_00208FE8(Exc_205C78* e);
s32* func_002014F0();

f32 func_00205C78(f32 x, f32 y)
{
    f32 z = func_002073F8(x, y);
    s32 mode = D_0024FF78;
    Exc_205C78 e;

    if (mode == -1 || func_00209238(y) != 0) {
        return z;
    }
    if (func_00209238(x) != 0) {
        if (y == 0.0f) {
            e.type = 1;
            e.name = (const char*)D_0024F938;
            e.err = 0;
            e.arg1 = func_001FD868(x);
            e.arg2 = func_001FD868(y);
            e.ret = func_001FD868(x);
            if (mode == 2) {
                e.ret = 1.0;
            } else if (func_00208FE8(&e) == 0) {
                *func_002014F0() = 0x21;
            }
            if (e.err != 0) {
                *func_002014F0() = e.err;
            }
            return func_001FD578(e.ret);
        }
        return z;
    }
    if (x == 0.0f) {
        if (y == 0.0f) {
            e.type = 1;
            e.name = (const char*)D_0024F938;
            e.err = 0;
            e.arg1 = func_001FD868(x);
            e.arg2 = func_001FD868(y);
            e.ret = 0.0;
            if (mode != 0) {
                e.ret = 1.0;
            } else if (func_00208FE8(&e) == 0) {
                *func_002014F0() = 0x21;
            }
            if (e.err != 0) {
                *func_002014F0() = e.err;
            }
            return func_001FD578(e.ret);
        }
        if (func_00209210(y) != 0 && y < 0.0f) {
            e.type = 1;
            e.name = (const char*)D_0024F938;
            e.err = 0;
            e.arg1 = func_001FD868(x);
            e.arg2 = func_001FD868(y);
            if (mode == 0) {
                e.ret = 0.0;
            } else {
                e.ret = func_001FCD78(0.0, D_0024FF70);
            }
            if (D_0024FF78 == 2 || func_00208FE8(&e) == 0) {
                *func_002014F0() = 0x21;
            }
            if (e.err != 0) {
                *func_002014F0() = e.err;
            }
            return func_001FD578(e.ret);
        }
        return z;
    }
    if (func_00209210(z) == 0 && func_00209210(x) != 0 && func_00209210(y) != 0) {
        if (func_00209238(z) != 0) {
            e.type = 1;
            e.name = (const char*)D_0024F938;
            e.err = 0;
            e.arg1 = func_001FD868(x);
            e.arg2 = func_001FD868(y);
            if (mode == 0) {
                e.ret = 0.0;
            } else {
                e.ret = D_0024F940;
            }
            if (D_0024FF78 == 2 || func_00208FE8(&e) == 0) {
                *func_002014F0() = 0x21;
            }
        } else {
            e.type = 3;
            e.name = (const char*)D_0024F938;
            e.err = 0;
            e.arg1 = func_001FD868(x);
            e.arg2 = func_001FD868(y);
            if (mode == 0) {
                e.ret = 3.40282346638528859812e+38;
                y = func_001FD578(func_001FCDE0(func_001FD868(y), 0.5));
                if (func_001FD308(func_001FD868(x), 0.0) < 0
                    && func_001FD308(func_00209010(func_001FD868(y)), func_001FD868(y)) != 0) {
                    e.ret = -3.40282346638528859812e+38;
                }
            } else {
                e.ret = D_0024FF70;
                y = func_001FD578(func_001FCDE0(func_001FD868(y), 0.5));
                if (func_001FD308(func_001FD868(x), 0.0) < 0
                    && func_001FD308(func_00209010(func_001FD868(y)), func_001FD868(y)) != 0) {
                    e.ret = func_001FCD78(0.0, D_0024FF70);
                }
            }
            if (D_0024FF78 == 2 || func_00208FE8(&e) == 0) {
                *func_002014F0() = 0x22;
            }
        }
        if (e.err != 0) {
            *func_002014F0() = e.err;
        }
        return func_001FD578(e.ret);
    }
    if (z == 0.0f && func_00209210(x) != 0 && func_00209210(y) != 0) {
        e.type = 4;
        e.name = (const char*)D_0024F938;
        e.err = 0;
        e.arg1 = func_001FD868(x);
        e.arg2 = func_001FD868(y);
        e.ret = 0.0;
        if (D_0024FF78 == 2 || func_00208FE8(&e) == 0) {
            *func_002014F0() = 0x22;
        }
        if (e.err != 0) {
            *func_002014F0() = e.err;
        }
        return func_001FD578(e.ret);
    }
    return z;
}
