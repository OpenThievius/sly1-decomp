// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 374/812 (46.1%), checked 2026-11-08
// Night-low1 (2026-11-08): `return -0.1f < acc.z;` in place of the if gives retail's shared
//       return-0 block after the f690 test (the boolean's li v0,1 / move v0,zero is no return-0
//       tail for cross-jumping to merge the early returns into), but the loops' delay slots then
//       fill otherwise and the C grows to 820 bytes (regdiff 'code' 84.7% to 89.7%); kept here
//       as the if until the count loop's registers (retail row a2, contact a0, row->next in v0
//       with move a2, v0) come too.
// NEAR: wave 4 e3. 812 bytes, same size and frame (0x90; the weights' slot at 0x10 below the spilled down vector at 0x20, the sum at 0). Structure is retail's: the guards, the contact
//       count, the three allocations, the Gram matrix with the copy of the first normal hoisted before the inner loop (vmove), the right-hand sides, the solve, the
//       weighted sum, the -0.1 test. Differences: the shared return-0 block of the first guard and the f690 test sits at the end in ours and inline after the f690
//       test in retail; the row and contact pointers of the loops are in other caller-saved registers (retail a2 and a0, ours t0, a1, v1) and the gram pointer in a2
//       (retail a3). ~12 compiles.
#include "common.h"
#include "point_object.h"
#include "collider.h"
#include "globals.h"
#include "shapes.h"
#include "placed_object.h"
#include "asm_func.h"
#include "fpu.h"
#include "vu0.h"

extern f32 D_0026185C;
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
void SolveActiveSetSystem(s32 count, u8* data, f32* values, f32* out);
s32 func_0017ECE8(Player* self)
{
    Vec02 acc;
    s32 n = 0;
    f32 now = D_0026185C;
    if (now - self->f222C < 1.0f) {
        return 0;
    }
    if (now - *(f32*)((u8*)self + 0x2238) < 1.0f) {
        return 0;
    }
    *(f32*)((u8*)self + 0x2238) = now;
    if (self->f690 != 0) {
        return 0;
    }
    Contacts03* ct = self->contacts;
    if (ct != 0) {
        for (ContactRow03* row = ct->head; row != 0; row = row->next) {
            for (Contact03* c = row->head; c != 0; c = c->next) {
                n++;
            }
        }
    }
    if (n == 0) {
        return 0;
    }
    PushBackMemoryMark();
    u128 down = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-1.0f));
    f32* gram = (f32*)AllocateBackMemory(n * n * 4);
    f32* rhs = (f32*)AllocateBackMemory(n * 4);
    f32* sol = (f32*)AllocateBackMemory(n * 4);
    f32* p = gram;
    for (ContactRow03* ra = self->contacts->head; ra != 0; ra = ra->next) {
        for (Contact03* a = ra->head; a != 0; a = a->next) {
            u128 na = Vu0::Q(a->v80);
            if (a->end[0].body != (Collider*)self) {
                na = Vu0::MulX(na, Vu0::Scalar(-1.0f));
            }
            for (ContactRow03* rb = self->contacts->head; rb != 0; rb = rb->next) {
                u128 ac = na;
                for (Contact03* b = rb->head; b != 0; b = b->next) {
                    u128 nb = Vu0::Q(b->v80);
                    if (b->end[0].body != (Collider*)self) {
                        nb = Vu0::MulX(nb, Vu0::Scalar(-1.0f));
                    }
                    *(u32*)p++ = Vu0::ToBits(Vu0::Dot(ac, nb));
                }
            }
        }
    }
    p = rhs;
    for (ContactRow03* ra = self->contacts->head; ra != 0; ra = ra->next) {
        for (Contact03* a = ra->head; a != 0; a = a->next) {
            u128 na = Vu0::Q(a->v80);
            if (a->end[0].body != (Collider*)self) {
                na = Vu0::MulX(na, Vu0::Scalar(-1.0f));
            }
            *(u32*)p++ = Vu0::ToBits(Vu0::Dot(na, down));
        }
    }
    SolveActiveSetSystem(n, (u8*)gram, rhs, sol);
    Vu0::Q(acc) = down;
    p = sol;
    for (ContactRow03* ra = self->contacts->head; ra != 0; ra = ra->next) {
        for (Contact03* a = ra->head; a != 0; a = a->next) {
            u128 na = Vu0::Q(a->v80);
            if (a->end[0].body != (Collider*)self) {
                na = Vu0::MulX(na, Vu0::Scalar(-1.0f));
            }
            Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(acc), na, Vu0::Scalar(*p++));
        }
    }
    PopBackMemoryMark();
    if (-0.1f < acc.z) {
        return 1;
    }
    return 0;
}
