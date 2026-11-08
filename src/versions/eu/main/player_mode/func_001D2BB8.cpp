// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: D_002701F8's mode and state are at 0x560 and 0x570 (US 0x250 and 0x260).
struct CaptionBox_1D2BB8_eu { u8 pad0[0x560]; s32 mode; u8 pad564[0x570 - 0x564]; s32 state; };

void func_001D2BB8(Player* self, PadRecord* pad)
{
    s32 ok;
    if (g_currentMode >= 0) {
        if ((g_modeMasks[g_currentMode] & MaskWorldBitsBySave()) == 0) {
            ShowModeLabel(-1);
            g_saveData->f19FC = -1;
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
        if (g_player == 0 || g_player->f2220 != 13) {
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
            s32 state = g_player->f2220;
            if (state == 10) {
                break;
            }
            if (state == 2 && g_player->f2228 == 8) {
                break;
            }
        }
        ok = 1;
        break;
    case 5:
        ok = g_player->f2220 != 14;
        break;
    case 6:
        ok = 0;
        if (g_player->f2220 != 15) {
            ok = g_player->f275C == 0;
        }
        break;
    case 3:
        ok = g_player->f2220 != 16;
        break;
    }
    if (g_player != 0 && g_player->f2220 == 4) {
        ok = 0;
    }
    if (((CaptionBox_1D2BB8_eu*)&g_typedTextCaptionBox)->mode != 0) {
        ok = 0;
    }
    if (ok && (pad->flags & 3)) {
        s32 m = FindNextTableIndexMatchingMask(pad, g_currentMode, 7, g_modeMasks);
        g_saveData->f19FC = -1;
        ShowModeLabel(m);
    }
    switch (g_currentMode) {
    case 4:
        if (((CaptionBox_1D2BB8_eu*)&g_typedTextCaptionBox)->state == 3) {
            self->f2748 = 0.0f;
        } else if (pad->keyA8 & 0x10) {
            self->f2748 = 1.0f;
        } else {
            self->f2748 = ApproachValueWithRamp(D_00274F78, 0, self->f2748, 0.0f, g_frameStep);
        }
        g_stepScale = self->f2748 * D_00274F84 + (1.0f - self->f2748);
        break;
    case 2:
        if (g_padSelectFlags & 3) {
            self->f2744 = 0;
        } else if (((CaptionBox_1D2BB8_eu*)&g_typedTextCaptionBox)->state == 3) {
            self->f2744 = 0;
        } else if (self->f2220 == 2) {
            if (pad->flags & 0x10) {
                ClearPadPressedBits(pad, 0x10);
                self->f2744 = 1;
            }
        } else if (pad->keyA8 & 0x10) {
            if (MaskWorldBitsBySave() & 0x1000) {
                self->f2744 = 1;
            } else {
                self->f2744 = 0;
            }
        } else {
            self->f2744 = 0;
        }
        if (self->f2744 != 0) {
            g_stepScale = D_00274F88[0];
        } else {
            g_stepScale = 1.0f;
        }
        break;
    case 1:
        switch (self->f2220) {
        case 0:
        case 1:
        case 2:
            if (pad->flags & 0x10) {
                ClearPadPressedBits(pad, 0x10);
                if (self->f690 != 0) {
                    SetPlayerState(self, 13, 0x37);
                } else {
                    SetPlayerState(self, 13, 0x36);
                }
            }
        }
        break;
    case 5:
        if ((u32)self->f2220 < 2 && (pad->flags & 0x10) && self->f2750 != 0) {
            ClearPadPressedBits(pad, 0x10);
            SetPlayerState(self, 14, -1);
        }
        break;
    case 6:
        if ((u32)self->f2220 < 2) {
            if (pad->flags & 0x10) {
                ClearPadPressedBits(pad, 0x10);
                SetPlayerState(self, 15, -1);
            }
        }
        if (self->f275C != 0 && 3.0f < g_gameClock.time - self->f2758) {
            SeekObjects105Animations(self, 0);
        }
        break;
    case 3:
        if ((u32)self->f2220 < 2 && (pad->flags & 0x10) && self->f1518 != 0) {
            ClearPadPressedBits(pad, 0x10);
            if (IsObjectAttached((PlayerHeldObject*)self->f1518)) {
                Vec02 d;
                Vu0::Q(d) = Vu0::Sub(Vu0::Q(((PlacedObject*)self->f1518)->v140), Vu0::Q(self->v140));
                self->f638 = ArctangentOfRatio(d.y, d.x);
                TurnColliderTowardHeading(self);
                SetPlayerState(self, 16, 0x3A);
            } else {
                SetPlayerState(self, 16, 0x39);
            }
        }
        break;
    }
}
