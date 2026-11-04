// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c05.h"
#include "c4a.h"
#include "c4b.h"
#include "c8f.h"

void func_001B9690(void* self);
void func_001C29E8(void* sub);

void func_00178008(C07* self)
{
    func_001B9690(self);
    func_001C29E8(self->f1520);
    self->f2768 = 0;
}

void func_001B7968(void* self);

void func_0017ADD0(C4A* self)
{
    func_001B7968(self);
    self->mode = -1;
}

s32 func_0012C918(void* a, void* b, s32 c, void* d, f32 e, f32 f);

s32 func_0017B510(C4A* self, s32 flag)
{
    void* p = 0;
    if (flag != 0) {
        p = self->ptrC;
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

void func_0017B598(C4A* self)
{
    func_0012C918(self->f60C, self, 1, self->f610, 0.0f, 1.0f);
}

extern s32 D_00263E2C;
s32 D_00263E30 = 0;

void func_0017B5D0(C4B* self)
{
    func_001B7968(self);
    self->n558 = 0x10;
    D_00263E2C = -1;
    D_00263E30 = 0;
}

struct Entry_263E08 { s32 kind; s32 id; s32 offset; };
extern Entry_263E08 D_00263E08[];

void func_00124A48(void* self);
void func_00124DF8(void* self, int n, void* table);

void func_0017B610(C4B* self)
{
    func_00124A48(self);
    func_00124DF8(self, 3, D_00263E08);
}

void func_00182C18(void* self);
void* func_0018D500(int size);

void func_0017B998(C8F* self)
{
    func_00182C18(self);
    self->buffer = func_0018D500(0xA00);
    self->flag68 = 1;
}

s32 func_0017ABD8(C1B* self)
{
    return self->f6D0 != 0;
}

void func_001794E0(void* self, void* a, void* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);

void func_0017AD50(C1B* self)
{
    u8 bufA[16];
    u8 bufB[16];
    func_001794E0(self, bufA, bufB);
    func_00127E60(self->f668, 0, bufA, 0, bufB, 0);
    self->desc02()->m1D(self, (Vec02*)bufA);
    self->desc02()->m20(self, (Vec02*)bufB);
}

struct Entry_263D58 { s32 kind; s32 id; s32 offset; };
extern Entry_263D58 D_00263D58[];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void func_00139038(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void func_001399F8(void* obj, s32 a1, s32 a2, void* a3);
void func_0017B410(C4A* self, s32 a1);
s32 func_0017B510(C4A* self, s32 a1);

void func_0017AE00(C4A* self)
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

extern u8 D_0026E248[];

void func_001AC060(void* p);
void func_0017B598(C4A* self);
void func_001837E0(void* self, s32 a, s32 b, s32 c);

s32 func_0017B3A8(C4A* self, Msg_17B3A8* msg)
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

s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

void func_0017B550(C4A* self, s32 index)
{
    if (index == -1) {
        self->f60C = 0;
    } else {
        self->f60C = (void*)func_0015A418(self->world, 0x101, index, self);
    }
}

struct Item_178258 { u8 pad[0x2D0]; s32 link; };

void func_00178258(C07* a0, Item_178258* a1)
{
    if (a0->f2220 != 9 && a1->link == 0) {
        a0->f2BE4 = a1;
    }
}

struct Item_178280 { u8 pad[0x2D0]; s32 link; };

void func_00178280(C07* a0, Item_178280* a1)
{
    if (a0->f2220 != 9 && a1->link == 0) {
        a0->f2BE8 = a1;
    }
}

void func_001921A8(void* self);

void func_001793C0(C1B* self)
{
    func_001921A8(self);
    self->f610 = -1;
}

struct Sub_1793F0 { u8 pad0[0xE0]; void* fE0; };
struct Packed_1793F0 { f32 v; } __attribute__((packed));

struct Entry_263AC8 { s32 kind; s32 id; s32 offset; };
extern Entry_263AC8 D_00263AC8[];
extern u8 D_00270650[];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void func_0012B5B8(void* a, s32 b, s32 c);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_00139038(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void func_001399F8(void* obj, s32 a1, s32 a2, void* a3);
void func_0017ABE8(void* self, s32 a1);
s32 func_001B4688(s32 key);

void func_001793F0(C1B* self)
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

void func_001C29E8(void* sub);
void func_00192820(void* self);

void func_00178038(C07* self)
{
    func_001C29E8(self->f1520);
    func_00192820(self);
}

typedef void (*VFn_179690)(void*);

void func_001BC088(void* self, void* b);

void func_00179690(C1B* self)
{
    func_001BC088(self, 0);
    VFn_179690 fn = (VFn_179690)((void**)((void**)self->desc))[0x58 / 4];
    if (fn != 0) fn(self);
}

void func_00192C58(void* self);
void func_0017ABE8(void* self, s32 a1);

void func_0017A6D0(C1B* self)
{
    func_00192C58(self);
    func_0017ABE8(self, 2);
}

struct Rec_17AB58 {
    s32 f0;
    s32 f4;
    s32 f8;
};

void func_00192230(void* self, s32 kind, Rec_17AB58* rec);

void func_0017AB58(C1B* self, s32 kind, Rec_17AB58* rec)
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

void func_00178598(C07* self, Pair_178598* s2, f32 f)
{
    Frame_178598 fr;
    fr.fl = f;
    if (s2 == 0) {
        func_00178D98(self, 0, 0, &fr.p0, &fr.fl);
        s2 = (Pair_178598*)&fr.p0;
    }
    void* q1 = &fr.q1;
    func_001782C0(self, s2, fr.fl, q1, &fr.q0, &fr.q2);
    ((Sub_178598*)self->f2514)->f18 = D_0026185C + fr.fl;
    ((Sub_178598*)self->f2514)->q20 = fr.q0;
    ((Sub_178598*)self->f2514)->q30 = fr.q2;
    self->desc02()->m20(self, (Vec02*)q1);
    self->q2B70[0] = *(Vec02*)&s2->q0;
    self->q2B70[1] = *(Vec02*)&s2->q1;

    func_00175170(self, 4, 0x2C);
}

// NEAR: the float store of f6D4 is scheduled before the li/sw of f6D0; retail stores f6D0 first

typedef s32 (*VFn_17AA40_A)(void* self, s32 v);
typedef void (*VFn_17AA40_B)(void* self, void* p);
typedef void (*VFn_17AA40_C)(void* self, s32 a, void* b);

struct Msg_17AA40 {
    void* self;
    s32 v;
};

s32 func_00160C58(void);
void func_001794E0(void* self, void* a, void* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void func_0017ABE8(void* self, s32 a1);

extern f32 D_0026185C;

s32 func_0017AA40(C1B* self, s32* arg)
{
    u8 bufA[16];
    u8 bufB[16];

    if (((VFn_17AA40_A)((void**)self->desc)[79])(self, *arg) != 0) {
        return 0;
    }
    if (func_00160C58() != 0) {
        self->f6D0 = 1;
        self->f6D4 = *(f32*)&D_0026185C;
    }
    if (self->f6D0 != 0) {
        self->f704 = 0;
        self->f708 = 3.0f;
        func_001794E0(self, bufA, bufB);
        func_00127E60(self->f668, 0, bufA, 0, bufB, 0);
        ((VFn_17AA40_B)((void**)self->desc)[36])(self, bufB);
    }
    if (func_00160C58() != 0) {
        func_0017ABE8(self, 3);
    } else {
        func_0017ABE8(self, 4);
    }
    {
        Msg_17AA40* m = (Msg_17AA40*)bufA;
        m->self = self;
        m->v = arg[1];
        ((VFn_17AA40_C)((void**)self->desc)[18])(self, 0x17, bufA);
    }
    return 1;
}

// NEAR: 0x558 clamp uses movz with the operand order ours does not reproduce; msg->f0C mask load goes to the other register

struct Msg_17B7A8 {
    u8 pad0[0xC];
    s32 f0C;
    s32 f10;
};

struct Vis_17B7A8 {
    u8 pad0[0x223C];
    s32 f223C;
};

extern u8 D_0026E248[];
extern void* D_00262E10;
extern s32 D_00263E2C;

void func_001AC060(void* p);
void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_0012C918(void* a, C4B* b, s32 c, void* d, f32 e, f32 f);
s32 func_001BC320(void* self, Msg_17B7A8* msg);

s32 func_0017B7A8(C4B* self, Msg_17B7A8* msg)
{
    void* p;
    if (msg->f0C & 0x20) {
        s32 n = self->n558 - 1;
        s32 pos = (0 < n);
        self->n558 = pos ? n : 0;
        func_001AC060(D_0026E248);
        if (self->n558 == 0) {
            D_00263E2C = 2;
            p = 0;
        } else {
            s32 flags = msg->f10;
            if (flags & 2) {
                if (D_00262E10 == 0) {
                    p = self->f55C;
                } else {
                    s32 t = ((Vis_17B7A8*)D_00262E10)->f223C;
                    if (t == 4 || t == 6) {
                        p = self->f55C;
                    } else {
                        p = self->f560;
                    }
                }
            } else if (flags & 4) {
                p = self->f564;
            } else {
                p = self->f55C;
            }
        }
        func_0012C918(p, self, 1, &self->f568, 0.0f, 1.0f);
        msg->f0C &= ~0x20;
        func_001837E0(self, 2, 0, 0);
    }
    return func_001BC320(self, msg);
}

struct __attribute__((aligned(16))) Quad_17B9D0 { f32 v[4]; };

struct Vt_17B9D0
{
    u8 pad0[0x28];
    void (*f28)(void* self, Quad_17B9D0* a, s32 b, Quad_17B9D0* c, Quad_17B9D0* d, s32 e, s32 f);
};

struct Node_17B9D0
{
    u8 pad0[0x18];
    void* f18;
    u8 pad1c[0x18];
    struct { Vt_17B9D0* vt; }* f34;
    u8 pad38[0x108];
    Quad_17B9D0 f140;
};

struct Self_17B9D0
{
    u8 pad0[0x3C];
    u8* f3C;
};

s32 func_001300E8(Node_17B9D0* n, s32 kind);
void func_001920B0(Node_17B9D0* n, Quad_17B9D0* out);
void func_001F3BD8(Node_17B9D0* n, Quad_17B9D0* out);
void func_001F3C08(Node_17B9D0* n, Quad_17B9D0* out);
f32 func_00205778(f32 a, f32 b);
void func_00128018(void* a, void* b, void* c, Quad_17B9D0* d);
void func_001280C0(void* a, void* b, Quad_17B9D0* c, Quad_17B9D0* d);

void func_0017B9D0(Self_17B9D0* self, Node_17B9D0* n, Quad_17B9D0* out, f32* outf)
{
    Quad_17B9D0 v;
    Quad_17B9D0 a;
    Quad_17B9D0 b;
    Quad_17B9D0 c;
    u8* s1 = self->f3C;
    f32 r;

    if (n == 0)
    {
        goto tail;
    }
    if (func_001300E8(n, 0x7E))
    {
        func_001920B0(n, &v);
        r = *(f32*)(s1 + 0x638);
    }
    else if (func_001300E8(n, 0x73))
    {
        func_001F3BD8(n, &v);
        func_001F3C08(n, &a);
        r = func_00205778(a.v[1], a.v[0]);
    }
    else if (func_001300E8(n, 0x6E))
    {
        func_00128018(0, n->f18, s1 + 0x100, &a);
        {
            void (*fn)(void*, Quad_17B9D0*, s32, Quad_17B9D0*, Quad_17B9D0*, s32, s32) =
                (void (*)(void*, Quad_17B9D0*, s32, Quad_17B9D0*, Quad_17B9D0*, s32, s32))n->f34->vt->f28;
            if (fn)
            {
                fn(n->f34, &a, 0, &a, &b, 0, 0);
            }
        }
        func_00128018(n->f18, 0, &a, &v);
        func_001280C0(n->f18, 0, &b, &c);
        r = func_00205778(c.v[1], c.v[0]);
    }
    else if (func_001300E8(n, 2))
    {
        v = n->f140;
        r = func_00205778(((f32*)n)[0x114 / 4], ((f32*)n)[0x110 / 4]);
    }
    else
    {
    tail:
        v = *(Quad_17B9D0*)(s1 + 0x100);
        v.v[2] -= 75.0f;
        r = *(f32*)(s1 + 0x638);
    }
    if (out)
    {
        *out = v;
    }
    if (outf)
    {
        *outf = r;
    }
}

// Matches retail's bytes (EXACT us and eu): the call result is tested directly with a goto to the zero return.

struct Ptr_17A9E0;
s32 func_001DDA80(Ptr_17A9E0* p);
s32 func_0017A9E0(C1B* self, s32 a1)
{
    if (a1 == 5) goto one;
    if (self->f610 == 3) goto one;
    if (self->f610 == 0) goto one;
    if (self->f610 == 4) goto one;
    if (self->f6D0 != 0) goto one;
    if (func_001DDA80((Ptr_17A9E0*)self->world) == 0) goto zero;
one:
    return 1;
zero:
    return 0;
}

struct Pair_1781E0 { s32 a, b; };

void func_001B6598(void* ptr, s32* out);
void func_001B6568(void* ptr, s32* out);

void func_001781E0(u8* self, u8* other)
{
    Pair_1781E0 r;
    if (*(s32*)(self + 0x2220) != 9) {
        func_001B6598(*(void**)(other + 0x2D8), &r.a);
        func_001B6568(*(void**)(other + 0x2D8), &r.b);
        if (r.a == 0x22E && (r.b == r.a || r.b == -1)) {
            *(u8**)(self + 0x2BE0) = other;
        }
    }
}

typedef void (*Fn_17B410)(void* self);

struct Sys_17B410 {
    Fn_17B410* vtbl;
    u8 pad0[0x260 - 4];
    s32 f260;
    s32 f264;
    u8 pad1[0x26C - 0x268];
    s32 f26C;
    s32 f270;
    s32 f274;
    f32 f278;
};

extern u8 D_0026E248[];
extern f32 D_0026185C;

void func_001DDC38(void* a, void* b);
s32 func_0012C918(void* a, void* b, s32 c, void* d, f32 e, f32 f);

void func_0017B410(C4A* self, s32 mode)
{
    void* x;
    if (mode == self->mode) {
        goto done;
    }
    x = 0;
    if (mode != 0) {
        if (mode == 1) {
            x = self->ptrB;
        }
    } else {
        x = self->ptrA;
    }
    if (mode >= 0) {
        if (mode < 2) {
            Sys_17B410* sys = (Sys_17B410*)D_0026E248;
            sys->f278 = 1.0f;
            sys->f26C = sys->f260;
            sys->f270 = sys->f264;
            sys->f274 = 0;
            func_001DDC38(self->world, self);
        } else if (mode < 4) {
            Sys_17B410* sys = (Sys_17B410*)D_0026E248;
            sys->vtbl[15](sys);
            func_001DDC38(self->world, 0);
        }
    }
    (void)func_0012C918(x, self, 1, self->f558, 0.0f, 1.0f);
    *(s32*)((u8*)self + 0x550) = mode;
    self->f554 = D_0026185C;
done:
    return;
}

extern s32 D_00263E2C;
extern s32 D_00263E30;
f32 D_00263E04 = 3.0f;
extern f32 D_0026185C;

void func_001B93F8(void* self);
void func_0012E760(void* p);
void func_0017B8C0(void* self, s32 state);
void func_00160578(s32 n);

void func_0017B648(C4B* self)
{
    Sub4B* p;

    func_001B93F8(self);
    p = self->f568;
    if (p != 0) {
        if (p->f18 == 0.0f) {
            func_0012E760(p);
            self->f568 = 0;
        }
    }
    if (D_00263E2C != -1) {
        func_0017B8C0(self, D_00263E2C);
    }
    if (self->mode == 2) {
        if (D_00263E04 < D_0026185C - self->f554) {
            if (D_00263E30 == 0) {
                D_00263E30 = 1;
                func_00160578(2);
            }
        }
    }
}

typedef void (*Fn_0017B308)(void* self);

struct Mgr_0017B308 { Fn_0017B308* vtbl; };
extern s32 D_00270458;
extern s32 D_00270B54;
extern s32 D_002717CC;
s32 func_001E9970(void* self);

void func_0017B308(C4A* self)
{
    s32 busy = 0;
    s32 mode = self->mode;
    if (mode < 2) {
        if (mode >= 0) {
            if (func_001E9970(self) != 0) {
                if (D_00270458 != 3 || (D_00270B54 == 0 && D_002717CC == 0)) busy = 1;
            }
        }
    }
    if (busy) ((Mgr_0017B308*)D_0026E248)->vtbl[0x38 / 4](D_0026E248);
    else ((Mgr_0017B308*)D_0026E248)->vtbl[0x3C / 4](D_0026E248);
}

typedef void (*Fn_0017B710)(void* self);

struct Mgr_0017B710 { Fn_0017B710* vtbl; };
extern s32 D_00270458;
extern s32 D_00270B54;
extern s32 D_002717CC;
s32 func_001E9970(void* self);

void func_0017B710(C4B* self)
{
    s32 busy = 0;
    if (self->mode == 1 && func_001E9970(self) != 0) {
        if (D_00270458 != 3 || (D_00270B54 == 0 && D_002717CC == 0)) busy = 1;
    }
    if (busy) ((Mgr_0017B710*)D_0026E248)->vtbl[0x38 / 4](D_0026E248);
    else ((Mgr_0017B710*)D_0026E248)->vtbl[0x3C / 4](D_0026E248);
}

struct Rgba_17A788 {
    u8 r, g, b, a;
};

extern f32 D_00261858[];
f32 D_00263D30[4] = { 1.0f, 0.0f, -0.75f, 0.0f };
f32 D_00263D40[6] = { 0.7f, 0.3f, 0.0f, 0.0f, 7e+02f, 6.5e+02f };
extern f32 D_00275C60[];
extern Rgba_17A788 D_002623E0;

f32 func_00205210(f32 x);
void func_00126A48(C1B* o, u32 value);
void func_00125C90(C1B* o, void* s, void* out);

void func_0017A788(C1B* self, void* s, void* out)
{
    Rgba_17A788 res;
    f32 t;
    f32 u;
    f32 a;
    f32 b;
    f32 k;
    f32 c1;
    f32 lo;
    f32 hi;
    u8 col[4];

    if ((self->flags & 0x100000000ULL) != 0) return;
    *(u32*)col = 0x800000A0;
    if (self->f6D0 != 0) {
        if (self->f610 != 3) {
            t = (D_00261858[1] - self->f6D8) * 0.5f;
        } else {
            t = 0.0f;
        }
        u = func_00205210((D_00261858[1] - self->f6D4) * 10.0f);
        a = D_00263D30[0] + t * (D_00263D30[1] + t * D_00263D30[2]);
        hi = D_00275C60[1];
        if (a < D_00275C60[0]) {
            c1 = D_00275C60[0];
        } else if (hi < a) {
            c1 = hi;
        } else {
            c1 = a;
        }
        b = D_00263D40[0] + u * (D_00263D40[1] + u * D_00263D40[2]);
        lo = D_00275C60[0];
        hi = D_00275C60[1];
        if (b < lo) {
            b = lo;
        } else if (hi < b) {
            b = hi;
        }
        k = c1 * b;
        res.r = (s32)((1.0f - k) * D_002623E0.r + k * col[0]);
        res.g = (s32)((1.0f - k) * D_002623E0.g + k * col[1]);
        res.b = (s32)((1.0f - k) * D_002623E0.b + k * col[2]);
        res.a = D_002623E0.a;
    } else {
        res = D_002623E0;
    }
    func_00126A48(self, *(u32*)&res);
    func_00125C90(self, s, out);
}

// NEAR: last call (func_001B9D10) loads a2 before $f12 is moved; retail moves $f12 first. Otherwise every instruction matches.

struct __attribute__((aligned(16))) Quad_179590 { s32 v[4]; };
struct Sub_179590;
extern u8 D_00248D30[];
extern f32 D_00263C20[];
extern f32 D_00263C30[];
extern f32 D_00263C40[];

void func_001B9338(C1B* self, f32 t);
void func_001794E0(C1B* self, Quad_179590* a, Quad_179590* b);
void func_00127E60(Sub_179590* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void func_001B9058(C1B* self, void* buf, f32 f, void* d1, void* d2, void* d3);
void func_001B9D10(C1B* self, f32 scale, void* out, void* data);

void func_00179590(C1B* self, f32 f)
{
    Quad_179590 a;
    Quad_179590 b;
    s32 mode = self->f610;
    if (mode < 2) {
        goto single;
    }
    if (mode < 4) {
        goto path2;
    }
    if (mode == 4) {
        goto path3;
    }
single:
    func_001B9338(self, f);
    return;
path2:
    func_001794E0(self, &a, &b);
    b = *(Quad_179590*)D_00248D30;
    func_00127E60(((Sub_179590*)self->f668), 0, &a, 0, &b, 0);
    goto tail;
path3:
    a = (*(Quad_179590*)&self->pos);
    b = *(Quad_179590*)D_00248D30;
tail:
    func_001B9058(self, &a, f, D_00263C20, &b, D_00263C30);
    func_001B9D10(self, f, (u8*)self + 0x620, D_00263C40);
}

struct Q_178D98 {
    u8 b[16];
} __attribute__((aligned(16)));
struct Hit_178D98 {
    Q_178D98 q0;
    Q_178D98 q1;
};
struct Node_178D98;
struct Vt_178D98;
struct Sub_178D98 {
    Vt_178D98* vt;
};
struct Vt_178D98 {
    u8 pad00[0x28];
    void (*f28)(Sub_178D98* self, Q_178D98* a, s32 b, s32 c, s32 d, s32 e, f32* out);
};
struct Node_178D98 {
    u8 pad00[0x18];
    void* f18;
    u8 pad1C[0x34 - 0x1C];
    Sub_178D98* f34;
};
struct Entry_178D98 {
    Node_178D98* node;
    f32 f4;
    u8 pad08[8];
    u8 f10[16];
};
struct Slot_178D98 {
    Node_178D98* node;
    u8 pad04[0x1C];
};
extern f32 D_0024AFA4;
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void func_0018D608(void);
Entry_178D98* func_0018D6A8(s32 size);
void func_0018D6F0(void);
s32 func_00182FC8(Node_178D98* p);
s32 func_001300E8(Node_178D98* n, s32 kind);
void func_00128018(void* a, void* b, Q_178D98* c, Q_178D98* d);
void func_001782C0(C07* self, Entry_178D98* e, f32 f, void* a2, void* a3, void* a4);
s32 func_00178D18(Entry_178D98* a, Entry_178D98* b);
void func_001F5CD0(Entry_178D98* base, s32 n, s32 size, s32 (*cmp)(Entry_178D98*, Entry_178D98*));
f32 func_001788F0(C07* self, void* e, s32 v, void* a3, Hit_178D98* a4, f32* a5);
void func_001F5C0C(void* dst, s32 value, s32 size);

void func_00178D98(C07* self, s32 n, Node_178D98** items, Hit_178D98* out, f32* outf)
{
    u8 scratch[0x80];
    Hit_178D98 hit;
    Q_178D98 tmp;
    f32 dist;
    f32 r;
    s32 v;
    Entry_178D98* buf;
    f32 best;
    s32 cnt = 0;

    v = func_0015A4F0(self->world, 5, 8, 0, 0x20, scratch);
    func_0018D608();
    buf = func_0018D6A8(n << 5);
    for (s32 i = 0; i < n; i++) {
        Node_178D98* node = items[i];
        if (func_00182FC8(node) != 0) {
            Entry_178D98* e = buf + cnt;
            cnt = cnt + 1;
            e->node = node;
            if (func_001300E8(node, 0x6E) != 0) {
                func_00128018(0, node->f18, (Q_178D98*)&self->v140, &tmp);
                Sub_178D98* s = node->f34;
                if (s->vt->f28 != 0) {
                    s->vt->f28(s, &tmp, 0, 0, 0, 0, &e->f4);
                }
            } else {
                e->f4 = 0;
            }
            func_001782C0(self, e, 0.7f, 0, e->f10, 0);
        }
    }
    func_001F5CD0(buf, cnt, 0x20, func_00178D18);
    best = D_0024AFA4;
    for (s32 i = 0; i < cnt; i++) {
        r = func_001788F0(self, &buf[i], v, scratch, &hit, &dist);
        if (r < best) {
            best = r;
            *out = hit;
            *outf = dist;
            if (best == 0.0f)
                goto done;
        }
    }
    if (best <= 1000.0f)
        goto done;
    for (s32 i = 0; i < self->f2768; i++) {
        Slot_178D98* q = &((Slot_178D98*)self->f2770)[i];
        if (q->node == 0 || func_00182FC8(q->node) != 0) {
            r = func_001788F0(self, q, v, scratch, &hit, &dist);
            if (r < best) {
                best = r;
                *out = hit;
                *outf = dist;
                if (best == 0.0f)
                    goto done;
            }
        }
    }
    if (best == D_0024AFA4) {
        func_001F5C0C(out, 0, 0x20);
        *(s32*)out = 0;
        out->q1 = *(Q_178D98*)&self->v140;
        ((f32*)out)[6] -= 75.0f;
        *outf = 0.75f;
    }
done:
    func_0018D6F0();
}

Entry_263AC8 D_00263AC8[26] = {
    { 0, 0x453, 0x688 },
    { 0, 0x454, 0x694 },
    { 0, 0x455, 0x6A0 },
    { 0, 0x456, 0x6AC },
    { 0, 0x457, 0x6B8 },
    { 0, 0x458, 0x6C4 },
    { 0, 0x459, 0x6C8 },
    { 0, 0x45A, 0x6CC },
    { 0, 0x44E, 0x654 },
    { 4, 0x50, 0x67C },
    { 4, 0x45, 0x680 },
    { 4, 0x44C, 0x6E4 },
    { 4, 0x44D, 0x6E8 },
    { 0, 0x162, 0x58C },
    { 0, 0x163, 0x590 },
    { 4, 0x160, 0x584 },
    { 32, 0x18D, 0x604 },
    { 4, 0x45B, 0x674 },
    { 4, 0x45C, 0x678 },
    { 4, 0x465, 0x66C },
    { 4, 0x466, 0x670 },
    { 4, 0x45D, 0x650 },
    { 5, 0x461, 0x65C },
    { 5, 0x45F, 0x660 },
    { 5, 0x45E, 0x664 },
    { 5, 0x460, 0x668 }
};

Entry_263D58 D_00263D58[13] = {
    { 0, 0x468, 0x584 },
    { 0, 0x469, 0x56C },
    { 0, 0x46A, 0x560 },
    { 0, 0x46B, 0x578 },
    { 0, 0x46C, 0x594 },
    { 0, 0x46D, 0x5A0 },
    { 0, 0x46E, 0x5AC },
    { 0, 0x46F, 0x5B8 },
    { 2, 0x470, 0x5C8 },
    { 2, 0x471, 0x5D4 },
    { 2, 0x472, 0x5E0 },
    { 2, 0x473, 0x5EC },
    { 2, 0x474, 0x5F8 }
};

Entry_263E08 D_00263E08[3] = {
    { 0, 0x478, 0x55C },
    { 0, 0x479, 0x560 },
    { 0, 0x47A, 0x564 }
};

f32 D_00263C20[4] = { 0.0f, 20.0f, 0.0f, 0.0f };
f32 D_00263C30[4] = { 0.0f, 10.0f, 0.0f, 0.0f };
f32 D_00263C40[3] = { 25.0f, 0.0f, 0.5f };
