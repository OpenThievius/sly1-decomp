// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL passes 0.975 where US passes 1.0.
void ApplyWarpPageTransform(void* obj, u8* s, void* c)
{
    u8 tmp[0x50];
    Camera* p = g_camera;
    f32 keep1 = p->zoom;
    f32 keep2 = p->zoomGoal;
    SnapCameraZoom(p, 0.975f);
    BuildPlacedObjectTransform((PlacedObject*)obj, (Quad16*)c, (ScaledTransform*)tmp);
    BuildMatrixFromRotationAndTranslation((const Vec02*)(s + 0x40), (const Mat02*)(s + 0x80), (Mat4A*)tmp);
    ApplyPlacedObjectTransform((PlacedObject*)obj, (Camera*)s, (ScaledTransform*)tmp);
    SnapCameraZoom(g_camera, keep1);
    g_camera->zoomGoal = keep2;
}
