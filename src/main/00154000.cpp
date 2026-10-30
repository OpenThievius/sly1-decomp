// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Actor_156108 {
    u8 pad0[0x2D4];
    s32 f2D4;
    s32 f2D8;
    u8 pad1[0x34C - 0x2DC];
    s32 f34C;
};

void func_00155F90();
void func_00155FA0(Actor_156108* self);

void func_00156108(Actor_156108* self, s32 a1)
{
    if (self->f2D4 == -1) {
        self->f2D8 = a1;
    } else if (self->f2D4 == 0) {
        if (a1 == 0) {
            func_00155F90();
        } else if (a1 == -1) {
            func_00155FA0(self);
        } else {
            self->f2D8 = a1;
        }
    }
    self->f34C = 1;
}

struct Actor_156178 {
    u8 pad0[0x308];
    s32 f308;
    u8 pad1[0x34C - 0x30C];
    s32 f34C;
};

void func_00156178(Actor_156178* a0, s32 a1)
{
    a0->f308 = a1;
    a0->f34C = 1;
}

void* func_00155778(void* a0, s32 a1);
void func_00156188(void* self, s32 a1);

void func_00156218(void* a0, s32 a1)
{
    void* r = func_00155778(a0, 1);
    func_00156188(r, a1);
}

void* func_00158DD8(void* a0, s32 a1);
void func_00156188(void* self, s32 a1);

void func_00156250(void* a0, s32 a1)
{
    void* r = func_00158DD8(a0, 1);
    func_00156188(r, a1);
}

struct __attribute__((aligned(16))) Quad_001566C8 { s32 a, b, c, d; };
struct Msg_001566C8 {
    s32 kind;
    u8 pad0[0x20 - 4];
    Quad_001566C8 q;
    s32 zero;
    f32 f;
    u8 pad1[0x50 - 0x38];
};
struct Game_001566C8 {
    u8 pad0[0x1D0C];
    void* f1D0C;
};
typedef void (*VFn_001566C8)(void* self, void* msg);

extern Game_001566C8* D_00275710;

void func_001566C8(Quad_001566C8* a0, f32 f)
{
    void* obj = D_00275710->f1D0C;
    if (obj != 0) {
        Msg_001566C8 m;
        m.kind = 12;
        m.q = *a0;
        m.f = f;
        m.zero = 0;
        VFn_001566C8* vt = *(VFn_001566C8**)obj;
        vt[31](obj, &m);
    }
}

struct Obj_1550B8;
typedef void (*VFn_1550B8)(Obj_1550B8* self, void* arg);
struct Sub_1550B8 { u8 pad[0x7C]; void* value; };
struct Obj_1550B8 { VFn_1550B8* vtbl; u8 pad[0x2D0 - 4]; Sub_1550B8* sub; };

void func_001550B8(Obj_1550B8* self)
{
    self->vtbl[25](self, self->sub->value);
}

struct Obj_1557B8 { u8 pad[0x34C]; s32 field; };

Obj_1557B8* func_001557B8(Obj_1557B8* self, s32 value)
{
    if (value == 1) {
        self->field = value;
    }
    return self;
}

extern f32 D_0026185C;

struct Obj_155FB0 { u8 pad0[0x2D4]; s32 a2d4; s32 a2d8; u8 pad1[0x340 - 0x2DC]; f32 f340; };

s32 func_00155FB0(Obj_155FB0* self)
{
    if (D_0026185C < self->f340) {
        return 1;
    }
    if (self->a2d4 < 2) {
        if (self->a2d4 >= 0) {
            if (self->a2d8 == 0) {
                return 1;
            }
        }
    }
    return 0;
}

struct Obj_157E00 {
    u8 pad0[0x120];
    s32 f120;
    u8 pad1[0x130 - 0x124];
    s32 f130;
};

struct Frame_157E00 {
    s32 out[4];
    s32 flag;
    s32 pad[3];
    s32 pair[2];
    u8 tail[0x18];
};

void func_0018D608(void);
void func_0018D6F0(void);
void func_001579B0(void* a, void* b, s32* out);
void func_00157320(void* b, void* c, void* a, s32 o0, s32 o1, s32 o2, s32 o3);
void func_00157B88(void* a, void* b, s32* out, s32* pair);
void func_001575D8(void* b, void* c, void* a, s32 o0, s32 o1, s32 o2, s32 o3, s32 p0, s32 p1);

