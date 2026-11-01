// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the key is passed zero-extended to 16 bits
f32 func_0015CA60(Owner_15CA60* self, s32 key)
{
    Entry_15CA60* e = (Entry_15CA60*)func_0015DAB8(self, (u16)key);
    f32 x;
    f32 y;
    if (e == 0) {
        x = self->a44;
        y = (f32)self->a4;
    } else {
        x = (f32)(e->value + 1);
        y = self->a44;
    }
    return x * y;
}
