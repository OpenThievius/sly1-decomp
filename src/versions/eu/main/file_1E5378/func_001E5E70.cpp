// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: sets up the 69 ring elements (50 Hz layout: fields 0x310 further on, tail 0x520 further on).
struct Obj_1E5E70_eu {
    u8 pad0[0x524];
    s32 mode;
    u8 pad1[0x544 - 0x528];
    f32 f544;
    f32 f548;
    u8 pad2[0x564 - 0x54C];
    u8 elems[0x1144 - 0x564];
    s32 f1144;
    u8 pad1148[4];
    f32 f114C;
    u8 pad1150[0x116C - 0x1150];
    f32 f116C;
    f32 f1170;
    f32 f1174;
    f32 f1178;
    u8 pad117C[0x1184 - 0x117C];
    f32 f1184;
    f32 f1188;
    f32 f118C;
};

void func_001AA1F0(Obj_1E5E70_eu* self, s32 kind);

void func_001E5E70(Obj_1E5E70_eu* self, s32 kind)
{
    self->f544 = 160.0f;
    self->f548 = 126.305084f;
    self->f1174 = self->f1178 = 2.7457628f;
    InitScreenElement(self, kind);
    f32 sign;
    if (kind == 0x1A) {
        self->f1170 = 0.0f;
        self->f116C = self->f544 - 63.152542f;
        sign = 1.0f;
    } else {
        self->f1170 = self->f544;
        self->f116C = 63.152542f;
        sign = -1.0f;
    }
    f32 step = 1.0f / 69.0f;
    s32 i = 0;
    u32 dim = 0x30000000;
    s32 special = 0x1A;
    ArcPointStep* p;
    for (p = (ArcPointStep*)self->elems; i < 69; i++) {
        f32 t = (f32)i * step;
        f32 y = t + t - 1.0f;
        p->f34 = y;
        p->f2C = sign * Fpu::Sqrt(1.0f - y * y);
        p->f3C = p->f40 = (i & 1) ? dim : 0x30808080;
        p->f44 = p->f48 = 0.0f;
        if (self->mode == special) {
            p->f4C = RandomFloatInRange(0.6f, 0.8f);
            p->f50 = RandomFloatInRange(0.4f, 0.6f);
            p->f54 = RandomFloatInRange(0.05f, 0.2f);
        } else {
            p->f4C = RandomFloatInRange(0.3f, 0.4f);
            p->f50 = RandomFloatInRange(0.2f, 0.3f);
            p->f54 = RandomFloatInRange(0.1f, 0.4f);
        }
        if (i != 0) {
            p->fC = p->f34;
            p->f4 = p->f2C;
        }
        p = (ArcPointStep*)((u8*)p + 0x2C);
    }
    self->f114C = 1.0f;
    self->f1144 = 0;
    if (self->mode == 0x1A) {
        self->f1184 = RandomFloatInRange(1.0f, 1.4f);
        self->f1188 = RandomFloatInRange(0.6f, 0.8f);
        self->f118C = RandomFloatInRange(0.1f, 0.2f);
    } else {
        self->f1184 = RandomFloatInRange(0.5f, 0.7f);
        self->f1188 = RandomFloatInRange(0.2f, 0.3f);
        self->f118C = RandomFloatInRange(0.3f, 0.5f);
    }
}
