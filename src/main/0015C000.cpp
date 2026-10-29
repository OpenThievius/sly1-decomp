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
