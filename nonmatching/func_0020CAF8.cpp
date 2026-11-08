// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1032/1052, checked 2026-11-08
// NEAR: in its file, src/lib/mpeg_macroblock.cpp (Sony's 2.9-ee-991111). The logic is
//       retail's (258 instructions to its 263, tools/regdiff.py "code" 49%): the luma and chroma
//       parts' positions, row splits and source rows, the routines from the two tables, the
//       count. Left: the register allocation and the spills; retail keeps &preds[0].count, the
//       destination base, x, dstField, the luma block and the routine index on the stack (a
//       0xB0 frame), ours keeps self + 0x6BC in LO1 and spills less (0xA0). Tried: the
//       destination base read first into a local, the chroma part's pointer taken later.
//       Written for this project from retail's code.
#include "common.h"

extern void (*D_0027B000[8])();
extern void (*D_0027B020[8])();

// One prediction of a block: where it goes, its sub-position, the rows before and after the
// source block's edge, the source's row stride and its two source rows.
struct Part_20CAF8 {
    u32 dst;
    s32 offset;
    s32 rows;
    s32 rest;
    s32 stride;
    u32 src0;
    u32 src1;
};

// A macroblock's list of predictions (up to four): the work buffer, the source macroblocks, the
// routines and the luma and chroma parts.
struct Pred_20CAF8 {
    u32 work;
    u8 pad4[4];
    u32 src0[4];
    u32 src1[4];
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
    u32 dst;
};

struct Frame_20CAF8 {
    u32 data;
    u8 pad4[0xC];
    s32 width;
};

void PredictMacroblock(Dec_20CAF8* self, Frame_20CAF8* src, s32 srcField, s32 dstField, s32 dstY, s32 height,
                       s32 x, s32 y, s32 dx, s32 dy, s32 half, s32 average)
{
    s32 n = self->preds[self->current].count;
    Part_20CAF8* luma = &self->preds[self->current].lumaPart[n];
    Part_20CAF8* chroma = &self->preds[self->current].chromaPart[n];
    s32 xs, ys, xb, yb, xo, yo, sub;
    s32 lumaBlock, lumaSel, chromaSel;
    s32 cxs, cys, cxb, cyb, cxo, cyo;
    u32 base;
    s32 cdx, cdy;

    xs = (dx >> 1) + x;
    if (half)
        ys = ((dy >> 1) << 1) + y + dstY + srcField;
    else
        ys = (dy >> 1) + y + dstY + srcField;
    xb = xs >> 4;
    yb = ys >> 4;
    lumaBlock = xb * src->width + yb;
    xo = xs - (xb << 4);
    yo = ys - (yb << 4);
    luma->offset = xo;
    luma->dst = self->dst + ((dstField + dstY) << 5);
    if (dy & 1) {
        if (yo + (height << half) < 16) {
            luma->rows = height;
            luma->rest = 0;
        } else {
            sub = (16 >> half) - (yo >> half) - 1;
            luma->rows = sub;
            luma->rest = height - sub;
        }
    } else {
        if (yo + (height << half) < 17) {
            luma->rows = height;
            luma->rest = 0;
        } else {
            sub = (16 >> half) - (yo >> half);
            luma->rows = sub;
            luma->rest = height - sub;
        }
    }
    lumaSel = (average << 2) | ((dx & 1) << 1) | (dy & 1);
    base = self->preds[self->current].work + n * 0x600;
    luma->src0 = base + (yo << 4);
    luma->stride = 16 << half;
    luma->src1 = base + (yo << 4) + 0x300;

    cdx = dx / 2;
    cdy = dy / 2;
    cxs = (cdx >> 1) + (x >> 1);
    if (half)
        cys = ((cdy >> 1) << 1) + (y >> 1) + (dstY >> 1) + srcField;
    else
        cys = (cdy >> 1) + (y >> 1) + (dstY >> 1) + srcField;
    cxb = cxs >> 3;
    cyb = cys >> 3;
    cxo = cxs - (cxb << 3);
    cyo = cys - (cyb << 3);
    chroma->offset = cxo;
    chroma->dst = self->dst + (((dstField + (dstY >> 1)) << 4) + 0x200);
    if (cdy & 1) {
        if (cyo + ((height >> 1) << half) < 8) {
            chroma->rows = height >> 1;
            chroma->rest = 0;
        } else {
            sub = (8 >> half) - (cyo >> half) - 1;
            chroma->rows = sub;
            chroma->rest = (height >> 1) - sub;
        }
    } else {
        if (cyo + ((height >> 1) << half) < 9) {
            chroma->rows = height >> 1;
            chroma->rest = 0;
        } else {
            sub = (8 >> half) - (cyo >> half);
            chroma->rows = sub;
            chroma->rest = (height >> 1) - sub;
        }
    }
    chroma->stride = 8 << half;
    chromaSel = (average << 2) | ((cdx & 1) << 1) | (cdy & 1);
    self->preds[self->current].luma[n] = D_0027B000[lumaSel];
    base += ((cxb - xb) * 2 + (cyb - yb)) * 0x180;
    chroma->src0 = base + (cyo << 3) + 0x100;
    chroma->src1 = base + (cyo << 3) + 0x400;
    self->preds[self->current].src0[n] = src->data + lumaBlock * 0x180;
    self->preds[self->current].chroma[n] = D_0027B020[chromaSel];
    self->preds[self->current].src1[n] = src->data + (lumaBlock + src->width) * 0x180;
    self->preds[self->current].count = n + 1;
}
