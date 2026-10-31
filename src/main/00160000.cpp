// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern u8 D_002623D0[];

void* func_00160110();

void* func_00160148()
{
    void* p = func_00160110();
    if (p == 0)
    {
        return D_002623D0;
    }
    return *(void**)((u8*)p + 0x24);
}

s32* func_00160810();

s32 func_00160850()
{
    s32* p = func_00160810();
    s32 value = 0;
    if (p)
    {
        value = *p;
    }
    return value;
}

struct Refs_160D00
{
    u8 pad[4];
    s32 refs;
};

void func_00160D00(Refs_160D00* self)
{
    self->refs--;
}

struct Stream_161458 {
    u8 pad0[0xC];
    u32* cur;
};

void func_001612E8(void* self, s32 a1, s32 a2);

void func_00161458(Stream_161458* self, u32 value)
{
    func_001612E8(self, 1, 1);
    u32* p = self->cur;
    self->cur = p + 4;
    p[0] = value & 0xFF;
    p[1] = (value & 0xFF00) >> 8;
    p[2] = (value >> 16) & 0xFF;
    p[3] = value >> 24;
}

struct Stream_161670 {
    u8 pad0[0xC];
    u32* cur;
};

void func_00161670(Stream_161670* self, u32 a1, u32 a2, u32 a3, u32 a4)
{
    func_001612E8(self, 1, 4);
    u32* p = self->cur;
    self->cur = p + 4;
    p[0] = a1;
    p[1] = a2;
    p[2] = (a3 & 0xFFFFFF) << 4;
    p[3] = ((a4 & 0xFF) << 4) | 0x8000;
}

struct Stream_1618C0 {
    u8 pad0[0xC];
    u64* cur;
};

void func_001618C0(Stream_1618C0* self, s32 a1, s32 a2, u32 a3, u32 a4)
{
    func_001612E8(self, 0, 4);
    u64 lo = (u64)a1 | (u64)(a2 << 16);
    u64 mid = a3 & 0xFFFFFF;
    u64* p = self->cur;
    self->cur = p + 1;
    *p = (lo | (mid << 32)) | ((u64)a4 << 56);
}

struct __attribute__((packed)) Unaligned_1626A8 { u32 value; };

void func_001626A8(u8* dst, u8* src)
{
    *(Unaligned_1626A8*)(dst + 0x114) = *(Unaligned_1626A8*)src;
}

struct Entry_001601D8 { u8 pad0[0x28]; s32 f28; };

Entry_001601D8* func_00160110(void* a0);

s32 func_001601D8(void* a0)
{
    Entry_001601D8* e = func_00160110(a0);
    s32 r = 0;
    if (e != 0) {
        r = e->f28;
    }
    return r;
}

struct Glob_002623C0 { u8 pad0[0xC]; f32 fC; u8 pad1[0x19C8]; s32 f19D8; s32 f19DC; s32 f19E0; s32 f19E4; u8 pad2[8]; s32 mask; s32 f19F4; s32 f19F8; };
extern Glob_002623C0* D_002623C0;

s32 func_001602A0(void);

void func_001604B8(s32 mode)
{
    switch (mode) {
    case 2:
        D_002623C0->f19F4 |= 0xA002;
        D_002623C0->f19F8 |= 2;
        break;
    case 4:
        if ((func_001602A0() & 4) != 0) {
            D_002623C0->f19F4 |= 0xC000;
        }
        break;
    case 8:
        if ((func_001602A0() & 8) != 0) {
            D_002623C0->f19F4 |= 0xC;
            D_002623C0->f19F8 |= 0xC;
        }
        break;
    }
}

struct Obj_002623C4 { u8 pad0[0x444]; f32 f444; s32 f448; };
struct Blk_002623C8 { s32 f0; f32 f4; };

extern Obj_002623C4* D_002623C4;
extern Blk_002623C8* D_002623C8;
extern s32 D_002623CC;
extern u8 D_00261420[];

s32 func_001601A0(s32 a0);
void func_001608E0(void);
void func_00140F48(u8* p);
void func_00140D90(u8* p);
void func_00160880(void);

void func_00160690(s32 a0, s32 flags)
{
    s32 r = func_001601A0(a0);
    s32 hi = (r != -1) ? (r >> 8) : 0;
    s32 lo = (r != -1) ? (r & 0xFF) : 0;
    u8* base = (u8*)D_002623C0 + (hi * 0x44C + 0x10);
    Glob_002623C0* g = D_002623C0;
    s32 gate = g->f19E0;
    D_002623C4 = (Obj_002623C4*)base;
    D_002623C8 = (Blk_002623C8*)(base + lo * 0x78);
    if (gate < 0 || (flags & 2) != 0) {
        func_001608E0();
    } else if ((flags & 1) != 0) {
        func_00140F48(D_00261420);
    } else if ((flags & 4) != 0) {
        func_00160880();
    } else {
        func_00140D90(D_00261420);
    }
    g = D_002623C0;
    D_002623CC = g->f19D8;
    g->f19D8 = hi;
    g->f19DC = lo;
    D_002623C4->f448 |= 1;
    D_002623C8->f0 |= 1;
}

