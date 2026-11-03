// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern s32 D_00262474;
extern u8 D_002622A8[];

void func_001EE3B8(void* obj, s32 size, s32 flags);

void func_00166658(void)
{
    s32 v = 0x23C - D_00262474;
    D_00262474 = v;
    func_001EE3B8(D_002622A8, v, 0);
}

void func_001CA5E0(void);

void func_00167EF0(void)
{
    func_001CA5E0();
}

extern u32 D_002623E0;
void func_00167D20(void* p, s32 value) { if ((u32)value == 0xFFFFu && p != 0) D_002623E0 = 0x80101010; }

void func_0016C528(void*);
void func_001660A0(u8* self)
{
    u8* p=*(u8**)(self+0x224);
    if (p && (*(s32*)(p+0xB0)&16) && *(s32*)(p+0x64)) func_0016C528(*(void**)(p+0x60));
}

void func_00167D48() { func_00167D20((void*)1, 65535); }

typedef void (*VFn_165728)(void* self);
struct Obj_165728 { VFn_165728* vtbl; };
struct Entry_165728 { u8 pad0[0x38]; Obj_165728* f38; u8 pad1[0x70 - 0x3C]; };
struct Node_165728 { u8 pad0[4]; void* f4; s32 f8; u8 pad1[0x80 - 0xC]; Node_165728* next80; };
struct Self_165728 { u8 pad0[0xC]; s32 count0C; Entry_165728* f10; u8* f14; u8 pad1[0x4C - 0x18]; Node_165728* f4C; };
struct Ctx_165728 { u8 pad0[0x14]; void* host14; };

void* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_001662A8(void* self, void* entry, void* sub, void* ctx);
void func_001F2798(void* owner, void* unused, void* ctx);

void func_00165728(Self_165728* self, Ctx_165728* ctx)
{
    for (s32 i = 0; i < self->count0C; i++)
    {
        Entry_165728* e = self->f10 + i;
        Obj_165728* o = e->f38;
        if (o != 0)
        {
            o->vtbl[1](o);
        }
        func_001662A8(self, e, self->f14 + i * 0x28, ctx);
    }
    Node_165728* n = self->f4C;
    if (n != 0)
    {
        do
        {
            void* v = func_0015A418(ctx->host14, 0x104, n->f8, ctx);
            if (v != 0)
            {
                func_001F2798(v, ctx, n->f4);
            }
            n = n->next80;
        } while (n != 0);
    }
}

struct __attribute__((aligned(16))) Quad_165828 { s32 a, b, c, d; };
struct Mat_165828 { Quad_165828 q[4]; };
struct Node_165828 { u8 pad0[0x110]; u8 sub110[0x30]; u8 sub140[0x40]; };
struct Elem_165828 { Node_165828* p0; u8 pad0[0xC]; Mat_165828 m; u8 tail[0x90 - 0x50]; };
struct Obj_165828 { s32 count; Elem_165828* elems; s32* keys; };
struct Ctx_165828 { u8 pad0[0x14]; void* p14; u8 pad1[0x110 - 0x18]; u8 sub110[0x30]; u8 sub140[0x40]; };
struct Frame_165828 { Quad_165828 a; u8 pad0[0x30]; Quad_165828 b; u8 pad1[0x30]; Mat_165828 m; };

void* func_0015A448(void* a, s32 b, void* c);
void func_00188B08(void* a, void* b, void* out);
void func_00188B48(void* a, void* b, void* out);
void func_00188668(void* out, void* b, void* in);

void func_00165828(Obj_165828* self, Ctx_165828* ctx)
{
    Frame_165828 f;
    s32 i;

    for (i = 0; i < self->count; i++) {
        Elem_165828* e = &self->elems[i];
        Node_165828* r = (Node_165828*)func_0015A448(ctx->p14, self->keys[i], ctx);
        e->p0 = r;
        if (r != 0) {
            func_00188B08(&ctx->sub140, &ctx->sub110, &f.a);
            func_00188B48(&e->p0->sub140, &e->p0->sub110, &f.b);
            func_00188668(&f.m, &f.b, &f.a);
            e->m = f.m;
        }
    }
}

