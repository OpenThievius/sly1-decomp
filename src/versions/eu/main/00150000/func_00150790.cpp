// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: D_0026F5A0.f260 is at 0x570 (US 0x260) and D_002701F8.f324 at 0x5B0 (US 0x324).
struct Glob_150790_eu { u8 pad0[0x570]; Self_150790* f260; };
struct __attribute__((packed)) Blk_150790_eu { u8 pad0[0x5B0]; s32 f5B0; };

void func_00150790(Self_150790* self, s32 next)
{
    s32 cur = self->f2D4;
    if (next == cur) {
        return;
    }
    switch (cur) {
    case 5:
        if (((Glob_150790_eu*)&D_0026F5A0)->f260 == self) {
            ((Glob_150790_eu*)&D_0026F5A0)->f260 = 0;
        }
        break;
    case 1:
        if (self->f2D0 != cur) {
            D_00261D38 = D_00261D38 - 1;
        }
        break;
    case 3:
        self->f304->f0 = 1;
        func_001BE998();
        func_001837E0(self, 0x15, 0, 0);
        if (self->f2D0 == 2) {
            func_001451F0(D_00261990, 0xF, 6, D_00261990->f460, 0, 0);
            func_001DDA50(D_00275710);
        }
        (void)func_00149610(D_00261990->f460);
        if ((self->f2E8 & 0x10) != 0 && self->f2F8 != 0) {
            func_0012E760(self->f2F8);
        }
        if (self->f2D0 == 2 && self->f330 != 0) {
            f32 f = 1.0f;
            func_001C06A0(9, 0, f);
            func_001C06A0(9, 1, f);
        }
        break;
    case 4:
        ((Blk_150790_eu*)&D_002701F8)->f5B0 = 0;
        func_001356C0((Blk_150790*)&D_002701F8, 0);
        break;
    }
    switch (next) {
    case 5:
        if (((Glob_150790_eu*)&D_0026F5A0)->f260 != 0) {
            func_00150790(((Glob_150790_eu*)&D_0026F5A0)->f260, 0);
        }
        ((Glob_150790_eu*)&D_0026F5A0)->f260 = self;
        self->f2D4 = next;
        break;
    case 1:
        if (self->f2D0 != next) {
            D_00261D38 = D_00261D38 + 1;
        }
        self->f2D4 = next;
        break;
    case 3:
        self->f2E4 = -1;
        self->f2E8 = 0;
        if (self->f2D0 == 2) {
            func_001495E8(D_00261990->f460, 4);
            func_00145088(D_00261990, 6, D_00261990->f460, 0, 0);
            func_001DDA20(D_00275710);
            func_001365A0((Blk_150790*)&D_002701F8, 0);
            if (self->f330 != 0) {
                f32 f = 0.6f;
                func_001C06A0(9, 0, f);
                func_001C06A0(9, 1, f);
            }
        } else {
            func_001495E8(D_00261990->f460, 3);
            if (self->f2D0 == 0) {
                if (self->f300 != -1) {
                    D_00261990->f4BC = (s32)func_0015A448(self->f14, self->f300, 0);
                } else {
                    D_00261990->f4BC = 0;
                }
            }
        }
        self->f2D4 = next;
        break;
    case 4:
        func_001E86E0(D_002708E0, 0);
        func_001E87F0(D_002708E0, 0);
        func_001E86E0(D_00271558, 0);
        func_001E87F0(D_00271558, 0);
        self->f2D4 = next;
        break;
    default:
        self->f2D4 = next;
        break;
    }
    self->f2D8 = D_0026185C[0];
}
