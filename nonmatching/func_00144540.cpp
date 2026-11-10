// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 627/772 (81.2%), checked 2026-11-10
// NEAR (2026-11-10, w14-144540): retail's size, frame, callee-saved registers and stack layout; every instruction is retail's (regdiff: order). Found: the view
//       after the join is the expression itself (GCSE's PRE copies self+0x80 into s5 in each arm, so no `view` variable); the clamp is ValueRange::Limit; the
//       rotation is a Mat02 (BuildRotationFromVector writes 3 rows); the weight is one named Scalar (slot at 0x50) used by pos, dir and corner, and tilt's own
//       Scalar(swing) slot (0xB0) is what overwrites the product's r.r[2], which flow1 then deletes as a dead store: that needs corner computed before the
//       product (its loads through lo_sum pseudos otherwise kill flow's mem_set_list); MulRotationRowsX gives retail's store order; tilt and proj declared
//       after the product reuse its frame (0x60, 0x70); the copy loop's pointers declared e, d, c, b, a give retail's a1/v1. Still differs: (1) the VU0
//       registers (retail s=vf5, ours vf7: local-alloc ranks the weight below the post-call product rows, which in retail are loaded before corner's store
//       at 0x50 and so live longer; ours wait for it because the rows' address, the inline reference parameter self+0x80, has no base find_base_term accepts
//       (a VOIDmode argument ADDRESS through a register without REGNO_POINTER_FLAG), while row 0 at 0x80(self) passes); (2) the projection's float
//       registers ($f0/$f3 for 4096/640 swapped), which follow from sched1's order in the same block. Tried for (1): a Mat02* local for the rows (before or after
//       the clamp), the rows read as Vu0::Vec members, corner stored as a Vec member, corner as u128 (ICE). ~35 compiles.
#include "common.h"
#include "shapes.h"
#include "collider.h"
#include "world.h"
#include "camera.h"
#include "pad_record.h"
#include "fpu.h"
#include "asm_func.h"
#include "vu0.h"
#include "ramp_profile.h"
#include "placed_object.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "game_clock.h"

#include "mul_rotation.h"
#include "value_range.h"
extern f32 D_002618C8;
extern f32 D_002618CC;
extern f32 D_002618D0[4];
extern f32 D_002618E0[4];
extern f32 D_002618F0[4];
extern f32 D_00261900[4];
extern f32 D_00261910[4];
void BuildViewProjectionMatrix(f32* b, f32* a, void* c, Quad16* out);
void* InvertMatrix4x4(void* a0, void* a1);
extern f32 D_0026185C;
extern u8 D_00248D40[];
f32 Sine(f32 x);
void BuildRotationFromVector(Vec02* v, Mat4* mat);
void BuildProjectionMatrix(Mat4* self, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void func_001443C8(Mat02* m, Vec02* out, f32 x, f32 y);
void func_00144540(Camera* self)
{
    Vec02 pos;
    Vec02 dir;
    Mat02 rotation;
    f32 f6 = D_0026185C - self->f218;
    if (D_002618C8 < f6) {
        BuildViewProjectionMatrix((f32*)self->f40, (f32*)self->f80, (void*)((u8*)self + 0xC0), (Quad16*)((u8*)self + 0x100));
    } else {
        f32 t = f6 / D_002618C8;
        f32 amount = g_unitRange.Limit(D_002618D0[0] + t * (D_002618D0[1] + t * D_002618D0[2]));
        f32 swing = Sine(f6 * D_002618CC) * amount;
        u128 turn = Vu0::Rotate(*(Mat02*)self->f80, Vu0::Q(*(Vec02*)D_002618E0));
        u128 s = Vu0::Scalar(swing);
        Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(*(Vec02*)self->f40), turn, s);
        Vu0::Q(dir) = Vu0::MulX(Vu0::Q(*(Vec02*)D_002618F0), s);
        BuildRotationFromVector(&dir, (Mat4*)&rotation);
        Vec02 corner;
        Vu0::Q(corner) = Vu0::MulAddX(Vu0::Q(*(Vec02*)D_00248D40), Vu0::Q(*(Vec02*)D_00261900), s);
        MulRotationRowsX(&rotation, *(Mat02*)self->f80, rotation);
        Vec02 tilt;
        Mat4 proj;
        Vu0::Q(tilt) = Vu0::MulX(Vu0::Q(*(Vec02*)D_00261910), Vu0::Scalar(swing));
        BuildProjectionMatrix(&proj, corner.x * 640.0f / (self->f1F0 * 4096.0f), corner.y * 224.0f / (self->f1F4 * 4096.0f), tilt.x, tilt.y, self->f1E4, self->f1E8);
        BuildViewProjectionMatrix((f32*)&pos, (f32*)&rotation, &proj, (Quad16*)((u8*)self + 0x100));
    }
    InvertMatrix4x4((u8*)self + 0x100, (u8*)self + 0x140);
    func_001443C8((Mat02*)self->f80, (Vec02*)((u8*)self + 0x180), self->f1F0, self->f1F4);
    {
        f32* e = (f32*)((u8*)self + 0x1B0);
        f32* d = self->planes[0];
        f32* c = (f32*)((u8*)self + 0x1A0);
        f32* b = (f32*)((u8*)self + 0x190);
        f32* a = (f32*)((u8*)self + 0x180);
        s32 n = 2;
        do {
            d[0] = *a++;
            d[1] = *b++;
            d[2] = *c++;
            d[3] = *e++;
            d += 4;
        } while (--n >= 0);
    }
}
