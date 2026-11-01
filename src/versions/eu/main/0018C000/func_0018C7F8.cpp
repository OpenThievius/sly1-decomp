// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the Gx object's field is at 0x58C (not 0x27C) and the packed word at 0x570 (not 0x260).
struct Gx_18C7F8_eu { u8 pad0[0x58C]; s32 f58C; };

void func_0018C7F8(Self_18C7F8* self)
{
    if (self->f4F44 != 0) {
        if ((D_002623C0->f19EC & 0x100) == 0) {
            ((Gx_18C7F8_eu*)D_0026FF68)->f58C = -1;
            func_00194D30(D_0026FF68, 1, 0x14);
        } else {
            func_0018B670(D_00269990, (void*)func_0018C638, self);
            u8* obj = (u8*)D_00273EB0;
            ((Pk_18C7F8*)(obj + 0x570))->v = 0;
            ((Obj_18C7F8*)obj)->vtbl[14](obj);
        }
    }
}
