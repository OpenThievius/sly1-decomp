// SPDX-License-Identifier: AGPL-3.0-or-later
// The cone agent (class 0x0A), 0x167D68 to 0x168130 (no .rodata, .data or .bss of its own): its
// set-up, start, draw and free test. Its start is placed_object_model.cpp's proved end (that
// file's static initialiser); its end is not proved by retail, only by the change of role to
// the display (display.cpp): these four methods read no .rodata or .data, so the cut could lie
// from 0x167F10 to 0x168130. The name is ours, after its role.
#include "common.h"
#include "asm_func.h"
#include "system.h"
#include "listed_collision_part.h"
#include "pooled_object.h"
#include "path_curve_object.h"
#include "point_object.h"
#include "list_iter.h"
#include "attachment.h"
#include "globals.h"
#include "strip_mesh.h"
#include "bump_allocator.h"
#include "texture_header.h"
#include "shapes.h"
#include "vu0.h"


void DrawAgent(void);

struct GatheredEventObject { u8 pad0[0x328]; s32 f328; };
struct GatheredObjects { s32 count; GatheredEventObject** items; };

void StartAgent(void* self);
void* FindFirstObjectByIdMode4(void* a, s32 b, void* c);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherAnimationEventObjects(void* a, void* b, s32* c, void** d);
void* CreateRecord2505C0(void);
void AppendToSmallList(void* a, void* b);

void InitAgent(void* self);
void InitConeAgent(ConeAgent* self);

void* FindFirstObjectByIdMode4(void* obj, s32 id, s32 flags);

void* FindFirstObjectByIdMode4(void* a, s32 b, s32 c);


void* IsObjectOfKind(void* node, s32 flags);


void InitConeAgent(ConeAgent* self)
{
    InitAgent(self);
    self->fC20 = 1000.0f;
    self->fC24 = 1500.0f;
    self->fC28 = 0.78539816f;
    self->fC2C = 3.14159265f;
    self->fC10 = 2000.0f;
    self->fC30 = -1;
    self->fC14 = 300.0f;
    self->fC18 = -1;
    self->f73C = 300.0f;
    self->f738 = 0;
    self->f74C = 1.04719755f;
}

void StartConeAgent(ConeAgent* self)
{
    GatheredObjects out;
    s32 i;

    StartAgent(self);
    if (self->fC18 != -1) {
        self->fC1C = (s32)FindFirstObjectByIdMode4(self->world, self->fC18, self);
    }
    if (self->fC30 != -1) {
        self->fC34 = (s32)FindFirstObjectByIdMode4(self->world, self->fC30, self);
    }
    if (self->f750 != 0) {
        PushBackMemoryMark();
        GatherAnimationEventObjects(self->f750, self, &out.count, (void**)&out.items);
        for (i = 0; i < out.count; i++) {
            GatheredEventObject* e = out.items[i];
            if (e->f328 == 0) {
                void* t = CreateRecord2505C0();
                e->f328 = (s32)t;
                AppendToSmallList(t, e);
            }
        }
        PopBackMemoryMark();
    }
}

void DrawConeAgent(void)
{
    DrawAgent();
}

s32 IsPadSelectFlagHeld(void* p);
typedef s32 (*SlotFnRet)(void* self);
s32 TestPointAgainstObjectShape(void* obj, Vec02* p);
f32 ComputeAgentTargetBearing(void* self);
s32 IsPlayerUntargetableByAgent(void* self);

s32 IsConeAgentFree(ConeAgent* self)
{
    if (IsPadSelectFlagHeld(self->world) != 0) {
        return 0;
    }
    if (self->f724 == 0x10) {
        return 0;
    }
    if (self->f724 == 0xB) {
        return 0;
    }
    Collider* target = (Collider*)self->desc08()->m62(self);
    s32 inside;
    if (self->fC40 != 0 || target == 0) {
        inside = 1;
    } else if (IsObjectOfKind(target, 5) != 0 && ((SlotFnRet*)target->desc)[81](target) == 2) {
        inside = 1;
    } else if (self->fC1C != 0) {
        inside = TestPointAgainstObjectShape((void*)self->fC1C, &target->v140) == 0;
    } else if (__builtin_fabsf(target->v140.z - self->v190.z) > self->fC14) {
        inside = 1;
    } else {
        u128 d = Vu0::Sub(Vu0::Q(target->v140), Vu0::Q(self->v190));
        f32 len = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
        inside = self->fC10 < len;
    }
    if (inside != 0) {
        self->fC38 = 0;
        return 0;
    }
    if (self->fC38q != 0) {
        return 1;
    }
    if (self->fC34 == 0 || TestPointAgainstObjectShape((void*)self->fC34, &target->v140) == 0) {
        u128 d = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(target->v140));
        f32 len = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
        if (!(len < self->fC24)) {
            return 0;
        }
        f32 limit;
        if (len < self->fC20) {
            limit = self->fC2C;
        } else {
            f32 t = (len - self->fC20) / (self->fC24 - self->fC20);
            limit = t * self->fC28 + (1.0f - t) * self->fC2C;
        }
        if (!(__builtin_fabsf(ComputeAgentTargetBearing(self)) <= limit)) {
            return 0;
        }
    }
    if (IsPlayerUntargetableByAgent(self) != 0) {
        return 0;
    }
    self->fC38 = 1;
    return 1;
}
