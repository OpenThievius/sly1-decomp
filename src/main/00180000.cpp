// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

int func_001EAC68(f32 a, f32 b, f32 eps);

void func_00183F40(f32* out0, f32* out1, f32 a, f32 b, f32 c, f32 d)
{
    if (func_001EAC68(a, c, 1e-4f)) {
        *(s32*)out1 = 0;
        *out0 = b;
    } else {
        f32 t = (d - b) / (c - a);
        *out1 = t;
        *out0 = b - t * a;
    }
}

struct __attribute__((packed)) Q_180F20 { u64 v; };
struct Obj_180F20 { u8 pad0[0x38]; Q_180F20 q; };
void func_001830D8(void* self);

void func_00180F20(Obj_180F20* self)
{
    Q_180F20 saved = self->q;
    func_001830D8(self);
    self->q = saved;
}

void func_00192C58(void* self);
void func_00181DA8(void* self, s32 n);

void func_00181AF0(void* self)
{
    func_00192C58(self);
    func_00181DA8(self, 1);
}

typedef void (*VFnA_182D00)(void* self);
typedef void (*VFnB_182D00)(void* self, s32 n, void* other);
struct Obj_182D00 { void** vtbl; };

void func_00182D00(Obj_182D00* self)
{
    ((VFnA_182D00)self->vtbl[10])(self);
    ((VFnB_182D00)self->vtbl[18])(self, 1, self);
}

typedef void (*VFn0_182E88)(void* self);
typedef void (*VFn2_182E88)(void* self, s32 a, void* b);
struct Obj_182E88 { void** vtbl; };

void func_00182E88(Obj_182E88* self)
{
    ((VFn0_182E88)self->vtbl[11])(self);
    ((VFn2_182E88)self->vtbl[18])(self, 2, self);
}

struct Node_1831E8 { void* f0; s32 f4; u8 pad0[8]; void* f10; };
void* func_001DBBD8(void);

void func_001831E8(void* a0, void** head, void* item, s32 count)
{
    Node_1831E8* n = (Node_1831E8*)func_001DBBD8();
    n->f0 = item;
    n->f4 = count;
    n->f10 = *head;
    *head = n;
}

struct Sub_183458 { u8 pad0[4]; s32 f4; };
struct Obj_183458 { u8 pad0[8]; s32 f8; u8 pad1[0x24]; Sub_183458* f30; };

s32 func_00183458(Obj_183458* a)
{
    if (a->f30) return a->f30->f4;
    return a->f8;
}

struct Obj_183DC0 { u8 pad0[0x14]; u8* f14; };
void func_00152600(void* a, void* b);
void func_001841B0(void* a);

void func_00183DC0(Obj_183DC0* self)
{
    func_00152600(self->f14 + 0x1BE8, self);
    func_001841B0(self);
}

s32 func_001EAC68(f32 a, f32 b, f32 c);

void func_00183FE0(f32* out, s32* flag, f32 x, f32 y, f32 z, f32 w)
{
    const f32 eps = 0.0001f;
    if (func_001EAC68(x, z, eps) || __builtin_fabsf(x) < eps || __builtin_fabsf(z) < eps) {
        *flag = 0;
        *out = y;
        return;
    }
    f32 t = (x * z) * (w - y) / (x - z);
    *(f32*)flag = t;
    *out = y - t / x;
}

void func_00128018(void* a0, s32 zero, void* table, void* out);
void func_001BC260(f32 t, void* obj, void* a, void* b);
f32 func_00205778(f32 a, f32 b);
f32 func_001EA408(f32 a);
void func_001C5D58(void* obj);
void func_00175170(void* obj, s32 a, s32 b);

extern u8 D_00264180[];
extern f32 D_00264190;

struct Vec_181B20 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

struct Obj_181B20 {
    void** vtbl;
    u8 pad0[0x638 - 4];
    f32 x638;
};

void func_00181B20(void* unused, void* obj_)
{
    Obj_181B20* obj = (Obj_181B20*)obj_;
    Vec_181B20 first;
    Vec_181B20 second;

    func_00128018(unused, 0, D_00264180, &first);
    func_001BC260(D_00264190, obj, &first, &second);
    ((void (*)(void*, void*))obj->vtbl[0x90 / 4])(obj, &second);
    f32 r = func_00205778(second.y, second.x);
    obj->x638 = func_001EA408(r + 3.1415927f);
    func_001C5D58(obj);
    func_00175170(obj, 4, 0x2B);
}

void func_001BC4D8(void* self, void* sub);

