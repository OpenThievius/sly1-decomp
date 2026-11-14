// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the caption box D_002701F8 keeps its state at 0x570 (US 0x260) and its text is wide, so the
// first character is a halfword (US a byte); the announcement flag of D_0026F138 is at 0x974
// (US 0x464).
struct Ann_eu_1F4AE0 { u8 pad[0x974]; s32 announce; };
struct Cap_eu_1F4AE0 { u8 pad00[8]; u16 t8; u8 pad0A[0x570 - 0x0A]; s32 f570; };
void UpdateObjectSubGroup(ObjectSubGroup* self, f32 dt)
{
    Vec02 local;
    Vec02 radius;
    UpdatePlacedObject(self, dt);
    switch (self->state) {
    case 5: {
        f32 t = self->fadeTime;
        f32 zero = 0.0f;
        if (zero < t) {
            if (t < g_gameClock.time) {
                StartObjectSubGroupFade(self);
                self->fadeTime = zero;
            }
        }
        return;
    }
    case 4:
        if (D_0026FA64 == 0) {
            if (D_002701C4 != 0 || ((Cap_eu_1F4AE0*)&g_typedTextCaptionBox)->f570 == 1 || ((Cap_eu_1F4AE0*)&g_typedTextCaptionBox)->f570 == 2
                || (((Cap_eu_1F4AE0*)&g_typedTextCaptionBox)->f570 == 3 && ((Cap_eu_1F4AE0*)&g_typedTextCaptionBox)->t8 != 0)) {
                D_0026F138.vt->m15(&D_0026F138);
            } else {
                SetScreenElementHoldTime(&D_0026F138, 0.0f);
                SetElementTextFromPackedEntry(&D_0026F138, GetEntryIdByKey(self->levelEntry));
                ((Ann_eu_1F4AE0*)&D_0026F138)->announce = 0;
                D_0026F138.vt->m14(&D_0026F138);
            }
        }
    case 0:
    case 1:
    case 3:
        break;
    default:
        return;
    }
    Collider* player = (Collider*)GetActiveSwitchedCollider();
    if (player == 0) {
        return;
    }
    TransformPointBetweenFrames(0, self, &player->v140, &local);
    s32 inside = IsPointInsideFaceTree((TreeNode03*)self->faceTree, (FacePoint*)&local);
    s32 near = 0;
    if (inside == 0 && self->nearCheck != 0 && __builtin_fabsf(local.z) < 300.0f) {
        if (Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(local), Vu0::Q(local)))) <= 1000.0f) {
            near = 1;
        }
    }
    switch (self->state) {
    case 3:
        if (inside != 0) {
            StartObjectSubGroupFinish(self);
        } else if (near != 0) {
            if (D_0026F388 == 0) {
                Camera* c = g_camera;
                u128 d = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(c->position));
                u128 ones = Vu0::Ones();
                Vu0::Q(radius) = Vu0::FromFloat(100.0f);
                if ((Vu0::PlaneSigns(Vu0::Q(c->planes[0]), Vu0::Q(c->planes[1]), Vu0::Q(c->planes[2]), d, ones, Vu0::Q(radius)) ^ 0xF0) == 0) {
                    SetObjectSubGroupState(self, 4);
                }
            }
        }
        break;
    case 4:
        if (inside != 0) {
            StartObjectSubGroupFinish(self);
        } else if (near == 0) {
            SetObjectSubGroupState(self, 3);
        }
        break;
    case 1:
        if (inside != 0) {
            SetObjectSubGroupState(self, 0);
        } else if (self->nearWaitTime < g_gameClock.time - self->stateStartTime) {
            SetObjectSubGroupState(self, 3);
        }
        break;
    case 0:
        if (inside == 0) {
            SetObjectSubGroupState(self, 1);
        }
        break;
    }
}
