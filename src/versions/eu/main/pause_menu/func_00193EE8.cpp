// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL uses its own floats at 0x26BB30..3C, keeps f288 at 0x598 and has a case 20 that calls func_eu_001DE018(6) and stores func_001BE980().
struct Self_193EE8_eu {
    u8 pad[0x598];
    s32 f288;
};
extern f32 D_eu_0026BB30;
extern f32 D_eu_0026BB34;
extern f32 D_eu_0026BB38;
extern f32 D_eu_0026BB3C;
s32 HasStreamVoice(void);
void OpenKeyRecord(void* slot);
void* GetLoadedKeyRecord(s32 n);

void ChangePauseMenuPage(Self_193EE8_eu* self, s32 a, s32 b)
{
    if (a == b) {
        return;
    }
    if (self->f288 != 0) {
        StopStreamVoice();
        self->f288 = 0;
    }
    if (a == 11) {
        goto call;
    }
    if (a > 10) {
        if (a < 18) {
            if (a > 15) {
            call:
                g_buttonHintElement.vt->m15(&g_buttonHintElement);
            }
        }
    }
    switch (b) {
    case 11:
    case 16:
    case 17: {
        T217D_330* o = &g_buttonHintElement;
        SetScreenElementHoldTime(o, 0.0f);
        SetScreenElementScale(o, 0.6f);
        break;
    }
    case 20:
        if (HasStreamVoice() != 0) {
            return;
        }
        OpenKeyRecord(GetLoadedKeyRecord(6));
        self->f288 = HasStreamVoice();
        break;
    case 24: {
        D_eu_0026BB30 = D_eu_0026BB38 = (f32)(u32)((DisplayRegRead*)&D_00262490)->a.x;
        D_eu_0026BB34 = D_eu_0026BB3C = (f32)((u32)(((DisplayRegRead*)&D_00262490)->q18 >> 12) & 0x7FF);
        break;
    }
    case -1:
        D_0026C6C8.vt->m15(&D_0026C6C8);
        D_0026C948.vt->m15(&D_0026C948);
        D_0026CBC8.vt->m15(&D_0026CBC8);
        D_0026CE48.vt->m15(&D_0026CE48);
        D_00274118.vt->m15(&D_00274118);
        break;
    }
}
