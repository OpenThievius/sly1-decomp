// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_00182ED0(void* self);
void func_001A93C8(void* self);

void func_001A80E0(void* self)
{
    func_00182ED0(self);
    func_001A93C8(self);
}

void func_001F3C08(void* a, f32* out);
void func_00128150(int a, int b, void* c, f32* d);
f32 func_00205778(f32 x, f32 y);

void func_001A97C8(u8* self, f32* out, int x)
{
    f32 v[12];
    if (*(void**)(self + 0x10) != 0) {
        func_001F3C08(*(void**)(self + 0x10), v);
        func_00128150(0, x, v, v);
        *out = func_00205778(v[1], v[0]);
    } else if (*(u8**)(self + 0x14) != 0) {
        func_00128150(0, x, *(u8**)(self + 0x14) + 0x110, v);
        *out = func_00205778(v[1], v[0]);
    } else {
        *out = *(f32*)(self + 0x8);
    }
}

void func_001C7CB8(void* self);
void func_0012E760(void* obj);

void func_001A9A40(void* self)
{
    u8* s = (u8*)self;
    func_001C7CB8(self);
    void* p = *(void**)(s + 0xC20);
    if (p != 0) {
        if (*(f32*)((u8*)p + 0x18) == 0.0f) {
            func_0012E760(p);
            *(void**)(s + 0xC20) = 0;
        }
    }
}

struct Obj_1AA788 { u8 pad[0x20C]; f32 value; };

void func_001AA788(Obj_1AA788* self, f32 v)
{
    self->value = v;
}

struct Obj_1AA8B8 { u8 pad[0x244]; f32 value; };

void func_001AA8B8(Obj_1AA8B8* self, f32 v)
{
    self->value = v;
}

extern f32 D_0026185C;
extern f32 D_00261860;

typedef void (*VFn_1AB660)(void* self);

void func_001AA298(void* self);
void func_001AB980(void* self, f32 value);

struct Obj_1AB660 {
    VFn_1AB660* vtbl;
    u8 pad[0x250 - 4];
    s32 mode;
    u8 pad2[0x260 - 0x254];
    s32 flag;
    f32 timer;
    u8 pad3[0x290 - 0x268];
    s32 extra;
};

void func_001AB660(Obj_1AB660* self)
{
    func_001AA298(self);
    if (self->mode == 0) {
        return;
    }
    if (self->flag == 0) {
        s32 close = (1.0f <= D_0026185C - self->timer);
        if ((u32)(self->mode - 1) < 2) {
            if (self->extra != 0 || close) {
                self->vtbl[15](self);
            }
        }
    } else {
        func_001AB980(self, D_00261860);
    }
}

extern f32 D_0026185C;

struct Obj_1ABE20 { u8 pad[0x260]; s32 state; f32 timer; };

void func_001ABE20(Obj_1ABE20* self, s32 state)
{
    if (self->state != state) {
        self->state = state;
        self->timer = D_0026185C;
    }
}

struct Obj_1AA268 {
    u8 pad0[4];
    s32 f4;
    u8 f8;
    u8 pad9[0x208 - 9];
    u32 f208;
    f32 f20c;
};

extern s32 D_0026227C;

void func_001AA268(Obj_1AA268* self)
{
    s32 value = D_0026227C;
    u32 flags = 0xFF808080;
    self->f4 = value;
    self->f20c = 1.0f;
    self->f208 = flags;
    self->f8 = 0;
}

struct Obj_1AA790 {
    u8 pad0[4];
    s32 f4;
    s8 f8;
    u8 pad9[0x208 - 9];
    s32 f208;
    f32 f20c;
    void* f210;
    u8 pad214[0x21C - 0x214];
    f32 f21c;
    f32 f220;
    u8 pad224[0x234 - 0x224];
    f32 f234;
    f32 f238;
};

typedef void (*VirtualCall_1AA790)(void* a, void* b, void* c, void* d);

extern u8 D_00262280[];

void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, s32* value);
void func_00137260(void* out, s32 flag);
void func_00137268(void* out, s32 flag);
void func_0015C8B8(s32 a, f32 x, f32 y);
void func_0015C638(s32 a, void* b, void* c, s32 d, void* e);
void func_0015C900(s32 v);

void func_001AA790(Obj_1AA790* self)
{
    u8 out[32];
    s32 tmp;
    void* handle;
    f32 x;

    if (self->f8 != 0) {
        f32 p = self->f234;
        f32 q = self->f238;
        s32 held = self->f208;
        func_00137228(out, self->f21c, self->f220);
        func_00137238(out, p, q);
        tmp = held;
        func_00137248(out, &tmp);
        func_00137260(out, 0);
        func_00137268(out, 0);

        handle = self->f210;
        if (handle != 0) {
            void* obj = *(void**)handle;
            if (obj != 0) {
                void* vt = *(void**)((u8*)obj + 76);
                VirtualCall_1AA790 fn = *(VirtualCall_1AA790*)((u8*)vt + 76);
                s16 adj = *(s16*)((u8*)vt + 72);
                fn((u8*)obj + adj, handle, out, D_00262280);
            }
        }
        x = self->f20c;
        func_0015C8B8(self->f4, x, x);
        func_0015C638(self->f4, &self->f8, out, 0, D_00262280);
        func_0015C900(self->f4);
    }
}

