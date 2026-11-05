// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: D_0026FF68 fields f25C and f268 are at 0x56C and 0x578 (US 0x25C, 0x268).
struct Glob_18BDC8_eu { u8 pad0[0x56C]; s32 f56C; u8 pad570[8]; s32 f578; };

void func_0018BDC8(MemoryCard* self)
{
    if (func_0018B770(&g_backgroundJob) != 0) return;
    if (self->state == self->targetState) {
        if (self->nextPollTime <= D_00261868[0])
            func_0018B670(&g_backgroundJob, (void*)func_0018D0A0, self);
    } else {
        func_0018C028(self, self->targetState);
    }
    if (func_0018B770(&g_backgroundJob) != 0) return;
    if (self->displayMode == 1 && D_00261868[0] - self->stateTime >= 0.3f) {
        if (self->i4F44 != 0) {
            if (self->state != 5) func_00194D30(D_0026FF68, 1, 0x15);
        } else if (((Glob_18BDC8_eu*)D_0026FF68)->f56C != 0 && ((Glob_18BDC8_eu*)D_0026FF68)->f578 == 0x11) {
            if (self->state != 5) func_00194D30(D_0026FF68, 1, 0x20);
        } else {
            switch (self->state) {
            case 1: func_00194D30(D_0026FF68, 1, 3); break;
            case 2: func_00194D30(D_0026FF68, 1, 4); break;
            case 3: func_00194D30(D_0026FF68, 1, 7); break;
            case 4: func_00194D30(D_0026FF68, 1, 10); break;
            }
        }
    }
}

