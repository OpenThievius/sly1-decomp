// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c05.h"
#include "asm_func.h"
#include "fpu.h"
#include "list_iter.h"
#include "t217d.h"
extern u8* D_00262E10;
extern u8* D_00275710;

void func_001921A8(void* self);
void* func_0018D500(s32 size);

void func_001E5378(C16* self)
{
    func_001921A8(self);
    self->f644 = 1;
    self->f63C = func_0018D500(0x40);
    self->f640 = func_0018D500(0x40);
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

struct Peer_1E5428 {
    u8 pad0[0xC2C];
    C16* owner;
};

extern s32 D_00275B28[10];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void* func_001B6290(void* a, void* self, s32 b, s32 c);
void* func_0015A448(void* a, s32 b, void* c);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_00189230(void* a, void* b, void* c);

void func_001E5428(C16* self)
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
        self->f584 = (void*)func_0015A418(self->world, 1, 0x160, r);
        i = 0;
        do {
            self->f588[i] = (void*)func_0015A418(self->world, 1, i + 0x161, r);
            i++;
        } while (i < 3);
        self->f594 = 300.0f;
        ((Vt_1E5428*)r)->vtbl[27](r, self);
    } else {
        self->f620 = (void*)D_00262E10;
    }

    n = 0;
    while (n < self->f638) {
        r2 = func_0015A448(self->world, ((s32*)self->f640)[n], self);
        if (r2 != 0) {
            ((void**)self->f63C)[n] = r2;
            n++;
        }
    }
    self->f638 = n;
    func_00189230((u8*)self + 0x110, (u8*)self + 0x648, (u8*)self + 0x64C);
}

typedef s32 (*VFn_1E55D0)(void* self);
struct Obj_1E55D0 { VFn_1E55D0* vtbl; };
struct Item_1E55D0 { u8 pad0[0x724]; s32 f724; };
void func_00192B58(void* self);
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void func_001C8F20(void* node, s32 kind, s32 flag);

