// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "fpu.h"
#include "list_iter.h"
extern u8* D_00262E10;
extern u8* D_00275710;

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

typedef void (*VFn_1E5428)(void* self, void* other);

struct Vt_1E5428 {
    VFn_1E5428* vtbl;
};

struct Ctx_1E5428 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x584 - 0x18];
    void* f584;
    void* f588[3];
    f32 f594;
    void* f598;
    u8 pad2[0x610 - 0x59C];
    void* f610;
    void* f614;
    u8 pad3[0x620 - 0x618];
    void* f620;
    void* f624;
    u8 pad4[0x638 - 0x628];
    s32 f638;
    void** f63C;
    s32* f640;
};

struct Peer_1E5428 {
    u8 pad0[0xC2C];
    Ctx_1E5428* owner;
};

extern s32 D_00275B28[10];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void* func_001B6290(void* a, void* self, s32 b, s32 c);
void* func_0015A448(void* a, s32 b, void* c);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_00189230(void* a, void* b, void* c);

void func_001E5428(Ctx_1E5428* self)
{
    void* r2;
    s32 i;
    s32 n;
    void* r;

    func_00124A48(self);
    func_00124DF8(self, 3, D_00275B28);
    self->f614 = func_001B6290(self->f610, self, -1, 1);
    r = func_0015A448(D_00275710, 7, self);
    if (r != 0) {
        self->f620 = r;
        self->f624 = r;
        ((Peer_1E5428*)r)->owner = self;
        self->f598 = r;
        self->f584 = (void*)func_0015A418(self->f14, 1, 0x160, r);
        i = 0;
        do {
            self->f588[i] = (void*)func_0015A418(self->f14, 1, i + 0x161, r);
            i++;
        } while (i < 3);
        self->f594 = 300.0f;
        ((Vt_1E5428*)r)->vtbl[27](r, self);
    } else {
        self->f620 = (void*)D_00262E10;
    }

    n = 0;
    while (n < self->f638) {
        r2 = func_0015A448(self->f14, self->f640[n], self);
        if (r2 != 0) {
            self->f63C[n] = r2;
            n++;
        }
    }
    self->f638 = n;
    func_00189230((u8*)self + 0x110, (u8*)self + 0x648, (u8*)self + 0x64C);
}

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

extern u8* D_00262E10;

typedef void (*VFn_56A0)(void* self, f32 t, void* buf);

void func_001E5938(void);
void func_0016EC20(void* obj, s32 n);
void func_001E5C78(void* self);
s32 func_00182FC8(void);
void func_001F5C0C(void* p, s32 v, s32 n);

