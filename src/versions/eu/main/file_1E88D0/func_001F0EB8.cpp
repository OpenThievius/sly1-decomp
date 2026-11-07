// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL passes 0.975 where US passes 1.0.
void ApplyWarpPageTransform(void* obj, u8* s, void* c)
{
    u8 tmp[0x50];
    Camera* p = g_camera;
    f32 keep1 = p->f1C4;
    f32 keep2 = p->f1C8;
    SnapCameraZoom(p, 0.975f);
    BuildPlacedObjectTransform(obj, c, tmp);
    BuildMatrixFromRotationAndTranslation(s + 0x40, s + 0x80, tmp);
    func_00125C90(obj, s, tmp);
    SnapCameraZoom(g_camera, keep1);
    g_camera->f1C8 = keep2;
}