void func_00181D88(void* self)
{
    func_001BC4D8(self, (u8*)self + 0xC04);
}

void func_0013CE40(void* self);
void func_00124DF8(void* self, s32 a, void* table);
s32 func_001B6290(void* a0, void* self, s32 b, s32 c);
s32 func_00121160(s32 a);
void* func_0018D500(s32 size);

extern u8 D_00264230[];

struct Alloc_1824D8 {
    u8 pad[8];
    s32 field8;
    void* field_c;
};

struct Obj_1824D8 {
    u8 pad0[0x6C4];
    void* x6C4;
    void* x6C8;
    u8 pad1[0x6E8 - 0x6CC];
    Alloc_1824D8* x6E8;
};

void func_001824D8(void* self_)
{
    Obj_1824D8* self = (Obj_1824D8*)self_;
    func_0013CE40(self);
    func_00124DF8(self, 2, D_00264230);
    self->x6C8 = (void*)func_001B6290(self->x6C4, self, 0x36E, 0);
    Alloc_1824D8* n = (Alloc_1824D8*)func_00121160(0);
    self->x6E8 = n;
    n->field8 = 0;
    self->x6E8->field_c = func_0018D500(0xC00);
}

typedef void (*VFn_182C18)(void* self);

struct Obj_182C18 {
    VFn_182C18* vtbl;
};

void func_00182C18(void* self_)
{
    Obj_182C18* self = (Obj_182C18*)self_;
    self->vtbl[5](self);
    self->vtbl[6](self);
}

void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_00182C58(void* self)
{
    func_001837E0(self, 0, 0, 0);
}

typedef void (*VFn_182F78)(void* self, s32 arg);
typedef void (*VFnNone_182F78)(void* self);
struct Obj_182F78 { void* vtbl; u8 pad[0x18 - 4]; s32 f18; };

void func_00182F78(void* a0, s32 a1)
{
    Obj_182F78* self = (Obj_182F78*)a0;
    ((VFn_182F78*)self->vtbl)[7](self, a1);
    self->f18 = a1;
    ((VFnNone_182F78*)self->vtbl)[6](self);
}

s32 func_00182FC8(void* p);

void func_00183028(void* a0, s32* out)
{
    *out = func_00182FC8(a0);
}

void* func_0011E580(s32 a, void* b, s32 c, s32 d, s32 e);

typedef void (*VFn_183058)(void* self, void* arg);
struct Ref_183058 { s32 pad0; s32 f4; };
struct Self_183058 { Ref_183058* ref; s32 pad4; s32 f8; };
struct Obj_183058 { void* vtbl; };

void* func_00183058(Self_183058* self, void* a1, s32 a2)
{
    Obj_183058* r = (Obj_183058*)func_0011E580(self->ref->f4, a1, a2, self->f8, -1);
    ((VFn_183058*)r->vtbl)[12](r, self);
    return r;
}

void func_001243E0(void* self);
void func_00183DC0(void* self);

void func_00183E70(void* self)
{
    func_001243E0(self);
    func_00183DC0(self);
}

struct Tuning_182E40 { u8 pad[0xC]; f32 scale; };

extern Tuning_182E40* D_002623C8;

s32 func_001EB050(void* target, f32 scale);
void func_00182DD8(void* self);

void func_00182E40(void* self, void* target)
{
    if (func_001EB050(target, D_002623C8->scale)) {
        func_00182DD8(self);
    }
}

void func_00182ED0(void* self)
{
    (void)self;
}

typedef void (*VFn_182ED8)(void* self);
struct Obj_182ED8 { VFn_182ED8* vtbl; };

s32 func_00182FC8(void* self);

void func_00182ED8(void* self)
{
    Obj_182ED8* obj = (Obj_182ED8*)self;
    if (func_00182FC8(self)) {
        VFn_182ED8 f = obj->vtbl[19];
        if (f) {
            f(self);
        }
        obj->vtbl[20](self);
        obj->vtbl[7](self);
    }
}

struct Link_182F40 { u8 pad[0x18]; Link_182F40* next; };

s32 func_00182F40(Link_182F40* node, Link_182F40* target)
{
    if (node == 0) {
        return 0;
    }
    while (node != 0) {
        if (node == target) {
            return 1;
        }
        node = node->next;
    }
    return target == 0;
}

struct __attribute__((aligned(16))) Quad_183B20 { s32 w[4]; };
struct __attribute__((packed)) Pack_183B20 { u64 v; };

