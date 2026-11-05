// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "entry_pool.h"
#include "r11b008.h"
#include "s137290.h"
#include "shapes.h"

// The five pools values are taken from (func_0011C240): func_0011BF70 sets them up, func_0011C040
// empties them all. Built at startup: the compiler's initialiser, constructor and destructor for this
// file are func_0011C0A8, func_0011C0E8 and func_0011C108 (config/us/generated.tsv).
EntryPool D_0025C250;
EntryPool D_0025C270;
EntryPool D_0025C290;
EntryPool D_0025C2B0;
EntryPool D_0025C2D0;

// The payloads of tags 0x19 and 0x1A as func_0011B258 copies them (ldl/ldr for the first two
// words: the pool does not align them).
struct Pair_11B258 { U64P xy; };
struct Triple_11B258 { U64P xy; s32 z; };

void func_0018D778(void* p);
void* func_0018D5C0(s32 size);
void* func_001F5C0C(void* p, s32 value, s32 size);
s32 func_001F59C4(void* a, void* b, s32 n);
void* func_0011C240(EntryPool* pool);
void func_0011C128(EntryPool* pool, s32 size, s32 count);
void func_0011C1D0(EntryPool* pool);
R11B008Key* func_0011C498(void);
void func_0011C418(R11B008Key* src, R11B008Key* dst, s32 zero);
void func_0011C4E8(void);
void func_0011CA90(void);
void func_0011CBB0(void);
extern u8 D_00259F38[];
void func_0011A6A8(void* p);
void func_0011A6B8(void* p);
void func_0011A670(void);

// The pooled payloads (0011C000.cpp): each tag's allocator, reference and release.
void* func_0011C508(void);
void* func_0011C618(void);
void* func_0011C748(void);
void* func_0011C858(void);
void* func_0011C968(void);
s32 func_0011C580(void* p);
s32 func_0011C690(void* p);
s32 func_0011C7C0(void* p);
s32 func_0011C8D0(void* p);
s32 func_0011C9E0(void* p);
void func_0011C5B0(void* p);
void func_0011C6C0(void* p);
void func_0011C7F0(void* p);
void func_0011C900(void* p);
void func_0011CA20(void* p);

// The stream reader (00134000.cpp).
s32 func_00137B90(S137290* r);
void func_00137BE0(S137290* r);
s32 func_00137D78(S137290* r);
f32 func_00137DF8(S137290* r);
s32 func_00137C40(S137290* r);

extern s32 D_00275714;

void* func_0011AE78(void)
{
    void* p = func_0011C240(&D_0025C2D0);
    func_001F5C0C(p, 0, 12);
    return p;
}

void func_0011AEB8(R11B008Node* src, R11B008Node* dst, s32 first)
{
    func_0011B258(src, dst, first);
    if (src->next != 0) {
        R11B008Node* copy = func_0011AF28();
        func_0011AEB8(src->next, copy, first);
        dst->next = copy;
    }
}

R11B008Node* func_0011AF28(void)
{
    R11B008Node* node = (R11B008Node*)func_0011C240(&D_0025C250);
    func_001F5C0C(node, 0, 12);
    func_0011B008(node);
    node->tag = -1;
    return node;
}

void func_0011AF78(R11B008Node* self)
{
    func_0011B060(self, 2);
}

void func_0011AF98(R11AFC8* src, R11AFC8* dst, s32 first)
{
    if (first == 0) {
        first = src->w0;
    }
    dst->w0 = first;
    dst->w4 = src->w4;
    dst->w8 = src->w8;
    dst->wC = src->wC;
    dst->w10 = src->w10;
}

R11AFC8* func_0011AFC8(void)
{
    R11AFC8* p = (R11AFC8*)func_0011C240(&D_0025C2B0);
    func_001F5C0C(p, 0, 0x14);
    return p;
}

R11B008* func_0011B008(R11B008* self)
{
    self->tag = -1;
    return self;
}

R11B008* func_0011B018(R11B008* self, const R11B008* src)
{
    func_0011B4A8(src);
    self->tag = src->tag;
    self->i = src->i;
    return self;
}

