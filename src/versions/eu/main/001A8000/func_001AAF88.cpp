// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields from f214 on sit 784 (0x310) bytes further on than in US.
struct Obj_1AAF88_eu {
    u8 pad000[4];
    u32 f004;
    u8 pad008[0x20C + 0x310];
    s32 f214;
    u8 pad218[0x48];
    s32 f260;
    void* f264;
    void* f268;
    f32 f26C;
};

extern u8* D_002623C0;
extern u8* D_002623C4;
extern u8* D_002623C8;
extern u8* D_00275710;

void func_001AA268(Obj_1AAF88_eu* self);

void func_001AAF88(Obj_1AAF88_eu* self)
{
    func_001AA268(self);
    self->f004 = (u32)func_0015C1C0(2);
    self->f260 = -1;
    self->f26C = 6000.0f;
    switch (self->f214) {
    case 3:
        self->f264 = D_002623C0 + 0x19E0;
        break;
    case 4:
        self->f264 = D_002623C8 + 0x64;
        self->f268 = D_00275710 + 0x2300;
        break;
    case 5:
        self->f264 = D_002623C4 + 0x438;
        break;
    case 6:
        self->f264 = D_002623C0 + 0x19E8;
        break;
    case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
    case 28: case 29:
    case 36:
        self->f264 = &self->f260;
        break;
    }
}
