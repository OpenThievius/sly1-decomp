// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: tears down a stream object whose fields sit at other offsets (state at 0x148, thread at 0x144).
struct Obj_18F6E8_eu {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
    u8 pad1[0x5C - 0x1C];
    s32 f5C;
    u8 pad2[0x128 - 0x60];
    s32 f128;
    s32 f12C;
    u8 pad3[0x144 - 0x130];
    s32 f144;
    volatile s32 f148;
};

void func_0018F6E8(Obj_18F6E8* self_)
{
    Obj_18F6E8_eu* self = (Obj_18F6E8_eu*)self_;
    void* s1;
    if (self->f148 == 1) {
        do {
            (void)func_0018F890((Obj_18F6E8*)self, 0);
        } while (self->f148 == 1);
    }
    if (func_0020B058((u8*)self + 0x10, self->f5C, 0x4B0) < 0) {
        return;
    }
    if (self->f18 == 0) {
        func_0018EDA8(self->f128, self->f5C, self->f10, self->f14);
        func_0018EF78(self->f12C, self->f10, self->f14);
        func_001F6C20(0);
    }
    s1 = (u8*)self + 0x80;
    if (self->f148 != 0) {
        do {
            (void)func_0018F890((Obj_18F6E8*)self, 0);
            func_0018F610((Obj_18F6E8*)self);
        } while (self->f148 != 0);
    }
    func_001F6B40(self->f144);
    func_0018EB98(s1);
}
