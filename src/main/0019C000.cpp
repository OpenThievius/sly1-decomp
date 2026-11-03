// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"

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

struct __attribute__((aligned(16))) Quad_19F988 { s32 a, b, c, d; };
struct Obj_19F988 {
    u8 pad_00[0x1C];
    f32 f1C;
    s32 i20;
    u8 pad_24[0xC0 - 0x24];
    Quad_19F988 q0C0;
};

extern u8* D_00275710;

void func_0019EB28(void* self);

void func_0019F988(Obj_19F988* self)
{
    func_0019EB28(self);
    self->f1C = 5.0f;
    u8* g = D_00275710;
    self->i20 = *(s32*)(g + 0x1CEC);
    self->q0C0 = *(Quad_19F988*)(g + 0x1EE0);
}

struct Obj_19FD70 {
    u8 pad_00[0x1C];
    f32 f1C;
    s32 i20;
    u8 pad_24[0x34 - 0x24];
    f32 f34;
};

extern u8* D_00275710;

void func_0019EB28(void* self);

void func_0019FD70(Obj_19FD70* self)
{
    func_0019EB28(self);
    self->f1C = 3.0f;
    u8* g = D_00275710;
    s32 v = *(s32*)(g + 0x1CF4);
    self->f34 = 0.6f;
    self->i20 = v;
}

extern f32 D_00261858[];

typedef void (*VFn_19E848)(void* self, void* arg);

struct Node_19E848 {
    VFn_19E848* vtbl;
    u8 pad4[0x14];
    f32 f18;
};

struct List_19E848 {
    void* head;
    u8 pad4[0x4];
    s32 link;
};

struct Obj_19E848 {
    u8 pad0[0x558];
    List_19E848 list;
};

struct Frame_19E848 {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};

void func_0019E848(Obj_19E848* self, void* arg)
{
    Frame_19E848 fr;
    s32 e = (s32)&self->list;
    fr.cursor = e;
    fr.list = e;
    s32 old = (s32)D_0027B314;
    s32 link = *(s32*)(e + 8);
    D_0027B314 = (ListFrame*)&fr;
    fr.prev = old;
    s32 h = *(s32*)e;
    fr.link = link;
    fr.cursor = h + link;
    s32 n = h;
    while (n != 0) {
        Node_19E848* node = (Node_19E848*)n;
        if (node->f18 >= D_00261858[1]) {
        } else {
            node->vtbl[5](node, arg);
        }
        s32 nx = *(s32*)fr.cursor;
        s32 lk = fr.link;
        fr.cursor = nx + lk;
        n = nx;
    }
    D_0027B314 = (ListFrame*)fr.prev;
}

struct __attribute__((aligned(16))) Quad_19FDC0 { s32 a, b, c, d; };
struct Obj_19FDC0 {
    u8 pad_00[0x1C];
    f32 f1C;
    u8 pad_20[0x38 - 0x20];
    f32 f38;
    u8 pad_3C[0xC0 - 0x3C];
    Quad_19FDC0 q0C0;
};

extern u8* D_00275710;

void func_0019EB28(void* self);

void func_0019FDC0(Obj_19FDC0* self)
{
    func_0019EB28(self);
    self->f1C = 2.0f;
    u8* g = D_00275710;
    self->q0C0 = *(Quad_19FDC0*)(g + 0x1EE0);
    self->f38 = -1.0f;
}

extern u8 D_0026AC10[];
extern u8 D_005E4700[];

struct Node_19D6C0;
typedef void (*VFn_19D6C0)(Node_19D6C0* self, void* arg, s32 z);
struct Node_19D6C0 {
    VFn_19D6C0* vtbl;
};

struct Frame_19D6C0 {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};

struct Obj_19D6C0 {
    u8 pad0[0x60];
    s32 h60;
};

void func_00159D00(Node_19D6C0* n);

void func_0019D6C0(Obj_19D6C0* self, void* arg)
{
    Frame_19D6C0 f1;
    Frame_19D6C0 f2;
    Frame_19D6C0 f3;
    s32 e = (s32)self + 0x60;
    f1.cursor = e;
    f1.list = e;
    s32 old = (s32)D_0027B314;
    s32 link = *(s32*)(e + 8);
    *(s32*)D_0026AC10 = (s32)D_005E4700;
    D_0027B314 = (ListFrame*)&f1;
    f1.prev = old;
    f1.link = link;
    s32 h = *(s32*)e;
    f1.cursor = h + link;
    s32 n = h;
    while (n != 0) {
        Node_19D6C0* node = (Node_19D6C0*)n;
        node->vtbl[40](node, arg, 0);
        s32 nx = *(s32*)f1.cursor;
        f1.cursor = nx + f1.link;
        n = nx;
    }
    s32 e2 = (s32)self + 0x78;
    s32 old2 = (s32)D_0027B314;
    f2.cursor = e2;
    f2.list = e2;
    s32 link2 = *(s32*)(e2 + 8);
    D_0027B314 = (ListFrame*)&f2;
    f2.prev = old2;
    s32 h2 = *(s32*)((s32)self + 0x78);
    f2.link = link2;
    f2.cursor = h2 + link2;
    n = h2;
    while (n != 0) {
        Node_19D6C0* node = (Node_19D6C0*)n;
        node->vtbl[40](node, arg, 0);
        s32 nx = *(s32*)f2.cursor;
        f2.cursor = nx + f2.link;
        n = nx;
    }
    s32 e3 = (s32)self + 0x1CD8;
    s32 old3 = (s32)D_0027B314;
    s32 link3 = *(s32*)(e3 + 8);
    f3.prev = old3;
    D_0027B314 = (ListFrame*)&f3;
    f3.list = e3;
    s32 h3 = *(s32*)((s32)self + 0x1CD8);
    f3.link = link3;
    f3.cursor = h3 + link3;
    n = h3;
    while (n != 0) {
        func_00159D00((Node_19D6C0*)n);
        s32 nx = *(s32*)f3.cursor;
        f3.cursor = nx + f3.link;
        n = nx;
    }
    D_0027B314 = (ListFrame*)f1.prev;
}

