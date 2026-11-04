// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: pair, f234 and count are 0x310 later (0x528, 0x544, 0x570) and q is at 0x578 (US 0x4).
typedef void (*VFn_14AEA0)(void* self, s32 arg);
struct Obj_14AEA0_eu {
    VFn_14AEA0* vtbl;
    u8 pad004[0x528 - 0x004];
    T217D_Place* pair;
    u8 pad52C[0x544 - 0x52C];
    f32 f234;
    u8 pad548[0x570 - 0x548];
    s32 count;
    u8 pad574[0x578 - 0x574];
    V24A2* q;
};

void func_001AAB20(Obj_14AEA0_eu* self, f32 a, f32 b);

void func_0014AEA0(Obj_14AEA0_eu* self, s32 n, f32 x, f32 y)
{
    self->pair->dx = x;
    self->pair->dy = y;
    self->count = n;
    V24A2* q = self->q;
    func_001AAB20(self, self->f234, (f32)q->height * q->sy * (f32)n);
    self->vtbl[16](self, 2);
}