void func_001E56A0(void* self, void* obj, f32 t)
{
    u8 buf[0xC4];
    u8* o;

    func_001E5938();
    if (*(u16*)((u8*)obj + 0xAA) & 0xC0) {
        func_0016EC20(obj, 0xC0);
        func_001E5C78(self);
    }
    o = D_00262E10;
    if (o != 0) {
        if (*(s32*)(o + 0x2740) != 0) {
            if (func_00182FC8()) {
                VFn_56A0 fn;
                func_001F5C0C(buf, 0, 0xC4);
                o = D_00262E10;
                fn = *(VFn_56A0*)(*(u8**)o + 0x134);
                if (fn != 0) {
                    fn(o, t, buf);
                }
            }
        }
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

INCLUDE_ASM(func_001E5938);

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

struct Pair_1E5E50 { s32 lo; s32 hi; };

void func_001E5E50(void* a0, void* a1, Pair_1E5E50* out)
{
    out->lo = 0;
    out->hi = 0;
}

struct Obj_001E5E60 { u8 pad[0x620]; void* value; };
void* func_001E5E60(Obj_001E5E60* self) { return self->value ? self->value : self; }


struct Elem_1E5E70 {
    u8 pad0[4];
    f32 f4;
    u8 pad1[4];
    f32 fC;
    u8 pad2[0x2C - 0x10];
    f32 f2C;
    u8 pad3[4];
    f32 f34;
    u8 pad4[4];
    u32 f3C;
    u32 f40;
    f32 f44;
    f32 f48;
    f32 f4C;
    f32 f50;
    f32 f54;
};

struct Obj_1E5E70 {
    u8 pad0[0x214];
    s32 mode;
    u8 pad1[0x234 - 0x218];
    f32 f234;
    f32 f238;
    u8 pad2[0x254 - 0x23C];
    u8 elems[0xC24 - 0x254];
    s32 fC24;
    u8 padC28[4];
    f32 fC2C;
    u8 padC30[0xC4C - 0xC30];
    f32 fC4C;
    f32 fC50;
    f32 fC54;
    f32 fC58;
    u8 padC5C[0xC64 - 0xC5C];
    f32 fC64;
    f32 fC68;
    f32 fC6C;
};

void func_001AA1F0(Obj_1E5E70* self, s32 kind);
f32 func_001EAAE0(f32 a, f32 b);

void func_001E5E70(Obj_1E5E70* self, s32 kind)
{
    self->f234 = 160.0f;
    self->f238 = 125.4f;
    self->fC54 = self->fC58 = 3.3000002f;
    func_001AA1F0(self, kind);
    f32 sign;
    if (kind == 0x1A) {
        self->fC50 = 0.0f;
        self->fC4C = self->f234 - 62.7f;
        sign = 1.0f;
    } else {
        self->fC50 = self->f234;
        self->fC4C = 62.7f;
        sign = -1.0f;
    }
    f32 step = 1.0f / 57.0f;
    s32 i = 0;
    u32 dim = 0x30000000;
    s32 special = 0x1A;
    Elem_1E5E70* p;
    for (p = (Elem_1E5E70*)self->elems; i < 0x39; i++) {
        f32 t = (f32)i * step;
        f32 y = t + t - 1.0f;
        p->f34 = y;
        p->f2C = sign * Fpu::Sqrt(1.0f - y * y);
        p->f3C = p->f40 = (i & 1) ? dim : 0x30808080;
        p->f44 = p->f48 = 0.0f;
        if (self->mode == special) {
            p->f4C = func_001EAAE0(0.6f, 0.8f);
            p->f50 = func_001EAAE0(0.4f, 0.6f);
            p->f54 = func_001EAAE0(0.05f, 0.2f);
        } else {
            p->f4C = func_001EAAE0(0.3f, 0.4f);
            p->f50 = func_001EAAE0(0.2f, 0.3f);
            p->f54 = func_001EAAE0(0.1f, 0.4f);
        }
        if (i != 0) {
            p->fC = p->f34;
            p->f4 = p->f2C;
        }
        p = (Elem_1E5E70*)((u8*)p + 0x2C);
    }
    self->fC2C = 1.0f;
    self->fC24 = 0;
    if (self->mode == 0x1A) {
        self->fC64 = func_001EAAE0(1.0f, 1.4f);
        self->fC68 = func_001EAAE0(0.6f, 0.8f);
        self->fC6C = func_001EAAE0(0.1f, 0.2f);
    } else {
        self->fC64 = func_001EAAE0(0.5f, 0.7f);
        self->fC68 = func_001EAAE0(0.2f, 0.3f);
        self->fC6C = func_001EAAE0(0.3f, 0.5f);
    }
}

extern u8* D_00275710;
extern u8 D_00275640[];
extern f32 D_00275B58[2];
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

struct Obj_001E6268 { u8 pad[0xC70]; f32 value; };
void func_001E6268(Obj_001E6268* self, s32* first, s32* second) { s32 n = (s32)(self->value * 57.0f); s32 half = (57 - n) / 2; *first = half; *second = half + n; }

struct Elem_1E62A8 { f32 f0; f32 f4; f32 f8; f32 fC; u8 pad10[0x1C]; };
struct Self_1E62A8 {
    u8 pad0[0x21C];
    f32 f21C; f32 f220; f32 f224; f32 f228;
    u8 pad22C[8];
    f32 f234; f32 f238;
    u8 pad23C[0x44];
    Elem_1E62A8 e[0x39];
    f32 fC4C; f32 fC50;
};
struct Ctx_1E62A8 { s32 x; };
extern s32 D_00270458;
void func_00161670(Ctx_1E62A8* c, s32 a, s32 b, s32 d, s32 e);
void func_001615F0(Ctx_1E62A8* c, s32 a, s32 b, s32 d, s32 e);
void func_001E6268(Self_1E62A8* self, s32* a, s32* b);

void func_001E62A8(Self_1E62A8* self, Ctx_1E62A8* c, s32 k)
{
    if (D_00270458 == 4) {
        f32 y = self->f228;
        f32 x = self->f224;
        s32 x0 = (s32)((x + 1728.0f) * 16.0f);
        s32 y0 = (s32)((y * 0.45454547f + 1936.0f) * 16.0f);
        func_00161670(c, x0, y0, k, 0);
        func_00161670(c, x0, (s32)(((y + self->f238) * 0.45454547f + 1936.0f) * 16.0f), k, 0);
        func_001615F0(c, (s32)(((x + self->f234) + 1728.0f) * 16.0f), y0, k, 0);
        y = y + self->f238;
        x = x + self->f234;
        func_001615F0(c, (s32)((x + 1728.0f) * 16.0f), (s32)((y * 0.45454547f + 1936.0f) * 16.0f), k, 0);
    } else {
        s32 r[2];
        func_001E6268(self, &r[0], &r[1]);
        if (r[0] != r[1]) {
            f32 a = self->f220 + 62.7f;
            f32 b = self->f21C + self->fC50;
            f32 bx = self->f21C + self->fC4C;
            s32 x0, y0, i;
            f32 t;
            y0 = (s32)(((a + self->e[r[0]].f8 * 62.7f) * 0.45454547f + 1936.0f) * 16.0f);
            x0 = (s32)((b + 1728.0f) * 16.0f);
            t = bx + self->e[r[0]].f0 * 62.7f;
            func_00161670(c, x0, y0, k, 0);
            func_00161670(c, (s32)((t + 1728.0f) * 16.0f), y0, k, 0);
            for (i = r[0]; i < r[1]; i++) {
                Elem_1E62A8* p = &self->e[i];
                t = bx + p->f4 * 62.7f;
                s32 x = (s32)((b + 1728.0f) * 16.0f);
                y0 = (s32)(((a + p->fC * 62.7f) * 0.45454547f + 1936.0f) * 16.0f);
                func_001615F0(c, x, y0, k, 0);
                func_001615F0(c, (s32)((t + 1728.0f) * 16.0f), y0, k, 0);
            }
        }
    }
}

INCLUDE_ASM(func_001E6600);

struct Rgba_1E6C20 { u8 c[4]; };
struct Elem_1E6C20 { f32 f0; f32 f4; f32 f8; f32 fC; u8 pad[0x2C - 0x10]; };
struct Self_1E6C20 {
    u8 pad0[0x21C]; f32 f21C; f32 f220;
    u8 pad1[0x260 - 0x224]; s32 f260; f32 f264;
    u8 pad2[0x280 - 0x268]; Elem_1E6C20 elems[1];
};
struct Buf_1E6C20;

extern f32 D_00261868;
extern Rgba_1E6C20 D_002610D8;
extern Rgba_1E6C20 D_002610E0;

void func_001613C0(Buf_1E6C20* b, s32 a1, s32 a2, s32 a3);
void func_00161458(Buf_1E6C20* b, u32 c);
void func_001615F0(Buf_1E6C20* b, s32 x, s32 y, s32 a3, s32 a4);
void func_001E6268(Self_1E6C20* self, s32* first, s32* last);

struct Lerp_1E6C20 {
    static u8 Of(s32 a, s32 b, f32 t)
    {
    if (a == b) return b;
    if (a < b) return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
    return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
    }
};

#define SX_1E6C20(x) ((s32)(((x) + 1728.0f) * 16.0f))
#define SY_1E6C20(y) ((s32)(((y) * 0.45454547f + 1936.0f) * 16.0f))

struct Clamp_1E6C20 {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) return lo;
        if (hi < x) return hi;
        return x;
    }
};