void func_0011B008(void* self);
void* func_0011C858(void);
void func_0011B818(void* self, void* ptr);
void func_001C2320(void* self, void* a1, void* a2, void* a3);
void func_0011B060(void* self, s32 mode);

void func_00183B20(void* a0, void* a1, void* a2)
{
    Quad_183B20 a;
    Quad_183B20 b;
    void* p;
    func_0011B008(&a);
    p = func_0011C858();
    *(Pack_183B20*)p = *(Pack_183B20*)a2;
    func_0011B818(&a, p);
    func_001C2320(&b, a0, a1, &a);
    func_0011B060(&b, 2);
    func_0011B060(&a, 2);
}

struct __attribute__((aligned(16))) Quad_183BB8 { s32 w[4]; };

void func_0011B008(void* self);
void func_0011B570(void* self, s32 n);
void func_001C2320(void* self, void* a1, void* a2, void* a3);
void func_0011B060(void* self, s32 mode);

void func_00183BB8(void* a0, void* a1, s32 n)
{
    Quad_183BB8 a;
    Quad_183BB8 b;
    func_0011B008(&a);
    func_0011B570(&a, n);
    func_001C2320(&b, a0, a1, &a);
    func_0011B060(&b, 2);
    func_0011B060(&a, 2);
}

struct __attribute__((aligned(16))) Quad_183C38 { s32 w[4]; };

void func_0011B008(void* self);
void* func_0011C508(void);
void func_0011B740(void* a, void* b);
void func_001C2320(void* self, void* a1, void* a2, void* a3);
void func_0011B060(void* self, s32 mode);

void func_00183C38(void* a0, void* a1, void* a2)
{
    Quad_183C38 a;
    Quad_183C38 b;
    void* p;
    func_0011B008(&a);
    p = func_0011C508();
    *(Quad_183C38*)p = *(Quad_183C38*)a2;
    func_0011B740(&a, p);
    func_001C2320(&b, a0, a1, &a);
    func_0011B060(&b, 2);
    func_0011B060(&a, 2);
}

void func_00125138(void* self);
void func_001841D0(void* self);
void func_00184B58(void* self);

void func_00183D88(void* self)
{
    func_00125138(self);
    func_001841D0(self);
    func_00184B58(self);
}

typedef s32 (*VFn_1830B0)(void* self);
struct Obj_1830B0 { VFn_1830B0* vtbl; };

s32 func_001830B0(Obj_1830B0* self)
{
    return ((VFn_1830B0*)self->vtbl)[13](self);
}

struct Desc_1830D8 { u8 pad0[0xC]; s32 size0C; };
struct Obj_1830D8 {
    Desc_1830D8* f0;
    void* f4;
    s32 f8;
    u8 pad1[8];
    u8* f14;
    u8 pad2[0x14];
    void* f2C;
    s32 f30;
};

extern u8 D_00259F38[];

void* func_0011BF30(void);
void func_0011BEE0(void* a, void* b);
void func_0011A708(u8* a, void* b);
void func_0018D800(void* dst, void* src, s32 size);
u8* func_00159F20(u8* base, s32 n);
void func_00152600(u8* p, void* self);
void func_00152470(u8* p, void* self);
void* func_0011A630(void);
void func_0011A800(u8* a);
void func_0011A5B0(void* a, void* b);
void func_0011A6C0(u8* a, void* b);

void func_001830D8(Obj_1830D8* self, Obj_1830D8* src)
{
    if (src->f4 != 0) {
        void* p = func_0011BF30();
        func_0011BEE0(src->f4, p);
        self->f4 = p;
        func_0011A708(D_00259F38, p);
    }
    Desc_1830D8* d = src->f0;
    u8* s0 = self->f14;
    func_0018D800((u8*)self + 0x34, (u8*)src + 0x34, d->size0C - 0x34);
    u8* t = func_00159F20(s0, self->f8);
    func_00152600(t, self);
    t = func_00159F20(s0, src->f8);
    func_00152470(t, self);
    self->f8 = src->f8;
    if (src->f2C != 0) {
        u8* s1 = D_00259F38;
        func_0011A800(s1);
        void* p = func_0011A630();
        func_0011A5B0(src->f2C, p);
        self->f2C = p;
        func_0011A6C0(s1, p);
    }
    self->f30 = src->f30;
}

typedef void (*VFn_00183DF8)(void* self);

struct Obj_00183DF8 { VFn_00183DF8* vtbl; u8 pad04[0x10]; u8* f14; };

void func_00152470(void* sub, void* self);