void func_001E55D0(C16* self)
{
    void* arr[8];
    s32 n;
    s32 count;
    s32 i;

    func_00192B58(self);
    if (((Obj_1E55D0*)self->f620) != 0) {
        if (((Obj_1E55D0*)self->f620)->vtbl[81](((Obj_1E55D0*)self->f620))) {
            n = func_0015A4F0(self->world, 5, 8, 0, 8, arr);
            if (n > 0) {
                count = n;
                i = 0;
                do {
                    void* item = arr[i];
                    if (item != ((Obj_1E55D0*)self->f620)) {
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

void func_001E56A0(C16* self, void* obj, f32 t)
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

extern Ctx_1E5750* D_00261990;
extern u8 D_00275BC0[];

void func_001922E8(void* a, void* b);
void func_001E9498(void* self, void* node);
void func_001E9570(void* self);
void func_001356C0(T217D_440* self, s32 mode);
void func_00145088(void* a, s32 b, void* c, void* d, s32 e);
void func_001495E8(void* a, s32 b);
void func_001451F0(void* a, s32 b, s32 c, void* d, void* e, s32 f);
void func_00149610(void* a);
void func_001B64D8(void* a, s32 b);

void func_001E5750(C16* self, u8* p)
{
    func_001922E8(self, p);
    if (p != 0) {
        D_00261990->f480 = 100.0f;
        func_001E9498(D_00275BC0, &D_002701F8);
        func_001356C0(&D_002701F8, 5);
        D_00261990->f4BC = self->f61C;
        if (self->f630 != 0) {
            D_00261990->q80 = *(Quad_1E5750*)&self->m110.r[0];
            D_00261990->q90 = *(Quad_1E5750*)&self->m110.r[1];
            D_00261990->qA0 = *(Quad_1E5750*)&self->m110.r[2];
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

ASM_FUNC(func_001E5938);

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
struct Rec_1E5CE8 { s32 w0; s32 w4; s32 w8; };

void func_00192230(void* self, s32 kind, Rec_1E5CE8* rec);
void func_001A8C90(void* a, s32 b);

void func_001E5CE8(C16* self, s32 kind, Rec_1E5CE8* rec)
{
    func_00192230(self, kind, rec);
    if (kind == 0x13) {
        Dev_1E5CE8* dev = (Dev_1E5CE8*)self->f614;
        s32 id = rec->w0;
        if (id == dev->f24) {
            if (rec->w8 == 0x35B) {
                func_001A8C90(self->f618, 1);
            }
        } else if (((Hdl_1E5CE8*)self->f624) != 0 && id == ((Hdl_1E5CE8*)self->f624)->f7E0) {
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

s32 func_001B8A08(void* a, void* b);
s32 func_001A8820(void* p, void* v);

s32 func_001E5DA8(C16* self, void* arg)
{
    if (func_001B8A08(self, arg)) {
        return 1;
    }
    if (self->f618 != 0) {
        s32 r = func_001A8820(self->f618, arg);
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

typedef void (*VFn_5E08)(void* self);

void func_001924C8(void* self);

void func_001E5E08(C16* self)
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

void func_001E5E50(C16* a0, void* a1, Pair_1E5E50* out)
{
    out->lo = 0;
    out->hi = 0;
}

void* func_001E5E60(C16* self) { return self->f620 ? self->f620 : self; }

// A view of the vertices that starts one vertex before the first (0x254): through it, the fields
// of the vertex i are at 0x2C more (x at 0x2C, y at 0x34, the colours at 0x3C and 0x40, the
// brightness at 0x44 and 0x48, the rates from 0x4C), and the previous vertex's next place is at
// 0x04 and 0x0C.
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

void func_001AA1F0(T217D* self, s32 kind);
f32 func_001EAAE0(f32 a, f32 b);

void func_001E5E70(T217D_3F0* self, s32 kind)
{
    self->w = 160.0f;
    self->h = 125.4f;
    self->lineLen = self->lineLen2 = 3.3000002f;
    func_001AA1F0(self, kind);
    f32 sign;
    if (kind == 0x1A) {
        self->edgeTo = 0.0f;
        self->edgeFrom = self->w - 62.7f;
        sign = 1.0f;
    } else {
        self->edgeTo = self->w;
        self->edgeFrom = 62.7f;
        sign = -1.0f;
    }
    f32 step = 1.0f / 57.0f;
    s32 i = 0;
    u32 dim = 0x30000000;
    s32 special = 0x1A;
    Elem_1E5E70* p;
    for (p = (Elem_1E5E70*)(self->pts - 1); i < 0x39; i++) {
        f32 t = (f32)i * step;
        f32 y = t + t - 1.0f;
        p->f34 = y;
        p->f2C = sign * Fpu::Sqrt(1.0f - y * y);
        p->f3C = p->f40 = (i & 1) ? dim : 0x30808080;
        p->f44 = p->f48 = 0.0f;
        if (self->index == special) {
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
    self->pts[56].nextY = 1.0f;
    self->pts[56].nextX = 0.0f;
    if (self->index == 0x1A) {
        self->pulseA = func_001EAAE0(1.0f, 1.4f);
        self->pulseB = func_001EAAE0(0.6f, 0.8f);
        self->pulseC = func_001EAAE0(0.1f, 0.2f);
    } else {
        self->pulseA = func_001EAAE0(0.5f, 0.7f);
        self->pulseB = func_001EAAE0(0.2f, 0.3f);
        self->pulseC = func_001EAAE0(0.3f, 0.5f);
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

void func_001AA268(T217D* self);
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

void func_001E6188(T217D_3F0* self)
{
    func_001AA268(self);
    self->sprite = func_0011E580(0x51, D_00275710, 0, 0x201, -1);
    func_00184768(self->sprite, 1);
    func_001847F0(self->sprite, D_00275640);
    func_00184858(self->sprite, D_00275650);
    func_00184818(self->sprite, D_00275654);
    func_00184878(self->sprite, D_00275658);
    func_00184838(self->sprite, D_0027565C);
    func_00184898(self->sprite, D_00275660);
    func_00184990(self->sprite, D_00275B58);
    func_00184968(self->sprite, 1);
    ((Inst_1E6188*)self->sprite)->vtbl[7](self->sprite);
}

void func_001E6268(T217D_3F0* self, s32* first, s32* second) { s32 n = (s32)(self->size * 57.0f); s32 half = (57 - n) / 2; *first = half; *second = half + n; }

struct Ctx_1E62A8 { s32 x; };
extern s32 D_00270458;
void func_00161670(Ctx_1E62A8* c, s32 a, s32 b, s32 d, s32 e);
void func_001615F0(Ctx_1E62A8* c, s32 a, s32 b, s32 d, s32 e);

void func_001E62A8(T217D_3F0* self, Ctx_1E62A8* c, s32 k)
{
    if (D_00270458 == 4) {
        f32 y = self->shownY;
        f32 x = self->shownX;
        s32 x0 = (s32)((x + 1728.0f) * 16.0f);
        s32 y0 = (s32)((y * 0.45454547f + 1936.0f) * 16.0f);
        func_00161670(c, x0, y0, k, 0);
        func_00161670(c, x0, (s32)(((y + self->h) * 0.45454547f + 1936.0f) * 16.0f), k, 0);
        func_001615F0(c, (s32)(((x + self->w) + 1728.0f) * 16.0f), y0, k, 0);
        y = y + self->h;
        x = x + self->w;
        func_001615F0(c, (s32)((x + 1728.0f) * 16.0f), (s32)((y * 0.45454547f + 1936.0f) * 16.0f), k, 0);
    } else {
        s32 r[2];
        func_001E6268(self, &r[0], &r[1]);
        if (r[0] != r[1]) {
            f32 a = self->y + 62.7f;
            f32 b = self->x + self->edgeTo;
            f32 bx = self->x + self->edgeFrom;
            s32 x0, y0, i;
            f32 t;
            y0 = (s32)(((a + self->pts[r[0]].y * 62.7f) * 0.45454547f + 1936.0f) * 16.0f);
            x0 = (s32)((b + 1728.0f) * 16.0f);
            t = bx + self->pts[r[0]].x * 62.7f;
            func_00161670(c, x0, y0, k, 0);
            func_00161670(c, (s32)((t + 1728.0f) * 16.0f), y0, k, 0);
            for (i = r[0]; i < r[1]; i++) {
                T217D_3F0_Pt* p = &self->pts[i];
                t = bx + p->nextX * 62.7f;
                s32 x = (s32)((b + 1728.0f) * 16.0f);
                y0 = (s32)(((a + p->nextY * 62.7f) * 0.45454547f + 1936.0f) * 16.0f);
                func_001615F0(c, x, y0, k, 0);
                func_001615F0(c, (s32)((t + 1728.0f) * 16.0f), y0, k, 0);
            }
        }
    }
}

ASM_FUNC(func_001E6600);

struct Rgba_1E6C20 { u8 c[4]; };
struct Buf_1E6C20;

extern f32 D_00261868;
extern Rgba_1E6C20 D_002610D8;
extern Rgba_1E6C20 D_002610E0;

void func_001613C0(Buf_1E6C20* b, s32 a1, s32 a2, s32 a3);
void func_00161458(Buf_1E6C20* b, u32 c);
void func_001615F0(Buf_1E6C20* b, s32 x, s32 y, s32 a3, s32 a4);

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

void func_001E6C20(T217D_3F0* self, Buf_1E6C20* buf)
{
    Rgba_1E6C20 c;
    f32 t;
    switch (self->fade) {
    case 0:
        t = Clamp_1E6C20::Of((D_00261868 - self->fadeSince) * 5.0f, 0.0f, 1.0f);
        break;
    case 1:
        t = Clamp_1E6C20::Of(1.0f - (D_00261868 - self->fadeSince) * 5.0f, 0.0f, 1.0f);
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
    f32 x0 = self->x + self->edgeFrom;
    f32 y0 = self->y + 62.7f;
    f32 xe = self->x + self->edgeTo;
    s32 first, last;
    func_001E6268(self, &first, &last);
    T217D_3F0_Pt* e = &self->pts[first];
    f32 len = self->lineLen;
    f32 xa = x0 + e->x * 62.7f;
    f32 xb = x0 + (len + 62.7f) * e->x;
    f32 ya = y0 + e->y * 62.7f;
    f32 yb = ya - len;
    func_001615F0(buf, SX_1E6C20(xe), SY_1E6C20(ya), 0, 0);
    func_001615F0(buf, SX_1E6C20(xe), SY_1E6C20(yb), 0, 0);
    func_001615F0(buf, SX_1E6C20(xa), SY_1E6C20(ya), 0, 0);
    func_001615F0(buf, SX_1E6C20(xb), SY_1E6C20(yb), 0, 0);
    for (s32 i = first; i < last; i++) {
        e = &self->pts[i];
        xa = x0 + e->x * 62.7f;
        ya = y0 + e->y * 62.7f;
        xb = x0 + (self->lineLen + 62.7f) * e->x;
        yb = y0 + (self->lineLen + 62.7f) * e->y;
        func_001615F0(buf, SX_1E6C20(xa), SY_1E6C20(ya), 0, 0);
        func_001615F0(buf, SX_1E6C20(xb), SY_1E6C20(yb), 0, 0);
    }
    xa = x0 + e->nextX * 62.7f;
    ya = y0 + e->nextY * 62.7f;
    yb = ya + self->lineLen;
    xb = x0 + (self->lineLen + 62.7f) * e->nextX;
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

void func_001E73B8(T217D_3F0* self)
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

extern f32 D_00261868;

void func_001E7440(T217D_3F0* a0, s32 a1)
{
    if (a1 != a0->fade) {
        a0->fade = a1;
        a0->fadeSince = D_00261868;
    }
}

struct Node_1E7460;
struct Obj_1E7460;
void func_00126BC0(Node_1E7460* node, T217D_3F0* self);
extern s32 D_00270458;

struct Node_1E7460 {
    void** vtable;
    u8 pad4[0x2C8 - 4];
    unsigned long f2C8;
};
void func_001E7460(T217D_3F0* self)
{
    Node_1E7460* cur = (Node_1E7460*)self->current;
    if ((Node_1E7460*)self->target == cur) {
        return;
    }
    if (cur != 0) {
        if (!(D_00270458 == 4 && cur == (Node_1E7460*)self->special)) {
            ((void (*)(Node_1E7460*))cur->vtable[7])(cur);
        }
    }
    self->current = self->target;
    if (self->current != 0) {
        ((void (*)(Node_1E7460*))((Node_1E7460*)self->current)->vtable[6])((Node_1E7460*)self->current);
        if (D_00270458 != 4) {
            func_00126BC0((Node_1E7460*)self->current, self);
        }
        ((Node_1E7460*)self->current)->f2C8 |= 0x100000000UL;
    }
}

extern f32 D_00261858[];
f32 func_001EAAE0(f32 a, f32 b);
void func_001BFCD8(s32 id, s32 a, s32 b, s32 c, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, s32 d, s32 e);

void func_001E7518(T217D_3F0* self, s32 mode)
{
    if (mode == self->phase) {
        return;
    }
    switch (mode) {
    case 0: {
        func_001BFCD8(0x8C, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        for (s32 i = 0; i < 57; i++) {
            T217D_3F0_Pt* e = &self->pts[i];
            e->level = 1.0f;
            e->target = func_001EAAE0(0.0f, 0.05f);
            e->rateA = 1.0f;
            e->rateB = 0.6f;
            e->rateC = 0.2f;
        }
        break;
    }
    case 2:
        func_001BFCD8(0x8D, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    case 1:
        self->size = 1.0f;
        break;
    case 3:
        self->size = 0.0f;
        func_001E7460(self);
        break;
    }
    self->phase = mode;
    self->phaseSince = D_00261858[4];
}

extern s32 D_00270458;
void func_001AAB20(T217D* self, f32 x, f32 y);

void func_001E76E0(T217D_3F0* self, s32 value)
{
    s32 old = self->mode;
    func_001AA998(self, value);
    if (old == value) return;
    if (old != 0) goto done;
    if (D_00270458 == 4) {
        self->place->dy = 0.0f;
        func_001AAB20(self, 640.0f, 360.0f);
    } else {
        self->place->dy = -20.0f;
        func_001AAB20(self, 160.0f, 125.4f);
    }
done:
    if (value != 2) return;
    if (D_00270458 == 4) return;
    self->phase = -1;
    func_001E7518(self, 3);
}

extern f32 D_00261858[];
extern s32 D_00270448;
extern s32 D_00270458;

void func_001AA298(T217D* self);
f32 func_001EA4B8(f32* p, s32 zero, f32 a, f32 b, f32 c);
s32 func_001EAC68(f32 a, f32 b, f32 c);
f32 func_001EAAE0(f32 a, f32 b);

void func_001E77C0(T217D_3F0* self)
{
    func_001AA298(self);
    s32 state = self->mode;
    s32 sub = self->phase;
    switch (state)
    {
    case 0:
        if (self->current != 0)
        {
            state = 2;
        }
        else if (self->target != 0)
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
            f32 f = self->size + D_00261858[5] * 5.0f;
            self->size = f;
            if (1.0f <= f)
            {
                self->size = 1.0f;
                sub = 1;
            }
            break;
        }
        case 2:
        {
            f32 f = self->size - D_00261858[5] * 5.0f;
            self->size = f;
            if (f <= 0.0f)
            {
                self->size = 0.0f;
                sub = 3;
            }
            break;
        }
        case 3:
            if (self->target != 0)
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
            self->pulse = func_001EA4B8(&self->pulseA, 0, self->pulse, self->pulseTarget, D_00261858[5]);
            if (func_001EAC68(self->pulse, self->pulseTarget, 1e-4f) != 0)
            {
                self->pulse = 1.0f;
                if (self->index == 0x1A)
                {
                    self->pulseA = func_001EAAE0(1.0f, 1.4f);
                    self->pulseB = func_001EAAE0(0.6f, 0.8f);
                    self->pulseC = func_001EAAE0(0.1f, 0.2f);
                }
                else
                {
                    self->pulseA = func_001EAAE0(0.5f, 0.7f);
                    self->pulseB = func_001EAAE0(0.2f, 0.3f);
                    self->pulseC = func_001EAAE0(0.3f, 0.5f);
                }
            }
            s32 idx = (s32)(self->pulse * 56.999f);
            f32 d = func_001EAAE0(0.1f, 0.2f);
            if (self->index == 0x1A)
            {
                d = d + d;
            }
            f32 lo = 0.0f;
            f32 hi = 1.0f;
            f32 v = self->pts[idx].level + d;
            if (v < lo)
            {
                v = lo;
            }
            else if (hi < v)
            {
                v = hi;
            }
            self->pts[idx].level = v;
            s32 big = 0x1A;
            f32* q;
            T217D_3F0_Pt* e;
            s32 i;
            for (q = &self->pts[0].rateA, e = self->pts, i = 0; i < 57; q += 11, i++, e++)
            {
                if (func_001EAC68(e->level, e->target, 1e-4f) != 0)
                {
                    if (self->index == big)
                    {
                        e->rateA = func_001EAAE0(0.6f, 0.8f);
                        e->rateB = func_001EAAE0(0.4f, 0.6f);
                        e->rateC = func_001EAAE0(0.05f, 0.2f);
                    }
                    else
                    {
                        e->rateA = func_001EAAE0(0.3f, 0.4f);
                        e->rateB = func_001EAAE0(0.2f, 0.3f);
                        e->rateC = func_001EAAE0(0.1f, 0.4f);
                    }
                    e->target = func_001EAAE0(0.0f, 0.05f);
                }
                else
                {
                    e->level = func_001EA4B8(q, 0, e->level, e->target, D_00261858[5]);
                }
            }
        }
        break;
    }
    self->vt->m16(self, state);
    func_001E7518(self, sub);
}

ASM_FUNC(func_001E7C60);

ASM_FUNC(func_001E80D8);

ASM_FUNC(func_001E83E0);

void func_001E87F0(T217D_3F0* self, void* a1);

void func_001E86E0(T217D_3F0* self, void* value)
{
    if (value == self->target) return;
    if (self->target == 0) {
        D_002701F8.vt->m08(&D_002701F8, 0);
    }
    self->target = value;
    if (D_002701F8.state == 4) {
        func_001E7460(self);
        if (self->target != 0) {
            self->vt->m16(self, 2);
            func_001E7518(self, 1);
            func_001E7440(self, 0);
        } else {
            self->vt->m16(self, 0);
            func_001E7518(self, 3);
            func_001E7440(self, 0);
            func_001E87F0(self, 0);
        }
    } else {
        s32 st = self->phase;
        if (st >= 2) return;
        if (st < 0) return;
        func_001E7518(self, 2);
    }
}

struct Obj_1E87F0 {
    u8 pad0[0x2C8];
    u64 f2C8;
};

void func_001E87F0(T217D_3F0* self, void* a1)
{
    Obj_1E87F0* old = (Obj_1E87F0*)self->special;
    if (old != 0) {
        old->f2C8 &= ~(1ULL << 32);
    }
    self->special = a1;
    if (a1 != 0) {
        ((Obj_1E87F0*)a1)->f2C8 |= (1ULL << 32);
    }
}

void func_001E8840(T217D_3F0* self)
{
    func_001AA8C8(self);
    self->size = 0;
    self->current = 0;
    self->target = 0;
    self->phase = 3;
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
