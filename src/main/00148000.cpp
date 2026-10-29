// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Glob_1481A0 {
    u8 pad0[0x19D8];
    s32 f19D8;
    s32 f19DC;
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

typedef void (*VFn_148CE0)(void* self, s32 arg);

struct Node_148CE0 {
    VFn_148CE0* vtbl;
    u8 pad0[0x374 - 4];
    Node_148CE0* next;
};

struct Self_148CE0 {
    u8 pad0[0x1C54];
    Node_148CE0* first;
};

typedef Glob_1481A0 Glob_148CE0;

extern s32 D_0026EC58;

s32 func_001300E8(void* node, s32 kind);

void func_00148CE0(Self_148CE0* self)
{
    Glob_148CE0* g = D_002623C0;
    if (((g->f19D8 << 8) | g->f19DC) == 0x308) return;
    s32 r = func_00160D98();
    if (g->f19E4 < r) {
        if (D_0026EC58 < 2) return;
    }
    Node_148CE0* p = self->first;
    if (p == 0) return;
    do {
        if (func_001300E8(p, 0x56) != 0) {
            p->vtbl[51](p, 2);
        }
        p = p->next;
    } while (p != 0);
}

typedef void (*VFn_148E18)(void* self, s32 arg);

struct Obj_148E18 {
    VFn_148E18* vtbl;
};

void func_00148E18(Obj_148E18* self)
{
    self->vtbl[51](self, 2);
}

typedef void (*VFn_14ADE0)(void* self);

struct Elem_14ADE0 {
    VFn_14ADE0* vtbl;
    u8 pad004[0x21C - 0x004];
    f32 f21C;
    f32 f220;
    u8 pad224[0x238 - 0x224];
    f32 f238;
    f32 f23C;
    u8 pad240[0x260 - 0x240];
};

struct Obj_14ADE0 {
    VFn_14ADE0* vtbl;
    u8 pad004[0x21C - 0x004];
    f32 f21C;
    f32 f220;
    u8 pad224[0x260 - 0x224];
    s32 count;
    Elem_14ADE0 items[1];
};

extern s32 D_00275BEC;
extern f32 D_00261850;

void func_0014ADE0(Obj_14ADE0* self)
{
    if (D_00275BEC == 1) {
        f32 acc = self->f220;
        s32 i;
        for (i = 0; i < self->count; i++) {
            Elem_14ADE0* e = &self->items[i];
            f32 saved = e->f23C;
            f32 base = self->f21C;
            f32 scaled = saved * D_00261850;
            e->f220 = acc;
            e->f21C = base;
            e->f23C = scaled;
            e->vtbl[9](e);
            e->f23C = saved;
            acc += e->f238;
        }
    }
}

typedef void (*VFn_14AEA0)(void* self, s32 arg);

struct Pair_14AEA0 {
    f32 a;
    f32 b;
};

struct Q_14AEA0 {
    u8 pad000[0x08];
    s32 v08;
    u8 pad00C[0x48 - 0x0C];
    f32 f48;
};

struct Obj_14AEA0 {
    VFn_14AEA0* vtbl;
    Q_14AEA0* q;
    u8 pad008[0x218 - 0x08];
    Pair_14AEA0* pair;
    u8 pad21C[0x234 - 0x21C];
    f32 f234;
    u8 pad238[0x260 - 0x238];
    s32 count;
};

void func_001AAB20(Obj_14AEA0* self, f32 a, f32 b);

void func_0014AEA0(Obj_14AEA0* self, s32 n, f32 x, f32 y)
{
    self->pair->a = x;
    self->pair->b = y;
    self->count = n;
    Q_14AEA0* q = self->q;
    func_001AAB20(self, self->f234, (f32)q->v08 * q->f48 * (f32)n);
    self->vtbl[16](self, 2);
}

typedef void (*VFn_14AF10)(void* self, s32 arg);

struct Obj_14AF10 {
    VFn_14AF10* vtbl;
};

void func_0014AF10(Obj_14AF10* self)
{
    self->vtbl[16](self, 0);
}
