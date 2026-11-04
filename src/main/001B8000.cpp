// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "c03.h"

void func_00125108(C03* self);
void func_00138BE0(void* a, void* b, s32 c);
void func_001389C8(void* a);

void func_001B89B8(C03* self)
{
    func_00125108(self);
    self->root03()->desc03()->m32(self->root03());
    func_00138BE0(self->world, self, 7);
    func_001389C8(self->world);
}

void func_001B9448(C03* self);

void func_001B9418(C03* self, f32 v)
{
    f32 a = self->mass;
    f32 q = v / a;
    self->mass = a * q;
    func_001B9448(self);
}

void func_001BAC28(C03* self, Attach03* node, f32 dt)
{
}

void func_001BB1A0(C03* self, s32 flag)
{
    self->flags538 = (self->flags538 & 0xFFFEFFFFFFFFFFFFULL) | ((u64)(flag & 1) << 48);
}

void func_001B94F0(C03* self, s32 value);

void func_001BB400(C03* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 43;
    self->flags538 = (self->flags538 & ~(1ULL << 43)) | bit;
    func_001B94F0(self, value != 0 ? 2 : 0);
}

s32 func_001BB9A0(Touch03* node, C03* value)
{
    while (node != 0) {
        if (node->obj == value) return 1;
        node = node->next;
    }
    return 0;
}

void func_001BB378(C03* self, s32 flag)
{
    self->flags538 = (self->flags538 & ~(1ULL << 51)) | ((u64)(flag & 1) << 51);
}

void func_001BB3B0(C03* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 42;
    self->flags538 = (self->flags538 & ~(1ULL << 42)) | bit;
    func_001B94F0(self, value != 0);
}

void func_001BB450(C03* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 44;
    self->flags538 = (self->flags538 & ~(1ULL << 44)) | bit;
    func_001B94F0(self, value != 0 ? 3 : 0);
}

void func_001BB4A0(C03* self)
{
    ListFrame frame;
    const Desc03* info = self->desc03();
    if (info->m41 != 0 || info->m3C != 0 || info->m3D != 0) {
        self->handler = self;
    } else if (info->m3E != 0) {
        self->handler = self;
    } else {
        C03* p = (C03*)self->parent;
        if (p != 0) {
            self->handler = p->handler;
        } else {
            self->handler = 0;
        }
    }
    C03* c = (C03*)self->children.head;
    while (c != 0) {
        if (c->desc->flags & 2) func_001BB4A0(c);
        c = (C03*)c->next;
    }
}

C03* func_001BB540(C03* node, s32 offset)
{
    C03* s;
    while (node != 0 && (s = node->handler) != 0) {
        if (*(s32*)((u8*)s->desc + offset) != 0) return s;
        node = (C03*)s->parent;
    }
    return 0;
}

void func_00138F28(void* a, void* b);

void func_001BB580(C03* self)
{
    ListFrame frame;
    s32 flag = 0;
    if (self->mode450 == 3) {
        flag = (self->mode470 == 3);
    }
    self->flags538 = (self->flags538 & ~(1ULL << 54)) | ((u64)flag << 54);
    s32 s2 = flag & 1;
    s32 a0 = 0;
    if (self->flags538 & (1ULL << 54)) {
        if (self->parent == 0 || (((C03*)self->parent)->flags538 & (1ULL << 56)) != 0) a0 = 1;
    }
    self->flags538 = (self->flags538 & ~(1ULL << 56)) | ((u64)a0 << 56);
    C03* c = (C03*)self->children.head;
    while (c != 0) {
        if (c->desc->flags & 2) {
            func_001BB580(c);
            if ((c->flags538 & (1ULL << 55)) == 0) s2 = 0;
        }
        c = (C03*)c->next;
    }
    u64 bit = (self->flags538 >> 55) & 1;
    if (bit != (u64)s2) {
        self->flags538 = (self->flags538 & ~(1ULL << 55)) | ((u64)(s2 & 1) << 55);
        if (self->parent == 0 && self->root != 0) {
            func_00138F28(self->world, self);
        }
    }
}

s32 func_001C1AD8(s32 value, void* out);
s32 func_001C1A28(s32 value, void* out);

