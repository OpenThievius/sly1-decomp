// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 801/828 (96.7%), checked 2026-11-08
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
// NEAR (2026-11-08, night-sizex1): 18 lines from retail. The rotation's rows of the chain's object read by index through a pointer (const u128* q = &o->rot; q[i]) give retail's addiu v0, a0, 0xD0 and its loads; the last row's two stores chained (z = r.r[2] = ...) and N = r before M = r give retail's store order. Still differs: the chain's object is kept in v0 where retail has a0 (q then takes v0), which moves the VU0 registers of the first rotation (retail: o->pos vf2, M's rows vf6, vf5, vf3). Tried: no local for the object (840 bytes), q formed at the top of the body.
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
        const u128* q = (const u128*)&o->rot;
        u128 a0 = Vu0::Q(M.r[0]);
        u128 a1 = Vu0::Q(M.r[1]);
        u128 a2 = Vu0::Q(M.r[2]);
        Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, q[0]);
        r.r[0] = x;
        Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, q[1]);
        r.r[1] = y;
        Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, q[2]);
        N = r;
        M = r;
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

