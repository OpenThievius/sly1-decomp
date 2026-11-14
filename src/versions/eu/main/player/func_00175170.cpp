// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the caption box's child sits at 0x5B0 (not 0x324).
// The player's words by offset, as player.cpp wrote them before its fields were named.
#define PS(T, o) (*(T*)((u8*)self + (o)))
struct CaptionBox_175170_eu {
    u8 pad000[0x5B0];
    void* child;            // 0x5B0
};

void SetPlayerState(Player* self, s32 state, s32 sub)
{
    void* walker;
    s32 sound = -1;
    f32 start = 0.0f;
    void* anim = 0;
    f32 speed = 1.0f;
    s32 flag = 1;
    s32 layers = 0;
    s32 walkerId = -1;
    s32 skip = 0;
    walker = 0;

    if (self->state == state && self->subState == sub) {
        return;
    }
    self->pendingFlags &= ~1;
    if (self->state != state) {
        switch (self->state) {
        case 2: {
            self->penalizedTarget = 0;
            if (state != 3 && state != 7) {
                StartSoundEffect(0x49, 0, self, 0, 1000.0f, 500.0f, 0.7f, 0.0f, 0.0f, 0, 0);
            }
            self->jumpKind = -1;
            if (self->aimMode == 0 && state != 7 && state != 3) {
                SetPlayerAimMode(self, -1);
            }
            if (self->f2438 == 0) {
                void* m = 0;
                switch (state) {
                case 6:
                    switch (self->targetMode) {
                    case 4:
                    case 5:
                        m = PS(void*, 0x2720);
                        break;
                    case 0:
                    case 1:
                    case 3:
                    case 6:
                    case 7:
                        m = PS(void*, 0x271C);
                        break;
                    }
                    break;
                case 0:
                case 1:
                case 5:
                case 9:
                case 10:
                case 12:
                    m = PS(void*, 0x271C);
                    break;
                }
                if (m != 0) {
                    SendEmptyMessage((MemberObject*)m);
                }
            }
            if (!(MaskWorldBitsBySave() & 0x1000)) {
                self->slowDownHeld = 0;
            }
            break;
        }
        case 5:
            self->eightWayHalf = -1;
            break;
        case 3: {
            if (state == 2) {
                self->penalizedTarget = (void*)self->boundObject;
            }
            TriggerScriptEvent((BaseObject*)self->boundObject, 3, 0, 0);
            BaseObject* o = (BaseObject*)self->boundObject;
            o->desc->m18(o, self);
            self->previousBoundObject = self->boundObject;
            SetPlayerAimMode(self, -1);
            PS(Attachment*, 0x251C)->mode0 = -1;
            PS(Attachment*, 0x251C)->mode1 = -1;
            PlacedObject* p = (PlacedObject*)self->f61C;
            p->desc02()->m2B(p);
            PS(Attachment*, 0x2520)->mode1 = -1;
            p = (PlacedObject*)self->f23D0;
            p->desc02()->m2B(p);
            SetTurningColliderLinkFlag(self, 1);
            if (self->linkSystem != 0) {
                RemoveColliderAttachment(((Attach03*)self->linkSystem)->target, (Attach03*)self->linkSystem);
                ReleaseAttachRecords((World*)self->world, (Attach03*)self->linkSystem);
                self->linkSystem = 0;
            }
            ResetTrailRing((TrailRing*)self->trail);
            break;
        }
        case 7: {
            if (state == 2) {
                self->penalizedTarget = (void*)self->aimCurve;
            }
            TriggerScriptEvent((BaseObject*)self->aimCurve, 3, 0, 0);
            BaseObject* o = (BaseObject*)self->aimCurve;
            o->desc->m18(o, self);
            SetFlaggedLinkContactMask(self, (BaseObject*)self->aimCurve, 0);
            self->previousAimCurve = self->aimCurve;
            PS(f32, 0x2218) = PS(f32, 0x220C);
            s32 aim = -1;
            if (state == 2 && self->aimAnim11 != 0) {
                aim = 11;
            }
            SetPlayerAimMode(self, aim);
            Vu0::Q(self->poseOffset) = Vu0::Sub(Vu0::Q(self->focusPoint), Vu0::Q(self->pos));
            self->poseOffset.z = 0.0f;
            ResetTrailRing((TrailRing*)self->trail);
            break;
        }
        case 8:
            SetFlaggedLinkContactMask(self, (BaseObject*)self->ledgeCollider, 0);
            self->ledgeCollider = 0;
            break;
        case 4:
            PS(s32, 0x23DC) = -1;
            if (PS(void*, 0x2490) != 0) {
                AT(Vec02, PS(void*, 0x2490), 0x300) = D_00248D30;
            }
            if (PS(void*, 0x2494) != 0) {
                AT(Vec02, PS(void*, 0x2494), 0x300) = D_00248D30;
            }
            self->f580 = 1;
            ResetTrailRing((TrailRing*)self->trail);
            self->pulseFadeStart = g_gameTime[0];
            break;
        case 6: {
            switch (self->targetMode) {
            case 2:
                StopPlayerAnimation(self);
                StartSoundEffect(0x4E, 0, self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                SetPooledObjectPlayerHold((PooledObject*)self->heldObject, 0);
                break;
            case 5:
                TriggerScriptEvent((BaseObject*)self->targetNode, 3, 0, 0);
                ((BaseObject*)self->targetNode)->desc->m18((BaseObject*)self->targetNode, self);
                SetFlaggedLinkContactMask(self, (BaseObject*)self->targetNode, 0);
                self->heldObject = 0;
                break;
            case 4:
                TriggerScriptEvent((BaseObject*)self->targetTrack, 3, 0, 0);
                ((BaseObject*)self->targetTrack)->desc->m18((BaseObject*)self->targetTrack, self);
                SetFlaggedLinkContactMask(self, (BaseObject*)self->targetTrack, 0);
                self->heldObject = 0;
                break;
            case 6:
                if (self->aimMode == 0 && state != 7 && state != 3) {
                    SetPlayerAimMode(self, -1);
                }
                break;
            case 7: {
                PlacedObject* o = (PlacedObject*)self->targetSwitch;
                self->heading = WrapAngle(ArctangentOfRatio(o->m110.r[0].y, o->m110.r[0].x) + 1.0f);
                self->targetSwitch = 0;
                break;
            }
            case 3:
            default:
                self->heldObject = 0;
                break;
            }
            if (state == 2) {
                if (self->targetCurve != 0) {
                    self->penalizedTarget = self->targetCurve;
                } else if (self->targetPoint != 0) {
                    self->penalizedTarget = self->targetPoint;
                } else if (self->targetNode != 0) {
                    self->penalizedTarget = self->targetNode;
                } else if (self->targetTrack != 0) {
                    self->penalizedTarget = self->targetTrack;
                } else {
                    self->penalizedTarget = 0;
                }
            }
            self->eightWayHalf = -1;
            self->targetMode = -1;
            self->targetCurve = 0;
            self->targetPoint = 0;
            self->targetNode = 0;
            self->targetTrack = 0;
            if (self->forcedOnOffObject != 0) {
                SetOnOffObjectForcedState((void*)self->forcedOnOffObject, 0);
                self->forcedOnOffObject = 0;
            }
            self->f268C = 0;
            if (PS(void*, 0x26A4) != 0) {
                ReleaseSoundLevel((SoundLevelEntry*)(PS(void*, 0x26A4)));
                PS(void*, 0x26A4) = 0;
            }
            BaseObject* o = PS(BaseObject*, 0x272C);
            if (o != 0) {
                o->desc->m03(o);
            }
            break;
        }
        case 11:
            SetColliderAnchors(self, 0, 0, 3, 0);
            SetColliderTreeContactsDropped(self, 0);
            break;
        case 10: {
            BaseObject* o = (BaseObject*)self->f25D8[2];
            self->aimTarget = 0;
            self->boundObject = 0;
            if (o != 0) {
                o->desc->m03(o);
            }
            break;
        }
        case 12:
            RemoveCameraControllers(g_camera, 0xF, 6, (CameraController*)((u8*)g_camera + 0x460), self, 0);
            if (D_00270454 != 0) {
                PopStackElement((ElementStack*)g_elementStack);
            }
            break;
        case 9:
            self->walkerHost = 0;
            self->desc05()->m4F(self, 0);
            break;
        case 0:
            switch (self->aimMode) {
            case 6:
                SetPlayerAimMode(self, 4);
                break;
            case 7:
                SetPlayerAimMode(self, 5);
                break;
            case 8:
            case 9:
                SetPlayerAimMode(self, -1);
                break;
            }
            break;
        case 1:
            break;
        case 13:
            self->flags538 &= ~((u64)1 << 40);
            self->hook = self->f273C;
            if (self->stateNodes[13] != 0) {
                SetTurningColliderFollowedMesh(self, (Collider*)self->stateNodes[13], 1);
            }
            break;
        }

        switch (state) {
        case 0:
            walkerId = 0x146;
            self->f118C = 0;
            walker = self->stateGraph;
            if (self->state == 2) {
                s32 late = self->f2250;
                if (late == -1) {
                    f32 limit = 0.95f;
                    if (self->subState == 3) {
                        limit = 1.25f;
                    }
                    late = limit < g_gameTime[0] - self->stateStartTime;
                }
                if (late == 1 && FindStateEntryIndex((StateGraph*)walker, 0x14A)) {
                    walkerId = 0x14A;
                } else if (FindStateEntryIndex((StateGraph*)walker, 0x149)) {
                    walkerId = 0x149;
                }
            }
            layers = 3;
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            break;
        case 1:
            anim = (void*)self->sixWayBlend;
            break;
        case 5:
            anim = (void*)self->eightWayBlend;
            break;
        case 2:
            if (self->jumpKind == -1) {
                self->jumpKind = 0;
            }
            self->f2250 = -1;
            self->f2498 = 0;
            PS(f32, 0x249C) = 3.40282347e+38f;
            break;
        case 3: {
            self->linkReturnState = -1;
            self->linkTowardRamp = self->linkMoveRamp = 1.0f;
            anim = self->linkBlend;
            self->linkPushTime = g_gameTime[0];
            start = 0.5f;
            SetTurningColliderLinkFlag(self, 0);
            speed = 0.0f;
            PS(Attachment*, 0x251C)->mode0 = 2;
            PS(Attachment*, 0x251C)->mode1 = 2;
            PlacedObject* p = (PlacedObject*)self->f61C;
            p->desc02()->m2B(p);
            PS(Attachment*, 0x2520)->mode1 = 2;
            p = (PlacedObject*)self->f23D0;
            p->desc02()->m2B(p);
            Vec02 pos;
            Mat02 rotA;
            Mat02 rotB;
            f32 heading;
            ComputePlayerLinkPose(self, &pos, &rotA, &rotB);
            Vu0::Q(PS(Vec02, 0x22F0)) = Vu0::Sub(Vu0::Q(((PlacedObject*)self->f61C)->pos), Vu0::Q(pos));
            MultiplyMatrices3x3(&rotA, &((PlacedObject*)self->f61C)->rot, &PS(Mat02, 0x2300));
            MultiplyMatrices3x3(&rotB, &((PlacedObject*)self->f23D0)->rot, &PS(Mat02, 0x2330));
            TriggerScriptEvent((BaseObject*)self->boundObject, 2, 0, 0);
            BaseObject* o = (BaseObject*)self->boundObject;
            o->desc->m17(o, self);
            GetLinkedObjectHeading(self, &heading);
            f32 back = WrapAngle(heading + 3.14159274f);
            s32 kind = 1;
            if (self->boundObject != 0) {
                kind = AT(s32, self->boundObject, 0xA0);
            }
            switch (kind) {
            case 2:
                self->heading = back;
                self->linkReversed = 1;
                break;
            case 1:
                self->heading = heading;
                self->linkReversed = 0;
                break;
            case 0:
                if (__builtin_fabsf(WrapAngle(heading - self->stickHeading)) < 1.57079637f) {
                    self->heading = heading;
                    self->linkReversed = 0;
                } else {
                    self->heading = back;
                    self->linkReversed = 1;
                }
                break;
            }
            u128 zero = Vu0::Zero();
            sound = AT(s32, self->boundObject, 0xA8);
            SetPlayerAimMode(self, 1);
            for (Collider* c = (Collider*)AT(BaseObject*, self->boundObject, 0x18); c != 0; c = (Collider*)c->parent) {
                if (c->desc->flags & 2) {
                    if ((c->mode450 != 3 && c->positionAttachment != 0 && c->positionAttachment->mode0 == 1) ||
                        (c->mode470 != 3 && c->orientationAttachment != 0 && c->orientationAttachment->mode1 == 1)) {
                        Attach03* a = TakeAttachRecord((World*)self->world);
                        a->owner = self;
                        a->target = c;
                        AddColliderAttachment(c, a);
                        self->linkSystem = a;
                        break;
                    }
                }
            }
            Vu0::Q(self->headingVelocity) = zero;
            PlacePlayerOnLinkedObject(self);
            break;
        }
        case 7: {
            TriggerScriptEvent((BaseObject*)self->aimCurve, 2, 0, 0);
            BaseObject* o = (BaseObject*)self->aimCurve;
            o->desc->m17(o, self);
            SetFlaggedLinkContactMask(self, (BaseObject*)self->aimCurve, 1);
            self->pathStickSide = -1;
            void* track = (void*)self->aimCurve;
            TrackShape_175170* s = AT(TrackShape_175170*, track, 0x34);
            s32 turn = AT(s32, track, 0x58);
            Vec02 a;
            Vec02 b;
            switch (turn) {
            case 0:
                self->pathFlipped = 0;
                break;
            case 1:
                self->pathFlipped = 1;
                break;
            default: {
                if (s->desc->m2 != 0) {
                    s->desc->m2(s, self->pathPos + D_00274F14, &a, 0);
                    if (s->desc->m2 != 0) {
                        s->desc->m2(s, self->pathPos - D_00274F14, &b, 0);
                    }
                }
                TransformPointBetweenFrames((PlacedObject*)(AT(void*, self->aimCurve, 0x18)), 0, &a, &a);
                TransformPointBetweenFrames((PlacedObject*)(AT(void*, self->aimCurve, 0x18)), 0, &b, &b);
                Vec02 d;
                *(u128*)&d = NormalizeOrElse_175170(Vu0::Sub(Vu0::Vec::Of(a), Vu0::Vec::Of(b)), Vu0::Vec::Of(g_unitZVector)).q;
                self->pathFlipped = d.z < -g_steepSlopeThreshold;
                break;
            }
            }
            f32 len = PS(f32, 0x220C);
            self->pathPos = len;
            if (s->looped == 0) {
                if (self->pathFlipped != 0) {
                    self->pathPos = Clamp_175170(len, s->lengths[0] + D_00274F00, s->lengths[s->count - 1] - D_00274F04);
                } else {
                    self->pathPos = Clamp_175170(len, s->lengths[0] + D_00274F04, s->lengths[s->count - 1] - D_00274F00);
                }
            }
            if (s->desc->m2 != 0) {
                s->desc->m2(s, self->pathPos, &a, 0);
            }
            TransformPointBetweenFrames((PlacedObject*)(AT(void*, self->aimCurve, 0x18)), 0, &a, &a);
            TransformPointBetweenFrames(self, 0, (Vec02*)&self->f23E0, &b);
            Vu0::Q(self->pathPoseOffset) = Vu0::Sub(Vu0::Q(a), Vu0::Q(b));
            sound = AT(s32, self->aimCurve, 0x50);
            Vu0::Q(self->poseOffset) = Vu0::Sub(Vu0::Q(self->focusPoint), Vu0::Q(a));
            break;
        }
        case 8: {
            SetPlayerAimMode(self, -1);
            sound = 0x59;
            SetFlaggedLinkContactMask(self, (BaseObject*)self->ledgeCollider, 1);
            Vec02 pos;
            Mat02 m;
            Vec02 k;
            TransformPointBetweenFrames((PlacedObject*)self->ledgeCollider, 0, (Vec02*)self->ledgeLocalPoint, &pos);
            Vu0::Q(k) = Vu0::FromFloat(-1.0f);
            Vu0::Q(m.r[0]) = Vu0::MulX(Vu0::Q(self->ledgeOffset), Vu0::Q(k));
            BuildPerpendicularPair(&m.r[0], &m.r[1], &g_unitZVector, &g_unitZVector);
            Vu0::Q(pos) = Vu0::Sub(Vu0::Q(pos), Vu0::Rotate(m, Vu0::Q(self->ledgeHandOffset)));
            anim = PS(void*, 0x1038);
            Vu0::Q(self->ledgeSlack) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(pos));
            self->pathPoseOffset = D_00248D30;
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            break;
        }
        case 4:
            if (PS(void*, 0x2490) != 0) {
                AT(Vec02, PS(void*, 0x2490), 0x300) = *(Vec02*)D_00263970;
            }
            if (PS(void*, 0x2494) != 0) {
                AT(Vec02, PS(void*, 0x2494), 0x300) = *(Vec02*)D_00263970;
            }
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            SetPlayerAimMode(self, -1);
            self->f580 = 0;
            self->pulseFadeStart = 3.40282347e+38f;
            break;
        case 6: {
            s32 loud = 0;
            switch (self->targetMode) {
            case 2:
                StopPlayerAnimation(self);
                StartSoundEffect(0x4D, 0, self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
                loud = 1;
                SetPooledObjectPlayerHold((PooledObject*)self->heldObject, 1);
                break;
            case 5:
                TriggerScriptEvent((BaseObject*)self->targetNode, 2, 0, 0);
                ((BaseObject*)self->targetNode)->desc->m17((BaseObject*)self->targetNode, self);
                SetFlaggedLinkContactMask(self, (BaseObject*)self->targetNode, 1);
                layers = 1;
                break;
            case 4: {
                void* track = self->targetTrack;
                layers = 1;
                TriggerScriptEvent((BaseObject*)track, 2, 0, 0);
                ((BaseObject*)track)->desc->m17((BaseObject*)track, self);
                SetFlaggedLinkContactMask(self, (BaseObject*)track, 1);
                self->pathStickSide = -1;
                Vec02 dir;
                Vec02 tan;
                TrackShape_175170* s = AT(TrackShape_175170*, track, 0x34);
                if (s->desc->m1 != 0) {
                    s->desc->m1(s, self->trackPos, 0, &tan);
                }
                TransformDirectionBetweenFrames((PlacedObject*)(AT(void*, track, 0x18)), 0, &tan, &dir);
                dir.z = 0.0f;
                AsVec_175170(dir) = NormalizeOrElse_175170(Vu0::Vec::Of(dir), Vu0::Vec::Of(g_unitXVector));
                s32 back = 1;
                if (!(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(dir), Vu0::Q(self->m110.r[0]))) < D_00263990)) {
                    back = 0;
                }
                self->trackReversed = back;
                break;
            }
            case 7:
                self->desc02()->m20(self, (Vec02*)&D_00248D30);
                loud = 1;
                self->desc02()->m21(self, (Vec02*)&D_00248D30);
                Vu0::Q(self->headingVelocity) = Vu0::Zero();
                ActivateSwitchedCollider(self->targetSwitch);
                break;
            case 3: {
                BaseObject* o = PS(BaseObject*, 0x272C);
                if (o != 0) {
                    o->desc->m02(o);
                    loud = 1;
                }
                if (HasNoActiveObject89(self)) {
                    StartSoundEffect(0x94, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect94Volume, 0.0f, 0.0f, 0, 0);
                } else {
                    StartSoundEffect(0x7E, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect7EVolume, 0.0f, 0.0f, 0, 0);
                }
                break;
            }
            case 0:
            case 1:
                loud = 1;
                if (self->state != 2 || (self->subState != 12 && self->subState != 13)) {
                    StartSoundEffect(0x94, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect94Volume, 0.0f, 0.0f, 0, 0);
                }
                break;
            }
            self->onOffPhase = -1;
            if (loud) {
                PS(void*, 0x26A4) = PushSoundLevel(-20);
            }
            break;
        }
        case 9: {
            Vec02 d;
            if (self->walkerHost != 0) {
                Vu0::Q(d) = Vu0::Sub(Vu0::Q(((PlacedObject*)self->walkerHost)->v140), Vu0::Q(g_player->v140));
            } else {
                Vu0::Q(d) = Vu0::Sub(Vu0::Q(g_camera->position), Vu0::Q(g_player->v140));
            }
            self->heading = ArctangentOfRatio(d.y, d.x);
            TurnColliderTowardHeading(self);
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            SetPlayerAimMode(self, -1);
            break;
        }
        case 11:
            SetPlayerAimMode(self, -1);
            SetColliderAnchors(self, 3, 0, 3, 0);
            SetColliderTreeContactsDropped(self, 1);
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            self->groundContact = 0;
            break;
        case 10:
            SetPlayerAimMode(self, -1);
            self->foundNodeCount = 0;
            TurnPlayerToClass75AheadMask8(self);
            break;
        case 12:
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            break;
        case 13:
            self->f273C = self->hook;
            self->hook = 0;
            self->flags538 |= (u64)1 << 40;
            self->radius3CC = D_00262E30;
            if (self->stateNodes[13] != 0) {
                SetTurningColliderFollowedMesh(self, 0, 0);
            }
            self->headingVelocity = D_00248D30;
            SetPlayerAimMode(self, -1);
            break;
        case 16:
            self->headingVelocity = D_00248D30;
            break;
        case 14: {
            BaseObject* o = (BaseObject*)self->contactOwner;
            if (IsObjectAttached(o)) {
                TakeCountedColliderTouch((CountedCollider*)self->contactOwner, self, 1);
            }
            o = (BaseObject*)self->contactOwner;
            o->desc->m02(o);
            o = (BaseObject*)self->contactOwner;
            o->desc->m15(o, self);
            o = (BaseObject*)self->contactOwner;
            o->desc->m03(o);
            anim = PS(void*, 0x274C);
            self->headingVelocity = D_00248D30;
            break;
        }
        case 15:
            anim = PS(void*, 0x2754);
            self->headingVelocity = D_00248D30;
            break;
        }
        ReleaseFarPlayerLinks(self);
    }

    if (self->subState != sub) {
        switch (self->subState) {
        case 17:
            self->eightWayHalf = -1;
            break;
        case 5: {
            Collider* held = (Collider*)self->heldObject;
            self->heldObject = 0;
            InitContactPairFlags(held->world, held);
            break;
        }
        case 4:
            if (state != 6 || self->targetMode != 2) {
                Collider* held = (Collider*)self->heldObject;
                self->heldObject = 0;
                InitContactPairFlags(held->world, held);
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            self->headingVelocity = D_00248D30;
            break;
        case 9:
            if (self->leapTarget != 0) {
                Collider* c = AT(Collider*, self->leapTarget, 0x60);
                if (c != 0) {
                    c->partMode = 0;
                }
                self->leapTarget = 0;
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            self->headingVelocity = D_00248D30;
            break;
        case 10:
            if (state != 6 || self->targetMode != 5) {
                self->targetNode = 0;
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 11:
            if (state != 6 || self->targetMode != 4) {
                self->targetTrack = 0;
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 13:
            if (state != 6 || self->targetMode != AT(s32, self->targetPoint, 0x58)) {
                self->targetPoint = 0;
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 12:
            if (state != 6 || self->targetMode != AT(s32, self->targetCurve, 0x40)) {
                self->targetCurve = 0;
            }
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 7:
        case 8: {
            if (self->aimMode == -1) {
                self->aimTarget = 0;
                self->boundObject = 0;
            }
            BaseObject* o = (BaseObject*)self->f25D8[1];
            if (o != 0) {
                o->desc->m03(o);
            }
            o = (BaseObject*)self->f25D8[3];
            if (o != 0) {
                o->desc->m03(o);
            }
            break;
        }
        case 44:
            SetColliderTreeContactsDropped(self, 0);
            FillMemory(&self->touchedObject, 0, 0x20);
        case 14:
        case 15:
            ((Attachment*)self->selfPoseSource)->mode0 = -1;
            self->desc02()->m2B(self);
            break;
        case 23:
            if (state == 7) {
                SetPlayerAimMode(self, self->aimAnim10 != 0 ? 10 : 2);
            }
            break;
        case 34: {
            f32 full = 1.0f;
            SetVolumeChannelFactor(5, 0, full);
            SetVolumeChannelFactor(5, 1, full);
            break;
        }
        case 39:
        case 47:
            AT(Vec02, PS(void*, 0x2490), 0x300) = D_00248D30;
            break;
        case 28:
            if (self->forcedOnOffObject != 0) {
                SetOnOffObjectForcedState((void*)self->forcedOnOffObject, 0);
                self->forcedOnOffObject = 0;
            }
            break;
        case 55: {
            BaseObject* o = (BaseObject*)self->f25D8[4];
            if (o != 0) {
                o->desc->m03(o);
            }
            break;
        }
        }

        switch (sub) {
        case -1:
            break;
        case 0: {
            Vec02 v;
            self->steerKeepsDirection = 0;
            self->f2498 = 1;
            self->jumpStickPhase = 0;
            f32 now = g_gameTime[0];
            self->stickReleaseTime = now;
            self->stickFullTime = now;
            self->jumpStartTime = now;
            self->jumpSpeed = D_00262E14 * Fpu::Sqrt(self->gravityScale);
            self->groundContact = 0;
            StartSoundEffect(0x4F, 0, self, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            ComputePlayerJumpVelocity(self, &v);
            switch (self->jumpKind) {
            case 1:
                anim = PS(void*, 0x1028);
                break;
            case 4:
                self->jumpSpeed *= D_00262E1C;
                anim = PS(void*, 0x1028);
                break;
            case 3:
                self->jumpSpeed *= D_00262E18;
                anim = PS(void*, 0x1028);
                break;
            case 0:
            case 2:
                if (self->jumpKind == 2) {
                    anim = PS(void*, 0x1024);
                } else {
                    anim = PS(void*, 0x1020);
                }
                break;
            }
            if (anim == 0) {
                anim = PS(void*, 0x1020);
            }
            if (self->jumpKind == 4 && self->stickLevel == 0.0f) {
                ComputePolarOffset((Vec3*)&v, self->heading, 100.0f, v.z);
                self->jumpStickPhase = 3;
            } else {
                ComputePolarOffset((Vec3*)&v, self->stickHeading, self->jumpSpeed * self->stickLevel, v.z);
            }
            self->desc02()->m20(self, &v);
            break;
        }
        case 1:
            skip = 1;
            break;
        case 2:
            if (self->subState != 1 && self->subState != 5) {
                switch (self->jumpKind) {
                case 1:
                case 3:
                case 4:
                    anim = PS(void*, 0x1028);
                    break;
                case 0:
                    anim = PS(void*, 0x1020);
                    break;
                case 2:
                    anim = PS(void*, 0x1024);
                    break;
                }
                start = GetAnimationMarkerTime((Animation*)anim, 0x134);
            } else {
                skip = 1;
            }
            break;
        case 4:
            ((Attachment*)self->selfPoseSource)->mode0 = 4;
            self->desc02()->m2B(self);
            if (self->state == 2) {
                skip = 1;
            } else {
                anim = PS(void*, 0x1020);
            }
            InitContactPairFlags(((Collider*)self->heldObject)->world, (Collider*)self->heldObject);
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            break;
        case 9: {
            ((Attachment*)self->selfPoseSource)->mode0 = 4;
            self->desc02()->m2B(self);
            if (self->state == 2) {
                skip = 1;
            } else {
                anim = PS(void*, 0x1020);
            }
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            Collider* c = AT(Collider*, self->leapTarget, 0x60);
            anim = PS(void*, 0x1030);
            if (c != 0) {
                c->partMode = 3;
            }
            break;
        }
        case 10:
        case 11: {
            Vec02 v;
            ComputeUpwardBoostVelocity(self, &v);
            self->desc02()->m20(self, &v);
            ((Attachment*)self->selfPoseSource)->mode0 = 4;
            self->desc02()->m2B(self);
            anim = PS(void*, 0x1030);
            self->f2498 = 0;
            AsVec_175170(self->headingVelocity) = Vu0::Vec::Zero();
            StartSoundEffect(0x50, 0, 0, 0, 3000.0f, 300.0f, D_00263994, D_00263998, 0.0f, 0, 0);
            break;
        }
        case 12:
        case 13:
        case 14:
        case 15:
            skip = 1;
            ((Attachment*)self->selfPoseSource)->mode0 = 4;
            self->desc02()->m2B(self);
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            self->f2498 = 0;
            if (sub == 12 || sub == 13) {
                StartSoundEffect(0x94, 0, 0, &self->v140, 3000.0f, 300.0f, g_soundEffect94Volume, 0.0f, 0.0f, 0, 0);
            }
            break;
        case 5: {
            Vec02 v;
            anim = PS(void*, 0xE2C);
            Vu0::Q(v) = Vu0::Add(Vu0::MulX(Vu0::Q(self->rot.r[2]), Vu0::Scalar(Fpu::Sqrt(self->gravityScale) * 800.0f)), Vu0::Q(self->v150));
            self->desc02()->m20(self, &v);
            self->f2498 = 1;
            break;
        }
        case 6:
            self->f2498 = 1;
            self->steerKeepsDirection = 1;
            self->jumpStickPhase = 2;
            self->jumpSpeed = D_00262E14 * Fpu::Sqrt(self->gravityScale);
            self->v2290 = self->v150;
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            self->groundContact = 0;
            anim = PS(void*, 0x1020);
            self->v2290.z = 0.0f;
            break;
        case 44:
            self->f2498 = 1;
            self->groundContact = 0;
            if (self->f2730 != 0) {
                anim = self->subStateAnims[43];
            } else {
                anim = PS(void*, 0x1020);
            }
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            if (self->touchedObject != 0 && IsObjectOfKind((BaseObject*)self->touchedObject, 0x70)) {
                self->heading = ArctangentOfRatio(self->v150.y, self->v150.x);
                TurnColliderTowardHeading(self);
            }
            ((Attachment*)self->selfPoseSource)->mode0 = 4;
            self->desc02()->m2B(self);
            SetColliderTreeContactsDropped(self, 1);
            self->groundContact = 0;
            break;
        case 7:
            self->foundNodeCount = 0;
            self->steerKeepsDirection = 1;
            sound = 10;
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            anim = PS(void*, 0x25C0);
            TurnPlayerToClass75AheadMask4(self);
            self->aimEndTime = g_gameTime[0] + D_0026399C;
            break;
        case 8:
            Vu0::Q(self->headingVelocity) = Vu0::Zero();
            self->steerKeepsDirection = 1;
            self->foundNodeCount = 0;
            anim = self->markerAnim;
            break;
        case 3: {
            Vec02 v;
            self->f2498 = 0;
            anim = PS(void*, 0x1034);
            ComputeUpwardBoostVelocityUnitSlope(self, &v);
            self->desc02()->m20(self, &v);
            break;
        }
        case 16:
        case 21:
            switch (self->targetMode) {
            case 0:
                anim = PS(void*, 0xB24);
                break;
            case 2:
                anim = PS(void*, 0xE24);
                break;
            case 1:
            case 3:
                anim = PS(void*, 0xC34);
                break;
            case 5:
                walker = self->stateGraph;
                walkerId = 0x14C;
                break;
            case 4:
                if (AT(s32, self->targetTrack, 0x40) != 0 && self->pathLeanBlend != 0) {
                    anim = self->pathLeanBlend;
                    self->pathLean = self->pathLeanRate = 0.0f;
                } else {
                    walker = self->stateGraph;
                    walkerId = 0x14D;
                }
                layers = 3;
                break;
            case 6:
                anim = PS(void*, 0x1014);
                break;
            case 7:
                anim = 0;
                break;
            }
            break;
        case 17:
            switch (self->targetMode) {
            case 0:
                speed = 2.0f;
                anim = PS(void*, 0xB20);
                if (self->forcedOnOffObject == 0) {
                    if (self->targetCurve != 0) {
                        void* o = self->targetCurve;
                        if (AT(s32, o, 0x4C) == 0) {
                            self->forcedOnOffObject = 0;
                        } else if (AT(s32, o, 0x48) != 0) {
                            self->forcedOnOffObject = AT(s32, o, 0x48);
                        } else {
                            self->forcedOnOffObject = (s32)self->ownOnOffObject;
                            ResetPlayerOnOffObject(self);
                            OnOffObject* p = (OnOffObject*)self->forcedOnOffObject;
                            p->desc->m15(p, AT(BaseObject*, self->targetCurve, 0x18));
                            ((OnOffObject*)self->forcedOnOffObject)->obj = AT(Arr63*, self->targetCurve, 0x34);
                        }
                    } else if (self->targetPoint != 0) {
                        void* o = self->targetPoint;
                        if (AT(s32, o, 0x68) == 0) {
                            self->forcedOnOffObject = 0;
                        } else if (AT(s32, o, 0x64) != 0) {
                            self->forcedOnOffObject = AT(s32, o, 0x64);
                        } else {
                            self->forcedOnOffObject = (s32)self->ownOnOffObject;
                            ResetPlayerOnOffObject(self);
                            OnOffObject* p = (OnOffObject*)self->forcedOnOffObject;
                            p->desc->m15(p, AT(BaseObject*, self->targetPoint, 0x18));
                            ((OnOffObject*)self->forcedOnOffObject)->f38C = 1;
                            ((OnOffObject*)self->forcedOnOffObject)->v400 = AT(Vec02, self->targetPoint, 0x40);
                            ((OnOffObject*)self->forcedOnOffObject)->orbitRadius = AT(f32, self->targetPoint, 0x5C);
                        }
                    }
                    if ((OnOffObject*)self->forcedOnOffObject == self->ownOnOffObject) {
                        const Vec02* z = &D_00248D30;
                        OnOffObject* p = (OnOffObject*)self->forcedOnOffObject;
                        p->desc02()->m1D(p, (Vec02*)z);
                        p = (OnOffObject*)self->forcedOnOffObject;
                        p->desc02()->m1E(p, (Mat02*)&g_identityMatrix);
                        p = (OnOffObject*)self->forcedOnOffObject;
                        p->desc02()->m20(p, (Vec02*)z);
                        p = (OnOffObject*)self->forcedOnOffObject;
                        p->desc02()->m21(p, (Vec02*)z);
                    }
                    if (self->forcedOnOffObject != 0) {
                        ((OnOffObject*)self->forcedOnOffObject)->switchedCollider = self;
                        SetOnOffObjectForcedState((void*)self->forcedOnOffObject, 1);
                    }
                }
                break;
            case 1:
                speed = 1.75f;
                anim = PS(void*, 0xC30);
                break;
            case 3:
                anim = (void*)self->eightWayBlend;
                break;
            }
            break;
        case 20:
            switch (self->targetMode) {
            case 2:
                anim = PS(void*, 0xE20);
                break;
            case 3:
                anim = (void*)self->sixWayBlend;
                break;
            case 4:
                anim = PS(void*, 0x1010);
                break;
            }
            break;
        case 19:
            switch (self->targetMode) {
            case 0:
                anim = PS(void*, 0xB2C);
                break;
            case 1:
                anim = PS(void*, 0xC3C);
                break;
            }
            break;
        case 18:
            switch (self->targetMode) {
            case 0:
                anim = PS(void*, 0xB28);
                break;
            case 1:
                anim = PS(void*, 0xC38);
                break;
            }
            break;
        case 23:
            anim = PS(void*, 0x1060);
            if (anim == 0) {
                anim = PS(void*, 0x1068);
                start = ((Animation*)anim)->length * 0.5f;
                speed = 0.5f;
            }
            self->pathSpeedEased = 0.0f;
            break;
        case 24:
            anim = self->f1064;
            break;
        case 25:
            anim = self->f105C;
            break;
        case 26:
            anim = self->f105C;
            speed = -1.0f;
            break;
        case 27:
            anim = PS(void*, 0x1068);
            self->pathFlipped = !self->pathFlipped;
            break;
        case 28:
        case 29:
        case 30:
            anim = self->subStateAnims[sub];
            if (sub == 28 && PS(void*, 0x267C) != 0) {
                self->forcedOnOffObject = PS(s32, 0x267C);
                SetOnOffObjectForcedState(PS(void*, 0x267C), 1);
            }
            if (sub == 30) {
                self->desc05()->m4F(self, 3);
            }
            PopActiveSequenceElement(self->world);
            break;
        case 31:
            anim = PS(void*, 0x25B8);
            sound = 14;
            break;
        case 32:
            anim = PS(void*, 0x25BC);
            break;
        case 33:
            if (PS(void*, 0x25CC) != 0) {
                anim = PS(void*, 0x25CC);
            }
            PushCameraController(g_camera, 6, (CameraController*)((u8*)g_camera + 0x460), self, 0);
            break;
        case 34: {
            f32 dim = 0.6f;
            SetVolumeChannelFactor(5, 0, dim);
            SetVolumeChannelFactor(5, 1, dim);
            StartCameraSounds((CameraSoundOwner*)((u8*)g_camera + 0x460));
            RequestCameraSnap(g_camera, 0);
            ((CaptionBox_175170_eu*)&g_typedTextCaptionBox)->child = self->pendingCaption;
            self->pendingCaption = 0;
            PushStackElement((ElementStack*)g_elementStack, &g_typedTextCaptionBox);
            break;
        }
        case 35:
            if (PS(void*, 0x25D0) != 0) {
                anim = PS(void*, 0x25D0);
            }
            RemoveCameraControllers(g_camera, 0xF, 6, (CameraController*)((u8*)g_camera + 0x460), self, 0);
            RequestCameraSnap(g_camera, 0);
            break;
        case 39:
        case 45:
        case 46:
        case 47:
            if (sub == 45) {
                u128 vel = Vu0::Q(self->v150);
                if (-250.0f < Vu0::ToFloatMoved(Vu0::Dot(vel, Vu0::Q(self->headingMatrix.r[0])))) {
                    sub = 46;
                } else {
                    f32 len = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(vel, vel)));
                    f32 k = D_002639A0[0] + len * (D_002639A0[1] + len * D_002639A0[2]);
                    f32* range = (f32*)&g_unitRange;
                    f32 lo = range[0];
                    f32 hi = range[1];
                    f32 r;
                    if (k < lo) {
                        r = lo;
                    } else if (hi < k) {
                        r = hi;
                    } else {
                        r = k;
                    }
                    self->heading = WrapAngle(self->heading + WrapAngle(ArctangentOfRatio(self->v150.y, self->v150.x) + 3.14159274f - self->heading) * r);
                    TurnColliderTowardHeading(self);
                }
            }
            anim = self->subStateAnims[sub];
            if (sub == 47 || sub == 39) {
                if (PS(void*, 0x2490) != 0) {
                    AT(Vec02, PS(void*, 0x2490), 0x300) = *(Vec02*)D_00263980;
                }
            }
            if (sub == 47) {
                Vec02 d;
                Vu0::Q(d) = Vu0::Sub(Vu0::Q(g_camera->position), Vu0::Q(self->v140));
                self->heading = ArctangentOfRatio(d.y, d.x);
            }
            break;
        case 41:
        case 48: {
            Vec02 d;
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(g_camera->position), Vu0::Q(self->v140));
            self->heading = ArctangentOfRatio(d.y, d.x);
            anim = self->subStateAnims[sub];
            break;
        }
        case 36:
        case 42:
        case 43:
            anim = self->subStateAnims[sub];
            break;
        case 40:
        case 49:
            self->desc02()->m21(self, (Vec02*)&D_00248D30);
            self->heading = self->stickHeading = ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x);
            anim = self->subStateAnims[sub];
            break;
        case 37:
        case 38:
            flag = 0;
            self->heading = self->stickHeading = ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x);
            anim = self->subStateAnims[sub];
            if (D_002639B8 != 0) {
                speed = 0.0f;
            }
            break;
        case 50:
        case 51:
        case 52:
            if (self->stateAnimPlayer != 0 && AT(void*, self->stateAnimPlayer, 8) == self->linkBlend) {
                skip = 1;
                break;
            }
            anim = self->linkBlend;
            speed = 0.0f;
            start = ((Animation*)anim)->length * 0.5f;
            break;
        case 53:
            walker = self->stateGraph;
            walkerId = 0x14B;
            break;
        case 55: {
            Vec02 v;
            u128 vel = Vu0::Q(self->v150);
            f32 most = D_00262E2C;
            Vu0::Q(v) = vel;
            s32 slow = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(vel, vel))) < D_002639B0[0];
            if (slow) {
                ComputePolarOffset((Vec3*)&v, self->heading, most, 0.0f);
            } else {
                f32 len = Vu0::ToFloatMoved(Vu0::Length(vel));
                if (len < most) {
                    Vu0::Q(v) = Vu0::MulX(vel, Vu0::Scalar(most / len));
                }
            }
            self->desc02()->m20(self, &v);
            v.z = 0.0f;
            Vu0::Vec len = NormalizeInPlace_175170(v, D_00248D30);
            f32 k = Vu0::ToFloatMoved(len) / self->radius3CC;
            Vec02 spin;
            Vu0::Q(spin) = Vu0::FromFloats(-k * v.y, k * v.x, 0.0f);
            self->desc02()->m21(self, &spin);
            anim = PS(void*, 0x25D4);
            if (self->f25D8[4] != 0) {
                if (MaskWorldBitsBySave() & 0x400) {
                    BaseObject* o = (BaseObject*)self->f25D8[4];
                    o->desc->m02(o);
                }
            }
            break;
        }
        case 54:
        case 56:
            anim = PS(void*, 0x25D4);
            break;
        case 57:
            anim = PS(void*, 0x2760);
            break;
        case 58:
            anim = PS(void*, 0x2764);
            break;
        }
    }

    if (state != self->state) {
        self->state = state;
        self->stateStartTime = g_gameTime[0];
    }
    if (sub != self->subState) {
        self->subState = sub;
        self->subStateStartTime = g_gameTime[0];
    }
    SelectPlayerStateAnimation(self);
    SetPlayerPartLayers(self, layers);
    if (sound != -1) {
        StartSoundEffect(sound, 0, 0, &self->v140, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    if (!skip) {
        StopPlayerAnimation(self);
        if (anim != 0) {
            AnimArg_175170 args[2];
            AnimArg_175170* arg = args;
            if (self->heldObject != 0) {
                arg->id = 0x61;
                arg->value = self->heldObject;
                arg++;
            }
            CreateAnimationPlayer((Animation*)anim, (Animation*)self, arg - args, (TargetBinding*)args, flag, (AnimationPlayer**)&self->stateAnimPlayer, start, speed);
        } else if (walker != 0) {
            self->stateWalker = CreateStateWalker((StateGraph*)walker, self, walkerId, flag);
        }
    }
}
#undef PS