s32 func_001BB710(C03* self, s32 value)
{
    C03* ctx = self->root03();
    ContactRow03* n = ctx->contacts->head;
    while (n != 0) {
        Contact03* e = n->head;
        while (e != 0) {
            s32 idx = ((u32)e->end[0].body ^ (u32)ctx) != 0;
            ContactEnd03* s = &e->end[idx];
            if (s->part == self) {
                void* tmp = e->end[1 - idx].part;
                if (func_001C1AD8(value, &tmp) == 0) {
                    if (func_001C1A28(value, &tmp) == 0) return 0;
                }
            }
            e = e->next;
        }
        n = n->next;
    }
    return 1;
}

s32 func_001B8A08(C03* a, C03* b)
{
    u64 m1 = 0x8080;
    s32 r = 0;
    m1 <<= 40;
    if ((a->flags538 & m1) != 0) {
        u64 bf = b->flags538;
        u64 m2 = 0x8000;
        m2 <<= 40;
        if ((bf & m2) != 0) {
            return 1;
        }
    }
    return r;
}

void func_001B8A48(C03* self)
{
    ContactRow03* node = self->contacts->head;
    while (node != 0) {
        Contact03* it = node->head;
        while (it != 0) {
            if (0.0001f < it->timer) {
                for (s32 i = 0; i < 2; i++) {
                    C03* obj = func_001BB540(it->end[i].part, 0x114);
                    if (obj != 0) {
                        void (*fn)(C03*, Contact03*, s32) = obj->desc03()->m41;
                        if (fn != 0) {
                            fn(obj, it, i);
                        }
                    }
                }
                *(s32*)&it->timer = 0;
            }
            if (node->head == 0) {
                break;
            }
            it = it->next;
        }
        node = node->next;
    }
}

struct Vec_1B9338 { s32 v[4]; };

void func_001BA500(void* a, void* b, void* c, void* d, s32 e);
void func_001B9AB0(void* a, void* b);

void func_001B9338(C03* self, f32 t)
{
    Vec_1B9338 local;
    Attach03* node;
    u64 m = 0x8000;
    m <<= 36;
    if (self->parent == 0) {
        if ((self->flags538 & m) == 0) {
            func_001BA500(self, &self->v440, &self->gravity, &local, 0);
            func_001B9AB0(self, &local);
        }
    }
    node = self->attached;
    if (node != 0) {
        do {
            C03* obj = node->owner;
            obj->desc03()->m33(obj, node, t);
            node = node->next;
        } while (node != 0);
    }
}

void func_001261C0(C03* self, void* a, void* m);

void func_001B93D8(C03* self, void* a, void* m)
{
    func_001261C0(self, a, m);
}

void func_00124FC0(void* self);

void func_001B93F8(C03* self)
{
    func_00124FC0(self);
}

void func_001B9680(C03* self)
{
    self->v370 = self->v140;
}

void func_001BA430(void* a, void* b, void* c, s32 d);

void func_001BA500(void* self, void* a, void* b, void* c, s32 d)
{
    func_001BA430(a, b, c, d);
}

void func_00129DF8(void* self);

void func_001BA528(C03* self, Attach03* node)
{
    node->next = self->attached;
    self->attached = node;
    func_00129DF8(self);
}

s32 func_001BBC30(C03* self)
{
    return 0;
}

void func_001B97E0(C03* self, Mat02* src)
{
    self->rot.r[0] = src->r[0];
    self->rot.r[1] = src->r[1];
    self->rot.r[2] = src->r[2];
    if (self->root != 0) {
        if (self->desc->m12 != 0) {
            self->desc->m12(self);
        }
        func_001B94F0(self, 1);
    }
    self->desc->m0E(self, 4, self);
}

void func_001BAFE0(C03* self, f32 v)
{
    self->flags538 |= (u64)0x8000 << 25;
    self->radius3CC = v;
}

void func_001BB138(C03* self, u32 value) { self->flags538 = (self->flags538 & ~(0xFULL << 32)) | ((u64)(value & 0xF) << 32); }

void func_001BB168(C03* self, u32 value) { self->flags538 = (self->flags538 & ~(1ULL << 47)) | ((u64)(value & 1) << 47); }

void func_001BB1D8(C03* self, u8 value) { self->b2C8 = value; }

