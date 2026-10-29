// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_178008 {
    u8 pad0[0x1520];
    u8 f1520[0x2768 - 0x1520];
    s32 f2768;
};

void func_001B9690(void* self);
void func_001C29E8(void* sub);

void func_00178008(Obj_178008* self)
{
    func_001B9690(self);
    func_001C29E8(self->f1520);
    self->f2768 = 0;
}

struct Obj_17ADD0 {
    u8 pad0[0x550];
    s32 f550;
};

void func_001B7968(void* self);

void func_0017ADD0(Obj_17ADD0* self)
{
    func_001B7968(self);
    self->f550 = -1;
}

struct Obj_17B510 {
    u8 pad0[0x600];
    void* f600;
    u8 f604[4];
};

s32 func_0012C918(void* a, void* b, s32 c, void* d, f32 e, f32 f);

s32 func_0017B510(Obj_17B510* self, s32 flag)
{
    void* p = 0;
    if (flag != 0) {
        p = self->f600;
    }
    return func_0012C918(p, self, 1, self->f604, 0.0f, 1.0f);
}

typedef void (*VFn_17BC20)(void* self);

struct Comp_17BC20 {
    VFn_17BC20* vtbl;
    u8 pad0[0x2D0 - 4];
    s32 f2D0;
};

struct Obj_17BC20 {
    u8 pad0[0x3C];
    s32 f3C;
    u8 pad1[0x58 - 0x40];
    Comp_17BC20* f58;
    s32 f5C;
};

void func_001E2840(void* p, s32 n);
s32 func_00182FC8(void* p);

void func_0017BC20(Obj_17BC20* self, Comp_17BC20* next)
{
    if (self->f58 != 0) {
        func_001E2840(self->f58, -1);
        self->f58->f2D0 = 0;
        if (self->f5C != 0) {
            self->f58->vtbl[7](self->f58);
        }
        self->f58 = 0;
    }
    if (next != 0) {
        self->f58 = next;
        s32 isNull = func_00182FC8(next) == 0;
        self->f5C = isNull;
        if (isNull != 0) {
            next->vtbl[6](next);
        }
        next->f2D0 = self->f3C;
        func_001E2840(next, 1);
    }
}

void func_0017B598(void* self)
{
    func_0012C918(*(void**)((u8*)self + 0x60C), self, 1, (u8*)self + 0x610, 0.0f, 1.0f);
}

extern s32 D_00263E2C;
extern s32 D_00263E30;

struct Obj_17B5D0 { u8 pad0[0x558]; s32 f558; };

void func_0017B5D0(void* self)
{
    Obj_17B5D0* o = (Obj_17B5D0*)self;
    func_001B7968(self);
    o->f558 = 0x10;
    D_00263E2C = -1;
    D_00263E30 = 0;
}

extern u8 D_00263E08[];

void func_00124A48(void* self);
void func_00124DF8(void* self, int n, void* table);

void func_0017B610(void* self)
{
    func_00124A48(self);
    func_00124DF8(self, 3, D_00263E08);
}

void func_00182C18(void* self);
void* func_0018D500(int size);

struct Obj_17B998 {
    u8 pad0[0x38];
    void* f38;
    u8 pad1[0x68 - 0x3C];
    s32 f68;
};

void func_0017B998(void* self)
{
    Obj_17B998* o = (Obj_17B998*)self;
    func_00182C18(self);
    o->f38 = func_0018D500(0xA00);
    o->f68 = 1;
}

struct Obj_0017ABD8 { u8 pad[0x6D0]; s32 flag; };

s32 func_0017ABD8(Obj_0017ABD8* self)
{
    return self->flag != 0;
}

typedef void (*Fn_0017AD50)(void* self, void* arg);

struct Obj_0017AD50 {
    Fn_0017AD50* vtbl;
    u8 pad[0x668 - 4];
    void* sub;
};

void func_001794E0(void* self, void* a, void* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);

void func_0017AD50(Obj_0017AD50* self)
{
    u8 bufA[16];
    u8 bufB[16];
    func_001794E0(self, bufA, bufB);
    func_00127E60(self->sub, 0, bufA, 0, bufB, 0);
    self->vtbl[0x84 / 4](self, bufA);
    self->vtbl[0x90 / 4](self, bufB);
}

