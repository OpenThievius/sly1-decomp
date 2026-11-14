// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the D_00270650 aim at 0x580 (US 0x270; PAL's ScreenElement is 0x310 bytes longer).

// D_00270650 as PAL lays it out, for the aim.
struct T217D_BF0Aim {
    u8 pad000[0x580];
    Vec02 aim;                  // 0x580
};

void HandleWorld5ModeColliderActivation(World5ModeCollider* self, void* active)
{
    HandleSwitchedColliderActivation(self, active);
    if (active) {
        Vu0::Q(((T217D_BF0Aim*)&D_00270650)->aim) = Vu0::FromFloats(0.0f, 0.0f, 2000.0f);
    } else {
        D_00270650.vt->m16(&D_00270650, 0);
        self->pulseActive = 0;
    }
}
