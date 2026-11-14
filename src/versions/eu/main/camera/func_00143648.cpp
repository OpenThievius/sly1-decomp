// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the constant stored at +0x1E0 is 1.36574075f (0x3FAED098) where US has 1.29870129f.
void InitCamera(Camera* self)
{
    u8* s = (u8*)self;

    InitObject(self);
    f32 one = 1.0f;
    *(f32*)(s + 0x1C0) = one;
    *(f32*)(s + 0x1C4) = one;
    *(f32*)(s + 0x1C8) = one;
    *(struct ParamBlock16*)(s + 0x1D0) = *(struct ParamBlock16*)D_002618B8;
    f32 k = 1.36574075f;
    f32 x = D_002618A0;
    f32 y = D_002618A4;
    f32 z = D_002618A8;
    f32 h = 100.0f;
    f32 t = 20000.0f;
    *(f32*)(s + 0x1E0) = k;
    *(f32*)(s + 0x1E4) = h;
    *(f32*)(s + 0x1E8) = t;
    *(f32*)(s + 0x1F8) = x;
    *(f32*)(s + 0x1FC) = y;
    *(f32*)(s + 0x200) = z;
    *(struct FogColorWord*)(s + 0x204) = *(struct FogColorWord*)&D_002618B0;
    *(struct FrameRow*)(s + 0x80) = *(struct FrameRow*)g_identityMatrix;
    *(struct FrameRow*)(s + 0x90) = *(struct FrameRow*)(g_identityMatrix + 0x10);
    *(struct FrameRow*)(s + 0xA0) = *(struct FrameRow*)(g_identityMatrix + 0x20);
    UpdateCameraProjection((Camera*)self);
    self->ctl454.vt = (const CameraControllerVt*)D_00217398;
    SetCameraControllerOwner(&self->ctl454, self);
    self->ctl460.vt = (const CameraControllerVt*)D_002173B0;
    InitTargetCameraController(&self->ctl460, self);
    self->ctl4C0.vt = (const CameraControllerVt*)D_002173C8;
    InitFrameCameraController(&self->ctl4C0, self);
    self->ctl510.vt = (const CameraControllerVt*)D_002173E0;
    SetCameraControllerOwner(&self->ctl510, self);
    self->ctl520.vt = (const CameraControllerVt*)D_002173F8;
    SetCameraControllerOwner(&self->ctl520, self);
    ResetCamera(self, 1);
}
