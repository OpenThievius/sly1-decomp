// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's func_0011E048 takes one more argument (a 0 before the final 1).
s32 func_0011E048(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9);

void func_001BE728(Obj_1BE728* self)
{
    if (D_00274744 != 0) {
        return;
    }
    Local_1BE728 l;
    Local_1BE728* p;
    if (func_001BE980() != 0) {
        func_001BE998();
    }
    p = &l;
    func_0018D410(p);
    s32 r = 0;
    if (self != 0) {
        s32 b = self->w4 ^ self->w1C;
        p->b = b;
        l.a = self->w0 ^ self->w14;
        r = b != 0;
    }
    if (r == 0) {
        return;
    }
    s32 h = func_0011E048(l.a, 0, 0, 0, 0x400, 0, 2, 0, 0, 1);
    if (h == 0) {
        return;
    }
    D_0027472C = h;
    D_00274730 = 1;
    func_0011E0E0(h, func_001BE5D8, (u32)h);
}
