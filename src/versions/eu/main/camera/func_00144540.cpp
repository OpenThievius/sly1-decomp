// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the projection's vertical scale is 256 (US 224).
void UpdateCameraMatrices(Camera* self)
{
    Vec02 pos;
    Vec02 dir;
    Mat02 rotation;
    f32 f6 = g_gameTime - self->swingStartTime;
    if (g_cameraSwingDuration < f6) {
        BuildViewProjectionMatrix((f32*)self->position, (f32*)self->rotation, (void*)((u8*)self + 0xC0), (Quad16*)((u8*)self + 0x100));
    } else {
        f32 t = f6 / g_cameraSwingDuration;
        f32 amount = g_unitRange.Limit(g_cameraSwingFalloffCurve[0] + t * (g_cameraSwingFalloffCurve[1] + t * g_cameraSwingFalloffCurve[2]));
        f32 swing = Sine(f6 * g_cameraSwingRate) * amount;
        u128 turn = Vu0::Rotate(*(Mat02*)self->rotation, Vu0::Q(*(Vec02*)g_cameraSwingOffset));
        Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(*(Vec02*)self->position), turn, Vu0::Scalar(swing));
        Vu0::Q(dir) = Vu0::MulX(Vu0::Q(*(Vec02*)g_cameraSwingTurn), Vu0::Scalar(swing));
        BuildRotationFromVector(&dir, (Mat02*)&rotation);
        MulRotationRowsX(&rotation, *(Mat02*)self->rotation, rotation);
        Vec02 corner;
        Vec02 tilt;
        Mat4 proj;
        Vu0::Q(corner) = Vu0::MulAddX(Vu0::Q(*(Vec02*)D_00248D40), Vu0::Q(*(Vec02*)g_cameraSwingCornerShift), Vu0::Scalar(swing));
        Vu0::Q(tilt) = Vu0::MulX(Vu0::Q(*(Vec02*)g_cameraSwingTiltShift), Vu0::Scalar(swing));
        BuildProjectionMatrix(&proj, corner.x * 640.0f / (self->projectionScaleX * 4096.0f), corner.y * 256.0f / (self->projectionScaleY * 4096.0f), tilt.x, tilt.y, self->nearDistance, self->farDistance);
        BuildViewProjectionMatrix((f32*)&pos, (f32*)&rotation, &proj, (Quad16*)((u8*)self + 0x100));
    }
    InvertMatrix4x4((u8*)self + 0x100, (u8*)self + 0x140);
    BuildFrustumSideNormals((Mat02*)self->rotation, (Vec02*)((u8*)self + 0x180), self->projectionScaleX, self->projectionScaleY);
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