void func_00183DF8(Obj_00183DF8* self)
{
    VFn_00183DF8 fn;

    func_00152470(self->f14 + 0x1BE8, self);
    fn = self->vtbl[22];
    if (fn != 0) fn(self);
}

typedef void (*VFn_00183E40)(void* self);

struct Obj_00183E40 { VFn_00183E40* vtbl; u8 pad04[0x10]; u8* f14; };

void func_001240F8(void* self);
void func_00183DF8(Obj_00183E40* self);

void func_00183E40(Obj_00183E40* self)
{
    func_001240F8(self);
    func_00183DF8(self);
}

void func_00180E38(s32 a, s32 b);

void func_00180E90(void)
{
    func_00180E38(1, 0xFFFF);
}

struct Obj_180EB0 { u8 pad[0x14]; u8* f14; };

void func_00182D48(void* self);
void func_00152470(u8* table, Obj_180EB0* self);

void func_00180EB0(Obj_180EB0* self)
{
    func_00182D48(self);
    func_00152470(self->f14 + 0x1C9C, self);
}

void func_00182D48(void)
{
}

typedef void (*VFn_182D50)(void* self);

struct Node_182D50 {
    VFn_182D50* vtbl;
    u8 pad4[0x10];
    s32 p14;
    s32 p18;
};

s32 func_001526D0(void* sub, Node_182D50* self);
s32 func_00182FC8(Node_182D50* self);
void func_00152600(void* sub, Node_182D50* self);

void func_00182D50(Node_182D50* self)
{
    void* sub;
    if (self->p18 == 0) {
        sub = (void*)(self->p14 + 0x48);
    } else {
        sub = (void*)(self->p18 + 0x34);
    }
    if (func_001526D0(sub, self) != 0) {
        if (func_00182FC8(self) != 0) {
            func_00152600(sub, self);
            self->vtbl[9](self);
            return;
        }
        func_00152600(sub, self);
    }
}

struct Link_1833F0;

struct Owner_1833F0 {
    u8 pad_00[8];
    s32 id_08;
    u8 pad_0C[0x24];
    Link_1833F0* link_30;
};

struct Link_1833F0 {
    u8 pad_00[4];
    s32 id_04;
};

s32 func_001833F0(Owner_1833F0* self, s32 id)
{
    Link_1833F0* link;

    if (id == -1) {
        return 0;
    }
    if (self->id_08 == id) {
        goto found;
    }
    link = self->link_30;
    if (link == 0) {
        goto missing;
    }
    if (link->id_04 != id) {
        goto missing;
    }
found:
    return 1;
missing:
    return 0;
}

struct Link_183438;

struct Owner_183438 {
    u8 pad_00[0x30];
    Link_183438* link_30;
};

struct Link_183438 {
    u8 pad_00[4];
    s32 id_04;
};

s32 func_00183438(Owner_183438* self)
{
    Link_183438* link = self->link_30;
    if (link != 0) {
        return link->id_04;
    }
    return -1;
}

struct Obj_180EE8 { u8 pad[0x14]; u8* f14; };

void func_00182ED0(void* self);
void func_00152600(u8* table, Obj_180EE8* self);

void func_00180EE8(Obj_180EE8* self)
{
    func_00182ED0(self);
    func_00152600(self->f14 + 0x1C9C, self);
}

struct Obj_180F68 { u8 pad[0xBF4]; f32 fBF4; };

void func_001D73A8(void* self);

void func_00180F68(Obj_180F68* self)
{
    func_001D73A8(self);
    self->fBF4 = -10.0f;
}

struct Hdr_182DD8 {
    u8 pad[8];
    s32 flags;
};

struct Node_182DD8 {
    s32 value;
    Node_182DD8* next;
};

struct Ent_182DD8 {
    Hdr_182DD8* hdr;
    u8 pad4[4];
    s32 value;
    u8 pad12[0xC];
    Ent_182DD8* parent;
    u8 pad1C[0x2C4 - 0x1C];
    Node_182DD8* list;
};

void* func_0018D500(s32 size);

void func_00182DD8(Ent_182DD8* self)
{
    Ent_182DD8* target;
    if (self->hdr->flags & 1) {
        target = self;
    } else {
        target = self->parent;
    }
    if (target != 0) {
        Node_182DD8* n = (Node_182DD8*)func_0018D500(8);
        n->value = self->value;
        n->next = target->list;
        target->list = n;
    }
}

struct Node_183238 {
    s32 key1;
    s32 key2;
    u8 pad8[8];
    Node_183238* next;
};

void func_001DBC18(void* a, void* b);

