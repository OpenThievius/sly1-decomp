// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_5E08 {
    u8 pad0[0x624];
    void* f624;
};

struct Vtbl_5E08 {
    void* slots[0x148 / 4];
};

typedef void (*VFn_5E08)(void* self);

void func_001924C8(void* self);

void func_001E5E08(void* self)
{
    Obj_5E08* o = (Obj_5E08*)self;

    if (o->f624 != 0) {
        VFn_5E08 fn = *(VFn_5E08*)(*(u8**)o->f624 + 0x148);
        fn(o->f624);
    } else {
        func_001924C8(self);
    }
}

struct Obj_E7440 { u8 pad[0x260]; s32 f260; f32 f264; };
extern f32 D_00261868;

void func_001E7440(Obj_E7440* a0, s32 a1)
{
    if (a1 != a0->f260) {
        a0->f260 = a1;
        a0->f264 = D_00261868;
    }
}

struct Ptr_1E76E0 {
    s32 f0;
    union {
        s32 i4;
        f32 f4;
    };
};

struct Obj_1E76E0 {
    u8 pad0[0x218];
    Ptr_1E76E0* f218;
    u8 pad1[0x250 - 0x21C];
    s32 f250;
    u8 pad2[0x268 - 0x254];
    s32 f268;
};

extern s32 D_00270458;
void func_001AA998(void* self, s32 flag);
void func_001AAB20(void* self, f32 x, f32 y);
void func_001E7518(void* self, s32 mode);

void func_001E76E0(Obj_1E76E0* self, s32 value)
{
    s32 old = self->f250;
    func_001AA998(self, value);
    if (old == value) return;
    if (old != 0) goto done;
    if (D_00270458 == 4) {
        self->f218->i4 = 0;
        func_001AAB20(self, 640.0f, 360.0f);
    } else {
        self->f218->f4 = -20.0f;
        func_001AAB20(self, 160.0f, 125.4f);
    }
done:
    if (value != 2) return;
    if (D_00270458 == 4) return;
    self->f268 = -1;
    func_001E7518(self, 3);
}

struct Ret_1E4880 { u8 pad[0x20]; f32 value; };

f32 func_001E4880(void* a0, void* a1, void* a2, Ret_1E4880* a3)
{
    return a3->value;
}

void func_001F5C0C(void* p, s32 v, s32 n);

struct Ctor_1E4E38 { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; u8 body[0x20]; };

Ctor_1E4E38* func_001E4E38(Ctor_1E4E38* self)
{
    self->f4 = 0;
    self->f10 = 0;
    self->fC = self->f8 = -1;
    func_001F5C0C(self->body, 0, 0x20);
    return self;
}

struct Blk_1E4E80 { s32 state; s32 a; s32 b; s32 c; s32 d; };

void func_001E4E80(Blk_1E4E80* self, s32 a1, s32 a2, s32 a3, s32 a4)
{
    if (self->state == 0) {
        self->state = 1;
        self->a = a1;
        self->b = a2;
        self->c = a3;
        self->d = a4;
    }
}

extern u8 D_00275AF0[];

void func_001E4E38(void* item);

void func_001E5328(void* owner, s32 code)
{
    if (code == 0xFFFF && owner != 0) {
        func_001E4E38(D_00275AF0);
    }
}

void func_001E5328(void* owner, s32 code);

void func_001E5358(void)
{
    func_001E5328((void*)1, 0xFFFF);
}

struct Table_1E5378 {
    u8 pad0[0x63C];
    void* p63C;
    void* p640;
    s32 f644;
    u8 pad1[0x650 - 0x648];
    f32 f650;
    f32 f654;
    f32 f658;
    f32 f65C;
};

void func_001921A8(void* self);
void* func_0018D500(s32 size);

void func_001E5378(Table_1E5378* self)
{
    func_001921A8(self);
    self->f644 = 1;
    self->p63C = func_0018D500(0x40);
    self->p640 = func_0018D500(0x40);
    self->f658 = -1.5f;
    self->f65C = 1.5f;
    self->f650 = -0.7f;
    self->f654 = 0.7f;
}

struct Table_1E53F8 {
    u8 pad0[0x638];
    s32 count;
    u8 pad1[4];
    void** items;
};

void func_001E53F8(Table_1E53F8* self, void* value)
{
    s32 n = self->count;
    if (n < 0x11) {
        self->items[n] = value;
        self->count = n + 1;
    }
}

struct __attribute__((aligned(16))) Quad_1E5750 { s32 a, b, c, d; };

struct Ctx_1E5750 {
    u8 pad0[0x80];
    Quad_1E5750 q80;
    Quad_1E5750 q90;
    Quad_1E5750 qA0;
    u8 pad1[0x480 - 0xB0];
    f32 f480;
    u8 pad2[0x4BC - 0x484];
    s32 f4BC;
};

