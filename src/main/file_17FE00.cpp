// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "c7e.h"
#include "c8e.h"



void func_00182C18(void* self);



// Built at startup: the compiler's initialiser and constructor for this file are func_00180E38
// and func_00180E90 (config/us/generated.tsv).
struct Clr_180E38 {
    u8 r, g, b, a;
    Clr_180E38(u8 r_, u8 g_, u8 b_, u8 a_) : r(r_), g(g_), b(b_), a(a_) {}
};
Clr_180E38 D_00264098(0xBF, 0xBF, 0xBF, 0x7F);
Clr_180E38 D_002640A0(0x00, 0x87, 0xFF, 0x7F);
void* D_002640A4;

void func_001830D8(void* self);



void func_00182C58(void* self);
s32 func_0015A418(void* ref, s32 mode, s32 key, void* self);



// NEAR: only li s8,12 / ori s7 (pre-loop hoist order) swapped; the rest matches

void func_0011EC40(C01* o, Stream8E* r);
s32 func_00137BE0(Stream8E* r);
f32 func_00137DF8(Stream8E* r);
Pt8E* func_0018D5C0(s32 bytes);
Ent8E* func_0018D500(s32 bytes);
Col8E* func_001B4688(s32 key);









typedef int V128_180108 __attribute__((mode(TI)));

struct Pkt_180108 {
    u8 pad[1];
};

struct Mesh_180108 {
    s32 count;
    s32 pad4;
};

struct Group_180108 {
    s32 pad0;
    s32 n;
    Mesh_180108* tris;
};

struct Obj_180108 {
    u8 pad00[0x38];
    V128_180108* verts;
    u8 pad3C[0x28];
    Group_180108 groups[5];
};

struct Col_180108 {
    u8 r, g, b, a;
};

union Q_180108 {
    V128_180108 v;
    f32 f[4];
};

extern Pkt_180108 D_00262280;

void func_0018A008(s32 zero, void* out, f32 v);
void func_001613C0(Pkt_180108* p, s32 a, s32 b, u64 c);
void func_00161708(Pkt_180108* p, s32 a, u64 v);
void func_00161458(Pkt_180108* p, u32 c);
void func_001615F0(Pkt_180108* p, s32 a, s32 b, s32 c, s32 d);
V128_180108 func_00188740(void* m, V128_180108 v);

void func_00180108(Obj_180108* self, f32 a, f32 b, f32 c, f32 d);

void func_0017FE00(C80* self)
{
    Keep7E tmp = self->keep;
    func_001830D8(self);
    self->keep = tmp;
}

void func_0017FE48(C80* self)
{
    func_00182C58(self);
    if (self->id5C != -1) {
        self->found60 = func_0015A418(self->world, 0x104, self->id5C, self);
    }
}

void func_0017FE90(C8E* self)
{
    func_00182C18(self);
    D_002640A4 = self;
}

void func_0017FEC0(C8E* self, Stream8E* rd)
{
    s32 i;
    s32 m;
    s32 j;
    s32 k;

    func_0011EC40(self, rd);
    self->f34 = func_00137BE0(rd);
    self->f38 = func_0018D5C0(self->f34 << 4);
    for (i = 0; i < self->f34; i++) {
        self->f38[i].x = func_00137DF8(rd);
        self->f38[i].y = -func_00137DF8(rd);
        self->f38[i].w = 1.0f;
    }
    self->f40 = func_00137DF8(rd);
    self->f44 = func_00137DF8(rd);
    self->f4C = 1.0f;
    self->f50 = func_00137DF8(rd);
    self->f54 = func_00137DF8(rd);
    self->f60 = self->f50 - self->f40;
    self->f5C = 1.0f;
    m = 0;
    for (; m < 5; m++) {
        Col8E* p = func_001B4688(m + 0x48E);
        Rec8E* r = &self->recs[m];
        if (p != 0) {
            r->col = p[1];
            for (k = 0; k < 4; k++) {
                r->col.c[k] = (r->col.c[k] + 1) >> 1;
            }
        } else {
            Col8E d;
            *(u32*)&d = 0x80808080;
            r->col = d;
        }
        r->n = func_00137BE0(rd);
        r->ents = func_0018D500(r->n * 12);
        for (j = 0; j < r->n; j++) {
            Ent8E* e = &r->ents[j];
            e->a = func_00137BE0(rd);
            e->b = func_00137BE0(rd);
            e->c = func_00137BE0(rd);
        }
    }
}

void func_00180108(Obj_180108* self, f32 a, f32 b, f32 c, f32 d)
{
    f32 sp[16];
    Col_180108 col;
    Q_180108 vv, q;
    s32 g;
    func_0018A008(0, sp, c);
    sp[12] = a;
    sp[13] = b;
    func_001613C0(&D_00262280, 0, 1, 0xE);
    func_00161708(&D_00262280, 0x47, 0x31001);
    func_00161708(&D_00262280, 0x42, 0x44);
    for (g = 4; g > 0; g--) {
        Group_180108* grp = &self->groups[g];
        if (grp->n > 0) {
            func_001613C0(&D_00262280, 0, 1, 1);
            col = *(Col_180108*)((u32)(g - 3) < 2 ? &D_00264098 : &D_002640A0);
            col.a = (u8)(s32)((f32)col.a * d);
            func_00161458(&D_00262280, *(u32*)&col);
            func_001613C0(&D_00262280, (s8)col.a >= 0 ? 0x43 : 0x83, 1, 4);
            {
                s32 i;
                for (i = 0; i < grp->n; i++) {
                    u32* idx = (u32*)((u8*)grp->tris + i * 12);
                    s32 j;
                    for (j = 2; j >= 0; j--) {
                        vv.v = self->verts[*idx++];
                        q.v = func_00188740(sp, vv.v);
                        func_001615F0(&D_00262280, (s32)((q.f[0] + 1728.0f) * 16.0f), (s32)((q.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
                    }
                }
            }
        }
    }
}

INCLUDE_ASM(func_00180398);


