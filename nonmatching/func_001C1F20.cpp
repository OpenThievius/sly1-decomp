// SPDX-License-Identifier: AGPL-3.0-or-later
// Near match: the code is the same as retail except which variable gets s3 and which gets s4
// (target and setter swapped). GCC gives the saved register to the variable with the higher
// allocation priority (uses weighted by live length); here the setter wins by a small margin.
// An empty do { } while (0) on the else arm changes that priority and matches EXACT, but it is
// an artificial barrier (AGENTS.md), so it is not kept here. Not linked.
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

s32 func_0011B008(Quad_001C1F20* q);
void func_0011B0A8(Quad_001C1F20* a, Quad_001C1F20* b);
void func_0011B060(Quad_001C1F20* p, s32 mode);
void func_0011B018(void* out, Quad_001C1F20* q);
void func_0011B928(Quad_001C1F20* out, Val_001C1F20* in);
void func_0011B9A8(Quad_001C1F20* out, Val_001C1F20* src);
void func_001C1BF8(Quad_001C1F20* t, s32 n, Val_001C1F20* c, Desc_001C1F20* z, s32* arr);

void* func_001C1F20(void* out, void* obj, Desc_001C1F20* desc, Val_001C1F20* val)
{
    Quad_001C1F20 a;
    Quad_001C1F20 b;
    Quad_001C1F20 c;
    Quad_001C1F20 d;
    s32 arr[1];
    void (*setter)(void*, s32);
    void* target;

    func_0011B008(&a);
    a.w[0] = 0x22;
    if (desc->flags & 0x10) {
        if (desc->flags & 0x1000)
            arr[0] = (s32)desc->getBase(obj, 1) + desc->off;
        else
            arr[0] = (s32)obj + desc->off;
        func_001C1BF8(&b, 1, val, desc, arr);
        func_0011B0A8(&a, &b);
        func_0011B060(&b, 2);
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
                func_0011B008(&b);
                func_0011B928(&c, val);
                func_0011B0A8(&b, &c);
                func_0011B060(&c, 2);
                v = b.w[1];
                func_0011B060(&b, 2);
            }
            setter(target, v);
            break;
        }
        case 1: {
            f32 f;
            if (val->type == 0x15) {
                f = *(f32*)&val->value;
            } else {
                func_0011B008(&b);
                func_0011B9A8(&d, val);
                func_0011B0A8(&b, &d);
                func_0011B060(&d, 2);
                f = *(f32*)&b.w[1];
                func_0011B060(&b, 2);
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
    func_0011B018(out, &a);
    func_0011B060(&a, 2);
    return out;
}
