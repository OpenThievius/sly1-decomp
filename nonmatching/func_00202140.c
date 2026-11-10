// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 604/624 (96.8%), checked 2026-11-10
/* NEAR (src/lib/graph.c, where it is INCLUDE_ASM; built as C by 2.9-ee-991111): six
 * instructions off, two pairs in the interlaced arms. Found 2026-11-10 (docs/TOOLCHAIN.md,
 * "Sony's compiler balances a chain of | and +"): the libraries' compiler re-associates a chain
 * of ORs into a balanced tree as fold builds it, and fold distributes the ORs over the field's
 * ternary (each term but dh saved before the test, the ORs copied into both arms, which
 * cross-jumping merges across the two modes). Of the 120 orders of the macro's terms only
 * magh, dh, dx, dy, dw gives retail's tree ((magh | dw) | (dx | dh)) | dy, in both the
 * interlaced and the plain arms. magh is declared in each arm: one variable assigned in four
 * arms is a global pseudo that the quotient cannot tie to (`mflo v1; move v0,v1` before).
 * Still differs: in each interlaced arm retail issues the division's zero trap (beqzl/break)
 * before dy's `dsll a3,v1,12`; ours after. sched2 gives the shift priority 5 (its anti
 * dependence on the dx term's daddiu into v1) and the trap 4 (the field load after it), and
 * the registers are retail's, so retail's sched2 saw a dependence ours lacks (a stale sched1
 * link to the trap, or the field load's chain one longer). Ruled out: the ternary as
 * `p->field ?`, `(... ? h * 2 : h) - 1`, `(h << 1) - 1`, `h * (... ? 2 : 1) - 1`, and
 * magh * w - 1 as a named (or const) local, which moves the multiplies. */
#include "common.h"

typedef struct GsParam {
    s16 interlace;
    s16 mode;
    s16 field;
    s16 version;
    s32 handler;
    s32 handler_id;
} GsParam;

typedef struct GsDispEnv {
    u64 pmode;
    u64 smode2;
    u64 dispfb;
    u64 display;
    u64 bgcolor;
} GsDispEnv;

s32 PrintFormatted(const char* format, ...);
GsParam* GetGsParams(void);
extern const char D_0024F510[];

/* The display register of a mode: position, magnification, size. */
#define GS_DISPLAY(dx, dy, magh, dw, dh) \
    (((u64)(magh) << 23) | ((u64)(dh) << 44) | (u64)(dx) | ((u64)(dy) << 12) | ((u64)(dw) << 32))


void DefineDisplayEnvironment(GsDispEnv* env, s16 psm, s16 w, s16 h, s16 dx, s16 dy)
{
    GsParam* p = GetGsParams();
    u16 interlace;

    interlace = p->interlace;
    env->pmode = 0x66;
    if (p->interlace != 0) {
        if (p->field != 0)
            env->smode2 = 3;
        else
            env->smode2 = 1;
    } else {
        env->smode2 = 2;
    }
    env->dispfb = ((u64)(psm & 0xF) << 15) | ((u64)(((w + 63) >> 6) & 0x3F) << 9);
    if (p->mode == 2) {
        if ((s16)interlace == 1) {
            s32 magh = (w + 0x9FF) / w;
            env->display = GS_DISPLAY(((u64)(dx * magh) + 0x27C) & 0xFFF, (dy + 0x32) & 0xFFF, magh - 1,
                                      magh * w - 1, p->field != 0 ? h * 2 - 1 : h - 1);
        } else {
            s32 magh = (w + 0x9FF) / w;
            env->display = GS_DISPLAY(((u64)(dx * magh) + 0x27C) & 0xFFF, (dy + 0x19) & 0xFFF, magh - 1,
                                      magh * w - 1, h - 1);
        }
    } else if (p->mode == 3) {
        if ((s16)interlace == 1) {
            s32 magh = (w + 0x9FF) / w;
            env->display = GS_DISPLAY(((u64)(dx * magh) + 0x290) & 0xFFF, (dy + 0x48) & 0xFFF, magh - 1,
                                      magh * w - 1, p->field != 0 ? h * 2 - 1 : h - 1);
        } else {
            s32 magh = (w + 0x9FF) / w;
            env->display = GS_DISPLAY(((u64)(dx * magh) + 0x290) & 0xFFF, (dy + 0x24) & 0xFFF, magh - 1,
                                      magh * w - 1, h - 1);
        }
    } else {
        PrintFormatted(D_0024F510, p->mode);
    }
    env->bgcolor = 0;
}
