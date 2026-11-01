// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the fields are 0x310 later, and the elements 0x570 apart, the first at 0x574 (US 0x264, 0x260 apart).
struct Elem_14ADE0_eu {
    VFn_14ADE0* vtbl;
    u8 pad004[0x52C - 0x004];
    f32 f21C;
    f32 f220;
    u8 pad534[0x548 - 0x534];
    f32 f238;
    f32 f23C;
    u8 pad550[0x570 - 0x550];
};

struct Obj_14ADE0_eu {
    VFn_14ADE0* vtbl;
    u8 pad004[0x52C - 0x004];
    f32 f21C;
    f32 f220;
    u8 pad534[0x570 - 0x534];
    s32 count;
    Elem_14ADE0_eu items[1];
};

void func_0014ADE0(Obj_14ADE0_eu* self)
{
    if (D_00275BEC == 1) {
        f32 acc = self->f220;
        s32 i;
        for (i = 0; i < self->count; i++) {
            Elem_14ADE0_eu* e = &self->items[i];
            f32 saved = e->f23C;
            f32 base = self->f21C;
            f32 scaled = saved * D_00261850;
            e->f220 = acc;
            e->f21C = base;
            e->f23C = scaled;
            e->vtbl[9](e);
            e->f23C = saved;
            acc += e->f238;
        }
    }
}
