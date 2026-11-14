// SPDX-License-Identifier: AGPL-3.0-or-later
// The rest of the MPEG library's decoder, from 0x20DEE8 to 0x2115C0, built whole
// (config/us/files.tsv): the IPU's control (func_0020DEE8), the slice and macroblock layer that
// drives the IPU's decoding (func_0020DF10 to func_0020EF70), the IPU's commands and its bit
// reading (func_0020F0C0 to func_0020F5B8), the picture header and its extensions, dispatched
// through the table D_00250430 (func_0020F708 to func_00210090), the pictures' output and
// their buffers (func_00210160 to func_00210A80), and the colour conversion by DMA and its
// interrupt handlers (func_00210C38 to func_00211348). Its start is exact: the hand-written
// prediction object ends at 0x20DEE8, and this file's .rodata starts at 0x250300 and its .data
// at 0x27B040, after src/lib/mpeg_macroblock.cpp's. Its end is chosen: the bit reader of
// src/lib/mpeg_bit_reader.cpp follows, which nothing here calls. Its .rodata is its messages and the
// extension table, its .data the IPU commands' table D_0027B040 and the table D_0027B068 (which
// ends at 0x27B0A8, before the padding to the IPU library's .data), its .bss func_00210C38's
// buffer. One file between those edges, with no evidence of a boundary inside it; it could be
// several. Written for this project from retail's code.
#include "common.h"
#include "asm_func.h"
#include "mpeg_decoder.h"
#include "system.h"

void SetIpuMpeg1Mode(u32 value)
{
    u32* setting = (u32*)0x10002010;
    u32 result = (*setting & 0xFF7FFFFFu) | (value << 23);
    *setting = result;
}

void WaitIpuCommandDone(MpegDecoder* o); // stays void: retail returns a value, but declared so func_0020DF10 and func_0020F708 differs in registers
void ReportMpegError(MpegDecoder* self, const char* value);
extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);

