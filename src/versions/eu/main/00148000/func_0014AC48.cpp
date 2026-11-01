// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's entries start at 0x574 with a 0x570 stride, call func_eu_001AAFB0 and func_eu_001AB550(0.5) and skip the sub-object writes.
struct Entry_14AC48_eu {
    VFn_14AC48* vtbl;
    u8 pad0[0x520 - 0x4];
    s32 f520;
    u8 pad1[0x570 - 0x524];
};

struct Obj_14AC48_eu {
    u8 pad0[0x574];
    Entry_14AC48_eu e[4];
};

void func_eu_001AAFB0(void* self);
void func_eu_001AB550(void* self, f32 v);

void func_0014AC48(Obj_14AC48_eu* self)
{
    Entry_14AC48_eu* e;
    u32 i;

    func_eu_001AAFB0(self);
    e = self->e;
    for (i = 0; i < 4; i++) {
        e->vtbl[1](e);
        e->f520 = 0;
        func_eu_001AB550(e, 0.5f);
        func_001AA8B0(e, 1.0f);
        func_001AA8C0(e, 1.0f);
        func_001AA8B8(e, 0.0f);
        e++;
    }
}
