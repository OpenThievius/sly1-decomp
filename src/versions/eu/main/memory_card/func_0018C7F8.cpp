// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the Gx object's field is at 0x58C (not 0x27C) and the packed word at 0x570 (not 0x260).
struct Gx_18C7F8_eu { u8 pad0[0x58C]; s32 f58C; };

void StartMemoryCardSave(MemoryCard* self)
{
    if (self->i4F44 != 0) {
        if ((g_saveData->optionFlags & 0x100) == 0) {
            ((Gx_18C7F8_eu*)&g_pauseMenuElement)->f58C = -1;
            SetPauseMenuLayerPage(&g_pauseMenuElement, 1, 0x14);
        } else {
            StartBackgroundJob(&g_backgroundJob, (void*)SaveGameToMemoryCardSlot, self);
            u8* obj = (u8*)&D_00273EB0;
            ((T217D_Word*)(obj + 0x570))->v = 0;
            ((ScreenElement*)obj)->vt->m14((ScreenElement*)obj);
        }
    }
}
