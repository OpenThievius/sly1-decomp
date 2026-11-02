// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "float_bits.h"

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

extern f32 D_0024F890[];
extern f32 D_0024F8A0[];
extern f32 D_0024F8B0[];
f32 func_002052F8(f32 x);

f32 func_00204F68(f32 x)
{
    s32 hx;
    FLOAT_TO_BITS(hx, x);
    s32 ix = hx & 0x7FFFFFFF;
    s32 id;
    if (ix >= 0x50800000) {
        if (ix > 0x7F800000) {
            return x + x;
        }
        if (hx > 0) {
            return D_0024F890[3] + D_0024F8A0[3];
        }
        return -D_0024F890[3] - D_0024F8A0[3];
    }
    if (ix < 0x3EE00000) {
        if (ix < 0x31000000) {
            if (1.0e30f + x > 1.0f) {
                return x;
            }
        }
        id = -1;
    } else {
        x = func_002052F8(x);
        if (ix < 0x3F980000) {
            if (ix < 0x3F300000) {
                id = 0;
                x = (2.0f * x - 1.0f) / (2.0f + x);
            } else {
                id = 1;
                x = (x - 1.0f) / (x + 1.0f);
            }
        } else {
            if (ix < 0x401C0000) {
                id = 2;
                x = (x - 1.5f) / (1.0f + 1.5f * x);
            } else {
                id = 3;
                x = -1.0f / x;
            }
        }
    }
    f32 z = x * x;
    f32 w = z * z;
    f32 s1 = z * (D_0024F8B0[0] + w * (D_0024F8B0[2] + w * (D_0024F8B0[4] + w * (D_0024F8B0[6] + w * (D_0024F8B0[8] + w * D_0024F8B0[10])))));
    f32 s2 = w * (D_0024F8B0[1] + w * (D_0024F8B0[3] + w * (D_0024F8B0[5] + w * (D_0024F8B0[7] + w * D_0024F8B0[9]))));
    if (id < 0) {
        return x - x * (s1 + s2);
    }
    z = D_0024F890[id] - ((x * (s1 + s2) - D_0024F8A0[id]) - x);
    return hx < 0 ? -z : z;
}

s32 func_00207C88(f32 x, f32* y);
f32 func_002081A0(f32 x, f32 y);
f32 func_00208C48(s32 iy, f32 x, f32 y);

f32 func_00205210(f32 x)
{
    f32 y[2];
    s32 n;
    s32 ix;
    FLOAT_TO_BITS(ix, x);
    ix = ix & 0x7fffffff;

    if (ix <= 0x3F490FD8) {
        return func_002081A0(x, 0.0f);
    }
    if (ix > 0x7F7FFFFF) {
        return x - x;
    }
    n = func_00207C88(x, y);
    switch (n & 3) {
    case 0:
        return func_002081A0(y[0], y[1]);
    case 1:
        return -func_00208C48(1, y[0], y[1]);
    case 2:
        return -func_002081A0(y[0], y[1]);
    default:
        return func_00208C48(1, y[0], y[1]);
    }
}

f32 func_002052F8(f32 x)
{
    s32 hx;
    FLOAT_TO_BITS(hx, x);
    hx &= 0x7FFFFFFF;
    BITS_TO_FLOAT(x, hx);
    return x;
}

s32 func_00207C88(f32 x, f32* y);
f32 func_002081A0(f32 x, f32 y);
f32 func_00208C48(s32 iy, f32 x, f32 y);

f32 func_00205400(f32 x)
{
    s32 ix;
    FLOAT_TO_BITS(ix, x);
    ix &= 0x7fffffff;
    f32 y[2];
    s32 n;

    if (ix <= 0x3F490FD8) {
        return func_00208C48(0, x, 0.0f);
    }
    if (ix > 0x7F7FFFFF) {
        return x - x;
    }
    n = func_00207C88(x, y);
    switch (n & 3) {
    case 0:
        return func_00208C48(1, y[0], y[1]);
    case 1:
        return func_002081A0(y[0], y[1]);
    case 2:
        return -func_00208C48(1, y[0], y[1]);
    default:
        return -func_002081A0(y[0], y[1]);
    }
}

struct Red_2054F0 { f32 f0; f32 f4; };
s32 func_00207C88(struct Red_2054F0* p);
f32 func_00208D50(f32 x, f32 y, s32 q);

