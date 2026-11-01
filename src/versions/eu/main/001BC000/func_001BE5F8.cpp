// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: func_0011E048 takes one more argument (a tenth, zero).
s32 func_0011E048(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9);

void func_001BE5F8(Obj_1BE5F8* self)
{
    if (D_00274744 != 0) {
        return;
    }
    if (self == 0) {
        return;
    }
    Local_1BE5F8 l;
    Local_1BE5F8* p;
    if (func_001BE980() != 0) {
        func_001BE998();
    }
    p = &l;
    func_0018D410(p);
    s32 b = self->w4 ^ self->w1C;
    p->b = b;
    p->a = self->w0 ^ self->w14;
    if (b == 0) {
        return;
    }
    s32 h = func_0011E048(p->a, 0, 0, 0, 0x400, 0, 2, 0, 0, 0);
    if (h == 0) {
        return;
    }
    D_0027472C = h;
    D_00274744 = 1;
    D_00274730 = 0;
    func_001C06A0(8, 1, 0.5f);
    func_001C06A0(8, 0, 0.5f);
    func_001C06A0(8, 3, 0.5f);
}
