// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL passes 0.975 where US passes 1.0.
void func_0019DBB0(void)
{
    Self_19DBB0* self = (Self_19DBB0*)D_002622A8;
    func_0015EAE0(self, D_00212160, D_00215C50);
    func_0019D860();
    func_0019D930();

    if (D_0026FA68 != 0) {
        s32 v = D_00274520[D_0026FA68->idx2F4];
        if (v != 0) {
            *(u64*)self->ptr0C = ((u64)v << 32) | 0x50000000;
            self->ptr0C = self->ptr0C + 0x10;
        }
    }

    {
        Obj_19DBB0* o = D_00261990;
        f32 keep20 = o->f1C4;
        f32 keep21 = o->f1C8;
        func_00143940(o, 0.975f);
        func_00144848(D_00261990);
        func_00143940(D_00261990, keep20);
        D_00261990->f1C8 = keep21;
    }
}
