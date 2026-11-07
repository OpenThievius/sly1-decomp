/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The power x ** y of floats (the kernel, unchecked). One of the math library's files, each its own object in retail
 * (config/us/files.tsv). C, built by the Linux cc1 of 2.9-ee-991111-01 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "float_bits.h"

static const f32 g_bases[] = { 1.0f, 1.5f };
static const f32 g_log2BaseHead[] = { 0.0f, 5.84960938e-01f };
static const f32 g_log2BaseTail[] = { 0.0f, 1.56322085e-06f };
static const f32 g_zero = 0.0f;
static const f32 g_one = 1.0f;
static const f32 g_two = 2.0f;
static const f32 g_subnormalScale = 16777216.0f;
static const f32 g_tenTo30 = 1.0e30f;
static const f32 g_tenToMinus30 = 1.0e-30f;
static const f32 g_logS4 = 6.0000002384e-01f;
static const f32 g_logS6 = 4.2857143283e-01f;
static const f32 g_logS8 = 3.3333334327e-01f;
static const f32 g_logS10 = 2.7272811532e-01f;
static const f32 g_logS12 = 2.3066075146e-01f;
static const f32 g_logS14 = 2.0697501302e-01f;
static const f32 g_expZ2 = 1.6666667163e-01f;
static const f32 g_expZ4 = -2.7777778450e-03f;
static const f32 g_expZ6 = 6.6137559770e-05f;
static const f32 g_expZ8 = -1.6533901999e-06f;
static const f32 g_expZ10 = 4.1381369442e-08f;
static const f32 g_ln2 = 6.9314718246e-01f;
static const f32 g_ln2Head = 6.93145752e-01f;
static const f32 g_ln2Tail = 1.42860654e-06f;
static const f32 g_overflowMargin = 4.2995665694e-08f;
static const f32 g_twoOver3Ln2 = 9.6179670095e-01f;
static const f32 g_twoOver3Ln2Head = 9.6179199219e-01f;
static const f32 g_twoOver3Ln2Tail = 4.7017383622e-06f;
static const f32 g_invLn2 = 1.4426950216e+00f;
static const f32 g_invLn2Head = 1.4426879883e+00f;
static const f32 g_invLn2Tail = 7.0526075433e-06f;

f32 func_002052F8(f32 x);
f32 func_00208068(f32 x);
f32 func_00209260(f32 x, s32 n);

