// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 516/660 (78.2%), checked 2026-11-09
// NEAR (night-low1, 2026-11-08): the body read into a local before v0.z's store (retail loads it
//       before the subtraction) and the unit-Z vector read after the probe radius's store (retail
//       loads it after that swc1, where rec->f08's store keeps it) take 65 differing lines to 49.
//       Still differs: the third call's argument moves (retail t0, t1, f12, f13, then a2), the
//       weights' slot stores (retail after the first length, the weights in vf6 and vf3, here
//       stored at once in vf3 and vf5), and the radius sum in f12 (here f0). Tried: v0.z by byte
//       offset (same), the lengths' order, the weights inline or after the radius (worse).
// Before: wave 4 e3. 660 bytes, same size; every instruction is there and the VU0 sequences match; the order of the
//       scheduling differs: the two weight stores and qmtc2s of the unit-Z steps come early (retail: after the first length),
//       the load of the body before the second call and the delay slot of the second jal (retail fills it with a0, ours a1).
//       The selected node, the four calls and the probe record's writes are retail's. ~12 compiles (scalar order, float
//       parameters between the pointers, node selection forms).
#include "common.h"
#include "globals.h"
#include "switched_collider.h"
#include "node_query.h"
#include "gauge_mode_object.h"
#include "countdown_collider.h"
#include "entry_queue.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "base_object.h"
#include "placed_object.h"
#include "world.h"
#include "font.h"
#include "level_entry.h"
#include "threshold_range.h"
#include "scatter_controller.h"
#include "render_frame.h"
#include "background_job.h"
#include "vu0.h"
#include "group_marker.h"
#include "game_progress.h"
#include "bump_allocator.h"
#include "camera.h"
#include "path_curve_object.h"
#include "asm_func.h"
#include "vu0.h"

extern f32 D_00263880;
extern f32 D_00263884;
struct ProbeRecord { void* f00; s32 f04; f32 f08; u8 pad0C[4]; Vec02 v10; Vec02 v20; Vec02 v30; Vec02 v40; };
struct ProbeNode { u8 pad00[8]; void* f08; };
struct ProbeNodeBase { u8 pad00[0x100]; Vec02 v100; };
struct ProbeBody { u8 pad00[0x60]; Vec02 v60; Vec02 v70; void* f80; ProbeNodeBase* f84; };
struct ProbeHolder { u8 pad00[0x224]; ProbeBody* body; };
void* FindAnimationMarkerEvent(void* node, s32 kind);
void func_0012CD78(void* node, void* a, f32 x, f32 y, void* self, s32 one, Vec02* out, Vec02* out2, s32 z0, s32 z1);
s32 CollectBoundsSpans(Vec02* out, Vec02* lo, Vec02* hi, s32 one, ColliderSpan* span);
void func_001719E8(void* self, s32 a, s32 b, void* part, f32 k, void* d)
{
    Player* pl = (Player*)self;
    ProbeHolder* obj = (ProbeHolder*)b;
    ProbeRecord* rec = (ProbeRecord*)d;
    ProbeNode* node;
    if (pl->f2220 == 0) {
        if (pl->f223C < 10) {
            if (pl->f223C < 6) {
                node = *(ProbeNode**)((u8*)pl->f2234 + 0x24);
            } else {
                node = *(ProbeNode**)((u8*)pl + 0x2244);
            }
        } else {
            node = *(ProbeNode**)((u8*)pl->f2234 + 0x24);
        }
    } else if (pl->f2234 != 0) {
        node = *(ProbeNode**)((u8*)pl->f2234 + 0x24);
    } else {
        node = (ProbeNode*)pl->watched2230;
    }
    if (node->f08 == rec->f00) {
        return;
    }
    rec->f00 = node->f08;
    f32 x = 0.0f;
    f32* found = (f32*)FindAnimationMarkerEvent(node->f08, 0x142);
    if (found != 0) {
        x = *found;
    }
    f32 y = 0.0f;
    Vec02 v0;
    Vec02 v10;
    Vec02 v20;
    Mat02 m30;
    Vec02 v60;
    Vec02 v70;
    ColliderSpan span;
    func_0012CD78(node->f08, (void*)a, x, y, pl, 1, &v0, 0, 0, 0);
    ProbeBody* b1 = obj->body;
    v0.z = v0.z - k;
    func_0012CD78(node->f08, b1->f80, x, y, pl, 1, &v10, 0, 0, 0);
    func_0012CD78(node->f08, obj, x, y, pl, 1, &v20, (Vec02*)&m30, 0, 0);
    u128 w = Vu0::Add(Vu0::Q(v20), Vu0::Rotate(m30, Vu0::Q(obj->body->v60)));
    Vu0::Q(v20) = w;
    Vu0::Q(rec->v20) = Vu0::Add(Vu0::Q(v10), Vu0::Sub(Vu0::Q(v0), w));
    u128 s80 = Vu0::ScalarAt(D_00263880);
    u128 s84 = Vu0::ScalarAt(D_00263884);
    ProbeBody* body = obj->body;
    rec->f08 = Vu0::ToFloat(Vu0::Length(Vu0::Q(body->v70))) + Vu0::ToFloat(Vu0::Length(Vu0::Q(body->f84->v100))) + 10.0f;
    u128 up = Vu0::Q(g_unitZVector);
    Vu0::Q(v70) = Vu0::MulAddX(Vu0::Q(v0), up, s84);
    Vu0::Q(v60) = Vu0::MulAddX(Vu0::Q(v0), up, s80);
    rec->f04 = 0 < CollectBoundsSpans(&rec->v20, &v60, &v70, 1, &span);
    rec->v10 = v0;
    rec->v30 = *(Vec02*)&span.q[0];
    rec->v40 = *(Vec02*)&span.q[1];
}
