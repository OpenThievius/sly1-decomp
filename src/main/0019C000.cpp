// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Buf_19DF48 { u8 raw[0x30]; };
typedef void (*Fn_19DF48)(void);
struct Row_19DF48 { Fn_19DF48 fn; u8 pad0[8 - 4]; s32 x8; u8 pad1[0x80 - 12]; };

extern u8 D_0026AC20[];
extern u8 D_0026AC30[];

void func_001611B8(void* self);
void func_001529C8(void* self, s32 a, void* b);
void func_001612F8(void* self, s32 a, s32 b, s32 c, s32 d, s32 e);
void func_0019DA30(void);
void func_0019DA60(void);
void func_0019DAD8(void);
void func_0019DB20(void);
void func_0019DB68(void);
void func_0019DBB0(void);

void func_0019DF48(void)
{
    Buf_19DF48 buf;
    Row_19DF48* rows;
    u8* p;
    s32 i;

    func_001611B8(buf.raw);
    func_001529C8(buf.raw, 1, D_0026AC20);
    func_001612F8(buf.raw, 0x7D, 0, 3, 0x412, 0);
    rows = (Row_19DF48*)D_0026AC30;

    rows[0].fn = func_0019DA30;
    rows[1].fn = func_0019DA60;
    rows[2].fn = func_0019DAD8;
    rows[3].fn = func_0019DB20;
    rows[4].fn = func_0019DB20;
    rows[5].fn = func_0019DB68;
    rows[6].fn = func_0019DB20;
    rows[7].fn = func_0019DB20;
    rows[8].fn = func_0019DB20;
    rows[9].fn = func_0019DB68;
    rows[12].fn = func_0019DB20;
    rows[11].fn = func_0019DB20;
    rows[10].fn = func_0019DB20;
    rows[13].fn = func_0019DB20;
    rows[14].fn = func_0019DB68;
    rows[15].fn = func_0019DB68;
    rows[16].fn = func_0019DB20;
    rows[17].fn = func_0019DBB0;

    p = D_0026AC30 + 0x888;
    i = 17;
    do {
        *(s32*)p = -1;
        i--;
        p -= 0x80;
    } while (i >= 0);
}

typedef void (*VFn_19E040)(void* self);
struct Node_19E040 { VFn_19E040* vtbl; u8 pad0[0x550 - 4]; s32 f550; u8 pad1[0x564 - 0x554]; Node_19E040* next564; };
struct Pool_19E040 { u8 pad0[0x1B38]; Node_19E040* head1B38; Node_19E040* last1B3C; };

Node_19E040* func_0019E040(Pool_19E040* self, s32 flag)
{
    if (flag == 0 && self->last1B3C != 0) {
        return self->last1B3C;
    }
    Node_19E040* n = self->head1B38;
    if (n != 0) {
        self->head1B38 = n->next564;
        n->f550 = flag;
        n->vtbl[6](n);
        if (flag == 0) {
            self->last1B3C = n;
        }
    }
    return n;
}

struct Obj_19E0B8 {
    u8 pad0[0x80];
    f32 f80;
    u8 pad84[0x2C8 - 0x84];
    u64 q2C8;
    u8 pad2D0[0x538 - 0x2D0];
    u64 q538;
    u8 pad540[0x558 - 0x540];
};

void func_001B7968(Obj_19E0B8* self);
void func_00152438(void* p, s32 n);

void func_0019E0B8(Obj_19E0B8* self)
{
    func_001B7968(self);
    func_00152438((u8*)self + 0x558, 0x10);
    u64 flags = self->q2C8;
    flags &= (u64)(s64)(s32)0xCFFFFFFF;
    flags |= 0x20000000ULL;
    u64 wide = self->q538;
    wide |= (u64)1 << 42;
    flags &= 0xFFFFFCFFFFFFFFFFULL;
    wide |= (u64)1 << 51;
    f32 k = 1e10f;
    flags |= (u64)1 << 40;
    self->q538 = wide;
    self->f80 = k;
    self->q2C8 = flags;
}

