// SPDX-License-Identifier: AGPL-3.0-or-later
// A float's bits as an integer, a double's two words, and back, for the math library
// (src/libm/). Written for this project. Retail's math library did this through macros of
// this do/while(0) form: GCC 2.9-ee takes each one for a loop, which puts the next label on
// an 8-byte boundary and orders the function's entry as retail has it (docs/TOOLCHAIN.md).
// Only src/libm uses them.
#ifndef FLOAT_BITS_H
#define FLOAT_BITS_H

#include "common.h"

union FloatBits {
    f32 f;
    s32 i;
};

#define FLOAT_TO_BITS(bits, value) \
    do {                           \
        FloatBits fb_;             \
        fb_.f = (value);           \
        (bits) = fb_.i;            \
    } while (0)

#define BITS_TO_FLOAT(value, bits) \
    do {                           \
        FloatBits fb_;             \
        fb_.i = (bits);            \
        (value) = fb_.f;           \
    } while (0)

union DoubleWords {
    double d;
    struct {
        s32 lo;
        s32 hi;
    } w;
};

#define DOUBLE_TO_WORDS(high, low, value) \
    do {                                  \
        DoubleWords dw_;                  \
        dw_.d = (value);                  \
        (high) = dw_.w.hi;                \
        (low) = dw_.w.lo;                 \
    } while (0)

#define WORDS_TO_DOUBLE(value, high, low) \
    do {                                  \
        DoubleWords dw_;                  \
        dw_.w.hi = (high);                \
        dw_.w.lo = (low);                 \
        (value) = dw_.d;                  \
    } while (0)

#define DOUBLE_HIGH(high, value) \
    do {                         \
        DoubleWords dw_;         \
        dw_.d = (value);         \
        (high) = dw_.w.hi;       \
    } while (0)

#define SET_DOUBLE_HIGH(value, high) \
    do {                             \
        DoubleWords dw_;             \
        dw_.d = (value);             \
        dw_.w.hi = (high);           \
        (value) = dw_.d;             \
    } while (0)

#endif
