// SPDX-License-Identifier: AGPL-3.0-or-later
// The MPEG library's macroblock layer, from 0x20C1A0 to 0x20D138, built whole
// (config/us/files.tsv): the decoding of a macroblock's modes and motion vectors
// (func_0020C1A0, func_0020C3F0, func_0020E120's prediction set-up), the prediction that calls the
// hand-written routines of src/lib/mpeg_motion_compensation.cpp through the two tables of this file's .data
// (func_0020CAF8), and the residual's addition (func_0020CF18). Its start is the 16-byte boundary
// after func_0020C188's padding (two more words of nops than 8-byte alignment explains), its end
// the hand-written object. Its .rodata is its messages. Written for
// this project from retail's code.
#include "common.h"
#include "asm_func.h"
#include "mpeg_decoder.h"

// The hand-written prediction routines (src/lib/mpeg_motion_compensation.cpp), by kind of motion: whole
// pixel and half pixel.
void FetchLumaBlock();
void FetchChromaBlock();
void FetchLumaBlockHalfVertical();
void FetchChromaBlockHalfVertical();
void FetchLumaBlockHalfHorizontal();
void FetchChromaBlockHalfHorizontal();
void FetchLumaBlockHalfBoth();
void FetchChromaBlockHalfBoth();
void BlendLumaBlock();
void BlendChromaBlock();
void BlendLumaBlockHalfVertical();
void BlendChromaBlockHalfVertical();
void BlendLumaBlockHalfHorizontal();
void BlendChromaBlockHalfHorizontal();
void BlendLumaBlockHalfBoth();
void BlendChromaBlockHalfBoth();
void (*D_0027B000[8])() = { FetchLumaBlock, FetchLumaBlockHalfVertical, FetchLumaBlockHalfHorizontal, FetchLumaBlockHalfBoth, BlendLumaBlock, BlendLumaBlockHalfVertical, BlendLumaBlockHalfHorizontal, BlendLumaBlockHalfBoth };
void (*D_0027B020[8])() = { FetchChromaBlock, FetchChromaBlockHalfVertical, FetchChromaBlockHalfHorizontal, FetchChromaBlockHalfBoth, BlendChromaBlock, BlendChromaBlockHalfVertical, BlendChromaBlockHalfHorizontal, BlendChromaBlockHalfBoth };

struct Chan_20C1A0 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    u8 pad14[0x140 - 0x14];
};

struct Blk_20C1A0 {
    s32 f00;
    u8 pad04[0x0C];
    s32 f10;
};

struct Dev_20C1A0 {
    u8 pad000[0x11C];
    s32 f11C;
    u8 pad120[0x12C - 0x120];
    s32 f12C;
    u8 pad130[0x174 - 0x130];
    s32 f174;
    u8 pad178[0x1C0 - 0x178];
    Blk_20C1A0* f1C0;
    u8 pad1C4[0x1D0 - 0x1C4];
    Blk_20C1A0* f1D0;
    u8 pad1D4[0x1E0 - 0x1D4];
    Blk_20C1A0* f1E0;
    u8 pad1E4[0x6B8 - 0x1E4];
    Chan_20C1A0 chan[1];
    u8 pad_after[0x810 - 0x6B8 - 0x140];
    s32 f810;
};

void ReportMpegErrorFormat(Dev_20C1A0* d, const char* msg, s32 code);
void ComputeMotionVectors(Dev_20C1A0* d, s32 a, s32 b, s32 flags);
void StartBlockChainToScratchpad(Dev_20C1A0* d);

s32 PrepareMacroblockPrediction(Dev_20C1A0* d, s32 n, s32 mode, s32 flags, s32 code)
{
    s32 dir = flags & 1;
    s32 q = n / d->f12C;
    s32 r = n % d->f12C;
    s32 rx = r << 4;
    s32 qx = q << 4;

    if (dir) {
        while ((*(volatile u32*)0x1000D400 >> 8) & 1) {
        }
        d->chan[d->f810].f10 = 0;
    } else {
        if ((u32)(code - 1) >= 3) {
            ReportMpegErrorFormat(d, "Invalid modion type -- ignored(%d)", code);
            d->f11C = 1;
            return 0;
        }
        ComputeMotionVectors(d, rx, qx, flags);
        while ((*(volatile u32*)0x1000D400 >> 8) & 1) {
        }
        StartBlockChainToScratchpad(d);
        d->chan[d->f810].f10 = 1;
    }
    if (mode == 1 && (flags & 2)) {
        d->chan[d->f810].f0C = mode;
    } else {
        d->chan[d->f810].f0C = 0;
    }
    d->chan[d->f810].f08 = dir;
    if (d->f174 == 3) {
        Blk_20C1A0* b3 = d->f1C0;
        d->chan[d->f810].f00 = b3->f00 + (r * b3->f10 + q) * 0x180;
    } else {
        Blk_20C1A0* b = d->f174 == 2 ? d->f1E0 : d->f1D0;
        d->chan[d->f810].f00 = b->f00 + (r * b->f10 + q) * 0x180;
    }
    return 1;
}

