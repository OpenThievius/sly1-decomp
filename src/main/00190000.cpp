// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct State_193288 { void* ptr; s32 scaled; s32 size; s32 value; s32 repeat; };
void func_00168AF8(State_193288*);
void func_00193318(State_193288*);
void func_00193288(State_193288* self, s32 value)
{
	if (self->ptr != 0) {
		if (self->size == 0) { self->scaled = value << 1; self->size = value; func_00168AF8(self); }
		else if (self->value == value) self->repeat++;
		else self->repeat = 0;
		self->value = value;
		func_00193318(self);
	}
}

struct Obj_192498 {
    void** vtbl;
};

void func_00192498(Obj_192498* self, s32* out)
{
    *out = ((s32 (*)(Obj_192498*, s32*))self->vtbl[0x144 / 4])(self, out);
}

extern s32 D_00269BCC;
extern void* D_00269C98[];

void* func_001925F0()
{
    s32 i = D_00269BCC;
    if (i < 0) return 0;
    return D_00269C98[i];
}

struct Obj_1926D0 {
    u8 pad0[0x8];
    s32 f8;
    u8 pad1[0x18 - 0xC];
    s32 f18;
    u8 pad2[0x550 - 0x1C];
    s32 f550;
};

extern s32 D_00269C90;
extern Obj_1926D0* D_00262E10;
s32 func_00182FC8();
s32 func_00192688(Obj_1926D0* value);

void func_001926D0(Obj_1926D0* self)
{
    if (self->f550 == 0) return;
    if (self->f18 != 0) return;
    if (!func_00182FC8()) return;
    if (func_00192688(self) >= 0) return;
    s32 n = D_00269C90;
    if ((u32)n < 16) {
        D_00269C98[n] = self;
        D_00269C90 = n + 1;
    } else if (self->f8 == 5 && D_00262E10 == 0) {
        D_00269C98[0] = self;
    }
}

s32 func_00192688(void* value);
void func_00192880(s32 index);
void func_001F5B08(void* dst, void* src, s32 size);

void func_00192780(void* value)
{
    s32 idx = func_00192688(value);
    if (idx < 0) return;
    if (idx == D_00269BCC) func_00192880(-1);
    s32 n = D_00269C90;
    func_001F5B08(&D_00269C98[idx], &D_00269C98[idx + 1], (n - idx) * 4 - 4);
    if (idx < D_00269BCC) D_00269BCC = D_00269BCC - 1;
    D_00269C90 = D_00269C90 - 1;
}

void func_001B7A98(void* self);
void func_001926D0(void* self);

void func_00192820(void* self)
{
    func_001B7A98(self);
    func_001926D0(self);
}

void func_001B7B78(void* self);
void func_00192780(void* self);

void func_00192850(void* self)
{
    func_001B7B78(self);
    func_00192780(self);
}

struct Obj_192990 {
    u8 pad[0x550];
    s32 f550;
};

void func_001926D0(Obj_192990* self);
void func_00192780(Obj_192990* self);

void func_00192990(Obj_192990* self, s32 value)
{
    if (self->f550 == value) return;
    self->f550 = value;
    if (value) func_001926D0(self);
    else func_00192780(self);
}

void func_001929D0(void* value)
{
    func_00192880(func_00192688(value));
}

extern u8 D_00604700[];
void* func_001925F0();

void* func_001929F8()
{
    void* r = func_001925F0();
    if (r) return (u8*)r + 0x580;
    return D_00604700;
}

struct Pair_192A28 {
    s32 a;
    s32 b;
};

void func_00192A28(s32, s32, Pair_192A28* out)
{
    out->b = 1;
    out->a = 1;
}

typedef s32 (*VFn_190450)(void* self, s32 value);

struct Mid_190450 { u8 pad0[0x618]; void* p618; };

struct Obj_190450 {
    VFn_190450* vtbl;
    u8 pad0[0xC2C - 4];
    Mid_190450* mid;
    s32 c30;
    s32 c34;
};

s32 func_001A8820(void* p, s32 v);
s32 func_001C9990(void* self, s32* arg);

