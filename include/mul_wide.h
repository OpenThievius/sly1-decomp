/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* A 32 by 32 bit unsigned multiply giving both halves of the product, as the toolchain's
 * runtime computed it: one multu, its halves read from lo and hi. Written for this project.
 * The runtime's 64-bit divide helpers (__divdi3 and its kind, compiled from C) multiply with an
 * inline-assembly macro of this form; no C product gives the single multu, as GCC splits a
 * 64-bit product or multiplies twice (docs/TOOLCHAIN.md). Beside Fpu::Sqrt (include/fpu.h), the
 * only inline assembly AGENTS.md allows, and only in that runtime's C. */
#ifndef MUL_WIDE_H
#define MUL_WIDE_H

#define MUL_WIDE(high, low, a, b) \
    __asm__("multu %2,%3" : "=l"(low), "=h"(high) : "d"(a), "d"(b))

#endif