// Motion-compensated prediction of one macroblock: picks the reference
// fields and vectors for each motion type and hands each block to the
// predictor.

void PredictMacroblock(MpegDecoder* self, MpegPicture* src, s32 srcField, s32 dstField, s32 dstY, s32 height, s32 x, s32 y, s32 dx, s32 dy, s32 half, s32 average);
void ComputeDualPrimeVectors(MpegDecoder* self, s32* out, s32* base, s32 dx, s32 dy);
void ReportMpegErrorFormat(MpegDecoder* self, const char* fmt, s32 value);


void ComputeMotionVectors(MpegDecoder* self, s32 x, s32 y, s32 flags, s32 type, s32* vec,
                   s32* sel, s32* base)
{
    s32 dual[4];
    MpegPicture* refs[2][2];
    s32 bottom;
    s32 other = 1;
    s32 average = 0;
    s32 forward;

    self->channel[self->f810].f04 = 0;
    forward = flags & 8;
    if (forward || self->f150 == 2) {
        if (self->f174 == 3) {
            if (type == 2 || !forward) {
                PredictMacroblock(self, self->pictures[0], 0, 0, 0, 16, x, y, vec[0], vec[1], 0, 0);
            } else if (type == 1) {
                PredictMacroblock(self, self->pictures[0], sel[0], 0, 0, 8, x, y, vec[0], vec[1] >> 1,
                              type, 0);
                PredictMacroblock(self, self->pictures[0], sel[2], 1, 0, 8, x, y, vec[4], vec[5] >> 1,
                              type, 0);
            } else if (type == 3) {
                ComputeDualPrimeVectors(self, dual, base, vec[0], vec[1] >> 1);
                PredictMacroblock(self, self->pictures[0], 0, 0, 0, 8, x, y, vec[0], vec[1] >> 1, other, 0);
                PredictMacroblock(self, self->pictures[0], 1, 0, 0, 8, x, y, dual[0], dual[1], other, 1);
                PredictMacroblock(self, self->pictures[0], 1, 1, 0, 8, x, y, vec[0], vec[1] >> 1, other, 0);
                PredictMacroblock(self, self->pictures[0], 0, 1, 0, 8, x, y, dual[2], dual[3], other, 1);
            } else {
                ReportMpegErrorFormat(self, "(a) invalid motion_type(%d)-0", type);
            }
        } else {
            bottom = self->f174 == 2;
            refs[0][0] = self->pictures[4];
            refs[0][1] = self->pictures[8];
            refs[1][0] = self->pictures[5];
            refs[1][1] = self->pictures[9];
            if (self->f150 == 2 && self->f120 != 0 && bottom != sel[0])
                other = 1;
            else
                other = 0;
            if (type == 1 || !forward) {
                PredictMacroblock(self, refs[other][sel[0]], 0, 0, 0, 16, x, y, vec[0], vec[1], 0,
                              0);
            } else if (type == 2) {
                PredictMacroblock(self, refs[other][sel[0]], 0, 0, 0, 8, x, y, vec[0], vec[1], 0,
                              0);
                other = 0;
                if (self->f150 == 2 && self->f120 != 0 && bottom != sel[2])
                    other = 1;
                PredictMacroblock(self, refs[other][sel[2]], 0, 0, 8, 8, x, y, vec[4], vec[5], 0,
                              0);
            } else if (type == 3) {
                other = 0;
                if (self->f120 != 0)
                    other = 1;
                ComputeDualPrimeVectors(self, dual, base, vec[0], vec[1]);
                PredictMacroblock(self, refs[0][bottom], 0, 0, 0, 16, x, y, vec[0], vec[1], 0, 0);
                PredictMacroblock(self, refs[other][!bottom], 0, 0, 0, 16, x, y, dual[0], dual[1],
                              0, 1);
            } else {
                ReportMpegErrorFormat(self, "(b) invalid motion_type(%d)-1", type);
            }
        }
        average = 1;
    }

    if (flags & 4) {
        if (self->f174 == 3) {
            other = 1;
            if (type == 2) {
                PredictMacroblock(self, self->pictures[1], 0, 0, 0, 16, x, y, vec[2], vec[3], 0, average);
            } else {
                PredictMacroblock(self, self->pictures[1], sel[1], 0, 0, 8, x, y, vec[2], vec[3] >> 1,
                              other, average);
                PredictMacroblock(self, self->pictures[1], sel[3], 1, 0, 8, x, y, vec[6], vec[7] >> 1,
                              other, average);
            }
        } else if (type == 1) {
            PredictMacroblock(self, sel[1] ? self->pictures[9] : self->pictures[5], 0, 0, 0, 16, x, y,
                          vec[2], vec[3], 0, average);
        } else if (type == 2) {
            PredictMacroblock(self, sel[1] ? self->pictures[9] : self->pictures[5], 0, 0, 0, 8, x, y,
                          vec[2], vec[3], 0, average);
            PredictMacroblock(self, sel[3] ? self->pictures[9] : self->pictures[5], 0, 0, 8, 8, x, y,
                          vec[6], vec[7], 0, average);
        } else {
            ReportMpegErrorFormat(self, "(c) invalid motion_type(%d)-2", type);
        }
    }
}

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
    s32 cxb, cyb, cxo;
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
        ys = ((cdy >> 1) << 1) + srcField + cY + (y >> 1);
    else
        ys = (cdy >> 1) + srcField + cY + (y >> 1);
    cyb = ys >> 3;
    yo = ys - (cyb << 3);
    fx = cdx & 1;
    cxb = xs >> 3;
    cxo = xs - (cxb << 3);
    fy = cdy & 1;
    chroma->offset = cxo;
    chroma->dst = dst + (((dstField + cY) << 4) + 0x200);
    if (fy) {
        if (yo + (ch << half) >= 8) {
            sub = (8 >> half) - (yo >> half) - 1;
            chroma->rows = sub;
            chroma->rest = ch - sub;
        } else {
            chroma->rows = ch;
            chroma->rest = 0;
        }
    } else {
        if (yo + (ch << half) > 8) {
            sub = (8 >> half) - (yo >> half);
            chroma->rows = sub;
            chroma->rest = ch - sub;
        } else {
            chroma->rows = ch;
            chroma->rest = 0;
        }
    }
    cbase = base + ((cxb - xb) * 2 + (cyb - yb)) * 0x180;
    chroma->src0 = cbase + ((yo << 3) + 0x100);
    chroma->src1 = cbase + ((yo << 3) + 0x400);
    chroma->stride = 8 << half;
    self->preds[self->current].luma[n] = D_0027B000[lumaSel];
    chromaSel = (average << 2) | (fx << 1) | fy;
    self->preds[self->current].src0[n] = (u8*)(src->data + lumaBlock * 0x180);
    self->preds[self->current].src1[n] = (u8*)(src->data + (lumaBlock + src->width) * 0x180);
    self->preds[self->current].chroma[n] = D_0027B020[chromaSel];
    self->preds[self->current].count++;
}

