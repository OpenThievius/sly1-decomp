// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Point2 { f32 x, y; };

// Points recorded in order, the first of them scaled into u and v.
struct Trail
{
    u8 pad[0xC];
    s32 count;
    Point2 points[6];
    f32 spare;
    f32 u, v;
};

void func_0015C8B8(Trail* trail, f32 su, f32 sv)
{
    Point2* point = &trail->points[trail->count++];
    point->x = trail->u;
    point->y = trail->u;
    trail->u = trail->points[0].x * su;
    trail->v = trail->points[0].y * sv;
}

extern s32 D_00262268[];
extern s32 D_0026227C;

s32 func_0015C1C0(s32 a)
{
    if (a == -1) {
        return 0;
    }
    s32 v = D_00262268[a];
    if (v != 0) {
        return v;
    }
    return D_0026227C;
}

s32 func_0015DAB8(void* a, s32 b);

s32 func_0015CA38(void* a, s32 b)
{
    return func_0015DAB8(a, (s8)b) != 0;
}

void func_0015DB80(void* self);
s32 func_0015DBE0(void* self);

s32 func_0015DF58(void* self)
{
    s32 n = 0;
    func_0015DB80(self);
    while (func_0015DBE0(self) != 0) {
        n++;
    }
    return n;
}

struct Frame_15EB20 {
    u8 scratch[0x80];
    u8 obj[0x30];
};

extern u8 D_00212160[];
extern u8 D_00215C50[];

void func_001611B8(void* p);
void func_001529C8(void* p, s32 n, void* q);
void func_001613C0(void* p, s32 a, s32 b, s32 c);
void func_00161708(void* p, s32 a, s32 b);
void func_00161200(void* p);
void func_001EE450(void* self);
void func_001EE8D0(void* self, void* p);
void func_0015EAE0(void* self, void* a, void* b);
void func_00152D30(void* self);
void func_001529E0(void* self, void* p, s32 n);

void func_0015EB20(void* self, void* p, s32 n)
{
    Frame_15EB20 fr;
    void* buf = fr.obj;
    func_001611B8(buf);
    func_001529C8(buf, 8, fr.scratch);
    func_001613C0(buf, 0, 1, 0xE);
    func_00161708(buf, 0x61, 0);
    func_00161200(buf);
    func_001EE450(self);
    func_001EE8D0(self, buf);
    func_0015EAE0(self, D_00212160, D_00215C50);
    func_00152D30(self);
    func_001529E0(self, p, n);
}

struct Owner_15F678
{
    u8 pad[0x1ED0];
    s32 count;
    void** items;
};

void func_0015F678(Owner_15F678* owner, u8* obj)
{
    u64 flags = *(u64*)(obj + 0x2C8);
    u64 bit = (u64)0x8000 << 24;
    if (!(flags & bit))
    {
        *(u64*)(obj + 0x2C8) = flags | bit;
        s32 n = owner->count;
        owner->items[n] = obj;
        owner->count = n + 1;
    }
}

void func_0015FA58(void* self);
void func_0015FD78(void* self);

void func_0015FF58(void* self)
{
    func_0015FA58(self);
    func_0015FD78(self);
}

struct Rec_15C9B0 {
    u8 pad0[0x50];
    s32 f50;
    s32 f54;
    s32 f58;
    u8 pad5C[4];
    s64 f60;
    s32 f68;
    s32 f6C;
    s32 f70;
    s32 f74;
    s32 f78;
    s32 f7C;
    s32 f80;
};

void func_0015C260(void* self, void* dst);

void func_0015C9B0(Rec_15C9B0* self, Rec_15C9B0* dst)
{
    func_0015C260(self, dst);
    dst->f50 = self->f50;
    dst->f54 = self->f54;
    dst->f58 = self->f58;
    dst->f60 = self->f60;
    dst->f68 = self->f68;
    dst->f6C = self->f6C;
    dst->f70 = self->f70;
    dst->f74 = self->f74;
    dst->f78 = self->f78;
    dst->f7C = self->f7C;
    dst->f80 = self->f80;
}

struct Entry_15CA60 {
    u16 key;
    u8 pad2[4];
    u16 value;
};

struct Owner_15CA60 {
    u8 pad0[4];
    s32 a4;
    u8 pad8[0x3C];
    f32 a44;
};

Entry_15CA60* func_0015DAB8(void* table, s8 key);

f32 func_0015CA60(Owner_15CA60* self, s8 key)
{
    Entry_15CA60* e = func_0015DAB8(self, key);
    f32 x;
    f32 y;
    if (e == 0) {
        x = self->a44;
        y = (f32)self->a4;
    } else {
        x = (f32)(e->value + 1);
        y = self->a44;
    }
    return x * y;
}

struct Flags_15CAB8 {
    u8 pad0[0x18];
    u32 flags;
};

struct PairA_15CAB8 {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
};

struct PairB_15CAB8 {
    u8 pad0[8];
    s32 f8;
    s32 fC;
};

struct Obj_15CAB8 {
    u8 pad0[0x54];
    PairA_15CAB8* pa;
    PairB_15CAB8* pb;
    u8 pad5C[0xC];
    s32 f68;
    s32 f6C;
    s32 f70;
    s32 f74;
    u8 pad78[8];
    u32 mask;
};

