// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 772/956 (80.8%), checked 2026-11-07
// NEAR: wave 4 e3. 956 bytes, same size and frame; regdiff 'code' 87.9% (210 of 239 words). The camera's look-around search: the box of the two points and the target, the best-position search
//       (func_00145950), the free-span test, the sweep of angles by 0.2857 steps scored by (1.25 - span end) * (|angle| + 0.4856), the mix of the best (MulXSum), the push
//       (func_00145B68) and the final mix by the span's middle. The floats take other FP registers: retail has the angle in f20 and the best score in f21, 1.0 in f22 and its copy for the loop in f27, the
//       zero copy in f23, pi in f24, 0.2857 in f26; ours swaps angle and best score (f21, f20) and renumbers the rest. D_0024E5F0 (FLT_MAX) stays INCLUDE_RODATA in the file; the near miss reads it extern.
//       ~8 compiles (declaration orders of the float locals).
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

struct SpanCandidate { u8 pad[0x20]; f32 value; };
extern f32 g_gameClock[];
extern const f32 D_0024E5F0;
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void ComputePolarOffset(Vec02* out, f32 a, f32 b, f32 c);
void ConvertOffsetToCylindrical(const Vec02* a, const Vec02* b, f32* angle, f32* dist, f32* height);
s32 HasColliderSecondTree(void* unused, Collider* other);
void GatherCollidersInBox(void* world, void* self, Vec02* a, Vec02* b, void* filter, s32 d, s32* count, Collider*** list);
s32 FindFirstFreeSpan(s32 count, Collider** objs, f32 thresh, void* a2, void* a3, f32* lo, f32* hi);
void func_00145950(s32 count, Collider** objs, Vec02* origin, Vec02* out, f32 r);
void func_00145B68(void* ctx, s32 count, Collider** objs, void* fn, f32 r, f32 limit, void* a4, Vec02* origin, Vec02* out);
f32 GetSpanCandidateValue(void* a0, void* a1, void* a2, SpanCandidate* a3);
void func_001E4888(CameraController* self, Vec02* p, Vec02* q, Vec02* out)
{
    Vec02 lo;
    Vec02 hi;
    Vec02 pos;
    Vec02 best;
    Vec02 dir;
    Vec02 cand;
    Vec02 mixed;
    s32 count;
    Collider** list;
    f32 spanLo;
    f32 spanHi;
    f32 m0;
    f32 m1;
    f32 m2;
    Camera* cam = (Camera*)self->owner;
    f32 angle = 0.0f;
    PushBackMemoryMark();
    Collider* target = (Collider*)cam->stack[0].target;
    Vu0::Q(lo) = Vu0::Min(Vu0::Q(*p), Vu0::Min(Vu0::Q(*q), Vu0::Q(target->v140)));
    Vu0::Q(hi) = Vu0::Max(Vu0::Q(*p), Vu0::Max(Vu0::Q(*q), Vu0::Q(target->v140)));
    GatherCollidersInBox(g_currentWorld, 0, &lo, &hi, (void*)HasColliderSecondTree, 0, &count, &list);
    func_00145950(count, list, &target->v140, &pos, 500.0f);
    FindFirstFreeSpan(count, list, angle, &pos, q, &spanLo, &spanHi);
    if (spanHi < 1.0f) {
        *(s32*)((u8*)self + 0x20) = 4;
        ConvertOffsetToCylindrical(q, p, &m0, &m1, &m2);
        f32 bestScore = D_0024E5F0;
        f32 zero = 0.0f;
        f32 next;
        do {
            ComputePolarOffset(&dir, m0 + angle, m1, m2);
            Vu0::Q(cand) = Vu0::Add(Vu0::Q(*p), Vu0::Q(dir));
            FindFirstFreeSpan(count, list, zero, &pos, &cand, &spanLo, &spanHi);
            f32 score = (1.25f - spanHi) * (__builtin_fabsf(angle) + 0.4856f);
            if (score < bestScore) {
                bestScore = score;
                Vu0::Q(mixed) = Vu0::MulXSum(Vu0::Q(pos), Vu0::Scalar(1.0f - spanHi), Vu0::Q(cand), Vu0::Scalar(spanHi));
            }
            next = -angle;
            if (angle <= zero) {
                next = next + 0.2857f;
            }
            angle = next;
            if (bestScore < (__builtin_fabsf(next) + 0.4856f) * 0.25f) {
                break;
            }
        } while (next < 3.1415927f);
        best = mixed;
    } else {
        Vu0::Q(best) = Vu0::MulXSum(Vu0::Q(pos), Vu0::Scalar(1.0f - spanHi), Vu0::Q(*q), Vu0::Scalar(spanHi));
    }
    func_00145B68(cam, count, list, (void*)GetSpanCandidateValue, ((f32*)cam)[0x1EC / 4], ((f32*)cam)[0x1EC / 4], &best, &best, out);
    FindFirstFreeSpan(count, list, 0.0f, &best, out, &spanLo, &spanHi);
    if (spanHi != 1.0f) {
        f32 w = (spanLo + spanHi) * 0.5f;
        Vu0::Q(*out) = Vu0::MulXSum(Vu0::Q(best), Vu0::Scalar(1.0f - w), Vu0::Q(*out), Vu0::Scalar(w));
    }
    PopBackMemoryMark();
}
