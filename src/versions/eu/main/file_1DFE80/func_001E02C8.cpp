// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the object fields sit 0x310 bytes later (0x568..0x57C); the best-time text is a
// translated label (text id 0xAB) followed by the formatted time, built in a 16-bit string
// on the stack, and the opening line is text id 0xA9.
struct VT2_1E00B0 { u8 pad[0x20]; void (*m20)(void*, void*); u8 pad24[0x14]; void (*m38)(void*); void (*m3C)(void*); };
struct VT_1E02C8 { u8 pad[0x20]; void (*m20)(void*, void*); u8 pad24[0x14]; void (*m38)(void*); void (*m3C)(void*); };
struct Obj_1E02C8_eu { VT_1E02C8* vt; u8 pad04[0x564]; f32* f568; s32 f56C_pad; s32 f570; f32 f574; s32 f578; s32 f57C; };
struct Obj2_1E02C8_eu { VT2_1E00B0* vt; u8 pad04[0x574]; f32 f578; };
const char* func_eu_001DDAB0(s32 id);
u16* func_eu_001E3050(u16* dst, const char* src);
u16* func_eu_001E3178(u16* dst, const u8* src);
s32 func_001E1FD0(char* dst, const char* fmt, ...);
void func_001AA8B8(Obj_1E02C8_eu* o, f32 v);

void func_001E02C8(Obj_1E02C8_eu* self, s32 n)
{
    if (self->f570 == n) {
        return;
    }
    switch (self->f570) {
    case 1:
        if (self->f57C != 0) {
            self->vt->m3C(self);
            self->f57C = 0;
        }
        break;
    case 2:
        StopTimer(&g_timerElement);
        g_timerElement.vt->m15(&g_timerElement);
        self->vt->m3C(self);
        break;
    }
    switch (n) {
    case 2: {
        f32 zero = 0.0f;
        f32 one = 1.0f;
        StartSoundEffect(0x6D, 0, 0, 0, 3000.0f, 300.0f, one, zero, zero, 0, 0);
        SetSpareCount(0);
        func_001DDAD0(g_currentWorld);
        StartTimer(&g_timerElement, g_currentWorld->f230C + 0.99f);
        SetTimerRate(&g_timerElement, -func_00205C78(2.0f, (f32)D_002623DC));
        SetTimerLimit(&g_timerElement, zero, 0);
        StartTimerCounting(&g_timerElement);
        G27C230* cam = g_currentEntry;
        if (cam->flags & 8) {
            char time[32];
            u16 text[128];
            f32 t = cam->f08;
            if (t < one) {
                FormatToString(time, " &10.%d", (s32)(t * 10.0f));
            } else {
                s32 s = (s32)t;
                s32 minutes = s / 60;
                s32 seconds = s % 60;
                FormatToString(time, " &1%d:%02d", minutes, seconds);
            }
            func_eu_001E3050(text, func_eu_001DDAB0(0xAB));
            func_eu_001E3178(text, (u8*)time);
            SetScreenElementHoldTime(self, zero);
            self->vt->m20(self, text);
        } else {
            SetScreenElementHoldTime(self, 5.0f);
            self->vt->m20(self, (void*)func_eu_001DDAB0(0xA9));
        }
        self->vt->m38(self);
        break;
    }
    case 3: {
        Obj2_1E02C8_eu* o = (Obj2_1E02C8_eu*)&g_timerElement;
        s32 id;
        f32 t = o->f578;
        if (0.0f < t) {
            G27C230* cam = g_currentEntry;
            if (cam->flags & 8) {
                if (cam->f08 < t) {
                    cam->f08 = t;
                    id = 0x1D;
                    StartMemoryCardSave(&g_memoryCard);
                } else {
                    id = 0x1E;
                }
            } else {
                id = 0x1B;
                cam->flags |= 8;
                cam->f08 = o->f578;
                g_currentLevelRecord->f440 = g_currentLevelRecord->f440 + 1;
                if (ComputeCompletionMask() & 8) {
                    ApplyCompletionFlags(8);
                    StartMemoryCardSave(&g_memoryCard);
                }
            }
        } else {
            id = 0x1C;
            if (g_currentEntry->flags & 8) {
                id = 0x1E;
            }
        }
        SetPauseMenuLayerPage(&g_pauseMenuElement, 0, id);
        break;
    }
    }
    self->f570 = n;
    self->f574 = *self->f568;
    if (n == 2) {
        CompleteSoundNotifiers(g_currentWorld);
    }
    self->f578 = (self->f570 != 0);
}
