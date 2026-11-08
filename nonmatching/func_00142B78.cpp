// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 787/844 (93.2%), checked 2026-11-07
// NEAR: wave 4 e3. 844 bytes, same size; instruction order only (regdiff: order, 206 of 211 words equal by opcode): the link pointer of the inner loop and the
//       copy of the segment pointer take s0 and s1 in the other order (retail: link in s0, which held the first parameter; segment in s1), and the
//       scheduler orders a few loads/qmtc2 of the opening and of case 0's two quadword copies differently. The kind switch needs a case 2 sharing the
//       default to give retail's compare tree; the mark/unmark loops, the record loops and the span fix-up are retail's. ~16 compiles.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "collider.h"
#include "shapes.h"

s32 CollectTreeNodeSpans(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
s32 MergeOverlappingSpans(s32 count, ColliderSpan* spans);
void* AllocateBackMemory(s32 size);
struct SpanRecord {
    struct SpanObject* obj;
    u8 pad04[8];
};
struct SpanLink {
    s16 vertA;
    s16 vertB;
    u8 pad04[2];
    s16 other;
    SpanLink* next;
};
struct SpanObject {
    u8 pad00[0x14];
    SpanLink* links;
    u8 pad18[4];
    u16 flags;
};
struct SpanOther {
    u8 pad00[0x1C];
    u16 flags;
    u8 pad1E[2];
};
struct SpanSet {
    u8 pad00[8];
    u8* verts;
    u8 padC[4];
    SpanOther* others;
};
struct SpanQuery {
    u8 pad00[4];
    s32 count;
    void* tree;
};
s32 func_0013E430(void* tree, Vec02* centre, SpanRecord** end, f32 r);
s32 func_00142278(Vec02* p, Vec02* q, u8* a, u8* b, f32 r, s32 max, ColliderSpan* out);
void FillMemory(void* dst, s32 v, s32 n);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);

s32 func_00142B78(SpanQuery* query, SpanSet* set, Vec02* p, Vec02* q, s32 max, ColliderSpan* out, f32 radius)
{
    Vec02 mid;
    SpanRecord* end;
    SpanRecord* recs;
    s32 total;
    s32 n;
    s32 i;
    if (max == 0) {
        return 0;
    }
    PushBackMemoryMark();
    f32 h = 0.5f;
    u128 half = Vu0::Scalar(h);
    Vu0::Q(mid) = Vu0::MulXSum(Vu0::Q(*p), half, Vu0::Q(*q), half);
    f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(*p), Vu0::Q(*q))));
    recs = (SpanRecord*)AllocateBackMemory(query->count * 12);
    f32 halfLen = len * h;
    end = recs;
    s32 kind = func_0013E430(query->tree, &mid, &end, halfLen + radius);
    switch (kind) {
    case 1:
        total = 0;
        break;
    case 0:
        FillMemory(out, 0, 0x70);
        total = 1;
        *(Vec02*)&out->q[0] = *p;
        *(Vec02*)&out->q[1] = *q;
        out->time[1] = 1.0f;
        break;
    case 2:
    default:
        n = end - recs;
        total = CollectTreeNodeSpans((void*)(end - 1), p, q, 0, max, out);
        for (i = 0; i < n; i++) {
            recs[i].obj->flags |= 0x100;
        }
        for (i = 0; i < n; i++) {
            SpanObject* o = recs[i].obj;
            if ((o->flags & 0x200) == 0) {
                o->flags |= 0x200;
                for (SpanLink* l = o->links; l != 0; l = l->next) {
                    if ((set->others[l->other].flags & 0x100) != 0) {
                        ColliderSpan* seg = out + total;
                        s32 got = func_00142278(p, q, set->verts + l->vertA * 16, set->verts + l->vertB * 16, radius, max - total, seg);
                        if (got > 0) {
                            s32 newTotal = total + got;
                            ColliderSpan* segEnd = seg + got;
                            for (ColliderSpan* sp = seg; sp < segEnd; sp++) {
                                f32 a = *(f32*)((u8*)sp + 0x50);
                                f32 b = *(f32*)((u8*)sp + 0x54);
                                sp->time[0] = a;
                                sp->time[1] = b;
                                if (b < a) {
                                    sp->time[0] = b;
                                    sp->time[1] = a;
                                }
                            }
                            total = MergeOverlappingSpans(newTotal, out);
                        }
                    }
                }
            }
        }
        for (i = 0; i < n; i++) {
            recs[i].obj->flags &= 0xFCFF;
        }
        break;
    }
    PopBackMemoryMark();
    return total;
}
