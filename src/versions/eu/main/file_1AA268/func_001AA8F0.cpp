// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: state, f254 and p258 sit 784 (0x310) bytes further on than in US.
typedef void (*VFn_1AA8F0)(void* self, s32 flag);

struct Obj_1AA8F0_eu {
    VFn_1AA8F0* vtbl;
    u8 pad0[0x250 - 4 + 0x310];
    s32 state;
    f32 f254;
    f32* p258;
};

void func_001AA8F0(Obj_1AA8F0_eu* self)
{
    s32 s = self->state;
    if (s == 2) {
        goto store;
    }
    if (s < 3) {
        if (s == 0) {
            goto call;
        }
        return;
    }
    if (s != 3) {
        return;
    }
call:
    self->vtbl[16](self, 1);
    return;
store:
    self->f254 = *self->p258;
}
