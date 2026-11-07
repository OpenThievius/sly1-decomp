// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 285/308 (92.5%), checked 2026-11-07
// NEAR: all but the register of the third row: retail's third vmaddz writes vf3 (the first row of the matrix, which dies there) where Vu0::Rotate ties its result to the vector (vf2). A Rotate whose result is not tied (the allocator then gives it the first input that dies) would match; the same form is needed by func_001EBDD0, func_00128150, func_00128E88, func_00125138, func_001CCF98, func_001CDD98 and func_001EA918.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "world.h"
#include "globals.h"
#include "shapes.h"
#include "collider.h"
#include "script_value.h"
#include "script_builtin.h"
#include "queued_call.h"

// Stands in for the static objects of the file: the check names its compiler-made functions.
struct MarkStacks {
    MarkStacks();
    ~MarkStacks();
};
MarkStacks::MarkStacks() {}
MarkStacks::~MarkStacks() {}
MarkStacks g_nmStacks;



typedef f32 (*MathFn_259938)(f32 x);
f32* AcquireMatrixPayload(void);
void MatrixToAxisAngle(void* a, f32* b, f32* c);
void ResetMatrixHomogeneous(void* p);

void MultiplyMatrices3x3(void* a, void* b, void* out);
void BuildAxisAngleMatrix(void* axis, void* out, f32 angle);

ScriptValue* InterpolateScriptRotation(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    Mat02 delta;
    Vec02 axis;
    Mat02 a;
    Mat02 b;
    f32 angle;
    InitScriptValue(&obj);
    f32* m = AcquireMatrixPayload();
    MultiplyMatrices3x3(args[0].p, args[1].p, &delta);
    MatrixToAxisAngle(&delta, &angle, (f32*)&axis);
    BuildAxisAngleMatrix(&axis, &delta, angle * args[2].f);
    const Mat02* src = (const Mat02*)args[0].p;
    u128 v0 = Vu0::Q(src->r[0]);
    Vu0::Q(b.r[0]) = Vu0::Q(a.r[0]) = Vu0::Rotate(delta, v0);
    Vu0::Q(b.r[1]) = Vu0::Q(a.r[1]) = Vu0::Rotate(delta, Vu0::Q(src->r[1]));
    Vu0::Q(b.r[2]) = Vu0::Q(a.r[2]) = Vu0::Rotate(delta, Vu0::Q(src->r[2]));
    *(Mat02*)m = a;
    ResetMatrixHomogeneous(m);
    SetScriptValueMatrix(&obj, m);
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}
