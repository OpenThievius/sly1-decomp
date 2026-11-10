// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 718/1052 (68.3%), checked 2026-11-10
// NEAR: in its file, src/lib/mpeg_macroblock.cpp (Sony's 2.9-ee-991111). Retail's size, frame
//       (0xB0) and all seven spill slots (dstField, x, the destination, the routine index, the
//       luma block, `&count`'s base, `average << 2`); tools/regdiff.py "order" 85.9%. Two luma
//       variables are reused for the chroma part, C style (docs/toolchain/sched1.md, "A variable
//       reused for a second half", func_0020CAF8): xs (set twice, so sched1 no longer raises
//       its add; the dx half then takes t2 and x is reloaded, retail's `lw a3,4(sp)`), and fy
//       (more references, so the routine index loses its register and is spilled at 12(sp)).
//       Left: global-alloc's order. fy (6 refs over 109 insns) is placed 16th and takes s0 where
//       retail has t9, which pushes dstY, srcField and dy one saved register up (s1, s2, t9
//       against s0, s1, s2); half and the luma part swap t4 and t5 (a preference for t4 from
//       the luma block's product, r203); `yo << 4` takes t2 in local-alloc (retail t1) and pulls
//       ys and yo into t2. Tried: every subset of reusing xs, ys, xo, yo, fx, fy for the chroma
//       part (64; xs+fy best, fx too gives 81%), the chroma base as its own variable (no change),
//       the src0/src1 statement orders, and permute.py --auto (this order).
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
    s32 cdx, cdy, ch, cY;
    s32 fx, fy, cfx;

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
    cxb = xs >> 3;
    cxo = xs - (cxb << 3);
    cyb = cys >> 3;
    cyo = cys - (cyb << 3);
    chroma->dst = dst + (((dstField + cY) << 4) + 0x200);
    chroma->offset = cxo;
    cfx = cdx & 1;
    fy = cdy & 1;
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
    base += ((cxb - xb) * 2 + (cyb - yb)) * 0x180;
    chroma->src0 = base + ((cyo << 3) + 0x100);
    chroma->src1 = base + ((cyo << 3) + 0x400);
    chroma->stride = 8 << half;
    self->preds[self->current].luma[n] = D_0027B000[lumaSel];
    chromaSel = (average << 2) | (cfx << 1) | fy;
    self->preds[self->current].src0[n] = (u8*)(src->data + lumaBlock * 0x180);
    self->preds[self->current].chroma[n] = D_0027B020[chromaSel];
    self->preds[self->current].src1[n] = (u8*)(src->data + (lumaBlock + src->width) * 0x180);
    self->preds[self->current].count++;
}
