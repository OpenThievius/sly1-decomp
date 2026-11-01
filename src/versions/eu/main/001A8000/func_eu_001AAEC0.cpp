// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: for 37 pointers of D_eu_0024B2F0, calls slot 9 of each object whose 0x560 is set, then runs two setup calls.
typedef void (*Hook_eu_1AAEC0)(void* self);

struct Obj_eu_1AAEC0 {
    Hook_eu_1AAEC0* vtbl;
    u8 pad4[0x55C];
    s32 f560;
};

extern Obj_eu_1AAEC0* D_eu_0024B2F0[];
extern u8 D_eu_0027F700[];
extern u8 D_eu_0027CFE8[];

void func_eu_001AAEC0(void)
{
    for (s32 i = 0; i < 37; i++) {
        Obj_eu_1AAEC0* o = D_eu_0024B2F0[i];
        if (o->f560 != 0) {
            o->vtbl[9](o);
        }
    }
    func_001EFEE0(D_eu_0027F700);
    func_001AE820(D_eu_0027CFE8);
}
