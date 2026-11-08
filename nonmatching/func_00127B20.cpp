// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 824/828, checked 2026-11-07
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "list_iter.h"
#include "placed_object.h"
#include "state_trigger.h"
#include "timed_object.h"
#include "transform_object.h"
#include "state_walker.h"
#include "screen_element.h"
#include "masked_collider.h"
#include "world.h"
#include "animation.h"
#include "attachment.h"
#include "anim_curve.h"
#include "range_record.h"
#include "cursor_animator.h"
#include "sound_record.h"
#include "object_link.h"
#include "target_binding.h"
#include "globals.h"
#include "object_cycler.h"
#include "paired_object.h"
#include "code_checksum.h"
#include "switched_collider.h"
#include "shapes.h"
#include "id_filter_object.h"
#include "c8b.h"
#include "object_message.h"
#include "queued_call.h"
#include "stream_reader.h"
#include "key_id.h"
#include "game_progress.h"
#include "base_object.h"
#include "stream_reader_window.h"
#include "world.h"
#include "object_cycler.h"
#include "paired_object.h"
// NEAR (2026-11-08, wave 4): 92.8% of the instructions: the frame (480), the chain walk, the fill loop, the rotations and the dead stores are retail's. Left: the chain's object is kept in v1 where retail has a0 (and the vector registers differ with it), retail reads the rows of the object's own rotation through v0 = o + 0xD0 (addiu v0, a0, 0xD0 once) and stores the product's rows to the matrix before the copy at 0xA0 and z, where here they come after, and the (i < n) test goes to v1 (v0 here). The product is written out with the function's x, y, z (the same slots serve the position block's temporaries) and a local r; MulRotationRows gives them slots of its own (frame 528).
void IgnoreStackLocal(Vec02* p);

void func_00127B20(PlacedObject* self, PlacedObject* top, s32 n, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin, f32 t)
{
    PlacedObject* chain[16];
    Vec02 P;
    Vec02 V;
    Vec02 W;
    Mat02 M;
    Mat02 N;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Mat02 r;
    s32 i = 0;
    while (self != top) {
        chain[i] = self;
        i++;
        Rec2195_224* rec = self->f224;
        if (rec != 0 && (rec->fB0 & 0xC)) {
            self = (PlacedObject*)rec->p60;
        } else {
            self = (PlacedObject*)self->parent;
        }
    }
    P = D_00248D30;
    M = g_identityMatrix;
    V = D_00248D30;
    W = D_00248D30;
    while (i < n) {
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
    for (i--; i >= 0; i--) {
        PlacedObject* o = chain[i];
        if (pos != 0 || vel != 0) {
            Vu0::Q(x) = Vu0::Rotate(M, Vu0::Q(o->pos));
            Vu0::Q(P) = Vu0::Add(Vu0::Q(P), Vu0::Q(x));
            if (vel != 0) {
                Vu0::Q(y) = Vu0::Rotate(M, Vu0::Q(o->v150));
                Vu0::Q(z) = Vu0::Cross(Vu0::Q(W), Vu0::Q(x));
                Vu0::Q(V) = Vu0::Add(Vu0::Q(V), Vu0::Q(y));
                Vu0::Q(V) = Vu0::Add(Vu0::Q(V), Vu0::Q(z));
            }
        }
        if (spin != 0 || vel != 0) {
            Vu0::Q(x) = Vu0::Rotate(M, Vu0::Q(o->v160));
            Vu0::Q(W) = Vu0::Add(Vu0::Q(W), Vu0::Q(x));
        }
        const Mat02& q = o->rot;
        u128 a0 = Vu0::Q(M.r[0]);
        u128 a1 = Vu0::Q(M.r[1]);
        u128 a2 = Vu0::Q(M.r[2]);
        Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(q.r[0]));
        r.r[0] = x;
        Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(q.r[1]));
        r.r[1] = y;
        Vu0::Q(z) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(q.r[2]));
        r.r[2] = z;
        M = r;
        N = M;
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
        IgnoreStackLocal(&P);
    }
}

