// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1228/1232, checked 2026-11-08
// NEAR (src/main/file_198980.cpp, where it is INCLUDE_ASM after INCLUDE_RODATA of its two jump
// tables; landing it needs `#include "pad_record.h"` there, with g_padRecord taken from it): the
// key tests, the mode label's compare tree, the pad's direction and the three switches with
// their jump tables are retail's. Left: the dial check loop. Retail lays it out with its
// increment and test (i++, code *= 10, i < 3) before the body, entered by a jump, and loads
// &t and &c afresh each time (frame 0x80); ours tests at the bottom and keeps &t in a saved
// register (s6 more, frame 0x90). Also retail keeps the target key in a1 and copies it to s0.
// Tried: for, for(;;) with a break, do-while, a goto loop.
#include "common.h"
#include "switched_collider.h"
#include "globals.h"
#include "game_progress.h"
#include "step_sequence.h"
#include "pad_record.h"

struct C17Marker { s32 owner; s32 object; s32 walker; };
void GetStateWalkerTargetKey(void* dev, s32* out);
void GetStateWalkerCurrentKey(void* dev, s32* out);
void SetStateWalkerTarget(void* dev, s32 value);
void ChooseStepSequenceState(StepSequence* s);
void ActivateSwitchedCollider(Player* p);
void ShowModeLabel(s32 mode);
s32 GetPadHorizontalStep(PadRecord* p);
s32 GetPadVerticalStep(PadRecord* p);
void ClearPadPressedBits(PadRecord* p, s32 mask);
void RecordC17ColliderCompletion(C17* self);
void CopyMemory(void* dst, void* src, s32 size);

// The combination lock: the pad turns the three dials (each key 0x385..0x38D a dial and a digit
// band, 0x38E open, 0x38F done), the dials matching f640's digits open it, and the queued step
// sequences run one at a time.
void ControlC17Collider(C17* self, PadRecord* pad)
{
    s32 cur;
    s32 target;

    GetStateWalkerCurrentKey(self->f614, &cur);
    GetStateWalkerTargetKey(self->f614, &target);
    s32 key = target;
    if (key == -1)
        key = cur;
    if (cur == 0x38F) {
        ActivateSwitchedCollider(g_player);
        return;
    }
    if (cur == 0x38E && target == cur) {
        if (self->f7D8 == 0 && D_0027051C == 0) {
            SetStateWalkerTarget(self->f614, 0x38F);
            switch (self->f760) {
            case 2:
            case 0x10:
                ShowModeLabel(0);
                break;
            case 0x80:
                ShowModeLabel(4);
                break;
            case 8:
            case 0x1000:
                ShowModeLabel(2);
                break;
            case 4:
            case 0x400:
                ShowModeLabel(1);
                break;
            case 0x200:
                ShowModeLabel(5);
                break;
            case 0x8000:
                ShowModeLabel(6);
                break;
            case 0x40:
                ShowModeLabel(3);
                break;
            }
        }
    } else if (target != 0x38F) {
        if (target == 0x38E)
            return;
        s32 dir = -1;
        s32 h = GetPadHorizontalStep(pad);
        s32 v = GetPadVerticalStep(pad);
        if (h < 0)
            dir = 1;
        else if (h > 0)
            dir = 0;
        else if (v < 0)
            dir = 2;
        else if (v > 0)
            dir = 3;
        else if (pad->flags & 0x20)
            dir = 0;
        else if (pad->flags & 0x80)
            dir = 1;
        else if (pad->flags & 0x10)
            dir = 2;
        else if (pad->flags & 0x40)
            dir = 3;
        ClearPadPressedBits(pad, 0xF0);
        switch (dir) {
        case 0:
            if (key < 0x385)
                break;
            if (key < 0x388)
                SetStateWalkerTarget(self->f614, 0x388);
            else if (key < 0x38B)
                SetStateWalkerTarget(self->f614, 0x38B);
            break;
        case 1:
            if (key < 0x388)
                break;
            if (key < 0x38B)
                SetStateWalkerTarget(self->f614, 0x385);
            else if (key < 0x38E)
                SetStateWalkerTarget(self->f614, 0x388);
            break;
        case 2:
            switch (key) {
            case 0x385:
            case 0x386:
            case 0x387:
                SetStateWalkerTarget(self->f614, 0x386);
                break;
            case 0x388:
            case 0x389:
            case 0x38A:
                SetStateWalkerTarget(self->f614, 0x389);
                break;
            case 0x38B:
            case 0x38C:
            case 0x38D:
                SetStateWalkerTarget(self->f614, 0x38C);
                break;
            }
            break;
        case 3:
            switch (key) {
            case 0x385:
            case 0x386:
            case 0x387:
                SetStateWalkerTarget(self->f614, 0x387);
                break;
            case 0x388:
            case 0x389:
            case 0x38A:
                SetStateWalkerTarget(self->f614, 0x38A);
                break;
            case 0x38B:
            case 0x38C:
            case 0x38D:
                SetStateWalkerTarget(self->f614, 0x38D);
                break;
            }
            break;
        }
        s32 i = 0;
        s32 code = *(s32*)(self->f61C + 0x24);
        C17Marker* m = (C17Marker*)self->f61C;
        for (; i < 3; i++, m++) {
            s32 t;
            s32 c;
            GetStateWalkerTargetKey((void*)m->walker, &t);
            if (t != -1)
                goto queue;
            GetStateWalkerCurrentKey((void*)m->walker, &c);
            if (c - 0x390 != code / 100 % 10)
                goto queue;
            code *= 10;
        }
        if ((g_currentEntry->flags & 4) == 0) {
            RecordC17ColliderCompletion(self);
            return;
        }
    }
queue:
    if (self->f7D8 > 0 && D_0027051C == 0) {
        ChooseStepSequenceState((StepSequence*)self->f7DC[0]);
        self->f7D8--;
        CopyMemory(&self->f7DC[0], &self->f7DC[1], self->f7D8 * 4);
    }
}
