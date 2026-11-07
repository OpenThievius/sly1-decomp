// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c52.h"
#include "asm_func.h"

// Small overrides of three classes (0x76's set-up and transform read, the slot 0xA4 of 0x35 and
// of 0x52) and the VU0 helper func_0016C528. Its .rodata is func_0016C470's FLT_MAX literal at
// 0x24A7DC and, after it, two -FLT_MAX words no code reads.

void func_001DFD90(void* self);

struct Obj_16C470 {
    u8 pad0[0x88];
    s32 f88;
    u8 pad8C[0xA8 - 0x8C];
    s32 fA8;
    s32 fAC;
    u8 padB0[0xB4 - 0xB0];
    f32 fB4;
};

void func_0016C470(void* a0)
{
    Obj_16C470* self = (Obj_16C470*)a0;
    func_001DFD90(a0);
    self->f88 = 1;
    self->fA8 = 8;
    self->fAC = 9;
    self->fB4 = 3.4028234663852886e+38f;
}

// Two words no code reads, after func_0016C470's literal: those of functions the linker stripped
// (func_0016C4D8 is what it left of one). The zeros after them are the linker's padding before
// target_follower's 16-aligned .rodata.
extern const f32 D_0024A7E0 = -3.40282347e+38f;
extern const f32 D_0024A7E4 = -3.40282347e+38f;

void func_001F3A40(void);

void func_0016C4B8(void)
{
    ReadTransformObject();
}

LINKER_REMNANT(func_0016C4D8);

void func_001B93D8(void);

void func_0016C4E8(void)
{
    func_001B93D8();
}

void func_001261C0(void);

void func_0016C508(void)
{
    func_001261C0();
}

ASM_FUNC(func_0016C528);