void func_00157E00(void* a, Obj_157E00* b, void* c)
{
    Frame_157E00 f;
    if (a == 0) {
        return;
    }
    func_0018D608();
    f.flag = 1;
    func_001579B0(a, b, f.out);
    if (b->f120 == 1) {
        func_00157320(b, c, a, f.out[0], f.out[1], f.out[2], f.out[3]);
    } else {
        if (b->f130 == 2) {
            func_00157B88(a, b, f.out, f.pair);
        } else {
            f.pair[0] = 0;
            f.pair[1] = 0;
        }
        func_001575D8(b, c, a, f.out[0], f.out[1], f.out[2], f.out[3], f.pair[0], f.pair[1]);
    }
    func_0018D6F0();
}

struct Word_154EE0 {
    s32 value;
};

struct __attribute__((packed)) Packed_154EE0 {
    s32 value;
};

struct Buffer_154EE0 {
    u8 pad0[0x4C];
    s32 cap;
    Packed_154EE0* items;
    void* source;
};

void* func_0018D500(s32 size);
void* func_00137B90(void* src);
Word_154EE0 func_00137C40(void* src);

void func_00154EE0(Buffer_154EE0* self, s32 count, void* unused, void* src)
{
    s32 limit = 31;
    s32 cap = (limit < count) ? 32 : count;
    self->cap = cap;
    self->items = (Packed_154EE0*)func_0018D500(cap * 4);
    self->source = func_00137B90(src);
    for (s32 i = 0; i < count; i++) {
        Word_154EE0 tmp = func_00137C40(src);
        if (i < self->cap) {
            self->items[i] = *(Packed_154EE0*)&tmp;
        }
    }
}

typedef void (*VFn_154F98)(void* self, s32 count);

struct Obj_154F98 {
    VFn_154F98* vtbl;
};

struct Node_154F98 {
    u8 pad0[0x10];
    s32 kind;
    u8 pad1[0x20 - 0x14];
    Obj_154F98* obj;
};

struct Owner_154F98 {
    u8 pad0[0x2D0];
    Node_154F98* node;
};

void* func_0018D500(s32 size);
void func_001549C8(void* mem);
void func_001289C0(void* self, s32 count);
s32 func_00137CC0(s32 count);
void* func_0014D9A8(s32 index);
void func_00154C80(void* self, s32 count);
s32 func_00137BE0(s32 count);
void* func_00155778(void* self, s32 flag);
void func_00154EE0(void* self, s32 count, void* unused, s32 src);

void func_00154F98(Owner_154F98* self, s32 count)
{
    void* mem = func_0018D500(0x200);
    self->node = (Node_154F98*)mem;
    func_001549C8(mem);
    func_001289C0(self, count);
    s32 index = func_00137CC0(count);
    if (index != -1) {
        Obj_154F98* obj = (Obj_154F98*)func_0014D9A8(index);
        self->node->obj = obj;
        VFn_154F98 fn = obj->vtbl[0];
        if (fn != 0) {
            fn(obj, count);
        }
    }
    if (self->node->kind == 4) {
        func_00154C80(&self->node->obj, count);
    }
    s32 n = func_00137BE0(count);
    if (n != 0) {
        void* b = func_00155778(self, 1);
        func_00154EE0((u8*)b + 0x130, n, self, count);
    }
}

struct Counter_155080 {
    s32 count;
};

struct Owner_155080 {
    u8 pad0[0x2D0];
    Counter_155080* counter;
};

void func_00127048(void* self);

void func_00155080(Owner_155080* self)
{
    func_00127048(self);
    self->counter->count++;
}

union Key_001550E8 { s64 whole; s32 part[2]; };

struct Rec_001550E8 { u8 pad00[0x18]; void* f18; u8 pad1C[0x18]; s32 f34; };

struct Sub_001550E8 {
    u8 pad00[0x10]; s32 f10;
    u8 pad14[0xC]; s32 f20;
    u8 pad24[0x58]; void* f7C;
    u8 pad80[0x120 - 0x80]; s32 f120;
    u8 pad124[0x188 - 0x124]; s32 f188;
    u8 pad18C[0x1D8 - 0x18C]; void* f1D8; void* f1DC; void* f1E0;
};

struct Ctx_001550E8 {
    u8 pad00[0x14]; void* f14;
    u8 pad18[0x2B8]; Sub_001550E8* f2D0;
    u8 pad2D4[0x24]; Key_001550E8 f2F8;
    s32 f300; s32 f304; u8 pad308[4]; s32 f30C;
};

