// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1120/1108, checked 2026-11-08
// BYTES 0/0, checked 2026-11-08
// NEAR (2026-11-08, worker night-large1): CollectTreeNodeSpans, the walk of a segment through a
// mesh's BSP tree (a stack of 32 entries) that writes a span for each run behind a face, retail's
// control flow and stores. loop.c moves the zero vector's address (lui, addiu: life 2, savings 2)
// out of the walk's loop (142 insns at the pass), where retail builds it in the branch; the spare
// register it takes adds a 16-byte spill to the frame, and the registers and the weights' mfc1
// order follow. Vec values for the lerps and dots leave it.
#include "common.h"
#include "flag_table.h"
#include "asm_func.h"
#include "list_iter.h"
#include "timed_state_object.h"
#include "trigger_zone.h"
#include "zone_collider.h"
#include "masked_collider.h"
#include "child_group_object.h"
#include "switched_collider.h"
#include "object_message.h"
#include "world.h"
#include "object_event.h"
#include "vu0.h"

// A face of a mesh's tree as the walk reads it: its plane.
struct TreeFace {
    Vec02 normal;           // 0x00
    f32 d;                  // 0x10
};

// An entry of the tree walk's stack: the part of the segment from t on, in a subtree.
struct TreeWalkEntry {
    TreeNode03* node;       // 0x00: the subtree still to walk (0: the segment is in a leaf)
    f32 t;                  // 0x04: where the part starts
    TreeNode03* solid;      // 0x08: the node behind whose face the part lies (0: in front)
    TreeFace* face;         // 0x0C: the face crossed at t
};

void FillMemory(void* p, s32 v, s32 n);
extern u8 D_00248D30[];

s32 func_0013DFD8(TreeNode03* root, Vec02* a, Vec02* b, s32* groups, s32 max, ColliderSpan* spans)
{
    TreeWalkEntry cur;
    TreeWalkEntry stack[32];
    TreeWalkEntry* top = stack;
    ColliderSpan* span = 0;
    ColliderSpan* next = spans;
    f32 one = 1.0f;
    cur.node = root;
    cur.t = 0.0f;
    cur.solid = 0;
    cur.face = 0;
    top->node = 0;
    top->t = one;
    top->solid = 0;
    top->face = 0;
    for (;;) {
        while (cur.node == 0) {
            if (cur.solid != 0) {
                if (span != 0 && cur.face == span->face54 &&
                    (groups == 0 || span->group == groups[cur.solid - root])) {
                    Vu0::Q(span->q[1]) = Vu0::MulXSum(Vu0::Vec::Of(*a), Vu0::Vec::Scalar(1.0f - top->t), Vu0::Vec::Of(*b), Vu0::Vec::Scalar(top->t)).q;
                    span->face54 = top->face;
                    if (top->face != 0) {
                        span->q[3] = *(Quad16*)top->face;
                    } else {
                        span->q[3] = *(Quad16*)D_00248D30;
                    }
                    span->time[1] = top->t;
                } else {
                    if (next - spans >= max) {
                        return max;
                    }
                    span = next;
                    FillMemory(span, 0, 0x70);
                    next++;
                    Vu0::Q(span->q[0]) = Vu0::MulXSum(Vu0::Vec::Of(*a), Vu0::Vec::Scalar(1.0f - cur.t), Vu0::Vec::Of(*b), Vu0::Vec::Scalar(cur.t)).q;
                    Vu0::Q(span->q[1]) = Vu0::MulXSum(Vu0::Vec::Of(*a), Vu0::Vec::Scalar(1.0f - top->t), Vu0::Vec::Of(*b), Vu0::Vec::Scalar(top->t)).q;
                    span->face50 = cur.face;
                    span->face54 = top->face;
                    if (cur.face != 0) {
                        span->q[2] = *(Quad16*)cur.face;
                    }
                    if (top->face != 0) {
                        span->q[3] = *(Quad16*)top->face;
                    }
                    span->time[0] = cur.t;
                    span->time[1] = top->t;
                    if (groups != 0) {
                        span->group = groups[cur.solid - root];
                    }
                }
            }
            if (top <= stack) {
                return next - spans;
            }
            cur = *top;
            top--;
        }
        TreeNode03* n = cur.node;
        TreeFace* f = (TreeFace*)n->face;
        f32 da = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(*a), Vu0::Vec::Of(f->normal))) - f->d;
        f32 db = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(*b), Vu0::Vec::Of(f->normal))) - f->d;
        if (da <= 0.0f && db <= 0.0f) {
            cur.solid = n;
            cur.node = n->back;
            continue;
        }
        if (0.0f < da && 0.0f < db) {
            cur.solid = 0;
            cur.node = n->front;
            continue;
        }
        f32 t = da / (da - db);
        f32 dIn = db * cur.t + (one - cur.t) * da;
        f32 dOut = db * top->t + (one - top->t) * da;
        if (cur.t < t && t < top->t) {
            top++;
            top->t = t;
            top->face = (TreeFace*)cur.node->face;
            if (dIn <= 0.0f) {
                top->solid = 0;
                top->node = cur.node->front;
            } else {
                top->solid = cur.node;
                top->node = cur.node->back;
            }
        }
        if (dIn < 0.0f || (dIn == 0.0f && dOut <= 0.0f)) {
            cur.solid = cur.node;
            cur.node = cur.node->back;
        } else {
            cur.solid = 0;
            cur.node = cur.node->front;
        }
    }
}