void func_001607D0(f32 dx)
{
    D_002623C0->fC += dx;
    D_002623C4->f444 += dx;
    D_002623C8->f4 += dx;
}

struct Vec3_162680 { f32 x; f32 y; f32 z; };

struct Body_162680 { u8 pad[0xFC]; f32 x; f32 y; f32 z; };

void func_00162680(Body_162680* body, Vec3_162680* v)
{
    body->x = v->x;
    body->y = v->y;
    body->z = v->z;
}

struct __attribute__((packed)) U64_1626C0 { u64 v; };

struct Src_1626C0 { U64_1626C0 head; };

struct Dst_1626C0 { u8 pad[0x118]; U64_1626C0 tail; };

void func_001626C0(Dst_1626C0* dst, Src_1626C0* src)
{
    dst->tail.v = src->head.v;
}

void* func_0018D500(s32 size);

struct Item_162810 { u8 pad[0x38]; void* ref; u8 rest[0x70 - 0x3C]; };

struct Owner_162810
{
    u8 pad0[0xC];
    s32 count;
    Item_162810* items;
    u8 pad1[0x50 - 0x14];
    s32 capacity;
    void** refs;
};

void func_00162810(Owner_162810* owner)
{
    owner->refs = (void**)func_0018D500(owner->capacity << 2);
    s32 n = 0;
    for (s32 i = 0; i < owner->count; i++) {
        void* ref = owner->items[i].ref;
        if (ref != 0)
            owner->refs[n++] = ref;
    }
}

void* func_001F5C0C(void* p, s32 value, s32 size);

void func_00160CC8(void* p)
{
    func_001F5C0C(p, 0, 8);
}

struct Counter_160CE8
{
    u8 pad[4];
    s32 count;
};

void func_00160CE8(Counter_160CE8* c)
{
    c->count = 0;
}

struct Counter_160CF0
{
    u8 pad[4];
    s32 count;
};

s32 func_00160CF0(Counter_160CF0* c)
{
    return ++c->count;
}

struct Ctx_160D10
{
    u8 pad[0x235C];
    s32 bits;
};

extern Ctx_160D10* D_00275710;

s32 func_00160D10()
{
    return D_002623C0->mask & D_00275710->bits;
}

void func_0018D778(void);

void func_00161A88(void* self, s32 flag)
{
    (void)self;
    if (flag & 1) {
        func_0018D778();
    }
}

void func_00162508(void* self);
void func_00188B08(void* a, void* b, void* c);
void func_00188B48(void* a, void* b, void* c);

void func_00161AB0(u8* self, void* a1, void* a2)
{
    func_00162508(self);
    func_00188B08(a1, a2, self);
    func_00188B48(a1, a2, self + 0x40);
}

struct Obj_00161BB0 {
    u8 pad0[0xF8];
    s32 f0F8;
};

void func_00162508(void* self);
void func_001626A8(void* self, u32* value);

void func_00161BB0(Obj_00161BB0* self, s32 value)
{
    u32 local;
    func_00162508(self);
    self->f0F8 = value;
    local = 0xFFFFFFFF;
    func_001626A8(self, &local);
}

s32 func_00160180(void)
{
    return (s32)func_00160110();
}

struct Rec_1600A0 { u8 pad[0x20]; s32 value; };

Rec_1600A0* func_001600A0(void);

s32 func_001601A0(void)
{
    s32 v;
    Rec_1600A0* r = func_001600A0();
    v = -1;
    if (r != 0) v = r->value;
    return v;
}

struct __attribute__((packed)) Word_269984 { u32 value; };

extern u8 D_002623D8[];
extern u8 D_00261EF0[];
extern Word_269984 D_00269984;
extern s32 D_00262C64;
extern s32 D_002623CC;

void func_001605E8(void* self);
void func_00160CC8(void* self);
void func_00151A68(void* self);
void func_001608E0(void);

void func_00160880(void)
{
    func_001605E8(D_002623C0);
    D_00269984.value = 0;
    func_00160CC8(D_002623D8);
    func_00151A68(D_00261EF0);
    D_00262C64 = 0;
    D_002623CC = -1;
    func_001608E0();
}

void func_001612E8(void* self, s32 a1, s32 a2);

struct Stream_1615F0 {
    u8 pad0[0xC];
    u32* cur;
};

