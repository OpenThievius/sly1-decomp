/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The graphics library, one object in retail from 0x2018E0 to 0x202768: the reset of the paths
 * to the GS and their wait (assembly: they drive VU0 and VIF1 with macro instructions), the
 * reset of the GS and its parameters, the display and drawing environments and their transfer
 * through DMA channel 2. Its .data holds the two VIF1 words the path reset sends, the library's
 * identification string and the GS parameters; its .rodata its two messages. The linker
 * stripped the function before the first and left a remnant of it. C, built by the cc1 of
 * 2.9-ee-991111 (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's
 * code. */
#include "common.h"
#include "asm_func.h"

/* The GS parameters: interlacing, the video mode, the field or frame mode, the GS version. */
typedef struct GsParam {
    s16 interlace;
    s16 mode;
    s16 field;
    s16 version;
    s32 handler;
    s32 handler_id;
} GsParam;

/* The words the path reset writes to VIF1's FIFO, each 16 bytes. */
u32 D_00279300[4] __attribute__((aligned(16))) = { 0x01000404, 0x20000000, 0, 0x05000000 };
u32 D_00279310[4] __attribute__((aligned(16))) = { 0x06000000, 0x03000000, 0x02000000, 0x04000000 };
char D_00279320[16] = "PsIIlibgraph2400";
GsParam D_00279330 = { 1, 2, 1, 3, 0, 0 };

/* The display environment: what the reset writes to the GS's privileged registers. */
typedef struct GsDispEnv {
    u64 pmode;
    u64 smode2;
    u64 dispfb;
    u64 display;
    u64 bgcolor;
} GsDispEnv;

/* A 16-byte record of two 64-bit words of bitfields. */
typedef struct GifTag {
    u64 count : 15;
    u64 last : 1;
    u64 pad0 : 44;
    u64 words : 4;
    u64 kind : 4;
    u64 pad1 : 60;
} GifTag;

typedef struct Low9 {
    u64 value : 9;
    u64 pad : 55;
} Low9;

typedef int V128 __attribute__((mode(TI)));

/* The double buffer of display and drawing environments. */
typedef struct GsDBuff {
    u8 pad0[0x38];
    Low9 f38;
    u8 pad40[0x50 - 0x40];
    GifTag tag50;
    Low9 f60;
    u8 pad68[0x140 - 0x68];
    GifTag tag140;
} GsDBuff;

typedef struct GsOffset {
    u8 pad0[0x20];
    u64 out;
    u8 pad1[0x8];
    u64 in;
} GsOffset;

s32 func_001E1F10(const char* format, ...);
void func_001F6910(s32 interlace, s32 mode, s32 field);
void func_001F6960(s32 cause, s32 id);
s32 func_001F6C60(s32 mask);
s32 func_001F6C70(u64 mask);
void func_001F6D40(s32 cause);
GsParam* func_00201BA8(void);
void func_00202140(void* env, s32 psm, s32 w, s32 h, s32 ztest, s32 zpsm);
void func_00202478(void* env, s32 psm, s32 w, s32 h, s32 dx, s32 dy);
void func_00202660(void* env, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i, s32 j);
s32 func_002023B0(s16 psm, s16 w, s16 h);

LINKER_REMNANT(func_002018E0);
ASM_FUNC(func_002018E8);
ASM_FUNC(func_00201988);

void func_00201A18(s16 mode, s16 x, s16 y, s16 flag)
{
    GsParam* p;
    u16 ext;

    switch (mode) {
    case 0:
        p = func_00201BA8();
        *(volatile u64*)0x12001000 = 0x200;
        p->interlace = x;
        ext = (u16)((*(volatile u64*)0x12001000 >> 16) & 0xFF);
        p->mode = y;
        p->version = ext;
        WriteGsInterruptMask(0xFF00);
        p->field = (flag != 0);
        if (p->handler != 0) {
            DisableInterruptCause(2);
            RemoveInterruptHandler(2, p->handler_id);
            p->handler = 0;
            p->handler_id = 0;
        }
        SetVideoModeSyscall(x & 1, (u8)y, flag & 1);
        return;
    case 1:
        *(volatile u64*)0x12001000 = 0x100;
        return;
    case 5:
        p = func_00201BA8();
        p->field = (flag != 0);
        p->interlace = x;
        p->mode = y;
        p->version = (u16)((*(volatile u64*)0x12001000 >> 16) & 0xFF);
        SetVideoModeSyscall(x & 1, (u8)y, flag & 1);
        return;
    default:
        return;
    }
}

GsParam* func_00201BA8(void)
{
    return &D_00279330;
}

void func_00201BB8(void* self)
{
    s16 kind = func_00201BA8()->version;
    if (kind == 1) {
        *(volatile u64*)0x12000000 = *(u64*)self;
        *(volatile u64*)0x12000070 = *(u64*)((u8*)self + 0x10);
        *(volatile u64*)0x12000080 = *(u64*)((u8*)self + 0x18);
        *(volatile u64*)0x120000C0 = *(u64*)((u8*)self + 0x20);
    } else {
        *(volatile u64*)0x12000000 = *(u64*)self;
        *(volatile u64*)0x12000020 = *(u64*)((u8*)self + 8);
        *(volatile u64*)0x12000090 = *(u64*)((u8*)self + 0x10);
        *(volatile u64*)0x120000A0 = *(u64*)((u8*)self + 0x18);
        *(volatile u64*)0x120000E0 = *(u64*)((u8*)self + 0x20);
    }
}

s32 func_00201C78(void* self)
{
    u32 n = 0;
    if (*(volatile u32*)0x1000A000 & 0x100) {
        do {
            if (n++ > 0x1000000) {
                func_001E1F10("sceGsPutDrawEnv: DMA Ch.2 does not terminate\r\n");
                return -1;
            }
        } while (*(volatile u32*)0x1000A000 & 0x100);
    }
    *(volatile u32*)0x1000A020 = (s32)(*(s64*)self & 0x7FFF) + 1;
    if (((u32)self & 0x70000000) == 0x70000000) {
        *(volatile u32*)0x1000A010 = ((u32)self & 0x0FFFFFFF) | 0x80000000;
    } else {
        *(volatile u32*)0x1000A010 = (u32)self & 0x0FFFFFFF;
    }
    *(volatile u32*)0x1000A000 = 0x101;
    return 0;
}

void func_00201D60(GsDBuff* self, s16 a1, s16 w, s16 h, s16 a4, s16 a5, s16 flag)
{
    u8* base = (u8*)self;
    u64* mode = (u64*)func_00201BA8();
    s32 r;

    func_00202140(self, a1, w, h, 0, 0);
    func_00202140(base + 0x28, a1, w, h, 0, 0);
    func_00202478(base + 0x60, a1, w, h, a4, a5);
    func_00202478(base + 0x150, a1, w, h, a4, a5);
    if (flag) {
        s32 y = 0x800 - (w >> 1);
        s32 z = 0x800 - (h >> 1);
        func_00202660(base + 0xE0, a4, y, z, w, h, 0, 0, 0, 0, 0);
        func_00202660(base + 0x1D0, a4, y, z, w, h, 0, 0, 0, 0, 0);
    }
    *(V128*)&self->tag50 = 0;
    *(V128*)&self->tag140 = 0;
    self->tag50.count = flag ? 14 : 8;
    self->tag50.last = 1;
    self->tag50.words = 1;
    self->tag50.kind = 14;
    self->tag140.count = flag ? 14 : 8;
    self->tag140.last = 1;
    self->tag140.words = 1;
    self->tag140.kind = 14;
    r = func_002023B0(a1, w, h);
    if ((*mode & 0xFFFF0000FFFFULL) == 0x100000001ULL || *(s16*)mode == 0) {
        s16 half = r >> 1;
        self->f38.value = half;
        self->f60.value = r >> 1;
    }
}

s32 func_00201FF8(void* self, s32 flag)
{
    u8* base = (u8*)self;
    s32 idx = flag & 1;
    s32 r;

    func_00201BB8(base + idx * 0x28);
    if (idx != 0) {
        r = func_00201C78(base + 0x140);
    } else {
        r = func_00201C78(base + 0x50);
    }
    return r;
}

s32 func_00202058(s32 mask)
{
    s32 r = ReadGsInterruptMask(mask);
    WriteGsInterruptMask(mask);
    return r;
}

void func_00202098(GsOffset* self, s16 a1, s16 a2, s16 a3)
{
    u64 v = self->in;
    s64 y = (u64)((s32)((v >> 48) & 0x7FF) + 1) >> 1;
    s64 b2 = a2;
    s64 b1 = a1;
    s64 x = (u64)((s32)((v >> 16) & 0x7FF) + 1) >> 1;
    s64 t;
    u64 lo;
    u64 hi;

    b2 -= y;
    b1 -= x;
    t = b2 << 4;
    lo = b1 << 4;
    if (a3 != 0) {
        hi = (u64)(t + 8) << 32;
    } else {
        hi = (u64)t << 32;
    }
    self->out = lo | hi;
}

s32 func_00202120(s32 mask)
{
    return ReadGsInterruptMask(mask);
}

INCLUDE_ASM(func_00202140);

/* The message of func_00202140, defined here while it is assembly. */
const char D_0024F510[] = "sceGsDefDispEnv:Not support displaymode for %d!!\n";

s32 func_002023B0(s16 px, s16 py, s16 pz)
{
    u64* bits = (u64*)func_00201BA8();
    s32 yS = (py + 63) / 64;
    s32 c;
    if (px & 2) {
        c = (pz + 63) / 64;
    } else {
        c = (pz + 31) / 32;
    }
    if ((*bits & 0x0000FFFF0000FFFFULL) == 1) {
        return ((yS * c) << 16) >> 16;
    }
    return ((yS * c) << 17) >> 16;
}

ASM_FUNC(func_00202478);
ASM_FUNC(func_00202660);
