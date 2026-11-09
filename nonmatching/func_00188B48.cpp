// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 192/196 (98.0%), checked 2026-11-08
// NEAR: two dead stores swapped: retail stores the transposed rows to the stack in the order 0x30, 0x40, 0x10, 0x50, 0x20; here 0x30, 0x40, 0x50, 0x10, 0x20. Everything else is retail's (Vu0::Transpose's two sequences and registers, the negated rotated position in place). Tried every order of the row assignments in Transpose, Q/Set/pointer stores, the result through a caller local (in a block or not, rows copied in every order) and through an out parameter.
// Still differs (2026-11-08, night-close1): Transpose's local as an aggregate initialiser copies it through a call; not closer.
// In the context of its file, src/main/matrix.cpp.
// Mechanism (2026-11-08, mech-188B48; docs/TOOLCHAIN.md, sched1, "Dead stores keep their insn order"):
// the five stores are dead (no dependents), so sched1 and sched2 rank them equal on every key and
// INSN_LUID decides: retail's RTL had them per row, the local's row then the result's (0x30, 0x0,
// 0x40, 0x10, 0x50, 0x20; the 0x0 one goes early as the Scalar's slot store depends on it). A
// returned local is copied after all its rows are written, so no caller form with this Transpose
// reaches it. Proved with a scratch copy of the helper that writes the return slot (g++'s named
// return value, `return y`) right after each row of its local: EXACT. Not landed: that form is
// not plausible original code, and the helper is shared.
// Still differs (2026-11-08, night-close6): Transpose with its second asm writing t's rows, or the rows copied to a second local before returning: the frame grows (13+ lines).
#include "common.h"
#include "shapes.h"
#include "vu0.h"

void InvertRigidTransform(void* a, void* b, Quad16* out)
{
    *(Vu0::Rows*)out = Vu0::Transpose(*(Vu0::Rows*)b);
    Vu0::Q(out[3]) = Vu0::RotateTransposed(*(Vu0::Rows*)b, Vu0::Q(*(Quad16*)a));
    Vu0::Q(out[3]) = Vu0::MulX(Vu0::Q(out[3]), Vu0::Scalar(-1.0f));
    out[0].w[3] = 0;
    out[1].w[3] = 0;
    out[2].w[3] = 0;
    *(f32*)&out[3].w[3] = 1.0f;
}
