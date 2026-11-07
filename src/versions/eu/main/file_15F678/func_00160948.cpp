// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's fallback key is entry D_eu_00263710 of a table of 0x20-byte keys, not the first one.
extern s32 D_eu_00263710;

void func_00160948(void)
{
    SessionKey* k = LookupEntryById((g_saveData->f19D8 << 8) | g_saveData->f19DC);
    if (k == 0) {
        k = (SessionKey*)((u8*)&D_00247AB0 + D_eu_00263710 * 0x20);
    }
    ClearTwoWords(D_002623D8);
    if (g_elementStack.f30 != 1 || g_saveData->fC != 0.0f || !k->Same((SessionKey*)&D_00275B04)) {
        StartObjectFade(k, -1, 1);
    } else if (g_elementStack.f30 == 1) {
        if (D_00275F84 == 0) {
            func_001C0760(g_saveData->f19EC & 0x80);
            func_001C0790(g_saveData->f19EC & 0x40);
            Animation* r = FindFirstObjectById(g_currentWorld, 0x105, 0x494, 0);
            if (r != 0) {
                PlayerListWalk frame((AnimationPlayerList*)r->props6C);
                void* head = *(void**)r->props6C;
                frame.cursor = (u8*)head + frame.next_off;
                void* node = head;
                if (node != 0) {
                    do {
                        StopAnimationPlayer(node);
                        node = frame.Next();
                    } while (node != 0);
                }
            }
            g_elementStack.f30 = -1;
            SetElementStackState(&g_elementStack, 3);
        }
    }
}