s32 func_00190450(Obj_190450* self, s32* arg)
{
    if (self->vtbl[79](self, arg[0])) {
        return 0;
    }
    self->c34 = 0;
    self->c30 = arg[0];
    if (arg[0] == 0 && arg[1] != 0) {
        if (func_001A8820(self->mid->p618, arg[1])) {
            self->c34 = 1;
        }
    }
    return func_001C9990(self, arg);
}

struct Obj_1906E8 { u8 pad0[0xC28]; s32 c28; };

void func_001906E8(Obj_1906E8* self, s32 value)
{
    self->c28 = value;
}

u32 func_001907E0(u32 x)
{
    return (x & 1) ? 0 : x;
}

extern s32 D_00269BA4;

void func_00191EB0(void)
{
    D_00269BA4 = 0;
}

struct Obj_191FD8 {
    u8 pad0[0x14];
    s32 c14;
    s32 c18_pad;
    u8 pad1[0x64 - 0x1C];
    s32 c64;
    s32 c68;
};

void func_00182C58(void* self);
s32 func_0015A418(s32 a0, s32 a1, s32 a2, void* a3);

void func_00191FD8(Obj_191FD8* self)
{
    func_00182C58(self);
    if (self->c64 != -1) {
        self->c68 = func_0015A418(self->c14, 4, self->c64, self);
    }
}

s32 func_00128018(void* a0, s32 a1, void* a2, void* a3);

s32 func_00192128(u8* self, void* other)
{
    void* p = self + 0x40;
    return func_00128018(other, 0, p, p);
}

struct Child_001900A0;
typedef void (*VirtFn)(void* self, s32 arg);
typedef void (*ChildFn)(void* self);

struct Actor_001900A0 {
    VirtFn* vtbl;
    u8 pad_004[0x5FC];
    s32 field_600;
    u8 pad_604[0x120];
    s32 field_724;
    u8 pad_728[0xC2C - 0x728];
    Child_001900A0* field_C2C;
};

struct Child_001900A0 {
    ChildFn* vtbl;
};

void func_001C9008(void* self);

void func_001900A0(Actor_001900A0* self)
{
    func_001C9008(self);
    s32 kind = self->field_724;
    if (kind != 8) {
        if (kind == 0x10) {
            Child_001900A0* child = self->field_C2C;
            if (child != 0) {
                child->vtbl[0x54](child);
            }
        }
    } else {
        if (self->field_600 == 1) {
            self->vtbl[0x53](self, 0);
        }
    }
}

struct Actor_001903F0 {
    u8 pad_000[0x14];
    void* field_14;
};

extern s32 D_00262C64;

s32 func_001DDA80(void* p);
s32 func_001C9A48(void* self, s32 a);

s32 func_001903F0(Actor_001903F0* self, s32 a1)
{
    if (D_00262C64 & 1) {
        return 1;
    }
    if (func_001DDA80(self->field_14) == 0) {
        return func_001C9A48(self, a1);
    }
    return 1;
}

s32 func_00192490(void)
{
    return 0;
}

struct __attribute__((aligned(16))) Quad_001924C8 { s32 a, b, c, d; };

typedef void (*Mode_001924C8)(void* self, s32 mode);
typedef void (*Init_001924C8)(void* self, void* table, s32 zero, f32 scale);

// A node made by func_0019EA78: a hook table, a float at 0x1C and a quad at 0xC0.
struct Node_001924C8 {
    Init_001924C8* vtbl;
    u8 pad0[0x1C - 4];
    f32 f1C;
    s32 f20;
    u8 pad1[0xC0 - 0x24];
    Quad_001924C8 q0C0;
    u8 pad2[0x134 - 0xD0];
    void* p134;
};

// The object that owns the node: a hook table at 0 and fields at 0x59C to 0x5F0.
struct Owner_001924C8 {
    Mode_001924C8* vtbl;
    u8 pad0[0x59C - 4];
    s32 f59C;
    u8 pad1[0x5AC - 0x5A0];
    Node_001924C8* p5AC;
    u8 pad2[0x5D0 - 0x5B0];
    s32 f5D0;
    u8 pad3[0x5F0 - 0x5D4];
    void* p5F0;
};

// The argument; its pointer at 0x14 leads to a block with a quad at 0x1EE0.
struct Source_001924C8 { u8 pad0[0x14]; u8* p14; };

void* func_0019EA78(s32 kind, s32 zero);
void func_0019F8E8(void* node, void* owner);
f32 func_0012CCC0(void* obj, s32 id);