void func_0011B060(R11B008* self, s32 flags)
{
    func_0011B418(self);
    if (flags & 1) {
        func_0018D778(self);
    }
}

R11B008* func_0011B0A8(R11B008* self, const R11B008* src)
{
    func_0011B4A8(src);
    func_0011B418(self);
    self->tag = src->tag;
    self->i = src->i;
    return self;
}

s32 func_0011B0F8(const R11B008* a, const R11B008* b)
{
    if (a->tag != b->tag)
        return 0;
    switch (a->tag) {
    case 0x15:
        return a->f == b->f;
    case 0x1B: {
        s32 r = 0;
        if (a->p == 0) {
            if (b->p == 0)
                goto yes;
            goto out;
        }
        if (b->p != 0) {
        yes:
            r = 1;
        }
    out:
        return r;
    }
    case 0x17:
        return func_001F59C4(a->p, b->p, 0x40) == 0;
    case 0x19: {
        f32* pa = a->v;
        f32* pb = b->v;
        s32 r = 0;
        if (pa[0] == pb[0] && pa[1] == pb[1])
            r = 1;
        return r;
    }
    case 0x16:
    case 0x18:
    case 0x1A: {
        f32* pa = a->v;
        f32* pb = b->v;
        s32 r = 0;
        if (pa[0] == pb[0] && pa[1] == pb[1] && pa[2] == pb[2])
            r = 1;
        return r;
    }
    case 0x14:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
        return a->i == b->i;
    }
    return 1;
}

void func_0011B258(const R11B008* src, R11B008* dst, s32 first)
{
    dst->tag = src->tag;
    switch (src->tag) {
    case 0x1E: {
        R11B008Node* n = func_0011AF28();
        func_0011AEB8(src->node, n, first);
        dst->node = n;
        break;
    }
    case 0x16: {
        Quad16* p = (Quad16*)func_0011C508();
        *p = *(Quad16*)src->p;
        (void)func_0011C580(p);
        dst->p = p;
        break;
    }
    case 0x17: {
        Mat4A* p = (Mat4A*)func_0011C618();
        *p = *(Mat4A*)src->p;
        (void)func_0011C690(p);
        dst->p = p;
        break;
    }
    case 0x18: {
        Quad16* p = (Quad16*)func_0011C748();
        *p = *(Quad16*)src->p;
        (void)func_0011C7C0(p);
        dst->p = p;
        break;
    }
    case 0x19: {
        Pair_11B258* p = (Pair_11B258*)func_0011C858();
        *p = *(Pair_11B258*)src->p;
        (void)func_0011C8D0(p);
        dst->p = p;
        break;
    }
    case 0x1A: {
        Triple_11B258* p = (Triple_11B258*)func_0011C968();
        *p = *(Triple_11B258*)src->p;
        (void)func_0011C9E0(p);
        dst->p = p;
        break;
    }
    case 0x1F: {
        R11AFC8* r = func_0011AFC8();
        func_0011AF98(src->rec, r, first);
        dst->rec = r;
        break;
    }
    default:
        dst->p = src->p;
        break;
    }
}

void func_0011B418(R11B008* self)
{
    switch (self->tag) {
    case 0x16: func_0011C5B0(self->p); break;
    case 0x17: func_0011C6C0(self->p); break;
    case 0x18: func_0011C7F0(self->p); break;
    case 0x19: func_0011C900(self->p); break;
    case 0x1A: func_0011CA20(self->p); break;
    }
}

void func_0011B4A8(const R11B008* self)
{
    switch (self->tag) {
    case 0x16: func_0011C580(self->p); break;
    case 0x17: func_0011C690(self->p); break;
    case 0x18: func_0011C7C0(self->p); break;
    case 0x19: func_0011C8D0(self->p); break;
    case 0x1A: func_0011C9E0(self->p); break;
    }
}

void func_0011B538(R11B008* self, s32 tag)
{
    func_0011B418(self);
    self->tag = tag;
}

void func_0011B570(R11B008* self, s32 value)
{
    func_0011B418(self);
    self->i = value;
    self->tag = 0x14;
}

void func_0011B5B0(R11B008* self, f32 value)
{
    func_0011B418(self);
    self->f = value;
    self->tag = 0x15;
}