s32 WaitIpuDecodeDone(MpegDecoder* o)
{
    MpegSignal m;
    MpegSignal n;
    s32 result = 1;
    WaitIpuCommandDone(o);
    while (*(volatile u32*)0x1000B020 != 0 && (*(volatile u32*)0x10002010 & 0x4000) == 0) {
        if (*(volatile u32*)0x1000B420 == 0 && (*(volatile u32*)0x1000B400 & 0x100) == 0) {
            m.kind = 1;
            RunMpegCallback(o->handle, &m);
        }
    }
    u32 bp = *(volatile u32*)0x10002020;
    s64 top = *(s64*)0x10002030;
    o->window = (s32)top;
    if (top < 0) {
        u32 frac = bp & 0x1F;
        o->windowBits = frac != 0 ? 0x20 - frac : 0;
    } else {
        o->windowBits = 0x20;
    }
    if ((*(volatile u32*)0x10002010 & 0x4000) != 0) {
        result = 0;
        ReportMpegError(o, "Error code detected(BDEC)");
        n.kind = 2;
        RunMpegCallback(o->handle, &n);
        *(volatile u32*)0x10002010 = 0x40000000;
        n.kind = 3;
        RunMpegCallback(o->handle, &n);
        DisableInterrupts();
        *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
        *(volatile u32*)0x1000B000 = 0;
        *(u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
        EnableInterrupts();
        *(volatile u32*)0x1000B020 = 0;
    }
    return result;
}

s16 DecodeIpuVariableLength(MpegDecoder* self, s32 mode);

s32 DecodeIpuMotionCode(MpegDecoder* self)
{
	return DecodeIpuVariableLength(self, 3);
}

void ComputeDualPrimeVectors(MpegDecoder* self, s32* out, s32* in, s32 x, s32 y)
{
    if (self->pictureStructure == 3) {
        if (self->topFieldFirst != 0) {
            out[0] = ((x > 0 ? x + 1 : x) >> 1) + in[0];
            out[1] = ((y > 0 ? y + 1 : y) >> 1) + in[1] - 1;
            { s32 gx = x * 3;
            out[2] = ((x > 0 ? gx + 1 : gx) >> 1) + in[0]; }
            { s32 gy = y * 3;
            out[3] = ((y > 0 ? gy + 1 : gy) >> 1) + in[1] + 1; }
        } else {
            { s32 gx = x * 3;
            out[0] = ((x > 0 ? gx + 1 : gx) >> 1) + in[0]; }
            { s32 gy = y * 3;
            out[1] = ((y > 0 ? gy + 1 : gy) >> 1) + in[1] - 1; }
            out[2] = ((x > 0 ? x + 1 : x) >> 1) + in[0];
            out[3] = ((y > 0 ? y + 1 : y) >> 1) + in[1] + 1;
        }
        return;
    }
    out[0] = ((x > 0 ? x + 1 : x) >> 1) + in[0];
    s32 r = ((y > 0 ? y + 1 : y) >> 1) + in[1];
    out[1] = r;
    if (self->pictureStructure == 1) {
        out[1] = r - 1;
    } else {
        out[1] = r + 1;
    }
}

s16 DecodeIpuVariableLength(MpegDecoder* self, s32 mode);
s32 PeekIpuBits(MpegDecoder* obj, s32 a1);
void SkipIpuBits(MpegDecoder* s0, u32 s1);
void ReportMpegErrorFormat(MpegDecoder *self, const char *a1, s32 a2);

s32 ReadMacroblockAddressIncrement(MpegDecoder *self) {
    s32 total = 0;
    s32 again;
    do {
        s32 tok = DecodeIpuVariableLength(self, 0);
        switch ((u32)tok) {
        case 0x22:
            again = 1;
            break;
        case 0x23:
            again = 1;
            total += 0x21;
            break;
        case 0: {
            s32 v3 = PeekIpuBits(self, 0xB);
            if (self->mpeg2 != 0 && v3 == 0xF) {
                SkipIpuBits(self, 0xB);
                again = 1;
            } else {
                ReportMpegErrorFormat(self, "Invalid macroblock_address_increment code(0x%08x)", tok);
                self->errored = 1;
                return 1;
            }
            break;
        }
        default:
            total += tok;
            again = 0;
            break;
        }
    } while (again);
    return total;
}

s32 DecodeSliceMacroblocks(MpegDecoder* c, s32 n);
void WaitIpuCommandDone(MpegDecoder* c);
s32 WaitIpuDecodeDone(MpegDecoder* o);
void AddMacroblockResiduals(MpegDecoder* self, s32 next);
void ReportMpegError(MpegDecoder* self, const char* value);

s32 DecodeAllMacroblocks(MpegDecoder* c)
{
    s32 r;
    s32 n;
    s32 res;
    c->currentMacroblock = 0;
    c->f814 = 0;
    n = c->mbWidth * c->mbHeight;
    if (c->pictureStructure != 3) n = n >> 1;
    do {
        r = DecodeSliceMacroblocks(c, n);
    } while (r == 1 || r == 3);
    WaitIpuCommandDone(c);
    if (WaitIpuDecodeDone(c) == 0) r = 2;
    while ((*(volatile u32*)0x1000D400 >> 8) & 1) {}
    if (r == 0) AddMacroblockResiduals(c, c->currentMacroblock == 0);
    if ((u32)(r - 1) < 2) ReportMpegError(c, "= Skip to the next picture =");
    res = (r == 0);
    return res;
}

void FindNextStartCode(MpegDecoder* self);
s32 PeekIpuBits(MpegDecoder* obj, s32 a1);
void ReportMpegErrorFormat(MpegDecoder *self, const char *a1, s32 a2);
void SkipIpuBits(MpegDecoder* s0, u32 s1);
s32 ReadSliceQuantiser(MpegDecoder* self);
s32 ReadMacroblockAddressIncrement(MpegDecoder *self);
void ReportMpegError(MpegDecoder* self, const char* value);

s32 ReadSliceStart(MpegDecoder *self, s32 a1, s32 *outA, s32 *outB, MpegMotionVector *vectors) {
    u32 s2;
    s32 s3;
    s32 e;

    self->errored = 0;
    FindNextStartCode(self);
    s2 = (u32)PeekIpuBits(self, 0x20);
    if (s2 - 0x101 >= 0xAF) {
        ReportMpegErrorFormat(self, "slice_start_code(0x%08x) out of range", s2);
        return 2;
    }
    SkipIpuBits(self, 0x20);
    s3 = ReadSliceQuantiser(self);
    e = ReadMacroblockAddressIncrement(self);
    *outB = e;
    if (self->errored != 0) {
        ReportMpegError(self, "_sliceA0(): error happens");
        return 1;
    }
    *outA = ((s3 << 7) + (s2 & 0xFF) - 1) * self->mbWidth + e - 1;
    *outB = 1;
    self->dcReset = 1;
    vectors[2].y = 0;
    vectors[2].x = 0;
    vectors[0].y = 0;
    vectors[0].x = 0;
    vectors[3].y = 0;
    vectors[3].x = 0;
    vectors[1].y = 0;
    vectors[1].x = 0;
    return 0;
}

s32 ReadSliceStart(MpegDecoder *self, s32 a1, s32 *outA, s32 *outB, MpegMotionVector *vectors);
s32 WaitIpuDecodeDone(MpegDecoder* o);
s32 PeekIpuBits(MpegDecoder* obj, s32 a1);
s32 ReadMacroblockAddressIncrement(MpegDecoder *self);
void ReportMpegError(MpegDecoder* self, const char* value);
s32 DecodeMacroblock(MpegDecoder* self, s32* type, s32* motionType, s32* dctType, MpegMotionVector* vectors, s32* select, s32* dualPrime);
s32 HandleSkippedMacroblock(MpegDecoder *self, MpegMotionVector *vectors, s32 *motionType, s32 *select, s32 *type);
s32 PrepareMacroblockPrediction(MpegDecoder* d, s32 n, s32 mode, s32 flags, s32 code, MpegMotionVector* vec, s32* sel,
                                s32* base);

s32 DecodeSliceMacroblocks(MpegDecoder* c, s32 n)
{
    MpegMotionVector vectors[4];
    s32 select[4];
    s32 dualPrime[4];
    s32 i, j, a, b, d;
    i = 0;
    j = 0;
    s32 r = ReadSliceStart(c, n, &i, &j, vectors);
    if (r != 0) return r;
    c->errored = 0;
    for (;;) {
        if (!(i < n)) return 0;
        c->macroblock[c->currentMacroblock].skipped = 0;
        if (WaitIpuDecodeDone(c) == 0) return 2;
        if (j == 0) {
            if (PeekIpuBits(c, 0x17) == 0) {
                c->errored = 0;
                return 3;
            }
            if (c->errored != 0) {
                c->errored = 0;
                return 3;
            }
            j = ReadMacroblockAddressIncrement(c);
            if (c->errored != 0) {
                c->errored = 0;
                return 1;
            }
        }
        if (!(i < n)) {
            ReportMpegError(c, "Too many macroblocks in picture");
            return 2;
        }
        if (j == 1) {
            if (DecodeMacroblock(c, &a, &b, &d, vectors, select, dualPrime) == 0) {
                c->errored = 0;
                return 1;
            }
        } else {
            if (HandleSkippedMacroblock(c, vectors, &b, select, &a) == 0) {
                c->errored = 0;
                return 2;
            }
        }
        if (PrepareMacroblockPrediction(c, i, j, a, b, vectors, select, dualPrime) == 0) {
            c->errored = 0;
            return 2;
        }
        if (i != 0) AddMacroblockResiduals(c, c->currentMacroblock ^ 1);
        i = i + 1;
        c->currentMacroblock = c->currentMacroblock ^ 1;
        j = j - 1;
    }
}

s32 HandleSkippedMacroblock(MpegDecoder *self, MpegMotionVector *vectors, s32 *motionType, s32 *select, s32 *type)
{
    s32 ret = 1;
    u32 t;

    self->macroblock[self->currentMacroblock].skipped = 1;
    self->dcReset = 1;
    if (self->pictureType == 2) {
        vectors[2].y = 0;
        vectors[2].x = 0;
        vectors[0].y = 0;
        vectors[0].x = 0;
    }
    if (self->pictureStructure == 3) {
        *motionType = 2;
    } else {
        *motionType = 1;
        t = (u32)(self->pictureStructure ^ 2) < 1;
        select[1] = t;
        select[0] = t;
    }
    if (self->pictureType == 1) {
        ReportMpegError(self, "skiped macroblock in I picure is not allowed");
        ret = 0;
    }
    *type &= -2;
    return ret;
}

s16 DecodeIpuVariableLength(MpegDecoder* self, s32 mode);
void ReportMpegError(MpegDecoder* self, const char* value);
u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void SkipIpuBits(MpegDecoder* s0, u32 s1);
void WaitIpuCommandDone(MpegDecoder* self);
void SendIpuCommand(MpegDecoder* obj, u32 value);
void StartIpuOutputDma(u32 a, s32 b);
void ReadFieldMotionVector(MpegDecoder* c, MpegMotionVector* vectors, s32* a2, s32* out, s32 i, s32 mode, s32 a6, s32 a7, s32 s6, s32 s3, s32 fp);
void ReadMotionVector(MpegDecoder* self, MpegMotionVector* n, s32* out, s32 p3, s32 p4, s32 want, s32 shift, s32 p7);

s32 DecodeMacroblock(MpegDecoder* self, s32* st, s32* mode, s32* o3, MpegMotionVector* b1, s32* o5, s32* b2)
{
    s32 m3, m4, m7, mfp;
    s32 v;

    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xF8FFFFFF) | (self->pictureType << 24);
    v = DecodeIpuVariableLength(self, 1);
    *st = v;
    if (v == 0) {
        ReportMpegError(self, "Invalid macroblock_type code: 0");
        self->errored = 1;
        return 0;
    }
    if (v & 0xC) {
        if (self->pictureStructure == 3 && self->framePredFrameDct != 0) {
            *mode = 2;
        } else {
            *mode = ReadIpuBits(self, 2);
        }
    } else if (v & 1) {
        if (self->concealmentMotionVectors != 0) {
            *mode = (self->pictureStructure == 3) ? 2 : 1;
        }
    }
    if (self->pictureStructure == 3) {
        m3 = (*mode == 1) ? 2 : 1;
        m4 = (*mode == 2);
    } else {
        m4 = 0;
        m3 = (*mode == 2) ? 2 : 1;
    }
    mfp = (*mode == 3);
    m7 = 0;
    if (m4 == 0) {
        m7 = (self->pictureStructure == 3);
    }
    s32 w;
    if (self->pictureStructure == 3 && self->framePredFrameDct == 0) {
        if ((*st & 3) != 0) {
            w = ReadIpuBits(self, 1);
        } else {
            w = 0;
        }
    } else {
        w = 0;
    }
    *o3 = w;
    if (*st & 0x10) {
        self->quantiserScale = ReadIpuBits(self, 5);
    }
    if ((*st & 8) || ((*st & 1) && self->concealmentMotionVectors)) {
        if (self->mpeg2) {
            ReadFieldMotionVector(self, b1, b2, o5, 0, m3, m4, self->fCode[0] - 1, self->fCode[1] - 1, mfp, m7);
        } else {
            s32 t = self->forwardFCode - 1;
            ReadMotionVector(self, b1, b2, t, t, 0, 0, self->fullPelForward);
        }
    }
    if (self->errored) {
        return 0;
    }
    if (*st & 4) {
        if (self->mpeg2) {
            ReadFieldMotionVector(self, b1, b2, o5, 1, m3, m4, self->fCode[2] - 1, self->fCode[3] - 1, 0, m7);
        } else {
            s32 t = self->backwardFCode - 1;
            ReadMotionVector(self, b1 + 1, b2, t, t, 0, 0, self->fullPelBackward);
        }
    }
    if (self->errored) {
        return 0;
    }
    if ((*st & 1) && self->concealmentMotionVectors) {
        SkipIpuBits(self, 1);
    }
    if (*st & 3) {
        StartIpuOutputDma(self->macroblock[self->currentMacroblock].output, 0x300);
        WaitIpuCommandDone(self);
        s32 x = ((*st & 1) << 27) | (self->quantiserScale << 16);
        s32 y = (self->dcReset << 26) | 0x20000000;
        s32 z = *o3 << 25;
        SendIpuCommand(self, x | y | z);
    } else {
        self->macroblock[self->currentMacroblock].skipped = 1;
    }
    self->dcReset = 0;
    if (self->errored) {
        return 0;
    }
    if ((*st & 1) == 0) {
        self->dcReset = 1;
    }
    if ((*st & 1) && self->concealmentMotionVectors == 0) {
        b1[2].y = 0;
        b1[2].x = 0;
        b1[0].y = 0;
        b1[0].x = 0;
        b1[3].y = 0;
        b1[3].x = 0;
        b1[1].y = 0;
        b1[1].x = 0;
    }
    s32 d = self->pictureType;
    if (d == 2 && (*st & 9) == 0) {
        b1[2].y = 0;
        b1[2].x = 0;
        b1[0].y = 0;
        b1[0].x = 0;
        if (self->pictureStructure == 3) {
            *mode = d;
        } else {
            *mode = 1;
            *o5 = (self->pictureStructure == 2);
        }
    }
    return 1;
}