struct Ctx_167E08 { u8 pad0[0x14]; void* p14; u8 pad1[0x750 - 0x18]; void* p750; u8 pad2[0xC18 - 0x754]; s32 c18; s32 c1c; u8 pad3[0xC30 - 0xC20]; s32 c30; s32 c34; };
struct Ent_167E08 { u8 pad0[0x328]; s32 f328; };
struct Out_167E08 { s32 count; Ent_167E08** items; };

void func_001C72A0(void* self);
void* func_0015A448(void* a, s32 b, void* c);
void func_0018D608(void);
void func_0018D6F0(void);
void func_0012D1B0(void* a, void* b, s32* c, void** d);
void* func_001EFA30(void);
void func_001EFA60(void* a, void* b);

void func_00167E08(Ctx_167E08* self)
{
    Out_167E08 out;
    s32 i;

    func_001C72A0(self);
    if (self->c18 != -1) {
        self->c1c = (s32)func_0015A448(self->p14, self->c18, self);
    }
    if (self->c30 != -1) {
        self->c34 = (s32)func_0015A448(self->p14, self->c30, self);
    }
    if (self->p750 != 0) {
        func_0018D608();
        func_0012D1B0(self->p750, self, &out.count, (void**)&out.items);
        for (i = 0; i < out.count; i++) {
            Ent_167E08* e = out.items[i];
            if (e->f328 == 0) {
                void* t = func_001EFA30();
                e->f328 = (s32)t;
                func_001EFA60(t, e);
            }
        }
        func_0018D6F0();
    }
}

struct Elem_165FE0;
typedef void (*VFn_165FE0)(void* self, f32 f);

struct Elem_165FE0 {
    VFn_165FE0* vtbl;
    u8 pad4[0x8];
    void* f0C;
    u8 pad10[0x70];
    Elem_165FE0* next80;
};

struct Owner_165FE0 {
    u8 pad0[0x4C];
    Elem_165FE0* head4C;
};

struct Sub_165FE0 {
    u8 pad0[0x27C];
    s32 count27C;
    Elem_165FE0** list280;
};

s32 func_001B4B08(void* p);
void func_001F3408(void* p);

void func_00165FE0(Owner_165FE0* self, Sub_165FE0* sub, f32 f)
{
    Elem_165FE0* e;
    s32 i;

    for (i = 0; i < sub->count27C; i++) {
        e = sub->list280[i];
        if (func_001B4B08(e) != 0) {
            VFn_165FE0 fn = e->vtbl[2];
            if (fn != 0) {
                fn(e, f);
            }
        }
    }
    for (e = self->head4C; e != 0; e = e->next80) {
        func_001F3408(e->f0C);
    }
}

extern u8 D_00000010[];
extern u8 D_000000F0[];

struct Ctx_165588 { u8 pad0[0x28]; s32 f28; };
struct Range_165588 { u16 lo; u16 hi; };
struct Rec_165588 { u8 pad0[0x18]; u8* f18; Range_165588* f1C; };
struct Out_165588 { void* f0; void* f4; void* f8; void* fC; void* f10; void* f14; };

void func_001EE318(void* p);
void func_00152938(void* buf, u32 count, u32 kind);
void func_001EE498(void* b, u32 x, u32 y);
void func_001EE5C8(void* s, u32 tag, s32 size, s32 a3, void* a4, void* a5);
void func_001EE3F0(void* s, void* n);
void func_001529E0(void* self, void* a, void* b);

void func_00165588(Ctx_165588* a, Rec_165588* b, Out_165588* c)
{
    u8 buf[0x30];
    s32 s0;

    if (*b->f18 != 0) return;
    if (a->f28 != 0) return;
    func_001EE318(buf);
    s0 = (b->f1C->hi - b->f1C->lo) / 4;
    func_00152938(buf, (u32)((s0 + 7) / 4), 0x1A);
    func_001EE498(buf, 1, 4);
    func_001EE5C8(buf, 0xE, s0, b->f1C->lo + 1, 0, &c->f8);
    func_001EE498(buf, 1, 1);
    func_001EE3F0(buf, D_00000010);
    func_001529E0(buf, &c->f0, &c->f4);
    func_00152938(buf, (u32)((s0 + 4) / 2), 0x1A);
    func_001EE498(buf, 1, 4);
    func_001EE5C8(buf, 0xE, s0, b->f1C->lo + 2, 0, &c->f14);
    func_001EE498(buf, 1, 1);
    func_001EE5C8(buf, 0xE, s0, b->f1C->hi, 0, 0);
    func_001EE3F0(buf, D_000000F0);
    func_001529E0(buf, &c->fC, &c->f10);
}

