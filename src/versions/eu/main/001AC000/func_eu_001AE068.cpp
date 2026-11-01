// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: when the flag is 0, clears the state at 0x570 (or 0x974 when that is already clear), then runs func_001AA998.
struct Obj_eu_1AE068 {
    u8 pad0[0x570];
    s32 f570;
    s32 f574;
    u8 pad578[0x3FC];
    s32 f974;
};

void func_eu_001AB2B0(void* self, void* p);

void func_eu_001AE068(Obj_eu_1AE068* self, s32 flag)
{
    if (self->f570 != 0 && flag == 0) {
        self->f570 = 0;
        func_eu_001AB2B0(self, &self->f574);
        flag = 1;
    }
    if (flag == 0) {
        self->f974 = 0;
    }
    func_001AA998(self, flag);
}