void func_00183238(void* mgr, Node_183238** link, s32 key1, s32 key2)
{
    Node_183238* node;
    goto test;
advance:
    link = &(*link)->next;
test:
    node = *link;
    if (node == 0) {
        return;
    }
    if (node->key1 != key1 || node->key2 != key2) {
        goto advance;
    }
    *link = node->next;
    node->next = 0;
    func_001DBC18(mgr, node);
}

s32 func_00183438(void* self);

void func_00183478(void* self, s32* out)
{
    *out = func_00183438(self);
}

struct __attribute__((aligned(16))) Quad_183910 { s32 w[4]; };

void func_0011B008(void* self);
void func_0011B5F0(void* self, void* arg);
void func_001C2320(void* self, void* a1, void* a2, void* a3);
void func_0011B060(void* self, s32 mode);

void func_00183910(void* a0, void* a1, void* a2)
{
    Quad_183910 a;
    Quad_183910 b;
    func_0011B008(&a);
    func_0011B5F0(&a, a2);
    func_001C2320(&b, a0, a1, &a);
    func_0011B060(&b, 2);
    func_0011B060(&a, 2);
}

struct S_181AE0 { u8 pad[0xBF0]; s32 value; };
s32 func_00181AE0(S_181AE0* p) { return p->value != 0; }

void func_001DAE48(void);

struct __attribute__((aligned(16))) Quad_181A58 { s32 q[4]; };
struct Inner_181A58 { u8 pad000[0x140]; Quad_181A58 q140; };
struct Obj_181A58 { u8 pad000[0xBC0]; Inner_181A58* pBC0; };

void func_00181A58(void* selfv, void* outv)
{
    Obj_181A58* self = (Obj_181A58*)selfv;
    Quad_181A58* out = (Quad_181A58*)((u8*)outv + 0x10);
    func_001DAE48();
    *out = self->pBC0->q140;
}

struct Sub_181D28 { u8 pad0[0x24]; s32 f24; };
struct Obj_181D28 { u8 pad0[0xBBC]; Sub_181D28* pBBC; u8 pad1[0xC00 - 0xBC0]; s32 fC00; };
struct Rec_181D28 { s32 f0; u8 pad4[4]; s32 f8; };

void func_001DAF08(void* self, s32 code, Rec_181D28* rec);

void func_00181D28(Obj_181D28* self, s32 code, Rec_181D28* rec)
{
    if (code == 0x13) {
        Sub_181D28* sub = self->pBBC;
        s32 key = rec->f0;
        if (sub != 0 && key == sub->f24) {
            s32 kind = rec->f8;
            if (kind != 0x15E) {
                if (kind == 0x15F) {
                    self->fC00 = 0;
                }
            } else {
                self->fC00 = 1;
            }
        }
    }
    func_001DAF08(self, code, rec);
}

struct Obj_182470 { u8 pad0[0x6CC]; f32 f6CC; s32 f6D0; f32 f6D4; f32 f6D8; f32 f6DC; f32 f6E0; };

void func_0013DDB8(void* self);

void func_00182470(Obj_182470* self)
{
    func_0013DDB8(self);
    self->f6DC = 10.0f;
    self->f6E0 = 1.0f;
    self->f6D8 = 3000.0f;
    self->f6CC = 1000.0f;
    self->f6D0 = 0;
    self->f6D4 = 0.5f;
}

struct Node_182C80;
typedef void (*VFn_182C80)(void* self);
struct Node_182C80 { VFn_182C80* vtbl; u8 pad4[0x10]; s32 p14; s32 p18; };

s32 func_001526D0(void* sub, Node_182C80* self);
void func_00152470(void* sub, Node_182C80* self);
s32 func_00182FC8(Node_182C80* self);

void func_00182C80(Node_182C80* self)
{
    void* sub;
    if (self->p18 == 0) {
        sub = (void*)(self->p14 + 0x48);
    } else {
        sub = (void*)(self->p18 + 0x34);
    }
    if (func_001526D0(sub, self) != 0) {
        return;
    }
    func_00152470(sub, self);
    if (func_00182FC8(self) != 0) {
        self->vtbl[8](self);
    }
}

struct Node_182FC8 { u8 pad0[0x14]; s32 p14; s32 p18; };

s32 func_001526D0(void* sub, Node_182FC8* self);

