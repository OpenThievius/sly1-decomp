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

u32 func_0020DEE8(u32 value)
{
    u32* setting = (u32*)0x10002010;
    u32 result = (*setting & 0xFF7FFFFFu) | (value << 23);
    *setting = result;
    return result;
}

struct Queue_20DF10;
struct Obj_20DF10 { u8 pad0[0x838]; s32 f838; s32 f83C; u8 pad840[0x18]; Queue_20DF10* f858; };
struct Msg_20DF10 { s32 cmd; s32 pad[7]; };

void func_0020F0F0(Obj_20DF10* o);
void func_0020B190(Queue_20DF10* q, Msg_20DF10* m);
void func_0020B978(Obj_20DF10* o, const char* msg);
s32 func_001F9D60(void);
s32 func_001F9DA8(void);

s32 func_0020DF10(Obj_20DF10* o)
{
    Msg_20DF10 m;
    Msg_20DF10 n;
    s32 result = 1;
    WaitIpuCommandDone(o);
    while (*(volatile u32*)0x1000B020 != 0 && (*(volatile u32*)0x10002010 & 0x4000) == 0) {
        if (*(volatile u32*)0x1000B420 == 0 && (*(volatile u32*)0x1000B400 & 0x100) == 0) {
            m.cmd = 1;
            RunMpegCallback(o->f858, &m);
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
        ReportMpegError(o, "Error code detected(BDEC)");
        n.cmd = 2;
        RunMpegCallback(o->f858, &n);
        *(volatile u32*)0x10002010 = 0x40000000;
        n.cmd = 3;
        RunMpegCallback(o->f858, &n);
        DisableInterrupts();
        *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
        *(volatile u32*)0x1000B000 = 0;
        *(u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
        EnableInterrupts();
        *(volatile u32*)0x1000B020 = 0;
    }
    return result;
}

struct Ctx_0020E100;
s32 func_0020F248(Ctx_0020E100* self, s32 kind);

s32 func_0020E100(Ctx_0020E100* self)
{
	return DecodeIpuVariableLength(self, 3);
}

struct Mode_E120 { u8 pad[0x174]; s32 mode; s32 flag; };

void func_0020E120(Mode_E120* self, s32* out, s32* in, s32 x, s32 y)
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

s32 func_0020F248(struct Node_20E2A8 *self, s32 a1);
s32 func_0020F3C0(struct Node_20E2A8 *self, s32 a1);
void func_0020F4C8(struct Node_20E2A8 *self, s32 a1);
void func_0020B940(struct Node_20E2A8 *self, const char *a1, s32 a2);

s32 func_0020E2A8(struct Node_20E2A8 *self) {
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
            if (self->field848 != 0 && v3 == 0xF) {
                SkipIpuBits(self, 0xB);
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

s32 func_0020E5F0(Ctx_20E3B8* c, s32 n);
void func_0020F0F0(Ctx_20E3B8* c);
s32 func_0020DF10(Ctx_20E3B8* c);
void func_0020CF18(Ctx_20E3B8* c, s32 a);
void func_0020B978(Ctx_20E3B8* c, const char* s);

s32 func_0020E3B8(Ctx_20E3B8* c)
{
    s32 r;
    s32 n;
    s32 res;
    c->f810 = 0;
    c->f814 = 0;
    n = c->f12C * c->f130;
    if (c->f174 != 3) n = n >> 1;
    do {
        r = DecodeSliceMacroblocks(c, n);
    } while (r == 1 || r == 3);
    WaitIpuCommandDone(c);
    if (WaitIpuDecodeDone(c) == 0) r = 2;
    while ((*(volatile u32*)0x1000D400 >> 8) & 1) {}
    if (r == 0) AddMacroblockResiduals(c, c->f810 == 0);
    if ((u32)(r - 1) < 2) ReportMpegError(c, "= Skip to the next picture =");
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

void func_0020F708(struct Ctx_20E4C0 *self);
s32 func_0020F3C0(struct Ctx_20E4C0 *self, s32 a1);
void func_0020B940(struct Ctx_20E4C0 *self, const char *a1, u32 a2);
void func_0020F4C8(struct Ctx_20E4C0 *self, s32 a1);
s32 func_0020F788(struct Ctx_20E4C0 *self);
s32 func_0020E2A8(struct Ctx_20E4C0 *self);
void func_0020B978(struct Ctx_20E4C0 *self, const char *a1);

s32 func_0020E4C0(struct Ctx_20E4C0 *self, s32 a1, s32 *outA, s32 *outB, struct Out_20E4C0 *outC) {
    u32 s2;
    s32 s3;
    s32 e;

    self->f11C = 0;
    FindNextStartCode(self);
    s2 = (u32)PeekIpuBits(self, 0x20);
    if (s2 - 0x101 >= 0xAF) {
        ReportMpegErrorFormat(self, "slice_start_code(0x%08x) out of range", s2);
        return 2;
    }
    SkipIpuBits(self, 0x20);
    s3 = func_0020F788(self);
    e = func_0020E2A8(self);
    *outB = e;
    if (self->f11C != 0) {
        ReportMpegError(self, "_sliceA0(): error happens");
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

s32 func_0020E4C0(Ctx_20E5F0* c, s32 n, s32* i, s32* j, Buf_20E5F0* b);
s32 func_0020DF10(Ctx_20E5F0* c);
s32 func_0020F3C0(Ctx_20E5F0* c, s32 k);
s32 func_0020E2A8(Ctx_20E5F0* c);
void func_0020B978(Ctx_20E5F0* c, const char* s);
s32 func_0020E8A0(Ctx_20E5F0* c, s32* a, s32* b, s32* d, Buf_20E5F0* e, Half_20E5F0* f, Half_20E5F0* g);
s32 func_0020E7E0(Ctx_20E5F0* c, Buf_20E5F0* e, s32* b, Half_20E5F0* f, s32* a);
s32 func_0020C1A0(Ctx_20E5F0* c, s32 i, s32 j, s32 a, s32 b, Buf_20E5F0* e, Half_20E5F0* f, Half_20E5F0* g);
void func_0020CF18(Ctx_20E5F0* c, s32 v);

s32 func_0020E5F0(Ctx_20E5F0* c, s32 n)
{
    Buf_20E5F0 e;
    Half_20E5F0 f;
    Half_20E5F0 g;
    s32 i, j, a, b, d;
    i = 0;
    j = 0;
    s32 r = func_0020E4C0(c, n, &i, &j, &e);
    if (r != 0) return r;
    c->f11c = 0;
    for (;;) {
        if (!(i < n)) return 0;
        *(s32*)((u8*)c + c->f810 * 0x140 + 0x6CC) = 0;
        if (WaitIpuDecodeDone(c) == 0) return 2;
        if (j == 0) {
            if (PeekIpuBits(c, 0x17) == 0) {
                c->f11c = 0;
                return 3;
            }
            if (c->f11c != 0) {
                c->f11c = 0;
                return 3;
            }
            j = func_0020E2A8(c);
            if (c->f11c != 0) {
                c->f11c = 0;
                return 1;
            }
        }
        if (!(i < n)) {
            ReportMpegError(c, "Too many macroblocks in picture");
            return 2;
        }
        if (j == 1) {
            if (func_0020E8A0(c, &a, &b, &d, &e, &f, &g) == 0) {
                c->f11c = 0;
                return 1;
            }
        } else {
            if (func_0020E7E0(c, &e, &b, &f, &a) == 0) {
                c->f11c = 0;
                return 2;
            }
        }
        if (PrepareMacroblockPrediction(c, i, j, a, b, &e, &f, &g) == 0) {
            c->f11c = 0;
            return 2;
        }
        if (i != 0) AddMacroblockResiduals(c, c->f810 ^ 1);
        i = i + 1;
        c->f810 = c->f810 ^ 1;
        j = j - 1;
    }
}

struct Node_20E7E0 {
    s32 field0;
};

void func_0020B978(struct Node_20E7E0 *self, const char *a1);

s32 func_0020E7E0(struct Node_20E7E0 *self, s32 *a1, s32 *a2, s32 *a3, s32 *flags)
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
        ReportMpegError(self, "skiped macroblock in I picure is not allowed");
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

s16 func_0020F248(Self_20E8A0* self, s32 mode);
void func_0020B978(Self_20E8A0* self, const char* msg);
s32 func_0020F5B8(Self_20E8A0* self, s32 n);
void func_0020F4C8(Self_20E8A0* self, s32 n);
void func_0020F0F0(Self_20E8A0* self);
void func_0020F0C0(Self_20E8A0* self, s32 v);
void func_00210D90(s32 a, s32 b);
void func_0020EDD0(Self_20E8A0* self, s32* b1, s32* b2, s32* o5, s32 a4, s32 a5, s32 a6, s32 a7, s32 s0, s32 s8, s32 s10);
void func_0020EF70(Self_20E8A0* self, s32* b1, s32* b2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);

s32 func_0020E8A0(Self_20E8A0* self, s32* st, s32* mode, s32* o3, s32* b1, s32* o5, s32* b2)
{
    s32 m3, m4, m7, mfp;
    s32 v;

    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xF8FFFFFF) | (self->f150 << 24);
    v = DecodeIpuVariableLength(self, 1);
    *st = v;
    if (v == 0) {
        ReportMpegError(self, "Invalid macroblock_type code: 0");
        self->f11C = 1;
        return 0;
    }
    if (v & 0xC) {
        if (self->f174 == 3 && self->f17C != 0) {
            *mode = 2;
        } else {
            *mode = func_0020F5B8(self, 2);
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
            w = ReadIpuBits(self, 1);
        } else {
            w = 0;
        }
    } else {
        w = 0;
    }
    *o3 = w;
    if (*st & 0x10) {
        self->f1B4 = ReadIpuBits(self, 5);
    }
    if ((*st & 8) || ((*st & 1) && self->f180)) {
        if (self->f848) {
            func_0020EDD0(self, b1, b2, o5, 0, m3, m4, self->f164 - 1, self->f168 - 1, mfp, m7);
        } else {
            s32 t = self->f158 - 1;
            func_0020EF70(self, b1, b2, t, t, 0, 0, self->f154);
        }
    }
    if (self->f11C) {
        return 0;
    }
    if (*st & 4) {
        if (self->f848) {
            func_0020EDD0(self, b1, b2, o5, 1, m3, m4, self->f16C - 1, self->f170 - 1, 0, m7);
        } else {
            s32 t = self->f160 - 1;
            func_0020EF70(self, b1 + 2, b2, t, t, 0, 0, self->f15C);
        }
    }
    if (self->f11C) {
        return 0;
    }
    if ((*st & 1) && self->f180) {
        SkipIpuBits(self, 1);
    }
    if (*st & 3) {
        func_00210D90(*(s32*)((u8*)self + self->f810 * 0x140 + 0x594), 0x300);
        WaitIpuCommandDone(self);
        s32 x = ((*st & 1) << 27) | (self->f1B4 << 16);
        s32 y = (self->f1B0 << 26) | 0x20000000;
        s32 z = *o3 << 25;
        SendIpuCommand(self, x | y | z);
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

INCLUDE_ASM(func_0020ED48);

struct Ctx_20EDD0;
s32 func_0020F5B8(Ctx_20EDD0* c, s32 n);
void func_0020EF70(Ctx_20EDD0* c, u8* p, s32 a2, s32 a3, s32 a4, s32 a5, s32* a6, s32 a7);

void func_0020EDD0(Ctx_20EDD0* c, u8* arr, s32 a2, s32* out, s32 i, s32 mode, s32 a6, s32 a7, s32 s6, s32 s3, s32* fp)
{
    s32 v;
    s32* o;

    if (mode == 1) {
        if (a6 == 0 && s3 == 0) {
            v = ReadIpuBits(c, 1);
            out[i] = v;
            out[i + 2] = v;
        }
        i <<= 3;
        func_0020EF70(c, arr + i, a2, a7, s6, s3, fp, 0);
        u32* q = (u32*)(arr + i);
        u32 x = q[0];
        u32 y = q[1];
        q[4] = x;
        q[5] = y;
    } else {
        s32 j = i << 3;
        v = ReadIpuBits(c, 1);
        out[i] = v;
        o = out + i;
        func_0020EF70(c, arr + j, a2, a7, s6, s3, fp, 0);
        o[2] = ReadIpuBits(c, 1);
        func_0020EF70(c, arr + (j + 16), a2, a7, s6, s3, fp, 0);
    }
}

struct Self_20EF70 { s32 f00; };
struct Node_20EF70 { s32 f00; s32 f04; };

s32 func_0020F248(Self_20EF70* self, s32 mode);
s32 func_0020F5B8(Self_20EF70* self, s32 x);
s32 func_0020E100(Self_20EF70* self);
void func_0020ED48(Node_20EF70* n, s32 a, s32 b, s32 c, s32 d);

void func_0020EF70(Self_20EF70* self, Node_20EF70* n, s32* out, s32 p3, s32 p4, s32 want, s32 shift, s32 p7)
{
    s32 s0;
    s32 a3;

    s0 = DecodeIpuVariableLength(self, 2);
    if (p3 != 0 && s0 != 0) {
        a3 = ReadIpuBits(self, p3);
    } else {
        a3 = 0;
    }
    func_0020ED48(n, p3, s0, a3, p7);
    if (want != 0) {
        out[0] = func_0020E100(self);
    }
    s0 = DecodeIpuVariableLength(self, 2);
    if (p4 != 0 && s0 != 0) {
        a3 = ReadIpuBits(self, p4);
    } else {
        a3 = 0;
    }
    if (shift != 0) {
        n->f04 = n->f04 >> 1;
    }
    func_0020ED48((Node_20EF70*)&n->f04, p4, s0, a3, p7);
    if (shift != 0) {
        n->f04 = n->f04 << 1;
    }
    if (want != 0) {
        out[1] = func_0020E100(self);
    }
}

struct Obj_20F0C0 { u8 pad[0x818]; u32 value; };
u32 D_0027B040[10] = { 0x1, 0x1, 0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1 };

void func_0020F0C0(Obj_20F0C0* obj, u32 value)
{
    u32 index = value >> 28;
    volatile u32* setting = (volatile u32*)0x10002000;
    *setting = value;
    obj->value = D_0027B040[index];
}

struct Dev_0020F0F0;

struct Obj_0020F0F0 {
    u8 pad_000[0x858];     // 0x000
    s32 dev;               // 0x858
};

s32 func_0020B1E0(Dev_0020F0F0* d);

s32 func_0020F0F0(Obj_0020F0F0* self)
{
    s32 n = 0;
    if ((s32)(*(volatile u32*)0x10002010 & 0x80004000) == (s32)0x80000000) {
        do {
            s32 c = n;
            n = c + 1;
            if (c >= 0x1389) {
                RunMpegStallCallback((Dev_0020F0F0*)self->dev);
                n = 0;
            }
        } while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000);
        return n;
    }
    return 0x80000000;
}

struct Dev_0020F198;
struct Ctx_0020F198 { u8 pad[0x858]; Dev_0020F198* dev; };
s32 func_0020B1E0(Dev_0020F198* a);

s64 func_0020F198(Ctx_0020F198* p) {
    s32 i = 0;
    s64 v = *(volatile s64*)0x10002000;
    if (v < 0 && (*(volatile u32*)0x10002010 & 0x4000) == 0) {
        do {
            s32 old = i;
            i++;
            if (old >= 5001) {
                RunMpegStallCallback(p->dev);
                i = 0;
            }
            v = *(volatile s64*)0x10002000;
        } while (v < 0 && (*(volatile u32*)0x10002010 & 0x4000) == 0);
    }
    return v;
}

extern u32 D_0027B040[];

struct Sub_20F248;
struct Self_20F248 {
    u8 pad0[0x11C];
    s32 f11C;
    u8 pad1[0x6F8];
    s32 f818;
    u8 pad2[0x1C];
    s32 f838;
    s32 f83C;
    u8 pad3[0x18];
    Sub_20F248* f858;
};

s32 func_0020B1E0(Sub_20F248* s);

s16 func_0020F248(Self_20F248* self, s32 mode)
{
    s32 m = 0;
    s32 n = 0;
    s32 cmd;
    s64 st;
    s64 hw;

    if ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000) {
        do {
            if (n++ >= 5001) {
                RunMpegStallCallback(self->f858);
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
                RunMpegStallCallback(self->f858);
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

struct Obj_20F3C0 {
    u8 pad0[0x818];
    s32 f818;
    u8 pad81C[0x838 - 0x81C];
    s32 f838;
    s32 f83C;
    u8 pad840[0x858 - 0x840];
    u8* f858;
};

s64 func_0020F198(Obj_20F3C0* obj);
s32 func_0020B1E0(u8* p);

extern u32 D_0027B040[];

s32 func_0020F3C0(Obj_20F3C0* obj, s32 a1)
{
    if (obj->f818 != 0 || obj->f83C < a1) {
        s32 cnt = 0;
        while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000) {
            if (cnt++ > 0x1388) {
                RunMpegStallCallback(obj->f858);
                cnt = 0;
            }
        }
        *(volatile u32*)0x10002000 = 0x40000000;
        obj->f818 = D_0027B040[4];
        obj->f838 = func_0020F198(obj);
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
extern s32 func_0020B1E0(Arg_20F4C8* a);
extern s64 func_0020F198(Ctx_20F4C8* c, u32* v);

void func_0020F4C8(Ctx_20F4C8* s0, u32 s1)
{
    s32 cnt = 0;
    u32 v;
    u32* p;

    while ((*(volatile u32*)0x10002010 & 0x80004000u) == 0x80000000u) {
        if (cnt++ > 0x1388) {
            RunMpegStallCallback((Arg_20F4C8*)s0->f858);
            cnt = 0;
        }
    }
    v = s1 | 0x40000000u;
    *(volatile u32*)0x10002000 = v;
    p = &D_0027B040[v >> 28];
    s0->f818 = *p;
    s0->f838 = func_0020F198(s0, p);
    s0->f83C = 0x20;
}

struct Obj_20F5B8 {
    u8 pad0[0x818];
    s32 f818;
    u8 pad81C[0x838 - 0x81C];
    s32 f838;
    s32 f83C;
    u8 pad840[0x858 - 0x840];
    u8* f858;
};

s64 func_0020F198(Obj_20F5B8* obj);
s32 func_0020B1E0(u8* p);

extern u32 D_0027B040[];

struct Cmd_20F5B8 {
    static void Send(Obj_20F5B8* obj, u32 cmd)
    {
        *(volatile u32*)0x10002000 = cmd;
        obj->f818 = D_0027B040[cmd >> 28];
        obj->f838 = func_0020F198(obj);
    }
};

s32 func_0020F5B8(Obj_20F5B8* obj, s32 a1)
{
    s32 cnt = 0;
    u32 v;
    while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000) {
        if (cnt++ > 0x1388) {
            RunMpegStallCallback(obj->f858);
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

struct Obj_0020F708 { u8 pad[4]; };
void func_0020F0F0(Obj_0020F708* self);
void func_0020F4C8(Obj_0020F708* self, s32 mode);
s32 func_0020F3C0(Obj_0020F708* self, s32 mode);
void func_0020F708(Obj_0020F708* self)
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

struct Obj_20F788 {
    u8 pad0[0x1B4];
    s32 f1B4;
};

s32 func_0020F5B8(Obj_20F788* self, s32 arg);
void func_0020F4C8(Obj_20F788* self, s32 arg);
void func_0020FCE0(Obj_20F788* self);

s32 func_0020F788(Obj_20F788* self)
{
    self->f1B4 = ReadIpuBits(self, 5);
    if (ReadIpuBits(self, 1) != 0) {
        ReadIpuBits(self, 1);
        SkipIpuBits(self, 7);
        func_0020FCE0(self);
    }
    return 0;
}

struct Self_0020F7F0 { u8 pad000[0x150]; s32 f150; u8 pad154[0x828 - 0x154]; s64 f828; s64 f830; u8 pad838[0x858 - 0x838]; s32 f858; };
struct Loc_0020F7F0 { s32 a; s64 b; s64 c; };

void func_0020F708(Self_0020F7F0* self);
s32 func_0020F5B8(Self_0020F7F0* self, s32 mask);
void func_0020B9F0(Self_0020F7F0* self);
void func_0020FDA0(Self_0020F7F0* self);
void func_0020F900(Self_0020F7F0* self);
void func_0020B190(s32 a0, Loc_0020F7F0* out);

s32 func_0020F7F0(Self_0020F7F0* self)
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
            Loc_0020F7F0 loc;
            ReadPictureHeader(self);
            loc.a = 5;
            loc.b = -1;
            loc.c = -1;
            RunMpegCallback(self->f858, &loc);
            self->f830 = loc.c;
            self->f828 = loc.b;
            return self->f150;
        }
    }
}

struct Obj_0020F900 {
    u8 pad000[0x150];
    s32 f150;
    s32 f154;
    s32 f158;
    s32 f15C;
    s32 f160;
};

s32 func_0020F5B8(Obj_0020F900* self, s32 bits);
void func_0020FCE0(Obj_0020F900* self);
void func_0020F9C8(Obj_0020F900* self);
s32 func_0020FD28(Obj_0020F900* self, s32 a1);

void func_0020F900(Obj_0020F900* self)
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
    func_0020FCE0(self);
    ReadExtensionsAndUserData(self);
    func_0020FD28(self, first);
}

struct Self_0020F9C8;

typedef void (*Fn_0020F9C8)(struct Self_0020F9C8* self);

struct __attribute__((packed)) Pack_0020F9C8 {
    u64 a[5];
};

struct Tbl_0020F9C8 {
    struct Pack_0020F9C8 p;
    Fn_0020F9C8 last;
};

union TblU_0020F9C8 {
    struct Tbl_0020F9C8 t;
    Fn_0020F9C8 fn[11];
};

void func_0020F708(struct Self_0020F9C8* self);
void func_0020F4C8(struct Self_0020F9C8* self, s32 a1);
s32 func_0020F5B8(struct Self_0020F9C8* self, s32 a1);
s32 func_0020F3C0(struct Self_0020F9C8* self, s32 a1);

// An entry of the table of extension handlers below.
typedef void (*Fn_Table)();
struct Obj_20FE40;
struct Ctx_20FAF0;
struct Self_0020FF08;
struct Bits_210000;
void func_0020FAF0(Ctx_20FAF0* c);
void func_0020FE40(struct Obj_20FE40 *self);
void func_0020FF08(Self_0020FF08* self);
void func_00210000(Bits_210000* self);
// The handlers of the extensions by their 4-bit id, the sequence's in src/lib/mpeg_decoder.cpp.
void func_0020BF78();
void func_0020C0A8();
void func_0020C138();
void func_0020C148();
void func_0020C158();
void func_0020C168();
extern const Fn_Table D_00250430[12] = { (Fn_Table)func_0020C148, (Fn_Table)func_0020BF78, (Fn_Table)func_0020C0A8, (Fn_Table)func_0020FE40, (Fn_Table)func_00210000, (Fn_Table)func_0020C138, (Fn_Table)func_0020C148, (Fn_Table)func_0020FF08, (Fn_Table)func_0020FAF0, (Fn_Table)func_0020C158, (Fn_Table)func_0020C168, 0 };

void func_0020F9C8(struct Self_0020F9C8* self)
{
    s32 kA = 0x1B2;
    union TblU_0020F9C8 t;
    t.t = *(struct Tbl_0020F9C8*)((u8*)D_00250430);
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

struct Ctx_20FAF0 {
    u8 pad0[0xD4];
    s32 f_d4;
    u8 pad1[0x164 - 0xD8];
    s32 f164, f168, f16c, f170, f174, f178, f17c, f180, f184, f188;
};

s32 func_0020F5B8(Ctx_20FAF0* c, s32 n);

void func_0020FAF0(Ctx_20FAF0* c)
{
    c->f164 = ReadIpuBits(c, 4);
    c->f168 = ReadIpuBits(c, 4);
    c->f16c = ReadIpuBits(c, 4);
    c->f170 = ReadIpuBits(c, 4);
    *(u32*)0x10002010 = (*(u32*)0x10002010 & 0xFFFCFFFF) | (func_0020F5B8(c, 2) << 16);
    s32 v = ReadIpuBits(c, 2);
    c->f174 = v;
    if (c->f_d4 == 0) c->f_d4 = v;
    c->f178 = ReadIpuBits(c, 1);
    c->f17c = ReadIpuBits(c, 1);
    c->f180 = ReadIpuBits(c, 1);
    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xFFBFFFFF) | (func_0020F5B8(c, 1) << 22);
    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xFFDFFFFF) | (func_0020F5B8(c, 1) << 21);
    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xFFEFFFFF) | (func_0020F5B8(c, 1) << 20);
    c->f184 = ReadIpuBits(c, 1);
    ReadIpuBits(c, 1);
    c->f188 = ReadIpuBits(c, 1);
    if (ReadIpuBits(c, 1) == 0) return;
    ReadIpuBits(c, 1);
    ReadIpuBits(c, 3);
    ReadIpuBits(c, 1);
    ReadIpuBits(c, 7);
    ReadIpuBits(c, 8);
}

struct Obj_0020FCE0;

s32 func_0020F5B8(Obj_0020FCE0* self, s32 a1);
void func_0020F4C8(Obj_0020FCE0* self, s32 a1);

void func_0020FCE0(Obj_0020FCE0* self)
{
    while (ReadIpuBits(self, 1))
        SkipIpuBits(self, 8);
}

struct Obj_20FD28 {
    u8 pad0[0x150];
    s32 f150;
    u8 pad1[0x1AC - 0x154];
    s32 f1AC;
    u8 pad2[0x84C - 0x1B0];
    s32 f84C;
    s32 f850;
    s32 f854;
};

s32 func_0020FD28(Obj_20FD28* self, s32 a1)
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

struct Obj_0020FDA0 {
    u8 pad000[0xE8];
    s32 fE8;
    u8 padEC[0x1A4 - 0xEC];
    s32 f1A4;
    s32 f1A8;
    u8 pad1AC[0x84C - 0x1AC];
    s32 f84C;
    s32 f850;
    s32 f854;
};

s32 func_0020F5B8(Obj_0020FDA0* self, s32 bits);
void func_0020F9C8(Obj_0020FDA0* self);

void func_0020FDA0(Obj_0020FDA0* self)
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

struct Obj_20FE40 {
    u8 pad[0x840];
    void *field840;
    void *field844;
};

void* func_0020F5B8(struct Obj_20FE40 *self, s32 a1);
void func_0020F0F0(struct Obj_20FE40 *self);
void func_0020F0C0(struct Obj_20FE40 *self, u32 value);
void func_0020B978(struct Obj_20FE40 *self, const char *a1);

void func_0020FE40(struct Obj_20FE40 *self)
{
    void *v;

    v = ReadIpuBits(self, 1);
    self->field840 = v;
    if (v != 0) {
        WaitIpuCommandDone(self);
        SendIpuCommand(self, 0x50000000);
        WaitIpuCommandDone(self);
    }
    v = ReadIpuBits(self, 1);
    self->field844 = v;
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
    return ReportMpegError(self, "load_chroma_non_intra_quantizer_matrix == 1");
}

struct Self_0020FF08 {
    u8 pad0[0x13C];
    s32 f13C;
    u8 pad1[0x174 - 0x140];
    s32 f174;
    s32 f178;
    u8 pad2[0x184 - 0x17C];
    s32 f184;
    u8 pad3[0x18C - 0x188];
    s32 a[3];
    s32 b[3];
};

s32 func_0020F5B8(Self_0020FF08* self, s32 k);

void func_0020FF08(Self_0020FF08* self)
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
        self->a[i] = ReadIpuBits(self, 0x10);
        ReadIpuBits(self, 1);
        self->b[i] = ReadIpuBits(self, 0x10);
        ReadIpuBits(self, 1);
    }
}

struct Bits_210000;
u32 func_0020F5B8(Bits_210000* self, u32 n);

void func_00210000(Bits_210000* self)
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

struct Sub_210090 { u8 pad[0x28]; s32 f28; };
struct Obj_210090 {
    u8 pad0[0x120];
    s32 f120;
    u8 pad1[0x50];
    s32 f174;
    u8 pad2[0x48];
    Sub_210090* f1C0;
    u8 pad3[0xC];
    Sub_210090* f1D0;
    u8 pad4[0xC];
    Sub_210090* f1E0;
};

s32 func_0020B978(Obj_210090* self, void* a1);
s32 func_0020E3B8(Obj_210090* self);

s32 func_00210090(Obj_210090* self)
{
    Sub_210090* s1;
    s32 v;
    s32 mode = self->f174;
    if (mode == 3 && self->f120 != 0) {
        ReportMpegError(self, (u8*)"odd number of field pictures");
        self->f120 = 0;
        mode = self->f174;
    }
    switch (mode) {
    case 3:
        s1 = self->f1C0;
        break;
    case 1:
        s1 = self->f1D0;
        break;
    case 2:
        s1 = self->f1E0;
        break;
    default:
        s1 = self->f1C0;
        ReportMpegError(self, (u8*)"unknown picture sutructure");
        break;
    }
    v = DecodeAllMacroblocks(self);
    if (v != 0) {
        s1->f28 = 1;
    }
    return v;
}

struct Node_210160 {
    u8 pad000[0xF8];
    s32 f0F8;
    u8 pad0FC[0x54];
    s32 f150;
    u8 pad154[0x20];
    s32 f174;
    u8 pad178[0x40];
    s32 f1B8;
    u8 pad1BC[0x8];
    s32 f1C4;
    s32 f1C8;
    u8 pad1CC[0x8];
    s32 f1D4;
    s32 f1D8;
    u8 pad1DC[0x8];
    s32 f1E4;
};

void func_00210970(struct Node_210160* a, s32 b, s32 c);
void func_00210A80(struct Node_210160* a, s32 b, s32 c, s32 d);

void func_00210160(struct Node_210160* self, s32 count, s32 flag)
{
    s32 n = count;
    if (flag != 0) {
        if (self->f174 == 3) {
            s32 x;
            if (self->f150 == 3) {
                x = self->f1C4;
            } else {
                x = self->f1B8;
            }
            func_00210970(self, x, n - 1);
        } else {
            s32 x;
            s32 y;
            if (self->f150 == 3) {
                x = self->f1D4;
                y = self->f1E4;
            } else {
                x = self->f1C8;
                y = self->f1D8;
            }
            n = n - 1;
            func_00210A80(self, x, y, n);
        }
    }
    if (self->f0F8 == 1) {
        self->f0F8 = 2;
    }
}

struct Sub_2101F0 {
    u8 pad00[0x18];
    u64 f18;
    u64 f20;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
    s32 f50;
    s32 f54;
    s32 f58;
    s32 f5C;
    s32 f60;
};

struct Obj_2101F0 {
    u8 pad000[0xA0];
    s32 fA0;
    s32 fA4;
    u8 pad0A8[0xE8 - 0xA8];
    s32 fE8;
    u8 pad0EC[0x13C - 0xEC];
    s32 f13C;
    u8 pad140[0x148 - 0x140];
    s32 f148;
    s32 f14C;
    s32 f150;
    u8 pad154[0x174 - 0x154];
    s32 f174;
    s32 f178;
    u8 pad17C[0x184 - 0x17C];
    s32 f184;
    s32 f188;
    s32 f18C;
    s32 f190;
    s32 f194;
    s32 f198;
    s32 f19C;
    s32 f1A0;
    s32 f1A4;
    s32 f1A8;
    u8 pad1AC[0x1B8 - 0x1AC];
    Sub_2101F0* f1B8;
    Sub_2101F0* f1BC;
    Sub_2101F0* f1C0;
    Sub_2101F0* f1C4;
    Sub_2101F0* f1C8;
    Sub_2101F0* f1CC;
    Sub_2101F0* f1D0;
    Sub_2101F0* f1D4;
    Sub_2101F0* f1D8;
    Sub_2101F0* f1DC;
    Sub_2101F0* f1E0;
    Sub_2101F0* f1E4;
    u8 pad1E8[0x828 - 0x1E8];
    u64 f828;
    u64 f830;
};

s32 func_002101F0(Obj_2101F0* p, s32 flag)
{
    Sub_2101F0* o = 0;
    s32 ok = 0;
    s32 lim = p->f174 == 3 ? 2 : 4;

    if (p->f150 == 3) {
        p->f1C0 = p->f1C4;
        p->f1D0 = p->f1D4;
        p->f1E0 = p->f1E4;
        if (p->fA0 + p->fA4 >= lim) {
            p->fE8 = 0;
            p->f1A8 = 0;
            p->f1A4 = 0;
        }
        if ((p->fE8 || p->f1A8) && !p->f1A4) {
            p->f1B8->f28 = 0;
            p->f1C8->f28 = 0;
            p->f1D8->f28 = 0;
        }
        p->fE8 = 0;
        p->f1A8 = 0;
        if (p->f174 == 3) {
            if ((p->f1B8->f28 == 1 || p->f1A4) && p->f1BC->f28 == 1) ok = 1;
        } else {
            if (((p->f1C8->f28 == 1 && p->f1D8->f28 == 1) || p->f1A4) && p->f1CC->f28 == 1 && p->f1DC->f28 == 1) ok = 1;
        }
    } else {
        if (flag == 0) {
            Sub_2101F0* t;
            t = p->f1B8; p->f1B8 = p->f1BC; p->f1BC = t;
            t = p->f1C8; p->f1C8 = p->f1CC; p->f1CC = t;
            t = p->f1D8; p->f1D8 = p->f1DC; p->f1DC = t;
        }
        p->f1C0 = p->f1BC;
        p->f1D0 = p->f1CC;
        p->f1E0 = p->f1DC;
        if (p->f174 == 3) {
            if (p->f150 != 2 || p->f1B8->f28 == 1) ok = 1;
        } else {
            Sub_2101F0* x = p->f174 == 1 ? p->f1DC : p->f1CC;
            if (p->f150 != 2) ok = 1;
            else if ((flag && x->f28 == 1) || (p->f1C8->f28 == 1 && p->f1D8->f28 == 1)) ok = 1;
        }
    }

    switch (p->f174) {
    case 2: o = p->f1E0; break;
    case 1: o = p->f1D0; break;
    case 3: o = p->f1C0; break;
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
    o->f44 = p->f18C;
    o->f48 = p->f190;
    o->f4C = p->f194;
    o->f50 = p->f198;
    o->f54 = p->f19C;
    o->f58 = p->f1A0;
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

s32 func_001E1FD0(char *dst, const char *fmt, ...);
s32 func_0020B978(struct Node_2104A8 *self, char *buf);

s32 func_002104A8(struct Node_2104A8 *self, struct Rec_2104A8 *rec) {
    char buf[0x100];
    s32 flag;
    if (self->fE0 != 0)
        flag = self->fDC >= rec->f4 && self->fE0 >= rec->f8;
    else
        flag = self->fE4 >= rec->fC * rec->f10;
    if (flag == 0) {
        FormatToString(buf, "Too small buffer size for %dx%d picture\n", rec->f4, rec->f8);
        ReportMpegError(self, buf);
    }
    return flag;
}

INCLUDE_ASM(func_00210548);

struct Object_2107B8 { u8 pad1[8]; s32 mode; u8 pad2[0xA0]; s32 fieldAC; u8 pad3[0x68]; s32 field118; u8 pad4[0x704]; s32 field820; };

s32 func_002107B8(Object_2107B8* obj)
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

struct Obj_2107E0 {
    u8 pad0[0x70];
    s32 f70;
    u8 pad1[0x4];
    s64 f78;
    s32 f80;
    u8 pad2[0x4];
    s64 f88;
    s32 f90;
    u8 pad3[0x5C];
    s64 fF0;
    s32 fF8;
};

s64 func_001FE890(s64 a, s64 b);

void func_002107E0(Obj_2107E0* self, Node_2107E0* node, s64* out1, s64* out3, s64* out4)
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
                v = func_001FE890(s2, self->f78 & 1);
                s6 = self->f90;
                v = func_001FE890(v, s6 & 1);
                s1 = (s32)v;
                *out1 = (s64)(s7 + ((s32)(func_001FE890(self->f78, s0) >> 1) + s1));
                if (func_001FE890(s2, self->f78 & 1)) {
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

INCLUDE_ASM(func_00210970);

struct Blk_210A80 { u8 p0[0x10]; s32 f10; u8 p14[0xC]; u64 f20; s32 f28; u8 p2C[0xC]; u64 f38; };
struct Src_210A80 { u8 p0[0x10]; s32 f10; u8 p14[0x14]; s32 f28; u8 p2C[0x18]; s32 f44; s32 f48; u8 p4C[4]; s32 f50; s32 f54; u8 p58[4]; s32 f5C; s32 f60; };
struct Ctx_210A80 {
    u8 p0[0x80]; s32 f80; u8 p84[4]; union { u64 d; u32 w[2]; } f88; u8 p90[0x20]; s32 fB0; s32 fB4; s32 fB8; u8 pBC[4]; s32 fC0; s32 fC4; u8 pC8[4]; s32 fCC; s32 fD0;
    u8 pD4[0x174 - 0xD4]; s32 f174; u8 p178[0x858 - 0x178]; Blk_210A80* f858;
};

void func_002107E0(Ctx_210A80* c, Src_210A80* s, void* a, void* b, void* d);
s32 func_002104A8(Ctx_210A80* c, Src_210A80* s);
void func_00211348(Ctx_210A80* c, Src_210A80* s);
s32 func_00210548(Ctx_210A80* c, Src_210A80* s);
s32 func_002107B8(Ctx_210A80* c);

void func_00210A80(Ctx_210A80* c, Src_210A80* a, Src_210A80* b)
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
    (void)func_002107E0(c, s3, (u8*)c->f858 + 0x10, (u8*)c->f858 + 0x18, (u8*)c->f858 + 0x20);
    c->f80 = c->f858->f10;
    c->f88.d = 1;
    (void)func_002107E0(c, s4, (u8*)c->f858 + 0x28, (u8*)c->f858 + 0x30, (u8*)c->f858 + 0x38);
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
    if (func_002104A8(c, a)) {
        if (a->f28 == 1 && b->f28 == 1) {
            a->f10 <<= 1;
            if (c->fB0) {
                ConvertPictureColours(c, a);
            } else {
                func_00210548(c, a);
            }
            a->f10 >>= 1;
            func_002107B8(c);
        }
    }

}

// The buffer of the hand-written func_00210C38, which only it reads.
static u8 D_0062C340[0x200];

ASM_FUNC(func_00210C38);

s32 func_001F9D60(void);
s32 func_001F9DA8(void);

void func_00210D90(u32 a, s32 b)
{
    DisableInterrupts();
    *(volatile u32*)0x1000B010 = (a & 0xFFFFFFF) | 0x80000000;
    *(volatile u32*)0x1000B020 = b >> 4;
    *(volatile u32*)0x1000B000 = 0x100;
    EnableInterrupts();
}

struct Hdl_210E00;
struct Obj_210E00 { u8 pad[0x858]; Hdl_210E00* f858; };

void func_0020F0C0(Obj_210E00* obj, u32 value);
s32 func_0020B190(Hdl_210E00* h, s32* p);

void func_00210E00(Obj_210E00* self, u32 a1, u32 a2)
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
    RunMpegCallback(self->f858, tmp);
    while ((*(volatile u32*)0x1000B000 >> 8) & 1) { }
    while (*(volatile s32*)0x10002010 < 0) { }
}

ASM_FUNC(func_00210F18);

struct Queue_211090;
struct Self_211090 {
    u8 pad000[0x858];
    Queue_211090* f858;
};

struct Msg_211090 {
    s32 cmd;
    s32 pad04[7];
};

struct Xfer_211090 {
    volatile s32 done;
    s32 error;
    s32 size;
    s32 addr;
    s32 total;
};

s32 func_001F6980(s32 channel, s32 (*handler)(s32, void*), s32 next, void* arg);
s32 func_001F6990(s32 channel, s32 id);
s32 func_001F6E10(s32 channel);
s32 func_001F6E78(s32 channel);
s32 func_001F9D60(void);
s32 func_001F9DA8(void);
s32 func_00210F18(s32 channel, void* arg);
s32 func_0020B190(Queue_211090* q, Msg_211090* m);
s32 func_0020B978(Self_211090* self, u8* msg);

void func_00211090(Self_211090* self, s32 addr, s32 size)
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
    s32 id = AddDmaHandlerAlt(3, func_00210F18, 0, &xfer);
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
        ReportMpegError(self, (u8*)"CSC handler error\n");
    }
    while (*(volatile s32*)0x10002010 < 0) {
    }
    DisableDmaInterrupt(3);
    RemoveDmaHandler(3, id);
}

struct Xfer_00211240 { u32 size; u32 addr; };

s32 func_001F9D60(void);
s32 func_001F9DA8(void);

s32 func_00211240(s32 unused, Xfer_00211240* p)
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

s32 func_001F6980(s32 channel, s32 (*handler)(s32, void*), s32 next, void* arg);
s32 func_001F6990(s32 channel, s32 id);
s32 func_001F6E10(s32 channel);
s32 func_001F6E78(s32 channel);
s32 func_001F9D60(void);
s32 func_001F9DA8(void);
s32 func_00211240(s32 unused, void* p);
s32 func_0020B190(Queue_211348* q, Msg_211348* m);
void func_0020F0C0(Self_211348* self, u32 value);
void func_00210E00(Self_211348* self, u32 addr, u32 size);
void func_00211090(Self_211348* self, s32 addr, s32 size);

void func_00211348(Self_211348* self, Desc_211348* d)
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
    SendIpuCommand(self, 0);
    u32 addr = d->addr;
    while (*(volatile s32*)0x10002010 < 0) {
    }
    u32 chunk = 0xFFFF;
    xfer.size = count * 0x18;
    xfer.addr = addr & 0xFFFFFFF;
    if (xfer.size > chunk) {
        s32 id = AddDmaHandlerAlt(4, func_00211240, 0, &xfer);
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
            func_00210E00(self, self->fD8, count);
        } else {
            func_00211090(self, self->fD8, count);
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
            func_00210E00(self, self->fD8, count);
        } else {
            func_00211090(self, self->fD8, count);
        }
    }
    msg.cmd = 3;
    RunMpegCallback(self->f858, &msg);
}
