// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 432/448 (96.4%), checked 2026-11-08
#include "common.h"
#include "vu0.h"
#include "state_notifier.h"
#include "deferred_request.h"
#include "globals.h"
// NEAR (2026-11-08, worker night-mmi): all but three instructions: retail stores the splat
// (sq v0, 0x50(sp)) right after its pextlw and only then forms &s in s0; here sched1 puts the
// addiu s0 between the mfc1 and the splat and the store after the two lui. Each arm evaluates
// the curve itself (cross-jumping merges the tails, leaving the c[0] load in the arms, as
// retail's), the clamp's 0 and 1 are locals, and k = c[0]; k += ... gives retail's add.s.
// The splat inside each arm cross-jumps further than retail's.

extern f32 D_0026185C;
extern f32 D_002619E4;
extern f32 D_002619E8;
extern f32 D_00261A80[4];
extern f32 D_00261A90[4];
void BuildScaledTransformMatrix(const void* pos, const void* rot, void* scale, void* out);
void BuildPlacedObjectTransform(PlacedObject* self, void* src, void* dst);
Mat4A MultiplyMatrices(const void* a, const void* b);
void func_00125C90(PlacedObject* self, void* a, void* m);

void ApplyStateNotifierScale(StateNotifier* self, void* a, void* m)
{
    if (self->flags & (1ULL << 32)) return;
    s32 state = self->state;
    switch (state) {
    case 4:
    case 5: {
        DrawTransform t;
        Quad16 scale;
        Mat4A s;
        f32 k;
        if (state == 4) {
            f32 v = (D_0026185C - self->stateSince) / D_002619E4;
            f32 lo = 0.0f;
            f32 hi = 1.0f;
            f32 x;
            if (v < lo) x = lo;
            else if (hi < v) x = hi;
            else x = v;
            f32* c = D_00261A80;
            k = c[0];
            k += x * (c[1] + x * c[2]);
            } else {
            f32 v = (D_0026185C - self->stateSince) / D_002619E8;
            f32 lo = 0.0f;
            f32 hi = 1.0f;
            f32 x;
            if (v < lo) x = lo;
            else if (hi < v) x = hi;
            else x = v;
            f32* c = D_00261A90;
            k = c[0];
            k += x * (c[1] + x * c[2]);
            }
        Vu0::Q(scale) = Vu0::Splat(k);
        BuildScaledTransformMatrix(&D_00248D30, &g_identityMatrix, &scale, &s);
        BuildPlacedObjectTransform(self, m, &t);
        *(Mat4A*)&t = MultiplyMatrices(&t, &s);
        m = &t;
        break;
    }
    }
    func_00125C90(self, a, m);
}