void func_001615F0(Stream_1615F0* self, u32 a1, u32 a2, u32 a3, u32 a4)
{
    func_001612E8(self, 1, 4);
    u32* p = self->cur;
    self->cur = p + 4;
    p[0] = a1;
    p[1] = a2;
    p[2] = a3;
    p[3] = (a4 & 0xFF) << 4;
}

void func_001612E8(void* self, s32 a1, s32 a2);

struct Stream_161708 {
    u8 pad0[0xC];
    u64* cur;
};

void func_00161708(Stream_161708* self, u64 a1, u64 a2)
{
    func_001612E8(self, 1, 14);
    u64* p = self->cur;
    self->cur = p + 2;
    p[0] = a2;
    p[1] = a1;
}

typedef void (*Fn_161768)(void* self, s32 a1);

struct Adjust_161768 { u8 pad0[8]; s16 adj; u8 pad1[2]; Fn_161768 fn; };

struct Obj_161768 {
    u8 pad0[0xC];
    u64* cur;
    u8 pad1[8];
    Adjust_161768* sub;
    u64* last;
    u32 f20;
    s32 f24;
};

void func_00161768(Obj_161768* self, u32 a1, u64 a2)
{
    Adjust_161768* sub = self->sub;
    sub->fn((u8*)self + sub->adj, 0);
    u64* p = self->cur;
    self->cur = p + 2;
    p[1] = a2;
    p[0] = ((u64)a1 << 60) | ((u64)0x8000 << 43);
    self->f20 = a1;
    self->last = p;
    self->f24 = 0;
}

void func_00160C48(s32 value)
{
    D_002623C0->f19E4 = value;
}

struct Stream_1617E8 { u8 pad0[0xC]; u8* cur; };

void func_001612E8(void* self, s32 a1, s32 a2);

void func_001617E8(Stream_1617E8* self, s32 tag, f32 value)
{
    func_001612E8(self, 0, 1);
    s32 bits = *(s32*)&value;
    u64 hi = (u64)(s64)bits << 32;
    u64 lo = (u64)(u32)tag;
    u64* p = (u64*)self->cur;
    self->cur = (u8*)(p + 1);
    *p = lo | hi;
}

s32 func_00160D98(void)
{
    return 2;
}

struct Rec_160E80 { u8 pad0[4]; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; s32 f18; };

void func_00160E80(Rec_160E80* self)
{
    self->f4 = 0;
    self->f8 = 0;
    self->fC = 0;
    self->f10 = 0;
    self->f14 = 0;
    self->f18 = 0;
}

typedef void (*Fn_161200)(void* self, s32 a);
struct Sub_161200 { u8 pad0[8]; s16 off8; u8 pad1[2]; Fn_161200 fn; };
struct Obj_161200 { u8 pad0[0x18]; Sub_161200* f18; s32 f1C; };

void func_001613C0(void* self, s32 a, s32 b, s32 c);

void func_00161200(Obj_161200* self)
{
    if (self->f1C != 0) {
        Sub_161200* s = self->f18;
        s->fn((u8*)self + s->off8, 1);
    } else {
        func_001613C0(self, 0, 1, 0xE);
        Sub_161200* s = self->f18;
        s->fn((u8*)self + s->off8, 1);
    }
}

struct Obj_00160050 { u8 pad[0x34]; s32 count; s32 values[1]; };
void func_00160050(Obj_00160050* obj, s32 value) { obj->values[obj->count++] = value; }

struct Obj_1612E8 { u8 pad[0x24]; s32 value; };
s32 func_001612E8(Obj_1612E8* obj) { return ++obj->value; }

void func_00160918();
void func_00160070() { func_00160918(); }

s32 func_00160C58()
{
    s32 result=0;
    if (D_002623C0->f19E4>0 || (D_00262C64&2)) result=1;
    return result;
}

void* func_00160CA0(u8* self,s32 index)
{
    if ((u32)(index-0x33B)>=12) return 0;
    else return self+(index*4-0xCD8);
}

void func_001614C8(Stream_161458* self,s32 a,s32 b)
{
    func_001612E8(self,1,3);
    s32* p=(s32*)self->cur;
    self->cur+=4;
    p[0]=a;
    p[1]=b;
}

void func_00161520(Stream_161458* self,f32 a,f32 b,f32 c)
{
    func_001612E8(self,1,2);
    f32* p=(f32*)self->cur;
    self->cur+=4;
    p[0]=a;
    p[1]=b;
    p[2]=c;
}

typedef void* (*Fill_161B80)(void*,s32,s32);
void func_00161B80(u8* self)
{
    *(s32*)(self+0xF8)=0;
    *(s32*)(self+0x124)=0;
    ((Fill_161B80)func_001F5C0C)(self+0x128,0,0x1720);
}

struct Stream_161588 {
    u8 pad0[0xC];
    u8* cur;
};

