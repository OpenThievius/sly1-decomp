// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL has no sound-slot setup nor the virtual call, and its fields sit at 0x518, 0x570 and 0x574.
struct Obj_1F1960_eu {
    VFn_1F1960* vtbl;
    u8 pad004[0x514];
    u32 f518;
    u8 pad51C[0x54];
    u32 f570;
    Clr_1F1960 f574;
};

void func_001AA268(Obj_1F1960_eu* self);
void func_001AA8B8(Obj_1F1960_eu* self, f32 v);
void func_001AA788(Obj_1F1960_eu* self, f32 v);

void func_001F1960(Obj_1F1960_eu* self) {
    func_001AA268(self);
    func_001AA8B8(self, 0.0f);
    func_001AA788(self, 0.6f);
    self->f518 = 0xDF7F7F7F;
    self->f570 = 0;
    func_001F5C0C(&self->f574, 0, 0x18);
}
