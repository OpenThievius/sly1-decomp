// SPDX-License-Identifier: AGPL-3.0-or-later
#include "object_finder.h"
// PAL: field at 0x560 (US 0x250); fades the 0x105/0x495 group's items out or in when the value goes to or from zero.
struct Obj_135550_eu { u8 pad0[0x560]; s32 f560; };
void SetScreenElementMode(Obj_135550_eu* self, s32 value);

void SetTextPanelMode(Obj_135550_eu* self, s32 value)
{
    if (value == self->f560) {
        return;
    }
    if (self->f560 == 0) {
        PlayerListHolder* g = (PlayerListHolder*)FindFirstObjectById(g_currentWorld, 0x105, 0x495, 0);
        if (g != 0) {
            ListFrame it;
            ListWalkBegin::Of(&it, &g->list);
            AnimationPlayer* obj;
            while ((obj = ListWalkNext::Of(&it)) != 0) {
                SetAnimationPlayerSpeed(obj, 0.0f);
            }
            g_activeListFrames = (ListFrame*)it.prev;
        }
    }
    if (value == 0) {
        PlayerListHolder* g = (PlayerListHolder*)FindFirstObjectById(g_currentWorld, 0x105, 0x495, 0);
        if (g != 0) {
            ListFrame it;
            ListWalkBegin::Of(&it, &g->list);
            AnimationPlayer* obj;
            while ((obj = ListWalkNext::Of(&it)) != 0) {
                SetAnimationPlayerSpeed(obj, 1.0f);
            }
            g_activeListFrames = (ListFrame*)it.prev;
        }
    }
    SetScreenElementMode(self, value);
}