void func_001612E8(void* self, s32 a1, s32 a2);

void func_00161588(Stream_161588* self, s32 a1, s32 a2, u64 a3)
{
    func_001612E8(self, 1, 5);
    u8* p = self->cur;
    self->cur = p + 0x10;
    *(s32*)(p + 0x0) = a1;
    *(s32*)(p + 0x4) = a2;
    *(u64*)(p + 0x8) = a3;
}

struct Stream_161860 {
    u8 pad0[0xC];
    u64* cur;
};

void func_001612E8(void* self, s32 a1, s32 a2);

void func_00161860(Stream_161860* self, s32 a1, s32 a2)
{
    func_001612E8(self, 0, 3);
    u64 v = (u64)a1 | (u64)(a2 << 16);
    u64* p = self->cur;
    self->cur = p + 1;
    *p = v;
}

struct Ctx_161028 { u8 pad0[4]; s32 count; u8* base; };
struct Entry_161028 { s16 k0; s16 k1; u8 pad[4]; Entry_161028* next; };
struct Holder_161028 { u8 pad0[0x14]; Entry_161028* head; };
struct Elem_161028 { Holder_161028* holder; u8 pad[8]; };

void func_0018D608(void);
u8* func_0018D658(s32 size);
void func_0018D6F0(void);
s32 func_0013E430(u8* a0, u8* a1, s32* a2, f32 scale);

s32 func_00161028(Ctx_161028* dst, Ctx_161028* src, s32 key, s32 maxOut, Entry_161028** out)
{
    s32 buf[4];

    func_0018D608();
    u8* k = func_0018D658(src->count * 12);
    buf[0] = (s32)k;
    if (func_0013E430(src->base, dst->base + key * 16, buf, 1.0f) != 2) {
        func_0018D6F0();
        return 0;
    }
    s32 i = 0;
    s32 n = (((s32)buf[0] - (s32)k) * (s32)0xAAAAAAAB) >> 2;
    s32 j = 0;
    if (n > 0) {
        for (; i < n; i++) {
            Elem_161028* e = (Elem_161028*)(k + i * 12);
            Entry_161028* p = e->holder->head;
            if (p == 0) {
                continue;
            }
            Entry_161028** o = (Entry_161028**)(j * 4 + (s32)out);
            while (p != 0) {
                if (key == p->k0 || key == p->k1) {
                    s32 m;
                    for (m = 0; m < j; m++) {
                        if (p == out[m]) {
                            break;
                        }
                    }
                    if (m >= j && j < maxOut) {
                        *o = p;
                        o++;
                        j++;
                    }
                }
                p = p->next;
            }
        }
    }
    func_0018D6F0();
    return j;
}

extern u8 D_000018C0[];
extern u8 D_000018F8[];

void func_001EE3F0(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void func_001EE3F0(void* s, s32 n);

typedef void (*Fn_1612F8)(void* self, s32 zero);
struct Sub_1612F8 { u8 pad0[8]; s16 off8; u8 pad1[2]; Fn_1612F8 fnC; };
struct Out_1612F8 { u8 pad0[0xC]; u8* cur0C; u8 pad1[0x18 - 0x10]; Sub_1612F8* sub18; };

void func_001612F8(void* self, u64 prim, s32 nloop, s32 nreg, u64 data, s32* out)
{
    Out_1612F8* w = (Out_1612F8*)self;
    Sub_1612F8* sub = w->sub18;
    sub->fnC((u8*)self + sub->off8, 0);

    u8* p = w->cur0C;
    u64 tag = (prim << 47) | (1ULL << 46) | (u64)nloop | ((u64)nreg << 60);
    w->cur0C = p + 16;
    *(u64*)(p + 8) = data;
    *(u64*)p = tag;
    if (out != 0) {
        *out = (s32)w->cur0C;
    }
    w->cur0C = w->cur0C + nloop * nreg * 16;
}

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void func_001EE3F0(void* obj, void* data);

void func_00163990(s32 mode, void* obj)
{
    switch (mode) {
    case 0:
        func_001EE3F0(obj, D_00000FA0);
        break;
    case 1:
        func_001EE3F0(obj, D_00000FD8);
        break;
    }
}

void* func_00160810(s32 key)
{
    return key == -1 ? 0 : (u8*)D_002623C0 + ((key >> 8) * 0x44C + 0x10) + (key & 0xFF) * 0x78;
}

extern u8 D_000018C0[];
extern u8 D_000018F8[];

void func_001EE3F0(void* obj, void* text);

void func_00163938(s32 mode, void* obj)
{
    switch (mode) {
    case 0:
        func_001EE3F0(obj, D_000018C0);
        break;
    case 1:
        func_001EE3F0(obj, D_000018F8);
        break;
    }
}

struct Obj_001605E8
{
    s32 a;
    s32 b;
    u8 pad0[0x19D8 - 8];
    s32 c;
    u8 pad1[0x19DC - 0x19D8 - 4];
    s32 d;
    s32 e;
    u8 pad2[0x19F0 - 0x19E0 - 4];
    s32 f;
    u8 pad3[0x19FC - 0x19F0 - 4];
    s32 g;
};

void func_001A7E90(void* self);

void func_001605E8(Obj_001605E8* self)
{
    func_001F5C0C(self, 0, 0x1A00);
    self->a = 0x12;
    self->c = 0;
    self->f = 0;
    self->b = 0x1A00;
    self->d = 3;
    self->e = 5;
    self->g = -1;
    func_001A7E90(self);
}

struct Key_160948 {
    u8 pad_000[8];
    s32 f8;
    u8 pad_00C[0xC];
    s32 f18;
    s32 Same(Key_160948* o)
    {
        if (this == o) {
            return 1;
        }
        if (this == 0) {
            return 0;
        }
        if (o == 0) {
            return 0;
        }
        return ((f8 ^ f18) ^ (o->f8 ^ o->f18)) == 0;
    }
};

struct Frame_160948;
extern Frame_160948* D_0027B314;

struct Lst_160948 {
    void* head;
    s32 pad4;
    s32 next_off;
};

struct Frame_160948 {
    void* list;
    void* cursor;
    s32 next_off;
    Frame_160948* prev;
    Frame_160948(Lst_160948* l)
    {
        list = l;
        cursor = l;
        next_off = l->next_off;
        prev = D_0027B314;
        D_0027B314 = this;
    }
    ~Frame_160948() { D_0027B314 = prev; }
    void* Next()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + next_off;
        return n;
    }
};

