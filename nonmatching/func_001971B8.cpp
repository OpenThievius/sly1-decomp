// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 532/540 (98.5%), checked 2026-11-08
// Still differs (2026-11-08, night-lwx): with FromFloatAt as "rV" the weight's lw s0,%lo(D_0026A828)(s0) is retail's; left: the loop preheader's lui s6 comes before move s2,sp (retail after). list through a pointer local, *(list + i) and o declared first leave it.
// NEAR: The gauge collider's best-target search (seven instructions differ, all the order of the prologue's lui/addiu and the register of one load). The loop, the frame, every call and the VU0 code are retail's. Retail loads the weight float with `lw s0,%lo(D_0026A828)(s0)` (the result in the register of the address, which then dies) and ours with `lw v0,...(s0)`; the same trait as func_00145E68's last weight. The weight is ScalarAt (Vu0::Scalar for a float in memory), which gives retail's shared slot at 0x170.
#include "common.h"
#include "switched_collider.h"
#include "asm_func.h"
extern f32 g_gameTime[];
#include "vu0.h"
#include "globals.h"
#include "shapes.h"
#include "placed_object.h"

f32 ArctangentOfRatio(f32 a, f32 b);
s32 GatherObjectsById(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
f32 D_0026A828 = 0.25f;
f32 D_0026A82C = 0.7f;
f32 D_0026A830 = 250.0f;

f32 WrapAngle(f32 a);
void BuildAxisAngleMatrix(void* axis, void* out, f32 angle);
void ConvertPositionToWorld(void* n, void* out);
void MeasurePointToSegment(Vec02* p, Vec02* a, Vec02* b, f32* t, f32* dist);
s32 ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, s32 e, s32 f, f32 t);

// Vu0::Scalar for a float in memory: FromFloatAt into a slot of its own.
static inline u128 ScalarAt(const f32& f)
{
    Vu0::Slot t;
    Vu0::Q(t) = Vu0::FromFloatAt(f);
    return Vu0::Q(t);
}

PlacedObject* func_001971B8(GaugeCollider* self)
{
    PlacedObject* list[0x40];
    Mat02 rot;
    Vec02 ahead;
    Vec02 here;
    Vec02 start;
    Vec02 diff;
    PlacedObject* best = 0;
    BuildAxisAngleMatrix((void*)&g_unitZVector, &rot, self->f618);
    Vu0::Q(ahead) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(self->v150), ScalarAt(D_0026A828));
    ConvertPositionToWorld(*(void**)((u8*)self + 0x670), &here);
    Vu0::Q(start) = Vu0::Add(Vu0::Rotate(rot, Vu0::Q(*(Vec02*)((u8*)*(void**)((u8*)self + 0x670) + 0x40))), Vu0::Q(ahead));
    Vu0::Q(diff) = Vu0::Sub(Vu0::Q(start), Vu0::Q(here));
    f32 nearest = D_0026A830;
    s32 n = GatherObjectsById(self->world, 5, 0x48, 0, 0x40, list);
    for (s32 i = 0; i < n; i++) {
        Vec02 framePos;
        Mat02 frameRot;
        Vec02 world;
        Vec02 end;
        Vec02 d;
        f32 t;
        f32 dist;
        PlacedObject* o = list[i];
        if (((SwitchedCollider*)o)->f550 != 0) {
            continue;
        }
        ComputeObjectFrameAtTime(((BaseObject*)((SwitchedCollider*)o)->f554)->parent, 0, &framePos, &frameRot, 0, 0, D_0026A828);
        ConvertPositionToWorld((void*)((SwitchedCollider*)o)->f554, &world);
        Vu0::Q(world) = Vu0::Add(Vu0::Q(world), Vu0::Q(diff));
        Vu0::Q(end) = Vu0::Add(Vu0::Rotate(frameRot, Vu0::Q(*(Vec02*)((u8*)((SwitchedCollider*)o)->f554 + 0x40))), Vu0::Q(framePos));
        MeasurePointToSegment(&start, &world, &end, &dist, &t);
        if (t < nearest) {
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(world), Vu0::Q(self->v140));
            if (!(D_0026A82C < __builtin_fabsf(WrapAngle(ArctangentOfRatio(d.y, d.x) - self->f618)))) {
                nearest = t;
                best = o;
            }
        }
    }
    return best;
}
