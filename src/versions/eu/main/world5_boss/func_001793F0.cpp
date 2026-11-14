// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the D_00270650 words at 0x594 and 0x598 (US 0x284 and 0x288).

void StartWorld5ModeCollider(World5ModeCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0x1A, g_modeColliderLinks);
    SetFollowObjects((PlacedObject*)self->f6E8, self->f680, self->f680);
    ((World5ModeColliderLinked*)self->f650)->frame = self->f660;
    self->stateWalker = CreateStateWalker((StateGraph*)self->stateGraph, self, -1, 0);
    BuildCombinedBlendAnimation(self, 0xC, 5, (u8*)&self->restWeight, 0, 0, 0, (BlendAnimation**)&self->weightBlend);
    self->restWeight = 1.0f;
    SetBlendItemWeights((BlendAnimationView*)self->weightBlend, 0xC, 5, &self->restWeight);
    SetWorld5ModeColliderMode(self, 2);
    u8* base = (u8*)&D_00270650;
    ((T217D_Float*)(base + 0x598))->v = 0.0f;
    *(s32*)(base + 0x594) = FindAnimRecord(0x36A);
}

