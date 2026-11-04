// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL scales y by 0.5462963f (not 0.45454547f) and offsets it by 1920.0f (not 1936.0f)
void func_00180108(Obj_180108* self, f32 a, f32 b, f32 c, f32 d)
{
    f32 sp[16];
    Col_180108 col;
    Q_180108 vv, q;
    s32 g;
    func_0018A008(0, sp, c);
    sp[12] = a;
    sp[13] = b;
    func_001613C0(&D_00262280, 0, 1, 0xE);
    func_00161708(&D_00262280, 0x47, 0x31001);
    func_00161708(&D_00262280, 0x42, 0x44);
    for (g = 4; g > 0; g--) {
        Group_180108* grp = &self->groups[g];
        if (grp->n > 0) {
            func_001613C0(&D_00262280, 0, 1, 1);
            col = *(Col_180108*)((u32)(g - 3) < 2 ? D_00264098 : D_002640A0);
            col.a = (u8)(s32)((f32)col.a * d);
            func_00161458(&D_00262280, *(u32*)&col);
            func_001613C0(&D_00262280, (s8)col.a >= 0 ? 0x43 : 0x83, 1, 4);
            {
                s32 i;
                for (i = 0; i < grp->n; i++) {
                    u32* idx = (u32*)((u8*)grp->tris + i * 12);
                    s32 j;
                    for (j = 2; j >= 0; j--) {
                        vv.v = self->verts[*idx++];
                        q.v = func_00188740(sp, vv.v);
                        func_001615F0(&D_00262280, (s32)((q.f[0] + 1728.0f) * 16.0f), (s32)((q.f[1] * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
                    }
                }
            }
        }
    }
}
