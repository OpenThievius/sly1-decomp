// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL has no sound-slot setup nor the virtual call, and its fields sit at 0x518, 0x570 and 0x574.
typedef void (*VFn_1F1960)(void* self, void* arg);
struct Obj_1F1960_eu {
    VFn_1F1960* vtbl;
    u8 pad004[0x514];
    u32 f518;
    u8 pad51C[0x54];
    u32 f570;
    WarpPage* f574[6];
};

void SetupScreenElementText(Obj_1F1960_eu* self);
void SetScreenElementHoldTime(Obj_1F1960_eu* self, f32 v);
void SetScreenElementScale(Obj_1F1960_eu* self, f32 v);

void InitWarpMenu(Obj_1F1960_eu* self) {
    SetupScreenElementText(self);
    SetScreenElementHoldTime(self, 0.0f);
    SetScreenElementScale(self, 0.6f);
    self->f518 = 0xDF7F7F7F;
    self->f570 = 0;
    FillMemory(&self->f574, 0, 0x18);
}
