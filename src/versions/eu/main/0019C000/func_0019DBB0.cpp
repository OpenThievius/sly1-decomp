// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL passes 0.975 where US passes 1.0.
void func_0019DBB0(void)
{
    V24A0* self = &g_vifPacketWriter;
    AddDmaRefTagIfChanged(self, D_00212160, D_00215C50);
    UploadProjectionConstants();
    func_0019D930();

    if (D_0026FA68 != 0) {
        s32 v = D_00274520[D_0026FA68->idx2F4];
        if (v != 0) {
            *(u64*)self->cur = ((u64)v << 32) | 0x50000000;
            self->cur = self->cur + 0x10;
        }
    }

    {
        Camera* o = g_camera;
        f32 keep20 = o->f1C4;
        f32 keep21 = o->f1C8;
        SnapCameraZoom(o, 0.975f);
        func_00144848(g_camera);
        SnapCameraZoom(g_camera, keep20);
        g_camera->f1C8 = keep21;
    }
}
