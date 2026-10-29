// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

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
