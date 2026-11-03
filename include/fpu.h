// SPDX-License-Identifier: AGPL-3.0-or-later
// The square root as the game computed it: one sqrt.s, written in place. Written for this
// project. Retail's bare sqrt.s instructions behave as an inline-assembly helper does: the
// compiler never moves code past them and never gives the result its input's register, which
// neither __builtin_sqrtf (a NaN check and a call to sqrtf) nor -ffast-math reproduces
// (docs/TOOLCHAIN.md). AGENTS.md allows inline assembly here and nowhere else.
#ifndef FPU_H
#define FPU_H

#include "common.h"

struct Fpu {
    static f32 Sqrt(f32 x)
    {
        f32 r;
        __asm__ volatile("sqrt.s %0, %1" : "=&f"(r) : "f"(x));
        return r;
    }
};

#endif
