// SPDX-License-Identifier: AGPL-3.0-or-later
#include "object_finder.h"
// PAL: the packed word of D_002701F8 is at 0x5B0 (not 0x324) and the two slots of D_0026D0C8 are at 0x574 and 0x578 (not 0x264 and 0x268).
struct __attribute__((packed)) Packed_1A4EF0_eu { u8 pad[0x5B0]; s32 v __attribute__((packed)); };
struct Glob_1A4EF0_eu { u8 pad[0x5B0]; void* v; };
struct Tab_1A4EF0_eu { u8 pad[0x574]; void* f574; void* f578; };

void SetPairControllerState(PairController* self, s32 state)
{
    PairController* o;
    void* v;
    ListFrame frame;
    if (W(self, 0x650) == state) return;
    W(self, 0x650) = state;
    F(self, 0x654) = g_gameClock[1];
    W(self, 0x658) = 0;
    switch (state) {
    case 0:
        break;
    case 1: {
        if (W(self, 0x64C) < 3) {
            if (W(self, 0x64C) >= 0) {
                if (g_currentEntry->f14) {
                    W(self, 0x658) = 0;
                } else {
                    P(self, 0x658) = FindFirstObjectById(self->world, 0x105, 0x33B, 0);
                }
            }
        }
        s32 w = W(self, 0x658);
        if (w) {
            ((Packed_1A4EF0_eu*)&g_typedTextCaptionBox)->v = w;
            PushStackElement((ElementStack*)g_elementStack, &g_typedTextCaptionBox);
        }
        break;
    }
    case 2: {
        ((Tab_1A4EF0_eu*)&g_pairControllerCountCaption)->f574 = &self->finishedCount;
        ((Tab_1A4EF0_eu*)&g_pairControllerCountCaption)->f578 = &self->limit3B8;
        SetWorldActiveFollower(self->world, self);
        break;
    }
    case 5:
        v = FindFirstObjectById(self->world, 0x105, 0x33D, 0);
        P(self, 0x658) = v;
        if (v) {
            ((Glob_1A4EF0_eu*)&g_typedTextCaptionBox)->v = v;
            PushStackElement((ElementStack*)g_elementStack, &g_typedTextCaptionBox);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) SetPairedState((PairedObject*)o, 8);
        ResetScatterLevels((ScatterController*)g_scatterController);
        break;
    case 3:
        v = FindFirstObjectById(self->world, 0x105, 0x33E, 0);
        P(self, 0x658) = v;
        if (v) {
            ((Glob_1A4EF0_eu*)&g_typedTextCaptionBox)->v = v;
            PushStackElement((ElementStack*)g_elementStack, &g_typedTextCaptionBox);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) {
            BaseObject* l = (BaseObject*)P(o, 0x55C);
            if (l == 0 || l->parent != o) SetPairedState((PairedObject*)o, 7);
        }
        RaiseScatterLevels((ScatterController*)g_scatterController, 1.0f);
        break;
    case 4:
        SetPauseMenuLayerPage((T217D_6D0*)&g_pauseMenuElement, 0, 0x1A);
        break;
    case 6:
        SetWalkerColliderState((WalkerCollider*)(P(self, 0x354)), 3);
        g_buttonHintElement.vt->m15(&g_buttonHintElement);
        break;
    }
}