struct Ctx_160948 {
    u8 pad0[0xC];
    f32 fC;
    u8 pad10[0x19D8 - 0x10];
    s32 f19D8;
    s32 f19DC;
    u8 pad19E0[0x19EC - 0x19E0];
    s32 f19EC;
};

struct Rec_160948 {
    u8 pad0[0x6C];
    void* head;
};

extern u8 D_002623D8[];
struct Sys_160948 { u8 pad0[0x30]; s32 f30; };
extern Sys_160948 D_00275BC0;
extern Key_160948 D_00275B04;
extern Key_160948 D_00247AB0;
extern s32 D_00275F84;

Key_160948* func_00160180(s32 key);
void func_00160CC8(void* p);
void func_001F0428(void* a, s32 b, s32 c);
void func_001C0760(s32 flag);
void func_001C0790(s32 flag);
Rec_160948* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_0012E760(void* obj);
void func_001E96F8(void* obj, s32 mode);

void func_00160948(void)
{
    Key_160948* k = func_00160180((((Ctx_160948*)D_002623C0)->f19D8 << 8) | ((Ctx_160948*)D_002623C0)->f19DC);
    if (k == 0) {
        k = &D_00247AB0;
    }
    func_00160CC8(D_002623D8);
    if (D_00275BC0.f30 != 1 || ((Ctx_160948*)D_002623C0)->fC != 0.0f || !k->Same(&D_00275B04)) {
        func_001F0428(k, -1, 1);
    } else if (D_00275BC0.f30 == 1) {
        if (D_00275F84 == 0) {
            func_001C0760(((Ctx_160948*)D_002623C0)->f19EC & 0x80);
            func_001C0790(((Ctx_160948*)D_002623C0)->f19EC & 0x40);
            Rec_160948* r = func_0015A418(D_00275710, 0x105, 0x494, 0);
            if (r != 0) {
                Frame_160948 frame((Lst_160948*)((u8*)r + 0x6C));
                void* head = r->head;
                frame.cursor = (u8*)head + frame.next_off;
                void* node = head;
                if (node != 0) {
                    do {
                        func_0012E760(node);
                        node = frame.Next();
                    } while (node != 0);
                }
            }
            D_00275BC0.f30 = -1;
            func_001E96F8(&D_00275BC0, 3);
        }
    }
}

extern u8 D_000018C0[];
extern u8 D_000018F8[];

void func_001EE3F0(void* s, s32 n);

extern u8 D_00000FA0[];
extern u8 D_00000FD8[];

void func_001EE3F0(void* s, s32 n);

struct Sys_1608E0;
void func_00140D90(Sys_1608E0* p);

extern u8 D_00261420[];

void func_001608E0(void)
{
    u8* g = (u8*)D_002623C0;
    *(s32*)(g + 0x19E0) = 5;
    *(s32*)(g + 0x19E4) = 0;
    func_00140D90((Sys_1608E0*)D_00261420);
}

struct Args_160DA0 {
    s32 f0;
    u8* f4;
    s32 f8;
    s32 fC;
    s32 f10;
};

