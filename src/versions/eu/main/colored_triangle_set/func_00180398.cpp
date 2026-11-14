// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL centres y on 234.30508f (not 246.40001f), clamps it to 452.61017f (not 476.80002f), tests
// 468.61017f (not 492.80002f), scales y by 0.5462963f and offsets it by 1920.0f, and the frame's
// y corners are 0x7800 and 0x8800 (not 0x7900 and 0x8700)
void DrawColoredTriangles(ColoredTriangleSet* self, f32 t)
{
    f32 mat[16];
    SwitchedCollider* o;

    BuildUniformScaleAboutPoint(0, mat, (1.0f - t) * (1280.0f / self->width) + t * (4.0f / self->width));
    o = GetActiveSwitchedCollider();
    if (o != 0 && (o = o->desc05()->m53(o)) != 0 && o->desc05()->m4D(o) == 2) {
        Vec02 v;
        f32 x, y;
        ProjectPointToCamera(g_camera, &o->v140, (f32*)&v);
        x = ClampHelper::Clamp(v.x * 320.0f + 320.0f, 10.0f, 630.0f);
        mat[12] = (1.0f - t) * 320.0f + t * x;
        y = ClampHelper::Clamp(v.y * -234.30508f + 234.30508f, 16.0f, 452.61017f);
        mat[13] = (1.0f - t) * 234.30508f + t * y;
    } else {
        mat[12] = 320.0f;
        mat[13] = 234.30508f;
    }
    {
        BlendColor base;
        s32 g;
        s32 vis;
        BeginGifTag(&g_gsPacketWriter, 0, 1, 0xE);
        AddGifRegisterWrite(&g_gsPacketWriter, 0x47, 0x31001);
        AddGifRegisterWrite(&g_gsPacketWriter, 0x42, 0x44);
        vis = 0;
        for (g = 4; g >= 0; g--) {
            TriangleList* r = &self->lists[g];
            BlendColor col = *(BlendColor*)&r->col;
            if (g == 0) {
                BlendColor mixed;
                BlendColor from = *(BlendColor*)&r->col;
                BlendColor black;
                *(u32*)&black = 0x80000000;
                mixed.Blend(from, black, t);
                col = mixed;
            }
            if (t <= 0.4f) {
                col.c[3] = (s32)((f32)col.c[3] * t * 2.5f);
            }
            if (g == 0) {
                base = col;
            }
            if (r->count > 0) {
                s32 i;
                BeginGifTag(&g_gsPacketWriter, 0, 1, 1);
                AddGifRgbaEntry(&g_gsPacketWriter, *(u32*)&col);
                BeginGifTag(&g_gsPacketWriter, (s8)col.c[3] >= 0 ? 0x43 : 0x83, 1, 4);
                for (i = 0; i < r->count; i++) {
                    u32* idx = (u32*)&r->triangles[i];
                    s32 j;
                    for (j = 2; j >= 0; j--, idx++) {
                        Quad128Floats p, q;
                        p.v = *(Quad128*)&self->points[*idx];
                        q.v = TransformVector4(mat, p.v);
                        AddGifXyzfEntry(&g_gsPacketWriter, (s32)((q.f[0] + 1728.0f) * 16.0f), (s32)((q.f[1] * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
                        vis = vis || 0.0f < q.f[0] || q.f[0] < 640.0f || 0.0f < q.f[1] || q.f[1] < 468.61017f;
                    }
                }
            }
        }
        if (vis) {
            Quad128Floats lo, hi;
            f32 d;
            lo.v = TransformVector4(mat, *(Quad128*)&self->minX);
            hi.v = TransformVector4(mat, *(Quad128*)&self->maxX);
            BeginGifTag(&g_gsPacketWriter, (s8)base.c[3] >= 0 ? 0x44 : 0x84, 0xB, 0x44444444441ULL);
            AddGifRgbaEntry(&g_gsPacketWriter, *(u32*)&base);
            AddGifXyzfEntry(&g_gsPacketWriter, 0x6C00, 0x7800, 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, (s32)((lo.f[0] + 1728.0f) * 16.0f), (s32)((lo.f[1] * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, 0x9400, 0x7800, 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, (s32)((hi.f[0] + 1728.0f) * 16.0f), (s32)((lo.f[1] * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, 0x9400, 0x8800, 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, (s32)((hi.f[0] + 1728.0f) * 16.0f), (s32)((hi.f[1] * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, 0x6C00, 0x8800, 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, (s32)((lo.f[0] + 1728.0f) * 16.0f), (s32)((hi.f[1] * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, 0x6C00, 0x7800, 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, (s32)((lo.f[0] + 1728.0f) * 16.0f), (s32)((lo.f[1] * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
            d = 1.0f - t;
            if (d <= 0.1f) {
                BlendColor fade = base;
                fade.c[3] = (s32)((f32)fade.c[3] * (1.0f - d * 10.0f));
                BeginGifTag(&g_gsPacketWriter, 0x44, 5, 0x44441);
                AddGifRgbaEntry(&g_gsPacketWriter, *(u32*)&fade);
                AddGifXyzfEntry(&g_gsPacketWriter, (s32)((lo.f[0] + 1728.0f) * 16.0f), (s32)((lo.f[1] * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
                AddGifXyzfEntry(&g_gsPacketWriter, (s32)((hi.f[0] + 1728.0f) * 16.0f), (s32)((lo.f[1] * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
                AddGifXyzfEntry(&g_gsPacketWriter, (s32)((lo.f[0] + 1728.0f) * 16.0f), (s32)((hi.f[1] * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
                AddGifXyzfEntry(&g_gsPacketWriter, (s32)((hi.f[0] + 1728.0f) * 16.0f), (s32)((hi.f[1] * 0.5462963f + 1920.0f) * 16.0f), 0, 0);
            }
        }
    }
}
