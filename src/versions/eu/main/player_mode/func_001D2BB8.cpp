// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: D_002701F8's mode and state are at 0x560 and 0x570 (US 0x250 and 0x260).
struct CaptionBox_1D2BB8_eu { u8 pad0[0x560]; s32 mode; u8 pad564[0x570 - 0x564]; s32 state; };

void UpdateModeSelection(Player* self, PadRecord* pad)
{
    s32 ok;
    if (g_currentMode >= 0) {
        if ((g_modeMasks[g_currentMode] & MaskWorldBitsBySave()) == 0) {
            ShowModeLabel(-1);
            g_saveData->lastHintMode = -1;
        }
    }
    switch (g_currentMode) {
    case -1:
        ok = 1;
        break;
    case 2:
    case 4:
        ok = AreFloatsNearlyEqual(g_stepScale, 1.0f, 0.0001f);
        break;
    case 1:
        ok = 0;
        if (g_player == 0 || g_player->state != 13) {
            ok = 1;
        }
        break;
    case 0:
        ok = 0;
        if (g_player == 0) {
            ok = 1;
            break;
        }
        {
            s32 state = g_player->state;
            if (state == 10) {
                break;
            }
            if (state == 2 && g_player->subState == 8) {
                break;
            }
        }
        ok = 1;
        break;
    case 5:
        ok = g_player->state != 14;
        break;
    case 6:
        ok = 0;
        if (g_player->state != 15) {
            ok = g_player->animSeekValue == 0;
        }
        break;
    case 3:
        ok = g_player->state != 16;
        break;
    }
    if (g_player != 0 && g_player->state == 4) {
        ok = 0;
    }
    if (((CaptionBox_1D2BB8_eu*)&g_typedTextCaptionBox)->mode != 0) {
        ok = 0;
    }
    if (ok && (pad->flags & 3)) {
        s32 m = FindNextTableIndexMatchingMask(pad, g_currentMode, 7, g_modeMasks);
        g_saveData->lastHintMode = -1;
        ShowModeLabel(m);
    }
    switch (g_currentMode) {
    case 4:
        if (((CaptionBox_1D2BB8_eu*)&g_typedTextCaptionBox)->state == 3) {
            self->speedUpAmount = 0.0f;
        } else if (pad->buttons & 0x10) {
            self->speedUpAmount = 1.0f;
        } else {
            self->speedUpAmount = ApproachValueWithRamp((RampProfile*)D_00274F78, 0, self->speedUpAmount, 0.0f, g_frameStep);
        }
        g_stepScale = self->speedUpAmount * D_00274F84 + (1.0f - self->speedUpAmount);
        break;
    case 2:
        if (g_padSelectFlags & 3) {
            self->slowDownHeld = 0;
        } else if (((CaptionBox_1D2BB8_eu*)&g_typedTextCaptionBox)->state == 3) {
            self->slowDownHeld = 0;
        } else if (self->state == 2) {
            if (pad->flags & 0x10) {
                ClearPadPressedBits(pad, 0x10);
                self->slowDownHeld = 1;
            }
        } else if (pad->buttons & 0x10) {
            if (MaskWorldBitsBySave() & 0x1000) {
                self->slowDownHeld = 1;
            } else {
                self->slowDownHeld = 0;
            }
        } else {
            self->slowDownHeld = 0;
        }
        if (self->slowDownHeld != 0) {
            g_stepScale = D_00274F88[0];
        } else {
            g_stepScale = 1.0f;
        }
        break;
    case 1:
        switch (self->state) {
        case 0:
        case 1:
        case 2:
            if (pad->flags & 0x10) {
                ClearPadPressedBits(pad, 0x10);
                if (self->groundContact != 0) {
                    SetPlayerState(self, 13, 0x37);
                } else {
                    SetPlayerState(self, 13, 0x36);
                }
            }
        }
        break;
    case 5:
        if ((u32)self->state < 2 && (pad->flags & 0x10) && self->contactOwner != 0) {
            ClearPadPressedBits(pad, 0x10);
            SetPlayerState(self, 14, -1);
        }
        break;
    case 6:
        if ((u32)self->state < 2) {
            if (pad->flags & 0x10) {
                ClearPadPressedBits(pad, 0x10);
                SetPlayerState(self, 15, -1);
            }
        }
        if (self->animSeekValue != 0 && 3.0f < g_gameClock.time - self->animSeekTime) {
            SeekObjects105Animations(self, 0);
        }
        break;
    case 3:
        if ((u32)self->state < 2 && (pad->flags & 0x10) && self->f1518 != 0) {
            ClearPadPressedBits(pad, 0x10);
            if (IsObjectAttached((BaseObject*)self->f1518)) {
                Vec02 d;
                Vu0::Q(d) = Vu0::Sub(Vu0::Q(((PlacedObject*)self->f1518)->v140), Vu0::Q(self->v140));
                self->heading = ArctangentOfRatio(d.y, d.x);
                TurnColliderTowardHeading(self);
                SetPlayerState(self, 16, 0x3A);
            } else {
                SetPlayerState(self, 16, 0x39);
            }
        }
        break;
    }
}
