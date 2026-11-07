// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's own definition: restores the mode, resets the camera sub-object and sets the mode's music/state.
const char* func_eu_001DDAB0(s32 id);

void func_001D29C8(u32 mode)
{
    switch (g_currentMode) {
    case 1:
        if ((*(Player**)&g_player) == 0)
            goto tail;
        if ((*(Player**)&g_player)->f2220 == 0xD)
            func_00175170((*(Player**)&g_player), 0, -1);
        break;
    case 3:
        if ((*(Player**)&g_player) == 0)
            goto tail;
        if (((PlayerHeldObject*)(*(Player**)&g_player)->f1518) != 0) {
            if (IsObjectAttached(((PlayerHeldObject*)(*(Player**)&g_player)->f1518)) != 0)
                func_00126D60(((PlayerHeldObject*)(*(Player**)&g_player)->f1518), 0.5f);
        }
        break;
    }
    if ((*(Player**)&g_player) != 0) {
        g_stepScale = 1.0f;
        if (((PlayerHeldObject*)(*(Player**)&g_player)->f2750) != 0) {
            if (IsObjectAttached(((PlayerHeldObject*)(*(Player**)&g_player)->f2750)) != 0)
                TakeCountedColliderTouch(((PlayerHeldObject*)(*(Player**)&g_player)->f2750), (*(Player**)&g_player), 1);
        }
        SeekObjects105Animations((*(Player**)&g_player), 0);
        if ((*(Player**)&g_player) != 0) {
            if ((void*)(*(Player**)&g_player) == GetActiveSwitchedCollider())
                g_currentMode = mode;
        }
    }
tail:
    if (mode != g_saveData->f19FC && mode < 7) {
        SetScreenElementHoldTime(&g_buttonHintElement, ((*(Player**)&g_player) != 0 && (void*)(*(Player**)&g_player) == GetActiveSwitchedCollider()) ? 3.0f : 8.0f);
        SetScreenElementScale(&g_buttonHintElement, 0.6f);
        g_buttonHintElement.vt->m08(&g_buttonHintElement, func_eu_001DDAB0((s32)g_modeLabels[mode]));
        g_buttonHintElement.vt->m14(&g_buttonHintElement);
        g_saveData->f19FC = mode;
    }
}
