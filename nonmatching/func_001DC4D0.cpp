// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 552/576 (95.8%), checked 2026-11-08
// NEAR: the size of the allocation read before the walk's frame is built (this brings the push of the frame into the call's delay slot, as retail's): still differs: skip and the result cursor in s1/s2 the other way round (retail gives the object to skip s1 and the cursor s2), and the count pointer spilled at sp+0x20 (retail: sp+0x24, so a 4-byte slot at +0x20 is taken in retail). Tried: no goto, the cursor declared before the walk.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "list_iter.h"
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


// A list walk's frame (as ListFrame) that pushes itself and pops itself when it goes.
struct SphereWalker {
    List01* list;
    s32* cur;
    s32 step;
    SphereWalker* prev;
    SphereWalker(List01* l)
    {
        list = l;
        cur = (s32*)&l->head;
        step = l->offset;
        prev = (SphereWalker*)g_activeListFrames;
        g_activeListFrames = (ListFrame*)this;
    }
    ~SphereWalker() { g_activeListFrames = (ListFrame*)prev; }
    s32 Next()
    {
        s32 n = *cur;
        cur = (s32*)(n + step);
        return n;
    }
};
void* AllocateBackMemory(s32 size);

void func_001DC4D0(World* world, Collider* skip, f32 radius, Vec02* center, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out)
{
    s32 size = *(s32*)((u8*)world + 0x34) * 4;
    SphereWalker walk((List01*)((u8*)world + 0x6C));
    Collider** cursor = (Collider**)AllocateBackMemory(size);
    *out = cursor;
    if (skip != 0 && ((skip->flags538 & 0x80000000000ull) != 0 || (skip->root03()->flags538 & 0x40000000000ull) != 0)) {
        goto done;
    }
    {
        Collider* c;
        while ((c = (Collider*)walk.Next()) != 0) {
            if (c == skip) {
                continue;
            }
            Vec02 d;
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*center), Vu0::Q(c->v140));
            f32 dist = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(d)));
            f32 reach = radius + c->radius3D0;
            if (reach * reach < dist) {
                continue;
            }
            if (c->root03()->flags538 & 0x40000000000ull) {
                continue;
            }
            if (skip != 0) {
                if (skip->desc03()->m38(skip, c) != 0) {
                    continue;
                }
                if (c->desc03()->m38(c, skip) != 0) {
                    continue;
                }
            }
            Collider* part = (Collider*)c->parts.head;
            while (part != 0) {
                if (filter != 0) {
                    if (filter(arg, part) != 0) {
                        *cursor++ = part;
                    }
                } else if ((part->flags538 & 0x80000000000ull) == 0) {
                    *cursor++ = part;
                }
                part = (Collider*)part->link2E4.next;
            }
        }
    }
done:
    *count = cursor - *out;
}
