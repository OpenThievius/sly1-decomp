// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 920/908, checked 2026-11-08
// NEAR: the frame (0x1A0, with the ColliderSpan at 0x50 and the count and list at 0xD0), the calls,
//       the min.s (the `<?` operator), the loop's materialised test and every VU0 sequence are
//       retail's. Still differs: retail keeps the high half of the clock's address in $fp from
//       before the first branch (gcse hoists the lui into the beqz's slot) and forms the time's
//       address from it at both reads; ours loads it twice, and $fp then holds the filter's high
//       half (retail's s7), which renumbers the saved registers of the loop (the up vector's in s6
//       for ours s1). 2026-11-08, night-size1: the time read through an inline ClockTime(g_gameClock)
//       gives retail's first block (addiu v1 from the high part, the loads in order); 6 words
//       closer. Before: about 25 compiles (the clock through a pointer, the test as an inline
//       function, the order of the locals).
#include "common.h"
#include "switched_collider.h"
#include "globals.h"
#include "vu0.h"

extern f32 g_gameClock[];
extern float D_00274C98[2];
#define F(T, o) (*(T*)((u8*)self + (o)))
void SnapPointToOwnerGraph(s32 graph, Vec02* in, Vec02* out);
s32 FindOwnerGraphPath(s32 graph, Vec02* a, Vec02* b, s32 max, Vec02* out);
void GatherCollidersInBox(World* world, s32 p1, Vec02* lo, Vec02* hi, s32 (*filter)(void*, Collider*), Agent* self, s32* n, Collider*** list);
s32 FindNearestSpanObject(s32 flags, Vec02* a, Vec02* b, s32 count, Collider** list, ColliderSpan* out);
s32 IsAgentPathBlocker(void* unused, Collider* self);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);

static inline s32 IsNearPoint(u128 a, u128 b, f32 reach)
{
    return Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(a, b), Vu0::Sub(a, b)))) < reach;
}

// The game clock's time (its second word), read through the clock's address.
static inline f32 ClockTime(const f32* clock) { return clock[1]; }

void func_001C8590(Agent* self)
{
    if (F(s32, 0xA60) != 0) {
        if (!(D_00274C98[0] < ClockTime(g_gameClock) - F(f32, 0xA64))) return;
    }
    s32 ok;
    if (F(s32, 0xB90) != 0) {
        F(s32, 0x92C) = 2;
        u128 pos = Vu0::Q(self->v140);
        u128 goal = Vu0::Q(self->vA50);
        f32 len = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(goal, pos), Vu0::Sub(goal, pos))));
        Vu0::Q(F(Vec02, 0x940)) = pos;
        f32 maxLen = __builtin_fabsf(F(f32, 0xB94));
        Vec02 a;
        if (maxLen < len) {
            f32 t = maxLen / len;
            Vu0::Q(a) = Vu0::MulXSum(goal, Vu0::Scalar(t), pos, Vu0::Scalar(1.0f - t));
        } else {
            Vu0::Q(a) = goal;
        }
        Vec02 b;
        if (self->f928 != 0) {
            SnapPointToOwnerGraph(self->f928, &a, &b);
        } else {
            b = a;
        }
        f32 reach = (maxLen <? len) * 0.5f;
        Vec02 c = b;
        while (IsNearPoint(Vu0::Q(c), Vu0::Q(self->v140), reach)) {
            f32 next = maxLen + 100.0f;
            maxLen = next <? len;
            f32 t = maxLen / len;
            Vu0::Q(c) = Vu0::MulXSum(Vu0::Q(self->vA50), Vu0::Scalar(t), Vu0::Q(self->v140), Vu0::Scalar(1.0f - t));
            SnapPointToOwnerGraph(self->f928, &c, &c);
        }
        PushBackMemoryMark();
        Vec02 d1;
        Vec02 d4;
        ColliderSpan span;
        s32 count;
        Collider** list;
        Vu0::Q(d4) = Vu0::MulAddX(Vu0::Q(c), Vu0::Q(D_00248D20), Vu0::Scalar(500.0f));
        Vu0::Q(d1) = Vu0::MulAddX(Vu0::Q(c), Vu0::Q(D_00248D20), Vu0::Scalar(-500.0f));
        GatherCollidersInBox(self->world, (s32)self, &d1, &d4, IsAgentPathBlocker, self, &count, &list);
        if (FindNearestSpanObject(1, &d4, &d1, count, list, &span) != 0) {
            f32 h = -((f32*)F(void*, 0x388))[(F(s32, 0x6D0) << 2) + 2] - 1.0f;
            if (F(s32, 0xC04) != 0) h += F(f32, 0x6CC);
            Vu0::Q(c) = Vu0::MulAddX(Vu0::Q(span.q[0]), Vu0::Q(D_00248D20), Vu0::Scalar(h));
        }
        PopBackMemoryMark();
        F(Vec02, 0x950) = c;
        ok = 1;
    } else {
        F(s32, 0x92C) = 0;
        if (self->f928 != 0) {
            F(s32, 0x92C) = FindOwnerGraphPath(self->f928, &self->v140, &self->vA50, 0x10, (Vec02*)((u8*)self + 0x940));
        }
        ok = 1;
        if (F(s32, 0x92C) == 0) {
            F(Vec02, 0x940) = self->v140;
            F(Vec02, 0x950) = self->vA50;
            F(s32, 0x92C) = 2;
        }
    }
    F(s32, 0x930) = 0;
    F(s32, 0xA60) = ok;
    F(f32, 0xA64) = ClockTime(g_gameClock);
}
