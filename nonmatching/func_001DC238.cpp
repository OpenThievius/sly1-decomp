// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 595/660 (90.2%), checked 2026-11-07
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

void func_001DC238(World* self, Collider* exclude, Vec02* a, Vec02* b, s32 (*filter)(void*, Collider*), void* arg, s32* n, Collider*** out)
{
    ListFrame frame;
    Vec02 lo;
    Vec02 hi;
    ActorList6C* l = &self->list6C;
    frame.list = l;
    frame.link = (u8*)l;
    frame.offset = l->offset;
    frame.prev = g_activeListFrames;
    g_activeListFrames = &frame;
    Collider** p = (Collider**)AllocateBackMemory(self->count34 * 4);
    *out = p;
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
