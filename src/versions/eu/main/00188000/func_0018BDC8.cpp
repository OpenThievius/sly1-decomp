// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: D_0026FF68 fields f25C and f268 are at 0x56C and 0x578 (US 0x25C, 0x268).
struct Glob_18BDC8_eu { u8 pad0[0x56C]; s32 f56C; u8 pad570[8]; s32 f578; };

void func_0018BDC8(MemoryCard* self)
{
    if (IsBackgroundJobRunning(&g_backgroundJob) != 0) return;
    if (self->state == self->targetState) {
        if (self->nextPollTime <= g_elapsedTime[0])
            StartBackgroundJob(&g_backgroundJob, (void*)PollMemoryCard, self);
    } else {
        SetMemoryCardState(self, self->targetState);
    }
    if (IsBackgroundJobRunning(&g_backgroundJob) != 0) return;
    if (self->displayMode == 1 && g_elapsedTime[0] - self->stateTime >= 0.3f) {
        if (self->i4F44 != 0) {
            if (self->state != 5) SetPauseMenuLayerPage(g_pauseMenuElement, 1, 0x15);
        } else if (((Glob_18BDC8_eu*)g_pauseMenuElement)->f56C != 0 && ((Glob_18BDC8_eu*)g_pauseMenuElement)->f578 == 0x11) {
            if (self->state != 5) SetPauseMenuLayerPage(g_pauseMenuElement, 1, 0x20);
        } else {
            switch (self->state) {
            case 1: SetPauseMenuLayerPage(g_pauseMenuElement, 1, 3); break;
            case 2: SetPauseMenuLayerPage(g_pauseMenuElement, 1, 4); break;
            case 3: SetPauseMenuLayerPage(g_pauseMenuElement, 1, 7); break;
            case 4: SetPauseMenuLayerPage(g_pauseMenuElement, 1, 10); break;
            }
        }
    }
}

