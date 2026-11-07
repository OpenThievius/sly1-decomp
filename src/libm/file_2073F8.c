/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The power x ** y of floats (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const f32 bases[] = { 1.0f, 1.5f };
static const f32 log2_base_head[] = { 0.0f, 5.84960938e-01f };
static const f32 log2_base_tail[] = { 0.0f, 1.56322085e-06f };
static const f32 zero_f = 0.0f;
static const f32 one_f = 1.0f;
static const f32 two_f = 2.0f;
static const f32 subnormal_scale = 16777216.0f;
static const f32 ten_to_30 = 1.0e30f;
static const f32 ten_to_minus_30 = 1.0e-30f;
static const f32 log_s4 = 6.0000002384e-01f;
static const f32 log_s6 = 4.2857143283e-01f;
static const f32 log_s8 = 3.3333334327e-01f;
static const f32 log_s10 = 2.7272811532e-01f;
static const f32 log_s12 = 2.3066075146e-01f;
static const f32 log_s14 = 2.0697501302e-01f;
static const f32 exp_z2 = 1.6666667163e-01f;
static const f32 exp_z4 = -2.7777778450e-03f;
static const f32 exp_z6 = 6.6137559770e-05f;
static const f32 exp_z8 = -1.6533901999e-06f;
static const f32 exp_z10 = 4.1381369442e-08f;
static const f32 ln2 = 6.9314718246e-01f;
static const f32 ln2_head = 6.93145752e-01f;
static const f32 ln2_tail = 1.42860654e-06f;
static const f32 overflow_margin = 4.2995665694e-08f;
static const f32 two_over_3ln2 = 9.6179670095e-01f;
static const f32 two_over_3ln2_head = 9.6179199219e-01f;
static const f32 two_over_3ln2_tail = 4.7017383622e-06f;
static const f32 inv_ln2 = 1.4426950216e+00f;
static const f32 inv_ln2_head = 1.4426879883e+00f;
static const f32 inv_ln2_tail = 7.0526075433e-06f;

f32 func_002052F8(f32 x);
f32 func_00208068(f32 x);
f32 func_00209260(f32 x, s32 n);

f32 func_002073F8(f32 x, f32 y)
{
    f32 value, abs_x, log_head, log_tail, prod_head, prod_tail;
    f32 y_head, log2_head, log2_tail, poly, factor, tmp, part_a, part_b, corr;
    f32 factor2, factor_head, factor_tail, tmp_head, tmp_tail;
    s32 mag, word, slot, y_int_kind, n;
    s32 x_bits, y_bits, x_mag, y_mag, chop_bits;

    FLOAT_TO_BITS(x_bits, x);
    FLOAT_TO_BITS(y_bits, y);
    x_mag = x_bits & 0x7fffffff;
    y_mag = y_bits & 0x7fffffff;

    if (y_mag == 0) {
        return one_f;
    }
    if (x_mag > 0x7f800000 || y_mag > 0x7f800000) {
        return x + y;
    }

    y_int_kind = 0;
    if (x_bits < 0) {
        if (y_mag > 0x4b7fffff) {
            y_int_kind = 2;
        } else if (y_mag > 0x3f7fffff) {
            slot = (y_mag >> 23) - 0x7f;
            word = y_mag >> (23 - slot);
            if ((word << (23 - slot)) == y_mag) {
                y_int_kind = 2 - (word & 1);
            }
        }
    }

    if (y_mag == 0x7f800000) {
        if (x_mag == 0x3f800000) {
            return y - y;
        } else if (x_mag > 0x3f800000) {
            return (y_bits >= 0) ? y : zero_f;
        } else {
            return (y_bits < 0) ? -y : zero_f;
        }
    }
    if (y_mag == 0x3f800000) {
        if (y_bits < 0) {
            return one_f / x;
        }
        return x;
    }
    if (y_bits == 0x40000000) {
        return x * x;
    }
    if (y_bits == 0x3f000000 && x_bits >= 0) {
        return func_00208068(x);
    }

    abs_x = func_002052F8(x);
    if (x_mag == 0x7f800000 || x_mag == 0 || x_mag == 0x3f800000) {
        value = abs_x;
        if (y_bits < 0) {
            value = one_f / value;
        }
        if (x_bits < 0) {
            if (((x_mag - 0x3f800000) | y_int_kind) == 0) {
                value = (value - value) / (value - value);
            } else if (y_int_kind == 1) {
                value = -value;
            }
        }
        return value;
    }

    if (((((u32)x_bits >> 31) - 1) | y_int_kind) == 0) {
        return (x - x) / (x - x);
    }

    if (y_mag > 0x4d000000) {
        if (x_mag < 0x3f7ffff8) {
            return (y_bits < 0) ? ten_to_30 * ten_to_30 : ten_to_minus_30 * ten_to_minus_30;
        }
        if (x_mag > 0x3f800007) {
            return (y_bits > 0) ? ten_to_30 * ten_to_30 : ten_to_minus_30 * ten_to_minus_30;
        }
        tmp = x - one_f;
        corr = (tmp * tmp) * (0.5f - tmp * (0.333333343f - tmp * 0.25f));
        part_a = inv_ln2_head * tmp;
        part_b = tmp * inv_ln2_tail - corr * inv_ln2;
        log2_head = part_a + part_b;
        FLOAT_TO_BITS(chop_bits, log2_head);
        chop_bits &= 0xfffff000;
        BITS_TO_FLOAT(log2_head, chop_bits);
        log2_tail = part_b - (log2_head - part_a);
    } else {
        n = 0;
        if (x_mag < 0x800000) {
            abs_x *= subnormal_scale;
            n -= 24;
            FLOAT_TO_BITS(x_mag, abs_x);
        }
        n += (x_mag >> 23) - 0x7f;
        word = x_mag & 0x7fffff;
        x_mag = word | 0x3f800000;
        if (word <= 0x1cc471) {
            slot = 0;
        } else if (word < 0x5db3d7) {
            slot = 1;
        } else {
            slot = 0;
            n += 1;
            x_mag -= 0x800000;
        }
        BITS_TO_FLOAT(abs_x, x_mag);

        part_a = abs_x - bases[slot];
        part_b = one_f / (abs_x + bases[slot]);
        factor = part_a * part_b;
        factor_head = factor;
        FLOAT_TO_BITS(chop_bits, factor_head);
        chop_bits &= 0xfffff000;
        BITS_TO_FLOAT(factor_head, chop_bits);
        chop_bits = ((x_mag >> 1) | 0x20000000) + 0x40000 + (slot << 21);
        BITS_TO_FLOAT(tmp_head, chop_bits);
        tmp_tail = abs_x - (tmp_head - bases[slot]);
        factor_tail = part_b * ((part_a - factor_head * tmp_head) - factor_head * tmp_tail);
        factor2 = factor * factor;
        poly = factor2 * factor2 * (log_s4 + factor2 * (log_s6 + factor2 * (log_s8 + factor2 * (log_s10 + factor2 * (log_s12 + factor2 * log_s14)))));
        poly += factor_tail * (factor_head + factor);
        factor2 = factor_head * factor_head;
        tmp_head = 3.0f + factor2 + poly;
        FLOAT_TO_BITS(chop_bits, tmp_head);
        chop_bits &= 0xfffff000;
        BITS_TO_FLOAT(tmp_head, chop_bits);
        tmp_tail = poly - ((tmp_head - 3.0f) - factor2);
        part_a = factor_head * tmp_head;
        part_b = factor_tail * tmp_head + tmp_tail * factor;
        prod_head = part_a + part_b;
        FLOAT_TO_BITS(chop_bits, prod_head);
        chop_bits &= 0xfffff000;
        BITS_TO_FLOAT(prod_head, chop_bits);
        prod_tail = part_b - (prod_head - part_a);
        log_head = two_over_3ln2_head * prod_head;
        log_tail = two_over_3ln2_tail * prod_head + prod_tail * two_over_3ln2 + log2_base_tail[slot];
        tmp = (f32)n;
        log2_head = ((log_head + log_tail) + log2_base_head[slot]) + tmp;
        FLOAT_TO_BITS(chop_bits, log2_head);
        chop_bits &= 0xfffff000;
        BITS_TO_FLOAT(log2_head, chop_bits);
        log2_tail = log_tail - (((log2_head - tmp) - log2_base_head[slot]) - log_head);
    }

    factor = one_f;
    if (((((u32)x_bits >> 31) - 1) | (y_int_kind - 1)) == 0) {
        factor = -one_f;
    }

    FLOAT_TO_BITS(chop_bits, y);
    chop_bits &= 0xfffff000;
    BITS_TO_FLOAT(y_head, chop_bits);
    prod_tail = (y - y_head) * log2_head + y * log2_tail;
    prod_head = y_head * log2_head;
    value = prod_tail + prod_head;
    FLOAT_TO_BITS(word, value);
    if (word > 0x43000000) {
        return factor * ten_to_30 * ten_to_30;
    } else if (word == 0x43000000) {
        if (prod_tail + overflow_margin > value - prod_head) {
            return factor * ten_to_30 * ten_to_30;
        }
    } else if ((word & 0x7fffffff) > 0x43160000) {
        return factor * ten_to_minus_30 * ten_to_minus_30;
    } else if ((u32)word == 0xc3160000) {
        if (prod_tail <= value - prod_head) {
            return factor * ten_to_minus_30 * ten_to_minus_30;
        }
    }

    mag = word & 0x7fffffff;
    slot = (mag >> 23) - 0x7f;
    n = 0;
    if (mag > 0x3f000000) {
        n = word + (0x800000 >> (slot + 1));
        slot = ((n & 0x7fffffff) >> 23) - 0x7f;
        BITS_TO_FLOAT(tmp, n & ~(0x7fffff >> slot));
        n = ((n & 0x7fffff) | 0x800000) >> (23 - slot);
        if (word < 0) {
            n = -n;
        }
        prod_head -= tmp;
    }
    tmp = prod_tail + prod_head;
    FLOAT_TO_BITS(chop_bits, tmp);
    chop_bits &= 0xfffff000;
    BITS_TO_FLOAT(tmp, chop_bits);
    part_a = tmp * ln2_head;
    part_b = (prod_tail - (tmp - prod_head)) * ln2 + tmp * ln2_tail;
    value = part_a + part_b;
    corr = part_b - (value - part_a);
    tmp = value * value;
    log2_head = value - tmp * (exp_z2 + tmp * (exp_z4 + tmp * (exp_z6 + tmp * (exp_z8 + tmp * exp_z10))));
    poly = (value * log2_head) / (log2_head - two_f) - (corr + value * corr);
    value = one_f - (poly - value);
    FLOAT_TO_BITS(word, value);
    word += n << 23;
    if ((word >> 23) <= 0) {
        value = func_00209260(value, n);
    } else {
        BITS_TO_FLOAT(value, word);
    }
    return factor * value;
}
