// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "c28.h"
#include "c29.h"
#include "flagged_object.h"
#include "object_gatherer.h"
#include "c6c.h"
#include "g261858.h"
#include "s1bc320.h"

extern const u32 D_00247AA0;
s32 D_002613F4;
extern s32 D_002613F8[6];
s32 func_0011E138(void*, void*, void*, void*);
s32 func_0011E1F8(s32);
s32 func_0011E2E8(void);
void func_00140C28(void* a, void* b, void* c)
{
	s32 result;
	do {
		result = func_0011E138(a, b, c, (void*)&D_00247AA0);
		D_002613F4 = result;
		if (result != 1) { func_0011E1F8(0); D_002613F8[0] = func_0011E2E8(); }
	} while (result != 1);
}

s32 func_00203B18(void*, void*, void*, void*);
s32 func_002032C8(s32);
s32 func_00203D90(void);
void func_00140CC8(void* a, void* b, void* c)
{
	s32 result;
	do {
		result = func_00203B18(a, b, c, (void*)&D_00247AA0);
		D_002613F4 = result;
		if (result != 1) { func_002032C8(0); D_002613F8[0] = func_00203D90(); }
	} while (result != 1);
}

s32 func_001C1A28(void* a, void* b);

struct Self_140550 {
    u8 pad0[0x598];
    s32 f598;
    void* f59C[32];
};

