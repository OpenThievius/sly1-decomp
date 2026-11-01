// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: every field from f208 on sits 784 (0x310) bytes further on than in US.
extern f32 D_0024CD4C;

struct Obj_001AB890_eu;
typedef void (*VFn_001AB890_eu)(Obj_001AB890_eu* self);

struct Obj_001AB890_eu {
    VFn_001AB890_eu* vtbl;
    u8 pad0[0x208 - 4 + 0x310];
    u32 f208;
    u8 pad1[0x268 - 0x20C];
    f32 f268;
    f32 f26C;
    s32 f270;
    s32 f274;
    f32 f278;
    u8 pad2[0x280 - 0x27C];
    s32 f280;
    s32 f284;
    s32 f288;
    s32 f28C;
    s32 f290;
};

void func_001ABE20(Obj_001AB890_eu* self, s32 state);
void func_001AB980(Obj_001AB890_eu* self, f32 value);

void func_001AB890(Obj_001AB890_eu* self, f32 x)
{
    self->f280 = 0;
    self->f284 = 0;
    self->f288 = 0;
    self->f28C = 0;
    self->f290 = 0;
    self->f208 = 0xFF808080;
    self->f26C = -1.0f;
    self->f270 = -1;
    self->f274 = -1;
    self->f278 = D_0024CD4C;
    self->f268 = x;
    func_001ABE20(self, 1);
    func_001AB980(self, 0.0f);
    self->vtbl[14](self);
}
