// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 574/576 (99.7%), checked 2026-11-09
// NEAR (2026-11-08, w5-1DC4D0): every instruction and register is retail's; only the count pointer's spill slot differs (sp+0x20 here, retail sp+0x24). What got here: one `*cursor++ = part` (the filter's two outcomes as continues in a for): two stores counted twice in the inner loop's weighted refs and put the cursor's priority (1.039) above the skipped object's (0.472), so global-alloc gave the cursor s1; with one store the object goes first, as in retail; and `cursor = *out = Allocate...`, which stores the call's value from v0. The slot: reload gives an unallocated pseudo its slot after every declared local, so retail has an object of at most 4 bytes declared after d that nothing reads. An empty class with an empty destructor declared before the parts loop gives EXACT (a class with a destructor is addressable, so it keeps a 1-byte, 16-aligned slot at 0x20 and the spill moves to 0x24), and GatherCollidersInBox (func_001DC238) has the same small object at 0x30 (its frame ends at 0x34, rounded to 0x40); not landed, because no type the original plausibly declared there is known (an invented empty type is a padding local). Tried: an empty object without a destructor, with a constructor only, or with a method that ignores this (no slot); a u8[3] or a destructor object at function scope (a 16-byte slot); docs/TOOLCHAIN.md, "An object with a destructor keeps a slot". w8 (2026-11-09): re-scored, unchanged; the object may sit anywhere after d (before the parts loop or after `done:` both EXACT), and an inline frame (16-byte BLKmode), a reload slot whose accesses were inherited (only parameters precede the count pseudo, all allocated), a dropped ADDRESSOF (purge runs after CSE), the m38 calls (func_00138F28 makes them with no slot) and a `const f32&` temporary are ruled out: only a class with a non-trivial destructor whose ctor and dtor emit nothing remains, its type unknown.
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
    Collider** cursor = *out = (Collider**)AllocateBackMemory(size);
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
            for (Collider* part = (Collider*)c->parts.head; part != 0; part = (Collider*)part->link2E4.next) {
                if (filter != 0) {
                    if (filter(arg, part) == 0) {
                        continue;
                    }
                } else if ((part->flags538 & 0x80000000000ull) != 0) {
                    continue;
                }
                *cursor++ = part;
            }
        }
    }
done:
    *count = cursor - *out;
}
