// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields 0x310 further on, the text goes to a local buffer handed to func_eu_001AB370
struct Self_1AB2B8_eu {
    u8 pad0[0x524];
    s32 f524;
    u8 pad528[0x570 - 0x528];
    s32 f570;
    u8 pad574[4];
    s32* f578;
};
void func_eu_001AB370(Self_1AB2B8_eu* self, char* buf);

void func_001AB2B8(Self_1AB2B8_eu* self)
{
    char buf[0x200];
    switch (self->f524) {
    case 3:
        func_001E20B8(buf, 0x200, D_0024CC78, 0x4C, self->f570);
        break;
    case 4:
        if (*self->f578 != 0) {
            func_001E20B8(buf, 0x200, D_0024CC80, self->f570, *self->f578,
                          self->f570 < *self->f578 ? 0x3F : 0x21);
        } else {
            buf[0] = 0;
        }
        break;
    case 5:
        if ((u32)(((A_1AB2B8*)D_002623C0)->f19D8 - 1) < 4) {
            func_001E20B8(buf, 0x200, D_0024CC88, self->f570, 0x4B);
        } else {
            buf[0] = 0;
        }
        break;
    case 6:
        if (((B_1AB2B8*)D_00275710)->f2354 != 0) {
            func_001E20B8(buf, 0x200, D_0024CC78, 0x43, self->f570);
        } else {
            buf[0] = 0;
        }
        break;
    case 7:
        func_001E20B8(buf, 0x200, D_0024CC80, self->f570, *self->f578, 0x56);
        break;
    case 8:
        func_001E20B8(buf, 0x200, D_0024CC80, self->f570, *self->f578, 0x4E);
        break;
    case 9:
        func_001E20B8(buf, 0x200, D_0024CC90, 0x46, self->f570, *self->f578);
        break;
    case 10:
        func_001E20B8(buf, 0x200, D_0024CC78, 0x4E, self->f570);
        break;
    case 11:
        func_001E20B8(buf, 0x200, D_0024CC80, self->f570, *self->f578, 0x56);
        break;
    case 28:
        func_001E20B8(buf, 0x200, D_0024CC80, self->f570, D_002751D4, 0x56);
        break;
    case 29:
        func_001E20B8(buf, 0x200, D_0024CC90, 0x4E, self->f570, D_002751D4);
        break;
    case 12:
        func_001E20B8(buf, 0x200, D_0024CC80, self->f570, *self->f578, 0x64);
        break;
    case 13:
        func_001E20B8(buf, 0x200, D_0024CC98, 's',
                      self->f570 >= 1 ? 'b' : 'm', self->f570 >= 2 ? 'b' : 'm',
                      self->f570 >= 3 ? 'b' : 'm', self->f570 >= 4 ? 'b' : 'm',
                      self->f570 >= 5 ? 'b' : 'm');
        break;
    case 14:
        func_001E20B8(buf, 0x200, D_0024CCA8);
        break;
    case 15:
        func_001E20B8(buf, 0x200, D_0024CCB0, 0x46, self->f570);
        break;
    case 36:
        func_001E20B8(buf, 0x200, D_0024CCB8, self->f570);
        break;
    }
    func_eu_001AB370(self, buf);
}
