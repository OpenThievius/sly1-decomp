// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the D_00270650 aim at 0x580 (US 0x270; PAL's ScreenElement is 0x310 bytes longer).

void ControlWorld5ModeCollider(World5ModeCollider* self, f32 dt, PadRecord* pad)
{
    Mat02 mats[2];
    s32 i;
    Mat02 aim;
    s32 key;
    f32 hiX;
    f32 loX;
    f32 hiY;
    f32 loY;

    if (self->mode == 3 && HasSpareCount() != 0) {
        World5ModeColliderSource* src = (World5ModeColliderSource*)self->modeAnimPlayer;
        if (src == 0 || src->f18 == 0.0f) {
            self->desc05()->m50(self);
        } else {
            if (pad->flags & 0x40) {
                ClearPadPressedBits(pad, 0x40);
                self->buttonPressTime = g_gameTime;
            }
            if (self->pressArmed != 0 && g_gameTime - self->buttonPressTime < g_world5ButtonWindow[0]) {
                self->desc05()->m50(self);
            }
        }
    }
    if (pad->buttons & 0x80) {
        GetStateWalkerCurrentKey((StateWalker*)self->stateWalker, &key);
        if (key >= 0x44F) {
            if (key < 0x451) {
                key = 0x451;
            } else if (key < 0x453) {
                key = 0x44F;
            }
        }
        SetStateWalkerTarget((StateWalker*)self->stateWalker, key);
    }
    switch (self->mode) {
    case 2:
    case 3:
    case 4: {
        Vec02 at;
        Vec02 pos;
        TransformPointBetweenFrames(0, (PlacedObject*)self->aimFrame, &self->aimTargetObject->v140, &at);
        f32 u = (at.y - g_world5AimMapY[0]) / g_world5AimMapY[1];
        f32 v = (at.z - g_world5AimMapZ[0]) / g_world5AimMapZ[1];
        ApproachValueWithRamp(self->aimX, u + g_world5AimMargin[1], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &hiX);
        ApproachValueWithRamp(self->aimX, u + g_world5AimMargin[0], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &loX);
        ApproachValueWithRamp(self->aimY, v + g_world5AimMargin[1], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &hiY);
        ApproachValueWithRamp(self->aimY, v + g_world5AimMargin[0], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &loY);
        f32 stickY = pad->stickY;
        if (g_saveData->optionFlags & 0x800) {
            stickY = -stickY;
        }
        f32 tx;
        f32 ty;
        if (self->mode == 2) {
            tx = loX + (pad->stickX + 1.0f) * ((hiX - loX) * 0.5f);
            ty = loY + (stickY + 1.0f) * ((hiY - loY) * 0.5f);
        } else {
            tx = (loX + hiX) * 0.5f;
            ty = (loY + hiY) * 0.5f;
        }
        self->aimRateX = ApproachValueWithRamp(self->aimRateX, tx, dt, (RampProfile*)g_world5AimSpeedRamp, 0);
        self->aimRateY = ApproachValueWithRamp(self->aimRateY, ty, dt, (RampProfile*)g_world5AimSpeedRamp, 0);
        self->aimX = ClampBetween(self->aimX + dt * self->aimRateX, u + g_world5AimMargin[0], u + g_world5AimMargin[1]);
        f32 w = ClampBetween(self->aimY + dt * self->aimRateY, v + g_world5AimMargin[0], v + g_world5AimMargin[1]);
        self->aimY = w;
        f32 h = self->aimX;
        Vu0::Q(pos) = Vu0::FromFloats(at.x, g_world5AimMapY[0] + h * (g_world5AimMapY[1] + h * g_world5AimMapY[2]),
                                      g_world5AimMapZ[0] + w * (g_world5AimMapZ[1] + w * g_world5AimMapZ[2]));
        TransformPointBetweenFrames((PlacedObject*)self->aimFrame, 0, &pos, &pos);
        TransformPointBetweenFrames(0, (PlacedObject*)self->aimFrame, &pos, (Vec02*)((u8*)self->f650 + 0xF0));
        ProjectPointToCamera(g_camera, &pos, (f32*)((u8*)&g_spinningSpriteElement + 0x580));
        for (i = 0; i < 2; i++) {
            Vec02 dir;
            *(Vu0::Vec*)&dir = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(self->turnedParts[i]->v140));
            BuildBasisFromXAndZHint(&dir, &g_unitZVector, &mats[i]);
            TransformRotationBetweenFrames(0, (PlacedObject*)self->turnedParts[i]->parent, &mats[i], &mats[i]);
        }
        ApproachValueWithRamp(self->poseX, g_world5SteerLimits[1], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &hiX);
        ApproachValueWithRamp(self->poseX, g_world5SteerLimits[0], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &loX);
        ApproachValueWithRamp(self->poseY, g_world5SteerLimits[1], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &hiY);
        ApproachValueWithRamp(self->poseY, g_world5SteerLimits[0], 0.0f, (RampProfile*)g_world5AimBoundsRamp, &loY);
        RampProfile3 prof = *(RampProfile3*)g_world5SteerRamp;
        if (self->mode == 2) {
            tx = loX + (pad->stickX + 1.0f) * ((hiX - loX) * 0.5f);
            ty = loY + (stickY + 1.0f) * ((hiY - loY) * 0.5f);
        } else {
            f32 k = (g_gameTime - self->modeStartTime) / ((World5ModeColliderSource*)self->modeAnimPlayer)->lengthRecord->length;
            f32 s = g_world5SteerProgressCoefficients[0] + k * (g_world5SteerProgressCoefficients[1] + k * g_world5SteerProgressCoefficients[2]);
            tx = (loX + hiX) * 0.5f;
            ty = hiY;
            s = ClampBetween(s, g_unitRange.lo, g_unitRange.hi);
            prof.maxSpeed *= s;
            prof.endSpeed *= s;
        }
        self->poseRateX = ApproachValueWithRamp(self->poseRateX, tx, dt, (RampProfile*)&prof, 0);
        self->poseRateY = ApproachValueWithRamp(self->poseRateY, ty, dt, (RampProfile*)&prof, 0);
        self->poseX = ClampBetween(self->poseX + dt * self->poseRateX, g_world5SteerLimits[0], g_world5SteerLimits[1]);
        self->poseY = ClampBetween(self->poseY + dt * self->poseRateY, g_world5SteerLimits[0], g_world5SteerLimits[1]);

        Mat02 pitch;
        Mat02 yaw;
        Mat02 face;
        Vec02 to;
        Vec02 rel;
        Mat02 tilt;
        Vec02 axis;
        TransformPointBetweenFrames(0, (PlacedObject*)self->f668, &((PlacedObject*)self->aimFrame)->v140, &rel);
        f32 sx = pad->stickX;
        if (rel.x < 0.0f) {
            sx = -sx;
        }
        BuildAxisAngleMatrix(&g_unitXVector, &pitch, g_world5PitchCoefficients[0] + sx * (g_world5PitchCoefficients[1] + sx * g_world5PitchCoefficients[2]));
        f32 sy = pad->stickY;
        BuildAxisAngleMatrix(&g_unitYVector, &yaw, g_world5YawCoefficients[0] + sy * (g_world5YawCoefficients[1] + sy * g_world5YawCoefficients[2]));
        *(Vu0::Vec*)&to = Vu0::Sub(Vu0::Vec::Of(((PlacedObject*)self->aimFrame)->v140), Vu0::Vec::Of(self->v140));
        BuildBasisFromXAndZHint(&to, &g_unitZVector, &face);
        f32 speed = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(self->v150), Vu0::Q(self->v150))));
        f32 angle = ClampBetween(g_world5TiltCoefficients[0] + speed * (g_world5TiltCoefficients[1] + speed * g_world5TiltCoefficients[2]), g_world5TiltLimits[0], g_world5TiltLimits[1]);
        Vu0::Vec n;
        n.q = Vu0::FromFloats(-self->v150.y, self->v150.x, 0.0f);
        *(Vu0::Vec*)&axis = n;
        *(Vu0::Vec*)&axis = Vu0::NormalizeOr(Vu0::Vec::Of(axis), Vu0::Vec::Of(g_unitXVector));
        BuildAxisAngleMatrix(&axis, &tilt, angle);
        Mat02 m3;
        Mat02 m2;
        Mat02 m1;
        RotationProductInto(&m1, tilt, face);
        RotationProductInto(&m2, m1, yaw);
        RotationProductInto(&m3, m2, pitch);
        self->m620 = m3;
        Vu0::Q(to) = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(self->thirdTurnedPart->v140)).q;
        BuildBasisFromXAndZHint(&to, &g_unitZVector, &aim);
        TransformRotationBetweenFrames(0, (PlacedObject*)self->thirdTurnedPart->linkRecord->p60, &aim, &aim);
        break;
    }
    default:
        BuildAxisAngleMatrix(&g_unitZVector, &self->m620, self->heading);
        for (i = 0; i < 2; i++) {
            mats[i] = self->turnedParts[i]->m1A0;
        }
        aim = g_identityMatrix;
        break;
    }
    Mat02 rot;
    for (i = 0; i < 2; i++) {
        ApproachRotationWithRamp(&self->turnedParts[i]->rot, &mats[i], (RampProfile*)g_world5PartRotationRamp, dt, &rot, 0);
        self->turnedParts[i]->desc02()->m1E(self->turnedParts[i], &rot);
    }
    if (self->thirdTurnedPart->orientationAttachment == 0) {
        MulRotationRowsIndexed(&aim, aim, self->thirdTurnedPart->m1A0);
        ApproachRotationWithRamp(&self->thirdTurnedPart->rot, &aim, (RampProfile*)g_world5AimRotationRamp, dt, &rot, 0);
        self->thirdTurnedPart->desc02()->m1E(self->thirdTurnedPart, &rot);
    }
    HandleStepSequenceSkipButtons(self, pad);
    ClearRootTries(self);
}