void func_001BB1E0(C03* self, u32 value) { self->flags538 = (self->flags538 & ~(0xFULL << 36)) | ((u64)(value & 0xF) << 36); }

typedef u64 Quad_1B8960 __attribute__((mode(TI)));

void func_00125138(void* self);
void func_001B8820(Mesh03* a, Mesh03* b, Quad_1B8960 q, Mat02* c);

void func_001B8960(C03* self)
{
    func_00125138(self);
    func_001B8820(&self->mesh, &self->meshCopy, *(Quad_1B8960*)&self->v140, &self->m110);
    func_001B8820(&self->mesh2, &self->mesh2Copy, *(Quad_1B8960*)&self->v140, &self->m110);
}

struct __attribute__((aligned(16))) Quad_1B9B50 { s32 a, b, c, d; };

void func_001280C0(void* a, void* b, void* c, void* d);
void func_001245A8(void* self, void* p);

void func_001B9B50(C03* self, C01* p)
{
    Quad_1B9B50 local0;
    Quad_1B9B50 local1;
    if (self->parent == p) {
        return;
    }
    C03* s5 = self->root03();
    func_001280C0(self->parent, 0, &self->v440, &local0);
    func_001280C0(self->parent, 0, &self->v460, &local1);
    func_001245A8(self, p);
    func_001280C0(0, p, &local0, &self->v440);
    func_001280C0(0, p, &local1, &self->v460);
    if (self->root != 0) {
        if ((self->flags538 & (1ULL << 54)) != 0 && s5 != 0) {
            func_001BB580(s5);
        }
        C03* f = self->root03();
        if ((f->flags538 & (1ULL << 55)) != 0) {
            func_001BB580(f);
        } else {
            func_001BB580(self);
        }
    }
    func_001BB4A0(self);
}

s32 func_00182F40(void* e, void* b);

void* func_001BA068(C03* self)
{
    C03* s3 = self->root03();
    ContactRow03* s2 = s3->contacts->head;
    for (; s2 != 0; s2 = s2->next) {
        Contact03* s0 = s2->head;
        while (s0 != 0) {
            s32 s1 = ((u32)s3 ^ (u32)s0->end[0].body) != 0;
            if (func_00182F40(*(void**)((u8*)(s0) + (s1 << 6) + 4), self) != 0) {
                return *(void**)((u8*)(s0) + ((1 - s1) << 6) + 4);
            }
            s0 = s0->next;
        }
    }
    return 0;
}

void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

void func_001BB000(void* self)
{
    func_001B9AE0(self, 3, 0, 3, 0);
}

void func_00183350(void* self, s32 kind, void* arg);

void func_001BB210(C03* self, s32 kind, void* arg)
{
    func_00183350(self, kind, arg);
    Attach03* n = self->attached;
    if (n != 0) {
        do {
            Attach03* next = n->next;
            C03* obj = n->owner;
            if (obj != self) {
                void (*fn)(C01*, s32, void*) = obj->desc->m0D;
                if (fn != 0) {
                    fn(obj, kind, arg);
                }
            }
            n = next;
        } while (n != 0);
    }
}

struct __attribute__((aligned(16))) Quad_1BB028 { s32 v[4]; };
struct Entry_1BB028 { Quad_1BB028* quad; s32 value; };
extern Quad_1BB028 D_00248D00;
extern Quad_1BB028 D_00248D10;
extern Quad_1BB028 D_00248D20;
extern Quad_1BB028 D_00248D30;
extern Entry_1BB028 D_002746E0[8];
void func_001BB028(s32 index, s32* out, Quad_1BB028* dst)
{
    *out = D_002746E0[index].value;
    *dst = *D_002746E0[index].quad;
}

void* func_0018D658(s32 n);