void func_001924C8(Owner_001924C8* self, s32 mode, Source_001924C8* other)
{
    switch (mode) {
    case 0:
        if (self->p5F0 == 0)
            return;
        {
            Node_001924C8* n = (Node_001924C8*)func_0019EA78(0x1A, 0);
            self->p5AC = n;
            self->f5D0 = 1;
            if (n != 0) {
                Init_001924C8 init = n->vtbl[0];
                init(n, (u8*)other + 0x140, 0, 1.0f);
                func_0019F8E8(n, self);
                f32 r = func_0012CCC0(self->p5F0, 0x13F);
                n->f1C = r;
                n->f20 = self->f59C;
                n->q0C0 = *(Quad_001924C8*)(other->p14 + 0x1EE0);
                n->p134 = other;
            }
        }
        self->vtbl[0x14C / 4](self, 1);
        break;
    case 1:
        self->vtbl[0x14C / 4](self, 2);
        break;
    }
}

typedef void (*Hook_00192880)(void* self, s32 mode, void* other);

// An entry with a hook table at 0 and a 64-bit flag word at 0x538.
struct Entry_00269C98 { Hook_00192880* vtbl; u8 pad[0x538 - 4]; u64 flags; };

void func_00192880(s32 index)
{
    if (index == D_00269BCC)
        return;
    if (D_00269BCC >= 0) {
        u64 mask = (u64)(s64)-8193;
        mask = (mask << 16) | 0xFFFF;
        mask = (mask << 16) | 0xFFFF;
        Entry_00269C98** slot = (Entry_00269C98**)&D_00269C98[D_00269BCC];
        (*slot)->flags &= mask;
        Hook_00192880* vt = (*slot)->vtbl;
        Entry_00269C98* next = index >= 0 ? (Entry_00269C98*)D_00269C98[index] : 0;
        vt[0x130 / 4]((*slot), 0, next);
    }
    s32 old = D_00269BCC;
    D_00269BCC = index;
    if (index >= 0) {
        Entry_00269C98** slot = (Entry_00269C98**)&D_00269C98[index];
        (*slot)->flags |= 1ULL << 45;
        Hook_00192880* vt = (*slot)->vtbl;
        Entry_00269C98* prev = old >= 0 ? (Entry_00269C98*)D_00269C98[old] : 0;
        vt[0x130 / 4]((*slot), 1, prev);
    }
}

extern u8 D_002701F8[];
extern u8 D_00275BC0[];

void func_001E9498(void* a, void* b);

// A block whose 32-bit field at 0x324 is not aligned in the packed layout.
struct __attribute__((packed)) BlockAt324 { u8 pad[0x324]; u32 field; };

void func_00192A38(void* self, u32 value)
{
    BlockAt324* block = (BlockAt324*)D_002701F8;
    block->field = value;
    func_001E9498(D_00275BC0, D_002701F8);
}

extern u8* D_00261990;
extern s32 D_00262C68;
extern u8 D_00262C70[];
extern u8 D_00262D38[];
extern u8* D_0026F800;

// A record whose 16-bit flags sit at 0xAA.
struct Rec_00192A70 { u8 pad[0xAA]; u16 flags; };

// The current context: a count at 0x2D4, a pointer at 0x304 and a value at 0x32C.
struct Ctx_00192A70 {
    u8 pad0[0x2D4];
    s32 f2D4;
    u8 pad1[0x304 - 0x2D8];
    s32* p304;
    u8 pad2[0x32C - 0x308];
    s32 f32C;
};

extern Ctx_00192A70* D_0027051C;

s32 func_001493A0(void* p);
void func_001516C0(Ctx_00192A70* ctx, Rec_00192A70* rec);
void func_00150790(void* p, s32 n);
void func_0016EC20(Rec_00192A70* rec, s32 n);

void func_00192A70(void* self, Rec_00192A70* rec)
{
    if (func_001493A0((u8*)D_00261990 + 0x454) != 0)
        return;
    Rec_00192A70* a1 = (D_00262C68 & 4) ? (Rec_00192A70*)D_00262C70 : (Rec_00192A70*)D_00262D38;
    Ctx_00192A70* ctx = D_0027051C;
    if (ctx != 0 && ctx->f2D4 == 3 && ctx->f32C == 0 && (a1->flags & 0xC) != 0
        && *ctx->p304 != 0) {
        func_001516C0(ctx, a1);
    } else if ((rec->flags & 0xC) != 0 && D_0026F800 != 0) {
        func_00150790(D_0026F800, 1);
    }
    func_0016EC20(rec, 0xC);
}

