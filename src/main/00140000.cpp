// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern u8 D_00247AA0[];
extern s32 D_002613F4;
extern s32 D_002613F8;
s32 func_0011E138(void*, void*, void*, void*);
s32 func_0011E1F8(s32);
s32 func_0011E2E8(void);
void func_00140C28(void* a, void* b, void* c)
{
	s32 result;
	do {
		result = func_0011E138(a, b, c, D_00247AA0);
		D_002613F4 = result;
		if (result != 1) { func_0011E1F8(0); D_002613F8 = func_0011E2E8(); }
	} while (result != 1);
}

s32 func_00203B18(void*, void*, void*, void*);
s32 func_002032C8(s32);
s32 func_00203D90(void);
void func_00140CC8(void* a, void* b, void* c)
{
	s32 result;
	do {
		result = func_00203B18(a, b, c, D_00247AA0);
		D_002613F4 = result;
		if (result != 1) { func_002032C8(0); D_002613F8 = func_00203D90(); }
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

struct Obj_1419C0 {
    u8 pad[0x550];
    s32 count;
    void* items[1];
};

void func_001419C0(Obj_1419C0* obj, void* item)
{
    s32 n = obj->count;
    obj->items[n] = item;
    obj->count = n + 1;
}

void func_001430C0(void** dst, void* value)
{
    *dst = value;
}

extern void* D_00261990;
void func_00143968(void* arg);

void func_001437E8(void)
{
    func_00143968(D_00261990);
}

extern void* D_00261990;
void func_00143A38(void* arg);

void func_001438D8(void)
{
    func_00143A38(D_00261990);
}

struct Obj_1439A8 {
    u8 pad[0x1F8];
    f32 value;
};
void func_00143560(void* self);

void func_001439A8(Obj_1439A8* self, f32 value)
{
    self->value = value;
    func_00143560(self);
}

struct Obj_143AF0 {
    u8 pad[0x340];
    s32 field;
};

void func_00143AF0(Obj_143AF0* obj)
{
    obj->field = 0;
}

extern f32 D_00261850;
extern s32 D_00261858;
void func_001430C0(void* dst, s32 value);

void func_00142ED0(f32 x)
{
    D_00261850 = x;
    func_001430C0(&D_00261858, x > 0.0f ? 1 : 0);
}

struct Timer_00142F10 {
    s32 running;
    f32 acc_a;
    f32 hist_b;
    f32 hist_c;
    f32 acc_d;
    f32 step;
    s64 last;
};

extern f32 D_00261850;
extern f32 D_00261854;
s64 func_001430F8(void);
f32 func_001FB6B0(s64 value);

void func_00142F10(Timer_00142F10* self)
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
    f32 new_a = self->acc_a + s;
    f32 old_b = self->hist_b;
    f32 new_d = self->acc_d + self->step;
    self->acc_a = new_a;
    self->hist_c = old_b;
    self->hist_b = s;
    self->acc_d = new_d;
    self->last = now;
}

struct Timer_00143030 {
    u8 pad0[0x10];
    f32 acc_d;
    f32 step;
    s64 last;
};

s64 func_001430F8(void);
f32 func_001FB6B0(s64 value);

void func_00143030(Timer_00143030* self)
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
    self->acc_d = self->acc_d + dt;
}

struct Timer_001430B8 {
    u8 pad0[4];
    f32 acc_a;
};

void func_001430B8(Timer_001430B8* self, f32 value)
{
    self->acc_a = value;
}

void func_00143140(void)
{
}

struct Target_00143148 {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
};

void func_001ED650(void* self, f32 x, f32 y, f32 z);

