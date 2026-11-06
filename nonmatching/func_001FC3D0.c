// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1342/1344 (99.9%), checked 2026-11-06
#include "mul_wide.h"
/* NEAR (o98c, 2 lines differ): every instruction matches but the frame: retail reserves 48 bytes
 * (addiu sp,-0x30 / 0x30) and uses only the remainder's slot at 0(sp); this C reserves 16. The same
 * helper gives __udivdi3 (func_001FBE00.c here) 10 lines from exact, again only retail's empty 16-byte
 * frame and its knock-on delay slot and pad, and __divdi3 (func_001FAE38) EXACT (div3.c here).
 * Retail's remainder slot sits below the extra space, so the extra space was allocated after w's
 * ADDRESSOF was purged (an inlined frame block would come first: tried, it puts w at 16). It looks
 * like reload stack slots for pseudos that later vanish, not anything from the source. Not from -g*,
 * -f flags (regmove, gcse, force-mem, schedule, exceptions, PIC), union order or const or brace
 * init, (void), a union remainder, K&R parameters or callers, non-static or pre-declared inline. */

/* Unsigned 64-bit remainder, done in 32-bit halves. */

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef int s32;
typedef long long s64;

typedef union {
    s64 all;
    struct {
        u32 lo;
        s32 hi;
    } h;
} Halves;

/* (high:low) -= (sub_high:sub_low), the borrow carried by hand. */
#define SUBTRACT_WIDE(high, low, sub_high, sub_low)                         \
    do {                                                                    \
        u32 t_;                                                             \
        t_ = (low) - (sub_low);                                             \
        (high) = (high) - (sub_high) - (t_ > (low));                        \
        (low) = t_;                                                         \
    } while (0)

/* Significant bits of each byte value. */
extern const u8 D_0024EFB0[];

#define LEAD_ZEROS(count, x)                                    \
    do {                                                        \
        u32 shift_;                                             \
        if (sizeof(u32) * 8 <= 32) {                            \
            if ((x) < 0x10000)                                  \
                shift_ = (x) < 0x100 ? 0 : 8;                   \
            else                                                \
                shift_ = (x) < 0x1000000 ? 16 : 24;             \
        } else {                                                \
            for (shift_ = sizeof(u32) * 8 - 8; shift_ > 0;      \
                 shift_ -= 8)                                   \
                if (((x) >> shift_) & 0xFF)                     \
                    break;                                      \
        }                                                       \
        (count) = 32 - (D_0024EFB0[(x) >> shift_] + shift_);    \
    } while (0)

/* (high:low) / den in two 16-bit steps; den is normalised. */
#define DIV_STEP(quot, rem, high, low, den)                     \
    do {                                                        \
        u32 dh_, dl_, q1_, q0_, r1_, r0_, m_;                   \
        dh_ = (den) >> 16;                                      \
        dl_ = (den) & 0xFFFF;                                   \
        q1_ = (high) / dh_;                                     \
        r1_ = (high) % dh_;                                     \
        m_ = q1_ * dl_;                                         \
        r1_ = r1_ * 0x10000L | (low) >> 16;                      \
        if (r1_ < m_) {                                         \
            q1_--, r1_ += (den);                                \
            if (r1_ >= (den))                                   \
                if (r1_ < m_)                                   \
                    q1_--, r1_ += (den);                        \
        }                                                       \
        r1_ -= m_;                                              \
        q0_ = r1_ / dh_;                                        \
        r0_ = r1_ % dh_;                                        \
        m_ = q0_ * dl_;                                         \
        r0_ = r0_ * 0x10000L | ((low) & 0xFFFF);                 \
        if (r0_ < m_) {                                         \
            q0_--, r0_ += (den);                                \
            if (r0_ >= (den))                                   \
                if (r0_ < m_)                                   \
                    q0_--, r0_ += (den);                        \
        }                                                       \
        r0_ -= m_;                                              \
        (quot) = q1_ * 0x10000L | q0_;                           \
        (rem) = r0_;                                            \
    } while (0)

static inline u64 divide(u64 num, u64 den, u64 *remp)
{
    Halves nn, dd, rr, ww;
    u32 d0, d1, n0, n1, n2;
    u32 q0, q1;
    u32 bm, b;

    nn.all = num;
    dd.all = den;
    d0 = dd.h.lo;
    d1 = dd.h.hi;
    n0 = nn.h.lo;
    n1 = nn.h.hi;

    if (d1 == 0) {
        if (d0 > n1) {
            LEAD_ZEROS(bm, d0);
            if (bm != 0) {
                d0 = d0 << bm;
                n1 = (n1 << bm) | (n0 >> (32 - bm));
                n0 = n0 << bm;
            }
            DIV_STEP(q0, n0, n1, n0, d0);
            q1 = 0;
        } else {
            if (d0 == 0)
                d0 = 1 / d0;
            LEAD_ZEROS(bm, d0);
            if (bm == 0) {
                n1 -= d0;
                q1 = 1;
            } else {
                b = 32 - bm;
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;
                DIV_STEP(q1, n1, n2, n1, d0);
            }
            DIV_STEP(q0, n0, n1, n0, d0);
        }
        if (remp != 0) {
            rr.h.lo = n0 >> bm;
            rr.h.hi = 0;
            *remp = rr.all;
        }
    } else {
        if (d1 > n1) {
            q0 = 0;
            q1 = 0;
            if (remp != 0) {
                rr.h.lo = n0;
                rr.h.hi = n1;
                *remp = rr.all;
            }
        } else {
            LEAD_ZEROS(bm, d1);
            if (bm == 0) {
                if (n1 > d1 || n0 >= d0) {
                    q0 = 1;
                    SUBTRACT_WIDE(n1, n0, d1, d0);
                } else {
                    q0 = 0;
                }
                q1 = 0;
                if (remp != 0) {
                    rr.h.lo = n0;
                    rr.h.hi = n1;
                    *remp = rr.all;
                }
            } else {
                u32 m1, m0, t;

                b = 32 - bm;
                d1 = (d1 << bm) | (d0 >> b);
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;
                DIV_STEP(q0, n1, n2, n1, d1);
                MUL_WIDE(m1, m0, q0, d0);
                if (m1 > n1 || (m1 == n1 && m0 > n0)) {
                    q0--;
                    SUBTRACT_WIDE(m1, m0, d1, d0);
                }
                q1 = 0;
                if (remp != 0) {
                    SUBTRACT_WIDE(n1, n0, m1, m0);
                    rr.h.lo = (n1 << b) | (n0 >> bm);
                    rr.h.hi = n1 >> bm;
                    *remp = rr.all;
                }
            }
        }
    }

    ww.h.lo = q0;
    ww.h.hi = q1;
    return ww.all;
}

u64 func_001FC3D0(u64 num, u64 den)
{
    u64 rem;

    divide(num, den, &rem);
    return rem;
}
