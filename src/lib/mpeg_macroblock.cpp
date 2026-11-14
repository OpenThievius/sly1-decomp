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
void FetchLumaBlock(MpegBlockPart*);
void FetchChromaBlock(MpegBlockPart*);
void FetchLumaBlockHalfVertical(MpegBlockPart*);
void FetchChromaBlockHalfVertical(MpegBlockPart*);
void FetchLumaBlockHalfHorizontal(MpegBlockPart*);
void FetchChromaBlockHalfHorizontal(MpegBlockPart*);
void FetchLumaBlockHalfBoth(MpegBlockPart*);
void FetchChromaBlockHalfBoth(MpegBlockPart*);
void BlendLumaBlock(MpegBlockPart*);
void BlendChromaBlock(MpegBlockPart*);
void BlendLumaBlockHalfVertical(MpegBlockPart*);
void BlendChromaBlockHalfVertical(MpegBlockPart*);
void BlendLumaBlockHalfHorizontal(MpegBlockPart*);
void BlendChromaBlockHalfHorizontal(MpegBlockPart*);
void BlendLumaBlockHalfBoth(MpegBlockPart*);
void BlendChromaBlockHalfBoth(MpegBlockPart*);
MpegBlockFn g_lumaBlockFunctions[8] = { FetchLumaBlock, FetchLumaBlockHalfVertical, FetchLumaBlockHalfHorizontal, FetchLumaBlockHalfBoth, BlendLumaBlock, BlendLumaBlockHalfVertical, BlendLumaBlockHalfHorizontal, BlendLumaBlockHalfBoth };
MpegBlockFn g_chromaBlockFunctions[8] = { FetchChromaBlock, FetchChromaBlockHalfVertical, FetchChromaBlockHalfHorizontal, FetchChromaBlockHalfBoth, BlendChromaBlock, BlendChromaBlockHalfVertical, BlendChromaBlockHalfHorizontal, BlendChromaBlockHalfBoth };

void ReportMpegErrorFormat(MpegDecoder* d, const char* msg, s32 code);
void ComputeMotionVectors(MpegDecoder* self, s32 x, s32 y, s32 flags, s32 type, MpegMotionVector* vec, s32* sel, s32* base);
void StartBlockChainToScratchpad(MpegDecoder* self);

s32 PrepareMacroblockPrediction(MpegDecoder* d, s32 n, s32 mode, s32 flags, s32 code, MpegMotionVector* vec, s32* sel,
                                s32* base)
{
    s32 dir = flags & 1;
    s32 q = n / d->mbWidth;
    s32 r = n % d->mbWidth;
    s32 rx = r << 4;
    s32 qx = q << 4;

    if (dir) {
        while ((*(volatile u32*)0x1000D400 >> 8) & 1) {
        }
        d->macroblock[d->currentMacroblock].coded = 0;
    } else {
        if ((u32)(code - 1) >= 3) {
            ReportMpegErrorFormat(d, "Invalid modion type -- ignored(%d)", code);
            d->errored = 1;
            return 0;
        }
        ComputeMotionVectors(d, rx, qx, flags, code, vec, sel, base);
        while ((*(volatile u32*)0x1000D400 >> 8) & 1) {
        }
        StartBlockChainToScratchpad(d);
        d->macroblock[d->currentMacroblock].coded = 1;
    }
    if (mode == 1 && (flags & 2)) {
        d->macroblock[d->currentMacroblock].f134 = mode;
    } else {
        d->macroblock[d->currentMacroblock].f134 = 0;
    }
    d->macroblock[d->currentMacroblock].intra = dir;
    if (d->pictureStructure == 3) {
        MpegPicture* b3 = d->pictures[2];
        d->macroblock[d->currentMacroblock].destination = b3->address + (r * b3->mbHeight + q) * 0x180;
    } else {
        MpegPicture* b = d->pictureStructure == 2 ? d->pictures[10] : d->pictures[6];
        d->macroblock[d->currentMacroblock].destination = b->address + (r * b->mbHeight + q) * 0x180;
    }
    return 1;
}

// Motion-compensated prediction of one macroblock: picks the reference
// fields and vectors for each motion type and hands each block to the
// predictor.

