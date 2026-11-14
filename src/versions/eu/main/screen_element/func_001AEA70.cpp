// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the same initialiser as US's, its first two array constructions 0x45 entries long where
// US's are 0x39.
void ConstructScreenTextStyles(s32 initialize, s32 priority)
{
    if (priority == 0xFFFF && initialize) {
        s32 i;
        for (i = 0x44; i != -1; i--) {
        }
        for (i = 0x44; i != -1; i--) {
        }
        for (i = 3; i != -1; i--) {
        }
        FillMemory(&D_002743D0, 0, 0x1C);
        D_002743D0.f04 = 0x2D;
        D_002743D0.f08 = 2.0f;
        D_002743D0.f0C = 1.0f;
        D_002743D0.f14 = D_002743D0.f10 = 0.3f;
        D_002743D0.color = 0xFF7D4B00;
        FillMemory(&D_002743F0, 0, 0x1C);
        D_002743F0.f04 = 0x2D;
        D_002743F0.f08 = 2.0f;
        D_002743F0.f0C = -4.0f;
        D_002743F0.f14 = D_002743F0.f10 = 0.3f;
        D_002743F0.color = 0xFF7D4B00;
        FillMemory(&D_00274410, 0, 0x1C);
        D_00274410.f04 = 0x3D;
        D_00274410.f08 = 2.0f;
        D_00274410.f0C = -4.0f;
        D_00274410.f14 = D_00274410.f10 = 0.3f;
        D_00274410.color = 0xFF7D4B00;
        FillMemory(&D_00274450, 0, 0x1C);
        D_00274450.f04 = 0x2D;
        D_00274450.f08 = 2.0f;
        D_00274450.f0C = -4.0f;
        D_00274450.f14 = D_00274450.f10 = 0.3f;
        D_00274450.color = 0xFF7D4B00;
        FillMemory(&D_00274488, 0, 0x1C);
        D_00274488.f04 = 0x2D;
        D_00274488.f08 = 2.0f;
        D_00274488.f0C = -4.0f;
        D_00274488.f14 = D_00274488.f10 = 0.3f;
        D_00274488.color = 0xFF7D4B00;
    }
}
