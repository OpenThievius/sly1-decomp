/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* What the math library's files (src/libm/) share: the record a checked function hands to the
 * error hook, the error mode and the double infinity it reads, and the runtime's software double
 * routines it calls. Written for this project from retail's code. */
#ifndef LIBM_H
#define LIBM_H

#include "common.h"

/* The record of a domain or range error, given to func_00208FE8: its kind (1 domain, 2 a
 * singularity, 3 an overflow, 4 an underflow), the function's name, both arguments, the result
 * to return, and an error code to store when it is not zero. */
typedef struct MathError {
    s32 kind;
    const char* function;
    double firstArg;
    double secondArg;
    double result;
    s32 errorCode;
} MathError;

extern const s32 D_0024FF78;    /* the error mode: -1 none, 0, 1, 2 (only the error code) */
extern const double D_0024FF70; /* a double's positive infinity */

s32 func_00208FE8(MathError* e);
s32* func_002014F0(void);
s32 func_00209210(f32 x);
s32 func_00209238(f32 x);
double func_00209010(double x);

double func_001FD868(f32 x);
f32 func_001FD578(double x);
double func_001FCD78(double a, double b);
double func_001FCDE0(double a, double b);
s32 func_001FD308(double a, double b);

#endif