s32 func_00140550(Self_140550* self, void* arg)
{
    for (s32 i = 0; i < self->f598; i++) {
        if (func_001C1A28(arg, &self->f59C[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

void func_0013EB30(void* p);
void func_00140640(void* a, void* b, void* c);

void func_00140688(void* self, void* b)
{
    func_00140640((u8*)self + 0x5C0, self, b);
}

void func_0013EB30(void* p);

void func_00140750(void* self)
{
    func_0013EB30((u8*)self + 0x554);
}

void func_001409D8(void) {}

s32 func_00141008(u8* bits, s32 index)
{
    s32 mask = 1 << (index & 7);
    bits += index / 8;
    return (bits[0xC] & mask) != 0;
}

void func_001419C0(FlaggedObject* obj, void* item)
{
    s32 n = obj->nIdsA;
    obj->idsA[n] = (s32)item;
    obj->nIdsA = n + 1;
}

void func_001430C0(void** dst, void* value)
{
    *dst = value;
}

extern f32 D_00261850;
void func_001430C0(void* dst, s32 value);

void func_00142ED0(f32 x)
{
    D_00261850 = x;
    func_001430C0(&D_00261858, x > 0.0f ? 1 : 0);
}

extern f32 D_00261850;
extern f32 D_00261854;
s64 func_001430F8(void);
f32 func_001FB6B0(s64 value);

void func_00142F10(G261858* self)
{
    s64 now = func_001430F8();
    s64 delta = now - self->last;
    u64 half = (u64)delta >> 1;
    f32 t;
    if (delta >= 0) {
        t = func_001FB6B0(delta);
    } else {
        t = func_001FB6B0((delta & 1) | half);
        t = t + t;
    }
    f32 dt = t * 0.0000000033908420f;
    f32 lo = 0.016666668f;
    f32 hi = 0.033333335f;
    if (dt < lo) {
        dt = lo;
    } else if (hi < dt) {
        dt = hi;
    }
    self->step = dt;
    f32 s = 0.0f;
    if (self->running) {
        s = dt;
    }
    s = s * (D_00261854 * D_00261850);
    if (0.016666668f <= s) {
        self->step = s;
    }
    f32 new_a = self->time + s;
    f32 old_b = self->dt;
    f32 new_d = self->f10 + self->step;
    self->time = new_a;
    self->f0C = old_b;
    self->dt = s;
    self->f10 = new_d;
    self->last = now;
}

s64 func_001430F8(void);
f32 func_001FB6B0(s64 value);

void func_00143030(G261858* self)
{
    s64 now = func_001430F8();
    s64 delta = now - self->last;
    u64 half = (u64)delta >> 1;
    f32 t;
    if (delta >= 0) {
        t = func_001FB6B0(delta);
    } else {
        t = func_001FB6B0((delta & 1) | half);
        t = t + t;
    }
    f32 dt = t * 0.0000000033908420f;
    self->last = now;
    self->step = dt;
    self->f10 = self->f10 + dt;
}

void func_001430B8(G261858* self, f32 value)
{
    self->time = value;
}

extern s32 D_002613EC;

void func_00140790(void)
{
    D_002613EC = 3;
}

struct Holder_1407A0 { u8 pad[0x4]; s32 value; };

s32 func_001407A0(Holder_1407A0* holder)
{
    return holder->value;
}

extern s32 D_002613F0;
void func_00203A20(s32 arg);

void func_001409A8(void)
{
    if (D_002613F0 == 0x14) {
        func_00203A20(2);
    }
}

void func_001405D0(void* a, void* b, int c);

void func_00140618(void* self, int value)
{
    func_001405D0((u8*)self + 0x5C0, self, value);
}

void func_0013E8F8(void* a, int b);

void func_00140640(void* self, void* unused, int value)
{
    func_0013E8F8((u8*)self + 0x90, value);
}

void func_00140640(void* self, void* unused, int value);

void func_00140660(C28* self, int value)
{
    func_00140640(&self->zone, self, value);
}

void func_001406B0(C28* list, s32 value)
{
    list->idsIn[list->countIdsIn++] = value;
}

void func_001BA130(C03* self);
void* func_00183058(void* item, void* x, FlaggedObject* self);

void func_001415D0(FlaggedObject* self)
{
    s32 keepB = self->flagIndex;
    s32 keepA = self->ordinal;
    func_001BA130(self);
    self->flagIndex = keepB;
    self->ordinal = keepA;
    for (s32 i = 0; i < self->countA; i++) {
        self->objsA[i] = func_00183058(self->objsA[i], self->world, self);
    }
    for (s32 j = 0; j < self->countB; j++) {
        self->objsB[j] = func_00183058(self->objsB[j], self->world, self);
    }
}

extern u8 D_00262C70[];

void func_00141870(FlaggedObject* self);
s32 func_001925F0(void* self, S1BC320* ev);
s32 func_001BC320(void* self, S1BC320* ev);
void func_0016EC38(void* p, f32 f, s32 n);

s32 func_001417F0(FlaggedObject* self, S1BC320* ev)
{
    s32 r = func_001925F0(self, ev);
    if (ev->type == r) {
        if ((ev->f10 & 0x10) == 0) {
            func_0016EC38(D_00262C70, 0.2f, 2);
        }
        func_00141870(self);
        return 1;
    }
    return func_001BC320(self, ev);
}

extern u8 D_00261EF0[];
extern u8 D_00261420[];

void func_00151ED8(void* table, FlaggedObject* self);
s32 func_00141008(void* table, s32 v);
void func_00141040(void* table, s32 v);
s32 func_00182F40(s32 v, FlaggedObject* self);
void func_00140E10(void* table, s32 a, s32 idx);
void func_0012C7B0(void* p, s32 a, s32 b, s32 c, f32 x, f32 y);
void func_001B64D8(void* p, s32 n);

void func_00141870(FlaggedObject* self)
{
    func_00151ED8(D_00261EF0, self);
    s32 sel;
    if (self->handle != 0) {
        sel = func_00141008(D_00261420, self->flagIndex) ? 0x549 : 0x548;
    }
    s32 idx = -1;
    func_00141040(D_00261420, self->flagIndex);
    if (func_00182F40((s32)self->child, self)) {
        for (C01* n = self; n != 0; n = n->parent) {
            Alias01* sl = n->alias;
            if (sl != 0) {
                idx = sl->id;
            }
        }
        if (idx == -1) {
            idx = self->id;
        }
    }
    func_00140E10(D_00261420, self->childId, idx);
    for (s32 i = 0; i < self->countA; i++) {
        func_0012C7B0(self->objsA[i], 0, 0, 0, 0.0f, 1.0f);
    }
    if (self->handle != 0) {
        func_001B64D8(self->handle, sel);
    }
}

void func_001419A0(FlaggedObject* q, s32 value)
{
    q->idsB[q->nIdsB++] = value;
}

void func_001406D0(C28* self, s32 value)
{
    s32 n = self->countIdsOut;
    self->idsOut[n] = value;
    self->countIdsOut = n + 1;
}

void func_001406F0(C28* self, s32 value)
{
    s32 n = self->countKindsIn;
    self->kindsIn[n] = value;
    self->countKindsIn = n + 1;
}

void func_001419E0(FlaggedObject* self, s32 value)
{
    self->childId = value;
}

void func_00124A48(void* self);
void func_0013EA38(void* p);
void func_00140238(C29* self, s32 flag);
void* func_0015A448(void* obj, s32 id, void* ctx);


void func_00140140(C29* self)
{
    func_00124A48(self);
    func_0013EA38(&self->zone);
    func_00140238(self, 0);
    for (s32 i = 0; i < self->countIds; i++) {
        void* p = func_0015A448(self->world, self->ids[i], self);
        if (p != 0) {
            s32 n = self->countObjs;
            self->objs[n] = (s32)p;
            self->countObjs = n + 1;
        }
    }
    if (self->countIds == 0) {
        self->f5BC = 1;
    }
}

void func_001BA130(void* self);


void func_00140200(C29* self)
{
    s32 saved = self->zone.id120;
    func_001BA130(self);
    self->zone.id120 = saved;
    self->zone.owner = self;
}

extern u8 D_00275B04[];
extern u8 D_00275F80[];

void func_001EFFA0(void* dst, void* args, s32 count);

struct Args_140ED0 {
    s32 kind;
    void* text;
    s32 x;
    s32 y;
    s32 z;
};

struct Ring_140ED0 {
    u8 pad0[0x424];
    s32 field424;
    s32 field428;
    s32 field42C;
};

void func_00140ED0(Ring_140ED0* r)
{
    Args_140ED0 args;
    args.kind = 1;
    args.text = D_00275B04;
    if (r->field42C != 0) {
        args.x = r->field424;
        args.y = r->field428;
        args.z = 0x11;
    } else {
        args.x = -1;
        args.y = -1;
        args.z = 0x10;
    }
    func_001EFFA0(D_00275F80, &args, 1);
}

typedef signed int s32;
typedef unsigned char u8;

extern void func_0013EB68(void* state);

void func_00140238(C29* self, s32 flag)
{
    func_0013EB68(&self->zone);
}

typedef signed int s32;
typedef unsigned char u8;

void func_0013E8F8(void* a, s32 b);

void func_001405D0(void* a, void* b, s32 c)
{
    func_0013E8F8((u8*)a + 0x8, c);
}

struct Ctr_140FF8 { u8 pad0[4]; s32 count; };

s32 func_00140FF8(void* p)
{
    Ctr_140FF8* c = (Ctr_140FF8*)p;
    c->count = c->count + 1;
    return c->count;
}

s32 func_00142B78(void* a, void* b, void* c, void* d, s32 e, s32 f, f32 x);
s32 func_00142170(void* a, void* b, void* c, void* d, s32 e, f32 fa, f32 fb);

struct Self_141D00 {
    u8 pad0[0x3CC];
    f32 f3CC;
    u8 pad1[0x3F8 - 0x3D0];
    s32 f3F8;
    u8 pad2[0x538 - 0x3FC];
    u64 f538;
};

s32 func_00141D00(Self_141D00* self, void* p1, void* p2, f32 x, void* p3, s32 p4)
{
    if (self->f3F8 != 0) {
        return func_00142B78((u8*)self + 0x3F0, (u8*)self + 0x3A4, p1, p2, (s32)p3, p4, x);
    }
    if (self->f538 & ((u64)0x8000 << 25)) {
        return func_00142170((u8*)self + 0x140, p1, p2, p3, p4, self->f3CC, x);
    }
    return 0;
}

// Newly matched US functions from the small-function wave.
extern void func_0013EB30(void*);
extern s32 func_0011E1F8(s32);
extern void func_001439A8(void*);
extern void func_001439C8(void*);
extern void func_001439E8(void*);
extern void func_00143A08(void*);
extern void* D_00261990;
extern void func_001448C8(void*, s32, void*);

void func_00140710(C28* self, void* value)
{
    s32 i = self->countKindsOut;
    u32 address = (u32)self + (u32)(i << 2);
    *(u32*)(address + 0x790) = (u32)value;
    self->countKindsOut = i + 1;
}

void func_00140730(void* self, void* value)
{
    s32 i = *(s32*)((u8*)self + 0x550);
    u32 address = (u32)self + (u32)(i << 2);
    *(u32*)(address + 0x554) = (u32)value;
    *(s32*)((u8*)self + 0x550) = i + 1;
}

void func_00140770(void* self) { func_0013EB30((u8*)self + 0x5C0); }

s32 func_00140D68(s32 value) { s32 result = func_0011E1F8((u32)value < 1u); return result == 0; }

void func_001405F0(u8* self, s32 value)
{
    func_001405D0(self + 0x554, self, value);
}

struct __attribute__((aligned(16))) Quad_00141170 { f32 v[4]; };
void func_001F3B48(void* self, void* value, void* out);
s32 func_001E4DC0(void* self, void* value);
s32 func_00141170(ObjectGatherer* self, void* value)
{
    Quad_00141170 local;
    func_001F3B48(self, value, &local);
    return func_001E4DC0(self->f8C, &local);
}


void func_001BAC30(void* self);
void func_0013E950(void* p, void* self);

void func_00140100(C29* self)
{
    func_001BAC30(self);
    func_0013E950(&self->zone, self);
    if (self->f790 != 0) {
        self->zone.f13C = 1;
    }
}

s32 func_001BC320(void* self, void* ev);
void func_0013F6F8(C28* state, s32 mode);

s32 func_00140028(C28* a0, void* a1)
{
    s32 r = func_001BC320(a0, a1);
    if (r != 0 && (*(s32*)((u8*)a1 + 0xC) & 4) == 0 && a0->state == 3 && a0->zone.mode == 0) {
        func_0013F6F8(a0, 1);
    }
    return r;
}

void func_00137EB0(void* a, void* b);
void func_00137E70(void* a, void* b);
s32 func_001E4C48(void*, void*, void*, void*, void*);
void func_0011EC40(void* a, void* b);

void func_00141108(void* a0, void* a1)
{
    func_00137EB0(a1, (u8*)a0 + 0x50);
    func_00137E70(a1, (u8*)a0 + 0x40);
    func_001E4C48(a1, (u8*)a0 + 0x80, (u8*)a0 + 0x84, (u8*)a0 + 0x88, (u8*)a0 + 0x8C);
    func_0011EC40(a0, a1);
}

extern u8 D_00261420[];
s32 func_00140FF8(void* p);
void func_001B7968(C03* self);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

void func_001411A8(FlaggedObject* self)
{
    func_001B7968(self);
    self->flagIndex = func_00140FF8(D_00261420);
    self->childId = -1;
    C6C* in = self->world;
    s32 n = in->count2304;
    self->ordinal = n;
    n = n + 1;
    in->count2304 = n;
    func_001B9AE0(self, 3, 0, 3, 0);
}

s32 func_0013DFD8(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
s32 func_00141F48(void* a, void* b, void* c, s32 d, s32 e, f32 x);

s32 func_00141C28(C03* self, void* a1, void* a2, s32 a3, s32 a4)
{
    if (self->tree.nodes != 0) {
        return func_0013DFD8((void*)self->tree.nodes, a1, a2, 0, a3, (void*)a4);
    }
    if (self->flags538 & ((u64)0x8000 << 25)) {
        return func_00141F48((u8*)self + 0x140, a1, a2, a3, a4, self->radius3CC);
    }
    return 0;
}

s32 func_0013DFD8(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
s32 func_00141F48(void* a, void* b, void* c, s32 d, s32 e, f32 x);

struct Self_141C90 {
    u8 pad0[0x3CC];
    f32 f3CC;
    u8 pad1[0x538 - 0x3D0];
    u64 f538;
};

s32 func_00141C90(Self_141C90* self, void* a1, void* a2, void* a3, s32 a4, void* a5)
{
    if (a1 != 0) {
        return func_0013DFD8(a1, a2, a3, 0, a4, a5);
    }
    if (self->f538 & ((u64)0x8000 << 25)) {
        return func_00141F48((u8*)self + 0x140, a2, a3, a4, (s32)a5, self->f3CC);
    }
    return 0;
}

void func_001249A8(void* self);
void* func_0015A448(void* host, s32 id, void* ctx);

void func_00141338(FlaggedObject* self)
{
    func_001249A8(self);
    s32 i = 0;
    while (i < self->nIdsA) {
        void* r = func_0015A448(self->world, self->idsA[i], self);
        if (r != 0) {
            s32 k = self->countA;
            self->objsA[k] = r;
            self->countA = k + 1;
        }
        i++;
    }
    i = 0;
    while (i < self->nIdsB) {
        void* r = func_0015A448(self->world, self->idsB[i], self);
        if (r != 0) {
            s32 k = self->countB;
            self->objsB[k] = r;
            self->countB = k + 1;
        }
        i++;
    }
}

struct BitSet_141040 {
    u8 pad0[8];
    s32 count;
    u8 bits[0x20C - 0xC];
    s32 flag;
};

void func_00141040(BitSet_141040* self, s32 bit)
{
    u8* base = self->bits;
    u8* byte = base + bit / 8;
    s32 mask = 1 << (bit & 7);
    s32 cur = *byte & mask;
    if (cur == 0) {
        self->flag = 1;
        goto done;
    }
done:
    if (!(*byte & mask)) {
        *byte = (u8)(*byte | mask);
        self->count++;
    }
}

void func_001410A0(BitSet_141040* self, s32 bit)
{
    u8* base = self->bits;
    u8* byte = base + bit / 8;
    s32 mask = 1 << (bit & 7);
    s32 cur = *byte & mask;
    if (cur != 0) {
        self->flag = 1;
        goto done;
    }
done:
    if ((*byte & mask) != 0) {
        *byte = (u8)(*byte & ~mask);
        self->count--;
    }
}

struct Blk_140F48 { s32 b[0x81]; };

void func_00140F48(u8* p)
{
    *(s32*)(p + 4) = 0;
    *(Blk_140F48*)(p + 8) = *(Blk_140F48*)(p + 0x220);
    *(s32*)(p + 0x20C) = 0;
}

struct Blk_140E10 { u8 b[0x200]; s32 tail; };

struct Ring_140E10 {
    u8 pad0[8];
    Blk_140E10 src;
    s32 tail1;
    u8 pad1[0x10];
    Blk_140E10 dst;
    s32 field424;
    s32 field428;
    s32 field42C;
};

void func_00140E10(Ring_140E10* r, s32 a, s32 b)
{
    r->tail1 = 0;
    r->dst = r->src;
    r->field424 = a;
    r->field428 = b;
    r->field42C = 1;
}

struct Frame_141210;

struct Frame_141210 {
    void* list;
    void* cursor;
    s32 next_off;
    Frame_141210* prev;
    Frame_141210(List01* l)
    {
        list = l;
        cursor = l;
        next_off = l->offset;
        prev = (Frame_141210*)D_0027B314;
        D_0027B314 = (ListFrame*)this;
    }
    ~Frame_141210() { D_0027B314 = (ListFrame*)prev; }
};

extern u32 D_00261410[4];
void func_001BAC30(C03* self);
void func_00124DF8(void* self, s32 a, void* b);
s32 func_001300E8(void* node, s32 kind);
void func_00182ED8(void* node);

void func_00141210(FlaggedObject* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 1, D_00261410);

    Frame_141210 frame(&self->children);
    void* head = *(void**)((u8*)self + 0x34);
    frame.cursor = (void*)((s32)head + frame.next_off);
    void* node = head;
    if (node != 0) {
        do {
            if (func_001300E8(node, 0x7B)) {
                s32 n = self->countB;
                self->objsB[n] = node;
                self->countB = n + 1;
            } else {
                if (!func_001300E8(node, 0x83)) {
                    goto skip;
                }
                s32 n = self->countA;
                self->objsA[n] = node;
                self->countA = n + 1;
            }
            func_00182ED8(node);
skip:
            void* next = *(void**)frame.cursor;
            frame.cursor = (void*)((s32)next + frame.next_off);
            node = next;
        } while (node != 0);
    }
}

struct Entry_141B48 { u8 pad[0x538]; u64 bits; };

s32 func_00141C28(void* a0, void* a1, void* a2, s32 a3, s32 a4);
s32 func_001429F8(s32 a0, s32 a1);

s32 func_00141B48(void* a0, void* a1, s32 count, Entry_141B48** list, s32 a4, s32 a5)
{
    s32 result = 0;
    if (count > 0) {
        const u64 mask = 0xC000ULL << 28;
        Entry_141B48** p = list;
        s32 n = count;
        do {
            Entry_141B48* e = *p;
            if ((e->bits & mask) == 0) {
                s32 r = func_00141C28(e, a0, a1, a4 - result, a5 + result * 0x70);
                if (r != 0) {
                    if (result != 0) {
                        r = func_001429F8(result + r, a5);
                    }
                    result = r;
                }
            }
            n--;
            p++;
        } while (n != 0);
    }
    return result;
}


void func_0013E918(Zone28* p);

void func_001400A8(C29* self)
{
    u64 m = 0x8000;
    func_001B7968(self);
    func_0013E918(&self->zone);
    m <<= 28;
    self->flags538 = self->flags538 | m;
    func_001B9AE0(self, 3, 0, 3, 0);
}

extern u8 D_002701B8[];
extern const u32 D_00247AA4;
extern const u32 D_00247AA8[2];
extern const u32 D_00247AA0;
extern u8 D_0026FF68[];
extern u8 D_0027B800[];
extern u32 D_002476A0[];

s32 func_00203EE0(s32 a0, s32* out);
s32 func_00140968(void);
s32 func_00140D68(s32 value);
void func_00194D30(void* self, s32 a, s32 b);
s32 func_0011E138(s32 a0, s32 a1, void* a2, void* a3);

void func_001409E0(void)
{
    s32 tmp[1];
    s32 s1;
    switch (D_002613EC) {
    case 3:
        if (func_00203EE0(2, tmp) != 0) {
            if (tmp[0] != 0) {
                if (func_00140968() == 0) {
                    func_00194D30(D_0026FF68, 2, 0x16);
                    D_002613EC = 1;
                }
            }
        }
        break;
    case 1:
        s1 = *(s32*)D_002701B8;
        if (s1 == 2) {
            if (func_00140968() != 0) {
                if (func_0011E138((s32)D_00247AA4, 1, D_0027B800, (void*)&D_00247AA0) == 1) {
                    D_002613EC = s1;
                }
            }
        }
        break;
    case 2:
        if (func_00140D68(0) != 0) {
            u8* p = D_0027B800;
            u32* tbl = D_002476A0;
            u32 crc = 0xFFFFFFFF;
            s32 n = 0x7FF;
            do {
                crc = *(u32*)((u8*)tbl + (((crc ^ *p) & 0xFF) << 2)) ^ (crc >> 8);
                p++;
                n--;
            } while (n != -1);
            if ((s32)crc != (s32)D_00247AA8[0]) {
                D_002613EC = 1;
            } else {
                func_00194D30(D_0026FF68, 2, -1);
                D_002613EC = 3;
            }
        }
        break;
    }
}

struct Buf_140B60 { char b[256]; };
struct Obj_140B60 { u8 pad; };

extern const u16 D_00249E20[4];
extern const char D_00249E28[8];
extern const char D_00249E30[8];
extern const char D_00249E38[4];

void* func_001E2180(Buf_140B60* dst, void* src);
s32 func_001407A8(Buf_140B60* p);
s32 func_001E2100(Buf_140B60* p);
s32 func_001E1FD0(Obj_140B60* dst, const char* fmt, ...);

void func_00140B60(void* self, void* a1, s32 flag)
{
    char buf[256];
    *(u16*)buf = D_00249E20[0];
    func_001E2180((Buf_140B60*)buf, a1);
    s32 n = func_001407A8((Buf_140B60*)buf);
    char* p = buf;
    for (s32 i = 1; i < n; i++) {
        p[func_001E2100((Buf_140B60*)p)] = 0x5C;
    }
    func_001E1FD0((Obj_140B60*)self, D_00249E28,
                  flag ? (void*)D_00249E30 : (void*)D_00249E38, buf);
}

struct Obj_1419E8;
struct __attribute__((aligned(16))) Rec_1419E8 { u8 pad[0x40]; f32 key; u8 rest[0x2C]; };

extern f32 D_00249E44;
s32 func_00141C28(Obj_1419E8* self, void* a1, void* a2, s32 a3, Rec_1419E8* out);

Obj_1419E8* func_001419E8(s32 flags, void* a1, void* a2, s32 count, Obj_1419E8** list, Rec_1419E8* out)
{
    f32 bestKey = D_00249E44;
    Obj_1419E8* best = 0;
    Rec_1419E8 buf[2];
    for (s32 i = 0; i < count; i++) {
        Obj_1419E8* obj = list[i];
        s32 n = func_00141C28(obj, a1, a2, 2, buf);
        s32 idx = 0;
        if (n > 0 && buf[0].key == 0.0f) {
            if (flags & 1) idx = 1;
        }
        if (idx < n && buf[idx].key < bestKey) {
            bestKey = buf[idx].key;
            best = obj;
            if (out != 0) {
                *out = buf[idx];
            }
        }
    }
    return best;
}

void func_001E2218(s8* p);
s32 func_001E2100(const s8* s);
void* func_001E2180(s8* dst, const char* src);

s32 func_001407A8(s8* path)
{
    func_001E2218(path);
    s32 len = func_001E2100(path);
    if (len != 0) {
        s8 last = path[len - 1];
        if (last != '\\' && last != '/') {
            func_001E2180(path, ";1");
            len = func_001E2100(path);
        }
    }
    s8* end = path + len;
    s8* out = path;
    s8* in = path;
    s32 count = 0;
    s32 n = 0;
    s32 max = 8;
    while (in < end) {
        switch (*in) {
        case '/':
        case '\\':
            if (n != 0) {
                *out++ = 0;
                n = 0;
                max = 8;
                count++;
            }
            break;
        case '.':
            if (n != 0 && max == 8) {
                *out++ = *in;
                n = 0;
                max = 3;
            }
            break;
        case ';':
            if (n != 0 && in == end - 2 && in[1] == '1') {
                *out++ = *in++;
                *out++ = *in;
                n += 2;
                break;
            }
        default:
            if (n < max) {
                if ((u8)(*in - 'A') < 26 || (u8)(*in - '0') < 10) {
                    *out++ = *in;
                } else {
                    *out++ = '_';
                }
                n++;
            }
            break;
        }
        in++;
    }
    if (n != 0) {
        *out = 0;
        count++;
    }
    return count;
}

struct Key_142998 { f32 f; s32 i; };

s32 func_00142998(Key_142998* a, Key_142998* b)
{
    f32 d = a->f - b->f;
    if (d < -0.0001f)
        return -1;
    if (0.0001f < d)
        return 1;
    return a->i - b->i;
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001493C0();
void func_001496C0();
void func_00149760();
void func_0014A7B8();
void func_0014A8D0();
void func_0014A8F8();
void func_0014AA90();
void func_0014AA98();
void func_0014AAA0();
void func_001E2E68();
void func_001E30A0();
void func_001E30D8();
void func_001E30E0();
void func_001E31F0();
typedef void (*Fn_Table)();
extern const Fn_Table D_00217398[6] = { 0, 0, 0, 0, (Fn_Table)func_001493C0, 0 };
extern const Fn_Table D_002173B0[6] = { (Fn_Table)func_001496C0, (Fn_Table)func_0014A7B8, 0, 0, (Fn_Table)func_00149760, 0 };
extern const Fn_Table D_002173C8[6] = { (Fn_Table)func_0014A8D0, 0, 0, 0, (Fn_Table)func_0014A8F8, 0 };
extern const Fn_Table D_002173E0[6] = { (Fn_Table)func_0014AA90, (Fn_Table)func_0014AA98, 0, 0, (Fn_Table)func_0014AAA0, 0 };
extern const Fn_Table D_002173F8[6] = { (Fn_Table)func_001E2E68, (Fn_Table)func_001E30A0, (Fn_Table)func_001E30D8, (Fn_Table)func_001E30E0, (Fn_Table)func_001E31F0, 0 };

struct List_141438 { u8* head; u8 pad4[4]; s32 offset; };
struct Iter_141438 { List_141438* list; u8* link; s32 offset; Iter_141438* saved; };
struct Next_141438 {
    static u8* Of(Iter_141438* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
};
struct Begin_141438 {
    static void Of(Iter_141438* it, List_141438* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_141438*)((void*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

extern u8 D_00261420[];
void func_00124A48(FlaggedObject* self);
void func_00182ED8(s32 a);
s32 func_001300E8(u8* node, s32 kind);
s32 func_00183438(u8* node);

s32 func_00141008(u8* t, s32 v);
void* func_001B6290(void* a, void* b, s32 c, s32 d);

void func_00141438(FlaggedObject* self)
{
    func_00124A48(self);
    for (s32 i = 0; i < self->countA; i++)
        func_00182ED8((s32)self->objsA[i]);
    for (s32 i = 0; i < self->countB; i++)
        func_00182ED8((s32)self->objsB[i]);
    if (self->childId == -1) {
        Iter_141438 it;
        u8* obj;
        Begin_141438::Of(&it, (List_141438*)&self->children);
        while ((obj = Next_141438::Of(&it)) != 0) {
            if (func_001300E8(obj, 0x74) != 0) {
                self->childId = func_00183438(obj);
                if (self->childId == -1)
                    self->childId = *(s32*)(obj + 8);
                self->child = obj;
            }
        }
        D_0027B314 = (ListFrame*)it.saved;
    } else {
        self->child = func_0015A448(self->world, self->childId, self);
    }
    if (self->f5A8 != 0) {
        self->handle = (S1B6290*)func_001B6290(self->f5A8, self, 0x546, 0);

        if (func_00141008(D_00261420, self->flagIndex) != 0)
            func_001B64D8(self->handle, 0x547);
    }
}

struct __attribute__((aligned(16))) Quad_1429F8 { s32 a, b, c, d; };

struct Event_1429F8 {
    f32 time;
    s32 end;
    u8 pad0[8];
    Quad_1429F8 q10;
    Quad_1429F8 q20;
};

struct Span_1429F8 {
    Quad_1429F8 q[4];
    f32 time[2];
    s32 f48;
    u8 pad0[0x70 - 0x4C];
};

void func_0018D608(void);
Event_1429F8* func_0018D658(s32 size);
void func_0018D6F0(void);
void func_001F5CD0(Event_1429F8* base, s32 n, s32 size, s32 (*cmp)(const void*, const void*));
s32 func_00142998(const void* a, const void* b);

s32 func_001429F8(s32 count, Span_1429F8* spans)
{
    Event_1429F8* mem;
    Event_1429F8* rec;
    Event_1429F8* end;
    Span_1429F8* dst;
    s32 i;
    s32 j;
    s32 depth;

    func_0018D608();
    mem = func_0018D658(count * 0x60);
    rec = mem;
    for (i = 0; i < count; i++) {
        for (j = 0; j < 2; j++) {
            rec->end = j;
            rec->time = spans[i].time[j];
            rec->q10 = spans[i].q[j];
            rec->q20 = spans[i].q[j + 2];
            rec++;
        }
    }

    func_001F5CD0(mem, count * 2, 0x30, func_00142998);

    dst = spans;
    end = rec;
    rec = mem;
    depth = 0;
    while (rec < end) {
        if (rec->end == 0) {
            depth++;
            if (depth == 1) {
                dst->time[0] = rec->time;
                dst->q[0] = rec->q10;
                dst->q[2] = rec->q20;
                dst->f48 = 4;
            }
        } else {
            depth--;
            if (depth == 0) {
                dst->time[1] = rec->time;
                dst->q[1] = rec->q10;
                dst->q[3] = rec->q20;
                dst++;
            }
        }
        rec++;
    }

    func_0018D6F0();
    return dst - spans;
}

u32 D_00261410[4] = { 2, 0x545, 0x5A8, 0 };
s32 D_002613F8[6] = { 0, 0, 0, 0, 0, 0 };
extern const u32 D_00247AA0 = 0x17F;
extern const u32 D_00247AA4 = 0x14E0EF;
extern const u32 D_00247AA8[2] = { 0x2E774159, 0 };
extern const u16 D_00249E20[4] = { 0x5C, 0, 0, 0 };
extern const char D_00249E28[8] = "%s\\%s";
extern const char D_00249E30[8] = "cdrom0:";
extern const char D_00249E38[4] = "";
