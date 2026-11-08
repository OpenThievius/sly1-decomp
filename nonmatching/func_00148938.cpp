// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 353/388 (91.0%), checked 2026-11-08
// NIGHT-DECLS (2026-11-08): SortElements declared void as defined (func_001F5CD0): 351 -> 353 bytes. Still differs as above.
// NEAR: the squared distance is now stored as retail does (Vu0::ToBits: qmfc2, then sw). Still differs in the loop's set-up and record pointer: retail fills the delay slot of the list-head test with move s2,v0 (here move a1,s2), and advances q first (addiu a1,v1,8), storing the object and the far distance at -4(a1) and -8(a1), with n++ in the delay slot of the state test; here the stores use the old pointer and q advances late. c = q; q = c + 1, n++ first, q->obj before c, writing through q and advancing it last, and the state test inverted: no closer.
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
            Candidate_00148938* c = q++;
            c->obj = p;
            n++;
            if (p->state == 2) {
                c->dist = 3.4028234663852886e+38f;
            } else {
                u128 d = Vu0::Sub(Vu0::Q(origin), Vu0::Q(p->v140));
                c->bits = Vu0::ToBits(Vu0::Dot(d, d));
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