void PredictMacroblock(MpegDecoder* self, MpegPicture* src, s32 srcField, s32 dstField, s32 dstY, s32 height, s32 x, s32 y, s32 dx, s32 dy, s32 half, s32 average);
void ComputeDualPrimeVectors(MpegDecoder* self, s32* out, s32* in, s32 x, s32 y);
void ReportMpegErrorFormat(MpegDecoder* self, const char* fmt, s32 value);


void ComputeMotionVectors(MpegDecoder* self, s32 x, s32 y, s32 flags, s32 type, MpegMotionVector* vec,
                   s32* sel, s32* base)
{
    s32 dual[4];
    MpegPicture* refs[2][2];
    s32 bottom;
    s32 other = 1;
    s32 average = 0;
    s32 forward;

    self->macroblock[self->currentMacroblock].count = 0;
    forward = flags & 8;
    if (forward || self->pictureType == 2) {
        if (self->pictureStructure == 3) {
            if (type == 2 || !forward) {
                PredictMacroblock(self, self->pictures[0], 0, 0, 0, 16, x, y, vec[0].x, vec[0].y, 0, 0);
            } else if (type == 1) {
                PredictMacroblock(self, self->pictures[0], sel[0], 0, 0, 8, x, y, vec[0].x, vec[0].y >> 1,
                              type, 0);
                PredictMacroblock(self, self->pictures[0], sel[2], 1, 0, 8, x, y, vec[2].x, vec[2].y >> 1,
                              type, 0);
            } else if (type == 3) {
                ComputeDualPrimeVectors(self, dual, base, vec[0].x, vec[0].y >> 1);
                PredictMacroblock(self, self->pictures[0], 0, 0, 0, 8, x, y, vec[0].x, vec[0].y >> 1, other, 0);
                PredictMacroblock(self, self->pictures[0], 1, 0, 0, 8, x, y, dual[0], dual[1], other, 1);
                PredictMacroblock(self, self->pictures[0], 1, 1, 0, 8, x, y, vec[0].x, vec[0].y >> 1, other, 0);
                PredictMacroblock(self, self->pictures[0], 0, 1, 0, 8, x, y, dual[2], dual[3], other, 1);
            } else {
                ReportMpegErrorFormat(self, "(a) invalid motion_type(%d)-0", type);
            }
        } else {
            bottom = self->pictureStructure == 2;
            refs[0][0] = self->pictures[4];
            refs[0][1] = self->pictures[8];
            refs[1][0] = self->pictures[5];
            refs[1][1] = self->pictures[9];
            if (self->pictureType == 2 && self->secondField != 0 && bottom != sel[0])
                other = 1;
            else
                other = 0;
            if (type == 1 || !forward) {
                PredictMacroblock(self, refs[other][sel[0]], 0, 0, 0, 16, x, y, vec[0].x, vec[0].y, 0,
                              0);
            } else if (type == 2) {
                PredictMacroblock(self, refs[other][sel[0]], 0, 0, 0, 8, x, y, vec[0].x, vec[0].y, 0,
                              0);
                other = 0;
                if (self->pictureType == 2 && self->secondField != 0 && bottom != sel[2])
                    other = 1;
                PredictMacroblock(self, refs[other][sel[2]], 0, 0, 8, 8, x, y, vec[2].x, vec[2].y, 0,
                              0);
            } else if (type == 3) {
                other = 0;
                if (self->secondField != 0)
                    other = 1;
                ComputeDualPrimeVectors(self, dual, base, vec[0].x, vec[0].y);
                PredictMacroblock(self, refs[0][bottom], 0, 0, 0, 16, x, y, vec[0].x, vec[0].y, 0, 0);
                PredictMacroblock(self, (refs[other][!bottom]), 0, 0, 0, 16, x, y, dual[0], dual[1],
                              0, 1);
            } else {
                ReportMpegErrorFormat(self, "(b) invalid motion_type(%d)-1", type);
            }
        }
        average = 1;
    }

    if (flags & 4) {
        if (self->pictureStructure == 3) {
            other = 1;
            if (type == 2) {
                PredictMacroblock(self, self->pictures[1], 0, 0, 0, 16, x, y, vec[1].x, vec[1].y, 0, average);
            } else {
                PredictMacroblock(self, self->pictures[1], sel[1], 0, 0, 8, x, y, vec[1].x, vec[1].y >> 1,
                              other, average);
                PredictMacroblock(self, self->pictures[1], sel[3], 1, 0, 8, x, y, vec[3].x, vec[3].y >> 1,
                              other, average);
            }
        } else if (type == 1) {
            PredictMacroblock(self, (sel[1] ? self->pictures[9] : self->pictures[5]), 0, 0, 0, 16, x, y,
                          vec[1].x, vec[1].y, 0, average);
        } else if (type == 2) {
            PredictMacroblock(self, (sel[1] ? self->pictures[9] : self->pictures[5]), 0, 0, 0, 8, x, y,
                          vec[1].x, vec[1].y, 0, average);
            PredictMacroblock(self, (sel[3] ? self->pictures[9] : self->pictures[5]), 0, 0, 8, 8, x, y,
                          vec[3].x, vec[3].y, 0, average);
        } else {
            ReportMpegErrorFormat(self, "(c) invalid motion_type(%d)-2", type);
        }
    }
}