s32 func_00190658(void)
{
    return 0;
}

struct Item_190660 { u8 pad0[0x724]; s32 kind; };

struct Slots_190660 {
    u8 pad0[0xC10];
    s32 count;
    Item_190660* items[4];
};

s32 func_00182FC8(void* p);
s32 func_001300E8(void* a, s32 b);

s32 func_00190660(Slots_190660* self, Item_190660* item)
{
    if (item != 0 && func_00182FC8(item) != 0) {
        if (func_001300E8(item, 8) == 0 || item->kind != 0xB) {
            s32 n = self->count;
            if ((u32)n < 4) {
                self->items[n] = item;
                self->count = n + 1;
                return 1;
            }
        }
    }
    return 0;
}

struct Node_001920E0 { u8 pad0[0x18]; void* link; };

void func_00182F78(void* self, s32 value);

void func_001920E0(Node_001920E0* self, s32 value)
{
    void* sub = (u8*)self + 0x40;
    func_00128018(self->link, value, sub, sub);
    func_00182F78(self, value);
}

void func_00192068(void* self, void* other);
void func_001384A0(void* other, void* sub);

void func_00192150(void* self, void* other)
{
    func_00192068(self, other);
    func_001384A0(other, (u8*)self + 0x50);
}

struct Obj_00192190 { u8 pad0[0x54]; f32 f54; f32 f58; };

void func_00192190(Obj_00192190* self)
{
    self->f54 = 0.5f;
    self->f58 = 0.5f;
}

struct Obj_001921A8 { u8 pad0[0x580]; s32 flag580; u8 pad1[0x598 - 0x584]; void* self598; };

void func_001B7968(void* self);
void func_00192990(void* self, s32 value);

void func_001921A8(Obj_001921A8* self)
{
    func_001B7968(self);
    self->self598 = self;
    self->flag580 = 1;
    func_00192990(self, 1);
}

struct Obj_1906F0 { u8 pad0[0xC24]; s32 f_C24; };

void func_001906F0(Obj_1906F0* self, s32 value)
{
    self->f_C24 = value;
}

struct Obj_1906F8 { u8 pad0[0x5F0]; s32 f_5F0; };

extern void func_001924C8(Obj_1906F8* self, s32 mode, void* extra);
extern void func_001C8F20(Obj_1906F8* self, s32 mode, s32 value);

void func_001906F8(Obj_1906F8* self, s32 flag, void* extra)
{
    func_001924C8(self, flag, extra);
    if (flag == 0) {
        func_001C8F20(self, 8, self->f_5F0);
    }
}

struct Obj_190770 { u8 pad0[0x7E0]; s32 f_7E0; };
struct Req_190770 { s32 f_0; u8 pad4[4]; s32 f_8; };

extern void func_001C9DE0(Obj_190770* self, s32 code, Req_190770* req);
extern void func_00160DA0(void);

void func_00190770(Obj_190770* self, s32 code, Req_190770* req)
{
    func_001C9DE0(self, code, req);
    if (code == 0x13) {
        if (req->f_0 == self->f_7E0) {
            if (req->f_8 == 0x53A) {
                func_00160DA0();
            }
        }
    }
}

struct Obj_1921E8 { u8 pad0[0x550]; s32 flag; };

void func_001BA130(Obj_1921E8* self);
void func_00192990(Obj_1921E8* self, s32 mode);

void func_001921E8(Obj_1921E8* self)
{
    func_001BA130(self);
    if (self->flag != 0) {
        return;
    }
    self->flag = 1;
    func_00192990(self, 0);
}

struct __attribute__((aligned(16))) Quad_1922E8 { s32 a, b, c, d; };
struct Obj_1922E8 {
    u8 pad0[0x140];
    Quad_1922E8 q140;
    u8 pad1[0x560 - 0x150];
    Quad_1922E8 q560;
};
struct Mgr_1922E8 { u8 pad0[0x224]; s32 f224; };


