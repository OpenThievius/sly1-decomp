// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 136/132, checked 2026-11-07
// NEAR: right but for one word. Retail reads the camera's +0x1E4 with lw and passes it to qmtc2 as a raw word; FromFloat takes an f32, so the compiler loads it with lwc1 and moves it with mfc1. A FromFloat taking the word (lw, qmtc2) would match.
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
#include "camera.h"

// Stands in for the static objects of the file: the check names its compiler-made functions.
struct MarkStacks {
    MarkStacks();
    ~MarkStacks();
};
MarkStacks::MarkStacks() {}
MarkStacks::~MarkStacks() {}
MarkStacks g_nmStacks;



typedef f32 (*MathFn_259938)(f32 x);
f32* AcquireVectorAPayload(void);

ScriptValue* GetScriptPointAheadOfCamera(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue obj;
    Vec02 t;
    Vec02 k;
    InitScriptValue(&obj);
    f32* p = AcquireVectorAPayload();
    Camera* c = g_camera;
    Vu0::Q(k) = Vu0::FromFloat(c->f1E4);
    Vu0::Q(t) = Vu0::MulX(Vu0::Q(c->f80), Vu0::Q(k));
    Vu0::Q(*(Vec02*)p) = Vu0::Add(Vu0::Q(c->f40), Vu0::Q(t));
    SetScriptValueVectorA(&obj, p);
    CopyConstructScriptValue(ret, &obj);
    DestroyScriptValue(&obj, 2);
    return ret;
}
