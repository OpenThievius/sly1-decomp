// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the D_00270650 words at 0x594 and 0x598 (US 0x284 and 0x288).

void StartModeWalkerObject(ModeWalker* self)
{
    StartPathFollower(self);
    ResolveObjectLinks(self, 0xA, g_modeWalkerLinks);
    self->stateWalker = (StateWalker*)CreateStateWalker((StateGraph*)self->stateGraph, self, -1, 0);

    AddMatrixAttachment((PlacedObject*)self->fBCC, 5, (Attachment**)&self->fBD0);
    ((u8*)self->fBD0)[0x10] = 9;
    ((u8*)self->fBD0)[0x11] = 9;
    ((PlacedObject*)self->fBCC)->desc02()->m2B((PlacedObject*)self->fBCC);
    TransformPointBetweenFrames(0, (PlacedObject*)self->fBC0, (Vec02*)((u8*)self->fBCC + 0x140), (Vec02*)((u8*)self + 0xBE0));
    SetModeWalkerMode(self, 1);
    self->paceChangeTime = 3.4028234663852886e+38f;
    u8* base = (u8*)&g_spinningSpriteElement;
    ((T217D_Float*)(base + 0x598))->v = 0.0f;
    *(s32*)(base + 0x594) = FindAnimRecord(0x36A);
}

