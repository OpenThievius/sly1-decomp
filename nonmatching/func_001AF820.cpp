// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 724/728, checked 2026-11-07
// NEAR: (2026-11-08, night-size3) fixed: the end point is stored to buf[f20 + 1], not buf[f20]
// (retail's sq at 16(v0)); the call's two 1.0s are one constant (w = a2 ? a2->f40 : 1.0f written
// in the call, retail's mov.s f12,f13 in the branch's delay slot); the state test is a switch of
// cases 0-2 and 4-6, retail's compare tree (slti 3, 7, 4) with the store twice. Still differs: the
// saved registers (retail: self s4, the child's points s5, fp s8, last s7, the copy loop's index
// s2, count s1 and pointer s0; here s5, s4, s7, s8, s0, s2, s1), and one reload of the next index
// (lw s0,24(sp)) in the state test's first delay slot, 4 bytes; with the test as one condition (st
// >= 0 && st != 3 && st < 7) the size is retail's but the tree is not. Earlier: about 60 compiles
// (the weights and rows as temporaries, the state test as nested ifs or one condition, the width
// as a ternary or a variable).
#include "common.h"
#include "timed_object.h"
#include "world.h"
#include "vu0.h"

f32 ComputeTimedGroupRamp(TimedGroup* o, TimedGroupChild* c);

struct DrawPoints {
    u8 pad0[0xC];
    s32 count;
    u8 pad10[0x18 - 0x10];
    Vec02* points;
};

void DrawCollider(TimedGroup* self, void* a1, void* a2);
void TransformPointBetweenFrames(TimedGroup* from, s32 to, Vec02* in, Vec02* out);
void func_001268B8(void* a0, void* a1, Vec02* a2, Vec02* a3, f32 f12, f32 f13);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
Vec02* AllocateBackMemory(s32 size);

void func_001AF820(TimedGroup* self, void* a1, void* a2)
{
    DrawCollider(self, a1, a2);
    s32 st = self->state;
    if (st == 8 || st < 0) return;
    void* fp;
    if (st < 4) {
        fp = *(void**)((u8*)self + 0xAE4);
    } else if (st < 8) {
        fp = *(void**)((u8*)self + 0xAE8);
    } else {
        return;
    }
    if (fp == 0) {
        fp = (void*)self->world->f1D14;
        if (fp == 0) return;
    }
    s32 i = 0;
    PushBackMemoryMark();
    Vec02* buf = AllocateBackMemory(*(s32*)((u8*)self + 0xAE0) << 4);
    while (i < self->groupCount) {
        TimedGroupChild* g = &self->groups[i];
        f32 acc = 0.0f;
        f32 total = ComputeTimedGroupRamp(self, g);
        DrawPoints* src = *(DrawPoints**)((u8*)g->child + 0x34);
        s32 n = src->count;
        if (*(s32*)((u8*)g + 0xC) != 0) {
            s32 lim = *(s32*)((u8*)g + 0x20) + 2;
            if (lim < n) n = lim;
        }
        s32 next = i + 1;
        s32 last = n - 1;
        for (s32 k = 0; k < n; k++) {
            TransformPointBetweenFrames(self, 0, &src->points[k], &buf[k]);
        }
        if (*(s32*)((u8*)g + 0xC) != 0) {
            buf[*(s32*)((u8*)g + 0x20) + 1] = *(Vec02*)((u8*)g + 0x10);
        }
        for (s32 k = 0; k < last; k++) {
            u128 d = Vu0::Sub(Vu0::Q(buf[k]), Vu0::Q(buf[k + 1]));
            f32 len = Vu0::ToFloat(Vu0::Sqrt(Vu0::Dot(d, d)));
            f32 rest = total - acc;
            if (rest < len) {
                f32 t = rest / len;
                u128 ws = Vu0::Scalar(1.0f - t);
                u128 p0 = Vu0::Q(buf[k]);
                u128 wt = Vu0::Scalar(t);
                u128 p1 = Vu0::Q(buf[k + 1]);
                Vu0::Q(buf[k + 1]) = Vu0::MulXSum(p0, ws, p1, wt);
            }
            func_001268B8(fp, a1, &buf[k], &buf[k + 1], 1.0f, a2 != 0 ? *(f32*)((u8*)a2 + 0x40) : 1.0f);
            acc += len;
            if (total < acc) break;
        }
        i = next;
        switch (self->state) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
            g->fallScale = acc;
            break;
        }
    }
    PopBackMemoryMark();
}
