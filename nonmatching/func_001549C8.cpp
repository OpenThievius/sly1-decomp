// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 561/580 (96.7%), checked 2026-11-06
#include "common.h"
// NEAR (p58b): 10 lines, unchanged from j40o03: the 200 gets a0 (retail v0) and the copy source v0 (retail a0), f00/f20 stores swap. extern const on the rodata quads changes nothing. Finding: the guard words D_00261F70/74 set after a temp+copy are exactly what GCC 2.95 emits for function-local statics initialised from an inline maker returning by value (`static B s = MakeB();`, see v549_make.cpp: same shape, same 10-line register diff, but it defines the statics so the relocations differ); a constructor (`static B s = B();`) builds in place instead.
// NEAR: 10 lines, all in B_1549C8() + its copy loop: the 200 gets a0 (retail v0), so the copy source (global) takes v0 (retail a0), and the f00/f20 stores swap. With q30 present, local-alloc never gives the 200 v0 in any order tried (j40o03: ~2000 hill-climbed store orders, floor 10; callee return void/s32/ptr/s64; q30 as TImode int, array global, pointer source; float/int constants as locals). Without q30 the 200 does get v0.

struct __attribute__((aligned(16))) Q_1549C8 { s32 a, b, c, d; };
struct Dst_1549C8;
void* FillMemory(void* p, s32 v, s32 n);
extern Q_1549C8 g_unitXVector;
extern Q_1549C8 g_unitZVector;
extern Q_1549C8 D_00248D30;

struct A_1549C8 {
    Q_1549C8 q[9];
    A_1549C8()
    {
        FillMemory(this, 0, 0x90);
        q[1] = D_00248D30;
        q[5] = g_unitXVector;
        q[8] = D_00248D30;
    }
};
struct B_1549C8 {
    f32 f00;
    f32 f04;
    f32 f08;
    s32 pad0C[3];
    f32 f18;
    s32 pad1C;
    f32 f20;
    s32 pad24[3];
    Q_1549C8 q30;
    s32 pad40[3];
    s32 i4C;
    f32 f50;
    f32 f54;
    s32 pad58[6];
    f32 f70;
    s32 pad74;
    f32 f78;
    s32 pad7C;
    B_1549C8()
    {
        FillMemory(this, 0, 0x80);
        f18 = -1500.0f;
        f04 = 750.0f;
        f50 = 1.0f;
        i4C = 200;
        f54 = 1.0f;
        q30 = g_unitZVector;
        f70 = 1.0f;
        f78 = -1.0f;
        f20 = -1.0f;
        f00 = 750.0f;
        f08 = 1.0f;
    }
};
struct C_1549C8 { Q_1549C8 q[13]; };
struct Dst_1549C8 {
    s32 f0;
    A_1549C8 a;
    B_1549C8 b;
    C_1549C8 c;
};

extern s32 D_00261F70;
extern s32 D_00261F74;
extern A_1549C8 D_0027C010;
extern B_1549C8 D_0027C0A0;
extern C_1549C8 D_00261F80;

void InitSpawnRecord(Dst_1549C8* self)
{
    if (!D_00261F70) {
        D_0027C010 = A_1549C8();
        D_00261F70 = 1;
    }
    if (!D_00261F74) {
        D_0027C0A0 = B_1549C8();
        D_00261F74 = 1;
    }
    FillMemory(self, 0, 0x200);
    self->f0 = 1;
    self->a = D_0027C010;
    self->b = D_0027C0A0;
    self->c = D_00261F80;
}
