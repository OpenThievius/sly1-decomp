// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1268/1292, checked 2026-11-08
// NEAR (src/main/file_14EE40.cpp, where it is INCLUDE_ASM; 2026-11-08, night-untouched): the
// allocation loop, the accumulation of the items' rows (the angular row's load named first,
// as retail loads it before the linear store) and AddLimited (the vector read through its
// pointer twice: reloaded after the scale's slot store from a part's buffer, kept and copied
// with vmove from the stack locals; the accumulator read first) are retail's code. Left: the
// last loop over each group's parts. Retail does not reduce it (the part read as list[i] with
// list reloaded from its spill at 0x60 each time, i in s4 against the count in s8, the buffer
// in s7); here loop.c turns list[i] into a pointer and the index into a countdown, and the
// saved registers differ from there on (217 lines). Vec values in that loop (a bigger loop at
// the loop pass) keep the index but still reduce the pointer.
#include "common.h"
#include "collider.h"
#include "active_set_solver.h"
#include "fpu.h"
#include "vu0.h"

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
extern u8* AllocateBackMemory(u32);

void* AllocateZeroedBackMemory(u32 size);
void ComputeColliderPointVelocity(Collider* body, Vec02* point, void* motion, Vec02* out);
void ConstrainColliderVector(Collider* body, Vec02* limits, Vec02* in, Vec02* out, s32 mode);

// A part's share of the solved impulses: a linear and an angular one.
struct PartImpulse {
    Vec02 lin;              // 0x00
    Vec02 ang;              // 0x10
};

// acc += v, with v cut to length `limit` when it is longer (limitSq is limit squared).
static inline void AddLimited(Vec02* acc, Vec02* v, f32 limitSq, f32 limit)
{
    f32 lengthSq = Vu0::ToFloat(Vu0::Dot(Vu0::Q(*v), Vu0::Q(*v)));
    if (limitSq < lengthSq) {
        u128 a = Vu0::Q(*acc);
        Vu0::Q(*acc) = Vu0::MulAddX(a, Vu0::Q(*v), Vu0::Scalar(limit / Fpu::Sqrt(lengthSq)));
    } else {
        Vu0::Q(*acc) = Vu0::Add(Vu0::Q(*acc), Vu0::Q(*v));
    }
}

// The solver's impulses handed out: each solved item adds its rows, weighted by its x, to the
// parts of the bodies at its contact's two ends (n groups of parts, counts[j] in group j); each
// part then takes its own impulse, relative to its parent's motion at its position and in the
// parent's frame when it has one, constrained and cut to maxLin and maxAng.
void func_00154370(ActiveSetSolver* self, s32 n, s32* counts, Collider*** lists, f32 maxLin, f32 maxAng)
{
    PartImpulse** bufs;
    f32 maxLinSq;
    f32 maxAngSq;

    PushBackMemoryMark();
    bufs = (PartImpulse**)AllocateBackMemory(n * 4);
    for (s32 i = 0; i < n; i++) {
        bufs[i] = (PartImpulse*)AllocateZeroedBackMemory(counts[i] << 5);
    }
    maxLinSq = maxLin * maxLin;
    maxAngSq = maxAng * maxAng;
    for (s32 i = 0; i < self->count; i++) {
        ActiveSetItem* it = (ActiveSetItem*)(self->items + i * 0x60);
        s32 k;
        if (it->x == 0.0f) {
            continue;
        }
        for (k = 0; k < 2; k++) {
            Collider* body = ((Contact03*)it->owner)->end[k].body;
            s32 m;
            if (body == 0) {
                continue;
            }
            s32 g = body->f4BC;
            if (g < 0) {
                continue;
            }
            Vec02* row = (Vec02*)it->rows[k];
            PartImpulse* buf = bufs[g];
            for (m = 0; m < counts[g]; m++) {
                u128 lin = Vu0::Q(buf[m].lin);
                Vu0::Q(buf[m].lin) = Vu0::MulAddX(lin, Vu0::Q(row[2 * m]), Vu0::ScalarAt(it->x));
                u128 ang = Vu0::Q(buf[m].ang);
                Vu0::Q(buf[m].ang) = Vu0::MulAddX(ang, Vu0::Q(row[2 * m + 1]), Vu0::ScalarAt(it->x));
            }
        }
    }
    for (s32 j = 0; j < n; j++) {
        s32 count = counts[j];
        Collider** list = lists[j];
        PartImpulse* buf = bufs[j];
        for (s32 i = 0; i < count; i++) {
            Collider* body = list[i];
            PartImpulse* own = &buf[body->index];
            Collider* parent = (Collider*)body->parent;
            if (parent != 0) {
                PartImpulse* up = &buf[parent->index];
                Vec02 lin;
                Vec02 ang;
                Vec02 linLocal;
                Vec02 angLocal;
                ComputeColliderPointVelocity(parent, &body->v140, up, &lin);
                Vu0::Q(lin) = Vu0::Sub(Vu0::Q(own->lin), Vu0::Q(lin));
                Vu0::Q(ang) = Vu0::Sub(Vu0::Q(own->ang), Vu0::Q(up->ang));
                Vu0::Q(linLocal) = Vu0::RotateTransposed(parent->m110, Vu0::Q(lin));
                Vu0::Q(angLocal) = Vu0::RotateTransposed(parent->m110, Vu0::Q(ang));
                ConstrainColliderVector(body, &body->v440, &linLocal, &linLocal, 0);
                ConstrainColliderVector(body, &body->v460, &angLocal, &angLocal, 0);
                AddLimited(&body->v490, &linLocal, maxLinSq, maxLin);
                AddLimited(&body->spin4A0, &angLocal, maxAngSq, maxAng);
            } else {
                AddLimited(&body->v490, &own->lin, maxLinSq, maxLin);
                AddLimited(&body->spin4A0, &own->ang, maxAngSq, maxAng);
            }
        }
    }
    PopBackMemoryMark();
}
