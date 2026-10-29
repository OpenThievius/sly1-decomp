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

struct Glob_002623C0 { u8 pad0[0xC]; f32 fC; u8 pad1[0x19C8]; s32 f19D8; s32 f19DC; s32 f19E0; u8 pad2[0xC]; s32 mask; s32 f19F4; s32 f19F8; };
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

void func_001F5C0C(void* p, s32 value, s32 size);

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