void func_001249A8(Ctx_001550E8* self);
Sub_001550E8* func_00155778(Ctx_001550E8* self, s32 mode);
void func_00158288(Sub_001550E8* p, Ctx_001550E8* self);
Rec_001550E8* func_0015A418(void* a0, s32 a1, s32 a2, Ctx_001550E8* a3);
s32 func_001300E8(Rec_001550E8* p, s32 k);
void func_001DBCC8(void* a0, void (*cb)(void), Ctx_001550E8* a2, s32 a3, s32 a4);

void func_001550E8(Ctx_001550E8* self)
{
    Sub_001550E8* s2;

    func_001249A8(self);
    if (self->f2F8.whole == -1 && self->f304 == -1 && self->f30C == -1 && self->f300 == -1) {
        Sub_001550E8* p = self->f2D0;
        if (p->f10 != 3 && (p->f120 != 0 || p->f188 == -1)) goto tail;
    }
    s2 = func_00155778(self, 1);
    if (self->f2F8.part[0] != -1) {
        Rec_001550E8* r = func_0015A418(self->f14, 0x104, self->f2F8.part[0], self);
        s2->f7C = r;
        if (r != 0) func_001DBCC8(self->f14, (void (*)(void))func_001550B8, self, 0, 0);
    }
    if (self->f2F8.part[1] != -1) {
        s2->f1D8 = func_0015A418(self->f14, 0x104, self->f2F8.part[1], self);
    }
    if (self->f304 != -1) {
        s2->f1DC = func_0015A418(self->f14, 0x104, self->f304, self);
    }
    if (self->f300 != -1) {
        Rec_001550E8* s1 = func_0015A418(self->f14, 0x104, self->f300, self);
        if (func_001300E8(s1, 3) != 0) s2->f1E0 = s1;
    }
    if (self->f30C != -1) {
        Rec_001550E8* r = func_0015A418(self->f14, 0x104, self->f30C, self);
        s2->f20 = r->f34;
        s2->f7C = r->f18;
    }
tail:
    func_00158288(self->f2D0, self);
}

typedef void (*VFn_00155678)(void* obj, void* owner);
struct VObj_00155678 { VFn_00155678* vtbl; };
struct Ctx_00155678 { u8 pad00[0x344]; VObj_00155678* f344; VObj_00155678* f348; };

void func_00155678(Ctx_00155678* self, s32 mode, VObj_00155678* p)
{
    if (mode == 2) {
        if (p == self->f344) {
            p->vtbl[28](p, self);
            self->f344 = 0;
        } else if (p == self->f348) {
            p->vtbl[28](p, self);
            self->f348 = 0;
        }
    }
}

struct Pool_001556E8 { s32 f0; u8 pad04[0xC]; s32 f10; u8 pad14[0xC]; s32 f20; void* f24; };

void* func_0018D568(s32 size, void* owner);

Pool_001556E8* func_001556E8(Pool_001556E8* self)
{
    Pool_001556E8* n;
    if (self->f0 < 2) return self;
    n = (Pool_001556E8*)func_0018D568(0x200, self);
    if (self->f10 == 3 && self->f24 != 0) {
        n->f24 = func_0018D568(0x28 * self->f20, self->f24);
    }
    n->f0 = 1;
    self->f0 -= 1;
    return n;
}

struct Ctx_00155778 { u8 pad00[0x2D0]; void* f2D0; u8 pad2D4[0x78]; s32 f34C; };

void* func_001556E8(void* pool);

void* func_00155778(Ctx_00155778* self, s32 mode)
{
    if (mode == 1) {
        self->f34C = mode;
        self->f2D0 = func_001556E8(self->f2D0);
    }
    return self->f2D0;
}

struct Node_00155F28 {
    u8 pad0[0x18];
    Node_00155F28* next;
    u8 pad1[0x88 - 0x1C];
    s32 field88;
    u8 pad2[0x2C8 - 0x8C];
    u64 flags;
};

void func_00155F28(Node_00155F28* self)
{
    if ((self->flags & 0x0C000000) == 0x08000000) {
        return;
    }
    Node_00155F28* p = self->next;
    while (p != 0) {
        if ((p->flags & 0x0C000000) == 0x08000000) {
            break;
        }
        p = p->next;
    }
    if (p != 0) {
        self->field88 = p->field88;
    }
}

struct Actor_155F78 { u8 pad0[0x340]; f32 f340; };

extern f32 D_0026185C;

void func_00155F78(Actor_155F78* self, f32 f)
{
    self->f340 = D_0026185C + f;
}