extern u8 D_0060478C[];
extern u8 D_002622A8[];
extern u8 D_0026ABF0[];
extern u8 D_0026AC00[];
extern u8 D_0026AC20[];
extern u8* D_00275710;

void func_00152B38(void* self);
void func_00152D70(void* self);
void func_001EE3B8(void* obj, s32 size, s32 flags);
void func_001EE668(void* obj, s32 size, s32 count, void* data, s32 flags);

void func_0019D860(void)
{
    if (*(s32*)D_0060478C == 0) {
        *(s32*)D_0060478C = 1;
        void* obj = D_002622A8;
        func_00152B38(obj);
        func_001EE3B8(obj, 0, 0);
        func_001EE668(obj, 8, 1, D_0026ABF0, 0);
        func_001EE668(obj, 8, 1, D_0026AC00, 1);
        func_001EE668(obj, 0xC, 1, D_0026AC20, 0xC);
        func_001EE668(obj, 4, 1, D_00275710 + 0x1D68, 3);
        func_00152D70(obj);
    }
}

extern s32 D_00604780;
extern s32 D_00604784;
extern u8 D_002622A8[];
extern u8 D_002BDC20[];
extern u8 D_002BDEE0[];

void func_00152B38(void* self);
void func_001EE7D0(void* self, s32 n, void* buf, s32 flag);
void func_001EE450(void* self);
void func_00152D70(void* self);

void func_0019D968(void)
{
    if (D_00604780 == 0) {
        void* self = D_002622A8;
        func_00152B38(self);
        func_001EE7D0(self, 0x2C, D_002BDC20, 0);
        func_00152D70(self);
        D_00604780 = 1;
        D_00604784 = 1;
    } else if (D_00604784 == 0) {
        void* self = D_002622A8;
        func_00152B38(self);
        func_001EE450(self);
        func_001EE7D0(self, 0x2C, D_002BDEE0, 0);
        func_00152D70(self);
        D_00604784 = 1;
    }
}

struct Slot_2622D8 { u8 pad00[0x1C]; s32 r1C; };

extern s32 D_00604780;
extern u8 D_002622A8[];
extern u8 D_00212160[];
extern u8 D_00215C50[];
extern Slot_2622D8* D_002622D8;

void func_0019D860(void);
void func_0019D930(void);
void func_0015EAE0(void* self, void* a, void* b);
void func_00152B38(void* self);
void func_001EE468(void* self);
void func_00152D70(void* self);

void func_0019DA60(void)
{
    func_0019D860();
    func_0019D930();
    void* self = D_002622A8;
    func_0015EAE0(self, D_00212160, D_00215C50);
    D_00604780 = 1;
    D_002622D8->r1C = 1;
    func_00152B38(self);
    func_001EE468(self);
    func_00152D70(self);
}

struct __attribute__((aligned(16))) Quad_19F9D0 { s32 a, b, c, d; };
struct Scratch_19F9D0 { Quad_19F9D0 head; u8 rest[0x700 - 16]; };
struct Ctx_19F9D0 { u8 pad000[0x278]; s32* f278; u8 pad27C[0x3F8 - 0x27C]; void* f3F8; };
struct Actor_19F9D0 { u8 pad00[0x24]; Ctx_19F9D0* f24; u8 pad28[0x80 - 0x28]; Quad_19F9D0 q80; u8 pad90[0x10]; };
struct Obj_19F9D0 { void** vtbl; u8 pad04[0x1C - 4]; f32 f1C; u8 pad20[0x34 - 0x20]; f32 f34; u8 pad38[0x114 - 0x38]; s32 f114; };