void func_00143148(void* a0, void* a1, Target_00143148* a2, void* a3)
{
    func_001ED650(a3, a2->f30 + 3.1415927f, a2->f34, 0.0f);
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

struct Scaler_001434C8 {
    u8 pad0[0x1F8];
    f32 f1F8;
    f32 f1FC;
    f32 f200;
};

void func_00183FE0(f32* a, f32* b, f32 x, f32 y, f32 z, f32 w);

void func_001434C8(Scaler_001434C8* self, f32* out, f32 p)
{
    f32 one = 1.0f;
    f32 scale = 4080.0f;
    f32 a = self->f200 * p;
    f32 b = self->f1FC;
    f32 c = self->f1F8;
    func_00183FE0(out, out + 1, one, scale, b / c, (one - a) * scale);
    out[0] = out[0] + 8388608.0f;
    out[2] = self->f1F8;
    out[3] = out[0] + 36864.0f;
}

extern void* D_00261990;

void func_00143940(void* self);

void func_001437C0(void)
{
    func_00143940(D_00261990);
}

extern void* D_00261990;

void func_00143988(void* self);

void func_00143810(void)
{
    func_00143988(D_00261990);
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

void func_00140660(void* self, int value)
{
    func_00140640((u8*)self + 0x554, self, value);
}

struct List_1406B0 { u8 pad0[0x720]; s32 count; s32 items[1]; };

void func_001406B0(List_1406B0* list, s32 value)
{
    list->items[list->count++] = value;
}

struct Table_1415D0 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x564 - 0x18];
    s32 countA;
    void* arrA[9];
    s32 countB;
    void* arrB[8];
    s32 f5B0;
    s32 f5B4;
};

void func_001BA130(void* self);
void* func_00183058(void* item, void* x, Table_1415D0* self);

void func_001415D0(Table_1415D0* self)
{
    s32 keepB = self->f5B0;
    s32 keepA = self->f5B4;
    func_001BA130(self);
    self->f5B0 = keepB;
    self->f5B4 = keepA;
    for (s32 i = 0; i < self->countA; i++) {
        self->arrA[i] = func_00183058(self->arrA[i], self->f14, self);
    }
    for (s32 j = 0; j < self->countB; j++) {
        self->arrB[j] = func_00183058(self->arrB[j], self->f14, self);
    }
}

struct Event_1417F0 {
    s32 type;
    u8 pad[0xC];
    s32 flags;
};

extern u8 D_00262C70[];

void func_00141870(void* self);
s32 func_001925F0(void* self, Event_1417F0* ev);
s32 func_001BC320(void* self, Event_1417F0* ev);
void func_0016EC38(void* p, f32 f, s32 n);

s32 func_001417F0(void* self, Event_1417F0* ev)
{
    s32 r = func_001925F0(self, ev);
    if (ev->type == r) {
        if ((ev->flags & 0x10) == 0) {
            func_0016EC38(D_00262C70, 0.2f, 2);
        }
        func_00141870(self);
        return 1;
    }
    return func_001BC320(self, ev);
}

struct Slot_141870 {
    s32 f0;
    s32 f4;
};

struct Node_141870 {
    u8 pad0[0x8];
    s32 f8;
    u8 pad1[0xC];
    Node_141870* f18;
    u8 pad2[0x14];
    Slot_141870* f30;
    u8 pad3[0x564 - 0x34];
    s32 countA;
    void* arrA[9];
    s32 countB;
    void* arrB[4];
    s32 f5A0;
    s32 f5A4;
    u8 pad5[0x5AC - 0x5A8];
    void* f5AC;
    s32 f5B0;
};

extern u8 D_00261EF0[];
extern u8 D_00261420[];

void func_00151ED8(void* table, Node_141870* self);
s32 func_00141008(void* table, s32 v);
void func_00141040(void* table, s32 v);
s32 func_00182F40(s32 v, Node_141870* self);
void func_00140E10(void* table, s32 a, s32 idx);
void func_0012C7B0(void* p, s32 a, s32 b, s32 c, f32 x, f32 y);
void func_001B64D8(void* p, s32 n);