struct Call_160DA0;

extern u8 D_00275F80[];
extern u8 D_00261EF0[];
extern u8 D_00261420[];
extern u8 D_0026FF68[];

void func_001DDAD0(Call_160DA0* x);
void func_001BE708(void);
void func_001EFFA0(Call_160DA0* dst, Args_160DA0* args, s32 count);
void func_00140ED0(Call_160DA0* r);
void func_00194D30(Call_160DA0* self, s32 a, s32 b);
void func_00151E20(Call_160DA0* self, f32 amount);

void func_00160DA0(void)
{
    u8* o = (u8*)D_002623C0;
    u8* x = (u8*)D_00275710;
    s32 t = *(s32*)(o + 0x19E0) - 1;
    *(s32*)(o + 0x19E0) = t;
    func_001DDAD0((Call_160DA0*)x);
    func_001BE708();
    u8* p = (u8*)D_002623C0;
    s32 m = *(s32*)(p + 0x19DC);
    if (m == 1) {
        Args_160DA0 args;
        args.f0 = m;
        args.f4 = (u8*)&D_00275B04;
        u8* base = args.f4 - 0x14;
        args.f8 = *(s32*)(base + 0x8);
        args.fC = *(s32*)(base + 0xC);
        args.f10 = 0x10;
        func_001EFFA0((Call_160DA0*)D_00275F80, &args, 1);
    } else if (*(s32*)(p + 0x19E0) >= 0) {
        func_00140ED0((Call_160DA0*)D_00261420);
    } else {
        func_00194D30((Call_160DA0*)D_0026FF68, 0, 1);
    }
    func_00151E20((Call_160DA0*)D_00261EF0, 1.0f);
}

struct Ent_1600A0 {
    u8 pad0[8];
    s32 k0;
    u8 pad1[0xC];
    s32 k1;
    u8 pad2[0x10];
};

extern u8 D_00247AF0[];

Ent_1600A0* func_001600A0(Ent_1600A0* key)
{
    Ent_1600A0* p = (Ent_1600A0*)D_00247AF0;
    Ent_1600A0* end = (Ent_1600A0*)(D_00247AF0 + 0x7E8);
    s32 m;

    do {
        if (key == p) {
            m = 1;
        } else if (key == 0 || p == 0) {
            m = 0;
        } else {
            m = ((key->k0 ^ key->k1) ^ (p->k0 ^ p->k1)) == 0;
        }
        if (!m) {
            p = (Ent_1600A0*)((u8*)p + 0x2C);
        } else {
            return p;
        }
    } while (p < end);
    return 0;
}

extern u8 D_00247AF0[];

void* func_00160110(s32 key)
{
    u8* p = D_00247AF0;
    u8* end = D_00247AF0 + 0x7E8;
    for (;;) {
        if (key != *(s32*)(p + 0x20)) {
            p += 0x2C;
            if ((u32)p < (u32)end) {
                continue;
            }
            return 0;
        }
        return p;
    }
}

extern u8 D_00247AF0[];

struct Entry_00160208 { u8 pad0[0x20]; s32 key; s32 pad24; s32 flags; };

void func_00160208(s32 key, s32* a1, s32* a2, s32* a3)
{
    Entry_00160208* p;
    Entry_00160208* end;

    *a3 = 0;
    *a2 = 0;
    p = (Entry_00160208*)D_00247AF0;
    *a1 = 0;
    end = (Entry_00160208*)(D_00247AF0 + 0x7E8);
    do {
        if ((p->key >> 8) == key) {
            if (p->flags & 2) {
                (*a1)++;
            }
            if (p->flags & 4) {
                (*a2)++;
            }
            if (p->flags & 8) {
                (*a3)++;
            }
        }
        p++;
    } while (p < end);
}

extern u8 D_00247AF0[];
struct Key_1602A0;
u32* func_00160810(Key_1602A0* key);

s32 func_001602A0(void) {
    u32 mask = 0xE;
    u8* p = D_00247AF0;
    u8* end = D_00247AF0 + 0x7E8;
    do {
        u32* r = func_00160810((Key_1602A0*)*(void**)(p + 0x20));
        mask &= ~*(u32*)(p + 0x28) | *r;
        p += 0x2C;
    } while (p < end);
    s32 clear = -3;
    s32 n = 4;
    u8* q = (u8*)D_002623C0 + 0x8A4;
    do {
        u32 flag = *(u32*)q & 0x20;
        mask = (flag == 0) ? (mask & (u32)clear) : mask;
        q += 0x44C;
        n--;
    } while (n >= 0);
    return mask;
}

struct Obj_160578 { s32 f0; };

extern u8 D_00247AD0[];