struct Actor_155FA0 { u8 pad0[0x340]; f32 f340; };

void func_00155FA0(Actor_155FA0* self)
{
    self->f340 = -1.0f;
}

struct Obj_156000;

void func_00155F90();
void func_00155FA0(Obj_156000* self);

void func_00156000(Obj_156000* self, s32 a1)
{
    if (a1 != 0) {
        func_00155FA0(self);
    } else {
        func_00155F90();
    }
}

struct Obj_156030;

s32 func_00155FB0(Obj_156030* self);

void func_00156030(Obj_156030* self, s32* out)
{
    *out = func_00155FB0(self) == 0;
}

void func_00123ED0(void*);
void func_00152438(void*,s32);
void func_00154C10(u8* self)
{
    func_00123ED0(self);
    *(s32*)(self+0x2D8)=-1;
    *(f32*)(self+0x2E0)=10.0f;
    *(s32*)(self+0x2F8)=-1;
    *(s32*)(self+0x2FC)=-1;
    *(s32*)(self+0x304)=-1;
    *(s32*)(self+0x300)=-1;
    *(s32*)(self+0x30C)=-1;
    *(s32*)(self+0x2D4)=-1;
    *(f32*)(self+0x2DC)=10.0f;
    *(f32*)(self+0x340)=-1.0f;
    *(s32*)(self+0x310)=-1;
    func_00152438(self+0x314,0x320);
}

void func_00158198(void*,void*,void*,f32,f32,f32,f32,void*);
void func_001557D0(void* self,void* a,void* b,f32 x,f32 y,f32 z,f32 w)
{
    u8* p=(u8*)func_00155778(self,1);
    func_00158198(p+16,a,b,x,y,z,w,self);
}

void func_00156060(void* self,s32* out)
{
    *out=func_00155FB0((Obj_155FB0*)self);
}

void func_0013A128(void*,void*);
void func_0019E158(void*,void*);
f32 func_001EAAE0(f32,f32);
void func_00156088(u8* self)
{
    *(s32*)(self+0x34C)=0;
    if (*(void**)(self+0x348)) func_0013A128(*(void**)(self+0x348),*(void**)(self+0x2D0));
    if (*(void**)(self+0x344)) func_0019E158(*(void**)(self+0x344),*(void**)(self+0x2D0));
    f32 value;
    if (*(s32*)(self+0x2D4)==3) value=func_001EAAE0(*(f32*)(self+0x2DC),*(f32*)(self+0x2E0))*60.0f;
    else value=func_001EAAE0(*(f32*)(self+0x2DC),*(f32*)(self+0x2E0));
    *(f32*)(self+0x328)=value;
}

void* func_001F5C0C(void*,s32,s32);
void func_00156188(u8* self,s32 kind)
{
    *(s32*)(self+0x1B0)=kind;
    func_001F5C0C(self+0x1F0,0,12);
    if (kind!=24) {
        if (kind==27) {
            *(s32*)(self+0x1F0)=-1;
            *(f32*)(self+0x1F4)=10.0f;
        }
    } else {
        *(f32*)(self+0x1F0)=25.0f;
        *(f32*)(self+0x1F4)=0.8f;
        *(f32*)(self+0x1F8)=0.8f;
    }
}

struct Item_154880 {
    u8 pad0[0x34];
    f32 f34;
    f32 f38;
    u8 pad1[0x44 - 0x3C];
    void* p44;
    u8 pad2[0x60 - 0x48];
};

struct Loc_154880 {
    u32 hdr;
    s32 count;
    u8* items;
    u8 pad[0x30 - 0xC];
    u8 tmp[0x10];
    u8 tail[0x10];
};

