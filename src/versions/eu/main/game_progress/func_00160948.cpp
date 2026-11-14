// SPDX-License-Identifier: AGPL-3.0-or-later
#include "object_finder.h"
// PAL's fallback key is entry D_eu_00263710 of a table of 0x20-byte keys, not the first one.
extern s32 D_eu_00263710;

void ResumeAtSavedLevel(void)
{
    SessionKey* k = (SessionKey*)LookupEntryById((g_saveData->levelIndex << 8) | g_saveData->entryIndex);
    if (k == 0) {
        k = (SessionKey*)((u8*)&g_sessionFadeKey + D_eu_00263710 * 0x20);
    }
    ClearTwoWords(D_002623D8);
    if (g_elementStack.f30 != 1 || g_saveData->totalTime != 0.0f || !k->Same((SessionKey*)&D_00275B04)) {
        StartObjectFade(k, -1, 1);
    } else if (g_elementStack.f30 == 1) {
        if (g_resumeSoundSetupDone == 0) {
            SilenceVolumeChannel3(g_saveData->optionFlags & 0x80);
            ApplySoundOptionFlag(g_saveData->optionFlags & 0x40);
            Animation* r = (Animation*)FindFirstObjectById(g_currentWorld, 0x105, 0x494, 0);
            if (r != 0) {
                PlayerListWalk frame((AnimationPlayerList*)r->props6C);
                void* head = *(void**)r->props6C;
                frame.cursor = (u8*)head + frame.next_off;
                void* node = head;
                if (node != 0) {
                    do {
                        StopAnimationPlayer((AnimationPlayer*)node);
                        node = frame.Next();
                    } while (node != 0);
                }
            }
            g_elementStack.f30 = -1;
            SetElementStackState((ElementStack*)&g_elementStack, 3);
        }
    }
}