s32 func_001BB800(C03* obj, s32* outCount, void*** outArr)
{
    C03* own = obj->root03();
    ContactRow03* nd;
    Contact03* it;
    s32 n = 0;
    for (nd = own->contacts->head; nd; nd = nd->next) {
        for (it = nd->head; it; it = it->next) {
            s32 g = it->end[0].body != own;
            if (func_00182F40(*(void**)((u8*)it + (g << 6) + 4), obj))
                n++;
        }
    }
    void** arr = (void**)func_0018D658(n << 2);
    void** end = arr;
    for (nd = own->contacts->head; nd; nd = nd->next) {
        for (Contact03* it2 = nd->head; it2; it2 = it2->next) {
            s32 f = it2->end[0].body != own;
            if (func_00182F40(*(void**)((u8*)it2 + (f << 6) + 4), obj)) {
                void* v = *(void**)((u8*)it2 + ((1 - f) << 6) + 4);
                void** p;
                for (p = arr; p < end; p++)
                    if (*p == v) break;
                if (!(p < end)) {
                    *end = v;
                    end++;
                }
            }
        }
    }
    *outArr = arr;
    s32 cnt = end - arr;
    *outCount = cnt;
    return cnt;
}

void func_001BA550(C03* o, Attach03* node)
{
    Attach03** link = &o->attached;
    if (*link == 0) {
        goto tail;
    }
    if (o->attached == node) {
        o->attached = node->next;
    } else {
        Attach03* prev;
        for (;;) {
            prev = *link;
            Attach03* nx = prev->next;
            link = &prev->next;
            if (nx == 0) {
                goto tail;
            }
            if (nx == node) {
                break;
            }
        }
        prev->next = node->next;
    }
    node->next = 0;
tail:
    func_00129DF8(o);
}

s32 func_001387F8(void* self, void* other);