struct Actor_1E5750 {
    u8 pad0[0x110];
    Quad_1E5750 q110;
    Quad_1E5750 q120;
    Quad_1E5750 q130;
    u8 pad1[0x614 - 0x140];
    void* f614;
    u8 pad2[0x61C - 0x618];
    s32 f61C;
    u8 pad3[0x630 - 0x620];
    s32 f630;
    u8 pad4[0x644 - 0x634];
    s32 f644;
};

extern Ctx_1E5750* D_00261990;
extern u8 D_00275BC0[];
extern u8 D_002701F8[];

void func_001922E8(void* a, void* b);
void func_001E9498(void* self, void* node);
void func_001E9570(void* self);
void func_001356C0(void* self, s32 mode);
void func_00145088(void* a, s32 b, void* c, void* d, s32 e);
void func_001495E8(void* a, s32 b);
void func_001451F0(void* a, s32 b, s32 c, void* d, void* e, s32 f);
void func_00149610(void* a);
void func_001B64D8(void* a, s32 b);

void func_001E5750(Actor_1E5750* self, u8* p)
{
    func_001922E8(self, p);
    if (p != 0) {
        D_00261990->f480 = 100.0f;
        func_001E9498(D_00275BC0, D_002701F8);
        func_001356C0(D_002701F8, 5);
        D_00261990->f4BC = self->f61C;
        if (self->f630 != 0) {
            D_00261990->q80 = self->q110;
            D_00261990->q90 = self->q120;
            D_00261990->qA0 = self->q130;
        }
        func_00145088(D_00261990, 6, (u8*)D_00261990 + 0x460, self, 0);
        func_001495E8((u8*)D_00261990 + 0x460, self->f644);
        func_001B64D8(self->f614, 0x359);
    } else {
        D_00261990->f480 = 10.0f;
        func_001E9570(D_00275BC0);
        func_001451F0(D_00261990, 0xF, 6, (u8*)D_00261990 + 0x460, self, 0);
        func_00149610((u8*)D_00261990 + 0x460);
        func_001B64D8(self->f614, 0x358);
    }
}

struct Actor_1E5C78 { u8 pad[0x614]; void* f614; void* f618; };

void func_001B6598(void* dev, s32* out);
void func_001B6568(void* dev, s32* out);
s32 func_001A8C50(void* a);
void func_001B64D8(void* dev, s32 value);

void func_001E5C78(Actor_1E5C78* self)
{
    s32 a;
    s32 b;
    func_001B6598(self->f614, &a);
    func_001B6568(self->f614, &b);
    if (a == 0x359 && b == a) {
        if (func_001A8C50(self->f618) != 0) {
            func_001B64D8(self->f614, 0x35A);
        }
    }
}

struct Dev_1E5CE8 { u8 pad[0x24]; s32 f24; };
struct Hdl_1E5CE8 { u8 pad[0x7E0]; s32 f7E0; };
struct Actor_1E5CE8 { u8 pad[0x614]; void* f614; void* f618; u8 pad2[8]; Hdl_1E5CE8* f624; s32 f628; };
struct Rec_1E5CE8 { s32 w0; s32 w4; s32 w8; };

void func_00192230(void* self, s32 kind, Rec_1E5CE8* rec);
void func_001A8C90(void* a, s32 b);

void func_001E5CE8(Actor_1E5CE8* self, s32 kind, Rec_1E5CE8* rec)
{
    func_00192230(self, kind, rec);
    if (kind == 0x13) {
        Dev_1E5CE8* dev = (Dev_1E5CE8*)self->f614;
        s32 id = rec->w0;
        if (id == dev->f24) {
            if (rec->w8 == 0x35B) {
                func_001A8C90(self->f618, 1);
            }
        } else if (self->f624 != 0 && id == self->f624->f7E0) {
            s32 k = rec->w8;
            if (k != 0x15E) {
                if (k == 0x15F) {
                    self->f628 = 0;
                }
            } else {
                self->f628 = 1;
            }
        }
    }
}

struct Ctx_1E5DA8 { u8 pad[0x618]; void* p618; };

s32 func_001B8A08(void* a, void* b);
s32 func_001A8820(void* p, void* v);

s32 func_001E5DA8(Ctx_1E5DA8* self, void* arg)
{
    if (func_001B8A08(self, arg)) {
        return 1;
    }
    if (self->p618 != 0) {
        s32 r = func_001A8820(self->p618, arg);
        if (r != 0) {
            return 1;
        }
    }
    return 0;
}

struct Pair_1E5E50 { s32 lo; s32 hi; };

void func_001E5E50(void* a0, void* a1, Pair_1E5E50* out)
{
    out->lo = 0;
    out->hi = 0;
}

struct Obj_001E5E60 { u8 pad[0x620]; void* value; };
void* func_001E5E60(Obj_001E5E60* self) { return self->value ? self->value : self; }