void func_0013DFD8(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
void* func_0019EA78(s32 a, s32 b);
void func_0019EBE8(void* self);

void func_0019F9D0(Actor_19F9D0* self, s32 flag)
{
    if (flag != 0) {
        Scratch_19F9D0 s;
        s.head = self->q80;
        if (self->f24->f3F8 != 0) {
            func_0013DFD8(self->f24->f3F8, self->pad90, &self->q80, 0, 0x10, &s);
        }
        Obj_19F9D0* p = (Obj_19F9D0*)func_0019EA78(4, 0);
        if (p != 0) {
            ((void (*)(void*, f32, void*, s32))p->vtbl[0])(p, 40.0f, &s, 0);
            p->f1C = 0.75f;
            p->f34 = 30.0f;
            if (self->f24->f278 != 0) {
                p->f114 = self->f24->f278[3];
            }
        }
        func_0019EBE8(self);
    }
}

struct Obj_19DBB0 { u8 pad0[0x1C4]; f32 f1C4; f32 f1C8; };
struct Ctx_19DBB0 { u8 pad0[0x2F4]; s32 idx2F4; };
struct Self_19DBB0 { u8 pad0[0xC]; u8* ptr0C; };

extern Ctx_19DBB0* D_0026FA68;
extern s32 D_00274520[];
extern Obj_19DBB0* D_00261990;
extern u8 D_002622A8[];
extern u8 D_00212160[];
extern u8 D_00215C50[];

void func_0015EAE0(void* self, void* a, void* b);
void func_0019D860(void);
void func_0019D930(void);
void func_00143940(Obj_19DBB0* self, f32 v);
void func_00144848(Obj_19DBB0* self);

void func_0019DBB0(void)
{
    Self_19DBB0* self = (Self_19DBB0*)D_002622A8;
    func_0015EAE0(self, D_00212160, D_00215C50);
    func_0019D860();
    func_0019D930();

    if (D_0026FA68 != 0) {
        s32 v = D_00274520[D_0026FA68->idx2F4];
        if (v != 0) {
            *(u64*)self->ptr0C = ((u64)v << 32) | 0x50000000;
            self->ptr0C = self->ptr0C + 0x10;
        }
    }

    {
        Obj_19DBB0* o = D_00261990;
        f32 keep20 = o->f1C4;
        f32 keep21 = o->f1C8;
        func_00143940(o, 1.0f);
        func_00144848(D_00261990);
        func_00143940(D_00261990, keep20);
        D_00261990->f1C8 = keep21;
    }
}

struct __attribute__((aligned(16))) Vec_19D338 { s32 a, b, c, d; };
struct Frame_19D338 {
    Vec_19D338 q0;
    Vec_19D338 q1;
    Vec_19D338 q2;
    Vec_19D338 q3;
    s32 w40;
    s32 w44;
    s32 w48;
    s32 w4C;
};

typedef s32 (*Slot_19D338)(void* self, void* a1, s32 a2, void* a3, s32 a4, s32 a5, f32 f, void* a6);
struct Obj_19D338 { Slot_19D338* vtbl; };
struct Src_19D338 {
    u8 pad0[0x18];
    s32 f18;
    u8 pad1[0x34 - 0x1C];
    Obj_19D338* f34;
};

s32 func_00128018(void* a, s32 b, void* c, void* d);
void func_0019D0E0(void* a, void* b, void* c, void* d, void* e);
void func_0019C9C8(void* a, s32 b, void* c);

void func_0019D338(void* self, void* dst, Src_19D338* src, f32* k)
{
    Frame_19D338 f;
    func_00128018(0, src->f18, (u8*)self + 0x140, &f.q0);
    Obj_19D338* o = src->f34;
    if (o->vtbl[12] != 0) {
        o->vtbl[12](o, &f.q0, 0, &f.q1, 0, 0, *k, k);
    }
    func_00128018((void*)src->f18, (s32)self, &f.q1, &f.q2);
    func_0019D0E0(dst, &f.q2, &f.q3, &f.w40, &f.w44);
    func_0019C9C8(dst, f.w40, &f.q3);
}

struct Node_19E168;
struct Obj_19E168;

struct Scene_19E168 {
    u8 pad0[0x1B38];
    Obj_19E168* first1B38;
    Obj_19E168* cur1B3C;
};

struct Obj_19E168 {
    u8 pad0[0x14];
    Scene_19E168* scene;
    u8 pad18[0x558 - 0x18];
    Node_19E168* head;
    u8 pad55C[4];
    s32 stride;
    Obj_19E168* saved564;
};

struct Cursor_19E168;
struct Node_19E168;
struct Cursor_19E168 {
    void* link;
    u8* at;
    s32 stride;
    Cursor_19E168* prev;
    Cursor_19E168(void* l) {
        link = l;
        at = (u8*)l;
        stride = ((s32*)l)[2];
        prev = ((Cursor_19E168*)D_0027B314);
        D_0027B314 = (ListFrame*)this;
    }
    Node_19E168* first() {
        Node_19E168* n = *(Node_19E168**)link;
        at = (u8*)n + stride;
        return n;
    }
    Node_19E168* next() {
        Node_19E168* n = *(Node_19E168**)at;
        at = (u8*)n + stride;
        return n;
    }
    ~Cursor_19E168() { D_0027B314 = (ListFrame*)prev; }
};


void func_0019EBE8(Node_19E168* node);
void func_001B7B78(Obj_19E168* self);

void func_0019E168(Obj_19E168* self)
{
    Cursor_19E168 cur(&self->head);
    Node_19E168* node = cur.first();
    while (node != 0) {
        func_0019EBE8(node);
        node = cur.next();
    }
    self->saved564 = self->scene->first1B38;
    self->scene->first1B38 = self;
    if (self == self->scene->cur1B3C) {
        self->scene->cur1B3C = 0;
    }
    func_001B7B78(self);
}

struct Stream_19C470;
struct Tri_19C470 { u8* a; u8* b; u8* c; };
struct Edge_19C470 { u8* a; u8* b; };
struct Rec_19C470 { s32 id; u8 pos[96]; };
struct Obj_19C470 {
    u8 pad0[0x48];
    s32 f48;
    u8 pad1[0xA0 - 0x4C];
    u8 fA0[4];
    s32 fA4;
    u8 padA8[8];
    u8* fB0;
    u8 padB4[0xC4 - 0xB4];
    Rec_19C470* fC4;
    s32 fC8;
    u8* fCC;
    s32 fD0;
    s32 fD4;
    Tri_19C470* fD8;
    Edge_19C470* fDC;
    f32 fE0;
};

s32 func_00137D10(Stream_19C470* in);
void func_00137FB0(Stream_19C470* in, void* p);
void* func_0018D5C0(s32 n);
s32 func_00137CC0(Stream_19C470* in);
void func_0019CD90(Obj_19C470* o, s32 i, f32* x, f32* y, f32* z);
void func_0019CC10(f32 x, f32 y, f32 z, Obj_19C470* o, void* p);
f32 func_00137DF8(Stream_19C470* in);
void func_0011EC40(Obj_19C470* o, Stream_19C470* in);

void func_0019C470(Obj_19C470* o, Stream_19C470* in)
{
    {
        s32 i = 0x17;
        s32* p = (s32*)((u8*)o + 0xF0);
        do {
            i--;
            *p = func_00137D10(in);
            p += 8;
        } while (i >= 0);
    }
    s32 i = 0;
    o->f48 = func_00137D10(in);
    func_00137FB0(in, o->fA0);
    o->fC4 = (Rec_19C470*)func_0018D5C0(o->fA4 * 100);
    for (i = 0; i < o->fA4; i++) {
        f32 x;
        f32 y;
        f32 z;
        Rec_19C470* r = &o->fC4[i];
        o->fC4[i].id = func_00137CC0(in);
        func_0019CD90(o, i, &x, &y, &z);
        func_0019CC10(x, y, z, o, r->pos);
    }
    o->fC8 = func_00137D10(in);
    o->fCC = (u8*)func_0018D5C0(o->fC8 << 4);
    for (s32 e = 0; e < o->fC8; e++) {
        s32* r = (s32*)(o->fCC + (e << 4));
        s32 j = 3;
        do {
            j--;
            *r = func_00137D10(in);
            r++;
        } while (j >= 0);
    }
    o->fD0 = o->fD4 = func_00137D10(in);
    o->fD8 = (Tri_19C470*)func_0018D5C0(o->fD0 * 12);
    o->fDC = (Edge_19C470*)func_0018D5C0(o->fD0 << 3);
    for (s32 n = 0; n < o->fD0; n++) {
        Tri_19C470* t = &o->fD8[n];
        Edge_19C470* e = &o->fDC[n];
        s32 a = func_00137D10(in);
        s32 b = func_00137D10(in);
        s32 c = func_00137D10(in);
        t->a = o->fB0 + (a << 5);
        if (b > 0) {
            b--;
            t->b = (u8*)&o->fD8[b];
        } else if (b < 0) {
            b = ~b;
            e->a = o->fCC + (b << 4);
        }
        if (c > 0) {
            c--;
            t->c = (u8*)&o->fD8[c];
        } else if (c < 0) {
            c = ~c;
            e->b = o->fCC + (c << 4);
        }
    }
    o->fE0 = func_00137DF8(in);
    func_0011EC40(o, in);
}

// NEAR: 3 lines: prologue schedules "li t0,17" before the two addiu sp addresses (retail after them)

struct Item_19D4B0 { s32 f0; s32 f4; s32 f8; u8 pad[0x74]; };


void func_001BE0A8(Item_19D4B0** base, s32 count, s32 size, void* cmp);
void func_0019D468(void);

s32 func_0019D4B0(s32 n, Item_19D4B0* items, Item_19D4B0** out)
{
    s32 start[18];
    s32 pos[18];
    s32 cnt[18];
    s32 j;
    s32 i;
    for (i = 0; i < 18; i++) cnt[i] = 0;
    for (j = 0; j < n; j++) cnt[items[j].f8]++;
    pos[0] = 0;
    if (cnt[0] > 0 && ((Item_19D4B0*)D_0026AC30)[0].f0 != 0) {
        out[0] = &((Item_19D4B0*)D_0026AC30)[0];
        pos[0] = 1;
        cnt[0]++;
    }
    start[0] = pos[0];
    for (i = 1; i < 18; i++) {
        pos[i] = cnt[i - 1];
        if (cnt[i] > 0 && ((Item_19D4B0*)D_0026AC30)[i].f0 != 0) {
            out[pos[i]] = &((Item_19D4B0*)D_0026AC30)[i];
            pos[i]++;
        }
        cnt[i] += pos[i];
        start[i] = pos[i];
    }
    for (j = 0; j < n; j++, items++) {
        s32 b = items->f8;
        out[start[b]++] = items;
    }
    {
        s32 c = cnt[4] - pos[4];
        func_001BE0A8(&out[pos[4]], c, 4, (void*)func_0019D468);
    }
    {
        s32 c = cnt[8] - pos[8];
        func_001BE0A8(&out[pos[8]], c, 4, (void*)func_0019D468);
    }
    {
        s32 c = cnt[13] - pos[13];
        func_001BE0A8(&out[pos[13]], c, 4, (void*)func_0019D468);
    }
    {
        s32 c = cnt[1] - pos[1];
        func_001BE0A8(&out[pos[1]], c, 4, (void*)func_0019D468);
    }
    return cnt[17];
}

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_00219C20[];
extern const Fn_Table D_00219C40[];
extern const Fn_Table D_00219C60[];
extern const Fn_Table D_00219C80[];
extern const Fn_Table D_00219CA0[];
extern const Fn_Table D_00219CC0[];
extern const Fn_Table D_00219CE0[];
extern const Fn_Table D_00219D00[];
extern const Fn_Table D_00219D20[];
extern const Fn_Table D_00219D40[];
extern const Fn_Table D_00219D60[];
extern const Fn_Table D_00219D80[];
extern const Fn_Table D_00219DA0[];
extern const Fn_Table D_00219DC0[];
extern u8 D_00219DE0[];
extern const Fn_Table D_00219E00[];
extern const Fn_Table D_00219E20[];
extern const Fn_Table D_00219E40[];
extern const Fn_Table D_00219E60[];
extern const Fn_Table D_00219E80[];
extern const Fn_Table D_00219EA0[];
extern const Fn_Table D_00219EC0[];
extern const Fn_Table D_00219EE0[];
extern const Fn_Table D_00219F00[];
extern const Fn_Table D_00219F20[];
extern const Fn_Table D_00219F40[];
extern const Fn_Table D_00219F60[];

u8* func_0019E908(u32 n)
{
    switch (n) {
    case 0: return ((u8*)D_00219C20);
    case 2: return ((u8*)D_00219C40);
    case 3: return ((u8*)D_00219C60);
    case 4: return ((u8*)D_00219C80);
    case 5: return ((u8*)D_00219CA0);
    case 6: return ((u8*)D_00219CC0);
    case 7: return ((u8*)D_00219CE0);
    case 8: return ((u8*)D_00219D00);
    case 9: return ((u8*)D_00219D20);
    case 10: return ((u8*)D_00219D40);
    case 11: return ((u8*)D_00219D60);
    case 12: return ((u8*)D_00219D80);
    case 13: return ((u8*)D_00219DA0);
    case 14: return ((u8*)D_00219DC0);
    case 15: return D_00219DE0;
    case 16: return ((u8*)D_00219E00);
    case 17: return ((u8*)D_00219E20);
    case 18: return ((u8*)D_00219E40);
    case 19: return ((u8*)D_00219E60);
    case 20: return ((u8*)D_00219E80);
    case 21: return ((u8*)D_00219EA0);
    case 22: return ((u8*)D_00219EC0);
    case 23: return ((u8*)D_00219EE0);
    case 24: return ((u8*)D_00219F00);
    case 25: return ((u8*)D_00219F20);
    case 26: return ((u8*)D_00219F40);
    case 27: return ((u8*)D_00219F60);
    default: return 0;
    }
}

// The loop walks an intrusive list with an iterator that registers itself on a global stack
// (D_0027B314) for its lifetime and unregisters in its destructor.

extern u8 D_00248D20[];
extern u8 D_00248D30[];

typedef void (*VFn_19C068)(void *self);
typedef void (*VFn2_19C068)(void *self, void *x);

struct List_19C068 { s32 head; s32 pad; s32 step; };

struct Obj_19C068 {
    VFn_19C068 *vtbl;
    u8 pad4[0x10];
    void *mgr;
    u8 pad18[0x2D8 - 0x18];
    struct List_19C068 list;
    u8 pad2E4[0x5FC - 0x2E4];
    void *o5FC;
    u8 pad600[0x660 - 0x600];
    void *o660;
};

struct Frame_19C068;
struct Frame_19C068 {
    List_19C068 *list;
    s32 *cur;
    s32 step;
    Frame_19C068 *prev;
    Frame_19C068(List_19C068 *l)
    {
        list = l;
        cur = &l->head;
        step = l->step;
        prev = ((Frame_19C068*)D_0027B314);
        D_0027B314 = (ListFrame*)this;
    }
    ~Frame_19C068() { D_0027B314 = (ListFrame*)prev; }
    s32 Next()
    {
        s32 n = *cur;
        cur = (s32 *)(n + step);
        return n;
    }
};

struct Mgr_19C068 {
    s32 field0;
};

struct Ob_19C068 {
    VFn_19C068 *vtbl;
};

void func_00152600(struct Mgr_19C068 *a, struct Obj_19C068 *b);
void func_00152470(struct Mgr_19C068 *a, struct Obj_19C068 *b);
struct Buf_19C068 { s32 w[4]; };
void func_00128018(struct Mgr_19C068 *a, s32 b, void *c, struct Buf_19C068 *d);
void func_001B9860(struct Obj_19C068 *a, struct Buf_19C068 *b, void *c);
void func_001B7C40(struct Obj_19C068 *self, s32 flag);

void func_0019C068(struct Obj_19C068 *self, s32 a1) {
    if (a1 != 0) {
        func_00152600((struct Mgr_19C068 *)((u8 *)self->mgr + 0x1C60), self);
        ((struct Ob_19C068 *)self->o5FC)->vtbl[7](self->o5FC);
    } else {
        struct Buf_19C068 buf;
        func_00152470((struct Mgr_19C068 *)((u8 *)self->mgr + 0x1C60), self);
        ((struct Ob_19C068 *)self->o5FC)->vtbl[6](self->o5FC);
        func_00128018((struct Mgr_19C068 *)*(void **)((u8 *)self->o660 + 0x18), 0,
                      (u8 *)self->o660 + 0x40, &buf);
        func_001B9860(self, &buf, D_00248D20);
    }
    func_001B7C40(self, a1 == 0);
    Frame_19C068 it(&self->list);
    s32 node = it.Next();
    while (node != 0) {
        func_001B7C40((struct Obj_19C068 *)node, a1 == 0);
        node = it.Next();
    }
    ((VFn2_19C068 *)self->vtbl)[0x90 / 4](self, D_00248D30);
    ((VFn2_19C068 *)self->vtbl)[0x94 / 4](self, D_00248D30);
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_0019ECE0();
void func_0019ED58();
void func_0019F390();
void func_0019FA98();
void func_0019FB08();
void func_0019FCE8();
void func_0019FD08();
void func_0019FE50();
void func_0019FF20();
void func_001A0020();
void func_001A0040();
void func_001A00A0();
void func_001A01B8();
void func_001A0258();
void func_001A0318();
void func_001A05D8();
void func_001A0758();
void func_001A09C0();
void func_001A0A78();
void func_001A0B20();
void func_001A0BA0();
void func_001A0C50();
void func_001A0C98();
void func_001A0D60();
void func_001A0DF0();
void func_001A0F88();
void func_001A1410();
void func_001A1458();
void func_001A1498();
void func_001A14A0();
void func_001A15D8();
void func_001A22C8();
void func_001A22E0();
void func_001A25F0();
void func_001A26B0();
void func_001A26F8();
void func_001A2770();
void func_001A2830();
void func_001A2A68();
void func_001A2B48();
void func_001A2D30();
void func_001A2D88();
void func_001A2E68();
void func_001A3008();
void func_001A3128();
void func_001A31A0();
void func_001A31F0();
void func_001A3250();
void func_001A3598();
void func_001A3730();
void func_001A38F0();
void func_001A3990();
void func_001A39C8();
void func_001A3A18();
extern const Fn_Table D_00219C20[8] = { (Fn_Table)(void (*)(Obj_19FE10* self))func_0019EB28, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219C40[8] = { (Fn_Table)func_0019F988, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019F9D0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219C60[8] = { (Fn_Table)func_0019FA98, 0, 0, (Fn_Table)func_0019FB08, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019FCE8, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219C80[8] = { (Fn_Table)func_0019FD08, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219CA0[8] = { (Fn_Table)func_0019FD70, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219CC0[8] = { (Fn_Table)func_0019FDC0, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219CE0[8] = { (Fn_Table)func_0019FE10, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019FE50, (Fn_Table)func_0019FF20, (Fn_Table)func_001A0020, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219D00[8] = { (Fn_Table)func_001A0040, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_001A00A0, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219D20[8] = { (Fn_Table)func_001A01B8, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219D40[8] = { (Fn_Table)func_001A0258, 0, (Fn_Table)func_001A0318, (Fn_Table)func_001A05D8, (Fn_Table)func_0019F560, (Fn_Table)func_001A0758, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219D60[8] = { (Fn_Table)func_001A09C0, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_001A0A78, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219D80[8] = { (Fn_Table)func_001A0B20, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219DA0[8] = { (Fn_Table)func_001A0BA0, 0, (Fn_Table)func_001A0318, (Fn_Table)func_001A05D8, (Fn_Table)func_0019F560, (Fn_Table)func_001A0758, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219DC0[8] = { (Fn_Table)func_001A0C50, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219E00[8] = { (Fn_Table)func_001A0C98, 0, 0, (Fn_Table)func_001A0D60, (Fn_Table)func_001A0F88, (Fn_Table)func_001A0DF0, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219E20[8] = { (Fn_Table)func_001A1410, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_001A00A0, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219E40[8] = { (Fn_Table)func_001A1458, 0, 0, (Fn_Table)func_001A1498, (Fn_Table)func_001A14A0, (Fn_Table)func_001A15D8, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219E60[8] = { (Fn_Table)(void (*)(Obj_19FE10* self))func_0019EB28, (Fn_Table)func_001A22C8, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_001A22E0, (Fn_Table)func_0019ECE0, (Fn_Table)func_001A25F0 };
extern const Fn_Table D_00219E80[8] = { (Fn_Table)(void (*)(Obj_19FE10* self))func_0019EB28, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_001A26B0, (Fn_Table)func_001A26F8, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219EA0[8] = { (Fn_Table)(void (*)(Obj_19FE10* self))func_0019EB28, (Fn_Table)func_001A2770, 0, (Fn_Table)func_001A2830, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_001A2A68 };
extern const Fn_Table D_00219EC0[8] = { (Fn_Table)(void (*)(Obj_19FE10* self))func_0019EB28, (Fn_Table)func_001A2B48, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219EE0[8] = { (Fn_Table)(void (*)(Obj_19FE10* self))func_0019EB28, (Fn_Table)func_001A2D30, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_001A2D88, (Fn_Table)func_0019ECE0, (Fn_Table)func_001A2E68 };
extern const Fn_Table D_00219F00[8] = { (Fn_Table)(void (*)(Obj_19FE10* self))func_0019EB28, (Fn_Table)func_001A3008, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_001A31A0, (Fn_Table)func_0019ECE0, (Fn_Table)func_001A3128 };
extern const Fn_Table D_00219F20[8] = { (Fn_Table)func_001A31F0, 0, 0, (Fn_Table)func_0019F390, (Fn_Table)func_0019F560, (Fn_Table)func_001A3250, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219F40[8] = { (Fn_Table)func_001A3598, 0, 0, (Fn_Table)func_001A3730, (Fn_Table)func_001A38F0, (Fn_Table)func_001A3990, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };
extern const Fn_Table D_00219F60[8] = { (Fn_Table)(void (*)(Obj_19FE10* self))func_0019EB28, (Fn_Table)func_001A39C8, 0, (Fn_Table)func_0019F390, (Fn_Table)func_001A3A18, (Fn_Table)func_0019F858, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58 };

struct Entry_19D410 { u32 w[32]; } __attribute__((aligned(16)));

// D_0026AC10 points at the next free 128-byte entry of D_005E4700 (1024 of them).
void func_0019D410(Entry_19D410* src)
{
    Entry_19D410* cur = *(Entry_19D410**)D_0026AC10;
    if ((u32)(cur - (Entry_19D410*)D_005E4700) < 0x400) {
        *(Entry_19D410**)D_0026AC10 = cur + 1;
        *(Entry_19D410*)((u32)cur | 0x20000000) = *src;
    }
}

struct Self_19CD90 {
    u8 pad0[0x48];
    s32 f48;
};

void func_0019CD90(Self_19CD90* self, s32 p, f32* out0, f32* out1, f32* out2)
{
    s32 n = self->f48;
    s32 q = p / ((n + 1) * (3 * n + 1));
    s32 r = p - q * (n + 1) * (3 * n + 1);
    s32 m = r / (3 * n + 1);
    s32 s = r - m * (3 * n + 1);
    *out0 = (f32)(q - n) / (f32)self->f48;
    *out1 = (f32)m / (f32)self->f48;
    *out2 = (f32)s / (f32)self->f48;
}

extern f32 D_00261858[];

struct Node_19E420;
struct Obj_19E420;
void func_0019EC20(Node_19E420* node);
void func_0019EC30(Node_19E420* node);
s32 func_00152720(void* list);
void func_0019E558(Obj_19E420* self);
void func_00129DF8(Obj_19E420* self);

struct NodeVt_19E420 {
    u8 pad0[0x10];
    void (*update)(Node_19E420* node, f32 t);
};
struct Node_19E420 {
    NodeVt_19E420* vtbl;
    u8 pad4[0x14];
    f32 f18;
};
struct List_19E420 { u8* head; u8 pad4[4]; s32 offset; };
struct Iter_19E420 { List_19E420* list; u8* link; s32 offset; Iter_19E420* saved; };
struct ObjVt_19E420 {
    u8 pad0[0x1C];
    void (*f1C)(Obj_19E420* self);
};
struct Obj_19E420 {
    ObjVt_19E420* vtbl;
    u8 pad4[0x2C4];
    s64 f2C8;
    u8 pad2D0[0x288];
    List_19E420 list;
};

struct Next_19E420 {
    static Node_19E420* Of(Iter_19E420* it)
    {
        Node_19E420* obj = *(Node_19E420**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_19E420 {
    static void Of(Iter_19E420* it, List_19E420* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = ((Iter_19E420*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

void func_0019E420(Obj_19E420* self, f32 t)
{
    Iter_19E420 it;
    Begin_19E420::Of(&it, &self->list);
    Node_19E420* node;
    while ((node = Next_19E420::Of(&it)) != 0) {
        if (node->f18 >= D_00261858[1]) {
            continue;
        }
        func_0019EC20(node);
        node->vtbl->update(node, t);
        func_0019EC30(node);
    }
    s64 m = 0x8000;
    m <<= 23;
    if ((self->f2C8 & m) != 0 || func_00152720(&self->list) != 0) {
        self->vtbl->f1C(self);
    } else {
        func_0019E558(self);
    }
    func_00129DF8(self);
    D_0027B314 = (ListFrame*)it.saved;
}

struct __attribute__((aligned(16))) Quad_19C728 { s32 a, b, c, d; };
struct Fl_19C728 { u8 pad[8]; f32 f8; };
struct In_19C728 { u8 pad[8]; Fl_19C728* p8; };
struct Gr_19C728 { u8 pad[0x78]; s32 f78; u8 pad7C[0x44]; In_19C728* pC0; };
struct Node_19C728;
typedef void (*VFn_19C728)(Node_19C728* n);
struct Node_19C728 { VFn_19C728* vtbl; };
struct Slot_19C728 { u8 pad0[4]; Node_19C728* n4; u8 pad8[4]; s32 fC; u8 pad10[0x10]; };
struct Obj_19C728 {
    u8 pad0[0x14]; void* f14; u8 pad18[0x1C];
    s32 f34; s32 f38; void* f3C; void* f40; u8 pad44[0xC]; s32 f50; f32 f54; f32 f58; f32 f5C; f32 f60;
    u8 pad64[0xC]; Quad_19C728 q70; s32 f80; f32 f84; f32 f88; f32 f8C; Quad_19C728 q90; u8 pad_a0[0x44];
    Slot_19C728 slots[24]; Gr_19C728* f3E4;
};

void func_00182C58(void* self);
void* func_0015A448(void* a, s32 b, void* c);
void* func_0015A480(void* a, s32 b, void* c);
void func_00139600(s32 a, s32 b, void* c, s32 d, s32 e, void* f);
void func_00139038(void* self, s32 a, s32 b, void* c, s32 d, void* e, void* f, void* g);
void func_00139B38(void* g, void* n);
void func_0019CC10(Obj_19C728* self, f32* out, f32 a, f32 b, f32 c);
void func_001399F8(void* g, s32 a, s32 b, void* c);
void func_0012CD78(f32 a, f32 b, Gr_19C728* g, void* r1, void* r2, s32 r3, void* r4, s32 r5, s32 r6, s32 r7);

extern u8 D_0026ABD0[];
extern u8 D_0026ABE0[];
extern u8 D_0026ABD8[];

void func_0019C728(Obj_19C728* self)
{
    Slot_19C728* s;
    s32 i;
    func_00182C58(self);
    self->f3C = func_0015A448(self->f14, self->f34, self);
    if (self->f3C == 0) return;
    self->f40 = func_0015A480(self->f14, self->f38, self->f3C);
    if (self->f40 == 0) return;
    for (i = 0; i < 24; i++) {
        s = &self->slots[i];
        Node_19C728* n = (Node_19C728*)func_0015A480(self->f14, s->fC, self->f3C);
        s->n4 = n;
        if (n != 0) n->vtbl[7](n);
    }
    func_00139600(0x20, 0x18, self->slots, 0x10, 2, D_0026ABD0);
    func_00139038(self->f3C, 0x20, 0x18, self->slots, 1, D_0026ABE0, D_0026ABD8, &self->f3E4);
    if (self->f3E4->f78 == 0) self->f3E4->f78 = 1;
    void* nd = func_0015A480(self->f14, 0x36, self->f3C);
    if (nd != 0) func_00139B38(self->f3E4, nd);
    f32 buf[24];
    func_0019CC10(self, buf, self->f54, self->f58, self->f5C);
    Slot_19C728* d = self->slots;
    f32* src = buf;
    for (i = 0; i < 24; i++, d++) *(f32*)d = *src++;
    func_001399F8(self->f3E4, 0x20, 0x18, self->slots);
    func_0012CD78(self->f3E4->pC0->p8->f8, 0.0f, self->f3E4, self->f40, self->f3C, 1, &self->q70, 0, 0, 0);
    self->f60 = self->f3E4->pC0->p8->f8;
    if (self->f80 != 0) {
        func_0019CC10(self, buf, self->f84, self->f88, self->f8C);
        d = self->slots;
        src = buf;
        for (i = 0; i < 24; i++, d++) *(f32*)d = *src++;
        func_001399F8(self->f3E4, 0x20, 0x18, self->slots);
        func_0012CD78(self->f3E4->pC0->p8->f8, 0.0f, self->f3E4, self->f40, self->f3C, 1, &self->q90, 0, 0, 0);
    } else {
        self->q90 = self->q70;
    }
    self->f50 = 1;
}

struct List_19E558 { u8* first; s32 pad4; s32 offset; };
struct Iter_19E558 { List_19E558* list; u8* link; s32 offset; Iter_19E558* prev; };


struct Begin_19E558 {
    static void Of(Iter_19E558* it, List_19E558* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = (Iter_19E558*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Next_19E558 {
    static u8* Of(Iter_19E558* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};

struct End_19E558 {
    static void Of(Iter_19E558* it)
    {
        D_0027B314 = (ListFrame*)it->prev;
    }
};

struct Hit_19E558 { u8 pad0[0x40]; f32 weight; u8 pad44[0x2C]; };
struct Meta_19E558 { u8 pad0[8]; u32 flags; };
struct Obj_19E558;
struct Node_19E558;
typedef s32 (*VFn_19E558)(Node_19E558* self, Obj_19E558* o, void* a2, void* a3);
struct Node_19E558 { VFn_19E558* vtbl; u8 pad4[0x14]; f32 f18; };
struct Obj_19E558 {
    Meta_19E558* meta;
    u8 pad4[0x2D4];
    List_19E558 list2D8;
    u8 pad2E4[0x10C];
    s32 f3F0; s32 f3F4; u8* f3F8;
    u8 pad3FC[0x13C];
    u64 f538;
};
struct Link_19E558 { s32 pad0; Link_19E558* next; s32 pad8; Obj_19E558* obj; };
struct Self_19E558 {
    void** vtbl;
    u8 pad4[0x13C];
    u8 f140[0x290];
    f32 f3D0;
    u8 pad3D4[0xAC];
    Link_19E558** f480;
    u8 pad484[0xCC];
    s32 f550;
    u8 pad554[4];
    List_19E558 f558;
};

extern f32 D_00261858[];

void func_0018D608(void);
void* func_0018D658(s32 size);
void func_0018D6F0(void);
s32 func_0013E430(u8* a0, u8* a1, void** a2, f32 scale);
s32 func_00141C90(Obj_19E558* self, void* a1, void* a2, void* a3, s32 a4, Hit_19E558* a5);
u32 func_00152720(List_19E558* p);

void func_0019E558(Self_19E558* self)
{
    if (self->f550 != 1) return;
    Link_19E558* l;
    for (l = *self->f480; l != 0; l = l->next) {
        Iter_19E558 it0;
        Begin_19E558::Of(&it0, &l->obj->list2D8);
        if (l->obj->f538 & ((u64)0x8000 << 27)) {
            End_19E558::Of(&it0);
            continue;
        }
        Obj_19E558* s2;
        for (s2 = (Obj_19E558*)Next_19E558::Of(&it0); s2 != 0; s2 = (Obj_19E558*)Next_19E558::Of(&it0)) {
            Iter_19E558 it1;
            void* buf;
            Hit_19E558 hits[4];
            Begin_19E558::Of(&it1, &self->f558);
            if ((s2->f538 & ((u64)0x8000 << 28)) && (s2->meta->flags & 0x80) == 0) {
                End_19E558::Of(&it1);
                continue;
            }
            func_0018D608();
            if (s2->f3F0 > 0) {
                buf = func_0018D658(s2->f3F4 * 12);
                if (func_0013E430(s2->f3F8, self->f140, &buf, self->f3D0) != 2) goto skip;
                buf = (u8*)buf - 12;
            } else {
                buf = 0;
            }
            {
                Node_19E558* n;
                for (n = (Node_19E558*)Next_19E558::Of(&it1); n != 0; n = (Node_19E558*)Next_19E558::Of(&it1)) {
                    if (n->f18 >= D_00261858[1]) continue;
                    s32 cnt = func_00141C90(s2, buf, (u8*)n + 0x90, (u8*)n + 0x80, 4, hits);
                    s32 i;
                    for (i = 0; i < cnt; i++) {
                        Hit_19E558* h = &hits[i];
                        if (h->weight == 0.0f) continue;
                        if (n->vtbl[7](n, s2, h, (u8*)h + 0x20) != 0) break;
                    }
                }
            }
        skip:
            func_0018D6F0();
            End_19E558::Of(&it1);
        }
        End_19E558::Of(&it0);
    }
    if (func_00152720(&self->f558) != 0) {
        ((void (*)(Self_19E558*))self->vtbl[7])(self);
    }
}