void func_00145088(void* mgr, s32 a1, void* a2, Obj_1922E8* self, s32 a4);
void func_001451F0(void* mgr, s32 a1, s32 a2, s32 a3, Obj_1922E8* self, s32 a5);

void func_001922E8(Obj_1922E8* self, s32 mode)
{
    if (mode != 0) {
        self->q560 = self->q140;
        func_00145088(D_00261990, 1, (u8*)D_00261990 + 0x520, self, 0);
        return;
    }
    for (s32 i = 1; i < 7; i++) {
        func_001451F0(D_00261990, 5, i, 0, self, 0);
    }
}

s32 func_00192410(void)
{
    return 1;
}

s32 func_001907F0(s32 value)
{
    if (value & 1) return value & -2;
    return 0;
}

s32 func_001909B0(f32 value)
{
    if (value > 1.0f) return 0;
    if (value < -1.0f) return 1;
    return 2;
}

void* func_001925F0(void);
void func_001929D0(void* value);

void func_00192418(void* self)
{
    if (self != func_001925F0()) func_001929D0(self);
}

s32 func_00192488(void* self)
{
    return 0;
}

struct Part_191A68 { u8 data[4]; };
struct Owner_191A68 { u8 head[0x34]; Part_191A68 part; };

void func_00191290(Part_191A68* part);

void func_00191A68(Owner_191A68* self)
{
    func_00191290(&self->part);
}

struct Part_191A88 { u8 data[4]; };
struct Owner_191A88 { u8 head[0x34]; Part_191A88 part; };

void func_00191570(Part_191A88* part);

void func_00191A88(Owner_191A88* self)
{
    func_00191570(&self->part);
}

void func_00137E70(void* a, void* b);
void func_0011EC40(void* a, void* b);

void func_00192068(void* self, void* other)
{
    func_00137E70(other, (u8*)self + 0x40);
    func_0011EC40(self, other);
}

struct Node_001920B0 { u8 pad[0x18]; s32 link; };

s32 func_00128018(void* a, s32 b, void* c, s32 d);

void func_001920B0(Node_001920B0* self, s32 arg)
{
    func_00128018((void*)self->link, 0, (u8*)self + 0x40, arg);
}

extern u8* D_00275710;

s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

s32 func_00193660(void)
{
    s32 r = func_0015A418(D_00275710, 5, 0x42C, 0);
    s32 v;
    if (r == 0) {
        v = 0;
    } else {
        v = *(s32*)(r + 0x48);
    }
    return v;
}

extern u8 D_0026A210[];

void func_001AA268(void* self);
s32 func_0015C188(s32 k);
void* func_0015C1C0(s32 k);

struct Obj_193E58 {
    u8 pad0[0x210];
    void** f210;
    u8 pad1[0x4C];
    s32 f260;
    u8 pad2[0x4];
    s32 arr268[3];
    u8 pad3[0x8];
    s32 f27C;
    u8 pad4[0x4];
    f32 f284;
};

void func_00193E58(Obj_193E58* self)
{
    func_001AA268(self);
    if (func_0015C188(2)) {
        self->f210 = (void**)D_0026A210;
        *self->f210 = func_0015C1C0(2);
    }
    self->f260 = -1;
    self->f27C = -1;
    for (u32 i = 0; i < 3; i++) {
        self->arr268[i] = -1;
    }
    self->f284 = 1.0f;
}

struct Obj_191AA8 {
    u8 pad0[0x54];
    void* p54;
};

s32 func_001909F0(void* p);

void func_00191AA8(Obj_191AA8* self)
{
    func_001909F0(self->p54);
}

extern s32 D_00269BA4;

void func_001F6C20(s32 a);

void func_00191E70(s32 value)
{
    if (D_00269BA4 != value) {
        func_001F6C20(0);
        D_00269BA4 = value;
    }
}

void* func_001930B0(void* p)
{
    return p;
}

s32 func_001930B8(s32 a, s32 b);

s32 func_001931F0(void)
{
    return func_001930B8(1, 0xFFFF);
}

struct S_190EA8 { u8 pad[4]; s32 value; };
s32 func_00190EA8(S_190EA8* p, s32 x) { return (x - p->value) >> 5; }

