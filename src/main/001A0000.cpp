// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_0019EBE8(void* self);

void func_001A0020(u8* self, void* other)
{
    if (other != 0) {
        func_0019EBE8(self);
    }
}

void func_0019EB28(u8* self);
extern u8* D_00275710;

void func_001A1458(u8* self)
{
    func_0019EB28(self);
    s32 v = *(s32*)(D_00275710 + 0x1D28);
    *(s32*)(self + 0x120) = -1;
    *(s32*)(self + 0x20) = v;
    *(s32*)(self + 0x128) = -1;
}

void func_0019F560(u8* self);
void func_0019EBE8(u8* self);
s32 func_00182FC8(s32 handle);

void func_001A26B0(u8* self)
{
    func_0019F560(self);
    s32 h = *(s32*)(self + 0x120);
    if (h != 0) {
        if (func_00182FC8(h) == 0) {
            func_0019EBE8(self);
        }
    }
}

void func_001BAC30(u8* self);
void func_00124DF8(u8* self, s32 n, void* data);
extern u8 D_0026B778[];

void func_001A3B20(u8* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 2, D_0026B778);
}

struct __attribute__((aligned(16))) Quad_1A0040 { s32 a, b, c, d; };

struct Obj_1A0040 {
    u8 pad00[0x1C];
    f32 f1C;
    s32 i20;
    u8 pad24[0x1C];
    Quad_1A0040 q40;
    u8 pad50[0xD0];
    f32 f120;
};

void func_0019EB28(Obj_1A0040* self);
extern u8* D_00275710;
extern Quad_1A0040 D_00275C50;

void func_001A0040(Obj_1A0040* self)
{
    func_0019EB28(self);
    self->f1C = 0.25f;
    s32 v = *(s32*)(D_00275710 + 0x1CF8);
    self->i20 = v;
    self->q40 = D_00275C50;
    self->f120 = 0.05f;
}

void func_001A0338(void* self, s32 kind, s32 extra);

void func_001A0318(void* self)
{
    func_001A0338(self, 0, 0);
}