struct Obj_0017AE00 {
    u8 pad0[0x55C];
    u8 grpA[0x24];
    f32 fA;
    u8 pad1[8];
    void* ptrA;
    f32 fB;
    u8 grpBrest[0x2C];
    void* ptrB;
    f32 fC;
    u8 grpCrest[0x38];
    void* ptrC;
};

extern u8 D_00263D58[];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void func_00139038(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void func_001399F8(void* obj, s32 a1, s32 a2, void* a3);
void func_0017B410(void* self, s32 a1);
void func_0017B510(void* self, s32 a1);

void func_0017AE00(Obj_0017AE00* self)
{
    func_00124A48(self);
    f32 one = 1.0f;
    func_00124DF8(self, 13, D_00263D58);

    func_00139038(self, 12, 4, self->grpA, 0, 0, 0, &self->ptrA);
    self->fA = one;
    func_001399F8(self->ptrA, 12, 4, self->grpA);

    func_00139038(self, 12, 4, &self->fB, 0, 0, 0, &self->ptrB);
    self->fB = one;
    func_001399F8(self->ptrB, 12, 4, &self->fB);

    func_00139038(self, 12, 5, &self->fC, 0, 0, 0, &self->ptrC);
    self->fC = one;
    func_001399F8(self->ptrC, 12, 5, &self->fC);

    func_0017B410(self, 0);
    func_0017B510(self, 1);
}

struct Msg_17B3A8 {
    u8 pad0[4];
    s32 f4;
    u8 pad1[8];
    u32 f10;
};

struct Obj_17B3A8 {
    u8 pad0[0x608];
    s32 f608;
};

extern u8 D_0026E248[];

void func_001AC060(void* p);
void func_0017B598(void* self);
void func_001837E0(void* self, s32 a, s32 b, s32 c);

s32 func_0017B3A8(Obj_17B3A8* self, Msg_17B3A8* msg)
{
    if (msg->f10 & 0x10) {
        if (msg->f4 == self->f608) {
            func_001AC060(D_0026E248);
            func_0017B598(self);
            func_001837E0(self, 2, 0, 0);
        }
    }
    return 1;
}

struct Obj_17B550 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x60C - 0x18];
    s32 f60C;
};

s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

void func_0017B550(Obj_17B550* self, s32 index)
{
    if (index == -1) {
        self->f60C = 0;
    } else {
        self->f60C = func_0015A418(self->f14, 0x101, index, self);
    }
}

struct Item_178258 { u8 pad[0x2D0]; s32 link; };
struct Owner_178258 { u8 pad0[0x2220]; s32 state; u8 pad1[0x2BE4 - 0x2224]; Item_178258* held; };

void func_00178258(Owner_178258* a0, Item_178258* a1)
{
    if (a0->state != 9 && a1->link == 0) {
        a0->held = a1;
    }
}

struct Item_178280 { u8 pad[0x2D0]; s32 link; };
struct Owner_178280 { u8 pad0[0x2220]; s32 state; u8 pad1[0x2BE8 - 0x2224]; Item_178280* held; };

void func_00178280(Owner_178280* a0, Item_178280* a1)
{
    if (a0->state != 9 && a1->link == 0) {
        a0->held = a1;
    }
}

struct Obj_1793C0 { u8 pad0[0x610]; s32 f610; };

void func_001921A8(void* self);

void func_001793C0(Obj_1793C0* self)
{
    func_001921A8(self);
    self->f610 = -1;
}

struct Obj_1793F0 { u8 pad0[0x650]; void* f650; void* f654; void* f658; u8 pad1[0x660 - 0x65C]; void* f660; u8 pad2[0x680 - 0x664]; s32 f680; f32 f684; u8 pad3[0x6C0 - 0x688]; void* f6C0; u8 pad4[0x6E8 - 0x6C4]; void* f6E8; };
struct Sub_1793F0 { u8 pad0[0xE0]; void* fE0; };
struct Packed_1793F0 { f32 v; } __attribute__((packed));

