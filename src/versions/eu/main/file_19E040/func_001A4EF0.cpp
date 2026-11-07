// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the packed word of D_002701F8 is at 0x5B0 (not 0x324) and the two slots of D_0026D0C8 are at 0x574 and 0x578 (not 0x264 and 0x268).
struct __attribute__((packed)) Packed_1A4EF0_eu { u8 pad[0x5B0]; s32 v __attribute__((packed)); };
struct Glob_1A4EF0_eu { u8 pad[0x5B0]; s32 v; };
struct Tab_1A4EF0_eu { u8 pad[0x574]; void* f574; void* f578; };

void func_001A4EF0(PairController* self, s32 state)
{
    PairController* o;
    s32 v;
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
                    W(self, 0x658) = FindFirstObjectById(self->world, 0x105, 0x33B, 0);
                }
            }
        }
        s32 w = W(self, 0x658);
        if (w) {
            ((Packed_1A4EF0_eu*)&g_typedTextCaptionBox)->v = w;
            PushStackElement(g_elementStack, (u8*)&g_typedTextCaptionBox);
        }
        break;
    }
    case 2: {
        ((Tab_1A4EF0_eu*)&D_0026D0C8)->f574 = &self->f3C4;
        ((Tab_1A4EF0_eu*)&D_0026D0C8)->f578 = &self->limit3B8;
        func_001DDC38(self->world, self);
        break;
    }
    case 5:
        v = FindFirstObjectById(self->world, 0x105, 0x33D, 0);
        W(self, 0x658) = v;
        if (v) {
            ((Glob_1A4EF0_eu*)&g_typedTextCaptionBox)->v = v;
            PushStackElement(g_elementStack, (u8*)&g_typedTextCaptionBox);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) SetPairedState(o, 8);
        ResetScatterLevels(g_scatterController);
        break;
    case 3:
        v = FindFirstObjectById(self->world, 0x105, 0x33E, 0);
        W(self, 0x658) = v;
        if (v) {
            ((Glob_1A4EF0_eu*)&g_typedTextCaptionBox)->v = v;
            PushStackElement(g_elementStack, (u8*)&g_typedTextCaptionBox);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) {
            Link_1A4EF0* l = (Link_1A4EF0*)P(o, 0x55C);
            if (l == 0 || l->f18 != o) SetPairedState(o, 7);
        }
        RaiseScatterLevels(g_scatterController, 1.0f);
        break;
    case 4:
        SetPauseMenuLayerPage((u8*)&g_pauseMenuElement, 0, 0x1A);
        break;
    case 6:
        func_001A4070(P(self, 0x354), 3);
        D_0026EC70.vt->m15(&D_0026EC70);
        break;
    }
}
