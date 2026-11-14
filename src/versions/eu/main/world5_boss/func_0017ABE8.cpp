// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the D_00270650 aim's speeds at 0x570 and the aim at 0x580 (US 0x260 and 0x270; PAL's
// ScreenElement is 0x310 bytes longer, as func_0017A700's PAL definition shows).

// D_00270650 as PAL lays it out, for the aim's speeds and the aim.
struct T217D_BF0Rates {
    u8 pad000[0x570];
    Vec02 rates;                // 0x570
    Vec02 aim;                  // 0x580
};

void SetWorld5ModeColliderMode(World5ModeCollider* self, s32 mode)
{
    s32 old = self->f610;
    if (mode == old) return;
    switch (old) {
    case 3:
    case 4:
        self->f6D8 = g_gameClock[1];
        break;
    }
    void* anim = 0;
    switch (mode) {
    case 2: {
        Vu0::Q(((T217D_BF0Rates*)&D_00270650)->aim) = Vu0::FromFloats(0.0f, 0.0f, 2000.0f);
        ((T217D_BF0Rates*)&D_00270650)->rates = D_00248D30;
        D_00270650.vt->m16(&D_00270650, 2);
        anim = self->f6C0;
        break;
    }
    case 1:
        anim = self->f6C4;
        break;
    case 3:
        anim = self->f6C8;
        self->f6D8 = 3.4028235e+38f;
        break;
    case 4:
        anim = self->f6CC;
        self->f6D8 = 3.4028235e+38f;
        SetFollowObjects((PlacedObject*)self->f6E8, self, self);
        break;
    }
    self->f610 = mode;
    self->f614 = g_gameClock[1];
    ReplaceAnimationPlayer((Animation*)anim, self, 1, (AnimationPlayer**)&self->f618, 0.0f, 1.0f);
}
