// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1068/1080, checked 2026-11-10
// NEAR (2026-11-08, worker night-large2): the chain walk, the fill of the slots past the
// chain, the pose calls and the accumulation are retail's instructions; the frame is 0x30
// bigger. Retail's rotated vectors (0x130, 0x140, 0x150, and the spin's at 0x130 again) share
// their space with MulRotation's matrix local (0x130) and its rows (0x160): here the matrix
// local takes a new 0x30 at 0x160 because the three Vec02 locals (TImode slots) are not
// joined for a BLKmode request, and every stack offset after it moves. Tried: Vu0::Slot and
// Vec4U for them, the accumulation as one inline function with the product (N first: the
// vectors land at 0x130, the matrix still at 0x160), a helper storing each rotated vector to
// a slot of its own (the matrix then lands at 0x130, but the three vectors share one slot).
// The Vec form keeps the chain index unreduced, as retail (u128 values reduce it).
// In the context of its file, src/main/placed_object.cpp.
#include "common.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "placed_object.h"
#include "attachment.h"
#include "c8b.h"
#include "globals.h"

void* FindEntryByObjectId(Gr8B* self, void* key);

// A source of an object's pose (Entry8B's mover and sub): its first method gives the pose at a
// time and scale, a vector and a second value (func_0012CD78).
typedef void (*PoseAtFn8B)(void* src, PlacedObject* o, f32 t, f32 scale, s32 z, void* a, Vec02* b);

void func_0012CD78(Gr8B* self, PlacedObject* o, PlacedObject* top, s32 n, Vec02* pos, Mat02* rot, Vec02* vel,
                   Vec02* spin, f32 t, f32 scale)
{
    typedef Vu0::Vec Vec;
    PlacedObject* chain[16];
    Vec02 P;
    Vec02 V;
    Vec02 W;
    Mat02 M;
    Vec02 p;
    Vec02 v;
    Vec02 w;
    Mat02 R;
    Mat02 N;
    f32 s = scale * (self->f7C * self->f98);
    s32 k = 0;
    while (o != top) {
        if (o->f224 == 0 || (o->f224->fB0 & 0xC) == 0) {
            chain[k++] = o;
        }
        o = (PlacedObject*)o->parent;
    }
    P = D_00248D30;
    M = g_identityMatrix;
    V = D_00248D30;
    W = D_00248D30;
    while (k < n) {
        n--;
        if (pos != 0) {
            pos[n] = P;
        }
        if (rot != 0) {
            rot[n] = M;
        }
        if (vel != 0) {
            vel[n] = V;
        }
        if (spin != 0) {
            spin[n] = W;
        }
    }
    for (s32 i = k - 1; i >= 0; i--) {
        PlacedObject* c = chain[i];
        Entry8B* e = (Entry8B*)FindEntryByObjectId(self, c);
        void* a = 0;
        void* b = 0;
        if (e != 0) {
            b = e->sub;
            a = e->mover;
        }
        if (pos != 0 || vel != 0) {
            if (a != 0) {
                (*(PoseAtFn8B*)*(void**)a)(a, c, t, s, 0, &p, &v);
            } else {
                p = c->pos;
                v = c->v150;
            }
        }
        if (b != 0) {
            (*(PoseAtFn8B*)*(void**)b)(b, c, t, s, 0, &R, &w);
        } else {
            R = c->rot;
            w = c->v160;
        }
        if (pos != 0 || vel != 0) {
            Vec02 d;
            Vu0::Q(d) = Vu0::RotateUntied(M, Vec::Of(p)).q;
            Vu0::Q(P) = Vu0::Add(Vec::Of(P), Vec::Of(d)).q;
            if (vel != 0) {
                Vec02 f;
                Vec02 g;
                Vu0::Q(f) = Vu0::Rotate(M, Vec::Of(v)).q;
                Vu0::Q(V) = Vu0::Add(Vec::Of(V), Vec::Of(f)).q;
                Vu0::Q(g) = Vu0::Cross(Vec::Of(W), Vec::Of(d)).q;
                Vu0::Q(V) = Vu0::Add(Vec::Of(V), Vec::Of(g)).q;
            }
        }
        if (spin != 0 || vel != 0) {
            Vec02 d;
            Vu0::Q(d) = Vu0::Rotate(M, Vec::Of(w)).q;
            Vu0::Q(W) = Vu0::Add(Vec::Of(W), Vec::Of(d)).q;
        }
        MulRotation(&N, M, R);
        M = N;
        if (i < n) {
            if (pos != 0) {
                pos[i] = P;
            }
            if (rot != 0) {
                rot[i] = M;
            }
            if (vel != 0) {
                vel[i] = V;
            }
            if (spin != 0) {
                spin[i] = W;
            }
        }
    }
}
