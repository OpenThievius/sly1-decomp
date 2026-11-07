/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The reduction of a large float argument by pi / 2 on a table of the digits of 2 / pi, 8 bits to a float. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const s32 terms_for_precision[] = { 4, 7, 9 };

static const f32 half_pi_parts[] = {
    1.5703125000e+00f, 4.5776367188e-04f, 2.5987625122e-05f, 7.5437128544e-08f,
    6.0026650317e-11f, 7.3896444519e-13f, 5.3845816694e-15f, 5.6378512969e-18f,
    8.3009228831e-20f, 3.2756352257e-22f, 6.3331015649e-25f,
};

static const f32 zero_f = 0.0f;
static const f32 one_f = 1.0f;
static const f32 digit_base = 2.5600000000e+02f;
static const f32 inv_digit_base = 3.9062500000e-03f;

f32 func_00209260(f32 x, s32 n);
f32 func_00205318(f32 x);

s32 func_002082F8(f32* digits, f32* parts, s32 exponent, s32 digit_count, s32 precision, const s32* two_over_pi)
{
    s32 last_term, last_digit, first_index, term_count, carry, quadrant, chunks[20], i, j, k, limit, chunk_exp, round_state;
    f32 value, sum, table_digits[20], products[20], terms[20];

    first_index = (exponent - 3) / 8;
    if (first_index < 0) {
        first_index = 0;
    }
    chunk_exp = exponent - 8 * (first_index + 1);

    term_count = terms_for_precision[precision];

    last_digit = digit_count - 1;
    j = first_index - last_digit;
    limit = last_digit + term_count;
    for (i = 0; i <= limit; i++, j++) {
        table_digits[i] = (j < 0) ? zero_f : (f32)two_over_pi[j];
    }

    for (i = 0; i <= term_count; i++) {
        for (j = 0, sum = zero_f; j <= last_digit; j++) {
            sum += digits[j] * table_digits[last_digit + i - j];
        }
        terms[i] = sum;
    }

    last_term = term_count;
recompute:
    for (i = 0, j = last_term, value = terms[last_term]; j > 0; i++, j--) {
        sum = (f32)(s32)(inv_digit_base * value);
        chunks[i] = (s32)(value - digit_base * sum);
        value = terms[j - 1] + sum;
    }

    value = func_00209260(value, chunk_exp);
    value -= 8.0f * func_00205318(value * 0.125f);
    quadrant = (s32)value;
    value -= (f32)quadrant;
    round_state = 0;
    if (chunk_exp > 0) {
        i = chunks[last_term - 1] >> (8 - chunk_exp);
        quadrant += i;
        chunks[last_term - 1] -= i << (8 - chunk_exp);
        round_state = chunks[last_term - 1] >> (7 - chunk_exp);
    } else if (chunk_exp == 0) {
        round_state = chunks[last_term - 1] >> 8;
    } else if (value >= 0.5f) {
        round_state = 2;
    }

    if (round_state > 0) {
        quadrant += 1;
        carry = 0;
        for (i = 0; i < last_term; i++) {
            j = chunks[i];
            if (carry == 0) {
                if (j != 0) {
                    carry = 1;
                    chunks[i] = 0x100 - j;
                }
            } else {
                chunks[i] = 0xFF - j;
            }
        }
        if (chunk_exp > 0) {
            switch (chunk_exp) {
            case 1:
                chunks[last_term - 1] &= 0x7F;
                break;
            case 2:
                chunks[last_term - 1] &= 0x3F;
                break;
            }
        }
        if (round_state == 2) {
            value = one_f - value;
            if (carry != 0) {
                value -= func_00209260(one_f, chunk_exp);
            }
        }
    }

    if (value == zero_f) {
        j = 0;
        for (i = last_term - 1; i >= term_count; i--) {
            j |= chunks[i];
        }
        if (j == 0) {
            for (k = 1; chunks[term_count - k] == 0; k++) {
            }
            for (i = last_term + 1; i <= last_term + k; i++) {
                table_digits[last_digit + i] = (f32)two_over_pi[first_index + i];
                for (j = 0, sum = zero_f; j <= last_digit; j++) {
                    sum += digits[j] * table_digits[last_digit + i - j];
                }
                terms[i] = sum;
            }
            last_term += k;
            goto recompute;
        }
    }

    if (value == zero_f) {
        last_term -= 1;
        chunk_exp -= 8;
        while (chunks[last_term] == 0) {
            last_term--;
            chunk_exp -= 8;
        }
    } else {
        value = func_00209260(value, -chunk_exp);
        if (value >= digit_base) {
            sum = (f32)(s32)(inv_digit_base * value);
            chunks[last_term] = (s32)(value - digit_base * sum);
            last_term += 1;
            chunk_exp += 8;
            chunks[last_term] = (s32)sum;
        } else {
            chunks[last_term] = (s32)value;
        }
    }

    sum = func_00209260(one_f, chunk_exp);
    for (i = last_term; i >= 0; i--) {
        terms[i] = sum * (f32)chunks[i];
        sum *= inv_digit_base;
    }

    for (i = last_term; i >= 0; i--) {
        for (sum = zero_f, k = 0; k <= term_count && k <= last_term - i; k++) {
            sum += half_pi_parts[k] * terms[i + k];
        }
        products[last_term - i] = sum;
    }

    switch (precision) {
    case 0:
        sum = zero_f;
        for (i = last_term; i >= 0; i--) {
            sum += products[i];
        }
        parts[0] = (round_state == 0) ? sum : -sum;
        break;
    case 1:
    case 2:
        sum = zero_f;
        for (i = last_term; i >= 0; i--) {
            sum += products[i];
        }
        parts[0] = (round_state == 0) ? sum : -sum;
        sum = products[0] - sum;
        for (i = 1; i <= last_term; i++) {
            sum += products[i];
        }
        parts[1] = (round_state == 0) ? sum : -sum;
        break;
    case 3:
        for (i = last_term; i > 0; i--) {
            sum = products[i - 1] + products[i];
            products[i] += products[i - 1] - sum;
            products[i - 1] = sum;
        }
        for (i = last_term; i > 1; i--) {
            sum = products[i - 1] + products[i];
            products[i] += products[i - 1] - sum;
            products[i - 1] = sum;
        }
        for (sum = zero_f, i = last_term; i >= 2; i--) {
            sum += products[i];
        }
        if (round_state == 0) {
            parts[0] = products[0];
            parts[1] = products[1];
            parts[2] = sum;
        } else {
            parts[0] = -products[0];
            parts[1] = -products[1];
            parts[2] = -sum;
        }
        break;
    }
    return quadrant & 7;
}
