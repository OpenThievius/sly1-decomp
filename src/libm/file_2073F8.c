/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The power x ** y of floats (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const f32 bases[] = { 1.0f, 1.5f };
static const f32 log2_base_high[] = { 0.0f, 5.84960938e-01f };
static const f32 log2_base_low[] = { 0.0f, 1.56322085e-06f };
static const f32 zero = 0.0f;
static const f32 one = 1.0f;
static const f32 two = 2.0f;
static const f32 scale24 = 16777216.0f;
static const f32 huge = 1.0e30f;
static const f32 tiny = 1.0e-30f;
static const f32 log_c1 = 6.0000002384e-01f;
static const f32 log_c2 = 4.2857143283e-01f;
static const f32 log_c3 = 3.3333334327e-01f;
static const f32 log_c4 = 2.7272811532e-01f;
static const f32 log_c5 = 2.3066075146e-01f;
static const f32 log_c6 = 2.0697501302e-01f;
static const f32 exp_c1 = 1.6666667163e-01f;
static const f32 exp_c2 = -2.7777778450e-03f;
static const f32 exp_c3 = 6.6137559770e-05f;
static const f32 exp_c4 = -1.6533901999e-06f;
static const f32 exp_c5 = 4.1381369442e-08f;
static const f32 ln2 = 6.9314718246e-01f;
static const f32 ln2_high = 6.93145752e-01f;
static const f32 ln2_low = 1.42860654e-06f;
static const f32 overflow_margin = 4.2995665694e-08f;
static const f32 two_over_3ln2 = 9.6179670095e-01f;
static const f32 two_over_3ln2_high = 9.6179199219e-01f;
static const f32 two_over_3ln2_low = 4.7017383622e-06f;
static const f32 inv_ln2 = 1.4426950216e+00f;
static const f32 inv_ln2_high = 1.4426879883e+00f;
static const f32 inv_ln2_low = 7.0526075433e-06f;

f32 func_002052F8(f32 x);
f32 func_00208068(f32 x);
f32 func_00209260(f32 x, s32 n);

f32 func_002073F8(f32 x, f32 y)
{
    f32 z, ax, z_h, z_l, p_h, p_l;
    f32 y1, t1, t2, r, s, t, u, v, w;
    f32 s2, s_h, s_l, t_h, t_l;
    s32 i, j, k, yisint, n;
    s32 hx, hy, ix, iy, is;

    FLOAT_TO_BITS(hx, x);
    FLOAT_TO_BITS(hy, y);
    ix = hx & 0x7fffffff;
    iy = hy & 0x7fffffff;

    if (iy == 0) {
        return one;
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
            return (hy >= 0) ? y : zero;
        } else {
            return (hy < 0) ? -y : zero;
        }
    }
    if (iy == 0x3f800000) {
        if (hy < 0) {
            return one / x;
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
            z = one / z;
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
            return (hy < 0) ? huge * huge : tiny * tiny;
        }
        if (ix > 0x3f800007) {
            return (hy > 0) ? huge * huge : tiny * tiny;
        }
        t = x - one;
        w = (t * t) * (0.5f - t * (0.333333343f - t * 0.25f));
        u = inv_ln2_high * t;
        v = t * inv_ln2_low - w * inv_ln2;
        t1 = u + v;
        FLOAT_TO_BITS(is, t1);
        is &= 0xfffff000;
        BITS_TO_FLOAT(t1, is);
        t2 = v - (t1 - u);
    } else {
        n = 0;
        if (ix < 0x800000) {
            ax *= scale24;
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

        u = ax - bases[k];
        v = one / (ax + bases[k]);
        s = u * v;
        s_h = s;
        FLOAT_TO_BITS(is, s_h);
        is &= 0xfffff000;
        BITS_TO_FLOAT(s_h, is);
        is = ((ix >> 1) | 0x20000000) + 0x40000 + (k << 21);
        BITS_TO_FLOAT(t_h, is);
        t_l = ax - (t_h - bases[k]);
        s_l = v * ((u - s_h * t_h) - s_h * t_l);
        s2 = s * s;
        r = s2 * s2 * (log_c1 + s2 * (log_c2 + s2 * (log_c3 + s2 * (log_c4 + s2 * (log_c5 + s2 * log_c6)))));
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
        z_h = two_over_3ln2_high * p_h;
        z_l = two_over_3ln2_low * p_h + p_l * two_over_3ln2 + log2_base_low[k];
        t = (f32)n;
        t1 = ((z_h + z_l) + log2_base_high[k]) + t;
        FLOAT_TO_BITS(is, t1);
        is &= 0xfffff000;
        BITS_TO_FLOAT(t1, is);
        t2 = z_l - (((t1 - t) - log2_base_high[k]) - z_h);
    }

    s = one;
    if (((((u32)hx >> 31) - 1) | (yisint - 1)) == 0) {
        s = -one;
    }

    FLOAT_TO_BITS(is, y);
    is &= 0xfffff000;
    BITS_TO_FLOAT(y1, is);
    p_l = (y - y1) * t1 + y * t2;
    p_h = y1 * t1;
    z = p_l + p_h;
    FLOAT_TO_BITS(j, z);
    if (j > 0x43000000) {
        return s * huge * huge;
    } else if (j == 0x43000000) {
        if (p_l + overflow_margin > z - p_h) {
            return s * huge * huge;
        }
    } else if ((j & 0x7fffffff) > 0x43160000) {
        return s * tiny * tiny;
    } else if ((u32)j == 0xc3160000) {
        if (p_l <= z - p_h) {
            return s * tiny * tiny;
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
    u = t * ln2_high;
    v = (p_l - (t - p_h)) * ln2 + t * ln2_low;
    z = u + v;
    w = v - (z - u);
    t = z * z;
    t1 = z - t * (exp_c1 + t * (exp_c2 + t * (exp_c3 + t * (exp_c4 + t * exp_c5))));
    r = (z * t1) / (t1 - two) - (w + z * w);
    z = one - (r - z);
    FLOAT_TO_BITS(j, z);
    j += n << 23;
    if ((j >> 23) <= 0) {
        z = func_00209260(z, n);
    } else {
        BITS_TO_FLOAT(z, j);
    }
    return s * z;
}
