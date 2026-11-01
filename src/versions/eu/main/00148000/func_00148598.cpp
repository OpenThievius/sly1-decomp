// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL always increments the counter at 0x438 (no D_00275C34 check).
void func_00148598(void* self, s32 mode)
{
    if (((Obj_148598*)self)->f2D0 == mode) return;
    if (mode == 1) {
        Flags_148598* fl = D_002623C8;
        s32 bits = fl->flags;
        if ((bits & 2) == 0) {
            fl->flags = bits | 2;
            D_002623C4->f438++;
        }
        VObj_148598* vo = (VObj_148598*)D_0026CBC8;
        vo->vtbl[14](vo);
        void* r = (void*)func_001925F0();
        if (r != 0) {
            ((VObj3_148598*)r)->vtbl[82](r, 0, self);
        }
        func_001837E0(self, 2, 0, 0);
        mode = 2;
        func_00151FC8(D_00261EF0);
        func_0018C7F8(D_00264A40);
    }
    func_00147AB0(self, mode);
}
