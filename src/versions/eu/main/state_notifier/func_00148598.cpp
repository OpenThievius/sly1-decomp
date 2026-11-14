// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL always increments the counter at 0x438 (no D_00275C34 check).
void SetSaveNotifierState(SaveNotifier* self, s32 mode)
{
    if (self->state == mode) return;
    if (mode == 1) {
        G27C230* fl = g_currentEntry;
        s32 bits = fl->flags;
        if ((bits & 2) == 0) {
            fl->flags = bits | 2;
            g_currentLevelRecord->f438++;
        }
        D_0026CBC8.vt->m14(&D_0026CBC8);
        SwitchedCollider* r = GetActiveSwitchedCollider();
        if (r != 0) {
            r->desc05()->m4E(r, 0, self);
        }
        TriggerScriptEvent(self, 2, 0, 0);
        mode = 2;
        ResetScatterLevels((ScatterController*)g_scatterController);
        StartMemoryCardSave((MemoryCard*)g_memoryCard);
    }
    SetStateNotifierState((Camera*)self, mode);
}
