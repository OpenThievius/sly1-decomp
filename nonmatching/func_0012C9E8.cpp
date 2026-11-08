// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 463/508 (91.1%), checked 2026-11-08
// Tried night-close3, 2 compiles: step computed after the call, t before bestT: no change or worse.
// Tried night-close8, 9 compiles: func_0012F210 declared (e, o, p, limit, big, t, a, b, c) and the sampler (obj, from, t, one, ...), as retail sets $f14 after a2 and a1 before $f12: 24 differing words down to 20. bestT and t declared first: no change.
// NEAR: registers only: the object (a1) and the entry from func_0012CCE8 are in s1 and s0, retail has s0 and s1, and the step and best-time floats are in f23 and f24, retail f24 and f23 (step computed straight into its register by max.s in retail).
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "list_iter.h"
#include "placed_object.h"
#include "state_trigger.h"
#include "timed_object.h"
#include "transform_object.h"
#include "state_walker.h"
#include "screen_element.h"
#include "masked_collider.h"
#include "world.h"
#include "animation.h"
#include "attachment.h"
#include "anim_curve.h"
#include "range_record.h"
#include "cursor_animator.h"
#include "sound_record.h"
#include "object_link.h"
#include "target_binding.h"
#include "globals.h"
#include "object_cycler.h"
#include "paired_object.h"
#include "code_checksum.h"
#include "switched_collider.h"
#include "shapes.h"
#include "id_filter_object.h"
#include "c8b.h"
#include "object_message.h"
#include "queued_call.h"
#include "stream_reader.h"
#include "key_id.h"
#include "game_progress.h"
#include "base_object.h"
#include "stream_reader_window.h"
#include "world.h"
#include "object_cycler.h"
#include "paired_object.h"


void func_0012C9E8(Animation* a, PlacedObject* b, f32 c, void* d, f32* e, s32 f, s32 g);
typedef void (*Fn_Table)();
void* FindEntryByObjectId(void);

struct PathSampler {
    void (*sample)(void* obj, void* from, f32 t, f32 one, s32 a, Vec02* out, s32 b);
};

struct PathEntry {
    u8 pad0[4];
    PathSampler** obj;      // 0x04: an object whose descriptor starts with a sampler
};

extern f32 D_00249B10[];
PathEntry* FindEntryByObjectId(void* self);
void func_0012F210(PathEntry* e, PlacedObject* o, Vec02* p, f32 limit, f32 big, f32 t, s32* a, Vec02* b, Vec02* c);

void func_0012C9E8(void* self, PlacedObject* o, Vec02* p, s32* a, Vec02* b, Vec02* c, f32 start)
{
    Vec02 sampled;
    f32 limit = *(f32*)((u8*)self + 0x34);
    f32 step = limit * 0.1f >? 0.5f;
    PathEntry* e = FindEntryByObjectId(self);
    if (e->obj == 0) {
        if (a != 0) {
            *a = 0;
        }
        if (b != 0) {
            *b = o->pos;
        }
        if (c != 0) {
            *c = D_00248D30;
        }
        return;
    }
    (*e->obj)->sample(e->obj, o, start, 1.0f, 0, &sampled, 0);
    f32 bestT = start;
    f32 t = 0.0f;
    u128 diff = Vu0::Sub(Vu0::Q(sampled), Vu0::Q(*p));
    f32 best = Vu0::ToFloat(Vu0::Dot(diff, diff));
    if (t < limit) {
        do {
            (*e->obj)->sample(e->obj, o, t, 1.0f, 0, &sampled, 0);
            u128 d2 = Vu0::Sub(Vu0::Q(sampled), Vu0::Q(*p));
            f32 dist = Vu0::ToFloat(Vu0::Dot(d2, d2));
            if (dist < best) {
                best = dist;
                bestT = t;
            }
            t = limit <? t + step;
        } while (t < limit);
    }
    func_0012F210(e, o, p, *(f32*)((u8*)self + 0x34), D_00249B10[0], bestT, a, b, c);
}
