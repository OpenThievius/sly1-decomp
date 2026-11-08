// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 768/776 (99.0%), checked 2026-11-07
#include "common.h"
#include "switched_collider.h"
#include "asm_func.h"
#include "vu0.h"
#include "list_iter.h"
#include "object_group.h"
#include "world.h"
#include "gauge_counted_object.h"
#include "object_link.h"
#include "attachment.h"
#include "shapes.h"
#include "globals.h"
#include "game_progress.h"
#include "screen_element.h"
#include "sound_state_object.h"
#include "pad_record.h"
#include "mul_rotation.h"
#include "value_range.h"
// NEAR (2026-11-08, worker vu0w4-e1): six instructions differ and nothing else: retail forms the
// addresses of n (sp+0xF0), the position (sp+0x10) and the list (sp+0xF4), which the loop keeps in
// stack slots 0xF8, 0x100 and 0xFC, in that order before the loop; here the same slots hold the
// same addresses and they are formed list, n, position. All six orders of the three pointer
// variables, and their place in the function, were tried; this one is the closest.
extern float g_gameTime[];
extern f32 D_0026A710;
extern f32 D_0026A714;
extern f32 D_0026A718;
extern f32 D_0026A71C;
extern f32 D_0026A820;
extern f32 D_0026A824;
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
s32 IsObjectOfKind(void* self, s32 kind);

void UpdateSwitchedCollider(GaugeCollider* self);
s32 FindColliderFloorContact(void* self, s32 a, s32 b);
void BuildPerpendicularPair(Vec02* in, Vec02* out, const Vec02* a, const Vec02* b);
void ComputeOscillatorDisplacement(f32 f, void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5);
void ClearRootTries(void* self);
void ConvertPositionToWorld(void* obj, Vec02* out);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, s32 p1, Vec02* lo, Vec02* hi, s32 (*filter)(void*, Collider*), void* p4, s32* n, Collider*** list);
Collider* FindNearestSpanObject(s32 flags, void* a1, void* a2, s32 count, Collider** list, ColliderSpan* out);
s32 AcceptColliderOfOtherRoot(void* a, Collider* self);
extern const Vec02 D_00248D20;
extern const Vec02 g_unitXVector;

struct GaugeSpanOwner { u8 pad00[0x278]; u8* f278; };

void func_00196EB0(GaugeCollider* self)
{
    Vec02 sum;
    Vec02 pos;
    Vec02 lo;
    Vec02 hi;
    ColliderSpan span;
    Vec02 dir;
    s32 n;
    Collider** list;
    u32 i;

    UpdateSwitchedCollider(self);
    if (FindColliderFloorContact(self, 0, 0) != 0) {
        self->f61C = g_gameTime[0];
        self->f628 = D_0026A718;
        self->f624 = D_0026A71C;
    } else if (self->f644 != 0) {
        self->f61C = g_gameTime[0];
        self->f628 = D_0026A710;
        self->f624 = D_0026A714;
    }
    sum = *(Vec02*)&D_00248D30;
    s32* np = &n;
    Collider*** lp = &list;
    Vec02* pp = &pos;
    for (i = 0; i < 4; i++) {
        ConvertPositionToWorld(self->f64C[i], pp);
        hi = pos;
        lo = pos;
        hi.z = hi.z + D_0026A820;
        lo.z = lo.z + D_0026A824;
        PushBackMemoryMark();
        GatherCollidersInBox(self->world, 0, &hi, &lo, AcceptColliderOfOtherRoot, self, np, lp);
        Collider* hit = FindNearestSpanObject(1, &hi, &lo, n, list, &span);
        if (hit != 0) {
            *(Quad16*)&dir = span.q[2];
            if (IsObjectOfKind(hit, 0x1F) != 0 && ((GaugeSpanOwner*)hit)->f278 != 0) {
                Vec02 pair[2];
                Vec02 in = dir;
                BuildPerpendicularPair(&in, pair, &g_unitXVector, &D_00248D20);
                ComputeOscillatorDisplacement(50.0f, *(void**)(((GaugeSpanOwner*)hit)->f278 + 0xC), &span, pair, 0, pair, 0);
                Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(pair[0]), Vu0::Q(pair[1])), Vu0::Q(D_00248D20)));
            }
            if (!(dir.z < 0.7f)) {
                goto keep;
            }
        }
        dir = self->v630;
    keep:
        Vu0::Q(sum) = Vu0::MulAddX(Vu0::Q(sum), Vu0::Q(dir), Vu0::Scalar(0.25f));
        PopBackMemoryMark();
    }
    Vu0::Q(self->v630) = Vu0::DivX(Vu0::Q(sum), Vu0::Length(Vu0::Q(sum)));
    ClearRootTries(self);
}

