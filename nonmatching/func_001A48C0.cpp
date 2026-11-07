// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 604/620 (97.4%), checked 2026-11-07
// NEAR: 8 lines differ: the four `max.s` (`A >? B` of poseA[n], poseB[n] as two for-loop tests):
//       retail loads poseA first but its max.s reads poseB as the first operand ($f1) and writes
//       $f1; ours (A >? B) reads A first and writes $f0; B >? A loads B first (17 lines). The loop
//       structure, typed stores and branch shapes are otherwise retail's. ~40 compiles.
#include "common.h"
#include "pair_controller.h"
#include "paired_object.h"
#include "hit_target.h"
#include "object_creator.h"
#include "globals.h"
#include "world.h"

int GetCurrentEntryVariant(void);
void AppendToList(void* list, void* item);
s32 IsObjectOfKind(void* self, s32 kind);
struct Controlled558 {
    u8 pad[0x558];
    void* controller;
};

struct Controlled678 {
    u8 pad[0x678];
    void* controller;
};

void PostLoadPlacedObject(void* self);
void* FindFirstObjectByIdMode4(World* w, s32 id, void* self);
s32 GatherObjectsByMode(World* w, s32 a, s32 id, void* self, s32 mode, void** out);
void* CreateObjectCopy(void* obj, World* w, s32 n);

void func_001A48C0(PairController* self)
{
    PostLoadPlacedObject(self);
    if (self->id64C == GetCurrentEntryVariant()) {
        u8* s = (u8*)self;
        void* first = FindFirstObjectByIdMode4(g_currentWorld, self->id2D8, self);
        self->f354 = first;
        ((Controlled678*)first)->controller = self;
        PairedObject* a = (PairedObject*)FindFirstObjectByIdMode4(g_currentWorld, self->id2D0, self);
        a->controller = self;
        PairedObject* b = (PairedObject*)FindFirstObjectByIdMode4(g_currentWorld, self->id2D4, self);
        b->controller = self;
        if (self->id2DC != -1) {
            self->target = (ObjectCreator*)FindFirstObjectByIdMode4(g_currentWorld, self->id2DC, self);
            ((HitTarget*)self->target)->controller = self;
        }
        s32 i;
        for (i = 0; (f32)i < (self->poseA[1] >? self->poseB[1]); i++) {
            void* o;
            if (i == 0) {
                o = a;
            } else {
                o = CreateObjectCopy(a, g_currentWorld, *(s32*)((u8*)a + 0x18));
            }
            AppendToList(s + 0x374, o);
        }
        for (i = 0; (f32)i < (self->poseA[9] >? self->poseB[9]); i++) {
            void* o;
            if (i == 0) {
                o = b;
            } else {
                o = CreateObjectCopy(b, g_currentWorld, *(s32*)((u8*)b + 0x18));
            }
            AppendToList(s + 0x390, o);
        }
        for (i = 0; i < self->idCount; i++) {
            void* found[4];
            s32 n = GatherObjectsByMode(g_currentWorld, 0x104, self->ids[i], self, 2, found);
            void* hit = 0;
            for (s32 k = 0; k < n; k++) {
                if (IsObjectOfKind(found[k], 0x44) != 0) {
                    hit = found[k];
                    break;
                }
            }
            ((Controlled558*)hit)->controller = self;
            AppendToList(s + 0x3A0, hit);
        }
    }
}
