// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the fields of self are at 0x560, 0x570, 0x58C and 0x590 (US 0x250, 0x260, 0x27C, 0x280).
struct Obj_1F1A08_eu {
    u8 pad0[0x560];
    s32 f560;
    u8 pad1[0x570 - 0x564];
    Sub_1F1A08* f570;
    u8 pad2[0x58C - 0x574];
    f32 f58C;
    f32 f590;
};

void func_001F1A08(Obj_1F1A08_eu* self, Obj_1F1A08* t)
{
    s32 loc[2];
    s32 s3;
    s32 s2;
    s32 v1;

    if (self->f570 == 0) return;
    if (self->f570->f2D0 != 2) return;
    if (self->f570->f560 != 0) return;
    if ((t->fAA & 0x910) != 0 || t->f14 == 1) {
        func_001E9570((Q_1F1A08*)D_00275BC0);
        func_0016EC20((Pool_1F1A08*)D_00262C70, 0x910);
        return;
    }
    if (self->f560 != self->f570->f2D0) return;

    s3 = func_001F0490(self->f570, self->f570->f2DC, &loc[0], &loc[1]);
    s2 = func_0016EC98(t);
    v1 = func_0016EED0(t);
    t->f30 = D_00261858[4] + t->f34;
    t->f38 = D_00261858[4] + t->f3C;

    if (v1 < 0) {
        func_001F1648(self->f570, 0);
    } else if (v1 > 0) {
        func_001F1648(self->f570, 1);
    } else if (s2 < 0) {
        func_001F1648(self->f570, 2);
    } else if (s2 > 0) {
        func_001F1648(self->f570, 3);
    } else if ((t->fAA & 0x40) != 0) {
        func_0016EC20((Pool_1F1A08*)D_00262C70, 0x40);
        if (self->f570->f2DC != func_001F0468()) {
            if (s3 != 0) {
                Val_1F1A08* v = func_00160180((loc[0] << 8) | loc[1]);
                self->f570->f560 = 1;
                func_001E9570((Q_1F1A08*)D_00275BC0);
                func_001F0428(v, -1, 2);
            } else {
                func_001BFCD8(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        } else {
            func_001E9570((Q_1F1A08*)D_00275BC0);
        }
    }

    if (s3 != 0) {
        self->f590 = 1.0f;
    } else {
        self->f590 = D_00275FC0[0];
    }
    self->f58C = func_001EA4B8((Q3_1F1A08*)D_00276278, 0, self->f58C, self->f590, D_00261858[5]);
}
