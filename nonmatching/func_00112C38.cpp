// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1560/1544, checked 2026-11-11
// DECLS (2026-11-11, w28-nmdecls): StoreFloatAsQuadword now returns void* (its definition returns a value): 325/386 -> 326/386 (regdiff code 84.2% -> 84.5%).
// EXACT FORM, NOT LANDED (2026-11-10, maintainer's rule): wave 11 matched this function byte for byte (branch w11-112C38, commit 4ddf80ff) with DivideScriptValues' ScaledMatrix/ScriptMatrixPayload forms (landed) plus one more helper, Vu0::ScalarInGprAt (an asm `lw` of a float in memory straight into a u128 GPR, the memory twin of ScalarInGpr), used only for the matrix-times-float arm. AGENTS.md allows an asm helper only for a sequence that recurs across retail's functions; it has one site, so it was not landed. A second retail use of that lw-into-128-bit-GPR pattern would justify it.
// RECURRENCE SEARCHED (2026-11-10, w17-112C38): no second use. A scan of every `lw` in asm/us/text.s whose register then reaches por (an argument move), qmtc2, sq or a pextlw/pcpyld/pcpyud/pextuw as a 128-bit value finds only this function's 0x112F90 (lw v0, 4(s2); por a2, zero, v0); the five other hits (func_0012F210, func_00155868, func_001A01B8, func_001A09C0, func_001EC190) are false, the register redefined by a call's return or across a branch. Of ScaleMatrix's five calls (0x112E40, 0x112FA4, 0x113498, 0x1134F0, 0x15859C) only 0x112FA4 lw's its weight; the others mfc1 it. Every ScalarInGpr user (pose_source, script_machine, file_1549C8, base_object, nonmatching 001D7778, 0013A618, 00191AC8) is an mfc1 site in retail. The helper stays out.
// NEAR: MultiplyScriptValues, written as DivideScriptValues (nonmatching/func_00113240.cpp) is:
// the first switch sets the tag in each case, a number times a vector, matrix, vector B or pair
// makes that kind (the matrix through ScaleMatrix with Vu0::ScalarInGpr, the vector B through
// StoreFloatAsQuadword with x->v read before the call, as retail keeps it in s0), a matrix times a
// vector is TransformByMatrixWithW (the matrix payload freed at the end), a matrix times a matrix
// MultiplyMatrices into a copy. Frame, saved registers and the ret spill are retail's.
// Left: (1) Divide's residual, in the three ScaleMatrix arms: &r is kept in s0 for CopyBytes where
// retail forms addiu a0/a1, sp, 0x60 again. Learned here: written `*(T*)&c = ScaleMatrix(...)`,
// the call's hidden address is retail's fresh addiu (the call's force_reg pseudo is coalesced
// into a0 when nothing uses the address again); every form that passes the address on again
// (a named result, a temporary bound to a reference, a matrix class whose operator= calls
// CopyBytes, the address of the returned temporary) keeps it in s0. The compiler's own block
// move never becomes CopyBytes: a 64-byte copy at any alignment is lq/sq or ldl/ldr pieces.
// (2) A matrix times a float in memory: retail lw's the float's word straight into the 128-bit
// GPR for a2 (lw v0, 4(s2); por a2, zero, v0; sq v0, 0x50), which ScalarInGpr (lwc1, mfc1) does
// not give; it would need a GPR form of ScalarAt. (3) Block order and the cross-jumped tails
// after (1).
// W23 (2026-11-11): re-scored, unchanged (1560/1544 without the helper). The 2026-11-10 decision allows a
// new helper only with retail recurrence, and w17's scan found none; the "*r" operand does not help
// (the word must reach a GPR without an FPR, which only an asm lw or reload of a memory operand gives).
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
void* StoreFloatAsQuadword(void* out, f32 f);

void TransformByMatrixWithW(const ScriptMatrixPayload* m, const void* v, void* out, f32 w);
ScriptMatrixPayload MultiplyMatrices(const ScriptMatrixPayload* a, const void* b);
void FreeMatrixPayload(void* p);