struct Pool_19EA78 { s32 size; };
struct Proc_19EA78 { u8 pad0[0x1B2C]; Pool_19EA78 pool1B2C; };
struct Sys_19EA78 {
    u8 pad0[0x14];
    Proc_19EA78* f14;
    u8 pad1[0x558 - 0x18];
    u8 list558[4];
};
struct Obj_19EA78 {
    void* f0;
    void* f4;
    u8 pad8[4];
    void* fC;
};

extern u8* D_00275710;

void* func_0019E040(void* ctx, s32 zero);
void* func_001B5EA0(void* p);
void func_001F5C0C(void* p, s32 zero, s32 size);
void* func_0019E908(void* owner);
void func_00152470(void* list, void* item);
void func_0019EC20(void* self);

void* func_0019EA78(s32 a, s32 b)
{
    void* owner = (void*)a;
    Sys_19EA78* sys = (Sys_19EA78*)b;
    if (sys == 0) {
        sys = (Sys_19EA78*)func_0019E040(D_00275710, 0);
        if (sys == 0) return 0;
    }
    Obj_19EA78* o = (Obj_19EA78*)func_001B5EA0((u8*)sys->f14 + 0x1B2C);
    if (o != 0) {
        func_001F5C0C(o, 0, sys->f14->pool1B2C.size);
        void* r = func_0019E908(owner);
        o->f4 = owner;
        o->fC = sys;
        o->f0 = r;
        func_00152470(sys->list558, o);
        func_0019EC20(o);
    }
    return o;
}

struct Obj_19EBE8 {
    u8 pad0[0xC];
    u8* fC;
};

void func_00152600(void* table, void* self);
void func_0019EC30(void* self);

void func_0019EBE8(void* self)
{
    Obj_19EBE8* o = (Obj_19EBE8*)self;
    func_00152600(o->fC + 0x558, self);
    func_0019EC30(self);
}

typedef void (*ItemFn_19EC30)(void* payload, s32 n, void* owner);
typedef void (*VFn_19EC30)(void* self);

struct Item_19EC30 {
    ItemFn_19EC30 fn;
    void* payload;
    u8 pad_08[0x8];
    Item_19EC30* next;
};

struct Ctx_19EC30 {
    u8 pad_00[0x14];
    u8* table;
};

struct Owner_19EC30 {
    VFn_19EC30* vtbl;
    u8 pad_04[0x4];
    s32 count;
    Ctx_19EC30* ctx;
    u8 pad_10[0x108];
    Item_19EC30* head;
};

void func_001DBC18(void* a, void* b);
void func_001B5F28(void* a, void* b);

void func_0019EC30(Owner_19EC30* self)
{
    s32 n = self->count - 1;
    self->count = n;
    if (n != 0) {
        return;
    }
    VFn_19EC30 fn = self->vtbl[2];
    if (fn != 0) {
        fn(self);
    }
    Item_19EC30* head = self->head;
    if (head != 0) {
        self->head = 0;
        for (Item_19EC30* it = head; it != 0; it = it->next) {
            it->fn(it->payload, 0x10, self);
        }
        func_001DBC18(D_00275710, head);
    }
    func_001B5F28(self->ctx->table + 0x1B2C, self);
}

struct Lerp_19ED00 {
    u8 pad_00[0x18];
    f32 a18;
    f32 a1C;
};

extern f32 D_00261858[];

void func_0019ED00(Lerp_19ED00* self, f32 x)
{
    f32 span = D_00261858[1] - self->a18;
    f32 t = self->a1C - span;
    if (x < t) {
        f32 r = t / self->a1C;
        f32 q = x / r;
        self->a1C = q;
        self->a18 = D_00261858[1] - (1.0f - r) * q;
    }
}

struct Obj_19FE10 { u8 pad0[0x1C]; f32 f1C; s32 i20; };

void func_0019EB28(Obj_19FE10* self);

