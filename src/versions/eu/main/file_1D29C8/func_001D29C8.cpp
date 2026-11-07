// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's own definition: restores the mode, resets the camera sub-object and sets the mode's music/state.
const char* func_eu_001DDAB0(s32 id);

void func_001D29C8(u32 mode)
{
    switch (D_00274F74) {
    case 1:
        if ((*(Player**)&g_player) == 0)
            goto tail;
        if ((*(Player**)&g_player)->f2220 == 0xD)
            SetPlayerState((*(Player**)&g_player), 0, -1);
        break;
    case 3:
        if ((*(Player**)&g_player) == 0)
            goto tail;
        if (((Sub_1D29C8*)(*(Player**)&g_player)->f1518) != 0) {
            if (IsObjectAttached(((Sub_1D29C8*)(*(Player**)&g_player)->f1518)) != 0)
                func_00126D60(((Sub_1D29C8*)(*(Player**)&g_player)->f1518), 0.5f);
        }
        break;
    }
    if ((*(Player**)&g_player) != 0) {
        g_stepScale = 1.0f;
        if (((Sub_1D29C8*)(*(Player**)&g_player)->f2750) != 0) {
            if (IsObjectAttached(((Sub_1D29C8*)(*(Player**)&g_player)->f2750)) != 0)
                func_001D32D8(((Sub_1D29C8*)(*(Player**)&g_player)->f2750), (*(Player**)&g_player), 1);
        }
        func_001D31D0((*(Player**)&g_player), 0);
        if ((*(Player**)&g_player) != 0) {
            if ((void*)(*(Player**)&g_player) == GetActiveSwitchedCollider())
                D_00274F74 = mode;
        }
    }
tail:
    if (mode != g_saveData->f19FC && mode < 7) {
        SetScreenElementHoldTime(&D_0026EC70, ((*(Player**)&g_player) != 0 && (void*)(*(Player**)&g_player) == GetActiveSwitchedCollider()) ? 3.0f : 8.0f);
        SetScreenElementScale(&D_0026EC70, 0.6f);
        D_0026EC70.vt->fn20(&D_0026EC70, (s32)func_eu_001DDAB0((s32)D_00274F58[mode]));
        D_0026EC70.vt->fn38(&D_0026EC70);
        g_saveData->f19FC = mode;
    }
}
