// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "collider.h"
#include "shapes.h"
#include "fpu.h"
#include "globals.h"
#include "functions/collider_contact.h"
#include "functions/collider_span.h"
#include "functions/warp_menu.h"
#include "functions/zone_collider.h"

// Types other files define, named by the parameters of their functions declared here.
struct SpanQuery;
struct SpanSet;


Collider* FindNearestSpanObject(s32 flags, Vec02* a1, Vec02* a2, s32 count, Collider** list, ColliderSpan* out)
{
    f32 bestKey = 3.4028235e+38f;
    Collider* best = 0;
    ColliderSpan buf[2];
    for (s32 i = 0; i < count; i++) {
        Collider* obj = list[i];
        s32 n = CollectColliderSpans(obj, a1, a2, 2, buf);
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


s32 CollectSpansFromList(void* a0, void* a1, s32 count, Collider** list, s32 a4, ColliderSpan* a5)
{
    s32 result = 0;
    if (count > 0) {
        const u64 mask = 0xC000ULL << 28;
        Collider** p = list;
        s32 n = count;
        do {
            Collider* e = *p;
            if ((e->flags538 & mask) == 0) {
                s32 r = CollectColliderSpans(e, (Vec02*)a0, (Vec02*)a1, a4 - result, a5 + result);
                if (r != 0) {
                    if (result != 0) {
                        r = MergeOverlappingSpans(result + r, a5);
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

s32 CollectColliderSpans(Collider* self, Vec02* a1, Vec02* a2, s32 a3, ColliderSpan* a4)
{
    if (self->tree.nodes != 0) {
        return CollectTreeNodeSpans((TreeNode03*)self->tree.nodes, (Vec02*)a1, (Vec02*)a2, 0, a3, (ColliderSpan*)a4);
    }
    if (self->flags538 & ((u64)0x8000 << 25)) {
        return CollectBoundsSpans((Vec02*)((u8*)self + 0x140), a1, a2, self->radius3CC, a3, a4);
    }
    return 0;
}

s32 CollectColliderSpansInTree(Collider* self, void* a1, void* a2, void* a3, s32 a4, ColliderSpan* a5)
{
    if (a1 != 0) {
        return CollectTreeNodeSpans((TreeNode03*)a1, (Vec02*)a2, (Vec02*)a3, 0, a4, (ColliderSpan*)a5);
    }
    if (self->flags538 & ((u64)0x8000 << 25)) {
        return CollectBoundsSpans((Vec02*)((u8*)self + 0x140), (Vec02*)a2, (Vec02*)a3, self->radius3CC, a4, a5);
    }
    return 0;
}

s32 TestColliderSegmentHit(Collider* self, void* p1, void* p2, f32 x, s32 p3, ColliderSpan* p4)
{
    if (self->tree.nodes != 0) {
        return TestTreeSegmentHit((SpanQuery*)((u8*)self + 0x3F0), (SpanSet*)((u8*)self + 0x3A4), (Vec02*)p1, (Vec02*)p2, p3, p4, x);
    }
    if (self->flags538 & ((u64)0x8000 << 25)) {
        return TestBoundsSegmentHit((u8*)self + 0x140, p1, p2, p3, p4, self->radius3CC, x);
    }
    return 0;
}

// The spans where the segment a-b is inside the sphere of the given radius around p (the roots
// of a quadratic in the position along the segment): the points, their directions from p and
// the times, into out.
s32 FindSegmentSphereSpan(Vec02* p, Vec02* a, Vec02* b, f32 radius, s32 count, ColliderSpan* out)
{
    if (count <= 0) {
        return 0;
    }
    Vec02 ab;
    Vec02 pa;
    f32 roots[2];
    Vu0::Q(ab) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    Vu0::Q(pa) = Vu0::Sub(Vu0::Q(*a), Vu0::Q(*p));
    f32 c = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(pa), Vu0::Q(pa))) - radius * radius;
    f32 hb = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ab), Vu0::Q(pa)));
    f32 ha = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ab), Vu0::Q(ab)));
    f32 twoB = hb + hb;
    f32 disc = twoB * twoB - ha * (c * 4.0f);
    if (disc < 0.0001f) {
        return 0;
    }
    disc = Fpu::Sqrt(disc);
    f32 twoA = ha + ha;
    roots[0] = (-twoB - disc) / twoA;
    roots[1] = (-twoB + disc) / twoA;
    for (s32 j = 0; j < 2; j++) {
        f32 t = roots[j];
        out->time[j] = t;
        Vu0::Q(out->q[j]) = Vu0::MulXSum(Vu0::Q(*b), Vu0::Scalar(t), Vu0::Q(*a), Vu0::Scalar(1.0f - t));
        Vu0::Vec d = Vu0::Sub(Vu0::Vec::Of(out->q[j]), Vu0::Vec::Of(*p));
        *(Vu0::Vec*)&out->q[j + 2] = d;
        *(Vu0::Vec*)&out->q[j + 2] = Vu0::NormalizeOr(d, Vu0::Vec::Of(g_unitXVector));
    }
    out->f48 = 1;
    return 1;
}

