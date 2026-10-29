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