struct Cfg_167D68 {
    u8 pad_000[0x738];
    s32 f738;
    f32 f73C;
    u8 pad_740[0x0C];
    f32 f74C;
    u8 pad_750[0x4C0];
    f32 fC10;
    f32 fC14;
    s32 fC18;
    u8 padC1C[0x4];
    f32 fC20;
    f32 fC24;
    f32 fC28;
    f32 fC2C;
    s32 fC30;
};

void func_001C6F48(void* self);
void func_00167D68(Cfg_167D68* self);

void func_00167D68(Cfg_167D68* self)
{
    func_001C6F48(self);
    self->fC20 = 1000.0f;
    self->fC24 = 1500.0f;
    self->fC28 = 0.78539816f;
    self->fC2C = 3.14159265f;
    self->fC10 = 2000.0f;
    self->fC30 = -1;
    self->fC14 = 300.0f;
    self->fC18 = -1;
    self->f73C = 300.0f;
    self->f738 = 0;
    self->f74C = 1.04719755f;
}

struct Node_165920 { s32 tag; Node_165920* p4; u8 pad8[0x48]; void* p50; void* p54; u8 pad58[0x28]; Node_165920* next; u8 pad84[0xC]; };
struct Sub_165920 { u8 pad[0x10]; u32 flags; };
struct Rec_165920 { u8 pad[0x38]; Sub_165920* a; u8 pad3C[0x18]; void* b; };
struct Obj_165920 { s32 n0; void* p4; u8 pad8[4]; s32 count; Rec_165920* recs; void* p14; u8 pad18[0x28]; s32 n40; void* p44; u8 pad48[4]; Node_165920* head; s32 f50; };

void func_0018D800(Obj_165920* dst, void* src, s32 n);
void* func_0018D5C0(s32 n);
void* func_0018D568(s32 size, void* src);
void func_00165AE8(Obj_165920* o, void* a, void* b);
void func_00162810(Obj_165920* o);

void func_00165920(Obj_165920* self, s32 arg, void* src)
{
    s32 i = 0;
    Node_165920** link;
    func_0018D800(self, src, 0x58);
    self->f50 = 0;
    self->p4 = func_0018D5C0(self->n0 * 0x90);
    self->p44 = func_0018D568(self->n40 << 2, self->p44);
    self->p14 = func_0018D568(self->count * 0x28, self->p14);
    Rec_165920* old = self->recs;
    for (; i < self->count; i++) {
        Rec_165920* r = (Rec_165920*)((u8*)self->recs + i * 0x70);
        if ((r->a && (r->a->flags & 4)) || r->b) {
            self->recs = (Rec_165920*)func_0018D568(self->count * 0x70, self->recs);
            break;
        }
    }
    link = &self->head;
    Node_165920* s = self->head;
    if (s) {
        do {
            Node_165920* n = (Node_165920*)func_0018D568(0x90, s);
            n->tag = arg;
            Node_165920** pf = &n->p4;
            u32 sz = self->count * 0x70;
            u32 nb = (u32)self->recs;
            if (pf) {
                u32 v = (u32)n->p4;
                if (!(v < (u32)old) && v < (u32)old + sz)
                    n->p4 = (Node_165920*)(v + (nb - (u32)old));
            }
            ((Rec_165920*)n->p4)->b = n;
            *link = n;
            link = &n->next;
            s = n->next;
        } while (s);
    }
    *link = 0;
    i = 0;
    if (self->count > 0) {
        s32 b = 0, a = 0;
        do {
            i++;
            func_00165AE8(self, (u8*)self->recs + a, (u8*)self->p14 + b);
            a += 0x70;
            b += 0x28;
        } while (i < self->count);
    }
    func_00162810(self);
}