void func_00141870(Node_141870* self)
{
    func_00151ED8(D_00261EF0, self);
    s32 sel;
    if (self->f5AC != 0) {
        sel = func_00141008(D_00261420, self->f5B0) ? 0x549 : 0x548;
    }
    s32 idx = -1;
    func_00141040(D_00261420, self->f5B0);
    if (func_00182F40(self->f5A4, self)) {
        for (Node_141870* n = self; n != 0; n = n->f18) {
            Slot_141870* sl = n->f30;
            if (sl != 0) {
                idx = sl->f4;
            }
        }
        if (idx == -1) {
            idx = self->f8;
        }
    }
    func_00140E10(D_00261420, self->f5A0, idx);
    for (s32 i = 0; i < self->countA; i++) {
        func_0012C7B0(self->arrA[i], 0, 0, 0, 0.0f, 1.0f);
    }
    if (self->f5AC != 0) {
        func_001B64D8(self->f5AC, sel);
    }
}

struct Queue_1419A0 {
    u8 pad[0x578];
    s32 count;
    s32 items[1];
};

void func_001419A0(Queue_1419A0* q, s32 value)
{
    q->items[q->count++] = value;
}

struct Obj_143A38 {
    u8 pad0[0x1C0];
    f32 f1C0;
};


void func_00143A38(Obj_143A38* self, f32 value)
{
    self->f1C0 = value;
    func_00143560(D_00261990);
}

struct Ctl_143A60 {
    u8 pad0[0x218];
    f32 f218;
    s32 f21C;
    u8 pad1[0x3D0 - 0x220];
    s32 f3D0;
    u8 pad2[0x454 - 0x3D4];
    u8 f454[0x20];
};

extern u8 D_00261880[];
extern u8 D_00261890[];
void func_00144938(void* self, void* a, void* b);
void func_001493B8(void* p, s32 zero);
void func_00145088(void* self, s32 a1, void* a2, s32 a3, s32 a4);
void func_001455C0(void* self, s32 zero);

void func_00143A60(Ctl_143A60* self, s32 flag)
{
    if (flag != 0) {
        func_00144938(self, D_00261880, D_00261890);
    }
    self->f3D0 = 0;
    func_001493B8(self->f454, 0);
    func_00145088(self, 0, self->f454, 0, 0);
    func_001455C0(self, 0);
    self->f21C = 0x0FFFFFFF;
    self->f218 = -10.0f;
}

struct ItemList_143AF8 {
    u8 pad0[0x340];
    s32 count;
    void* items[8];
};

void func_00143AF8(ItemList_143AF8* list, void* item)
{
    u32 n = list->count;
    if (n < 8) {
        list->items[n] = item;
        list->count = n + 1;
    }
}

struct WordStack_1406D0 { u8 pad[0x744]; s32 count; s32 items[1]; };

void func_001406D0(WordStack_1406D0* self, s32 value)
{
    s32 n = self->count;
    self->items[n] = value;
    self->count = n + 1;
}

struct WordStack_1406F0 { u8 pad[0x768]; s32 count; s32 items[1]; };

void func_001406F0(WordStack_1406F0* self, s32 value)
{
    s32 n = self->count;
    self->items[n] = value;
    self->count = n + 1;
}

struct Slot_1419E0 { u8 pad[0x5A0]; s32 value; };

void func_001419E0(Slot_1419E0* self, s32 value)
{
    self->value = value;
}

struct IdList_143B20 { u8 pad[0x340]; s32 count; s32 items[1]; };

void func_0018D800(void* dst, void* src, u32 size);

void func_00143B20(IdList_143B20* list, s32 value)
{
    for (s32 i = 0; i < list->count; i++) {
        if (value == list->items[i]) {
            func_0018D800(&list->items[i], &list->items[i + 1], (list->count - i - 1) * 4);
            list->count--;
            return;
        }
    }
}

struct Entry_143BA8 { u8 pad0[0x404]; s32 flag404; u8 pad1[0x538 - 0x408]; u64 bits538; };

s32 func_00143BA8(void* unused, Entry_143BA8* e)
{
    s64 field = 0xF000;
    s64 want = 0x8000;
    s32 r = 0;
    field <<= 20;
    want <<= 17;
    if ((e->bits538 & field) == want) {
        goto set;
    }
    if (e->flag404 == 0) {
        goto done;
    }
set:
    r = 1;
done:
    return r;
}

