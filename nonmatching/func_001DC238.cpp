// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 626/660 (94.8%), checked 2026-11-08
// Tried night-close3, 2 compiles: the allocation size read before the frame (which helped func_001DC4D0) or before the list setup: no change.
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "vu0.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "child_group_object.h"
#include "screen_element.h"
#include "object_link.h"
#include "object_message.h"
#include "owner_message.h"
#include "output_buffer.h"
#include "shapes.h"
#include "globals.h"
#include "world.h"
#include "queued_call.h"
#include "effect.h"
#include "game_progress.h"
#include "buffered_stream.h"
#include "value_range.h"
#include "script_value.h"
#include "cone_volume.h"
#include "redirect_object.h"
#include "font.h"
#include "level_entry.h"
#include "message_body.h"
#include "path_curve_object.h"
#include "state_notifier.h"
// NEAR (2026-11-07, worker vu0-c): the same instructions in retail's order but for the saved
// registers and the frame's set-up. Retail keeps the excluded object in s1, a in s2, b in s0 and
// the output in s3 (here s2, s0, s3, s1), loads b before a for the Min and Max, and stores the
// walk's list and link before loading its offset and the previous frame; here the four loads
// come first. The unused ListFrame of the parts walk gives retail's 0xE0 frame.

void* AllocateBackMemory(s32 size);

// The next object of a list walk (ListFrame), its link moved on past it.
static inline Collider* NextListedCollider(ListFrame* it)
{
    Collider* c = *(Collider**)it->link;
    it->link = (u8*)c + it->offset;
    return c;
}

// Starts a walk of a list: the frame's list, link and offset, pushed on the active frames.
static inline void StartListWalk(ListFrame* it, ActorList6C* l)
{
    it->list = l;
    it->link = (u8*)l;
    it->offset = l->offset;
    it->prev = g_activeListFrames;
    g_activeListFrames = it;
}

void func_001DC238(World* self, Collider* exclude, Vec02* a, Vec02* b, s32 (*filter)(void*, Collider*), void* arg, s32* n, Collider*** out)
{
    ListFrame frame;
    Vec02 lo;
    Vec02 hi;
    StartListWalk(&frame, &self->list6C);
    *out = (Collider**)AllocateBackMemory(self->count34 * 4);
    Collider** p = *out;
    if (exclude == 0 || (!(exclude->flags538 & (1ULL << 43)) && !(((Collider*)exclude->root)->flags538 & (1ULL << 42)))) {
        Vu0::Q(lo) = Vu0::Min(Vu0::Q(*a), Vu0::Q(*b));
        Vu0::Q(hi) = Vu0::Max(Vu0::Q(*a), Vu0::Q(*b));
        Collider* c;
        while ((c = NextListedCollider(&frame)) != 0) {
            if (c != exclude && !(c->boundsMin.x > hi.x) && !(c->boundsMax.x < lo.x) && !(c->boundsMin.y > hi.y) &&
                !(c->boundsMax.y < lo.y) && !(c->boundsMin.z > hi.z) && !(c->boundsMax.z < lo.z) &&
                !(((Collider*)c->root)->flags538 & (1ULL << 42)) &&
                (exclude == 0 || (!exclude->desc03()->m38(exclude, c) && !c->desc03()->m38(c, exclude)))) {
                ListFrame partWalk;
                for (c = (Collider*)c->parts.head; c != 0; c = (Collider*)c->link2E4.next) {
                    if (filter != 0) {
                        if (filter(arg, c)) {
                            *p++ = c;
                        }
                    } else if (!(c->flags538 & (1ULL << 43))) {
                        *p++ = c;
                    }
                }
            }
        }
    }
    *n = p - *out;
    g_activeListFrames = frame.prev;
}
