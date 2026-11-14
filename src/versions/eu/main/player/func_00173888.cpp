// SPDX-License-Identifier: AGPL-3.0-or-later
#include "object_finder.h"
// PAL: the caption box's state and child sit at 0x570 and 0x5B0 (not 0x260 and 0x324).
struct CaptionBox_eu {
    u8 pad000[0x570];
    s32 state;              // 0x570
    u8 pad574[0x5B0 - 0x574];
    void* child;            // 0x5B0
};

void ControlPlayer(Player* self, PadRecord* pad, f32 dt)
{
    if (HasAnimationDrivenAttachment(self)) {
        if (!(0.0f < pad->stickMagnitude) && (pad->flags & 0xF0) == 0) {
            return;
        }
        ReleaseAnimationDrivenAttachments(self);
    }
    PadRecord blank;
    if (D_00261D38 > 0 || self->walkerActivation != 0 || self->firstActivation != 0 || self->secondActivation != 0) {
        switch (self->state) {
        case 12:
            if (self->pendingCaption == 0) {
                SetPlayerState(g_player, 12, 0x23);
            }
            break;
        case 8:
            if (g_gameTime[0] - self->stateStartTime > 0.2f) {
                self->jumpKind = 4;
                SetPlayerState(g_player, 2, 0);
            }
            break;
        case 2:
            switch (self->subState) {
            case 4:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
                SetPlayerState(self, 2, 2);
                break;
            }
            break;
        }
        FillMemory(&blank, 0, sizeof(blank));
        pad = &blank;
    }
    if (self->state != 4) {
    if (self->entryQueue != 0 && IsEntryQueueRunning(self->entryQueue)) {
        EntryQueue* q = self->entryQueue;
        if ((g_padRecord.flags & 0x800) && g_resumeSoundSetupDone == 0) {
            s32 start = q->entryIndex;
            if (start >= 0) {
                for (s32 i = start; i < q->entryCount; i++) {
                    QueueEntry* e = &((QueueEntry*)q->buffer)[i];
                    if (e->kind == 1) {
                        BaseObject* o = FindFirstObjectById(q->world, 0x104, e->id, (void*)q->lastFoundObject);
                        if (o != 0 && IsObjectOfKind(o, 0x74)) {
                            StartObjectFade(&D_00275B04, o->id, 1);
                            ClearPadPressedBits(&g_padRecord, 0x800);
                            break;
                        }
                    }
                }
            }
        }
        FillMemory(&blank, 0, sizeof(blank));
        pad = &blank;
        DrivePlayerFromEntryQueue(self->entryQueue, &blank);
    } else {
        if (self->entryQueue != 0) {
            UnbindEntryQueue(self->entryQueue);
        }
        ReadTurningColliderStickHeading(self, pad);
    }
    } else {
        ReadTurningColliderStickHeading(self, pad);
    }
    s32 skipStep = 0;
    s32 noFloor = 0;
    s32 moving;
    s32 falling = 0;
    s32 jump = 0;
    WrapAngle(self->stickHeading - ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x));
    if (pad->flags & 0x40) {
        switch (self->state) {
        case 6:
            if (self->targetMode == 2 || self->targetMode == 5 || self->targetMode == 4) {
                jump = 1;
            }
            break;
        case 2:
            switch (self->subState) {
            case 7:
            case 8:
                break;
            default:
                if (self->f2498 != 0) {
                    Vec02 off;
                    Vu0::Q(off) = Vu0::MulXSum3(Vu0::Q(g_unitZVector), Vu0::Scalar(-self->probeDepth),
                                                Vu0::Q(self->v150), Vu0::Scalar(0.1f),
                                                Vu0::Q(self->gravity), Vu0::Scalar(0.5f * 0.1f * 0.1f));
                    falling = HasFloorAtPlayerOffset(self, &off) == 0;
                }
                break;
            }
            break;
        case 4:
            goto held;
        case 5:
        default: {
            Vec02 off;
            *(u128*)&off = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-self->probeDepth - 60.0f));
            if (g_gameTime[0] - self->groundContactTime < 0.1f || HasFloorAtPlayerOffset(self, &off)) {
                jump = 1;
            }
            break;
        }
        case 3:
        case 7:
        case 8:
            jump = 1;
            break;
        }
        if (!jump) {
            self->f2284 = g_gameTime[0];
        }
    } else if (g_gameTime[0] - self->f2284 < 0.1f && g_gameTime[0] - self->groundContactTime < 0.1f) {
        jump = 1;
    }