s32 func_00182FC8(Node_182FC8* self)
{
    Node_182FC8* node = self;
    while (node != 0) {
        s32 next = node->p18;
        void* sub;
        if (next != 0) {
            sub = (void*)(next + 0x34);
        } else {
            sub = (void*)(node->p14);
            sub = (u8*)sub + 0x48;
        }
        if (func_001526D0(sub, node) == 0) {
            return 0;
        }
        node = (Node_182FC8*)next;
    }
    return 1;
}

struct Mgr_183290 { u8 pad0[0x14]; void* f14; u8 pad1[0x10]; void* f28; };

void func_001831E8(void* a0, void** head, void* item, s32 count);

void func_00183290(Mgr_183290* self, void* item, s32 count)
{
    func_001831E8(self->f14, &self->f28, item, count);
}

struct Mgr_1832C0 { u8 pad0[0x14]; void* f14; u8 pad1[0x10]; void* f28; };

void func_00183238(void* mgr, void** link, s32 key1, s32 key2);

void func_001832C0(Mgr_1832C0* self, s32 key1, s32 key2)
{
    func_00183238(self->f14, &self->f28, key1, key2);
}

struct Item_1832F0 { u8 pad0[0x44]; void* f44; };
struct Src_1832F0 { Item_1832F0* f0; };
struct Mgr_1832F0 { u8 pad0[0x14]; void* f14; u8 pad1[0x10]; void* f28; };

void func_001831E8(void* a0, void** head, void* item, void* count);

void func_001832F0(Mgr_1832F0* self, Src_1832F0* src)
{
    func_001831E8(self->f14, &self->f28, src->f0->f44, src);
}

struct __attribute__((aligned(16))) Quad_183990 { s32 w[4]; };

void func_0011B008(void* self);
void func_0011B570(void* self, s32 n);
void func_001C2320(void* self, void* a1, void* a2, void* a3);
void func_0011B060(void* self, s32 mode);

void func_00183990(void* a0, void* a1, s32 n)
{
    Quad_183990 a;
    Quad_183990 b;
    func_0011B008(&a);
    func_0011B570(&a, n);
    func_001C2320(&b, a0, a1, &a);
    func_0011B060(&b, 2);
    func_0011B060(&a, 2);
}

struct __attribute__((aligned(16))) Quad_183A10 { s32 w[4]; };

void func_0011B008(void* self);
void* func_0011B5B0(void* obj, f32 x);
void func_001C2320(void* self, void* a1, void* a2, void* a3);
void func_0011B060(void* self, s32 mode);

void func_00183A10(void* a0, void* a1, f32 x)
{
    Quad_183A10 a;
    Quad_183A10 b;
    func_0011B008(&a);
    func_0011B5B0(&a, x);
    func_001C2320(&b, a0, a1, &a);
    func_0011B060(&b, 2);
    func_0011B060(&a, 2);
}

struct __attribute__((aligned(16))) Quad_183A90 { s32 w[4]; };

void func_0011B008(void* self);
void* func_0011C748(void);
void func_0011B7D0(void* self, void* ptr);
void func_001C2320(void* self, void* a1, void* a2, void* a3);
void func_0011B060(void* self, s32 mode);

void func_00183A90(void* a0, void* a1, void* a2)
{
    Quad_183A90 a;
    Quad_183A90 b;
    func_0011B008(&a);
    Quad_183A90* p = (Quad_183A90*)func_0011C748();
    *p = *(Quad_183A90*)a2;
    func_0011B7D0(&a, p);
    func_001C2320(&b, a0, a1, &a);
    func_0011B060(&b, 2);
    func_0011B060(&a, 2);
}

struct Item_183320 { u8 pad0[0x44]; void* f44; };
struct Src_183320 { Item_183320* f0; };
struct Mgr_183320 { u8 pad0[0x14]; void* f14; u8 pad1[0x10]; void* f28; };

void func_00183238(void* mgr, void** link, s32 key1, Src_183320* key2);

void func_00183320(Mgr_183320* self, Src_183320* src)
{
    func_00183238(self->f14, &self->f28, (s32)src->f0->f44, src);
}

void func_0011EC40(void* a, void* b);

void func_001833D0(void* a, void* b)
{
    func_0011EC40(a, b);
}

// NEAR: all calls and branches match; only the vtable load for the last call differs (retail loads the vtable into $v1 and the slot into $v0, ours the other way round)
typedef s32 (*VFnQ_181BC8)(void* self, s32 a);
typedef void (*VFnP_181BC8)(void* self, void* a);
typedef s32 (*VFnR_181BC8)(void* self, void* a);
typedef void (*VFnV_181BC8)(void* self);
typedef void (*VFnPPP_181BC8)(void* self, s32 a, void* b);
typedef void (*Fn_181BC8)(void);

