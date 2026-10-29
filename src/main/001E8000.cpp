// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_E8E08 { u8 pad[0xC58]; s32 f58; s32 f5C; };
void func_001C9AF8(void);

void func_001E8E08(Obj_E8E08* a0)
{
    if (a0->f58 != 0x2DA) {
        s32 v = a0->f5C - 1;
        if (!(0 < v)) v = 0;
        a0->f5C = v;
    }
    func_001C9AF8();
}

extern u8 D_00275BC0[];
void func_001E90A8(void* p);

void func_001E9088(void)
{
    func_001E90A8(D_00275BC0);
}

void func_001AA110(void);

void func_001E9668(void)
{
    func_001AA110();
}

void func_001EB018(f32* a0, f32 x, f32 y, f32 z, f32 w)
{
    f32 p = w - x;
    f32 q = y - x;
    a0[0] = x;
    f32 r = p / z - q;
    r = r / (z - 1.0f);
    a0[2] = r;
    a0[1] = q - r;
}

struct __attribute__((packed)) Entry8_1EBCD8 { u8 b[8]; };
struct List_1EBCD8 { u8 pad[0x630]; s32 count; Entry8_1EBCD8 items[1]; };

void func_001EBCD8(List_1EBCD8* list, const Entry8_1EBCD8* src)
{
    s32 n = list->count;
    list->count = n + 1;
    Entry8_1EBCD8* dst = (Entry8_1EBCD8*)((u8*)list + (n * 8 + 0x634));
    *dst = *src;
}

struct Obj_1E86E0 {
    u8 pad0[0x268];
    s32 f268;
    u8 pad1[0x270 - 0x26C];
    s32 f270;
};

struct Mgr_1E86E0 {
    void** vtbl;
    u8 pad[0x260 - 4];
    s32 f260;
};

extern Mgr_1E86E0 D_002701F8;
void func_001E7460(void* self);
void func_001E7440(void* self, s32 v);
void func_001E7518(void* self, s32 mode);
void func_001E87F0(void* self, void* a1);

void func_001E86E0(Obj_1E86E0* self, s32 value)
{
    if (value == self->f270) return;
    if (self->f270 == 0) {
        void** vt = D_002701F8.vtbl;
        ((void (*)(void*, s32))vt[8])(&D_002701F8, 0);
    }
    self->f270 = value;
    if (D_002701F8.f260 == 4) {
        func_001E7460(self);
        if (self->f270 != 0) {
            void** vt = *(void***)self;
            ((void (*)(void*, s32))vt[16])(self, 2);
            func_001E7518(self, 1);
            func_001E7440(self, 0);
        } else {
            void** vt = *(void***)self;
            ((void (*)(void*, s32))vt[16])(self, 0);
            func_001E7518(self, 3);
            func_001E7440(self, 0);
            func_001E87F0(self, 0);
        }
    } else {
        s32 st = self->f268;
        if (st >= 2) return;
        if (st < 0) return;
        func_001E7518(self, 2);
    }
}

struct Obj_1E87F0 {
    u8 pad0[0x278];
    Obj_1E87F0* f278;
    u8 pad1[0x2C8 - 0x27C];
    u64 f2C8;
};

void func_001E87F0(Obj_1E87F0* self, Obj_1E87F0* a1)
{
    Obj_1E87F0* old = self->f278;
    if (old != 0) {
        old->f2C8 &= ~(1ULL << 32);
    }
    self->f278 = a1;
    if (a1 != 0) {
        a1->f2C8 |= (1ULL << 32);
    }
}

struct Obj_1E8840 {
    u8 pad0[0x268];
    s32 f268;
    s32 pad1;
    s32 f270;
    s32 f274;
    u8 pad2[0xC70 - 0x278];
    s32 fC70;
};

void func_001AA8C8(void* self);

void func_001E8840(Obj_1E8840* self)
{
    func_001AA8C8(self);
    self->fC70 = 0;
    self->f274 = 0;
    self->f270 = 0;
    self->f268 = 3;
}

s32 func_001E8878(s32 a0, s32 a1);

void func_001E88B0(void)
{
    func_001E8878(1, 0xFFFF);
}

struct Obj_1EB598 { u8 pad0[0x14]; void* f14; u8 pad1[0x610 - 0x18]; void* f610; void* f614; };

extern u8 D_00275CA0[];
void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a, void* p);
void* func_001B6290(void* a, void* self, s32 b, s32 c);
void func_001DBCC8(void* a, void* cb, void* ctx, s32 b, s32 c);
void func_001EB550(Obj_1EB598* self);

void func_001EB598(Obj_1EB598* self)
{
    func_00124A48(self);
    func_00124DF8(self, 4, D_00275CA0);
    self->f614 = func_001B6290(self->f610, self, 0x4CA, 1);
    func_001DBCC8(self->f14, (void*)func_001EB550, self, 0, 0);
}

struct Inner_1EB608 { u8 pad[0xC3C]; void* c3C; };
struct Obj_1EB608 { u8 pad0[0x14]; void* f14; u8 pad1[0x614 - 0x18]; void* f614; u8 pad2[0x68C - 0x618]; void* f68C; };
struct Glob_1EB608 { u8 pad[0x26D0]; f32 f26D0; };

extern Glob_1EB608* D_00262E10;

void func_001922E8(void* self);
void* func_0015A838(void* a, s32 b, s32 c, s32 d);
void func_001B64D8(void* a, s32 b);

void func_001EB608(Obj_1EB608* self, void* p)
{
    func_001922E8(self);
    Inner_1EB608* r = (Inner_1EB608*)func_0015A838(self->f14, 5, 0x13, 0);
    if (p != 0) {
        func_001B64D8(self->f614, 0x4CB);
        r->c3C = self;
        self->f68C = r;
    } else {
        func_001B64D8(self->f614, 0x4CA);
        D_00262E10->f26D0 = 2.0f;
    }
}

struct Obj_1EBC88 { u8 pad0[0x14]; void* f14; u8 pad1[0x688 - 0x18]; s32 f688; };

extern s32 D_00262C64;
s32 func_001DDA80(void* p);

s32 func_001EBC88(Obj_1EBC88* self)
{
    if (D_00262C64 & 1) return 1;
    if (func_001DDA80(self->f14) == 0) return self->f688 != 0;
    return 1;
}

s32 func_001EBD08(void)
{
    return 0;
}

struct Table_001E9038 {
    u8 pad0[0xC64];
    s32 items[6];
};

struct Probe_001E9038 {
    u8 pad0[0x50];
    s32 key;
};

s32 func_001C7468(void* self, void* probe);

s32 func_001E9038(Table_001E9038* self, Probe_001E9038* probe)
{
    s32 key = probe->key;
    u32 i = 0;
    s32 result;
    do {
        if (key == self->items[i]) {
            result = 0;
            goto done;
        }
        i++;
    } while (i < 6);
    result = func_001C7468(self, probe);
done:
    return result;
}

struct Ctor_001E90A8 {
    u8 pad0[4];
    s32 a04;
    u8 pad1[4];
    s32 a0C;
    u8 pad2[0x1C];
    s32 a2C;
    s32 a30;
};

void func_001E96F8(void* self, s32 mode);

void func_001E90A8(Ctor_001E90A8* self)
{
    self->a30 = -1;
    self->a04 = -1;
    func_001E96F8(self, 3);
    self->a0C = 0;
    self->a2C = 1;
}

void func_001E96F8(void* self, s32 mode);

void func_001E90E8(void* self)
{
    func_001E96F8(self, 3);
}
