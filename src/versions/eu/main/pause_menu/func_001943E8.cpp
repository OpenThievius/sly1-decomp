// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: self/hud fields 0x310 further on, camera clamps 438..874 and 15..129 at PAL-only floats, per-language text ids (157..161) through func_eu_001DDAB0, and a text-scan in menu 20
struct Self_1943E8_eu {
    u8 pad0[0x560];
    s32 f560;
    f32 f564;
    u8 pad568[0x570 - 0x568];
    s32 f570;
    s32 f574;
    u8 pad578[0x584 - 0x578];
    s32 f584;
    u8 pad588[0x58C - 0x588];
    s32 f58C;
    u8 pad590[0x598 - 0x590];
    s32 f598;
};
struct Hud_1943E8_eu {
    void** vt;
    u8 pad4[0x574 - 0x4];
    s32* f574;
    u8 pad578[0x58C - 0x578];
    s32 f58C;
};
void func_00194D30(Self_1943E8_eu* self, s32 a, s32 b);
void func_00195958(Self_1943E8_eu* self);
void func_001961C0(Self_1943E8_eu* self);
extern CardSlot D_eu_00255538[];
extern f32 D_eu_0026BB30;
extern f32 D_eu_0026BB34;
extern u8 D_eu_00263550[];
extern u16 D_eu_00263558[];
const char* func_eu_001DDAB0(s32 id);
#define HUD_EU ((Hud_1943E8_eu*)&D_00274118)
void func_001943E8(Self_1943E8_eu* self)
{
    GameProgress* g = g_saveData;
    MenuPage* row = &g_pauseMenuPages[self->f570];
    s32 on;
    s32 n;
    PadRecord* pad;

    on = 0;
    switch ((g->f19D8 << 8) | g->f19DC) {
    case 0x106:
    case 0x204:
    case 0x304:
    case 0x307:
    case 0x407:
    case 0x502:
    case 0x504:
        break;
    default:
        on = self->f570 == 0;
        break;
    }
    if (on) {
        D_0026C6C8.vt->m14(&D_0026C6C8);
        D_0026C948.vt->m14(&D_0026C948);
        D_0026CBC8.vt->m14(&D_0026CBC8);
        D_0026CE48.vt->m14(&D_0026CE48);
    } else {
        D_0026C6C8.vt->m15(&D_0026C6C8);
        D_0026C948.vt->m15(&D_0026C948);
        D_0026CBC8.vt->m15(&D_0026CBC8);
        D_0026CE48.vt->m15(&D_0026CE48);
    }
    switch (self->f570) {
    case 0:
    case 11:
    case 17:
        HUD_EU->f58C = ComputeCompletionPercent(g_saveData);
        HUD_EU->f574 = &HUD_EU->f58C;
        D_00274118.vt->m14(&D_00274118);
        break;
    default:
        D_00274118.vt->m15(&D_00274118);
        break;
    }
    if (self->f598 != 0) {
        if (func_001BE810() != 0) {
            PollIopCommands();
        }
        self->f598 = HasStreamVoice();
    }
    s32 ready = 1;
    if (self->f584 != 0 || self->f560 != 2 || !(0.1f < g_elapsedTime - self->f564)) {
        ready = 0;
    }
    pad = &g_padRecord;
    if (row->count == 0) {
        n = 0;
    } else if (row->vertical != 0) {
        n = GetPadVerticalStep(pad);
    } else {
        n = GetPadHorizontalStep(pad);
    }
    if (n > 0) {
        self->f574 = (self->f574 + 1) % row->count;
        StartSoundEffect(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    if (n < 0) {
        self->f574 = (self->f574 + row->count - 1) % row->count;
        StartSoundEffect(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    if (!ready) {
        return;
    }
    if (pad->flags & 0x810) {
        ClearPadPressedBits(&g_padRecord, 0x810);
        CancelPauseMenuPage(self);
        return;
    }
    if (pad->flags & 0x80) {
        ClearPadPressedBits(&g_padRecord, 0x80);
        if (self->f570 == 11 || self->f570 == 16) {
            CardSlot* e = &D_eu_00255538[row->items[self->f574]];
            if (e->f0C != 0.0f) {
                D_0026998C = e;
                SetPauseMenuLayerPage(self, 1, 0x12);
            }
        }
        return;
    }
    if (pad->flags & 0x40) {
        ClearPadPressedBits(&g_padRecord, 0x40);
        ActivatePauseMenuSelection(self);
        return;
    }
    switch (self->f570) {
    case 24: {
        f32 a = GetPadButtonAnalog(pad, 0);
        f32 dx = a - GetPadButtonAnalog(pad, 1);
        f32 b = GetPadButtonAnalog(pad, 3);
        f32 dy = b - GetPadButtonAnalog(pad, 2);
        f32 v;
        if (dx == 0.0f && dy == 0.0f) {
            return;
        }
        D_eu_0026BB30 = ClampFloat::Of(D_eu_0026BB30 + dx * D_0026A22C, 438.0f, 874.0f);
        v = ClampFloat::Of(D_eu_0026BB34 + dy * D_0026A230.f0, 15.0f, 129.0f);
        D_eu_0026BB34 = v;
        {
            DisplayRegs* gs = &D_00262490;
            s32 h = func_001FD7A0(D_eu_0026BB30);
            DisplayReg64 ra = gs->f40;
            DisplayReg32 rb = gs->f18;
            ra.lo = h;
            rb.lo = h;
            gs->f40 = ra;
            gs->f18 = rb;
            s32 w = func_001FD7A0(v);
            ra.mid = w & ~1;
            rb.mid = w & 0x7FE;
            gs->f40 = ra;
            gs->f18 = rb;
        }
        break;
    }
    case 11:
    case 16:
    case 17:
        if (g_memoryCard.displayMode != 1) {
            CancelPauseMenuPage(self);
            return;
        } else {
            s32 id = row->items[self->f574];
            if ((u32)(id - 10) < 3) {
                CardSlot* e = &D_eu_00255538[id];
                if (self->f570 == 16) {
                    if (e->f0C != 0.0f) { g_buttonHintElement.vt->m08(&g_buttonHintElement, func_eu_001DDAB0(157)); } else { g_buttonHintElement.vt->m08(&g_buttonHintElement, func_eu_001DDAB0(158)); }
                } else if (self->f570 == 17) {
                    if (e->f0C != 0.0f) { g_buttonHintElement.vt->m08(&g_buttonHintElement, func_eu_001DDAB0(159)); } else { g_buttonHintElement.vt->m08(&g_buttonHintElement, func_eu_001DDAB0(158)); }
                } else {
                    if (e->f0C != 0.0f) { g_buttonHintElement.vt->m08(&g_buttonHintElement, func_eu_001DDAB0(160)); } else { g_buttonHintElement.vt->m08(&g_buttonHintElement, func_eu_001DDAB0(161)); }
                }
                g_buttonHintElement.vt->m14(&g_buttonHintElement);
            } else {
                g_buttonHintElement.vt->m15(&g_buttonHintElement);
            }
        }
        break;
    case 18:
        if (g_memoryCard.displayMode != 1) {
            CancelPauseMenuPage(self);
        }
        break;
    case 20: {
        u16* p;
        s32 found;
        if (g_memoryCard.displayMode != 1) {
            CancelPauseMenuPage(self);
        }
        found = 0;
        p = (u16*)func_eu_001DDAB0((s32)row->title);
        for (;;) {
            u16 c = p[0];
            u16 d;
            if (c == 0) {
                break;
            }
            d = p[1];
            if (d == 0) {
                break;
            }
            if (c == 38 && (d == D_eu_00263558[1] || d == D_eu_00263550[1])) {
                found = 1;
                break;
            }
            p++;
        }
        if (found) {
            p[2] = GetCyclingGlyph();
        }
        break;
    }
    case 3:
    case 4:
    case 7:
    case 10:
    case 32:
        if (D_00264A4C == 5) {
            SetPauseMenuLayerPage((Self_1943E8_eu*)&g_pauseMenuElement, 1, -1);
        }
        break;
    case 5: {
        BackgroundJob* p = &g_backgroundJob;
        if (IsBackgroundJobRunning(p) == 0) {
            if (p->result == 0) {
                StartBackgroundJob(p, (void*)(void (*)(MemoryCard*))CreateMemoryCardSaveFiles, ((u8*)&g_memoryCard));
                SetPauseMenuLayerPage(self, 1, 8);
            } else {
                SetPauseMenuLayerPage(self, 1, 6);
            }
        }
        break;
    }
    case 8: {
        BackgroundJob* p = &g_backgroundJob;
        if (IsBackgroundJobRunning(p) == 0) {
            if (p->result == 0) {
                SetPauseMenuLayerPage(self, 1, -1);
            } else {
                SetPauseMenuLayerPage(self, 1, 9);
            }
        }
        break;
    }
    case 12: {
        BackgroundJob* p = &g_backgroundJob;
        if (IsBackgroundJobRunning(p) == 0) {
            if (p->result == 0) {
                SetPauseMenuLayerPage(self, 1, -1);
                if (self->f58C == 2) {
                    func_00194398();
                }
            } else {
                SetPauseMenuLayerPage(self, 0, 0x17);
                SetPauseMenuLayerPage(self, 1, 0xF);
            }
        }
        break;
    }
    case 19: {
        BackgroundJob* p = &g_backgroundJob;
        if (IsBackgroundJobRunning(p) == 0) {
            D_0026998C = 0;
            if (p->result == 0) {
                SetPauseMenuLayerPage(self, 1, -1);
            } else {
                SetPauseMenuLayerPage(self, 0, 0x17);
                SetPauseMenuLayerPage(self, 1, 0xF);
            }
        }
        break;
    }
    }
}
