// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 644/624, checked 2026-11-08
/* NEAR (src/lib/graph.c, where it is INCLUDE_ASM; built as C by 2.9-ee-991111): the start
 * matches up to the video mode test: the interlace value is read as a u16 before the store to
 * pmode (retail's lh for the smode2 test and lhu for the later (s16) compare: the store may
 * alias, so CSE keeps both loads), and dx's offset is added in 64 bits (daddiu: the product
 * cast to u64 first). Left: the four display computations come out 5 instructions longer;
 * retail cross-jumps the two interlaced tails (from the field test) and the two progressive
 * ones, and computes dy's term first, then magh, the products, magh - 1 and dx. Tried: five
 * orders of the OR tree in the macro. */
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
    ((u64)(dx) | ((u64)(dy) << 12) | ((u64)(magh) << 23) | ((u64)(dw) << 32) | ((u64)(dh) << 44))


void DefineDisplayEnvironment(GsDispEnv* env, s16 psm, s16 w, s16 h, s16 dx, s16 dy)
{
    GsParam* p = GetGsParams();
    u16 interlace;
    s32 magh;

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
            magh = (w + 0x9FF) / w;
            env->display = GS_DISPLAY(((u64)(dx * magh) + 0x27C) & 0xFFF, (dy + 0x32) & 0xFFF, magh - 1,
                                      magh * w - 1, p->field == 0 ? h - 1 : h * 2 - 1);
        } else {
            magh = (w + 0x9FF) / w;
            env->display = GS_DISPLAY(((u64)(dx * magh) + 0x27C) & 0xFFF, (dy + 0x19) & 0xFFF, magh - 1,
                                      magh * w - 1, h - 1);
        }
    } else if (p->mode == 3) {
        if ((s16)interlace == 1) {
            magh = (w + 0x9FF) / w;
            env->display = GS_DISPLAY(((u64)(dx * magh) + 0x290) & 0xFFF, (dy + 0x48) & 0xFFF, magh - 1,
                                      magh * w - 1, p->field == 0 ? h - 1 : h * 2 - 1);
        } else {
            magh = (w + 0x9FF) / w;
            env->display = GS_DISPLAY(((u64)(dx * magh) + 0x290) & 0xFFF, (dy + 0x24) & 0xFFF, magh - 1,
                                      magh * w - 1, h - 1);
        }
    } else {
        PrintFormatted(D_0024F510, p->mode);
    }
    env->bgcolor = 0;
}
