// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "effect.h"
#include "world.h"
#include "globals.h"

void func_0019EBE8(Effect* self);

void func_001A0020(Effect* self, void* other)
{
    if (other != 0) {
        RemoveEffect(self);
    }
}

void func_0019EB28(Effect* self);

void func_001A1458(Effect* self)
{
    func_0019EB28(self);
    s32 v = g_currentWorld->f1D28;
    self->i120 = -1;
    self->i20 = v;
    self->i128 = -1;
}

void func_0019F560(Effect* self);
s32 func_00182FC8(s32 handle);

void func_001A26B0(Effect* self)
{
    func_0019F560(self);
    s32 h = self->i120;
    if (h != 0) {
        if (IsObjectAttached(h) == 0) {
            RemoveEffect(self);
        }
    }
}

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 n, void* data);
extern s32 D_0026B778[6];

void func_001A3B20(C15* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 2, (void*)D_0026B778);
}

void func_0019EB28(Effect* self);
extern Quad219C D_00275C50;

void func_001A0040(Effect* self)
{
    func_0019EB28(self);
    self->life = 0.25f;
    s32 v = (s32)g_currentWorld->slot1CE8[4];
    self->i20 = v;
    self->q40 = D_00275C50;
    self->f120 = 0.05f;
}

void func_001A0338(void* self, s32 kind, s32 extra);

void func_001A0318(Effect* self)
{
    func_001A0338(self, 0, 0);
}

extern f32 D_0026185C;

void func_0019EBE8(Effect* self);

void func_001A0F88(Effect* self)
{
    if (self->life < g_gameTime - self->start) {
        RemoveEffect(self);
        self->params->fn60(self->p134);
    }
}

void func_001A0FE8(Effect* self)
{
    func_0019EB28(self);
    self->q40 = D_00275C50;
    self->life = 2.0f;
}

s32 func_001A3FE0(C15* self)
{
    s32 r = self->f610;
    switch (r) {
    case 0:
        if (0.0f < self->f61C) {
            r = 1;
        }
        break;
    case 1:
        if (self->f61C == 0.0f) {
            r = 0;
        }
        break;
    case 2:
        if (self->f684 == 0) {
            r = 1;
        }
        break;
    }
    return r;
}

void func_001A0040(Effect* self);

void func_001A1410(Effect* self)
{
    func_001A0040(self);
    World* ctx = g_currentWorld;
    s32 v = ctx->f1D28;
    self->f120 = 0.15f;
    self->i20 = v;
}

void func_001A1498(Effect* self)
{
}

