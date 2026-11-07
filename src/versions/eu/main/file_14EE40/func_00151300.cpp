// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: D_002708E0/D_00271558 Hld fields at 0x578 and 0x580 (US 0x268, 0x270); D_002701F8 Sc fields at 0x584 and 0x58C (US 0x2F8, 0x300).
struct Hld_151300_eu { u8 pad[0x578]; s32 f578; u8 pad2[4]; s32 f580; };
struct Sc_151300_eu { u8 pad[0x584]; u8 f584; u8 pad2[7]; f32 f58C; };

s32 func_00151300(StepSequence* self)
{
    s32 flags = self->f2E8;
    if (flags & 2) {
        SequenceStep* e = self->step2E4 < self->count2DC - 1 ? &((SequenceStep*)self->steps2E0)[self->step2E4 + 1] : 0;
        if (e != 0 && e->type == 2) {
            if (flags == 2) return 0;
        }
        if (((Hld_151300_eu*)&D_002708E0)->f580 == self->f2F0 && ((Hld_151300_eu*)&D_002708E0)->f578 == 1) flags &= 0xFFFFFFFD;
    }
    if (flags & 4) {
        SequenceStep* e = self->step2E4 < self->count2DC - 1 ? &((SequenceStep*)self->steps2E0)[self->step2E4 + 1] : 0;
        if (e != 0 && e->type == 1 && flags == 4) return 0;
        if (((Hld_151300_eu*)&D_00271558)->f580 == self->f2F4 && ((Hld_151300_eu*)&D_00271558)->f578 == 1) flags &= 0xFFFFFFFB;
    }
    if (flags & 1) {
        if (func_001BE810() == 0) flags &= 0xFFFFFFFE;
    }
    if (flags & 8) {
        if (HasStreamVoice() == 0) flags &= 0xFFFFFFF7;
    }
    if (flags & 0x10) {
        if (self->value2F8 == 0) flags &= 0xFFFFFFEF;
    }
    if (flags & 0x20) {
        if (IsTextPanelTextTyped(&g_typedTextCaptionBox) != 0) flags &= 0xFFFFFFDF;
    }
    if (flags & 0x40) {
        if (g_camera->ctl460.g18 == ((Sc_151300_eu*)&g_typedTextCaptionBox)->f58C) flags &= 0xFFFFFFBF;
    }
    if (flags & 0x80) {
        if (self->f2FC <= g_gameTime[0]) flags &= 0xFFFFFF7F;
    }
    ((Sc_151300_eu*)&g_typedTextCaptionBox)->f584 = 0;
    if (flags == 0x100) {
        s32 r;
        PadRecord* in = (g_padRouting & 4) ? &g_padRecord : &g_blankPadRecord;
        s32 k = self->f2EC;
        r = 0;
        switch (k) {
        case 9:
            if (0.8f < in->f48) r = 1;
            break;
        case 10:
            if (0.8f < in->f7C) r = 1;
            break;
        case 11:
            if (0.8f < __builtin_fabsf(in->f40)) r = 1;
            break;
        case 12:
            if (0.8f < __builtin_fabsf(in->f44)) r = 1;
            break;
        case 13:
            if (g_player != 0 && g_player->f2220 == 2) r = g_player->f2228 == 3;
            break;
        case 14:
        {
            G27C230* fl = g_currentEntry;
            u32 t = fl->bits & 4;
            r = t != 0;
        }
            break;
        default:
            r = (in->flags & D_00261D08[k]) != 0;
            break;
        }
        if (r != 0) {
            flags = 0;
        } else {
            ((Sc_151300_eu*)&g_typedTextCaptionBox)->f584 = D_00261D28[k];
        }
    }
    self->f2E8 = flags;
    return flags != 0;
}