struct Obj_001E6268 { u8 pad[0xC70]; f32 value; };
void func_001E6268(Obj_001E6268* self, s32* first, s32* second) { s32 n = (s32)(self->value * 57.0f); s32 half = (57 - n) / 2; *first = half; *second = half + n; }

typedef s32 (*VFn_1E55D0)(void* self);
struct Obj_1E55D0 { VFn_1E55D0* vtbl; };
struct Item_1E55D0 { u8 pad0[0x724]; s32 f724; };
struct Self_1E55D0 { u8 pad0[0x14]; void* f14; u8 pad1[0x568]; s32 f580; u8 pad2[0x9C]; Obj_1E55D0* f620; };

void func_00192B58(void* self);
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void func_001C8F20(void* node, s32 kind, s32 flag);

void func_001E55D0(Self_1E55D0* self)
{
    void* arr[8];
    s32 n;
    s32 count;
    s32 i;

    func_00192B58(self);
    if (self->f620 != 0) {
        if (self->f620->vtbl[81](self->f620)) {
            n = func_0015A4F0(self->f14, 5, 8, 0, 8, arr);
            if (n > 0) {
                count = n;
                i = 0;
                do {
                    void* item = arr[i];
                    if (item != self->f620) {
                        if (((Item_1E55D0*)item)->f724 != 0xB) {
                            func_001C8F20(item, 0xA, 0);
                        }
                    }
                    count--;
                    i++;
                } while (count != 0);
            }
            self->f580 = 0;
        } else {
            self->f580 = 1;
        }
    }
}

extern u8* D_00275710;
extern u8 D_00275640[];
extern u8 D_00275B58[];
extern f32 D_00275650;
extern f32 D_00275654;
extern f32 D_00275658;
extern f32 D_0027565C;
extern f32 D_00275660;

typedef void (*VFn_1E6188)(void* self);
struct Inst_1E6188 { VFn_1E6188* vtbl; };
struct Obj_1E6188 { u8 pad[0x27C]; Inst_1E6188* p27C; };

void func_001AA268(void* self);
void* func_0011E580(s32 a0, void* a1, void* a2, s32 a3, s32 a4);
void func_00184768(void* p, s32 v);
void func_001847F0(void* p, void* q);
void func_00184858(void* p, f32 v);
void func_00184818(void* p, f32 v);
void func_00184878(void* p, f32 v);
void func_00184838(void* p, f32 v);
void func_00184898(void* p, f32 v);
void func_00184990(void* p, void* q);
void func_00184968(void* p, s32 v);

void func_001E6188(Obj_1E6188* self)
{
    func_001AA268(self);
    self->p27C = (Inst_1E6188*)func_0011E580(0x51, D_00275710, 0, 0x201, -1);
    func_00184768(self->p27C, 1);
    func_001847F0(self->p27C, D_00275640);
    func_00184858(self->p27C, D_00275650);
    func_00184818(self->p27C, D_00275654);
    func_00184878(self->p27C, D_00275658);
    func_00184838(self->p27C, D_0027565C);
    func_00184898(self->p27C, D_00275660);
    func_00184990(self->p27C, D_00275B58);
    func_00184968(self->p27C, 1);
    self->p27C->vtbl[7](self->p27C);
}

extern u8 D_00262280[];

s32 func_001E9A68(void);
void func_001613C0(void* p, s32 a, s32 b, s32 c);
void func_00161708(void* p, s32 a, u64 b);
void func_001E6600(void* self, void* p);
void func_001E6C20(void* self, void* p);

void func_001E73B8(void* self)
{
    u8* s = D_00262280;
    if (func_001E9A68()) {
        func_001613C0(s, 0, 1, 0xE);
        func_00161708(s, 0x47, 0x31001);
        func_00161708(s, 0x42, 0x44);
        func_001E6600(self, s);
        func_001E6C20(self, s);
    }
}

typedef s32 (*VFn_1E5888)(void* self, void* other);
struct Vobj_1E5888 { VFn_1E5888* vtbl; };
struct Rec_1E5888 { u8 pad0[0x48]; Vobj_1E5888* f48; };
struct Ctx_1E5888 { u8 pad0[0x618]; Rec_1E5888* f618; };
struct Node_1E5888 { u8 pad0[0x50]; Vobj_1E5888* f50; u8 pad1[0x4E0]; u64 f538; };

s32 func_001A8820(void* p, void* v);

s32 func_001E5888(Ctx_1E5888* self, Node_1E5888* node)
{
    Vobj_1E5888* a;
    Vobj_1E5888* b;

    if (node->f538 & (1ULL << 43)) {
        return 0;
    }
    if ((void*)node->f50 == (void*)self) {
        return 0;
    }
    if (func_001A8820(self->f618, node) != 0) {
        return 0;
    }
    a = node->f50;
    b = self->f618->f48;
    if (a->vtbl[60](a, b) != 0 || b->vtbl[60](b, a) != 0) {
        return 0;
    }
    return 1;
}
