// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL always increments the counter at 0x438 (no D_00275C34 check).
void func_00148598(C59* self, s32 mode)
{
    if (self->state == mode) return;
    if (mode == 1) {
        G27C230* fl = g_currentEntry;
        s32 bits = fl->flags;
        if ((bits & 2) == 0) {
            fl->flags = bits | 2;
            g_currentLevelRecord->f438++;
        }
        VObj_148598* vo = (VObj_148598*)&D_0026CBC8;
        vo->vtbl[14](vo);
        void* r = (void*)GetActiveSwitchedCollider();
        if (r != 0) {
            ((VObj3_148598*)r)->vtbl[82](r, 0, self);
        }
        TriggerScriptEvent(self, 2, 0, 0);
        mode = 2;
        func_00151FC8(D_00261EF0);
        StartMemoryCardSave(g_memoryCard);
    }
    SetStateNotifierState(self, mode);
}
