// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 763/776 (98.3%), checked 2026-11-07
// NEAR: wave 4 e3. 776 bytes, same size; 7 of 194 words differ, and only in which callee-saved registers hold the addresses of hi, count and list
//       (ours s0, s1, s5; retail s5, s0, s1: the address of hi is allocated last in retail). Everything else is retail's: pad flag, guards,
//       the camera-to-target basis by Cross and NormalizeOr, the five rotated offsets with Min and Max (hi is the Max of the new lo, as retail has it),
//       the box query, the five project/unproject/span probes (the counter is one variable for both loops, unsigned), the snap.
//       The globals D_00275970, D_00275974, D_00275978 and D_00275AA0 are INCLUDE_DATA in the file; this near miss declares them extern, and
//       landing it needs them defined in C (0.5f, 2.0f, two zero words, and the five vectors (0,0,0), (0,-50,0), (0,50,0), (0,0,75), (0,0,-50)).
//       ~14 compiles (pointer locals in three orders, local orders).
#include "common.h"
#include "asm_func.h"
#include "on_off_object.h"
#include "collider.h"
#include "world.h"
#include "camera_controller.h"
#include "globals.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "load_progress.h"
#include "output_buffer.h"
#include "game_progress.h"
#include "flag_table.h"
#include "semaphore_params.h"
#include "thread_params.h"
#include "memory_card.h"
#include "screen_element.h"
#include "vu0.h"
#include "fpu.h"

extern s32 g_padSelectFlags;
extern f32 D_00275970;
extern f32 D_00275974;
extern s32 D_00275978;
extern Vec02 D_00275AA0[5];
extern f32 g_gameClock[];
extern f32 D_0026185C;
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void ProjectPointToCamera(Camera* cam, Vec02* in, Vec02* out);
void UnprojectCameraPoint(Camera* cam, Vec02* in, Vec02* out);
void QueueCameraSnap(Camera* cam);
s32 HasColliderSecondTree(void* unused, Collider* other);
void GatherCollidersInBox(void* world, void* self, Vec02* a, Vec02* b, void* filter, s32 d, s32* count, Collider*** list);
s32 FindFirstFreeSpan(s32 count, Collider** objs, f32 thresh, void* a2, void* a3, f32* lo, f32* hi);
void func_001E4578(CameraController* self)
{
    Vec02 lo;
    Vec02 hi;
    Vec02 tmp;
    Vec02 pts[5];
    Mat02 basis;
    s32 count;
    Collider** list;
    f32 spanEnd;
    s32 i;
    Camera* cam = (Camera*)self->owner;
    Collider* target = (Collider*)cam->stack[0].target;
    if (g_padSelectFlags & 2) {
        *(f32*)((u8*)self + 0x60) = D_0026185C;
        return;
    }
    if (self->ptr != 0 && *(s32*)((u8*)self->ptr + 0x440) != 0) {
        return;
    }
    if (D_00275978 != 0) {
        return;
    }
    if (g_gameClock[1] - *(f32*)((u8*)self + 0x60) < D_00275970) {
        return;
    }
    lo = hi = *(Vec02*)cam->f40;
    Vu0::Q(basis.r[2]) = Vu0::Q(g_unitZVector);
    u128 side = Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Sub(Vu0::Q(target->v140), Vu0::Q(*(Vec02*)cam->f40))), Vu0::Q(g_unitXVector));
    Vu0::Q(basis.r[1]) = side;
    Vu0::Q(basis.r[0]) = Vu0::Cross(Vu0::Q(basis.r[2]), side);
    for (i = 0; (u32)i < 5; i++) {
        u128 p = Vu0::Add(Vu0::Q(target->v140), Vu0::Rotate(basis, Vu0::Q(D_00275AA0[i])));
        Vu0::Q(lo) = Vu0::Min(Vu0::Q(lo), p);
        Vu0::Q(hi) = Vu0::Max(Vu0::Q(lo), p);
        Vu0::Q(pts[i]) = p;
    }
    PushBackMemoryMark();
    f32 one = 1.0f;
    GatherCollidersInBox(g_currentWorld, 0, &lo, &hi, (void*)HasColliderSecondTree, 0, &count, &list);
    for (i = 0; (u32)i < 5; i++) {
        ProjectPointToCamera(cam, &pts[i], &tmp);
        tmp.z = cam->f1E4;
        UnprojectCameraPoint(cam, &tmp, &tmp);
        if (FindFirstFreeSpan(count, list, 0.0f, &pts[i], &tmp, 0, &spanEnd) != 0 && one <= spanEnd) {
            *(f32*)((u8*)self + 0x60) = g_gameClock[1];
            break;
        }
    }
    PopBackMemoryMark();
    if (D_00275974 < g_gameClock[1] - *(f32*)((u8*)self + 0x60)) {
        QueueCameraSnap(cam);
    }
}
