// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 160/208 (76.9%), checked 2026-11-07
// NEAR: right instructions; differs in the VU0 register numbers (retail: matrix rows vf1,vf2,vf6, the frame rows vf3,vf4,vf5, ascending; ours descending) and in the order of the stores (retail stores the world rows, then each copy's row pair).
#include "common.h"
#include "asm_func.h"
#include "counted_collider.h"
#include "switched_collider.h"
#include "globals.h"
#include "game_progress.h"
#include "pad_record.h"
#include "object_message.h"
#include "screen_element.h"
#include "game_clock.h"
#include "vu0.h"

struct FrameSource;
struct FrameSourceDesc { u8 pad00[0x1C]; void (*getFrame)(FrameSource* self, Mat02* out); };
struct FrameSource { FrameSourceDesc* desc; };
typedef u64 Qword128 __attribute__((mode(TI)));
void ComputePlacedObjectWorldFrame(void* self);
void ComputeColliderWorldFrame(Collider* self);
void TransformMeshToWorld(Mesh03* a, Mesh03* b, Qword128 q, Mat02* c);

void func_001D35A8(CountedCollider* self)
{
    if (self->f1F4 != 0) {
        Mat02 world;
        Mat02 frame;
        Mat02 copyA;
        Mat02 copyB;
        ComputePlacedObjectWorldFrame(self);
        FrameSource* src = (FrameSource*)self->f1F4;
        src->desc->getFrame(src, &frame);
        u128 r0 = Vu0::Rotate(self->m110, Vu0::Q(frame.r[0]));
        u128 r1 = Vu0::Rotate(self->m110, Vu0::Q(frame.r[1]));
        u128 r2 = Vu0::Rotate(self->m110, Vu0::Q(frame.r[2]));
        Vu0::Q(world.r[0]) = r0;
        Vu0::Q(world.r[1]) = r1;
        Vu0::Q(world.r[2]) = r2;
        Vu0::Q(copyA.r[0]) = r0;
        Vu0::Q(copyA.r[1]) = r1;
        Vu0::Q(copyA.r[2]) = r2;
        Vu0::Q(copyB.r[0]) = r0;
        Vu0::Q(copyB.r[1]) = r1;
        Vu0::Q(copyB.r[2]) = r2;
        TransformMeshToWorld(&self->mesh, &self->meshCopy, *(Qword128*)&self->v140, &world);
    } else {
        ComputeColliderWorldFrame(self);
    }
}
