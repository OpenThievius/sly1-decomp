// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 627/772 (81.2%), checked 2026-11-12
// w25 (2026-11-11, w25-deps): the REG_EQUAL route is closed: no writer of REG_EQUAL/REG_EQUIV before sched1 notes `self + 0x80` outside a loop (docs/toolchain/alias-classes.md, "Where a pointer's known value can come from"); rows read from `self` in a copy of MulRotationRowsX rise above corner's store but lose s5 (170 lines against 58), and retail's rows are s0-based. The 33rd-reference flush is not reached (28 references).
// Wave 23 (w23-vuD, 2026-11-11), alias.c read for wall (1): in the .sched dump the post-call row loads (insns 329, 330: mem:TI (plus (reg/v 163) 16|32)) depend on corner's store (316, mem:TI at 80, no flags). Pseudo 163 (the reference parameter self+0x80, set once, user var) has no base: find_base_value's PLUS case replaces self by its VOIDmode argument ADDRESS and then recurses on that ADDRESS, which falls to the default (0); base_alias_check's fallback, canon_rtx, needs a REG_EQUAL or REG_EQUIV note on 163's set for reg_known_value, and it has none. Retail's rows pass the store, so in retail either the pseudo's set carried a REG_EQUAL (a set CSE or GCSE rewrote from another expression, e.g. a copy of the PRE register s5 with the address as its note), or the rows were MEM_IN_STRUCT_P loads through a varying address against a MEM_SCALAR_P corner store (fixed_scalar_and_varying_struct_p). Tried (2 compiles): the product's rows read as Vu0::Vec members (a local copy of MulRotationRowsX): unchanged; with corner also a u128 read through a (s128) cast's copy (Scalar's MEM_SCALAR_P temporary), the rows still load after corner's store and the frame grows (780 bytes, 156 of 193). The REG_EQUAL route is untested.
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
// w40-fc (2026-11-12): two probes for wall (1), both no closer: the product's a rows read as Vu0::Vec members (mem/s) with corner unchanged (58 lines, the same), and with corner a u128 stored through a cast's copy (`(const f32*)&(s128)cq`, a mem/f slot): the frame grows 16 bytes and the rows still wait (121 lines). A u128 corner read as floats is the ICE at expr.c:614.
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
extern f32 g_gameTime;
extern u8 D_00248D40[];
f32 Sine(f32 x);
void BuildRotationFromVector(Vec02* v, Mat4* mat);
void BuildProjectionMatrix(Mat4* self, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);
void BuildFrustumSideNormals(Mat02* m, Vec02* out, f32 x, f32 y);
void UpdateCameraMatrices(Camera* self)
{
    Vec02 pos;
    Vec02 dir;
    Mat02 rotation;
    f32 f6 = g_gameTime - self->f218;
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
    BuildFrustumSideNormals((Mat02*)self->f80, (Vec02*)((u8*)self + 0x180), self->f1F0, self->f1F4);
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
