// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1040/1052, checked 2026-11-10
// NEAR: in its file, src/lib/mpeg_macroblock.cpp (Sony's 2.9-ee-991111). The frame (0xB0), the
//       branch layout and the spill slots but one are retail's (tools/regdiff.py "code" 76%); the
//       three words short are retail's spill of the routine index (sw/lw 12(sp)) and its reload
//       of x (lw 4(sp)), so the size is the allocation's too. docs/TOOLCHAIN.md, "Reading a
//       library function's source off its code", has the readings: pointer rows (the constant added to the index first), the frame's data an
//       int and the rows one pointer type (type-based aliasing), the sums' term orders through
//       the balance table, the row tests with the split as `then`, the locals declared first (the
//       spill slots in pseudo order), ch and cY named (computed once before the branch).
//       Left: the routine index keeps s5 where retail spills it to 12(sp); local-alloc gives
//       `yo << 4` t2 after the luma row tests (retail t1), whose preference pulls ys and yo into
//       t2 (retail a2), the first difference in global-alloc's order; the registers cascade.
//       Tried: every order of the five statements after the luma tests with the four chroma
//       halvings (2,880 orders, best 77%), the flags' and the index's positions.
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
    s32 cxs, cys, cxb, cyb, cxo, cyo;
    u8* base;
    s32 cdx, cdy, ch, cY;
    s32 fx, fy, cfx, cfy;

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
    lumaSel = (average << 2) | (fx << 1) | fy;
    base = self->preds[self->current].work + n * 0x600;
    luma->src0 = base + (yo << 4);
    luma->stride = 16 << half;
    luma->src1 = base + ((yo << 4) + 0x300);

    cdx = dx / 2;
    cdy = dy / 2;
    ch = height >> 1;
    cY = dstY >> 1;
    cxs = (cdx >> 1) + (x >> 1);
    if (half)
        cys = ((cdy >> 1) << 1) + srcField + cY + (y >> 1);
    else
        cys = (cdy >> 1) + srcField + cY + (y >> 1);
    cxb = cxs >> 3;
    cyb = cys >> 3;
    cxo = cxs - (cxb << 3);
    cyo = cys - (cyb << 3);
    chroma->offset = cxo;
    chroma->dst = dst + (((dstField + cY) << 4) + 0x200);
    cfx = cdx & 1;
    cfy = cdy & 1;
    if (cfy) {
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
    chroma->stride = 8 << half;
    chromaSel = (average << 2) | (cfx << 1) | cfy;
    self->preds[self->current].luma[n] = D_0027B000[lumaSel];
    base += ((cxb - xb) * 2 + (cyb - yb)) * 0x180;
    chroma->src0 = base + ((cyo << 3) + 0x100);
    chroma->src1 = base + ((cyo << 3) + 0x400);
    self->preds[self->current].src0[n] = (u8*)(src->data + lumaBlock * 0x180);
    self->preds[self->current].chroma[n] = D_0027B020[chromaSel];
    self->preds[self->current].src1[n] = (u8*)(src->data + (lumaBlock + src->width) * 0x180);
    self->preds[self->current].count++;
}
