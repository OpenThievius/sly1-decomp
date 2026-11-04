// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 568/572 (99.3%), checked 2026-11-04
#include "common.h"
// NEAR: 2 swapped stores: D_00261118 .b and .g (retail stores b then g in the jal delay slot; ours g then b, with the two constants in swapped registers)

struct Rgba_136FE8 { u8 r, g, b, a; };
struct Block_136FE8 {
    u8 pad0[4];
    u8 f4;
    u8 pad5[3];
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u32 f18;
};

extern Rgba_136FE8 D_002610D0;
extern Rgba_136FE8 D_002610D8;
extern Rgba_136FE8 D_002610E0;
extern Rgba_136FE8 D_002610E8;
extern Rgba_136FE8 D_002610F0;
extern Rgba_136FE8 D_002610F8;
extern Rgba_136FE8 D_00261100;
extern Rgba_136FE8 D_00261108;
extern Rgba_136FE8 D_00261110;
extern Rgba_136FE8 D_00261118;
extern Block_136FE8 D_00261148;
extern Block_136FE8 D_00261168;
void func_001F5C0C(void* block, s32 value, s32 size);

void func_00136FE8(s32 a, s32 b)
{
    if (b == 0xFFFF && a != 0) {
        D_002610D0.r = 0x0;
        D_002610D0.g = 0x0;
        D_002610D0.b = 0x0;
        D_002610D0.a = 0x80;
        D_002610D8.r = 0x0;
        D_002610D8.g = 0x52;
        D_002610D8.b = 0x7E;
        D_002610D8.a = 0x80;
        D_002610E0.r = 0x19;
        D_002610E0.g = 0x1E;
        D_002610E0.b = 0x6E;
        D_002610E0.a = 0x80;
        D_002610E8.r = 0x7E;
        D_002610E8.g = 0x28;
        D_002610E8.b = 0xA;
        D_002610E8.a = 0x80;
        D_002610F0.r = 0x50;
        D_002610F0.g = 0x28;
        D_002610F0.b = 0x28;
        D_002610F0.a = 0x80;
        D_002610F8.r = 0xF0;
        D_002610F8.g = 0xF0;
        D_002610F8.b = 0x0;
        D_002610F8.a = 0x80;
        D_00261100.r = 0x28;
        D_00261100.g = 0x28;
        D_00261100.b = 0x0;
        D_00261100.a = 0x80;
        D_00261108.r = 0xFF;
        D_00261108.g = 0xFF;
        D_00261108.b = 0xFF;
        D_00261108.a = 0x80;
        D_00261110.r = 0xE6;
        D_00261110.g = 0xE6;
        D_00261110.b = 0xE6;
        D_00261110.a = 0x80;
        D_00261118.r = 0x2F;
        D_00261118.g = 0x72;
        D_00261118.b = 0x3E;
        D_00261118.a = 0x80;
        func_001F5C0C(&D_00261148, 0, 0x1C);
        D_00261148.f4 = 0x2D;
        D_00261148.f8 = 2.0f;
        D_00261148.f10 = 0.3f;
        D_00261148.f14 = 0.3f;
        D_00261148.f18 = 0xFF7D4B00;
        func_001F5C0C(&D_00261168, 0, 0x1C);
        D_00261168.f4 = 0x2D;
        D_00261168.f8 = 32.0f;
        D_00261168.fC = 16.0f;
        D_00261168.f10 = 0.3f;
        D_00261168.f14 = 0.3f;
        D_00261168.f18 = 0xFF7D4B00;
    }
}
