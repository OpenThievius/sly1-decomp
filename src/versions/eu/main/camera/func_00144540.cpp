// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the projection's vertical scale is 256 (US 224).
void UpdateCameraMatrices(Camera* self)
{
    Vec02 pos;
    Vec02 dir;
    Mat02 rotation;
    f32 f6 = g_gameTime - self->f218;
    if (D_002618C8 < f6) {
        BuildViewProjectionMatrix((f32*)self->f40, (f32*)self->f80, (void*)((u8*)self + 0xC0), (Quad16*)((u8*)self + 0x100));
    } else {
        f32 t = f6 / D_002618C8;
        f32 amount = g_unitRange.Limit(D_002618D0[0] + t * (D_002618D0[1] + t * D_002618D0[2]));
        f32 swing = Sine(f6 * D_002618CC) * amount;
        u128 turn = Vu0::Rotate(*(Mat02*)self->f80, Vu0::Q(*(Vec02*)D_002618E0));
        Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(*(Vec02*)self->f40), turn, Vu0::Scalar(swing));
        Vu0::Q(dir) = Vu0::MulX(Vu0::Q(*(Vec02*)D_002618F0), Vu0::Scalar(swing));
        BuildRotationFromVector(&dir, (Mat02*)&rotation);
        MulRotationRowsX(&rotation, *(Mat02*)self->f80, rotation);
        Vec02 corner;
        Vec02 tilt;
        Mat4 proj;
        Vu0::Q(corner) = Vu0::MulAddX(Vu0::Q(*(Vec02*)D_00248D40), Vu0::Q(*(Vec02*)D_00261900), Vu0::Scalar(swing));
        Vu0::Q(tilt) = Vu0::MulX(Vu0::Q(*(Vec02*)D_00261910), Vu0::Scalar(swing));
        BuildProjectionMatrix(&proj, corner.x * 640.0f / (self->f1F0 * 4096.0f), corner.y * 256.0f / (self->f1F4 * 4096.0f), tilt.x, tilt.y, self->f1E4, self->f1E8);
        BuildViewProjectionMatrix((f32*)&pos, (f32*)&rotation, &proj, (Quad16*)((u8*)self + 0x100));
    }
    InvertMatrix4x4((u8*)self + 0x100, (u8*)self + 0x140);
    BuildFrustumSideNormals((Mat02*)self->f80, (Vec02*)((u8*)self + 0x180), self->f1F0, self->f1F4);
    {
        f32* e = (f32*)((u8*)self + 0x1B0);
        f32* d = self->planes[0];
        f32* c = (f32*)((u8*)self + 0x1A0);
        f32* b = (f32*)((u8*)self + 0x190);
        f32* a = (f32*)((u8*)self + 0x180);
        s32 n = 2;
        do {
            d[0] = *a++;
            d[1] = *b++;
            d[2] = *c++;
            d[3] = *e++;
            d += 4;
        } while (--n >= 0);
    }
}