extern f32 D_0026185C;
f32 D_0026B600[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
f32 D_0026B610[4] = { 1.0f, -0.7f, 0.0f, 0.0f };
void func_001A1DF0(Effect* self, s32 n);
void func_0019EBE8(Effect* self);

void func_001A14A0(Effect* c, f32 dt)
{
    f32 t = (g_gameTime - c->start) / c->life;
    f32 k;
    switch (c->i120) {
    case 0: k = D_0026B600[0] + t * (D_0026B600[1] + t * D_0026B600[2]); break;
    case 1: k = D_0026B610[0]; break;
    case 2: k = D_0026B610[0] + t * (D_0026B610[1] + t * D_0026B610[2]); break;
    }
    f32 p = c->f124 + k * dt;
    c->f124 = p;
    if (1.0f <= p) c->f124 = p - 1.0f;
    if (1.0f < t) {
        switch (c->i120) {
        case 0: SetEffectPhase(c, 1); break;
        case 1: SetEffectPhase(c, 2); break;
        case 2: RemoveEffect(c); break;
        }
    }
}

struct Item_1A1F18 { u8 pad0[0x20]; f32 key20; };

s32 func_001A1F18(Item_1A1F18* a, Item_1A1F18* b)
{
    if (a->key20 < b->key20) return -1;
    return 1;
}

struct Src_1A22C8 { u8 pad0[0x1DC]; s32 f1DC; u8 pad1[0x10]; s32 f1F0; };

void func_001A22C8(Effect* self, Src_1A22C8* src)
{
    self->i120 = src->f1DC;
    self->i124 = src->f1F0;
}

struct Obj_1A25F0 { u8 pad0[0x50]; void* f50; };

extern s32 D_0026B6C0[4];

void func_001A2380(Effect* self, s32 v, void* other, void* a2, void* a3, s32 zero);
void func_0019EBE8(Effect* self);
s32 func_001300E8(void* self, s32 kind);

s32 func_001A25F0(Effect* self, Obj_1A25F0* other, void* a2, void* a3)
{
    u32 i;
    for (i = 0; i < 4; i++) {
        if (IsObjectOfKind(other->f50, D_0026B6C0[i]) != 0) {
            return 0;
        }
    }
    if (IsObjectOfKind(other, 0x1F) == 0) {
        func_001A2380(self, self->i120, other, a2, a3, 0);
    }
    RemoveEffect(self);
    return 1;
}

void func_0019F560(Effect* self);
Effect* func_0019EA78(s32 kind, EffectOwner* sys);
extern f32 D_0026185C;

void func_001A0A78(Effect* self, f32 arg)
{
    func_0019F560(self);
    f32 d = g_gameTime - self->start;
    d = d - 0.15f;
    if (0.0f <= d && d < arg) {
        arg = -self->m30[2];
        Effect* n = CreateEffect(12, 0);
        if (n != 0) {
            n->vt->m00(n, &self->q80, arg, 0);
        }
    }
}

s32 func_001300E8(void* self, s32 kind);
s32 func_0019ED58(Effect* a, void* b, void* c, void* d);

struct Obj_1A3128 { u8 pad0[0x50]; void* p50; };

s32 func_001A3128(Effect* a0, Obj_1A3128* a1, void* a2, void* a3)
{
    if (IsObjectOfKind(a1->p50, 6) != 0) {
        return 0;
    }
    return func_0019ED58(a0, a1, a2, a3);
}

void func_0019EB28(Effect* self);

void func_001A0C50(Effect* self)
{
    func_0019EB28(self);
    World* g = g_currentWorld;
    s32 v = (s32)g->slot1CE8[1];
    self->life = 0.5f;
    self->i20 = v;
    self->qC0 = *(Quad219C*)&g->gravity;
}

typedef void (*VFn_1A38F0)(void* self);
struct Obj_1A38F0 { VFn_1A38F0* vtbl; };
extern f32 D_00261858[];

void func_001A35F0(Effect* self);
void func_0019EBE8(Effect* self);

void func_001A38F0(Effect* self)
{
    if (self->start <= g_gameClock[1]) {
        if (self->i134 != 0) {
            func_001A35F0(self);
        }
    }
    f32 span = g_gameClock[1] - self->start;
    if (self->life < span) {
        Obj_1A38F0* o = (Obj_1A38F0*)self->p20;
        o->vtbl[6](o);
        RemoveEffect(self);
    }
}

extern f32 D_0026185C;

void func_0019F858(Effect* self);

void func_001A3990(Effect* self)
{
    if (g_gameTime < self->start) {
        return;
    }
    func_0019F858(self);
}

void func_001A0338(void* self, s32 kind, s32 extra);

void func_001A0950(void* self, s32 kind, s32 extra)
{
    if (kind == 3) {
        goto three;
    }
    if (kind < 4) {
        if (kind == 2) {
            goto zero;
        }
        return;
    }
    if (kind == 10) {
        goto zero;
    }
    if (kind != 16) {
        return;
    }
zero:
    func_001A0338(self, 0, 0);
    return;
three:
    func_001A0338(self, 0, extra + 16);
}


void func_00128018(void* a0, void* a1, void* a2, void* a3);
void func_00128150(void* a0, void* a1, void* a2, void* a3);
s32 func_0019F620(void* self, void* a1, void* a2, void* a3);

void func_001A26F8(Effect* self, void* a1)
{
    u8 scratch[0x40];

    func_00128018(self->p120, 0, &self->q80, scratch);
    func_00128150(self->p120, 0, self->rot50, scratch + 0x10);
    func_0019F620(self, a1, scratch, scratch + 0x10);
}

struct Other_1A2A68 { u8 pad0[0x50]; void* f50; };

s32 func_001300E8(void* node, s32 kind);
void func_001A2380(Effect* self, s32 v, void* other, void* a2, void* a3, void* out);
void func_00128150(void* a0, void* a1, void* a2, void* a3);
void func_0019EBE8(Effect* self);

s32 func_001A2A68(Effect* self, void* a1, void* a2, void* a3)
{
    Other_1A2A68* other = (Other_1A2A68*)a1;
    u8 out[0x10];
    void* p;

    if (IsObjectOfKind(other->f50, 0x40) != 0) {
        return 0;
    }
    if (IsObjectOfKind(other->f50, 6) != 0) {
        return 0;
    }
    func_001A2380(self, self->i20, other, a2, a3, out);
    p = *(void**)out;
    if (p != 0) {
        func_00128150(0, other, (u8*)p + 0x50, (u8*)p + 0x50);
    }
    RemoveEffect(self);
    return 1;
}

struct Self_1A2B18 { u8 pad0[0x7C]; void* f7C; };
struct Other_1A2B18 { u8 pad0[0x538]; u64 f538; };

s32 func_001A2B18(Self_1A2B18* self, Other_1A2B18* other)
{
    u64 flag = 0x8000;

    flag <<= 28;
    if ((other->f538 & flag) != 0) {
        return 0;
    }
    return other != self->f7C;
}

struct Src_1A2D30 { u8 pad0[0x7C]; void* link; u8 pad1[0x1F0 - 0x80]; s32 f1F0; s32 f1F4; };

void func_00128018(void* a0, void* a1, void* a2, void* a3);

void func_001A2D30(Effect* dst, void* a1)
{
    Src_1A2D30* src = (Src_1A2D30*)a1;
    func_00128018(src->link, 0, (u8*)src + 0x20, &dst->q80);
    dst->iB0 = 0;
    dst->i110 = 0;
    dst->i120 = src->f1F4;
    dst->i124 = src->f1F0;
}

extern f32 D_0026B5B0[4];
extern f32 D_0026B5C0[4];

void func_0019EB28(Effect* self);

void func_001A0B20(Effect* self)
{
    func_0019EB28(self);
    World* sys = g_currentWorld;
    self->i20 = (s32)sys->slot1CE8[9];
    self->life = 3.0f;
    self->q40 = *(Quad219C*)D_0026B5B0;
    self->m30[1] = self->m30[0] * 0.25f;
    self->qC0 = *(Quad219C*)D_0026B5C0;
    self->fB0 = -1.0f;
}

s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

struct Other_1A39C8 {
    u8 pad000[0x7C];
    void* p7C;
    u8 pad080[0x1F0 - 0x80];
    s32 i1F0;
    f32 f1F4;
};

void func_001A39C8(Effect* self, void* otherv)
{
    Other_1A39C8* other = (Other_1A39C8*)otherv;
    self->i120 = FindFirstObjectById(g_currentWorld, 0x104, other->i1F0, other->p7C);
    self->f124 = other->f1F4;
}

typedef void (*VFn_1A3B58)(void* self);
extern s32 D_0026B790[18];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void func_001A4070(void* self, s32 n);
void func_001A42C8(void* self, s32 v);

void func_001A3B58(C15* self)
{
    StartPlacedObject(self);
    if (self->f678 != 0) {
        ResolveObjectLinks(self, 6, (void*)D_0026B790);
        SetColliderAnchors(self, 0, 0, 3, 0);
        if (self->f640 != 0) {
            self->f644 = CreateStateWalker(self->f640, self, -1, 0);
        }
        if (self->f650 != 0) {
            self->f654 = CreateStateWalker(self->f650, self, -1, 1);
        }
        self->f668 = GatherObjectsById(g_currentWorld, 1, 0x50, self->f664, 3, self->f66C);
        func_001A4070(self, 2);
        func_001A42C8(self, 0);
    } else {
        ((VFn_1A3B58*)self->desc)[7](self);
    }
}

struct Src_1A3F40 { u8 pad_000[0x48]; f32 f48; u8 pad_04C[0x7C - 0x4C]; f32 f7C; };




void func_00144FF8(void* a, void* b, s32 c, void* d);

void func_001A3F40(C15* out, Src_1A3F40* src)
{
    if (0.3f < src->f48) {
        func_00144FF8(g_camera, src, 0, &out->f618);
    }
    out->f61C = src->f48;
    if (0.8f < src->f7C) {
        func_00144FF8(g_camera, src, 1, &out->f620);
    }
    out->f624 = src->f7C;
}

extern f32 D_0026B710[4];
extern f32 D_0026B720[4];

void func_0019EB28(Effect* self);

void func_001A31F0(Effect* self)
{
    func_0019EB28(self);
    f32 half = 0.5f;
    u8* sys = (u8*)g_currentWorld;
    self->life = half;
    self->i20 = *(s32*)(sys + 0x1D30);
    self->q40 = *(Quad219C*)D_0026B710;
    self->q30 = *(Quad219C*)D_0026B720;
}

void func_0019EB28(Effect* self, f32 x);

void func_001A3598(Effect* self, f32 x)
{
    func_0019EB28(self, x);
    self->q40 = *(Quad219C*)&D_00275C50;
    self->m30[0] = x;
    self->m30[1] = 1.0f - x;
    *(s32*)&self->m30[2] = 0;
}

struct Quad_1A3A18 { s32 a, b, c, d; } __attribute__((aligned(16)));
struct Buf_1A3A18 { s32 n; u8 pad[0x1C]; Quad_1A3A18 q; u8 tail[0x20]; };
typedef void (*Fn_1A3A18)(void* self, void* arg);

void func_0019F560(Effect* self, f32 s);

void func_001A3A18(Effect* self, f32 scale)
{
    func_0019F560(self, scale);
    if (self->p120 == 0) return;
    f32 t = scale * self->f124;
    f32 v = self->f128 + t;
    self->f128 = v;
    if (!(1.0f <= v)) return;
    f32 nv;
    do {
        Buf_1A3A18 buf;
        buf.n = 4;
        buf.q = *(Quad_1A3A18*)&self->q80;
        void* obj = self->p120;
        Fn_1A3A18* vt = *(Fn_1A3A18**)obj;
        vt[31](obj, &buf);
        nv = self->f128 - 1.0f;
        self->f128 = nv;
    } while (1.0f <= nv);
}

typedef int V128_1A0258 __attribute__((mode(TI)));
void func_0019EB28(Effect* self, f32 f);
void func_00118CF0(void* out, f32 f);
void* func_00118D10(void* out, void* in);
V128_1A0258 func_00118D30(V128_1A0258 a, V128_1A0258 b);
void* func_00118D20(void* dst, V128_1A0258 v);
extern f32 D_0026B570[4];
extern f32 D_0026B580[4];

void func_001A0258(Effect* self, f32 f)
{
    func_0019EB28(self, f);
    Quad219C* sub = &self->q30;
    u8* p = (u8*)D_0026B580;
    s32 v = (s32)g_currentWorld->slot1CE8[7];
    self->fB0 = -15.0f;
    self->i20 = v;
    self->q40 = *(Quad219C*)D_0026B570;
    self->life = 0.35f;
    V128_1A0258 t;
    func_00118CF0(&t, f);
    V128_1A0258 tv = t;
    V128_1A0258 u;
    CopyQuadword(&u, p);
    StoreQuadword(sub, func_00118D30(tv, u));
}

extern f32 D_0026B5D0[4];
extern f32 D_0026B5E0[4];

void func_001A0BA0(Effect* self, f32 f)
{
    func_001A0258(self, f);
    Quad219C* sub = &self->q30;
    u8* p = (u8*)D_0026B5E0;
    s32 v = (s32)g_currentWorld->slot1CE8[10];
    self->fB0 = -15.0f;
    self->i20 = v;
    self->q40 = *(Quad219C*)D_0026B5D0;
    V128_1A0258 t;
    func_00118CF0(&t, f);
    V128_1A0258 tv = t;
    V128_1A0258 u;
    CopyQuadword(&u, p);
    StoreQuadword(sub, func_00118D30(tv, u));
}

Effect* func_0019EA78(s32 kind, EffectOwner* sys);
void func_001A0338(void* self, s32 kind, void* extra);
extern f32 D_0026185C;

void func_001A04A0(Effect* self)
{
    Effect* d = CreateEffect(10, 0);
    if (d != 0) {
        d->vt->m00(d, &self->q80, 0.0f, 0);
        d->i20 = self->i20;
        d->fB0 = self->fB0;
        d->q40 = self->q40;
        d->life = self->life;
        Effect* p;
        if (self->i120 == 1) {
            p = self->p124;
            f32* m = p->m30;
            f32 q = (self->start - p->start) / p->life;
            f32 den = p->m30[0] + q * (m[1] + q * m[2]);
            f32 res = self->m30[0] / den;
            q = (g_gameTime - p->start) / p->life;
            res = res * (p->m30[0] + q * (m[1] + q * m[2]));
            d->m30[0] = res;
            d->m30[1] = -res;
        } else {
            d->q30 = self->q30;
            p = self->p128;
        }
        func_001A0338(d, self->i120, p);
        func_001A0338(self, 3, d);
    } else {
        func_001A0338(self, 0, 0);
    }
}

typedef int V128_1A01B8 __attribute__((mode(TI)));

void func_0019EB28(Effect* self, f32 f);
void func_00118CF0(void* out, f32 f);
void* func_00118D10(void* out, void* in);
V128_1A01B8 func_00118D30(V128_1A01B8 a, V128_1A01B8 b);
void* func_00118D20(void* dst, V128_1A01B8 v);
extern f32 D_0026B560[4];

void func_001A01B8(Effect* self, f32 f)
{
    func_0019EB28(self, f);
    self->life = 0.5f;
    s32 v = (s32)g_currentWorld->slot1CE8[5];
    u8* p = (u8*)D_0026B560;
    self->i20 = v;
    V128_1A01B8 t;
    func_00118CF0(&t, f);
    Quad219C* sub = &self->q30;
    V128_1A01B8 tv = t;
    V128_1A01B8 u;
    CopyQuadword(&u, p);
    StoreQuadword(sub, func_00118D30(tv, u));
}

struct Inner_1A3C40;
struct Src_1A3C40;
struct Ptr_1A3C40;
struct Out_1A3C40;
typedef void (*VFn_1A3C40)(Inner_1A3C40* self, void* a);

struct Tri_1A3C40 { s64 a __attribute__((packed)); s32 b; };
struct Inner_1A3C40 {
    VFn_1A3C40* vtbl;   // 0x00
    u8 pad04[0x10C];
    f32 f110;           // 0x110
    f32 f114;           // 0x114
};
struct Frame_1A3C40 {
    f32 buf[4];         // 0x00
    u8 pad10[0x20];
    Tri_1A3C40 tri;     // 0x30
    u8 pad3c[0x04];
};

extern const f32 D_0024C9C0[4];
extern f32 D_00261860;

void func_0012E760(Ptr_1A3C40* obj);
void func_001A3F40(C15* self, Src_1A3C40* src);
void func_001ED650(Out_1A3C40* out, f32 unused, f32 scale, f32 z);
f32 func_00205778(f32 a, f32 b);
f32 func_001EA728(u8* p, s32 a, f32 b, f32 c, f32 d);
void func_001892A0(f32* out, f32 unused, f32 value);
void func_00128150(void* a0, C15* a1, void* a2, void* a3);

void func_001A3C40(C15* self, Src_1A3C40* src)
{
    Frame_1A3C40 f;
    if (self->f688 != 0) {
        StopAnimationPlayer(((Ptr_1A3C40*)self->f684));
        self->f684 = 0;
        self->f688 = 0;
    }
    func_001A3F40(self, src);
    ComputePolarOffset((Out_1A3C40*)((u8*)self + 0x630), self->f618, self->f61C * self->f628, 0.0f);
    f.tri = *(Tri_1A3C40*)D_0024C9C0;
    f32 r = func_00205778(((Inner_1A3C40*)self->f64C)->f114, ((Inner_1A3C40*)self->f64C)->f110);
    r = ApproachAngleWithRamp((u8*)&f.tri, 0, r, self->f620, g_frameDt);
    func_001892A0(f.buf, r, 0.0f);
    func_00128150(0, self, f.buf, f.buf);
    ((Inner_1A3C40*)self->f64C)->vtbl[34](((Inner_1A3C40*)self->f64C), f.buf);
}


extern f32 D_00261858[];
extern const f32 D_0024C9B8 = 3.4028235e+38f;
extern f32 D_0026B6A0[4];
extern f32 D_0026B6B0[4];

void func_001A1DF0(Effect* self, s32 mode)
{
    f32 t;
    f32 x;

    if (mode == self->i120) {
        return;
    }
    f32 one = 1.0f;
    x = (g_gameClock[1] - self->start) / self->life;
    if (x < 0.0f) {
        t = 0.0f;
    } else if (one < x) {
        t = one;
    } else {
        t = x;
    }
    switch (mode) {
    case 0:
        self->q40 = *(Quad219C*)D_0026B6A0;
        self->life = 0.25f;
        break;
    case 1:
        self->q40 = *(Quad219C*)((u8*)&D_00275C50);
        self->life = D_0024C9B8;
        break;
    case 2:
        self->q40 = *(Quad219C*)D_0026B6B0;
        self->life = 0.5f;
        break;
    }
    if ((mode == 0 || mode == 2) && (self->i120 == 0 || self->i120 == 2)) {
        t = 1.0f - t;
    } else {
        t = 0.0f;
    }
    self->start = g_gameClock[1] - t * self->life;
    self->i120 = mode;
}

f32 D_0026B560[4] = { 0.5f, 2.0f, -2.0f, 0.0f };
f32 D_0026B570[4] = { 0.5f, -0.5f, 0.0f, 0.0f };
f32 D_0026B580[4] = { 1.0f, -1.0f, 0.0f, 0.0f };
f32 D_0026B5B0[4] = { 0.699999988079071f, 0.0f, -0.699999988079071f, 0.0f };
f32 D_0026B5C0[4] = { 0.0f, 0.0f, 50.0f, 0.0f };
f32 D_0026B6A0[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_0026B6B0[4] = { 1.0f, -1.0f, 0.0f, 0.0f };
f32 D_0026B710[4] = { 0.0f, 4.0f, -4.0f, 0.0f };
f32 D_0026B720[4] = { 0.25f, 3.0f, -3.0f, 0.0f };
s32 D_0026B6C0[4] = { 0x40, 5, 0x42, 0x43 };
s32 D_0026B778[6] = { 2, 0x28E, 0x640, 2, 0x292, 0x650 };
s32 D_0026B790[18] = { 4, 0x291, 0x64C, 4, 0x299, 0x664, 4, 0x297, 0x65C, 4, 0x298, 0x660, 2, 0x29A, 0x680, 2, 0x29B, 0x67C };
extern const f32 D_0024C9C0[4] = { 30.0f, 0.0f, 0.2f, 0.0f };

void func_001921A8(void* self);

void func_001A3AE0(C15* self)
{
    C15* o = self;
    InitSwitchedCollider(self);
    o->f610 = -1;
    o->f628 = 2000.0f;
    o->f614 = -1;
}

typedef int V128_1A09C0 __attribute__((mode(TI)));
void func_0019EB28(Effect* self, f32 f);
void func_00118CF0(void* out, f32 f);
void* func_00118D10(void* out, void* in);
V128_1A09C0 func_00118D30(V128_1A09C0 a, V128_1A09C0 b);
void* func_00118D20(Quad219C* dst, V128_1A09C0 v);
extern f32 D_0026B590[4];
extern f32 D_0026B5A0[4];

void func_001A09C0(Effect* self, f32 f)
{
    func_0019EB28(self, f);
    Quad219C* sub = &self->q30;
    u8* p = (u8*)D_0026B590;
    s32 v = (s32)g_currentWorld->slot1CE8[8];
    self->life = 0.25f;
    self->i20 = v;
    V128_1A09C0 t;
    func_00118CF0(&t, f);
    V128_1A09C0 tv = t;
    V128_1A09C0 u;
    CopyQuadword(&u, p);
    (void)StoreQuadword(sub, func_00118D30(tv, u));
    u8* q = (u8*)D_0026B5A0;
    self->q40 = *(Quad219C*)q;
}