void func_0011B5F0(R11B008* self, s32 flag)
{
    func_0011B418(self);
    if (flag != 0)
        self->i = 1;
    else
        self->i = 0;
    self->tag = 0x1B;
}

void func_0011B640(R11B008* self, void* p)
{
    func_0011B418(self);
    self->p = p;
    self->tag = 0x1C;
}

void func_0011B680(R11B008* self, s32 value)
{
    func_0011B418(self);
    self->i = value;
    self->tag = 0x1D;
}

void func_0011B6C0(R11B008* self, R11B008Node* node)
{
    func_0011B418(self);
    self->node = node;
    self->tag = 0x1E;
}

void func_0011B700(R11B008* self, R11AFC8* rec)
{
    func_0011B418(self);
    self->rec = rec;
    self->tag = 0x1F;
}

void func_0011B740(R11B008* self, f32* v)
{
    func_0011C580(v);
    func_0011B418(self);
    self->v = v;
    self->tag = 0x16;
}

void func_0011B788(R11B008* self, f32* v)
{
    (void)func_0011C690(v);
    func_0011B418(self);
    self->v = v;
    self->tag = 23;
}

void func_0011B7D0(R11B008* self, f32* v)
{
    (void)func_0011C7C0(v);
    func_0011B418(self);
    self->v = v;
    self->tag = 24;
}

void func_0011B818(R11B008* self, f32* v)
{
    (void)func_0011C8D0(v);
    func_0011B418(self);
    self->v = v;
    self->tag = 25;
}

void func_0011B860(R11B008* self, f32* v)
{
    (void)func_0011C9E0(v);
    func_0011B418(self);
    self->v = v;
    self->tag = 26;
}

void func_0011B8A8(R11B008* self, void* p)
{
    func_0011B418(self);
    self->p = p;
    self->tag = 0x20;
}

void func_0011B8E8(R11B008* self, s32 value)
{
    func_0011B418(self);
    self->tag = 0x21;
    self->i = value;
}

R11B008* func_0011B928(R11B008* out, const R11B008* in)
{
    if (in->tag == 0x14) {
        func_0011B018(out, in);
    } else {
        R11B008 tmp;
        func_0011B008(&tmp);
        func_0011B570(&tmp, (s32)in->f);
        func_0011B018(out, &tmp);
        func_0011B060(&tmp, 2);
    }
    return out;
}

R11B008* func_0011B9A8(R11B008* out, const R11B008* in)
{
    if (in->tag == 0x15) {
        func_0011B018(out, in);
    } else {
        R11B008 tmp;
        func_0011B008(&tmp);
        func_0011B5B0(&tmp, (f32)in->i);
        func_0011B018(out, &tmp);
        func_0011B060(&tmp, 2);
    }
    return out;
}

R11B008Node* func_0011BA28(S137290* rd)
{
    s32 tag = func_00137B90(rd);
    if (tag == 0xFF) {
        return 0;
    }
    s32 flag = tag & 0x80;
    R11B008Node* n = func_0011AF28();
    n->tag = tag & 0x7F;
    if (D_00275714) {
        func_00137BE0(rd);
        func_00137BE0(rd);
        func_00137BE0(rd);
        func_00137BE0(rd);
        func_00137BE0(rd);
    }
    switch (n->tag) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        break;
    case 20:
        func_0011B570(n, func_00137D78(rd));
        break;
    case 21:
        func_0011B5B0(n, func_00137DF8(rd));
        break;
    case 27:
        func_0011B5F0(n, func_00137C40(rd));
        break;
    case 32:
        func_0011B8A8(n, (void*)func_00137C40(rd));
        break;
    case 28:
        func_0011B640(n, (void*)func_00137C40(rd));
        break;
    case 29:
        func_0011B680(n, func_00137C40(rd));
        break;
    case 22:
    {
        s32 i = 2;
        f32* buf = (f32*)func_0011C508();
        f32* p = buf;
        do {
            *p++ = func_00137DF8(rd);
        } while (--i >= 0);
        n->tag = -1;
        func_0011B740(n, buf);
    }
        break;
    case 23:
    {
        s32 i = 15;
        f32* buf = (f32*)func_0011C618();
        f32* p = buf;
        do {
            *p++ = func_00137DF8(rd);
        } while (--i >= 0);
        n->tag = -1;
        func_0011B788(n, buf);
    }
        break;
    case 24:
    {
        s32 i = 2;
        f32* buf = (f32*)func_0011C748();
        f32* p = buf;
        do {
            *p++ = func_00137DF8(rd);
        } while (--i >= 0);
        n->tag = -1;
        func_0011B7D0(n, buf);
    }
        break;
    case 25:
    {
        f32* p = (f32*)func_0011C858();
        p[0] = func_00137DF8(rd);
        p[1] = func_00137DF8(rd);
        n->tag = -1;
        func_0011B818(n, p);
    }
        break;
    case 26:
    {
        f32* p = (f32*)func_0011C968();
        p[0] = func_00137DF8(rd);
        p[1] = func_00137DF8(rd);
        p[2] = func_00137DF8(rd);
        n->tag = -1;
        func_0011B860(n, p);
    }
        break;
    case 30:
        func_0011B6C0(n, func_0011BA28(rd));
        break;
    }
    if (flag) {
        n->next = func_0011BA28(rd);
    } else {
        n->next = 0;
    }
    return n;
}

