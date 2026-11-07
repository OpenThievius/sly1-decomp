// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL has the object fields 0x310 bytes later (0x570..0x57C) and calls func_eu_001AB238 where US calls vt->m20.
struct VT_1E00B0 { u8 pad[0x20]; void (*m20)(void*, void*); u8 pad24[0x14]; void (*m38)(void*); void (*m3C)(void*); };
struct Obj_1E00B0_eu { VT_1E00B0* vt; u8 pad04[0x56C]; s32 f570; u8 pad574[4]; f32 f578; s32 f57C; };
void func_eu_001AB238(Obj_1E00B0_eu* q, void* p);
void func_001AA298(Obj_1E00B0_eu* q);
void func_001AA8B8(Obj_1E00B0_eu* q, f32 v);
void func_001E02C8(Obj_1E00B0_eu* q, s32 n);
void func_001AB920(Obj_1E00B0_eu* q, f32 v);

void func_001E00B0(Obj_1E00B0_eu* self)
{
    UpdateScreenElementSlide(self);
    switch (self->f570) {
    case 0:
    case 1:
    {
        if (self->f57C != 0) {
        if (g_padRecord.flags & 4) {
            ClearPadPressedBits(&g_padRecord, 4);
            StartLockedStreamVoice((s32)g_currentWorld->f2310);
            if (g_currentWorld->f2314 != 0) {
                SetScreenElementHoldTime(self, 15.0f);
                func_eu_001AB238(self, g_currentWorld->f2314);
            } else {
                self->vt->m3C(self);
            }
            self->f57C = 0;
        } else if (g_gameTime >= 5.0f) {
            self->vt->m3C(self);
            self->f57C = 0;
        }
        }
    break;
    }
    case 2:
    {
        Obj_1E00B0_eu* o = (Obj_1E00B0_eu*)&g_timerElement;
        s32 r;
        if (o->f570 == 0) {
            SetBestTimeState(self, 3);
            return;
        }
        SetTimerRate(o, -func_00205C78(2.0f, (f32)D_002623DC));
        r = AreMenusAndFadeClear();
        if (r) o->vt->m38(o); else o->vt->m3C(o);
        if (g_currentEntry->flags & 8) {
            s32 b = 0;
            if (r && D_002701C4 == 0 && g_currentEntry->f08 < ((Obj_1E00B0_eu*)&g_timerElement)->f578) b = 1;
            if (b) g_timerCaption.vt->m14(&g_timerCaption); else g_timerCaption.vt->m15(&g_timerCaption);
        }
    }
    break;
    }
}
