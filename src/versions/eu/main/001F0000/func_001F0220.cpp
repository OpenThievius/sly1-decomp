// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL has the table at its own address, read at 0x570 and stores 8 at offset 0x30 of D_00275BC0 (unaligned) before func_001E96F8.
struct Sys_1F0220_eu { u8 pad0[0x30]; s32 f30; } __attribute__((packed));
struct Tbl_1F0220_eu { u8 pad0[0x570]; void* f570; void* f574[1]; };
extern Tbl_1F0220_eu D_eu_00274868;

void func_001F0220(Obj_1F0220* self, s32 mode)
{
    if (self->f4 == mode) goto L0410;
    if (self->f4 == 2) {
        if (D_0026FA68 != 0) {
            func_001F1050(D_0026FA68, 0);
        }
    }
    if (mode == 1) goto L02E0;
    if (mode < 2) {
        if (mode == 0) {
            self->fC.i = 0;
            goto L0400;
        }
        self->f4 = mode;
        goto L0404;
    }
    if (mode == 2) goto L02A0;
    if (mode == 3) goto L0374;
    self->f4 = mode;
    goto L0404;

L02A0:
    if (self->f10 != 0) {
        Quint_1F0220* q = (Quint_1F0220*)((u8*)self + 0x10);
        func_001E4E80(D_00275AF0, q->b, q->c, q->d, q->e);
    }
    self->f10 = 0;
    self->fC.f = 1.0f;
    self->f28 = 0;
    goto L0400;

L02E0:
    {
        s32 v = self->f24;
        if (v == 2) goto L0300;
        if (v == 3) goto L0354;
        goto L0364;
    }

L0300:
    {
        s32 v = func_001601A0(self->f14);
        s32 a3 = v >> 8;
        s32 a2 = v & 0xFF;
        if (D_0026FA68 == 0) goto L034C;
        if (v == -1) goto L034C;
        s32 a1 = 10;
        if (a3 != 0) a1 = a2;
        func_001F1590(D_0026FA68, a1, 3);
        func_001DDB58(D_00275710);
        goto L0364;
    }

L034C:
    self->f24 = 0;
    goto L0364;

L0354:
    mode = 2;
    goto L02A0;

L0364:
    ((Sys_1F0220_eu*)D_00275BC0)->f30 = 8;
    func_001E96F8(D_00275BC0, 8);
    self->f4 = mode;
    goto L0404;

L0374:
    {
        s32 a = self->f24;
        if (a == 2) goto L038C;
        if (a == mode) goto L03EC;
        self->f4 = mode;
        goto L0404;
    }

L038C:
    {
        if (self->f24 == D_00275BF0) {
            s32 idx = D_002623CC;
            if (idx != -1) {
                D_eu_00274868.f570 = D_eu_00274868.f574[idx];
            }
        }
        if (D_eu_00274868.f570 != 0) {
            ((Sub_1F0220*)D_eu_00274868.f570)->f2E0 = 3;
            func_001F1050(D_eu_00274868.f570, 4);
            self->f4 = mode;
            goto L0404;
        }
        self->f24 = 3;
        goto L0400;
    }

L03EC:
    func_00168B68(0.25f);
    self->f24 = 0;
    goto L0400;

L0400:
    self->f4 = mode;
L0404:
    self->f8 = D_00261868;
L0410:
    return;
}
