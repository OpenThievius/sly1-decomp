// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 664/668, checked 2026-11-07
// NEAR: only the lqc2 store/reload remains. Retail stores the difference vector (`sqc2 vf1, 0(sp)`)
//       and loads it back at once (`lqc2 vf1, 0(sp)`) for the dot product, so vmul.xy works in place
//       in vf1; ours forwards the stored value (CSE) and uses vf2. The loop, both arms, the clamps and
//       the switch are retail's. About 40 compiles (for(;;) with the test at the top gives retail's
//       jump to the else arm; Set/Q stores, a struct holding the u128, a pointer to the local, a
//       helper reading the operand from memory: all forwarded).
#include "common.h"
#include "switched_collider.h"
#include "globals.h"
#include "vu0.h"

f32 ArctangentOfRatio(f32 a, f32 b);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);
#define F(T, o) (*(T*)((u8*)self + (o)))
struct __attribute__((aligned(16))) PaddedQuadratic { f32 c[3]; };
extern PaddedQuadratic D_00274CA0;
extern PaddedQuadratic D_00274CB0;
extern PaddedQuadratic D_00274CC0;
extern float D_00274CD0[2];
extern float D_00274CD8[2];
extern float D_00274C94;

static inline f32 ClampTo(f32 v, const f32* r)
{
    f32 l = r[0];
    f32 h = r[1];
    f32 out;
    if (v < l)
        out = l;
    else if (h < v)
        out = h;
    else
        out = v;
    return out;
}

void func_001C8920(Agent* self)
{
    ((void (*)(Agent*))self->desc08()->m5F)(self);
    for (;;) {
        if (!(self->f930 < self->f92C)) break;
        s32 i = self->f930;
        u128 d = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(*(Vec02*)((u8*)self + 0x940 + (i << 4))));
        s32 far = D_00274C94 < Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
        if (far) break;
        self->f930 = i + 1;
    }
    u128 a, b;
    if (self->f930 < self->f92C) {
        b = Vu0::Q(self->v140);
        a = Vu0::Q(*(Vec02*)((u8*)self + 0x940 + (self->f930 << 4)));
    } else {
        s32 m = self->f92C;
        a = Vu0::Q(*(Vec02*)((u8*)self + 0x930 + (m << 4)));
        b = Vu0::Q(*(Vec02*)((u8*)self + 0x920 + (m << 4)));
    }
    Vec02 dir;
    Vu0::Set(dir, Vu0::Sub(a, b));
    f32 yaw;
    if (1.0f < Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(dir), Vu0::Q(dir))))) {
        yaw = ArctangentOfRatio(dir.y, dir.x);
    } else {
        yaw = self->f638;
    }
    f32 pitch;
    if (F(s32, 0xB1C) == 0) {
        pitch = 0.0f;
    } else {
        u128 e = Vu0::Sub(Vu0::Q(self->vA50), Vu0::Q(self->v140));
        f32 dist = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(e, e)));
        f32 dz = self->vA50.z - self->v140.z;
        switch (self->f724) {
        case 5: case 6: case 7: case 10: case 12: case 13: case 14: case 15:
            dz += F(f32, 0xB20);
            break;
        }
        f32 g1 = D_00274CA0.c[0] + dist * (D_00274CA0.c[1] + dist * D_00274CA0.c[2]);
        g1 = ClampTo(g1, D_00274CB0.c);
        f32 adz = __builtin_fabsf(dz);
        f32 g2 = D_00274CC0.c[0] + adz * (D_00274CC0.c[1] + adz * D_00274CC0.c[2]);
        g2 = ClampTo(g2, D_00274CD0);
        pitch = g1 * g2 * D_00274CD8[0];
        if (dz < 0.0f) pitch = -pitch;
    }
    SetAgentFacingAngles(self, yaw, pitch);
}