void ApplyMotionVectorDelta(s32* component, s32 rsize, s32 code, s32 residual, s32 half)
{
    s32 f = 16 << rsize;
    s32 v = *component;
    if (half) {
        v >>= 1;
    }
    if (code > 0) {
        v += ((code - 1) << rsize) + residual + 1;
        if (v >= f) {
            v -= f * 2;
        }
    } else if (code < 0) {
        v -= ((-code - 1) << rsize) + residual + 1;
        if (v < -f) {
            v += f * 2;
        }
    }
    *component = half ? v << 1 : v;
}


u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void ReadMotionVector(MpegDecoder* self, MpegMotionVector* n, s32* out, s32 p3, s32 p4, s32 want, s32 shift, s32 p7);

void ReadFieldMotionVector(MpegDecoder* c, MpegMotionVector* vectors, s32* a2, s32* out, s32 i, s32 mode, s32 a6, s32 a7, s32 s6, s32 s3, s32 fp)
{
    s32 v;
    s32* o;

    if (mode == 1) {
        if (a6 == 0 && s3 == 0) {
            v = ReadIpuBits(c, 1);
            out[i] = v;
            out[i + 2] = v;
        }
        MpegMotionVector* q = &vectors[i];
        ReadMotionVector(c, q, a2, a7, s6, s3, fp, 0);
        u32 x = q[0].x;
        u32 y = q[0].y;
        q[2].x = x;
        q[2].y = y;
    } else {
        v = ReadIpuBits(c, 1);
        out[i] = v;
        o = out + i;
        ReadMotionVector(c, &vectors[i], a2, a7, s6, s3, fp, 0);
        o[2] = ReadIpuBits(c, 1);
        ReadMotionVector(c, &vectors[i + 2], a2, a7, s6, s3, fp, 0);
    }
}

s16 DecodeIpuVariableLength(MpegDecoder* self, s32 mode);
s32 DecodeIpuMotionCode(MpegDecoder* self);

void ReadMotionVector(MpegDecoder* self, MpegMotionVector* n, s32* out, s32 p3, s32 p4, s32 want, s32 shift, s32 p7)
{
    s32 s0;
    s32 a3;

    s0 = DecodeIpuVariableLength(self, 2);
    if (p3 != 0 && s0 != 0) {
        a3 = ReadIpuBits(self, p3);
    } else {
        a3 = 0;
    }
    ApplyMotionVectorDelta(&n->x, p3, s0, a3, p7);
    if (want != 0) {
        out[0] = DecodeIpuMotionCode(self);
    }
    s0 = DecodeIpuVariableLength(self, 2);
    if (p4 != 0 && s0 != 0) {
        a3 = ReadIpuBits(self, p4);
    } else {
        a3 = 0;
    }
    if (shift != 0) {
        n->y = n->y >> 1;
    }
    ApplyMotionVectorDelta(&n->y, p4, s0, a3, p7);
    if (shift != 0) {
        n->y = n->y << 1;
    }
    if (want != 0) {
        out[1] = DecodeIpuMotionCode(self);
    }
}

u32 D_0027B040[10] = { 0x1, 0x1, 0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1 };

void SendIpuCommand(MpegDecoder* obj, u32 value)
{
    u32 index = value >> 28;
    volatile u32* setting = (volatile u32*)0x10002000;
    *setting = value;
    obj->windowInvalid = D_0027B040[index];
}


void WaitIpuCommandDone(MpegDecoder* self)
{
    s32 n = 0;
    if ((s32)(*(volatile u32*)0x10002010 & 0x80004000) == (s32)0x80000000) {
        do {
            s32 c = n;
            n = c + 1;
            if (c >= 0x1389) {
                RunMpegStallCallback(self->handle);
                n = 0;
            }
        } while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000);
    }
}

s64 WaitIpuCommandResult(MpegDecoder* p) {
    s32 i = 0;
    s64 v = *(volatile s64*)0x10002000;
    if (v < 0 && (*(volatile u32*)0x10002010 & 0x4000) == 0) {
        do {
            s32 old = i;
            i++;
            if (old >= 5001) {
                RunMpegStallCallback(p->handle);
                i = 0;
            }
            v = *(volatile s64*)0x10002000;
        } while (v < 0 && (*(volatile u32*)0x10002010 & 0x4000) == 0);
    }
    return v;
}

extern u32 D_0027B040[];


s16 DecodeIpuVariableLength(MpegDecoder* self, s32 mode)
{
    s32 m = 0;
    s32 n = 0;
    s32 cmd;
    s64 st;
    s64 hw;

    if ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000) {
        do {
            if (n++ >= 5001) {
                RunMpegStallCallback(self->handle);
                n = 0;
            }
        } while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000);
    }
    cmd = (mode << 26) | 0x30000000;
    *(volatile u32*)0x10002000 = cmd;
    self->windowInvalid = D_0027B040[cmd >> 28];
    st = *(volatile s64*)0x10002000;
    if (st < 0) {
        do {
            if (m++ >= 5001) {
                RunMpegStallCallback(self->handle);
                m = 0;
            }
            st = *(volatile s64*)0x10002000;
        } while (st < 0);
    }
    u32 cnt = *(volatile u32*)0x10002020;
    hw = *(s64*)0x10002030;
    self->window = (s32)hw;
    if (hw < 0) {
        self->windowBits = (-(cnt & 0x1F)) & 0x1F;
    } else {
        self->windowBits = 0x20;
    }
    self->errored = ((s32)st == 0);
    return (s16)st;
}


s64 WaitIpuCommandResult(MpegDecoder* obj);

extern u32 D_0027B040[];

