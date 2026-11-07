// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "collider.h"

struct __attribute__((aligned(16))) Quad_1429F8 { s32 a, b, c, d; };

// A span a collider query writes: entry and exit points (q[0..1]), their normals (q[2..3]),
// the two times and a kind.
struct Span_1429F8 {
    Quad_1429F8 q[4];
    f32 time[2];
    s32 f48;
    u8 pad0[0x70 - 0x4C];
};


s32 func_00141C28(Collider* self, void* a1, void* a2, s32 a3, s32 a4);
s32 func_001429F8(s32 count, Span_1429F8* spans);
s32 func_0013DFD8(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
s32 func_00141F48(void* a, void* b, void* c, s32 d, s32 e, f32 x);
s32 func_00142B78(void* a, void* b, void* c, void* d, s32 e, s32 f, f32 x);
s32 func_00142170(void* a, void* b, void* c, void* d, s32 e, f32 fa, f32 fb);

Collider* func_001419E8(s32 flags, void* a1, void* a2, s32 count, Collider** list, Span_1429F8* out)
{
    f32 bestKey = 3.4028235e+38f;
    Collider* best = 0;
    Span_1429F8 buf[2];
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


s32 func_00141B48(void* a0, void* a1, s32 count, Collider** list, s32 a4, s32 a5)
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
                        r = MergeOverlappingSpans(result + r, (Span_1429F8*)a5);
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

s32 func_00141C28(Collider* self, void* a1, void* a2, s32 a3, s32 a4)
{
    if (self->tree.nodes != 0) {
        return func_0013DFD8((void*)self->tree.nodes, a1, a2, 0, a3, (void*)a4);
    }
    if (self->flags538 & ((u64)0x8000 << 25)) {
        return func_00141F48((u8*)self + 0x140, a1, a2, a3, a4, self->radius3CC);
    }
    return 0;
}

s32 func_00141C90(Collider* self, void* a1, void* a2, void* a3, s32 a4, void* a5)
{
    if (a1 != 0) {
        return func_0013DFD8(a1, a2, a3, 0, a4, a5);
    }
    if (self->flags538 & ((u64)0x8000 << 25)) {
        return func_00141F48((u8*)self + 0x140, a2, a3, a4, (s32)a5, self->radius3CC);
    }
    return 0;
}

s32 func_00141D00(Collider* self, void* p1, void* p2, f32 x, void* p3, s32 p4)
{
    if (self->tree.nodes != 0) {
        return func_00142B78((u8*)self + 0x3F0, (u8*)self + 0x3A4, p1, p2, (s32)p3, p4, x);
    }
    if (self->flags538 & ((u64)0x8000 << 25)) {
        return func_00142170((u8*)self + 0x140, p1, p2, p3, p4, self->radius3CC, x);
    }
    return 0;
}

ASM_FUNC(func_00141D88);

ASM_FUNC(func_00141F48);

ASM_FUNC(func_00142170);

ASM_FUNC(func_00142278);

LINKER_REMNANT(func_00142990);

struct Key_142998 { f32 f; s32 i; };

s32 func_00142998(Key_142998* a, Key_142998* b)
{
    f32 d = a->f - b->f;
    if (d < -0.0001f)
        return -1;
    if (0.0001f < d)
        return 1;
    return a->i - b->i;
}

struct Event_1429F8 {
    f32 time;
    s32 end;
    u8 pad0[8];
    Quad_1429F8 q10;
    Quad_1429F8 q20;
};

void func_0018D608(void);
Event_1429F8* func_0018D658(s32 size);
void func_0018D6F0(void);
void func_001F5CD0(Event_1429F8* base, s32 n, s32 size, s32 (*cmp)(Key_142998*, Key_142998*));

s32 func_001429F8(s32 count, Span_1429F8* spans)
{
    Event_1429F8* mem;
    Event_1429F8* rec;
    Event_1429F8* end;
    Span_1429F8* dst;
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

    func_001F5CD0(mem, count * 2, 0x30, CompareSpanEndpoints);

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

ASM_FUNC(func_00142B78);

LINKER_REMNANT(func_00142EC8);

// The file's .rodata ends with a second FLT_MAX that no code loads: the constant of a function
// the linker stripped (one of the two above), kept here as the value it is.
extern const f32 D_00249E48 = 3.4028235e+38f;
