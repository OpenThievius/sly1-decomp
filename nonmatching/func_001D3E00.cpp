// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 658/668 (98.5%), checked 2026-11-07
// NEAR: 3 lines differ: the order of `move a0`, `move a1` and `mov.s $f13` before the first
//       InterpolateBlendEntryPosition call (min.s via `<?` already sits right). ~30 compiles.
#include "common.h"
#include "switched_collider.h"
#include "c8b.h"
#include "shapes.h"

s32 FillOuterProductTable(s32 stride, s32 n, s32 m, char* out, ...);

u64 func_001FD868(f32 x);
s32 FindObjectAlongSegment(void* p, void* a, void* b, void* out);

struct BlendSpan { f32 t; u8 pad4[8]; f32 len; };
struct BlendSpans { u8 pad0[8]; BlendSpan* a; u8 padC[8]; BlendSpan* b; };

#define F(o, off) (*(f32*)((u8*)(o) + (off)))
#define W(o, off) (*(s32*)((u8*)(o) + (off)))

void InterpolateBlendEntryPosition(f32 a, f32 b, void* p, void* e, s32 i, s32 j, void* out);
void SetBlendItemWeights(Gr8B* obj, s32 a1, s32 a2, void* a3);
void SumBlendEntryVectors(s32 a0, void* a1, s32 a2, void* a3);

void func_001D3E00(TurningCollider* p, void* e, Gr8B* g, void* a3)
{
    f32 t;
    f32 lo;
    f32 hi;
    Vec02 va;
    Vec02 vb;
    Vec02 vd;
    Vec02 vc;
    if (W(e, 0x54) == 0) {
        t = 0.0f;
    } else {
        f32 zero = 0.0f;
        f32 one = 1.0f;
        f32 d0 = F(p, 0x640) - F(e, 0x10);
        f32 d1 = F(p, 0x640) - F(e, 0x60);
        f32 n = F(e, 0x34) * d0;
        t = n / (n - F(e, 0x84) * d1);
        if (t < zero) {
            t = zero;
        } else if (one < t) {
            t = one;
        }
    }
    if (W(e, 0xA4) == 0) {
        lo = 0.0f;
        hi = lo;
    } else {
        BlendSpans* sp = (BlendSpans*)g->pC0;
        f32 now = F(a3, 0x14);
        f32 x = sp->a->t - now;
        if (x <= 0.0f) {
            x += g->f34;
        }
        f32 q = x / sp->a->len;
        f32 y = sp->b->t - now;
        if (y <= 0.0f) {
            y += g->f34;
        }
        f32 r = y / sp->a->len;
        hi = q;
        lo = (r <? q);
        InterpolateBlendEntryPosition(lo, t, p, e, 2, 3, &va);
        InterpolateBlendEntryPosition(lo, t, p, e, 0, 1, &vb);
        if (FindObjectAlongSegment(p, &va, &vb, &vc)) {
            lo = 0.0f;
            hi = 1.0f - vc.x;
        } else if (W(e, 0x144) != 0) {
            InterpolateBlendEntryPosition(lo, t, p, e, 4, 5, &vd);
            if (FindObjectAlongSegment(p, &vb, &vd, &vc)) {
                lo = vc.x;
                hi = 0.0f;
            } else {
                lo = 1.0f;
                hi = 0.0f;
            }
        } else {
            lo = 0.0f;
            hi = lo;
        }
    }
    u64 hv = func_001FD868(hi);
    u64 lv = func_001FD868(lo);
    u64 tv = func_001FD868(t);
    if (FillOuterProductTable(0x50, 3, 2, (char*)e, hv, lv, tv)) {
        SetBlendItemWeights(g, 0x50, 6, e);
        SumBlendEntryVectors(6, e, (s32)g->pC0->p8, (u8*)p + 0x640);
    }
}