void func_0018D608(void);
void func_0018D6F0(void);
void* func_0018D658(s32 size);
void func_0018D800(void* dst, void* src, s32 size);
void func_00153528(Loc_154880* loc, s32 count);
void func_00152470(void* tmp, Item_154880* item);
void func_00153EC0(Loc_154880* loc, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_00154880(s32 count, u8* data, f32* values, f32* out)
{
    Loc_154880 loc;
    s32 i;

    func_0018D608();
    func_00153528(&loc, count);
    for (i = 0; i < count; i++) {
        Item_154880* item = (Item_154880*)(loc.items + i * 0x60);
        item->p44 = func_0018D658(count * 4);
        func_0018D800(item->p44, data + i * count * 4, count * 4);
        item->f38 = values[i];
        func_00152470(loc.tmp, item);
    }
    loc.count = count;
    func_00153EC0(&loc, 0, 0, 0, 0, 0);
    for (i = 0; i < count; i++)
        out[i] = *(f32*)(loc.items + i * 0x60 + 0x34);
    func_0018D6F0();
}

struct Self_155F90 { u8 pad0[0x340]; f32 f340; };

void func_00155F90(Self_155F90* self)
{
    self->f340 = 3.4028234663852886e+38f;
}

struct __attribute__((aligned(16))) Q_157320 { s32 a, b, c, d; };
struct Self_157320 { u8 pad[4]; };
struct Hdr_157320 { u8 pad[4]; s32* f4; s32 f8; };
struct Node_157320 { u8 pad[4]; };
struct Item_157320 { u8 pad[4]; };

Node_157320* func_0019E040(u8* ctx, s32 flag);
void func_0019E158(Node_157320* a, Self_157320* b);
Item_157320* func_0019EA78(s32 a, Node_157320* b);
void func_001A0338(Node_157320* self, s32 kind, Item_157320* extra);
void func_001583E8(Item_157320* a, Self_157320* b);
f32 func_001EAAE0(f32 a, f32 b);
s32 func_00152720(void* p);

#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))
typedef void (*VFn)();

void func_00157320(Self_157320* self, Hdr_157320* h, s32 n, Q_157320* pos, Q_157320* q2, f32* v5, f32* v6)
{
    u8* s7 = AT(u8*, self, 0x7C);
    Node_157320* node = 0;
    u8* c = (u8*)self + 0x120;
    s32 i;
    if (h) {
        if (h->f4) node = (Node_157320*)*h->f4;
    }
    if (!node) {
        node = func_0019E040((u8*)D_00275710, AT(s32, c, 0xC4));
        if (!node) return;
        if (h) {
            if (h->f4) *h->f4 = (s32)node;
        }
        func_0019E158(node, self);
        if (h) {
            if (h->f8) {
                typedef void (*F)(Node_157320*, s32);
                (*(F*)(AT(u8*, node, 0) + 0x6C))(node, h->f8);
            }
        }
    }
    if (node) {
    for (i = 0; i < n; i++) {
        Item_157320* it = func_0019EA78(AT(s32, c, 0x90), node);
        if (!it) break;
        Q_157320* s1 = pos + i;
        u8* cls = AT(u8*, it, 0);
        f32 f = func_001EAAE0(AT(f32, c, 0xB0), AT(f32, c, 0xB4));
        typedef void (*F0)(Item_157320*, Q_157320*, s32, f32);
        (*(F0*)cls)(it, s1, AT(s32, c, 0xC0), f);
        f32 f1 = AT(f32, c, 0xA4);
        if (f1 != 0.0f || AT(f32, c, 0xA8) != 0.0f) {
            AT(f32, it, 0x34) = f1;
            AT(f32, it, 0x38) = AT(f32, c, 0xA8);
        }
        AT(Q_157320, it, 0xA0) = q2[i];
        AT(f32, it, 0x18) = v5[i];
        AT(f32, it, 0x1C) = v6[i] - v5[i];
        AT(Q_157320, it, 0x40) = AT(Q_157320, self, 0x110);
        func_001583E8((Item_157320*)((u8*)it + 0xB0), self);
        if (AT(s32, c, 0xB8)) AT(s32, it, 0x20) = AT(s32, c, 0xB8);
        if (s7) {
            AT(Q_157320, it, 0x50) = AT(Q_157320, s7, 0x110);
            AT(Q_157320, it, 0x60) = AT(Q_157320, s7, 0x120);
            AT(Q_157320, it, 0x70) = AT(Q_157320, s7, 0x130);
        }
        if (AT(s32, c, 0x94) != -1) {
            Node_157320* o = (Node_157320*)func_0019EA78(AT(s32, c, 0x94), 0);
            if (!o) break;
            typedef void (*F1)(f32, Node_157320*, void*, s32);
            F1 fn = *(F1*)(*(u8**)o);
            fn(AT(f32, it, 0x30) * 0.5f, o, (u8*)it + 0x80, 0);
            func_001A0338(o, 1, it);
        }
        {
            u8* cl = AT(u8*, it, 0);
            VFn* p = (VFn*)(cl + 4);
            if (*p) ((void (*)(Item_157320*, Self_157320*))*p)(it, self);
        }
    }
    if (func_00152720((u8*)node + 0x558)) {
        typedef void (*F2)(Node_157320*);
        (*(F2*)(AT(u8*, node, 0) + 0x1C))(node);
    }
    }
}