ScriptValue* MultiplyScriptValues(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue q;
    InitScriptValue(&q);
    f32 n = 0.0f;
    s32 tag;
    s32 isInt = 0;
    ScriptVectorRow* va = 0;
    ScriptVectorRow* vb = 0;
    ScriptFloatPair* pair = 0;
    ScriptMatrixPayload* m = 0;
    switch (args[0].tag) {
    case 0x15:
        tag = 0x15;
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
        tag = 0x16;
        *va = *(ScriptVectorRow*)args[0].v;
        break;
    case 0x17:
        m = (ScriptMatrixPayload*)AcquireMatrixPayload();
        tag = 0x17;
        *m = *(ScriptMatrixPayload*)args[0].v;
        break;
    case 0x18:
        vb = (ScriptVectorRow*)AcquireVectorBPayload();
        tag = 0x18;
        *vb = *(ScriptVectorRow*)args[0].v;
        break;
    case 0x19:
        pair = (ScriptFloatPair*)AcquirePairPayload();
        tag = 0x19;
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
                n *= x->f;
                break;
            case 0x14:
                n *= (f32)x->i;
                break;
            case 0x16: {
                va = (ScriptVectorRow*)AcquireVectorAPayload();
                tag = 0x16;
                u128 k = Vu0::Scalar(n);
                Vu0::Q(*va) = Vu0::MulX(Vu0::Q(*(ScriptVectorRow*)x->v), k);
                break;
            }
            case 0x17: {
                m = (ScriptMatrixPayload*)AcquireMatrixPayload();
                tag = 0x17;
                ScriptMatrixPayload c;
                u128 s = Vu0::ScalarInGpr(n);
                ScriptMatrixPayload r = ScaleMatrix((ScriptMatrixPayload*)x->v, s);
                CopyBytes(&c, &r, 0x40);
                *m = c;
                break;
            }
            case 0x18: {
                vb = (ScriptVectorRow*)AcquireVectorBPayload();
                tag = 0x18;
                Quad_118D10 t;
                f32* p = x->v;
                StoreFloatAsQuadword(&t, n);
                Quad_118D20 tv = *(Quad_118D20*)&t;
                Quad_118D10 u;
                CopyQuadword(&u, p);
                StoreQuadword((Quad_118D20*)vb, ScaleQuadword(tv, *(Quad_118D20*)&u));
                break;
            }
            case 0x19: {
                pair = (ScriptFloatPair*)AcquirePairPayload();
                tag = 0x19;
                f32* p = x->v;
                pair->v[0] = p[0] * n;
                pair->v[1] = p[1] * n;
                break;
            }
            }
            break;
        case 0x16:
            switch (x->tag) {
            case 0x14:
                Vu0::Q(*va) = Vu0::MulX(Vu0::Q(*va), Vu0::Scalar((f32)x->i));
                break;
            case 0x15:
                Vu0::Q(*va) = Vu0::MulX(Vu0::Q(*va), Vu0::ScalarAt(x->f));
                break;
            }
            break;
        case 0x17:
            switch (x->tag) {
            case 0x14: {
                ScriptMatrixPayload c;
                u128 s = Vu0::ScalarInGpr((f32)x->i);
                ScriptMatrixPayload r = ScaleMatrix(m, s);
                CopyBytes(&c, &r, 0x40);
                *m = c;
                break;
            }
            case 0x15: {
                ScriptMatrixPayload c;
                u128 s = Vu0::ScalarInGpr(x->f);
                ScriptMatrixPayload r = ScaleMatrix(m, s);
                CopyBytes(&c, &r, 0x40);
                *m = c;
                break;
            }
            case 0x16:
                va = (ScriptVectorRow*)AcquireVectorAPayload();
                tag = 0x16;
                TransformByMatrixWithW(m, x->v, va, 1.0f);
                break;
            case 0x17: {
                ScriptMatrixPayload c;
                c = MultiplyMatrices(m, x->v);
                *m = c;
                break;
            }
            }
            break;
        case 0x18:
            switch (x->tag) {
            case 0x14: {
                Quad_118D10 t;
                StoreFloatAsQuadword(&t, (f32)x->i);
                Quad_118D20 tv = *(Quad_118D20*)&t;
                Quad_118D10 u;
                CopyQuadword(&u, vb);
                StoreQuadword((Quad_118D20*)vb, ScaleQuadword(tv, *(Quad_118D20*)&u));
                break;
            }
            case 0x15: {
                Quad_118D10 t;
                StoreFloatAsQuadword(&t, x->f);
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
                f32 k = (f32)x->i;
                pair->v[0] *= k;
                pair->v[1] *= k;
                break;
            }
            case 0x15: {
                f32 k = x->f;
                pair->v[0] *= k;
                pair->v[1] *= k;
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
        if (m != 0) {
            FreeMatrixPayload(m);
        }
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
