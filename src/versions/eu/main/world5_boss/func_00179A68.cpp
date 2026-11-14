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
            if (self->f6E0 != 0 && g_gameTime - self->buttonPressTime < D_00263C50[0]) {
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
        TransformPointBetweenFrames(0, (PlacedObject*)self->f660, &self->f664->v140, &at);
        f32 u = (at.y - D_00263CA0[0]) / D_00263CA0[1];
        f32 v = (at.z - D_00263CB0[0]) / D_00263CB0[1];
        ApproachValueWithRamp(self->aimX, u + D_00263C78[1], 0.0f, (RampProfile*)D_00263C58, &hiX);
        ApproachValueWithRamp(self->aimX, u + D_00263C78[0], 0.0f, (RampProfile*)D_00263C58, &loX);
        ApproachValueWithRamp(self->aimY, v + D_00263C78[1], 0.0f, (RampProfile*)D_00263C58, &hiY);
        ApproachValueWithRamp(self->aimY, v + D_00263C78[0], 0.0f, (RampProfile*)D_00263C58, &loY);
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
        self->aimRateX = ApproachValueWithRamp(self->aimRateX, tx, dt, (RampProfile*)D_00263C68, 0);
        self->aimRateY = ApproachValueWithRamp(self->aimRateY, ty, dt, (RampProfile*)D_00263C68, 0);
        self->aimX = ClampBetween(self->aimX + dt * self->aimRateX, u + D_00263C78[0], u + D_00263C78[1]);
        f32 w = ClampBetween(self->aimY + dt * self->aimRateY, v + D_00263C78[0], v + D_00263C78[1]);
        self->aimY = w;
        f32 h = self->aimX;
        Vu0::Q(pos) = Vu0::FromFloats(at.x, D_00263CA0[0] + h * (D_00263CA0[1] + h * D_00263CA0[2]),
                                      D_00263CB0[0] + w * (D_00263CB0[1] + w * D_00263CB0[2]));
        TransformPointBetweenFrames((PlacedObject*)self->f660, 0, &pos, &pos);
        TransformPointBetweenFrames(0, (PlacedObject*)self->f660, &pos, (Vec02*)((u8*)self->f650 + 0xF0));
        ProjectPointToCamera(g_camera, &pos, (f32*)((u8*)&D_00270650 + 0x580));
        for (i = 0; i < 2; i++) {
            Vec02 dir;
            *(Vu0::Vec*)&dir = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(self->f674[i]->v140));
            BuildBasisFromXAndZHint(&dir, &g_unitZVector, &mats[i]);
            TransformRotationBetweenFrames(0, (PlacedObject*)self->f674[i]->parent, &mats[i], &mats[i]);
        }
        ApproachValueWithRamp(self->poseX, D_00263C90[1], 0.0f, (RampProfile*)D_00263C58, &hiX);
        ApproachValueWithRamp(self->poseX, D_00263C90[0], 0.0f, (RampProfile*)D_00263C58, &loX);
        ApproachValueWithRamp(self->poseY, D_00263C90[1], 0.0f, (RampProfile*)D_00263C58, &hiY);
        ApproachValueWithRamp(self->poseY, D_00263C90[0], 0.0f, (RampProfile*)D_00263C58, &loY);
        RampProfile3 prof = *(RampProfile3*)D_00263C80;
        if (self->mode == 2) {
            tx = loX + (pad->stickX + 1.0f) * ((hiX - loX) * 0.5f);
            ty = loY + (stickY + 1.0f) * ((hiY - loY) * 0.5f);
        } else {
            f32 k = (g_gameTime - self->modeStartTime) / ((World5ModeColliderSource*)self->modeAnimPlayer)->lengthRecord->length;
            f32 s = D_00263CC0[0] + k * (D_00263CC0[1] + k * D_00263CC0[2]);
            tx = (loX + hiX) * 0.5f;
            ty = hiY;
            s = ClampBetween(s, g_unitRange.lo, g_unitRange.hi);
            prof.maxSpeed *= s;
            prof.endSpeed *= s;
        }
        self->poseRateX = ApproachValueWithRamp(self->poseRateX, tx, dt, (RampProfile*)&prof, 0);
        self->poseRateY = ApproachValueWithRamp(self->poseRateY, ty, dt, (RampProfile*)&prof, 0);
        self->poseX = ClampBetween(self->poseX + dt * self->poseRateX, D_00263C90[0], D_00263C90[1]);
        self->poseY = ClampBetween(self->poseY + dt * self->poseRateY, D_00263C90[0], D_00263C90[1]);

        Mat02 pitch;
        Mat02 yaw;
        Mat02 face;
        Vec02 to;
        Vec02 rel;
        Mat02 tilt;
        Vec02 axis;
        TransformPointBetweenFrames(0, (PlacedObject*)self->f668, &((PlacedObject*)self->f660)->v140, &rel);
        f32 sx = pad->stickX;
        if (rel.x < 0.0f) {
            sx = -sx;
        }
        BuildAxisAngleMatrix(&g_unitXVector, &pitch, D_00263CD0[0] + sx * (D_00263CD0[1] + sx * D_00263CD0[2]));
        f32 sy = pad->stickY;
        BuildAxisAngleMatrix(&g_unitYVector, &yaw, D_00263CE0[0] + sy * (D_00263CE0[1] + sy * D_00263CE0[2]));
        *(Vu0::Vec*)&to = Vu0::Sub(Vu0::Vec::Of(((PlacedObject*)self->f660)->v140), Vu0::Vec::Of(self->v140));
        BuildBasisFromXAndZHint(&to, &g_unitZVector, &face);
        f32 speed = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(self->v150), Vu0::Q(self->v150))));
        f32 angle = ClampBetween(D_00263CF0[0] + speed * (D_00263CF0[1] + speed * D_00263CF0[2]), D_00263D00[0], D_00263D00[1]);
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
        Vu0::Q(to) = Vu0::Sub(Vu0::Vec::Of(pos), Vu0::Vec::Of(self->f67C->v140)).q;
        BuildBasisFromXAndZHint(&to, &g_unitZVector, &aim);
        TransformRotationBetweenFrames(0, (PlacedObject*)self->f67C->linkRecord->p60, &aim, &aim);
        break;
    }
    default:
        BuildAxisAngleMatrix(&g_unitZVector, &self->m620, self->heading);
        for (i = 0; i < 2; i++) {
            mats[i] = self->f674[i]->m1A0;
        }
        aim = g_identityMatrix;
        break;
    }
    Mat02 rot;
    for (i = 0; i < 2; i++) {
        ApproachRotationWithRamp(&self->f674[i]->rot, &mats[i], (RampProfile*)D_00263D08, dt, &rot, 0);
        self->f674[i]->desc02()->m1E(self->f674[i], &rot);
    }
    if (self->f67C->orientationAttachment == 0) {
        MulRotationRowsIndexed(&aim, aim, self->f67C->m1A0);
        ApproachRotationWithRamp(&self->f67C->rot, &aim, (RampProfile*)D_00263D18, dt, &rot, 0);
        self->f67C->desc02()->m1E(self->f67C, &rot);
    }
    HandleStepSequenceSkipButtons(self, pad);
    ClearRootTries(self);
}
