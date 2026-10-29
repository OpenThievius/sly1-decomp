// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_18D168 { u8 pad0[4]; void* p4; void* p8; u8 pad1[0x18]; s32 p24; s32 p28; s32 p2C; };

s32 func_00209CB8(void* a, void* b, s32* c, s32* d, s32* e);
s32 func_0018BD00(s32 v, s32 code, s32 extra);

s32 func_0018D168(Obj_18D168* a0, s32* a1)
{
    s32 v = func_0018BD00(func_00209CB8(a0->p4, a0->p8, &a0->p24, &a0->p28, &a0->p2C), 1, 0);
    switch (v) {
    case 9: v = 0; break;
    case 10: v = 12; break;
    }
    if (v == 0) { *a1 = a0->p28 << 10; } else { *a1 = 0; }
    return v;
}

s32 func_00209870(void* a, void* b, void* c);
s32 func_0018BD00(s32 v, s32 code, void* extra);

s32 func_0018D2E8(void* a0, void* a1, void* a2, void* a3, void* a4)
{
    return func_0018BD00(func_00209870(a1, a2, a3), 5, a4);
}

void* func_0018D500(u32 n);
void func_001F5C0C(void* p, s32 v, s32 n);

void* func_0018D5C0(u32 n)
{
    void* p = func_0018D500(n);
    if (p) {
        func_001F5C0C(p, 0, n);
    }
    return p;
}

int func_0018D740(void)
{
    return 0;
}

struct Obj_18E678 { u8 pad0[4]; s32 f04; s32 f08; };

void func_0018E6A0(void* self);

void func_0018E678(Obj_18E678* self, s32 a1, s32 a2)
{
    self->f04 = a2;
    self->f08 = a1;
    func_0018E6A0(self);
}

int func_0018E938(void)
{
    return 1;
}

struct Obj_18FF28 {
    u8 pad0[0x5F0];
    s32 f5F0;
    u8 pad1[0xC38 - 0x5F4];
    s32 fC38;
    s32 fC3C;
    s32 fC40;
    s32 fC44;
};

extern u8 D_00269B60[];

void func_001C72A0(void* self);
void func_00124DF8(void* self, s32 n, void* table);
s32 func_001CA758(void* self, s32 id);

void func_0018FF28(Obj_18FF28* self)
{
    func_001C72A0(self);
    func_00124DF8(self, 2, D_00269B60);
    self->f5F0 = func_001CA758(self, 0xEF);
    self->fC38 = func_001CA758(self, 0x16C);
    self->fC3C = func_001CA758(self, 0x16D);
    self->fC40 = func_001CA758(self, 0x16A);
    self->fC44 = func_001CA758(self, 0x16B);
}

void func_0018D4F8(s32 size)
{
    (void)size;
}

extern u8* D_002C2A1C;

void func_0018D4F8(s32 size);

u8* func_0018D500(s32 size)
{
    u8* result;

    if (size == 0) {
        return 0;
    }
    func_0018D4F8(size);
    result = D_002C2A1C;
    D_002C2A1C = result + ((size + 15) & ~15);
    return result;
}

extern u8* D_002C2A18;

void func_0018D550(void)
{
    D_002C2A1C = D_002C2A18;
}

u8* func_0018D500(s32 size);
void func_0018D800(u8* dst, void* src, s32 count);

u8* func_0018D568(s32 size, void* src)
{
    u8* result = func_0018D500(size);

    if (result != 0) {
        func_0018D800(result, src, size);
    }
    return result;
}

extern u8 D_002C2A28[];
extern s32 D_002C2A34;
extern u8* D_002C2A20;
extern u8 D_002C2A38[];

void func_001E22F8(void* obj);

void func_0018D608(void)
{
    func_001E22F8(D_002C2A28);
    D_002C2A34 = D_002C2A34 + 1;
    ((u8**)D_002C2A38)[D_002C2A34] = D_002C2A20;
}

u8* func_0018D658(s32 size)
{
    u8* result;

    if (size == 0) {
        return 0;
    }
    func_0018D4F8(size);
    result = D_002C2A20;
    result = result - ((size + 15) & ~15);
    D_002C2A20 = result;
    return result;
}

s32 func_0018F940(s32 a, s32 b);

s32 func_0018F968(void)
{
    return func_0018F940(1, 0xFFFF);
}

struct Actor_0018F988 {
    u8 pad_000[0x538];
    u64 flags_538;
};

void func_001B7968(void* self);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

void func_0018F988(Actor_0018F988* self)
{
    func_001B7968(self);
    self->flags_538 |= (u64)0x8000 << 28;
    func_001B9AE0(self, 3, 0, 3, 0);
}

struct Actor_0018FEF8 {
    u8 pad_000[0xBD0];
    s32 field_BD0;
    s32 field_BD4;
};