s32 PeekIpuBits(MpegDecoder* obj, s32 a1)
{
    if (obj->windowInvalid != 0 || obj->windowBits < a1) {
        s32 cnt = 0;
        while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000) {
            if (cnt++ > 0x1388) {
                RunMpegStallCallback(obj->handle);
                cnt = 0;
            }
        }
        *(volatile u32*)0x10002000 = 0x40000000;
        obj->windowInvalid = D_0027B040[4];
        obj->window = WaitIpuCommandResult(obj);
        obj->windowBits = 0x20;
    }
    return (u32)obj->window >> (32 - a1);
}

extern u32 D_0027B040[];
extern s64 WaitIpuCommandResult(MpegDecoder* c, u32* v);

void SkipIpuBits(MpegDecoder* s0, u32 s1)
{
    s32 cnt = 0;
    u32 v;
    u32* p;

    while ((*(volatile u32*)0x10002010 & 0x80004000u) == 0x80000000u) {
        if (cnt++ > 0x1388) {
            RunMpegStallCallback(s0->handle);
            cnt = 0;
        }
    }
    v = s1 | 0x40000000u;
    *(volatile u32*)0x10002000 = v;
    p = &D_0027B040[v >> 28];
    s0->windowInvalid = *p;
    s0->window = WaitIpuCommandResult(s0, p);
    s0->windowBits = 0x20;
}


s64 WaitIpuCommandResult(MpegDecoder* obj);

extern u32 D_0027B040[];

struct IpuCommand {
    static void Send(MpegDecoder* obj, u32 cmd)
    {
        *(volatile u32*)0x10002000 = cmd;
        obj->windowInvalid = D_0027B040[cmd >> 28];
        obj->window = WaitIpuCommandResult(obj);
    }
};

u32 ReadIpuBits(MpegDecoder* obj, s32 a1)
{
    s32 cnt = 0;
    u32 v;
    while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000) {
        if (cnt++ > 0x1388) {
            RunMpegStallCallback(obj->handle);
            cnt = 0;
        }
    }
    if (obj->windowInvalid != 0 || obj->windowBits < a1) {
        IpuCommand::Send(obj, 0x40000000);
    }
    v = (u32)obj->window >> (32 - a1);
    obj->windowBits = 0x20;
    IpuCommand::Send(obj, a1 | 0x40000000);
    return v;
}

void WaitIpuCommandDone(MpegDecoder* self); // stays void: retail returns a value, but declared so func_0020DF10 and func_0020F708 differs in registers
void SkipIpuBits(MpegDecoder* s0, u32 s1);
s32 PeekIpuBits(MpegDecoder* obj, s32 a1);
void FindNextStartCode(MpegDecoder* self)
{
    WaitIpuCommandDone(self);
    volatile u32* reg = (volatile u32*)0x10002020;
    s32 mask = -(*reg & 7) & 7;
    if (mask != 0) {
        SkipIpuBits(self, mask);
    }
    while (PeekIpuBits(self, 0x18) != 1) {
        SkipIpuBits(self, 8);
    }
}


u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void SkipIpuBits(MpegDecoder* s0, u32 s1);
void SkipExtraInformation(MpegDecoder* self);

s32 ReadSliceQuantiser(MpegDecoder* self)
{
    self->quantiserScale = ReadIpuBits(self, 5);
    if (ReadIpuBits(self, 1) != 0) {
        ReadIpuBits(self, 1);
        SkipIpuBits(self, 7);
        SkipExtraInformation(self);
    }
    return 0;
}

void FindNextStartCode(MpegDecoder* self);
u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void ReadSequenceHeader(MpegDecoder* d);
void ReadGroupOfPicturesHeader(MpegDecoder* self);
void ReadPictureHeader(MpegDecoder* self);

s32 ParseMpegHeaders(MpegDecoder* self)
{
    u32 v;
    for (;;) {
        FindNextStartCode(self);
        v = ReadIpuBits(self, 0x20);
        if (v == 0x1B3) goto c1B3;
        if (v < 0x1B4) {
            if (v == 0x100) goto c100;
            continue;
        }
        if (v == 0x1B7) return 0;
        if (v == 0x1B8) goto c1B8;
        continue;
    c1B3:
        ReadSequenceHeader(self);
        continue;
    c1B8:
        ReadGroupOfPicturesHeader(self);
        continue;
    c100:
        {
            MpegPositionQuery loc;
            ReadPictureHeader(self);
            loc.kind = 5;
            loc.pts = -1;
            loc.dts = -1;
            RunMpegCallback(self->handle, &loc);
            self->pts = loc.pts;
            self->dts = loc.dts;
            return self->pictureType;
        }
    }
}

u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void SkipExtraInformation(MpegDecoder* self);
void ReadExtensionsAndUserData(MpegDecoder* self);
s32 UpdatePictureOrder(MpegDecoder* self, s32 a1);

void ReadPictureHeader(MpegDecoder* self)
{
    s32 first = ReadIpuBits(self, 10);
    self->pictureType = ReadIpuBits(self, 3);
    ReadIpuBits(self, 16);
    if ((u32)(self->pictureType - 2) < 2) {
        self->fullPelForward = ReadIpuBits(self, 1);
        self->forwardFCode = ReadIpuBits(self, 3);
    }
    if (self->pictureType == 3) {
        self->fullPelBackward = ReadIpuBits(self, 1);
        self->backwardFCode = ReadIpuBits(self, 3);
    }
    SkipExtraInformation(self);
    ReadExtensionsAndUserData(self);
    UpdatePictureOrder(self, first);
}

// The handlers of the extensions are copied out of their table as a packed head of five 8-byte
// words and the last one, as the original's struct copy was.
typedef void (*ExtensionHandlerFn)(MpegDecoder* self);

struct __attribute__((packed)) ExtensionHandlerHead {
    u64 a[5];
};

struct ExtensionHandlerCopy {
    struct ExtensionHandlerHead p;
    ExtensionHandlerFn last;
};

union ExtensionHandlerTable {
    struct ExtensionHandlerCopy t;
    ExtensionHandlerFn fn[11];
};

void FindNextStartCode(MpegDecoder* self);
void SkipIpuBits(MpegDecoder* s0, u32 s1);
u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
s32 PeekIpuBits(MpegDecoder* obj, s32 a1);

// An entry of the table of extension handlers below.
typedef void (*Fn_Table)();
void ReadPictureCodingExtension(MpegDecoder* c);
void ReadQuantiserMatrixExtension(MpegDecoder *self);
void ReadPictureDisplayExtension(MpegDecoder* self);
void ReadCopyrightExtension(MpegDecoder* self);
// The handlers of the extensions by their 4-bit id, the sequence's in src/lib/mpeg_decoder.cpp.
void ReadSequenceExtension(MpegDecoder *self);
void ReadSequenceDisplayExtension(MpegDecoder* self);
void RejectSequenceScalableExtension(MpegDecoder* self);
void RejectUnknownExtension(MpegDecoder* self);
void RejectSpatialScalableExtension(MpegDecoder* self);
void RejectTemporalScalableExtension(MpegDecoder* self);
extern const Fn_Table D_00250430[12] = { (Fn_Table)RejectUnknownExtension, (Fn_Table)ReadSequenceExtension, (Fn_Table)ReadSequenceDisplayExtension, (Fn_Table)ReadQuantiserMatrixExtension, (Fn_Table)ReadCopyrightExtension, (Fn_Table)RejectSequenceScalableExtension, (Fn_Table)RejectUnknownExtension, (Fn_Table)ReadPictureDisplayExtension, (Fn_Table)ReadPictureCodingExtension, (Fn_Table)RejectSpatialScalableExtension, (Fn_Table)RejectTemporalScalableExtension, 0 };

