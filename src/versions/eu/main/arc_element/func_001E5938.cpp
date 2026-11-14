// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the caption box D_002701F8 keeps its palette at 0x5AC (US 0x320), and the screen is 234.3
// rows high where US has 246.4 (the unprojection's vertical scale).
struct Cap_eu_1E5938 { u8 pad[0x5AC]; s32 palette; };

void ChoosePlayerLinkedColliderTarget(PlayerLinkedCollider* self)
{
    if (HasObjectPoolChoice(self->f618) != 0) {
        ObjectPool* pool = self->f618;
        u8* place = (u8*)pool + 0x60;
        u8* e0 = (u8*)pool + 0xE0;
        u8* ang = (u8*)pool + 0x150;
        f32 cx;
        f32 cy;
        Vec02 a;
        Vec02 b;
        Vec02 lo;
        Vec02 hi;
        Collider** list;
        s32 n;

        GetTextPanelCenter(&g_typedTextCaptionBox, &cx, &cy);
        Vu0::Set(a, Vu0::FromFloats(cx * 0.003125f - 1.0f, 1.0f - cy * 0.00426794f, 10.0f));
        Vu0::Set(b, Vu0::FromFloats(cx * 0.003125f - 1.0f, 1.0f - cy * 0.00426794f, 80000.0f));
        UnprojectCameraPoint(g_camera, (f32*)&a, &lo);
        UnprojectCameraPoint(g_camera, (f32*)&b, &hi);
        Vec02 pos;
        SpanHit hit;
        PushBackMemoryMark();
        GatherCollidersInBox(self->world, 0, &lo, &hi, IsPlayerLinkedColliderCandidate, self, &n, &list);
        u8* found = FindNearestSpanObject(0, &lo, &hi, n, (Collider**)list, (ColliderSpan*)&hit);
        if (found != 0 && *(s32*)(found + 8) != 1) {
            *(u8**)e0 = found;
            TransformPointBetweenFrames(0, (PlacedObject*)found, (Vec02*)&hit, (Vec02*)&pool->fF0);
            pos = hit.point;
            if (IsObjectOfKind((BaseObject*)(*(void**)(found + 0x50)), 0xE) != 0 || IsObjectOfKind((BaseObject*)(*(void**)(found + 0x50)), 7) != 0) {
                ((Cap_eu_1E5938*)&g_typedTextCaptionBox)->palette = 2;
            } else if (IsObjectOfKind((BaseObject*)(*(void**)(found + 0x50)), 8) != 0) {
                ((Cap_eu_1E5938*)&g_typedTextCaptionBox)->palette = 1;
            } else {
                u8* c = found;
                while (c != 0) {
                    s32 i;
                    for (i = 0; i < self->f638; i++) {
                        if (((u8**)self->f63C)[i] == c) {
                            break;
                        }
                    }
                    if (i < self->f638) {
                        break;
                    }
                    c = *(u8**)(c + 0x18);
                }
                if (c != 0) {
                    ((Cap_eu_1E5938*)&g_typedTextCaptionBox)->palette = 1;
                } else {
                    ((Cap_eu_1E5938*)&g_typedTextCaptionBox)->palette = 0;
                }
            }
        } else {
            *(u8**)e0 = 0;
            *(Vec02*)(e0 + 0x10) = hi;
            ((Cap_eu_1E5938*)&g_typedTextCaptionBox)->palette = 0;
            pos = hi;
        }
        PopBackMemoryMark();
        Vec02 c0;
        Mat02 rot;
        Vec02 d;
        GetPlacementRecordTransform((FrameSource*)place, &c0, rot.r, 0);
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(c0));
        *(f32*)(ang + 8) = ArctangentOfRatio(d.y, d.x);
        *(f32*)(ang + 4) = ArctangentOfRatio(d.z, Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(d), Vu0::Q(d)))));
    }
}
