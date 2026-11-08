// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 702/716 (98.0%), checked 2026-11-08
// NEAR: the scalar, vector and matrix bodies are retail's (registers included); left: the order of the first loads and of move s1,zero (retail loads args[1].tag and args[0].tag before it, it fills the branch delay slot) and, with it, the order of the prologue saves of ra and s1.
// Night-close2 (2026-11-08): n = 0 first, tag after, a ternary, the arms swapped and switch on args[0].tag give 5 to 8 words; retail's args[1].tag load comes first with move s1,zero in the delay slot.
// Still differs (2026-11-08, night-close5): n = 0 before, between or after the tag reads, and the tags in locals, leave move s1,zero after the call (sched2), not in beqz's delay slot; func_00112698 has the same three words.
#include "common.h"
#include "script_value.h"
#include "shapes.h"
#include "placed_object.h"
#include "vu0.h"
struct ScriptScope;
void SetScriptValueInt(ScriptValue* v, s32 n);
void SetScriptValueFloat(ScriptValue* v, f32 f);
void SetScriptValueVectorA(ScriptValue* v, f32* p);
void SetScriptValueMatrix(ScriptValue* v, f32* p);
f32* AcquireVectorAPayload(void);
f32* AcquireMatrixPayload(void);

ScriptValue* SubtractScriptValues(ScriptValue* ret, s32 count, ScriptValue* args, ScriptScope* scope)
{
    ScriptValue t;
    InitScriptValue(&t);
    s32 tag = args[0].tag;
    R11B008Node* n;
    if (args[1].tag != 0) {
        n = args[1].node;
    } else {
        n = 0;
    }
    switch (tag) {
    case 0x14:
    case 0x15: {
        s32 isInt;
        f32 sum;
        if (args[0].tag == 0x14) {
            sum = (f32)args[0].i;
            isInt = 1;
        } else {
            sum = args[0].f;
            isInt = 0;
        }
        for (; n != 0; n = n->next) {
            if (n->tag == 0x14) {
                sum = sum - (f32)n->i;
            } else {
                isInt = 0;
                sum = sum - n->f;
            }
        }
        if (isInt != 0) {
            SetScriptValueInt(&t, (s32)sum);
        } else {
            SetScriptValueFloat(&t, sum);
        }
        break;
    }
    case 0x16: {
        Vec02* v = (Vec02*)AcquireVectorAPayload();
        *v = *(Vec02*)args[0].v;
        for (; n != 0; n = n->next) {
            Vu0::Q(*v) = Vu0::Sub(Vu0::Q(*v), Vu0::Q(*(Vec02*)n->v));
        }
        SetScriptValueVectorA(&t, (f32*)v);
        break;
    }
    case 0x17: {
        Mat4A* m = (Mat4A*)AcquireMatrixPayload();
        *m = *(Mat4A*)args[0].v;
        for (; n != 0; n = n->next) {
            f32* src = n->v;
            ((f32*)m)[0] = ((f32*)m)[0] - src[0];
            ((f32*)m)[1] = ((f32*)m)[1] - src[1];
            ((f32*)m)[2] = ((f32*)m)[2] - src[2];
            ((f32*)m)[3] = ((f32*)m)[3] - src[3];
            ((f32*)m)[4] = ((f32*)m)[4] - src[4];
            ((f32*)m)[5] = ((f32*)m)[5] - src[5];
            ((f32*)m)[6] = ((f32*)m)[6] - src[6];
            ((f32*)m)[7] = ((f32*)m)[7] - src[7];
            ((f32*)m)[8] = ((f32*)m)[8] - src[8];
            ((f32*)m)[9] = ((f32*)m)[9] - src[9];
            ((f32*)m)[10] = ((f32*)m)[10] - src[10];
            ((f32*)m)[11] = ((f32*)m)[11] - src[11];
            ((f32*)m)[12] = ((f32*)m)[12] - src[12];
            ((f32*)m)[13] = ((f32*)m)[13] - src[13];
            ((f32*)m)[14] = ((f32*)m)[14] - src[14];
            ((f32*)m)[15] = ((f32*)m)[15] - src[15];
        }
        SetScriptValueMatrix(&t, (f32*)m);
        break;
    }
    }
    CopyConstructScriptValue(ret, &t);
    DestroyScriptValue(&t, 2);
    return ret;
}
