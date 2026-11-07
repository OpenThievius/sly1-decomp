// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 436/420, checked 2026-11-07
// NEAR: the code matches except that GCC keeps the address of the loop's second vector (&nearest) in a callee-saved register across the walk, where retail forms it afresh at each use: one more saved register, so the frame is 16 bytes larger. Moving the declarations into the loop, putting the uses in other orders, and the order of the statements around the span query did not change it.
#include "common.h"
#include "list_iter.h"
#include "object_cycler.h"
#include "globals.h"
#include "vu0.h"

s32 TransformPointBetweenFrames(void* from, void* to, void* point, Vec02* out);
void PushBackMemoryMark(void);
typedef int Quadword128 __attribute__((mode(TI)));
typedef s32 (*ObjectFilterFn)(void* a, void* b);
void PopBackMemoryMark(void);
void GatherCollidersInSphere(s32 a0, s32 a1, void* a2, ObjectFilterFn a3, void* a4, s32* a5, s32* a6, f32 f12);
extern const f32 D_0024A218[2] = {3.4028235e+38f, 0.0f};
struct ListedFrameItem {
    u8 pad00[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x34 - 0x1C];
    BaseObject* item;       // 0x34
    ListedFrameItem* next;  // 0x38
};
typedef void (*ItemPointFn)(BaseObject* self, Vec02* in, s32 a, Vec02* out, s32 b, s32 c, s32 d);
s32 FindNearestSpanObject(s32 zero, void* p, void* q, s32 a, s32 b, ColliderSpan* out);

s32 func_0015BD48(ObjectCycler* self, Quadword128* out)
{
    ListFrame frame;
    Vec02 hit;
    f32 best = D_0024A218[0];
    for (ListedFrameItem* n = (ListedFrameItem*)self->world->list1C9C.head; n != 0; n = n->next) {
        Vec02 from;
        Vec02 nearest;
        TransformPointBetweenFrames(0, n->frame, &self->v140, &from);
        ItemPointFn fn = (ItemPointFn)((void**)n->item->desc)[10];
        if (fn != 0) {
            fn(n->item, &from, 0, &nearest, 0, 0, 0);
        }
        f32 d = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(from), Vu0::Q(nearest))));
        if (d < best) {
            best = d;
            TransformPointBetweenFrames(n->frame, 0, &nearest, &hit);
        }
    }
    if (best < D_0024A218[0]) {
        ColliderSpan span;
        Vec02 below;
        s32 count;
        s32 list;
        PushBackMemoryMark();
        GatherCollidersInSphere((s32)self->world, (s32)self, &hit, 0, 0, &count, &list, 500.0f);
        below = hit;
        below.z = below.z - 500.0f;
        s32 r = FindNearestSpanObject(0, &hit, &below, count, list, &span);
        PopBackMemoryMark();
        if (r != 0) {
            *out = *(Quadword128*)&span;
            return 1;
        }
        return 0;
    }
    return 0;
}