// The spans where the segment a-b, cut to its ends, is inside the sphere of the given radius around p (the roots
// of a quadratic in the position along the segment): the points, their directions from p and
// the times, into out.
// The cut roots: the constant in the first register of max.s and min.s, the result in its register.
static inline f32 MaxF(f32 a, f32 b) { return a >? b; }
static inline f32 MinF(f32 a, f32 b) { return b <? a; }
s32 CollectBoundsSpans(Vec02* p, Vec02* a, Vec02* b, f32 radius, s32 count, ColliderSpan* out)
{
    if (count <= 0) {
        return 0;
    }
    Vec02 ab;
    Vec02 pa;
    f32 roots[2];
    Vu0::Q(ab) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    Vu0::Q(pa) = Vu0::Sub(Vu0::Q(*a), Vu0::Q(*p));
    f32 c = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(pa), Vu0::Q(pa))) - radius * radius;
    f32 hb = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ab), Vu0::Q(pa)));
    f32 ha = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ab), Vu0::Q(ab)));
    f32 twoB = hb + hb;
    f32 disc = twoB * twoB - ha * (c * 4.0f);
    if (disc < 0.0001f) {
        return 0;
    }
    disc = Fpu::Sqrt(disc);
    f32 twoA = ha + ha;
    f32 r0 = (-twoB - disc) / twoA;
    f32 r1 = (-twoB + disc) / twoA;
    roots[0] = r0;
    roots[1] = r1;
    if (r0 < 0.0f && r1 < 0.0f) {
        return 0;
    }
    if (1.0f < r0 && 1.0f < r1) {
        return 0;
    }
    roots[0] = MaxF(0.0f, roots[0]);
    roots[1] = MinF(roots[1], 1.0f);
    for (s32 j = 0; j < 2; j++) {
        f32 t = roots[j];
        out->time[j] = t;
        Vu0::Q(out->q[j]) = Vu0::MulXSum(Vu0::Q(*b), Vu0::Scalar(t), Vu0::Q(*a), Vu0::Scalar(1.0f - t));
        Vu0::Vec d = Vu0::Sub(Vu0::Vec::Of(out->q[j]), Vu0::Vec::Of(*p));
        *(Vu0::Vec*)&out->q[j + 2] = d;
        *(Vu0::Vec*)&out->q[j + 2] = Vu0::NormalizeOr(d, Vu0::Vec::Of(g_unitXVector));
    }
    out->f48 = 1;
    return 1;
}


// Whether the segment a-b, moved toward p's bounds by the offset from its nearest point to p
// (at most fb long), hits them (CollectBoundsSpans).
s32 TestBoundsSegmentHit(void* p, void* a, void* b, s32 d, ColliderSpan* e, f32 fa, f32 fb)
{
    Vec02 nearest;
    Vec02 off;
    Vec02 a2;
    Vec02 b2;
    f32 t;
    f32 dist;
    MeasurePointToSegment((Vec02*)p, (Vec02*)a, (Vec02*)b, &t, &dist);
    Vu0::Q(nearest) = Vu0::MulXSum(Vu0::Q(*(Vec02*)a), Vu0::Scalar(1.0f - t), Vu0::Q(*(Vec02*)b), Vu0::Scalar(t));
    Vu0::Q(off) = Vu0::Sub(Vu0::Q(*(Vec02*)p), Vu0::Q(nearest));
    ClampVectorLength(&off, &off, fb);
    Vu0::Q(a2) = Vu0::Add(Vu0::Q(*(Vec02*)a), Vu0::Q(off));
    Vu0::Q(b2) = Vu0::Add(Vu0::Q(*(Vec02*)b), Vu0::Q(off));
    return CollectBoundsSpans((Vec02*)p, &a2, &b2, fa, d, e);
}

