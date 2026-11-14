// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields 0x310 further on, 69 elements where US has 57, and the rest 0x520 further on.
struct Elem_1E77C0 { u8 pad00[0x18]; f32 f18; f32 f1C; f32 f20; f32 f24; f32 f28; };
struct Obj_1E77C0_eu;
typedef void (*VFn_1E77C0_eu)(Obj_1E77C0_eu* self, s32 state);

struct Obj_1E77C0_eu
{
    VFn_1E77C0_eu* vtbl;
    u8 pad004[0x520];
    s32 f214;
    u8 pad218[0x38];
    s32 f250;
    u8 pad254[0x14];
    s32 f268;
    u8 pad26C[0x4];
    s32 f270;
    s32 f274;
    u8 pad278[0x8];
    Elem_1E77C0 elems[69];
    u8 padC4C[0x10];
    f32 fC5C;
    f32 fC60;
    f32 fC64;
    f32 fC68;
    f32 fC6C;
    f32 fC70;
};

void UpdateScreenElementSlide(Obj_1E77C0_eu* self);
void SetArcPhase(Obj_1E77C0_eu* self, s32 mode);

void UpdateArc(Obj_1E77C0_eu* self)
{
    UpdateScreenElementSlide(self);
    s32 state = self->f250;
    s32 sub = self->f268;
    switch (state)
    {
    case 0:
        if (self->f274 != 0)
        {
            state = 2;
        }
        else if (self->f270 != 0)
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
            f32 f = self->fC70 + g_gameClock[5] * 5.0f;
            self->fC70 = f;
            if (1.0f <= f)
            {
                self->fC70 = 1.0f;
                sub = 1;
            }
            break;
        }
        case 2:
        {
            f32 f = self->fC70 - g_gameClock[5] * 5.0f;
            self->fC70 = f;
            if (f <= 0.0f)
            {
                self->fC70 = 0.0f;
                sub = 3;
            }
            break;
        }
        case 3:
            if (self->f270 != 0)
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
            self->fC5C = ApproachValueWithRamp((RampProfile*)&self->fC64, 0, self->fC5C, self->fC60, g_gameClock[5]);
            if (AreFloatsNearlyEqual(self->fC5C, self->fC60, 1e-4f) != 0)
            {
                self->fC5C = 1.0f;
                if (self->f214 == 0x1A)
                {
                    self->fC64 = RandomFloatInRange(1.0f, 1.4f);
                    self->fC68 = RandomFloatInRange(0.6f, 0.8f);
                    self->fC6C = RandomFloatInRange(0.1f, 0.2f);
                }
                else
                {
                    self->fC64 = RandomFloatInRange(0.5f, 0.7f);
                    self->fC68 = RandomFloatInRange(0.2f, 0.3f);
                    self->fC6C = RandomFloatInRange(0.3f, 0.5f);
                }
            }
            s32 idx = (s32)(self->fC5C * 68.999f);
            f32 d = RandomFloatInRange(0.1f, 0.2f);
            if (self->f214 == 0x1A)
            {
                d = d + d;
            }
            f32 lo = 0.0f;
            f32 hi = 1.0f;
            f32 v = self->elems[idx].f18 + d;
            if (v < lo)
            {
                v = lo;
            }
            else if (hi < v)
            {
                v = hi;
            }
            self->elems[idx].f18 = v;
            s32 big = 0x1A;
            f32* q;
            Elem_1E77C0* e;
            s32 i;
            for (q = &self->elems[0].f20, e = self->elems, i = 0; i < 69; q += 11, i++, e++)
            {
                if (AreFloatsNearlyEqual(e->f18, e->f1C, 1e-4f) != 0)
                {
                    if (self->f214 == big)
                    {
                        e->f20 = RandomFloatInRange(0.6f, 0.8f);
                        e->f24 = RandomFloatInRange(0.4f, 0.6f);
                        e->f28 = RandomFloatInRange(0.05f, 0.2f);
                    }
                    else
                    {
                        e->f20 = RandomFloatInRange(0.3f, 0.4f);
                        e->f24 = RandomFloatInRange(0.2f, 0.3f);
                        e->f28 = RandomFloatInRange(0.1f, 0.4f);
                    }
                    e->f1C = RandomFloatInRange(0.0f, 0.05f);
                }
                else
                {
                    e->f18 = ApproachValueWithRamp((RampProfile*)q, 0, e->f18, e->f1C, g_gameClock[5]);
                }
            }
        }
        break;
    }
    self->vtbl[16](self, state);
    SetArcPhase(self, sub);
}
