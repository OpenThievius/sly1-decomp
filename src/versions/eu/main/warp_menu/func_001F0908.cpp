// SPDX-License-Identifier: AGPL-3.0-or-later
#include "object_finder.h"
// PAL's own definition: resets the two engines after a pending change and restores the slot's pose.
struct Eng_1F0908;
typedef void (*SetFn_1F0908)(Eng_1F0908* e, s32 mode);
struct EngVt_1F0908 { u8 pad[0x40]; SetFn_1F0908 set; };
struct Eng_1F0908 { EngVt_1F0908* vt; };
void SetScreenElementHoldTime(Eng_1F0908* e, f32 x);
void SetElementTextFromEntry(Eng_1F0908* e, s32 a, s32 b);
struct Eng_eu_1F0908 {
    EngVt_1F0908* vt;
    u8 pad4[0x56C];
    s32 i570;
    u8 pad574[0x400];
    s32 i974;
};

void AnnouncePendingWarpEntry(WarpPage* self)
{
    if (g_pendingWarpEntry == -1) return;
    SetScreenElementHoldTime(&g_letterboxElement, ((g_saveData->levelIndex << 8) | g_saveData->entryIndex) == 4 ? 0.5f : 2.0f);
    g_letterboxElement.vt->m16(&g_letterboxElement, 2);
    Eng_eu_1F0908* e = ((Eng_eu_1F0908*)&g_copiedTextCaption);
    e->i570 = 0;
    e->vt->set((Eng_1F0908*)e, 0);
    SetElementTextFromEntry((Eng_1F0908*)e, g_saveData->levelIndex, g_saveData->entryIndex);
    e->i974 = 1;
    SetScreenElementHoldTime((Eng_1F0908*)e, 0.0f);
    e->vt->set((Eng_1F0908*)e, 2);
    Animation* sl = self->entries[g_pendingWarpEntry].animation;
    if (sl != 0) {
        f32 f = 0.0f;
        if (g_pendingWarpEntryAtEnd == 0) f = sl->length;
        ReplaceAnimationPlayer(sl, self, 0, (AnimationPlayer**)&self->entryPlayer, f, 0.0f);
    }
    if (self->closeAnimation != 0) {
        for (s32 i = 0; i < self->closeAnimation->startCount; i++) {
            AnimEvent* en = &self->closeAnimation->startList[i];
            if (en->kind == 10) {
                BaseObject* n = FindFirstObjectById(self->world, 0x104, en->a8.i, self);
                if (n != 0) n->desc->m02(n);
            }
        }
    }
    g_pendingWarpEntry = -1;
}
