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
#include "object_finder.h"


void DrawAgent(Agent* self, void* arg1, void* arg2);

struct GatheredEventObject { u8 pad0[0x328]; s32 f328; };
struct GatheredObjects { s32 count; GatheredEventObject** items; };

void StartAgent(Agent* self);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherAnimationEventObjects(Animation* self, BaseObject* ctx, s32* outCount, BaseObject*** outArr);
void* CreateRecord2505C0(void);
struct StateResetObject;
struct StateResetGroup;
void AppendToSmallList(StateResetGroup* self, StateResetObject* value);

void InitAgent(Agent* self);
void InitConeAgent(ConeAgent* self);




void* IsObjectOfKind(BaseObject* list, s32 key);


void InitConeAgent(ConeAgent* self)
{
    InitAgent(self);
    self->nearRange = 1000.0f;
    self->farRange = 1500.0f;
    self->farAngle = 0.78539816f;
    self->nearAngle = 3.14159265f;
    self->leashDistance = 2000.0f;
    self->sightZoneId = -1;
    self->leashHeight = 300.0f;
    self->zoneId = -1;
    self->targetRangeMax = 300.0f;
    self->targetRangeMin = 0;
    self->targetAngleLimit = 1.04719755f;
}

void StartConeAgent(ConeAgent* self)
{
    GatheredObjects out;
    s32 i;

    StartAgent(self);
    if (self->zoneId != -1) {
        self->fC1C = (ObjectGatherer*)FindFirstObjectByIdMode4(self->world, self->zoneId, self);
    }
    if (self->sightZoneId != -1) {
        self->sightZone = (ObjectGatherer*)FindFirstObjectByIdMode4(self->world, self->sightZoneId, self);
    }
    if (self->mainClip != 0) {
        PushBackMemoryMark();
        GatherAnimationEventObjects((Animation*)self->mainClip, self, &out.count, (BaseObject***)&out.items);
        for (i = 0; i < out.count; i++) {
            GatheredEventObject* e = out.items[i];
            if (e->f328 == 0) {
                void* t = CreateRecord2505C0();
                e->f328 = (s32)t;
                AppendToSmallList((StateResetGroup*)t, (StateResetObject*)e);
            }
        }
        PopBackMemoryMark();
    }
}

void DrawConeAgent(ConeAgent* self, void* arg1, void* arg2)
{
    DrawAgent(self, arg1, arg2);
}

s32 IsPadSelectFlagHeld(World* self);
typedef s32 (*SlotFnRet)(void* self);
struct ObjectGatherer;
s32 TestPointAgainstObjectShape(ObjectGatherer* self, void* value);
f32 ComputeAgentTargetBearing(Agent* self);
s32 IsPlayerUntargetableByAgent(Agent* self);

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
    if (self->disabled != 0 || target == 0) {
        inside = 1;
    } else if (IsObjectOfKind(target, 5) != 0 && ((SlotFnRet*)target->desc)[81](target) == 2) {
        inside = 1;
    } else if (self->fC1C != 0) {
        inside = TestPointAgainstObjectShape(self->fC1C, &target->v140) == 0;
    } else if (__builtin_fabsf(target->v140.z - self->v190.z) > self->leashHeight) {
        inside = 1;
    } else {
        u128 d = Vu0::Sub(Vu0::Q(target->v140), Vu0::Q(self->v190));
        f32 len = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
        inside = self->leashDistance < len;
    }
    if (inside != 0) {
        self->engaged = 0;
        return 0;
    }
    if (self->engagedQuad != 0) {
        return 1;
    }
    if (self->sightZone == 0 || TestPointAgainstObjectShape(self->sightZone, &target->v140) == 0) {
        u128 d = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(target->v140));
        f32 len = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
        if (!(len < self->farRange)) {
            return 0;
        }
        f32 limit;
        if (len < self->nearRange) {
            limit = self->nearAngle;
        } else {
            f32 t = (len - self->nearRange) / (self->farRange - self->nearRange);
            limit = t * self->farAngle + (1.0f - t) * self->nearAngle;
        }
        if (!(__builtin_fabsf(ComputeAgentTargetBearing(self)) <= limit)) {
            return 0;
        }
    }
    if (IsPlayerUntargetableByAgent(self) != 0) {
        return 0;
    }
    self->engaged = 1;
    return 1;
}