void func_001F0428(Obj_160578* obj, s32 m, s32 n);
void func_0018E4F0(s32 slot, u32 n);

void func_00160578(s32 kind)
{
    s32 s0 = -1;

    if (kind != 4) { if (kind < 5) { if (kind == 2) { s0 = 0xD; } } } else { s0 = 0xE; }
    func_001F0428((Obj_160578*)D_00247AD0, -1, 1);
    if (s0 != -1) {
        func_0018E4F0(s0, 0xF);
    }
}

struct Obj_160918 { u8 pad[0]; };

void func_00160880(void);
void func_001F0428(Obj_160918* obj, s32 value, s32 count);

void func_00160918(void)
{
    func_00160880();
    func_001F0428((Obj_160918*)&D_00247AB0, -1, 0);
}

struct Self_1611B8 { u8 pad0[0x14]; s32 f14; void* f18; s32 f1C; s32 f20; s32 f24; };
extern u8 D_0024A6F8[];
s32 func_00152888(Self_1611B8* a);

Self_1611B8* func_001611B8(Self_1611B8* self)
{
    (void)func_00152888(self);
    self->f14 = 1;
    self->f18 = D_0024A6F8;
    self->f1C = 0;
    self->f20 = 0;
    self->f24 = 0;
    return self;
}

void func_00160340(s32 n)
{
    switch (n) {
    case 1: D_002623C0->f19F4 |= 0x10; break;
    case 2: D_002623C0->f19F4 |= 0x40; break;
    case 3: D_002623C0->f19F4 |= 0x100; break;
    case 4: D_002623C0->f19F4 |= 0x400; break;
    case 5: D_002623C0->f19F4 |= 0x1000; break;
    }
}

struct Rec_1603E8 { s32 flags; u8 pad[0x448]; };
struct Glob_1603E8 { u8 pad0[0x458]; Rec_1603E8 recs[1]; };
void func_001604B8(s32 mode);

void func_001603E8(s32 n)
{
    ((Glob_1603E8*)D_002623C0)->recs[n].flags |= 0x20;
    switch (n) {
    case 1:
        D_002623C0->f19F4 |= 0x20;
        break;
    case 2:
        D_002623C0->f19F4 |= 0x80;
        break;
    case 3:
        D_002623C0->f19F4 |= 0x200;
        D_002623C0->mask |= 0x10000;
        break;
    case 4:
        D_002623C0->f19F4 |= 0x800;
        break;
    case 5:
        func_001604B8(2);
        break;
    }
}

void func_00160D30(u32* out)
{
    s32 m;
    switch (D_002623C0->f19D8) {
    case 4: m = 0x10000000; break;
    case 1: m = 0x20000000; break;
    case 2: m = 0x40000000; break;
    case 3: m = 0x80000000; break;
    case 0:
    case 5: m = 0; break;
    }
    if (out) *out = m;
}

// EXACT: self->block store ahead of self->f20 store.

typedef void (*Fn_1613C0)(void* self, s32 mode);

struct Desc_1613C0 {
    u8 pad0[8];
    s16 adj;
    u8 pad1[2];
    Fn_1613C0 fn;
};

struct Ctx_1613C0 {
    u8 pad0[0xC];
    u8* cur;
    u8 pad1[8];
    Desc_1613C0* desc;
    u8* block;
    s32 f20;
    s32 f24;
};

void func_001613C0(Ctx_1613C0* self, s32 a1, s32 a2, s32 a3)
{
    Desc_1613C0* d = self->desc;
    d->fn((u8*)self + d->adj, 0);
    u8* blk = self->cur;
    s64 lo = ((s64)a2 << 60) | ((s64)1 << 46);
    s64 hdr = ((s64)a1 << 47) | lo;
    self->cur = blk + 0x10;
    *(s64*)blk = hdr;
    *(s64*)(blk + 8) = (s64)a3;
    self->block = blk;
    self->f20 = a2;
    self->f24 = 0;
}

struct Pkt_1639E8;
struct Frame_1639E8
{
    s32 f0;
    u8* f4;
    u8 pad08[0x28];
};
struct Hdr_1639E8
{
    u16* p;
    s32 count;
};
struct Vec3_1639E8
{
    f32 x;
    f32 y;
    f32 z;
};
struct Ent_1639E8
{
    u16* idx;
    s32 pad;
};
struct Self_1639E8
{
    u8 pad00[0x40];
    s32 f40;
};
struct Rgba_1639E8
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

extern Rgba_1639E8 D_002623E0;
extern s32 D_002623E8[];
extern s32 D_00262400[];
extern u8 D_00001298[];
extern u8 D_00001368[];
extern u8 D_00000ED8[];