void func_00124A48(void* self);
void func_0013EA38(void* p);
void func_00140238(void* self, s32 flag);
void* func_0015A448(void* obj, s32 id, void* ctx);

struct Self_140140 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x550 - 0x18];
    s32 f550;
    s32 f554[8];
    s32 f574;
    s32 f578[1];
    u8 pad2[0x5BC - 0x57C];
    s32 f5BC;
};

void func_00140140(Self_140140* self)
{
    func_00124A48(self);
    func_0013EA38((u8*)self + 0x5C0);
    func_00140238(self, 0);
    for (s32 i = 0; i < self->f550; i++) {
        void* p = func_0015A448(self->f14, self->f554[i], self);
        if (p != 0) {
            s32 n = self->f574;
            self->f578[n] = (s32)p;
            self->f574 = n + 1;
        }
    }
    if (self->f550 == 0) {
        self->f5BC = 1;
    }
}

void func_001BA130(void* self);

struct Self_140200 {
    u8 pad0[0x5C4];
    void* f5C4;
    u8 pad1[0x6E0 - 0x5C8];
    s32 f6E0;
};

void func_00140200(Self_140200* self)
{
    s32 saved = self->f6E0;
    func_001BA130(self);
    self->f6E0 = saved;
    self->f5C4 = self;
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

typedef int s32;
typedef unsigned char u8;
typedef float f32;

struct Ctl_143940 {
    u8 pad0[0x1C4];
    f32 f1C4;
    f32 f1C8;
    s32 i1CC;
};

void func_00143560(void* self);

void func_00143940(void* self, f32 x)
{
    Ctl_143940* c = (Ctl_143940*)self;
    c->f1C4 = x;
    c->f1C8 = x;
    c->i1CC = 0;
    func_00143560(self);
}

typedef int s32;
typedef unsigned char u8;
typedef float f32;

struct Ctl_143968 {
    u8 pad0[0x1E4];
    f32 f1E4;
};

void func_00143560(void* self);

void func_00143968(void* self, f32 x)
{
    Ctl_143968* c = (Ctl_143968*)self;
    c->f1E4 = x;
    func_00143560(self);
}

typedef signed int s32;
typedef unsigned char u8;

extern void func_0013EB68(void* state);

void func_00140238(void* self, s32 flag)
{
    func_0013EB68((u8*)self + 0x5C0);
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

struct Obj_143988 {
    u8 pad[0x1E8];
    f32 f1E8;
};
void func_00143560(void* self);

void func_00143988(Obj_143988* self, f32 value)
{
    self->f1E8 = value;
    func_00143560(self);
}

struct Obj_1439C8 {
    u8 pad[0x1FC];
    f32 f1FC;
};
void func_00143560(void* self);

void func_001439C8(Obj_1439C8* self, f32 value)
{
    self->f1FC = value;
    func_00143560(self);
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

void func_00140710(void* self, void* value)
{
    s32 i = *(s32*)((u8*)self + 0x78C);
    u32 address = (u32)self + (u32)(i << 2);
    *(u32*)(address + 0x790) = (u32)value;
    *(s32*)((u8*)self + 0x78C) = i + 1;
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

void func_00143838(void) { func_001439A8(D_00261990); }

void func_00143860(void) { func_001439C8(D_00261990); }

void func_00143888(void) { func_001439E8(D_00261990); }

void func_001438B0(void) { func_00143A08(D_00261990); }

void func_00143920(void* arg, void* arg2) { func_001448C8(arg, 0, arg2); }

void func_001405F0(u8* self, s32 value)
{
    func_001405D0(self + 0x554, self, value);
}

struct State_00141170 { u8 pad[0x8C]; void* child; };
struct __attribute__((aligned(16))) Quad_00141170 { f32 v[4]; };
void func_001F3B48(void* self, void* value, void* out);
s32 func_001E4DC0(void* self, void* value);
s32 func_00141170(State_00141170* self, void* value)
{
    Quad_00141170 local;
    func_001F3B48(self, value, &local);
    return func_001E4DC0(self->child, &local);
}

void func_001448C8(void* self, void* a, void* b);
void func_00143900(void* self, void* value)
{
    func_001448C8(self, value, 0);
}

struct State_001439E8 { u8 pad[0x200]; f32 value; };
void func_001439E8(void* ptr, f32 value)
{
    State_001439E8* self = (State_001439E8*)ptr;
    self->value = value;
    func_00143560(self);
}

struct __attribute__((packed)) Value_00143A08 { u32 value; };
void func_00143A08(void* self, void* value)
{
    *(Value_00143A08*)((u8*)self + 0x204) = *(Value_00143A08*)value;
    func_00143560(self);
}

struct Obj_140100 { u8 pad0[0x6FC]; s32 f6FC; u8 pad1[0x790 - 0x700]; s32 f790; };

void func_001BAC30(void* self);
void func_0013E950(void* p, void* self);

void func_00140100(Obj_140100* self)
{
    func_001BAC30(self);
    func_0013E950((u8*)self + 0x5C0, self);
    if (self->f790 != 0) {
        self->f6FC = 1;
    }
}

s32 func_001BC320(void* self, void* ev);
void func_0013F6F8(void* state, s32 mode);

s32 func_00140028(void* a0, void* a1)
{
    s32 r = func_001BC320(a0, a1);
    if (r != 0 && (*(s32*)((u8*)a1 + 0xC) & 4) == 0 && *(s32*)((u8*)a0 + 0x550) == 3 && *(s32*)((u8*)a0 + 0x680) == 0) {
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
void func_001B7968(void* self);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

struct Inner_1411A8 {
    u8 pad0[0x2304];
    s32 f2304;
};

struct Self_1411A8 {
    u8 pad0[0x14];
    Inner_1411A8* f14;
    u8 pad1[0x5A0 - 0x18];
    s32 f5A0;
    u8 pad2[0x5B0 - 0x5A4];
    s32 f5B0;
    s32 f5B4;
};

void func_001411A8(void* self)
{
    Self_1411A8* s = (Self_1411A8*)self;
    func_001B7968(self);
    s->f5B0 = func_00140FF8(D_00261420);
    s->f5A0 = -1;
    Inner_1411A8* in = s->f14;
    s32 n = in->f2304;
    s->f5B4 = n;
    n = n + 1;
    in->f2304 = n;
    func_001B9AE0(self, 3, 0, 3, 0);
}

s32 func_0013DFD8(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
s32 func_00141F48(void* a, void* b, void* c, s32 d, s32 e, f32 x);

struct Self_141C28 {
    u8 pad0[0x3CC];
    f32 f3CC;
    u8 pad1[0x3F8 - 0x3D0];
    s32 f3F8;
    u8 pad2[0x538 - 0x3FC];
    u64 f538;
};

s32 func_00141C28(Self_141C28* self, void* a1, void* a2, s32 a3, s32 a4)
{
    if (self->f3F8 != 0) {
        return func_0013DFD8((void*)self->f3F8, a1, a2, 0, a3, (void*)a4);
    }
    if (self->f538 & ((u64)0x8000 << 25)) {
        return func_00141F48((u8*)self + 0x140, a1, a2, a3, a4, self->f3CC);
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

struct Obj_141338 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x550 - 0x18];
    s32 f550;
    s32 f554[4];
    s32 f564;
    void* f568[4];
    s32 f578;
    s32 f57C[4];
    s32 f58C;
    void* f590[4];
};

void func_00141338(void* selfp)
{
    Obj_141338* self = (Obj_141338*)selfp;
    func_001249A8(self);
    s32 i = 0;
    while (i < self->f550) {
        void* r = func_0015A448(self->f14, self->f554[i], self);
        if (r != 0) {
            s32 k = self->f564;
            self->f568[k] = r;
            self->f564 = k + 1;
        }
        i++;
    }
    i = 0;
    while (i < self->f578) {
        void* r = func_0015A448(self->f14, self->f57C[i], self);
        if (r != 0) {
            s32 k = self->f58C;
            self->f590[k] = r;
            self->f58C = k + 1;
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
