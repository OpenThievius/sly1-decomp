// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: f234 and f238 sit 784 (0x310) bytes further on than in US.
struct Obj_001AAB20_eu {
    u8 pad[0x234 + 0x310];
    f32 f234;
    f32 f238;
};

void func_001AAB60(Obj_001AAB20_eu* self);

void func_001AAB20(Obj_001AAB20_eu* self, f32 x, f32 y) {
    if (0.0f <= x) {
        self->f234 = x;
    }
    if (0.0f <= y) {
        self->f238 = y;
    }
    func_001AAB60(self);
}
