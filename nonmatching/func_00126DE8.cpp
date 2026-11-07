// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 412/400, checked 2026-11-07
// NEAR: 12 bytes too long: the compiler keeps the address of the vector at 0xC0 (k) in a callee-saved register from the first call to the last, and retail forms it again at each use. With k a Vec02 or a u128 local the frame is wrong (k at 0x100); inside a struct with the result matrix the slots are right but the register stays.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
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


typedef void (*Fn_Table)();

void BuildShortestArcRotation(void* from, void* to, void* out);
void BuildMatrixFromRotationAndTranslation(void* translation, void* rotation, void* out);
void MultiplyMatrices(void* out, void* a, void* b);

void func_00126DE8(void* unused0, Camera* cam, void* unused2, f32* pos, Mat4A* m)
{
    Vec02 a;
    Mat02 rot;
    Mat4A t;
    Mat4A local;
    struct {
        u128 k;
        Mat4A r;
    } w;
    w.k = Vu0::FromFloat(-1.0f);
    Vu0::Q(a) = Vu0::MulX(Vu0::Q(cam->f80), w.k);
    BuildShortestArcRotation(m, &a, &rot);
    local = *m;
    local.m[3][0] -= pos[0];
    local.m[3][1] -= pos[1];
    local.m[3][2] -= pos[2];
    BuildMatrixFromRotationAndTranslation((void*)&D_00248D30, &rot, &t);
    MultiplyMatrices(&w.r, &t, &local);
    w.k = Vu0::Sub(Vu0::Q(w.r.m[2]), Vu0::MulX(Vu0::Q(a), Vu0::Dot(Vu0::Q(w.r.m[2]), Vu0::Q(a))));
    *m = w.r;
    BuildShortestArcRotation(&w.k, &cam->fA0, &rot);
    BuildMatrixFromRotationAndTranslation(pos, &rot, &t);
    MultiplyMatrices(&w.r, &t, m);
    *m = w.r;
}