held:
    switch (self->state) {
    case 0:
    case 1:
    case 5:
    case 6:
    case 14:
    case 15:
    case 16:
        if (g_gameTime[0] - self->groundContactTime > 0.1f) {
            Vec02 off;
            if (self->state == 6 && self->targetMode == 3) {
                Vu0::Q(off) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-self->probeDepth - 200.0f));
            } else {
                Vu0::Q(off) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-self->probeDepth - 60.0f));
            }
            noFloor = !HasFloorAtPlayerOffset(self, &off);
        }
        break;
    default:
        noFloor = 0;
        break;
    }
    moving = 0.0f < self->stickLevel;
    s32 aim = pad->buttons & 0x20;
    s32 modeKey = 0;
    if (pad->flags & 0x10) {
        modeKey = g_currentMode == 0;
    }
    UpdateModeSelection(self, pad);
    if (!IsTopCameraController((CameraController*)&g_camera->ctl454)) {
        PadRecord* rec = (g_padRouting & 4) ? &g_padRecord : &g_blankPadRecord;
        StepSequence* seq = (StepSequence*)((CaptionBox_eu*)&g_typedTextCaptionBox)->child;
        if (seq != 0 && seq->state2D4 == 3 && seq->f32C == 0 && (rec->flags & 0xC) && *(s32*)seq->target304 != 0) {
            if (self->state == 12) {
                self->pendingCaption = 0;
                skipStep = 1;
            }
            SkipRemainingSteps((StepSequence*)((CaptionBox_eu*)&g_typedTextCaptionBox)->child);
            ClearPadPressedBits(rec, 0xC);
        } else if (self->f2BD4 != 0 || (pad->flags & 0xC)) {
            if (self->state == 12) {
                if (((CaptionBox_eu*)&g_typedTextCaptionBox)->child == 0) {
                    self->pendingCaption = 0;
                    skipStep = 1;
                }
            } else if (((CaptionBox_eu*)&g_typedTextCaptionBox)->child == 0) {
                if ((pad->flags & 4) && g_playerStepSequence != 0 && (self->f2BD4 == 0 || g_playerStepSequence->mode2D0 == 1)) {
                    SetStepSequenceState(g_playerStepSequence, 1);
                } else if (self->f2BD4 == 0) {
                    self->pendingCaption = 0;
                    skipStep = 1;
                }
            }
        }
    }
    for (;;) {
        s32 state = self->state;
        s32 sub = self->subState;
        s32 target;
        switch (state) {
        case 4:
            if (HasSpareCount()) {
                if (pad->flags & 0x40) {
                    ClearPadPressedBits(pad, 0x40);
                    self->f2734 = g_gameTime[0];
                }
            }
            if (self->f2738 != 0 && g_gameTime[0] - self->f2734 < D_00263910[0]) {
                RunPlayerCallback(self);
                state = self->state;
                sub = self->subState;
            }
            break;
        case 0:
            if ((self->aimMode == 8 || self->aimMode == 9) && self->f2248 == 0) {
                break;
            }
            if (jump) {
                state = 2;
                sub = 0;
                break;
            }
            if (noFloor) {
                state = 2;
                sub = 2;
                break;
            }
            if (modeKey && (MaskWorldBitsBySave() & 2)) {
                state = 10;
                sub = 0x1F;
                break;
            }
            if (aim) {
                target = ChooseNearbyPlayerTarget((Chooser_1CDFB8*)self, 0, &self->targetMode);
                if (target != -1) {
                    state = 6;
                    sub = target;
                    break;
                }
                if (pad->flags & 0x20) {
                    StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect7EVolume, 0.0f, 0.0f, 0, 0);
                }
            }
            if (skipStep) {
                state = 12;
                sub = 0x21;
                break;
            }
            if (moving) {
                state = 1;
                sub = -1;
            }
            break;
        case 1:
            if (jump) {
                state = 2;
                sub = 0;
                self->jumpKind = state;
                break;
            }
            if (noFloor) {
                state = 2;
                sub = 2;
                break;
            }
            if (modeKey && (MaskWorldBitsBySave() & 2)) {
                state = 10;
                sub = 0x1F;
                break;
            }
            if (aim) {
                target = ChooseNearbyPlayerTarget((Chooser_1CDFB8*)self, 0, &self->targetMode);
                if (target != -1) {
                    state = 6;
                    sub = target;
                    break;
                }
                if (pad->flags & 0x20) {
                    StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect7EVolume, 0.0f, 0.0f, 0, 0);
                }
            }
            if (skipStep) {
                state = 12;
                sub = 0x21;
                break;
            }
            if (!moving) {
                state = 0;
                sub = -1;
            }
            break;
        case 5:
            if (jump) {
                state = 2;
                sub = 0;
                break;
            }
            if (noFloor) {
                state = 2;
                sub = 2;
                break;
            }
            if (aim) {
                target = ChooseNearbyPlayerTarget((Chooser_1CDFB8*)self, 0, &self->targetMode);
                if (target != -1) {
                    state = 6;
                    sub = target;
                    break;
                }
                if (pad->flags & 0x20) {
                    StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect7EVolume, 0.0f, 0.0f, 0, 0);
                }
            }
            if (skipStep) {
                state = 12;
                sub = 0x21;
                break;
            }
            state = 0;
            sub = -1;
            break;
        case 2: {
            s32 ready = !(sub == 10 || sub == 11 || sub == 13 || sub == 12 || sub == 14 || sub == 15 || sub == 8)
                && (sub != 5 || g_gameTime[0] - self->subStateStartTime > 0.05f);
            if (ready) {
                if (pad->flags & 0x20) {
                    ClearPadPressedBits(pad, 0x20);
                    SetPlayerAimMode(self, -1);
                    sub = ChoosePlayerTargetByCost((Chooser*)self, 0);
                    break;
                }
                if ((sub != 6 || self->jumpSpeed != 0.0f) && (pad->flags & 0x80)) {
                    SetPlayerAimMode(self, -1);
                    sub = 7;
                    ClearPadPressedBits(pad, 0x80);
                    break;
                }
            }
            if (ready && modeKey && (MaskWorldBitsBySave() & 0x10)) {
                SetPlayerAimMode(self, -1);
                sub = 8;
                break;
            }
            if (jump) {
                sub = 0;
                if (MaskWorldBitsBySave() & 0x1000) {
                    break;
                }
                if (!(pad->buttons & 0x10)) {
                    self->slowDownHeld = 0;
                }
                break;
            }
            if (falling) {
                sub = 3;
            }
            break;
        }
        case 3:
        case 7:
            if (jump) {
                state = 2;
                sub = 0;
                self->jumpKind = 1;
            }
            break;
        case 6:
            if (self->targetMode == 2) {
                if (jump) {
                    state = 2;
                    sub = 5;
                }
                break;
            }
            if (jump) {
                state = 2;
                sub = 0;
                break;
            }
            if (self->targetMode == 4 || self->targetMode == 5) {
                break;
            }
            if (modeKey && (MaskWorldBitsBySave() & 2)) {
                state = 10;
                sub = 0x1F;
                break;
            }
            if (noFloor) {
                state = 2;
                sub = 2;
                break;
            }
            if (pad->buttons & 0x20) {
                break;
            }
            if (g_padSelectFlags & 1) {
                break;
            }
            state = ChoosePlayerNextState(self);
            sub = -1;
            break;
        case 8:
            if (jump) {
                state = 2;
                sub = 0;
                self->jumpKind = 4;
            }
            break;
        case 12:
            if (skipStep) {
                if (self->subState == 0x22) {
                    sub = 0x23;
                    PopStackElement((ElementStack*)g_elementStack);
                    break;
                }
            } else if (self->subState == 0x22) {
                CaptionBox_eu* box = (CaptionBox_eu*)&g_typedTextCaptionBox;
                if (box->state == 0 || (box->state == 2 && box->child != 0 && ((StepSequence*)box->child)->state2D4 == 4)) {
                    sub = 0x23;
                    break;
                }
            }
            if (self->subState == 0x21 && self->f25CC == 0 && g_gameTime[0] - self->subStateStartTime >= 0.5f) {
                sub = 0x22;
                break;
            }
            if (self->subState == 0x23 && self->f25D0 == 0 && g_gameTime[0] - self->subStateStartTime >= 0.25f) {
                state = 0;
                sub = -1;
            }
            break;
        case 13:
            if (!(pad->buttons & 0x10) && g_gameTime[0] - self->stateStartTime > g_state13ExitDelay) {
                sub = 0x38;
                break;
            }
            self->heading = self->stickHeading;
            break;
        case 14:
        case 15:
        case 16:
            if (noFloor) {
                state = 2;
                sub = 2;
            }
            break;
        }
        if (state == self->state && sub == self->subState) {
            break;
        }
        SetPlayerState(self, state, sub);
        skipStep = 0;
        jump = 0;
        falling = 0;
    }
    HandlePlayerAimButton(self, pad);
    switch (self->state) {
    case 5:
        SetPlayerVelocityFromHeading(self, (const Vec02*)((u8*)self + 0x910), self->eightWayBlend, self->stickHeading, self->stickLevel);
        break;
    case 1:
        SetPlayerBlendWeights(self->stickHeading, self->stickLevel, self, (TurnBlendRecords*)((u8*)self + 0x720), self->sixWayBlend);
        break;
    case 4:
    case 10: {
        self->headingVelocity = D_00248D30;
        PlayerNoticePlayer* src = (PlayerNoticePlayer*)self->stateAnimPlayer;
        if (src != 0) {
            Track83* track = src->anim->movedTrack;
            if (track != 0) {
                PositionCurve* c = track->pos;
                if (c != 0) {
                    Vec02 v;
                    c->vt->eval(c, self, src->time, src->speed, 0, 0, &v);
                    Vu0::Q(self->headingVelocity) = Vu0::MulX(Vu0::Q(v), Vu0::Scalar(-1.0f));
                }
            }
        }
        break;
    }
    case 3:
        ControlPlayerOnLinkedObject(self, pad);
        break;
    case 7:
        ControlPlayerOnPath(self, (PathPad*)pad);
        break;
    case 2:
        ControlPlayerState2(self, pad);
        break;
    case 6:
        ControlPlayerOnTarget(self, pad);
        break;
    case 0:
    case 16:
        break;
    }
    UpdatePlayerGrabs(self);
}
