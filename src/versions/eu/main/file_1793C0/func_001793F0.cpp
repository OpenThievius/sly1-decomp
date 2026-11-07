// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the D_00270650 words at 0x594 and 0x598 (US 0x284 and 0x288).

void StartModeCollider(ModeCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0x1A, g_modeColliderLinks);
    SetFollowObjects(self->f6E8, self->f680, self->f680);
    ((Sub_1793F0*)self->f650)->fE0 = self->f660;
    self->f658 = CreateStateWalker(self->f654, self, -1, 0);
    BuildCombinedBlendAnimation(self, 0xC, 5, &self->f684, 0, 0, 0, &self->f6C0);
    self->f684 = 1.0f;
    SetBlendItemWeights(self->f6C0, 0xC, 5, &self->f684);
    SetModeColliderMode(self, 2);
    u8* base = (u8*)&D_00270650;
    ((T217D_Float*)(base + 0x598))->v = 0.0f;
    *(s32*)(base + 0x594) = FindAnimRecord(0x36A);
}