void func_001EE5C8(Pkt_1639E8* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void* func_001F5C0C(void* p, s32 value, s32 size);
void func_001611B8(Frame_1639E8* f);
void func_00152980(Frame_1639E8* f, s32 size);
void func_001613C0(Frame_1639E8* f, s32 a, s32 b, s32 c);
void func_00161708(Frame_1639E8* f, s32 a, u64 b);
void func_00161278(Frame_1639E8* f, s32 n);
void func_001EE668(Pkt_1639E8* s, s32 a, s32 b, void* data, s32 flags);
void func_001528E0(Frame_1639E8* f);
void func_001615F0(Frame_1639E8* f, s32 a1, s32 a2, s32 a3, s32 a4);
void func_001EE4C0(Pkt_1639E8* s, u32* src);
void func_001EE528(Pkt_1639E8* s, s32 value);
void func_001EE3F0(Pkt_1639E8* s, void* data);
void func_001EE480(Pkt_1639E8* s);
void func_00163990(s32 mode, Pkt_1639E8* obj);

struct Zero_1639E8
{
    static void Clear(u32* q)
    {
        func_001F5C0C(q, 0, 0x10);
    }
};

void func_001639E8(Self_1639E8* self, s32 mode, Hdr_1639E8* hdr, s32 n, Vec3_1639E8* vecs, s32 extra,
                   void* extraData, Ent_1639E8* ents, Vec3_1639E8* verts, void* data, Pkt_1639E8* pkt)
{
    Frame_1639E8 f;
    u32 buf[4];
    s32 i;
    Vec3_1639E8* out;
    s32 off = 0x2B;

    func_001EE5C8(pkt, 0xD, 2, 0x16, 0, hdr);
    func_001F5C0C(hdr->p, 0, 0x10);
    func_001611B8(&f);
    func_00152980(&f, 8);
    func_001613C0(&f, 0, 1, 0xE);
    func_00161708(&f, 0x42, 0x44);
    func_00161708(&f, 1, (u64)D_002623E0.r | ((u64)D_002623E0.g << 8) | ((u64)D_002623E0.b << 16)
                             | ((u64)D_002623E0.a << 24) | (1ULL << 32));
    func_00161278(&f, 1);
    func_001EE668(pkt, 0xC, 2, f.f4, 0x18);
    func_001528E0(&f);
    func_001613C0(&f, 0xC1, 3, 0x44E);
    func_00161708(&f, 0x47, 0x70000);
    func_001615F0(&f, 0, 0, 0, 0);
    func_001615F0(&f, 0, 0, 0, 0);
    func_00161278(&f, 0);
    func_001613C0(&f, 1, 3, 0x44E);
    func_00161708(&f, 0x47, 0x72001);
    func_001615F0(&f, 0, 0, 0, 0);
    func_001615F0(&f, 0, 0, 0, 0);
    func_00161278(&f, 1);
    func_001EE668(pkt, 0xC, 2, f.f4, 0x1B);
    func_001EE668(pkt, 0xC, 2, f.f4 + 0x40, 0x1F);
    func_001EE668(pkt, 0xC, 2, f.f4, 0x23);
    func_001EE668(pkt, 0xC, 2, f.f4 + 0x40, 0x27);

    hdr->p[0] = off;
    off += n;
    hdr->p[1] = off;
    func_001EE668(pkt, 8, n, vecs, hdr->p[0]);
    if (hdr->count > 0)
    {
        hdr->p[4] = off;
        off += hdr->count * 4;
        hdr->p[5] = off;
        Zero_1639E8::Clear(buf);
        off += n;
        func_001EE4C0(pkt, buf);
        func_001EE528(pkt, D_002623E8[hdr->count]);
        func_001EE668(pkt, D_00262400[hdr->count], n, data, hdr->p[5]);
        func_001EE528(pkt, 0);
    }
    s32 end = off + extra;
    if (self->f40 != 0)
    {
        hdr->p[5] = off;
        hdr->p[6] = self->f40 + off;
        for (i = 0; i < self->f40; i++)
        {
            func_001EE668(pkt, 0, 1, &i, 0x1D);
            func_001EE5C8(pkt, 8, n, hdr->p[6], 0, &out);
            u16* idx = ents[i].idx;
            for (s32 k = 0; k < n; k++)
            {
                Vec3_1639E8* v = &verts[idx[k]];
                out[k].x = v->x - vecs[k].x;
                out[k].y = v->y - vecs[k].y;
                out[k].z = v->z - vecs[k].z;
            }
            func_001EE3F0(pkt, D_00001298);
            func_001EE480(pkt);
        }
    }
    hdr->p[2] = off;
    hdr->p[3] = end;
    func_001EE668(pkt, 0xE, extra, extraData, hdr->p[2]);
    func_00163990(mode, pkt);
    func_001EE3F0(pkt, D_00001368);
    func_001EE3F0(pkt, D_00000ED8);
}
