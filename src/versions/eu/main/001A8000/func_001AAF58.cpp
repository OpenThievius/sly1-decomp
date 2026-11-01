// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: f254 and f258 sit 784 (0x310) bytes further on than in US.
extern u8 D_00261868[];

struct Obj_1AAF58_eu {
    u8 pad0[0x254 + 0x310];
    f32 f254;
    void* f258;
};

void func_001AAF58(Obj_1AAF58_eu* self, f32* p)
{
    if (self->f258 != p) {
        if (p == 0) {
            p = (f32*)D_00261868;
        }
        self->f254 = *p;
    }
    self->f258 = p;
}