f32 SplitVectorAlongAxis(const Vec02* v, const Vec02* axis, Vec02* along, Vec02* rest);

static inline u128 NormalizeOfCopy(u128 v, u128 vc, u128 fallback)
{
    u128 len = Vu0::Length(vc);
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        return fallback;
    }
    return Vu0::DivX(v, len);
}

s32 IntersectSegmentWithCapsule(Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32 radius, s32 count, ColliderSpan* out)
{
    Vec02 cd;
    Vec02 ab;
    Vec02 ca;
    Vec02 n;
    Vec02 x;
    Vec02 m;
    Vec02 dir;
    f32 s;
    f32 u;
    if (count == 0)
        return 0;
    Vu0::Q(cd) = Vu0::Sub(Vu0::Q(*d), Vu0::Q(*c));
    Vu0::Q(ab) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    Vu0::Q(ca) = Vu0::Sub(Vu0::Q(*a), Vu0::Q(*c));
    Vu0::Q(n) = Vu0::Cross(Vu0::Q(cd), Vu0::Q(ab));
    f32 nn = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(n), Vu0::Q(n)));
    if (!(nn < 0.0001f)) {
        Vu0::Q(x) = Vu0::Cross(Vu0::Q(ca), Vu0::Q(ab));
        s = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(x), Vu0::Q(n))) / nn;
        Vu0::Q(x) = Vu0::Cross(Vu0::Q(ca), Vu0::Q(cd));
        f32 side = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ca), Vu0::Q(n)));
        u = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(x), Vu0::Q(n))) / nn;
        if (side < 0.0f)
            Vu0::Q(n) = Vu0::MulX(Vu0::Q(n), Vu0::Scalar(-1.0f));
    }
    Vu0::Set(n, Vu0::NormalizeOr(Vu0::Q(n), Vu0::Q(g_unitZVector)));
    f32 h = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ca), Vu0::Q(n)));
    if (radius < h)
        return 0;
    {
        u128 p = Vu0::Cross(Vu0::Q(n), Vu0::Q(ab));
        u128 pc = Vu0::Copy(p);
        Vu0::Q(m) = pc;
        Vu0::Set(m, NormalizeOfCopy(p, pc, Vu0::Q(g_unitYVector)));
    }
    f32 w = Fpu::Sqrt(radius * radius - h * h) / Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(cd), Vu0::Q(m)));
    f32 k = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(cd), Vu0::Q(ab)));
    f32 kk = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ab), Vu0::Q(ab)));
    out->time[0] = s - w;
    out->time[1] = s + w;
    w = w * k;
    w = w / kk;
    out->param[0] = u - w;
    out->param[1] = u + w;
    if (out->param[1] < out->param[0]) {
        f32 tmp = out->time[0];
        out->time[0] = out->time[1];
        out->time[1] = tmp;
        tmp = out->param[0];
        out->param[0] = out->param[1];
        out->param[1] = tmp;
    }
    if (out->param[1] < 0.0f)
        return 0;
    if (1.0f < out->param[0])
        return 0;
    if (0.0001f < out->param[1] - out->param[0]) {
        f32 f = out->param[0] / (out->param[0] - out->param[1]);
        if (0.0f < f && f < 1.0f) {
            out->param[0] = (1.0f - f) * out->param[0] + f * out->param[1];
            out->time[0] = (1.0f - f) * out->time[0] + f * out->time[1];
        }
        f = (out->param[0] - 1.0f) / (out->param[0] - out->param[1]);
        if (0.0f < f && f < 1.0f) {
            out->param[1] = (1.0f - f) * out->param[0] + f * out->param[1];
            out->time[1] = (1.0f - f) * out->time[0] + f * out->time[1];
        }
    }
    if (out->time[0] > out->time[1]) {
        f32 a1 = out->time[1];
        f32 a0 = out->time[0];
        f32 b0 = out->param[0];
        f32 b1 = out->param[1];
        out->time[0] = a1;
        out->time[1] = a0;
        out->param[0] = b1;
        out->param[1] = b0;
    }
    if (out->time[1] < 0.0f)
        return 0;
    if (1.0f < out->time[0])
        return 0;
    if (0.0001f < out->time[1] - out->time[0]) {
        f32 f = out->time[0] / (out->time[0] - out->time[1]);
        if (0.0f < f && f < 1.0f) {
            out->time[0] = (1.0f - f) * out->time[0] + f * out->time[1];
            out->param[0] = (1.0f - f) * out->param[0] + f * out->param[1];
        }
        f = (out->time[0] - 1.0f) / (out->time[0] - out->time[1]);
        if (0.0f < f && f < 1.0f) {
            out->time[1] = (1.0f - f) * out->time[0] + f * out->time[1];
            out->param[1] = (1.0f - f) * out->param[0] + f * out->param[1];
        }
    }
    Vu0::Q(dir) = Vu0::Q(ab);
    Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Q(dir), Vu0::Q(g_unitXVector)));
    for (s32 i = 0; i < 2; i++) {
        f32 ti = out->time[i];
        Vu0::Q(out->q[i]) = Vu0::MulXSum(Vu0::Vec::Of(*c), Vu0::Vec::Scalar(1.0f - ti), Vu0::Vec::Of(*d), Vu0::Vec::Scalar(ti)).q;
        if (out->param[0] == 0.0f) {
            Vu0::Q(out->q[i + 2]) = Vu0::MulX(Vu0::Vec::Of(dir), Vu0::Vec::Scalar(-1.0f)).q;
        } else if (out->param[0] == 1.0f) {
            *(Vec02*)&out->q[i + 2] = dir;
        } else {
            Vu0::Q(ca) = Vu0::Sub(Vu0::Vec::Of(out->q[i]), Vu0::Vec::Of(*a)).q;
            SplitVectorAlongAxis(&ca, &dir, 0, (Vec02*)&out->q[i + 2]);
            Vu0::Q(out->q[i + 2]) = Vu0::NormalizeOr(Vu0::Vec::Of(out->q[i + 2]), Vu0::Vec::Of(g_unitZVector)).q;
        }
    }
    out->f48 = 2;
    return 1;
}

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
void SortElements(void* base, u32 n, u32 size, s32 (*compare)(const void* x, const void* y));

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

    SortElements(mem, count * 2, 0x30, (s32 (*)(const void*, const void*))CompareSpanEndpoints);

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
struct PlaneTreeNode;
struct PlaneTreeOutput;
extern "C" void* FillMemory(void* p, s32 value, s32 size);

