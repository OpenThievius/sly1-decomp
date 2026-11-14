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
struct Node_20C0A8;

struct Self_20B978;

struct Dec_20B9F0;
struct Q_0020B1E0;
struct Self_20B978;


void SetIpuMpeg1Mode(u32 value)
{
    u32* setting = (u32*)0x10002010;
    u32 result = (*setting & 0xFF7FFFFFu) | (value << 23);
    *setting = result;
}

struct Msg_20DF10 { s32 cmd; s32 pad[7]; };

struct IpuWaitView;
void WaitIpuCommandDone(MpegDecoder* o); // stays void: retail returns a value, but declared so func_0020DF10 and func_0020F708 differs in registers
s32 RunMpegCallback(MpegHandle* q, Msg_20DF10* m);
void ReportMpegError(Self_20B978* self, const char* value);
extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);

s32 WaitIpuDecodeDone(MpegDecoder* o)
{
    Msg_20DF10 m;
    Msg_20DF10 n;
    s32 result = 1;
    WaitIpuCommandDone(o);
    while (*(volatile u32*)0x1000B020 != 0 && (*(volatile u32*)0x10002010 & 0x4000) == 0) {
        if (*(volatile u32*)0x1000B420 == 0 && (*(volatile u32*)0x1000B400 & 0x100) == 0) {
            m.cmd = 1;
            RunMpegCallback(o->handle, &m);
        }
    }
    u32 bp = *(volatile u32*)0x10002020;
    s64 top = *(s64*)0x10002030;
    o->f838 = (s32)top;
    if (top < 0) {
        u32 frac = bp & 0x1F;
        o->f83C = frac != 0 ? 0x20 - frac : 0;
    } else {
        o->f83C = 0x20;
    }
    if ((*(volatile u32*)0x10002010 & 0x4000) != 0) {
        result = 0;
        ReportMpegError((Self_20B978*)o, "Error code detected(BDEC)");
        n.cmd = 2;
        RunMpegCallback(o->handle, &n);
        *(volatile u32*)0x10002010 = 0x40000000;
        n.cmd = 3;
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

struct Self_20F248;
s16 DecodeIpuVariableLength(Self_20F248* self, s32 mode);

s32 DecodeIpuMotionCode(MpegDecoder* self)
{
	return DecodeIpuVariableLength((Self_20F248*)self, 3);
}

struct Mode_E120 { u8 pad[0x174]; s32 mode; s32 flag; };

void ComputeDualPrimeVectors(Mode_E120* self, s32* out, s32* in, s32 x, s32 y)
{
    if (self->mode == 3) {
        if (self->flag != 0) {
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
    if (self->mode == 1) {
        out[1] = r - 1;
    } else {
        out[1] = r + 1;
    }
}

struct Node_20E2A8 {
    u8 pad0[0x11C];
    s32 field11C;
    u8 pad1[0x848 - 0x120];
    s32 field848;
};

s16 DecodeIpuVariableLength(Self_20F248* self, s32 mode);
s32 PeekIpuBits(MpegDecoder* obj, s32 a1);
struct Ctx_20F4C8;
void SkipIpuBits(Ctx_20F4C8* s0, u32 s1);
void ReportMpegErrorFormat(struct Node_20E2A8 *self, const char *a1, s32 a2);

s32 ReadMacroblockAddressIncrement(struct Node_20E2A8 *self) {
    s32 total = 0;
    s32 again;
    do {
        s32 tok = DecodeIpuVariableLength((Self_20F248*)self, 0);
        switch ((u32)tok) {
        case 0x22:
            again = 1;
            break;
        case 0x23:
            again = 1;
            total += 0x21;
            break;
        case 0: {
            s32 v3 = PeekIpuBits((MpegDecoder*)self, 0xB);
            if (self->field848 != 0 && v3 == 0xF) {
                SkipIpuBits((Ctx_20F4C8*)self, 0xB);
                again = 1;
            } else {
                ReportMpegErrorFormat(self, "Invalid macroblock_address_increment code(0x%08x)", tok);
                self->field11C = 1;
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

struct Ctx_20E3B8 { u8 pad0[0x12C]; s32 f12C; s32 f130; u8 pad134[0x40]; s32 f174; u8 pad178[0x698]; s32 f810; s32 f814; };

struct Ctx_20E5F0;
s32 DecodeSliceMacroblocks(Ctx_20E5F0* c, s32 n);
void WaitIpuCommandDone(Ctx_20E3B8* c);
struct Dev_20CF18;
s32 WaitIpuDecodeDone(MpegDecoder* o);
void AddMacroblockResiduals(Dev_20CF18* self, s32 next);
void ReportMpegError(Self_20B978* self, const char* value);

s32 DecodeAllMacroblocks(Ctx_20E3B8* c)
{
    s32 r;
    s32 n;
    s32 res;
    c->f810 = 0;
    c->f814 = 0;
    n = c->f12C * c->f130;
    if (c->f174 != 3) n = n >> 1;
    do {
        r = DecodeSliceMacroblocks((Ctx_20E5F0*)c, n);
    } while (r == 1 || r == 3);
    WaitIpuCommandDone(c);
    if (WaitIpuDecodeDone((MpegDecoder*)c) == 0) r = 2;
    while ((*(volatile u32*)0x1000D400 >> 8) & 1) {}
    if (r == 0) AddMacroblockResiduals((Dev_20CF18*)c, c->f810 == 0);
    if ((u32)(r - 1) < 2) ReportMpegError((Self_20B978*)c, "= Skip to the next picture =");
    res = (r == 0);
    return res;
}

struct Ctx_20E4C0 {
    u8 pad0[0x11C];
    s32 f11C;
    u8 pad1[0x0C];
    s32 f12C;
    u8 pad2[0x80];
    s32 f1B0;
};

struct Out_20E4C0 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
};

void FindNextStartCode(MpegDecoder* self);
s32 PeekIpuBits(MpegDecoder* obj, s32 a1);
void ReportMpegErrorFormat(struct Ctx_20E4C0 *self, const char *a1, s32 a2);
void SkipIpuBits(Ctx_20F4C8* s0, u32 s1);
s32 ReadSliceQuantiser(MpegDecoder* self);
s32 ReadMacroblockAddressIncrement(struct Node_20E2A8 *self);
void ReportMpegError(Self_20B978* self, const char* value);

s32 ReadSliceStart(struct Ctx_20E4C0 *self, s32 a1, s32 *outA, s32 *outB, struct Out_20E4C0 *outC) {
    u32 s2;
    s32 s3;
    s32 e;

    self->f11C = 0;
    FindNextStartCode((MpegDecoder*)self);
    s2 = (u32)PeekIpuBits((MpegDecoder*)self, 0x20);
    if (s2 - 0x101 >= 0xAF) {
        ReportMpegErrorFormat(self, "slice_start_code(0x%08x) out of range", s2);
        return 2;
    }
    SkipIpuBits((Ctx_20F4C8*)self, 0x20);
    s3 = ReadSliceQuantiser((MpegDecoder*)self);
    e = ReadMacroblockAddressIncrement((struct Node_20E2A8*)self);
    *outB = e;
    if (self->f11C != 0) {
        ReportMpegError((Self_20B978*)self, "_sliceA0(): error happens");
        return 1;
    }
    *outA = ((s3 << 7) + (s2 & 0xFF) - 1) * self->f12C + e - 1;
    *outB = 1;
    self->f1B0 = 1;
    outC->f14 = 0;
    outC->f10 = 0;
    outC->f4 = 0;
    outC->f0 = 0;
    outC->f1C = 0;
    outC->f18 = 0;
    outC->fC = 0;
    outC->f8 = 0;
    return 0;
}

struct Ctx_20E5F0 {
    u8 pad0[0x11C];
    s32 f11c;
    u8 pad1[0x6CC - 0x120];
    u8 slots[0x144];
    u8 pad2[0x810 - 0x810];
    s32 f810;
};
struct Buf_20E5F0 { s32 w[8]; };
struct Half_20E5F0 { s32 w[4]; };

struct Self_20E8A0;
s32 ReadSliceStart(struct Ctx_20E4C0 *self, s32 a1, s32 *outA, s32 *outB, struct Out_20E4C0 *outC);
s32 WaitIpuDecodeDone(MpegDecoder* o);
s32 PeekIpuBits(MpegDecoder* obj, s32 a1);
s32 ReadMacroblockAddressIncrement(struct Node_20E2A8 *self);
void ReportMpegError(Self_20B978* self, const char* value);
s32 DecodeMacroblock(Self_20E8A0* self, s32* st, s32* mode, s32* o3, s32* b1, s32* o5, s32* b2);
s32 HandleSkippedMacroblock(struct Node_20E7E0 *self, s32 *a1, s32 *a2, s32 *a3, s32 *flags);
struct Dev_20C1A0;
s32 PrepareMacroblockPrediction(Dev_20C1A0* d, s32 n, s32 mode, s32 flags, s32 code, s32* vec, s32* sel,
                                s32* base);

s32 DecodeSliceMacroblocks(Ctx_20E5F0* c, s32 n)
{
    Buf_20E5F0 e;
    Half_20E5F0 f;
    Half_20E5F0 g;
    s32 i, j, a, b, d;
    i = 0;
    j = 0;
    s32 r = ReadSliceStart((struct Ctx_20E4C0*)c, n, &i, &j, (struct Out_20E4C0*)&e);
    if (r != 0) return r;
    c->f11c = 0;
    for (;;) {
        if (!(i < n)) return 0;
        *(s32*)((u8*)c + c->f810 * 0x140 + 0x6CC) = 0;
        if (WaitIpuDecodeDone((MpegDecoder*)c) == 0) return 2;
        if (j == 0) {
            if (PeekIpuBits((MpegDecoder*)c, 0x17) == 0) {
                c->f11c = 0;
                return 3;
            }
            if (c->f11c != 0) {
                c->f11c = 0;
                return 3;
            }
            j = ReadMacroblockAddressIncrement((struct Node_20E2A8*)c);
            if (c->f11c != 0) {
                c->f11c = 0;
                return 1;
            }
        }
        if (!(i < n)) {
            ReportMpegError((Self_20B978*)c, "Too many macroblocks in picture");
            return 2;
        }
        if (j == 1) {
            if (DecodeMacroblock((Self_20E8A0*)c, &a, &b, &d, (s32*)&e, (s32*)&f, (s32*)&g) == 0) {
                c->f11c = 0;
                return 1;
            }
        } else {
            if (HandleSkippedMacroblock((struct Node_20E7E0*)c, (s32*)&e, &b, (s32*)&f, &a) == 0) {
                c->f11c = 0;
                return 2;
            }
        }
        if (PrepareMacroblockPrediction((Dev_20C1A0*)c, i, j, a, b, e.w, f.w, g.w) == 0) {
            c->f11c = 0;
            return 2;
        }
        if (i != 0) AddMacroblockResiduals((Dev_20CF18*)c, c->f810 ^ 1);
        i = i + 1;
        c->f810 = c->f810 ^ 1;
        j = j - 1;
    }
}

struct Node_20E7E0 {
    s32 field0;
};

void ReportMpegError(Self_20B978* self, const char* value);

s32 HandleSkippedMacroblock(struct Node_20E7E0 *self, s32 *a1, s32 *a2, s32 *a3, s32 *flags)
{
    s32 ret = 1;
    u32 t;

    *(s32 *)((u8 *)self + *(s32 *)((u8 *)self + 0x810) * 0x140 + 0x6CC) = 1;
    *(s32 *)((u8 *)self + 0x1B0) = 1;
    if (*(s32 *)((u8 *)self + 0x150) == 2) {
        a1[5] = 0;
        a1[4] = 0;
        a1[1] = 0;
        a1[0] = 0;
    }
    if (*(s32 *)((u8 *)self + 0x174) == 3) {
        *a2 = 2;
    } else {
        *a2 = 1;
        t = (u32)(*(s32 *)((u8 *)self + 0x174) ^ 2) < 1;
        a3[1] = t;
        a3[0] = t;
    }
    if (*(s32 *)((u8 *)self + 0x150) == 1) {
        ReportMpegError((Self_20B978*)self, "skiped macroblock in I picure is not allowed");
        ret = 0;
    }
    *flags &= -2;
    return ret;
}

struct Self_20E8A0 {
    u8 pad0[0x11C];
    s32 f11C;
    u8 pad1[0x150 - 0x120];
    s32 f150;
    s32 f154;
    s32 f158;
    s32 f15C;
    s32 f160;
    s32 f164;
    s32 f168;
    s32 f16C;
    s32 f170;
    s32 f174;
    u8 pad2[4];
    s32 f17C;
    s32 f180;
    u8 pad3[0x1B0 - 0x184];
    s32 f1B0;
    s32 f1B4;
    u8 pad4[0x810 - 0x1B8];
    s32 f810;
    u8 pad5[0x848 - 0x814];
    s32 f848;
};

struct Ctx_20EDD0;
struct Node_20EF70;
struct Self_20EF70;
s16 DecodeIpuVariableLength(Self_20F248* self, s32 mode);
void ReportMpegError(Self_20B978* self, const char* value);
u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void SkipIpuBits(Ctx_20F4C8* s0, u32 s1);
void WaitIpuCommandDone(Self_20E8A0* self);
void SendIpuCommand(MpegDecoder* obj, u32 value);
void StartIpuOutputDma(u32 a, s32 b);
void ReadFieldMotionVector(Ctx_20EDD0* c, u8* arr, s32* a2, s32* out, s32 i, s32 mode, s32 a6, s32 a7, s32 s6, s32 s3, s32 fp);
void ReadMotionVector(Self_20EF70* self, Node_20EF70* n, s32* out, s32 p3, s32 p4, s32 want, s32 shift, s32 p7);

s32 DecodeMacroblock(Self_20E8A0* self, s32* st, s32* mode, s32* o3, s32* b1, s32* o5, s32* b2)
{
    s32 m3, m4, m7, mfp;
    s32 v;

    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xF8FFFFFF) | (self->f150 << 24);
    v = DecodeIpuVariableLength((Self_20F248*)self, 1);
    *st = v;
    if (v == 0) {
        ReportMpegError((Self_20B978*)self, "Invalid macroblock_type code: 0");
        self->f11C = 1;
        return 0;
    }
    if (v & 0xC) {
        if (self->f174 == 3 && self->f17C != 0) {
            *mode = 2;
        } else {
            *mode = ReadIpuBits((MpegDecoder*)self, 2);
        }
    } else if (v & 1) {
        if (self->f180 != 0) {
            *mode = (self->f174 == 3) ? 2 : 1;
        }
    }
    if (self->f174 == 3) {
        m3 = (*mode == 1) ? 2 : 1;
        m4 = (*mode == 2);
    } else {
        m4 = 0;
        m3 = (*mode == 2) ? 2 : 1;
    }
    mfp = (*mode == 3);
    m7 = 0;
    if (m4 == 0) {
        m7 = (self->f174 == 3);
    }
    s32 w;
    if (self->f174 == 3 && self->f17C == 0) {
        if ((*st & 3) != 0) {
            w = ReadIpuBits((MpegDecoder*)self, 1);
        } else {
            w = 0;
        }
    } else {
        w = 0;
    }
    *o3 = w;
    if (*st & 0x10) {
        self->f1B4 = ReadIpuBits((MpegDecoder*)self, 5);
    }
    if ((*st & 8) || ((*st & 1) && self->f180)) {
        if (self->f848) {
            ReadFieldMotionVector((Ctx_20EDD0*)self, (u8*)b1, b2, o5, 0, m3, m4, self->f164 - 1, self->f168 - 1, mfp, m7);
        } else {
            s32 t = self->f158 - 1;
            ReadMotionVector((Self_20EF70*)self, (Node_20EF70*)b1, b2, t, t, 0, 0, self->f154);
        }
    }
    if (self->f11C) {
        return 0;
    }
    if (*st & 4) {
        if (self->f848) {
            ReadFieldMotionVector((Ctx_20EDD0*)self, (u8*)b1, b2, o5, 1, m3, m4, self->f16C - 1, self->f170 - 1, 0, m7);
        } else {
            s32 t = self->f160 - 1;
            ReadMotionVector((Self_20EF70*)self, (Node_20EF70*)(b1 + 2), b2, t, t, 0, 0, self->f15C);
        }
    }
    if (self->f11C) {
        return 0;
    }
    if ((*st & 1) && self->f180) {
        SkipIpuBits((Ctx_20F4C8*)self, 1);
    }
    if (*st & 3) {
        StartIpuOutputDma(*(s32*)((u8*)self + self->f810 * 0x140 + 0x594), 0x300);
        WaitIpuCommandDone(self);
        s32 x = ((*st & 1) << 27) | (self->f1B4 << 16);
        s32 y = (self->f1B0 << 26) | 0x20000000;
        s32 z = *o3 << 25;
        SendIpuCommand((MpegDecoder*)self, x | y | z);
    } else {
        *(s32*)((u8*)self + self->f810 * 0x140 + 0x6CC) = 1;
    }
    self->f1B0 = 0;
    if (self->f11C) {
        return 0;
    }
    if ((*st & 1) == 0) {
        self->f1B0 = 1;
    }
    if ((*st & 1) && self->f180 == 0) {
        b1[5] = 0;
        b1[4] = 0;
        b1[1] = 0;
        b1[0] = 0;
        b1[7] = 0;
        b1[6] = 0;
        b1[3] = 0;
        b1[2] = 0;
    }
    s32 d = self->f150;
    if (d == 2 && (*st & 9) == 0) {
        b1[5] = 0;
        b1[4] = 0;
        b1[1] = 0;
        b1[0] = 0;
        if (self->f174 == 3) {
            *mode = d;
        } else {
            *mode = 1;
            *o5 = (self->f174 == 2);
        }
    }
    return 1;
}

struct Node_20EF70 { s32 f00; s32 f04; };

void ApplyMotionVectorDelta(Node_20EF70* n, s32 rsize, s32 code, s32 residual, s32 half)
{
    s32 f = 16 << rsize;
    s32 v = n->f00;
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
    n->f00 = half ? v << 1 : v;
}


struct Ctx_20EDD0;
u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void ReadMotionVector(Self_20EF70* self, Node_20EF70* n, s32* out, s32 p3, s32 p4, s32 want, s32 shift, s32 p7);

void ReadFieldMotionVector(Ctx_20EDD0* c, u8* arr, s32* a2, s32* out, s32 i, s32 mode, s32 a6, s32 a7, s32 s6, s32 s3, s32 fp)
{
    s32 v;
    s32* o;

    if (mode == 1) {
        if (a6 == 0 && s3 == 0) {
            v = ReadIpuBits((MpegDecoder*)c, 1);
            out[i] = v;
            out[i + 2] = v;
        }
        i <<= 3;
        ReadMotionVector((Self_20EF70*)c, (Node_20EF70*)(arr + i), a2, a7, s6, s3, fp, 0);
        u32* q = (u32*)(arr + i);
        u32 x = q[0];
        u32 y = q[1];
        q[4] = x;
        q[5] = y;
    } else {
        s32 j = i << 3;
        v = ReadIpuBits((MpegDecoder*)c, 1);
        out[i] = v;
        o = out + i;
        ReadMotionVector((Self_20EF70*)c, (Node_20EF70*)(arr + j), a2, a7, s6, s3, fp, 0);
        o[2] = ReadIpuBits((MpegDecoder*)c, 1);
        ReadMotionVector((Self_20EF70*)c, (Node_20EF70*)(arr + (j + 16)), a2, a7, s6, s3, fp, 0);
    }
}

struct Self_20EF70 { s32 f00; };

s16 DecodeIpuVariableLength(Self_20F248* self, s32 mode);
u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
s32 DecodeIpuMotionCode(MpegDecoder* self);

void ReadMotionVector(Self_20EF70* self, Node_20EF70* n, s32* out, s32 p3, s32 p4, s32 want, s32 shift, s32 p7)
{
    s32 s0;
    s32 a3;

    s0 = DecodeIpuVariableLength((Self_20F248*)self, 2);
    if (p3 != 0 && s0 != 0) {
        a3 = ReadIpuBits((MpegDecoder*)self, p3);
    } else {
        a3 = 0;
    }
    ApplyMotionVectorDelta(n, p3, s0, a3, p7);
    if (want != 0) {
        out[0] = DecodeIpuMotionCode((MpegDecoder*)self);
    }
    s0 = DecodeIpuVariableLength((Self_20F248*)self, 2);
    if (p4 != 0 && s0 != 0) {
        a3 = ReadIpuBits((MpegDecoder*)self, p4);
    } else {
        a3 = 0;
    }
    if (shift != 0) {
        n->f04 = n->f04 >> 1;
    }
    ApplyMotionVectorDelta((Node_20EF70*)&n->f04, p4, s0, a3, p7);
    if (shift != 0) {
        n->f04 = n->f04 << 1;
    }
    if (want != 0) {
        out[1] = DecodeIpuMotionCode((MpegDecoder*)self);
    }
}

u32 D_0027B040[10] = { 0x1, 0x1, 0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1 };

void SendIpuCommand(MpegDecoder* obj, u32 value)
{
    u32 index = value >> 28;
    volatile u32* setting = (volatile u32*)0x10002000;
    *setting = value;
    obj->f818 = D_0027B040[index];
}

// func_0020F0F0 is declared on its own type, not MpegDecoder: the other functions declare
// WaitIpuCommandDone as void on MpegDecoder (retail's registers want that), and one name cannot
// return both. Its only field is the handle at 0x858.
struct IpuWaitView {
    u8 pad_000[0x858];     // 0x000
    MpegHandle* handle;    // 0x858
};

s32 RunMpegStallCallback(Q_0020B1E0* q);

void WaitIpuCommandDone(IpuWaitView* self)
{
    s32 n = 0;
    if ((s32)(*(volatile u32*)0x10002010 & 0x80004000) == (s32)0x80000000) {
        do {
            s32 c = n;
            n = c + 1;
            if (c >= 0x1389) {
                RunMpegStallCallback((Q_0020B1E0*)self->handle);
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
                RunMpegStallCallback((Q_0020B1E0*)p->handle);
                i = 0;
            }
            v = *(volatile s64*)0x10002000;
        } while (v < 0 && (*(volatile u32*)0x10002010 & 0x4000) == 0);
    }
    return v;
}

extern u32 D_0027B040[];

struct Self_20F248 {
    u8 pad0[0x11C];
    s32 f11C;
    u8 pad1[0x6F8];
    s32 f818;
    u8 pad2[0x1C];
    s32 f838;
    s32 f83C;
    u8 pad3[0x18];
    MpegHandle* f858;
};

s32 RunMpegStallCallback(Q_0020B1E0* q);

s16 DecodeIpuVariableLength(Self_20F248* self, s32 mode)
{
    s32 m = 0;
    s32 n = 0;
    s32 cmd;
    s64 st;
    s64 hw;

    if ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000) {
        do {
            if (n++ >= 5001) {
                RunMpegStallCallback((Q_0020B1E0*)self->f858);
                n = 0;
            }
        } while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000);
    }
    cmd = (mode << 26) | 0x30000000;
    *(volatile u32*)0x10002000 = cmd;
    self->f818 = D_0027B040[cmd >> 28];
    st = *(volatile s64*)0x10002000;
    if (st < 0) {
        do {
            if (m++ >= 5001) {
                RunMpegStallCallback((Q_0020B1E0*)self->f858);
                m = 0;
            }
            st = *(volatile s64*)0x10002000;
        } while (st < 0);
    }
    u32 cnt = *(volatile u32*)0x10002020;
    hw = *(s64*)0x10002030;
    self->f838 = (s32)hw;
    if (hw < 0) {
        self->f83C = (-(cnt & 0x1F)) & 0x1F;
    } else {
        self->f83C = 0x20;
    }
    self->f11C = ((s32)st == 0);
    return (s16)st;
}


s64 WaitIpuCommandResult(MpegDecoder* obj);
s32 RunMpegStallCallback(Q_0020B1E0* q);

extern u32 D_0027B040[];

s32 PeekIpuBits(MpegDecoder* obj, s32 a1)
{
    if (obj->f818 != 0 || obj->f83C < a1) {
        s32 cnt = 0;
        while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000) {
            if (cnt++ > 0x1388) {
                RunMpegStallCallback((Q_0020B1E0*)obj->handle);
                cnt = 0;
            }
        }
        *(volatile u32*)0x10002000 = 0x40000000;
        obj->f818 = D_0027B040[4];
        obj->f838 = WaitIpuCommandResult(obj);
        obj->f83C = 0x20;
    }
    return (u32)obj->f838 >> (32 - a1);
}

struct Ctx_20F4C8 {
    u8 pad0[0x818];
    s32 f818;
    u8 pad1[0x838 - 0x81C];
    s32 f838;
    s32 f83C;
    u8 pad2[0x858 - 0x840];
    s32 f858;
};
struct Arg_20F4C8 { u32 v; };

extern u32 D_0027B040[];
extern s32 RunMpegStallCallback(Q_0020B1E0* q);
extern s64 WaitIpuCommandResult(Ctx_20F4C8* c, u32* v);

void SkipIpuBits(Ctx_20F4C8* s0, u32 s1)
{
    s32 cnt = 0;
    u32 v;
    u32* p;

    while ((*(volatile u32*)0x10002010 & 0x80004000u) == 0x80000000u) {
        if (cnt++ > 0x1388) {
            RunMpegStallCallback((Q_0020B1E0*)s0->f858);
            cnt = 0;
        }
    }
    v = s1 | 0x40000000u;
    *(volatile u32*)0x10002000 = v;
    p = &D_0027B040[v >> 28];
    s0->f818 = *p;
    s0->f838 = WaitIpuCommandResult(s0, p);
    s0->f83C = 0x20;
}


s64 WaitIpuCommandResult(MpegDecoder* obj);
s32 RunMpegStallCallback(Q_0020B1E0* q);

extern u32 D_0027B040[];

struct Cmd_20F5B8 {
    static void Send(MpegDecoder* obj, u32 cmd)
    {
        *(volatile u32*)0x10002000 = cmd;
        obj->f818 = D_0027B040[cmd >> 28];
        obj->f838 = WaitIpuCommandResult(obj);
    }
};

u32 ReadIpuBits(MpegDecoder* obj, s32 a1)
{
    s32 cnt = 0;
    u32 v;
    while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000) {
        if (cnt++ > 0x1388) {
            RunMpegStallCallback((Q_0020B1E0*)obj->handle);
            cnt = 0;
        }
    }
    if (obj->f818 != 0 || obj->f83C < a1) {
        Cmd_20F5B8::Send(obj, 0x40000000);
    }
    v = (u32)obj->f838 >> (32 - a1);
    obj->f83C = 0x20;
    Cmd_20F5B8::Send(obj, a1 | 0x40000000);
    return v;
}

void WaitIpuCommandDone(MpegDecoder* self); // stays void: retail returns a value, but declared so func_0020DF10 and func_0020F708 differs in registers
void SkipIpuBits(Ctx_20F4C8* s0, u32 s1);
s32 PeekIpuBits(MpegDecoder* obj, s32 a1);
void FindNextStartCode(MpegDecoder* self)
{
    WaitIpuCommandDone(self);
    volatile u32* reg = (volatile u32*)0x10002020;
    s32 mask = -(*reg & 7) & 7;
    if (mask != 0) {
        SkipIpuBits((Ctx_20F4C8*)self, mask);
    }
    while (PeekIpuBits(self, 0x18) != 1) {
        SkipIpuBits((Ctx_20F4C8*)self, 8);
    }
}


u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void SkipIpuBits(Ctx_20F4C8* s0, u32 s1);
void SkipExtraInformation(MpegDecoder* self);

s32 ReadSliceQuantiser(MpegDecoder* self)
{
    self->f1B4 = ReadIpuBits(self, 5);
    if (ReadIpuBits(self, 1) != 0) {
        ReadIpuBits(self, 1);
        SkipIpuBits((Ctx_20F4C8*)self, 7);
        SkipExtraInformation(self);
    }
    return 0;
}

// The record func_0020F7F0 hands the callback to ask for the picture's position: a kind, then two
// words the callback fills in.
struct MpegPositionQuery { s32 kind; s64 first; s64 second; };

void FindNextStartCode(MpegDecoder* self);
u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void ReadSequenceHeader(Dec_20B9F0* d);
void ReadGroupOfPicturesHeader(MpegDecoder* self);
void ReadPictureHeader(MpegDecoder* self);
s32 RunMpegCallback(MpegHandle* a0, MpegPositionQuery* out);

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
        ReadSequenceHeader((Dec_20B9F0*)self);
        continue;
    c1B8:
        ReadGroupOfPicturesHeader(self);
        continue;
    c100:
        {
            MpegPositionQuery loc;
            ReadPictureHeader(self);
            loc.kind = 5;
            loc.first = -1;
            loc.second = -1;
            RunMpegCallback(self->handle, &loc);
            self->f828 = loc.first;
            self->f830 = loc.second;
            return self->f150;
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
    self->f150 = ReadIpuBits(self, 3);
    ReadIpuBits(self, 16);
    if ((u32)(self->f150 - 2) < 2) {
        self->f154 = ReadIpuBits(self, 1);
        self->f158 = ReadIpuBits(self, 3);
    }
    if (self->f150 == 3) {
        self->f15C = ReadIpuBits(self, 1);
        self->f160 = ReadIpuBits(self, 3);
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
void SkipIpuBits(Ctx_20F4C8* s0, u32 s1);
u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
s32 PeekIpuBits(MpegDecoder* obj, s32 a1);

// An entry of the table of extension handlers below.
typedef void (*Fn_Table)();
struct Ctx_20FAF0;
struct Bits_210000;
void ReadPictureCodingExtension(Ctx_20FAF0* c);
void ReadQuantiserMatrixExtension(MpegDecoder *self);
void ReadPictureDisplayExtension(MpegDecoder* self);
void ReadCopyrightExtension(Bits_210000* self);
// The handlers of the extensions by their 4-bit id, the sequence's in src/lib/mpeg_decoder.cpp.
struct Node_20C0A8;
void ReadSequenceExtension(MpegDecoder *self);
void ReadSequenceDisplayExtension(struct Node_20C0A8* self);
void RejectSequenceScalableExtension(MpegDecoder* self);
void RejectUnknownExtension(MpegDecoder* self);
void RejectSpatialScalableExtension(MpegDecoder* self);
void RejectTemporalScalableExtension(MpegDecoder* self);
extern const Fn_Table g_mpegExtensionHandlers[12] = { (Fn_Table)RejectUnknownExtension, (Fn_Table)ReadSequenceExtension, (Fn_Table)ReadSequenceDisplayExtension, (Fn_Table)ReadQuantiserMatrixExtension, (Fn_Table)ReadCopyrightExtension, (Fn_Table)RejectSequenceScalableExtension, (Fn_Table)RejectUnknownExtension, (Fn_Table)ReadPictureDisplayExtension, (Fn_Table)ReadPictureCodingExtension, (Fn_Table)RejectSpatialScalableExtension, (Fn_Table)RejectTemporalScalableExtension, 0 };

void ReadExtensionsAndUserData(MpegDecoder* self)
{
    s32 kA = 0x1B2;
    union ExtensionHandlerTable t;
    t.t = *(struct ExtensionHandlerCopy*)((u8*)g_mpegExtensionHandlers);
    s32 kB = 0x1B5;
    s32 r;

    FindNextStartCode(self);
    u32 limit = 10;
    while ((r = PeekIpuBits(self, 0x20)) == kB || r == kA) {
        if (r == kB) {
            SkipIpuBits((Ctx_20F4C8*)self, 0x20);
            u32 idx = (u32)ReadIpuBits(self, 4);
            if (limit < idx) {
                idx = 0;
            }
            t.fn[idx](self);
            FindNextStartCode(self);
        } else {
            SkipIpuBits((Ctx_20F4C8*)self, 0x20);
            FindNextStartCode(self);
        }
    }
}

struct Ctx_20FAF0 {
    u8 pad0[0xD4];
    s32 f_d4;
    u8 pad1[0x164 - 0xD8];
    s32 f164, f168, f16c, f170, f174, f178, f17c, f180, f184, f188;
};

u32 ReadIpuBits(MpegDecoder* obj, s32 a1);

void ReadPictureCodingExtension(Ctx_20FAF0* c)
{
    c->f164 = ReadIpuBits((MpegDecoder*)c, 4);
    c->f168 = ReadIpuBits((MpegDecoder*)c, 4);
    c->f16c = ReadIpuBits((MpegDecoder*)c, 4);
    c->f170 = ReadIpuBits((MpegDecoder*)c, 4);
    *(u32*)0x10002010 = (*(u32*)0x10002010 & 0xFFFCFFFF) | (ReadIpuBits((MpegDecoder*)c, 2) << 16);
    s32 v = ReadIpuBits((MpegDecoder*)c, 2);
    c->f174 = v;
    if (c->f_d4 == 0) c->f_d4 = v;
    c->f178 = ReadIpuBits((MpegDecoder*)c, 1);
    c->f17c = ReadIpuBits((MpegDecoder*)c, 1);
    c->f180 = ReadIpuBits((MpegDecoder*)c, 1);
    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xFFBFFFFF) | (ReadIpuBits((MpegDecoder*)c, 1) << 22);
    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xFFDFFFFF) | (ReadIpuBits((MpegDecoder*)c, 1) << 21);
    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xFFEFFFFF) | (ReadIpuBits((MpegDecoder*)c, 1) << 20);
    c->f184 = ReadIpuBits((MpegDecoder*)c, 1);
    ReadIpuBits((MpegDecoder*)c, 1);
    c->f188 = ReadIpuBits((MpegDecoder*)c, 1);
    if (ReadIpuBits((MpegDecoder*)c, 1) == 0) return;
    ReadIpuBits((MpegDecoder*)c, 1);
    ReadIpuBits((MpegDecoder*)c, 3);
    ReadIpuBits((MpegDecoder*)c, 1);
    ReadIpuBits((MpegDecoder*)c, 7);
    ReadIpuBits((MpegDecoder*)c, 8);
}

u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void SkipIpuBits(Ctx_20F4C8* s0, u32 s1);

void SkipExtraInformation(MpegDecoder* self)
{
    while (ReadIpuBits(self, 1))
        SkipIpuBits((Ctx_20F4C8*)self, 8);
}


s32 UpdatePictureOrder(MpegDecoder* self, s32 a1)
{
    s32 lim = 0;
    s32 neg = 0;
    if (self->f150 != 3 && a1 != 0) {
        if (a1 < 0) {
            neg = (u32)self->f854 < 1;
        }
        self->f854 = 0;
        lim = a1;
    }
    s32 v1 = self->f84C + a1;
    self->f1AC = v1;
    if (neg && lim >= a1) {
        self->f1AC = v1 + 0x400;
    }
    s32 v0 = self->f850;
    if (v0 < self->f1AC) {
        v0 = self->f1AC;
    }
    self->f850 = v0;
    return v0;
}

u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void ReadExtensionsAndUserData(MpegDecoder* self);

void ReadGroupOfPicturesHeader(MpegDecoder* self)
{
    self->fE8 = 0;
    self->f84C = self->f850 + 1;
    self->f854 = 1;
    ReadIpuBits(self, 1);
    ReadIpuBits(self, 5);
    ReadIpuBits(self, 6);
    ReadIpuBits(self, 1);
    ReadIpuBits(self, 6);
    ReadIpuBits(self, 6);
    self->f1A4 = ReadIpuBits(self, 1);
    self->f1A8 = ReadIpuBits(self, 1);
    ReadExtensionsAndUserData(self);
}


u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void WaitIpuCommandDone(MpegDecoder *self);
void SendIpuCommand(MpegDecoder* obj, u32 value);
void ReportMpegError(Self_20B978* self, const char* value);

void ReadQuantiserMatrixExtension(MpegDecoder *self)
{
    s32 v;

    v = ReadIpuBits(self, 1);
    self->f840 = v;
    if (v != 0) {
        WaitIpuCommandDone(self);
        SendIpuCommand(self, 0x50000000);
        WaitIpuCommandDone(self);
    }
    v = ReadIpuBits(self, 1);
    self->f844 = v;
    if (v != 0) {
        WaitIpuCommandDone(self);
        SendIpuCommand(self, 0x58000000);
        WaitIpuCommandDone(self);
    }
    v = ReadIpuBits(self, 1);
    if (v != 0) {
        ReportMpegError((Self_20B978*)self, "load_chroma_intra_quantizer_matrix == 1");
    }
    v = ReadIpuBits(self, 1);
    if (v == 0) {
        return;
    }
    ReportMpegError((Self_20B978*)self, "load_chroma_non_intra_quantizer_matrix == 1");
}

u32 ReadIpuBits(MpegDecoder* obj, s32 a1);

void ReadPictureDisplayExtension(MpegDecoder* self)
{
    s32 n;
    s32 i;
    if (self->f13C != 0) {
        if (self->f184 != 0) n = (self->f178 != 0) ? 3 : 2;
        else n = 1;
    } else if (self->f174 != 3) {
        n = 1;
    } else {
        n = (self->f184 != 0) ? 3 : 2;
    }
    for (i = 0; i < n; i++) {
        self->centreHorizontal[i] = ReadIpuBits(self, 0x10);
        ReadIpuBits(self, 1);
        self->centreVertical[i] = ReadIpuBits(self, 0x10);
        ReadIpuBits(self, 1);
    }
}

struct Bits_210000;
u32 ReadIpuBits(MpegDecoder* obj, s32 a1);

void ReadCopyrightExtension(Bits_210000* self)
{
    ReadIpuBits((MpegDecoder*)self, 1);
    ReadIpuBits((MpegDecoder*)self, 8);
    ReadIpuBits((MpegDecoder*)self, 1);
    ReadIpuBits((MpegDecoder*)self, 7);
    ReadIpuBits((MpegDecoder*)self, 1);
    ReadIpuBits((MpegDecoder*)self, 0x14);
    ReadIpuBits((MpegDecoder*)self, 1);
    ReadIpuBits((MpegDecoder*)self, 0x16);
    ReadIpuBits((MpegDecoder*)self, 1);
    ReadIpuBits((MpegDecoder*)self, 0x16);
}


void ReportMpegError(Self_20B978* self, const char* value);
s32 DecodeAllMacroblocks(Ctx_20E3B8* c);

s32 DecodePictureData(MpegDecoder* self)
{
    MpegPicture* s1;
    s32 v;
    s32 mode = self->f174;
    if (mode == 3 && self->f120 != 0) {
        ReportMpegError((Self_20B978*)self, (const char*)((u8*)"odd number of field pictures"));
        self->f120 = 0;
        mode = self->f174;
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
        ReportMpegError((Self_20B978*)self, (const char*)((u8*)"unknown picture sutructure"));
        break;
    }
    v = DecodeAllMacroblocks((Ctx_20E3B8*)self);
    if (v != 0) {
        s1->f28 = 1;
    }
    return v;
}

struct Src_210970;
struct Src_210A80;
struct Node_210160 {
    u8 pad000[0xF8];
    s32 f0F8;
    u8 pad0FC[0x54];
    s32 f150;
    u8 pad154[0x20];
    s32 f174;
    u8 pad178[0x40];
    Src_210970* f1B8;
    u8 pad1BC[0x8];
    Src_210970* f1C4;
    Src_210A80* f1C8;
    u8 pad1CC[0x8];
    Src_210A80* f1D4;
    Src_210A80* f1D8;
    u8 pad1DC[0x8];
    Src_210A80* f1E4;
};

struct Ctx_210970;
void OutputFramePicture(Ctx_210970* c, Src_210970* s, s32 count);
struct Ctx_210A80;
void OutputFieldPicturePair(Ctx_210A80* c, Src_210A80* a, Src_210A80* b, s32 count);

void OutputPictureIfDecoded(struct Node_210160* self, s32 count, s32 flag)
{
    s32 n = count;
    if (flag != 0) {
        if (self->f174 == 3) {
            Src_210970* x;
            if (self->f150 == 3) {
                x = self->f1C4;
            } else {
                x = self->f1B8;
            }
            OutputFramePicture((Ctx_210970*)self, x, n - 1);
        } else {
            Src_210A80* x;
            Src_210A80* y;
            if (self->f150 == 3) {
                x = self->f1D4;
                y = self->f1E4;
            } else {
                x = self->f1C8;
                y = self->f1D8;
            }
            n = n - 1;
            OutputFieldPicturePair((Ctx_210A80*)self, x, y, n);
        }
    }
    if (self->f0F8 == 1) {
        self->f0F8 = 2;
    }
}



s32 SelectPictureBuffer(MpegDecoder* p, s32 flag)
{
    MpegPicture* o = 0;
    s32 ok = 0;
    s32 lim = p->f174 == 3 ? 2 : 4;

    if (p->f150 == 3) {
        p->pictures[2] = p->pictures[3];
        p->pictures[6] = p->pictures[7];
        p->pictures[10] = p->pictures[11];
        if (p->fA0 + p->fA4 >= lim) {
            p->fE8 = 0;
            p->f1A8 = 0;
            p->f1A4 = 0;
        }
        if ((p->fE8 || p->f1A8) && !p->f1A4) {
            p->pictures[0]->f28 = 0;
            p->pictures[4]->f28 = 0;
            p->pictures[8]->f28 = 0;
        }
        p->fE8 = 0;
        p->f1A8 = 0;
        if (p->f174 == 3) {
            if ((p->pictures[0]->f28 == 1 || p->f1A4) && p->pictures[1]->f28 == 1) ok = 1;
        } else {
            if (((p->pictures[4]->f28 == 1 && p->pictures[8]->f28 == 1) || p->f1A4) && p->pictures[5]->f28 == 1 && p->pictures[9]->f28 == 1) ok = 1;
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
        if (p->f174 == 3) {
            if (p->f150 != 2 || p->pictures[0]->f28 == 1) ok = 1;
        } else {
            MpegPicture* x = p->f174 == 1 ? p->pictures[9] : p->pictures[5];
            if (p->f150 != 2) ok = 1;
            else if ((flag && x->f28 == 1) || (p->pictures[4]->f28 == 1 && p->pictures[8]->f28 == 1)) ok = 1;
        }
    }

    switch (p->f174) {
    case 2: o = p->pictures[10]; break;
    case 1: o = p->pictures[6]; break;
    case 3: o = p->pictures[2]; break;
    }
    o->f28 = 0;
    o->f18 = p->f828;
    o->f2C = p->f150;
    o->f20 = p->f830;
    o->f30 = p->f174;
    o->f34 = p->f13C;
    o->f38 = p->f188;
    o->f3C = p->f178;
    o->f40 = p->f184;
    o->f44 = p->centreHorizontal[0];
    o->f48 = p->centreHorizontal[1];
    o->f4C = p->centreHorizontal[2];
    o->f50 = p->centreVertical[0];
    o->f54 = p->centreVertical[1];
    o->f58 = p->centreVertical[2];
    o->f5C = p->f148;
    o->f60 = p->f14C;
    return ok;
}

struct Node_2104A8 {
    u8 pad0[0xDC];
    s32 fDC;
    s32 fE0;
    s32 fE4;
};

struct Rec_2104A8 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
};

s32 FormatToString(char* dst, const char* fmt, ...);
void ReportMpegError(Self_20B978* self, const char* value);

s32 CheckPictureBufferSize(struct Node_2104A8 *self, struct Rec_2104A8 *rec) {
    char buf[0x100];
    s32 flag;
    if (self->fE0 != 0)
        flag = self->fDC >= rec->f4 && self->fE0 >= rec->f8;
    else
        flag = self->fE4 >= rec->fC * rec->f10;
    if (flag == 0) {
        FormatToString(buf, "Too small buffer size for %dx%d picture\n", rec->f4, rec->f8);
        ReportMpegError((Self_20B978*)self, buf);
    }
    return flag;
}

struct Pic_210548 {
    u32 f0;
    u8 p4[8];
    s32 fC;
    s32 f10;
};

struct Ctx_210548 {
    u8 p0[0xD8];
    u32 fD8;
    u8 pDC[4];
    s32 fE0;
    s32 fE4;
    u8 pE8[0x174 - 0xE8];
    s32 f174;
};

void CopyPictureThroughScratchpad(Ctx_210548* c, Pic_210548* pic)
{
    s32 passes;
    u32 src = pic->f0 & 0x0FFFFFFF;
    u32 dst = c->fD8 & 0x0FFFFFFF;
    s32 srcStride;
    s32 dstStride;
    s32 qwc;
    s32 pass;
    s32 i;
    u32 to;

    if (c->f174 == 3 || c->fE0 == 0) {
        srcStride = pic->f10 * 0x180;
        qwc = srcStride >> 4;
        if (c->fE0 != 0)
            dstStride = (c->fE0 >> 4) * 0x180;
        else
            dstStride = srcStride;
        passes = 1;
    } else {
        dstStride = (c->fE0 >> 4) * 0xC0;
        srcStride = (pic->f10 >> 1) * 0x180;
        passes = 2;
        qwc = srcStride >> 4;
    }
    for (pass = 0; pass < passes; pass++) {
        to = dst;
        for (i = 0; i < pic->fC; i++) {
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
        dst += c->fE4 * 0xC0;
    }
}


struct Object_2107B8 { u8 pad1[8]; s32 mode; u8 pad2[0xA0]; s32 fieldAC; u8 pad3[0x68]; s32 field118; u8 pad4[0x704]; s32 field820; };

s32 SignalPictureReady(Object_2107B8* obj)
{
    s32 value;
    s32 result = 1;
    if (obj->mode == 2) {
        goto done;
    }
    value = obj->field118;
    obj->mode = 2;
    obj->fieldAC = value;
done:
    obj->field820 = result;
    return result;
}

struct Node_2107E0 {
    u8 pad0[0x18];
    s64 f18;
    s64 f20;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
};


extern "C" s64 MultiplySigned64(s64 u, s64 v);

void FillPictureOutputInfo(MpegDecoder* self, Node_2107E0* node, s64* out1, s64* out3, s64* out4)
{
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s6;
    s32 s7;
    s64 v;
    s64 t88;

    if (self->f70 != 0) {
        v = node->f18;
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
        *out1 = node->f18;
    }
    if (self->fF8 == 2) {
        if (self->fF0 >= 0) {
            *out1 = self->fF0;
            self->fF8 = 0;
            self->fF0 = -1;
        }
    }
    *out3 = node->f20;
    *out4 = ((s64)node->f34 << 8) | (node->f2C | ((s64)node->f38 << 7) | ((s64)node->f3C << 6) | ((s64)node->f40 << 5) | ((s64)node->f30 << 3));
}

// A table of 16 words by a 4-bit code, which func_00210970 reads.
u32 D_0027B068[16] = { 0x2, 0x0, 0x2, 0x0, 0x2, 0x3, 0x2, 0x3, 0x0, 0x0, 0x0, 0x0, 0x2, 0x4, 0x0, 0x6 };
u32 D_0027B0A8[2] = { 0 };

struct Blk_210970 { u8 p0[0x10]; s32 f10; u8 p14[0xC]; u64 f20; };
struct Src_210970 { u8 p0[0x28]; s32 f28; u8 p2C[0x18]; s32 f44; s32 f48; s32 f4C; s32 f50; s32 f54; s32 f58; s32 f5C; s32 f60; };
struct Ctx_210970 {
    u8 p0[0x80]; s32 f80; u8 p84[4]; u64 f88; u8 p90[0x20]; s32 fB0; s32 fB4; s32 fB8; s32 fBC; s32 fC0; s32 fC4; s32 fC8; s32 fCC; s32 fD0;
    u8 pD4[0x858 - 0xD4]; Blk_210970* f858;
};
void FillPictureOutputInfo(MpegDecoder* self, Node_2107E0* node, s64* out1, s64* out3, s64* out4);
s32 CheckPictureBufferSize(struct Node_2104A8 *self, struct Rec_2104A8 *rec);
struct Desc_211348;
struct Self_211348;
void ConvertPictureColours(Self_211348* self, Desc_211348* d);
void CopyPictureThroughScratchpad(Ctx_210548* c, Pic_210548* pic);
s32 SignalPictureReady(Object_2107B8* obj);

void OutputFramePicture(Ctx_210970* c, Src_210970* s, s32 count)
{
    FillPictureOutputInfo((MpegDecoder*)c, (Node_2107E0*)s, (s64*)((u8*)c->f858 + 0x10), (s64*)((u8*)c->f858 + 0x18), (s64*)((u8*)c->f858 + 0x20));
    Blk_210970* p = c->f858;
    u32 idx = (u32)(p->f20 >> 5) & 0xF;
    c->f80 = p->f10;
    c->f88 = D_0027B068[idx];
    c->fCC = s->f5C;
    c->fD0 = s->f60;
    c->fB4 = s->f44;
    c->fB8 = s->f48;
    c->fBC = s->f4C;
    c->fC0 = s->f50;
    c->fC4 = s->f54;
    c->fC8 = s->f58;
    if (CheckPictureBufferSize((struct Node_2104A8*)c, (struct Rec_2104A8*)s)) {
        if (s->f28 == 1) {
            if (c->fB0) {
                ConvertPictureColours((Self_211348*)c, (Desc_211348*)s);
            } else {
                CopyPictureThroughScratchpad((Ctx_210548*)c, (Pic_210548*)s);
            }
            SignalPictureReady((Object_2107B8*)c);
        }
    }
}

struct Blk_210A80 { u8 p0[0x10]; s32 f10; u8 p14[0xC]; u64 f20; s32 f28; u8 p2C[0xC]; u64 f38; };
struct Src_210A80 { u8 p0[0x10]; s32 f10; u8 p14[0x14]; s32 f28; u8 p2C[0x18]; s32 f44; s32 f48; u8 p4C[4]; s32 f50; s32 f54; u8 p58[4]; s32 f5C; s32 f60; };
struct Ctx_210A80 {
    u8 p0[0x80]; s32 f80; u8 p84[4]; union { u64 d; u32 w[2]; } f88; u8 p90[0x20]; s32 fB0; s32 fB4; s32 fB8; u8 pBC[4]; s32 fC0; s32 fC4; u8 pC8[4]; s32 fCC; s32 fD0;
    u8 pD4[0x174 - 0xD4]; s32 f174; u8 p178[0x858 - 0x178]; Blk_210A80* f858;
};

void FillPictureOutputInfo(MpegDecoder* self, Node_2107E0* node, s64* out1, s64* out3, s64* out4);
s32 CheckPictureBufferSize(struct Node_2104A8 *self, struct Rec_2104A8 *rec);
void ConvertPictureColours(Self_211348* self, Desc_211348* d);
void CopyPictureThroughScratchpad(Ctx_210548* c, Pic_210548* pic);
s32 SignalPictureReady(Object_2107B8* obj);

void OutputFieldPicturePair(Ctx_210A80* c, Src_210A80* a, Src_210A80* b, s32 count)
{
    Src_210A80* s3;
    Src_210A80* s4;
    s32 s6 = 0;
    if (c->f174 == 2) {
        s3 = a;
        s4 = b;
        s6 = 0x40;
    } else {
        s3 = b;
        s4 = a;
    }
    (void)FillPictureOutputInfo((MpegDecoder*)c, (Node_2107E0*)s3, (s64*)((u8*)c->f858 + 0x10), (s64*)((u8*)c->f858 + 0x18), (s64*)((u8*)c->f858 + 0x20));
    c->f80 = c->f858->f10;
    c->f88.d = 1;
    (void)FillPictureOutputInfo((MpegDecoder*)c, (Node_2107E0*)s4, (s64*)((u8*)c->f858 + 0x28), (s64*)((u8*)c->f858 + 0x30), (s64*)((u8*)c->f858 + 0x38));
    c->f80 = c->f858->f28;
    c->f88.d = 1;
    Blk_210A80* p = c->f858;
    u64 v0 = p->f20 | (s64)s6;
    s32 a2 = s3->f5C;
    u64 v1 = p->f38 | (s64)s6;
    c->fCC = a2;
    p->f20 = v0;
    s32 a2b = s3->f60;
    p->f38 = v1;
    c->fD0 = a2b;
    c->fB4 = s3->f44;
    c->fB8 = s4->f48;
    c->fC0 = s3->f50;
    c->fC4 = s4->f54;
    if (CheckPictureBufferSize((struct Node_2104A8*)c, (struct Rec_2104A8*)a)) {
        if (a->f28 == 1 && b->f28 == 1) {
            a->f10 <<= 1;
            if (c->fB0) {
                ConvertPictureColours((Self_211348*)c, (Desc_211348*)a);
            } else {
                CopyPictureThroughScratchpad((Ctx_210548*)c, (Pic_210548*)a);
            }
            a->f10 >>= 1;
            SignalPictureReady((Object_2107B8*)c);
        }
    }

}

// The DMA chain func_00210C38 builds, which only it reads.
static u8 g_blockChainTags[0x200];

extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);

// One of the decoder's two pictures, 0x140 bytes from +0x590 (the one in use at +0x810).
struct Pic_210C38 {
    u32 f00;                // 0x00: the address the chain's transfer starts from
    u8 pad04[0x08 - 0x04];
    u32 a[4];               // 0x08: the source of each block's first transfer
    u32 b[4];               // 0x18: the source of each block's second
    u8 pad28[0x12C - 0x28];
    s32 count;              // 0x12C: the blocks
    u8 pad130[0x140 - 0x130];
};

struct Dec_210C38 {
    u8 pad000[0x590];
    Pic_210C38 pics[2];     // 0x590
    u8 pad810[0x810 - 0x810];
    s32 current;            // 0x810
};

// Builds the DMA chain of the current picture's blocks in uncached memory (two REF tags a
// block, the last REFE) and starts it on channel 9 (to the scratchpad): its address, its tag
// and the channel's control word, with interrupts disabled.
void StartBlockChainToScratchpad(Dec_210C38* self)
{
    u64* tag = (u64*)(((u32)g_blockChainTags & 0x0FFFFFFF) | 0x20000000);
    s32 n = self->pics[self->current].count;
    for (s32 i = 0; i < n; i++) {
        u64 first = (u64)(self->pics[self->current].a[i] & 0x0FFFFFFF) << 32;
        u64 second = (u64)(self->pics[self->current].b[i] & 0x0FFFFFFF) << 32;
        u64 id = (i == n - 1) ? 0 : 3;
        tag[0] = first | 0x30000030;
        tag[2] = second | (id << 28) | 0x30;
        tag += 4;
    }
    DisableInterrupts();
    Sync();
    *(volatile u32*)0x1000D480 = self->pics[self->current].f00;
    *(volatile u32*)0x1000D430 = (u32)g_blockChainTags;
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
s32 RunMpegCallback(MpegHandle* h, s32* p);

void ConvertSmallPictureColours(MpegDecoder* self, u32 a1, u32 a2)
{

    s32 tmp[8];
    while (*(volatile s32*)0x10002010 < 0) { }
    (void)DisableInterrupts();
    *(volatile u32*)0x1000B010 = a1 & 0x0FFFFFFF;
    *(volatile u32*)0x1000B020 = a2 << 6;
    *(volatile u32*)0x1000B000 = 0x100;
    (void)EnableInterrupts();
    SendIpuCommand(self, a2 | 0x70000000);
    tmp[0] = 4;
    RunMpegCallback(self->handle, tmp);
    while ((*(volatile u32*)0x1000B000 >> 8) & 1) { }
    while (*(volatile s32*)0x10002010 < 0) { }
}

// The record of a decode's input transfer in chunks of 0x3FF quadwords (func_00211090 fills it).
struct Xfer_211090 {
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
    Xfer_211090* x = (Xfer_211090*)arg;
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

struct Queue_211090;
struct Self_211090 {
    u8 pad000[0x858];
    Queue_211090* f858;
};

struct Msg_211090 {
    s32 cmd;
    s32 pad04[7];
};

s32 AddDmaHandlerAlt(s32 channel, s32 (*handler)(s32, void*), s32 next, void* arg);
s32 RemoveDmaHandler(s32 channel, s32 id);
s32 DisableDmaInterrupt(s32 channel);
s32 EnableDmaInterrupt(s32 channel);
extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);
s32 ContinueColourConversionOutput(s32 channel, void* arg);
s32 RunMpegCallback(Queue_211090* q, Msg_211090* m);
void ReportMpegError(Self_20B978* self, const char* value);

void ConvertLargePictureColours(Self_211090* self, s32 addr, s32 size)
{
    s32 chunk = 0x3FF;
    Msg_211090 msg;
    Xfer_211090 xfer;
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
    msg.cmd = 4;
    RunMpegCallback(self->f858, &msg);
    while (xfer.done < xfer.total) {
    }
    if (xfer.error != 0) {
        ReportMpegError((Self_20B978*)self, (const char*)((u8*)"CSC handler error\n"));
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

extern u8 g_frameInfoObject0[], g_frameInfoObject1[], g_frameInfoObject2[], g_frameInfoObject3[], g_frameInfoObject4[], g_frameInfoObject5[];

struct Queue_211348;
struct Self_211348 {
    u8 pad000[0xD8];
    s32 fD8;
    u8 pad0DC[0x858 - 0xDC];
    Queue_211348* f858;
};

struct Desc_211348 {
    u32 addr;
    s32 pad4[2];
    s32 w;
    s32 h;
};

struct Msg_211348 {
    s32 cmd;
    s32 pad04[7];
};

struct Xfer_211348 {
    u32 size;
    u32 addr;
};

s32 AddDmaHandlerAlt(s32 channel, s32 (*handler)(s32, void*), s32 next, void* arg);
s32 RemoveDmaHandler(s32 channel, s32 id);
s32 DisableDmaInterrupt(s32 channel);
s32 EnableDmaInterrupt(s32 channel);
extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);
s32 ContinueColourConversionInput(s32 unused, PendingInput* p);
s32 RunMpegCallback(Queue_211348* q, Msg_211348* m);
void SendIpuCommand(MpegDecoder* obj, u32 value);
void ConvertSmallPictureColours(MpegDecoder* self, u32 a1, u32 a2);
void ConvertLargePictureColours(Self_211090* self, s32 addr, s32 size);

void ConvertPictureColours(Self_211348* self, Desc_211348* d)
{
    Msg_211348 msg;
    Xfer_211348 xfer;
    s32 count = d->w * d->h;
    msg.cmd = 2;
    RunMpegCallback(self->f858, &msg);
    if ((*(volatile u32*)0x10002010 & 0x4000) != 0) {
        *(volatile u32*)0x10002010 = 0x40000000;
    }
    s32 small = count < 0x400;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    SendIpuCommand((MpegDecoder*)self, 0);
    u32 addr = d->addr;
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
            ConvertSmallPictureColours((MpegDecoder*)self, self->fD8, count);
        } else {
            ConvertLargePictureColours((Self_211090*)self, self->fD8, count);
        }
        DisableDmaInterrupt(4);
        RemoveDmaHandler(4, id);
    } else {
        (void)DisableInterrupts();
        *(volatile u32*)0x1000B410 = d->addr & 0xFFFFFFF;
        *(volatile u32*)0x1000B420 = xfer.size;
        *(volatile u32*)0x1000B400 = 0x101;
        (void)EnableInterrupts();
        xfer.size = 0;
        if (small) {
            ConvertSmallPictureColours((MpegDecoder*)self, self->fD8, count);
        } else {
            ConvertLargePictureColours((Self_211090*)self, self->fD8, count);
        }
    }
    msg.cmd = 3;
    RunMpegCallback(self->f858, &msg);
}
