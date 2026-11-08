// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 724/736, checked 2026-11-08
// NEAR: the same code and frame (0x240) as retail, the VU0 parts (Length, MulXSum with its two Scalars, the Y/Z reads of v5E0) and the list scans match; what differs is the FPR constants of the step loop. Retail holds 1.0 and 0.0001 in f24 and f23 for the whole loop over the segments and loads the others where used (step = 1.0 in the then arm, 5.0 in the else arm before the divide, `1.0 - t` in the guarded loop); here loop.c also hoists the 5.0 and the then-arm 1.0 (f25, f24, f23, f22 are all hoisted, the divide reads f24), so the head of the loop and four registers differ, and the prologue's saves come in another order. Tried the step as chained assignments in each arm (t = step = ...), as one ternary, and the node time compare both ways round (g_gameClock[1] >= n->time is retail's order). The four nodes at 0x59C and the vector at 0x5E0 are read by offset (the header has them as an s32 and padding). Found (night-sizex1, cc1plus -dL): this form's segment loop is 56 insns at the loop pass, under loop.c's limit, so every constant moves; with Length and MulXSum on Vu0::Vec values and the then-arm's 1.0 a named local it is 78 (77 on the rerun) and the then-arm 1.0 stays in the loop as retail's, but the rerun still moves 1e-4 and 5.0; at 82 (msg.vb stored as a Vec too) neither moves. Retail moves 1.0 and 1e-4 and not 5.0: a loop between those sizes, not found.
// In the context of its file, src/main/file_18F988.cpp.
#include "common.h"
#include "switched_collider.h"
#include "world.h"
#include "globals.h"
#include "object_message.h"
#include "vu0.h"

s32 IsObjectAttached(void* p);

extern f32 g_gameClock[];

struct TrailNode {
    u8 pad00[0x18];
    f32 time;               // 0x18
    u8 pad1C[0x80 - 0x1C];
    Vec02 v80;              // 0x80
    Vec02 v90;              // 0x90
};

void func_00192DD0(SwitchedCollider* self)
{
    Vec02 from[9];
    Vec02 to[9];
    SlotMessage msg;
    Vec02 a;
    Vec02 b;
    BaseObject* sink = *(BaseObject**)((u8*)self->world + 0x1D5C);
    PlacedObject* target = 0;
    s32 count;
    if (sink != 0) {
        for (u32 k = 0; k < 4; k++) {
            if (((void**)((u8*)self + 0x59C))[k] != 0 && IsObjectAttached(((void**)((u8*)self + 0x59C))[k]) != 0) {
                target = (PlacedObject*)((void**)((u8*)self + 0x59C))[k];
                break;
            }
        }
        if (target != 0) {
            count = 1;
            s32 still = 0;
            if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(*(Vec02*)((u8*)self + 0x5E0)))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(*(Vec02*)((u8*)self + 0x5E0)))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(*(Vec02*)((u8*)self + 0x5E0)))) < 0.0001f) {
                still = 1;
            }
            if (still) {
                from[0] = target->v140;
            } else {
                from[0] = (*(Vec02*)((u8*)self + 0x5E0));
            }
            to[0] = target->v140;
        } else {
            count = 0;
            for (s32 k = 0; k < self->f5D0; k++) {
                TrailNode* n = (TrailNode*)self->f5AC[k];
                if (n != 0 && g_gameClock[1] >= n->time) {
                    from[count] = n->v90;
                    to[count] = n->v80;
                    count++;
                }
            }
        }
        msg.kind = 4;
        for (s32 i = 0; i < count; i++) {
            a = from[i];
            b = to[i];
            f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(a), Vu0::Q(b))));
            f32 step;
            f32 t;
            if (len < 0.0001f) {
                t = step = 1.0f;
            } else {
                t = step = 5.0f / len;
            }
            if (t < 1.0f) {
                do {
                    Vu0::Q(msg.vb) = Vu0::MulXSum(Vu0::Q(a), Vu0::Scalar(1.0f - t), Vu0::Q(b), Vu0::Scalar(t));
                    sink->desc->m1B(sink, &msg);
                    t += step;
                } while (t < 1.0f);
            }
            msg.vb = b;
            sink->desc->m1B(sink, &msg);
            (*(Vec02*)((u8*)self + 0x5E0)) = b;
        }
    }
}
