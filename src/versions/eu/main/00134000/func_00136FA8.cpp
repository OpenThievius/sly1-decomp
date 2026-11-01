// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the child pointer is at 0x5B0 (US 0x324).
struct Owner_136FA8_eu { u8 pad[0x5B0]; void* child; };

s32 func_001356C0(Owner_136FA8_eu* self, s32 mode);

s32 func_00136FA8(Owner_136FA8_eu* self)
{
    s32 r;
    if (self->child != 0) {
        r = func_00150790(self->child, 4);
        goto done;
    }
    r = func_001356C0(self, 0);
done:
    return r;
}
