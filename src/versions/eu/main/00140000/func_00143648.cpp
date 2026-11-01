// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the constant stored at +0x1E0 is 1.36574075f (0x3FAED098) where US has 1.29870129f.
void func_00143648(struct Self_00143648* self)
{
    u8* s = (u8*)self;

    func_00182C18(self);
    f32 one = 1.0f;
    *(f32*)(s + 0x1C0) = one;
    *(f32*)(s + 0x1C4) = one;
    *(f32*)(s + 0x1C8) = one;
    *(struct Pk16_00143648*)(s + 0x1D0) = *(struct Pk16_00143648*)D_002618B8;
    f32 k = 1.36574075f;
    f32 x = D_002618A0;
    f32 y = D_002618A4;
    f32 z = D_002618A8;
    f32 h = 100.0f;
    f32 t = 20000.0f;
    *(f32*)(s + 0x1E0) = k;
    *(f32*)(s + 0x1E4) = h;
    *(f32*)(s + 0x1E8) = t;
    *(f32*)(s + 0x1F8) = x;
    *(f32*)(s + 0x1FC) = y;
    *(f32*)(s + 0x200) = z;
    *(struct Pk4_00143648*)(s + 0x204) = *(struct Pk4_00143648*)D_002618B0;
    *(struct Quad_00143648*)(s + 0x80) = *(struct Quad_00143648*)D_002483D0;
    *(struct Quad_00143648*)(s + 0x90) = *(struct Quad_00143648*)(D_002483D0 + 0x10);
    *(struct Quad_00143648*)(s + 0xA0) = *(struct Quad_00143648*)(D_002483D0 + 0x20);
    func_00143560(self);
    *(void**)(s + 0x454) = D_00217398;
    func_00149398((struct Sub_00143648*)(s + 0x454), self);
    *(void**)(s + 0x460) = D_002173B0;
    func_00149660((struct Sub_00143648*)(s + 0x460), self);
    *(void**)(s + 0x4C0) = D_002173C8;
    func_0014A888((struct Sub_00143648*)(s + 0x4C0), self);
    *(void**)(s + 0x510) = D_002173E0;
    func_00149398((struct Sub_00143648*)(s + 0x510), self);
    *(void**)(s + 0x520) = D_002173F8;
    func_00149398((struct Sub_00143648*)(s + 0x520), self);
    func_00143A60(self, 1);
}