// A block of a macroblock's channel, handed to its routine.
struct Blk_20CF18 {
    u8 pad00[0x1C];
};

// One channel of the decoder, 0x140 bytes from +0x590: each block's two routines and the
// blocks, then the predicted picture, the block count and the macroblock's flags.
struct Chan_20CF18 {
    s32 f00;
    s32 f04;
    u8 pad08[0x28 - 0x08];
    void (*first[4])(Blk_20CF18* b);
    void (*second[4])(Blk_20CF18* b);
    Blk_20CF18 blkA[4];
    Blk_20CF18 blkB[4];
    s32 f128;
    s32 count;
    s32 intra;
    u8 pad134[0x138 - 0x134];
    s32 coded;
    s32 skip;
};

struct Dev_20CF18 {
    u8 pad000[0x590];
    Chan_20CF18 chan[2];
    u8 pad810[0x81C - 0x810];
    s32 f81C;
};

s32 ReportMpegError(Dev_20CF18* d, const char* msg);
void ClampMacroblock(s32 a, s32 b);
void AddAndClampMacroblock(s32 a, s32 b, s32 c);

void AddMacroblockResiduals(Dev_20CF18* d, s32 n)
{
    s32 i;

    if (d->chan[n].coded != 0) {
        for (i = 0; i < d->chan[n].count; i++) {
            d->chan[n].first[i](&d->chan[n].blkA[i]);
            d->chan[n].second[i](&d->chan[n].blkB[i]);
        }
    }
    if (d->chan[n].intra != 0 && d->chan[n].skip != 0)
        ReportMpegError(d, "intra && skip MB");
    if (d->chan[n].intra != 0) {
        ClampMacroblock(d->chan[n].f128, d->chan[n].f04);
    } else if (d->chan[n].skip != 0) {
        ClampMacroblock(d->chan[n].f128, d->f81C);
    } else {
        AddAndClampMacroblock(d->chan[n].f128, d->f81C, d->chan[n].f04);
    }
}