void func_0019FE10(Obj_19FE10* self)
{
    func_0019EB28(self);
    u8* g = D_00275710;
    s32 v = *(s32*)(g + 0x1D00);
    self->f1C = 0.5f;
    self->i20 = v;
}

struct Obj_19CE38 { u8 pad0[0x54]; f32 f54; f32 f58; f32 f5C; u8 pad1[0x80 - 0x60]; s32 f80; };

void func_0019CE38(Obj_19CE38* self, f32 x, f32 y, f32 z)
{
    self->f80 = 1;
    self->f54 = x;
    self->f58 = y;
    self->f5C = z;
}

struct Obj_19D2A8 { u8 pad0[0x2424]; f32 f2424; };
struct __attribute__((aligned(16))) Vec_19D2A8 { s32 a, b, c, d; };
struct Frame_19D2A8 { Vec_19D2A8 q0; Vec_19D2A8 q1; s32 w20; s32 w24; };

extern f32 D_00261858[];

void func_0019CEC0(void* a, void* b, void* c, f32 d);
void func_0019D0E0(void* a, void* b, void* c, void* d, void* e);
void func_0019C9C8(void* a, s32 b, void* c);

void func_0019D2A8(Obj_19D2A8* self, void* x, void* y)
{
    Frame_19D2A8 f;
    if (y != 0) {
        f32 d = self->f2424 - D_00261858[1];
        if (d < D_00261858[2]) {
            d = D_00261858[2];
        }
        func_0019CEC0(x, y, &f.q0, d);
        func_0019D0E0(x, &f.q0, &f.q1, &f.w20, &f.w24);
        func_0019C9C8(x, f.w20, &f.q1);
    }
}

struct Ctx_19F560 {
    u8 pad_000[0x550];
    s32 f550;
};

struct Sub_19F560 {
    u8 pad_000[0x3F8];
    s32 f3F8;
};

typedef void (*VFn_19F560)(void* self, s32 flag);

struct Actor_19F560 {
    VFn_19F560* vtbl;
    u8 pad_004[0x0C - 4];
    Ctx_19F560* ctx_0C;
    u8 pad_010[0x18 - 0x10];
    f32 f18;
    f32 f1C;
    u8 pad_020[0x24 - 0x20];
    Sub_19F560* sub_24;
    u8 pad_028[0x80 - 0x28];
};

extern f32 D_0026185C;

void func_0019EBE8(void* self);
s32 func_00182FC8(void* p);
s32 func_0013E658(void* a, s32 b);

void func_0019F560(Actor_19F560* self)
{
    f32 t = D_0026185C - self->f18;
    if (self->f1C < t) {
        func_0019EBE8(self);
        return;
    }
    Ctx_19F560* c = self->ctx_0C;
    if (c->f550 == 1) {
        return;
    }
    Sub_19F560* h = self->sub_24;
    if (h == 0) {
        return;
    }
    if (h->f3F8 == 0) {
        return;
    }
    s32 flag = 0;
    if (func_00182FC8(h) != 0) {
        if (func_0013E658(&self->pad_028[0x80 - 0x28], self->sub_24->f3F8) != 0) {
            flag = 1;
        }
    }
    self->vtbl[6](self, flag);
}

struct Obj_19F858 {
    u8 pad_000[0x114];
    void* f114;
};

void func_001F2EF0(f32 f, void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5);
s32 func_0019F620(void* self, void* a1, void* a2, void* a3);
void func_0019EBE8(void* self);

void func_0019F858(Obj_19F858* self, void* a1)
{
    u8 scratch[0x40];
    void* a2;
    void* a3;
    if (self->f114 != 0) {
        func_001F2EF0(50.0f, self->f114, (u8*)self + 0x80, (u8*)self + 0x50,
                      scratch, scratch + 0x10, 0);
        a2 = scratch;
        a3 = scratch + 0x10;
    } else {
        a2 = (u8*)self + 0x80;
        a3 = (u8*)self + 0x50;
    }
    s32 r = func_0019F620(self, a1, a2, a3);
    if (r == 0) {
        func_0019EBE8(self);
    }
}
