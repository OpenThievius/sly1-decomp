// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 96/116 (82.8%), checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001AAF38.cpp func_eu_001AAF38 --unit src/main/001A8000.cpp
// Still differs: Sets table, index, 0.25 constants and calls func_001AAB20; retail has the 0.25 store at +0x550 before the +0x568 store and different v1/a2 roles, ours moves it after.
// Sets the table entry and index for slot a1 (20-byte elements of D_eu_0026D810), calls func_001AAB20 with the two floats at +0x544 and +0x548, then copies the pair at +0x53C to +0x52C.
struct Obj_eu_001AAF38 {
    u8 pad000[0x524];
    s32 index;
    void* table;
    f32 out0;
    f32 out1;
    u8 pad534[8];
    f32 in0;
    f32 in1;
    f32 x;
    f32 y;
    u8 pad54C[4];
    f32 f550;
    u8 pad554[4];
    f32 f558;
    u8 pad55C[0xC];
    void* f568;
};

extern u8 D_eu_0026D810[];
extern u8 D_eu_00262B68[];
void func_001AAB20(void* self, f32 x, f32 y);

void func_eu_001AAF38(Obj_eu_001AAF38* self, s32 a1)
{
    f32 i0;
    f32 i1;

    f32 q = 0.25f;
    self->table = D_eu_0026D810 + a1 * 20;
    self->f558 = q;
    self->f550 = q;
    self->f568 = D_eu_00262B68;
    self->index = a1;
    func_001AAB20(self, self->x, self->y);
    i0 = self->in0;
    i1 = self->in1;
    self->out0 = i0;
    self->out1 = i1;
}
