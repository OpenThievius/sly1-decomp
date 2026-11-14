// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the four global pointer slots are 0x310 further in (0x574, 0x578 instead of 0x264, 0x268).
void HandlePathFollowerActivation(PathFollower* self, void* v)
{
    HandleSwitchedColliderActivation(self, v);
    if (v != 0) {
        u8* a = (u8*)&g_pathFollowerFirstCountCaption;
        *(void**)(D_0026DAAC) = (u8*)self + 0x858;
        u8* b = (u8*)&g_pathFollowerSecondCountCaption;
        *(void**)(a + 0x574) = (u8*)self + 0xB00;
        *(void**)(a + 0x578) = (u8*)self + 0xB04;
        *(void**)(b + 0x574) = (u8*)self + 0xB08;
        *(void**)(b + 0x578) = (u8*)self + 0xB0C;
        SetWorldActiveFollower((World*)(*(void**)((u8*)self + 0x14)), self);
    } else {
        if (self->mode == 2) {
            SetPathFollowerMode(self, 0);
        }
    }
}
