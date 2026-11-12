// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 241/312 (77.2%), checked 2026-11-12
// w37-f3 (2026-11-12): the four ring records matched as brace initialisers whose first group's stores wait for a CLOBBER: store_constructor emits `(clobber (mem:BLK ...))` for a union-typed member with a non-zero initialiser, every earlier store of the record precedes it and every later one follows (docs/toolchain/large-functions.md, "A brace initialiser's union member is a CLOBBER"). Not tried here: this record written as a brace initialiser with a union member where -1.0's group starts (0x70; 0x50 and 0x00 are candidates too), which would put -0.5's store before -1.0's load.
// w25 (2026-11-11, w25-deps): the pending-list flush at a block's 33rd memory reference (docs/toolchain/sched1.md, "The 33rd memory reference of a block is a barrier") is not reached here (most pending: 12; FillMemory's call resets the count), so it is not what holds the late stores; the other sources of a store's dependents are listed in docs/toolchain/large-functions.md, "Dependence sources enumerated".
// NEAR: order: the first block is exact with the destination pointer declared before the memset;
//       the second differs only in the order its constants are loaded and stored.
// See docs/TOOLCHAIN.md, "Open: constructor stores kept in source order": retail is sched2 of an order sched1 does not give here (2026-11-08).
// 2026-11-10: retail's registers need sched1 to store -0.5 (f20) before it loads -1.0 (f74), both $f0;
//       independent frame stores never allow it, and one variable reused for both (26 lines differ)
//       becomes global and cannot take $f0 (local-alloc emulator; TOOLCHAIN.md, func_001930B8).
// 2026-11-10 (wave 15): `D = (Cfg_1930B8){ ... };` (a compound literal, no FillMemory written) is the
//       plausible form: the global's address before the compiler's memset, the first record exact,
//       the second the same differences (34 lines). Retail's $f0 needs -0.5/-1.0 as ONE local quantity
//       (REG_N_DEATHS 1), which no plain form gives (docs/toolchain/large-functions.md, func_001930B8).
#include "common.h"
#include "shapes.h"

struct __attribute__((aligned(16))) Cfg_1930B8 {
    f32 f0; f32 f4; f32 f8; u8 padC[0xC]; f32 f18; u8 pad1C[4]; f32 f20; u8 pad24[0xC]; Quad16 q30; u8 pad40[0xC]; s32 i4c; f32 f50; f32 f54; u8 pad58[8]; Quad16 q60; f32 f70; f32 f74; u8 pad78[8];
};
typedef char check_Cfg_1930B8[sizeof(Cfg_1930B8) == 0x80 ? 1 : -1];

extern u8 D_00248D30[];
extern u8 g_unitZVector[];
extern Cfg_1930B8 D_00604700;
extern Cfg_1930B8 D_00269C10;
void* FillMemory(void* p, s32 zero, s32 size);

void ConstructSwitchedColliderDefaults(s32 a0, s32 a1)
{
    if (a1 == 0xFFFF && a0 != 0) {
        {
            Cfg_1930B8 c;
            Cfg_1930B8* p = &D_00604700;
            FillMemory(&c, 0, 0x80);
            c.q60 = *(Quad16*)D_00248D30;
            *p = c;
        }
        {
            Cfg_1930B8 c;
            Cfg_1930B8* p = &D_00269C10;
            FillMemory(&c, 0, 0x80);
            c.f0 = 1000.0f;
            c.f18 = -1750.0f;
            c.f4 = 1200.0f;
            c.f20 = -0.5f;
            c.q30 = *(Quad16*)g_unitZVector;
            c.i4c = 1;
            c.f50 = 0.5f;
            c.f54 = 2.0f;
            c.f8 = 1.0f;
            c.f70 = 1.0f;
            c.f74 = -1.0f;
            *p = c;
        }
    }
}
