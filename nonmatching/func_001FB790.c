// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1625/1640 (99.1%), checked 2026-11-06
#include "mul_wide.h"
/* NEAR (o98b, 7 lines differ, same size): everything lines up except (1) the frame: retail
 * reserves 64 bytes (the remainder at 0(sp), 32 unused bytes, s0 at 48(sp)); this C gives 32
 * (remainder, s0 at 16). __umoddi3 (48) and __udivdi3 (16) show the same unused slots, __divdi3
 * none; no change to the caller (void cast, union or u64 remainder, plain s64 negation), to the
 * helper's unions (brace initialisers) or to the 64/128-bit types moved it. (2) in path 3 the
 * n0 < m0 compare (sltu) is not taken into the delay slot of the m1 == n1 branch: ours is
 * bne/nop/sltu/beqz, retail bne/sltu/beqz/nop (the label pad nop absorbs the difference).
 * Built on o98a's exact __divdi3 helper, with a remainder store in each of its four paths. */
/* Signed 64-bit remainder, done in 32-bit halves. */

typedef unsigned int u32;
typedef int s32;
typedef long long s64;
typedef unsigned long long u64;
typedef unsigned char u8;

typedef union {
    s64 all;
    struct {
        u32 lo;
        s32 hi;
    } h;
} Halves;

/* Number of significant bits of each byte value. */
extern const u8 D_0024EDB0[];

/* Leading zero bits of a 32-bit value. */
#define LEADING_ZEROS(count, x)                                             \
    do {                                                                    \
        u32 v_ = (x);                                                       \
        u32 s_;                                                             \
        if (sizeof(u32) * 8 <= 32) {                                        \
            if (v_ < 0x10000)                                               \
                s_ = v_ < 0x100 ? 0 : 8;                                    \
            else                                                            \
                s_ = v_ < 0x1000000 ? 16 : 24;                              \
        } else {                                                            \
            for (s_ = sizeof(u32) * 8 - 8; s_ > 0; s_ -= 8)                 \
                if (((v_ >> s_) & 0xFF) != 0)                               \
                    break;                                                  \
        }                                                                   \
        (count) = 32 - (D_0024EDB0[v_ >> s_] + s_);                         \
    } while (0)

/* (high:low) / den in two 16-bit steps: quotient and remainder. */
#define DIVIDE_STEP(quot, rem, high, low, den)                              \
    do {                                                                    \
        u32 dh_, dl_, q1_, q0_, r1_, r0_, m_;                               \
        dh_ = (den) >> 16;                                                  \
        dl_ = (den) & 0xFFFF;                                               \
        q1_ = (high) / dh_;                                                 \
        r1_ = (high) % dh_;                                           \
        m_ = q1_ * dl_;                                                     \
        r1_ = r1_ * 0x10000L | (low) >> 16;                                  \
        if (r1_ < m_) {                                                     \
            q1_--, r1_ += (den);                                            \
            if (r1_ >= (den))                                               \
                if (r1_ < m_)                                               \
                    q1_--, r1_ += (den);                                    \
        }                                                                   \
        r1_ -= m_;                                                          \
        q0_ = r1_ / dh_;                                                    \
        r0_ = r1_ % dh_;                                              \
        m_ = q0_ * dl_;                                                     \
        r0_ = r0_ * 0x10000L | ((low) & 0xFFFF);                             \
        if (r0_ < m_) {                                                     \
            q0_--, r0_ += (den);                                            \
            if (r0_ >= (den))                                               \
                if (r0_ < m_)                                               \
                    q0_--, r0_ += (den);                                    \
        }                                                                   \
        r0_ -= m_;                                                          \
        (quot) = q1_ * 0x10000L | q0_;                                       \
        (rem) = r0_;                                                        \
    } while (0)

/* (high:low) -= (sub_high:sub_low), the borrow carried by hand. */
#define SUBTRACT_WIDE(high, low, sub_high, sub_low)                         \
    do {                                                                    \
        u32 t_;                                                             \
        t_ = (low) - (sub_low);                                             \
        (high) = (high) - (sub_high) - (t_ > (low));                        \
        (low) = t_;                                                         \
    } while (0)

static inline s64 negate(s64 x)
{
    Halves in, out;

    in.all = x;
    out.h.lo = -in.h.lo;
    out.h.hi = -in.h.hi - ((u32)out.h.lo > 0);
    return out.all;
}

static inline u64 divide(u64 num, u64 den, u64* remp)
{
    Halves nn, dd, ww, rr;
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
            LEADING_ZEROS(bm, d0);
            if (bm != 0) {
                d0 = d0 << bm;
                n1 = (n1 << bm) | (n0 >> (32 - bm));
                n0 = n0 << bm;
            }
            DIVIDE_STEP(q0, n0, n1, n0, d0);
            q1 = 0;
        } else {
            if (d0 == 0)
                d0 = 1 / d0;
            LEADING_ZEROS(bm, d0);
            if (bm == 0) {
                n1 -= d0;
                q1 = 1;
            } else {
                b = 32 - bm;
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;
                DIVIDE_STEP(q1, n1, n2, n1, d0);
            }
            DIVIDE_STEP(q0, n0, n1, n0, d0);
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
            LEADING_ZEROS(bm, d1);
            if (bm == 0) {
                if (n1 > d1 || n0 >= d0) {
                    q0 = 1;
                    SUBTRACT_WIDE(n1, n0, d1, d0);
                } else
                    q0 = 0;
                q1 = 0;
                if (remp != 0) {
                    rr.h.lo = n0;
                    rr.h.hi = n1;
                    *remp = rr.all;
                }
            } else {
                u32 m1, m0;
                b = 32 - bm;
                d1 = (d1 << bm) | (d0 >> b);
                d0 = d0 << bm;
                n2 = n1 >> b;
                n1 = (n1 << bm) | (n0 >> b);
                n0 = n0 << bm;
                DIVIDE_STEP(q0, n1, n2, n1, d1);
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

s64 func_001FB790(s64 num, s64 den)
{
    int neg = 0;
    Halves nn, dd;
    s64 rem;

    nn.all = num;
    dd.all = den;
    if (nn.h.hi < 0) {
        neg = ~neg;
        nn.all = negate(nn.all);
    }
    if (dd.h.hi < 0)
        dd.all = negate(dd.all);
    divide(nn.all, dd.all, (u64*)&rem);
    if (neg)
        rem = negate(rem);
    return rem;
}
