// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the projection's vertical scale is 256 (US 224).
void UpdateCameraProjection(Camera* self)
{
    u8* s = (u8*)self;
    f32 one = 1.0f;
    f32 t = Tangent(self->f1C4 * 0.5f);
    f32 inv = one / self->f1C4;
    f32 w = *(f32*)(s + 0x1E0);
    *(f32*)(s + 0x1F4) = t;
    *(f32*)(s + 0x1F0) = t * w;
    f32 d = w * w + one;
    *(f32*)(s + 0xB0) = (one >? self->f1C0 * inv);
    f32 q = t * Fpu::Sqrt(d);
    *(f32*)(s + 0x1EC) = q * self->f1E4 + one;
    BuildProjectionMatrix(s + 0xC0, 640.0f / (t * w * 4096.0f), 256.0f / (t * 4096.0f), 0.0f, 0.0f, self->f1E4, self->f1E8);
    ComputeCameraFogTerms(self, (f32*)(s + 0x208), one);
    UpdateCameraMatrices(self);
}