// Index written (i << 4) * 9: a plain &items[i] gives a mult that loop.c does not strength-reduce (no s4 offset giv).
struct __attribute__((aligned(16))) Quad_1660E8 { s32 a, b, c, d; };
struct Mat_1660E8 { Quad_1660E8 q[4]; };
struct Obj_1660E8;
typedef void (*VFn_1660E8)(Obj_1660E8* self);
struct VT_1660E8 { u8 pad[0xC0]; VFn_1660E8 f; };
struct Link_1660E8 { u8 pad0[0x60]; Mat_1660E8 m60; u8 pad[4]; s32 a4; u8 pad2[8]; u32 flags; };
struct Obj_1660E8 { VT_1660E8* vt; u8 pad0[0x10C]; u8 sub110[0x30]; u8 sub140[0x40]; u8 pad180[0xA4]; Link_1660E8* link; };
struct Elem_1660E8 { Obj_1660E8* obj; u8 pad[0xC]; Quad_1660E8 q10[4]; Mat_1660E8 m50;  };
struct List_1660E8 { s32 count; Elem_1660E8* items; };
struct Par_1660E8 { u8 pad[0x30]; };
struct Self_1660E8 { u8 pad0[0x110]; u8 sub110[0x30]; u8 sub140[0x40]; u8 pad180[0xAC]; List_1660E8 list; };

void func_00188B48(void* a, void* b, void* out);
void func_00188B08(void* a, void* b, void* out);
Mat_1660E8 func_00188668(Mat_1660E8 a, void* q);

void func_001660E8(Self_1660E8* self, Par_1660E8* par)
{
    Mat_1660E8 a;
    Mat_1660E8 b;
    Mat_1660E8 c;
    Mat_1660E8 e;
    s32 i;
    List_1660E8* l = &self->list;

    if (l->count > 0) {
        func_00188B48(self->sub140, self->sub110, &a);
        if (par != 0) {
            func_00188B48((u8*)par + 0x30, par, &b);
        } else {
            b = a;
        }
        for (i = 0; i < l->count; i++) {
            Elem_1660E8* el = (Elem_1660E8*)((u8*)l->items + (i << 4) * 9);
            if (el->obj != 0) {
                el->obj->vt->f(el->obj);
                Link_1660E8* t = el->obj->link;
                if (t != 0 && (t->flags & 0x80) && t->a4 != 0) {
                    c = t->m60;
                    e = func_00188668(b, &c);
                } else {
                    func_00188B08(el->obj->sub140, el->obj->sub110, &c);
                    e = func_00188668(a, &c);
                }
                el->m50 = func_00188668(e, &el->q10);
            }
        }
    }
}