s32 func_00160C58();
void func_00181DA8(void* self, s32 n);
void func_00192990(void* self, s32 value);
void func_00175170(void* self, s32 a, s32 b);
void func_001929D0(void* value);
void func_001D7098(void* out, s32 mode, void* owner);
void func_00181B20(void);

extern s32 D_00262E10;
extern f32 D_0026185C;

struct Self_181BC8 { void** vt; u8 pad004[0xBC8 - 4]; void* pBC8; u8 padBCC[0xBF0 - 0xBCC]; s32 bf0; f32 bf4; };
struct Vt_181BC8 { void** vt; };
struct Loc_181BC8 { void* self; s32 val; s32 pad8; Fn_181BC8 fn; };

s32 func_00181BC8(void* selfv, s32* arg)
{
    Self_181BC8* self = (Self_181BC8*)selfv;
    Loc_181BC8 loc;
    s32 r;
    s32 g;
    Vt_181BC8* gp;
    VFnP_181BC8 f;
    void** vt2;

    if (((VFnQ_181BC8)self->vt[79])(self, arg[0])) {
        return 0;
    }
    if (func_00160C58()) {
        self->bf0 = 1;
    }
    self->bf4 = D_0026185C;
    r = func_00160C58();
    if (r == 0) {
        g = D_00262E10;
        if (g != 0) {
            goto then_block;
        }
    }
    func_00181DA8(self, 2);
    goto tail;
then_block:
    ((VFnV_181BC8)((Vt_181BC8*)D_00262E10)->vt[6])((void*)D_00262E10);
    ((VFnP_181BC8)((Vt_181BC8*)D_00262E10)->vt[35])((void*)D_00262E10, self->pBC8);
    ((VFnV_181BC8)((Vt_181BC8*)self->pBC8)->vt[7])(self->pBC8);
    func_00192990((void*)D_00262E10, 1);
    func_00175170((void*)D_00262E10, 2, 2);
    func_001929D0((void*)D_00262E10);
    func_00181DA8(self, 3);
    func_001D7098(&loc, 0, self);
    gp = (Vt_181BC8*)D_00262E10;
    gp = (Vt_181BC8*)D_00262E10;
    loc.fn = func_00181B20;
    (void)((VFnR_181BC8)gp->vt[80])(gp, &loc);
tail:
    loc.self = self;
    loc.val = arg[1];
    ((VFnPPP_181BC8)self->vt[18])(self, 0x17, &loc);
    return 1;
}

struct Obj_181448;
typedef s32 (*Fn_181448)(Obj_181448*, void*, void*);
struct Vt_181448 { u8 pad0[0x12C]; Fn_181448 f12C; u8 pad1[0x140 - 0x130]; void (*f140)(Obj_181448*, void*); };
struct Obj_181448 {
    Vt_181448* vtbl;
    u8 pad4[0x10];
    void* f14;
    u8 pad18[0xBB0 - 0x18];
    s32 fBB0;
    u8 padBB4[0xBCC - 0xBB4];
    void* fBCC;
    u8 padBD0[0xBF0 - 0xBD0];
    s32 fBF0;
    f32 fBF4;
    f32 fBF8;
    u8 padBFC[0xC04 - 0xBFC];
    void* fC04;
};
struct Ch_181448;
struct Slot_181448 { Ch_181448* p; u8 pad[0x3C]; };
struct Node_181448 {
    Obj_181448* owner;
    Slot_181448 s[2];
    u8 pad[0xD0 - 0x84];
    Node_181448* next;
};
struct Ch_181448 {
    Vt_181448* vtbl;
    u8 pad4[0x14];
    Ch_181448* f18;
    u8 pad1C[0x4E0 - 0x1C];
    s32 f4E0;
};

extern f32 D_00261858[];
extern f32 D_00264140[];
extern f32 D_00264150[];
extern f32 D_00264154[];
extern f32 D_00275C60[];

void func_001D9C98(Obj_181448* self, f32 dt);
void func_001D7098(void* out, s32 mode, Ch_181448* c);
void func_001861E8(void* a, void* head);
void func_00129E10(void* o, f32 v);
void func_00129FB0(void* o, f32 v);

