// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1171/1196 (97.9%), checked 2026-11-08
// NEAR (2026-11-08, worker night-large2): both states are retail's but for the two clip-range
// calls (13 lines): retail keeps the entry's mover in v0, the animation in v1 and the
// sequence in a0 (its count loaded into a0 in the call's delay slot), ours puts the mover in
// v1, the animation in a0 and the sequence in a3. Found on the way: the target as the first
// argument of ComputeObjectFrameAtTime, SetPlayerBlendWeights with its floats first, the
// distance through ToFloatMoved, the two clamps of case 12 as Limit (case 14's as Clamp).
// Tried: the mover or the animation as named locals, the chain written twice, the floats-first
// prototype of FindCyclicRangeIndex (pose_source.cpp's).
// In the context of its file, src/main/gauge_agent.cpp.
// Still differs (2026-11-08, night-close5): FindCyclicRangeIndex with its floats first (pose_source.cpp's order) gives 14 lines, the sequence's f34 through g 62.
#include "common.h"
#include "vu0.h"
#include "switched_collider.h"
#include "value_range.h"
#include "c8b.h"
#include "camera.h"
#include "attachment.h"
#include "globals.h"

extern f32 D_002649D0[2];
extern f32 D_00264A00[4];
extern f32 D_00264A10[4];
extern f32 D_00264A20[5];
void ComputeObjectFrameAtTime(void* a, s32 b, void* c, s32 d, s32 e, s32 f, f32 g);
struct QuadraticCurve {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};

// The sequence an Entry8B's mover holds at 0x10 (func_0018AE38): FindCyclicRangeIndex's pairs.
struct ClipSpan8B {
    u8 pad00[0x04];
    s32 count;              // 0x04
    void* pairs;            // 0x08
};

extern ValueRange g_unitRange;
extern Camera* g_camera;
extern Player* g_player;
void UpdateAgentState(void* self);
void GetGaugeAgentLevelFactor(GaugeAgent* a0, f32* a1);
f32 ArctangentOfRatio(f32 y, f32 x);
f32 WrapAngle(f32 a);
void SetPlayerBlendWeights(f32 angle, f32 weight, void* self, void* blend, s32 table);
Entry8B* FindEntryByObjectId(Gr8B* self, s32 key);
s32 FindCyclicRangeIndex(s32 count, void* pairs, f32 x, f32 period, f32* out);
void RecordCameraTimestamp(Camera* c);
void StartSoundEffect(s32 a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
s32 IsAgentFacingBlocked(void* self);
void SetAgentFacingAngles(void* self, f32 yaw, f32 pitch);
typedef Agent* (*GaugeTargetFn)(GaugeAgent* self);

void UpdateGaugeAgentState(GaugeAgent* self)
{
    typedef Vu0::Vec Vec;
    UpdateAgentState(self);
    switch (self->f724) {
    case 12: {
        if (self->f7E0 == 0) {
            break;
        }
        if (g_player != 0 && g_player->f275C != 0) {
            return;
        }
        Agent* tgt = ((GaugeTargetFn)((void**)self->desc)[0x198 / 4])(self);
        f32 weight;
        if (tgt != 0) {
            f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(Vec::Of(self->v140), Vec::Of(tgt->v140)).q,
                                                        Vu0::Sub(Vec::Of(self->v140), Vec::Of(tgt->v140)).q)));
            f32 near = g_unitRange.Limit(((QuadraticCurve*)D_00264A00)->Eval(dist));
            f32 far = g_unitRange.Limit(((QuadraticCurve*)D_00264A10)->Eval(dist));
            f32 level;
            GetGaugeAgentLevelFactor(self, &level);
            weight = level * far + (1.0f - level) * near;
        } else {
            weight = 1.0f;
        }
        f32 heading = ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x);
        f32 turn = __builtin_fabsf(WrapAngle(heading - self->f638));
        f32 k = g_unitRange.Clamp(((QuadraticCurve*)D_00264A20)->Eval(turn));
        SetPlayerBlendWeights(self->f638, weight * k, self, (u8*)self + 0xC20, self->fE00);
        Gr8B* g = (Gr8B*)self->fE00;
        ClipSpan8B* a = *(ClipSpan8B**)((u8*)FindEntryByObjectId(g, (s32)self->f610)->mover + 0x10);
        s32 offFirst = FindCyclicRangeIndex(a->count, a->pairs, self->f7E0->time, ((Gr8B*)self->fE00)->f34, 0) == 0;
        ClipSpan8B* b = *(ClipSpan8B**)((u8*)FindEntryByObjectId((Gr8B*)self->fE00, (s32)self->f614)->mover + 0x10);
        s32 offSecond = FindCyclicRangeIndex(b->count, b->pairs, self->f7E0->time, ((Gr8B*)self->fE00)->f34, 0) == 0;
        if (offFirst && self->fE04 == 0) {
            RecordCameraTimestamp(g_camera);
            StartSoundEffect(0x1CC, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
        if (offSecond && self->fE08 == 0) {
            RecordCameraTimestamp(g_camera);
            StartSoundEffect(0x1CC, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
        self->fE04 = offFirst;
        self->fE08 = offSecond;
        break;
    }
    case 14: {
        if (IsAgentFacingBlocked(self)) {
            return;
        }
        Vec02 to;
        Vec02 curve = { 0.0f, 0.00016666666f, 0.0f, 0.0f };
        f32 level;
        GetGaugeAgentLevelFactor(self, &level);
        f32 rest = 1.0f - level;
        f32 limit = (1.0f - rest) * D_002649D0[0] + rest * D_002649D0[1];
        Agent* tgt = ((GaugeTargetFn)((void**)self->desc)[0x198 / 4])(self);
        if (tgt != 0) {
            f32 dist = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(Vec::Of(tgt->v140), Vec::Of(self->v140)).q,
                                                        Vu0::Sub(Vec::Of(tgt->v140), Vec::Of(self->v140)).q)));
            f32 t = g_unitRange.Clamp(((QuadraticCurve*)&curve)->Eval(dist));
            ComputeObjectFrameAtTime(tgt, 0, &self->vE40, 0, 0, 0, t <? limit);
            Vu0::Q(to) = Vu0::Sub(Vec::Of(self->vE40), Vec::Of(self->v140)).q;
            SetAgentFacingAngles(self, ArctangentOfRatio(to.y, to.x), 0.0f);
        }
        break;
    }
    }
}