f32 func_002054F0(f32 x)
{
    struct Red_2054F0 buf;
    s32 bits;
    f32 y;
    s32 q;
    s32 n;

    FLOAT_TO_BITS(bits, x);
    bits &= 0x7FFFFFFF;
    if (0x3F490FDA >= bits) {
        y = 0.0f;
        q = 1;
    } else {
        if (bits > 0x7F7FFFFF) return x - x;
        n = func_00207C88(&buf);
        x = buf.f0;
        y = buf.f4;
        q = 1;
        q -= (n & 1) << 1;
    }
    return func_00208D50(x, y, q);
}

f32 func_00208068(f32 x);

f32 func_00206298(f32 x)
{
    f32 t, num, den, ratio, root, head, tail;
    s32 bits, mag, hb;

    FLOAT_TO_BITS(bits, x);
    mag = bits & 0x7fffffff;

    if (mag == 0x3f800000) {
        if (bits > 0) {
            return 0.0f;
        }
        return 3.14159274101f;
    } else if (mag > 0x3f800000) {
        return (x - x) / (x - x);
    }
    if (mag < 0x3f000000) {
        if (mag <= 0x23000000) {
            return 1.57079637051f;
        }
        t = x * x;
        num = t * (1.66666671634e-01f + t * (-3.25565814972e-01f + t * (2.01212525368e-01f + t * (-4.00555357337e-02f + t * (7.91535014287e-04f + t * 3.47933091689e-05f)))));
        den = 1.0f + t * (-2.40339493752e+00f + t * (2.02094578743e+00f + t * (-6.88283979893e-01f + t * 7.70381540060e-02f)));
        ratio = num / den;
        return 1.57079625130f - (x - (7.54978941586e-08f - x * ratio));
    } else if (bits < 0) {
        t = (1.0f + x) * 0.5f;
        num = t * (1.66666671634e-01f + t * (-3.25565814972e-01f + t * (2.01212525368e-01f + t * (-4.00555357337e-02f + t * (7.91535014287e-04f + t * 3.47933091689e-05f)))));
        den = 1.0f + t * (-2.40339493752e+00f + t * (2.02094578743e+00f + t * (-6.88283979893e-01f + t * 7.70381540060e-02f)));
        root = func_00208068(t);
        ratio = num / den;
        return 3.14159250259f - 2.0f * (root + (ratio * root - 7.54978941586e-08f));
    } else {
        t = (1.0f - x) * 0.5f;
        root = func_00208068(t);
        head = root;
        FLOAT_TO_BITS(hb, head);
        BITS_TO_FLOAT(head, hb & 0xfffff000);
        tail = (t - head * head) / (root + head);
        num = t * (1.66666671634e-01f + t * (-3.25565814972e-01f + t * (2.01212525368e-01f + t * (-4.00555357337e-02f + t * (7.91535014287e-04f + t * 3.47933091689e-05f)))));
        den = 1.0f + t * (-2.40339493752e+00f + t * (2.02094578743e+00f + t * (-6.88283979893e-01f + t * 7.70381540060e-02f)));
        ratio = num / den;
        return 2.0f * (head + (ratio * root + tail));
    }
}

f32 func_002052F8(f32 x);
f32 func_00208068(f32 x);

f32 func_002066C8(f32 x)
{
    s32 hx;
    FLOAT_TO_BITS(hx, x);
    s32 ix = hx & 0x7FFFFFFF;
    f32 t, w, p, q, s, r, c;
    if (ix == 0x3F800000) {
        return x * 1.57079625129699707f + x * 7.5497894159e-08f;
    }
    if (ix > 0x3F800000) {
        return (x - x) / (x - x);
    }
    if (ix < 0x3F000000) {
        if (ix < 0x32000000) {
            if (1.0e30f + x > 1.0f) {
                return x;
            }
        } else {
            t = x * x;
        }
        p = t * (0.16666667163372040f + t * (-0.32556581497192383f + t * (0.20121252536773682f + t * (-0.040055535733699799f + t * (7.9153501428663731e-04f + t * 3.4793309169013e-05f)))));
        q = 1.0f + t * (-2.4033949375152588f + t * (2.0209457874298096f + t * (-0.68828397989273071f + t * 0.07703815400600433f)));
        w = p / q;
        return x + x * w;
    }
    w = 1.0f - func_002052F8(x);
    t = w * 0.5f;
    p = t * (0.16666667163372040f + t * (-0.32556581497192383f + t * (0.20121252536773682f + t * (-0.040055535733699799f + t * (7.9153501428663731e-04f + t * 3.4793309169013e-05f)))));
    q = 1.0f + t * (-2.4033949375152588f + t * (2.0209457874298096f + t * (-0.68828397989273071f + t * 0.07703815400600433f)));
    s = func_00208068(t);
    if (ix >= 0x3F79999A) {
        w = p / q;
        t = 1.57079625129699707f - (2.0f * (s + s * w) - 7.5497894159e-08f);
    } else {
        s32 sb;
        FLOAT_TO_BITS(sb, s);
        sb &= 0xFFFFF000;
        BITS_TO_FLOAT(w, sb);
        c = (t - w * w) / (s + w);
        r = p / q;
        p = 2.0f * s * r - (7.5497894159e-08f - 2.0f * c);
        q = 0.78539818525314331f - 2.0f * w;
        t = 0.78539818525314331f - (p - q);
    }
    if (hx > 0) {
        return t;
    }
    return -t;
}