void ReadExtensionsAndUserData(MpegDecoder* self)
{
    s32 kA = 0x1B2;
    union ExtensionHandlerTable t;
    t.t = *(struct ExtensionHandlerCopy*)((u8*)D_00250430);
    s32 kB = 0x1B5;
    s32 r;

    FindNextStartCode(self);
    u32 limit = 10;
    while ((r = PeekIpuBits(self, 0x20)) == kB || r == kA) {
        if (r == kB) {
            SkipIpuBits(self, 0x20);
            u32 idx = (u32)ReadIpuBits(self, 4);
            if (limit < idx) {
                idx = 0;
            }
            t.fn[idx](self);
            FindNextStartCode(self);
        } else {
            SkipIpuBits(self, 0x20);
            FindNextStartCode(self);
        }
    }
}

u32 ReadIpuBits(MpegDecoder* obj, s32 a1);

void ReadPictureCodingExtension(MpegDecoder* c)
{
    c->fCode[0] = ReadIpuBits(c, 4);
    c->fCode[1] = ReadIpuBits(c, 4);
    c->fCode[2] = ReadIpuBits(c, 4);
    c->fCode[3] = ReadIpuBits(c, 4);
    *(u32*)0x10002010 = (*(u32*)0x10002010 & 0xFFFCFFFF) | (ReadIpuBits(c, 2) << 16);
    s32 v = ReadIpuBits(c, 2);
    c->pictureStructure = v;
    if (c->firstStructure == 0) c->firstStructure = v;
    c->topFieldFirst = ReadIpuBits(c, 1);
    c->framePredFrameDct = ReadIpuBits(c, 1);
    c->concealmentMotionVectors = ReadIpuBits(c, 1);
    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xFFBFFFFF) | (ReadIpuBits(c, 1) << 22);
    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xFFDFFFFF) | (ReadIpuBits(c, 1) << 21);
    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xFFEFFFFF) | (ReadIpuBits(c, 1) << 20);
    c->repeatFirstField = ReadIpuBits(c, 1);
    ReadIpuBits(c, 1);
    c->progressiveFrame = ReadIpuBits(c, 1);
    if (ReadIpuBits(c, 1) == 0) return;
    ReadIpuBits(c, 1);
    ReadIpuBits(c, 3);
    ReadIpuBits(c, 1);
    ReadIpuBits(c, 7);
    ReadIpuBits(c, 8);
}

u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void SkipIpuBits(MpegDecoder* s0, u32 s1);

void SkipExtraInformation(MpegDecoder* self)
{
    while (ReadIpuBits(self, 1))
        SkipIpuBits(self, 8);
}


s32 UpdatePictureOrder(MpegDecoder* self, s32 a1)
{
    s32 lim = 0;
    s32 neg = 0;
    if (self->pictureType != 3 && a1 != 0) {
        if (a1 < 0) {
            neg = (u32)self->gopStart < 1;
        }
        self->gopStart = 0;
        lim = a1;
    }
    s32 v1 = self->orderBase + a1;
    self->pictureOrder = v1;
    if (neg && lim >= a1) {
        self->pictureOrder = v1 + 0x400;
    }
    s32 v0 = self->maxOrder;
    if (v0 < self->pictureOrder) {
        v0 = self->pictureOrder;
    }
    self->maxOrder = v0;
    return v0;
}

u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void ReadExtensionsAndUserData(MpegDecoder* self);

void ReadGroupOfPicturesHeader(MpegDecoder* self)
{
    self->fE8 = 0;
    self->orderBase = self->maxOrder + 1;
    self->gopStart = 1;
    ReadIpuBits(self, 1);
    ReadIpuBits(self, 5);
    ReadIpuBits(self, 6);
    ReadIpuBits(self, 1);
    ReadIpuBits(self, 6);
    ReadIpuBits(self, 6);
    self->closedGop = ReadIpuBits(self, 1);
    self->brokenLink = ReadIpuBits(self, 1);
    ReadExtensionsAndUserData(self);
}


u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void WaitIpuCommandDone(MpegDecoder *self);
void SendIpuCommand(MpegDecoder* obj, u32 value);
void ReportMpegError(MpegDecoder* self, const char* value);

void ReadQuantiserMatrixExtension(MpegDecoder *self)
{
    s32 v;

    v = ReadIpuBits(self, 1);
    self->loadIntraMatrix = v;
    if (v != 0) {
        WaitIpuCommandDone(self);
        SendIpuCommand(self, 0x50000000);
        WaitIpuCommandDone(self);
    }
    v = ReadIpuBits(self, 1);
    self->loadNonIntraMatrix = v;
    if (v != 0) {
        WaitIpuCommandDone(self);
        SendIpuCommand(self, 0x58000000);
        WaitIpuCommandDone(self);
    }
    v = ReadIpuBits(self, 1);
    if (v != 0) {
        ReportMpegError(self, "load_chroma_intra_quantizer_matrix == 1");
    }
    v = ReadIpuBits(self, 1);
    if (v == 0) {
        return;
    }
    ReportMpegError(self, "load_chroma_non_intra_quantizer_matrix == 1");
}

u32 ReadIpuBits(MpegDecoder* obj, s32 a1);

void ReadPictureDisplayExtension(MpegDecoder* self)
{
    s32 n;
    s32 i;
    if (self->progressiveSequence != 0) {
        if (self->repeatFirstField != 0) n = (self->topFieldFirst != 0) ? 3 : 2;
        else n = 1;
    } else if (self->pictureStructure != 3) {
        n = 1;
    } else {
        n = (self->repeatFirstField != 0) ? 3 : 2;
    }
    for (i = 0; i < n; i++) {
        self->centreHorizontal[i] = ReadIpuBits(self, 0x10);
        ReadIpuBits(self, 1);
        self->centreVertical[i] = ReadIpuBits(self, 0x10);
        ReadIpuBits(self, 1);
    }
}

u32 ReadIpuBits(MpegDecoder* obj, s32 a1);

void ReadCopyrightExtension(MpegDecoder* self)
{
    ReadIpuBits(self, 1);
    ReadIpuBits(self, 8);
    ReadIpuBits(self, 1);
    ReadIpuBits(self, 7);
    ReadIpuBits(self, 1);
    ReadIpuBits(self, 0x14);
    ReadIpuBits(self, 1);
    ReadIpuBits(self, 0x16);
    ReadIpuBits(self, 1);
    ReadIpuBits(self, 0x16);
}


void ReportMpegError(MpegDecoder* self, const char* value);
s32 DecodeAllMacroblocks(MpegDecoder* c);

s32 DecodePictureData(MpegDecoder* self)
{
    MpegPicture* s1;
    s32 v;
    s32 mode = self->pictureStructure;
    if (mode == 3 && self->secondField != 0) {
        ReportMpegError(self, (const char*)((u8*)"odd number of field pictures"));
        self->secondField = 0;
        mode = self->pictureStructure;
    }
    switch (mode) {
    case 3:
        s1 = self->pictures[2];
        break;
    case 1:
        s1 = self->pictures[6];
        break;
    case 2:
        s1 = self->pictures[10];
        break;
    default:
        s1 = self->pictures[2];
        ReportMpegError(self, (const char*)((u8*)"unknown picture sutructure"));
        break;
    }
    v = DecodeAllMacroblocks(self);
    if (v != 0) {
        s1->decoded = 1;
    }
    return v;
}

void OutputFramePicture(MpegDecoder* c, MpegPicture* s, s32 count);
void OutputFieldPicturePair(MpegDecoder* c, MpegPicture* a, MpegPicture* b, s32 count);