struct Obj_1AA898 {
    u8 pad[576];
    f32 value;
};

f32 func_001AA898(Obj_1AA898* self)
{
    return self->value;
}

struct Obj_1AA8A0 {
    u8 pad[580];
    f32 value;
};

f32 func_001AA8A0(Obj_1AA8A0* self)
{
    return self->value;
}

struct Obj_1AA8A8 {
    u8 pad[584];
    f32 value;
};

f32 func_001AA8A8(Obj_1AA8A8* self)
{
    return self->value;
}

struct Node_1A98F8 { u8 pad0[0x14]; void* sub; };

void func_001C72A0(Node_1A98F8* self);
void func_001DDC38(void* sub, Node_1A98F8* self);

void func_001A98F8(Node_1A98F8* self)
{
    func_001C72A0(self);
    func_001DDC38(self->sub, self);
}

struct Node_1A9928 { u8 pad0[0x14]; void* sub; u8 pad1[0xC24 - 0x18]; s32 field_C24; };

s32 func_001DDA80(void* sub);

s32 func_001A9928(Node_1A9928* self)
{
    if (func_001DDA80(self->sub) != 0)
        return 0;
    return self->field_C24;
}

typedef void* (*VFn_1A9960)(void* self);
struct Obj_1A9960 { VFn_1A9960* vtbl; u8 pad0[0x724 - 4]; s32 state724; };

void func_001C8C08(Obj_1A9960* self);
void func_001C8418(Obj_1A9960* self, void* p);

void func_001A9960(Obj_1A9960* self)
{
    func_001C8C08(self);
    if (self->state724 == 0x10) {
        void* r = self->vtbl[102](self);
        if (r != 0)
            func_001C8418(self, (u8*)r + 0x140);
    }
}

struct Obj_1A99B8 { u8 pad0[0x724]; s32 state724; };

void func_001C8E28(Obj_1A99B8* self);
void func_001C8BC0(Obj_1A99B8* self);

void func_001A99B8(Obj_1A99B8* self)
{
    func_001C8E28(self);
    if (self->state724 == 0x10)
        func_001C8BC0(self);
}

struct Flag_1AB958 { u8 pad[0x290]; s32 value; };

void func_001ABE20(void* self, s32 v);

void func_001AB958(Flag_1AB958* self)
{
    self->value = 1;
    func_001ABE20(self, 0);
}

f32 func_001ABE40(void)
{
    return 0.0f;
}

f32 func_001ABE50(void)
{
    return 0.0f;
}

f32 func_001ABE60(void)
{
    return 0.0f;
}

struct Obj_1A99F8 { u8 pad[0x724]; s32 state; };

extern u8 D_00264A40[];

void func_001C91C8(Obj_1A99F8* self);
void func_001603E8(s32 n);
void func_0018C7F8(u8* p);

void func_001A99F8(Obj_1A99F8* self)
{
    func_001C91C8(self);
    if (self->state == 0xB) {
        func_001603E8(4);
        func_0018C7F8(D_00264A40);
    }
}

typedef void (*VFn_1A9A98)(void* self);
struct Obj_1A9A98 { VFn_1A9A98* vtbl; };

extern Obj_1A9A98 D_0026E248;

s32 func_001E9970(void);

void func_001A9A98(void)
{
    if (func_001E9970()) {
        D_0026E248.vtbl[14](&D_0026E248);
    } else {
        D_0026E248.vtbl[15](&D_0026E248);
    }
}

struct Obj_1A9C58 { u8 pad[0xC14]; s32 f14; s32 f18; s32 f1C; };

void func_001A9C58(Obj_1A9C58* self, s32 a, s32 b, s32 c)
{
    self->f14 = a;
    self->f18 = b;
    self->f1C = c;
}

struct Obj_1AA1F0 {
    u8 pad0[0x214];
    s32 index;
    u8* entry218;
    f32 f21C;
    f32 f220;
    u8 pad1[8];
    f32 f22C;
    f32 f230;
    f32 f234;
    f32 f238;
    u8 pad4[4];
    f32 f240;
    u8 pad2[4];
    f32 f248;
    u8 pad3[12];
    u8* table258;
};

extern u8 D_0026C3E0[];
extern u8 D_00261868[];

void func_001AAB20(Obj_1AA1F0* self, f32 x, f32 y);

void func_001AA1F0(Obj_1AA1F0* self, s32 index)
{
    self->entry218 = D_0026C3E0 + index * 20;
    self->f248 = 0.25f;
    self->f240 = 0.25f;
    self->table258 = D_00261868;
    self->index = index;
    func_001AAB20(self, self->f234, self->f238);
    self->f21C = self->f22C;
    self->f220 = self->f230;
}
