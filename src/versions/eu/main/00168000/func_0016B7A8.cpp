// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: Obj_16B7A8 fields f25C, f260 and f264 are at 0x56C, 0x570 and 0x574 (US 0x25C, 0x260, 0x264).
struct Obj_16B7A8_eu { VFn_16B7A8* vtbl; u8 pad0[0x56C - 4]; s32 f56C; void* f570; s32 f574; };

void func_0016B7A8(Obj_16B7A8_eu* self, s32 v)
{
    s32 flag = (v != 0);
    if (flag != (self->f56C == 0)) {
        return;
    }
    if (v != 0) {
        func_0016B300(self->f570, ((Node_16B7A8*)self->f570)->f2D0, 0);
        func_0016E0F0(1);
        func_0016EC88(D_00262C70);
    } else {
        if (self->f574 != 0) {
            func_001BE998();
            self->f574 = 0;
        }
        func_0016E118(1);
        self->vtbl[15](self);
        Obj_16B7A8* g = (Obj_16B7A8*)D_0026F138;
        g->vtbl[15](g);
    }
    self->f56C = v;
}