void PredictMacroblock(MpegDecoder* self, MpegPicture* src, s32 srcField, s32 dstField, s32 dstY, s32 height,
                       s32 x, s32 y, s32 dx, s32 dy, s32 half, s32 average)
{
    u8* dst;
    s32 n;
    MpegBlockPart* luma;
    MpegBlockPart* chroma;
    s32 xs, ys, xb, yb, xo, yo, sub;
    s32 lumaSel, lumaBlock, chromaSel;
    s32 cxb, cyb, cxo;
    u8* base;
    u8* cbase;
    s32 cdx, cdy, ch, cY;
    s32 fx, fy;

    dst = (u8*)self->scratchDestination;
    n = self->macroblock[self->currentMacroblock].count;
    luma = &self->macroblock[self->currentMacroblock].lumaPart[n];
    chroma = &self->macroblock[self->currentMacroblock].chromaPart[n];

    xs = (dx >> 1) + x;
    if (half)
        ys = ((dy >> 1) << 1) + srcField + dstY + y;
    else
        ys = (dy >> 1) + srcField + dstY + y;
    xb = xs >> 4;
    yb = ys >> 4;
    lumaBlock = xb * src->mbHeight + yb;
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
    base = (u8*)self->macroblock[self->currentMacroblock].work + n * 0x600;
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
    self->macroblock[self->currentMacroblock].luma[n] = g_lumaBlockFunctions[lumaSel];
    chromaSel = (average << 2) | (fx << 1) | fy;
    self->macroblock[self->currentMacroblock].src0[n] = (u8*)(src->address + lumaBlock * 0x180);
    self->macroblock[self->currentMacroblock].src1[n] = (u8*)(src->address + (lumaBlock + src->mbHeight) * 0x180);
    self->macroblock[self->currentMacroblock].chroma[n] = g_chromaBlockFunctions[chromaSel];
    self->macroblock[self->currentMacroblock].count++;
}

void ReportMpegError(MpegDecoder* self, const char* value);
void ClampMacroblock(s32 destination, u32 buffer);
void AddAndClampMacroblock(s32 destination, u32 scratch, u32 output);

void AddMacroblockResiduals(MpegDecoder* d, s32 n)
{
    s32 i;

    if (d->macroblock[n].coded != 0) {
        for (i = 0; i < d->macroblock[n].count; i++) {
            d->macroblock[n].luma[i](&d->macroblock[n].lumaPart[i]);
            d->macroblock[n].chroma[i](&d->macroblock[n].chromaPart[i]);
        }
    }
    if (d->macroblock[n].intra != 0 && d->macroblock[n].skipped != 0)
        ReportMpegError(d, "intra && skip MB");
    if (d->macroblock[n].intra != 0) {
        ClampMacroblock(d->macroblock[n].destination, d->macroblock[n].output);
    } else if (d->macroblock[n].skipped != 0) {
        ClampMacroblock(d->macroblock[n].destination, d->scratchDestination);
    } else {
        AddAndClampMacroblock(d->macroblock[n].destination, d->scratchDestination, d->macroblock[n].output);
    }
}
