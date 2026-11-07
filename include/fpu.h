// SPDX-License-Identifier: AGPL-3.0-or-later
// The floating-point instructions the game's C used through inline-assembly helpers: the square
// root (sqrt.s) and the larger and smaller of two floats (max.s, min.s). Written for this
// project. Retail's bare sqrt.s instructions behave as an inline-assembly helper does: the
// compiler never moves code past them and never gives the result its input's register, which
// neither __builtin_sqrtf (a NaN check and a call to sqrtf) nor -ffast-math reproduces
// (docs/TOOLCHAIN.md). max.s and min.s sit in compiled code the same way, in files whose matched
// functions -ffast-math would change, and Max is func_001EAC68's word for word: unlike the square
// root, their result may take an input's register (docs/ASM_CLASSIFICATION.md, "inline").
// AGENTS.md allows these helpers.
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

    static f32 Max(f32 a, f32 b)
    {
        f32 r;
        __asm__ volatile("max.s %0, %1, %2" : "=f"(r) : "f"(a), "f"(b));
        return r;
    }

    static f32 Min(f32 a, f32 b)
    {
        f32 r;
        __asm__ volatile("min.s %0, %1, %2" : "=f"(r) : "f"(a), "f"(b));
        return r;
    }
};

#endif
