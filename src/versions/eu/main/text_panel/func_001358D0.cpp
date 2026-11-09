// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the caption box's fields are later (state at 0x570, blockA at 0x5BC, countA at 0x5DC,
// count at 0x5E0, the markers at 0x5E4); the code is US's.
struct PanelMarkers_1358D0_eu {
    u8 pad0[0x570];
    s32 state;                  // 0x570
    u8 pad574[0x5BC - 0x574];
    s32 blockA[4];              // 0x5BC
    u8 pad5CC[0x5DC - 0x5CC];
    s32 countA;                 // 0x5DC
    s32 count;                  // 0x5E0
    T217D_440_Marker markers[31]; // 0x5E4
};

void CollectPanelEntriesOfClass(PanelMarkers_1358D0_eu* self, s32 kind, void* a2, void* a3, s32 limit, s32 a5, f32 range)
{
    PanelEntry entries[0x80];
    void* objs[0x80];
    Vec02 d;
    s32 want;
    s32 i = 0;
    s32 n = GatherObjectsById(*(s32*)g_currentWorld, 0x105, kind, 0, 0x80, objs);
    PanelEntry* e;
    for (; i < n; i++) {
        e = &entries[i];
        e->obj = objs[i];
        ((void (*)(void*, PanelEntryPosition*, f32*))a2)(e->obj, &e->v, &e->radius);
        e->key = Vu0::Distance(e->v, *(PanelEntryPosition*)g_camera->f40) - e->radius;
    }
    HeapSortRecords(entries, n, 0x20, kind == 0x2E ? CompareEntriesFlaggedLast : CompareEntriesByAttachedKey);
    s32 mayStart = 1;
    FillMemory(self->blockA, 0, 0x10);
    if (!(D_00261274 < g_gameClock[1] - *(f32*)&self->countA)) {
        mayStart = 0;
    }
    for (i = 0; i < n;) {
        e = &entries[i];
        if (kind == 0x2E) {
            GetNumberedItemFlag(e->obj, &want);
            want = want == 0 && self->state == 1 && i < limit && e->key < range;
        } else {
            want = self->state == 1 && IsObjectAttached(e->obj) && i < limit && e->key < range;
        }
        CameraHeading* cam = g_camera;
        u128 ones = Vu0::Ones();
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(e->v), Vu0::Q(cam->f40));
        u32 signs = Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), Vu0::Q(d), ones, Vu0::ScalarAt(e->radius)) ^ 0xF0;
        s32 visible = signs == 0;
        if (want && !visible) {
            f32 yaw = ArctangentOfRatio(d.y, d.x);
            u128 v = Vu0::Q(d);
            f32 rise = ArctangentOfRatio(d.z, Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(v, v))));
            yaw = WrapAngle(yaw - g_camera->heading);
            f32 pitch = WrapAngle(rise - g_camera->pitch);
            if (g_camera->f1C4 * (g_camera->f1E0 * 0.45f) < yaw) {
                self->blockA[0] = 1;
            } else if (yaw < g_camera->f1C4 * (g_camera->f1E0 * -0.45f)) {
                self->blockA[1] = 1;
            } else if (g_camera->f1C4 * 0.45f < pitch) {
                self->blockA[2] = 1;
            } else if (pitch < g_camera->f1C4 * -0.45f) {
                self->blockA[3] = 1;
            }
        }
        s32 next = i + 1;
        void* effect = 0;
        s32 j;
        for (j = 0; j < self->count; j++) {
            if (self->markers[j].obj == e->obj) {
                effect = self->markers[j].effect;
                break;
            }
        }
        if (effect != 0) {
            if (!want) {
                SetEffectPhase(effect, 2);
                CopyMemory(&self->markers[j], &self->markers[j + 1], (self->count - j - 1) * 8);
                self->count--;
            }
        } else if (want && mayStart && visible) {
            void* fx = CreateEffect(0x12, 0);
            if (fx != 0) {
                mayStart = 0;
                (*(void (**)(void*, PanelEntryPosition*, s32, f32))*(void**)fx)(fx, &e->v, 0, 1.0f);
                *(s32*)((u8*)fx + 0x20) = a5;
                *(void**)((u8*)fx + 0x130) = a3;
                *(void**)((u8*)fx + 0x134) = e->obj;
                SetEffectPhase(fx, 0);
                *(f32*)&self->countA = g_gameClock[1];
                self->markers[self->count].obj = e->obj;
                self->markers[self->count].effect = fx;
                self->count++;
            }
        }
        i = next;
    }
}
