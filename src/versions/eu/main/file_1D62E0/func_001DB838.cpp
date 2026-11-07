// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's reset of the game state when the flag is set.
void func_001DB838(s32 a0)
{
    if (a0 != 0) {
        ActivateSwitchedColliderIndex(-1);
        g_switchedColliderCount = 0;
        g_player = 0;
        D_00262C6C = 0;
        func_0016E148();
        ClearCameraObjectList(g_camera);
        ClearClass75List();
        ClearPointObjectList();
        ClearTargetVectorList();
        ClearObjectLists();
        StopAllSoundsAndWait();
        func_001B40C8();
        ShutDownScriptValuePools();
        ResetElementStack(g_elementStack);
        ResetFrontMemory();
        u8* c = (u8*)&D_0026CE48;
        u8* e = (u8*)&g_timerElement;
        g_camera = 0;
        g_coloredTriangleSet = 0;
        g_stepScale = 1.0f;
        ((Word_1DB838*)(c + 0x584))->v = 0;
        ((Word_1DB838*)(e + 0x590))->v = 0;
        D_00261D38 = 0;
        *(s32*)(c + 0x588) = 0;
        *(s32*)(e + 0x59C) = 0;
    }
}