void OutputPictureIfDecoded(MpegDecoder* self, s32 count, s32 flag)
{
    s32 n = count;
    if (flag != 0) {
        if (self->pictureStructure == 3) {
            MpegPicture* x;
            if (self->pictureType == 3) {
                x = self->pictures[3];
            } else {
                x = self->pictures[0];
            }
            OutputFramePicture(self, x, n - 1);
        } else {
            MpegPicture* x;
            MpegPicture* y;
            if (self->pictureType == 3) {
                x = self->pictures[7];
                y = self->pictures[11];
            } else {
                x = self->pictures[4];
                y = self->pictures[8];
            }
            n = n - 1;
            OutputFieldPicturePair(self, x, y, n);
        }
    }
    if (self->fF8 == 1) {
        self->fF8 = 2;
    }
}



s32 SelectPictureBuffer(MpegDecoder* p, s32 flag)
{
    MpegPicture* o = 0;
    s32 ok = 0;
    s32 lim = p->pictureStructure == 3 ? 2 : 4;

    if (p->pictureType == 3) {
        p->pictures[2] = p->pictures[3];
        p->pictures[6] = p->pictures[7];
        p->pictures[10] = p->pictures[11];
        if (p->pictureCount[0] + p->pictureCount[1] >= lim) {
            p->fE8 = 0;
            p->brokenLink = 0;
            p->closedGop = 0;
        }
        if ((p->fE8 || p->brokenLink) && !p->closedGop) {
            p->pictures[0]->decoded = 0;
            p->pictures[4]->decoded = 0;
            p->pictures[8]->decoded = 0;
        }
        p->fE8 = 0;
        p->brokenLink = 0;
        if (p->pictureStructure == 3) {
            if ((p->pictures[0]->decoded == 1 || p->closedGop) && p->pictures[1]->decoded == 1) ok = 1;
        } else {
            if (((p->pictures[4]->decoded == 1 && p->pictures[8]->decoded == 1) || p->closedGop) && p->pictures[5]->decoded == 1 && p->pictures[9]->decoded == 1) ok = 1;
        }
    } else {
        if (flag == 0) {
            MpegPicture* t;
            t = p->pictures[0]; p->pictures[0] = p->pictures[1]; p->pictures[1] = t;
            t = p->pictures[4]; p->pictures[4] = p->pictures[5]; p->pictures[5] = t;
            t = p->pictures[8]; p->pictures[8] = p->pictures[9]; p->pictures[9] = t;
        }
        p->pictures[2] = p->pictures[1];
        p->pictures[6] = p->pictures[5];
        p->pictures[10] = p->pictures[9];
        if (p->pictureStructure == 3) {
            if (p->pictureType != 2 || p->pictures[0]->decoded == 1) ok = 1;
        } else {
            MpegPicture* x = p->pictureStructure == 1 ? p->pictures[9] : p->pictures[5];
            if (p->pictureType != 2) ok = 1;
            else if ((flag && x->decoded == 1) || (p->pictures[4]->decoded == 1 && p->pictures[8]->decoded == 1)) ok = 1;
        }
    }

    switch (p->pictureStructure) {
    case 2: o = p->pictures[10]; break;
    case 1: o = p->pictures[6]; break;
    case 3: o = p->pictures[2]; break;
    }
    o->decoded = 0;
    o->pts = p->pts;
    o->pictureType = p->pictureType;
    o->dts = p->dts;
    o->pictureStructure = p->pictureStructure;
    o->progressiveSequence = p->progressiveSequence;
    o->progressiveFrame = p->progressiveFrame;
    o->topFieldFirst = p->topFieldFirst;
    o->repeatFirstField = p->repeatFirstField;
    o->centreHorizontal[0] = p->centreHorizontal[0];
    o->centreHorizontal[1] = p->centreHorizontal[1];
    o->centreHorizontal[2] = p->centreHorizontal[2];
    o->centreVertical[0] = p->centreVertical[0];
    o->centreVertical[1] = p->centreVertical[1];
    o->centreVertical[2] = p->centreVertical[2];
    o->displayWidth = p->displayWidth;
    o->displayHeight = p->displayHeight;
    return ok;
}

s32 FormatToString(char* dst, const char* fmt, ...);
void ReportMpegError(MpegDecoder* self, const char* value);

s32 CheckPictureBufferSize(MpegDecoder *self, MpegPicture *rec) {
    char buf[0x100];
    s32 flag;
    if (self->outputHeight != 0)
        flag = self->outputWidth >= rec->width && self->outputHeight >= rec->height;
    else
        flag = self->outputMacroblocks >= rec->mbWidth * rec->mbHeight;
    if (flag == 0) {
        FormatToString(buf, "Too small buffer size for %dx%d picture\n", rec->width, rec->height);
        ReportMpegError(self, buf);
    }
    return flag;
}

void CopyPictureThroughScratchpad(MpegDecoder* c, MpegPicture* pic)
{
    s32 passes;
    u32 src = pic->address & 0x0FFFFFFF;
    u32 dst = c->outputBuffer & 0x0FFFFFFF;
    s32 srcStride;
    s32 dstStride;
    s32 qwc;
    s32 pass;
    s32 i;
    u32 to;

    if (c->pictureStructure == 3 || c->outputHeight == 0) {
        srcStride = pic->mbHeight * 0x180;
        qwc = srcStride >> 4;
        if (c->outputHeight != 0)
            dstStride = (c->outputHeight >> 4) * 0x180;
        else
            dstStride = srcStride;
        passes = 1;
    } else {
        dstStride = (c->outputHeight >> 4) * 0xC0;
        srcStride = (pic->mbHeight >> 1) * 0x180;
        passes = 2;
        qwc = srcStride >> 4;
    }
    for (pass = 0; pass < passes; pass++) {
        to = dst;
        for (i = 0; i < pic->mbWidth; i++) {
            DisableInterrupts();
            *(volatile u32*)0x1000D480 = 0;
            *(volatile u32*)0x1000D410 = src;
            *(volatile u32*)0x1000D420 = qwc;
            *(volatile u32*)0x1000D400 = 0x101;
            EnableInterrupts();
            while (*(volatile u32*)0x1000D400 & 0x100) {
            }
            DisableInterrupts();
            *(volatile u32*)0x1000D080 = 0;
            *(volatile u32*)0x1000D010 = to;
            *(volatile u32*)0x1000D020 = qwc;
            *(volatile u32*)0x1000D000 = 0x100;
            EnableInterrupts();
            while (*(volatile u32*)0x1000D000 & 0x100) {
            }
            while (*(volatile u32*)0x1000D020 != 0) {
            }
            to += dstStride;
            src += srcStride;
        }
        dst += c->outputMacroblocks * 0xC0;
    }
}


s32 SignalPictureReady(MpegDecoder* obj)
{
    s32 value;
    s32 result = 1;
    if (obj->phase == 2) {
        goto done;
    }
    value = obj->pictureNumber;
    obj->phase = 2;
    obj->firstPictureNumber = value;
done:
    obj->pictureReady = result;
    return result;
}

extern "C" s64 MultiplySigned64(s64 u, s64 v);

void FillPictureOutputInfo(MpegDecoder* self, MpegPicture* node, s64* out1, s64* out3, s64* out4)
{
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s6;
    s32 s7;
    s64 v;
    s64 t88;

    if (self->f70 != 0) {
        v = node->pts;
        if (v >= 0) {
            *out1 = v;
        } else {
            s7 = self->f80;
            if (s7 < 0) {
                *out1 = v;
            } else {
                t88 = self->f88;
                s0 = (s32)t88;
                s2 = s0 & 1;
                v = MultiplySigned64(s2, self->f78 & 1);
                s6 = self->f90;
                v = MultiplySigned64(v, s6 & 1);
                s1 = (s32)v;
                *out1 = (s64)(s7 + ((s32)(MultiplySigned64(self->f78, s0) >> 1) + s1));
                if (MultiplySigned64(s2, self->f78 & 1)) {
                    self->f90 = s6 + 1;
                }
            }
        }
    } else {
        *out1 = node->pts;
    }
    if (self->fF8 == 2) {
        if (self->fF0 >= 0) {
            *out1 = self->fF0;
            self->fF8 = 0;
            self->fF0 = -1;
        }
    }
    *out3 = node->dts;
    *out4 = ((s64)node->progressiveSequence << 8) | (node->pictureType | ((s64)node->progressiveFrame << 7) | ((s64)node->topFieldFirst << 6) | ((s64)node->repeatFirstField << 5) | ((s64)node->pictureStructure << 3));
}

