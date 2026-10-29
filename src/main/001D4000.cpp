// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

typedef void (*VFn_D5418)(void* self);
struct Obj_D5418 {
    VFn_D5418* vtbl;
};

s32 func_00160C58(void* a);
void func_00175170(void* a, s32 b, s32 c);

void func_001D5418(Obj_D5418* a0)
{
    if (func_00160C58(a0)) {
        a0->vtbl[84](a0);
    } else {
        func_00175170(a0, 4, 0x2D);
    }
}

extern f32 D_00261858[];

typedef void (*VFnA)(void* self);
typedef void (*VFnB)(void* self, void* arg);

struct Node_1D6CB0 {
    void** vtbl;
};

struct Obj_1D6CB0 {
    void** vtbl;
    u8 pad4[0x68C];
    f32 f690;
    s32 f694;
};

struct Owner_1D6CB0 {
    u8 pad0[0x1504];
    Node_1D6CB0* fallback;
    Node_1D6CB0* slots[4];
    Obj_1D6CB0* obj;
};

s32 func_00182FC8(void* node);

void func_001D6CB0(Owner_1D6CB0* self)
{
    Obj_1D6CB0* obj = self->obj;
    if (obj != 0) {
        Node_1D6CB0* s0 = 0;
        u32 i = 0;
        while (i < 4) {
            s0 = self->slots[i];
            if (s0 != 0 && func_00182FC8(s0) != 0) {
                break;
            }
            i++;
        }
        if (i >= 4) {
            s0 = self->fallback;
        }
        ((VFnA)obj->vtbl[6])(obj);
        ((VFnB)obj->vtbl[25])(obj, 0);
        ((VFnB)obj->vtbl[35])(obj, s0);
        obj->f690 = D_00261858[1];
        obj->f694 = 1;
        if (s0 != self->fallback) {
            ((VFnA)s0->vtbl[7])(s0);
        }
    }
}

extern s32 D_00262E10;

s32 func_001B8A08(void* self, s32 value);

s32 func_001D6DA0(void* self, s32 value)
{
    if (value == D_00262E10) {
        return 1;
    }
    return func_001B8A08(self, value);
}

struct Obj_1D7018 {
    u8 pad0[0x694];
    s32 f694;
};

void func_0013BA70(void* self);

void func_001D7018(Obj_1D7018* self)
{
    func_0013BA70(self);
    self->f694 = 0;
}

struct Node_1D7100 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
};

Node_1D7100* func_001D7100(Node_1D7100* self, s32 value)
{
    self->fC = value;
    self->f0 = 0;
    self->f4 = 0;
    self->f8 = 0;
    self->f10 = 0;
    self->f14 = 0;
    return self;
}
