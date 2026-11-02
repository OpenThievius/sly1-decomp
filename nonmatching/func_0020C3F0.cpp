// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1783/1796 (99.3%), checked 2026-11-02
#include "common.h"
// NEAR: 7 lines differ, all in the field-picture block's loads of the four reference pointers (0x20C684 on): retail keeps the constant 2 of the f150 compare in a2 and the loads of f1D8[0]/f1C8[1] in a1/a0, ours a0 and a2/a1 (one load and the li swapped). Statement orders of the block (all 720) and if/ternary/&& forms of 'other' leave it put. Note: src/lib/0020C000.cpp declares this function with 4 parameters for func_0020C1A0; it takes 8.

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

void func_0020CAF8(Dev_0020C3F0* self, Frame_0020C3F0* src, s32 srcField, s32 dstField,
                   s32 dstY, s32 height, s32 x, s32 y, s32 dx, s32 dy, s32 half,
                   s32 average);
void func_0020E120(Dev_0020C3F0* self, s32* out, s32* base, s32 dx, s32 dy);
void func_0020B940(Dev_0020C3F0* self, const char* fmt, s32 value);

extern const char D_00250288[];
extern const char D_002502A8[];
extern const char D_002502C8[];

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
                func_0020CAF8(self, self->f1B8, 0, 0, 0, 16, x, y, vec[0], vec[1], 0, 0);
            } else if (type == 1) {
                func_0020CAF8(self, self->f1B8, sel[0], 0, 0, 8, x, y, vec[0], vec[1] >> 1,
                              type, 0);
                func_0020CAF8(self, self->f1B8, sel[2], 1, 0, 8, x, y, vec[4], vec[5] >> 1,
                              type, 0);
            } else if (type == 3) {
                func_0020E120(self, dual, base, vec[0], vec[1] >> 1);
                func_0020CAF8(self, self->f1B8, 0, 0, 0, 8, x, y, vec[0], vec[1] >> 1, other, 0);
                func_0020CAF8(self, self->f1B8, 1, 0, 0, 8, x, y, dual[0], dual[1], other, 1);
                func_0020CAF8(self, self->f1B8, 1, 1, 0, 8, x, y, vec[0], vec[1] >> 1, other, 0);
                func_0020CAF8(self, self->f1B8, 0, 1, 0, 8, x, y, dual[2], dual[3], other, 1);
            } else {
                func_0020B940(self, D_00250288, type);
            }
        } else {
            bottom = self->f174 == 2;
            refs[0][0] = self->f1C8[0];
            refs[0][1] = self->f1D8[0];
            refs[1][0] = self->f1C8[1];
            refs[1][1] = self->f1D8[1];
            other = self->f150 == 2 && self->f120 != 0 && bottom != sel[0];
            if (type == 1 || !forward) {
                func_0020CAF8(self, refs[other][sel[0]], 0, 0, 0, 16, x, y, vec[0], vec[1], 0,
                              0);
            } else if (type == 2) {
                func_0020CAF8(self, refs[other][sel[0]], 0, 0, 0, 8, x, y, vec[0], vec[1], 0,
                              0);
                other = 0;
                if (self->f150 == 2 && self->f120 != 0 && bottom != sel[2])
                    other = 1;
                func_0020CAF8(self, refs[other][sel[2]], 0, 0, 8, 8, x, y, vec[4], vec[5], 0,
                              0);
            } else if (type == 3) {
                other = 0;
                if (self->f120 != 0)
                    other = 1;
                func_0020E120(self, dual, base, vec[0], vec[1]);
                func_0020CAF8(self, refs[0][bottom], 0, 0, 0, 16, x, y, vec[0], vec[1], 0, 0);
                func_0020CAF8(self, refs[other][!bottom], 0, 0, 0, 16, x, y, dual[0], dual[1],
                              0, 1);
            } else {
                func_0020B940(self, D_002502A8, type);
            }
        }
        average = 1;
    }

    if (flags & 4) {
        if (self->f174 == 3) {
            other = 1;
            if (type == 2) {
                func_0020CAF8(self, self->f1BC, 0, 0, 0, 16, x, y, vec[2], vec[3], 0, average);
            } else {
                func_0020CAF8(self, self->f1BC, sel[1], 0, 0, 8, x, y, vec[2], vec[3] >> 1,
                              other, average);
                func_0020CAF8(self, self->f1BC, sel[3], 1, 0, 8, x, y, vec[6], vec[7] >> 1,
                              other, average);
            }
        } else if (type == 1) {
            func_0020CAF8(self, sel[1] ? self->f1D8[1] : self->f1C8[1], 0, 0, 0, 16, x, y,
                          vec[2], vec[3], 0, average);
        } else if (type == 2) {
            func_0020CAF8(self, sel[1] ? self->f1D8[1] : self->f1C8[1], 0, 0, 0, 8, x, y,
                          vec[2], vec[3], 0, average);
            func_0020CAF8(self, sel[3] ? self->f1D8[1] : self->f1C8[1], 0, 0, 8, 8, x, y,
                          vec[6], vec[7], 0, average);
        } else {
            func_0020B940(self, D_002502C8, type);
        }
    }
}