// A table of 16 words by a 4-bit code, which func_00210970 reads.
u32 D_0027B068[16] = { 0x2, 0x0, 0x2, 0x0, 0x2, 0x3, 0x2, 0x3, 0x0, 0x0, 0x0, 0x0, 0x2, 0x4, 0x0, 0x6 };
u32 D_0027B0A8[2] = { 0 };

void FillPictureOutputInfo(MpegDecoder* self, MpegPicture* node, s64* out1, s64* out3, s64* out4);
s32 CheckPictureBufferSize(MpegDecoder *self, MpegPicture *rec);
void ConvertPictureColours(MpegDecoder* self, MpegPicture* d);
void CopyPictureThroughScratchpad(MpegDecoder* c, MpegPicture* pic);
s32 SignalPictureReady(MpegDecoder* obj);

void OutputFramePicture(MpegDecoder* c, MpegPicture* s, s32 count)
{
    FillPictureOutputInfo(c, s, &c->handle->info[0].pts, &c->handle->info[0].dts, &c->handle->info[0].flags);
    MpegHandle* p = c->handle;
    u32 idx = (u32)(p->info[0].flags >> 5) & 0xF;
    c->f80 = (s32)p->info[0].pts;
    c->f88 = D_0027B068[idx];
    c->outputDisplayWidth = s->displayWidth;
    c->outputDisplayHeight = s->displayHeight;
    c->outputCentreHorizontal[0] = s->centreHorizontal[0];
    c->outputCentreHorizontal[1] = s->centreHorizontal[1];
    c->outputCentreHorizontal[2] = s->centreHorizontal[2];
    c->outputCentreVertical[0] = s->centreVertical[0];
    c->outputCentreVertical[1] = s->centreVertical[1];
    c->outputCentreVertical[2] = s->centreVertical[2];
    if (CheckPictureBufferSize(c, s)) {
        if (s->decoded == 1) {
            if (c->convertColours) {
                ConvertPictureColours(c, s);
            } else {
                CopyPictureThroughScratchpad(c, s);
            }
            SignalPictureReady(c);
        }
    }
}

void OutputFieldPicturePair(MpegDecoder* c, MpegPicture* a, MpegPicture* b, s32 count)
{
    MpegPicture* s3;
    MpegPicture* s4;
    s32 s6 = 0;
    if (c->pictureStructure == 2) {
        s3 = a;
        s4 = b;
        s6 = 0x40;
    } else {
        s3 = b;
        s4 = a;
    }
    (void)FillPictureOutputInfo(c, s3, &c->handle->info[0].pts, &c->handle->info[0].dts, &c->handle->info[0].flags);
    c->f80 = (s32)c->handle->info[0].pts;
    c->f88 = 1;
    (void)FillPictureOutputInfo(c, s4, &c->handle->info[1].pts, &c->handle->info[1].dts, &c->handle->info[1].flags);
    c->f80 = (s32)c->handle->info[1].pts;
    c->f88 = 1;
    MpegHandle* p = c->handle;
    u64 v0 = p->info[0].flags | (s64)s6;
    s32 a2 = s3->displayWidth;
    u64 v1 = p->info[1].flags | (s64)s6;
    c->outputDisplayWidth = a2;
    p->info[0].flags = v0;
    s32 a2b = s3->displayHeight;
    p->info[1].flags = v1;
    c->outputDisplayHeight = a2b;
    c->outputCentreHorizontal[0] = s3->centreHorizontal[0];
    c->outputCentreHorizontal[1] = s4->centreHorizontal[1];
    c->outputCentreVertical[0] = s3->centreVertical[0];
    c->outputCentreVertical[1] = s4->centreVertical[1];
    if (CheckPictureBufferSize(c, a)) {
        if (a->decoded == 1 && b->decoded == 1) {
            a->mbHeight <<= 1;
            if (c->convertColours) {
                ConvertPictureColours(c, a);
            } else {
                CopyPictureThroughScratchpad(c, a);
            }
            a->mbHeight >>= 1;
            SignalPictureReady(c);
        }
    }

}

// The DMA chain func_00210C38 builds, which only it reads.
static u8 D_0062C340[0x200];

extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);

// The decoder's two macroblocks as the DMA chain reads them: the addresses their predictions fetch
// from as numbers, where MpegMacroblock holds them as pointers (a pointer is what the prediction's
// code wants, and a number what the chain's).
struct MacroblockAddresses {
    u32 work;               // 0x00
    u8 pad04[4];
    u32 src0[4];            // 0x08
    u32 src1[4];            // 0x18
    u8 pad28[0x12C - 0x28];
    s32 count;              // 0x12C
    u8 pad130[0x140 - 0x130];
};

struct ChainView {
    u8 pad000[0x590];
    MacroblockAddresses macroblock[2];  // 0x590
    u8 pad810[0x810 - 0x590 - 2 * 0x140];
    s32 current;            // 0x810
};

// Builds the DMA chain of the current picture's blocks in uncached memory (two REF tags a
// block, the last REFE) and starts it on channel 9 (to the scratchpad): its address, its tag
// and the channel's control word, with interrupts disabled.
void StartBlockChainToScratchpad(MpegDecoder* decoder)
{
    ChainView* self = (ChainView*)decoder;
    u64* tag = (u64*)(((u32)D_0062C340 & 0x0FFFFFFF) | 0x20000000);
    s32 n = self->macroblock[self->current].count;
    for (s32 i = 0; i < n; i++) {
        u64 first = (u64)(self->macroblock[self->current].src0[i] & 0x0FFFFFFF) << 32;
        u64 second = (u64)(self->macroblock[self->current].src1[i] & 0x0FFFFFFF) << 32;
        u64 id = (i == n - 1) ? 0 : 3;
        tag[0] = first | 0x30000030;
        tag[2] = second | (id << 28) | 0x30;
        tag += 4;
    }
    DisableInterrupts();
    Sync();
    *(volatile u32*)0x1000D480 = self->macroblock[self->current].work;
    *(volatile u32*)0x1000D430 = (u32)D_0062C340;
    *(volatile u32*)0x1000D420 = 0;
    *(volatile u32*)0x1000D400 = 0x105;
    EnableInterrupts();
}

void StartIpuOutputDma(u32 a, s32 b)
{
    DisableInterrupts();
    *(volatile u32*)0x1000B010 = (a & 0xFFFFFFF) | 0x80000000;
    *(volatile u32*)0x1000B020 = b >> 4;
    *(volatile u32*)0x1000B000 = 0x100;
    EnableInterrupts();
}


void SendIpuCommand(MpegDecoder* obj, u32 value);

void ConvertSmallPictureColours(MpegDecoder* self, u32 a1, u32 a2)
{

    MpegSignal tmp;
    while (*(volatile s32*)0x10002010 < 0) { }
    (void)DisableInterrupts();
    *(volatile u32*)0x1000B010 = a1 & 0x0FFFFFFF;
    *(volatile u32*)0x1000B020 = a2 << 6;
    *(volatile u32*)0x1000B000 = 0x100;
    (void)EnableInterrupts();
    SendIpuCommand(self, a2 | 0x70000000);
    tmp.kind = 4;
    RunMpegCallback(self->handle, &tmp);
    while ((*(volatile u32*)0x1000B000 >> 8) & 1) { }
    while (*(volatile s32*)0x10002010 < 0) { }
}

