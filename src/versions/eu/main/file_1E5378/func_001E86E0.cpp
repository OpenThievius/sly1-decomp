// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields at 0x578/0x580 and the manager state at 0x570; calls PAL's func_eu_001AB238 where US calls vtable slot 8.
struct Obj_1E86E0_eu {
    u8 pad0[0x578];
    s32 f578;
    u8 pad1[4];
    s32 f580;
};

struct Mgr_1E86E0_eu {
    void** vtbl;
    u8 pad[0x570 - 4];
    s32 f570;
};

void func_eu_001AB238(void* self, s32 v);

void func_001E86E0(Obj_1E86E0_eu* self, s32 value)
{
    if (value == self->f580) return;
    if (self->f580 == 0) {
        func_eu_001AB238(&D_002701F8, 0);
    }
    self->f580 = value;
    if (((Mgr_1E86E0_eu*)&D_002701F8)->f570 == 4) {
        func_001E7460(self);
        if (self->f580 != 0) {
            void** vt = *(void***)self;
            ((void (*)(void*, s32))vt[16])(self, 2);
            func_001E7518(self, 1);
            func_001E7440(self, 0);
        } else {
            void** vt = *(void***)self;
            ((void (*)(void*, s32))vt[16])(self, 0);
            func_001E7518(self, 3);
            func_001E7440(self, 0);
            func_001E87F0(self, 0);
        }
    } else {
        s32 st = self->f578;
        if (st >= 2) return;
        if (st < 0) return;
        func_001E7518(self, 2);
    }
}
