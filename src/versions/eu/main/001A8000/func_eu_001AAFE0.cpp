// SPDX-License-Identifier: AGPL-3.0-or-later
// Steps a fade state machine (fade in, hold, fade out) and interpolates two position pairs on a state change.
struct Vt_eu_1AAFE0 {
    u8 pad0[0x2C];
    f32 (*fadeIn)(void* self);
    f32 (*hold)(void* self);
    f32 (*fadeOut)(void* self);
    u8 pad1[8];
    void (*setState)(void* self, s32 state);
};
struct Obj_eu_1AAFE0 {
    Vt_eu_1AAFE0* vt;
    u8 pad0[0x52C - 4];
    f32 a52C; f32 a530; f32 a534; f32 a538; f32 a53C; f32 a540;
    u8 pad1[0x54C - 0x544];
    f32 a54C; u8 pad2[0x55C - 0x550];
    f32 a55C; s32 state; f32 a564; f32* clock;
};
struct Curve_eu_1AAFE0 { f32 c0; f32 c1; f32 c2; };
extern Curve_eu_1AAFE0 D_eu_0027DAF0;
void func_001AAEC0(void* self);

static inline f32 clamp2_eu_1AAFE0(f32 v, f32 lo, f32 hi)
{
    return v < lo ? lo : (hi < v ? hi : v);
}

static inline f32 clamp_eu_1AAFE0(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

void func_eu_001AAFE0(Obj_eu_1AAFE0* self)
{
    f32 now = *self->clock;
    s32 state = self->state;
    switch (state) {
    case 2: {
        f32 len = self->vt->hold(self);
        if (len != 0.0f) {
            if (len <= now - self->a564) {
                state = 3;
            }
        }
        break;
    }
    case 1: {
        f32 len = self->vt->fadeIn(self);
        if (len != 0.0f) {
            f32 t = ((now - self->a564) + self->a55C) / len;
            t = clamp_eu_1AAFE0(t, 0.0f, 1.0f);
            self->a54C = t;
        }
        if (1.0f <= self->a54C) {
            state = 2;
        }
        break;
    }
    case 3: {
        f32 len = self->vt->fadeOut(self);
        if (len != 0.0f) {
            f32 t = ((now - self->a564) + self->a55C) / len;
            t = clamp2_eu_1AAFE0(t, 0.0f, 1.0f);
            self->a54C = 1.0f - t;
        }
        if (self->a54C <= 0.0f) {
            state = 0;
        }
        break;
    }
    }
    if (state == self->state) {
        f32 e = self->a54C;
        f32 s = D_eu_0027DAF0.c0 + e * (D_eu_0027DAF0.c1 + e * D_eu_0027DAF0.c2);
        self->a52C = self->a53C + s * (self->a534 - self->a53C);
        self->a530 = self->a540 + s * (self->a538 - self->a540);
        func_001AAEC0(self);
    }
    self->vt->setState(self, state);
}
