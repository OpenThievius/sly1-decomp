// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 396/388, checked 2026-11-07
// NEAR: right structure and the loop; retail stores the squared distance with sw straight from the qmfc2 register (an integer word) where ToFloat's f32 result goes through mtc1/swc1 (or, via a union, one extra move); also the record pointer q lives in $a1 in retail, $a2 here. The word would need a Vu0 helper that returns the qmfc2 result as an integer.
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
extern const f32 D_00249E90[4];

// A candidate func_00148938 sorts: its squared distance from the point of view, and the object.
struct Candidate_00148938 {
    union {
        f32 dist;
        s32 bits;
    };
    StateNotifier* obj;
};

s32 CountListItems(List01* list);
s32 SortElements(void* base, s32 count, s32 size, void* cmp);

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
                c->dist = D_00249E90[0];
            } else {
                u128 d = Vu0::Sub(Vu0::Q(origin), Vu0::Q(p->v140));
                union {
                    f32 f;
                    s32 i;
                } u;
                u.f = Vu0::ToFloat(Vu0::Dot(d, d));
                c->bits = u.i;
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

