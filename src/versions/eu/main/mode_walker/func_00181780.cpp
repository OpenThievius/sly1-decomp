// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the D_00270650 aim at 0x580 (US 0x270; PAL's ScreenElement is 0x310 bytes longer).

void HandleModeWalkerActivation(ModeWalker* self, void* active)
{
    HandlePathFollowerActivation(self, active);
    if (active) {
        AimReticle* e = &g_spinningSpriteElement;
        e->vt->m16(e, 2);
        Vu0::Q(*(Vec4*)((u8*)e + 0x580)) = Vu0::FromFloats(0.0f, 0.0f, 2000.0f);
    } else {
        g_spinningSpriteElement.vt->m16(&g_spinningSpriteElement, 0);
        self->pulseActive = 0;
    }
}