struct S_193270 { s32 a,b,c,d,e; };
void func_00193270(S_193270* p) { p->a=0; p->e=0; p->d=0; p->c=0; p->b=0; }

struct S_193300 { s32 a,b,c,d,e; };
void func_00193300(S_193300* p) { p->a=0; p->e=0; p->d=0; p->c=0; p->b=0; }

struct __attribute__((packed)) Pack_192020 { u64 value; };

void func_001830D8(void* self);

void func_00192020(void* a0)
{
    Pack_192020 tmp;
    tmp = *(Pack_192020*)((u8*)a0 + 0x38);
    func_001830D8(a0);
    *(Pack_192020*)((u8*)a0 + 0x38) = tmp;
}

struct __attribute__((packed)) Word_193210 { u32 value; };
struct Obj_193210 {
    s32 f00; s32 f04; s32 f08; s32 f0C; s32 f10;
    Word_193210 f14; Word_193210 f18; Word_193210 f1C; Word_193210 f20;
};

Obj_193210* func_00193210(Obj_193210* self, Word_193210* s1, Word_193210* s2, Word_193210* s3, Word_193210* s4)
{
    self->f14 = *s1;
    self->f18 = *s2;
    self->f1C = *s3;
    self->f20 = *s4;
    self->f00 = 0;
    self->f10 = 0;
    self->f0C = 0;
    self->f08 = 0;
    self->f04 = 0;
    return self;
}

extern u8 D_00269BA8[];

void func_00152438(void* self, s32 value);

void func_00191EC0()
{
    func_00152438(D_00269BA8, 0x38);
}

extern u8 D_00269BA8[];
void func_00152440(void* p);

void func_00191EE8(void)
{
    func_00152440(D_00269BA8);
}

extern u8 D_00269BA8[];
void func_00182D48(void* self);
void func_00152470(void* table, void* self);

void func_00191F68(void* self)
{
    func_00182D48(self);
    func_00152470(D_00269BA8, self);
}

extern u8 D_00269BA8[];
void func_00182ED0(void* self);
void func_00152600(void* table, void* self);

void func_00191FA0(void* self)
{
    func_00182ED0(self);
    func_00152600(D_00269BA8, self);
}

extern s32 D_0026A068[];

s32 func_00193598(s32 index)
{
    return D_0026A068[index];
}

// was NEAR: GCC folds the final return 1/return 0 into sltiu/xori; retail keeps li v0,16 + bne and a separate move v0,zero tail

struct Obj_190740 {
    u8 pad0[0x724];
    s32 kind;
};

s32 func_00190740(Obj_190740* self)
{
    switch (self->kind) {
    case 0x10: return 1;
    case 0xB: return 2;
    }
    return 0;
}

s32 func_001DDA80(void* p);

struct Obj_00192450 {
    u8 pad[0x14];
    void* f14;
};

s32 func_00192450(Obj_00192450* self)
{
    if ((D_00262C64 & 1) || func_001DDA80(self->f14)) return 1;
    return 0;
}

struct __attribute__((aligned(16))) Quad_192380 { s32 w[4]; };

extern u8 D_00269BC0[];
extern u8* D_00261990;
void func_001B9F30(void);
// func_001EA4B8 takes its float arguments first: the caller then sets $f14 before $a0.
f32 func_001EA4B8(f32 a, f32 b, f32 c, Quad_192380* p, s32 zero);

void func_00192380(u8* self, u8* out, f32 a)
{
    func_001B9F30();
    if (*(s32*)(self + 0x554) != 0) {
        *(Quad_192380*)(out + 0x10) = *(Quad_192380*)(self + 0x560);
        return;
    }
    u8* base = D_00261990;
    if (*(s32*)(base + 0x224) == 0) {
        *(f32*)(out + 0x18) = func_001EA4B8(*(f32*)(self + 0x568), *(f32*)(self + 0x148), a, (Quad_192380*)D_00269BC0, 0);
    }
    *(Quad_192380*)(self + 0x560) = *(Quad_192380*)(out + 0x10);
}

extern s32 D_00269C90;

s32 func_00192688(s32 key)
{
    s32 i;
    for (i = 0; i < D_00269C90; i++) {
        if (key == (s32)D_00269C98[i]) {
            return i;
        }
    }
    return -1;
}