extern u8 D_00263AC8[];
extern u8 D_00270650[];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void func_0012B5B8(void* a, s32 b, s32 c);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_00139038(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void func_001399F8(void* obj, s32 a1, s32 a2, void* a3);
void func_0017ABE8(void* self, s32 a1);
s32 func_001B4688(s32 key);

void func_001793F0(Obj_1793F0* self)
{
    func_00124A48(self);
    func_00124DF8(self, 0x1A, D_00263AC8);
    func_0012B5B8(self->f6E8, self->f680, self->f680);
    ((Sub_1793F0*)self->f650)->fE0 = self->f660;
    self->f658 = func_001B6290(self->f654, self, -1, 0);
    func_00139038(self, 0xC, 5, &self->f684, 0, 0, 0, &self->f6C0);
    self->f684 = 1.0f;
    func_001399F8(self->f6C0, 0xC, 5, &self->f684);
    func_0017ABE8(self, 2);
    u8* base = D_00270650;
    ((Packed_1793F0*)(base + 0x288))->v = 0.0f;
    *(s32*)(base + 0x284) = func_001B4688(0x36A);
}

struct Obj_178038 { u8 pad0[0x1520]; u8 f1520[0x2768 - 0x1520]; };

void func_001C29E8(void* sub);
void func_00192820(void* self);

void func_00178038(Obj_178038* self)
{
    func_001C29E8(self->f1520);
    func_00192820(self);
}

struct Obj_179690 { void** vtbl; };

typedef void (*VFn_179690)(void*);

void func_001BC088(void* self, void* b);

void func_00179690(Obj_179690* self)
{
    func_001BC088(self, 0);
    VFn_179690 fn = (VFn_179690)((void**)self->vtbl)[0x58 / 4];
    if (fn != 0) fn(self);
}

void func_00192C58(void* self);
void func_0017ABE8(void* self, s32 a1);

void func_0017A6D0(void* self)
{
    func_00192C58(self);
    func_0017ABE8(self, 2);
}

struct Rec_17AB58 {
    s32 f0;
    s32 f4;
    s32 f8;
};

struct Self_17AB58 {
    u8 pad_000[0x618];
    s32 f618;
    u8 pad_61C[0x6E0 - 0x61C];
    s32 f6E0;
    u8 pad_6E4[0x70C - 0x6E4];
    s32 f70C;
};

void func_00192230(void* self, s32 kind, Rec_17AB58* rec);

void func_0017AB58(Self_17AB58* self, s32 kind, Rec_17AB58* rec)
{
    if (kind == 0x13 && rec->f0 == self->f618) {
        switch (rec->f8) {
        case 0x15E:
            self->f6E0 = 1;
            break;
        case 0x15F:
            self->f6E0 = 0;
            break;
        case 0x467:
            self->f70C = 1;
            break;
        }
    }
    func_00192230(self, kind, rec);
}

struct __attribute__((aligned(16))) Quad_178598 {
    s32 a, b, c, d;
};

struct Pair_178598 {
    Quad_178598 q0;
    Quad_178598 q1;
};

struct Sub_178598 {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1[0x20 - 0x1C];
    Quad_178598 q20;
    Quad_178598 q30;
};

typedef void (*VFn_178598)(void* self, void* a);

struct Obj_178598 {
    VFn_178598* vtbl;
    u8 pad0[0x2514 - 4];
    Sub_178598* f2514;
    u8 pad1[0x2B70 - 0x2518];
    Quad_178598 q2B70;
    Quad_178598 q2B80;
};

struct Frame_178598 {
    Quad_178598 q0;
    Quad_178598 q1;
    Quad_178598 q2;
    Quad_178598 p0;
    Quad_178598 p1;
    f32 fl;
};

void func_00178D98(void* self, s32 a1, s32 a2, void* a3, void* a4);
void func_001782C0(void* self, void* s2, f32 f, void* a2, void* a3, void* a4);
void func_00175170(void* self, s32 a, s32 b);

extern f32 D_0026185C;

void func_00178598(Obj_178598* self, Pair_178598* s2, f32 f)
{
    Frame_178598 fr;
    fr.fl = f;
    if (s2 == 0) {
        func_00178D98(self, 0, 0, &fr.p0, &fr.fl);
        s2 = (Pair_178598*)&fr.p0;
    }
    void* q1 = &fr.q1;
    func_001782C0(self, s2, fr.fl, q1, &fr.q0, &fr.q2);
    self->f2514->f18 = D_0026185C + fr.fl;
    self->f2514->q20 = fr.q0;
    self->f2514->q30 = fr.q2;
    self->vtbl[36](self, q1);
    self->q2B70 = s2->q0;
    self->q2B80 = s2->q1;
    func_00175170(self, 4, 0x2C);
}
