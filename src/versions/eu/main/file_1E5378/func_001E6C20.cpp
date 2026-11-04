// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields 0x310 further on (0x920 for the tail), and PAL's screen scale and centre.
struct Elem_1E6C20 { f32 f0; f32 f4; f32 f8; f32 fC; u8 pad[0x2C - 0x10]; };
struct Self_eu_1E6C20 {
    u8 pad0[0x52C]; f32 f52C; f32 f530;
    u8 pad1[0x570 - 0x534]; s32 f570; f32 f574;
    u8 pad2[0x590 - 0x578]; Elem_1E6C20 elems[69];
    f32 f116C; f32 f1170; f32 f1174;
};

void func_001E6268(Self_eu_1E6C20* self, s32* first, s32* last);

#define SX_eu_1E6C20(x) ((s32)(((x) + 1728.0f) * 16.0f))
#define SY_eu_1E6C20(y) ((s32)(((y) * 0.5462963f + 1920.0f) * 16.0f))

void func_001E6C20(Self_eu_1E6C20* self, Buf_1E6C20* buf)
{
    Rgba_1E6C20 c;
    f32 t;
    switch (self->f570) {
    case 0:
        t = Clamp_1E6C20::Of((D_00261868 - self->f574) * 5.0f, 0.0f, 1.0f);
        break;
    case 1:
        t = Clamp_1E6C20::Of(1.0f - (D_00261868 - self->f574) * 5.0f, 0.0f, 1.0f);
        break;
    }
    func_001613C0(buf, 0, 1, 1);
    {
        Rgba_1E6C20 a = D_002610D8;
        Rgba_1E6C20 b = D_002610E0;
        Rgba_1E6C20 r;
        r.c[0] = Lerp_1E6C20::Of(a.c[0], b.c[0], t);
        r.c[1] = Lerp_1E6C20::Of(a.c[1], b.c[1], t);
        r.c[2] = Lerp_1E6C20::Of(a.c[2], b.c[2], t);
        r.c[3] = Lerp_1E6C20::Of(a.c[3], b.c[3], t);
        c = r;
    }
    func_00161458(buf, *(u32*)&c);
    func_001613C0(buf, 0x44, 1, 4);
    f32 x0 = self->f52C + self->f116C;
    f32 y0 = self->f530 + 63.152542f;
    f32 xe = self->f52C + self->f1170;
    s32 first, last;
    func_001E6268(self, &first, &last);
    Elem_1E6C20* e = &self->elems[first];
    f32 len = self->f1174;
    f32 xa = x0 + e->f0 * 63.152542f;
    f32 xb = x0 + (len + 63.152542f) * e->f0;
    f32 ya = y0 + e->f8 * 63.152542f;
    f32 yb = ya - len;
    func_001615F0(buf, SX_eu_1E6C20(xe), SY_eu_1E6C20(ya), 0, 0);
    func_001615F0(buf, SX_eu_1E6C20(xe), SY_eu_1E6C20(yb), 0, 0);
    func_001615F0(buf, SX_eu_1E6C20(xa), SY_eu_1E6C20(ya), 0, 0);
    func_001615F0(buf, SX_eu_1E6C20(xb), SY_eu_1E6C20(yb), 0, 0);
    for (s32 i = first; i < last; i++) {
        e = &self->elems[i];
        xa = x0 + e->f0 * 63.152542f;
        ya = y0 + e->f8 * 63.152542f;
        xb = x0 + (self->f1174 + 63.152542f) * e->f0;
        yb = y0 + (self->f1174 + 63.152542f) * e->f8;
        func_001615F0(buf, SX_eu_1E6C20(xa), SY_eu_1E6C20(ya), 0, 0);
        func_001615F0(buf, SX_eu_1E6C20(xb), SY_eu_1E6C20(yb), 0, 0);
    }
    xa = x0 + e->f4 * 63.152542f;
    ya = y0 + e->fC * 63.152542f;
    yb = ya + self->f1174;
    xb = x0 + (self->f1174 + 63.152542f) * e->f4;
    func_001615F0(buf, SX_eu_1E6C20(xa), SY_eu_1E6C20(ya), 0, 0);
    func_001615F0(buf, SX_eu_1E6C20(xb), SY_eu_1E6C20(yb), 0, 0);
    func_001615F0(buf, SX_eu_1E6C20(xe), SY_eu_1E6C20(ya), 0, 0);
    func_001615F0(buf, SX_eu_1E6C20(xe), SY_eu_1E6C20(yb), 0, 0);
}
