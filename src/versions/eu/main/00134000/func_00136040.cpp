// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: f260 is at 0x570 and f304..f314 at 0x590..0x5A0 (US 0x260 and 0x304..0x314).
struct Self_136040_eu {
    u8 pad_000[0x570];
    s32 f260;
    u8 pad_574[0x590 - 0x574];
    f32 f304;
    f32 f308;
    u8 pad_30C[8];
    f32 f314;
};

void func_00135F48(Self_136040_eu* self, Pad_136040* p);

void func_00136040(Self_136040_eu* self, Pad_136040* p)
{
    switch (self->f260) {
    case 1: {
        Vec_136040 va;
        Vec_136040 vb;
        Vec_136040 r;
        f32 lo = -1.0f;
        f32 hi = 1.0f;
        f32 sum = p->f40 + p->f74;
        Tri_136040 t0 = *(Tri_136040*)D_00249D00;
        Tri_136040 t1 = *(Tri_136040*)D_00249D10;
        f32 u = (sum < lo) ? lo : ((hi < sum) ? hi : sum);
        f32 v = p->f44;
        f32 lo2 = -1.0f;
        f32 hi2 = 1.0f;
        if (v < lo2) {
            v = lo2;
        } else if (hi2 < v) {
            v = hi2;
        }
        if (D_002623C0->flags & 0x200) v = -v;
        va.x = self->f304;
        va.y = self->f308;
        va.z = 0;
        vb.x = u * 50.0f;
        vb.y = v * 50.0f;
        vb.z = 0;
        f32* g = ((f32*)D_00261858);
        *(Quad_136040*)&r = func_001EA818(*(Quad_136040*)&va, *(Quad_136040*)&vb, (0.0001f < p->f48 + p->f7C) ? &t0 : &t1, 0, g[2]);
        self->f314 += u * -0.08f;
        self->f304 = r.x;
        self->f308 = r.y;
        self->f314 = func_001EAFE0(self->f314, 1.0f);
        break;
    }
    case 5:
        self->f308 = 50.0f;
        break;
    }
    func_00135F48(self, p);
}