void func_001C6F48(void* self);

void func_0018FEF8(Actor_0018FEF8* self)
{
    func_001C6F48(self);
    self->field_BD4 = 0;
    self->field_BD0 = 0;
}

struct Actor_0018FFB0 {
    u8 pad_000[0x4];
    s32 field_004;
    u8 pad_008[0x720 - 0x008];
    void* field_720_ptr;
    s32 field_724;
    u8 pad_728[0xC04 - 0x728];
    s32 field_C04;
    u8 pad_C08[0xC10 - 0xC08];
    s32 field_C10;
    u8 pad_C14[0xC28 - 0xC14];
    s32 field_C28;
    s32 field_C2C;
    s32 field_C30;
    s32 field_C34;
    s32 field_C38;
    s32 field_C3C;
    s32 field_C40;
    s32 field_C44;
};

void func_001CB6F8(void* a, void* b);
void func_001C91C8(void* self, s32 a, s32 b);

void func_0018FFB0(Actor_0018FFB0* self, s32 a1, s32 a2)
{
    s32 a2v = a2;
    switch (self->field_724) {
    case 4:
        self->field_C28 = 0;
        self->field_C10 = 0;
        break;
    case 0x10:
        if (self->field_C30 == 4) {
            a2v = self->field_C44;
        } else {
            a2v = self->field_C3C;
        }
        break;
    case 0xB:
        if (self->field_C30 == 4) {
            a2v = self->field_C40;
        } else {
            a2v = self->field_C38;
        }
        if (self->field_720_ptr != 0) {
            func_001CB6F8(self->field_720_ptr, self);
        }
        break;
    }
    func_001C91C8(self, a1, a2v);
    s32 kind = self->field_724;
    if (kind == 0xB || kind == 0x10) {
        self->field_C04 = 0;
    }
}

struct Obj_18C1A8 { u8 pad0[0x14]; s32 f14; };

s32 func_0018D1F8(void* self);

s32 func_0018C1A8(Obj_18C1A8* self)
{
    s32 r = func_0018D1F8(self);
    if (r != 0) {
        self->f14 = 2;
    } else {
        self->f14 = 3;
    }
    return r;
}

struct Key_18C1E8 { s32 w0; s32 w4; s32 w8; s32 wC; };
struct Obj_18C1E8 { s32 f00; s32 f04; u8 pad08[0xC]; s32 f14; u8 pad18[4]; s32 f1C; };

void func_0018D410(void* p);
s32 func_001407A0(void* p);

s32 func_0018C1E8(Obj_18C1E8* self)
{
    Key_18C1E8 key;
    s32 flag;
    func_0018D410(&key);
    if (self == 0) {
        flag = 0;
    } else {
        s32 x = self->f04 ^ self->f1C;
        key.w0 = self->f00 ^ self->f14;
        key.w4 = x;
        flag = x != 0;
    }
    if (flag != 0) {
        return func_001407A0(&key);
    }
    return 0;
}

void func_0018D778(void* self)
{
}

struct Ctx_0018D8E0 { u8 pad[0x6B8]; s32 ready; };

void func_0013B4C0(void* self);

void func_0018D8E0(Ctx_0018D8E0* self)
{
    func_0013B4C0(self);
    self->ready = 1;
}

struct Ctx_0018D910 { u8 pad[0x2C8]; u64 flags; };

extern u8 D_002699B0[];

void func_0013B598(void* self);
void func_00124DF8(void* self, s32 mode, void* data);

void func_0018D910(Ctx_0018D910* self)
{
    u64 mask = (u64)(s64)-0x301;
    u64 set = 0x8000;
    func_0013B598(self);
    func_00124DF8(self, 1, D_002699B0);
    mask <<= 16;
    mask |= 0xFFFF;
    mask <<= 16;
    mask |= 0xFFFF;
    set <<= 25;
    self->flags = (self->flags & mask) | set;
}

struct Ctx_18E7C0 {
    u8 pad0[4];
    s32 f4;
    u8 pad1[4];
    s32 fC;
};

struct Span_18E7C0 {
    s32 a;
    s32 b;
    void* c;
    s32 d;
};

void func_001F6C20(s32 a);
void* func_001F6CA0(Span_18E7C0* span, s32 n);
s32 func_001F6C90(void* obj);

void* func_0018E7C0(Ctx_18E7C0* p, void* a1, s32 a2)
{
    Span_18E7C0 span;
    void* obj;

    span.a = a2;
    span.b = p->f4 + p->fC;
    span.c = a1;
    span.d = 0;
    func_001F6C20(0);
    obj = func_001F6CA0(&span, 1);
    while (func_001F6C90(obj) >= 0) {
    }
    return a1;
}

void* func_0018E8C0(void)
{
    return 0;
}
