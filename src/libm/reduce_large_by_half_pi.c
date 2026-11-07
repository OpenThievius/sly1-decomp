/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The reduction of a large float argument by pi / 2 on a table of the digits of 2 / pi, 8 bits to a float. One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const s32 g_termsForPrecision[] = { 4, 7, 9 };

static const f32 g_halfPiParts[] = {
    1.5703125000e+00f, 4.5776367188e-04f, 2.5987625122e-05f, 7.5437128544e-08f,
    6.0026650317e-11f, 7.3896444519e-13f, 5.3845816694e-15f, 5.6378512969e-18f,
    8.3009228831e-20f, 3.2756352257e-22f, 6.3331015649e-25f,
};

static const f32 g_zero = 0.0f;
static const f32 g_one = 1.0f;
static const f32 g_digitBase = 2.5600000000e+02f;
static const f32 g_invDigitBase = 3.9062500000e-03f;

f32 ScaleByPowerOfTwo(f32 x, s32 n);
f32 RoundDown(f32 x);

s32 ReduceLargeByHalfPi(f32* digits, f32* parts, s32 exponent, s32 digitCount, s32 precision, const s32* twoOverPi)
{
    s32 lastTerm, lastDigit, firstIndex, termCount, carry, quadrant, chunks[20], i, j, k, limit, chunkExp, roundState;
    f32 value, sum, tableDigits[20], products[20], terms[20];

    firstIndex = (exponent - 3) / 8;
    if (firstIndex < 0) {
        firstIndex = 0;
    }
    chunkExp = exponent - 8 * (firstIndex + 1);

    termCount = g_termsForPrecision[precision];

    lastDigit = digitCount - 1;
    j = firstIndex - lastDigit;
    limit = lastDigit + termCount;
    for (i = 0; i <= limit; i++, j++) {
        tableDigits[i] = (j < 0) ? g_zero : (f32)twoOverPi[j];
    }

    for (i = 0; i <= termCount; i++) {
        for (j = 0, sum = g_zero; j <= lastDigit; j++) {
            sum += digits[j] * tableDigits[lastDigit + i - j];
        }
        terms[i] = sum;
    }

    lastTerm = termCount;
recompute:
    for (i = 0, j = lastTerm, value = terms[lastTerm]; j > 0; i++, j--) {
        sum = (f32)(s32)(g_invDigitBase * value);
        chunks[i] = (s32)(value - g_digitBase * sum);
        value = terms[j - 1] + sum;
    }

    value = ScaleByPowerOfTwo(value, chunkExp);
    value -= 8.0f * RoundDown(value * 0.125f);
    quadrant = (s32)value;
    value -= (f32)quadrant;
    roundState = 0;
    if (chunkExp > 0) {
        i = chunks[lastTerm - 1] >> (8 - chunkExp);
        quadrant += i;
        chunks[lastTerm - 1] -= i << (8 - chunkExp);
        roundState = chunks[lastTerm - 1] >> (7 - chunkExp);
    } else if (chunkExp == 0) {
        roundState = chunks[lastTerm - 1] >> 8;
    } else if (value >= 0.5f) {
        roundState = 2;
    }

    if (roundState > 0) {
        quadrant += 1;
        carry = 0;
        for (i = 0; i < lastTerm; i++) {
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
        if (chunkExp > 0) {
            switch (chunkExp) {
            case 1:
                chunks[lastTerm - 1] &= 0x7F;
                break;
            case 2:
                chunks[lastTerm - 1] &= 0x3F;
                break;
            }
        }
        if (roundState == 2) {
            value = g_one - value;
            if (carry != 0) {
                value -= ScaleByPowerOfTwo(g_one, chunkExp);
            }
        }
    }

    if (value == g_zero) {
        j = 0;
        for (i = lastTerm - 1; i >= termCount; i--) {
            j |= chunks[i];
        }
        if (j == 0) {
            for (k = 1; chunks[termCount - k] == 0; k++) {
            }
            for (i = lastTerm + 1; i <= lastTerm + k; i++) {
                tableDigits[lastDigit + i] = (f32)twoOverPi[firstIndex + i];
                for (j = 0, sum = g_zero; j <= lastDigit; j++) {
                    sum += digits[j] * tableDigits[lastDigit + i - j];
                }
                terms[i] = sum;
            }
            lastTerm += k;
            goto recompute;
        }
    }

    if (value == g_zero) {
        lastTerm -= 1;
        chunkExp -= 8;
        while (chunks[lastTerm] == 0) {
            lastTerm--;
            chunkExp -= 8;
        }
    } else {
        value = ScaleByPowerOfTwo(value, -chunkExp);
        if (value >= g_digitBase) {
            sum = (f32)(s32)(g_invDigitBase * value);
            chunks[lastTerm] = (s32)(value - g_digitBase * sum);
            lastTerm += 1;
            chunkExp += 8;
            chunks[lastTerm] = (s32)sum;
        } else {
            chunks[lastTerm] = (s32)value;
        }
    }

    sum = ScaleByPowerOfTwo(g_one, chunkExp);
    for (i = lastTerm; i >= 0; i--) {
        terms[i] = sum * (f32)chunks[i];
        sum *= g_invDigitBase;
    }

    for (i = lastTerm; i >= 0; i--) {
        for (sum = g_zero, k = 0; k <= termCount && k <= lastTerm - i; k++) {
            sum += g_halfPiParts[k] * terms[i + k];
        }
        products[lastTerm - i] = sum;
    }

    switch (precision) {
    case 0:
        sum = g_zero;
        for (i = lastTerm; i >= 0; i--) {
            sum += products[i];
        }
        parts[0] = (roundState == 0) ? sum : -sum;
        break;
    case 1:
    case 2:
        sum = g_zero;
        for (i = lastTerm; i >= 0; i--) {
            sum += products[i];
        }
        parts[0] = (roundState == 0) ? sum : -sum;
        sum = products[0] - sum;
        for (i = 1; i <= lastTerm; i++) {
            sum += products[i];
        }
        parts[1] = (roundState == 0) ? sum : -sum;
        break;
    case 3:
        for (i = lastTerm; i > 0; i--) {
            sum = products[i - 1] + products[i];
            products[i] += products[i - 1] - sum;
            products[i - 1] = sum;
        }
        for (i = lastTerm; i > 1; i--) {
            sum = products[i - 1] + products[i];
            products[i] += products[i - 1] - sum;
            products[i - 1] = sum;
        }
        for (sum = g_zero, i = lastTerm; i >= 2; i--) {
            sum += products[i];
        }
        if (roundState == 0) {
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