f32 func_002073F8(f32 x, f32 y)
{
    f32 value, absX, logHead, logTail, prodHead, prodTail;
    f32 yHead, log2Head, log2Tail, poly, factor, tmp, partA, partB, corr;
    f32 factor2, factorHead, factorTail, tmpHead, tmpTail;
    s32 mag, word, slot, yIntKind, n;
    s32 xBits, yBits, xMag, yMag, chopBits;

    FLOAT_TO_BITS(xBits, x);
    FLOAT_TO_BITS(yBits, y);
    xMag = xBits & 0x7fffffff;
    yMag = yBits & 0x7fffffff;

    if (yMag == 0) {
        return g_one;
    }
    if (xMag > 0x7f800000 || yMag > 0x7f800000) {
        return x + y;
    }

    yIntKind = 0;
    if (xBits < 0) {
        if (yMag > 0x4b7fffff) {
            yIntKind = 2;
        } else if (yMag > 0x3f7fffff) {
            slot = (yMag >> 23) - 0x7f;
            word = yMag >> (23 - slot);
            if ((word << (23 - slot)) == yMag) {
                yIntKind = 2 - (word & 1);
            }
        }
    }

    if (yMag == 0x7f800000) {
        if (xMag == 0x3f800000) {
            return y - y;
        } else if (xMag > 0x3f800000) {
            return (yBits >= 0) ? y : g_zero;
        } else {
            return (yBits < 0) ? -y : g_zero;
        }
    }
    if (yMag == 0x3f800000) {
        if (yBits < 0) {
            return g_one / x;
        }
        return x;
    }
    if (yBits == 0x40000000) {
        return x * x;
    }
    if (yBits == 0x3f000000 && xBits >= 0) {
        return SquareRootKernel(x);
    }

    absX = AbsoluteValue(x);
    if (xMag == 0x7f800000 || xMag == 0 || xMag == 0x3f800000) {
        value = absX;
        if (yBits < 0) {
            value = g_one / value;
        }
        if (xBits < 0) {
            if (((xMag - 0x3f800000) | yIntKind) == 0) {
                value = (value - value) / (value - value);
            } else if (yIntKind == 1) {
                value = -value;
            }
        }
        return value;
    }

    if (((((u32)xBits >> 31) - 1) | yIntKind) == 0) {
        return (x - x) / (x - x);
    }

    if (yMag > 0x4d000000) {
        if (xMag < 0x3f7ffff8) {
            return (yBits < 0) ? g_tenTo30 * g_tenTo30 : g_tenToMinus30 * g_tenToMinus30;
        }
        if (xMag > 0x3f800007) {
            return (yBits > 0) ? g_tenTo30 * g_tenTo30 : g_tenToMinus30 * g_tenToMinus30;
        }
        tmp = x - g_one;
        corr = (tmp * tmp) * (0.5f - tmp * (0.333333343f - tmp * 0.25f));
        partA = g_invLn2Head * tmp;
        partB = tmp * g_invLn2Tail - corr * g_invLn2;
        log2Head = partA + partB;
        FLOAT_TO_BITS(chopBits, log2Head);
        chopBits &= 0xfffff000;
        BITS_TO_FLOAT(log2Head, chopBits);
        log2Tail = partB - (log2Head - partA);
    } else {
        n = 0;
        if (xMag < 0x800000) {
            absX *= g_subnormalScale;
            n -= 24;
            FLOAT_TO_BITS(xMag, absX);
        }
        n += (xMag >> 23) - 0x7f;
        word = xMag & 0x7fffff;
        xMag = word | 0x3f800000;
        if (word <= 0x1cc471) {
            slot = 0;
        } else if (word < 0x5db3d7) {
            slot = 1;
        } else {
            slot = 0;
            n += 1;
            xMag -= 0x800000;
        }
        BITS_TO_FLOAT(absX, xMag);

        partA = absX - g_bases[slot];
        partB = g_one / (absX + g_bases[slot]);
        factor = partA * partB;
        factorHead = factor;
        FLOAT_TO_BITS(chopBits, factorHead);
        chopBits &= 0xfffff000;
        BITS_TO_FLOAT(factorHead, chopBits);
        chopBits = ((xMag >> 1) | 0x20000000) + 0x40000 + (slot << 21);
        BITS_TO_FLOAT(tmpHead, chopBits);
        tmpTail = absX - (tmpHead - g_bases[slot]);
        factorTail = partB * ((partA - factorHead * tmpHead) - factorHead * tmpTail);
        factor2 = factor * factor;
        poly = factor2 * factor2 * (g_logS4 + factor2 * (g_logS6 + factor2 * (g_logS8 + factor2 * (g_logS10 + factor2 * (g_logS12 + factor2 * g_logS14)))));
        poly += factorTail * (factorHead + factor);
        factor2 = factorHead * factorHead;
        tmpHead = 3.0f + factor2 + poly;
        FLOAT_TO_BITS(chopBits, tmpHead);
        chopBits &= 0xfffff000;
        BITS_TO_FLOAT(tmpHead, chopBits);
        tmpTail = poly - ((tmpHead - 3.0f) - factor2);
        partA = factorHead * tmpHead;
        partB = factorTail * tmpHead + tmpTail * factor;
        prodHead = partA + partB;
        FLOAT_TO_BITS(chopBits, prodHead);
        chopBits &= 0xfffff000;
        BITS_TO_FLOAT(prodHead, chopBits);
        prodTail = partB - (prodHead - partA);
        logHead = g_twoOver3Ln2Head * prodHead;
        logTail = g_twoOver3Ln2Tail * prodHead + prodTail * g_twoOver3Ln2 + g_log2BaseTail[slot];
        tmp = (f32)n;
        log2Head = ((logHead + logTail) + g_log2BaseHead[slot]) + tmp;
        FLOAT_TO_BITS(chopBits, log2Head);
        chopBits &= 0xfffff000;
        BITS_TO_FLOAT(log2Head, chopBits);
        log2Tail = logTail - (((log2Head - tmp) - g_log2BaseHead[slot]) - logHead);
    }

    factor = g_one;
    if (((((u32)xBits >> 31) - 1) | (yIntKind - 1)) == 0) {
        factor = -g_one;
    }

    FLOAT_TO_BITS(chopBits, y);
    chopBits &= 0xfffff000;
    BITS_TO_FLOAT(yHead, chopBits);
    prodTail = (y - yHead) * log2Head + y * log2Tail;
    prodHead = yHead * log2Head;
    value = prodTail + prodHead;
    FLOAT_TO_BITS(word, value);
    if (word > 0x43000000) {
        return factor * g_tenTo30 * g_tenTo30;
    } else if (word == 0x43000000) {
        if (prodTail + g_overflowMargin > value - prodHead) {
            return factor * g_tenTo30 * g_tenTo30;
        }
    } else if ((word & 0x7fffffff) > 0x43160000) {
        return factor * g_tenToMinus30 * g_tenToMinus30;
    } else if ((u32)word == 0xc3160000) {
        if (prodTail <= value - prodHead) {
            return factor * g_tenToMinus30 * g_tenToMinus30;
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
        prodHead -= tmp;
    }
    tmp = prodTail + prodHead;
    FLOAT_TO_BITS(chopBits, tmp);
    chopBits &= 0xfffff000;
    BITS_TO_FLOAT(tmp, chopBits);
    partA = tmp * g_ln2Head;
    partB = (prodTail - (tmp - prodHead)) * g_ln2 + tmp * g_ln2Tail;
    value = partA + partB;
    corr = partB - (value - partA);
    tmp = value * value;
    log2Head = value - tmp * (g_expZ2 + tmp * (g_expZ4 + tmp * (g_expZ6 + tmp * (g_expZ8 + tmp * g_expZ10))));
    poly = (value * log2Head) / (log2Head - g_two) - (corr + value * corr);
    value = g_one - (poly - value);
    FLOAT_TO_BITS(word, value);
    word += n << 23;
    if ((word >> 23) <= 0) {
        value = ScaleByPowerOfTwo(value, n);
    } else {
        BITS_TO_FLOAT(value, word);
    }
    return factor * value;
}
