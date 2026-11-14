// SPDX-License-Identifier: AGPL-3.0-or-later
#include "object_finder.h"
// PAL: the count fields of the two counters are at 0x58C (US 0x27C).
struct Counter_1D9D78_eu { u8 pad[0x58C]; s32 count; };

// The pad's control of a path follower: its heading from the stick, its pace in mode 2 and the
// button 0x80, then by kind the race places (0) or the end of the round (1).
void ControlPathFollower(PathFollower* self, PadRecord* pad, f32 dt)
{
    if (self->fB34 != 1) {
        if (0.0f < pad->f48) {
            ComputeCameraRelativeStickHeading(g_camera, pad, 0, &self->f694);
        } else {
            self->f694 = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
        }
    }
    if (self->fB34 == 2) {
        self->f698 = self->f618 * pad->f48;
        if (g_movieChecksumFailed != 0) {
            self->f698 = self->f698 * 0.4f;
        }
        if ((pad->flags & 0x80) != 0) {
            ClearPadPressedBits(pad, 0x80);
            switch (self->fB30) {
            case 0:
                if (self->f858 > 0 && D_002751DC < g_gameTime - self->f854) {
                    CountDownPathFollowerLap(self);
                    StartSoundEffect(0x5A, 0, 0, 0, 0.0f, 0.0f, 2.0f, -0.25f, 0.0f, 0, 0);
                } else {
                    StartSoundEffect(0x73, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                }
                break;
            case 1:
                if (self->fB44 != 0) {
                    SetStateWalkerTarget((StateWalker*)self->fB48, 0x485);
                    self->pushedCount = 0;
                }
                break;
            case 2:         // a kind with nothing to do: retail's compare tree has it
                break;
            }
        }
    }
    HandleStepSequenceSkipButtons(self, pad);
    if (self->fAFC != 0) {
        self->f698 = self->fAFC->f1C <? self->f698;
    }
    switch (self->fB30) {
    case 0: {
        WalkerHolder* r = (WalkerHolder*)FindFirstObjectById(self->world, 5, 0x42C, 0);
        if (r != 0) {
            void* dev = r->f48;
            s32 code;
            GetStateWalkerTargetKey((StateWalker*)dev, &code);
            if (code == -1) {
                GetStateWalkerCurrentKey((StateWalker*)dev, &code);
            }
            if (code < 0x431) {
                if (code >= 0x42F && 0.5f < g_gameClock[1] - self->fB10 && self->f830 != 0) {
                    PathFollower* found[16];
                    s32 n = GatherObjectsById(self->world, 5, 0x19, 0, 0x10, found);
                    s32 place = 1;
                    for (s32 i = 0; i < n; i++) {
                        if (self != found[i] && IsPathFollowerAhead(found[i], self) != 0) {
                            place++;
                        }
                    }
                    if (place != self->fB08 || n != self->fB0C) {
                        self->fB08 = place;
                        self->fB0C = n;
                        self->fB10 = g_gameClock[1];
                    }
                }
            }
        }
        break;
    }
    case 1: {
        WalkerHolder* r = (WalkerHolder*)FindFirstObjectById(self->world, 5, 0x42C, 0);
        if (r != 0) {
            void* dev = r->f48;
            s32 code;
            GetStateWalkerTargetKey((StateWalker*)dev, &code);
            if (code == -1) {
                GetStateWalkerCurrentKey((StateWalker*)dev, &code);
            }
            if (code == 0x42F) {
                if (((Counter_1D9D78_eu*)&D_00272430)->count >= D_002751D4) {
                    SetStateWalkerTarget((StateWalker*)dev, 0x432);
                } else if (((Counter_1D9D78_eu*)&D_002726B0)->count >= D_002751D4) {
                    SetStateWalkerTarget((StateWalker*)dev, 0x431);
                    RaiseScatterLevels((ScatterController*)g_scatterController, 1.0f);
                }
            }
        }
        break;
    }
    case 2:             // as above
        break;
    }
}
