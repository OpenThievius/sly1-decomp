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

// The hand-written prediction routines (src/lib/mpeg_motion_compensation.cpp), by kind of motion: whole
// pixel and half pixel.
void func_0020D138();
void func_0020D1B0();
void func_0020D248();
void func_0020D300();
void func_0020D3D0();
void func_0020D480();
void func_0020D538();
void func_0020D630();
void func_0020D730();
void func_0020D7D0();
void func_0020D880();
void func_0020D960();
void func_0020DA48();
void func_0020DB20();
void func_0020DBF0();
void func_0020DD10();
void (*D_0027B000[8])() = { func_0020D138, func_0020D248, func_0020D3D0, func_0020D538, func_0020D730, func_0020D880, func_0020DA48, func_0020DBF0 };
void (*D_0027B020[8])() = { func_0020D1B0, func_0020D300, func_0020D480, func_0020D630, func_0020D7D0, func_0020D960, func_0020DB20, func_0020DD10 };

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

void func_0020B940(Dev_20C1A0* d, const char* msg, s32 code);
void func_0020C3F0(Dev_20C1A0* d, s32 a, s32 b, s32 flags);
void func_00210C38(Dev_20C1A0* d);

s32 func_0020C1A0(Dev_20C1A0* d, s32 n, s32 mode, s32 flags, s32 code)
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
        func_00210C38(d);
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

struct Frame_0020C3F0;

struct Chan_0020C3F0 {
    s32 f00;
    s32 f04;
    u8 pad08[0x140 - 0x08];
};

struct Dev_0020C3F0 {
    u8 pad000[0x120];
    s32 f120;
    u8 pad124[0x150 - 0x124];
    s32 f150;
    u8 pad154[0x174 - 0x154];
    s32 f174;
    u8 pad178[0x1B8 - 0x178];
    Frame_0020C3F0* f1B8;
    Frame_0020C3F0* f1BC;
    u8 pad1C0[0x1C8 - 0x1C0];
    Frame_0020C3F0* f1C8[2];
    u8 pad1D0[0x1D8 - 0x1D0];
    Frame_0020C3F0* f1D8[2];
    u8 pad1E0[0x6B8 - 0x1E0];
    Chan_0020C3F0 chan[1];
    u8 pad_after[0x810 - 0x6B8 - 0x140];
    s32 f810;
};

void func_0020CAF8(Dev_0020C3F0* self, Frame_0020C3F0* src, s32 srcField, s32 dstField, s32 dstY, s32 height, s32 x, s32 y, s32 dx, s32 dy, s32 half, s32 average);
void func_0020E120(Dev_0020C3F0* self, s32* out, s32* base, s32 dx, s32 dy);
void func_0020B940(Dev_0020C3F0* self, const char* fmt, s32 value);


void func_0020C3F0(Dev_0020C3F0* self, s32 x, s32 y, s32 flags, s32 type, s32* vec,
                   s32* sel, s32* base)
{
    s32 dual[4];
    Frame_0020C3F0* refs[2][2];
    s32 bottom;
    s32 other = 1;
    s32 average = 0;
    s32 forward;

    self->chan[self->f810].f04 = 0;
    forward = flags & 8;
    if (forward || self->f150 == 2) {
        if (self->f174 == 3) {
            if (type == 2 || !forward) {
                PredictMacroblock(self, self->f1B8, 0, 0, 0, 16, x, y, vec[0], vec[1], 0, 0);
            } else if (type == 1) {
                PredictMacroblock(self, self->f1B8, sel[0], 0, 0, 8, x, y, vec[0], vec[1] >> 1,
                              type, 0);
                PredictMacroblock(self, self->f1B8, sel[2], 1, 0, 8, x, y, vec[4], vec[5] >> 1,
                              type, 0);
            } else if (type == 3) {
                func_0020E120(self, dual, base, vec[0], vec[1] >> 1);
                PredictMacroblock(self, self->f1B8, 0, 0, 0, 8, x, y, vec[0], vec[1] >> 1, other, 0);
                PredictMacroblock(self, self->f1B8, 1, 0, 0, 8, x, y, dual[0], dual[1], other, 1);
                PredictMacroblock(self, self->f1B8, 1, 1, 0, 8, x, y, vec[0], vec[1] >> 1, other, 0);
                PredictMacroblock(self, self->f1B8, 0, 1, 0, 8, x, y, dual[2], dual[3], other, 1);
            } else {
                ReportMpegErrorFormat(self, "(a) invalid motion_type(%d)-0", type);
            }
        } else {
            bottom = self->f174 == 2;
            refs[0][0] = self->f1C8[0];
            refs[0][1] = self->f1D8[0];
            refs[1][0] = self->f1C8[1];
            refs[1][1] = self->f1D8[1];
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
                func_0020E120(self, dual, base, vec[0], vec[1]);
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
                PredictMacroblock(self, self->f1BC, 0, 0, 0, 16, x, y, vec[2], vec[3], 0, average);
            } else {
                PredictMacroblock(self, self->f1BC, sel[1], 0, 0, 8, x, y, vec[2], vec[3] >> 1,
                              other, average);
                PredictMacroblock(self, self->f1BC, sel[3], 1, 0, 8, x, y, vec[6], vec[7] >> 1,
                              other, average);
            }
        } else if (type == 1) {
            PredictMacroblock(self, sel[1] ? self->f1D8[1] : self->f1C8[1], 0, 0, 0, 16, x, y,
                          vec[2], vec[3], 0, average);
        } else if (type == 2) {
            PredictMacroblock(self, sel[1] ? self->f1D8[1] : self->f1C8[1], 0, 0, 0, 8, x, y,
                          vec[2], vec[3], 0, average);
            PredictMacroblock(self, sel[3] ? self->f1D8[1] : self->f1C8[1], 0, 0, 8, 8, x, y,
                          vec[6], vec[7], 0, average);
        } else {
            ReportMpegErrorFormat(self, "(c) invalid motion_type(%d)-2", type);
        }
    }
}

INCLUDE_ASM(func_0020CAF8);

// The message of func_0020CF18, which is not matched yet.
extern const char D_002502E8[] = "intra && skip MB";

INCLUDE_ASM(func_0020CF18);
