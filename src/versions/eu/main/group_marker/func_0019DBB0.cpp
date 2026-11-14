// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL passes 0.975 where US passes 1.0.
void PrepareUnzoomedGroup(void)
{
    PacketWriter* self = &g_vifPacketWriter;
    AddDmaRefTagIfChanged(self, g_groupMicroprogram, g_groupMicroprogramEnd);
    UploadProjectionConstants();
    UploadCameraOncePerFrame();

    if (D_0026FA68 != 0) {
        s32 v = g_maskImageUploads[D_0026FA68->slot];
        if (v != 0) {
            *(u64*)self->cur = ((u64)v << 32) | 0x50000000;
            self->cur = self->cur + 0x10;
        }
    }

    {
        Camera* o = g_camera;
        f32 keep20 = o->zoom;
        f32 keep21 = o->zoomGoal;
        SnapCameraZoom(o, 0.975f);
        WriteCameraMatricesPacket(g_camera);
        SnapCameraZoom(g_camera, keep20);
        g_camera->zoomGoal = keep21;
    }
}
