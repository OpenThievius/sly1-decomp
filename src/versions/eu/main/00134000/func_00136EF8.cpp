// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the child pointer is at 0x5B0 (US 0x324).
struct Owner_136EF8_eu { u8 pad0[0x5B0]; Child_136EF8* child; };

void func_001356C0(Owner_136EF8_eu* self, s32 mode);

void func_00136EF8(Owner_136EF8_eu* self)
{
    if (self->child != 0) {
        switch (self->child->kind) {
        case 0:
            func_001356C0(self, 2);
            break;
        case 1:
            func_001356C0(self, 3);
            break;
        case 2:
            func_001356C0(self, 4);
            break;
        }
        func_00150790(self->child, 3);
    } else {
        func_001356C0(self, 1);
    }
}
