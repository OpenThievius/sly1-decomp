// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1040/1052 (98.9%), checked 2026-11-10
// NEAR: in its file, src/lib/mpeg_macroblock.cpp (Sony's 2.9-ee-991111). Every instruction and
//       register but one value's: tools/regdiff.py "registers" 100% (263/263). xs, fx and fy are
//       reused for the chroma part (C style); the chroma block's base is its own variable (cbase),
//       which drops base's global-alloc priority (4 refs over 92 insns, from 7 over 112) below
//       srcField's, so fy takes t9 in pass 0 and dstY, srcField, base get s0, s1, s2 as retail;
//       fx reused gives fx and cdx s3 (docs/toolchain/global-alloc.md, func_0020CAF8). The chroma
//       statements in retail's order (cyb and cyo first, the offset stored before the
//       destination) and chroma[n] stored after src1[n].
//       Left: ys and yo take t1 where retail has a2 (8 instructions). yo dies in `yo << 4`,
//       whose register local-alloc makes t1 (as in retail); set_preference gives yo, and
//       through expand_preferences ys, a preference for t1, and global-alloc honours it. Retail's
//       a2 means t1 was excluded (a lower-priority conflicting allocno preferring t1, pass 0's
//       regs_someone_prefers) or yo did not die there. Tried: ys reused as yo, src1 before src0,
//       ch named before the luma part, permute.py --auto over this order.
//       Written for this project from retail's code.
#include "common.h"

extern void (*D_0027B000[8])();
extern void (*D_0027B020[8])();

// One prediction of a block: where it goes, its sub-position, the rows before and after the
// source block's edge, the source's row stride and its two source rows.
struct Part_20CAF8 {
    u8* dst;
    s32 offset;
    s32 rows;
    s32 rest;
    s32 stride;
    u8* src0;
    u8* src1;
};

// A macroblock's list of predictions (up to four): the work buffer, the source macroblocks, the
// routines and the luma and chroma parts.
struct Pred_20CAF8 {
    u8* work;
    u8 pad4[4];
    u8* src0[4];
    u8* src1[4];
    void (*luma[4])();
    void (*chroma[4])();
    Part_20CAF8 lumaPart[4];
    Part_20CAF8 chromaPart[4];
    u8 pad128[4];
    s32 count;
    u8 pad130[0x140 - 0x130];
};

struct Dec_20CAF8 {
    u8 pad000[0x590];
    Pred_20CAF8 preds[2];
    u8 pad810_[0x810 - 0x590 - 2 * 0x140];
    s32 current;
    u8 pad814[0x81C - 0x814];
    u8* dst;
};

// A reference frame: its macroblocks (0x180 bytes each, an address held as an int) and its
// width in macroblocks.
struct Frame_20CAF8 {
    s32 data;
    u8 pad4[0xC];
    s32 width;
};

void PredictMacroblock(Dec_20CAF8* self, Frame_20CAF8* src, s32 srcField, s32 dstField, s32 dstY, s32 height,
                       s32 x, s32 y, s32 dx, s32 dy, s32 half, s32 average)
{
    u8* dst;
    s32 n;
    Part_20CAF8* luma;
    Part_20CAF8* chroma;
    s32 xs, ys, xb, yb, xo, yo, sub;
    s32 lumaSel, lumaBlock, chromaSel;
    s32 cxb, cys, cyb, cxo, cyo;
    u8* base;
    u8* cbase;
    s32 cdx, cdy, ch, cY;
    s32 fx, fy;

    dst = self->dst;
    n = self->preds[self->current].count;
    luma = &self->preds[self->current].lumaPart[n];
    chroma = &self->preds[self->current].chromaPart[n];

    xs = (dx >> 1) + x;
    if (half)
        ys = ((dy >> 1) << 1) + srcField + dstY + y;
    else
        ys = (dy >> 1) + srcField + dstY + y;
    xb = xs >> 4;
    yb = ys >> 4;
    lumaBlock = xb * src->width + yb;
    xo = xs - (xb << 4);
    yo = ys - (yb << 4);
    luma->offset = xo;
    luma->dst = dst + ((dstField + dstY) << 5);
    fx = dx & 1;
    fy = dy & 1;
    if (fy) {
        if (yo + (height << half) >= 16) {
            sub = (16 >> half) - (yo >> half) - 1;
            luma->rows = sub;
            luma->rest = height - sub;
        } else {
            luma->rows = height;
            luma->rest = 0;
        }
    } else {
        if (yo + (height << half) > 16) {
            sub = (16 >> half) - (yo >> half);
            luma->rows = sub;
            luma->rest = height - sub;
        } else {
            luma->rows = height;
            luma->rest = 0;
        }
    }
    base = self->preds[self->current].work + n * 0x600;
    luma->src0 = base + (yo << 4);
    luma->src1 = base + ((yo << 4) + 0x300);
    luma->stride = 16 << half;
    lumaSel = (average << 2) | (fx << 1) | fy;

    cdx = dx / 2;
    cdy = dy / 2;
    ch = height >> 1;
    cY = dstY >> 1;
    xs = (cdx >> 1) + (x >> 1);
    if (half)
        cys = ((cdy >> 1) << 1) + srcField + cY + (y >> 1);
    else
        cys = (cdy >> 1) + srcField + cY + (y >> 1);
    cyb = cys >> 3;
    cyo = cys - (cyb << 3);
    fx = cdx & 1;
    cxb = xs >> 3;
    cxo = xs - (cxb << 3);
    fy = cdy & 1;
    chroma->offset = cxo;
    chroma->dst = dst + (((dstField + cY) << 4) + 0x200);
    if (fy) {
        if (cyo + (ch << half) >= 8) {
            sub = (8 >> half) - (cyo >> half) - 1;
            chroma->rows = sub;
            chroma->rest = ch - sub;
        } else {
            chroma->rows = ch;
            chroma->rest = 0;
        }
    } else {
        if (cyo + (ch << half) > 8) {
            sub = (8 >> half) - (cyo >> half);
            chroma->rows = sub;
            chroma->rest = ch - sub;
        } else {
            chroma->rows = ch;
            chroma->rest = 0;
        }
    }
    cbase = base + ((cxb - xb) * 2 + (cyb - yb)) * 0x180;
    chroma->src0 = cbase + ((cyo << 3) + 0x100);
    chroma->src1 = cbase + ((cyo << 3) + 0x400);
    chroma->stride = 8 << half;
    self->preds[self->current].luma[n] = D_0027B000[lumaSel];
    chromaSel = (average << 2) | (fx << 1) | fy;
    self->preds[self->current].src0[n] = (u8*)(src->data + lumaBlock * 0x180);
    self->preds[self->current].src1[n] = (u8*)(src->data + (lumaBlock + src->width) * 0x180);
    self->preds[self->current].chroma[n] = D_0027B020[chromaSel];
    self->preds[self->current].count++;
}
