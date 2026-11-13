// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x14B550 to 0x14B6A8 (its .bss from 0x27C008): class 0x10's register, unregister
// and copy, class 0x11's first two methods (InitNumberedAgent and StartNumberedAgent, which share
// the running count D_0027C008) and SetSinCosPair. Its start is not proved by retail, only by the
// change of role from the symmetric solve (symmetric_solve.cpp). Its end is gauge_manager.cpp's
// .rodata start, the one edge here retail proves in the data; but any function start from
// 0x14A7B8 to 0x14B6A8 links to the same bytes (gauge_manager.cpp says why), so these functions
// could as well open gauge_manager.cpp, which holds the rest of class 0x11: D_0027C008 can be
// either file's .bss, since a file of words aligns its .bss to 4. Its name is ours, by its main
// role: five of its six functions put an agent of class 0x10 on the world's list or give one of
// class 0x11 its number; SetSinCosPair is the odd one out.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_notifier.h"
#include "world.h"
#include "camera.h"
#include "game_progress.h"
#include "effect.h"
#include "screen_element.h"
#include "font.h"
#include "gauge_manager.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "object_link.h"
#include "scatter_controller.h"
#include "shapes.h"
#include "object_pool.h"
#include "owner_message.h"
#include "vu0.h"
#include "scope_marker.h"
#include "mul_rotation.h"
#include "pad_record.h"
#include "ramp_profile.h"

void RegisterAgent(void* self);
void AppendToList(void* table, void* self);

// What SetSinCosPair fills: the two results of ComputeSinCos and a word it clears.
struct SinCosPair { f32 a; f32 b; s32 value; };

void ComputeSinCos(void* a, void* b, f32 value);
void UnregisterAgent(void*);
void RemoveFromList(void*, void*);
void CopyAgent(void*, void*);
void InitAgent(void*);
void StartAgent(void*);
void RemoveFromList(void* a, void* b);

void AppendToList(void*,void*);


// The file's statics (.bss from 0x27C008).
static s32 D_0027C008;  // a running count, reset by func_0014B608

void RegisterWorldListedAgent(WorldListedAgent* self)
{
    RegisterAgent(self);
    AppendToList(&self->world->list1CCC, self);
}

void UnregisterWorldListedAgent(WorldListedAgent* self) { UnregisterAgent(self); RemoveFromList(&self->world->list1CCC, self); }

void CopyWorldListedAgent(WorldListedAgent* self, void* other) { Pack10 save=self->fC10; CopyAgent(self,other); self->fC10=save; }

void InitNumberedAgent(NumberedAgent* self) { InitAgent(self); self->fC24=1; D_0027C008=0; }

void StartNumberedAgent(NumberedAgent* self) { StartAgent(self); self->fC2C=D_0027C008++; }

void SetSinCosPair(f32 value, SinCosPair* self)
{
    ComputeSinCos(&self->b, self, value);
    self->value = 0;
}
