// SPDX-License-Identifier: AGPL-3.0-or-later
// Sets up an object: kind 1, the table D_0024A220 at +0x64, the pointer that func_eu_001DDAB0 returns at +0x4, two fields, four 0xFF808080 colours, then runs func_eu_0015DDA0.
const char* func_eu_001DDAB0(s32 id);
void func_eu_0015DDA0(void* self);

struct Obj_eu_0015DD18 {
    s32 f0;
    const char* f4;
    u8 pad8[0x8];
    s32 f10;
    u8 pad14[0x50];
    void* vt64;
    u8 pad68[0x3C];
    s32 fA4;
    s32 fA8;
    s32 fAC;
    s32 fB0;
    s32 fB4;
};

void* func_eu_0015DD18(Obj_eu_0015DD18* self, s32 id, s32 a, s32 b)
{
    self->f0 = 1;
    self->vt64 = &D_0024A220;
    self->f4 = func_eu_001DDAB0(id);
    self->f10 = a;
    self->fB4 = b;
    self->fB0 = 0xFF808080;
    self->fAC = 0xFF808080;
    self->fA8 = 0xFF808080;
    self->fA4 = 0xFF808080;
    func_eu_0015DDA0(self);
    return self;
}