extern const f32 D_0024FA50[];
extern const f32 D_0024FA58[];
extern const f32 D_0024FA60[];

f32 func_00208068(f32 x);
f32 func_002052F8(f32 x);
f32 func_00209260(f32 x, s32 n);

f32 func_002073F8(f32 x, f32 y)
{
    f32 z, ax, z_h, z_l, p_h, p_l;
    f32 y1, t1, t2, r, s, t, u, v, w;
    s32 i, j, k, yisint, n;
    s32 hx, hy, ix, iy, is;

    FLOAT_TO_BITS(hx, x);
    FLOAT_TO_BITS(hy, y);
    ix = hx & 0x7fffffff;
    iy = hy & 0x7fffffff;

    if (iy == 0) {
        return 1.0f;
    }
    if (ix > 0x7f800000 || iy > 0x7f800000) {
        return x + y;
    }

    yisint = 0;
    if (hx < 0) {
        if (iy > 0x4b7fffff) {
            yisint = 2;
        } else if (iy > 0x3f7fffff) {
            k = (iy >> 23) - 0x7f;
            j = iy >> (23 - k);
            if ((j << (23 - k)) == iy) {
                yisint = 2 - (j & 1);
            }
        }
    }

    if (iy == 0x7f800000) {
        if (ix == 0x3f800000) {
            return y - y;
        } else if (ix > 0x3f800000) {
            return (hy >= 0) ? y : 0.0f;
        } else {
            return (hy < 0) ? -y : 0.0f;
        }
    }
    if (iy == 0x3f800000) {
        if (hy < 0) {
            return 1.0f / x;
        }
        return x;
    }
    if (hy == 0x40000000) {
        return x * x;
    }
    if (hy == 0x3f000000 && hx >= 0) {
        return func_00208068(x);
    }

    ax = func_002052F8(x);
    if (ix == 0x7f800000 || ix == 0 || ix == 0x3f800000) {
        z = ax;
        if (hy < 0) {
            z = 1.0f / z;
        }
        if (hx < 0) {
            if (((ix - 0x3f800000) | yisint) == 0) {
                z = (z - z) / (z - z);
            } else if (yisint == 1) {
                z = -z;
            }
        }
        return z;
    }

    if (((((u32)hx >> 31) - 1) | yisint) == 0) {
        return (x - x) / (x - x);
    }

    if (iy > 0x4d000000) {
        if (ix < 0x3f7ffff8) {
            return (hy < 0) ? 1.0e30f * 1.0e30f : 1.0e-30f * 1.0e-30f;
        }
        if (ix > 0x3f800007) {
            return (hy > 0) ? 1.0e30f * 1.0e30f : 1.0e-30f * 1.0e-30f;
        }
        t = x - 1.0f;
        w = (t * t) * (0.5f - t * (0.333333343f - t * 0.25f));
        u = 1.44268798828125f * t;
        v = t * 7.05260754e-06f - w * 1.44269502f;
        t1 = u + v;
        FLOAT_TO_BITS(is, t1);
        is &= 0xfffff000;
        BITS_TO_FLOAT(t1, is);
        t2 = v - (t1 - u);
    } else {
        f32 s2, s_h, s_l, t_h, t_l;
        n = 0;
        if (ix < 0x800000) {
            ax *= 16777216.0f;
            n -= 24;
            FLOAT_TO_BITS(ix, ax);
        }
        n += (ix >> 23) - 0x7f;
        j = ix & 0x7fffff;
        ix = j | 0x3f800000;
        if (j <= 0x1cc471) {
            k = 0;
        } else if (j < 0x5db3d7) {
            k = 1;
        } else {
            k = 0;
            n += 1;
            ix -= 0x800000;
        }
        BITS_TO_FLOAT(ax, ix);

        u = ax - D_0024FA50[k];
        v = 1.0f / (ax + D_0024FA50[k]);
        s = u * v;
        s_h = s;
        FLOAT_TO_BITS(is, s_h);
        is &= 0xfffff000;
        BITS_TO_FLOAT(s_h, is);
        is = ((ix >> 1) | 0x20000000) + 0x40000 + (k << 21);
        BITS_TO_FLOAT(t_h, is);
        t_l = ax - (t_h - D_0024FA50[k]);
        s_l = v * ((u - s_h * t_h) - s_h * t_l);
        s2 = s * s;
        r = s2 * s2 * (0.600000024f + s2 * (0.428571433f + s2 * (0.333333343f + s2 * (0.272728115f + s2 * (0.230660751f + s2 * 0.206975013f)))));
        r += s_l * (s_h + s);
        s2 = s_h * s_h;
        t_h = 3.0f + s2 + r;
        FLOAT_TO_BITS(is, t_h);
        is &= 0xfffff000;
        BITS_TO_FLOAT(t_h, is);
        t_l = r - ((t_h - 3.0f) - s2);
        u = s_h * t_h;
        v = s_l * t_h + t_l * s;
        p_h = u + v;
        FLOAT_TO_BITS(is, p_h);
        is &= 0xfffff000;
        BITS_TO_FLOAT(p_h, is);
        p_l = v - (p_h - u);
        z_h = 0.961791992f * p_h;
        z_l = 4.70173836e-06f * p_h + p_l * 0.961796701f + D_0024FA60[k];
        t = (f32)n;
        t1 = ((z_h + z_l) + D_0024FA58[k]) + t;
        FLOAT_TO_BITS(is, t1);
        is &= 0xfffff000;
        BITS_TO_FLOAT(t1, is);
        t2 = z_l - (((t1 - t) - D_0024FA58[k]) - z_h);
    }

    s = 1.0f;
    if (((((u32)hx >> 31) - 1) | (yisint - 1)) == 0) {
        s = -1.0f;
    }

    FLOAT_TO_BITS(is, y);
    is &= 0xfffff000;
    BITS_TO_FLOAT(y1, is);
    p_l = (y - y1) * t1 + y * t2;
    p_h = y1 * t1;
    z = p_l + p_h;
    FLOAT_TO_BITS(j, z);
    if (j > 0x43000000) {
        return s * 1.0e30f * 1.0e30f;
    } else if (j == 0x43000000) {
        if (p_l + 4.29956657e-08f > z - p_h) {
            return s * 1.0e30f * 1.0e30f;
        }
    } else if ((j & 0x7fffffff) > 0x43160000) {
        return s * 1.0e-30f * 1.0e-30f;
    } else if ((u32)j == 0xc3160000) {
        if (p_l <= z - p_h) {
            return s * 1.0e-30f * 1.0e-30f;
        }
    }

    i = j & 0x7fffffff;
    k = (i >> 23) - 0x7f;
    n = 0;
    if (i > 0x3f000000) {
        n = j + (0x800000 >> (k + 1));
        k = ((n & 0x7fffffff) >> 23) - 0x7f;
        BITS_TO_FLOAT(t, n & ~(0x7fffff >> k));
        n = ((n & 0x7fffff) | 0x800000) >> (23 - k);
        if (j < 0) {
            n = -n;
        }
        p_h -= t;
    }
    t = p_l + p_h;
    FLOAT_TO_BITS(is, t);
    is &= 0xfffff000;
    BITS_TO_FLOAT(t, is);
    u = t * 0.693145752f;
    v = (p_l - (t - p_h)) * 0.693147182f + t * 1.42860654e-06f;
    z = u + v;
    w = v - (z - u);
    t = z * z;
    t1 = z - t * (0.166666672f + t * (-0.00277777785f + t * (6.61375598e-05f + t * (-1.65339022e-06f + t * 4.13813679e-08f))));
    r = (z * t1) / (t1 - 2.0f) - (w + z * w);
    z = 1.0f - (r - z);
    FLOAT_TO_BITS(j, z);
    j += n << 23;
    if ((j >> 23) <= 0) {
        z = func_00209260(z, n);
    } else {
        BITS_TO_FLOAT(z, j);
    }
    return s * z;
}