s32 func_001B9FB0(C03* self, void* other)
{
    s32 key;
    Contact03* n;
    for (n = (Contact03*)func_001387F8(self, other), key = (s32)self->root; n != 0; n = n->next) {
        s32 s1 = (key ^ (s32)n->end[0].body) != 0;
        s32 o0 = s1 * 64;
        if (func_00182F40(*(void**)((u8*)n + o0 + 4), self) != 0) {
            s32 o1 = (1 - s1) * 64;
            if (func_00182F40(*(void**)((u8*)n + o1 + 4), other) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

// Matched by indexing the end as (u32)e + (i << 6).

void func_001837E0(void* self, s32 a, s32 b, void* c);
void func_001DC108(void* pool, Touch03* m);
Touch03* func_001DC0C8(void* pool);

void func_001BB9D0(C03* self)
{
    C03* core = self->root03();
    ContactRow03* o;
    Contact03* e;
    Touch03* m;
    Touch03* prev;
    C03* other;
    void* args;
    for (o = core->contacts->head; o != 0; o = o->next) {
        for (e = o->head; e != 0; e = e->next) {
            s32 i = e->end[0].body != core;
            if (((ContactEnd03*)((u32)e + (i << 6)))->part == self) {
                other = ((ContactEnd03*)((u32)e + ((1 - i) << 6)))->part;
                if (!func_001BB9A0(self->touching, other)) {
                    args = &other;
                    func_001837E0(self, 6, 1, &args);
                }
            }
        }
    }
    for (m = self->touching; m != 0; m = m->next) {
        s32 found = 0;
        for (o = core->contacts->head; o != 0 && !found; o = o->next) {
            for (e = o->head; e != 0 && !found; e = e->next) {
                s32 i = e->end[0].body != core;
                if (((ContactEnd03*)((u32)e + (i << 6)))->part == self) {
                    other = ((ContactEnd03*)((u32)e + ((1 - i) << 6)))->part;
                    if (other == m->obj) found = 1;
                }
            }
        }
        if (!found) {
            args = m;
            func_001837E0(self, 7, 1, &args);
        }
    }
    func_001DC108(self->world, self->touching);
    self->touching = 0;
    for (o = core->contacts->head; o != 0; o = o->next) {
        for (e = o->head; e != 0; e = e->next) {
            s32 i = e->end[0].body != core;
            if (((ContactEnd03*)((u32)e + (i << 6)))->part == self) {
                other = ((ContactEnd03*)((u32)e + ((1 - i) << 6)))->part;
                Touch03* n = func_001DC0C8(self->world);
                n->obj = other;
                if (self->touching != 0) prev->next = n; else self->touching = n;
                prev = n;
            }
        }
    }
}

void func_00127048(C03* self, C03* other);
void func_001B7C40(C03* self, s32 flag);
void func_00160EA0(Mesh03* a, s32 b, Mesh03* c);
void func_0013E6C8(Mesh03* a, Tree03* b, Mesh03* c, Tree03* d);

void func_001BA130(C03* self, C03* other)
{
    u64 bit = (self->flags538 >> 50) & 1;
    Link02 a, c, d;
    List01 b;
    a = self->link2D0;
    b = self->parts;
    c = self->link2E4;
    Contacts03* s480 = self->contacts;
    C03* s4E4 = self->handler;
    d = self->link414;
    func_00127048(self, other);
    self->contacts = s480;
    self->link2D0 = a;
    self->parts = b;
    self->link2E4 = c;
    self->link414 = d;
    self->handler = s4E4;
    self->attached = 0;
    self->f4B8 = 0;
    self->flags538 = (self->flags538 & 0xFFFBFFFFFFFFFFFFULL) | (bit << 50);
    func_001B7C40(self, 1);
    if (self->meshCopy.vertCount) func_00160EA0(&other->meshCopy, 0, &self->meshCopy);
    if (self->tree.nodes) func_0013E6C8(&other->meshCopy, &other->tree, &self->meshCopy, &self->tree);
    if (self->mesh2Copy.vertCount) func_00160EA0(&other->mesh2Copy, 0, &self->mesh2Copy);
    if ((s32)self->flags538) func_0013E6C8(&other->mesh2Copy, &other->tree2, &self->mesh2Copy, &self->tree2);
    self->touching = 0;
    self->flags538 |= 0x20000000000ULL;
}

// NEAR: 14 lines: retail preloads f400/f40C into s0 (lw s0 before loop and in the bnel delay slot), we load into v1; f408 loop test reload; last loop pointer s2 vs index

struct In_1BAC30 { u8 pad[4]; };

s32 func_00137B90(In_1BAC30* in);
void func_00137FB0(In_1BAC30* in, Mesh03* p);
void func_00138278(In_1BAC30* in, Mesh03* a, Tree03* out);
f32 func_00137DF8(In_1BAC30* in);
void func_00137EB0(In_1BAC30* in, Mat02* p);
void func_00137E70(In_1BAC30* in, Vec02* p);
void func_001B9448(C03* self, f32 x);
s32 func_00137BE0(In_1BAC30* in);
void* func_0018D500(s32 size);
s32 func_00137D10(In_1BAC30* in);
s32 func_00137C40(In_1BAC30* in);
void func_001289C0(C03* self, In_1BAC30* in);
void func_00138F28(void* a, C03* b);

void func_001BAC30(C03* self, In_1BAC30* in)
{
    s32 i;
    s32 j;
    s32 n;
    Pair03* e;
    u8 flag = func_00137B90(in) & 1;
    self->flags = (self->flags & ~(1ULL << 33)) | ((u64)flag << 33);
    func_00137FB0(in, &self->mesh);
    self->radius3D0 = self->mesh.radius;
    self->radius3CC = self->mesh.radius;
    if (self->flags & (1ULL << 33)) {
        self->meshCopy = self->mesh;
    } else {
        func_00160EA0(&self->mesh, 0, &self->meshCopy);
    }
    func_00138278(in, &self->meshCopy, &self->tree);
    i = 0;
    self->mass = func_00137DF8(in);
    func_00137EB0(in, &self->inertia);
    func_00137E70(in, &self->offset);
    func_001B9448(self, 1.0f);
    self->groupCount = func_00137BE0(in);
    self->groups = (Pair03*)func_0018D500(self->groupCount << 3);
    if (self->groupCount > 0) {
        do {
            e = self->groups;
            e += i++;
            e->a = func_00137D10(in);
            e->b = func_00137BE0(in);
        } while (i < self->groupCount);
    }
    n = func_00137C40(in);
    j = 0;
    self->nodeGroups = (s32*)func_0018D500(n << 2);
    if (n > 0) {
        do {
            s32 v = func_00137D10(in);
            self->nodeGroups[j] = v;
            j++;
        } while (j < n);
    }
    self->refCount = func_00137C40(in);
    i = 0;
    self->refs = (Pair03*)func_0018D500(self->refCount << 3);
    while (i < self->refCount) {
        e = self->refs;
        e += i++;
        e->a = func_00137D10(in);
        e->b = func_00137D10(in);
    }
    if (self->refCount > 0) {
        j = 0;
        self->faceStarts = (s32*)func_0018D500((self->meshCopy.faceCount + 1) << 2);
        if (self->meshCopy.faceCount >= 0) {
            do {
                s32 v = func_00137D10(in);
                self->faceStarts[j] = v;
                j++;
            } while (self->meshCopy.faceCount >= j);
        }
    }
    func_00137FB0(in, &self->mesh2);
    if (self->flags & (1ULL << 33)) {
        self->mesh2Copy = self->mesh2;
    } else {
        func_00160EA0(&self->mesh2, 0, &self->mesh2Copy);
    }
    func_00138278(in, &self->mesh2Copy, &self->tree2);
    func_001289C0(self, in);
    func_001B7C40(self, 1);
    self->desc03()->m44(self);
    if (self->parent == 0) {
        self->desc03()->m32(self);
        func_00138F28(self->world, self);
    }
}

struct Quad_1B9F30 { f32 v[4]; } __attribute__((aligned(16)));
struct Out_1B9F30 {
    s32 f00;
    u8 pad04[0x0C];
    Vec02 q10;
    Vec02 q20;
    f32 f30;
    f32 f34;
    f32 f38;
    s32 f3C;
};

void func_00189378(Mat02* m, s32 zero, Quad_1B9F30* out);
f32 func_00205778(f32 a, f32 b);
extern f32 D_0026185C[];

void func_001B9F30(C03* self, Out_1B9F30* out)
{
    Quad_1B9F30 tmp[3];
    out->q10 = self->v140;
    out->q20 = self->v150;
    func_00189378(&self->m110, 0, &tmp[0]);
    out->f30 = func_00205778(-tmp[0].v[1], -tmp[0].v[0]);
    out->f34 = 100.0f;
    out->f00 = 0;
    out->f38 = D_0026185C[0];
    out->f3C = 0;
}

void func_001B9AE0(C03* self, s32 a1, Vec02* a2, s32 a3, Vec02* a4)
{
    self->mode450 = a1;
    u64 flag = (self->flags538 >> 54) & 1;
    if (a2 != 0) {
        self->v440 = *a2;
    }
    self->mode470 = a3;
    if (a4 != 0) {
        self->v460 = *a4;
    }
    C03* sub = self->root03();
    if (sub != 0) {
        s32 f2 = 0;
        if (a1 == 3) {
            f2 = (a3 == 3);
        }
        if (flag != f2) {
            func_001BB580(sub);
        }
    }
}

void func_001861E8(void* pool, Contact03* head);

void func_001B94F0(C03* self, s32 mode)
{
    C03* ctx = self->root03();
    if (ctx == 0) {
        return;
    }
    if (mode != 0) {
        Contact03* freed = 0;
        for (ContactRow03* o = ctx->contacts->head; o != 0; o = o->next) {
            Contact03** pp = &o->head;
            Contact03* it;
            while ((it = *pp) != 0) {
                s32 other = it->end[0].body != ctx;
                ContactEnd03* p = &it->end[other];
                s32 hit;
                switch (mode) {
                case 1:
                    hit = func_00182F40(p->part, self);
                    break;
                case 2:
                    hit = p->part == self;
                    break;
                case 3:
                    hit = 0;
                    if (p->part == self && other == 0) {
                        if (it->kind >= 8 && it->kind <= 9) {
                            hit = 1;
                        }
                    }
                    break;
                default:
                    hit = 0;
                    break;
                }
                if (hit != 0) {
                    *pp = it->next;
                    it->next = freed;
                    freed = it;
                } else {
                    pp = &it->next;
                }
            }
            *o->link = o->head;
        }
        func_001861E8(self->world, freed);
    }
    ctx->f4B8 = 0;
}

Entry_1BB028 D_002746E0[8] = {
    { &D_00248D30, 0 },
    { &D_00248D30, 3 },
    { &D_00248D00, 2 },
    { &D_00248D10, 2 },
    { &D_00248D20, 2 },
    { &D_00248D20, 1 },
    { &D_00248D10, 1 },
    { &D_00248D00, 1 },
};
