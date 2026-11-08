// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 271/724 (37.4%), checked 2026-11-07
// NEAR: the frame (0x120, with rot as the Mat02 the rotation call fills), the calls, the branches and
//       every VU0 sequence are retail's; the registers are not. Retail keeps the zeroed array in $s8,
//       the next index in $s6 and the member in $s4, &listed.found[0] in $s7 and spills &rot and
//       &owned.found[0]; ours spills the array and keeps &rot in a register. About 25 compiles (next
//       index as a variable, the order of the declarations, a walking pointer for the inner loop).
#include "common.h"
#include "item_keeper.h"
#include "switched_collider.h"
#include "vu0.h"

f32 ArctangentOfRatio(f32 a, f32 b);
f32 WrapAngle(f32 a);
f32 RandomFloatInRange(f32 a, f32 b);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateZeroedBackMemory(s32 size);
void* GetItemKeeperTarget(ItemKeeper* self);
extern float D_00274D20[2];
extern float D_00274D28[2];
struct __attribute__((aligned(16))) PaddedQuadratic { f32 c[3]; };
extern PaddedQuadratic D_00274D30;

extern f32 D_0024DA94[];

void GetObjectWorldPosition(void* obj, void* out);
void GetObjectWorldRotation(void* obj, void* out);
void ComputePolarOffset(void* out, f32 angle, f32 dist, f32 z);

void func_001CC120(ItemKeeper* self)
{
    Vec02 offset;
    Mat02 rot;
    Vec02 pos;
    s32 i = 0;
    PushBackMemoryMark();
    s32* used = (s32*)AllocateZeroedBackMemory(self->listed.count << 2);
    while (i < (self->owned.count < self->listed.count ? self->owned.count : self->listed.count)) {
        Agent* member = self->owned.found[i];
        s32 best = -1;
        f32 bestDist = D_0024DA94[0];
        for (s32 j = 0; j < self->listed.count; j++) {
            if (used[j] == 0) {
                GetObjectWorldPosition(self->listed.found[j], &pos);
                f32 d = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::Dot(Vu0::Sub(Vu0::Q(self->targetPos), Vu0::Q(pos)), Vu0::Sub(Vu0::Q(self->targetPos), Vu0::Q(pos)))));
                if (d < bestDist) {
                    bestDist = d;
                    best = j;
                }
            }
        }
        used[best] = 1;
        Agent* m = self->listed.found[best];
        i++;
        GetObjectWorldPosition(m, (u8*)member + 0x900);
        GetObjectWorldRotation(m, &rot);
        *(f32*)((u8*)member + 0x910) = ArctangentOfRatio(rot.r[0].y, rot.r[0].x);
    }
    PopBackMemoryMark();
    if (i != self->owned.count) {
        f32 cnt = (f32)self->owned.count;
        f32 step = 6.2831855f / cnt;
        f32 radius = cnt * D_00274D20[0] * 0.15915494f;
        u8* target = (u8*)GetItemKeeperTarget(self);
        f32 ang0;
        if (target != 0) {
            ang0 = ArctangentOfRatio(*(f32*)(target + 0x154), *(f32*)(target + 0x150));
        } else {
            ang0 = 0.0f;
        }
        if (i < self->owned.count) {
            Agent** p = &self->owned.found[i];
            do {
                i++;
                Agent* m = *p;
                f32 r = RandomFloatInRange(D_00274D28[0], D_00274D28[1]);
                p++;
                f32 ang = WrapAngle(ang0 + r * step);
                f32 r2 = RandomFloatInRange(D_00274D30.c[0], D_00274D30.c[1]);
                ComputePolarOffset(&offset, ang, r2 * radius, 0.0f);
                u128 q = Vu0::Add(Vu0::Q(self->targetPos), Vu0::Q(offset));
                *(f32*)((u8*)m + 0x910) = ang;
                Vu0::Q(*(Vec02*)((u8*)m + 0x900)) = q;
                ang0 = WrapAngle(ang0 + step);
            } while (i < self->owned.count);
        }
    }
}