// The record of a decode's input transfer in chunks of 0x3FF quadwords (func_00211090 fills it).
struct ColourOutputTransfer {
    volatile s32 done;      // 0x00: the chunks done
    s32 error;              // 0x04: set when the IPU was still busy
    s32 size;               // 0x08: the quadwords left
    s32 addr;               // 0x0C: the next chunk's address
    s32 total;              // 0x10: the chunks in all
};

// The DMA handler of the IPU's input channel: after each chunk, starts the next one (the last
// with what is left), or marks an error when the channel was still busy; then ends the handler.
s32 ContinueColourConversionOutput(s32 channel, void* arg)
{
    ColourOutputTransfer* x = (ColourOutputTransfer*)arg;
    *(volatile u32*)0x1000E010 = 8;
    x->done++;
    if (*(volatile u32*)0x1000B020 != 0 || (*(volatile u32*)0x1000B000 & 0x100)) {
        x->error = 1;
        return 0;
    }
    s32 last = x->total - 1;
    if (x->done < last) {
        DisableInterrupts();
        *(volatile u32*)0x1000B010 = x->addr;
        *(volatile u32*)0x1000B020 = 0xFFC0;
        *(volatile u32*)0x1000B000 = 0x100;
        EnableInterrupts();
        *(volatile u32*)0x10002000 = 0x700003FF;
        x->addr = (x->addr + 0xFFC00) & 0xFFFFFFF;
    } else if (x->done == last) {
        x->size = x->size - x->done * 0x3FF;
        DisableInterrupts();
        *(volatile u32*)0x1000B010 = x->addr;
        *(volatile u32*)0x1000B020 = x->size << 6;
        *(volatile u32*)0x1000B000 = 0x100;
        EnableInterrupts();
        *(volatile u32*)0x10002000 = x->size | 0x70000000;
    }
    SyncAndEnableInterrupts();
    return 0;
}

s32 AddDmaHandlerAlt(s32 channel, s32 (*handler)(s32, void*), s32 next, void* arg);
s32 RemoveDmaHandler(s32 channel, s32 id);
s32 DisableDmaInterrupt(s32 channel);
s32 EnableDmaInterrupt(s32 channel);
extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);
s32 ContinueColourConversionOutput(s32 channel, void* arg);
void ReportMpegError(MpegDecoder* self, const char* value);

void ConvertLargePictureColours(MpegDecoder* self, s32 addr, s32 size)
{
    s32 chunk = 0x3FF;
    MpegSignal msg;
    ColourOutputTransfer xfer;
    xfer.total = size / chunk + 1;
    xfer.addr = (addr + 0xFFC00) & 0xFFFFFFF;
    xfer.size = size;
    xfer.error = 0;
    xfer.done = 0;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    s32 id = AddDmaHandlerAlt(3, ContinueColourConversionOutput, 0, &xfer);
    *(volatile u32*)0x1000E010 = 8;
    EnableDmaInterrupt(3);
    DisableInterrupts();
    *(volatile u32*)0x1000B010 = addr & 0xFFFFFFF;
    *(volatile u32*)0x1000B020 = chunk << 6;
    *(volatile u32*)0x1000B000 = 0x100;
    EnableInterrupts();
    *(volatile u32*)0x10002000 = chunk | 0x70000000;
    msg.kind = 4;
    RunMpegCallback(self->handle, &msg);
    while (xfer.done < xfer.total) {
    }
    if (xfer.error != 0) {
        ReportMpegError(self, (const char*)((u8*)"CSC handler error\n"));
    }
    while (*(volatile s32*)0x10002010 < 0) {
    }
    DisableDmaInterrupt(3);
    RemoveDmaHandler(3, id);
}

// What is left of the colour conversion's input to send: its size and where it continues.
struct PendingInput { u32 size; u32 addr; };

extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);

s32 ContinueColourConversionInput(s32 unused, PendingInput* p)
{
    *(volatile u32*)0x1000E010 = 0x10;
    if (p->size == 0) {
        return 1;
    }
    u32 max = 0xFFFF;
    if (p->size > max) {
        (void)DisableInterrupts();
        *(volatile u32*)0x1000B410 = p->addr;
        *(volatile u32*)0x1000B420 = max;
        *(volatile u32*)0x1000B400 = 0x101;
        (void)EnableInterrupts();
        p->size = p->size - max;
        p->addr = (p->addr + 0xFFFF0) & 0xFFFFFFF;
    } else {
        (void)DisableInterrupts();
        *(volatile u32*)0x1000B410 = p->addr;
        *(volatile u32*)0x1000B420 = p->size;
        *(volatile u32*)0x1000B400 = 0x101;
        (void)EnableInterrupts();
        p->size = 0;
    }
    return 0;
}

extern u8 D_00278000[], D_00278050[], D_00278644[], D_002789DC[], D_00278A7C[], D_00278E88[];


s32 AddDmaHandlerAlt(s32 channel, s32 (*handler)(s32, void*), s32 next, void* arg);
s32 RemoveDmaHandler(s32 channel, s32 id);
s32 DisableDmaInterrupt(s32 channel);
s32 EnableDmaInterrupt(s32 channel);
extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);
s32 ContinueColourConversionInput(s32 unused, PendingInput* p);
void SendIpuCommand(MpegDecoder* obj, u32 value);
void ConvertSmallPictureColours(MpegDecoder* self, u32 a1, u32 a2);
void ConvertLargePictureColours(MpegDecoder* self, s32 addr, s32 size);

void ConvertPictureColours(MpegDecoder* self, MpegPicture* d)
{
    MpegSignal msg;
    PendingInput xfer;
    s32 count = d->mbWidth * d->mbHeight;
    msg.kind = 2;
    RunMpegCallback(self->handle, &msg);
    if ((*(volatile u32*)0x10002010 & 0x4000) != 0) {
        *(volatile u32*)0x10002010 = 0x40000000;
    }
    s32 small = count < 0x400;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    SendIpuCommand(self, 0);
    u32 addr = d->address;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    u32 chunk = 0xFFFF;
    xfer.size = count * 0x18;
    xfer.addr = addr & 0xFFFFFFF;
    if (xfer.size > chunk) {
        s32 id = AddDmaHandlerAlt(4, ContinueColourConversionInput, 0, &xfer);
        *(volatile u32*)0x1000E010 = 0x10;
        EnableDmaInterrupt(4);
        (void)DisableInterrupts();
        *(volatile u32*)0x1000B410 = xfer.addr;
        *(volatile u32*)0x1000B420 = chunk;
        *(volatile u32*)0x1000B400 = 0x101;
        (void)EnableInterrupts();
        xfer.addr = (xfer.addr + 0xFFFF0) & 0xFFFFFFF;
        xfer.size = xfer.size - chunk;
        if (small) {
            ConvertSmallPictureColours(self, self->outputBuffer, count);
        } else {
            ConvertLargePictureColours(self, self->outputBuffer, count);
        }
        DisableDmaInterrupt(4);
        RemoveDmaHandler(4, id);
    } else {
        (void)DisableInterrupts();
        *(volatile u32*)0x1000B410 = d->address & 0xFFFFFFF;
        *(volatile u32*)0x1000B420 = xfer.size;
        *(volatile u32*)0x1000B400 = 0x101;
        (void)EnableInterrupts();
        xfer.size = 0;
        if (small) {
            ConvertSmallPictureColours(self, self->outputBuffer, count);
        } else {
            ConvertLargePictureColours(self, self->outputBuffer, count);
        }
    }
    msg.kind = 3;
    RunMpegCallback(self->handle, &msg);
}
