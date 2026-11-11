// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: stores a 16-bit value through a pointer, byte or half by the object's mode.
struct Writer_eu_15DEE0 {
    s32 mode;
    u8 pad4[4];
    void* target;
};

void func_eu_0015DEE0(Writer_eu_15DEE0* self, u16 v)
{
    switch (self->mode) {
    case 0:
        *(u8*)self->target = (u8)v;
        break;
    case 1:
        *(u16*)self->target = v;
        break;
    }
}
