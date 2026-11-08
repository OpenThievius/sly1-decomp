// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: all but the first ArctangentOfRatio's arguments are retail's, registers and frame
// included: retail loads d.y into $f12 before the jal and d.x into $f13 in its delay slot, ours
// the other way round (two words). The same call matches elsewhere (agent.cpp's func_001C7A60,
// camera.cpp's ConvertOffsetToSpherical); here no form moved it: the coordinates as locals in
// either order, d declared in the loop, Set or a frame store for d, an inline helper for the two
// angles. What placed the rest: i set before GatherObjectsById, entries[i] with e->obj passed on
// (an unreversed first loop), the view test's flags XORed into a word of their own, the second
// angle in a variable of its own (rise, pitch), and T217D_440's markers at 0x358 (two hoisted
// bases, the object's and the effect's). PAL's T217D_440 is laid out differently (+0x28C).
#include "common.h"
#include "screen_element.h"
#include "placed_object.h"
#include "vu0.h"

struct CameraHeading {
    u8 pad0[0x40];
    s32 f40[4];             // 0x40: the eye
    f32 planes[3][4];       // 0x50: the view planes' normals, as columns (camera.h)
    u8 pad80[0x1C4 - 0x80];
    f32 f1C4;               // 0x1C4
    u8 pad1C8[0x1E0 - 0x1C8];
    f32 f1E0;               // 0x1E0
    u8 pad1E4[0x468 - 0x1E4];
    f32 heading;            // 0x468
    u8 pad46C[0x470 - 0x46C];
    f32 pitch;              // 0x470
    u8 pad474[0x478 - 0x474];
    f32 f478;
};

extern CameraHeading* g_camera;
extern u8 g_currentWorld[];
extern f32 g_gameClock[];
struct __attribute__((aligned(16))) PanelEntryPosition { s32 a, b, c, d; };
struct SortEntry {
    void* obj;
    f32 key;
};
s32 IsObjectAttached(void* obj);
void GetNumberedItemFlag(void* obj, s32* out);
void SetEffectPhase(void* handle, s32 mode);
void* FillMemory(void* block, s32 value, s32 size);
f32 WrapAngle(f32 a);
s32 CompareEntriesByAttachedKey(SortEntry* a, SortEntry* b);
s32 CompareEntriesFlaggedLast(SortEntry* a, SortEntry* b);

struct PanelEntry {
    void* obj;              // 0x00
    f32 key;                // 0x04
    f32 radius;             // 0x08
    u8 pad0C[4];
    PanelEntryPosition v;   // 0x10
};

s32 GatherObjectsById(s32 a, s32 b, s32 c, void* d, s32 e, void* f);
void HeapSortRecords(void* base, s32 count, s32 size, s32 (*cmp)(SortEntry* a, SortEntry* b));
f32 ArctangentOfRatio(f32 y, f32 x);
void CopyMemory(void* dst, void* src, u32 size);
void* CreateEffect(s32 kind, s32 owner);
extern f32 D_00261274;

void CollectPanelEntriesOfClass(T217D_440* self, s32 kind, void* a2, void* a3, s32 limit, s32 a5, f32 range)
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
            f32 rise = ArctangentOfRatio(d.z, Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(v, v))));
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
