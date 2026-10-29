// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Glob_1481A0 {
    u8 pad0[0x19E0];
    s32 f19E0;
    s32 f19E4;
    s32 f19E8;
};
typedef Glob_1481A0 Glob_148178;

extern Glob_148178* D_002623C0;

void func_00148178(void)
{
    Glob_148178* g = D_002623C0;
    s32 r = 99;
    if (g->f19E0 + 1 <= 98) r = g->f19E0 + 1;
    g->f19E0 = r;
}


struct Self_1481A0 {
    u8 pad0[0x14];
    void* p14;
};

struct Sys_1481A0 {
    u8 pad0[0x26C];
    f32 f26C;
    u8 pad1[0x4];
    void (*fn274)(void);
    void* p278;
};

struct __attribute__((packed)) PSys_1481A0 {
    u8 pad0[0x26C];
    f32 f26C;
};

typedef void (*VFn_1481A0)(void* self);
struct VObj_1481A0 {
    VFn_1481A0* vtbl;
};

extern Glob_1481A0* D_002623C0;
extern u8 D_0026CE48[];
extern u8 D_0026C6C8[];

void func_00148038(void);
void func_00148178(void);
s32 func_00160D98(void);

void func_001481A0(void* self)
{
    Self_1481A0* s = (Self_1481A0*)self;
    Glob_1481A0* g = D_002623C0;
    s32 c = g->f19E8 + 1;
    s32 r;
    g->f19E8 = c;
    if (c >= 100) {
        r = func_00160D98();
        if (g->f19E4 < r) {
            D_002623C0->f19E8 = 0;
            ((PSys_1481A0*)D_0026CE48)->f26C = 250.0f;
            ((Sys_1481A0*)D_0026CE48)->fn274 = func_00148038;
            ((Sys_1481A0*)D_0026CE48)->p278 = s->p14;
            return;
        }
        if (D_002623C0->f19E0 < 99) {
            D_002623C0->f19E8 = 0;
            ((Sys_1481A0*)D_0026CE48)->f26C = 250.0f;
            ((Sys_1481A0*)D_0026CE48)->p278 = 0;
            ((Sys_1481A0*)D_0026CE48)->fn274 = func_00148178;
            {
                VObj_1481A0* obj = (VObj_1481A0*)D_0026C6C8;
                obj->vtbl[14](obj);
            }
        } else {
            D_002623C0->f19E8 = 99;
        }
    }
}
