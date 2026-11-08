// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 628/640 (98.1%), checked 2026-11-08
// Near match: the code is the same as retail except which variable gets s3 and which gets s4
// (target and setter swapped). GCC gives the saved register to the variable with the higher
// allocation priority (uses weighted by live length); here the setter wins by a small margin.
// An empty do { } while (0) on the else arm changes that priority and matches EXACT, but it is
// an artificial barrier (AGENTS.md), so it is not kept here. Not linked.
// Still differs (2026-11-08, night-close6): setter computed before target gives retail's s3/s4 but moves the code (18 lines); target declared first, either as an if, case 0..11 apart, the conversions calling the setter in their arms: not closer.
#include "common.h"

struct Quad_001C1F20 {
    s32 w[4];
};
struct Desc_001C1F20 {
    s32 type;
    s32 flags;
    s32 pad8[3];
    s32 off;
    s32 pad18;
    void* (*getBase)(void*, s32);
};
struct Val_001C1F20 {
    s32 type;
    s32 value;
};

s32 InitScriptValue(Quad_001C1F20* q);
void AssignScriptValue(Quad_001C1F20* a, Quad_001C1F20* b);
void DestroyScriptValue(Quad_001C1F20* p, s32 mode);
void CopyConstructScriptValue(void* out, Quad_001C1F20* q);
void ConvertScriptValueToInt(Quad_001C1F20* out, Val_001C1F20* in);
void ConvertScriptValueToFloat(Quad_001C1F20* out, Val_001C1F20* src);
void StoreScriptArguments(Quad_001C1F20* t, s32 n, Val_001C1F20* c, Desc_001C1F20* z, s32* arr);

void* WritePropertyValue(void* out, void* obj, Desc_001C1F20* desc, Val_001C1F20* val)
{
    Quad_001C1F20 a;
    Quad_001C1F20 b;
    Quad_001C1F20 c;
    Quad_001C1F20 d;
    s32 arr[1];
    void (*setter)(void*, s32);
    void* target;

    InitScriptValue(&a);
    a.w[0] = 0x22;
    if (desc->flags & 0x10) {
        if (desc->flags & 0x1000)
            arr[0] = (s32)desc->getBase(obj, 1) + desc->off;
        else
            arr[0] = (s32)obj + desc->off;
        StoreScriptArguments(&b, 1, val, desc, arr);
        AssignScriptValue(&a, &b);
        DestroyScriptValue(&b, 2);
    } else {
        target = (desc->flags & 0x1000) ? desc->getBase(obj, 1) : obj;
        setter = (desc->flags & 0x20) ? (void (*)(void*, s32))desc->off
                                      : *(void (**)(void*, s32))(*(s32*)obj + desc->off);
        switch (desc->type) {
        case 5: case 6: case 7: case 8: case 14: case 15: case 16: case 17: {
            s32 v;
            if (val->type == 0x14) {
                v = val->value;
            } else {
                InitScriptValue(&b);
                ConvertScriptValueToInt(&c, val);
                AssignScriptValue(&b, &c);
                DestroyScriptValue(&c, 2);
                v = b.w[1];
                DestroyScriptValue(&b, 2);
            }
            setter(target, v);
            break;
        }
        case 1: {
            f32 f;
            if (val->type == 0x15) {
                f = *(f32*)&val->value;
            } else {
                InitScriptValue(&b);
                ConvertScriptValueToFloat(&d, val);
                AssignScriptValue(&b, &d);
                DestroyScriptValue(&d, 2);
                f = *(f32*)&b.w[1];
                DestroyScriptValue(&b, 2);
            }
            ((void (*)(void*, f32))setter)(target, f);
            break;
        }
        case 3: case 12:
        default:
            if (desc->type & 0x1000) {
        case 0: case 2: case 4: case 9: case 10: case 11:
                setter(target, val->value);
            } else if (desc->type & 0x2000) {
                setter(target, val->value);
            }
            break;
        case 13:
            break;
        }
    }
    CopyConstructScriptValue(out, &a);
    DestroyScriptValue(&a, 2);
    return out;
}
