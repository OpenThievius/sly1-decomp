// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1272/1264, checked 2026-11-08
// NEAR: everything but the matrix arms is retail's (the three switches, the payload copies, the
// Scalar of the vector, the StoreFloatAsQuadword/CopyQuadword/ScaleQuadword chain); the matrix
// arms take the new Vu0::ScalarInGpr (mfc1, por a2, sq to the slot, as retail) and retail's
// slots (the copy first, then the weight, then the scaled matrix in the weight's freed slot).
// Left: &r is kept in s0 across ScaleMatrix for CopyBytes, where retail forms addiu a0, sp, 0x60
// and addiu a1, sp, 0x60 afresh (two words per arm, and the branch offsets after them). Tried:
// an out pointer, a value return into r, a temporary bound to a reference of an inline copy, an
// inline function returning the scaled matrix (that drops the CopyBytes: its copy is lq/sq).
// Still differs (2026-11-08, with Multiply): `*(T*)&c = ScaleMatrix(...)` gives retail's fresh
// hidden address for the call, but then no CopyBytes; a matrix class whose operator= calls
// CopyBytes, or the returned temporary's address, keep it in s0 as before (func_00112C38's notes).
#include "common.h"
#include "script_value.h"
#include "vu0.h"
struct ScriptScope;
f32* AcquireVectorAPayload(void);
f32* AcquireMatrixPayload(void);
f32* AcquireVectorBPayload(void);
f32* AcquirePairPayload(void);
void SetScriptValueInt(ScriptValue* self, s32 n);
void SetScriptValueFloat(ScriptValue* self, f32 f);
void SetScriptValueVectorA(ScriptValue* self, f32* v);
void SetScriptValueMatrix(ScriptValue* self, f32* v);
void SetScriptValueVectorB(ScriptValue* self, f32* v);
void SetScriptValuePair(ScriptValue* self, f32* v);
typedef u64 Quad_118D10 __attribute__((mode(TI)));
typedef u64 Quad_118D20 __attribute__((mode(TI)));
Quad_118D10* CopyQuadword(Quad_118D10* out, void* src);
Quad_118D20* StoreQuadword(Quad_118D20* out, Quad_118D20 v);
struct __attribute__((aligned(16))) ScriptVectorRow {
    f32 v[4];               // 0x00
};
struct ScriptMatrixPayload {
    ScriptVectorRow row[4];      // 0x00
};
// The two floats of tag 0x19, copied as one 8-byte value.
struct ScriptFloatPair {
    f32 v[2];
};
void* CopyBytes(void* dst, void* src, s32 n);
Quad_118D20 ScaleQuadword(Quad_118D20 s, Quad_118D20 v);
ScriptMatrixPayload ScaleMatrix(const ScriptMatrixPayload* m, u128 s);
void StoreFloatAsQuadword(void* out, f32 f);

ScriptValue* DivideScriptValues(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    f32 n = 0.0f;
    s32 tag = args[0].tag;
    ScriptVectorRow* va = 0;
    ScriptVectorRow* vb = 0;
    s32 isInt = 0;
    ScriptFloatPair* pair = 0;
    ScriptMatrixPayload* m = 0;
    switch (tag) {
    case 0x15:
        n = args[0].f;
        isInt = 0;
        break;
    case 0x14:
        tag = 0x15;
        n = (f32)args[0].i;
        isInt = 1;
        break;
    case 0x16:
        va = (ScriptVectorRow*)AcquireVectorAPayload();
        *va = *(ScriptVectorRow*)args[0].v;
        break;
    case 0x17:
        m = (ScriptMatrixPayload*)AcquireMatrixPayload();
        *m = *(ScriptMatrixPayload*)args[0].v;
        break;
    case 0x18:
        vb = (ScriptVectorRow*)AcquireVectorBPayload();
        *vb = *(ScriptVectorRow*)args[0].v;
        break;
    case 0x19:
        pair = (ScriptFloatPair*)AcquirePairPayload();
        *pair = *(ScriptFloatPair*)args[0].v;
        break;
    }
    R11B008Node* x = 0;
    if (args[1].tag != 0) {
        x = args[1].node;
    }
    for (; x != 0; x = x->next) {
        switch (tag) {
        case 0x15:
            switch (x->tag) {
            case 0x15:
                isInt = 0;
                n /= x->f;
                break;
            case 0x14:
                n /= (f32)x->i;
                break;
            }
            break;
        case 0x16:
            switch (x->tag) {
            case 0x14: {
                Vu0::Q(*va) = Vu0::MulX(Vu0::Q(*va), Vu0::Scalar(1.0f / (f32)x->i));
                break;
            }
            case 0x15: {
                Vu0::Q(*va) = Vu0::MulX(Vu0::Q(*va), Vu0::Scalar(1.0f / x->f));
                break;
            }
            }
            break;
        case 0x17:
            switch (x->tag) {
            case 0x14: {
                ScriptMatrixPayload c;
                u128 s = Vu0::ScalarInGpr(1.0f / (f32)x->i);
                ScriptMatrixPayload r = ScaleMatrix(m, s);
                CopyBytes(&c, &r, 0x40);
                    *m = c;
                break;
            }
            case 0x15: {
                ScriptMatrixPayload c;
                u128 s = Vu0::ScalarInGpr(1.0f / x->f);
                ScriptMatrixPayload r = ScaleMatrix(m, s);
                CopyBytes(&c, &r, 0x40);
                    *m = c;
                break;
            }
            }
            break;
        case 0x18:
            switch (x->tag) {
            case 0x14: {
                Quad_118D10 t;
                StoreFloatAsQuadword(&t, 1.0f / (f32)x->i);
                Quad_118D20 tv = *(Quad_118D20*)&t;
                Quad_118D10 u;
                CopyQuadword(&u, vb);
                StoreQuadword((Quad_118D20*)vb, ScaleQuadword(tv, *(Quad_118D20*)&u));
                break;
            }
            case 0x15: {
                Quad_118D10 t;
                StoreFloatAsQuadword(&t, 1.0f / x->f);
                Quad_118D20 tv = *(Quad_118D20*)&t;
                Quad_118D10 u;
                CopyQuadword(&u, vb);
                StoreQuadword((Quad_118D20*)vb, ScaleQuadword(tv, *(Quad_118D20*)&u));
                break;
            }
            }
            break;
        case 0x19:
            switch (x->tag) {
            case 0x14: {
                f32 r = 1.0f / (f32)x->i;
                pair->v[1] *= r;
                pair->v[0] *= r;
                break;
            }
            case 0x15: {
                f32 r = 1.0f / x->f;
                pair->v[0] *= r;
                pair->v[1] *= r;
                break;
            }
            }
            break;
        }
    }
    switch (tag) {
    case 0x15:
        if (isInt) {
            SetScriptValueInt(&q, (s32)n);
        } else {
            SetScriptValueFloat(&q, n);
        }
        break;
    case 0x16:
        SetScriptValueVectorA(&q, (f32*)va);
        break;
    case 0x17:
        SetScriptValueMatrix(&q, (f32*)m);
        break;
    case 0x18:
        SetScriptValueVectorB(&q, (f32*)vb);
        break;
    case 0x19:
        SetScriptValuePair(&q, (f32*)pair);
        break;
    }
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}