struct Pkt_164868 {
    u8 pad[0x24];
};
struct Vec3_164868 {
    f32 x;
    f32 y;
    f32 z;
};
struct Uv_164868 {
    f32 u;
    f32 v;
};
struct Rec_164868 {
    u8 pos;
    u8 nrm;
    u8 uv;
    u8 flags;
};
struct Ent_164868 {
    u16* pos;
    u16* nrm;
};
struct Quad_164868 {
    f32 x[4];
    f32 y[4];
    f32 z[4];
    f32 w[4];
};
struct Self_164868 {
    u8 pad00[0x40];
    s32 f40;
};
struct Info_164868 {
    u8 pad00[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
};
struct Node_164868 {
    s32 flags;
};
struct Mesh_164868;
struct Hook_164868;
typedef Node_164868* (*HookFn_164868)(Hook_164868* self, Mesh_164868* mesh);
struct Hook_164868 {
    HookFn_164868* vt;
};
struct Obj_164868 {
    u8 pad00[0x18];
    s32 f18;
    u8 pad1C[0x28 - 0x1C];
    s32 f28;
    u8 pad2C[0x38 - 0x2C];
    Hook_164868* f38;
    u8 pad3C[0x40 - 0x3C];
    f32 f40;
    u8 pad44[0x54 - 0x44];
    Info_164868* f54;
};
struct Strip_164868 {
    s32 count;
    s32 pad;
};
struct Mesh_164868 {
    u8 kind;
    u8 mode;
    u8 pad2[2];
    u8 color[4];
    u8 pad8[0x18 - 0x8];
    s32 nstrips;
    Strip_164868* strips;
    u8 pad20[0x24 - 0x20];
    Hook_164868* f24;
};
struct Extra_164868 {
    s32 f0;
    s32 a4[4];
    s32 a14[4];
    s32 a24[4];
};
struct Unpack_164868 {
    u16 off[4];
    u16 strip[4];
    u16 f10;
    u16 f12;
    u16 pad14[2];
};
struct Hdr_164868 {
    u8 pad00[0x14];
    u32 f14;
    u8 pad18[0x1C - 0x18];
    Unpack_164868* p;
    Extra_164868* extra;
    s32 count;
};

extern s32 D_00262448[];
extern s32 D_00262460[];
extern u8 D_00000288[];
extern u8 D_00001AB0[];
extern u8 D_00002008[];
extern u8 D_00002088[];
extern u8 D_000023B8[];
extern u8 D_000023D8[];
extern u8 D_000023F0[];
extern u8 D_000027C0[];
extern u8 D_00003A80[];
extern u8 D_00003AA0[];

void func_00152B38(Pkt_164868* pkt);
void func_00152D70(Pkt_164868* pkt);
void func_00152CA0(Pkt_164868* pkt);
void func_001EE5C8(Pkt_164868* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void* func_001F5C0C(void* p, s32 value, s32 size);
void func_001EE498(Pkt_164868* s, s32 a, s32 b);
void func_001EE4C0(Pkt_164868* s, u32* src);
void func_001EE528(Pkt_164868* s, s32 value);
void func_001EE3F0(Pkt_164868* s, void* data);
void func_001EE480(Pkt_164868* s);
void func_001EE668(Pkt_164868* s, s32 a, s32 b, void* data, s32 flags);
void func_001EE718(Pkt_164868* s, s32 a, s32 b, s32 c, s32 d, s32* out);
void* func_0018D5C0(s32 bytes);
void func_00163938(s32 mode, Pkt_164868* pkt);
void func_00169608(s32 a, s32 b, Node_164868* node);
void func_001694F8(Mesh_164868* mesh, Strip_164868* strip, s32 a, s32 b, s32 n, Node_164868* node);

void func_00164868(Self_164868* self, Obj_164868* obj, s32 unused2, s32 mode, Hdr_164868* hdr,
                   Mesh_164868* mesh, Vec3_164868* vecs, Vec3_164868* nrms, u8 (*tints)[4], Uv_164868* uvs,
                   s32 n, Rec_164868* recs, Ent_164868* ents, Vec3_164868* verts, Vec3_164868* vnrms,
                   f32* weights, Pkt_164868* pkt, s32** outs)
{
    u32 buf[4];
    f32* posOut;
    f32* wOut;
    s32 k;
    Vec3_164868* dOut;
    Quad_164868* quads;
    f32* nOut;
    u8* cOut;
    Vec3_164868* nDelta;
    f32* uvOut;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 off;
    Node_164868* node;
    s32 i;
    Rec_164868* r;

    if (obj->f54 != 0) {
        func_00152B38(&pkt[2]);
    }
    obj->f18 = 1;
    func_001EE5C8(&pkt[0], 0xD, 3, 0xB, 0, &hdr->p);
    off = 0x24;
    func_001F5C0C(hdr->p, 0, 0x18);
    hdr->p->f10 = 4;
    hdr->p->f12 = hdr->f14 * 0x7FA6 / 0xFF;
    hdr->p->off[0] = off;
    off = n * 4 + 0x24;
    hdr->p->off[1] = off;
    if (hdr->count != 0 || self->f40 != 0) {
        obj->f28 = 1;
    }
    if (obj->f28 != 0) {
        off += (((n + 3) & ~3) - n) * 4;
    }
    hdr->p->strip[3] = off;
    off += n;
    func_001EE498(&pkt[0], 1, 4);
    func_001EE5C8(&pkt[0], 0xC, n, hdr->p->off[0] + 3, 0, &posOut);
    func_001EE498(&pkt[0], 1, 1);
    if (outs[0] != 0) {
        *outs[0] = n;
    }
    if (outs[1] != 0) {
        *outs[1] = (s32)posOut;
    }
    if (obj->f54 != 0) {
        Extra_164868* e = (Extra_164868*)func_0018D5C0(0x34);
        hdr->extra = e;
        e->f0 = (s32)posOut;
    }
    for (i = 0; i < n; i++) {
        r = &recs[i];
        *(Vec3_164868*)posOut = vecs[r->pos];
        if (r->flags >> 7) {
            posOut[3] = obj->f40 + 32768.0f;
        } else {
            posOut[3] = obj->f40 + 28672.0f;
        }
        posOut += 4;
    }
    func_00163938(mode, &pkt[0]);
    if (hdr->count > 0) {
        hdr->p->off[2] = off;
        off += hdr->count * 4;
        hdr->p->off[3] = off;
        off += n;
        func_001F5C0C(buf, 0, 0x10);
        func_001EE4C0(&pkt[0], buf);
        func_001EE528(&pkt[0], D_00262448[hdr->count]);
        func_001EE5C8(&pkt[0], D_00262460[hdr->count], n, hdr->p->off[3], 0, &wOut);
        func_001EE528(&pkt[0], 0);
        for (i = 0; i < n; i++) {
            r = &recs[i];
            for (s32 j = 0; j < hdr->count; j++) {
                *wOut++ = weights[r->pos * hdr->count + j];
            }
        }
        func_001EE3F0(&pkt[0], D_00002008);
    }
    if (self->f40 != 0) {
        hdr->p->off[3] = off;
        off += self->f40;
        for (k = 0; k < self->f40; k++) {
            func_001EE668(&pkt[0], 0, 1, &k, 0x16);
            func_001EE5C8(&pkt[0], 8, n, hdr->p->strip[3], 0, &dOut);
            u16* idx = ents[k].pos;
            for (i = 0; i < n; i++) {
                r = &recs[i];
                Vec3_164868* v = &verts[idx[i]];
                dOut[i].x = v->x - vecs[r->pos].x;
                dOut[i].y = v->y - vecs[r->pos].y;
                dOut[i].z = v->z - vecs[r->pos].z;
            }
            func_001EE3F0(&pkt[0], D_000023B8);
            func_001EE480(&pkt[0]);
        }
    }
    func_001EE498(&pkt[1], 1, 4);
    if (obj->f28 != 0 && hdr->count == 0 && self->f40 == 0) {
        func_001EE5C8(&pkt[1], 0xC, (n + 3) & ~3, hdr->p->off[0], 0, &quads);
        nOut = 0;
    } else {
        func_001EE5C8(&pkt[1], 0xC, n, hdr->p->off[0], 0, &nOut);
        quads = 0;
    }
    func_001EE5C8(&pkt[1], 0xE, n, hdr->p->off[0] + 1, 0, &cOut);
    func_001EE498(&pkt[1], 1, 1);
    if (hdr->count > 0) {
        func_001EE3F0(&pkt[1], D_00002088);
    }
    if (self->f40 > 0) {
        for (s32 m = 0; m < self->f40; m++) {
            if (m > 0) {
                func_001EE480(&pkt[1]);
            }
            func_001EE5C8(&pkt[1], 8, n, hdr->p->strip[3], 0, &nDelta);
            u16* idx = ents[m].nrm;
            for (i = 0; i < n; i++) {
                r = &recs[i];
                Vec3_164868* v = &vnrms[idx[i]];
                nDelta[i].x = v->x - nrms[r->nrm].x;
                nDelta[i].y = v->y - nrms[r->nrm].y;
                nDelta[i].z = v->z - nrms[r->nrm].z;
            }
            func_001EE3F0(&pkt[1], D_000023D8);
        }
        func_001EE3F0(&pkt[1], D_000023F0);
    }
    func_001EE3F0(&pkt[1], D_00000288);
    for (i = 0; i < n; i++) {
        s32 j;
        r = &recs[i];
        if ((r->flags & 0x7F) == 0x7F) {
            for (j = 0; j < 4; j++) {
                cOut[j] = (mesh->color[j] + 1) >> 1;
            }
        } else {
            for (j = 0; j < 4; j++) {
                cOut[j] = (mesh->color[j] * tints[r->flags & 0x7F][j] + 0x100) / 0x1FE;
            }
        }
        if (nOut != 0) {
            if (r->nrm == 0xFF) {
                nOut[0] = nOut[1] = nOut[2] = 0.0f;
            } else {
                *(Vec3_164868*)nOut = nrms[r->nrm];
            }
            nOut[3] = (cOut[0] + cOut[1] + cOut[2]) * 0.33333334f;
            nOut += 4;
        }
        cOut += 4;
    }
    if (quads != 0) {
        for (i = 0; i < n; i += 4) {
            for (s32 j = 0; j < 4; j++) {
                if (i + j < n) {
                    quads->x[j] = nrms[recs[i + j].nrm].x;
                    quads->y[j] = nrms[recs[i + j].nrm].y;
                    quads->z[j] = nrms[recs[i + j].nrm].z;
                } else {
                    quads->x[j] = quads->y[j] = quads->z[j] = 0.0f;
                }
            }
            func_001F5C0C(quads->w, 0, 0x10);
            quads++;
        }
    }
    func_001EE498(&pkt[2], 1, 4);
    func_001EE5C8(&pkt[2], 8, n, hdr->p->off[0], 0, &uvOut);
    func_001EE498(&pkt[2], 1, 1);
    if (outs[2] != 0) {
        *outs[2] = (s32)uvOut;
    }
    for (i = 0; i < n; i++) {
        r = &recs[i];
        if (r->uv == 0xFF) {
            uvOut[0] = uvOut[1] = 0.0f;
        } else {
            uvOut[0] = uvs[r->uv].u;
            uvOut[1] = uvs[r->uv].v;
        }
        uvOut[2] = 1.0f;
        uvOut += 3;
    }
    node = 0;
    if (obj->f38 != 0) {
        node = obj->f38->vt[5](obj->f38, mesh);
    }
    if (node == 0 && mesh->f24 != 0) {
        node = mesh->f24->vt[5](mesh->f24, mesh);
    }
    if (node != 0 && (node->flags & 2)) {
        func_001EE5C8(&pkt[2], 4, 1, 0x16, &a, &b);
        func_00169608(b, a, node);
        func_001EE3F0(&pkt[2], D_000027C0);
    }
    if (hdr->extra != 0) {
        Extra_164868* e = hdr->extra;
        for (s32 i = 0; i < obj->f54->f10; i++) {
            func_001EE5C8(&pkt[2], 0xC, n, off, 0, &e->a24[i]);
            if (obj->f54->f18 != 0) {
                func_001EE718(&pkt[2], 0xC, 4, 0, 0x16, &e->a14[i]);
                func_001EE3F0(&pkt[2], D_00003A80);
                func_001EE480(&pkt[2]);
            }
            if (obj->f54->f14 != 0) {
                func_001EE718(&pkt[2], 0xC, 4, 0, 0x16, &e->a4[i]);
                func_001EE3F0(&pkt[2], D_00003AA0);
                func_001EE480(&pkt[2]);
            }
        }
        hdr->p->off[3] = off;
        off += n;
    }
    func_001EE3F0(&pkt[2], D_00001AB0);
    s32 slot = 0;
    for (s32 i = 0; i < mesh->nstrips; i++) {
        Strip_164868* s = &mesh->strips[i];
        func_001EE5C8(&pkt[2], 0xC, s->count, off, &c, &d);
        func_001694F8(mesh, s, d, c, n, node);
        hdr->p->strip[slot++] = off;
        off += s->count;
    }
    if (obj->f54 != 0) {
        func_00152D70(&pkt[2]);
        func_00152CA0(&pkt[2]);
    }
}