void func_001E6C20(Self_1E6C20* self, Buf_1E6C20* buf)
{
    Rgba_1E6C20 c;
    f32 t;
    switch (self->f260) {
    case 0:
        t = Clamp_1E6C20::Of((D_00261868 - self->f264) * 5.0f, 0.0f, 1.0f);
        break;
    case 1:
        t = Clamp_1E6C20::Of(1.0f - (D_00261868 - self->f264) * 5.0f, 0.0f, 1.0f);
        break;
    }
    func_001613C0(buf, 0, 1, 1);
    {
        Rgba_1E6C20 a = D_002610D8;
        Rgba_1E6C20 b = D_002610E0;
        Rgba_1E6C20 r;
        r.c[0] = Lerp_1E6C20::Of(a.c[0], b.c[0], t);
        r.c[1] = Lerp_1E6C20::Of(a.c[1], b.c[1], t);
        r.c[2] = Lerp_1E6C20::Of(a.c[2], b.c[2], t);
        r.c[3] = Lerp_1E6C20::Of(a.c[3], b.c[3], t);
        c = r;
    }
    func_00161458(buf, *(u32*)&c);
    func_001613C0(buf, 0x44, 1, 4);
    f32 x0 = self->f21C + *(f32*)((u8*)self + 0xC4C);
    f32 y0 = self->f220 + 62.7f;
    f32 xe = self->f21C + *(f32*)((u8*)self + 0xC50);
    s32 first, last;
    func_001E6268(self, &first, &last);
    Elem_1E6C20* e = &self->elems[first];
    f32 len = *(f32*)((u8*)self + 0xC54);
    f32 xa = x0 + e->f0 * 62.7f;
    f32 xb = x0 + (len + 62.7f) * e->f0;
    f32 ya = y0 + e->f8 * 62.7f;
    f32 yb = ya - len;
    func_001615F0(buf, SX_1E6C20(xe), SY_1E6C20(ya), 0, 0);
    func_001615F0(buf, SX_1E6C20(xe), SY_1E6C20(yb), 0, 0);
    func_001615F0(buf, SX_1E6C20(xa), SY_1E6C20(ya), 0, 0);
    func_001615F0(buf, SX_1E6C20(xb), SY_1E6C20(yb), 0, 0);
    for (s32 i = first; i < last; i++) {
        e = &self->elems[i];
        xa = x0 + e->f0 * 62.7f;
        ya = y0 + e->f8 * 62.7f;
        xb = x0 + (*(f32*)((u8*)self + 0xC54) + 62.7f) * e->f0;
        yb = y0 + (*(f32*)((u8*)self + 0xC54) + 62.7f) * e->f8;
        func_001615F0(buf, SX_1E6C20(xa), SY_1E6C20(ya), 0, 0);
        func_001615F0(buf, SX_1E6C20(xb), SY_1E6C20(yb), 0, 0);
    }
    xa = x0 + e->f4 * 62.7f;
    ya = y0 + e->fC * 62.7f;
    yb = ya + *(f32*)((u8*)self + 0xC54);
    xb = x0 + (*(f32*)((u8*)self + 0xC54) + 62.7f) * e->f4;
    func_001615F0(buf, SX_1E6C20(xa), SY_1E6C20(ya), 0, 0);
    func_001615F0(buf, SX_1E6C20(xb), SY_1E6C20(yb), 0, 0);
    func_001615F0(buf, SX_1E6C20(xe), SY_1E6C20(ya), 0, 0);
    func_001615F0(buf, SX_1E6C20(xe), SY_1E6C20(yb), 0, 0);
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

struct Obj_E7440 { u8 pad[0x260]; s32 f260; f32 f264; };
extern f32 D_00261868;

void func_001E7440(Obj_E7440* a0, s32 a1)
{
    if (a1 != a0->f260) {
        a0->f260 = a1;
        a0->f264 = D_00261868;
    }
}

struct Node_1E7460;
struct Obj_1E7460;
void func_00126BC0(Node_1E7460* node, Obj_1E7460* self);
extern s32 D_00270458;

struct Node_1E7460 {
    void** vtable;
    u8 pad4[0x2C8 - 4];
    unsigned long f2C8;
};
struct Obj_1E7460 {
    u8 pad0[0x270];
    Node_1E7460* f270;
    Node_1E7460* f274;
    Node_1E7460* f278;
};

void func_001E7460(Obj_1E7460* self)
{
    Node_1E7460* cur = self->f274;
    if (self->f270 == cur) {
        return;
    }
    if (cur != 0) {
        if (!(D_00270458 == 4 && cur == self->f278)) {
            ((void (*)(Node_1E7460*))cur->vtable[7])(cur);
        }
    }
    self->f274 = self->f270;
    if (self->f274 != 0) {
        ((void (*)(Node_1E7460*))self->f274->vtable[6])(self->f274);
        if (D_00270458 != 4) {
            func_00126BC0(self->f274, self);
        }
        self->f274->f2C8 |= 0x100000000UL;
    }
}

struct Obj_1E7460;
void func_001E7460(Obj_1E7460* self);
extern f32 D_00261858[];
f32 func_001EAAE0(f32 a, f32 b);
void func_001BFCD8(s32 id, s32 a, s32 b, s32 c, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, s32 d, s32 e);

struct Obj_1E77C0;
typedef void (*VFn_1E77C0)(Obj_1E77C0* self, s32 state);
struct Elem_1E77C0
{
    u8 pad00[0x18];
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
};
struct Obj_1E77C0
{
    VFn_1E77C0* vtbl;
    u8 pad004[0x210];
    s32 f214;
    u8 pad218[0x38];
    s32 f250;
    u8 pad254[0x14];
    s32 f268;
    f32 f26C;
    s32 f270;
    s32 f274;
    u8 pad278[0x8];
    Elem_1E77C0 elems[57];
    u8 padC4C[0x10];
    f32 fC5C;
    f32 fC60;
    f32 fC64;
    f32 fC68;
    f32 fC6C;
    f32 fC70;
};
void func_001E7518(Obj_1E77C0* self, s32 mode)
{
    if (mode == self->f268) {
        return;
    }
    switch (mode) {
    case 0: {
        func_001BFCD8(0x8C, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        for (s32 i = 0; i < 57; i++) {
            Elem_1E77C0* e = &self->elems[i];
            e->f18 = 1.0f;
            e->f1C = func_001EAAE0(0.0f, 0.05f);
            e->f20 = 1.0f;
            e->f24 = 0.6f;
            e->f28 = 0.2f;
        }
        break;
    }
    case 2:
        func_001BFCD8(0x8D, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    case 1:
        self->fC70 = 1.0f;
        break;
    case 3:
        self->fC70 = 0.0f;
        func_001E7460((Obj_1E7460*)self);
        break;
    }
    self->f268 = mode;
    self->f26C = D_00261858[4];
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




extern f32 D_00261858[];
extern s32 D_00270448;
extern s32 D_00270458;

void func_001AA298(Obj_1E77C0* self);
f32 func_001EA4B8(f32* p, s32 zero, f32 a, f32 b, f32 c);
s32 func_001EAC68(f32 a, f32 b, f32 c);
f32 func_001EAAE0(f32 a, f32 b);
void func_001E7518(Obj_1E77C0* self, s32 mode);

void func_001E77C0(Obj_1E77C0* self)
{
    func_001AA298(self);
    s32 state = self->f250;
    s32 sub = self->f268;
    switch (state)
    {
    case 0:
        if (self->f274 != 0)
        {
            state = 2;
        }
        else if (self->f270 != 0)
        {
            state = D_00270448 != 0;
        }
        break;
    case 3:
        sub = 3;
        break;
    case 2:
        switch (sub)
        {
        case 0:
        {
            f32 f = self->fC70 + D_00261858[5] * 5.0f;
            self->fC70 = f;
            if (1.0f <= f)
            {
                self->fC70 = 1.0f;
                sub = 1;
            }
            break;
        }
        case 2:
        {
            f32 f = self->fC70 - D_00261858[5] * 5.0f;
            self->fC70 = f;
            if (f <= 0.0f)
            {
                self->fC70 = 0.0f;
                sub = 3;
            }
            break;
        }
        case 3:
            if (self->f270 != 0)
            {
                sub = 0;
            }
            else
            {
                state = 3;
            }
            break;
        }
        if (D_00270458 != 4)
        {
            self->fC5C = func_001EA4B8(&self->fC64, 0, self->fC5C, self->fC60, D_00261858[5]);
            if (func_001EAC68(self->fC5C, self->fC60, 1e-4f) != 0)
            {
                self->fC5C = 1.0f;
                if (self->f214 == 0x1A)
                {
                    self->fC64 = func_001EAAE0(1.0f, 1.4f);
                    self->fC68 = func_001EAAE0(0.6f, 0.8f);
                    self->fC6C = func_001EAAE0(0.1f, 0.2f);
                }
                else
                {
                    self->fC64 = func_001EAAE0(0.5f, 0.7f);
                    self->fC68 = func_001EAAE0(0.2f, 0.3f);
                    self->fC6C = func_001EAAE0(0.3f, 0.5f);
                }
            }
            s32 idx = (s32)(self->fC5C * 56.999f);
            f32 d = func_001EAAE0(0.1f, 0.2f);
            if (self->f214 == 0x1A)
            {
                d = d + d;
            }
            f32 lo = 0.0f;
            f32 hi = 1.0f;
            f32 v = self->elems[idx].f18 + d;
            if (v < lo)
            {
                v = lo;
            }
            else if (hi < v)
            {
                v = hi;
            }
            self->elems[idx].f18 = v;
            s32 big = 0x1A;
            f32* q;
            Elem_1E77C0* e;
            s32 i;
            for (q = &self->elems[0].f20, e = self->elems, i = 0; i < 57; q += 11, i++, e++)
            {
                if (func_001EAC68(e->f18, e->f1C, 1e-4f) != 0)
                {
                    if (self->f214 == big)
                    {
                        e->f20 = func_001EAAE0(0.6f, 0.8f);
                        e->f24 = func_001EAAE0(0.4f, 0.6f);
                        e->f28 = func_001EAAE0(0.05f, 0.2f);
                    }
                    else
                    {
                        e->f20 = func_001EAAE0(0.3f, 0.4f);
                        e->f24 = func_001EAAE0(0.2f, 0.3f);
                        e->f28 = func_001EAAE0(0.1f, 0.4f);
                    }
                    e->f1C = func_001EAAE0(0.0f, 0.05f);
                }
                else
                {
                    e->f18 = func_001EA4B8(q, 0, e->f18, e->f1C, D_00261858[5]);
                }
            }
        }
        break;
    }
    self->vtbl[16](self, state);
    func_001E7518(self, sub);
}

INCLUDE_ASM(func_001E7C60);

INCLUDE_ASM(func_001E80D8);

INCLUDE_ASM(func_001E83E0);

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

void func_001E7460(void* self);
void func_001E7440(void* self, s32 v);
void func_001E7518(void* self, s32 mode);
void func_001E87F0(void* self, void* a1);

void func_001E86E0(Obj_1E86E0* self, s32 value)
{
    if (value == self->f270) return;
    if (self->f270 == 0) {
        void** vt = (*(Mgr_1E86E0*)&D_002701F8).vtbl;
        ((void (*)(void*, s32))vt[8])(((Mgr_1E86E0*)&D_002701F8), 0);
    }
    self->f270 = value;
    if ((*(Mgr_1E86E0*)&D_002701F8).f260 == 4) {
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

extern u8 D_00275B50[8];
void func_001E8878(s32 enabled, u32 value) { if (value == 0xFFFF && enabled) { D_00275B50[0] = 0x80; D_00275B50[1] = 0x80; D_00275B50[2] = 0x80; D_00275B50[3] = 0x80; } }

s32 func_001E8878(s32 a0, s32 a1);

void func_001E88B0(void)
{
    func_001E8878(1, 0xFFFF);
}

s32 D_00275B28[10] = { 0x00000000, 0x00000356, 0x00000618, 0x00000000, 0x00000357, 0x00000610, 0x00000002, 0x0000035C, 0x0000061C, 0x00000000 };
u8 D_00275B50[8] = { 0 };
f32 D_00275B58[2] = { 500.0f, 2500.0f };
