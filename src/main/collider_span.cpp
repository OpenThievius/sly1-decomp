// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "collider.h"
#include "shapes.h"

s32 CollectColliderSpans(Collider* self, void* a1, void* a2, s32 a3, s32 a4);
s32 MergeOverlappingSpans(s32 count, ColliderSpan* spans);
s32 CollectTreeNodeSpans(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
s32 CollectBoundsSpans(void* a, void* b, void* c, s32 d, s32 e, f32 x);
s32 TestTreeSegmentHit(void* a, void* b, void* c, void* d, s32 e, s32 f, f32 x);
s32 TestBoundsSegmentHit(void* a, void* b, void* c, void* d, s32 e, f32 fa, f32 fb);

Collider* FindNearestSpanObject(s32 flags, void* a1, void* a2, s32 count, Collider** list, ColliderSpan* out)
{
    f32 bestKey = 3.4028235e+38f;
    Collider* best = 0;
    ColliderSpan buf[2];
    for (s32 i = 0; i < count; i++) {
        Collider* obj = list[i];
        s32 n = CollectColliderSpans(obj, a1, a2, 2, (s32)buf);
        s32 idx = 0;
        if (n > 0 && buf[0].time[0] == 0.0f) {
            if (flags & 1) idx = 1;
        }
        if (idx < n && buf[idx].time[0] < bestKey) {
            bestKey = buf[idx].time[0];
            best = obj;
            if (out != 0) {
                *out = buf[idx];
            }
        }
    }
    return best;
}


s32 CollectSpansFromList(void* a0, void* a1, s32 count, Collider** list, s32 a4, s32 a5)
{
    s32 result = 0;
    if (count > 0) {
        const u64 mask = 0xC000ULL << 28;
        Collider** p = list;
        s32 n = count;
        do {
            Collider* e = *p;
            if ((e->flags538 & mask) == 0) {
                s32 r = CollectColliderSpans(e, a0, a1, a4 - result, a5 + result * 0x70);
                if (r != 0) {
                    if (result != 0) {
                        r = MergeOverlappingSpans(result + r, (ColliderSpan*)a5);
                    }
                    result = r;
                }
            }
            n--;
            p++;
        } while (n != 0);
    }
    return result;
}

s32 CollectColliderSpans(Collider* self, void* a1, void* a2, s32 a3, s32 a4)
{
    if (self->tree.nodes != 0) {
        return CollectTreeNodeSpans((void*)self->tree.nodes, a1, a2, 0, a3, (void*)a4);
    }
    if (self->flags538 & ((u64)0x8000 << 25)) {
        return CollectBoundsSpans((u8*)self + 0x140, a1, a2, a3, a4, self->radius3CC);
    }
    return 0;
}

s32 CollectColliderSpansInTree(Collider* self, void* a1, void* a2, void* a3, s32 a4, void* a5)
{
    if (a1 != 0) {
        return CollectTreeNodeSpans(a1, a2, a3, 0, a4, a5);
    }
    if (self->flags538 & ((u64)0x8000 << 25)) {
        return CollectBoundsSpans((u8*)self + 0x140, a2, a3, a4, (s32)a5, self->radius3CC);
    }
    return 0;
}

s32 TestColliderSegmentHit(Collider* self, void* p1, void* p2, f32 x, void* p3, s32 p4)
{
    if (self->tree.nodes != 0) {
        return TestTreeSegmentHit((u8*)self + 0x3F0, (u8*)self + 0x3A4, p1, p2, (s32)p3, p4, x);
    }
    if (self->flags538 & ((u64)0x8000 << 25)) {
        return TestBoundsSegmentHit((u8*)self + 0x140, p1, p2, p3, p4, self->radius3CC, x);
    }
    return 0;
}

INCLUDE_ASM(func_00141D88);

INCLUDE_ASM(func_00141F48);

INCLUDE_ASM(func_00142170);

INCLUDE_ASM(func_00142278);

LINKER_REMNANT(func_00142990);

struct SpanEvent {
    f32 time;
    s32 end;
    u8 pad0[8];
    Quad16 q10;
    Quad16 q20;
};

s32 CompareSpanEndpoints(SpanEvent* a, SpanEvent* b)
{
    f32 d = a->time - b->time;
    if (d < -0.0001f)
        return -1;
    if (0.0001f < d)
        return 1;
    return a->end - b->end;
}

void PushBackMemoryMark(void);
SpanEvent* AllocateBackMemory(s32 size);
void PopBackMemoryMark(void);
void SortElements(SpanEvent* base, s32 n, s32 size, s32 (*cmp)(SpanEvent*, SpanEvent*));

s32 MergeOverlappingSpans(s32 count, ColliderSpan* spans)
{
    SpanEvent* mem;
    SpanEvent* rec;
    SpanEvent* end;
    ColliderSpan* dst;
    s32 i;
    s32 j;
    s32 depth;

    PushBackMemoryMark();
    mem = AllocateBackMemory(count * 0x60);
    rec = mem;
    for (i = 0; i < count; i++) {
        for (j = 0; j < 2; j++) {
            rec->end = j;
            rec->time = spans[i].time[j];
            rec->q10 = spans[i].q[j];
            rec->q20 = spans[i].q[j + 2];
            rec++;
        }
    }

    SortElements(mem, count * 2, 0x30, CompareSpanEndpoints);

    dst = spans;
    end = rec;
    rec = mem;
    depth = 0;
    while (rec < end) {
        if (rec->end == 0) {
            depth++;
            if (depth == 1) {
                dst->time[0] = rec->time;
                dst->q[0] = rec->q10;
                dst->q[2] = rec->q20;
                dst->f48 = 4;
            }
        } else {
            depth--;
            if (depth == 0) {
                dst->time[1] = rec->time;
                dst->q[1] = rec->q10;
                dst->q[3] = rec->q20;
                dst++;
            }
        }
        rec++;
    }

    PopBackMemoryMark();
    return dst - spans;
}

INCLUDE_ASM(func_00142B78);

LINKER_REMNANT(func_00142EC8);

// The file's .rodata ends with a second FLT_MAX that no code loads: the constant of a function
// the linker stripped (one of the two above), kept here as the value it is.
extern const f32 D_00249E48 = 3.4028235e+38f;
