// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the fields of self are at 0x560, 0x570, 0x58C and 0x590 (US 0x250, 0x260, 0x27C, 0x280).
struct Obj_1F1A08_eu {
    u8 pad0[0x560];
    s32 f560;
    u8 pad1[0x570 - 0x564];
    WarpPage* f570;
    u8 pad2[0x58C - 0x574];
    f32 f58C;
    f32 f590;
};

void HandleWarpMenuInput(Obj_1F1A08_eu* self, PadRecord* t)
{
    s32 loc[2];
    s32 s3;
    s32 s2;
    s32 v1;

    if (self->f570 == 0) return;
    if (self->f570->mode != 2) return;
    if (self->f570->f560 != 0) return;
    if ((t->flags & 0x910) != 0 || t->connectionMode == 1) {
        PopStackElement((ElementStack*)g_elementStack);
        ClearPadPressedBits(&g_padRecord, 0x910);
        return;
    }
    if (self->f560 != self->f570->mode) return;

    s3 = IsWarpEntryAvailable(self->f570, self->f570->cursor, &loc[0], &loc[1]);
    s2 = GetPadHorizontalStep(t);
    v1 = GetPadVerticalStep(t);
    t->nextStepTimeX = g_gameClock.elapsed + t->stepDelayX;
    t->nextStepTimeY = g_gameClock.elapsed + t->stepDelayY;

    if (v1 < 0) {
        MoveWarpCursor(self->f570, 0);
    } else if (v1 > 0) {
        MoveWarpCursor(self->f570, 1);
    } else if (s2 < 0) {
        MoveWarpCursor(self->f570, 2);
    } else if (s2 > 0) {
        MoveWarpCursor(self->f570, 3);
    } else if ((t->flags & 0x40) != 0) {
        ClearPadPressedBits(&g_padRecord, 0x40);
        if (self->f570->cursor != GetCurrentWarpEntry()) {
            if (s3 != 0) {
                IdentityKey* v = LookupEntryById((loc[0] << 8) | loc[1]);
                self->f570->f560 = 1;
                PopStackElement((ElementStack*)g_elementStack);
                StartObjectFade(v, -1, 2);
            } else {
                StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        } else {
            PopStackElement((ElementStack*)g_elementStack);
        }
    }

    if (s3 != 0) {
        self->f590 = 1.0f;
    } else {
        self->f590 = D_00275FC0;
    }
    self->f58C = ApproachValueWithRamp((RampProfile*)D_00276278, 0, self->f58C, self->f590, g_gameClock.step);
}
