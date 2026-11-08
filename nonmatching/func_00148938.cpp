// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 353/388 (91.0%), checked 2026-11-08
// NIGHT-DECLS (2026-11-08): SortElements declared void as defined (func_001F5CD0): 351 -> 353 bytes. Still differs as above.
// Tried night-close8, 8 compiles: q advanced first and the record written through q[-1]: 11 differing words down to 6. Retail sets the record pointer with move v1,a1 then addiu a1,v1,8 and stores the object and the far distance at -4(a1) and -8(a1) but the squared distance at 0(v1); here loop.c makes q a giv biased by -0x8000 (addiu a1,s2,-32768, stores at 32764(v1), 32760(v1), 32760(a1)). StoreX for the distance, c kept for some stores, n++ in each arm: further.
// NEAR: the record pointer: addiu a1,s2,-32768 for move a1,s2 before the loop and the three stores at offsets biased by 0x8000; the rest is retail's.
#include "common.h"
#include "state_notifier.h"
#include "world.h"
#include "switched_collider.h"
#include "camera.h"
#include "vu0.h"
extern u8 g_camera[];
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 bytes);
s32 CompareFloatsDescending(const f32* first, const f32* second);
SwitchedCollider* GetActiveSwitchedCollider(void);

// A candidate func_00148938 sorts: its squared distance from the point of view, and the object.
struct Candidate_00148938 {
    union {
        f32 dist;
        u32 bits;
    };
    StateNotifier* obj;
};

s32 CountListItems(List01* list);
void SortElements(void* base, s32 count, s32 size, void* cmp);

s32 func_00148938(World* self, s32 kind, s32 max, StateNotifier** out)
{
    Vec02 origin;
    Candidate_00148938* recs;
    Candidate_00148938* q;
    s32 n;
    if (max == 0) {
        return 0;
    }
    PushBackMemoryMark();
    SwitchedCollider* viewer = GetActiveSwitchedCollider();
    Vec02* src;
    if (viewer != 0) {
        src = &viewer->v140;
    } else {
        src = (Vec02*)(*(u8**)g_camera + 0x40);
    }
    origin = *src;
    n = 0;
    recs = (Candidate_00148938*)AllocateBackMemory(CountListItems(&self->list1C54) * 8);
    q = recs;
    for (StateNotifier* p = (StateNotifier*)self->list1C54.head; p != 0; p = p->next374) {
        if (p->f338 != 0 && ((Desc01*)p->desc)->id == kind) {
            q++;
            q[-1].obj = p;
            n++;
            if (p->state == 2) {
                q[-1].dist = 3.4028234663852886e+38f;
            } else {
                u128 d = Vu0::Sub(Vu0::Q(origin), Vu0::Q(p->v140));
                q[-1].bits = Vu0::ToBits(Vu0::Dot(d, d));
            }
        }
    }
    SortElements(recs, n, 8, (void*)CompareFloatsDescending);
    if (n < max) {
        max = n;
    }
    for (s32 i = 0; i < max; i++) {
        out[i] = recs[i].obj;
    }
    PopBackMemoryMark();
    return max;
}