R11B008* func_0011BD28(R11B008* out, R11B008List* list, s32 key, const R11B008* value)
{
    R11B008 tmp;
    func_0011B008(&tmp);
    R11B008Key* node = func_0011C498();
    node->key = key;
    (void)func_0011B0A8(&node->value, value);
    node->next = list->head;
    list->head = node;
    func_0011B538(&tmp, 0x22);
    func_0011B018(out, &tmp);
    func_0011B060(&tmp, 2);
    return out;
}

R11B008* func_0011BDD0(R11B008* out, R11B008List* list, s32 key, const R11B008* value)
{
    R11B008 tmp;
    R11B008Key* node = list->head;
    while (node != 0) {
        if (node->key == key) {
            func_0011B008(&tmp);
            (void)func_0011B0A8(&node->value, value);
            func_0011B538(&tmp, 0x22);
            func_0011B018(out, &tmp);
            func_0011B060(&tmp, 2);
            goto done;
        }
        node = node->next;
    }
    func_0011B008(&tmp);
    func_0011B538(&tmp, 0x22);
    func_0011B018(out, &tmp);
    func_0011B060(&tmp, 2);
done:
    return out;
}

s32 func_0011BE90(R11B008List* list, s32 key, R11B008* out)
{
    R11B008Key* n = list->head;
    while (n != 0) {
        if (n->key == key) {
            if (out != 0) {
                func_0011B0A8(out, &n->value);
            }
            return 1;
        }
        n = n->next;
    }
    return 0;
}

void func_0011BEE0(R11B008List* self, R11B008List* out)
{
    R11B008Key* copy = func_0011C498();
    func_0011C418(self->head, copy, 0);
    out->head = copy;
}

R11B008List* func_0011BF30(void)
{
    R11B008List* p = (R11B008List*)func_0018D5C0(4);
    func_001F5C0C(p, 0, 4);
    return p;
}

void func_0011BF70(void)
{
    func_0011A6A8(D_00259F38);
    func_0011C128(&D_0025C250, 0xC, 0x2000);
    D_0025C250.removeCallback = (void*)func_0011AF78;
    func_0011C128(&D_0025C270, 0x1C, 0x190);
    D_0025C270.removeCallback = (void*)func_0011A670;
    func_0011C128(&D_0025C290, 0x10, 0x800);
    D_0025C290.removeCallback = (void*)func_0011C4E8;
    func_0011C128(&D_0025C2B0, 0x14, 0x800);
    func_0011CA90();
    func_0011C128(&D_0025C2D0, 0xC, 0x80);
}

void func_0011C040(void)
{
    func_0011C1D0(&D_0025C250);
    func_0011C1D0(&D_0025C270);
    func_0011C1D0(&D_0025C290);
    func_0011C1D0(&D_0025C2B0);
    func_0011CBB0();
    func_0011C1D0(&D_0025C2D0);
    func_0011A6B8(D_00259F38);
}
