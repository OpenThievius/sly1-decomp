// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: with a state 0 at 0x560 it calls func_eu_001AB2B0; with a state 0 to 3 it runs func_eu_001E3100 and, if that holds, sets 0x570 and calls slot 16 of the object.
typedef void (*Method_eu_1AD668)(void* self, s32 c);

struct Self_eu_1AD668 {
    Method_eu_1AD668* vtbl;
    u8 pad4[0x55C];
    s32 f560;
    u8 pad564[0x570 - 0x564];
    s32 f570;
    s32 f574;
};

s32 func_eu_001E3100(void* p, s32 c);
void func_eu_001AB2B0(void* self, s32 c);

void func_eu_001AD668(Self_eu_1AD668* self, s32 arg)
{
    s32 st = self->f560;
    if (st == 0) {
        func_eu_001AB2B0(self, arg);
        return;
    }
    if (st < 0) {
        return;
    }
    if (st >= 4) {
        return;
    }
    if (func_eu_001E3100((u8*)self + 8, arg) == 0) {
        return;
    }
    self->f574 = arg;
    self->f570 = 1;
    self->vtbl[16](self, 3);
}
