// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the Gx object's field is at 0x58C (not 0x27C) and the packed word at 0x570 (not 0x260).
struct Gx_18C7F8_eu { u8 pad0[0x58C]; s32 f58C; };

void func_0018C7F8(MemoryCard* self)
{
    if (self->i4F44 != 0) {
        if ((g_saveData->f19EC & 0x100) == 0) {
            ((Gx_18C7F8_eu*)g_pauseMenuElement)->f58C = -1;
            SetPauseMenuLayerPage(g_pauseMenuElement, 1, 0x14);
        } else {
            StartBackgroundJob(g_backgroundJob, (void*)SaveGameToMemoryCardSlot, self);
            u8* obj = (u8*)D_00273EB0;
            ((Pk_18C7F8*)(obj + 0x570))->v = 0;
            ((Obj_18C7F8*)obj)->vtbl[14](obj);
        }
    }
}