s32 TestTreeSegmentHit(SpanQuery* query, SpanSet* set, Vec02* p, Vec02* q, s32 max, ColliderSpan* out, f32 radius)
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
    end = (SpanRecord*)AllocateBackMemory(query->count * 12);
    recs = end;
    f32 halfLen = len * h;
    s32 kind = QueryPlaneTreePoint((PlaneTreeNode*)query->tree, &mid, halfLen + radius, (PlaneTreeOutput*)&end);
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
        total = CollectTreeNodeSpans((TreeNode03*)((void*)(end - 1)), p, q, 0, max, out);
        for (i = 0; i < n; i++) {
            recs[i].obj->flags |= 0x100;
        }
        for (i = 0; i < n; i++) {
            SpanObject* o = recs[i].obj;
            if ((o->flags & 0x200) == 0) {
                o->flags |= 0x200;
                for (SpanLink* l = o->links; l != 0; l = l->next) {
                    SpanOther* other = &set->others[l->other];
                    if ((other->flags & 0x100) != 0) {
                        ColliderSpan* seg = out + total;
                        s32 got = IntersectSegmentWithCapsule(p, q, (Vec02*)(set->verts + l->vertA * 16), (Vec02*)(set->verts + l->vertB * 16), radius, max - total, seg);
                        if (got > 0) {
                            ColliderSpan* sp = seg;
                            ColliderSpan* segEnd = sp + got;
                            for (; sp < segEnd; sp++) {
                                f32 a = sp->param[0];
                                f32 b = sp->param[1];
                                sp->time[0] = a;
                                sp->time[1] = b;
                                if (b < a) {
                                    sp->time[0] = b;
                                    sp->time[1] = a;
                                }
                            }
                            total = MergeOverlappingSpans(total + got, out);
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

LINKER_REMNANT(func_00142EC8);

// The file's .rodata ends with a second FLT_MAX that no code loads: the constant of a function
// the linker stripped (one of the two above), kept here as the value it is.
extern const f32 D_00249E48 = 3.4028235e+38f;
