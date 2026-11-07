// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: menu fields 0x310 further on, menu 15 joins the closing group, a per-language title string, and two new menus (33, 34); the entry table sits at 0x255538, which the tools cannot pair with US's D_002542D8.
struct Menu_195958_eu {
    u8 pad0[0x570];
    s32 f260;
    s32 f264;
    s32 f268;
    u8 pad1[0x27C - 0x26C];
    s32 f27C;
    s32 f280;
};
struct Sub_195958_eu {
    u8 pad0[0x570];
    s32 f260;
};

extern u8 D_eu_00249050[][32];
extern s32 D_eu_00263710;
extern s32 D_eu_00263624;
extern Ent_195958 D_eu_00255538[];

void func_001961C0(Menu_195958_eu* self);
void func_00194D30(Menu_195958_eu* self, s32 a, s32 b);
void func_00194278(Menu_195958_eu* self, s32 a, s32 b);
void func_001936A0(Menu_195958_eu* self);
void func_001E9498(u8* a, Sub_195958_eu* b);
void func_eu_00160620(s32 a);
u8* func_eu_00160788(s32 a);

void func_00195958(Menu_195958_eu* self)
{
    s32 sel = g_pauseMenuPages[self->f260].items ? g_pauseMenuPages[self->f260].items[self->f264] : -1;
    if (sel == 0x11) {
        CancelPauseMenuPage(self);
        return;
    }
    switch (self->f260) {
    case 0:
        switch (sel) {
        case 3:
            SetPauseMenuLayerPage(self, 0, -1);
            return;
        case 4: {
            Sub_195958_eu* s = (Sub_195958_eu*)&g_mapScreenList;
            if (s->f260 != 0) {
                SetPauseMenuLayerPage(self, 0, -1);
                PushStackElement(g_elementStack, s);
                return;
            }
            StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            return;
        }
        case 18: {
            s32 v;
            void* s2 = (void*)func_00193660();
            void* s0 = GetActiveSwitchedCollider();
            if (s2 != 0 && s0 != 0 && IsObjectOfKind(s0, 0x19) != 0) {
                func_001B6598(s2, &v);
                if (v < 0x431) {
                    if (v >= 0x42F) {
                        RecordPathFollowerProgress(s0);
                        TeleportStateWalker(s2, 0x42E);
                    }
                }
            }
            SetPauseMenuLayerPage(self, 0, -1);
            return;
        }
        case 19:
        case 20:
            ExitLevelFromPauseMenu(self, 1, 1);
            return;
        case 21:
            SetPauseMenuLayerPage(self, 0, -1);
            func_001F4408(1, 2);
            return;
        case 22:
            SetPauseMenuLayerPage(self, 0, -1);
            StartObjectFade(D_eu_00249050[D_eu_00263710], -1, 2);
            return;
        case 9:
            SetPauseMenuLayerPage(self, 0, 2);
            return;
        case 5:
            SetPauseMenuLayerPage(self, 0, 0x17);
            return;
        case 23:
            SetPauseMenuLayerPage(self, 0, 0x1F);
            return;
        }
        return;
    case 23:
        switch (sel) {
        case 6:
            SetMemoryCardDisplayMode(&g_memoryCard, 1);
            SetPauseMenuLayerPage(self, 0, 0x10);
            return;
        case 7:
            SetMemoryCardDisplayMode(&g_memoryCard, 1);
            SetPauseMenuLayerPage(self, 0, 0x11);
            return;
        case 8:
            SetMemoryCardDisplayMode(&g_memoryCard, 1);
            SetPauseMenuLayerPage(self, 0, 0xB);
            return;
        case 13:
            TogglePadPatternSetting(g_saveData);
            {
                s32 keep;
                keep = self->f264;
                func_001936A0(self);
                self->f264 = keep;
            }
            return;
        case 15: {
            GameProgress* g = g_saveData;
            g->u19EC ^= 0x80;
            func_001C0760(g->u19EC & 0x80);
            {
                s32 keep;
                keep = self->f264;
                func_001936A0(self);
                self->f264 = keep;
            }
            return;
        }
        case 16: {
            GameProgress* g = g_saveData;
            g->u19EC ^= 0x40;
            func_001C0790(g->u19EC & 0x40);
            {
                s32 keep;
                keep = self->f264;
                func_001936A0(self);
                self->f264 = keep;
            }
            return;
        }
        case 14:
            SetPauseMenuLayerPage(self, 0, 0x18);
            return;
        case 23:
            SetPauseMenuLayerPage(self, 0, 0x1F);
            return;
        }
        return;
    case 27:
        if ((ComputeCompletionMask() & 8) != 0) {
            FadeOutAndQueueMovie(8);
            return;
        }
        ExitLevelFromPauseMenu(self, 0, 2);
        return;
    case 1:
    case 26:
    case 28:
    case 29:
    case 30:
        ExitLevelFromPauseMenu(self, (u32)sel < 1, 1);
        return;
    case 25: {
        s32 a = self->f280;
        self->f280 = 0;
        SetStateWalkerTarget(a, sel == 0 ? 0x434 : 0x435);
        SetPauseMenuLayerPage(self, 0, -1);
        return;
    }
    case 2:
        if (sel == 0) {
            MemoryCard* b = &g_memoryCard;
            if (b->f4F44 != 0) {
                self->f27C = 2;
                if ((g_saveData->u19EC & 0x100) == 0) {
                    SetPauseMenuLayerPage(self, 1, 0x14);
                } else {
                    SetPauseMenuLayerPage(self, 1, 0xC);
                    StartBackgroundJob(&g_backgroundJob, (void*)SaveGameToMemoryCardSlot, b);
                }
            } else {
                func_00194398();
            }
            SetPauseMenuLayerPage(self, 0, -1);
            return;
        }
        SetPauseMenuLayerPage(self, 0, -1);
        return;
    case 31:
        switch (sel) {
        case 0x18: {
            g_saveData->u19EC ^= 0x200;
            s32 keep = self->f264;
            func_001936A0(self);
            self->f264 = keep;
            return;
        }
        case 0x19: {
            g_saveData->u19EC ^= 0x400;
            s32 keep = self->f264;
            func_001936A0(self);
            self->f264 = keep;
            return;
        }
        case 0x1A: {
            g_saveData->u19EC ^= 0x800;
            s32 keep = self->f264;
            func_001936A0(self);
            self->f264 = keep;
            return;
        }
        }
        return;
    case 33:
        SetPauseMenuLayerPage(self, 0, -1);
        if (sel >= 0x22) {
            break;
        }
        if (sel < 0x1B) {
            return;
        }
        func_eu_00160620(sel - 0x1B);
        StartObjectFade(func_eu_00160788(3), 0x1BE, 1);
        return;
    case 34:
        SetPauseMenuLayerPage(self, 0, -1);
        D_eu_00263624 = 1;
        return;
    case 14:
        if (sel == 0) {
            goto c6030;
        }
        SetPauseMenuLayerPage(self, 1, -1);
        return;
    case 4:
        if (sel == 0) {
            StartBackgroundJob(&g_backgroundJob, (void*)func_0018C1A8, &g_memoryCard);
            SetPauseMenuLayerPage(self, 1, 5);
            return;
        }
        goto c5EC0;
    case 7:
        if (sel == 0) {
            StartBackgroundJob(&g_backgroundJob, (void*)CreateMemoryCardSaveFiles, &g_memoryCard);
            SetPauseMenuLayerPage(self, 1, 8);
            return;
        }
        goto c5EC0;
    case 3:
    case 6:
    case 9:
    case 10:
    case 15:
    case 21:
    case 32:
    c5EC0: {
        s32 v;
        SetPauseMenuLayerPage(self, 1, -1);
        SetMemoryCardDisplayMode(&g_memoryCard, 2);
        v = self->f268;
        if (v == 0xB) {
            goto c5F08;
        }
        if (v < 0xB) {
            return;
        }
        if (v >= 0x12) {
            return;
        }
        if (v < 0x10) {
            return;
        }
    }
    case 24:
    c5F08:
        SetPauseMenuLayerPage(self, 0, 0x17);
        return;
    case 16: {
        Ent_195958* e = &D_eu_00255538[sel];
        if (e->fC == 0.0f) {
            SetPauseMenuLayerPage(self, 0, -1);
            g_memoryCard.f4F44 = e;
            ApplyMemoryCardImage(&g_memoryCard);
            ResumeAtSavedLevel();
            return;
        }
        StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    case 17:
        SetPauseMenuLayerPage(self, 0, -1);
        g_memoryCard.f4F44 = &D_eu_00255538[sel];
        ApplyMemoryCardImage(&g_memoryCard);
        ResumeAtSavedLevel();
        return;
    case 11: {
        Ent_195958* e;
        u32 p;
        p = sel * sizeof(Ent_195958);
        p += (u32)D_eu_00255538;
        e = (Ent_195958*)p;
        g_memoryCard.f4F4C = e;
        if (e->fC == 0.0f) {
        c6030:
            MemoryCard* b;
            b = &g_memoryCard;
            b->f4F44 = b->f4F4C;
            self->f27C = 0xB;
            if ((g_saveData->u19EC & 0x100) == 0) {
                SetPauseMenuLayerPage(self, 1, 0x14);
            } else {
                SetPauseMenuLayerPage(self, 1, 0xC);
                StartBackgroundJob(&g_backgroundJob, (void*)SaveGameToMemoryCardSlot, b);
            }
            SetPauseMenuLayerPage(self, 0, -1);
            return;
        }
        SetPauseMenuLayerPage(self, 1, 0xE);
        return;
    }
    case 18:
        if (sel == 0) {
            StartBackgroundJob(&g_backgroundJob, (void*)WriteSelectedMemoryCardSlot, &g_memoryCard);
            SetPauseMenuLayerPage(self, 1, 0x13);
            return;
        }
        SetPauseMenuLayerPage(self, 1, -1);
        return;
    case 13:
        SetPauseMenuLayerPage(self, 1, -1);
        return;
    case 20: {
        g_saveData->u19EC |= 0x100;
        s32 v = self->f27C;
        switch (v) {
        case 2:
        case 0xB:
            SetPauseMenuLayerPage(self, 1, 0xC);
            break;
        case -1:
            SetPauseMenuLayerPage(self, 1, -1);
            D_00273EB0.vt->m14(&D_00273EB0);
            break;
        }
        StartBackgroundJob(&g_backgroundJob, (void*)SaveGameToMemoryCardSlot, &g_memoryCard);
        return;
    }
    }
}