extern Flags_15CAB8* D_002622D8;

void func_00152D70(void* obj);
void func_00152B80(void* obj, s32 a, s32 b);
void func_00152B38(void* obj);

s32 func_0015CAB8(Obj_15CAB8* self, void* obj)
{
    s32 r = (D_002622D8->flags & self->mask) == 0;
    if (r != 0) {
        func_00152D70(obj);
        func_00152B80(obj, self->f68, self->f6C);
        func_00152B80(obj, self->pa->f14, self->pa->f10);
        if (self->pb != 0) {
            func_00152B80(obj, self->f70, self->f74);
            func_00152B80(obj, self->pb->fC, self->pb->f8);
        }
        func_00152B38(obj);
        D_002622D8->flags |= self->mask;
    }
    return r;
}

struct Flags_15CB88 {
    u8 pad0[0x18];
    u32 flags;
};

struct PairA_15CB88 {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
};

struct PairB_15CB88 {
    u8 pad0[8];
    s32 f8;
    s32 fC;
};

struct Obj_15CB88 {
    u8 pad0[0x30];
    s32 f30;
    u8 pad34[4];
    s64 f38;
    u8 pad40[0x20];
    s64 f60;
    u8 pad68[0x18];
    u32 mask;
};

void func_0015C2E8(void* a0, s32 a1, void* a2);
s32 func_0015CAB8(Obj_15CB88* self, void* obj);
void func_001613C0(void* obj, s32 a, s32 b, s32 c);
void func_00161708(void* obj, s32 tag, s64 value);
void func_00161768(void* obj, s32 tag, s64 value);

void func_0015CB88(Obj_15CB88* self, s32 a1, void* obj)
{
    func_0015C2E8(self, a1, obj);
    s32 ok = func_0015CAB8(self, obj);
    func_001613C0(obj, 6, 1, 0xE);
    if (ok != 0) {
        func_00161708(obj, 0x3F, 0);
    }
    s64 v = 0x31001;
    if (self->f30 != 0) {
        v = self->f38;
    }
    func_00161708(obj, 0x47, v);
    func_00161708(obj, 0x42, 0x44);
    func_00161708(obj, 6, self->f60);
    func_00161708(obj, 0x14, 0x60);
    func_00161708(obj, 8, 5);
    func_00161708(obj, 0, 0x1D6);
    func_00161768(obj, 5, 0x43431);
}

struct Flags_15CC80 {
    u8 pad0[0x18];
    u32 flags;
};

struct PairA_15CC80 {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
};

struct PairB_15CC80 {
    u8 pad0[8];
    s32 f8;
    s32 fC;
};

struct Obj_15CC80 {
    u8 pad0[0x54];
    PairA_15CC80* pa;
    PairB_15CC80* pb;
    u8 pad5C[4];
    s64 f60;
    u8 pad68[0x18];
    u32 mask;
};

s32 func_0015CAB8(Obj_15CC80* self, void* obj);

void func_0015CC80(Obj_15CC80* self, void* obj)
{
    s32 ok = func_0015CAB8(self, obj);
    func_001613C0(obj, 6, 1, 0xE);
    if (ok != 0) {
        func_00161708(obj, 0x3F, 0);
    }
    func_00161708(obj, 6, self->f60);
    func_00161708(obj, 0, 0x1D6);
    func_00161768(obj, 5, 0x43431);
}

extern s32 D_0026227C;

void func_0015C178(void)
{
    D_0026227C = 0;
}

struct Record_0015C260 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 count0C;
    u8 body10[0x20];
    s32 f30;
    s64 f38;
    s32 f40;
    f32 f44;
    f32 f48;
};

void func_0018D800(void* dst, void* src, s32 size);

void func_0015C260(Record_0015C260* src, Record_0015C260* dst)
{
    dst->f00 = src->f00;
    dst->f04 = src->f04;
    dst->f08 = src->f08;
    dst->f44 = src->f44;
    dst->f48 = src->f48;
    dst->count0C = src->count0C;
    func_0018D800(dst->body10, src->body10, src->count0C << 3);
    dst->f30 = src->f30;
    dst->f38 = src->f38;
    dst->f40 = src->f40;
}

struct Pair_15EF88 { u8 pad0[0x4]; s32 f4; u8 pad8[0x4]; s32 fC; };

extern s32 D_00261F18;
extern s32 D_00261F1C;

void func_0015ED50(void* a, s32 b);
void func_001686E8(s32 a, s32 b);

void func_0015EF88(Pair_15EF88* self, s32 flag)
{
    func_0015ED50(self, flag);
    func_001686E8(D_00261F18, self->fC);
    if (flag != 0) {
        *(volatile s32*)0x10003010 = 0;
        func_001686E8(D_00261F1C, self->f4);
    }
}

extern u8 D_00262280[];
extern u8 D_002622A8[];

void func_001611B8(void* p);
void func_001EE318(void* p);

void func_0015F618(s32 flag, s32 code)
{
    if (code == 0xFFFF && flag != 0) {
        func_001611B8(D_00262280);
        func_001EE318(D_002622A8);
    }
}

void func_0015F618(s32 flag, s32 code);

void func_0015F658(void)
{
    func_0015F618(1, 0xFFFF);
}
