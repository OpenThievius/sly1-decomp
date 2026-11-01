// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the table byte unsigned (lbu).
u8 func_001E13D0(Obj_1E13D0* self0, s32 a, s32 b)
{
    Obj_1E13D0* self = self0;
    s32 idx;
    if (a < b || a - 15 >= b) {
        idx = 0;
    } else {
        f32 t = func_00205C78(10.0f, (f32)(-b));
        Obj_1E13D0* p = func_001FCDE0(self, (u64)func_001FD868(t));
        self = func_001EAE78(p);
        p = func_001EAE78(func_001FCDE0(self, 0.1));
        p = func_001FCDE0(p, (u64)0x4024000000000000ULL);
        idx = func_001FD410(func_001FCD78(self, p));
    }
    return ((u8*)&D_00275940)[idx];
}
