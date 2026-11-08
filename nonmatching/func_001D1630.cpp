// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1088/1100, checked 2026-11-08
// NEAR (2026-11-08, worker night-large1): the player's frame on its path at a length: the path's
// start direction, then lengths stepped out on both sides until the direction there turns less
// than 0.9 away from it, the shortest-arc rotation of the path's offset, and the frame built
// from the first direction and that offset (turned about when 0x221C is set). Retail's code but
// in the search loop: there the direction is normalised with the fallback in the branch (the
// form a store straight to memory gives) and kept in a register for the copy to the first
// direction, while this C's u128 makes the fallback-first form; storing it straight to memory
// instead keeps its address in a saved register. The tail's VU0 registers differ in turn
// (tools/regdiff.py: code, 95.6%).
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "game_clock.h"
#include "globals.h"
#include "vu0.h"

extern float D_00274F14;
extern float D_00274F20[2];

// The path object (+0x2208): a frame at +0x18, a holder at +0x34 whose descriptor has the
// methods the player calls (slots 1, 2, 8 and 10), and an offset at +0x40 (func_001D1630).
struct PathHolder;
struct PathHolderDesc {
    u8 pad00[4];
    void (*m1)(PathHolder* self, Vec02* pos, f32 t, Vec02* tangent);  // 0x04
    void (*m2)(PathHolder* self, Vec02* out, f32 t, s32 a);           // 0x08
    u8 pad0C[0x20 - 0x0C];
    f32 (*m8)(PathHolder* self);                                      // 0x20: the length
    u8 pad24[0x28 - 0x24];
    void (*m10)(PathHolder* self, Vec02* in, s32 a, s32 b, s32 c, s32 d, f32* out);
};
struct PathHolder {
    PathHolderDesc* desc;
    u8 pad04[4];
    s32 closed;             // 0x08: set, a length wraps around the path (func_001D1630)
    u8 pad0C[4];
    f32* start;             // 0x10: the length the path starts at (func_001D1630)
    f32* first;             // 0x14: the smallest length it takes (func_001D1630)
};
struct PathObject { const Desc01* desc; u8 pad04[0x14]; void* frame; u8 pad1C[0x34 - 0x1C]; PathHolder* holder; u8 pad38[0x40 - 0x38]; Vec02 v40; };

f32 WrapModulo(f32 x, f32 y);
void BuildShortestArcRotation(const Vec02* from, const Vec02* to, Mat02* out);
void TransformDirectionBetweenFrames(void* from, void* to, Vec02* dir, Vec02* out);

void func_001D1630(Player* self, PathObject* path, Mat02* out, f32 length)
{
    Vec02 start;
    Vec02 first;
    Vec02 dir;
    Vec02 ahead;
    PathHolder* h = path->holder;
    f32 total = h->desc->m8(h);
    if (h->desc->m1 != 0) {
        h->desc->m1(h, 0, *h->start, &start);
    }
    Vu0::Q(start) = Vu0::NormalizeOr(Vu0::Q(start), Vu0::Q(g_unitXVector));
    s32 i = 0;
    for (;; i++) {
        f32 step;
        if (i & 1) {
            step = (f32)(i + 1) * D_00274F20[0];
        } else {
            step = (f32)i * -D_00274F20[0];
        }
        f32 at = length + step;
        if (h->closed == 0) {
            if (at < *h->first) {
                continue;
            }
            if (total < length) {
                continue;
            }
        } else {
            at = WrapModulo(at, total);
        }
        Vec02 behind;
        if (h->desc->m2 != 0) {
            h->desc->m2(h, &ahead, at + D_00274F14, 0);
            if (h->desc->m2 != 0) {
                h->desc->m2(h, &behind, at - D_00274F14, 0);
            }
        }
        u128 d = Vu0::NormalizeOr(Vu0::Sub(Vu0::Q(ahead), Vu0::Q(behind)), Vu0::Q(g_unitZVector));
        Vu0::Q(dir) = d;
        if (i == 0) {
            Vu0::Q(first) = d;
        }
        if (-0.9f < Vu0::ToFloat(Vu0::Dot(Vu0::Q(start), Vu0::Q(dir)))) {
            break;
        }
    }
    Mat02 arc;
    BuildShortestArcRotation(&start, &dir, &arc);
    Vu0::Q(ahead) = Vu0::Rotate(arc, Vu0::Q(path->v40));
    TransformDirectionBetweenFrames(path->frame, 0, &first, &first);
    TransformDirectionBetweenFrames(path->frame, 0, &ahead, &ahead);
    Mat02 m;
    u128 z = Vu0::NormalizeOr(Vu0::Q(first), Vu0::Q(g_unitZVector));
    Vu0::Q(m.r[2]) = z;
    u128 y = Vu0::NormalizeOr(Vu0::Cross(z, Vu0::Q(ahead)), Vu0::Q(g_unitYVector));
    Vu0::Q(m.r[0]) = Vu0::Cross(y, Vu0::Q(m.r[2]));
    Vu0::Q(m.r[1]) = y;
    if (self->f221C != 0) {
        u128 k = Vu0::Scalar(-1.0f);
        Vu0::Q(m.r[2]) = Vu0::MulX(Vu0::Q(m.r[2]), k);
        Vu0::Q(m.r[1]) = Vu0::MulX(Vu0::Q(m.r[1]), k);
    }
    if (out != 0) {
        *out = m;
    }
}