void func_00181448(Obj_181448* self, f32 dt)
{
    s32 buf[4];
    func_001D9C98(self, dt);
    if (self->fC04 != 0) {
        Node_181448* n = (Node_181448*)self->fC04;
        do {
            s32 j = (n->owner != self);
            Ch_181448* c = n->s[1 - j].p;
            while (c != 0 && c->f4E0 == 0) c = c->f18;
            if (c != 0 && (c->f4E0 == 1 || c->f4E0 == 4)) {
                func_001D7098(buf, 0, c);
                while (c != 0) {
                    if (c->vtbl->f12C((Obj_181448*)c, n, buf) != 0) break;
                    c = c->f18;
                }
                self->vtbl->f140(self, buf);
            }
            n = n->next;
        } while (n != 0);
        func_001861E8(self->f14, self->fC04);
        self->fC04 = 0;
    }
    f32 t = D_00261858[1] - self->fBF4;
    f32 v = D_00264140[0] + t * (D_00264140[1] + t * D_00264140[2]);
    f32* r = D_00275C60;
    f32 lo = D_00275C60[0];
    f32 hi = r[1];
    f32 x;
    if (v < lo) x = lo;
    else if (hi < v) x = hi;
    else x = v;
    func_00129E10(self->fBCC, x * D_00264150[0]);
    func_00129FB0(self->fBCC, x * D_00264154[0]);
    if (self->fBF0 != 0 && self->fBB0 != 2 && D_00261858[1] - self->fBF8 > 2.0f) self->fBF0 = 0;
}

struct __attribute__((aligned(16))) Quad_1834A0 { s32 w[4]; };
struct Link_1834A0 { s32 a; void* b; Link_1834A0* next; };
struct Mid_1834A0 { s32 pad0; void* kind; Link_1834A0* head; };
struct Rec_1834A0 { s32 key; Mid_1834A0* mid; s32 pad8; s32 padC; void* f10; };
struct Self_1834A0 { u8 pad0[0x2C]; void* f2C; };
struct Slot_1834A0 { s32 flag; s32 value; };
struct Item_1834A0 { s32 pad0; s32 pad4; Item_1834A0* next; };

void func_0011B008(Quad_1834A0* q);
void func_0011A800(void* d);
s32 func_0011A498(void* a, s32 b, s32 c, Quad_1834A0* d);
void func_0011B060(Quad_1834A0* q, s32 mode);
void func_0011A328(Slot_1834A0* slot, s32 value);
void func_0011B8A8(Quad_1834A0* q, Self_1834A0* s);
void* func_0011A358(Quad_1834A0* out, Slot_1834A0* owner, void* kind, void* body);
void func_0011B0A8(Quad_1834A0* a, Quad_1834A0* b);
void func_00119A58(Quad_1834A0* out, void* list, Slot_1834A0* c);
extern u8 D_00259F38[];

void func_001834A0(Self_1834A0* self, s32 key, Item_1834A0* list)
{
    Quad_1834A0 q0, q1, q2, q3;
    func_0011B008(&q0);
    func_0011B008(&q1);
    func_0011B008(&q2);
    func_0011A800(D_00259F38);
    if (func_0011A498(self->f2C, key, 1, &q0) == 0) {
        func_0011B060(&q2, 2);
        func_0011B060(&q1, 2);
        func_0011B060(&q0, 2);
        return;
    }
    Rec_1834A0* rec = (Rec_1834A0*)q0.w[1];
    Slot_1834A0* slot = (Slot_1834A0*)func_0011A630();
    func_0011A328(slot, rec->key);
    func_0011B8A8(&q1, self);
    func_0011A358(&q3, slot, rec->mid->kind, &q1);
    func_0011B0A8(&q2, &q3);
    func_0011B060(&q3, 2);
    if (list != 0) {
        Item_1834A0* it = list;
        Link_1834A0* l = rec->mid->head;
        do {
            func_0011A358(&q3, slot, l->b, it);
            func_0011B0A8(&q2, &q3);
            func_0011B060(&q3, 2);
            it = it->next;
            l = l->next;
        } while (it != 0);
    }
    func_00119A58(&q3, rec->f10, slot);
    func_0011B0A8(&q2, &q3);
    func_0011B060(&q3, 2);
    func_0011B060(&q2, 2);
    func_0011B060(&q1, 2);
    func_0011B060(&q0, 2);
}

s32 func_001DDA80(void* p);

struct Obj_181A98 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0xBB0 - 0x18];
    s32 fBB0;
    u8 pad2[0xBF0 - 0xBB4];
    s32 fBF0;
};

s32 func_00181A98(Obj_181A98* self)
{
    if (self->fBB0 != 1 || self->fBF0 != 0 || func_001DDA80(self->f14) != 0) return 1;
    return 0;
}
